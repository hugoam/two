//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <infra/Array.h>
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#ifndef MUD_MODULES
namespace bx
{
	struct FileReaderI;
	struct FileWriterI;
}
#endif

namespace mud
{
	export_ enum class refl_ TextureHint : unsigned int
	{
		Black,
		White,
		Normal
	};

	export_ MUD_GFX_EXPORT void save_bgfx_texture(bx::AllocatorI& allocator, bx::FileWriterI& writer, cstring file_path, bgfx::TextureFormat::Enum target_format, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum texture_format, uint16_t width, uint16_t height, uint16_t depth = 1);
	export_ MUD_GFX_EXPORT bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, cstring name, void* data, size_t size, uint64_t flags = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info = nullptr, bool generate_mips = false);
	export_ MUD_GFX_EXPORT bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, bx::FileReaderI& reader, cstring file_path, uint64_t flags = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info = nullptr, bool generate_mips = false);
	export_ MUD_GFX_EXPORT bimg::ImageContainer* load_bgfx_image(bx::AllocatorI& allocator, bx::FileReaderI& reader, cstring file_path, bgfx::TextureFormat::Enum dst_format);

	export_ MUD_GFX_EXPORT void save_texture(GfxSystem& gfx_system, Texture& texture, const string& path);
	export_ MUD_GFX_EXPORT void load_texture(GfxSystem& gfx_system, Texture& texture, const string& path);
	export_ MUD_GFX_EXPORT void load_texture_mem(GfxSystem& gfx_system, Texture& texture, array<uint8_t> data);
	export_ MUD_GFX_EXPORT void load_texture_rgba(Texture& texture, uint16_t width, uint16_t height, array<uint8_t> data);

	export_ class refl_ MUD_GFX_EXPORT Texture
	{
	public:
		Texture(const string& name);
		~Texture();

		attr_ string m_name;
		attr_ uint16_t m_width = 0;
		attr_ uint16_t m_height = 0;
		attr_ uint32_t m_bits_per_pixel = 0;

		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
		bgfx::TextureFormat::Enum m_format;
	};
}
