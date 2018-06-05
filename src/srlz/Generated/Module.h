
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#endif
        
#include <srlz/Generated/Forward.h>
#include <srlz/Generated/Types.h>

#include <srlz/Serial.h>

#include <srlz/Generated/Convert.h>

namespace mud
{
	export_ class MUD_SRLZ_EXPORT mudsrlz : public Module
	{
	private:
		mudsrlz();

	public:
		static mudsrlz& m() { static mudsrlz instance; return instance; }
	};
}

#ifdef MUD_SRLZ_MODULE
extern "C"
MUD_SRLZ_EXPORT Module& getModule();
#endif
