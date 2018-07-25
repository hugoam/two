//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <gfx/Filter.h>
#include <gfx/RenderTarget.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Filters/Blur.h>
#endif

namespace mud
{
	BlockBlur::BlockBlur(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_program("filter/gaussian_blur")
	{
		static cstring options[2] = { "GAUSSIAN_HORIZONTAL", "GAUSSIAN_VERTICAL" };
		m_shader_block->m_options = { options, 2 };
		m_program.register_block(*this);
	}

	void BlockBlur::init_gfx_block()
	{
		u_uniform.createUniforms();
	}

	void BlockBlur::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockBlur::submit_gfx_block(Render& render)
	{
		UNUSED(render);
	}

	void BlockBlur::blur(Render& render)
	{
		static BlurKernel kernel = {
			{ 0.214607f, 0.189879f, 0.157305f, 0.071303f, 0.189879f, 0.157305f, 0.071303f },
			{ 0.38774f, 0.24477f, 0.06136f, 0.24477f, 0.06136f }
		};

		uvec4 rect = render.m_viewport.m_rect;

		for(uint8_t i = 0; i < 4; ++i)//render.m_target->m_effects.m_num_mips; i++)
		{
			gaussian_pass(render, rect, i, true, kernel);
			gaussian_pass(render, rect, i, false, kernel);
		}
	}

	void BlockBlur::gaussian_pass(Render& render, uvec4& rect, uint8_t lod, bool horizontal, const BlurKernel& kernel)
	{
		bgfx::TextureHandle source = render.m_target->m_ping_pong.last();
		bgfx::FrameBufferHandle target = render.m_target->m_ping_pong.swap();

		// @todo: optimize this, I can't think of another way right now than to have a clear pass for EVERY blur level :/
		uint8_t clear = render.composite_pass();
		bgfx::setViewRect(clear, 0, 0, uint16_t(render.m_target->m_size.x), uint16_t(render.m_target->m_size.y));
		bgfx::setViewClear(clear, BGFX_CLEAR_COLOR);
		bgfx::setViewFrameBuffer(clear, target);
		bgfx::touch(clear);

		uvec4 source_rect = rect;
		if(horizontal)
			rect = rect / 2U;

		vec4 screen_params{ rect_size(vec4(rect)), 1.f / rect_size(vec4(rect)) };
		bgfx::setUniform(m_filter.u_uniform.u_screen_size_pixel_size, &screen_params);

		vec4 blur_params = { float(lod), 0.f, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_blur_params, &blur_params);

		bgfx::setUniform(u_uniform.u_blur_kernel_0_3, horizontal ? &kernel.m_horizontal[0] : &kernel.m_vertical[0]);
		bgfx::setUniform(u_uniform.u_blur_kernel_4_7, horizontal ? &kernel.m_horizontal[4] : &kernel.m_vertical[4]);

		ShaderVersion version(&m_program);
		version.set_option(m_index, uint8_t(horizontal ? GAUSSIAN_HORIZONTAL : GAUSSIAN_VERTICAL), true);

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, source);

		RenderQuad quad = { render.m_target->source_quad(vec4(source_rect), true), render.m_target->dest_quad(vec4(rect), true), true };
		m_filter.submit_quad(*render.m_target, render.composite_pass(), target, m_program.version(version), quad);
	}
}