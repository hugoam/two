//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <cstdint>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.gfx-pbr;
#else
#include <obj/Vector.h>
#include <gfx/Item.h>
#include <gfx/Material.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Generated/Types.h>
#include <gfx-pbr/Depth.h>
#endif

namespace mud
{
	PassDepth::PassDepth(GfxSystem& gfx_system, BlockDepth& block_depth)
		: DrawPass(gfx_system, "depth", PassType::Depth)
		, m_block_depth(block_depth)
	{}

	void PassDepth::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_Z | BGFX_STATE_DEPTH_TEST_LEQUAL | BGFX_STATE_CULL_CW ;

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthAscending);

		//m_block_depth.m_depth_params = {};
		//m_block_depth.m_depth_params.m_depth_normal_bias = 1.f;
		bgfx::setUniform(m_block_depth.u_depth.u_depth_params, &m_block_depth.m_depth_params);
	}

	void PassDepth::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);

		if(element.m_item->m_cast_shadows == ItemShadow::DoubleSided)
			element.m_material = m_block_depth.m_depth_material_twosided;
		else
			element.m_material = m_block_depth.m_depth_material;

		element.m_shader_version = { element.m_material->m_program };

		add_element(element);
	}

	void PassDepth::submit_draw_element(Pass& render_pass, DrawElement& element)
	{
		UNUSED(render_pass); UNUSED(element);
	}

	BlockDepth::BlockDepth(GfxSystem& gfx_system)
		: DrawBlock(gfx_system, type<BlockDepth>())
	{}

	BlockDepth::~BlockDepth()
	{}

	void BlockDepth::init_gfx_block()
	{
		m_depth_material = &m_gfx_system.fetch_material("depth", "depth");
		m_depth_material_twosided = &m_gfx_system.fetch_material("depth_twosided", "depth");
		m_depth_material_twosided->m_base_block.m_cull_mode = CullMode::None;
		u_depth.createUniforms();
	}

	void BlockDepth::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::begin_gfx_pass(Render& render)
	{
		UNUSED(render);
	}

	void BlockDepth::submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element)
	{
		UNUSED(render); UNUSED(render_pass); UNUSED(element);
	}
}
