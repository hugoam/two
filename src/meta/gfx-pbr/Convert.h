#pragma once

#include <gfx-pbr/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::TonemapMode& val) { val = mud::TonemapMode(enu<mud::TonemapMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TonemapMode& val, string& str) { str = enu<mud::TonemapMode>().name(uint32_t(val)); };
	
	
}
