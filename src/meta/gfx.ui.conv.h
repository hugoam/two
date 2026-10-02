#pragma once

#if defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	template <> inline void to_value(const string& str, two::ui::OrbitMode& val) { val = two::ui::OrbitMode(enu<two::ui::OrbitMode>().value(str.c_str())); };
	template <> inline void to_string(const two::ui::OrbitMode& val, string& str) { str = enu<two::ui::OrbitMode>().name(uint32_t(val)); };
	
	
}
