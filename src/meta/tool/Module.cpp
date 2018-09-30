#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#include <meta/tool/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/tool/Convert.h>
#endif
#define MUD_TOOL_REFLECTION_IMPL
#include <meta/tool/Meta.h>

namespace mud
{
	mud_tool::mud_tool()
		: Module("mud::tool")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_tree::m();
        mud_type::m();
        mud_refl::m();
        mud_srlz::m();
        mud_lang::m();
        mud_math::m();
        mud_geom::m();
        mud_ctx::m();
        mud_ui::m();
        mud_uio::m();
        mud_gfx::m();
        mud_gfx_pbr::m();

        // setup reflection meta data
		mud_tool_meta(*this);
	}
}

#ifdef MUD_TOOL_MODULE
extern "C"
Module& getModule()
{
	return mud_tool::m();
}
#endif
