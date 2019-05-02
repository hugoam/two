//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Sheet.h>

namespace two
{
namespace ui
{
	export_ struct CursorStyles
	{
		void reset();
		Style cursor; Style resize_x; Style resize_y; Style move; Style resize_diag_left; Style resize_diag_right; Style caret;
	};

	export_ TWO_UI_EXPORT CursorStyles& cursor_styles();

	export_ TWO_UI_EXPORT Widget* hoverbox(Widget& parent, const vec2& position, float delay = 0.5f);
	export_ TWO_UI_EXPORT func_ Widget* hoverbox(Widget& parent, float delay = 0.5f);

	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, const vec2& position, span<cstring> elements);

	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, cstring content);
	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, span<cstring> elements);

	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, const Frame& parent_frame);
	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, const Frame& parent_frame, cstring content);
	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, const Frame& parent_frame, span<cstring> elements);

	export_ TWO_UI_EXPORT Widget& cursor(Widget& parent, const vec2& position, Style& style, bool locked = false);
	export_ TWO_UI_EXPORT func_ Widget& cursor(Widget& parent, const vec2& position, Widget& hovered, bool locked = false);

	export_ TWO_UI_EXPORT func_ Widget& rectangle(Widget& parent, const vec4& rect);
	export_ TWO_UI_EXPORT func_ Widget& viewport(Widget& parent, const vec4& rect);
}
}
