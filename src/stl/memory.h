#pragma once
#include <infra/Config.h>

//#define MUD_UNIQUE_PTR_STL
#ifdef MUD_UNIQUE_PTR_STL
#ifndef MUD_CPP_20
#include <memory>
namespace mud
{
	export_ using std::unique_ptr;
	export_ using std::make_unique;
}
#endif
#else
//#include <stl/algorithm.h>
#include <utility>
namespace mud
{
	template<typename T>
	class unique_ptr
	{
	public:
		unique_ptr() : m_ptr(nullptr) {}
		explicit unique_ptr(T* m_ptr) : m_ptr(m_ptr) {}
		~unique_ptr() { delete m_ptr; }
		unique_ptr(std::nullptr_t) : m_ptr(nullptr) {}

		unique_ptr& operator=(std::nullptr_t)
		{
			reset();
			return *this;
		}

		// Constructor/Assignment that allows move semantics
		unique_ptr(unique_ptr&& moving) noexcept
		{
			moving.swap(*this);
		}
		unique_ptr& operator=(unique_ptr&& moving) noexcept
		{
			moving.swap(*this);
			return *this;
		}

		// Constructor/Assignment for use with types derived from T
		template<typename U>
		unique_ptr(unique_ptr<U>&& moving)
		{
			unique_ptr<T> tmp(moving.release());
			tmp.swap(*this);
		}
		template<typename U>
		unique_ptr& operator=(unique_ptr<U>&& moving)
		{
			unique_ptr<T> tmp(moving.release());
			tmp.swap(*this);
			return *this;
		}

		// Remove compiler generated copy semantics.
		unique_ptr(unique_ptr const&) = delete;
		unique_ptr& operator=(unique_ptr const&) = delete;

		// Const correct access owned object
		T* operator->() const { return m_ptr; }
		T& operator*()  const { return *m_ptr; }

		// Access to smart pointer state
		T* get()                 const { return m_ptr; }
		explicit operator bool() const { return m_ptr != nullptr; }

		// Modify object state
		T* release() noexcept
		{
			T* result = nullptr;
			std::swap(result, m_ptr);
			return result;
		}
		void swap(unique_ptr& src) noexcept
		{
			std::swap(m_ptr, src.m_ptr);
		}
		void reset()
		{
			T* tmp = release();
			delete tmp;
		}

	private:
		T* m_ptr;
	};

	template<typename T>
	void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs)
	{
		lhs.swap(rhs);
	}

	template<class T, class U> inline bool operator==(const unique_ptr<T>& l, const unique_ptr<U>& r) 
	{
		return (l.get() == r.get());
	}
	template<class T, class U> inline bool operator!=(const unique_ptr<T>& l, const unique_ptr<U>& r) 
	{
		return (l.get() != r.get());
	}
	template<class T, class U> inline bool operator<=(const unique_ptr<T>& l, const unique_ptr<U>& r) 
	{
		return (l.get() <= r.get());
	}
	template<class T, class U> inline bool operator<(const unique_ptr<T>& l, const unique_ptr<U>& r) 
	{
		return (l.get() < r.get());
	}
	template<class T, class U> inline bool operator>=(const unique_ptr<T>& l, const unique_ptr<U>& r) 
	{
		return (l.get() >= r.get());
	}
	template<class T, class U> inline bool operator>(const unique_ptr<T>& l, const unique_ptr<U>& r) 
	{
		return (l.get() > r.get());
	}

	template<class T, class... Types>
	inline unique_ptr<T> make_unique(Types&&... args)
	{
		return unique_ptr<T>(new T(static_cast<Types&&>(args)...));
	}

	template<class T, class... Types>
	inline unique_ptr<T> construct(Types&&... args)
	{
		return unique_ptr<T>(new T(static_cast<Types&&>(args)...));
	}
}

#if 0
#include <cassert>	
namespace mud
{
	template<class T>
	class unique_ptr
	{
	public:
		typedef T element_type;

		unique_ptr() : m_ptr(nullptr) {}
		explicit unique_ptr(T* p) : m_ptr(p) {}

		unique_ptr(unique_ptr const&) = delete;
		unique_ptr& operator=(unique_ptr const&) = delete;

		unique_ptr(unique_ptr&& other)
			: m_ptr(other.m_ptr)
		{
			const_cast<unique_ptr&>(other).m_ptr = nullptr;
		}

		unique_ptr& operator=(unique_ptr&& other)
		{
			swap(other);
			return *this;
		}

		template <class U>
		unique_ptr(const unique_ptr<U>& other)
			: m_ptr(static_cast<typename unique_ptr<T>::element_type*>(ptr.m_ptr))
		{
			const_cast<unique_ptr<U>&>(ptr).m_ptr = nullptr; // const-cast to force ownership transfer!
		}

		inline ~unique_ptr(void)
		{
			destroy();
		}
		inline void reset()
		{
			destroy();
		}
		void reset(T* p)
		{
			assert((nullptr == p) || (m_ptr != p)); // auto-reset not allowed
			destroy();
			m_ptr = p;
		}

		void swap(unique_ptr& lhs)
		{
			std::swap(m_ptr, lhs.m_ptr);
		}

		inline void release()
		{
			m_ptr = nullptr;
		}

		inline explicit operator bool() const
		{
			return (nullptr != m_ptr); // TODO nullptr
		}

		inline T& operator*() const
		{
			assert(nullptr != m_ptr);
			return *m_ptr;
		}
		inline T* operator->() const
		{
			assert(nullptr != m_ptr);
			return m_ptr;
		}

		inline T* get() const
		{
			return m_ptr;
		}

	private:
		inline void destroy()
		{
			delete m_ptr;
			m_ptr = nullptr;
		}

		inline void release()const
		{
			m_ptr = nullptr;
		}

	private:
		T* m_ptr;
	};
}
#endif
#endif
