#pragma once

#include <infra/Config.h>

#include <type_traits>

namespace mud
{
	using std::enable_if; using std::is_copy_assignable; using std::is_copy_constructible; using std::is_pointer;
	using std::is_function; using std::integral_constant; using std::remove_pointer; using std::is_trivially_destructible;
	using std::is_integral; using std::is_invocable;
}
