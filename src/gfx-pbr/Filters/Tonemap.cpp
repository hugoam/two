//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef TWO_MODULES
module two.gfx.pbr;
#else
#include <gfx/RenderTarget.h>
#include <gfx/Filter.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-pbr/Types.h>
#include <gfx-pbr/Filters/Tonemap.h>
#include <gfx-pbr/Gpu/Tonemap.hpp>
#endif

namespace two
{
	GpuState<BCS> GpuState<BCS>::me;
	GpuState<Tonemap> GpuState<Tonemap>::me;

	BlockTonemap::BlockTonemap(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy)
		: GfxBlock(gfx, *this)
		, m_program(gfx.programs().create("filter/tonemap"))
	{}

	void BlockTonemap::init_block()
	{
		GpuState<BCS>::me.init();
		GpuState<Tonemap>::me.init();
	}

	void pass_tonemap(GfxSystem& gfx, Render& render, Tonemap& tonemap, BCS& bcs)
	{
		static BlockTonemap& block = *gfx.m_renderer.block<BlockTonemap>();

		ProgramVersion program = { block.m_program };

		gfx.m_filter->source0(render.m_target->m_post.last());

		if(tonemap.m_color_lut)
			gfx.m_filter->source1(*tonemap.m_color_lut);

		GpuState<Tonemap>::me.upload(tonemap);
		GpuState<Tonemap>::me.options(tonemap, render.m_viewport->m_to_gamma, bcs.m_enabled);

		if(bcs.m_enabled)
			GpuState<BCS>::me.upload(bcs);

		const Pass pass = render.composite_pass("tonemap");
		gfx.m_filter->quad(pass, *render.m_fbo, program);
	}
}
