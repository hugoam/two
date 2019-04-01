//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <math/Vec.hpp>
#include <gfx/RenderTarget.h>
#include <gfx/Node3.h>
#include <gfx/Renderer.h>
#endif

#define MUD_GL_NO_MRT
//#define MUD_GFX_DEFERRED

namespace mud
{
#if defined MUD_UNIFORM_BLOCKS
	TypedUniformBlock<RenderBlock> RenderBlock::s_block = { "render" };
#endif

	FrameBuffer::FrameBuffer()
	{}

	FrameBuffer::FrameBuffer(const uvec2& size, void* window)
		: m_size(size)
	{
		if(window == nullptr)
			m_fbo = BGFX_INVALID_HANDLE;
		else
			m_fbo = bgfx::createFrameBuffer(window, uint16_t(size.x), uint16_t(size.y));

#if defined MUD_UNIFORM_BLOCKS
		m_render_block.m_render_size = vec2(m_size);
		m_render_block.m_pixel_size = 1.0f / vec2(m_size);
#endif
	}

	FrameBuffer::FrameBuffer(const uvec2& size, TextureFormat format, uint64_t flags)
		: FrameBuffer(size)
	{
		m_tex = { size, false, format, flags | BGFX_TEXTURE_RT };
		m_fbo = bgfx::createFrameBuffer(1, &m_tex.m_tex, false);
	}
	
	FrameBuffer::FrameBuffer(const uvec2& size, span<Texture*> textures)
		: FrameBuffer(size)
	{
		bgfx::TextureHandle handles[6];
		for(size_t i = 0; i < textures.size(); ++i)
		{
			m_attach[i] = textures[i];
			handles[i] = textures[i]->m_tex;
		}
		m_fbo = bgfx::createFrameBuffer(uint8_t(textures.size()), handles, false);
	}

	FrameBuffer::FrameBuffer(const uvec2& size, Texture& texture, span<bgfx::Attachment> attach)
		: FrameBuffer(size)
	{
		m_fbo = bgfx::createFrameBuffer(attach.size(), attach.data(), false);
	}

	FrameBuffer::FrameBuffer(Texture& texture)
		: FrameBuffer(texture.m_size)
	{
		m_fbo = bgfx::createFrameBuffer(1, &texture.m_tex, false);
	}

	FrameBuffer::~FrameBuffer()
	{
		if(bgfx::isValid(m_fbo))
			bgfx::destroy(m_fbo);
	}

	FrameBuffer::FrameBuffer(FrameBuffer&& other)
	{
		*this = move(other);
	}

	FrameBuffer& FrameBuffer::operator=(FrameBuffer&& other)
	{
		m_fbo = other.m_fbo;
		m_size = other.m_size;
		m_tex = move(other.m_tex);
		for(size_t i = 0; i < 6; ++i)
			m_attach[i] = other.m_attach[i];
		other.m_fbo = BGFX_INVALID_HANDLE; return *this;
	}

	bool FrameBuffer::valid() const { return bgfx::isValid(m_fbo); }

	void SwapBuffer::create(const uvec2& size, TextureFormat color_format)
	{
		m_one = { size, color_format, GFX_TEXTURE_CLAMP };// | GFX_TEXTURE_POINT);
		m_two = { size, color_format, GFX_TEXTURE_CLAMP };// | GFX_TEXTURE_POINT);
	}

	SwapBuffer::~SwapBuffer()
	{}

	void Cascade::create(const uvec2& size, TextureFormat color_format)
	{
		//const uint64_t flags = BGFX_TEXTURE_BLIT_DST | GFX_TEXTURE_CLAMP;
		const uint64_t flags = BGFX_TEXTURE_RT | GFX_TEXTURE_CLAMP;

		if(!bgfx::isTextureValid(1, false, 1, bgfx::TextureFormat::Enum(color_format), flags))
			return;

		m_texture = { size, true, color_format, flags };

		for(uint16_t i = 0; size.x > 1 && i < 9; ++i)
		{
			uvec2 level_size = uvec2(size.x >> i, size.y >> i);
			bgfx::Attachment attach = { bgfx::Access::Write, m_texture, i, 0, BGFX_RESOLVE_NONE };
			m_fbos[i] = make_unique<FrameBuffer>(level_size, m_texture, span<bgfx::Attachment>{ attach });
		}
	}

