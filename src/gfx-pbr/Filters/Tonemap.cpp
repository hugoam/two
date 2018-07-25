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
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Filters/Tonemap.h>
#endif

namespace mud
{
	BlockTonemap::BlockTonemap(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_copy(copy)
		, m_program("filter/tonemap")
	{
		static cstring options[2] = {
			"ADJUST_BCS",
			"COLOR_CORRECTION",
		};
		static cstring modes[2] = {
			"TONEMAP_MODE",
		};

		m_shader_block->m_options = { options, 1 };
		m_shader_block->m_modes = { modes, 1 };

		m_program.register_block(*this);
	}

	void BlockTonemap::init_gfx_block()
	{
		u_uniform.createUniforms();
	}

	void BlockTonemap::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockTonemap::submit_gfx_block(Render& render)
	{
		if(render.m_filters && render.m_filters->m_tonemap.m_enabled)
			this->render(render, render.m_filters->m_tonemap, render.m_filters->m_bcs);
		else
			m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_post_process.last(), render.m_viewport.m_rect);
	}

	void BlockTonemap::render(Render& render, Tonemap& tonemap, BCS& bcs)
	{
		ShaderVersion shader_version(&m_program);

		m_filter.set_uniforms(render);

		shader_version.set_mode(m_index, TONEMAP_MODE, uint8_t(tonemap.m_mode));

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_post_process.last());

		if(bgfx::isValid(tonemap.m_color_correction))
		{
			shader_version.set_option(m_index, COLOR_CORRECTION, true);
			bgfx::setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, tonemap.m_color_correction);
		}

		vec4 exposure_params = { tonemap.m_exposure, tonemap.m_white_point, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_exposure_params, &exposure_params);

		if(bcs.m_enabled)
		{
			shader_version.set_option(m_index, ADJUST_BCS, true);

			vec4 bcs_values = { bcs.m_brightness, bcs.m_contrast, bcs.m_saturation, 0.f };
			bgfx::setUniform(u_uniform.u_bcs, &bcs_values);
		}

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_fbo, m_program.version(shader_version), render.m_viewport.m_rect);
	}
}
