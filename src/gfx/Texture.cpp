//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#define BX_COMPILER_MSVC_CONFORMANCE
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>
#include <bimg/decode.h>
#include <bimg/encode.h>
#include <bx/readerwriter.h>
#include <bx/file.h>
#include <gfx/Cpp20.h>
module two.gfx;

#include <cstdio>
#include <cstring>

namespace two
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
			error("gfx - failed to open: %s.", file_path);
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

	void save_bgfx_texture(GfxSystem& gfx, const string& file_path, bgfx::TextureFormat::Enum target_format, bgfx::TextureHandle texture, bgfx::TextureFormat::Enum texture_format, uint16_t width, uint16_t height, uint16_t depth)
	{
		bimg::ImageContainer* source = bimg::imageAlloc(&gfx.allocator(), bimg::TextureFormat::Enum(texture_format), width, height, depth, 1, false, false);
		if(source == nullptr) return;

		for(uint8_t mip = 0; mip < source->m_numMips; ++mip)
		{
			uint32_t ready = bgfx::readTexture(texture, source->m_data, mip);
			while(bgfx::frame() != ready);
		}

		if(!bx::open(&gfx.file_writer(), file_path.c_str()))
		{
			error("Unable to open output file '%s'", file_path.c_str());
			return;
		}

		bimg::ImageContainer* encoded = source;
		if(target_format != texture_format)
			encoded = bimg::imageEncode(&gfx.allocator(), bimg::TextureFormat::Enum(target_format), bimg::Quality::Default, *source);
		if(encoded == nullptr)
		{
			bimg::imageFree(source);
			return;
		}

		uint8_t stride = bimg::getBitsPerPixel(bimg::TextureFormat::Enum(target_format)) / 8;

		if(target_format == bgfx::TextureFormat::RGBA16F)
			//bimg::imageWriteKtx(&writer, bimg::TextureFormat::RGBA16F, false, width, height, depth, source->m_numMips, 1, encoded->m_data, nullptr);
			bimg::imageWriteHdr(&gfx.file_writer(), width, height, width * depth * stride, encoded->m_data, bimg::TextureFormat::RGBA16F, false, nullptr);
		if(target_format == bgfx::TextureFormat::RGBA8)
			bimg::imageWritePng(&gfx.file_writer(), width, height, width * depth * stride, encoded->m_data, bimg::TextureFormat::RGBA8, false);
		if(target_format == bgfx::TextureFormat::BC3 || target_format == bgfx::TextureFormat::BC6H)
			bimg::imageWriteDds(&gfx.file_writer(), *encoded, encoded->m_data, encoded->m_size, nullptr);

		bx::close(&gfx.file_writer());

		bimg::imageFree(source);
		if(target_format != texture_format)
			bimg::imageFree(encoded);
	}

	bgfx::TextureHandle load_bgfx_image(GfxSystem& gfx, bimg::ImageContainer& image, const string& name, uint64_t flags, bgfx::TextureInfo* texture_info, bool gen_mips)
	{
		// @todo implement per-type asset load options and remove this
		bool need_mips = image.m_format == bimg::TextureFormat::R8
			|| image.m_format == bimg::TextureFormat::RGB8
			|| image.m_format == bimg::TextureFormat::RGBA8;

		//need_mips = false;

		if(need_mips && gen_mips && image.m_numMips <= 1)
		{
			bimg::ImageContainer* rgba8 = bimg::imageConvert(&gfx.allocator(), bimg::TextureFormat::RGBA8, image);
			bimg::ImageContainer* mips = bimg::imageGenerateMips(&gfx.allocator(), *rgba8);
			if(mips != nullptr)
			{
				bimg::imageFree(rgba8);
				bimg::imageFree(&image);
				return load_bgfx_image(gfx, *mips, name, flags, texture_info, false);
			}
			else
			{
				warn("could not generate mips for texture %s", name.c_str());
			}
		}

		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

		const bgfx::Memory* mem = bgfx::makeRef(image.m_data, image.m_size, release_bgfx_image, &image);
		uint64_t srgb = image.m_srgb ? BGFX_TEXTURE_SRGB : 0;

		info("gfx - loaded image %s srgb(%i) of size %s in memory", name.c_str(), int(image.m_srgb), readable_file_size(image.m_size).c_str());

		bgfx::TextureFormat::Enum format = bgfx::TextureFormat::Enum(image.m_format);

		if (!bgfx::isTextureValid(uint16_t(image.m_depth), 1 < image.m_numMips, image.m_numLayers, format, flags | srgb))
			return BGFX_INVALID_HANDLE;

		if(image.m_cubeMap)
		{
			handle = bgfx::createTextureCube(uint16_t(image.m_width), 1 < image.m_numMips,
											 image.m_numLayers, format, flags | srgb, mem);
		}
		else if(1 < image.m_depth)
		{
			handle = bgfx::createTexture3D(uint16_t(image.m_width), uint16_t(image.m_height), uint16_t(image.m_depth),
										   1 < image.m_numMips, format, flags | srgb, mem);
		}
		else
		{
			handle = bgfx::createTexture2D(uint16_t(image.m_width), uint16_t(image.m_height), 1 < image.m_numMips,
										   image.m_numLayers, format, flags | srgb, mem);
		}
		
		if(texture_info)
		{
			bgfx::calcTextureSize(*texture_info, uint16_t(image.m_width), uint16_t(image.m_height), uint16_t(image.m_depth),
								  image.m_cubeMap, 1 < image.m_numMips, image.m_numLayers, format);
		}

		return handle;
	}

	bgfx::TextureHandle load_bgfx_texture(GfxSystem& gfx, const string& name, void* data, size_t size, uint64_t flags, bgfx::TextureInfo* info, bool gen_mips)
	{
		bimg::ImageContainer* image = bimg::imageParse(&gfx.allocator(), data, uint32_t(size));
		BX_FREE(&gfx.allocator(), data);

		if(!image)
			return BGFX_INVALID_HANDLE;

		return load_bgfx_image(gfx, *image, name, flags, info, gen_mips);
	}

	bgfx::TextureHandle load_bgfx_texture(GfxSystem& gfx, const string& file_path, uint64_t flags, bgfx::TextureInfo* info, bool generate_mips)
	{
		uint32_t size;
		void* data = load_mem(&gfx.file_reader(), &gfx.allocator(), file_path.c_str(), &size);
		if(!data)
			return BGFX_INVALID_HANDLE;
		else
			return load_bgfx_texture(gfx, file_path, data, size, flags, info, generate_mips);
	}

	bimg::ImageContainer* load_bgfx_image(GfxSystem& gfx, const string& file_path, bgfx::TextureFormat::Enum dest_format)
	{
		uint32_t size = 0;
		void* data = load_mem(&gfx.file_reader(), &gfx.allocator(), file_path.c_str(), &size);
		return bimg::imageParse(&gfx.allocator(), data, size, bimg::TextureFormat::Enum(dest_format));
	}

	void save_texture(GfxSystem& gfx, Texture& tex, const string& path, TextureFormat target_format)
	{
		bgfx::TextureFormat::Enum bgfx_format = bgfx::TextureFormat::Enum(tex.m_format);
		bgfx::TextureFormat::Enum bgfx_target_format = target_format == TextureFormat::None ? bgfx_format : bgfx::TextureFormat::Enum(target_format);
		save_bgfx_texture(gfx, path, bgfx_target_format, tex.m_tex, bgfx_format, uint16_t(tex.m_size.x), uint16_t(tex.m_size.y), tex.m_depth ? tex.m_depth : 1);
	}

	Texture::Texture(const string& name)
		: m_name(name)
	{}

	Texture::Texture(const uvec2& size, bool mips, TextureFormat format, uint64_t flags, bool cube)
		: m_size(size)
		, m_format(format)
		, m_is_cube(cube)
	{
		bgfx::TextureFormat::Enum bformat = bgfx::TextureFormat::Enum(format);
		m_tex = cube
			? bgfx::createTextureCube(uint16_t(size.x), mips, 1, bformat, flags)
			: bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), mips, 1, bformat, flags);
		m_is_depth = bformat >= bgfx::TextureFormat::D16 && bformat <= bgfx::TextureFormat::D0S8;
	}

	Texture::Texture(const uvec2& size, bool mips, int layers, TextureFormat format, uint64_t flags)
		: m_size(size)
		, m_format(format)
	{
		bgfx::TextureFormat::Enum bformat = bgfx::TextureFormat::Enum(format);
		m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), mips, uint16_t(layers), bformat, flags);
		m_is_depth = bformat >= bgfx::TextureFormat::D16 && bformat <= bgfx::TextureFormat::D0S8;
		m_is_array = true;
	}

	Texture::Texture(const uvec3& size, bool mips, TextureFormat format, uint64_t flags)
		: m_size(size.x, size.y)
		, m_depth(uint16_t(size.z))
		, m_format(format)
	{
		bgfx::TextureFormat::Enum bformat = bgfx::TextureFormat::Enum(format);
		m_tex = bgfx::createTexture3D(uint16_t(size.x), uint16_t(size.y), uint16_t(size.z), mips, bformat, flags);
		m_is_depth = bformat >= bgfx::TextureFormat::D16 && bformat <= bgfx::TextureFormat::D0S8;
	}

	Texture::~Texture()
	{
		if(bgfx::isValid(m_tex))
			bgfx::destroy(m_tex);
	}

	bool Texture::valid() const { return bgfx::isValid(m_tex); }

	void Texture::load(GfxSystem& gfx, const string& path, bool srgb, bool mips)
	{
		bgfx::TextureHandle texture;
		bgfx::TextureInfo texture_info;

		if (file_extension(path) == "cube")
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
			for (size_t i = 0; i < 6; ++i)
			{
				uint32_t size;
				void* data = two::load_mem(&gfx.file_reader(), &gfx.allocator(), paths[i].c_str(), &size);
				sides[i] = bimg::imageParse(&gfx.allocator(), data, uint32_t(size));
				BX_FREE(&gfx.allocator(), data);
			}

			bimg::ImageContainer* cubemap = bimg::imageCubemapFrom6Sides(&gfx.allocator(), sides, nullptr);

			for (size_t i = 0; i < 6; ++i)
				bimg::imageFree(sides[i]);

			texture = load_bgfx_image(gfx, *cubemap, path.c_str(), !srgb ? BGFX_TEXTURE_NONE : BGFX_TEXTURE_SRGB, &texture_info, mips);
		}
		else
		{
			texture = load_bgfx_texture(gfx, path, !srgb ? BGFX_TEXTURE_NONE : BGFX_TEXTURE_SRGB, &texture_info, mips);
		}

		m_location = path;

		this->init(texture, texture_info);
	}

	void Texture::load_mem(GfxSystem& gfx, span<uint8_t> data)
	{
		bgfx::TextureInfo texture_info;
		bgfx::TextureHandle texture = load_bgfx_texture(gfx, m_name, (void*)data.m_pointer, data.m_count, 0U, &texture_info, true);
		this->init(texture, texture_info);
	}

	void Texture::reload(GfxSystem& gfx, bool srgb, bool mips)
	{
		this->load(gfx, m_location, srgb, mips);
	}

	void Texture::load_float(const uvec2& size, const bgfx::Memory& memory, uint8_t num_components)
	{
		UNUSED(num_components);
		if(m_size == size)
		{
			bgfx::updateTexture2D(m_tex, 0, 0, 0, 0, uint16_t(size.x), uint16_t(size.y), &memory);
		}
		else
		{
			m_size = size;
			m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA32F, TEXTURE_POINT, &memory);
		}
	}

	void Texture::load_rgba(const uvec2& size, const bgfx::Memory& memory)
	{
		if(m_size == size)
		{
			bgfx::updateTexture2D(m_tex, 0, 0, 0, 0, uint16_t(size.x), uint16_t(size.y), &memory);
		}
		else
		{
			m_size = size;
			m_tex = bgfx::createTexture2D(uint16_t(size.x), uint16_t(size.y), false, 1, bgfx::TextureFormat::RGBA8, TEXTURE_POINT, &memory);
		}
	}

	void Texture::load_rgba(const uvec2& size, span<uint32_t> data, bool ref)
	{
		const bgfx::Memory* memory = ref
			? bgfx::makeRef(data.data(), uint32_t(data.size()))
			: bgfx::alloc(uint32_t(data.m_count * sizeof(uint32_t)));
		if(!ref)
			memcpy(memory->data, data.m_pointer, data.m_count * sizeof(uint32_t));
		this->load_rgba(size, *memory);
	}

	void Texture::load_float(const uvec2& size, span<float> data, bool ref)
	{
		const bgfx::Memory* memory = ref
			? bgfx::makeRef(data.data(), uint32_t(data.size()))
			: bgfx::alloc(uint32_t(data.m_count * sizeof(float)));
		if(!ref)
			memcpy(memory->data, data.m_pointer, data.m_count * sizeof(float));
		this->load_float(size, *memory);
	}
}
