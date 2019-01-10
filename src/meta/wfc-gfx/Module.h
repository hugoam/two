#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/type/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/wfc/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-ui/Module.h>
#endif

#include <wfc-gfx/Forward.h>
#include <wfc-gfx/Types.h>
#include <wfc-gfx/Api.h>

#include <meta/wfc-gfx/Convert.h>

#ifndef MUD_WFC_GFX_REFL_EXPORT
#define MUD_WFC_GFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_WFC_GFX_REFL_EXPORT mud_wfc_gfx : public Module
	{
	private:
		mud_wfc_gfx();
		
	public:
		static mud_wfc_gfx& m() { static mud_wfc_gfx instance; return instance; }
	};
}

#ifdef MUD_WFC_GFX_MODULE
extern "C"
MUD_WFC_GFX_REFL_EXPORT Module& getModule();
#endif
