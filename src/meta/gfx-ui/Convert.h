
#pragma once

#include <gfx-ui/Types.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void from_string(const string& str, mud::ui::OrbitMode& val) { val = static_cast<mud::ui::OrbitMode>(enu<mud::ui::OrbitMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ui::OrbitMode& val, string& str) { str = enu<mud::ui::OrbitMode>().m_map[size_t(val)]; };

}
