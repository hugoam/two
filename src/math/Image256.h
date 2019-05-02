//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <stl/span.h>
#include <math/Forward.h>
#include <math/Vec.h>
#include <math/Colour.h>

namespace two
{
	export_ using cstring = const char*;

	export_ enum class refl_ Spectrum : short int
	{
		Value = 0,
		Hue = 1
	};

	export_ struct refl_ TWO_MATH_EXPORT Palette
	{
	public:
		constr_ Palette(Spectrum spectrum, size_t steps);
		constr_ Palette(span<Colour> colours);
		constr_ Palette();

		void reset();
		void load(cstring file);
		void add(Colour colour);

		size_t find_colour(const Colour& colour);

		void value_spectrum(size_t steps, bool toWhite = false);
		void hue_spectrum(size_t steps);

		vector<Colour> m_colours;
	};

	export_ struct refl_ TWO_MATH_EXPORT Image256
	{
	public:
		constr_ Image256(const uvec2& size = uvec2(0U), const Palette& palette = Palette());

		bool operator==(const Image256& other) const;

		void resize(const uvec2& size);
		uint32_t& at(const uvec2& p) { return m_pixels[p.x + p.y * m_size.x]; }

		vector<uint8_t> read() const;
		vector<uint32_t> read32() const;
		void read(uint8_t* data) const;

		attr_ vector<uint32_t> m_pixels;
		attr_ uvec2 m_size;
		attr_ Palette m_palette;
	};
}
