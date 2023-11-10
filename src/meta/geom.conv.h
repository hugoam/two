#pragma once

#ifndef TWO_MODULES
#include <geom/Types.h>
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::CatmullType& val) { val = two::CatmullType(enu<two::CatmullType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::CatmullType& val, string& str) { str = enu<two::CatmullType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::DrawMode& val) { val = two::DrawMode(enu<two::DrawMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::DrawMode& val, string& str) { str = enu<two::DrawMode>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::PrimitiveType& val) { val = two::PrimitiveType(enu<two::PrimitiveType>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::PrimitiveType& val, string& str) { str = enu<two::PrimitiveType>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::SymbolDetail& val) { val = two::SymbolDetail(enu<two::SymbolDetail>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::SymbolDetail& val, string& str) { str = enu<two::SymbolDetail>().name(uint32_t(val)); };
	
	
}
