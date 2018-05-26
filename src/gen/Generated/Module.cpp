
#include <gen/Generated/Module.h>

#ifdef MUD_GEN_REFLECT
#include <gen/Generated/Convert.h>

#define MUD_GEN_REFLECTION_IMPL
#include <gen/Generated/Meta.h>
#endif

namespace mud
{
	mudgen::mudgen()
		: Module("mud::gen")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudmath::module();
        mudgeom::module();
        mudui::module();
        mudgfx::module();
        mudedit::module();

#ifdef MUD_GEN_REFLECT
        // setup reflection meta data
		gen_meta(*this);
#endif
	}
}

#ifdef MUD_GEN_MODULE
extern "C"
MUD_GEN_EXPORT Module& getModule()
{
	return mudgen::module();
}
#endif
