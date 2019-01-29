#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.math;
#else
#endif

namespace mud
{
	Colour Colour::Black(0.f, 0.f, 0.f);
	Colour Colour::AlphaBlack(0.f, 0.f, 0.f, 0.5f);
	Colour Colour::Red(1.f, 0.f, 0.f);
	Colour Colour::Green(0.f, 1.f, 0.f);
	Colour Colour::NeonGreen(0.f, 1.f, 0.2f);
	Colour Colour::Blue(0.f, 0.f, 1.f);
	Colour Colour::Pink(1.f, 0.2f, 1.f);
	Colour Colour::Cyan(0.f, 1.f, 1.f);
	Colour Colour::Yellow(1.f, 1.f, 0.f);
	Colour Colour::White(1.f, 1.f, 1.f);
	Colour Colour::AlphaWhite(1.f, 1.f, 1.f, 0.5f);
	Colour Colour::LightGrey(0.6f, 0.6f, 0.6f);
	Colour Colour::MidGrey(0.45f, 0.45f, 0.45f);
	Colour Colour::DarkGrey(0.3f, 0.3f, 0.3f);
	Colour Colour::AlphaGrey(0.45f, 0.45f, 0.45f, 0.5f);
	Colour Colour::Transparent(0.f, 0.f, 0.f, 0.f);
	Colour Colour::Invisible(0.f, 0.f, 0.f, 0.0001f);
	Colour Colour::None(0.f, 0.f, 0.f, 0.f);

	Colour::Colour()
		: m_r(1.f), m_g(1.f), m_b(1.f), m_a(1.f)
	{}

	Colour::Colour(float v, float a)
		: m_r(v), m_g(v), m_b(v), m_a(a)
	{}

	Colour::Colour(float r, float g, float b, float a)
		: m_r(r), m_g(g), m_b(b), m_a(a)
	{}

	Colour Colour::hsl(float h, float s, float l)
	{
		return hsl_to_rgb(h, s, l);
	}

	Colour clamp_colour(const Colour& colour)
	{
#ifdef MUD_PLATFORM_EMSCRIPTEN
		Colour clamped = colour;
		for(size_t i = 0; i < 4; ++i)
			clamped[i] = clamp(colour[i], 0.f, 1.f);
		return clamped;
#else
		return colour;
#endif
	}

	uint32_t to_rgba(const Colour& colour)
	{
		Colour col = clamp_colour(colour);
		uint32_t rgba = 0;
		rgba |= uint8_t(col.m_r * 255.f) << 24;
		rgba |= uint8_t(col.m_g * 255.f) << 16;
		rgba |= uint8_t(col.m_b * 255.f) << 8;
		rgba |= uint8_t(col.m_a * 255.f);
		return rgba;
	}

	uint32_t to_abgr(const Colour& colour)
	{
		Colour col = clamp_colour(colour);
		uint32_t rgba = 0;
		rgba |= uint8_t(col.m_r * 255.f);
		rgba |= uint8_t(col.m_g * 255.f) << 8;
		rgba |= uint8_t(col.m_b * 255.f) << 16;
		rgba |= uint8_t(col.m_a * 255.f) << 24;
		return rgba;
	}

	Colour from_rgba(uint32_t rgba)
	{
		Colour colour;
		colour.m_r =  (rgba >> 24) / 255.f;
		colour.m_g = ((rgba >> 16) & 0xFF) / 255.f;
		colour.m_b = ((rgba >> 8) & 0xFF) / 255.f;
		colour.m_a = ((rgba >> 0) & 0xFF) / 255.f;
		return colour;
	}

	Colour from_abgr(uint32_t abgr)
	{
		Colour colour;
		colour.m_r = ((abgr >> 0)  & 0xFF) / 255.f;
		colour.m_g = ((abgr >> 8)  & 0xFF) / 255.f;
		colour.m_b = ((abgr >> 16) & 0xFF) / 255.f;
		colour.m_a =  (abgr >> 24) / 255.f;
		return colour;
	}

	inline float to_linear(float value)
	{
		return value < 0.04045 ? float(value * (1.0 / 12.92)) : float(pow((value + 0.055) * (1.0 / (1 + 0.055)), 2.4));
	}

	inline float to_gamma(float value)
	{
		return value > 0.0031308 ? float(value * 12.92) : float(pow(abs(value), 1.0 / 2.4) * 1.055 - 0.055);
	}

	Colour to_linear(const Colour& colour)
	{
		return Colour(to_linear(colour.m_r), to_linear(colour.m_g), to_linear(colour.m_b), colour.m_a);
	}

	Colour to_gamma(const Colour& colour)
	{
		return Colour(to_gamma(colour.m_r), to_gamma(colour.m_g), to_gamma(colour.m_b), colour.m_a);
	}

	Colour to_srgb(const Colour& colour)
	{
		return Colour(to_gamma(colour.m_r), to_gamma(colour.m_g), to_gamma(colour.m_b), colour.m_a);
	}

	float hue_to_rgb(float p, float q, float t)
	{
		if(t < 0.f) t += 1.f;
		if(t > 1.f) t -= 1.f;
		if(t < 1.f / 6.f) return p + (q - p) * 6.f * t;
		if(t < 1.f / 2.f) return q;
		if(t < 2.f / 3.f) return p + (q - p) * (2.f / 3.f - t) * 6.f;
		return p;
	}

	Colour hsl_to_rgb(float h, float s, float l)
	{
		float r, g, b;

		if(s == 0.f)
		{
			r = g = b = l; // achromatic
		}
		else
		{
			float q = l < 0.5f ? l * (1.f + s) : l + s - l * s;
			float p = 2.f * l - q;
			r = hue_to_rgb(p, q, h + 1.f / 3.f);
			g = hue_to_rgb(p, q, h);
			b = hue_to_rgb(p, q, h - 1.f / 3.f);
		}
		return { r, g, b };
	}

	Colour hsla_to_rgba(const Colour& colour)
	{
		return hsl_to_rgb(colour.m_h, colour.m_s, colour.m_l);
	}

	Colour rgb_to_hsl(float r, float g, float b)
	{
		float lmax = max(r, max(g, b));
		float lmin = min(r, min(g, b));
		float h, s, l;
		h = s = l = (lmax + lmin) / 2.f;

		if(lmax == lmin)
		{
			h = s = 0.f; // achromatic
		}
		else
		{
			float d = lmax - lmin;
			s = l > 0.5f ? d / (2.f - lmax - lmin) : d / (lmax + lmin);
			if(lmax == r) h = (g - b) / d + (g < b ? 6.f : 0.f);
			if(lmax == g) h = (b - r) / d + 2.f;
			if(lmax == b) h = (r - g) / d + 4.f;
			h /= 6.f;
		}

		return { h, s, l };
	}

	Colour rgba_to_hsla(const Colour& colour)
	{
		return rgb_to_hsl(colour.m_r, colour.m_g, colour.m_b);
	}
}


#ifdef MUD_MODULES
module mud.math;
#else
#endif

namespace mud
{
	template <class T>
	ValueCurve<T>::ValueCurve() {}
	template <class T>
	ValueCurve<T>::ValueCurve(vector<T> keys) : m_keys(keys) {}
	template <class T>
	ValueCurve<T>::~ValueCurve() {}

	template <class T>
	T ValueCurve<T>::sample_curve(float t)
	{
		uint32_t key = uint32_t(t * (m_keys.size() - 1));
		float interval = 1.f / float(m_keys.size() - 1);
		float ttmod = fmod(t, interval) / interval;

		return mud::lerp(m_keys[key], m_keys[key + 1], ttmod);
	}