	Cascade::~Cascade()
	{
		if(bgfx::isValid(m_texture))
			bgfx::destroy(m_texture);
	}

	void SwapCascade::create(const uvec2& size, TextureFormat color_format)
	{
		m_one.create(size, color_format);
		m_two.create(size, color_format);
	}
	
	SwapCascade::~SwapCascade()
	{}

	RenderTarget::RenderTarget(const uvec2& size, void* window)
		: FrameBuffer(size)
		, m_backbuffer(size, window)
		//, m_msaa(MSAA::X16)
	{
		static const table<MSAA, uint64_t> msaa_flag = { BGFX_TEXTURE_RT, BGFX_TEXTURE_RT_MSAA_X2, BGFX_TEXTURE_RT_MSAA_X4, BGFX_TEXTURE_RT_MSAA_X8, BGFX_TEXTURE_RT_MSAA_X16 };
		
		TextureFormat color_format = TextureFormat::RGBA16F;

		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::Enum(color_format), 0))
			color_format = TextureFormat::RGB10A2;
		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::Enum(color_format), 0))
			color_format = TextureFormat::RGBA8;
		if(!bgfx::isTextureValid(0, false, 1, bgfx::TextureFormat::Enum(color_format), msaa_flag[m_msaa]))
			m_msaa = MSAA::Disabled;

		const uint64_t flags = msaa_flag[m_msaa];

#ifdef MUD_PLATFORM_EMSCRIPTEN
		const uint64_t depth_flags = flags | GFX_TEXTURE_POINT;
#else
		const uint64_t depth_flags = flags;
#endif

		m_depth = { size, false, TextureFormat::D24S8, depth_flags };

		m_diffuse = { size, false, color_format, flags };

		m_mrt = bgfx::getCaps()->limits.maxFBAttachments >= 4;
		
#ifdef MUD_GL_NO_MRT
		// disabling MRT on OpenGL until we figure out a fix for the visual bug
		bool is_opengl = bgfx::getRendererType() == bgfx::RendererType::OpenGLES
					  || bgfx::getRendererType() == bgfx::RendererType::OpenGL;
		if(is_opengl)
			m_mrt = false;
#endif

		m_mrt = false;
		if(m_mrt)
		{
			m_specular = { size, false, color_format, flags };

			m_normal_rough = { size, false, TextureFormat::RGBA8, flags };

			//m_sss = { size, bgfx::TextureFormat::R8, render_target_flags };

			bgfx::TextureHandle textures[4] = { m_depth, m_diffuse, m_specular, m_normal_rough };
			m_fbo = bgfx::createFrameBuffer(4, textures, true);
		}
		else
		{
			bgfx::TextureHandle textures[2] = { m_depth, m_diffuse };
			m_fbo = bgfx::createFrameBuffer(2, textures, true);
		}

		m_ping_pong.create(size, color_format);
		m_post.create(size, color_format);

		m_cascade.create(size, color_format);

#ifdef MUD_GFX_DEFERRED
		m_deferred = true;
#else
		m_deferred = false;
#endif
		if(m_deferred)
			m_gbuffer.create(size, color_format, flags, depth_flags);
	}

	RenderTarget::~RenderTarget()
	{}

	void GBuffer::create(const uvec2& size, TextureFormat color_format, uint64_t flags, uint64_t depth_flags)
	{
		m_depth    = { size, false, TextureFormat::D24S8, depth_flags };
		m_position = { size, false, color_format,		  flags };
		m_normal   = { size, false, color_format,		  flags };
		m_albedo   = { size, false, color_format,		  flags };
		m_surface  = { size, false, TextureFormat::RGBA8, flags };

		(FrameBuffer&)*this = { size, { &m_depth, &m_position, &m_normal, &m_albedo, &m_surface } };
	}
}
