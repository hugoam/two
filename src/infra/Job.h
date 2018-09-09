#pragma once

//#define MUD_JOB_FIBERS

#ifdef MUD_JOB_FIBERS
#include <ftl/task_scheduler.h>
#include <ftl/atomic_counter.h>
#undef near
#undef far

namespace mud
{
	using JobSystem = ftl::TaskScheduler;
}

#else
#include <infra/Array.h>

#include <assert.h>

#include <atomic>
#include <functional>
#include <thread>
#include <vector>

#include <cstddef>

#include <condition_variable>
#include <mutex>

#include <type_traits>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#if defined(WIN32)
#include <malloc.h>
#endif

#ifdef WIN32
// Size is chosen so that we can store at least std::function<> and a job size is a multiple of a
// cacheline.
#    define JOB_PADDING (6+8)
#else
#    define JOB_PADDING (6)
#endif

#include <immintrin.h>

#define __i386__

#ifdef __ARM_ACLE
#   include <arm_acle.h>
#   define UTILS_WAIT_FOR_INTERRUPT()   __wfi()
#   define UTILS_WAIT_FOR_EVENT()       __wfe()
#   define UTILS_BROADCAST_EVENT()      __sev()
#   define UTILS_SIGNAL_EVENT()         __sevl()
#   define UTILS_PAUSE()                __yield()
#   define UTILS_PREFETCHW(addr)        __pldx(1, 0, 0, addr)
#else // !__ARM_ACLE
#   if (defined(__i386__) || defined(__x86_64__))
#       define UTILS_WAIT_FOR_INTERRUPT()   _mm_pause();
#       define UTILS_WAIT_FOR_EVENT()       _mm_pause();
#       define UTILS_BROADCAST_EVENT()
#       define UTILS_SIGNAL_EVENT()
#       define UTILS_PAUSE()                _mm_pause();
#       define UTILS_PREFETCHW(addr)        UTILS_PREFETCH(addr)
#   else // !x86
#       define UTILS_WAIT_FOR_INTERRUPT()
#       define UTILS_WAIT_FOR_EVENT()
#       define UTILS_BROADCAST_EVENT()
#       define UTILS_SIGNAL_EVENT()
#       define UTILS_PAUSE()
#       define UTILS_PREFETCHW(addr)        UTILS_PREFETCH(addr)
#   endif // x86
#endif // __ARM_ACLE

namespace mud
{
	inline void* aligned_alloc(size_t size, size_t align) noexcept {
		assert(align && !(align & align - 1));

		void* p = nullptr;

		// must be a power of two and >= sizeof(void*)
		while(align < sizeof(void*)) {
			align <<= 1;
		}

#if defined(WIN32)
		p = ::_aligned_malloc(size, align);
#else
		::posix_memalign(&p, align, size);
#endif
		return p;
}

	inline void aligned_free(void* p) noexcept {
#if defined(WIN32)
		::_aligned_free(p);
#else
		::free(p);
#endif
	}

	/*
	* This allocator can be used with std::vector for instance to ensure all items are aligned
	* to their alignof(). e.g.
	*
	*      template<typename T>
	*      usign aligned_vector = std::vector<T, utils::STLAlignedAllocator<T>>;
	*
	*      aligned_vector<Foo> foos;
	*
	*/
	template<typename TYPE>
	class STLAlignedAllocator {
		static_assert(!(alignof(TYPE) & (alignof(TYPE)-1)), "alignof(T) must be a power of two");

	public:
		using value_type = TYPE;
		using pointer = TYPE*;
		using const_pointer = const TYPE*;
		using reference = TYPE&;
		using const_reference = const TYPE&;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;
		using is_always_equal = std::true_type;

		template<typename T>
		struct rebind { using other = STLAlignedAllocator<T>; };

	public:
		inline STLAlignedAllocator() noexcept = default;

		template<typename T>
		inline explicit STLAlignedAllocator(const STLAlignedAllocator<T>&) noexcept {}

		inline ~STLAlignedAllocator() noexcept = default;

		inline pointer allocate(size_type n) noexcept {
			return (pointer)aligned_alloc(n * sizeof(value_type), alignof(TYPE));
		}

		inline void deallocate(pointer p, size_type) {
			aligned_free(p);
		}

		// stateless allocators are always equal
		template<typename T, typename U>
		friend bool
			operator==(const STLAlignedAllocator<T>& rhs, const STLAlignedAllocator<U>& lhs) {
			return true;
		}

		template<typename T, typename U>
		friend bool
			operator!=(const STLAlignedAllocator<T>& rhs, const STLAlignedAllocator<U>& lhs) {
			return false;
		}
	};

#ifdef __ARM_32BIT_STATE
	// on ARM 32-bits, assume 32-bytes cache lines
	constexpr size_t CACHELINE_SIZE = 32;
#else
	// on ARM64 and x86 we assume 64-bytes cache lines
	constexpr size_t CACHELINE_SIZE = 64;
#endif


	namespace pointermath {

		template <typename P, typename T>
		static inline P* add(P* a, T b) noexcept {
			return (P*)(uintptr_t(a) + uintptr_t(b));
		}

		template <typename P>
		static inline P* align(P* p, size_t alignment) noexcept {
			// alignment must be a power-of-two
			assert(alignment && !(alignment & alignment - 1));
			return (P*)((uintptr_t(p) + alignment - 1) & ~(alignment - 1));
		}

		template <typename P>
		static inline P* align(P* p, size_t alignment, size_t offset) noexcept {
			P* const r = align(add(p, offset), alignment);
			assert(pointermath::add(r, -offset) >= p);
			return r;
		}

	}

