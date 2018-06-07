
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#endif
        
#include <procgen/Generated/Forward.h>
#include <procgen/Generated/Types.h>
#include <procgen/Api.h>

#include <procgen/Generated/Convert.h>

namespace mud
{
	export_ class MUD_PROCGEN_EXPORT mudprocgen : public Module
	{
	private:
		mudprocgen();

	public:
		static mudprocgen& m() { static mudprocgen instance; return instance; }
	};
}

#ifdef MUD_PROCGEN_MODULE
extern "C"
MUD_PROCGEN_EXPORT Module& getModule();
#endif
