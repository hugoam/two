//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <math/Interp.h>
#include <ui/ImageAtlas.h>
#endif

#include <stb_rect_pack.h>
#include <stb_image.h>

namespace mud
{
	struct StbRectPack
	{
		StbRectPack(uvec2 size, size_t num_nodes)
			: m_nodes(num_nodes)
		{
			stbrp_init_target(&m_context, size.x, size.y, m_nodes.data(), num_nodes);
		}

		stbrp_context m_context;
		std::vector<stbrp_node> m_nodes;
	};

	ImageAtlas::ImageAtlas(uvec2 size)
		: m_size(size)
		, m_inverse_size(1.f / vec2(size))
		, m_image("ImageAtlas", "", m_size)
		//, m_rect_pack(make_unique<GuillotineBinPack>(size.x, size.y))
	{}

	ImageAtlas::~ImageAtlas()
	{}

	std::vector<unsigned char> ImageAtlas::generate_atlas(std::vector<Image*>& images)
	{
		size_t size = m_size.x * m_size.y * 4;
		std::vector<unsigned char> data(size, 0);

		m_images = images;

		// @todo : sort images

		m_rect_pack = make_unique<StbRectPack>(m_size, images.size());

		for(Image* image : images)
		{
			this->place_image(*image);
			this->blit_image(*image, data);
		}

		return data;
	}

	void ImageAtlas::place_image(Image& sprite)
	{
		//BPRect rect = m_rect_packer->Insert(sprite.d_size.x, sprite.d_size.y, false,
		//									GuillotineBinPack::RectBestShortSideFit, GuillotineBinPack::SplitShorterLeftoverAxis);

		stbrp_rect rect = { 0, stbrp_coord(sprite.d_size.x), stbrp_coord(sprite.d_size.y), 0, 0, false };
		stbrp_pack_rects(&m_rect_pack->m_context, &rect, 1);

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
		for(uint i = 0; i < m_num_frames; ++i)
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
	{
		m_rect_pack = make_unique<StbRectPack>(m_size, 128);
	}

	const Sprite& SpriteAtlas::find_sprite(cstring name) const
	{
		for(const Sprite& sprite : m_sprites)
			if(strcmp(sprite.d_name, name) == 0)
				return sprite;
		return m_sprites[0];
	}

	Sprite* SpriteAtlas::add_sprite(cstring name, uvec2 size, uvec2 frames)
	{
		if(m_sprites.size() >= m_rect_pack->m_nodes.size())
			return nullptr;
		m_sprites.emplace_back(name, "", size, frames);
		Sprite& sprite = m_sprites.back();
		this->place_image(sprite);
		sprite.compute_frames(m_inverse_size);
		return &sprite;
	}

	vec4 SpriteAtlas::sprite_uv(const Sprite& sprite, uint32_t frame) const
	{
		return sprite.m_frame_uvs[frame];
	}

	vec4 SpriteAtlas::sprite_uv(const Sprite& sprite, float t) const
	{
		if(sprite.m_num_frames > 0)
		{
			size_t index = lerp(0U, sprite.m_num_frames - 1U, t);
			return sprite.m_frame_uvs[index];
		}

		return sprite.m_frame_uvs[0];
	}
}
