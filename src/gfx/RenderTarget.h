//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/span.h>
#include <math/Vec.hpp>
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
	export_ struct refl_ MUD_GFX_EXPORT RenderQuad
	{
		attr_ vec4 m_source = vec4(vec2(0.f), vec2(1.f));
		attr_ vec4 m_dest = vec4(vec2(0.f), vec2(1.f));
		attr_ bool m_fbo_flip = false;
		attr_ bool m_relative = true;
		constr_ RenderQuad() {}
		constr_ RenderQuad(const vec4& crop, const vec4& dest, bool fbo_flip = false, bool relative = true)
			: m_source(crop), m_dest(dest), m_fbo_flip(fbo_flip), m_relative(relative)
		{}
		constr_ RenderQuad(const vec4& rect, bool fbo_flip = false, bool relative = true)
			: m_source(rect), m_dest(rect), m_fbo_flip(fbo_flip), m_relative(relative)
		{}
	};

	export_ class refl_ MUD_GFX_EXPORT FrameBuffer
	{
	public:
		constr_ FrameBuffer();
		constr_ FrameBuffer(const uvec2& size, TextureFormat format, uint64_t flags = 0U);
		constr_ FrameBuffer(const uvec2& size, span<Texture*> textures);
		FrameBuffer(const uvec2& size, void* window = nullptr);
		FrameBuffer(const uvec2& size, Texture& texture, span<bgfx::Attachment> attach);
		FrameBuffer(Texture& texture);
		~FrameBuffer();

		FrameBuffer(FrameBuffer&& other);
		FrameBuffer& operator=(FrameBuffer&& other);

		attr_ uvec2 m_size;
		attr_ Texture m_tex;

		Texture* m_attach[6] = {};
		bgfx::FrameBufferHandle m_fbo = BGFX_INVALID_HANDLE;
		
		meth_ bool valid() const;

		//Texture& tex(size_t i) { return *m_attach[i]; }

		operator bgfx::FrameBufferHandle() const { return m_fbo; }

	private:
		FrameBuffer(const FrameBuffer& other) = default;
		FrameBuffer& operator=(const FrameBuffer& other) = default;
	};

	export_ class refl_ SwapBuffer
	{
	public:
		constr_ SwapBuffer() {}
		meth_ void create(const uvec2& size, TextureFormat color_format);
		~SwapBuffer();
		meth_ FrameBuffer& swap() { m_state = !m_state; return m_state ? m_one : m_two; }
		meth_ FrameBuffer& current() { return m_state ? m_one : m_two; }
		meth_ Texture& last() { return m_state ? m_one.m_tex : m_two.m_tex; }
		attr_ FrameBuffer m_one;
		attr_ FrameBuffer m_two;
		bool m_state = false;
	};

	export_ class refl_ Cascade
	{
	public:
		constr_ Cascade() {}
		meth_ void create(const uvec2& size, TextureFormat color_format);
		~Cascade();
		attr_ Texture m_texture;
		attr_ size_t m_num_mips;
		unique<FrameBuffer> m_fbos[9] = {};

		// @todo expose array members to reflection and get rid of this
		meth_ FrameBuffer& level(uint8_t index) { return *m_fbos[index]; }
	};

	export_ class refl_ SwapCascade
	{
	public:
		constr_ SwapCascade() {}
		meth_ void create(const uvec2& size, TextureFormat color_format);
		~SwapCascade();
		meth_ Cascade& swap() { m_state = !m_state; return m_state ? m_one : m_two; }
		meth_ Cascade& last() { return m_state ? m_one : m_two; }
		attr_ Cascade m_one;
		attr_ Cascade m_two;
		bool m_state = false;
	};

	export_ struct MUD_GFX_EXPORT GBuffer : public FrameBuffer
	{
		void create(const uvec2& size, TextureFormat color_format, uint64_t flags);

		Texture m_depth;
		Texture m_position;
		Texture m_normal;
		Texture m_albedo;
		Texture m_surface;
	};

	export_ class refl_ MUD_GFX_EXPORT RenderTarget : public FrameBuffer
	{
	public:
		RenderTarget(const uvec2& size, void* window = nullptr);
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
		attr_ SwapBuffer m_post;

		attr_ Cascade m_cascade;
		attr_ SwapCascade m_swap_cascade;

		attr_ bool m_deferred = false;

		GBuffer m_gbuffer;
	};
}
