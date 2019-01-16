#pragma once

#include <gfx-ui/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::ui::OrbitMode& val) { val = mud::ui::OrbitMode(enu<mud::ui::OrbitMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ui::OrbitMode& val, string& str) { str = enu<mud::ui::OrbitMode>().name(uint32_t(val)); };
	
	
}
