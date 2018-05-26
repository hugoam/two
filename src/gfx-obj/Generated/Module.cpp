
#include <gfx-obj/Generated/Module.h>

#ifdef MUD_GFX_OBJ_REFLECT
#include <gfx-obj/Generated/Convert.h>

#define MUD_GFX_OBJ_REFLECTION_IMPL
#include <gfx-obj/Generated/Meta.h>
#endif

namespace mud
{
	mudgfxobj::mudgfxobj()
		: Module("mud::gfxobj")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudmath::module();
        mudgeom::module();
        mudgfx::module();

#ifdef MUD_GFX_OBJ_REFLECT
        // setup reflection meta data
		gfxobj_meta(*this);
#endif
	}
}

#ifdef MUD_GFXOBJ_MODULE
extern "C"
MUD_GFX_OBJ_EXPORT Module& getModule()
{
	return mudgfxobj::module();
}
#endif
