#pragma once

#include <mud/srlz.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <srlz/Types.h>

#ifndef MUD_SRLZ_REFL_EXPORT
#define MUD_SRLZ_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_SRLZ_REFL_EXPORT mud_srlz : public mud::Module
	{
	private:
		mud_srlz();
		
	public:
		static mud_srlz& m() { static mud_srlz instance; return instance; }
	};
}

#ifdef MUD_SRLZ_MODULE
extern "C"
MUD_SRLZ_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	
}
