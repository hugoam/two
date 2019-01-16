#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <srlz/Forward.h>
#include <srlz/Types.h>

#ifndef MUD_SRLZ_REFL_EXPORT
#define MUD_SRLZ_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_SRLZ_REFL_EXPORT mud_srlz : public Module
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
