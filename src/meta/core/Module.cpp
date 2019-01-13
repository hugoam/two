#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.core;
#else
#include <meta/core/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/core/Convert.h>
#endif
#define MUD_CORE_REFLECTION_IMPL
#include <meta/core/Meta.h>

namespace mud
{
	mud_core::mud_core()
		: Module("mud::core", { &mud_gfx::m(), &mud_gfx_ui::m() })
	{
		// setup reflection meta data
		mud_core_meta(*this);
	}
}

#ifdef MUD_CORE_MODULE
extern "C"
Module& getModule()
{
		return mud_core::m();
}
#endif
