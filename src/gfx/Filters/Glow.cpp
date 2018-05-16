
#include <gfx/Generated/Types.h>
#include <gfx/Filters/Glow.h>

#include <gfx/RenderTarget.h>
#include <gfx/Filter.h>
#include <gfx/Filters/Blur.h>
#include <gfx/Filters/Tonemap.h>

#define MAX_GLOW_LEVELS 7

namespace mud
{
	BlockGlow::BlockGlow(GfxSystem& gfx_system, BlockFilter& filter, BlockBlur& blur)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_blur(blur)
		, m_bleed_program(gfx_system, "filter/glow_bleed", {})
		, m_merge_program(gfx_system, "filter/glow", {})
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

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_ping_pong.swap(), m_bleed_program.default_version(), { vec4(render.m_viewport.m_rect), true });
	}

	void BlockGlow::glow_blur(Render& render, Glow& glow)
	{
		UNUSED(glow);
		uvec4 rect = render.m_viewport.m_rect;

		static BlurKernel kernel = {
			{ 0.174938f, 0.165569f, 0.140367f, 0.106595f, 0.165569f, 0.140367f, 0.106595f },
			{ 0.288713f, 0.233062f, 0.122581f, 0.233062f, 0.122581f }
		};

		size_t max_level = min<size_t>(MAX_GLOW_LEVELS, render.m_target->m_cascade.m_num_mips - 1 - 1);

		for(uint8_t i = 0; i < (max_level + 1); i++)
		{
			m_blur.gaussian_pass(render, rect, i, true, kernel);
			m_blur.gaussian_pass(render, rect, i, false, kernel);
			
			bgfx::blit(render.composite_pass(),
					   render.m_target->m_cascade.m_texture, i + 1, 0, 0, 0,
					   render.m_target->m_ping_pong.last(), 0, 0, 0, 0, uint16_t(rect_w(rect)) , uint16_t(rect_h(rect)), 1);
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

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_post_process.swap(), m_merge_program.version(shader_version), { vec4(render.m_viewport.m_rect), true });
	}
}
