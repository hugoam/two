//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Renderer.h>
#include <gfx-pbr/Generated/Forward.h>
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

	export_ enum class _refl_ TonemapMode : unsigned int
	{
		Linear,
		Reinhardt,
		Filmic,
		ACES
	};

	export_ struct _refl_ MUD_GFX_EXPORT BCS
	{
		_attr_ _mut_ bool m_enabled = false;
		_attr_ _mut_ float m_brightness = 1.0f;
		_attr_ _mut_ float m_contrast = 1.0f;
		_attr_ _mut_ float m_saturation = 1.0f;
	};

	export_ struct _refl_ MUD_GFX_EXPORT Tonemap
	{
		_attr_ _mut_ TonemapMode m_mode = TonemapMode::Linear;
		_attr_ _mut_ bool m_enabled = false;
		_attr_ _mut_ float m_exposure = 1.0f;
		_attr_ _mut_ float m_white_point = 1.0f;

		bgfx::TextureHandle m_color_correction = BGFX_INVALID_HANDLE;
	};

	export_ struct _refl_ MUD_GFX_EXPORT RenderFilters
	{
		_attr_ _mut_ DofBlur m_dof_blur;
		//_attr_ _mut_ Exposure m_exposure;
		_attr_ _mut_ Glow m_glow;
		_attr_ _mut_ BCS m_bcs;
		_attr_ _mut_ Tonemap m_tonemap;
	};

	struct TonemapUniform
	{
		void createUniforms()
		{
			u_bcs = bgfx::createUniform("u_tonemap_bcs", bgfx::UniformType::Vec4);
			u_exposure_params = bgfx::createUniform("u_exposure_params", bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle u_bcs;
		bgfx::UniformHandle u_exposure_params;
	};

	export_ class _refl_ MUD_GFX_EXPORT BlockTonemap : public GfxBlock
	{
	public:
		BlockTonemap(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		void render(Render& render, Tonemap& tonemap, BCS& bcs);

		BlockFilter& m_filter;

		TonemapUniform u_uniform;
		Program m_program;
	};
}
