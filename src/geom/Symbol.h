//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>

namespace two
{
	using cstring = const char*;

	export_ enum class refl_ SymbolDetail : unsigned short
	{
		Lowest,
		Low,
		Medium,
		High,
		Highest
	};

	export_ struct refl_ TWO_GEOM_EXPORT Symbol
	{
	public:
		constr_ Symbol(Colour fill = Colour(1.f), Colour outline = Colour(0.f, 0.f), bool overlay = false, bool double_sided = false, SymbolDetail detail = SymbolDetail::Medium);
		Symbol(cstring image, float alpha = 1.f);
		Symbol(const Image256& image256, float alpha = 1.f);

		constr_ static inline Symbol plain(Colour colour, bool overlay = false) { return Symbol(colour, Colour(0.f, 0.f), overlay); }
		constr_ static inline Symbol wire(Colour colour, bool overlay = false) { return Symbol(Colour(0.f, 0.f), colour, overlay); }

		bool operator==(const Symbol& other) const;

		attr_ Colour m_outline;
		attr_ Colour m_fill;
		attr_ bool m_overlay;
		attr_ bool m_double_sided;
		attr_ SymbolDetail m_detail;
		attr_ uvec2 m_subdiv = uvec2(0U);

		attr_ cstring m_image = nullptr;
		attr_ Image256* m_image256 = nullptr;
		attr_ cstring m_program = nullptr;

		bool outline() const { return !m_outline.null(); }
		bool fill() const { return !m_fill.null(); }
	};
}
