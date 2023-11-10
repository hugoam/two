//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>
#include <stl/string.h>
#include <stl/span.h>
#include <stl/swap.h>
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>

#ifndef TWO_MODULES
namespace bx
{
	struct FileReaderI;
	struct FileWriterI;
}
#endif

namespace two
{
	export_ using cstring = const char*;

	export_ enum class refl_ TextureHint : unsigned int
	{
		Black,
		White,
		Normal
	};

	export_ TWO_GFX_EXPORT void save_bgfx_texture(GfxSystem& gfx, const string& file_path, bgfx::TextureFormat::Enum target_format, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum texture_format, uint16_t width, uint16_t height, uint16_t depth = 1);
	export_ TWO_GFX_EXPORT bimg::ImageContainer* load_bgfx_image(GfxSystem& gfx, const string& file_path, bgfx::TextureFormat::Enum dst_format);

	export_ enum class refl_ TextureFormat : unsigned int
	{
		None    = bgfx::TextureFormat::Unknown,

		R8      = bgfx::TextureFormat::R8,
		R16F    = bgfx::TextureFormat::R16F,
		R32U	= bgfx::TextureFormat::R32U,
		R32F    = bgfx::TextureFormat::R32F,
		RG8     = bgfx::TextureFormat::RG8,
		RG16F   = bgfx::TextureFormat::RG16F,
		RG32F   = bgfx::TextureFormat::RG32F,
		RGB8    = bgfx::TextureFormat::RGB8,
		BGRA8   = bgfx::TextureFormat::BGRA8,
		RGBA8   = bgfx::TextureFormat::RGBA8,
		RGB10A2 = bgfx::TextureFormat::RGB10A2,
		RGBA16F = bgfx::TextureFormat::RGBA16F,
		RGBA32F = bgfx::TextureFormat::RGBA32F,

		D16     = bgfx::TextureFormat::D16,
		D24     = bgfx::TextureFormat::D24,
		D24S8   = bgfx::TextureFormat::D24S8,
		D32     = bgfx::TextureFormat::D32,
		D32F    = bgfx::TextureFormat::D32F,

		Count
	};

	export_ TWO_GFX_EXPORT void save_texture(GfxSystem& gfx, Texture& texture, const string& path, TextureFormat target_format = TextureFormat::None);

	export_ class refl_ TWO_GFX_EXPORT Texture
	{
	public:
		constr_ Texture(const string& name = "");
		constr_ Texture(const uvec2& size, bool mips, TextureFormat format, uint64_t flags = 0U, bool cube = false);
		Texture(const uvec2& size, bool mips, int layers, TextureFormat format, uint64_t flags = 0U);
		Texture(const uvec3& size, bool mips, TextureFormat format, uint64_t flags = 0U);
		~Texture();

		Texture(Texture&& other) : Texture(other) { other.m_tex = BGFX_INVALID_HANDLE; }
		Texture& operator=(Texture&& other) { bgfx::TextureHandle tex = m_tex; *this = other; other.m_tex = tex; return *this; }

		attr_ string m_name;
		attr_ string m_location;
		attr_ TextureFormat m_format;
		attr_ uvec2 m_size = uvec2(0U);
		attr_ uint16_t m_depth = 0;
		attr_ uint32_t m_memsize = 0;
		attr_ uint32_t m_bits_per_pixel = 0;
		attr_ bool m_is_depth = false;
		attr_ bool m_is_depth_packed = false;
		attr_ bool m_is_array = false;
		attr_ bool m_is_cube = false;
		attr_ bool m_is_fbo = false;
		attr_ bool m_mips = false;

		meth_ bool valid() const;

		meth_ void load(GfxSystem& gfx, const string& path, bool srgb = false, bool mips = false);
		meth_ void reload(GfxSystem& gfx, bool srgb = false, bool mips = false);

		meth_ void load_mem(GfxSystem& gfx, span<uint8_t> data);

		void load_rgba(const uvec2& size, const bgfx::Memory& data);
		void load_float(const uvec2& size, const bgfx::Memory& data, uint8_t num_components = 4);

		meth_ void load_rgba(const uvec2& size, span<uint32_t> data, bool ref = false);
		meth_ void load_float(const uvec2& size, span<float> data, bool ref = false);

		void init(bgfx::TextureHandle texture, bgfx::TextureInfo& texture_info)
		{
			if (!bgfx::isValid(texture))
			{
				// set placeholder "missing texture" texture instead
				return;
			}

			m_tex = texture;

			m_size = uvec2(texture_info.width, texture_info.height);
			m_format = TextureFormat(texture_info.format);
			m_memsize = texture_info.storageSize;
			m_bits_per_pixel = texture_info.bitsPerPixel;
			m_is_cube = texture_info.cubeMap;
			m_is_array = texture_info.numLayers > 1;
			m_mips = texture_info.numMips > 0;

			//bgfx::setName(m_tex, path.c_str());
			bgfx::setName(m_tex, m_name.c_str());
		}

		bgfx::TextureHandle m_tex = BGFX_INVALID_HANDLE;

		operator bgfx::TextureHandle() const { return m_tex; }

	protected:
		Texture(const Texture& other) = default;
		Texture& operator=(const Texture& other) = default;
	};

	export_ struct GpuTexture
	{
		Texture texture;
		vector<float> memory;
		vector<float> prev;
		uint16_t width = 1024;
		uint8_t stride = 4;
	};
}
