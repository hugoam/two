//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <math/Vec.hpp>
#include <gfx/Filter.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx/RenderTarget.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Filters/Blur.h>
#endif

namespace two
{
	BlockBlur::BlockBlur(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_program(gfx.programs().create("filter/gaussian_blur"))
	{}

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

		for(uint8_t i = 0; i < 4; ++i)//target.m_effects.m_num_mips; i++)
		{
			gaussian_pass(render, target, render.m_rect, i, true, kernel);
			gaussian_pass(render, target, render.m_rect, i, false, kernel);
		}
	}

	void BlockBlur::gaussian_pass(Render& render, RenderTarget& target, const vec4& rect, uint8_t lod, bool horizontal, const BlurKernel& kernel)
	{
		Texture& source = target.m_ping_pong.last();
		FrameBuffer& fbo = target.m_ping_pong.swap();

		Pass blur_pass = render.composite_pass("blur", fbo, rect);
		vec4 blur_p0 = { float(horizontal), float(lod), 0.f, 0.f };
		bgfx::setUniform(u_uniform.u_blur_p0, &blur_p0);

		bgfx::setUniform(u_uniform.u_blur_kernel_0_3, horizontal ? &kernel.m_horizontal[0] : &kernel.m_vertical[0]);
		bgfx::setUniform(u_uniform.u_blur_kernel_4_7, horizontal ? &kernel.m_horizontal[4] : &kernel.m_vertical[4]);

		m_filter.source0(source);

		m_filter.submit(blur_pass, fbo, m_program, RenderQuad(rect, true));
	}
}