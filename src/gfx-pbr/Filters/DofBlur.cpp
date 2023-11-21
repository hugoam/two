//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

module two.gfx.pbr;

namespace two
{
	GpuState<DofBlur> GpuState<DofBlur>::me;

	BlockDofBlur::BlockDofBlur(GfxSystem& gfx, BlockFilter& filter)
		: GfxBlock(gfx, *this)
		, m_filter(filter)
		, m_program(gfx.programs().create("filter/dof_blur"))
	{
		m_options = { "DOF_FIRST_PASS" };
		m_program.register_block(*this);
	}

	void BlockDofBlur::init_block()
	{
		GpuState<DofBlur>::me.init();
	}

	void pass_dofblur(GfxSystem& gfx, Render& render, const DofBlur& blur)
	{
		static BlockDofBlur& block = *gfx.m_renderer.block<BlockDofBlur>();

		auto blur_pass = [](GfxSystem& gfx, Render& render, RenderTarget& target, const DofBlur& blur, bool first_pass, uint64_t bgfx_state = 0)
		{
			ProgramVersion program = { block.m_program };
			program.set_option(block.m_index, DOF_FIRST_PASS, first_pass);

			GpuState<DofBlur>::me.upload(blur);

			if(first_pass)
			{
				gfx.m_filter->source0(target.m_diffuse, TEXTURE_CLAMP | TEXTURE_POINT);
			}
			else
			{
				gfx.m_filter->source0(target.m_ping_pong.last(), TEXTURE_CLAMP | TEXTURE_POINT);
				gfx.m_filter->source1(target.m_diffuse, TEXTURE_CLAMP | TEXTURE_POINT);
			}

			gfx.m_filter->sourcedepth(target.m_depth);

			FrameBuffer& fbo = first_pass ? target.m_ping_pong.swap() : target.m_post.swap();

			Pass pass = render.composite_pass("dof blur");
			gfx.m_filter->quad(pass, fbo, program, bgfx_state);
		};

		blur_pass(gfx, render, *render.m_target, blur, true);
		blur_pass(gfx, render, *render.m_target, blur, false);//, BGFX_STATE_BLEND_ALPHA);
	}
}
