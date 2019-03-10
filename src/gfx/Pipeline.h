//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/function.h>
#include <stl/table.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Renderer.h>

namespace mud
{
	using PassJob = function<void(Render&, const Pass&)>;

	export_ MUD_GFX_EXPORT void pipeline_minimal(GfxSystem& gfx, Renderer& pipeline, bool deferred);

	export_ struct MUD_GFX_EXPORT PassJobs
	{
		table<PassType, vector<PassJob>> m_jobs;
	};

	export_ MUD_GFX_EXPORT void pass_clear(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_EXPORT void pass_depth(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_EXPORT void pass_background(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_EXPORT void pass_solid(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_EXPORT void pass_flip(GfxSystem& gfx, Render& render);

	export_ MUD_GFX_EXPORT void render_minimal(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_EXPORT void render_solid(GfxSystem& gfx, Render& render);
	export_ MUD_GFX_EXPORT void render_clear(GfxSystem& gfx, Render& render);
}
