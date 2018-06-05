#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfxgltf;
#else
#include <gfx-gltf/Generated/Module.h>
#endif

#ifdef MUD_GFX_GLTF_REFLECT
#ifndef MUD_MODULES
#include <gfx-gltf/Generated/Convert.h>
#endif
#define MUD_GFX_GLTF_REFLECTION_IMPL
#include <gfx-gltf/Generated/Meta.h>
#endif

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

#ifdef MUD_GFX_GLTF_REFLECT
        // setup reflection meta data
		gfxgltf_meta(*this);
#endif
	}
}

#ifdef MUD_GFXGLTF_MODULE
extern "C"
MUD_GFX_GLTF_EXPORT Module& getModule()
{
	return mudgfxgltf::m();
}
#endif