	class FreeListBase {
	public:
		struct Node {
			Node* next;
		};
		static Node* init(void* begin, void* end,
			size_t elementSize, size_t alignment, size_t extra) noexcept;
	};

	class FreeList : private FreeListBase {
	public:
		FreeList() noexcept = default;
		FreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra) noexcept;
		FreeList(const FreeList& rhs) = delete;
		FreeList& operator=(const FreeList& rhs) = delete;
		FreeList(FreeList&& rhs) noexcept = default;
		FreeList& operator=(FreeList&& rhs) noexcept = default;

		void* get() noexcept {
			Node* const head = mHead;
			mHead = head ? head->next : nullptr;
			// this could indicate a use after free
			assert(!mHead || mHead >= mBegin && mHead < mEnd);
			return head;
		}

		void put(void* p) noexcept {
			assert(p);
			assert(p >= mBegin && p < mEnd);
			// TODO: assert this is one of our pointer (i.e.: it's address match one of ours)
			Node* const head = static_cast<Node*>(p);
			head->next = mHead;
			mHead = head;
		}

		void *getCurrent() noexcept {
			return mHead;
		}

	private:
		Node* mHead = nullptr;

#ifndef NDEBUG
		// These are needed only for debugging...
		void* mBegin = nullptr;
		void* mEnd = nullptr;
#endif
	};

	class AtomicFreeList : private FreeListBase {
	public:
		AtomicFreeList() noexcept = default;
		AtomicFreeList(void* begin, void* end,
			size_t elementSize, size_t alignment, size_t extra) noexcept;
		AtomicFreeList(const FreeList& rhs) = delete;
		AtomicFreeList& operator=(const FreeList& rhs) = delete;

		void* get() noexcept {
			Node* head = mHead.load(std::memory_order_relaxed);
			while(head && !mHead.compare_exchange_weak(head, head->next,
				std::memory_order_release, std::memory_order_relaxed)) {
			}
			return head;
		}

		void put(void* p) noexcept {
			assert(p);
			Node* head = static_cast<Node*>(p);
			head->next = mHead.load(std::memory_order_relaxed);
			while(!mHead.compare_exchange_weak(head->next, head,
				std::memory_order_release, std::memory_order_relaxed)) {
			}
		}

		void* getCurrent() noexcept {
			return mHead.load(std::memory_order_relaxed);
		}

	private:
		std::atomic<Node*> mHead;
	};

	// ------------------------------------------------------------------------------------------------

	template <
		size_t ELEMENT_SIZE,
		size_t ALIGNMENT = alignof(std::max_align_t),
		size_t OFFSET = 0,
		typename FREELIST = FreeList>
		class PoolAllocator {
		static_assert(ELEMENT_SIZE >= sizeof(void*), "ELEMENT_SIZE must accommodate at least a pointer");
		public:
			// our allocator concept
			void* alloc(size_t size = ELEMENT_SIZE,
				size_t alignment = ALIGNMENT, size_t offset = OFFSET) noexcept {
				assert(size <= ELEMENT_SIZE);
				assert(alignment <= ALIGNMENT);
				assert(offset == OFFSET);
				return mFreeList.get();
			}

			void free(void* p) noexcept {
				mFreeList.put(p);
			}

			size_t getSize() const noexcept { return ELEMENT_SIZE; }

			PoolAllocator(void* begin, void* end) noexcept
				: mFreeList(begin, end, ELEMENT_SIZE, ALIGNMENT, OFFSET) {
			}

			template <typename AREA>
			explicit PoolAllocator(const AREA& area) noexcept
				: PoolAllocator(area.begin(), area.end()) {
			}

			// Allocators can't be copied
			PoolAllocator(const PoolAllocator& rhs) = delete;
			PoolAllocator& operator=(const PoolAllocator& rhs) = delete;

			PoolAllocator() noexcept = default;
			~PoolAllocator() noexcept = default;

			// API specific to this allocator

			void *getCurrent() noexcept {
				return mFreeList.getCurrent();
			}

		private:
			FREELIST mFreeList;
	};

