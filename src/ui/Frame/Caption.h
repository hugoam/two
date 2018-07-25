//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <ui/Forward.h>
#include <ui/Frame/Dim.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ struct MUD_UI_EXPORT TextGlyph
	{
		const char* m_position;
		vec4 m_rect;
	};

	export_ struct MUD_UI_EXPORT TextRow
	{
		const char* m_start;
		const char* m_end;
		size_t m_start_index;
		size_t m_end_index;
		vec4 m_rect;

		std::vector<TextGlyph> m_glyphs;
	};

	inline TextRow text_row(const char* str, const char* start, const char* end, const vec4& rect)
	{
		return { start, end, size_t(start - str), size_t(end - str), rect };
	}
}
