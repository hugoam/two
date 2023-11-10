#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#ifndef TWO_STD_MODULES
#include <functional>
#endif
namespace stl
{
	using std::function;
}
#else
#include <stl/move.h>
#include <stl/traits.h>
#include <stl/new.h>
namespace stl
{
	template <class T>
	class function;

	template <class Return, typename... Args>
	class refl_ function<Return(Args...)>
	{
	public:
		function() {}

		template <class T, typename = enable_if<is_invocable<T, Args...>>>
		function(T functor)
		{
			m_func = [](const void* user, Args... args) -> Return
			{
				const T& func = *static_cast<const T*>(user);
				return func(static_cast<Args&&>(args)...);
			};

			m_dtor = [](void* user)
			{
				T& func = *static_cast<T*>(user);
				func.~T();
			};

			static_assert(sizeof(T) <= sizeof(m_storage));
			new(stl::placeholder(), m_storage) T(move(functor));
		}

		~function()
		{
			if(m_dtor) m_dtor(m_storage);
		}

		Return operator()(Args... args) const
		{
			return m_func(m_storage, static_cast<Args&&>(args)...);
		}

		explicit operator bool() const { return m_func != nullptr; }

		using Func = Return(*)(const void*, Args...); Func m_func = nullptr;
		using Dtor = void(*)(void*); Dtor m_dtor = nullptr;
		void* m_storage[8];
	};
}
#endif

namespace two
{
	export_ using stl::function;
}