	template struct MUD_MATH_EXPORT ValueCurve<vec3>;
	template struct MUD_MATH_EXPORT ValueCurve<quat>;
	template struct MUD_MATH_EXPORT ValueCurve<float>;
	template struct MUD_MATH_EXPORT ValueCurve<uint32_t>;
	template struct MUD_MATH_EXPORT ValueCurve<Colour>;

	template <class T>
	ValueTrack<T>::ValueTrack() {}
	template <class T>
	ValueTrack<T>::ValueTrack(TrackMode mode, ValueCurve<T> curve, ValueCurve<T> min_curve, ValueCurve<T> max_curve) : m_mode(mode), m_curve(curve), m_min_curve(min_curve), m_max_curve(max_curve) {}
	template <class T>
	ValueTrack<T>::ValueTrack(T value) : m_mode(TrackMode::Constant), m_value(value) {}
	template <class T>
	ValueTrack<T>::ValueTrack(T min, T max) : m_mode(TrackMode::ConstantRandom), m_min(min), m_max(max) {}
	template <class T>
	ValueTrack<T>::ValueTrack(vector<T> values) : m_mode(TrackMode::Curve), m_curve(values) {}
	template <class T>
	ValueTrack<T>::ValueTrack(vector<T> min_values, vector<T> max_values) : m_mode(TrackMode::CurveRandom), m_min_curve(min_values), m_max_curve(max_values) {}
	template <class T>
	ValueTrack<T>::~ValueTrack() {}

	template <class T>
	void ValueTrack<T>::set_mode(TrackMode mode)
	{
		if (mode == TrackMode::Constant)
			*this = ValueTrack<T>(T());
		else if (mode == TrackMode::ConstantRandom)
			*this = ValueTrack<T>(T(), T());
		else if (mode == TrackMode::Curve)
			*this = ValueTrack<T>(vector<T>(2, T()));
		else if (mode == TrackMode::CurveRandom)
			*this = ValueTrack<T>(vector<T>(2, T()), vector<T>(2, T()));
	}

	template <class T>
	T ValueTrack<T>::sample(float t, float seed)
	{
		if (m_mode == TrackMode::Constant)
			return m_value;
		else if (m_mode == TrackMode::ConstantRandom)
			return mud::lerp(m_min, m_max, seed);
		else if (m_mode == TrackMode::Curve)
			return m_value * m_curve.sample_curve(t);
		else //if(m_mode == TrackMode::CurveRandom)
			return mud::lerp(m_min * m_min_curve.sample_curve(t), m_max * m_max_curve.sample_curve(t), seed);
	}

	template struct MUD_MATH_EXPORT ValueTrack<vec3>;
	template struct MUD_MATH_EXPORT ValueTrack<quat>;
	template struct MUD_MATH_EXPORT ValueTrack<float>;
	template struct MUD_MATH_EXPORT ValueTrack<uint32_t>;
	template struct MUD_MATH_EXPORT ValueTrack<Colour>;
}

#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#endif

using namespace mud;
namespace tinystl
{
	template class MUD_MATH_EXPORT vector<const char*>;
	template class MUD_MATH_EXPORT vector<char>;
	template class MUD_MATH_EXPORT vector<uchar>;
	template class MUD_MATH_EXPORT vector<ushort>;
	template class MUD_MATH_EXPORT vector<uint>;
	template class MUD_MATH_EXPORT vector<ulong>;
	template class MUD_MATH_EXPORT vector<long>;
	template class MUD_MATH_EXPORT vector<llong>;
	template class MUD_MATH_EXPORT vector<ullong>;
	template class MUD_MATH_EXPORT vector<float>;
	template class MUD_MATH_EXPORT vector<uvec2>;
	template class MUD_MATH_EXPORT vector<uvec3>;
	template class MUD_MATH_EXPORT vector<ivec2>;
	template class MUD_MATH_EXPORT vector<ivec3>;
	template class MUD_MATH_EXPORT vector<ivec4>;
	template class MUD_MATH_EXPORT vector<vec2>;
	template class MUD_MATH_EXPORT vector<vec3>;
	template class MUD_MATH_EXPORT vector<vec4>;
	template class MUD_MATH_EXPORT vector<quat>;
	template class MUD_MATH_EXPORT vector<mat4>;
	template class MUD_MATH_EXPORT vector<Colour>;
	template class MUD_MATH_EXPORT vector<Image>;
	template class MUD_MATH_EXPORT vector<Sprite>;
	template class MUD_MATH_EXPORT unordered_map<Type*, Colour>;

	template class MUD_MATH_EXPORT vector<stbrp_node>;
}

#ifndef MUD_CPP_20
#include <cstring>
#include <cstdio>
#endif

#ifdef MUD_MODULES
module mud.math;
#else
#endif

namespace mud
{
	Palette::Palette()
		: m_colours()
	{}

	Palette::Palette(vector<Colour> colours)
		: m_colours(colours)
	{}

	Palette::Palette(Spectrum spectrum, size_t steps)
		: m_colours()
	{
		if(spectrum == Spectrum::Value)
			this->value_spectrum(steps);
		else if(spectrum == Spectrum::Hue)
			this->hue_spectrum(steps);
	}

	void Palette::value_spectrum(size_t steps, bool to_white)
	{
		for(size_t i = 0; i < steps; ++i)
		{
			float r = float(i) / float(steps - 1);
			float l = to_white ? r : 1.f - r;
			m_colours.push_back(Colour(l, l, l));
		}
	}

	void Palette::hue_spectrum(size_t steps)
	{
		for(size_t i = 0; i < steps; ++i)
		{
			float h = float(i) / float(steps - 1);
			m_colours.push_back(hsl_to_rgb(h, 0.5f, 0.5f));
		}
	}

	void Palette::reset()
	{
		m_colours.clear();
	}

	void Palette::load(cstring file)
	{
		FILE* fpalette = fopen(file, "r");
		for(size_t i = 0; i < 256U; i++)
		{
			uint8_t cl1, cl2, cl3;
			fread(&cl1, sizeof(uint8_t), 1, fpalette);
			fread(&cl2, sizeof(uint8_t), 1, fpalette);
			fread(&cl3, sizeof(uint8_t), 1, fpalette);
			m_colours.push_back(Colour(cl3, cl2, cl1));
		}
		fclose(fpalette);
	}

	void Palette::add(Colour colour)
	{
		m_colours.push_back(colour);
	}

	size_t Palette::find_colour(const Colour& search)
	{
		for(size_t i = 0; i < m_colours.size(); i++)
			if(m_colours[i] == search)
				return i;
		return 0;
	}

	Image256::Image256(uint16_t width, uint16_t height, const Palette& palette)
		: m_pixels(width * height)
		, m_width(width)
		, m_height(height)
		, m_palette(palette)
	{}

	bool Image256::operator==(const Image256& other) const
	{
		UNUSED(other);
		return false;
	}

	void Image256::resize(uint16_t w, uint16_t h)
	{
		m_width = w;
		m_height = h;
		m_pixels.resize(m_width * m_height);
	}

	void Image256::read(uint8_t* data) const
	{
		size_t index = 0;
		for(size_t y = 0; y < m_height; ++y)
			for(size_t x = 0; x < m_width; ++x, ++index)
			{
				size_t colid = m_pixels[index];
				Colour color = /*colid == 16 ? Colour() :*/ m_palette.m_colours[colid];

				*data++ = static_cast<uint8_t>(color.m_r * 255);
				*data++ = static_cast<uint8_t>(color.m_g * 255);
				*data++ = static_cast<uint8_t>(color.m_b * 255);
				*data++ = 255;
			}
	}

	vector<uint8_t> Image256::read() const
	{
		vector<uint8_t> data(m_width * m_height * 4);
		this->read(&data[0]);
		return data;
	}
}


#ifdef MUD_MODULES
module mud.ui;
#else
#include <stb_rect_pack.h>
#include <stb_image.h>
#endif

