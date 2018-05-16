//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <ui/Generated/Forward.h>
#include <ui/Frame/Dim.h>

#include <vector>

namespace mud
{
	struct MUD_UI_EXPORT TextGlyph
	{
		const char* m_position;
		vec4 m_rect;
	};

	struct MUD_UI_EXPORT TextRow
	{
		const char* m_start;
		const char* m_end;
		size_t m_start_index;
		size_t m_end_index;
		vec4 m_rect;

		std::vector<TextGlyph> m_glyphs;
	};
}
