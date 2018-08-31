//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <gfx/RenderTarget.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Filters/DofBlur.h>
#include <gfx-pbr/Filters/Tonemap.h>
#endif

namespace mud
{
	BlockDofBlur::BlockDofBlur(GfxSystem& gfx_system, BlockFilter& filter)
		: GfxBlock(gfx_system, *this)
		, m_filter(filter)
		, m_program("filter/dof_blur")
	{
		static cstring options[1] = { "DOF_FIRST_PASS" };
		m_shader_block->m_options = { options, 1 };
		m_program.register_block(*this);
	}

	void BlockDofBlur::init_gfx_block()
	{
		u_uniform.createUniforms();
	}

	void BlockDofBlur::begin_gfx_block(Render& render)
	{
		UNUSED(render);
	}
	
	void BlockDofBlur::submit_gfx_block(Render& render)
	{
		if(render.m_filters && render.m_filters->m_dof_blur.m_enabled)
			this->render(render, render.m_filters->m_dof_blur);
	}

	void BlockDofBlur::render(Render& render, const DofBlur& blur)
	{
		submit_blur_pass(render, blur, true);
		submit_blur_pass(render, blur, false);//, BGFX_STATE_BLEND_ALPHA);
	}

	void BlockDofBlur::submit_blur_pass(Render& render, const DofBlur& blur, bool first_pass, uint64_t bgfx_state)
	{
		ShaderVersion shader_version = { &m_program };
		shader_version.set_option(m_index, DOF_FIRST_PASS, first_pass);

		vec4 dof_near_params =
		{
			blur.m_near_distance,
			blur.m_near_distance - blur.m_near_transition,
			blur.m_near_radius,
			1.f / blur.m_near_radius,
		};

		vec4 dof_far_params =
		{
			blur.m_far_distance,
			blur.m_far_distance + blur.m_far_transition,
			blur.m_far_radius,
			0.f
		};

		vec4 dof_params = { blur.m_max_coc_radius, 0.f, 0.f, 0.f };

		bgfx::setUniform(u_uniform.u_dof_near_params, &dof_near_params);
		bgfx::setUniform(u_uniform.u_dof_far_params, &dof_far_params);
		bgfx::setUniform(u_uniform.u_dof_params, &dof_params);

		if(first_pass)
		{
			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_diffuse, GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
		}
		else
		{
			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_ping_pong.last(), GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
			bgfx::setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, render.m_target->m_diffuse, GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
		}

		bgfx::setTexture(uint8_t(TextureSampler::SourceDepth), m_filter.u_uniform.s_source_depth, render.m_target->m_depth);

		bgfx::FrameBufferHandle target = first_pass ? render.m_target->m_ping_pong.swap() : render.m_target->m_post_process.swap();

		m_filter.submit_quad(*render.m_target, render.composite_pass(),
							 target, m_program.version(shader_version), render.m_viewport.m_rect, bgfx_state);
	}
}
