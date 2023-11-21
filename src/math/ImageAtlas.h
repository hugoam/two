//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <math/Forward.h>
#include <math/Image.h>

class GuillotineBinPack;

namespace two
{
	struct StbRectPack;

	export_ TWO_MATH_EXPORT void load_folder_images(vector<Image>& images, const string& path, const string& subfolder);

	export_ class refl_ TWO_MATH_EXPORT ImageAtlas
	{
	public:
		ImageAtlas(uvec2 size);
		~ImageAtlas();

		vector<unsigned char> generate_atlas(span<Image*> images);

		bool place_image(Image& image);
		void blit_image(Image& image, vector<unsigned char>& data);

	public:
		uvec2 m_size;
		vec2 m_inverse_size;

		Image m_image;
		vector<Image*> m_images;

	protected:
		//unique<GuillotineBinPack> m_rect_pack;
		unique<StbRectPack> m_rect_pack;
	};

	export_ class refl_ TWO_MATH_EXPORT TextureAtlas : public ImageAtlas
	{
	public:
		TextureAtlas(uvec2 size);

		const Image& find_texture(cstring name) const;
		Image* add_texture(cstring name, uvec2 size);

		vector<Image> m_textures;
	};

	export_ class refl_ TWO_MATH_EXPORT Sprite : public Image
	{
	public:
		Sprite();
		Sprite(cstring name, cstring path, const uvec2& size, const uvec2& frames = uvec2(0U));

		void compute_frames(const vec2& atlas_inverse_size);

		uvec2 m_frames;
		uint m_num_frames;
		uvec2 m_frame_size;
		vector<uvec2> m_frame_coords;
		vector<vec4> m_frame_uvs;
	};

	export_ class refl_ TWO_MATH_EXPORT SpriteAtlas : public ImageAtlas
	{
	public:
		SpriteAtlas(uvec2 size);

		const Sprite& find_sprite(cstring name) const;
		Sprite* add_sprite(cstring name, const uvec2& size, uvec2 frames = uvec2(0U));

		vec4 sprite_uv(const Sprite& sprite, uint32_t frame) const;
		vec4 sprite_uv(const Sprite& sprite, float t) const;

		vector<Sprite> m_sprites;
	};
}
