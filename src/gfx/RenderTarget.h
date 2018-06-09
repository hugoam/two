//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Viewport.h>

#ifdef MUD_UNIFORM_BLOCKS
#include <gfx/Uniform.h>
#endif

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

namespace mud
{
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

#ifdef MUD_UNIFORM_BLOCKS
		RenderBlock m_render_block;
#endif

		bgfx::FrameBufferHandle m_fbo;

		mat4 m_screen_view;
		mat4 m_screen_proj;
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
	};
}
