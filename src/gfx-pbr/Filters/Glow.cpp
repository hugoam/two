//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <gfx/RenderTarget.h>
#include <gfx/Filter.h>
#include <gfx/Pipeline.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Filters/Glow.h>
#include <gfx-pbr/Filters/Blur.h>
#include <gfx-pbr/Filters/Tonemap.h>
#endif

#define MAX_GLOW_LEVELS 7

namespace mud
{
	BlockGlow::BlockGlow(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy, BlockBlur& blur)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_copy(copy)
		, m_blur(blur)
		, m_bleed_program(gfx_system.programs().create("filter/glow_bleed"))
		, m_merge_program(gfx_system.programs().create("filter/glow"))
	{
		static cstring options[1] = { "GLOW_FILTER_BICUBIC" };
		m_shader_block->m_options = { options, 1 };

		m_blur.m_program.register_block(*this);
		m_merge_program.register_block(*this);
	}

	void BlockGlow::init_gfx_block()
	{
		u_uniform.createUniforms();
	}

	void BlockGlow::begin_gfx_block(Render& render)
	{
		UNUSED(render);
		//BlockCopy& copy = *m_gfx_system.m_pipeline->block<BlockCopy>();
		//copy.debug_show_texture(*render.m_target, render.m_target->m_cascade.m_texture, false, false, false, 1);
		//copy.debug_show_texture(*render.m_target, render.m_target->m_ping_pong.last());
	}

	void BlockGlow::submit_gfx_block(Render& render)
	{
		if(render.m_filters && render.m_filters->m_glow.m_enabled)
			this->render(render, render.m_filters->m_glow);
	}

	void BlockGlow::render(Render& render, Glow& glow)
	{
		this->glow_bleed(render, glow);
		this->glow_blur(render, glow);
		this->glow_merge(render, glow);
	}

	void BlockGlow::glow_bleed(Render& render, Glow& glow)
	{
		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_diffuse);
		//bgfx::setUniform(m_blur.u_uniform.u_exposure, &m_tonemap.m_exposure);

		vec4 glow_params = { 0.f, glow.m_bloom, glow.m_bleed_threshold, glow.m_bleed_scale };
		bgfx::setUniform(u_uniform.u_glow_params_0, &glow_params);

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_ping_pong.swap(), m_bleed_program.default_version(), render.m_viewport.m_rect);
	}

	void BlockGlow::glow_blur(Render& render, Glow& glow)
	{
		UNUSED(glow);
		uvec4 rect = render.m_viewport.m_rect;

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
			m_blur.gaussian_pass(render, rect, i, true, kernel);
			m_blur.gaussian_pass(render, rect, i, false, kernel);

			//bool blit_support = (bgfx::getCaps()->supported & BGFX_CAPS_TEXTURE_BLIT) != 0;
			bool blit_support = false;

			RenderQuad quad = { render.m_target->source_quad(vec4(rect), true), render.m_target->dest_quad_mip(vec4(rect), i + 1, true), true };
			
			if(blit_support)
				bgfx::blit(render.composite_pass(),
						   render.m_target->m_cascade.m_texture, i + 1, uint16_t(rect.x), uint16_t(rect.y), 0,
						   render.m_target->m_ping_pong.last(), 0, uint16_t(rect.x), uint16_t(rect.y), 0, uint16_t(rect_w(rect)), uint16_t(rect_h(rect)), 1);
			else
				m_copy.submit_quad(*render.m_target->m_cascade.m_mips[i + 1], render.composite_pass(), render.m_target->m_ping_pong.last(), quad);
		}
	}

	void BlockGlow::glow_merge(Render& render, Glow& glow)
	{
		ShaderVersion shader_version(&m_merge_program);

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_post_process.last());

		shader_version.set_option(m_index, GLOW_FILTER_BICUBIC, glow.m_bicubic_filter);

		bgfx::setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, render.m_target->m_cascade.m_texture);

		vec4 glow_params = { glow.m_intensity, 0.f, float(render.m_target->m_size.x), float(render.m_target->m_size.y) };
		bgfx::setUniform(u_uniform.u_glow_params_1, &glow_params);
		bgfx::setUniform(u_uniform.u_glow_levels_1_4, &glow.m_levels_1_4);
		bgfx::setUniform(u_uniform.u_glow_levels_5_8, &glow.m_levels_5_8);

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_post_process.swap(), m_merge_program.version(shader_version), render.m_viewport.m_rect);
	}
}
