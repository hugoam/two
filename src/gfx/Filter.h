//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/map.h>
#include <math/Vec.h>
#endif
#include <gfx/Renderer.h>

namespace mud
{
	export_ enum ShaderOptionFilter : unsigned int
	{
		UNPACK_DEPTH,
		SOURCE_DEPTH,
		SOURCE_0_CUBE,
		SOURCE_0_ARRAY,
		DEBUG_UV,
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

			u_source_levels = bgfx::createUniform("u_source_levels", bgfx::UniformType::Vec4);
			u_source_crop	= bgfx::createUniform("u_source_crop",	 bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle s_source_0;
		bgfx::UniformHandle s_source_1;
		bgfx::UniformHandle s_source_2;
		bgfx::UniformHandle s_source_3;
		bgfx::UniformHandle s_source_depth;

		bgfx::UniformHandle u_source_levels;
		bgfx::UniformHandle u_source_crop;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockFilter : public GfxBlock
	{
	public:
		BlockFilter(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		void quad(const Pass& pass, FrameBuffer& fbo, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);

		void quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		void quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, const uvec4& rect, uint64_t flags = 0U, bool render = false);
		void quad(const Pass& pass, FrameBuffer& fbo, const ProgramVersion& program, uint64_t flags = 0U, bool render = false);

		void quad(const Pass& pass, FrameBuffer& fbo, Program& program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		void quad(const Pass& pass, FrameBuffer& fbo, Program& program, uint64_t flags = 0U, bool render = false);
		meth_ void quad(const Pass& pass, FrameBuffer& fbo, Program& program, const uvec4& rect, uint64_t flags = 0U, bool render = false);

		void source0(Texture& texture, ProgramVersion& program, int level = 0, uint32_t flags = UINT32_MAX);

		meth_ void source0(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source1(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source2(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void source3(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void sourcedepth(Texture& texture, uint32_t flags = UINT32_MAX);
		meth_ void uniform(const Pass& pass, const string& name, const vec4& value);
		meth_ void uniforms(const Pass& pass, const string& name, const vec4* value, uint16_t num);

		FilterUniform u_uniform;

		map<string, bgfx::UniformHandle> m_uniforms;

		Program& m_quad_program;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockCopy : public GfxBlock
	{
	public:
		BlockCopy(GfxSystem& gfx, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		void quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, const RenderQuad& quad, uint64_t flags = 0U);
		void quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, uint64_t flags = 0U);
		meth_ void quad(const Pass& pass, FrameBuffer& fbo, Texture& texture, const uvec4& rect, uint64_t flags = 0U);

		void debug_show_texture(Render& render, Texture& texture, const vec4& rect, int level = 0);

		BlockFilter& m_filter;

		Program& m_program;
	};
}
