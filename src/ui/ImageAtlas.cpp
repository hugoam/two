//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui/ImageAtlas.h>

#include <RectPacking/Rect.h>
#include <RectPacking/GuillotineBinPack.h>

#include <math/Interp.h>

#ifndef MUD_PLATFORM_EMSCRIPTEN
#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb_image.h>

namespace mud
{
	ImageAtlas::ImageAtlas(uvec2 size)
		: m_size(size)
		, m_inverse_size(1.f / vec2(size))
		, m_image("ImageAtlas", "", m_size)
		, m_rectPacker(make_unique<GuillotineBinPack>(size.x, size.y))
	{}

	ImageAtlas::~ImageAtlas()
	{}

	std::vector<unsigned char> ImageAtlas::generate_atlas(std::vector<Image*>& images)
	{
		size_t size = m_size.x * m_size.y * 4;
		std::vector<unsigned char> data(size, 0);

		m_images = images;

		// @todo : sort images

		for(Image* image : images)
		{
			this->place_image(*image);
			this->blit_image(*image, data);
		}

		return data;
	}

	void ImageAtlas::place_image(Image& sprite)
	{
		BPRect rect = m_rectPacker->Insert(sprite.d_size.x, sprite.d_size.y, false,
										   GuillotineBinPack::RectBestShortSideFit, GuillotineBinPack::SplitShorterLeftoverAxis);

		sprite.d_coord = { uint(rect.x), uint(rect.y) };
		sprite.d_atlas = this;
	}

	void ImageAtlas::blit_image(Image& sprite, std::vector<unsigned char>& data)
	{
		int width, height, n;
		stbi_set_unpremultiply_on_load(1);
		stbi_convert_iphone_png_to_rgb(1);
		unsigned char* sprite_data = stbi_load(sprite.d_path.c_str(), &width, &height, &n, 4);

		for(int y = 0; y < height; ++y)
		{
			size_t dest_offset = sprite.d_coord.x * 4 + (sprite.d_coord.y + y) * m_size.x * 4;
			std::copy(sprite_data + y * width * 4, sprite_data + (y + 1) * width * 4, data.data() + dest_offset);
		}

		stbi_image_free(sprite_data);
	}

	Sprite::Sprite(cstring name, cstring path, const uvec2& size, const uvec2& frames)
		: Image(name, path, size)
		, m_frames(frames)
		, m_num_frames(frames.x * frames.y)
		, m_frame_size(m_num_frames ? d_size / m_frames : uvec2(0U))
	{}

	Sprite::Sprite()
		: Sprite("", "", {}, {})
	{}

	void Sprite::compute_frames(const vec2& atlas_inverse_size)
	{
		for(size_t i = 0; i < m_num_frames; ++i)
		{
			uvec2 frame_coord = { i % m_frames.x, i / m_frames.x };
			m_frame_coords.push_back(d_coord + frame_coord * m_frame_size);
		}

		if(m_num_frames == 0)
		{
			m_frame_coords.push_back(d_coord);
			m_frame_size = d_size;
		}

		for(size_t i = 0; i < m_frame_coords.size(); ++i)
		{
			vec4 uv = { vec2{ m_frame_coords[i] } * atlas_inverse_size,
						vec2{ m_frame_coords[i] + m_frame_size } * atlas_inverse_size };
			m_frame_uvs.push_back(uv);
		}
	}

	SpriteAtlas::SpriteAtlas(uvec2 size)
		: ImageAtlas(size)
	{}

	const Sprite& SpriteAtlas::find_sprite(cstring name) const
	{
		for(const Sprite& sprite : m_sprites)
			if(strcmp(sprite.d_name, name) == 0)
				return sprite;
		return m_sprites[0];
	}

	Sprite& SpriteAtlas::add_sprite(cstring name, uvec2 size, uvec2 frames)
	{
		m_sprites.emplace_back(name, "", size, frames);
		Sprite& sprite = m_sprites.back();
		this->place_image(sprite);
		sprite.compute_frames(m_inverse_size);
		return sprite;
	}

	vec4 SpriteAtlas::sprite_uv(const Sprite& sprite, uint32_t frame) const
	{
		return sprite.m_frame_uvs[frame];
	}

	vec4 SpriteAtlas::sprite_uv(const Sprite& sprite, float t) const
	{
		if(sprite.m_num_frames > 0)
		{
			size_t index = lerp(size_t(0U), sprite.m_num_frames - 1U, t);
			return sprite.m_frame_uvs[index];
		}

		return sprite.m_frame_uvs[0];
	}
}
