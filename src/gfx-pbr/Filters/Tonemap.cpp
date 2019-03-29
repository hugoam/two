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

	void BlockTonemap::submit_pass(Render& render)
	{
		RenderTarget& target = *render.m_target;
		if(render.m_filters.comp<Tonemap>().m_enabled)
			this->render(render, target, render.m_filters.comp<Tonemap>(), render.m_filters.comp<BCS>());
		else
			m_copy.quad(render.composite_pass("tonemap blit"), *render.m_target_fbo, target.m_post_process.last(), render.m_rect);
	}

	void BlockTonemap::render(Render& render, RenderTarget& target, Tonemap& tonemap, BCS& bcs)
	{
		ProgramVersion program = { &m_program };

		program.set_mode(m_index, TONEMAP_MODE, uint8_t(tonemap.m_mode));

		m_filter.source0(target.m_post_process.last());

		if(tonemap.m_color_correction)
		{
			program.set_option(m_index, COLOR_CORRECTION, true);
			m_filter.source1(*tonemap.m_color_correction);
		}

		GpuState<Tonemap>::me.upload(tonemap);

		if(bcs.m_enabled)
		{
			program.set_option(m_index, ADJUST_BCS, true);

			GpuState<BCS>::me.upload(bcs);
		}

		const Pass pass = render.composite_pass("tonemap");
		m_filter.quad(pass, target, program, render.m_rect);
	}
}
