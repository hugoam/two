#pragma once

#include <uio/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/String.h>
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::EditNestMode& val) { val = mud::EditNestMode(enu<mud::EditNestMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::EditNestMode& val, string& str) { str = enu<mud::EditNestMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::EditorHint& val) { val = mud::EditorHint(enu<mud::EditorHint>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::EditorHint& val, string& str) { str = enu<mud::EditorHint>().name(uint32_t(val)); };
	
	
}
