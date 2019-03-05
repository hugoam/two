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

	export_ struct refl_ DofParams
	{
		attr_ gpu_ float m_distance;
		attr_ gpu_ float m_transition;
		attr_ gpu_ float m_radius;
	};

	export_ struct refl_ DofBlur
	{
		attr_ bool m_enabled = false;
		attr_ gpu_ DofParams m_far = { 10.f, 5.f, 5.f };
		attr_ gpu_ DofParams m_near = { 2.f, 1.f, 5.f };
		attr_ gpu_ float m_max_coc_radius = 8.f;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockDofBlur : public GfxBlock
	{
	public:
		BlockDofBlur(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;
		virtual void submit_pass(Render& render) final;

		void render(Render& render, const DofBlur& blur);

		void submit_blur_pass(Render& render, const DofBlur& blur, bool first, uint64_t bgfx_state = 0);

		BlockFilter& m_filter;

		Program& m_program;
	};
}
