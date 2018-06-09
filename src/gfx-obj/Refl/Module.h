
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <obj/Refl/Module.h>
#include <srlz/Refl/Module.h>
#include <math/Refl/Module.h>
#include <geom/Refl/Module.h>
#include <gfx/Refl/Module.h>
#endif
        
#include <gfx-obj/Forward.h>
#include <gfx-obj/Types.h>
#include <gfx-obj/Api.h>

#include <gfx-obj/Refl/Convert.h>

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
