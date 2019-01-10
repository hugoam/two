#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#endif

#include <gfx-edit/Forward.h>
#include <gfx-edit/Types.h>
#include <gfx-edit/Api.h>

#include <meta/gfx-edit/Convert.h>

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
