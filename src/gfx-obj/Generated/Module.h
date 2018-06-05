
#pragma once

#ifndef MUD_MODULES
#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <gfx/Generated/Module.h>
#endif
        
#include <gfx-obj/Generated/Forward.h>
#include <gfx-obj/Generated/Types.h>

#include <gfx-obj/ImporterObj.h>

namespace mud
{
	export_ class MUD_GFX_OBJ_EXPORT mudgfxobj : public Module
	{
	private:
		mudgfxobj();

	public:
		static mudgfxobj& m() { static mudgfxobj instance; return instance; }
	};
}

#ifdef MUD_GFXOBJ_MODULE
extern "C"
MUD_GFX_OBJ_EXPORT Module& getModule();
#endif
