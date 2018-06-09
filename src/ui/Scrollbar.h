//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Button.h>
#include <ui/Slider.h>

namespace mud
{
namespace ui
{
	export_ struct ScrollbarStyles
	{
		ScrollbarStyles();
		Style scrollbar; Style scroll_up; Style scroll_down; Style scroll_left; Style scroll_right; Style scroller; Style scroller_knob;
	};

	export_ MUD_UI_EXPORT ScrollbarStyles& scrollbar_styles();

	export_ MUD_UI_EXPORT bool overflow(Frame& frame, Frame& content, Dim dim);
	export_ MUD_UI_EXPORT Widget& scrollbar(Widget& parent, Frame& frame, Frame& content, Dim dim, Dim2<size_t> grid_index = { 0, 0 });
}
}
