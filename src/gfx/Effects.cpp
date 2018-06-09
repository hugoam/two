//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <infra/Vector.h>
#include <gfx/Types.h>
#include <gfx/Effects.h>
#include <gfx/Filter.h>
#include <gfx/RenderTarget.h>
#endif

namespace mud
{
	PassEffects::PassEffects(GfxSystem& gfx_system)
		: RenderPass(gfx_system, "effects", PassType::Effects)
	{}

	void PassEffects::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}

	void PassEffects::submit_render_pass(Render& render)
	{
		UNUSED(render);
	}

	BlockResolve::BlockResolve(GfxSystem& gfx_system, BlockCopy& copy)
		: GfxBlock(gfx_system, *this)
		, m_copy(copy)
	{}

	void BlockResolve::init_gfx_block()
	{}

	void BlockResolve::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}
	
	void BlockResolve::submit_gfx_block(Render& render)
	{
		if(!render.m_is_mrt) return;
		
		// @todo three passes to resolve ? this is terrible :( but we can't read and write from the same buffer at the same time can we
		bgfx::FrameBufferHandle target = render.m_target->m_ping_pong.swap();
		m_copy.submit_quad(*render.m_target, render.composite_pass(), target,
						   render.m_target->m_diffuse, { vec4(render.m_viewport.m_rect), true });

		m_copy.submit_quad(*render.m_target, render.composite_pass(), target,
						   render.m_target->m_specular, { vec4(render.m_viewport.m_rect), true }, BGFX_STATE_BLEND_ADD);

		m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target_fbo,
						   render.m_target->m_ping_pong.last(), { vec4(render.m_viewport.m_rect), true });
	}

	PassPostProcess::PassPostProcess(GfxSystem& gfx_system, BlockCopy& copy)
		: RenderPass(gfx_system, "post process", PassType::PostProcess)
		, m_copy(copy)
	{}

	void PassPostProcess::begin_render_pass(Render& render)
	{
		m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_post_process.swap(),
						   render.m_target->m_diffuse, { vec4(render.m_viewport.m_rect), true });
	}

	void PassPostProcess::submit_render_pass(Render& render)
	{
		UNUSED(render);
	}
}