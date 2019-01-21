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

		template <class T>
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

			new(m_storage) T(move(functor));
		}

		~function()
		{
			if(m_dtor) m_dtor(m_storage);
		}

		Return operator()(Args... args)
		{
			m_func(m_storage, static_cast<Args&&>(args)...);
		}

		Return operator()(Args... args) const
		{
			m_func(m_storage, static_cast<Args&&>(args)...);
		}

		explicit operator bool() { return m_func != nullptr; }

		using Func = Return(*)(const void*, Args...); Func m_func = nullptr;
		using Dtor = void(*)(void*); Dtor m_dtor = nullptr;
		void* m_storage[8];
	};
}
#endif
