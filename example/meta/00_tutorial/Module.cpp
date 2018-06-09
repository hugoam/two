#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module .ex_00_tutorial;
#else
#include <meta/00_tutorial/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/00_tutorial/Convert.h>
#endif
#define _00_TUTORIAL_REFLECTION_IMPL
#include <meta/00_tutorial/Meta.h>

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

        // setup reflection meta data
		ex_00_tutorial_meta(*this);
	}

#ifdef _00_TUTORIAL_MODULE
extern "C"
Module& getModule()
{
	return ex_00_tutorial::m();
}
#endif
