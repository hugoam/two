
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <gfx/Generated/Module.h>
        
#include <gfx-pbr/Generated/Forward.h>
#include <gfx-pbr/Generated/Types.h>

#include <gfx-pbr/Depth.h>
#include <gfx-pbr/Light.h>
#include <gfx-pbr/Radiance.h>
#include <gfx-pbr/Reflection.h>
#include <gfx-pbr/ReflectionAtlas.h>
#include <gfx-pbr/Shadow.h>
#include <gfx-pbr/ShadowAtlas.h>
#include <gfx-pbr/ShadowCSM.h>
#include <gfx-pbr/Filters/Blur.h>
#include <gfx-pbr/Filters/DofBlur.h>
#include <gfx-pbr/Filters/Glow.h>
#include <gfx-pbr/Filters/Tonemap.h>

namespace mud
{
	export_ class MUD_GFX_PBR_EXPORT mudgfxpbr : public Module
	{
	private:
		mudgfxpbr();

	public:
		static mudgfxpbr& m() { static mudgfxpbr instance; return instance; }
	};
}

#ifdef MUD_GFXPBR_MODULE
extern "C"
MUD_GFX_PBR_EXPORT Module& getModule();
#endif
