//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <gfx/Renderer.h>
#include <gfx/Program.h>
#include <gfx/Filter.h>
#endif

namespace two
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

	export_ TWO_GFX_PBR_EXPORT func_ void pass_dofblur(GfxSystem& gfx, Render& render, const DofBlur& blur);

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockDofBlur : public GfxBlock
	{
	public:
		BlockDofBlur(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		BlockFilter& m_filter;

		Program& m_program;
	};
}
