#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfxgltf;
#else
#include <gfx-gltf/Refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <gfx-gltf/Refl/Convert.h>
#endif
#define MUD_GFX_GLTF_REFLECTION_IMPL
#include <gfx-gltf/Refl/Meta.h>

namespace mud
{
	mudgfxgltf::mudgfxgltf()
		: Module("mud::gfxgltf")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudsrlz::m();
        mudmath::m();
        mudgeom::m();
        mudgfx::m();

        // setup reflection meta data
		mudgfxgltf_meta(*this);
	}
}

#ifdef MUD_GFX_GLTF_MODULE
extern "C"
Module& getModule()
{
	return mudgfxgltf::m();
}
#endif