#include <algorithm>
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
			std::copy(sprite_data + y * width * 4, sprite_data + (y + 1) * width * 4, data.data() + dest_offset);
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
			vec4 uv = { vec2{ m_frame_coords[i] } * atlas_inverse_size,
						vec2{ m_frame_coords[i] + m_frame_size } * atlas_inverse_size };
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


#ifdef MUD_MODULES
module mud.math;
#else
#endif

namespace mud
{
	Lerp::Lerp()
	{
		dispatch_branch<int>(*this, +[](int& value, Ref source, Ref dest, float ratio) { value = lerp(val<int>(source), val<int>(dest), ratio); });
		dispatch_branch<float>(*this, +[](float& value, Ref source, Ref dest, float ratio) { value = lerp(val<float>(source), val<float>(dest), ratio); });
		dispatch_branch<double>(*this, +[](double& value, Ref source, Ref dest, float ratio) { value = lerp(val<double>(source), val<double>(dest), ratio); });
		dispatch_branch<vec3>(*this, +[](vec3& value, Ref source, Ref dest, float ratio) { value = lerp(val<vec3>(source), val<vec3>(dest), ratio); });
		dispatch_branch<quat>(*this, +[](quat& value, Ref source, Ref dest, float ratio) { value = slerp(val<quat>(source), val<quat>(dest), ratio); });
	}
}


#ifdef MUD_MODULES
#include <cstdlib>
module mud.math;
#else
#endif

namespace mud
{
#ifndef M_PI
	const float c_pi = 3.14159265358979323846f;
#else
	const float c_pi = M_PI;
#endif

	void register_math_conversions()
	{
#if 0
		dispatch_branch<float, vec3, copy_convert<float, vec3>>(TypeConverter::me());
		TypeConverter::me().default_converter<vec3, ivec3>();
		TypeConverter::me().default_converter<vec3, uvec3>();
#endif
	}

	const vec3 X3 = { 1.f, 0.f, 0.f };
	const vec3 Y3 = { 0.f, 1.f, 0.f };
	const vec3 Z3 = { 0.f, 0.f, 1.f };

	const vec3 Zero3 = { 0.f, 0.f, 0.f };
	const vec3 Unit3 = { 1.f, 1.f, 1.f };

	const Side c_sides[6] = { Side::Right, Side::Left, Side::Up, Side::Down, Side::Back, Side::Front };

	const vec3 c_axes[3]			 = {  X3,  Y3,  Z3 };
	const vec3 c_tangents[6]		 = {  Y3,  Z3,  Y3 };
	const vec3 c_binormals[6]		 = {  Z3,  X3,  X3 };

	const vec3 c_dirs[6]			 = {  X3, -X3,  Y3, -Y3,  Z3, -Z3 };
	const vec3 c_dirs_tangents[6]	 = {  Y3, -Z3, -Z3,  X3,  Y3,  X3 };
	const vec3 c_dirs_normals[6]	 = { -Z3,  Y3,  X3, -Z3,  X3,  Y3 };

	const quat ZeroQuat = { 0.f, 0.f, 0.f, 1.f };

	const vec2 Zero2 = { 0.f, 0.f };
	const vec2 Unit2 = { 1.f, 1.f };

	const vec4 Zero4 = { 0.f, 0.f, 0.f, 0.f };
	const vec4 Rect4 = { 0.f, 0.f, 1.f, 1.f };

	quat average_quat(quat& cumulative, const quat& rotation, const quat& first, uint32_t count)
	{
		if(dot(rotation, first) < 0.f)
			return average_quat(cumulative, inverse(rotation), first, count);

		float factor = 1.f / float(count);
		cumulative += rotation;
		return normalize(cumulative * factor);
	}

	Transform average_transforms(array<Transform*> transforms)
	{
		Transform average;
		average.m_scale = Zero3;

		quat cumulative = { 0.f, 0.f, 0.f, 0.f };

		uint32_t count = 0;
		for(Transform* transform : transforms)
		{
			average.m_position += transform->m_position;
			average.m_scale += transform->m_scale;
			average.m_rotation = average_quat(cumulative, transform->m_rotation, transforms[0]->m_rotation, ++count);
		}
		average.m_position = average.m_position / float(transforms.size());
		average.m_scale = average.m_scale / float(transforms.size());

		return average;
	}

	float nsinf(float a) { return (sinf(a) + 1.f) / 2.f; } // @kludge can't be inline because we identify reflected functions through their pointer 
	float ncosf(float a) { return (cosf(a) + 1.f) / 2.f; }

	double nsin(double a) { return (sin(a) + 1.0) / 2.0; }
	double ncos(double a) { return (cos(a) + 1.0) / 2.0; }

	quat look_dir(const vec3& direction, const vec3& forward)
	{
		float d = dot(forward, direction);

		if(abs(d - (-1.0f)) < 0.000001f)
			return axis_angle(Y3, c_pi);
		if(abs(d - (1.0f)) < 0.000001f)
			return ZeroQuat;

		vec3 axis = normalize(cross(-Z3, direction));
		return axis_angle(axis, acos(d));
	}

	quat look_at(const vec3& source, const vec3& dest, const vec3& forward)
	{
		vec3 direction = normalize(dest - source);
		return look_dir(direction, forward);
	}

	uint32_t pack4(const vec4& colour)
	{
		vec4 clamped = clamp(colour * 255.f, 0.f, 255.f);
		uint32_t rgba = 0;
		rgba |= uint32_t(clamped[0]) << 24;
		rgba |= uint32_t(clamped[1]) << 16;
		rgba |= uint32_t(clamped[2]) << 8;
		rgba |= uint32_t(clamped[3]);
		return rgba;
	}

	uint32_t pack3(const vec3& colour)
	{
		vec3 clamped = clamp(colour * 255.f, 0.f, 255.f);
		uint32_t rgb = 0;
		rgb |= uint32_t(clamped[0]) << 16;
		rgb |= uint32_t(clamped[1]) << 8;
		rgb |= uint32_t(clamped[2]) << 0;
		return rgb;
	}

	vec3 unpack3(uint32_t rgb)
	{
		float x = ((rgb >> 16) & 0xFF) / 255.f;
		float y = ((rgb >> 8) & 0xFF) / 255.f;
		float z = ((rgb >> 0) & 0xFF) / 255.f;
		return { x, y, z };
	}

	vec4 unpack4(uint32_t rgba)
	{
		float x = (rgba >> 24) / 255.f;
		float y = ((rgba >> 16) & 0xFF) / 255.f;
		float z = ((rgba >> 8) & 0xFF) / 255.f;
		float w = ((rgba >> 0) & 0xFF) / 255.f;
		return { x, y, z, w };
	}

	Axis nearest_axis(const vec3& direction)
	{
		Axis axis = Axis::X;

		float closest_dot = 0.f;
		for(Axis a : { Axis::X, Axis::Y, Axis::Z })
		{
			float product = abs(dot(direction, to_vec3(a)));
			if(a == Axis::X || product > closest_dot)
			{
				axis = a;
				closest_dot = product;
			}
		}

		return axis;
	}

	float float_shortest_angle(float angle1, float angle2)
	{
		return min((2.f * c_pi) - abs(angle1 - angle2), abs(angle1 - angle2));
	}

	float trigo_angle(const vec3& vec1, const vec3& vec2)
	{
		float angle = shortest_angle(vec1, vec2);
		
		if(angle < 0)
			angle += 2 * c_pi;

		return angle;
	}

	float shortest_angle(const vec3& vec1, const vec3& vec2)
	{
		return oriented_angle(vec1, vec2, Y3);
	}

#if 0
	float shortest_angle(const vec3& vec1, const vec3& vec2)
	{
		float a = angle(vec1, vec2);
		if(a == 0.f) return a;

		vec3 clockwise = rotate(vec1, a, Y3);
		flatten(clockwise);

		if(angle(vec2, clockwise) > 0.001f)
			a = -a;

		return a;
	}
#endif

