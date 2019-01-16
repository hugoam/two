#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-ui;
#else
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-ui/Module.h>
#endif

#include <gfx-ui/Api.h>

#ifndef MUD_MODULES
#include <meta/gfx-ui/Convert.h>
#endif
#define MUD_GFX_UI_REFLECTION_IMPL
#include <meta/gfx-ui/Meta.h>

namespace mud
{
	mud_gfx_ui::mud_gfx_ui()
		: Module("mud::gfx-ui", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m(), &mud_ctx::m(), &mud_ui::m(), &mud_gfx::m() })
	{
		// setup reflection meta data
		mud_gfx_ui_meta(*this);
	}
}

#ifdef MUD_GFX_UI_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_ui::m();
}
#endif
