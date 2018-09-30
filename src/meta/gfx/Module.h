
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ctx-glfw/Module.h>
#include <meta/bgfx/Module.h>
#endif
        
#include <gfx/Forward.h>
#include <gfx/Types.h>
#include <gfx/Api.h>

#include <meta/gfx/Convert.h>

#ifndef MUD_GFX_REFL_EXPORT
#define MUD_GFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_REFL_EXPORT mud_gfx : public Module
	{
	private:
		mud_gfx();

	public:
		static mud_gfx& m() { static mud_gfx instance; return instance; }
	};
}

#ifdef MUD_GFX_MODULE
extern "C"
MUD_GFX_REFL_EXPORT Module& getModule();
#endif
