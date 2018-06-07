//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Array.h>
#include <obj/Strung.h>
#include <math/Vec.h>
#endif
#include <gfx/Generated/Forward.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>
#endif

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

	export_ MUD_GFX_EXPORT bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, bx::FileReaderI& reader, cstring file_path, uint32_t flags = BGFX_TEXTURE_NONE, bgfx::TextureInfo* info = nullptr, bimg::Orientation::Enum* orientation = nullptr);
	export_ MUD_GFX_EXPORT bimg::ImageContainer* load_bgfx_image(bx::AllocatorI& allocator, bx::FileReaderI& reader, cstring file_path, bgfx::TextureFormat::Enum dst_format);

	export_ MUD_GFX_EXPORT void load_texture(GfxSystem& gfx_system, Texture& texture, cstring path);
	export_ MUD_GFX_EXPORT void load_texture_mem(Texture& texture, array<uint8_t> data);
	export_ MUD_GFX_EXPORT void load_texture_rgba(Texture& texture, uint16_t width, uint16_t height, array<uint8_t> data);

	export_ class refl_ MUD_GFX_EXPORT Texture
	{
	public:
		//Texture(cstring path, cstring name);
		Texture(cstring name);
		~Texture();

		/*attr_ mut_*/ string m_name;
		attr_ mut_ uint16_t m_width = 0;
		attr_ mut_ uint16_t m_height = 0;

		bgfx::TextureHandle m_texture = BGFX_INVALID_HANDLE;
	};
}
