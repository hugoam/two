//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Sheet.h>
#include <ui/Scrollbar.h>

namespace two
{
namespace ui
{
	export_ TWO_UI_EXPORT void draw_grid(const Frame& frame, const vec4& rect, Vg& vg);

	export_ TWO_UI_EXPORT func_ ScrollSheet& scroll_sheet(Widget& parent, Style& style = styles().scrollsheet, Style* surface_style = nullptr);
	export_ TWO_UI_EXPORT func_ ScrollSheet& scroll_plan(Widget& parent, Style& style = styles().scrollsheet);

	export_ TWO_UI_EXPORT func_ Widget& scrollable(Widget& parent);

	export_ TWO_UI_EXPORT void autofit_scroll_plan(ScrollSheet& scroll_sheet, span<Widget*> elements);
}
}
