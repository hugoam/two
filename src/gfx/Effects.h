//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Renderer.h>

namespace two
{
	export_ TWO_GFX_EXPORT void pass_resolve(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT void pass_effects(GfxSystem& gfx, Render& render);
}
