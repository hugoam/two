//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <ecs/Entity.h>
#include <gfx/Renderer.h>
#endif
#include <gfx-pbr/Forward.h>
#include <gfx-pbr/Filters/Glow.h>
#include <gfx-pbr/Filters/DofBlur.h>

namespace two
{
	export_ enum class refl_ TonemapMode : unsigned int
	{
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

		Texture* m_color_lut = nullptr;
	};

	export_ TWO_GFX_PBR_EXPORT func_ void pass_tonemap(GfxSystem& gfx, Render& render, Tonemap& tonemap, BCS& bcs);

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockTonemap : public GfxBlock
	{
	public:
		BlockTonemap(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy);

		virtual void init_block() override;

		Program& m_program;
	};


}
