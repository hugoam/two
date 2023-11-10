#pragma once

#ifndef TWO_MODULES
#include <gfx-ui/Types.h>
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::ui::OrbitMode& val) { val = two::ui::OrbitMode(enu<two::ui::OrbitMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ui::OrbitMode& val, string& str) { str = enu<two::ui::OrbitMode>().name(uint32_t(val)); };
	
	
}
