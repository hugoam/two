#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module .ex_00_tutorial;
#else
#include <00_tutorial/Refl/Module.h>
#endif

#ifdef _00_TUTORIAL_REFLECT
#ifndef MUD_MODULES
#include <00_tutorial/Refl/Convert.h>
#endif
#define _00_TUTORIAL_REFLECTION_IMPL
#include <00_tutorial/Refl/Meta.h>
#endif

	ex_00_tutorial::ex_00_tutorial()
		: Module("ex_00_tutorial")
	{
        // ensure dependencies are instantiated
        mudobj::m();
        mudmath::m();
        mudui::m();
        muduio::m();
        mudgfx::m();
        mudedit::m();
        mudprocgen::m();
        mudprocgen_gfx::m();

#ifdef _00_TUTORIAL_REFLECT
        // setup reflection meta data
		ex_00_tutorial_meta(*this);
#endif
	}

#ifdef _00_TUTORIAL_MODULE
extern "C"
_00_TUTORIAL_EXPORT Module& getModule()
{
	return ex_00_tutorial::m();
}
#endif
