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

	void pipeline_minimal(GfxSystem& gfx, Renderer& pipeline, bool deferred)
	{
		UNUSED(deferred);

		BlockMaterial& material = pipeline.add_block<BlockMaterial>(gfx);
		UNUSED(material);

		// filters
		BlockFilter& filter = pipeline.add_block<BlockFilter>(gfx);
		BlockCopy& copy = pipeline.add_block<BlockCopy>(gfx, filter);
		UNUSED(copy);

		// pipeline
		BlockDepth& depth = pipeline.add_block<BlockDepth>(gfx);
		BlockSky& sky = pipeline.add_block<BlockSky>(gfx, filter);
		BlockParticles& particles = pipeline.add_block<BlockParticles>(gfx);
		UNUSED(sky);
		UNUSED(particles);

		vector<GfxBlock*> depth_blocks =  { &depth };

		auto create_programs = [&]()
		{
			Program& solid = gfx.programs().create("solid");
			//solid.register_blocks(pipeline.m_pass_blocks[PassType::Solid]);
			solid.m_blocks[MaterialBlock::Alpha] = true;
			solid.m_blocks[MaterialBlock::Solid] = true;

			Program& depth = gfx.programs().create("depth");
			depth.register_blocks(depth_blocks);
			depth.m_blocks[MaterialBlock::Alpha] = true;

			Program& distance = gfx.programs().create("distance");
			distance.register_blocks(depth_blocks);
			distance.m_blocks[MaterialBlock::Alpha] = true;

			Program& pbr = gfx.programs().create("pbr/pbr");
			//pbr.register_blocks(pipeline.m_pass_blocks[PassType::Opaque]);
			pbr.m_blocks[MaterialBlock::Alpha] = true;
			pbr.m_blocks[MaterialBlock::Pbr] = true;

			Program& fresnel = gfx.programs().create("fresnel");
			fresnel.m_blocks[MaterialBlock::Alpha] = true;
			fresnel.m_blocks[MaterialBlock::Fresnel] = true;
		};

		create_programs();

		gfx.set_renderer(Shading::Shaded, render_minimal);
		gfx.set_renderer(Shading::Volume, render_minimal);

		pipeline.m_gather_func = gather_render;
	}

	void render_minimal(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_particles(gfx, render);
		pass_solid(gfx, render);
		pass_flip(gfx, render);
	}

	void render_solid(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_solid(gfx, render);
		pass_flip(gfx, render);
	}

	void render_clear(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
	}

	static uint8_t s_blank = 0;
	static uint8_t s_zero = 1;

	struct ClearInit
	{
		ClearInit()
		{
			bgfx::setPaletteColor(s_blank, 0.f, 0.f, 0.f, 1.f);
			bgfx::setPaletteColor(s_zero, 0.f, 0.f, 0.f, 0.f);
		};
	};

	void pass_clear(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		static ClearInit init;

		Pass render_pass = render.next_pass("clear", PassType::Clear);

		if(render.m_target && render.m_target->m_mrt) //render_pass.m_use_mrt)
			bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_blank, s_blank, s_blank, s_blank);
		else
			bgfx::setViewClear(render_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, to_rgba(render.m_viewport.m_clear_colour), 1.f, 0);

		if(render.m_target && render.m_target->m_deferred)
		{
			Pass gbuffer_pass = render.next_pass("clear gbuffer", PassType::Clear);
			bgfx::setViewClear(gbuffer_pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_zero, s_zero, s_zero, s_zero);
			bgfx::setViewFrameBuffer(gbuffer_pass.m_index, render.m_target->m_gbuffer.m_fbo);
		}

		bgfx::touch(render_pass.m_index);
	}

	void pass_solid(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		Pass render_pass = render.next_pass("solid", PassType::Solid);
		
		render_pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL
									 | BGFX_STATE_MSAA | BGFX_STATE_CULL_CW;// | BGFX_STATE_BLEND_ALPHA;

		bgfx::Encoder& encoder = *render_pass.m_encoder;
		for(ImmediateDraw* immediate : render.m_shot->m_immediate)
			immediate->submit(encoder, render_pass.m_index, render_pass.m_bgfx_state);

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement element)
		{
			UNUSED(render);

			if(element.m_program->m_blocks[MaterialBlock::Solid] || element.m_program->m_blocks[MaterialBlock::Fresnel])
			{
				blend_state(element.m_material->m_base.m_blend_mode, element.m_bgfx_state);
				gfx.m_renderer.add_element(render, pass, element);
			}
		};

		gfx.m_renderer.pass(render, render_pass, queue_draw_element);
	}

	void pass_background(GfxSystem& gfx, Render& render)
	{
		static BlockSky& block_sky = *gfx.m_renderer.block<BlockSky>();

		//Pass render_pass = render.next_pass("background", PassType::Background);
		block_sky.submit_pass(render);
	}

	void pass_flip(GfxSystem& gfx, Render& render)
	{
		static BlockCopy& block_copy = *gfx.m_renderer.block<BlockCopy>();

		//Pass render_pass = render.next_pass("flip", PassType::Flip);
		block_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_diffuse, render.m_viewport.m_rect);
	}
}