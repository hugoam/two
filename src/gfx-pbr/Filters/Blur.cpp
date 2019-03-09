//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <math/Vec.hpp>
#include <gfx/Filter.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx/RenderTarget.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Filters/Blur.h>
#endif

namespace mud
{
	BlockBlur::BlockBlur(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_program(gfx.programs().create("filter/gaussian_blur"))
	{
		static cstring options[] = { "GAUSSIAN_HORIZONTAL", "GAUSSIAN_VERTICAL" };
		m_shader_block->m_options = options;
		m_program.register_block(*this);
	}

	void BlockBlur::init_block()
	{
		u_uniform.createUniforms();
	}

	void BlockBlur::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockBlur::blur(Render& render, RenderTarget& target)
	{
		static BlurKernel kernel = {
			{ 0.214607f, 0.189879f, 0.157305f, 0.071303f, 0.189879f, 0.157305f, 0.071303f },
			{ 0.38774f, 0.24477f, 0.06136f, 0.24477f, 0.06136f }
		};

		uvec4 rect = render.m_viewport.m_rect;

		for(uint8_t i = 0; i < 4; ++i)//target.m_effects.m_num_mips; i++)
		{
			gaussian_pass(render, target, rect, i, true, kernel);
			gaussian_pass(render, target, rect, i, false, kernel);
		}
	}

	void BlockBlur::gaussian_pass(Render& render, RenderTarget& target, uvec4& rect, uint8_t lod, bool horizontal, const BlurKernel& kernel)
	{
		bgfx::TextureHandle source = target.m_ping_pong.last();
		bgfx::FrameBufferHandle fbo = target.m_ping_pong.swap();

		uvec4 source_rect = rect;
		if(horizontal) rect = rect / 2U;

		// @todo: optimize this, I can't think of another way right now than to have a clear pass for EVERY blur level :/
		Pass clear_pass = render.composite_pass("blur", fbo, uvec4(uvec2(0U), render.m_target->m_size));
		bgfx::setViewRect(clear_pass.m_index, 0, 0, uint16_t(render.m_target->m_size.x), uint16_t(render.m_target->m_size.y));
		bgfx::setViewClear(clear_pass.m_index, BGFX_CLEAR_COLOR);
		bgfx::setViewFrameBuffer(clear_pass.m_index, fbo);
		bgfx::touch(clear_pass.m_index);

		Pass blur_pass = render.composite_pass("blur", fbo, rect);
		vec4 blur_params = { float(lod), 0.f, 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_blur_params, &blur_params);

		bgfx::setUniform(u_uniform.u_blur_kernel_0_3, horizontal ? &kernel.m_horizontal[0] : &kernel.m_vertical[0]);
		bgfx::setUniform(u_uniform.u_blur_kernel_4_7, horizontal ? &kernel.m_horizontal[4] : &kernel.m_vertical[4]);

		ShaderVersion version = { &m_program };
		version.set_option(m_index, uint8_t(horizontal ? GAUSSIAN_HORIZONTAL : GAUSSIAN_VERTICAL), true);

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, source);

		RenderQuad quad = { target.source_quad(vec4(source_rect), true), target.dest_quad(vec4(rect), true), true };
		m_filter.submit_quad(target, blur_pass.m_index, fbo, m_program.version(version), quad);
	}
}