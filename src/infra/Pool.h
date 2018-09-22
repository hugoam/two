#pragma once

#include <infra/Array.h>

#include <cassert>
#include <cstddef>

#include <atomic>
#include <type_traits>

#if defined(WIN32)
#include <malloc.h>
#endif

namespace mud
{
	namespace pointermath
	{
		template <typename P, typename T>
		static inline P* add(P* a, T b)
		{
			return (P*)(uintptr_t(a) + uintptr_t(b));
		}

		template <typename P>
		static inline P* align(P* p, size_t alignment)
		{
			// alignment must be a power-of-two
			assert(alignment && !(alignment & alignment - 1));
			return (P*)((uintptr_t(p) + alignment - 1) & ~(alignment - 1));
		}

		template <typename P>
		static inline P* align(P* p, size_t alignment, size_t offset)
		{
			P* const r = align(add(p, offset), alignment);
			assert(pointermath::add(r, -offset) >= p);
			return r;
		}
	}

	class FreeListBase
	{
	public:
		struct Node
		{
			Node* next;
		};
		static Node* init(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra);
	};

	class FreeList : private FreeListBase
	{
	public:
		FreeList() = default;
		FreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra);
		FreeList(const FreeList& rhs) = delete;
		FreeList& operator=(const FreeList& rhs) = delete;
		FreeList(FreeList&& rhs) = default;
		FreeList& operator=(FreeList&& rhs) = default;

		void* pop()
		{
			Node* const head = m_head;
			m_head = head ? head->next : nullptr;
			// this could indicate a use after free
			assert(!m_head || m_head >= m_begin && m_head < m_end);
			return head;
}

		void push(void* p)
		{
			assert(p);
			assert(p >= m_begin && p < m_end);
			// TODO: assert this is one of our pointer (i.e.: it's address match one of ours)
			Node* const head = static_cast<Node*>(p);
			head->next = m_head;
			m_head = head;
		}

		void* current() { return m_head; }

	private:
		Node* m_head = nullptr;

#ifndef NDEBUG
		void* m_begin = nullptr;
		void* m_end = nullptr;
#endif
	};

	class AtomicFreeList : private FreeListBase {
	public:
		AtomicFreeList() = default;
		AtomicFreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra);
		AtomicFreeList(const FreeList& rhs) = delete;
		AtomicFreeList& operator=(const FreeList& rhs) = delete;

		void* pop()
		{
			Node* head = m_head.load(std::memory_order_relaxed);
			while(head && !m_head.compare_exchange_weak(head, head->next, std::memory_order_release, std::memory_order_relaxed))
			{
			}
			return head;
		}

		void push(void* p)
		{
			assert(p);
			Node* head = static_cast<Node*>(p);
			head->next = m_head.load(std::memory_order_relaxed);
			while(!m_head.compare_exchange_weak(head->next, head, std::memory_order_release, std::memory_order_relaxed))
			{
			}
		}

		void* current() { return m_head.load(std::memory_order_relaxed); }

	private:
		std::atomic<Node*> m_head;
	};

#define GENERIC_MAX(a,b) ((a) > (b) ? (a) : (b))

	template <class T, class T_FreeList = FreeList>
	class Arena
	{
	public:
		Arena() = default;

		Arena(const char* name, size_t size)
			: m_begin(malloc(size))
			, m_end(pointermath::add(m_begin, size))
			, m_freelist(m_begin, m_end, sizeof(T), GENERIC_MAX(alignof(T_FreeList), alignof(T)), 0)
			, m_name(name)
		{}

		~Arena()
		{
			free(m_begin);
		}

		void* alloc()
		{
			void* p = m_freelist.pop();
			return p;
		}

		template <typename U = T, typename = typename std::enable_if<std::is_trivially_destructible<U>::value>::type>
		T* alloc(size_t count, size_t alignment = alignof(T))
		{
			return (T*)alloc(count * sizeof(T), alignment);
		}

		void free(void* p)
		{
			if(p) m_freelist.push(p);
		}

		void free(void* p, size_t size)
		{
			if(p) m_freelist.push(p);
		}

		//void reset() { m_allocator.reset(); }

		void* current() { return m_freelist.current(); }

		//void rewind(void* addr) { m_allocator.rewind(addr); }

		template <typename... T_Args>
		T* make(T_Args&&... args)
		{
			void* const p = this->alloc();
			return p ? new(p) T(std::forward<T_Args>(args)...) : nullptr;
		}

		void destroy(T* p)
		{
			p->~T();
			this->free((void*)p);
		}

		Arena(Arena const& rhs) = delete;
		Arena& operator=(Arena const& rhs) = delete;

		const char* m_name = nullptr;
		void* m_begin = nullptr;
		void* m_end = nullptr;
		T_FreeList m_freelist;
	};
}
