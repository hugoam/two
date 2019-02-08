#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <gfx-gltf/Forward.h>
//#include <gfx-gltf/Types.h>

#ifndef MUD_GFX_GLTF_REFL_EXPORT
#define MUD_GFX_GLTF_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_GLTF_REFL_EXPORT mud_gfx_gltf : public mud::Module
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
