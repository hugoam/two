#pragma once

#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::TypeClass& val) { val = mud::TypeClass(enu<mud::TypeClass>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::TypeClass& val, string& str) { str = enu<mud::TypeClass>().name(uint32_t(val)); };
	
	
}

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif


#ifndef MUD_REFL_REFL_EXPORT
#define MUD_REFL_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_REFL_REFL_EXPORT mud_refl : public Module
	{
	private:
		mud_refl();
		
	public:
		static mud_refl& m() { static mud_refl instance; return instance; }
	};
}

#ifdef MUD_REFL_MODULE
extern "C"
MUD_REFL_REFL_EXPORT Module& getModule();
#endif

