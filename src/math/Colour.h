//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stdint.h>
#include <stl/stddef.h>
#include <math/Forward.h>

namespace mud
{
	export_ struct refl_ array_  MUD_MATH_EXPORT ColourHSL
	{
		attr_ float h; attr_ float s; attr_ float l; attr_ float a;
	};

	export_ struct refl_ array_  MUD_MATH_EXPORT Colour
	{
		constr_ Colour();
		constr_ explicit Colour(float v, float a = 1.f);
		constr_ Colour(float r, float g, float b, float a = 1.f);

		constr_ static Colour hsl(float h, float s, float l);

		Colour(const Colour& col) = default;
		Colour& operator=(const Colour&) = default;

		bool operator==(const Colour& other) const { return this->r == other.r && g == other.g && b == other.b && a == other.a; }

		union {
			struct {
				attr_ float r;
				attr_ float g;
				attr_ float b;
				attr_ float a;
			};
			float m_floats[4];
		};

		float operator[](size_t i) const { return m_floats[i]; }
		float& operator[](size_t i) { return m_floats[i]; }

		Colour operator*(const float factor) const { return Colour(r*factor, g*factor, b*factor, a); }
		Colour operator*(const Colour& colour) const { return Colour(r*colour.r, g*colour.g, b*colour.b, a); }
		Colour operator+(const Colour& colour) const { return Colour(r+colour.r, g+colour.g, b+colour.b, a+colour.a); }
		Colour operator-(const Colour& colour) const { return Colour(r-colour.r, g-colour.g, b-colour.b, a-colour.a); }

		bool null() const { return a == 0.f; }

	public:
		attr_ static Colour Black;
		attr_ static Colour AlphaBlack;
		attr_ static Colour Red;
		attr_ static Colour Green;
		attr_ static Colour NeonGreen;
		attr_ static Colour Blue;
		attr_ static Colour Pink;
		attr_ static Colour Cyan;
		attr_ static Colour Yellow;
		attr_ static Colour White;
		attr_ static Colour AlphaWhite;
		attr_ static Colour LightGrey;
		attr_ static Colour MidGrey;
		attr_ static Colour DarkGrey;
		attr_ static Colour AlphaGrey;
		attr_ static Colour Transparent;
		attr_ static Colour Invisible;
		attr_ static Colour None;
	};

	export_ MUD_MATH_EXPORT func_ Colour rgb(uint32_t colour);
	export_ MUD_MATH_EXPORT func_ Colour rgba(uint32_t colour);
	export_ MUD_MATH_EXPORT func_ Colour abgr(uint32_t colour);

	export_ MUD_MATH_EXPORT func_ Colour hsl(float h, float s, float l);

	export_ MUD_MATH_EXPORT func_ uint32_t to_rgba(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ uint32_t to_abgr(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour to_linear(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour to_gamma(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour to_srgb(const Colour& colour);

	export_ MUD_MATH_EXPORT func_ ColourHSL to_hsl(float r, float g, float b);
	export_ MUD_MATH_EXPORT func_ ColourHSL to_hsl(const Colour& colour);

	export_ MUD_MATH_EXPORT func_ ColourHSL to_hsla(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour to_rgba(const ColourHSL& colour);

	inline Colour saturation(const Colour& colour, float amount)
	{
		ColourHSL result = to_hsl(colour.r, colour.g, colour.b);
		result.s *= amount;
		return hsl(result.h, result.s, result.l);
	}

	inline Colour offset_hsl(const Colour& colour, float h, float s, float l)
	{
		ColourHSL result = to_hsl(colour.r, colour.g, colour.b);
		result.h *= h;
		result.s *= s;
		result.l *= l;
		return hsl(result.h, result.s, result.l);
	}

	export_ inline Colour to_colour(uint8_t r, uint8_t g, uint8_t b) { return Colour(float(r) / 255.f, float(g) / 255.f, float(b) / 255.f); }
	export_ inline Colour to_colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { return Colour(float(r) / 255.f, float(g) / 255.f, float(b) / 255.f, float(a) / 255.f); }
}
