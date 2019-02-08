#pragma once

#include <infra/Config.h>

#ifdef USE_STL
#include <utility>
namespace stl
{
	using std::move;
}
#else
#include <stl/traits.h>
namespace stl
{
	template <class T>
	constexpr remove_reference<T>&& move(T&& arg) noexcept
	{
		return (static_cast<remove_reference<T>&&>(arg));
	}
}
#endif

namespace mud
{
	using stl::move;
}