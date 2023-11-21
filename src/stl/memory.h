#pragma once

#include <infra/Config.h>

#ifdef USE_STL
#ifndef TWO_STD_MODULES
#include <memory>
#endif
namespace stl
{
	using std::unique_ptr;
	using std::make_unique;
}
#else
#include <stl/swap.h>
namespace stl
{
	using nullptr_t = decltype(nullptr);

	template <class T>
	class refl_ nocopy_ unique_ptr
	{
	public:
		unique_ptr() : m_ptr(nullptr) {}
		unique_ptr(nullptr_t) : m_ptr(nullptr) {}
		explicit unique_ptr(T* m_ptr) : m_ptr(m_ptr) {}
		~unique_ptr() { delete m_ptr; }

		unique_ptr(unique_ptr const&) = delete;
		unique_ptr& operator=(unique_ptr const&) = delete;

		unique_ptr(unique_ptr&& moving) noexcept
			: unique_ptr()
		{
			moving.swap(*this);
		}

		unique_ptr& operator=(unique_ptr&& moving) noexcept
		{
			moving.swap(*this);
			return *this;
		}

		template <class U>
		unique_ptr(unique_ptr<U>&& moving)
			: unique_ptr()
		{
			unique_ptr<T>(moving.release()).swap(*this);
		}

		template <class U>
		unique_ptr& operator=(unique_ptr<U>&& moving)
		{
			unique_ptr<T>(moving.release()).swap(*this);
			return *this;
		}

		bool operator==(nullptr_t) const { return m_ptr == nullptr; }
		bool operator!=(nullptr_t) const { return m_ptr != nullptr; }

		explicit operator bool() const { return m_ptr; }

		T* get() const { return m_ptr; }
		T* operator->() const { return m_ptr; }
		T& operator*() const { return *m_ptr; }

		void swap(unique_ptr& src) noexcept
		{
			using stl::swap;
			swap(m_ptr, src.m_ptr);
		}

		void reset()
		{
			T* tmp = release();
			delete tmp;
		}

		T* release() noexcept
		{
			T* result = nullptr;
			two::swap(result, m_ptr);
			return result;
		}

	private:
		T* m_ptr;
	};

#if 0
	template <class T>
	void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs)
	{
		lhs.swap(rhs);
	}
#endif

	template <class T> bool operator==(nullptr_t, const unique_ptr<T>& b) { return b == nullptr; }
	template <class T> bool operator!=(nullptr_t, const unique_ptr<T>& b) { return b != nullptr; }

	template <class T, class U> inline bool operator==(const unique_ptr<T>& l, const unique_ptr<U>& r) { return (l.get() == r.get()); }
	template <class T, class U> inline bool operator!=(const unique_ptr<T>& l, const unique_ptr<U>& r) {	return (l.get() != r.get()); }

	template <class T, class... Types>
	inline unique_ptr<T> make_unique(Types&&... args)
	{
		return unique_ptr<T>(new T(static_cast<Types&&>(args)...));
	}
}

#endif

namespace two
{
	export_ template <class T>
	using unique = stl::unique_ptr<T>;

	export_ using stl::unique_ptr;
	export_ using stl::make_unique;

	export_ template <class T, class... Types>
	inline unique<T> construct(Types&&... args)
	{
		return unique<T>(new T(static_cast<Types&&>(args)...));
	}
}
