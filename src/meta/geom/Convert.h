#pragma once

#include <geom/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/String.h>
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::DrawMode& val) { val = mud::DrawMode(enu<mud::DrawMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::DrawMode& val, string& str) { str = enu<mud::DrawMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::PrimitiveType& val) { val = mud::PrimitiveType(enu<mud::PrimitiveType>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::PrimitiveType& val, string& str) { str = enu<mud::PrimitiveType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::SymbolDetail& val) { val = mud::SymbolDetail(enu<mud::SymbolDetail>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::SymbolDetail& val, string& str) { str = enu<mud::SymbolDetail>().name(uint32_t(val)); };
	
	
}
