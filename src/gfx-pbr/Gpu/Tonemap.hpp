//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/Filters/Tonemap.h>

namespace two
{
	export_ template <>
	struct GpuState<BCS>
	{
		void init()
		{
			u_bcs = bgfx::createUniform("u_tonemap_bcs", bgfx::UniformType::Vec4);
		}

		void upload(const BCS& bcs)
		{
			vec4 bcs_values = { bcs.m_brightness, bcs.m_contrast, bcs.m_saturation, 0.f };
			bgfx::setUniform(u_bcs, &bcs_values);
		}

		bgfx::UniformHandle u_bcs;

		static GpuState me;
	};

	export_ template <>
	struct GpuState<Tonemap>
	{
		void init()
		{
			u_tonemap_modes = bgfx::createUniform("u_tonemap_modes", bgfx::UniformType::Vec4);
			u_tonemap_opts  = bgfx::createUniform("u_tonemap_opts",  bgfx::UniformType::Vec4);
			u_exposure_p0   = bgfx::createUniform("u_exposure_p0",   bgfx::UniformType::Vec4);
		}

		void upload(const Tonemap& tonemap)
		{
			const vec4 exposure_p0 = { tonemap.m_exposure, tonemap.m_white_point, 0.f, 0.f };
			bgfx::setUniform(u_exposure_p0, &exposure_p0);
		}

		void options(const Tonemap& tonemap, bool to_gamma, bool bcs)
		{
			const vec4 modes = vec4(float(tonemap.m_mode), 0.f, 0.f, 0.f);
			const vec4 opts = vec4(bvec4(to_gamma, tonemap.m_color_lut, bcs, false));

			bgfx::setUniform(u_tonemap_modes, &modes);
			bgfx::setUniform(u_tonemap_opts, &opts);
		}

		bgfx::UniformHandle u_tonemap_modes;
		bgfx::UniformHandle u_tonemap_opts;
		bgfx::UniformHandle u_exposure_p0;

		static GpuState me;
	};
}
