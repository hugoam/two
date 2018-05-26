//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Renderer.h>
#include <gfx/Filter.h>
#include <gfx-pbr/Generated/Forward.h>

#include <map>

namespace mud
{
	enum ShaderOptionRadiance : unsigned int
	{
		RADIANCE_ENVMAP,
		RADIANCE_ARRAY,
	};

	class _refl_ MUD_GFX_EXPORT BlockRadiance : public DrawBlock
	{
	public:
		BlockRadiance(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy);

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		virtual void begin_gfx_pass(Render& render) final;
		virtual void submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element) final;;

		void prefilter_radiance(Render& render, Radiance& radiance);

		struct RadianceUniform
		{
			void createUniforms()
			{
				s_radiance_map = bgfx::createUniform("s_radiance_map", bgfx::UniformType::Int1);
			}

			bgfx::UniformHandle s_radiance_map;

		} u_radiance;

		struct PrefilterUniform
		{
			void createUniforms()
			{
				u_prefilter_envmap_params = bgfx::createUniform("u_prefilter_envmap_params", bgfx::UniformType::Vec4);
			}

			bgfx::UniformHandle u_prefilter_envmap_params;

		} u_prefilter;

		BlockFilter& m_filter;
		BlockCopy& m_copy;

		Program m_prefilter_program;

		std::map<uint16_t, uint16_t> m_prefiltered;
	};
}
