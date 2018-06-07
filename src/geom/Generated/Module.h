
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#endif
        
#include <geom/Generated/Forward.h>
#include <geom/Generated/Types.h>
#include <geom/Api.h>

#include <geom/Generated/Convert.h>

namespace mud
{
	export_ class MUD_GEOM_EXPORT mudgeom : public Module
	{
	private:
		mudgeom();

	public:
		static mudgeom& m() { static mudgeom instance; return instance; }
	};
}

#ifdef MUD_GEOM_MODULE
extern "C"
MUD_GEOM_EXPORT Module& getModule();
#endif
