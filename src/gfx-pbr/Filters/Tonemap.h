//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <ecs/Entity.h>
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/Filters/Glow.h>
#include <gfx-pbr/Filters/DofBlur.h>

namespace mud
{
	enum TonemapShaderOption : unsigned int
	{
		ADJUST_BCS,
		COLOR_CORRECTION,
	};

	enum TonemapShaderMode : unsigned int
	{
		TONEMAP_MODE,
	};

	export_ enum class refl_ TonemapMode : unsigned int
	{
		None,
		Linear,
		Reinhardt,
		Filmic,
		ACES,
		Cineon,
		Uncharted2
	};

	export_ struct refl_ BCS
	{
		attr_ gpu_ bool m_enabled = false;
		attr_ gpu_ float m_brightness = 1.0f;
		attr_ gpu_ float m_contrast = 1.0f;
		attr_ gpu_ float m_saturation = 1.0f;
	};

	export_ struct refl_ Tonemap
	{
		attr_ TonemapMode m_mode = TonemapMode::Linear;
		attr_ bool m_enabled = false;
		attr_ gpu_ float m_exposure = 1.0f;
		attr_ gpu_ float m_white_point = 1.0f;

		bgfx::TextureHandle m_color_correction = BGFX_INVALID_HANDLE;
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockTonemap : public GfxBlock
	{
	public:
		BlockTonemap(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;
		virtual void submit_pass(Render& render) final;

		void render(Render& render, Tonemap& tonemap, BCS& bcs);

		BlockFilter& m_filter;
		BlockCopy& m_copy;

		Program& m_program;
	};
}
