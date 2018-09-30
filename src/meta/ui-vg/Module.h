
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/ui/Module.h>
#endif
        
#include <ui-vg/Forward.h>
#include <ui-vg/Types.h>
#include <ui-vg/Api.h>

#include <meta/ui-vg/Convert.h>

#ifndef MUD_UI_VG_REFL_EXPORT
#define MUD_UI_VG_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UI_VG_REFL_EXPORT mud_ui_vg : public Module
	{
	private:
		mud_ui_vg();

	public:
		static mud_ui_vg& m() { static mud_ui_vg instance; return instance; }
	};
}

#ifdef MUD_UI_VG_MODULE
extern "C"
MUD_UI_VG_REFL_EXPORT Module& getModule();
#endif
