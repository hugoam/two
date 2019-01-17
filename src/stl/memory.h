#pragma once
#include <infra/Config.h>

//#define MUD_UNIQUE_PTR_STL
#ifdef MUD_UNIQUE_PTR_STL
#ifndef MUD_CPP_20
#include <memory>
namespace mud
{
	export_ template <class T>
	using unique = std::unique_ptr<T>;
	export_ using std::unique_ptr;
	export_ using std::make_unique;

	template<class T, class... Types>
	inline unique<T> construct(Types&&... args)
	{
		return unique<T>(new T(static_cast<Types&&>(args)...));
	}
}
#endif
#else
#include <utility>
namespace mud
{
	template<class T>
	class unique
	{
	public:
		unique() noexcept : m_ptr(nullptr) {}
		unique(std::nullptr_t) noexcept : m_ptr(nullptr) {}
		explicit unique(T* pointer) noexcept : m_ptr(pointer) {}
		~unique() { delete m_ptr; }

		unique(const unique<T>&) = delete;
		unique<T>& operator=(const unique<T>&) = delete;

		unique(unique<T>&& other) noexcept
			: m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}

		template<class U>
		unique(unique<U>&& other) noexcept
			: m_ptr(other.m_ptr)
		{
			other.m_ptr = nullptr;
		}

		unique<T>& operator=(unique<T>&& other) noexcept
		{
			std::swap(m_ptr, other.m_ptr);
			return *this;
		}

		bool operator==(std::nullptr_t) const { return !m_ptr; }
		bool operator!=(std::nullptr_t) const { return m_ptr; }

		explicit operator bool() const { return m_ptr; }

		T* get() const { return m_ptr; }
		T* operator->() const { return m_ptr; }
		T& operator*() const { return *m_ptr; }

		void reset(T* pointer)
		{
			delete m_ptr;
			m_ptr = pointer;
		}

		template<class ...Args>
		T& emplace(Args&&... args)
		{
			delete m_ptr;
			m_ptr = new T{ std::forward<Args>(args)... };
			return *m_ptr;
		}

		T* release()
		{
			T* const out = m_ptr;
			m_ptr = nullptr;
			return out;
		}

	public:
		T* m_ptr;
	};

	template<class T> bool operator==(std::nullptr_t, const unique<T>& b) { return b == nullptr; }
	template<class T> bool operator!=(std::nullptr_t, const unique<T>& b) { return b != nullptr; }

	template<class T, class... Types>
	inline unique<T> make_unique(Types&&... args)
	{
		return unique<T>(new T(static_cast<Types&&>(args)...));
	}

	template<class T, class... Types>
	inline unique<T> construct(Types&&... args)
	{
		return unique<T>(new T(static_cast<Types&&>(args)...));
	}
}

#endif
