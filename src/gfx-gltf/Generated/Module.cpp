
#include <gfx-gltf/Generated/Module.h>

#ifdef MUD_GFX_GLTF_REFLECT
#include <gfx-gltf/Generated/Convert.h>

#define MUD_GFX_GLTF_REFLECTION_IMPL
#include <gfx-gltf/Generated/Meta.h>
#endif

namespace mud
{
	mudgfxgltf::mudgfxgltf()
		: Module("mud::gfxgltf")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudmath::module();
        mudgeom::module();
        mudgfx::module();

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
	return mudgfxgltf::module();
}
#endif
