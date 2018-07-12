
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#endif
        
#include <ui-nanovg/Forward.h>
#include <ui-nanovg/Types.h>
#include <ui-nanovg/Api.h>

#include <meta/ui-nanovg/Convert.h>

#ifndef MUD_UI_NANOVG_REFL_EXPORT
#define MUD_UI_NANOVG_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UI_NANOVG_REFL_EXPORT mud_ui_nanovg : public Module
	{
	private:
		mud_ui_nanovg();

	public:
		static mud_ui_nanovg& m() { static mud_ui_nanovg instance; return instance; }
	};
}

#ifdef MUD_UI_NANOVG_MODULE
extern "C"
MUD_UI_NANOVG_REFL_EXPORT Module& getModule();
#endif