#define UTILS_MAX(a,b) ((a) > (b) ? (a) : (b))

	template <typename T, size_t OFFSET = 0>
	using ObjectPoolAllocator = PoolAllocator<sizeof(T),
		UTILS_MAX(alignof(FreeList), alignof(T)), OFFSET>;

	template <typename T, size_t OFFSET = 0>
	using ThreadSafeObjectPoolAllocator = PoolAllocator<sizeof(T),
		UTILS_MAX(alignof(FreeList), alignof(T)), OFFSET, AtomicFreeList>;


	// ------------------------------------------------------------------------------------------------
	// Areas
	// ------------------------------------------------------------------------------------------------

	class HeapArea {
	public:
		HeapArea() noexcept = default;

		explicit HeapArea(size_t size) {
			if(size) {
				// TODO: policy committing memory
				mBegin = malloc(size);
				mEnd = pointermath::add(mBegin, size);
			}
		}

		~HeapArea() noexcept {
			// TODO: policy for returning memory to system
			free(mBegin);
		}

		HeapArea(const HeapArea& rhs) = delete;
		HeapArea& operator=(const HeapArea& rhs) = delete;
		HeapArea(HeapArea&& rhs) noexcept = delete;
		HeapArea& operator=(HeapArea&& rhs) noexcept = delete;

		void* data() const noexcept { return mBegin; }
		void* begin() const noexcept { return mBegin; }
		void* end() const noexcept { return mEnd; }
		size_t getSize() const noexcept { return uintptr_t(mEnd) - uintptr_t(mBegin); }

	private:
		void* mBegin = nullptr;
		void* mEnd = nullptr;
	};


	// ------------------------------------------------------------------------------------------------
	// Policies
	// ------------------------------------------------------------------------------------------------

	namespace LockingPolicy {

		struct NoLock {
			void lock() noexcept { }
			void unlock() noexcept { }
		};

		class SpinLock {
			std::atomic_flag mLock = { 0 };

		public:
			void lock() noexcept {
				//UTILS_PREFETCHW(&mLock);
#ifdef __ARM_ACLE
				// we signal an event on this CPU, so that the first yield() will be a no-op,
				// and falls through the test_and_set(). This is more efficient than a while { }
				// construct.
				UTILS_SIGNAL_EVENT();
				do {
					yield();
				} while(mLock.test_and_set(std::memory_order_acquire));
#else
				goto start;
				do {
					yield();
				start:;
				} while(mLock.test_and_set(std::memory_order_acquire));
#endif
			}

			void unlock() noexcept {
				mLock.clear(std::memory_order_release);
#ifdef __ARM_ARCH_7A__
				// on ARMv7a SEL is needed
				UTILS_SIGNAL_EVENT();
				// as well as a memory barrier is needed
				__dsb(0xA);     // ISHST = 0xA (b1010)
#else
				// on ARMv8 we could avoid the call to SE, but we'de need to write the
				// test_and_set() above by hand, so the WFE only happens without a STRX first.
				UTILS_BROADCAST_EVENT();
#endif
			}

		private:
			inline void yield() noexcept {
				// on x86 call pause instruction, on ARM call WFE
				UTILS_WAIT_FOR_EVENT();
			}
		};

		using Mutex = std::mutex;

	} // namespace LockingPolicy


	namespace TrackingPolicy {

		struct Untracked {
			Untracked() noexcept = default;
			Untracked(const char* name, size_t size) noexcept { UNUSED(name); UNUSED(size); }
			void onAlloc(void* p, size_t size, size_t alignment, size_t extra) noexcept { UNUSED(p); UNUSED(size); UNUSED(alignment); UNUSED(extra); }
			void onFree(void* p, size_t = 0) noexcept { UNUSED(p); }
			void onReset() noexcept { }
			void onRewind(void* addr) noexcept { UNUSED(addr); }
		};

		// This high watermark tracker works only with allocator that either implement
		// free(void*, size_t), or reset() / rewind()

		struct HighWatermark {
			HighWatermark() noexcept = default;
			HighWatermark(const char* name, size_t size) noexcept
				: mName(name), mSize(uint32_t(size)) { }
			~HighWatermark() noexcept;
			void onAlloc(void* p, size_t size, size_t alignment, size_t extra) noexcept {
				UNUSED(alignment); UNUSED(extra);
				if(!mBase) { mBase = p; }
				mCurrent += uint32_t(size);
				mHighWaterMark = mCurrent > mHighWaterMark ? mCurrent : mHighWaterMark;
			}
			void onFree(void* p, size_t size) noexcept { UNUSED(p); mCurrent -= uint32_t(size); }
			void onReset() noexcept { mCurrent = 0; }
			void onRewind(void const* addr) noexcept { mCurrent = uint32_t(uintptr_t(addr) - uintptr_t(mBase)); }

		private:
			const char* mName = nullptr;
			void* mBase = nullptr;
			uint32_t mSize = 0;
			uint32_t mCurrent = 0;
			uint32_t mHighWaterMark = 0;
		};

	} // namespace TrackingPolicy

	  // ------------------------------------------------------------------------------------------------
	  // Arenas
	  // ------------------------------------------------------------------------------------------------

	template<typename AllocatorPolicy, typename LockingPolicy,
		typename TrackingPolicy = TrackingPolicy::Untracked>
		class Arena {
		public:

			Arena() = default;

			// construct an arena with a name and forward argument to its allocator
			template<typename ... ARGS>
			Arena(const char* name, size_t size, ARGS&& ... args)
				: mArea(size),
				mAllocator(mArea, std::forward<ARGS>(args) ...),
				mListener(name, size),
				mArenaName(name) {
			}

			// allocate memory from arena with given size and alignment
			// (acceptable size/alignment may depend on the allocator provided)
			void* alloc(size_t size, size_t alignment = alignof(std::max_align_t), size_t extra = 0) noexcept {
				std::lock_guard<LockingPolicy> guard(mLock);
				void* p = mAllocator.alloc(size, alignment, extra);
				mListener.onAlloc(p, size, alignment, extra);
				return p;
			}

			// Allocate an array of trivially destructible objects
			// for safety, we disable the object-based alloc method if the object type is not
			// trivially destructible, since free() won't call the destructor and this is allocating
			// an array.
			template <typename T,
				typename = typename std::enable_if<std::is_trivially_destructible<T>::value>::type>
				T* alloc(size_t count, size_t alignment = alignof(T), size_t extra = 0) noexcept {
				return (T*)alloc(count * sizeof(T), alignment, extra);
			}

			// return memory pointed by p to the arena
			// (actual behaviour may depend on allocator provided)
			void free(void* p) noexcept {
				if(p) {
					std::lock_guard<LockingPolicy> guard(mLock);
					mListener.onFree(p);
					mAllocator.free(p);
				}
			}

			// some allocators require the size of the allocation for free
			void free(void* p, size_t size) noexcept {
				if(p) {
					std::lock_guard<LockingPolicy> guard(mLock);
					mListener.onFree(p, size);
					mAllocator.free(p, size);
				}
			}

			// some allocators don't have a free() call, but a single reset() or rewind() instead
			void reset() noexcept {
				std::lock_guard<LockingPolicy> guard(mLock);
				mListener.onReset();
				mAllocator.reset();
			}

			void* getCurrent() noexcept { return mAllocator.getCurrent(); }

			void rewind(void *addr) noexcept {
				std::lock_guard<LockingPolicy> guard(mLock);
				mListener.onRewind(addr);
				mAllocator.rewind(addr);
			}

			// Allocate and construct an object
			template<typename T, size_t ALIGN = alignof(T), typename... ARGS>
			T* make(ARGS&& ... args) noexcept {
				void* const p = this->alloc(sizeof(T), ALIGN);
				return p ? new(p) T(std::forward<ARGS>(args)...) : nullptr;
			}

			// destroys an object created with make<T>() above, and frees associated memory
			template<typename T>
			void destroy(T* p) noexcept {
				if(p) {
					p->~T();
					this->free((void*)p);
				}
			}

			char const* getName() const noexcept { return mArenaName; }

			AllocatorPolicy& getAllocator() noexcept { return mAllocator; }
			AllocatorPolicy const& getAllocator() const noexcept { return mAllocator; }

			TrackingPolicy& getListener() noexcept { return mListener; }
			TrackingPolicy const& getListener() const noexcept { return mListener; }

			HeapArea& getArea() noexcept { return mArea; }
			HeapArea const& getArea() const noexcept { return mArea; }

			void setListener(TrackingPolicy listener) noexcept {
				std::swap(mListener, listener);
			}

			template <typename ... ARGS>
			void emplaceListener(ARGS&& ... args) noexcept {
				mListener.~TrackingPolicy();
				new (&mListener) TrackingPolicy(std::forward<ARGS>(args)...);
			}

			// An arena can't be copied
			Arena(Arena const& rhs) noexcept = delete;
			Arena& operator=(Arena const& rhs) noexcept = delete;

		private:
			HeapArea mArea; // We might want to make that a template parameter too eventually.
			AllocatorPolicy mAllocator;
			LockingPolicy mLock;
			TrackingPolicy mListener;
			char const* mArenaName = nullptr;
	};

	// ------------------------------------------------------------------------------------------------

	// This doesn't implement our allocator concept, because it's too risky to use this as an allocator
	// in particular, doing ArenaScope<ArenaScope>.
	template<typename ARENA>
	class ArenaScope {

		struct Finalizer {
			void(*finalizer)(void* p) = nullptr;
			Finalizer* next = nullptr;
		};

		template <typename T>
		static void destruct(void* p) noexcept {
			static_cast<T*>(p)->~T();
		}

	public:
		explicit ArenaScope(ARENA& allocator)
			: mArena(allocator), mRewind(allocator.getCurrent()) {
		}

		ArenaScope& operator=(const ArenaScope& rhs) = delete;
		ArenaScope(ArenaScope&& rhs) noexcept = delete;
		ArenaScope& operator=(ArenaScope&& rhs) noexcept = delete;

		~ArenaScope() {
			// run the finalizer chain
			Finalizer* head = mFinalizerHead;
			while(head) {
				void* p = pointermath::add(head, sizeof(Finalizer));
				head->finalizer(p);
				head = head->next;
			}
			// ArenaScope works only with Arena that implements rewind()
			mArena.rewind(mRewind);
		}

		template<typename T, size_t ALIGN = alignof(T), typename... ARGS>
		T* make(ARGS&& ... args) noexcept {
			T* o = nullptr;
			if(std::is_trivially_destructible<T>::value) {
				o = mArena.template make<T, ALIGN>(std::forward<ARGS>(args)...);
			}
			else {
				void* const p = (Finalizer*)mArena.alloc(sizeof(T), ALIGN, sizeof(Finalizer));
				if(p != nullptr) {
					Finalizer* const f = static_cast<Finalizer*>(p) - 1;
					// constructor must be called before adding the dtor to the list
					// so that the ctor can allocate objects in a nested scope and have the
					// finalizers called in reverse order.
					o = new(p) T(std::forward<ARGS>(args)...);
					f->finalizer = &destruct<T>;
					f->next = mFinalizerHead;
					mFinalizerHead = f;
				}
			}
			return o;
		}

		void* allocate(size_t size, size_t alignment = 1) noexcept {
			return mArena.template alloc(size, alignment, 0);
		}

		template <typename T>
		T* allocate(size_t size, size_t alignment = alignof(T), size_t extra = 0) noexcept {
			return mArena.template alloc<T>(size, alignment, extra);
		}

		// use with caution
		ARENA& getAllocator() noexcept { return mArena; }

	private:
		ARENA& mArena;
		void* mRewind = nullptr;
		Finalizer* mFinalizerHead = nullptr;
	};

	template <typename TYPE, size_t COUNT>
	class WorkStealingDequeue {
		static_assert(!(COUNT & (COUNT - 1)), "COUNT must be a power of two");
		static constexpr size_t MASK = COUNT - 1;
		std::atomic<int32_t> mTop = { 0 };      // written/read in pop()/steal()
		std::atomic<int32_t> mBottom = { 0 };   // written only in pop(), read in push(), steal()
		TYPE mItems[COUNT];

		TYPE getItemAt(int32_t index) noexcept { return mItems[index & MASK]; }
		void setItemAt(int32_t index, TYPE item) noexcept { mItems[index & MASK] = item; }

	public:
		using value_type = TYPE;

		inline void push(TYPE item) noexcept;
		inline TYPE pop() noexcept;
		inline TYPE steal() noexcept;

		size_t getSize() const noexcept { return COUNT; }

		bool isEmpty() const noexcept {
			uint32_t bottom = (uint32_t)mBottom.load(std::memory_order_relaxed);
			uint32_t top = (uint32_t)mTop.load(std::memory_order_seq_cst);
			return top >= bottom;
		}

		// for debugging only...
		int32_t getCount() const noexcept {
			int32_t bottom = mBottom.load(std::memory_order_relaxed);
			int32_t top = mTop.load(std::memory_order_relaxed);
			return bottom - top;
		}
	};


	template <typename TYPE, size_t COUNT>
	void WorkStealingDequeue<TYPE, COUNT>::push(TYPE item) noexcept {

		// mBottom is only written in pop() which cannot be concurrent with push(),
		// however, it is read in steal() so we need basic atomicity.
		int32_t bottom = mBottom.load(std::memory_order_relaxed);
		setItemAt(bottom, item);

		// memory accesses cannot be reordered after mBottom write, which notifies the
		// availability of an extra item.
		mBottom.store(bottom + 1, std::memory_order_release);
	}

	template <typename TYPE, size_t COUNT>
	TYPE WorkStealingDequeue<TYPE, COUNT>::pop() noexcept {
		// mBottom is only written in push(), which cannot be concurrent with pop(),
		// however, it is read in steal(), so we need basic atomicity.
		//   i.e.: bottom = mBottom--;
		int32_t bottom = mBottom.fetch_sub(1, std::memory_order_relaxed) - 1;

		// we need a full memory barrier here; mBottom must be written and visible to
		// other threads before we read mTop.
		int32_t top = mTop.load(std::memory_order_seq_cst);

		if(top < bottom) {
			// Queue isn't empty and it's not the last item, just return it.
			return getItemAt(bottom);
		}

		TYPE item{};
		if(top == bottom) {
			// We took the last item in the queue
			item = getItemAt(bottom);

			// Items can be added only in push() which isn't concurrent to us, however we could
			// be racing with a steal() -- pretend to steal from ourselves to resolve this
			// potential conflict.
			if(mTop.compare_exchange_strong(top, top + 1,
				std::memory_order_seq_cst,
				std::memory_order_relaxed)) {
				// success: mTop was equal to top, mTop now equals top+1
				// We successfully poped an item, adjust top to make the queue canonically empty.
				top++;
			}
			else {
				// failure: mTop was not equal to top, which means the item was stolen under our feet.
				// top now equals to mTop. Simply discard the item we just poped.
				// The queue is now empty.
				item = TYPE();
			}
		}

		// no concurrent writes to mBottom possible
		mBottom.store(top, std::memory_order_relaxed);
		return item;
	}

	template <typename TYPE, size_t COUNT>
	TYPE WorkStealingDequeue<TYPE, COUNT>::steal() noexcept {
		do {
			// mTop must be read before mBottom
			int32_t top = mTop.load(std::memory_order_seq_cst);

			// mBottom is written concurrently to the read below in pop() or push(), so
			// we need basic atomicity. Also makes sure that writes made in push()
			// (prior to mBottom update) are visible.
			int32_t bottom = mBottom.load(std::memory_order_acquire);

			if(top >= bottom) {
				// queue is empty
				return TYPE();
			}

			// The queue isn't empty
			TYPE item(getItemAt(top));
			if(mTop.compare_exchange_strong(top, top + 1,
				std::memory_order_seq_cst,
				std::memory_order_relaxed)) {
				// success: we stole a job, just return it.
				return item;
			}
			// failure: the item we just tried to steal was pop()'ed under our feet,
			// simply discard it; nothing to do.
		} while(true);
	}

	class JobSystem {
		static constexpr size_t MAX_JOB_COUNT = 4096;
		static_assert(MAX_JOB_COUNT <= 0x7FFE, "MAX_JOB_COUNT must be <= 0x7FFE");
		using WorkQueue = WorkStealingDequeue<uint16_t, MAX_JOB_COUNT>;

	public:
		class Job;

		using JobFunc = void(*)(void*, JobSystem&, Job*);

		class alignas(CACHELINE_SIZE)Job { // NOLINT(cppcoreguidelines-pro-type-member-init)
		public:
			Job() noexcept {} // = default;
			Job(const Job&) = delete;
			Job(Job&&) = delete;

			void* getData() { return padding; }
			void const* getData() const { return padding; }
		private:
			friend class JobSystem;
			JobFunc function;
			uint16_t parent;
			std::atomic<uint16_t> runningJobCount = { 0 };
			// on 64-bits systems, there is an extra 32-bits lost here
			void* padding[JOB_PADDING];
		};

		static_assert(
			(sizeof(Job) % CACHELINE_SIZE == 0) ||
			(CACHELINE_SIZE % sizeof(Job) == 0),
			"A Job must be N cache-lines long or N Jobs must fit in a cache line exactly.");

		explicit JobSystem(size_t threadCount = 0, size_t adoptableThreadsCount = 1) noexcept;

		~JobSystem();

		// Make the current thread part of the thread pool.
		void adopt();

		// Remove this adopted thread from the parent. This is intended to be used for
		// shutting down a JobSystem. In particular, this doesn't allow the parent to
		// adopt more thread.
		void emancipate();


		// return the JobSystem this thread is associated with. nullptr if this thread is not
		// part of a Jobsystem.
		static JobSystem* getJobSystem() noexcept;

		// If a parent is not specified when creating a job, that job will automatically take the
		// master job as a parent.
		// The master job is reset when calling reset()
		Job* setMasterJob(Job* job) noexcept { return mMasterJob = job; }

		// Clears the master job
		void reset() noexcept { mMasterJob = nullptr; }


		// NOTE: All methods below must be called from the same thread and that thread must be
		// owned by JobSystem's thread pool.

		/*
		* Job creation examples:
		* ----------------------
		*
		*  struct Functor {
		*   uintptr_t storage[6];
		*   void operator()(JobSystem&, Jobsystem::Job*);
		*  } functor;
		*
		*  struct Foo {
		*   uintptr_t storage[6];
		*   void method(JobSystem&, Jobsystem::Job*);
		*  } foo;
		*
		*  Functor and Foo size muse be <= uintptr_t[6]
		*
		*   createJob()
		*   createJob(parent)
		*   createJob<Foo, &Foo::method>(parent, &foo)
		*   createJob<Foo, &Foo::method>(parent, foo)
		*   createJob<Foo, &Foo::method>(parent, std::ref(foo))
		*   createJob(parent, functor)
		*   createJob(parent, std::ref(functor))
		*   createJob(parent, [ up-to 6 uintptr_t ](JobSystem*, Jobsystem::Job*){ })
		*
		*  Utility functions:
		*  ------------------
		*    These are less efficient, but handle any size objects using the heap if needed.
		*    (internally uses std::function<>), and don't require the callee to take
		*    a (JobSystem&, Jobsystem::Job*) as parameter.
		*
		*  struct BigFoo {
		*   uintptr_t large[16];
		*   void operator()();
		*   void method(int answerToEverything);
		*   static void exec(BigFoo&) { }
		*  } bigFoo;
		*
		*   jobs::createJob(js, parent, [ any-capture ](int answerToEverything){}, 42);
		*   jobs::createJob(js, parent, &BigFoo::method, &bigFoo, 42);
		*   jobs::createJob(js, parent, &BigFoo::exec, std::ref(bigFoo));
		*   jobs::createJob(js, parent, bigFoo);
		*   jobs::createJob(js, parent, std::ref(bigFoo));
		*   etc...
		*
		*  struct SmallFunctor {
		*   uintptr_t storage[3];
		*   void operator()(T* data, size_t count);
		*  } smallFunctor;
		*
		*   jobs::parallel_for(js, data, count, [ up-to 3 uintptr_t ](T* data, size_t count) { });
		*   jobs::parallel_for(js, data, count, smallFunctor);
		*   jobs::parallel_for(js, data, count, std::ref(smallFunctor));
		*
		*/

		// creates an empty (no-op) job with an optional parent
		Job* createJob(Job* parent = nullptr) noexcept {
			return create(parent, nullptr);
		}

		// creates a job from a KNOWN method pointer w/ object passed by pointer
		// the caller must ensure the object will outlive the Job
		template<typename T, void(T::*method)(JobSystem&, Job*)>
		Job* createJob(Job* parent, T* data) noexcept {
			struct stub {
				static void call(void* user, JobSystem& js, Job* job) noexcept {
					(*static_cast<T**>(user)->*method)(js, job);
				}
			};
			Job* job = create(parent, &stub::call);
			if(job) {
				job->padding[0] = data;
			}
			return job;
		}

		// creates a job from a KNOWN method pointer w/ object passed by value
		template<typename T, void(T::*method)(JobSystem&, Job*)>
		Job* createJob(Job* parent, T data) noexcept {
			static_assert(sizeof(data) <= sizeof(Job::padding), "user data too large");
			struct stub {
				static void call(void* user, JobSystem& js, Job* job) noexcept {
					T* that = static_cast<T*>(user);
					(that->*method)(js, job);
					that->~T();
				}
			};
			Job* job = create(parent, &stub::call);
			if(job) {
				new(job->padding) T(std::move(data));
			}
			return job;
		}

		// creates a job from a functor passed by value
		template<typename T>
		Job* createJob(Job* parent, T functor) noexcept {
			static_assert(sizeof(functor) <= sizeof(Job::padding), "functor too large");
			struct stub {
				static void call(void* user, JobSystem& js, Job* job) noexcept {
					T& that = *static_cast<T*>(user);
					that(js, job);
					that.~T();
				}
			};
			Job* job = create(parent, &stub::call);
			if(job) {
				new(job->padding) T(std::move(functor));
			}
			return job;
		}

		// Add job to this thread's execution queue.
		// Current thread must be owned by JobSystem's thread pool. See adopt().
		enum runFlags { DONT_SIGNAL = 0x1 };
		void run(Job* job, uint32_t flags = 0) noexcept;

		// Wait on a job.
		// Current thread must be owned by JobSystem's thread pool. See adopt().
		void wait(Job const* job) noexcept;

		void runAndWait(Job* job) noexcept {
			run(job);
			wait(job);
		}

		// jobs are normally finished automatically, this can be used to cancel a job
		// before it is run.
		void finish(Job* job) noexcept;

		// for debugging
		// friend utils::io::ostream& operator << (utils::io::ostream& out, JobSystem const& js);


		// utility functions...

		// set the name of the current thread (on OSes that support it)
		static void setThreadName(const char* threadName) noexcept;

		enum class Priority {
			NORMAL,
			DISPLAY,
			URGENT_DISPLAY
		};

		static void setThreadPriority(Priority priority) noexcept;
		static void setThreadAffinity(uint32_t mask) noexcept;

		size_t getParallelSplitCount() const noexcept {
			return mParallelSplitCount;
		}

	private:
		// this is just to avoid using std::default_random_engine, since we're in a public header.
		class default_random_engine {
			static constexpr uint32_t m = 0x7fffffffu;
			uint32_t mState; // must be 0 < seed < 0x7fffffff
		public:
			inline constexpr explicit default_random_engine(uint32_t seed = 1u) noexcept
				: mState(((seed % m) == 0u) ? 1u : seed % m) {
			}
			inline uint32_t operator()() noexcept {
				return mState = uint32_t((uint64_t(mState) * 48271u) % m);
			}
		};

		struct alignas(CACHELINE_SIZE)ThreadState {    // this causes 40-bytes padding
													   // make sure storage is cache-line aligned
			WorkQueue workQueue;

			// these are not accessed by the worker threads
			alignas(CACHELINE_SIZE)     // this causes 56-bytes padding
				JobSystem* js;
			std::thread thread;
			default_random_engine rndGen;
			uint32_t mask;
		};

		static_assert(sizeof(ThreadState) % CACHELINE_SIZE == 0,
			"ThreadState doesn't align to a cache line");

		static ThreadState& getState() noexcept;

		Job* create(Job* parent, JobFunc func) noexcept;
		Job* allocateJob() noexcept;
		JobSystem::ThreadState& getStateToStealFrom(JobSystem::ThreadState& state) noexcept;
		bool hasJobCompleted(Job const* job) noexcept;

		void requestExit() noexcept;
		bool exitRequested() const noexcept;

		void loop(ThreadState* threadState) noexcept;
		bool execute(JobSystem::ThreadState& state) noexcept;

		void put(WorkQueue& workQueue, Job* job) noexcept {
			size_t index = job - mJobStorageBase;
			assert(index >= 0 && index < MAX_JOB_COUNT);
			workQueue.push(uint16_t(index + 1));
		}

		Job* pop(WorkQueue& workQueue) noexcept {
			size_t index = workQueue.pop();
			assert(index <= MAX_JOB_COUNT);
			return !index ? nullptr : (mJobStorageBase - 1) + index;
		}

		Job* steal(WorkQueue& workQueue) noexcept {
			size_t index = workQueue.steal();
			assert(index <= MAX_JOB_COUNT);
			return !index ? nullptr : (mJobStorageBase - 1) + index;
		}

		// these have thread contention, keep them together
		std::mutex mLock;
		std::condition_variable mCondition;
		std::atomic<uint32_t> mActiveJobs = { 0 };
		Arena<ThreadSafeObjectPoolAllocator<Job>, LockingPolicy::NoLock> mJobPool;

		template <typename T>
		using aligned_vector = std::vector<T, STLAlignedAllocator<T>>;

		// these are essentially const, make sure they're on a different cache-lines than the
		// read-write atomics.
		// We can't use "alignas(CACHELINE_SIZE)" because the standard allocator can't make this
		// guarantee.
		char padding[CACHELINE_SIZE];

		alignas(16) // at least we align to half (or quarter) cache-line
			aligned_vector<ThreadState> mThreadStates;          // actual data is stored offline
		std::atomic<bool> mExitRequested = { 0 };           // this one is almost never written
		std::atomic<uint16_t> mAdoptedThreads = { 0 };      // this one is almost never written
		Job* const mJobStorageBase;                         // Base for conversion to indices
		uint16_t mThreadCount = 0;                          // total # of threads in the pool
		uint8_t mParallelSplitCount = 0;                    // # of split allowable in parallel_for
		Job* mMasterJob = nullptr;

		static thread_local ThreadState* sThreadState;
	};

	// -------------------------------------------------------------------------------------------------
	// Utility functions built on top of JobSystem

	namespace jobs {

		// These are convenience C++11 style job creation methods that support lambdas
		//
		// IMPORTANT: these are less efficient to call and may perform heap allocation
		//            depending on the capture and parameters
		//
		template<typename CALLABLE, typename ... ARGS>
		JobSystem::Job* createJob(JobSystem& js, JobSystem::Job* parent,
			CALLABLE&& func, ARGS&&... args) noexcept {
			struct Data {
				std::function<void()> f;
				// Renaming the method below could cause an Arrested Development.
				void gob(JobSystem&, JobSystem::Job*) noexcept { f(); }
			} user{ std::bind(std::forward<CALLABLE>(func),
				std::forward<ARGS>(args)...) };
			return js.createJob<Data, &Data::gob>(parent, std::move(user));
		}

		template<typename CALLABLE, typename T, typename ... ARGS,
			typename = typename std::enable_if<
			std::is_member_function_pointer<typename std::remove_reference<CALLABLE>::type>::value
			>::type
		>
			JobSystem::Job* createJob(JobSystem& js, JobSystem::Job* parent,
				CALLABLE&& func, T&& o, ARGS&&... args) noexcept {
			struct Data {
				std::function<void()> f;
				// Renaming the method below could cause an Arrested Development.
				void gob(JobSystem&, JobSystem::Job*) noexcept { f(); }
			} user{ std::bind(std::forward<CALLABLE>(func), std::forward<T>(o),
				std::forward<ARGS>(args)...) };
			return js.createJob<Data, &Data::gob>(parent, std::move(user));
		}


		namespace details {

			template<typename S, typename F>
			struct ParallelForJobData {
				using SplitterType = S;
				using Functor = F;
				using JobData = ParallelForJobData;
				using size_type = uint32_t;

				ParallelForJobData(size_type start, size_type count, uint8_t splits,
					Functor functor,
					const SplitterType& splitter) noexcept
					: start(start), count(count),
					functor(std::move(functor)),
					splits(splits),
					splitter(splitter) {
				}

				void parallelWithJobs(JobSystem& js, JobSystem::Job* parent) noexcept {

					// We first split about the number of threads we have, and only then we split the rest
					// in a single thread (but execute the final cut in new jobs, see parallel() below),
					// this way we save a lot of copies of JobData.
					if(splits == js.getParallelSplitCount()) {
						parallel(js, parent);
						return;
					}

					if(splitter.split(splits, count)) {
						const size_type lc = count / 2;
						JobData ld(start, lc, splits + uint8_t(1), functor, splitter);
						JobSystem::Job* l = js.createJob<JobData, &JobData::parallelWithJobs>(parent, std::move(ld));

						if(UTILS_UNLIKELY(l == nullptr)) {
							// couldn't create a job, just pretend we're done splitting
							goto done;
						}

						// start the left side before attempting the right side, so we parallelize in case
						// of job creation failure -- rare, but still.
						js.run(l);

						const size_type rc = count - lc;
						JobData rd(start + lc, rc, splits + uint8_t(1), functor, splitter);
						JobSystem::Job* r = js.createJob<JobData, &JobData::parallelWithJobs>(parent, std::move(rd));

						if(UTILS_UNLIKELY(r == nullptr)) {
							// couldn't allocate right side job, execute it right now
							functor(start + lc, rc);
							return;
						}

						// All good, execute the right side, but don't signal it,
						// so it's more likely to be executed next on the same thread
						js.run(r, JobSystem::DONT_SIGNAL);
					}
					else {
					done:
						// we're done splitting, do the real work here!
						functor(start, count);
					}
				}

				void parallel(JobSystem& js, JobSystem::Job* parent) noexcept {
					// here we split the data ona single thread, and launch jobs once we're completely
					// done splitting
					if(splitter.split(splits, count)) {
						auto lc = count / 2;
						auto rc = count - lc;
						auto rd = start + lc;
						auto s = ++splits;

						// left-side
						count = lc;
						parallel(js, parent);

						// note: in practice the compiler is able to optimize out the call to parallel() below
						// right-side
						start = rd;
						count = rc;
						splits = s;
						parallel(js, parent);
					}
					else {
						// only capture what we need
						auto job = js.createJob(parent,
							[f = functor, s = start, c = count](JobSystem&, JobSystem::Job*) {
							// we're done splitting, do the real work here!
							f(s, c);
						});
						if(UTILS_LIKELY(job)) {
							js.run(job);
						}
						else {
							// oops, no more job available
							functor(start, count);
						}
					}
				}

				size_type start;            // 4
				size_type count;            // 4
				Functor functor;            // ?
				uint8_t splits;             // 1
				SplitterType splitter;      // 1
			};

		} // namespace details


		  // parallel jobs with start/count indices
		template<typename S, typename F>
		JobSystem::Job* parallel_for(JobSystem& js, JobSystem::Job* parent,
			uint32_t start, uint32_t count, F functor, const S& splitter) noexcept {
			using JobData = details::ParallelForJobData<S, F>;
			JobData jobData(start, count, 0, std::move(functor), splitter);
			return js.createJob<JobData, &JobData::parallelWithJobs>(parent, std::move(jobData));
		}

		// parallel jobs with pointer/count
		template<typename T, typename S, typename F>
		JobSystem::Job* parallel_for(JobSystem& js, JobSystem::Job* parent,
			T* data, uint32_t count, F functor, const S& splitter) noexcept {
			auto user = [data, f = std::move(functor)](uint32_t s, uint32_t c) {
				f(data + s, c);
			};
			using JobData = details::ParallelForJobData<S, decltype(user)>;
			JobData jobData(0, count, 0, std::move(user), splitter);
			return js.createJob<JobData, &JobData::parallelWithJobs>(parent, std::move(jobData));
		}


		// parallel jobs with start/count indices + sequential 'reduce'
		template<typename S, typename F, typename R>
		JobSystem::Job* parallel_for(JobSystem& js, JobSystem::Job* parent,
			uint32_t start, uint32_t count, F functor, const S& splitter, R finish) noexcept {
			using JobData = details::ParallelForJobData<S, F>;
			JobData jobData(start, count, 0, std::move(functor), splitter);
			auto wrapper = js.createJob(parent, [jobData, finish](JobSystem& js, JobSystem::Job* p) {
				auto parallelJob = js.createJob<JobData, &JobData::parallelWithJobs>(p, std::move(jobData));
				js.runAndWait(parallelJob);
				finish(js, parallelJob);
			});
			return wrapper;
		}

		// parallel jobs with pointer/count + sequential 'reduce'
		template<typename T, typename S, typename F, typename R>
		JobSystem::Job* parallel_for(JobSystem& js, JobSystem::Job* parent,
			T* data, uint32_t count, F functor, const S& splitter, R finish) noexcept {
			auto user = [data, f = std::move(functor)](uint32_t s, uint32_t c) {
				f(data + s, c);
			};
			using JobData = details::ParallelForJobData<S, decltype(user)>;
			JobData jobData(0, count, 0, std::move(user), splitter);
			auto wrapper = js.createJob(parent, [jobData, finish](JobSystem& js, JobSystem::Job* p) {
				auto parallelJob = js.createJob<JobData, &JobData::parallelWithJobs>(p, std::move(jobData));
				js.runAndWait(parallelJob);
				finish(js, parallelJob);
			});
			return wrapper;
		}

		// parallel jobs on a Slice<>
		template<typename T, typename S, typename F>
		JobSystem::Job* parallel_for(JobSystem& js, JobSystem::Job* parent,
			array<T> slice, F functor, const S& splitter) noexcept {
			return parallel_for(js, parent, slice.data(), slice.size(), functor, splitter);
		}

		// parallel jobs on a Slice<> + sequential 'reduce'
		template<typename T, typename S, typename F, typename R>
		JobSystem::Job* parallel_for(JobSystem& js, JobSystem::Job* parent,
			array<T> slice, F functor, const S& splitter, R finish) noexcept {
			return parallel_for(js, parent, slice.data(), slice.size(), functor, splitter, finish);
		}


		template <size_t COUNT, size_t MAX_SPLITS = 12>
		class CountSplitter {
		public:
			bool split(size_t splits, size_t count) const noexcept {
				return (splits < MAX_SPLITS && count >= COUNT * 2);
			}
		};

	} // namespace jobs

}

#endif