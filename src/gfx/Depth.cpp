//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <infra/Vector.h>
#include <gfx/Item.h>
#include <gfx/Material.h>
#include <gfx/GfxSystem.h>
#include <gfx/Types.h>
#include <gfx/Depth.h>
#endif

namespace mud
{
	PassDepth::PassDepth(GfxSystem& gfx_system, cstring name, BlockDepth& block_depth)
		: DrawPass(gfx_system, name, PassType::Depth)
		, m_block_depth(block_depth)
	{}

	PassDepth::PassDepth(GfxSystem& gfx_system, BlockDepth& block_depth)
		: PassDepth(gfx_system, "depth", block_depth)
	{}

	void PassDepth::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW ;

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

		m_block_depth.m_current_params = &m_block_depth.m_depth_params;
	}

	void PassDepth::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		
		if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
		{
			if(element.m_item->m_shadow == ItemShadow::DoubleSided)
				element.m_material = m_block_depth.m_depth_material_twosided;
			else
				element.m_material = m_block_depth.m_depth_material;

			element.m_program = element.m_material->m_program;
			element.m_shader_version = { element.m_material->m_program };

			this->add_element(render, element);
		}
	}

	BlockDepth::BlockDepth(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockDepth>())
	{}

	BlockDepth::~BlockDepth()
	{}

	void BlockDepth::init_block()
	{
		m_depth_material = &m_gfx_system.fetch_material("depth", "depth");
		m_depth_material_twosided = &m_gfx_system.fetch_material("depth_twosided", "depth");
		m_depth_material_twosided->m_base_block.m_cull_mode = CullMode::None;
		u_depth.createUniforms();
	}

	void BlockDepth::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::begin_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::begin_draw_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::options(Render& render, ShaderVersion& shader_version) const
	{
		UNUSED(render); UNUSED(shader_version);
	}

	void BlockDepth::submit(Render& render, const Pass& render_pass) const
	{
		UNUSED(render);
		bgfx::Encoder& encoder = *render_pass.m_encoder;
		encoder.setUniform(u_depth.u_depth_params, &(*m_current_params));
	}
}
