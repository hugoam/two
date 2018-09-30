
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/gfx/Module.h>
#endif
        
#include <gfx-obj/Forward.h>
#include <gfx-obj/Types.h>
#include <gfx-obj/Api.h>

#include <meta/gfx-obj/Convert.h>

#ifndef MUD_GFX_OBJ_REFL_EXPORT
#define MUD_GFX_OBJ_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_OBJ_REFL_EXPORT mud_gfx_obj : public Module
	{
	private:
		mud_gfx_obj();

	public:
		static mud_gfx_obj& m() { static mud_gfx_obj instance; return instance; }
	};
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
MUD_GFX_OBJ_REFL_EXPORT Module& getModule();
#endif
