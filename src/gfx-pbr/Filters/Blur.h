//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <gfx/Renderer.h>
#include <gfx/Program.h>
#endif

namespace two
{
	struct EffectBlurUniform
	{
		void createUniforms()
		{
			u_blur_p0 = bgfx::createUniform("u_blur_p0", bgfx::UniformType::Vec4);
			u_blur_kernel_0_3 = bgfx::createUniform("u_blur_kernel_0_3", bgfx::UniformType::Vec4);
			u_blur_kernel_4_7 = bgfx::createUniform("u_blur_kernel_4_7", bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle u_blur_p0;
		bgfx::UniformHandle u_blur_kernel_0_3;
		bgfx::UniformHandle u_blur_kernel_4_7;
	};

	struct gpu_ GpuBlurKernel
	{
		attr_ gpu_ float m_kernel[8];
	};

	struct BlurKernel
	{
		float m_horizontal[7];
		float m_vertical[5];
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockBlur : public GfxBlock
	{
	public:
		BlockBlur(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		
		void blur(Render& render, RenderTarget& target);

		void gaussian_pass(Render& render, RenderTarget& target, const vec4& rect, uint8_t lod, bool horizontal, const BlurKernel& kernel);

		BlockFilter& m_filter;

		EffectBlurUniform u_uniform;
		Program& m_program;
	};
}
