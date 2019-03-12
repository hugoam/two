//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/algorithm.h>
#include <gfx/Item.h>
#include <gfx/Material.h>
#include <gfx/GfxSystem.h>
#include <gfx/Types.h>
#include <gfx/Depth.h>
#include <gfx/Asset.h>
#endif

namespace mud
{
	void queue_depth(GfxSystem& gfx, Render& render, Pass& pass, DrawElement element)
	{
		static BlockDepth& block_depth = *gfx.m_renderer.block<BlockDepth>();

		if(element.m_material->m_base.m_depth_draw == DepthDraw::Enabled
		&& !element.m_material->m_alpha.m_is_alpha)
		{
			const DepthMethod depth_method = block_depth.m_depth_method;
			const Program& program = depth_method == DepthMethod::Distance ? *block_depth.m_distance_program
																		   : *block_depth.m_depth_program;

			element.m_program = &program;
			element.m_shader_version = element.m_material->shader_version(*element.m_program);

			gfx.m_renderer.add_element(render, pass, element);
		}
	}

	void pass_depth(GfxSystem& gfx, Render& render, Pass& render_pass, bool submit)
	{
		static BlockDepth& block_depth = *gfx.m_renderer.block<BlockDepth>();
		block_depth.submit(render, render_pass);

		UNUSED(render);
		if(block_depth.m_depth_method == DepthMethod::Distance)
			render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW;
		else
			render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

		if(submit)
			gfx.m_renderer.pass(render, render_pass, queue_depth);
	}

#if 0
	void pass_override(GfxSystem& gfx, Render& render, Pass& render_pass, Program& program)
	{
		UNUSED(render);
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;

		auto queue_draw_element = [&](GfxSystem& gfx, Render& render, Pass& pass, DrawElement element)
		{
			element.m_program = &program;
			element.m_shader_version = element.m_material->shader_version(*element.m_program);

			gfx.m_renderer.add_element(render, pass, element);
		};

		gfx.m_renderer.pass(render, render_pass, queue_draw_element);
	}
#endif

	void pass_depth(GfxSystem& gfx, Render& render)
	{
		Pass render_pass = render.next_pass("depth", PassType::Depth);
		pass_depth(gfx, render, render_pass);
	}

	BlockDepth::BlockDepth(GfxSystem& gfx)
		: DrawBlock(gfx, type<BlockDepth>())
	{}

	BlockDepth::~BlockDepth()
	{}

	void BlockDepth::init_block()
	{
		m_depth_program = m_gfx.programs().file("depth");
		m_distance_program = m_gfx.programs().file("distance");

		u_depth.createUniforms();
	}

	void BlockDepth::begin_render(Render& render)
	{
		UNUSED(render);

		m_depth_params = {};
		m_distance_params = {};
	}

	void BlockDepth::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockDepth::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);
		bgfx::setViewUniform(render_pass.m_index, u_depth.u_depth_p0, &m_depth_params);

		vec4 distance_p0 = { m_distance_params.m_eye, 0.f };
		vec4 distance_p1 = { m_distance_params.m_near, m_distance_params.m_far, 0.f, 0.f };
		bgfx::setViewUniform(render_pass.m_index, u_depth.u_distance_p0, &distance_p0);
		bgfx::setViewUniform(render_pass.m_index, u_depth.u_distance_p1, &distance_p1);
	}

	void BlockDepth::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(render_pass);
	}
}
