//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
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

		vector<ShaderBlock*> depth_blocks =  { &depth };

		auto create_programs = [&]()
		{
			Program& solid = gfx.programs().create("solid");
			solid.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Solid });

			Program& depth = gfx.programs().create("depth");
			depth.register_blocks(depth_blocks);
			depth.set_blocks({ MaterialBlock::Alpha });

			Program& distance = gfx.programs().create("distance");
			distance.register_blocks(depth_blocks);
			distance.set_blocks({ MaterialBlock::Alpha });

			Program& pbr = gfx.programs().create("pbr/pbr");
			pbr.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Pbr });

			Program& fresnel = gfx.programs().create("fresnel");
			fresnel.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Fresnel });
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
	}

	void render_solid(GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_solid(gfx, render);
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

	void pass_clear_fbo(GfxSystem& gfx, Render& render, FrameBuffer& fbo, const Colour& colour, float depth)
	{
		UNUSED(gfx);
		Pass pass = render.next_pass("clear", PassType::Clear);

		bgfx::setViewRect(pass.m_index, 0, 0, uint16_t(fbo.m_size.x), uint16_t(fbo.m_size.y));
		bgfx::setViewClear(pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, to_rgba(colour), depth);
		bgfx::setViewFrameBuffer(pass.m_index, fbo);

		bgfx::touch(pass.m_index);
	}

	void pass_clear(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		static ClearInit init;

		Pass pass = render.next_pass("clear", PassType::Clear);

		if(render.m_target && render.m_target->m_mrt) //pass.m_use_mrt)
			bgfx::setViewClear(pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_blank, s_blank, s_blank, s_blank);
		else
			bgfx::setViewClear(pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, to_rgba(render.m_viewport->m_clear_colour), 1.f, 0);

		bgfx::touch(pass.m_index);
	}

	void pass_gclear(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		if(render.m_target && render.m_target->m_deferred)
		{
			Pass pass = render.next_pass("clear gbuffer", PassType::Clear);
			bgfx::setViewClear(pass.m_index, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 1.f, 0, s_zero, s_zero, s_zero, s_zero);
			bgfx::setViewFrameBuffer(pass.m_index, render.m_target->m_gbuffer.m_fbo);
			bgfx::touch(pass.m_index);
		}
	}

	void pass_solid(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx);
		Pass pass = render.next_pass("solid", PassType::Solid);
		
		pass.m_bgfx_state = 0 | BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_DEPTH_TEST_LEQUAL
							  | BGFX_STATE_MSAA | BGFX_STATE_CULL_CW;// | BGFX_STATE_BLEND_ALPHA;

		bgfx::Encoder& encoder = *pass.m_encoder;
		for(ImmediateDraw* immediate : render.m_shot->m_immediate)
			immediate->submit(encoder, pass.m_index, pass.m_bgfx_state);

		auto queue_draw_element = [](GfxSystem& gfx, Render& render, Pass& pass, DrawElement& element)
		{
			UNUSED(gfx); UNUSED(render); UNUSED(pass);
			const Program& program = *element.m_program.m_program;
			if(!program.m_blocks[MaterialBlock::Solid] && !program.m_blocks[MaterialBlock::Fresnel])
				return false;

			blend_state(element.m_material->m_base.m_blend_mode, element.m_bgfx_state);
			return true;
		};

		gfx.m_renderer.pass(render, pass, queue_draw_element);
	}

	void pass_background(GfxSystem& gfx, Render& render)
	{
		static BlockSky& block_sky = *gfx.m_renderer.block<BlockSky>();

		//Pass pass = render.next_pass("background", PassType::Background);
		block_sky.submit_pass(render);
	}

	void pass_flip(GfxSystem& gfx, Render& render)
	{
		Pass pass = render.next_pass("flip", PassType::Flip);
		gfx.m_copy->quad(pass, render.m_target->m_backbuffer, render.m_target->m_diffuse);
	}
}