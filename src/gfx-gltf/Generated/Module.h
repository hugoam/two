
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
        
#include <gfx-gltf/Generated/Forward.h>
#include <gfx-gltf/Generated/Types.h>

#include <gfx-gltf/ImporterGltf.h>

#include <gfx-gltf/Generated/Convert.h>

namespace mud
{
	export_ class MUD_GFX_GLTF_EXPORT mudgfxgltf : public Module
	{
	private:
		mudgfxgltf();

	public:
		static mudgfxgltf& m() { static mudgfxgltf instance; return instance; }
	};
}

#ifdef MUD_GFXGLTF_MODULE
extern "C"
MUD_GFX_GLTF_EXPORT Module& getModule();
#endif
