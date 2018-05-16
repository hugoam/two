//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <math/Colour.h>

#include <vector>

namespace mud
{
	using cstring = const char*;

	enum _refl_ SpectrumPalette : short int
	{
		SPECTRUM_GRAYSCALE = 0,
		SPECTRUM_HUE = 1
	};

	struct _refl_ MUD_OBJ_EXPORT Palette
	{
	public:
		_constr_ Palette(SpectrumPalette spectrum, size_t steps);
		_constr_ Palette(std::vector<Colour> colours);
		_constr_ Palette();

		void reset();
		void load(cstring file);
		void add(Colour colour);

		size_t findColour(const Colour& colour);

		void grayScaleSpectrum(size_t steps, bool toWhite = false);
		void hueSpectrum(size_t steps);

		std::vector<Colour> m_colours;
	};

	struct _refl_ MUD_OBJ_EXPORT Image256
	{
	public:
		_constr_ Image256(uint16_t width = 0, uint16_t height = 0, const Palette& palette = Palette());

		bool operator==(const Image256& other) const;

		void resize(uint16_t width, uint16_t height);
		uint32_t& at(uint16_t x, uint16_t y) { return m_pixels[x + y * m_width]; }

		std::vector<uint8_t> read() const;
		void read(uint8_t* data) const;

		_attr_ std::vector<uint32_t> m_pixels;
		_attr_ uint16_t m_width;
		_attr_ uint16_t m_height;
		_attr_ Palette m_palette;
	};
}
