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
#include <gfx/Texture.h>

#ifdef MUD_UNIFORM_BLOCKS
#include <gfx/Uniform.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	export_ MUD_GFX_EXPORT vec4 fbo_dest_quad(const uvec2& size, const vec4& rect, bool from_fbo = false);
	export_ MUD_GFX_EXPORT vec4 fbo_source_quad(const uvec2& size, const vec4& rect, bool from_fbo = false);

	export_ struct refl_ MUD_GFX_EXPORT RenderQuad
	{
		attr_ vec4 m_source;
		attr_ vec4 m_dest;
		attr_ bool m_fbo_flip = false;
		constr_ RenderQuad(vec4 crop, vec4 dest, bool fbo_flip = false) : m_source(crop), m_dest(dest), m_fbo_flip(fbo_flip) {}
		constr_ RenderQuad() {}
	};

	export_ class refl_ MUD_GFX_EXPORT FrameBuffer : public Texture
	{
	public:
		FrameBuffer();
		FrameBuffer(const uvec2& size);
		FrameBuffer(const uvec2& size, bgfx::TextureFormat::Enum format, uint64_t flags = 0U);
		FrameBuffer(const uvec2& size, bgfx::FrameBufferHandle fbo);
		FrameBuffer(Texture& texture);
		~FrameBuffer();

		FrameBuffer(FrameBuffer&& other) : FrameBuffer(other) { other.m_fbo = BGFX_INVALID_HANDLE; other.m_tex = BGFX_INVALID_HANDLE; }
		FrameBuffer& operator=(FrameBuffer&& other) { *this = other; other.m_fbo = BGFX_INVALID_HANDLE; other.m_tex = BGFX_INVALID_HANDLE; return *this; }

		attr_ uvec2 m_size;

		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		
		bool valid() const;

		operator bgfx::FrameBufferHandle() const { return m_fbo; }

		vec4 dest_quad(const vec4& rect, bool from_fbo = false) const { return fbo_dest_quad(m_size, rect, from_fbo); }
		vec4 source_quad(const vec4& rect, bool from_fbo = false) const { return fbo_source_quad(m_size, rect, from_fbo); }

		RenderQuad render_quad(const vec4& rect, bool fbo_flip = true, bool from_fbo = false) const
		{
			return { this->source_quad(rect, from_fbo), this->dest_quad(rect, from_fbo), fbo_flip };
		}

		vec4 dest_quad(bool origin_fbo = false) const { return dest_quad(vec4(vec2(0.f), vec2(m_size)), origin_fbo); }
		vec4 source_quad(bool origin_fbo = false) const { return source_quad(vec4(vec2(0.f), vec2(m_size)), origin_fbo); }

		vec4 dest_quad_mip(const vec4& rect, int level, bool origin_fbo = false) const { return fbo_dest_quad({ m_size.x >> level, m_size.y >> level }, rect, origin_fbo); }
		vec4 source_quad_mip(const vec4& rect, int level, bool origin_fbo = false) const { return fbo_source_quad({ m_size.x >> level, m_size.y >> level }, rect, origin_fbo); }

	private:
		FrameBuffer(const FrameBuffer& other) = default;
		FrameBuffer& operator=(const FrameBuffer& other) = default;
	};

	export_ class refl_ SwapBuffer
	{
	public:
		void create(uvec2 size, bgfx::TextureFormat::Enum color_format);
		~SwapBuffer();
		meth_ FrameBuffer& swap() { m_state = !m_state; return m_state ? m_one : m_two; }
		meth_ Texture& last() { return m_state ? m_one : m_two; }
		attr_ FrameBuffer m_one;
		attr_ FrameBuffer m_two;
		bool m_state = false;
	};

	export_ class refl_ Cascade
	{
	public:
		void create(uvec2 size, bgfx::TextureFormat::Enum color_format);
		~Cascade();
		attr_ Texture m_texture;
		attr_ size_t m_num_mips;
		unique<FrameBuffer> m_fbos[9] = {};
	};

	export_ class refl_ SwapCascade
	{
	public:
		void create(uvec2 size, bgfx::TextureFormat::Enum color_format);
		~SwapCascade();
		meth_ Cascade& swap() { m_state = !m_state; return m_state ? m_one : m_two; }
		meth_ Cascade& last() { return m_state ? m_one : m_two; }
		attr_ Cascade m_one;
		attr_ Cascade m_two;
		bool m_state = false;
	};

	export_ class refl_ MUD_GFX_EXPORT RenderTarget : public FrameBuffer
	{
	public:
		RenderTarget(uvec2 size);
		~RenderTarget();

		attr_ FrameBuffer m_backbuffer;

		attr_ MSAA m_msaa = MSAA::Disabled;

		attr_ bool m_mrt = true;

		attr_ Texture m_depth;
		attr_ Texture m_diffuse;

		attr_ Texture m_specular;
		attr_ Texture m_normal_rough;
		attr_ Texture m_sss;

		attr_ SwapBuffer m_ping_pong;
		attr_ SwapBuffer m_post_process;

		attr_ Cascade m_cascade;
		attr_ SwapCascade m_swap_cascade;

		attr_ bool m_deferred = false;

		struct GBuffer
		{
			FrameBuffer m_fbo;

			Texture m_depth;
			Texture m_position;
			Texture m_normal;
			Texture m_albedo;
			Texture m_surface;

		} m_gbuffer;
	};
}
