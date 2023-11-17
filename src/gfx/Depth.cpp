//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <bgfx/bgfx.h>
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
	bool queue_depth(GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
	{
		UNUSED(render); UNUSED(pass); UNUSED(element);
		static BlockDepth& block_depth = *gfx.m_renderer.block<BlockDepth>();

		if(element.m_material->m_base.m_depth_draw != DepthDraw::Enabled
		|| element.m_material->m_alpha.m_is_alpha)
			return false;

		const DepthMethod depth_method = block_depth.m_depth_method;
		const Program& program = depth_method == DepthMethod::Distance ? *block_depth.m_distance_program
																	   : *block_depth.m_depth_program;

		element.set_program(program);
		return true;
	}

	void pass_depth(GfxSystem& gfx, Render& render, Pass& pass, bool submit)
	{
		static BlockDepth& block_depth = *gfx.m_renderer.block<BlockDepth>();
		block_depth.submit(render, pass);

		const bool is_color = block_depth.m_depth_method == DepthMethod::Distance
						   || block_depth.m_depth_method == DepthMethod::DepthPacked;
		UNUSED(render);
		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;
		if (is_color)
			pass.m_bgfx_state |= BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A;

		bgfx::setViewMode(pass.m_index, bgfx::ViewMode::DepthAscending);

		if(submit)
			gfx.m_renderer.pass(render, pass, queue_depth);
	}

#if 0
	void pass_override(GfxSystem& gfx, Render& render, Pass& pass, Program& program)
	{
		UNUSED(render);
		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;

		auto queue_draw_element = [&](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			element.set_program(program);
			return true;
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}
#endif

	void pass_depth(GfxSystem& gfx, Render& render)
	{
		Pass pass = render.next_pass("depth", PassType::Depth);
		pass_depth(gfx, render, pass);
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

	void BlockDepth::options(Render& render, const DrawElement& element, ProgramVersion& program) const
	{
		UNUSED(render); UNUSED(element); UNUSED(program);
	}

	void BlockDepth::submit(Render& render, const Pass& pass) const
	{
		UNUSED(render); UNUSED(pass);
		bgfx::setViewUniform(pass.m_index, u_depth.u_depth_p0, &m_depth_params);

		vec4 distance_p0 = { m_distance_params.m_eye, 0.f };
		vec4 distance_p1 = { m_distance_params.m_near, m_distance_params.m_far, 0.f, 0.f };
		bgfx::setViewUniform(pass.m_index, u_depth.u_distance_p0, &distance_p0);
		bgfx::setViewUniform(pass.m_index, u_depth.u_distance_p1, &distance_p1);
	}

	void BlockDepth::submit(Render& render, const DrawElement& element, const Pass& pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(pass);
	}
}
