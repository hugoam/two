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
#include <gfx/Filter.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Handles.h>
#include <gfx-pbr/Filters/Tonemap.h>
#include <gfx-pbr/Gpu/Tonemap.hpp>
#endif

namespace mud
{
	GpuState<BCS> GpuState<BCS>::me;
	GpuState<Tonemap> GpuState<Tonemap>::me;

	BlockTonemap::BlockTonemap(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_copy(copy)
		, m_program(gfx.programs().create("filter/tonemap"))
	{
		static cstring options[] = { "ADJUST_BCS", "COLOR_CORRECTION" };
		static cstring modes[] = { "TONEMAP_MODE" };
		m_shader_block->m_options = options;
		m_shader_block->m_modes = modes;

		m_program.register_block(*this);
	}

	void BlockTonemap::init_block()
	{
		GpuState<BCS>::me.init();
		GpuState<Tonemap>::me.init();
	}

	void BlockTonemap::begin_render(Render& render)
	{
		UNUSED(render);
	}

	void BlockTonemap::begin_pass(Render& render)
	{
		UNUSED(render);
	}
	
	void BlockTonemap::submit_pass(Render& render)
	{
		if(render.m_filters.comp<Tonemap>().m_enabled)
			this->render(render, render.m_filters.comp<Tonemap>(), render.m_filters.comp<BCS>());
		else
			m_copy.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_post_process.last(), render.m_viewport.m_rect);
	}

	void BlockTonemap::render(Render& render, Tonemap& tonemap, BCS& bcs)
	{
		ShaderVersion shader_version = { &m_program };

		shader_version.set_mode(m_index, TONEMAP_MODE, uint8_t(tonemap.m_mode));

		bgfx::setTexture(uint8_t(TextureSampler::Source0), m_filter.u_uniform.s_source_0, render.m_target->m_post_process.last());

		if(bgfx::isValid(tonemap.m_color_correction))
		{
			shader_version.set_option(m_index, COLOR_CORRECTION, true);
			bgfx::setTexture(uint8_t(TextureSampler::Source1), m_filter.u_uniform.s_source_1, tonemap.m_color_correction);
		}

		GpuState<Tonemap>::me.upload(tonemap);

		if(bcs.m_enabled)
		{
			shader_version.set_option(m_index, ADJUST_BCS, true);

			GpuState<BCS>::me.upload(bcs);
		}

		m_filter.submit_quad(*render.m_target, render.composite_pass(), render.m_target->m_fbo, m_program.version(shader_version), render.m_viewport.m_rect);
	}
}
