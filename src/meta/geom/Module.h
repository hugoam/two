
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/obj/Module.h>
#include <meta/math/Module.h>
#endif
        
#include <geom/Forward.h>
#include <geom/Types.h>
#include <geom/Api.h>

#include <meta/geom/Convert.h>

#ifndef MUD_GEOM_REFL_EXPORT
#define MUD_GEOM_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GEOM_REFL_EXPORT mudgeom : public Module
	{
	private:
		mudgeom();

	public:
		static mudgeom& m() { static mudgeom instance; return instance; }
	};
}

#ifdef MUD_GEOM_MODULE
extern "C"
MUD_GEOM_REFL_EXPORT Module& getModule();
#endif
