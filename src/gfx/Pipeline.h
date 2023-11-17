//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Renderer.h>

namespace two
{
	using PassJob = function<void(GfxSystem&, Render&, const Pass&)>;

	export_ TWO_GFX_EXPORT void pipeline_minimal(GfxSystem& gfx, Renderer& pipeline, bool deferred);

	export_ struct TWO_GFX_EXPORT PassJobs
	{
		table<PassType, vector<PassJob>> m_jobs;
	};

	export_ TWO_GFX_EXPORT func_ void pass_clear_fbo(GfxSystem& gfx, Render& render, FrameBuffer& fbo, const Colour& colour, float depth = 1.f);

	export_ TWO_GFX_EXPORT func_ void pass_clear(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_gclear(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_depth(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_background(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_solid(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void pass_flip(GfxSystem& gfx, Render& render);

	export_ TWO_GFX_EXPORT func_ void render_minimal(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void render_solid(GfxSystem& gfx, Render& render);
	export_ TWO_GFX_EXPORT func_ void render_clear(GfxSystem& gfx, Render& render);
}
