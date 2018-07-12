
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/obj/Module.h>
#include <meta/math/Module.h>
#include <meta/ui/Module.h>
#endif
        
#include <ui-nanovg-bgfx/Forward.h>
#include <ui-nanovg-bgfx/Types.h>
#include <ui-nanovg-bgfx/Api.h>

#include <meta/ui-nanovg-bgfx/Convert.h>

#ifndef MUD_UI_NANOVG_BGFX_REFL_EXPORT
#define MUD_UI_NANOVG_BGFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UI_NANOVG_BGFX_REFL_EXPORT mud_ui_nanovg_bgfx : public Module
	{
	private:
		mud_ui_nanovg_bgfx();

	public:
		static mud_ui_nanovg_bgfx& m() { static mud_ui_nanovg_bgfx instance; return instance; }
	};
}

#ifdef MUD_UI_NANOVG_BGFX_MODULE
extern "C"
MUD_UI_NANOVG_BGFX_REFL_EXPORT Module& getModule();
#endif
