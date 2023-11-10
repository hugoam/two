//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Filters/Blur.h>

namespace two
{
	export_ template <>
	struct GpuState<GpuBlurKernel>
	{
		void init()
		{
			u_blur_kernel_0_3 = bgfx::createUniform("u_blur_kernel_0_3", bgfx::UniformType::Vec4);
			u_blur_kernel_4_7 = bgfx::createUniform("u_blur_kernel_4_7", bgfx::UniformType::Vec4);
		}

		void upload(const GpuBlurKernel& kernel)
		{
			bgfx::setUniform(u_blur_kernel_0_3, kernel.m_kernel + 0);
			bgfx::setUniform(u_blur_kernel_4_7, kernel.m_kernel + 4);
		}

		bgfx::UniformHandle u_blur_kernel_0_3;
		bgfx::UniformHandle u_blur_kernel_4_7;

		static GpuState me;
	};
}
