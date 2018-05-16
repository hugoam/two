
#include <edit/Generated/Module.h>

#ifdef MUD_EDIT_REFLECT
#include <edit/Generated/Convert.h>

#define MUD_EDIT_REFLECTION_IMPL
#include <edit/Generated/Meta.h>
#endif

namespace mud
{
	mudedit::mudedit()
		: Module("mud::edit")
	{
        // ensure dependencies are instantiated
        mudobj::module();
        mudmath::module();
        mudgeom::module();
        mudlang::module();
        mudui::module();
        muduio::module();
        mudgfx::module();

#ifdef MUD_EDIT_REFLECT
        // setup reflection meta data
		edit_meta(*this);
#endif
	}
}

#ifdef MUD_EDIT_MODULE
extern "C"
MUD_EDIT_EXPORT Module& getModule()
{
	return mudedit::module();
}
#endif
