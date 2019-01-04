//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
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
			s_source_0		= bgfx::createUniform("s_source_0",		bgfx::UniformType::Int1);
			s_source_1		= bgfx::createUniform("s_source_1",		bgfx::UniformType::Int1);
			s_source_2		= bgfx::createUniform("s_source_2",		bgfx::UniformType::Int1);
			s_source_3		= bgfx::createUniform("s_source_3",		bgfx::UniformType::Int1);
			s_source_depth	= bgfx::createUniform("s_source_depth",	bgfx::UniformType::Int1);

			u_source_0_level	 = bgfx::createUniform("u_source_0_level",		bgfx::UniformType::Int1);
			u_source_1_level	 = bgfx::createUniform("u_source_1_level",		bgfx::UniformType::Int1);
			u_source_2_level	 = bgfx::createUniform("u_source_2_level",		bgfx::UniformType::Int1);
			u_source_3_level	 = bgfx::createUniform("u_source_3_level",		bgfx::UniformType::Int1);
			u_source_depth_level = bgfx::createUniform("u_source_depth_level",	bgfx::UniformType::Int1);

			u_source_0_crop		 = bgfx::createUniform("u_source_0_crop",		bgfx::UniformType::Vec4);

			u_screen_size_pixel_size =		bgfx::createUniform("u_screen_size_pixel_size",		bgfx::UniformType::Vec4);
			u_camera_params =				bgfx::createUniform("u_camera_params",				bgfx::UniformType::Vec4);
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

		bgfx::UniformHandle u_screen_size_pixel_size;
		bgfx::UniformHandle u_camera_params;
	};

	export_ class refl_ MUD_GFX_EXPORT Filter
	{
	public:
		virtual ~Filter() {}
	};

	export_ struct refl_ MUD_GFX_EXPORT RenderQuad
	{
		vec4 m_source;
		vec4 m_dest;
		bool m_fbo_flip = false;
		RenderQuad(vec4 crop, vec4 dest, bool fbo_flip = false) : m_source(crop), m_dest(dest), m_fbo_flip(fbo_flip) {}
		RenderQuad() {}
	};

	RenderQuad copy_quad(const FrameBuffer& target, const vec4& rect);

	//RenderQuad copy_quad(const FrameBuffer& source, const FrameBuffer& target, const vec4& source_rect, const vec4& dest_rect);
	
	export_ class refl_ MUD_GFX_EXPORT BlockFilter : public GfxBlock
	{
	public:
		BlockFilter(GfxSystem& gfx_system);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		void set_uniforms(Render& render, bgfx::Encoder& encoder);

		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags = 0U, bool render = false);

		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const RenderQuad& quad, uint64_t flags = 0U, bool render = false);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const uvec4& rect, uint64_t flags = 0U, bool render = false);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, uint64_t flags = 0U, bool render = false);

		FilterUniform u_uniform;

		Program& m_quad_program;
	};

	export_ class refl_ MUD_GFX_EXPORT BlockCopy : public GfxBlock
	{
	public:
		BlockCopy(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_block() override;

		virtual void begin_render(Render& render) override;
		virtual void begin_pass(Render& render) override;

		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const uvec4& rect, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const RenderQuad& quad, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const uvec4& rect, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, uint64_t flags = 0U);

		void debug_show_texture(Render& render, bgfx::TextureHandle texture, const vec4& rect, bool is_depth = false, bool is_depth_packed = false, bool is_array = false, int level = 0);

		BlockFilter& m_filter;

		Program& m_program;
	};
}
