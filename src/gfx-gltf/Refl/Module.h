
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
        
#include <gfx-gltf/Forward.h>
#include <gfx-gltf/Types.h>
#include <gfx-gltf/Api.h>

#include <gfx-gltf/Refl/Convert.h>

#ifndef MUD_GFX_GLTF_REFL_EXPORT
#define MUD_GFX_GLTF_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_GLTF_REFL_EXPORT mudgfxgltf : public Module
	{
	private:
		mudgfxgltf();

	public:
		static mudgfxgltf& m() { static mudgfxgltf instance; return instance; }
	};
}

#ifdef MUD_GFX_GLTF_MODULE
extern "C"
MUD_GFX_GLTF_REFL_EXPORT Module& getModule();
#endif
