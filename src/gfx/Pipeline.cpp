//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <infra/Vector.h>
#include <gfx/Types.h>
#include <gfx/Pipeline.h>
#include <gfx/Api.h>
#endif

namespace mud
{
#define MUD_GFX_STATE_DEFAULT 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL \
								| BGFX_STATE_WRITE_Z | BGFX_STATE_CULL_CW | BGFX_STATE_MSAA

#define MUD_GFX_STATE_DEFAULT_ALPHA 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LESS \
									  | BGFX_STATE_MSAA | BGFX_STATE_BLEND_ALPHA

	void pipeline_minimal(GfxSystem& gfx_system, Pipeline& pipeline)
	{
		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx_system);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx_system, filter);
		
		// pipeline
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx_system);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx_system, filter);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx_system);
		UNUSED(particles);

		// mrt
		BlockResolve& resolve = pipeline.add_block<BlockResolve>(gfx_system, copy);

		// effects

		pipeline.m_pass_blocks[size_t(PassType::Depth)] = { &depth };
		pipeline.m_pass_blocks[size_t(PassType::Unshaded)] = { &depth };
		pipeline.m_pass_blocks[size_t(PassType::Background)] = { &sky };
		pipeline.m_pass_blocks[size_t(PassType::Opaque)] = {};
		pipeline.m_pass_blocks[size_t(PassType::Alpha)] = {};
		pipeline.m_pass_blocks[size_t(PassType::Effects)] = { &resolve };
		pipeline.m_pass_blocks[size_t(PassType::PostProcess)] = {};

		gfx_system.programs().create("unshaded", [&](Program& program) { program.register_blocks(pipeline.pass_blocks(PassType::Unshaded)); });
		gfx_system.programs().create("depth", [&](Program& program) { program.register_blocks(pipeline.pass_blocks(PassType::Depth)); });
		gfx_system.programs().create("pbr/pbr", [&](Program& program) { program.register_blocks(pipeline.pass_blocks(PassType::Opaque)); });

		static MinimalRenderer main_renderer = { gfx_system, pipeline };
		static MinimalRenderer shadow_renderer = { gfx_system, pipeline };

		gfx_system.set_renderer(Shading::Shaded, main_renderer);
		gfx_system.set_renderer(Shading::Volume, shadow_renderer);
	}

	Pipeline::Pipeline(GfxSystem& gfx_system)
	{
		UNUSED(gfx_system);
	}

	Pipeline::~Pipeline()
	{}

	array<GfxBlock*> Pipeline::pass_blocks(PassType pass)
	{
		return to_array(m_pass_blocks[size_t(pass)]);
	}

	MinimalRenderer::MinimalRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassOpaque>(gfx_system);
		this->add_pass<PassUnshaded>(gfx_system);
		this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	UnshadedRenderer::UnshadedRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline)
	{
		this->add_pass<PassClear>(gfx_system);
		this->add_pass<PassUnshaded>(gfx_system);
		this->add_pass<PassFlip>(gfx_system, *pipeline.block<BlockCopy>());
		this->init();
	}

	ClearRenderer::ClearRenderer(GfxSystem& gfx_system, Pipeline& pipeline)
		: Renderer(gfx_system, pipeline)
	{
		this->add_pass<PassClear>(gfx_system);
		this->init();
	}

	PassClear::PassClear(GfxSystem& gfx_system)
		: RenderPass(gfx_system, "clear", PassType::Clear)
	{
		uint8_t blank = 5;
		bgfx::setPaletteColor(blank, 0.f, 0.f, 0.f, 1.f);
	}

	void PassClear::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}

	void PassClear::submit_render_pass(Render& render)
	{
		Pass render_pass = render.next_pass("clear");

		uint8_t blank = 5;

		if(render.m_target && render.m_target->m_mrt) //render_pass.m_use_mrt)
			bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, blank, blank, blank, blank);
		else
			bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, to_rgba(render.m_viewport.m_clear_colour), 1.f, 0);
	}

	PassUnshaded::PassUnshaded(GfxSystem& gfx_system)
		: DrawPass(gfx_system, "unshaded", PassType::Unshaded)
	{}

	void PassUnshaded::next_draw_pass(Render& render, Pass& render_pass)
	{
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL
									 | BGFX_STATE_MSAA | BGFX_STATE_CULL_CW | BGFX_STATE_BLEND_ALPHA;

		for(ImmediateDraw* immediate : render.m_shot->m_immediate)
			immediate->submit(render_pass.m_index, render_pass.m_bgfx_state);
	}

	void PassUnshaded::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);

		if(element.m_material->m_unshaded_block.m_enabled)
			add_element(element);
	}

	void PassUnshaded::submit_draw_element(Pass& render_pass, DrawElement& element)
	{
		UNUSED(render_pass); UNUSED(element);
	}

	PassOpaque::PassOpaque(GfxSystem& gfx_system)
		: DrawPass(gfx_system, "opaque", PassType::Opaque)
	{}

	void PassOpaque::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);
		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT;
	}

	void PassOpaque::queue_draw_element(Render& render, DrawElement& element)
	{
		if(element.m_material->m_pbr_block.m_enabled && !element.m_material->m_base_block.m_is_alpha)
		{
			element.m_shader_version.set_option(0, MRT, render.m_is_mrt);
			add_element(element);
		}
	}

	void PassOpaque::submit_draw_element(Pass& render_pass, DrawElement& element)
	{
		UNUSED(render_pass);
		if(element.m_material->m_base_block.m_depth_draw_mode == DepthDraw::Enabled)
			element.m_bgfx_state |= BGFX_STATE_WRITE_Z;
	}

	PassBackground::PassBackground(GfxSystem& gfx_system)
		: RenderPass(gfx_system, "background", PassType::Background)
	{}

	void PassBackground::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}

	void PassBackground::submit_render_pass(Render& render)
	{
		UNUSED(render);
	}

	PassAlpha::PassAlpha(GfxSystem& gfx_system)
		: DrawPass(gfx_system, "alpha", PassType::Alpha)
	{}

	void PassAlpha::next_draw_pass(Render& render, Pass& render_pass)
	{
		UNUSED(render);

		render_pass.m_bgfx_state = MUD_GFX_STATE_DEFAULT_ALPHA;

		bgfx::setViewMode(render_pass.m_index, bgfx::ViewMode::DepthDescending);
	}

	void PassAlpha::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);
		if(element.m_material->m_pbr_block.m_enabled && element.m_material->m_base_block.m_is_alpha)
			add_element(element);
	}

	void PassAlpha::submit_draw_element(Pass& render_pass, DrawElement& element)
	{
		UNUSED(render_pass);
		blend_state(element.m_material->m_base_block.m_blend_mode, element.m_bgfx_state);
	}

	PassFlip::PassFlip(GfxSystem& gfx_system, BlockCopy& copy)
		: RenderPass(gfx_system, "post process", PassType::Flip)
		, m_copy(copy)
	{}

	void PassFlip::begin_render_pass(Render& render)
	{
		UNUSED(render);
	}

	void PassFlip::submit_render_pass(Render& render)
	{
		m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_diffuse, { vec4(render.m_viewport.m_rect), true });
	}
}