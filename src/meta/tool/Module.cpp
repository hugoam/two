#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.tool;
#else
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/lang/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#include <meta/gfx-ui/Module.h>
#include <meta/gfx-edit/Module.h>
#include <meta/tool/Module.h>
#include <meta/tool/Convert.h>
#endif

#include <tool/Api.h>
#define MUD_TOOL_REFLECTION_IMPL
#include <meta/tool/Meta.h>

namespace mud
{
	mud_tool::mud_tool()
		: Module("mud::tool", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_lang::m(), &mud_math::m(), &mud_geom::m(), &mud_ctx::m(), &mud_ui::m(), &mud_uio::m(), &mud_gfx::m(), &mud_gfx_pbr::m(), &mud_gfx_ui::m(), &mud_gfx_edit::m() })
	{
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
