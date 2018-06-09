#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module .ex_15_script;
#else
#include <15_script/Refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <15_script/Refl/Convert.h>
#endif
#define _15_SCRIPT_REFLECTION_IMPL
#include <15_script/Refl/Meta.h>

	ex_15_script::ex_15_script()
		: Module("ex_15_script")
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
		ex_15_script_meta(*this);
	}

#ifdef _15_SCRIPT_MODULE
extern "C"
Module& getModule()
{
	return ex_15_script::m();
}
#endif