	void orthonormalize(const mat4& transform, vec3& x, vec3& y, vec3& z)
	{
		// Gram-Schmidt Process

		x = { transform[0].x, transform[1].x, transform[2].x };
		y = { transform[0].y, transform[1].y, transform[2].y };
		z = { transform[0].z, transform[1].z, transform[2].z };

		x = normalize(x);
		y = (y - x * (dot(x, y)));
		y = normalize(y);
		z = (z - x * (dot(x, z)) - y * (dot(y, z)));
		z = normalize(z);
	}

	mat4 orthonormalize(const mat4& transform)
	{
		vec3 x, y, z;
		orthonormalize(transform, x, y, z);

		mat4 result = transform;
		result[0].x = x[0]; result[1].x = x[1]; result[1].x = x[1];
		result[0].y = y[0]; result[1].y = y[1]; result[1].y = y[1];
		result[0].z = z[0]; result[1].z = z[1]; result[1].z = z[1];

		return result;
	}

	mat4 bias_mat()
	{
		return {
			0.5f, 0.f,  0.f,  0.f,
			0.f,  0.5f, 0.f,  0.f,
			0.f,  0.f,  0.5f, 0.f,
			0.5f, 0.5f, 0.5f, 1.f
		};
	}

	mat4 bias_mat_bgfx(bool origin_bottom_left, bool homogeneous_depth)
	{
		const float sy = origin_bottom_left ? 0.5f : -0.5f;
		const float sz = homogeneous_depth ? 0.5f : 1.0f;
		const float tz = homogeneous_depth ? 0.5f : 0.0f;
		return {
			0.5f, 0.0f, 0.0f, 0.0f,
			0.0f, sy,   0.0f, 0.0f,
			0.0f, 0.0f, sz,   0.0f,
			0.5f, 0.5f, tz,   1.0f,
		};
	}

	mat4 rect_mat(vec4 rect)
	{
		return
		{
			rect_w(rect), 0.f, 0.f, 0.f,
			0.f, rect_h(rect), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			rect.x, rect.y, 0.f, 1.f
		};
	}

	mat4 abs(const mat4& mat)
	{
		mat4 result;
		for(mat4::length_type i = 0; i < 4; ++i)
			for(mat4::length_type j = 0; j < 4; ++j)
				result[i][j] = abs(mat[i][j]);
		return result;
	}

	void grid(const uvec3& size, vector<uvec3>& output_coords)
	{
		for(uint z = 0; z < size.z; ++z)
			for(uint y = 0; y < size.y; ++y)
				for(uint x = 0; x < size.x; ++x)
					output_coords.push_back({ x, y, z });
	}

	vec3 grid_center(const uvec3& coord, float cell_size)
	{
		return vec3(coord) * cell_size + cell_size * 0.5f;
	}

	vec3 grid_center(const uvec3& coord, const vec3& cell_size)
	{
		return vec3(coord) * cell_size + cell_size * 0.5f;
	}

	void index_list(uint32_t size, vector<uint32_t>& output_indices)
	{
		for(uint32_t i = 0; i < size; ++i)
			output_indices.push_back(i);
	}
}

#ifndef MUD_CPP_20
#include <random>
#endif

#ifdef MUD_MODULES
module mud.math;
#else
#endif

namespace mud
{
	template <class T>
	T random_integer(T min, T max)
	{
		static std::random_device device;
		static std::mt19937 generator(device());
		std::uniform_int_distribution<T> distribution(min, max);
		return distribution(generator);
	}

	template <class T>
	T random_scalar(T min, T max)
	{
		static std::random_device device;
		static std::mt19937 generator(device());
		std::uniform_real_distribution<T> distribution(min, max);
		return distribution(generator);
	}

	template <class T>
	T random_scalar()
	{
		static std::random_device device;
		static std::mt19937 generator(device());
		static std::uniform_real_distribution<T> distribution { T(0), T(1) };
		return distribution(generator);
	}

	template MUD_MATH_EXPORT float random_scalar<float>();
	template MUD_MATH_EXPORT double random_scalar<double>();

	template MUD_MATH_EXPORT float random_scalar<float>(float min, float max);
	template MUD_MATH_EXPORT double random_scalar<double>(double min, double max);

	template MUD_MATH_EXPORT int random_integer<int>(int min, int max);
	template MUD_MATH_EXPORT uint random_integer<uint>(uint min, uint max);
	template MUD_MATH_EXPORT ulong random_integer<ulong>(ulong min, ulong max);
	template MUD_MATH_EXPORT ullong random_integer<ullong>(ullong min, ullong max);
}


#ifdef MUD_MODULES
module mud.math;
#else
#endif

namespace mud
{
#if 0
	Ratio::Ratio(float value)
		: Stat<float>(m_value, def())
		, m_value(value)
	{}

	Gauge::Gauge(float value)
		: Stat<float>(m_value, def())
		, m_value(value)
	{}
#endif

	template struct MUD_MATH_EXPORT StatDef<int>;
	template struct MUD_MATH_EXPORT StatDef<float>;

	template struct MUD_MATH_EXPORT Stat<int>;
	template struct MUD_MATH_EXPORT Stat<float>;

	template struct MUD_MATH_EXPORT AutoStat<int>;
	template struct MUD_MATH_EXPORT AutoStat<float>;
}


#ifdef MUD_MODULES
module mud.infra;
#else
#endif

namespace mud
{
	const double c_tick_interval = 0.02;

    Clock::Clock()
        : m_last(clock())
		, m_last_tick(0)
    {}

    void Clock::update()
    {
		m_last = clock();
    }

	size_t Clock::readTick()
	{
		return size_t(this->read() / c_tick_interval);
	}

	size_t Clock::stepTick()
	{
		size_t tick = this->readTick();
		size_t delta = tick - m_last_tick;

		m_last_tick = tick;
		return delta;
	}

    double Clock::read()
    {
        double timeStep = static_cast<double>(clock() - m_last) / CLOCKS_PER_SEC;
        return timeStep;
    }

	double Clock::step()
	{
		double step = this->read();
		this->update();
		return step;
	}
}

