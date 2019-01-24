#pragma once

#include <mud/fract.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::PatternSampling& val) { val = mud::PatternSampling(enu<mud::PatternSampling>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::PatternSampling& val, string& str) { str = enu<mud::PatternSampling>().name(uint32_t(val)); };
	
	
}

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif


#ifndef MUD_FRACT_REFL_EXPORT
#define MUD_FRACT_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_FRACT_REFL_EXPORT mud_fract : public Module
	{
	private:
		mud_fract();
		
	public:
		static mud_fract& m() { static mud_fract instance; return instance; }
	};
}

#ifdef MUD_FRACT_MODULE
extern "C"
MUD_FRACT_REFL_EXPORT Module& getModule();
#endif

