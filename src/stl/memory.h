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
#include <stl/swap.h>
#include <cstddef>
namespace mud
{
	template<typename T>
	class unique
	{
	public:
		unique() : m_ptr(nullptr) {}
		unique(std::nullptr_t) : m_ptr(nullptr) {}
		explicit unique(T* m_ptr) : m_ptr(m_ptr) {}
		~unique() { delete m_ptr; }

		unique(unique const&) = delete;
		unique& operator=(unique const&) = delete;

		unique(unique&& moving) noexcept
			: unique()
		{
			moving.swap(*this);
		}

		unique& operator=(unique&& moving) noexcept
		{
			moving.swap(*this);
			return *this;
		}

		template<typename U>
		unique(unique<U>&& moving)
			: unique()
		{
			unique<T>(moving.release()).swap(*this);
		}

		template<typename U>
		unique& operator=(unique<U>&& moving)
		{
			unique<T>(moving.release()).swap(*this);
			return *this;
		}

		bool operator==(std::nullptr_t) const { return m_ptr == nullptr; }
		bool operator!=(std::nullptr_t) const { return m_ptr != nullptr; }

		explicit operator bool() const { return m_ptr; }

		T* get() const { return m_ptr; }
		T* operator->() const { return m_ptr; }
		T& operator*() const { return *m_ptr; }

		void swap(unique& src) noexcept
		{
			mud::swap(m_ptr, src.m_ptr);
		}

		void reset()
		{
			T* tmp = release();
			delete tmp;
		}

		T* release() noexcept
		{
			T* result = nullptr;
			mud::swap(result, m_ptr);
			return result;
		}

	private:
		T* m_ptr;
	};

#if 0
	template<typename T>
	void swap(unique<T>& lhs, unique<T>& rhs)
	{
		lhs.swap(rhs);
	}
#endif

	template<class T> bool operator==(std::nullptr_t, const unique<T>& b) { return b == nullptr; }
	template<class T> bool operator!=(std::nullptr_t, const unique<T>& b) { return b != nullptr; }

	template<class T, class U> inline bool operator==(const unique<T>& l, const unique<U>& r) { return (l.get() == r.get()); }
	template<class T, class U> inline bool operator!=(const unique<T>& l, const unique<U>& r) {	return (l.get() != r.get()); }

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
