#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <gfx-edit/Forward.h>
#include <gfx-edit/Types.h>

#ifndef MUD_GFX_EDIT_REFL_EXPORT
#define MUD_GFX_EDIT_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_EDIT_REFL_EXPORT mud_gfx_edit : public Module
	{
	private:
		mud_gfx_edit();
		
	public:
		static mud_gfx_edit& m() { static mud_gfx_edit instance; return instance; }
	};
}

#ifdef MUD_GFX_EDIT_MODULE
extern "C"
MUD_GFX_EDIT_REFL_EXPORT Module& getModule();
#endif
