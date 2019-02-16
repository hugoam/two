//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/Filters/DofBlur.h>

namespace mud
{
	template <>
	struct GpuState<DofBlur>
	{
		void init()
		{
			u_dof_near_params = bgfx::createUniform("u_dof_near_params", bgfx::UniformType::Vec4);
			u_dof_far_params = bgfx::createUniform("u_dof_far_params", bgfx::UniformType::Vec4);
			u_dof_params = bgfx::createUniform("u_dof_params", bgfx::UniformType::Vec4);
		}

		void upload(const DofBlur& dof)
		{
			vec4 dof_near_params =
			{
				dof.m_near.m_distance,
				dof.m_near.m_distance - dof.m_near.m_transition,
				dof.m_near.m_radius,
				1.f / dof.m_near.m_radius,
			};

			vec4 dof_far_params =
			{
				dof.m_far.m_distance,
				dof.m_far.m_distance + dof.m_far.m_transition,
				dof.m_far.m_radius,
				0.f
			};

			vec4 dof_params = { dof.m_max_coc_radius, 0.f, 0.f, 0.f };

			bgfx::setUniform(u_dof_near_params, &dof_near_params);
			bgfx::setUniform(u_dof_far_params, &dof_far_params);
			bgfx::setUniform(u_dof_params, &dof_params);
		}

		bgfx::UniformHandle u_dof_near_params;
		bgfx::UniformHandle u_dof_far_params;
		bgfx::UniformHandle u_dof_params;

		static GpuState me;
	};
}
