
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/obj/Module.h>
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
	export_ class MUD_GFX_OBJ_REFL_EXPORT mudgfxobj : public Module
	{
	private:
		mudgfxobj();

	public:
		static mudgfxobj& m() { static mudgfxobj instance; return instance; }
	};
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
MUD_GFX_OBJ_REFL_EXPORT Module& getModule();
#endif
