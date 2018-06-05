//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Colour.h>
#endif
#include <geom/Generated/Forward.h>

namespace mud
{
	using cstring = const char*;

	export_ enum class _refl_ SymbolDetail : unsigned short
	{
		Lowest,
		Low,
		Medium,
		High,
		Highest
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Symbol
	{
	public:
		_constr_ Symbol(Colour outline = Colour::White, Colour fill = Colour::None, bool overlay = false, bool double_sided = false, SymbolDetail detail = SymbolDetail::Medium);
		Symbol(cstring image, float alpha = 1.f);
		Symbol(const Image256& image256, float alpha = 1.f);

		bool operator==(const Symbol& other) const;

		_attr_ Colour m_outline;
		_attr_ Colour m_fill;
		_attr_ bool m_overlay;
		_attr_ bool m_double_sided;
		_attr_ SymbolDetail m_detail;

		_attr_ cstring m_image = nullptr;
		_attr_ Image256* m_image256 = nullptr;
		_attr_ cstring m_program = nullptr;

		bool outline() const { return !m_outline.null(); }
		bool fill() const { return !m_fill.null(); }
	};
}