#ifdef MUD_MODULES
module mud.math;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_MATH_EXPORT Type& type<mud::Axes>() { static Type ty("mud::Axes", sizeof(mud::Axes)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Axis>() { static Type ty("mud::Axis", sizeof(mud::Axis)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Clockwise>() { static Type ty("mud::Clockwise", sizeof(mud::Clockwise)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Side>() { static Type ty("mud::Side", sizeof(mud::Side)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::SignedAxis>() { static Type ty("mud::SignedAxis", sizeof(mud::SignedAxis)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Spectrum>() { static Type ty("mud::Spectrum", sizeof(mud::Spectrum)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::TrackMode>() { static Type ty("mud::TrackMode", sizeof(mud::TrackMode)); return ty; }
    
    template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<float>>() { static Type ty("AutoStat<float>", sizeof(mud::AutoStat<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::AutoStat<int>>() { static Type ty("AutoStat<int>", sizeof(mud::AutoStat<int>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Colour>() { static Type ty("Colour", sizeof(mud::Colour)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Image>() { static Type ty("Image", sizeof(mud::Image)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Image256>() { static Type ty("Image256", sizeof(mud::Image256)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ImageAtlas>() { static Type ty("ImageAtlas", sizeof(mud::ImageAtlas)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Palette>() { static Type ty("Palette", sizeof(mud::Palette)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<float>>() { static Type ty("Range<float>", sizeof(mud::Range<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::Colour>>() { static Type ty("Range<mud::Colour>", sizeof(mud::Range<mud::Colour>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::quat>>() { static Type ty("Range<mud::quat>", sizeof(mud::Range<mud::quat>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<mud::vec3>>() { static Type ty("Range<mud::vec3>", sizeof(mud::Range<mud::vec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Range<uint32_t>>() { static Type ty("Range<uint32_t>", sizeof(mud::Range<uint32_t>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Time>() { static Type ty("Time", sizeof(mud::Time)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::TimeSpan>() { static Type ty("TimeSpan", sizeof(mud::TimeSpan)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Transform>() { static Type ty("Transform", sizeof(mud::Transform)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<float>>() { static Type ty("ValueCurve<float>", sizeof(mud::ValueCurve<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::Colour>>() { static Type ty("ValueCurve<mud::Colour>", sizeof(mud::ValueCurve<mud::Colour>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::quat>>() { static Type ty("ValueCurve<mud::quat>", sizeof(mud::ValueCurve<mud::quat>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<mud::vec3>>() { static Type ty("ValueCurve<mud::vec3>", sizeof(mud::ValueCurve<mud::vec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueCurve<uint32_t>>() { static Type ty("ValueCurve<uint32_t>", sizeof(mud::ValueCurve<uint32_t>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<float>>() { static Type ty("ValueTrack<float>", sizeof(mud::ValueTrack<float>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::Colour>>() { static Type ty("ValueTrack<mud::Colour>", sizeof(mud::ValueTrack<mud::Colour>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::quat>>() { static Type ty("ValueTrack<mud::quat>", sizeof(mud::ValueTrack<mud::quat>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<mud::vec3>>() { static Type ty("ValueTrack<mud::vec3>", sizeof(mud::ValueTrack<mud::vec3>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ValueTrack<uint32_t>>() { static Type ty("ValueTrack<uint32_t>", sizeof(mud::ValueTrack<uint32_t>)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::bvec3>() { static Type ty("bvec3", sizeof(mud::bvec3)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::bvec4>() { static Type ty("bvec4", sizeof(mud::bvec4)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::half2>() { static Type ty("half2", sizeof(mud::half2)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::half3>() { static Type ty("half3", sizeof(mud::half3)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ivec2>() { static Type ty("ivec2", sizeof(mud::ivec2)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ivec3>() { static Type ty("ivec3", sizeof(mud::ivec3)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::ivec4>() { static Type ty("ivec4", sizeof(mud::ivec4)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::mat4>() { static Type ty("mat4", sizeof(mud::mat4)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::quat>() { static Type ty("quat", sizeof(mud::quat)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::uvec2>() { static Type ty("uvec2", sizeof(mud::uvec2)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::uvec3>() { static Type ty("uvec3", sizeof(mud::uvec3)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::uvec4>() { static Type ty("uvec4", sizeof(mud::uvec4)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::vec2>() { static Type ty("vec2", sizeof(mud::vec2)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::vec3>() { static Type ty("vec3", sizeof(mud::vec3)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::vec4>() { static Type ty("vec4", sizeof(mud::vec4)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::Sprite>() { static Type ty("Sprite", type<mud::Image>(), sizeof(mud::Sprite)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::SpriteAtlas>() { static Type ty("SpriteAtlas", type<mud::ImageAtlas>(), sizeof(mud::SpriteAtlas)); return ty; }
    template <> MUD_MATH_EXPORT Type& type<mud::TextureAtlas>() { static Type ty("TextureAtlas", type<mud::ImageAtlas>(), sizeof(mud::TextureAtlas)); return ty; }
}


#ifdef MUD_MODULES
module mud.math;
#else
#endif

#include <json11.hpp>

namespace mud
{
	inline float jfloat(const json& j) { return float(j.number_value()); }

	void from_json(const json& j, vec3& vec)
	{
		vec = vec3(jfloat(j[0]), jfloat(j[1]), jfloat(j[2]));
	}

	void from_json(const json& j, quat& q)
	{
		q = quat(jfloat(j[0]), jfloat(j[1]), jfloat(j[2]), jfloat(j[3]));
	}

	void from_json(const json& j, mat4& mat)
	{
		mat = mat4(
			vec4(jfloat(j[0]),  jfloat(j[1]),  jfloat(j[2]),  jfloat(j[3])),
			vec4(jfloat(j[4]),  jfloat(j[5]),  jfloat(j[6]),  jfloat(j[7])),
			vec4(jfloat(j[8]),  jfloat(j[9]),  jfloat(j[10]), jfloat(j[11])),
			vec4(jfloat(j[12]), jfloat(j[13]), jfloat(j[14]), jfloat(j[15]))
		);
	}
}

namespace mud
{
	void from_json(const json& j, Colour& col)
	{
		col = Colour(float(j[0].number_value()), float(j[1].number_value()), float(j[2].number_value()), float(j[3].number_value()));
	}

	void to_json(const Colour& col, json& j)
	{
		vector<json> values;
		values = { col.m_r, col.m_g, col.m_b, col.m_a };
		j = values;
	}
}

#ifndef MUD_CPP_20
#include <limits>
#endif

#ifdef MUD_MODULES
#include <cstdlib>
module mud.math;
#else
#endif

#include <algorithm>

namespace mud
{
	template <class T>
	inline v2<T>::v2() { }
	template <class T>
	inline v2<T>::v2(T v) : x(v), y(v) {}
	template <class T>
	inline v2<T>::v2(T x, T y) : x(x), y(y) {}
	template <class T>
	template <class V>
	inline v2<T>::v2(V v) : x(T(v.x)), y(T(v.y)) {}
	template <class T>
	inline T v2<T>::operator[](uint index) const { return *((T*)&x + index); }
	template <class T>
	inline T& v2<T>::operator[](uint index) { return *((T*)&x + index); }
	template <class T>
	inline bool v2<T>::operator==(const v2& other) const { return x == other.x && y == other.y; }
	template <class T>
	inline bool v2<T>::operator!=(const v2& other) const { return x != other.x || y != other.y; }
	template <class T>
	inline v2<T>::operator T() { return T(x); }

	template <class T>
	inline v3<T>::v3() { }
	template <class T>
	inline v3<T>::v3(T v) : x(v), y(v), z(v) {}
	template <class T>
	inline v3<T>::v3(T x, T y, T z) : x(x), y(y), z(z) {}
	template <class T>
	inline v3<T>::v3(v2<T> a, T z) : x(a.x), y(a.y), z(z) {}
	template <class T>
	template <class V>
	inline v3<T>::v3(V v) : x(T(v.x)), y(T(v.y)), z(T(v.z)) {}
	template <class T>
	inline T v3<T>::operator[](uint index) const { return *((T*)&x + index); }
	template <class T>
	inline T& v3<T>::operator[](uint index) { return *((T*)&x + index); }
	template <class T>
	inline bool v3<T>::operator==(const v3& other) const { return x == other.x && y == other.y && z == other.z; }
	template <class T>
	inline bool v3<T>::operator!=(const v3& other) const { return x != other.x || y != other.y || z != other.z; }
	template <class T>
	inline v3<T>::operator T() { return T(x); }
	template <class T>
	inline v3<T>::operator v2<T>() { return v2<T>(x, y); }

	template <class T>
	inline v4<T>::v4() {}
	template <class T>
	inline v4<T>::v4(T v) : x(v), y(v), z(v), w(v) {}
	template <class T>
	inline v4<T>::v4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	template <class T>
	inline v4<T>::v4(v3<T> a, T w) : x(a.x), y(a.y), z(a.z), w(w) {}
	template <class T>
	inline v4<T>::v4(T x, v3<T> b) : x(x), y(b.x), z(b.y), w(b.z) {}
	template <class T>
	inline v4<T>::v4(v2<T> a, v2<T> b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
	template <class T>
	template <class V>
	inline v4<T>::v4(V v) : x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w)) {}
	template <class T>
	inline T v4<T>::operator[](uint index) const { return *((T*)&x + index); }
	template <class T>
	inline T& v4<T>::operator[](uint index) { return *((T*)&x + index); }
	template <class T>
	inline bool v4<T>::operator==(const v4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
	template <class T>
	inline bool v4<T>::operator!=(const v4& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }
	template <class T>
	inline v4<T>::operator v2<T>() { return v2<T>(x, y); }
	template <class T>
	inline v4<T>::operator v3<T>() { return v3<T>(x, y, z); }

	template struct MUD_MATH_EXPORT v2<float>;
	template struct MUD_MATH_EXPORT v3<float>;
	template struct MUD_MATH_EXPORT v4<float>;

	template struct MUD_MATH_EXPORT v2<int>;
	template struct MUD_MATH_EXPORT v3<int>;
	template struct MUD_MATH_EXPORT v4<int>;

	template struct MUD_MATH_EXPORT v2<uint>;
	template struct MUD_MATH_EXPORT v3<uint>;
	template struct MUD_MATH_EXPORT v4<uint>;

	template struct MUD_MATH_EXPORT v2<bool>;
	template struct MUD_MATH_EXPORT v3<bool>;
	template struct MUD_MATH_EXPORT v4<bool>;

	template <class T>
	inline T epsilon() { return std::numeric_limits<T>::epsilon(); }

	quat operator+(const quat& q) { return q; }
	quat operator-(const quat& v) { return quat(-v.x, -v.y, -v.z, -v.w); }

	quat operator+(const quat& a, const quat& b) { return quat(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	quat operator-(const quat& a, const quat& b) { return quat(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

	quat operator*(const quat& q, float s) { return quat(q.x * s, q.y * s, q.z * s, q.w * s); }
	quat operator/(const quat& q, float s) { return quat(q.x / s, q.y / s, q.z / s, q.w / s); }
	quat operator*(float s, const quat& q) { return quat(q.x * s, q.y * s, q.z * s, q.w * s); }
	quat operator/(float s, const quat& q) { return quat(s / q.x, s / q.y, s / q.w, s / q.w); }

	quat operator*(const quat& a, const quat& b)
	{
		return quat(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
			a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
		);
	}

	float3 operator*(const quat& q, const float3& v)
	{
		const float3 QuatVector(q.x, q.y, q.z);
		const float3 uv(cross(QuatVector, v));
		const float3 uuv(cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * float(2);
	}

	float4 operator*(const quat& q, const float4& v)
	{
		return float4(q * xyz(v), v.w);
	}

	quat conjugate(const quat& q) { return quat(-q.x, -q.y, -q.z, q.w); }
	quat inverse(const quat& q) { return conjugate(q) / dot(q, q); }
		
	quat normalize(const quat& q)
	{
		float len = length(q);
		if(len <= float(0))
			return quat(float(0), float(0), float(0), float(1));
		float invlen = float(1) / len;
		return quat(q.x * invlen, q.y * invlen, q.z * invlen, q.w * invlen);
	}

	//bool operator==(const quat& q1, const quat& q2) { return all(equal(q1, q2, epsilon<float>())); }
	//bool operator!=(const quat& q1, const quat& q2) { return any(not_equal(q1, q2, epsilon<float>())); }

	float dot(const quat& a, const quat& b)
	{
		float4 tmp(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
		return (tmp.x + tmp.y) + (tmp.z + tmp.w);
	}

#if 0
	quat lerp(const quat& a, const quat& b, float t)
	{
		float4 vec = lerp((float4&)a, (float4&)b, t);
		return quat(vec.x, vec.y, vec.z, vec.w);
	}
#endif

	quat slerp(const quat& x, const quat& y, float a)
	{
		quat z = y;

		float cosTheta = dot(x, y);

		// If cosTheta < 0, the interpolation will take the long way around the sphere. 
		// To fix this, one quat must be negated.
		if(cosTheta < float(0))
		{
			z = -y;
			cosTheta = -cosTheta;
		}

		// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
		if(cosTheta > float(1) - epsilon<float>())
		{
			// Linear interpolation
			return quat(lerp(x.x, z.x, a), lerp(x.y, z.y, a), lerp(x.z, z.z, a), lerp(x.w, z.w, a));
		}
		else
		{
			// Essential Mathematics, page 467
			float angle = acos(cosTheta);
			return (sin((float(1) - a) * angle) * x + sin(a * angle) * z) / sin(angle);
		}
	}

	float oriented_angle(const float3& a, const float3& b, const float3& ref)
	{
		const float angle = acos(clamp(dot(a, b), float(-1), float(1)));
		return lerp(angle, -angle, dot(ref, cross(a, b)) < float(0));
	}

	float oriented_angle(const float2& a, const float2& b)
	{
		const float angle = acos(clamp(dot(a, b), float(-1), float(1)));

		if(all(equal(b, rotate(a, angle), epsilon<float>())))
			return angle;
		else
			return -angle;
	}

	mat4 operator*(const mat4& m, float f)
	{
		mat4 result;
		result[0] = m[0] * f;
		result[1] = m[1] * f;
		result[2] = m[2] * f;
		result[3] = m[3] * f;
		return result;
	}

	mat4 transpose(const mat4& m)
	{
		mat4 result;
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[0][3] = m[3][0];

		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		result[1][3] = m[3][1];

		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		result[2][3] = m[3][2];

		result[3][0] = m[0][3];
		result[3][1] = m[1][3];
		result[3][2] = m[2][3];
		result[3][3] = m[3][3];
		return result;
	}

	mat4 inverse(const mat4& m)
	{
#if 1
		float xx = m.f[0];
		float xy = m.f[1];
		float xz = m.f[2];
		float xw = m.f[3];
		float yx = m.f[4];
		float yy = m.f[5];
		float yz = m.f[6];
		float yw = m.f[7];
		float zx = m.f[8];
		float zy = m.f[9];
		float zz = m.f[10];
		float zw = m.f[11];
		float wx = m.f[12];
		float wy = m.f[13];
		float wz = m.f[14];
		float ww = m.f[15];

		float det = 0.0f;
		det += xx * (yy*(zz*ww - zw * wz) - yz * (zy*ww - zw * wy) + yw * (zy*wz - zz * wy));
		det -= xy * (yx*(zz*ww - zw * wz) - yz * (zx*ww - zw * wx) + yw * (zx*wz - zz * wx));
		det += xz * (yx*(zy*ww - zw * wy) - yy * (zx*ww - zw * wx) + yw * (zx*wy - zy * wx));
		det -= xw * (yx*(zy*wz - zz * wy) - yy * (zx*wz - zz * wx) + yz * (zx*wy - zy * wx));

		float invDet = 1.0f / det;

		mat4 result;
		result.f[0] = +(yy*(zz*ww - wz * zw) - yz * (zy*ww - wy * zw) + yw * (zy*wz - wy * zz)) * invDet;
		result.f[1] = -(xy*(zz*ww - wz * zw) - xz * (zy*ww - wy * zw) + xw * (zy*wz - wy * zz)) * invDet;
		result.f[2] = +(xy*(yz*ww - wz * yw) - xz * (yy*ww - wy * yw) + xw * (yy*wz - wy * yz)) * invDet;
		result.f[3] = -(xy*(yz*zw - zz * yw) - xz * (yy*zw - zy * yw) + xw * (yy*zz - zy * yz)) * invDet;

		result.f[4] = -(yx*(zz*ww - wz * zw) - yz * (zx*ww - wx * zw) + yw * (zx*wz - wx * zz)) * invDet;
		result.f[5] = +(xx*(zz*ww - wz * zw) - xz * (zx*ww - wx * zw) + xw * (zx*wz - wx * zz)) * invDet;
		result.f[6] = -(xx*(yz*ww - wz * yw) - xz * (yx*ww - wx * yw) + xw * (yx*wz - wx * yz)) * invDet;
		result.f[7] = +(xx*(yz*zw - zz * yw) - xz * (yx*zw - zx * yw) + xw * (yx*zz - zx * yz)) * invDet;

		result.f[8] = +(yx*(zy*ww - wy * zw) - yy * (zx*ww - wx * zw) + yw * (zx*wy - wx * zy)) * invDet;
		result.f[9] = -(xx*(zy*ww - wy * zw) - xy * (zx*ww - wx * zw) + xw * (zx*wy - wx * zy)) * invDet;
		result.f[10] = +(xx*(yy*ww - wy * yw) - xy * (yx*ww - wx * yw) + xw * (yx*wy - wx * yy)) * invDet;
		result.f[11] = -(xx*(yy*zw - zy * yw) - xy * (yx*zw - zx * yw) + xw * (yx*zy - zx * yy)) * invDet;

		result.f[12] = -(yx*(zy*wz - wy * zz) - yy * (zx*wz - wx * zz) + yz * (zx*wy - wx * zy)) * invDet;
		result.f[13] = +(xx*(zy*wz - wy * zz) - xy * (zx*wz - wx * zz) + xz * (zx*wy - wx * zy)) * invDet;
		result.f[14] = -(xx*(yy*wz - wy * yz) - xy * (yx*wz - wx * yz) + xz * (yx*wy - wx * yy)) * invDet;
		result.f[15] = +(xx*(yy*zz - zy * yz) - xy * (yx*zz - zx * yz) + xz * (yx*zy - zx * yy)) * invDet;

		return result;
#else
		const float c00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		const float c02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		const float c03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		const float c04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		const float c06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		const float c07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		const float c08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		const float c10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		const float c11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		const float c12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		const float c14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		const float c15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		const float c16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		const float c18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		const float c19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		const float c20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		const float c22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		const float c23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		float4 Fac0 = float4(c00, c00, c02, c03);
		float4 Fac1 = float4(c04, c04, c06, c07);
		float4 Fac2 = float4(c08, c08, c10, c11);
		float4 Fac3 = float4(c12, c12, c14, c15);
		float4 Fac4 = float4(c16, c16, c18, c19);
		float4 Fac5 = float4(c20, c20, c22, c23);

		float4 Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		float4 Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		float4 Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		float4 Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		float4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		float4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		float4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		float4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		float4 SignA(+1, -1, +1, -1);
		float4 SignB(-1, +1, -1, +1);
		mat4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		float4 Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		float4 Dot0(m[0] * Row0);
		float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		float OneOverDeterminant = float(1) / Dot1;

		return Inverse * OneOverDeterminant;
#endif
	}

	mat4 operator*(const mat4& m1, const mat4& m2)
	{
		const float4 a0 = m1[0];
		const float4 a1 = m1[1];
		const float4 a2 = m1[2];
		const float4 a3 = m1[3];

		const float4 b0 = m2[0];
		const float4 b1 = m2[1];
		const float4 b2 = m2[2];
		const float4 b3 = m2[3];

		mat4 result;
		result[0] = a0 * b0[0] + a1 * b0[1] + a2 * b0[2] + a3 * b0[3];
		result[1] = a0 * b1[0] + a1 * b1[1] + a2 * b1[2] + a3 * b1[3];
		result[2] = a0 * b2[0] + a1 * b2[1] + a2 * b2[2] + a3 * b2[3];
		result[3] = a0 * b3[0] + a1 * b3[1] + a2 * b3[2] + a3 * b3[3];
		return result;
	}

	float4 operator*(const mat4& m, const float4& v)
	{
		const float4 mov0(v[0]);
		const float4 mov1(v[1]);
		const float4 mul0 = m[0] * mov0;
		const float4 mul1 = m[1] * mov1;
		const float4 add0 = mul0 + mul1;
		const float4 mov2(v[2]);
		const float4 mov3(v[3]);
		const float4 mul2 = m[2] * mov2;
		const float4 mul3 = m[3] * mov3;
		const float4 add1 = mul2 + mul3;
		const float4 add2 = add0 + add1;
		return add2;
	}

#if 0

	// For float->float16 conversion
	half float_to_half(float f);
	float half_to_float(const half& h);

	// Uniform distribution mapping functions
	float3 UniformUVToSphere(const float2& uv, float r);
	float3 UniformUVToHemisphere(const float2& uv);
	float3 UniformUVToHemisphere(const float2& uv, float max_theta);
	float3 UniformUVToHemisphereCosine(const float2& uv);
	float3 UniformUVToHemisphereCosine(const float2& uv, float max_theta);

	// Signed distance functions
	// TODO: Move for use in HLSL
	float sdSphere(const float3& p, float r);
	float sdCylinder(const float3& p, const float2& h);
	float sdBox(const float3& p, const float3& b);
	float sdCapsule(const float3& p, const float3& a, const float3& b, float r);
	float sdEllipsoid(const float3& p, const float3& r);
	float sdUnion(float a, float b);
	float sdSubtract(float a, float b0);
	float sdIntersect(float a, float b);
	float sdSmoothUnion(float a, float b, float k);

	//
	// Vector conversion functions
	//
	float3 double3_to_float3(const double3& v);
	double3 float3_to_double3(const float3& v);


/*$pycgen
	code = """
	T coserp_t(T t);
	T2 coserp_t(const T2& t);
	T3 coserp_t(const T3& t);
	T4 coserp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float coserp_t(float t);
	float2 coserp_t(const float2& t);
	float3 coserp_t(const float3& t);
	float4 coserp_t(const float4& t);
//$pycgen-end


/*$pycgen
	code = """
	T cuberp_t(T t);
	T2 cuberp_t(const T2& t);
	T3 cuberp_t(const T3& t);
	T4 cuberp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float cuberp_t(float t);
	float2 cuberp_t(const float2& t);
	float3 cuberp_t(const float3& t);
	float4 cuberp_t(const float4& t);
//$pycgen-end


/*$pycgen
	code = """
	T quinterp_t(T t);
	T2 quinterp_t(const T2& t);
	T3 quinterp_t(const T3& t);
	T4 quinterp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float quinterp_t(float t);
	float2 quinterp_t(const float2& t);
	float3 quinterp_t(const float3& t);
	float4 quinterp_t(const float4& t);
//$pycgen-end

	//
	// Scalar math
	//
	float2 SinCos(float angle);
	float DegreesToRadians(float degrees);
	double DegreesToRadians(double degrees);
	float RadiansToDegrees(float radians);
	double RadiansToDegrees(double radians);
	uint Factorial(uint v);


	//
	// Procedural operations on vectors
	//
	float3	vSlerp(const float3& a, const float3& b, float t);
	float3 	vPerpendicular(const float3& v);
	double3	vPerpendicular(const double3& v);
	bool 	vEquals(const int3& a, const int3& b, float epsilon);
	float3	vProjectOnto(const float3& a, const float3& b);
	double3	vMapCubeToSphere(const double3& v);
	double3	vMapNonUnitCubeToSphere(const double3& v, double extents);
	float3	vFraction(const float3& v);
	double3	vFraction(const double3& v);
	void	vOrthogonalise(const float3& a, float3& b, float3& c);


	//
	// Matrix generation functions
	//
	mat3 m3Zero();
	mat4 m4Zero();
	mat3 m3Identity();
	mat4 m4Identity();
	mat3 m3RotateX(float angle);
	mat4 m4RotateX(float angle);
	mat3 m3RotateY(float angle);
	mat4 m4RotateY(float angle);
	mat3 m3RotateZ(float angle);
	mat4 m4RotateZ(float angle);
	mat3 m3Scale(float x, float y, float z);
	mat3 m3Scale(const float3& s);
	mat3 m3Direction(const float3& z);
	mat3 m3Direction(const float3& z, float3 y);
	mat4 m4Translate(float x, float y, float z);
	mat4 m4Translate(const float3& v);
	mat4 m4PerspectiveFovLH(float fov_y, float aspect_ratio, float near_z, float far_z);
	mat4 m4PerspectiveFovOffCenterLH(float fov_y, float aspect_ratio, const float4& rect, float near_z, float far_z);
	mat3 m3Up(const double3& y);
	mat3d m3dZero();
	mat3d m3dIdentity();


	//
	// Matrix conversion functions
	//
	mat3 mat4_to_mat3(const mat4& m4);
	mat4 mat3_to_mat4(const mat3& m3);
	mat3 mat3d_to_mat3(const mat3d& m3d);
	mat3d mat3_to_mat3d(const mat3& m3);


	//
	// Procedural operations on matrices
	// Disabled in HLSL for now as it's easy to mess up during porting
//
	mat3 m3Multiply(const mat3& a, const mat3& b);
	mat4 m4Multiply(const mat4& a, const mat4& b);
	mat3d m3dMultiply(const mat3d& a, const mat3d& b);
	float m3Determinant(const mat3& m);
	float m4Determinant(const mat4& m);
	bool m3Inverse(const mat3& m, mat3& inv_m);
	bool m4Inverse(const mat4& m, mat4& inv_m);
	mat3 m3Transpose(const mat3& m);
	mat4 m4Transpose(const mat4& m);
	mat3 m3Orthogonalise(const mat3& m, int axis);
	mat3 m3Orthonormalise(const mat3& m, int axis);
	float3 m3Transform(const mat3& m, const float3& v);
	double3 m3Transform(const mat3& m, const double3& v);
	float4 m4Transform(const mat4& m, const float4& v);
	float3 m3TransformTransposed(const mat3& m, const float3& v);
	double3 m3TransformTransposed(const mat3& m, const double3& v);
	float3 m4TransformPos(const mat4& m, const float3& v);
	double3 m4TransformPos(const mat4& m, const double3& v);
	float3 m4TransformDir(const mat4& m, const float3& v);
	bool m3ToEulerXYZ(const mat3& m, float3& angles);
	bool m3ToEulerYXZ(const mat3& m, float3& angles);
	bool m3ToEulerZXY(const mat3& m, float3& angles);
	bool m3ToEulerZYX(const mat3& m, float3& angles);
	void m3dDiagonalise(const mat3d& m, mat3d& Q, mat3d& D);


	//
	// Quaternion functions
	//
	quat qZero();
	quat qIdentity();
	quat qAxisAngle(const float3& v, float angle);
	float qNorm(const quat& q);
	quat qNormalise(const quat& q);
	quat qNegate(const quat& q);
	quat qConjugate(const quat& q);
	quat qInverse(const quat& q);
	quat qScale(const quat& q, float scale);
	float qDot(const quat& a, const quat& b);
	quat qMultiply(const quat& a, const quat& b);
	quat qMultiplyPure(const quat& a, const float3& b);
	float3 qTransformPos(const quat& q, const float3& p);
	double3 qTransformPos(const quat& q, const double3& p);
	quat qRotationBetween(float3 v0, float3 v1);
	quat qLerp(const quat& a, const quat& b, float t);
	quat qSlerp(quat a, const quat& b, float t);


	//
	// Quaternion conversion functions
	//
	mat3 quat_to_mat3(const quat& q);
	mat4 quat_to_mat4(const quat& q);
	quat mat3_to_quat(const mat3& m);


	//
	// Dual quaternion generation functions
	//
	dualquat dqIdentity();


	//
	// Frame functions
	//
	frame fIdentity();
	framed fdIdentity();
	frame fPosition(const float3& position);
	framed fdPosition(const double3& position);
	frame fPositionRotation(const float3& position, const quat& rotation);
	framed fdPositionRotation(const double3& position, const quat& rotation);
	frame fInverse(const frame& f);
	framed fInverse(const framed& f);
	frame fMultiply(const frame& a, const frame& b);
	framed fMultiply(const framed& a, const framed& b);
	frame fLerp(const frame& a, const frame& b, float t);
	float3 fTransformPos(const frame& f, const float3& v);
	double3 fTransformPos(const framed& f, const double3& v);


	//
	// Frame conversion functions
	//
	frame framed_to_frame(const framed& f);

	//
	// Transform functions
	//
	transform tZero();
	transform tIdentity();
	transform tPosition(const double3& position);
	transform tPositionRotation(const double3& position, const mat3& rotation);
	mat4 tToMat4(const transform& t);
	mat4 tToMat4Rigid(const transform& t);
	double3 tTransformPos(const transform& t, const double3& v);
	transform tMultiplyRigid(const transform& a, const transform& b);


	//
	// Box functions
	//
	boxi biScale(const boxi& box, i32 scale);
	boxi biInvScale(const boxi& box, i32 inv_scale);
	boxi biUnion(const boxi& a, const boxi& b);
	boxi biIntersection(const boxi& a, const boxi& b);
	bool biIntersects(const boxi& a, const boxi& b);
	i32 biVolume(const boxi& b);


	//
	// Plane generation functions
	//
	planef pPositionNormal(const float3& position, const float3& normal);
	planed pPositionNormal(const double3& position, const double3& normal);
	planef pTriangle(const float3& a, const float3& b, const float3& c);
	planed pTriangle(const double3& a, const double3& b, const double3& c);


	//
	// Procedural operations with planes
	//
	float pDistanceFrom(const planef& p, const float3& v);
	double pDistanceFrom(const planed& p, const double3& v);
	float pDistanceFrom(const planef& p, const float3& pos, const float3& extents);
	double pDistanceFrom(const planed& p, const double3& pos, const double3& extents);
	float3 pProjectVector(const planef& p, const float3& v);
	double3 pProjectVector(const planed& p, const double3& v);
	planef pNormalise(const planef& p);
	planed pNormalise(const planed& p);
	planef pTransform(const planef& p, const mat4& m);
	planed pTransform(const planed& p, const mat4& m);
	planef pTranslate(const planef& p, const float3& v);
	planed pTranslate(const planed& p, const double3& v);
	float3 pIntersectionPoint(const planef& a, const planef& b, const planef& c);
	double3 pIntersectionPoint(const planed& a, const planed& b, const planed& c);
	bool pIntersectionPoint(const planef& a, const planef& b, const planef& c, float3& Q);
	bool pIntersectionPoint(const planed& a, const planed& b, const planed& c, double3& Q);
	bool pIntersectionLine(const planef& a, const planef& b, float3& Q, float3& V);
	bool pIntersectionLine(const planed& a, const planed& b, double3& Q, double3& V);


	// Frustum functions
	frustumf frustumfMake(const mat4& m);
	frustumd frustumdMake(const mat4& m);
	frustumf frustumTransform(const frustumf& f, const mat4& m);
	frustumd frustumTransform(const frustumd& f, const mat4& m);
	frustumf frustumTranslate(const frustumf& f, const float3& v);
	frustumd frustumTranslate(const frustumd& f, const double3& v);
	bool frustumContains(const frustumf& f, const float3& pos, const float3& extents);
	bool frustumContains(const frustumd& f, const double3& pos, const double3& extents);


	//
	// Some utility functions
	//
	float QuadAreaApproximateSphereProjectionSize(const float3& pos, float radius, const mat4& w2c, const mat4& c2s, float near_z);
	double SphereAngularProjectionOntoPosition(const double3& sphere_pos, double radius, const double3& position);
	void MakeHammersleyPoints(u32 nb_points, vector<float4>& points);
	i16 Compress_DoubleToSigned16(double d, double extents);
	double Decompress_Signed16ToDouble(i16 d, double extents);
#endif
}
