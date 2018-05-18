//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Unique.h>
#include <math/Vec.h>
#include <ui/Generated/Forward.h>
#include <ui/Image.h>

#include <vector>

class GuillotineBinPack;

namespace mud
{
	struct StbRectPack;

	class _refl_ MUD_UI_EXPORT ImageAtlas
	{
	public:
		ImageAtlas(uvec2 size);
		~ImageAtlas();

		void create_atlas();
		std::vector<unsigned char> generate_atlas(std::vector<Image*>& images);

		void place_image(Image& image);
		void blit_image(Image& image, std::vector<unsigned char>& data);

	public:
		uvec2 m_size;
		vec2 m_inverse_size;

		Image m_image;
		std::vector<Image*> m_images;

	protected:
		//unique_ptr<GuillotineBinPack> m_rect_pack;
		unique_ptr<StbRectPack> m_rect_pack;
	};

	class _refl_ MUD_UI_EXPORT Sprite : public Image
	{
	public:
		Sprite();
		Sprite(cstring name, cstring path, const uvec2& size, const uvec2& frames = uvec2(0U));

		void compute_frames(const vec2& atlas_inverse_size);

		uvec2 m_frames;
		size_t m_num_frames;
		uvec2 m_frame_size;
		std::vector<uvec2> m_frame_coords;
		std::vector<vec4> m_frame_uvs;
	};

	class _refl_ MUD_UI_EXPORT SpriteAtlas : public ImageAtlas
	{
	public:
		SpriteAtlas(uvec2 size);

		const Sprite& find_sprite(cstring name) const;
		Sprite* add_sprite(cstring name, uvec2 size, uvec2 frames = uvec2(0U));

		vec4 sprite_uv(const Sprite& sprite, uint32_t frame) const;
		vec4 sprite_uv(const Sprite& sprite, float t) const;

		std::vector<Sprite> m_sprites;
	};
}
