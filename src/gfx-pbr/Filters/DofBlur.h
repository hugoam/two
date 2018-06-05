//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#include <gfx/Program.h>
#include <gfx/Filter.h>
#endif

namespace mud
{
	enum ShaderOptionDofBlur : unsigned int
	{
		DOF_FIRST_PASS,
	};

	export_ struct _refl_ MUD_GFX_EXPORT DofBlur
	{
		_attr_ _mut_ bool m_enabled = false;
		_attr_ _mut_ float m_far_distance = 10.f;
		_attr_ _mut_ float m_far_transition = 5.f;
		_attr_ _mut_ float m_far_radius = 5.f;
		_attr_ _mut_ float m_near_distance = 2.f;
		_attr_ _mut_ float m_near_transition = 1.f;
		_attr_ _mut_ float m_near_radius = 5.f;
		_attr_ _mut_ float m_max_coc_radius = 8.f;
	};

	struct DofBlurUniform
	{
		void createUniforms()
		{
			u_dof_near_params = bgfx::createUniform("u_dof_near_params", bgfx::UniformType::Vec4);
			u_dof_far_params = bgfx::createUniform("u_dof_far_params", bgfx::UniformType::Vec4);
			u_dof_params = bgfx::createUniform("u_dof_params", bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle u_dof_near_params;
		bgfx::UniformHandle u_dof_far_params;
		bgfx::UniformHandle u_dof_params;
	};

	export_ class _refl_ MUD_GFX_EXPORT BlockDofBlur : public GfxBlock
	{
	public:
		BlockDofBlur(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		void render(Render& render, const DofBlur& blur);

		void submit_blur_pass(Render& render, const DofBlur& blur, bool first, uint64_t bgfx_state = 0);

		BlockFilter& m_filter;

		DofBlurUniform u_uniform;

		Program m_program;
	};
}
