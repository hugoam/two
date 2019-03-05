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
	PassDepth::PassDepth(GfxSystem& gfx, cstring name, BlockDepth& block_depth)
		: DrawPass(gfx, name, PassType::Depth)
		, m_block_depth(block_depth)
	{}

	PassDepth::PassDepth(GfxSystem& gfx, BlockDepth& block_depth)
		: PassDepth(gfx, "depth", block_depth)
	{}

	void PassDepth::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		if(m_block_depth.m_depth_method == DepthMethod::Distance)
			render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_WRITE_A | BGFX_STATE_CULL_CW;
		else
			render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW;

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);
	}

	void PassDepth::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);

		if(element.m_material->m_base.m_depth_draw == DepthDraw::Enabled
		&& !element.m_material->m_alpha.m_is_alpha)
		{
			const DepthMethod depth_method = m_block_depth.m_depth_method;
			const Program& program = depth_method == DepthMethod::Distance ? *m_block_depth.m_distance_program
																		   : *m_block_depth.m_depth_program;

			element.m_program = &program;
			element.m_shader_version = element.m_material->shader_version(*element.m_program);

			this->add_element(render, element);
		}
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

	void BlockDepth::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockDepth::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(render_pass);
		bgfx::setViewUniform(render_pass.m_index, u_depth.u_depth_params, &m_depth_params);

		vec4 distance_params_0 = { m_distance_params.m_eye, 0.f };
		vec4 distance_params_1 = { m_distance_params.m_near, m_distance_params.m_far, 0.f, 0.f };
		bgfx::setViewUniform(render_pass.m_index, u_depth.u_distance_params_0, &distance_params_0);
		bgfx::setViewUniform(render_pass.m_index, u_depth.u_distance_params_1, &distance_params_1);
	}

	void BlockDepth::submit(Render& render, const DrawElement& element, const Pass& render_pass) const
	{
		UNUSED(render); UNUSED(element); UNUSED(render_pass);
	}
}
