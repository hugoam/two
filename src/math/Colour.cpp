//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <functional>
#include <algorithm>
#endif

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/Colour.h>
#include <math/Math.h>
#include <math/Clamp.h>
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

	Colour clamp_colour(const Colour& colour)
	{
#ifdef MUD_PLATFORM_EMSCRIPTEN
		Colour clamped = colour;
		for(size_t i = 0; i < 4; ++i)
			clamped[i] = std::clamp(colour[i], 0.f, 1.f);
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
		return value < 0.04045 ? float(value * (1.0 / 12.92)) : float(std::pow((value + 0.055) * (1.0 / (1 + 0.055)), 2.4));
	}

	Colour to_linear(const Colour& colour)
	{
		return Colour(to_linear(colour.m_r), to_linear(colour.m_g), to_linear(colour.m_b), colour.m_a);
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
