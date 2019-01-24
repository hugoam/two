#pragma once

#include <mud/gfx.ui.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::ui::OrbitMode& val) { val = mud::ui::OrbitMode(enu<mud::ui::OrbitMode>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ui::OrbitMode& val, string& str) { str = enu<mud::ui::OrbitMode>().name(uint32_t(val)); };
	
	
}

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif


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

