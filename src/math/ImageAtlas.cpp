//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <stb_rect_pack.h>
#include <stb_image.h>
#include <infra/StringOps.h>
#include <infra/File.h>
#include <math/Interp.h>
#include <math/ImageAtlas.h>
#endif

#include <cstring>

namespace mud
{
	void load_folder_images(vector<Image>& images, const string& path, const string& subfolder)
	{
		auto visit_file = [&](const string& file)
		{
			string fullpath = path + "/" + file;
			string name = subfolder + replace(file, ".png", "");

			int width, height, n;
			unsigned char* img = stbi_load(fullpath.c_str(), &width, &height, &n, 4);
			stbi_image_free(img);
			images.push_back({ name, fullpath, { uint(width), uint(height) } });
		};

		visit_files(path, visit_file);
	}

	struct StbRectPack
	{
		StbRectPack(uvec2 size, size_t num_nodes)
			: m_nodes(num_nodes)
		{
			stbrp_init_target(&m_context, size.x, size.y, m_nodes.data(), int(num_nodes));
		}

		stbrp_context m_context;
		vector<stbrp_node> m_nodes;
	};

	ImageAtlas::ImageAtlas(uvec2 size)
		: m_size(size)
		, m_inverse_size(1.f / vec2(size))
		, m_image("ImageAtlas", "", m_size)
	{}

	ImageAtlas::~ImageAtlas()
	{}

	vector<unsigned char> ImageAtlas::generate_atlas(vector<Image*>& images)
	{
		size_t size = m_size.x * m_size.y * 4;
		vector<unsigned char> data(size, 0);

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

	bool ImageAtlas::place_image(Image& sprite)
	{
		stbrp_rect rect = { 0, stbrp_coord(sprite.d_size.x), stbrp_coord(sprite.d_size.y), 0, 0, false };
		int success = stbrp_pack_rects(&m_rect_pack->m_context, &rect, 1);
		if(success == 0)
			return false;

		sprite.d_coord = { uint(rect.x), uint(rect.y) };
		sprite.d_atlas = this;
		return true;
	}

	void ImageAtlas::blit_image(Image& sprite, vector<unsigned char>& data)
	{
		int width, height, n;
		stbi_set_unpremultiply_on_load(1);
		stbi_convert_iphone_png_to_rgb(1);
		unsigned char* sprite_data = stbi_load(sprite.d_path.c_str(), &width, &height, &n, 4);

		for(int y = 0; y < height; ++y)
		{
			size_t dest_offset = sprite.d_coord.x * 4 + (sprite.d_coord.y + y) * m_size.x * 4;
			memcpy(data.data() + dest_offset, sprite_data + y * width * 4, width * 4);
		}

		stbi_image_free(sprite_data);
	}

	TextureAtlas::TextureAtlas(uvec2 size)
		: ImageAtlas(size)
	{
		m_rect_pack = make_unique<StbRectPack>(size, size.x);
	}

	const Image& TextureAtlas::find_texture(cstring name) const
	{
		for(const Image& texture : m_textures)
			if(strcmp(texture.d_name.c_str(), name) == 0)
				return texture;
		return m_textures[0];
	}

	Image* TextureAtlas::add_texture(cstring name, uvec2 size)
	{
		if(m_textures.size() >= m_rect_pack->m_nodes.size())
			return nullptr;
		m_textures.push_back({ name, "", size });
		Image& texture = m_textures.back();
		if(!this->place_image(texture))
		{
			m_textures.pop_back();
			return nullptr;
		}
		return &texture;
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
			vec4 uv = { vec2(m_frame_coords[i]) * atlas_inverse_size,
						vec2(m_frame_coords[i] + m_frame_size) * atlas_inverse_size };
			m_frame_uvs.push_back(uv);
		}
	}

	SpriteAtlas::SpriteAtlas(uvec2 size)
		: ImageAtlas(size)
	{
		m_rect_pack = make_unique<StbRectPack>(size, size.x);
	}

	const Sprite& SpriteAtlas::find_sprite(cstring name) const
	{
		for(const Sprite& sprite : m_sprites)
			if(strcmp(sprite.d_name.c_str(), name) == 0)
				return sprite;
		return m_sprites[0];
	}

	Sprite* SpriteAtlas::add_sprite(cstring name, uvec2 size, uvec2 frames)
	{
		if(m_sprites.size() >= m_rect_pack->m_nodes.size())
			return nullptr;
		m_sprites.push_back({ name, "", size, frames });
		Sprite& sprite = m_sprites.back();
		if(!this->place_image(sprite))
		{
			m_sprites.pop_back();
			return nullptr;
		}
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
