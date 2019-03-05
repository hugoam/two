//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/algorithm.h>
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

	void pipeline_minimal(GfxSystem& gfx, Pipeline& pipeline, bool deferred)
	{
		UNUSED(deferred);

		BlockMaterial& material = pipeline.add_block<BlockMaterial>(gfx);
		UNUSED(material);

		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx, filter);
		
		// pipeline
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx, filter);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx);
		UNUSED(particles);

		// mrt
		BlockResolve& resolve = pipeline.add_block<BlockResolve>(gfx, copy);

		// effects

		pipeline.m_pass_blocks[PassType::Depth] = { &depth };
		pipeline.m_pass_blocks[PassType::Solid] = {};
		pipeline.m_pass_blocks[PassType::Background] = { &sky };
		pipeline.m_pass_blocks[PassType::Opaque] = {};
		pipeline.m_pass_blocks[PassType::Alpha] = {};
		pipeline.m_pass_blocks[PassType::Effects] = { &resolve };
		pipeline.m_pass_blocks[PassType::PostProcess] = {};

		auto create_programs = [&]()
		{
			Program& solid = gfx.programs().create("solid");
			solid.register_blocks(pipeline.m_pass_blocks[PassType::Solid]);
			solid.m_blocks[MaterialBlock::Alpha] = true;
			solid.m_blocks[MaterialBlock::Solid] = true;

			Program& depth = gfx.programs().create("depth");
			depth.register_blocks(pipeline.m_pass_blocks[PassType::Depth]);
			depth.m_blocks[MaterialBlock::Alpha] = true;

			Program& distance = gfx.programs().create("distance");
			distance.register_blocks(pipeline.m_pass_blocks[PassType::Depth]);
			distance.m_blocks[MaterialBlock::Alpha] = true;

			Program& pbr = gfx.programs().create("pbr/pbr");
			pbr.register_blocks(pipeline.m_pass_blocks[PassType::Opaque]);
			pbr.m_blocks[MaterialBlock::Alpha] = true;
			pbr.m_blocks[MaterialBlock::Pbr] = true;

			Program& fresnel = gfx.programs().create("fresnel");
			fresnel.m_blocks[MaterialBlock::Alpha] = true;
			fresnel.m_blocks[MaterialBlock::Fresnel] = true;
		};

		create_programs();

		static MinimalRenderer main_renderer = { gfx, pipeline };
		static MinimalRenderer shadow_renderer = { gfx, pipeline };

		gfx.set_renderer(Shading::Shaded, main_renderer);
		gfx.set_renderer(Shading::Volume, shadow_renderer);

		pipeline.m_gather_func = gather_render;
	}

	Pipeline::Pipeline(GfxSystem& gfx)
	{
		UNUSED(gfx);
	}

	Pipeline::~Pipeline()
	{}

	MinimalRenderer::MinimalRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Shaded)
	{
		this->add_pass<PassClear>(gfx);
		//this->add_pass<PassOpaque>(gfx);
		this->add_pass<PassParticles>(gfx);
		this->add_pass<PassSolid>(gfx);
		this->add_pass<PassFlip>(gfx, *pipeline.block<BlockCopy>());
		this->init();
	}

	SolidRenderer::SolidRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Solid)
	{
		this->add_pass<PassClear>(gfx);
		this->add_pass<PassSolid>(gfx);
		this->add_pass<PassFlip>(gfx, *pipeline.block<BlockCopy>());
		this->init();
	}

	ClearRenderer::ClearRenderer(GfxSystem& gfx, Pipeline& pipeline)
		: Renderer(gfx, pipeline, Shading::Clear)
	{
		this->add_pass<PassClear>(gfx);
		this->init();
	}

	static uint8_t s_blank = 0;
	static uint8_t s_zero = 1;

	PassClear::PassClear(GfxSystem& gfx)
		: RenderPass(gfx, "clear", PassType::Clear)
	{
		bgfx::setPaletteColor(s_blank, 0.f, 0.f, 0.f, 1.f);
		bgfx::setPaletteColor(s_zero, 0.f, 0.f, 0.f, 0.f);
	}

	void PassClear::submit_render_pass(Render& render)
	{
		Pass render_pass = render.next_pass("clear");

		if(render.m_target && render.m_target->m_mrt) //render_pass.m_use_mrt)
			bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_blank, s_blank, s_blank, s_blank);
		else
			bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, to_rgba(render.m_viewport.m_clear_colour), 1.f, 0);

		if(render.m_target && render.m_target->m_deferred)
		{
			Pass gbuffer_pass = render.next_pass("clear gbuffer");
			bgfx::setViewClear(gbuffer_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_zero, s_zero, s_zero, s_zero);
			bgfx::setViewFrameBuffer(gbuffer_pass.m_index, render.m_target->m_gbuffer.m_fbo);
		}

		bgfx::touch(render_pass.m_index);
	}

	PassSolid::PassSolid(GfxSystem& gfx)
		: DrawPass(gfx, "solid", PassType::Solid)
	{}

	void PassSolid::next_draw_pass(Render& render, Pass& render_pass)
	{
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL
									 | BGFX_STATE_MSAA | BGFX_STATE_CULL_CW;// | BGFX_STATE_BLEND_ALPHA;

		bgfx::Encoder& encoder = *render_pass.m_encoder;
		for(ImmediateDraw* immediate : render.m_shot->m_immediate)
			immediate->submit(encoder, render_pass.m_index, render_pass.m_bgfx_state);
	}

	void PassSolid::queue_draw_element(Render& render, DrawElement& element)
	{
		UNUSED(render);

		if(element.m_program->m_blocks[MaterialBlock::Solid] || element.m_program->m_blocks[MaterialBlock::Fresnel])
		{
			blend_state(element.m_material->m_base.m_blend_mode, element.m_bgfx_state);
			this->add_element(render, element);
		}
	}

	PassBackground::PassBackground(GfxSystem& gfx)
		: RenderPass(gfx, "background", PassType::Background)
	{}

	void PassBackground::submit_render_pass(Render& render)
	{
		UNUSED(render);
	}

	PassFlip::PassFlip(GfxSystem& gfx, BlockCopy& copy)
		: RenderPass(gfx, "post process", PassType::Flip)
		, m_copy(copy)
	{}

	void PassFlip::submit_render_pass(Render& render)
	{
		m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_diffuse, render.m_viewport.m_rect);
	}
}