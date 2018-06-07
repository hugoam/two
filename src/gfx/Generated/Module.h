
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
        
#include <gfx/Generated/Forward.h>
#include <gfx/Generated/Types.h>
#include <gfx/Api.h>

#include <gfx/Generated/Convert.h>

namespace mud
{
	export_ class MUD_GFX_EXPORT mudgfx : public Module
	{
	private:
		mudgfx();

	public:
		static mudgfx& m() { static mudgfx instance; return instance; }
	};
}

#ifdef MUD_GFX_MODULE
extern "C"
MUD_GFX_EXPORT Module& getModule();
#endif
