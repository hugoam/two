
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <obj/Refl/Module.h>
#include <refl/Refl/Module.h>
#endif
        
#include <srlz/Forward.h>
#include <srlz/Types.h>
#include <srlz/Api.h>

#include <srlz/Refl/Convert.h>

#ifndef MUD_SRLZ_REFL_EXPORT
#define MUD_SRLZ_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_SRLZ_REFL_EXPORT mudsrlz : public Module
	{
	private:
		mudsrlz();

	public:
		static mudsrlz& m() { static mudsrlz instance; return instance; }
	};
}

#ifdef MUD_SRLZ_MODULE
extern "C"
MUD_SRLZ_REFL_EXPORT Module& getModule();
#endif
