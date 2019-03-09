//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx.pbr;
#else
#include <ecs/ECS.hpp>
#include <gfx/RenderTarget.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Handles.h>
#include <gfx-pbr/Filters/DofBlur.h>
#include <gfx-pbr/Filters/Tonemap.h>
#include <gfx-pbr/Gpu/DofBlur.hpp>
#endif

namespace mud
{
	GpuState<DofBlur> GpuState<DofBlur>::me;

	BlockDofBlur::BlockDofBlur(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_program(gfx.programs().create("filter/dof_blur"))
	{
		static cstring options[] = { "DOF_FIRST_PASS" };
		m_shader_block->m_options = options;
		m_program.register_block(*this);
	}

	void BlockDofBlur::init_block()
	{
		GpuState<DofBlur>::me.init();
	}

	void BlockDofBlur::begin_render(Render& render)
	{
		UNUSED(render);
	}
	
	void BlockDofBlur::submit_pass(Render& render)
	{
		if(render.m_filters.comp<DofBlur>().m_enabled)
			this->render(render, render.m_filters.comp<DofBlur>());
	}

	void BlockDofBlur::render(Render& render, const DofBlur& blur)
	{
		submit_blur_pass(render, *render.m_target, blur, true);
		submit_blur_pass(render, *render.m_target, blur, false);//, BGFX_STATE_BLEND_ALPHA);
	}

	void BlockDofBlur::submit_blur_pass(Render& render, RenderTarget& target, const DofBlur& blur, bool first_pass, uint64_t bgfx_state)
	{
		ShaderVersion shader_version = { &m_program };
		shader_version.set_option(m_index, DOF_FIRST_PASS, first_pass);

		GpuState<DofBlur>::me.upload(blur);

		if(first_pass)
		{
			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, target.m_diffuse, GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
		}
		else
		{
			bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, target.m_ping_pong.last(), GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
			bgfx::setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, target.m_diffuse, GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
		}

		bgfx::setTexture(uint8_t(TextureSampler::SourceDepth), m_filter.u_uniform.s_source_depth, target.m_depth);

		bgfx::FrameBufferHandle fbo = first_pass ? target.m_ping_pong.swap() : target.m_post_process.swap();

		m_filter.submit_quad(target, render.composite_pass(),
							 fbo, m_program.version(shader_version), render.m_viewport.m_rect, bgfx_state);
	}
}
