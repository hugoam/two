#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gltf/Module.h>
#endif

#include <gfx-gltf/Forward.h>
#include <gfx-gltf/Types.h>
#include <gfx-gltf/Api.h>

#include <meta/gfx-gltf/Convert.h>

#ifndef MUD_GFX_GLTF_REFL_EXPORT
#define MUD_GFX_GLTF_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_GLTF_REFL_EXPORT mud_gfx_gltf : public Module
	{
	private:
		mud_gfx_gltf();
		
	public:
		static mud_gfx_gltf& m() { static mud_gfx_gltf instance; return instance; }
	};
}

#ifdef MUD_GFX_GLTF_MODULE
extern "C"
MUD_GFX_GLTF_REFL_EXPORT Module& getModule();
#endif
