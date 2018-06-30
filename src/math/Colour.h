//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>

#ifndef MUD_CPP_20
#include <cmath>
#include <cstddef>
#include <cstdint>
#endif

namespace mud
{
	export_ struct refl_ array_  MUD_MATH_EXPORT Colour
	{
		constr_ Colour();
		constr_ Colour(float v, float a = 1.f);
		constr_ Colour(float r, float g, float b, float a = 1.f);

		Colour(const Colour& col) = default;
		Colour& operator=(const Colour&) = default;

		bool operator==(const Colour& other) const { return m_r == other.m_r && m_g == other.m_g && m_b == other.m_b && m_a == other.m_a; }

		union {
			struct {
				attr_ mut_ float m_r;
				attr_ mut_ float m_g;
				attr_ mut_ float m_b;
				attr_ mut_ float m_a;
			};
			struct { float m_h; float m_s; float m_l; float m__; };
			float m_floats[4];
		};

		float operator[](size_t i) const { return m_floats[i]; }
		float& operator[](size_t i) { return m_floats[i]; }

		Colour operator*(const float factor) const { return Colour(m_r*factor, m_g*factor, m_b*factor, m_a); }
		Colour operator*(const Colour& colour) const { return Colour(m_r*colour.m_r, m_g*colour.m_g, m_b*colour.m_b, m_a); }
		Colour operator+(const Colour& colour) const { return Colour(m_r+colour.m_r, m_g+colour.m_g, m_b+colour.m_b, m_a+colour.m_a); }
		Colour operator-(const Colour& colour) const { return Colour(m_r-colour.m_r, m_g-colour.m_g, m_b-colour.m_b, m_a-colour.m_a); }

		bool null() const { return m_a == 0.f; }

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

	export_ MUD_MATH_EXPORT func_ uint32_t to_rgba(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ uint32_t to_abgr(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour from_rgba(uint32_t colour);
	export_ MUD_MATH_EXPORT func_ Colour from_abgr(uint32_t colour);
	export_ MUD_MATH_EXPORT func_ Colour to_linear(const Colour& colour);

	export_ MUD_MATH_EXPORT func_ Colour hsl_to_rgb(float h, float s, float l);
	export_ MUD_MATH_EXPORT func_ Colour rgb_to_hsl(float r, float g, float b);

	export_ MUD_MATH_EXPORT func_ Colour rgba_to_hsla(const Colour& colour);
	export_ MUD_MATH_EXPORT func_ Colour hsla_to_rgba(const Colour& colour);

	export_ inline Colour to_colour(uint8_t r, uint8_t g, uint8_t b) { return Colour(float(r) / 255.f, float(g) / 255.f, float(b) / 255.f); }
	export_ inline Colour to_colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { return Colour(float(r) / 255.f, float(g) / 255.f, float(b) / 255.f, float(a) / 255.f); }
}
