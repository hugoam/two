//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/Colour.h>
#include <math/Math.h>
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
		: r(1.f), g(1.f), b(1.f), a(1.f)
	{}

	Colour::Colour(float v, float a)
		: r(v), g(v), b(v), a(a)
	{}

	Colour::Colour(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a)
	{}

	Colour Colour::hsl(float h, float s, float l)
	{
		return mud::hsl(h, s, l);
	}

	uint32_t to_rgba(const Colour& colour)
	{
		uint32_t rgba = 0;
		rgba |= uint8_t(clamp(colour.r, 0.f, 1.f) * 255.f) << 24;
		rgba |= uint8_t(clamp(colour.g, 0.f, 1.f) * 255.f) << 16;
		rgba |= uint8_t(clamp(colour.b, 0.f, 1.f) * 255.f) << 8;
		rgba |= uint8_t(clamp(colour.a, 0.f, 1.f) * 255.f);
		return rgba;
	}

	uint32_t to_abgr(float r, float g, float b, float a)
	{
		//Colour col = clamp_colour(colour);
		uint32_t rgba = 0;
		rgba |= uint8_t(clamp(r, 0.f, 1.f) * 255.f);
		rgba |= uint8_t(clamp(g, 0.f, 1.f) * 255.f) << 8;
		rgba |= uint8_t(clamp(b, 0.f, 1.f) * 255.f) << 16;
		rgba |= uint8_t(clamp(a, 0.f, 1.f) * 255.f) << 24;
		return rgba;
	}

	uint32_t to_abgr(const Colour& colour)
	{
		uint32_t rgba = 0;
		rgba |= uint8_t(clamp(colour.r, 0.f, 1.f) * 255.f);
		rgba |= uint8_t(clamp(colour.g, 0.f, 1.f) * 255.f) << 8;
		rgba |= uint8_t(clamp(colour.b, 0.f, 1.f) * 255.f) << 16;
		rgba |= uint8_t(clamp(colour.a, 0.f, 1.f) * 255.f) << 24;
		return rgba;
	}
	
	Colour rgb(uint32_t rgba)
	{
		Colour colour;
		colour.r = ((rgba >> 16) & 0xFF) / 255.f;
		colour.g = ((rgba >> 8)  & 0xFF) / 255.f;
		colour.b = ((rgba >> 0)  & 0xFF) / 255.f;
		return colour;
	}

	Colour rgba(uint32_t rgba)
	{
		Colour colour;
		colour.r =  (rgba >> 24) / 255.f;
		colour.g = ((rgba >> 16) & 0xFF) / 255.f;
		colour.b = ((rgba >> 8)  & 0xFF) / 255.f;
		colour.a = ((rgba >> 0)  & 0xFF) / 255.f;
		return colour;
	}

	Colour abgr(uint32_t abgr)
	{
		Colour colour;
		colour.r = ((abgr >> 0)  & 0xFF) / 255.f;
		colour.g = ((abgr >> 8)  & 0xFF) / 255.f;
		colour.b = ((abgr >> 16) & 0xFF) / 255.f;
		colour.a =  (abgr >> 24) / 255.f;
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
		return Colour(to_linear(colour.r), to_linear(colour.g), to_linear(colour.b), colour.a);
	}

	Colour to_gamma(const Colour& colour)
	{
		return Colour(to_gamma(colour.r), to_gamma(colour.g), to_gamma(colour.b), colour.a);
	}

	Colour to_srgb(const Colour& colour)
	{
		return Colour(to_gamma(colour.r), to_gamma(colour.g), to_gamma(colour.b), colour.a);
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

	Colour hsl(float h, float s, float l)
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

	Colour to_rgba(const ColourHSL& colour)
	{
		return hsl(colour.h, colour.s, colour.l);
	}

	ColourHSL to_hsl(float r, float g, float b)
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

		return { h, s, l, 1.f };
	}

	ColourHSL to_hsl(const Colour& colour)
	{
		return to_hsl(colour.r, colour.g, colour.b);
	}

	ColourHSL to_hsla(const Colour& colour)
	{
		return to_hsl(colour.r, colour.g, colour.b);
	}
}
