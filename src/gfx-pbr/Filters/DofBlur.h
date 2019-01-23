//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
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

	export_ struct refl_ MUD_GFX_PBR_EXPORT DofBlur
	{
		attr_ bool m_enabled = false;
		attr_ float m_far_distance = 10.f;
		attr_ float m_far_transition = 5.f;
		attr_ float m_far_radius = 5.f;
		attr_ float m_near_distance = 2.f;
		attr_ float m_near_transition = 1.f;
		attr_ float m_near_radius = 5.f;
		attr_ float m_max_coc_radius = 8.f;
	};

	struct DofBlurFar : public DofBlur {};
	struct DofBlurNear : public DofBlur {};

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

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockDofBlur : public GfxBlock
	{
	public:
		BlockDofBlur(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;
		virtual void submit_pass(Render& render) final;

		void render(Render& render, const DofBlur& blur);

		void submit_blur_pass(Render& render, const DofBlur& blur, bool first, uint64_t bgfx_state = 0);

		BlockFilter& m_filter;

		DofBlurUniform u_uniform;

		Program& m_program;
	};
}
