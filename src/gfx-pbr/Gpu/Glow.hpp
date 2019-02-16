//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/Filters/Glow.h>

namespace mud
{
	template <>
	struct GpuState<Glow>
	{
		void init()
		{
			u_glow_params_0 = bgfx::createUniform("u_glow_params_0", bgfx::UniformType::Vec4);
			u_glow_params_1 = bgfx::createUniform("u_glow_params_1", bgfx::UniformType::Vec4);
			u_glow_levels_1_4 = bgfx::createUniform("u_glow_levels_1_4", bgfx::UniformType::Vec4);
			u_glow_levels_5_8 = bgfx::createUniform("u_glow_levels_5_8", bgfx::UniformType::Vec4);
		}

		void upload(const Glow& glow)
		{
			vec4 glow_params_0 = { 0.f, glow.m_bloom, glow.m_bleed_threshold, glow.m_bleed_scale };
			bgfx::setUniform(u_glow_params_0, &glow_params_0);

			vec4 glow_params_1 = { glow.m_intensity, 0.f, 0.f, 0.f }; // float(render.m_target->m_size.x), float(render.m_target->m_size.y)
			bgfx::setUniform(u_glow_params_1, &glow_params_1);
			bgfx::setUniform(u_glow_levels_1_4, &glow.m_levels_1_4);
			bgfx::setUniform(u_glow_levels_5_8, &glow.m_levels_5_8);
		}

		bgfx::UniformHandle u_glow_params_0;
		bgfx::UniformHandle u_glow_params_1;
		bgfx::UniformHandle u_glow_levels_1_4;
		bgfx::UniformHandle u_glow_levels_5_8;

		static GpuState me;
	};
}
