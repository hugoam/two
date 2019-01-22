#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#ifndef MUD_CPP_20
#include <functional>
#endif
namespace mud
{
	export_ using std::function;
}
#else
#include <stl/move.h>
#include <stl/type_traits.h>
#include <new>
namespace mud
{
	template <typename T>
	class function;

	template <typename Return, typename... Args>
	class function<Return(Args...)>
	{
	public:
		function() {}

		template <class T, typename = typename enable_if<is_invocable<T, Args...>::value>::type>
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
			new(m_storage) T(move(functor));
		}

		~function()
		{
			if(m_dtor) m_dtor(m_storage);
		}

		Return operator()(Args... args) const
		{
			return m_func(m_storage, static_cast<Args&&>(args)...);
		}

		explicit operator bool() { return m_func != nullptr; }

		using Func = Return(*)(const void*, Args...); Func m_func = nullptr;
		using Dtor = void(*)(void*); Dtor m_dtor = nullptr;
		void* m_storage[8];
	};
}
#endif
