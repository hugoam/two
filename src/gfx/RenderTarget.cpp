//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bx/math.h>
#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <gfx/RenderTarget.h>
#include <gfx/Node3.h>
#include <gfx/Renderer.h>
#endif

#define MUD_GL_NO_MRT

namespace mud
{
#if defined MUD_UNIFORM_BLOCKS
	TypedUniformBlock<RenderBlock> RenderBlock::s_block = { "render" };
#endif

	FrameBuffer::FrameBuffer(uvec2 size)
		: m_size(size)
		, m_screen_view(bxidentity())
		, m_screen_proj(bxortho({ 0.f, 1.f, 1.f, 0.f }, 0.f, 1.f, 0.f, bgfx::getCaps()->homogeneousDepth))// false))
	{
		m_fbo = BGFX_INVALID_HANDLE;

#if defined MUD_UNIFORM_BLOCKS
		m_render_block.m_render_size = vec2(m_size);
		m_render_block.m_pixel_size = 1.0f / vec2(m_size);
#endif
	}

	FrameBuffer::FrameBuffer(uvec2 size, bgfx::TextureFormat::Enum format, uint32_t textureFlags)
		: FrameBuffer(size)
	{
		m_fbo = bgfx::createFrameBuffer(uint16_t(size.x), uint16_t(size.y), format, textureFlags);
	}

	FrameBuffer::FrameBuffer(uvec2 size, bgfx::FrameBufferHandle fbo)
		: FrameBuffer(size)
	{
		m_fbo = fbo;
	}

	FrameBuffer::~FrameBuffer()
	{
		if(bgfx::isValid(m_fbo))
			bgfx::destroy(m_fbo);
	}

	void SwapBuffer::create(uvec2 size, bgfx::TextureFormat::Enum color_format)
	{
		m_one = bgfx::createFrameBuffer(uint16_t(size.x), uint16_t(size.y), color_format, GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
		m_two = bgfx::createFrameBuffer(uint16_t(size.x), uint16_t(size.y), color_format, GFX_TEXTURE_CLAMP | GFX_TEXTURE_POINT);
	}

	SwapBuffer::~SwapBuffer()
	{
		if(bgfx::isValid(m_one))
			bgfx::destroy(m_one);
		if(bgfx::isValid(m_two))
			bgfx::destroy(m_two);
	}

	void Cascade::create(uvec2 size, bgfx::TextureFormat::Enum color_format)
	{
		if(bgfx::isTextureValid(0, true, 1, color_format, BGFX_TEXTURE_BLIT_DST | GFX_TEXTURE_CLAMP))
			m_texture = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), true, 1, color_format, BGFX_TEXTURE_BLIT_DST | GFX_TEXTURE_CLAMP);
	}

	Cascade::~Cascade()
	{
		if(bgfx::isValid(m_texture))
			bgfx::destroy(m_texture);
	}

	RenderTarget::RenderTarget(uvec2 size)
		: FrameBuffer(size)
		, m_msaa(MSAA::X16)
	{
		static const uint32_t msaa_value[] = { BGFX_TEXTURE_RT, BGFX_TEXTURE_RT_MSAA_X2, BGFX_TEXTURE_RT_MSAA_X4, BGFX_TEXTURE_RT_MSAA_X8, BGFX_TEXTURE_RT_MSAA_X16 };
		uint32_t render_target_flags = msaa_value[size_t(m_msaa)];

#if defined MUD_PLATFORM_EMSCRIPTEN && !defined MUD_WEBGL2
		render_target_flags |= GFX_TEXTURE_CLAMP;
#endif

		bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;

		if(!bgfx::isTextureValid(0, false, 1, color_format, render_target_flags))
			color_format = bgfx::TextureFormat::RGB10A2;
		if(!bgfx::isTextureValid(0, false, 1, color_format, render_target_flags))
			color_format = bgfx::TextureFormat::RGBA8;

		m_depth = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::D24S8, render_target_flags);

		m_diffuse = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, color_format, render_target_flags);

#if defined MUD_PLATFORM_EMSCRIPTEN && !defined MUD_WEBGL2
		m_mrt = false;
#else
		m_mrt = bgfx::getCaps()->limits.maxFBAttachments >= 4;
#endif
		
#ifdef MUD_GL_NO_MRT
		// disabling MRT on OpenGL until we figure out a fix for the visual bug
		bool is_opengl = bgfx::getRendererType() == bgfx::RendererType::OpenGLES
					  || bgfx::getRendererType() == bgfx::RendererType::OpenGL;
		if(is_opengl)
			m_mrt = false;
#endif

		if(m_mrt)
		{
			m_specular = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, color_format, render_target_flags);

			m_normal_rough = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA8, render_target_flags);

			m_sss = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::R8, render_target_flags);

			bgfx::TextureHandle textures[5] = { m_depth, m_diffuse, m_specular, m_normal_rough, m_sss };
			m_fbo = bgfx::createFrameBuffer(5, textures, true);
		}
		else
		{
			bgfx::TextureHandle textures[2] = { m_depth, m_diffuse };
			m_fbo = bgfx::createFrameBuffer(2, textures, true);
		}

		m_ping_pong.create(size, color_format);
		m_post_process.create(size, color_format);

#if !defined MUD_PLATFORM_EMSCRIPTEN || defined MUD_WEBGL2
		m_cascade.create(size, color_format);
#endif
	}

	RenderTarget::~RenderTarget()
	{
		if(bgfx::isValid(m_fbo))
			bgfx::destroy(m_fbo);
	}
}
