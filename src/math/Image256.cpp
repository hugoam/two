//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <cstring>
#include <cstdio>
#endif

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/Image256.h>
#include <math/Colour.h>
#endif

namespace mud
{
	Palette::Palette()
		: m_colours()
	{}

	Palette::Palette(span<Colour> colours)
		: m_colours(colours.begin(), colours.end())
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
			m_colours.push_back(hsl(h, 0.5f, 0.5f));
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

				*data++ = static_cast<uint8_t>(color.r * 255);
				*data++ = static_cast<uint8_t>(color.g * 255);
				*data++ = static_cast<uint8_t>(color.b * 255);
				*data++ = 255;
			}
	}

	vector<uint8_t> Image256::read() const
	{
		vector<uint8_t> buffer(m_width * m_height * 4);
		this->read(buffer.data());
		return buffer;
	}

	vector<uint32_t> Image256::read32() const
	{
		vector<uint32_t> buffer(m_width * m_height);
		this->read((uint8_t*)buffer.data());
		return buffer;
	}
}
