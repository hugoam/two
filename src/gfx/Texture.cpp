//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#include <bgfx/bgfx.h>
#include <bimg/bimg.h>
#include <bimg/decode.h>
#include <bimg/encode.h>
#include <bx/readerwriter.h>
#include <bx/file.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <stl/string.h>
#include <infra/File.h>
#include <gfx/Texture.h>
#include <gfx/GfxSystem.h>
#include <gfx/Node3.h>
#include <gfx/Renderer.h>
#endif

#include <cstdio>
#include <cstring>

namespace mud
{
	string readable_file_size(double size)
	{
		int i = 0;
		const char* units[] = { "B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" };
		for(; size > 1024; ++i)
			size /= 1024;
		char buffer[10];
		sprintf(buffer, "%.*f %s", i, size, units[i]);
		return string(buffer);
	}

	static void* load_mem(bx::FileReaderI* reader, bx::AllocatorI* allocator, const char* file_path, uint32_t* size)
	{
		if(!bx::open(reader, file_path))
		{
			printf("ERROR: Failed to open: %s.\n", file_path);
			return nullptr;
		}

		uint32_t data_size = (uint32_t)bx::getSize(reader);
		void* data = BX_ALLOC(allocator, data_size);
		bx::read(reader, data, data_size);
		bx::close(reader);

		if(size)
			*size = data_size;
		return data;
	}

	static void release_bgfx_image(void* _ptr, void* _userData)
	{
		BX_UNUSED(_ptr);
		bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
		bimg::imageFree(imageContainer);
	}

	void save_bgfx_texture(bx::AllocatorI& allocator, bx::FileWriterI& writer, cstring file_path, bgfx::TextureFormat::Enum target_format, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum texture_format, uint16_t width, uint16_t height, uint16_t depth)
	{
		bimg::ImageContainer* source = bimg::imageAlloc(&allocator, bimg::TextureFormat::Enum(texture_format), width, height, depth, 1, false, false);
		if(source == nullptr) return;

		for(uint8_t mip = 0; mip < source->m_numMips; ++mip)
		{
			uint32_t ready = bgfx::readTexture(texture, source->m_data, mip);
			while(bgfx::frame() != ready);
		}

		if(!bx::open(&writer, file_path))
		{
			printf("ERROR: Unable to open output file '%s'", file_path);
			return;
		}

		bimg::ImageContainer* encoded = source;
		if(target_format != texture_format)
			encoded = bimg::imageEncode(&allocator, bimg::TextureFormat::Enum(target_format), bimg::Quality::Default, *source);
		if(encoded == nullptr)
		{
			bimg::imageFree(source);
			return;
		}

		uint8_t stride = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(target_format)) / 8;

		if(target_format == bgfx::TextureFormat::RGBA16F)
			//bimg::imageWriteKtx(&writer, bimg::TextureFormat::RGBA16F, false, width, height, depth, source->m_numMips, 1, encoded->m_data, nullptr);
			bimg::imageWriteHdr(&writer, width, height, width * depth * stride, encoded->m_data, bimg::TextureFormat::RGBA16F, false, nullptr);
		if(target_format == bgfx::TextureFormat::RGBA8)
			bimg::imageWritePng(&writer, width, height, width * depth * stride, encoded->m_data, bimg::TextureFormat::RGBA8, false);
		if(target_format == bgfx::TextureFormat::BC3 || target_format == bgfx::TextureFormat::BC6H)
			bimg::imageWriteDds(&writer, *encoded, encoded->m_data, encoded->m_size, nullptr);

		bx::close(&writer);

