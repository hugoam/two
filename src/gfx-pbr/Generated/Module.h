
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <gfx/Generated/Module.h>
#endif
        
#include <gfx-pbr/Generated/Forward.h>
#include <gfx-pbr/Generated/Types.h>
#include <gfx-pbr/Api.h>

#include <gfx-pbr/Generated/Convert.h>

namespace mud
{
	export_ class MUD_GFX_PBR_EXPORT mudgfxpbr : public Module
	{
	private:
		mudgfxpbr();

	public:
		static mudgfxpbr& m() { static mudgfxpbr instance; return instance; }
	};
}

#ifdef MUD_GFX_PBR_MODULE
extern "C"
MUD_GFX_PBR_EXPORT Module& getModule();
#endif
