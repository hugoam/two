//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <gfx/Renderer.h>
#include <gfx/Filter.h>
#endif
#include <gfx-pbr/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#include <map>
#endif

namespace mud
{
	enum ShaderOptionRadiance : unsigned int
	{
		RADIANCE_ENVMAP,
		RADIANCE_ARRAY,
	};

	export_ class refl_ MUD_GFX_PBR_EXPORT BlockRadiance : public DrawBlock
	{
	public:
		BlockRadiance(GfxSystem& gfx_system, BlockFilter& filter, BlockCopy& copy);

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		virtual void begin_draw_pass(Render& render) override;

		virtual void options(Render& render, ShaderVersion& shader_version) const override;
		virtual void submit(Render& render, const Pass& render_pass) const override;

		void prefilter_radiance(Radiance& radiance);

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

		Program& m_prefilter_program;

		std::vector<Radiance*> m_prefilter_queue;
		std::map<uint16_t, uint16_t> m_prefiltered;
	};
}
