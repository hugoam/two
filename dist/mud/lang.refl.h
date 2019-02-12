#pragma once

#include <mud/lang.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <lang/Types.h>

#ifndef MUD_LANG_REFL_EXPORT
#define MUD_LANG_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_LANG_REFL_EXPORT mud_lang : public mud::Module
	{
	private:
		mud_lang();
		
	public:
		static mud_lang& m() { static mud_lang instance; return instance; }
	};
}

#ifdef MUD_LANG_MODULE
extern "C"
MUD_LANG_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::Language& val) { val = mud::Language(enu<mud::Language>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Language& val, string& str) { str = enu<mud::Language>().name(uint32_t(val)); };
	
	
}
