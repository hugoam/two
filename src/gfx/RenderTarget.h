//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/span.h>
#include <type/Unique.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Viewport.h>

#ifdef MUD_UNIFORM_BLOCKS
#include <gfx/Uniform.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	export_ MUD_GFX_EXPORT vec4 fbo_dest_quad(const uvec2& size, const vec4& rect, bool origin_fbo = false);
	export_ MUD_GFX_EXPORT vec4 fbo_source_quad(const uvec2& size, const vec4& rect, bool origin_fbo = false);

#ifdef MUD_UNIFORM_BLOCKS
	export_ struct refl_ MUD_GFX_EXPORT RenderBlock
	{
		attr_ vec2 m_render_size;
		attr_ vec2 m_pixel_size;

		static TypedUniformBlock<RenderBlock> s_block;
	};
#endif

	export_ class refl_ MUD_GFX_EXPORT FrameBuffer
	{
	public:
		FrameBuffer(uvec2 size);
		FrameBuffer(uvec2 size, bgfx::TextureFormat::Enum format, uint32_t textureFlags);
		FrameBuffer(uvec2 size, bgfx::FrameBufferHandle fbo);
		~FrameBuffer();

		uvec2 m_size;
		bgfx::FrameBufferHandle m_fbo;

		mat4 m_screen_view;
		mat4 m_screen_proj;

		vec4 dest_quad(const vec4& rect, bool origin_fbo = false) const { return fbo_dest_quad(m_size, rect, origin_fbo); }
		vec4 source_quad(const vec4& rect, bool origin_fbo = false) const { return fbo_source_quad(m_size, rect, origin_fbo); }

		vec4 dest_quad(bool origin_fbo = false) const { return dest_quad(vec4(vec2(0.f), vec2(m_size)), origin_fbo); }
		vec4 source_quad(bool origin_fbo = false) const { return source_quad(vec4(vec2(0.f), vec2(m_size)), origin_fbo); }

		vec4 dest_quad_mip(const vec4& rect, int level, bool origin_fbo = false) const { return fbo_dest_quad({ m_size.x >> level, m_size.y >> level }, rect, origin_fbo); }
		vec4 source_quad_mip(const vec4& rect, int level, bool origin_fbo = false) const { return fbo_source_quad({ m_size.x >> level, m_size.y >> level }, rect, origin_fbo); }

#ifdef MUD_UNIFORM_BLOCKS
		RenderBlock m_render_block;
#endif
	};

	export_ struct SwapBuffer
	{
		void create(uvec2 size, bgfx::TextureFormat::Enum color_format);
		~SwapBuffer();
		bgfx::FrameBufferHandle swap() { m_state = !m_state; return m_state ? m_one : m_two; }
		bgfx::TextureHandle last() { return m_state ? bgfx::getTexture(m_one) : bgfx::getTexture(m_two); }
		bgfx::FrameBufferHandle m_one;
		bgfx::FrameBufferHandle m_two;
		bool m_state = false;
	};

	export_ struct Cascade
	{
		void create(uvec2 size, bgfx::TextureFormat::Enum color_format);
		~Cascade();
		bgfx::FrameBufferHandle m_fbo;
		bgfx::TextureHandle m_texture;
		size_t m_num_mips;
		unique<FrameBuffer> m_mips[9] = {};
	};

	export_ class refl_ MUD_GFX_EXPORT RenderTarget : public FrameBuffer
	{
	public:
		RenderTarget(uvec2 size);
		~RenderTarget();

		MSAA m_msaa = MSAA::Disabled;

		bool m_mrt = true;
		bgfx::FrameBufferHandle m_fbo;

		bgfx::TextureHandle m_depth;
		bgfx::TextureHandle m_diffuse;

		bgfx::TextureHandle m_specular;
		bgfx::TextureHandle m_normal_rough;
		bgfx::TextureHandle m_sss;

		SwapBuffer m_ping_pong;
		SwapBuffer m_post_process;

		Cascade m_cascade;

		bool m_deferred = false;

		struct
		{
			bgfx::FrameBufferHandle m_fbo;

			bgfx::TextureHandle m_depth;
			bgfx::TextureHandle m_position;
			bgfx::TextureHandle m_normal;
			bgfx::TextureHandle m_albedo;
			bgfx::TextureHandle m_surface;

		} m_gbuffer;
	};
}
