//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/map.h>
#include <math/Vec.h>
#endif
#include <gfx/Renderer.h>

namespace two
{
	export_ enum ShaderOptionFilter : unsigned int
	{
		SOURCE_0_CUBE,
		SOURCE_0_ARRAY,
	};

	export_ struct FilterUniform
	{
		void createUniforms()
		{
			s_source_0		= bgfx::createUniform("s_source_0",		bgfx::UniformType::Sampler);
			s_source_1		= bgfx::createUniform("s_source_1",		bgfx::UniformType::Sampler);
			s_source_2		= bgfx::createUniform("s_source_2",		bgfx::UniformType::Sampler);
			s_source_3		= bgfx::createUniform("s_source_3",		bgfx::UniformType::Sampler);
			s_source_depth	= bgfx::createUniform("s_source_depth",	bgfx::UniformType::Sampler);
			
			u_filter_p0		= bgfx::createUniform("u_filter_p0",	bgfx::UniformType::Vec4);

			u_source_opts   = bgfx::createUniform("u_source_opts",   bgfx::UniformType::Vec4);
			u_source_levels = bgfx::createUniform("u_source_levels", bgfx::UniformType::Vec4);
			u_source_crop	= bgfx::createUniform("u_source_crop",	 bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle s_source_0;
		bgfx::UniformHandle s_source_1;
		bgfx::UniformHandle s_source_2;
		bgfx::UniformHandle s_source_3;
		bgfx::UniformHandle s_source_depth;

		bgfx::UniformHandle u_filter_p0;

		bgfx::UniformHandle u_source_opts;
		bgfx::UniformHandle u_source_levels;
		bgfx::UniformHandle u_source_crop;
	};

	export_ class refl_ TWO_GFX_EXPORT BlockFilter : public GfxBlock
	{
	public:
		BlockFilter(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		meth_ void submit(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		meth_ void quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, uint64_t flags = 0U, bool render = false);

		meth_ void multiply(float mul);

		meth_ void source0p(const Texture& texture, ProgramVersion& program, int level = 0, uint32_t flags = UINT32_MAX);

		meth_ void source0(const Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source1(const Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source2(const Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source3(const Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void sourcedepth(const Texture& texture, uint32_t flags = UINT32_MAX);

		void uniform(const Pass& pass, const string& name, const mat4& value);
		meth_ void uniform(const Pass& pass, const string& name, const vec4& value);
		meth_ void uniforms(const Pass& pass, const string& name, span<float> values);
		void uniforms4(const Pass& pass, const string& name, span<vec4> values);

		FilterUniform u_uniform;

		map<string, bgfx::UniformHandle> m_uniforms;

		Program& m_quad_program;

		float m_multiply = 1.f;
	};

	export_ class refl_ TWO_GFX_EXPORT BlockCopy : public GfxBlock
	{
	public:
		BlockCopy(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		meth_ void submit(const Pass& pass, FrameBuffer& fbo, const Texture& texture, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		meth_ void quad(const Pass& pass, FrameBuffer& fbo, const Texture& texture, uint64_t flags = 0U, bool render = false);

		meth_ void debug_show_texture(Render& render, const Texture& texture, const vec4& rect, int level = 0);
		meth_ void debug_show_texturep(Render& render, const Texture* texture, const vec4& rect, int level = 0);

		BlockFilter& m_filter;

		Program& m_program;
	};
}
