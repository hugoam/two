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
		FILTER_UNPACK_DEPTH,
		FILTER_SOURCE_DEPTH,
		FILTER_SOURCE_0_CUBE,
		FILTER_SOURCE_0_ARRAY,
		FILTER_DEBUG_UV,
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

			u_source_0_level	 = bgfx::createUniform("u_source_0_level",		bgfx::UniformType::Sampler);
			u_source_1_level	 = bgfx::createUniform("u_source_1_level",		bgfx::UniformType::Sampler);
			u_source_2_level	 = bgfx::createUniform("u_source_2_level",		bgfx::UniformType::Sampler);
			u_source_3_level	 = bgfx::createUniform("u_source_3_level",		bgfx::UniformType::Sampler);
			u_source_depth_level = bgfx::createUniform("u_source_depth_level",	bgfx::UniformType::Sampler);

			u_source_0_crop		 = bgfx::createUniform("u_source_0_crop",		bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle s_source_0;
		bgfx::UniformHandle s_source_1;
		bgfx::UniformHandle s_source_2;
		bgfx::UniformHandle s_source_3;
		bgfx::UniformHandle s_source_depth;

		bgfx::UniformHandle u_source_0_level;
		bgfx::UniformHandle u_source_1_level;
		bgfx::UniformHandle u_source_2_level;
		bgfx::UniformHandle u_source_3_level;
		bgfx::UniformHandle u_source_depth_level;

		bgfx::UniformHandle u_source_0_crop;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockFilter : public GfxBlock
	{
	public:
		BlockFilter(GfxSystem& gfx);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;

		void submit_quad(uint8_t view, FrameBuffer& fbo, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		//void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags = 0U, bool render = false);

		void submit_quad(uint8_t view, FrameBuffer& fbo, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags = 0U, bool render = false);
		void submit_quad(uint8_t view, FrameBuffer& fbo, bgfx::ProgramHandle program, uint64_t flags = 0U, bool render = false);

		meth_ void set_source0(Texture& texture);
		meth_ void set_source1(Texture& texture);
		meth_ void set_source2(Texture& texture);
		meth_ void set_source3(Texture& texture);
		meth_ void set_sourcedepth(Texture& texture);
		meth_ void set_uniform(uint8_t view, const string& name, const vec4& value);

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

		void submit_quad(uint8_t view, FrameBuffer& fbo, Texture& texture, const RenderQuad& quad, uint64_t flags = 0U);
		void submit_quad(uint8_t view, FrameBuffer& fbo, Texture& texture, const uvec4& rect, uint64_t flags = 0U);
		void submit_quad(uint8_t view, FrameBuffer& fbo, Texture& texture, uint64_t flags = 0U);

		void debug_show_texture(Render& render, Texture& texture, const vec4& rect, int level = 0);

		BlockFilter& m_filter;

		Program& m_program;
	};
}
