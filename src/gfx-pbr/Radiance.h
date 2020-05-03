//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <stl/map.h>
#include <gfx/Renderer.h>
#include <gfx/Filter.h>
#endif
#include <gfx-pbr/Forward.h>

namespace two
{
	enum ShaderOptionRadiance : unsigned int
	{
		RADIANCE_CUBE,
	};

	export_ class refl_ TWO_GFX_PBR_EXPORT BlockRadiance : public DrawBlock
	{
	public:
		BlockRadiance(GfxSystem& gfx, BlockFilter& filter, BlockCopy& copy);

		virtual void init_block() override;
		virtual void begin_frame(const RenderFrame& frame) override;

		virtual void begin_render(Render& render) override;

		virtual void options(Render& render, const DrawElement& element, ProgramVersion& program) const override;
		virtual void submit(Render& render, const Pass& pass) const override;
		virtual void submit(Render& render, const DrawElement& element, const Pass& pass) const override;

		void prefilter_radiance(Radiance& radiance);

		struct RadianceUniform
		{
			void createUniforms()
			{
				u_radiance_opts = bgfx::createUniform("u_radiance_opts", bgfx::UniformType::Vec4,    1U, bgfx::UniformSet::View);
				s_radiance      = bgfx::createUniform("s_radiance",      bgfx::UniformType::Sampler, 1U, bgfx::UniformSet::View);
			}

			bgfx::UniformHandle u_radiance_opts;
			bgfx::UniformHandle s_radiance;

		} u_radiance;

		struct PrefilterUniform
		{
			void createUniforms()
			{
				u_prefilter_envmap_p0 = bgfx::createUniform("u_prefilter_envmap_p0", bgfx::UniformType::Vec4);
				u_prefilter_cube = bgfx::createUniform("u_prefilter_cube", bgfx::UniformType::Mat4);
			}

			bgfx::UniformHandle u_prefilter_envmap_p0;
			bgfx::UniformHandle u_prefilter_cube;

		} u_prefilter;

		BlockFilter& m_filter;
		BlockCopy& m_copy;

		Program& m_prefilter_program;

		vector<Radiance*> m_prefilter_queue;
		map<Texture*, Texture*> m_prefiltered;
	};
}
