
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/obj/Module.h>
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
#endif
        
#include <gfx-ui/Forward.h>
#include <gfx-ui/Types.h>
#include <gfx-ui/Api.h>

#include <meta/gfx-ui/Convert.h>

#ifndef MUD_GFX_UI_REFL_EXPORT
#define MUD_GFX_UI_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_UI_REFL_EXPORT mud_gfx_ui : public Module
	{
	private:
		mud_gfx_ui();

	public:
		static mud_gfx_ui& m() { static mud_gfx_ui instance; return instance; }
	};
}

#ifdef MUD_GFX_UI_MODULE
extern "C"
MUD_GFX_UI_REFL_EXPORT Module& getModule();
#endif
