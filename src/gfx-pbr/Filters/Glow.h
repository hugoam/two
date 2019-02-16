//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#include <gfx/Program.h>
#include <gfx/Filter.h>
#endif
#include <gfx-pbr/Forward.h>

namespace mud
{
	enum ShaderOptionGlow : unsigned int
	{
		GLOW_FILTER_BICUBIC,
	};

	export_ struct refl_ MUD_GFX_PBR_EXPORT Glow
	{
		attr_ bool m_enabled = false;
		attr_ gpu_ vec4 m_levels_1_4 = { 1.f, 0.f, 0.f, 0.f };
		attr_ gpu_ vec4 m_levels_5_8 = vec4(0.f);
		attr_ gpu_ float m_intensity = 0.4f;
		attr_ gpu_ float m_bloom = 0.0f;
		attr_ gpu_ float m_bleed_threshold = 1.0f;
		attr_ gpu_ float m_bleed_scale = 2.0f;
		attr_ gpu_ bool m_bicubic_filter = false;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockGlow : public GfxBlock
	{
	public:
		BlockGlow(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy, BlockBlur& blur);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;
		virtual void submit_pass(Render& render) final;

		void glow_bleed(Render& render, Glow& glow);
		void glow_blur(Render& render, Glow& glow);
		void glow_merge(Render& render, Glow& glow);

		void render(Render& render, Glow& glow);

		BlockFilter& m_filter;
		BlockCopy& m_copy;
		BlockBlur& m_blur;

		Program& m_bleed_program;
		Program& m_merge_program;
	};
}
