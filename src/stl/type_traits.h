#pragma once

#include <infra/Config.h>

#include <type_traits>

namespace mud
{
	using std::enable_if; using std::integral_constant;
	using std::is_copy_assignable; using std::is_copy_constructible; using std::is_default_constructible; using std::is_trivially_destructible;
	using std::is_pointer; using std::is_function; using std::is_invocable; using std::is_integral; using std::is_unsigned;
	using std::remove_reference; using std::remove_reference_t; using std::remove_pointer; using std::remove_pointer_t; using std::remove_cv;
	using std::false_type; using std::true_type;
}