		bimg::imageFree(source);
		if(target_format != texture_format)
			bimg::imageFree(encoded);
	}

	bgfx::TextureHandle load_bgfx_image(bimg::ImageContainer& image, const char* name, uint64_t flags, bgfx::TextureInfo* info)
	{
		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

		const bgfx::Memory* mem = bgfx::makeRef(image.m_data, image.m_size, release_bgfx_image, &image);

		printf("INFO: Loaded image %s of size %s in memory\n", name, readable_file_size(image.m_size).c_str());

		if(image.m_cubeMap)
		{
			handle = bgfx::createTextureCube(uint16_t(image.m_width), 1 < image.m_numMips,
											 image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format), flags, mem);
		}
		else if(1 < image.m_depth)
		{
			handle = bgfx::createTexture3D(uint16_t(image.m_width), uint16_t(image.m_height), uint16_t(image.m_depth),
										   1 < image.m_numMips, bgfx::TextureFormat::Enum(image.m_format), flags, mem);
		}
		else
		{
			handle = bgfx::createTexture2D(uint16_t(image.m_width), uint16_t(image.m_height), 1 < image.m_numMips,
										   image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format), flags, mem);
		}
		
		if(info)
		{
			bgfx::calcTextureSize(*info, uint16_t(image.m_width), uint16_t(image.m_height), uint16_t(image.m_depth),
								  image.m_cubeMap, 1 < image.m_numMips, image.m_numLayers, bgfx::TextureFormat::Enum(image.m_format));
		}

		return handle;
	}

	bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, const char* name, void* data, size_t size, uint64_t flags, bgfx::TextureInfo* info, bool generate_mips)
	{
		bimg::ImageContainer* image = bimg::imageParse(&allocator, data, uint32_t(size));
		BX_FREE(&allocator, data);

		if(!image)
			return BGFX_INVALID_HANDLE;

		// @todo implement per-type asset load options and remove this
		bool need_mips = image->m_format == bimg::TextureFormat::R8
					  || image->m_format == bimg::TextureFormat::RGB8
					  || image->m_format == bimg::TextureFormat::RGBA8;

		need_mips = false;

		if(need_mips && generate_mips && image->m_numMips <= 1)
		{
			bimg::ImageContainer* rgba8 = bimg::imageConvert(&allocator, bimg::TextureFormat::RGBA8, *image);
			bimg::ImageContainer* mips = bimg::imageGenerateMips(&allocator, *rgba8);
			if(mips != nullptr)
			{
				bimg::imageFree(rgba8);
				bimg::imageFree(image);
				image = mips;
			}
			else
			{
				printf("WARNING: could not generate mips for texture %s\n", name);
			}
		}

		return load_bgfx_image(*image, name, flags, info);
	}

	bgfx::TextureHandle load_bgfx_texture(bx::AllocatorI& allocator, bx::FileReaderI& reader, const char* file_path, uint64_t flags, bgfx::TextureInfo* info, bool generate_mips)
	{
		uint32_t size;
		void* data = load_mem(&reader, &allocator, file_path, &size);
		if(!data)
			return BGFX_INVALID_HANDLE;
		else
			return load_bgfx_texture(allocator, file_path, data, size, flags, info, generate_mips);
	}

	bimg::ImageContainer* load_bgfx_image(bx::AllocatorI& allocator, bx::FileReaderI& _reader, const char* _filePath, bgfx::TextureFormat::Enum _dstFormat)
	{
		uint32_t size = 0;
		void* data = load_mem(&_reader, &allocator, _filePath, &size);
		return bimg::imageParse(&allocator, data, size, bimg::TextureFormat::Enum(_dstFormat));
	}

	void save_texture(GfxSystem& gfx, Texture& tex, const string& path)
	{
		save_bgfx_texture(gfx.allocator(), gfx.file_writer(), path.c_str(), tex.m_format, 
						  tex.m_tex, tex.m_format, uint16_t(tex.m_size.x), uint16_t(tex.m_size.y));
	}

	void set_texture_info(Texture& texture, bgfx::TextureInfo& texture_info)
	{
		texture.m_size = uvec2(texture_info.width, texture_info.height);
		texture.m_format = texture_info.format;
		texture.m_memsize = texture_info.storageSize;
		texture.m_bits_per_pixel = texture_info.bitsPerPixel;
		texture.m_is_cube = texture_info.cubeMap;
		texture.m_is_array = texture_info.numLayers > 1;
		texture.m_mips = texture_info.numMips > 0;
	}

	void load_texture(GfxSystem& gfx, Texture& texture, const string& path)
	{
		if(file_extension(path) == "cube")
		{
			const string name = file_noext(path);
			const string format = "." + file_extension(name);
			const string base = file_noext(name);

			const string paths[] = {
				base + "/" + "px" + format, base + "/" + "nx" + format,
				base + "/" + "py" + format, base + "/" + "ny" + format,
				base + "/" + "pz" + format, base + "/" + "nz" + format
			};
			
			bimg::ImageContainer* sides[6] = {};
			for(size_t i = 0; i < 6; ++i)
			{
				uint32_t size;
				void* data = load_mem(&gfx.file_reader(), &gfx.allocator(), paths[i].c_str(), &size);
				sides[i] = bimg::imageParse(&gfx.allocator(), data, uint32_t(size));
				BX_FREE(&gfx.allocator(), data);
			}

			bimg::ImageContainer* cubemap = bimg::imageCubemapFrom6Sides(&gfx.allocator(), sides, nullptr);

			for(size_t i = 0; i < 6; ++i)
				bimg::imageFree(sides[i]);

			bgfx::TextureInfo texture_info;
			texture.m_tex = load_bgfx_image(*cubemap, path.c_str(), 0U, &texture_info);
			set_texture_info(texture, texture_info);
		}
		else
		{
			bgfx::TextureInfo texture_info;
			texture.m_tex = load_bgfx_texture(gfx.allocator(), gfx.file_reader(), path.c_str(), 0U, &texture_info, true);
			// if(!bgfx::isValid(texture.m_texture)) set placeholder "missing texture" texture instead
			set_texture_info(texture, texture_info);
		}
	}

	void load_texture_mem(GfxSystem& gfx, Texture& texture, span<uint8_t> data)
	{
		bgfx::TextureInfo texture_info;
		texture.m_tex = load_bgfx_texture(gfx.allocator(), texture.m_name.c_str(), (void*)data.m_pointer, data.m_count, 0U, &texture_info, true);
		// if(!bgfx::isValid(texture.m_texture)) set placeholder "missing texture" texture instead
		set_texture_info(texture, texture_info);
	}

	void load_texture_float(Texture& texture, const uvec2& size, const bgfx::Memory& memory, uint8_t num_components)
	{
		texture.m_size = size;
		texture.m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA32F, GFX_TEXTURE_POINT, &memory);
	}

	void load_texture_rgba(Texture& texture, const uvec2& size, const bgfx::Memory& memory)
	{
		texture.m_size = size;
		texture.m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA8, GFX_TEXTURE_POINT, &memory);
	}

	//void load_texture_rgba(Texture& texture, const uvec2& size, span<uint8_t> data)
	void load_texture_rgba(Texture& texture, const uvec2& size, span<uint32_t> data)
	{
		const bgfx::Memory* memory = bgfx::alloc(uint32_t(data.m_count * sizeof(uint32_t)));
		memcpy(memory->data, data.m_pointer, data.m_count * sizeof(uint32_t));
		load_texture_rgba(texture, size, *memory);
	}

	Texture::Texture(const string& name)
		: m_name(name)
	{}

	Texture::Texture(const uvec2& size, bool mips, bgfx::TextureFormat::Enum format, uint64_t flags, bool cube)
		: m_size(size)
		, m_format(format)
		, m_is_cube(cube)
	{
		m_tex = cube
			? bgfx::createTextureCube(uint16_t(size.x), mips, 1, format, flags)
			: bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), mips, 1, format, flags);
		m_is_depth = format >= bgfx::TextureFormat::D16 && format <= bgfx::TextureFormat::D0S8;
	}

	Texture::Texture(const uvec2& size, bool mips, int layers, bgfx::TextureFormat::Enum format, uint64_t flags)
		: m_size(size)
		, m_format(format)
	{
		m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), mips, layers, format, flags);
		m_is_depth = format >= bgfx::TextureFormat::D16 && format <= bgfx::TextureFormat::D0S8;
		m_is_array = true;
	}

	Texture::Texture(const uvec3& size, bool mips, bgfx::TextureFormat::Enum format, uint64_t flags)
		: m_size(size.x, size.y)
		, m_depth(size.z)
		, m_format(format)
	{
		m_tex = bgfx::createTexture3D(uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), mips, format, flags);
		m_is_depth = format >= bgfx::TextureFormat::D16 && format <= bgfx::TextureFormat::D0S8;
	}

	Texture::~Texture()
	{
		if(bgfx::isValid(m_tex))
			bgfx::destroy(m_tex);
	}

	bool Texture::valid() const { return bgfx::isValid(m_tex); }
}
