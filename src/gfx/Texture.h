//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/span.h>
#include <stl/swap.h>
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
	export_ using cstring = const char*;

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

	export_ MUD_GFX_EXPORT void save_texture(GfxSystem& gfx, Texture& texture, const string& path);
	export_ MUD_GFX_EXPORT void load_texture(GfxSystem& gfx, Texture& texture, const string& path);
	export_ MUD_GFX_EXPORT void load_texture_mem(GfxSystem& gfx, Texture& texture, span<uint8_t> data);
	export_ MUD_GFX_EXPORT void load_texture_rgba(Texture& texture, const uvec2& size, const bgfx::Memory& data);
	export_ MUD_GFX_EXPORT void load_texture_float(Texture& texture, const uvec2& size, const bgfx::Memory& data, uint8_t num_components = 4);
	export_ MUD_GFX_EXPORT func_ void load_texture_rgba(Texture& texture, const uvec2& size, span<uint32_t> data);
	//export_ MUD_GFX_EXPORT func_ void load_texture_rgba(Texture& texture, uint16_t width, uint16_t height, span<uint8_t> data);

	export_ class refl_ MUD_GFX_EXPORT Texture
	{
	public:
		Texture(const string& name = "");
		Texture(const uvec2& size, bool mips, bgfx::TextureFormat::Enum format, uint64_t flags = 0U);
		Texture(const uvec2& size, bool mips, int layers, bgfx::TextureFormat::Enum format, uint64_t flags = 0U);
		Texture(const uvec3& size, bool mips, bgfx::TextureFormat::Enum format, uint64_t flags = 0U);
		explicit Texture(bgfx::TextureHandle texture);
		~Texture();

		Texture(Texture&& other) : Texture(other) { other.m_tex = BGFX_INVALID_HANDLE; }
		Texture& operator=(Texture&& other) { *this = other; other.m_tex = BGFX_INVALID_HANDLE; return *this; }

		attr_ string m_name;
		attr_ uvec2 m_size = uvec2(0U);
		attr_ uint16_t m_depth = 0;
		attr_ uint32_t m_bits_per_pixel = 0;
		attr_ bool m_is_depth = false;
		attr_ bool m_is_depth_packed = false;
		attr_ bool m_is_array = false;

		meth_ bool valid() const;

		bgfx::TextureHandle m_tex = BGFX_INVALID_HANDLE;
		bgfx::TextureFormat::Enum m_format;

		operator bgfx::TextureHandle() const { return m_tex; }

	protected:
		Texture(const Texture& other) = default;
		Texture& operator=(const Texture& other) = default;
	};
}
