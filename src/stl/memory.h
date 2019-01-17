#pragma once
#include <infra/Config.h>

#define MUD_UNIQUE_PTR_STL
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
//#include <stl/algorithm.h>
#include <utility>
namespace mud
{
	template<typename T>
	class unique
	{
	public:
		unique() : m_ptr(nullptr) {}
		explicit unique(T* m_ptr) : m_ptr(m_ptr) {}
		~unique() { delete m_ptr; }
		unique(std::nullptr_t) : m_ptr(nullptr) {}

		unique& operator=(std::nullptr_t)
		{
			reset();
			return *this;
		}

		// Constructor/Assignment that allows move semantics
		unique(unique&& moving) noexcept
		{
			moving.swap(*this);
		}
		unique& operator=(unique&& moving) noexcept
		{
			moving.swap(*this);
			return *this;
		}

		// Constructor/Assignment for use with types derived from T
		template<typename U>
		unique(unique<U>&& moving)
		{
			unique<T> tmp(moving.release());
			tmp.swap(*this);
		}
		template<typename U>
		unique& operator=(unique<U>&& moving)
		{
			unique<T> tmp(moving.release());
			tmp.swap(*this);
			return *this;
		}

		// Remove compiler generated copy semantics.
		unique(unique const&) = delete;
		unique& operator=(unique const&) = delete;

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
		void swap(unique& src) noexcept
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
	void swap(unique<T>& lhs, unique<T>& rhs)
	{
		lhs.swap(rhs);
	}

	template<class T, class U> inline bool operator==(const unique<T>& l, const unique<U>& r) 
	{
		return (l.get() == r.get());
	}
	template<class T, class U> inline bool operator!=(const unique<T>& l, const unique<U>& r) 
	{
		return (l.get() != r.get());
	}
	template<class T, class U> inline bool operator<=(const unique<T>& l, const unique<U>& r) 
	{
		return (l.get() <= r.get());
	}
	template<class T, class U> inline bool operator<(const unique<T>& l, const unique<U>& r) 
	{
		return (l.get() < r.get());
	}
	template<class T, class U> inline bool operator>=(const unique<T>& l, const unique<U>& r) 
	{
		return (l.get() >= r.get());
	}
	template<class T, class U> inline bool operator>(const unique<T>& l, const unique<U>& r) 
	{
		return (l.get() > r.get());
	}

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

#if 0
#include <cassert>	
namespace mud
{
	template<class T>
	class unique
	{
	public:
		typedef T element_type;

		unique() : m_ptr(nullptr) {}
		explicit unique(T* p) : m_ptr(p) {}

		unique(unique const&) = delete;
		unique& operator=(unique const&) = delete;

		unique(unique&& other)
			: m_ptr(other.m_ptr)
		{
			const_cast<unique&>(other).m_ptr = nullptr;
		}

		unique& operator=(unique&& other)
		{
			swap(other);
			return *this;
		}

		template <class U>
		unique(const unique<U>& other)
			: m_ptr(static_cast<typename unique<T>::element_type*>(ptr.m_ptr))
		{
			const_cast<unique<U>&>(ptr).m_ptr = nullptr; // const-cast to force ownership transfer!
		}

		inline ~unique(void)
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

		void swap(unique& lhs)
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
