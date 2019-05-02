//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/Filters/DofBlur.h>

namespace two
{
	template <>
	struct GpuState<DofBlur>
	{
		void init()
		{
			u_dof_near_p0 = bgfx::createUniform("u_dof_near_p0", bgfx::UniformType::Vec4);
			u_dof_far_p0 = bgfx::createUniform("u_dof_far_p0", bgfx::UniformType::Vec4);
			u_dof_p0 = bgfx::createUniform("u_dof_p0", bgfx::UniformType::Vec4);
		}

		void upload(const DofBlur& dof)
		{
			vec4 dof_near_p0 =
			{
				dof.m_near.m_distance,
				dof.m_near.m_distance - dof.m_near.m_transition,
				dof.m_near.m_radius,
				1.f / dof.m_near.m_radius,
			};

			vec4 dof_far_p0 =
			{
				dof.m_far.m_distance,
				dof.m_far.m_distance + dof.m_far.m_transition,
				dof.m_far.m_radius,
				0.f
			};

			vec4 dof_p0 = { dof.m_max_coc_radius, 0.f, 0.f, 0.f };

			bgfx::setUniform(u_dof_near_p0, &dof_near_p0);
			bgfx::setUniform(u_dof_far_p0, &dof_far_p0);
			bgfx::setUniform(u_dof_p0, &dof_p0);
		}

		bgfx::UniformHandle u_dof_near_p0;
		bgfx::UniformHandle u_dof_far_p0;
		bgfx::UniformHandle u_dof_p0;

		static GpuState me;
	};
}
