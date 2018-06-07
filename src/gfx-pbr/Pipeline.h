//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/EnumArray.h>
#include <gfx/Pipeline.h>
#endif
#include <gfx-pbr/Generated/Forward.h>

namespace mud
{
	struct ReflectionRenderer : public Renderer
	{
		ReflectionRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	struct MainRenderer : public Renderer
	{
		MainRenderer(GfxSystem& gfx_system, Pipeline& pipeline);
	};

	export_ MUD_GFX_PBR_EXPORT void pipeline_pbr(GfxSystem& gfx_system, Pipeline& pipeline);
}
