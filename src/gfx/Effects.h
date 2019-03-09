//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Renderer.h>

namespace mud
{
	export_ MUD_GFX_EXPORT void pass_effects(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_EXPORT void pass_post_process(GfxSystem& gfx, Render& render);
}
