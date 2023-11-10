#pragma once

#ifndef TWO_MODULES
#include <uio/Types.h>
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::EditNestMode& val) { val = two::EditNestMode(enu<two::EditNestMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::EditNestMode& val, string& str) { str = enu<two::EditNestMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::EditorHint& val) { val = two::EditorHint(enu<two::EditorHint>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::EditorHint& val, string& str) { str = enu<two::EditorHint>().name(uint32_t(val)); };
	
	
}
