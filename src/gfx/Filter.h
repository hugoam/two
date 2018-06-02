//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <gfx/Renderer.h>

namespace mud
{
	enum ShaderOptionFilter : unsigned int
	{
		FILTER_UNPACK_DEPTH,
		FILTER_SOURCE_DEPTH,
		FILTER_SOURCE_0_CUBE,
		FILTER_SOURCE_0_ARRAY,
		FILTER_DEBUG_UV,
	};

	struct FilterUniform
	{
		void createUniforms()
		{
			s_source_0		= bgfx::createUniform("s_source_0",		bgfx::UniformType::Int1);
			s_source_1		= bgfx::createUniform("s_source_1",		bgfx::UniformType::Int1);
			s_source_2		= bgfx::createUniform("s_source_2",		bgfx::UniformType::Int1);
			s_source_depth	= bgfx::createUniform("s_source_depth",	bgfx::UniformType::Int1);

			u_source_0_level	 = bgfx::createUniform("u_source_0_level",		bgfx::UniformType::Int1);
			u_source_1_level	 = bgfx::createUniform("u_source_1_level",		bgfx::UniformType::Int1);
			u_source_2_level	 = bgfx::createUniform("u_source_2_level",		bgfx::UniformType::Int1);
			u_source_depth_level = bgfx::createUniform("u_source_depth_level",	bgfx::UniformType::Int1);

			u_source_0_crop		 = bgfx::createUniform("u_source_0_crop",		bgfx::UniformType::Vec4);

			u_screen_size_pixel_size =		bgfx::createUniform("u_screen_size_pixel_size",		bgfx::UniformType::Vec4);
			u_camera_params =				bgfx::createUniform("u_camera_params",				bgfx::UniformType::Vec4);
		}

		bgfx::UniformHandle s_source_0;
		bgfx::UniformHandle s_source_1;
		bgfx::UniformHandle s_source_2;
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

	export_ class _refl_ MUD_GFX_EXPORT Filter
	{
	public:
		virtual ~Filter() {}
	};

	export_ struct _refl_ MUD_GFX_EXPORT RenderQuad
	{
		vec4 m_source = Rect4;
		vec4 m_dest = Zero4;
		bool m_source_fbo = false;
		bool m_relative = false;

		RenderQuad(vec4 rect, bool source_fbo = false, bool relative = false) : m_source(rect), m_dest(rect), m_source_fbo(source_fbo), m_relative(relative) {}
		RenderQuad(vec4 crop, vec4 dest, bool source_fbo = false, bool relative = false) : m_source(crop), m_dest(dest), m_source_fbo(source_fbo), m_relative(relative) {}
		RenderQuad() {}
	};

	export_ class _refl_ MUD_GFX_EXPORT BlockFilter : public GfxBlock
	{
	public:
		BlockFilter(GfxSystem& gfx_system);

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		void set_uniforms(Render& render);

		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::ProgramHandle program, const RenderQuad& quad = {}, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const RenderQuad& quad = {}, uint64_t flags = 0U);

		void render_quad(FrameBuffer& target, uint8_t view, bgfx::ProgramHandle program, const RenderQuad& quad = {});

		FilterUniform u_uniform;
	};

	export_ class _refl_ MUD_GFX_EXPORT BlockCopy : public GfxBlock
	{
	public:
		BlockCopy(GfxSystem& gfx_system, BlockFilter& filter);

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::FrameBufferHandle fbo, bgfx::TextureHandle texture, const RenderQuad& quad = {}, uint64_t flags = 0U);
		void submit_quad(FrameBuffer& target, uint8_t view, bgfx::TextureHandle texture, const RenderQuad& quad = {}, uint64_t flags = 0U);
		
		void debug_show_texture(FrameBuffer& target, bgfx::TextureHandle texture, bool is_depth = false, bool is_depth_packed = false, bool is_array = false, int level = 0);

		BlockFilter& m_filter;

		Program m_program;
	};
}
