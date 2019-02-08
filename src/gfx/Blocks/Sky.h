//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/map.h>
#include <gfx/Forward.h>
#include <gfx/Renderer.h>
#include <gfx/Filter.h>

namespace mud
{
	export_ enum class refl_ Month : unsigned int
	{
		January = 0,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};

	MUD_GFX_EXPORT quat sun_rotation(float azimuth, float altitude, const vec3& up = Y3, const vec3& north = X3);
	MUD_GFX_EXPORT quat sun_rotation(Month month, float latitude, float hour, float ecliptic_obliquity = 0.408407f, const vec3& up = Y3, const vec3& north = X3);

	export_ class refl_ MUD_GFX_EXPORT BlockSky : public GfxBlock
	{
	public:
		BlockSky(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		BlockFilter& m_filter;

		struct SkyboxUniform
		{
			void createUniforms()
			{
				u_skybox_matrix = bgfx::createUniform("u_skybox_matrix", bgfx::UniformType::Mat4);
				u_skybox_params = bgfx::createUniform("u_skybox_params", bgfx::UniformType::Vec4);
				s_skybox_map = bgfx::createUniform("s_skybox_map", bgfx::UniformType::Int1);
			}

			bgfx::UniformHandle u_skybox_matrix;
			bgfx::UniformHandle u_skybox_params;
			bgfx::UniformHandle s_skybox_map;

		} u_skybox;

		Program& m_skybox_program;
	};
}