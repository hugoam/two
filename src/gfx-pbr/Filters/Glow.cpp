//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <math/Vec.hpp>
#include <gfx/RenderTarget.h>
#include <gfx/Filter.h>
#include <gfx/Pipeline.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Filters/Glow.h>
#include <gfx-pbr/Filters/Blur.h>
#include <gfx-pbr/Filters/Tonemap.h>
#include <gfx-pbr/Gpu/Glow.hpp>
#endif

#define MAX_GLOW_LEVELS 7

namespace two
{
	GpuState<Glow> GpuState<Glow>::me;

	BlockGlow::BlockGlow(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy, BlockBlur& blur)
		: GfxBlock(gfx, *this)
		, m_bleed_program(gfx.programs().create("filter/glow_bleed"))
		, m_merge_program(gfx.programs().create("filter/glow"))
	{
		UNUSED(filter); UNUSED(copy);
		m_options = { "GLOW_FILTER_BICUBIC" };

		blur.m_program.register_block(*this);
		m_merge_program.register_block(*this);
	}

	void BlockGlow::init_block()
	{
		GpuState<Glow>::me.init();
	}


	void debug_glow(GfxSystem& gfx, Render& render, RenderTarget& target)
	{
		gfx.m_copy->debug_show_texture(render, target.m_cascade.m_texture, vec4(0.f), 1);
		gfx.m_copy->debug_show_texture(render, target.m_ping_pong.last(), vec4(0.f));
	}

	void glow_bleed(GfxSystem& gfx, Render& render, BlockGlow& block, Glow& glow)
	{
		gfx.m_filter->source0(render.m_target->m_diffuse);
		//bgfx::setUniform(m_blur.u_uniform.u_exposure, &m_tonemap.m_exposure);

		GpuState<Glow>::me.upload(glow);

		Pass pass = render.composite_pass("glow bleed");
		gfx.m_filter->quad(pass, render.m_target->m_ping_pong.swap(), block.m_bleed_program);
	}

	void glow_blur(GfxSystem& gfx, Render& render, BlockBlur& blur, Glow& glow)
	{
		UNUSED(glow);

		static BlurKernel kernel = {
			{ 0.174938f, 0.165569f, 0.140367f, 0.106595f, 0.165569f, 0.140367f, 0.106595f },
			{ 0.288713f, 0.233062f, 0.122581f, 0.233062f, 0.122581f }
		};

		size_t max_level = 0;

		for(vec4::length_type i = 0; i < 8; ++i)
			if((i < 4 && glow.m_levels_1_4[i]) || (i >= 4 && glow.m_levels_5_8[i - 4]))
				max_level = i;

		for(uint8_t i = 0; i < (max_level + 1); i++)
		{
			blur.gaussian_pass(render, *render.m_target, render.m_rect, i, true, kernel);
			blur.gaussian_pass(render, *render.m_target, render.m_rect, i, false, kernel);

			//bool blit_support = (bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_BLIT) != 0;
			//bool blit_support = false;

			RenderQuad quad = { render.m_rect, render.m_rect, true };

			Pass pass = render.composite_pass("glow blit");
			//if(blit_support)
			//	bgfx::blit(pass.m_index,
			//			   target.m_cascade.m_texture, i + 1, uint16_t(rect.x), uint16_t(rect.y), 0,
			//			   target.m_ping_pong.last(), 0, uint16_t(rect.x), uint16_t(rect.y), 0, uint16_t(rect.width), uint16_t(rect.height), 1);
			//else
			gfx.m_copy->submit(pass, *render.m_target->m_cascade.m_fbos[i + 1], render.m_target->m_ping_pong.last(), quad);
		}
	}

	void glow_merge(GfxSystem& gfx, Render& render, BlockGlow& block, Glow& glow)
	{
		ProgramVersion program = { block.m_merge_program };

		program.set_option(block.m_index, GLOW_FILTER_BICUBIC, glow.m_bicubic_filter);

		gfx.m_filter->source0(render.m_target->m_post.last());
		gfx.m_filter->source1(render.m_target->m_cascade.m_texture);

		GpuState<Glow>::me.upload(glow);

		Pass pass = render.composite_pass("glow merge");
		gfx.m_filter->quad(pass, render.m_target->m_post.swap(), program);
	}

	void pass_glow(GfxSystem& gfx, Render& render, Glow& glow)
	{
		static BlockGlow& block = *gfx.m_renderer.block<BlockGlow>();
		static BlockBlur& blur = *gfx.m_renderer.block<BlockBlur>();

		glow_bleed(gfx, render, block, glow);
		glow_blur(gfx, render, blur, glow);
		glow_merge(gfx, render, block, glow);
	}
}
