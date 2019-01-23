#pragma once

#include <infra/Config.h>

#ifndef MUD_NO_STL
#include <utility>
namespace mud
{
	using std::move;
}
#else
#include <stl/type_traits.h>
namespace mud
{
#if 0
	template<class T>
	struct remove_reference { using type = T; };

	template<class T>
	struct remove_reference<T&> { using type = T; };

	template<class T>
	struct remove_reference<T&&> { using type = T; };

	template<class T>
	using remove_reference_t = typename remove_reference<T>::type;
#endif

	template<class T>
	constexpr remove_reference_t<T>&& move(T&& arg) noexcept
	{
		return (static_cast<remove_reference_t<T>&&>(arg));
	}
}
#endif
