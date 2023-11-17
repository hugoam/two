//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

module two.gfx.pbr;

namespace two
{
	GpuState<BCS> GpuState<BCS>::me;
	GpuState<Tonemap> GpuState<Tonemap>::me;

	BlockTonemap::BlockTonemap(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy)
		: GfxBlock(gfx, *this)
		, m_program(gfx.programs().create("filter/tonemap"))
	{
		UNUSED(filter); UNUSED(copy);
		m_options = { "TO_GAMMA", "ADJUST_BCS", "COLOR_LUT" };
		m_modes = { "TONEMAP_MODE" };

		m_program.register_block(*this);
	}

	void BlockTonemap::init_block()
	{
		GpuState<BCS>::me.init();
		GpuState<Tonemap>::me.init();
	}

	void pass_tonemap(GfxSystem& gfx, Render& render, Tonemap& tonemap, BCS& bcs)
	{
		static BlockTonemap& block = *gfx.m_renderer.block<BlockTonemap>();

		ProgramVersion program = { block.m_program };

		program.set_mode(block.m_index, TONEMAP_MODE, uint8_t(tonemap.m_mode));
		program.set_option(block.m_index, TO_GAMMA, render.m_viewport->m_to_gamma);

		gfx.m_filter->source0(render.m_target->m_post.last());

		if(tonemap.m_color_lut)
		{
			program.set_option(block.m_index, COLOR_LUT, true);
			gfx.m_filter->source1(*tonemap.m_color_lut);
		}

		GpuState<Tonemap>::me.upload(tonemap);

		if(bcs.m_enabled)
		{
			program.set_option(block.m_index, ADJUST_BCS, true);

			GpuState<BCS>::me.upload(bcs);
		}

		const Pass pass = render.composite_pass("tonemap");
		gfx.m_filter->quad(pass, *render.m_fbo, program);
	}
}
