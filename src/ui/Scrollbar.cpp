//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.ui;
#else
#include <math/Vec.hpp>
#include <ui/Scrollbar.h>
#include <ui/Button.h>
#include <ui/Style/Styles.h>
#include <ui/WidgetStruct.h>
#endif

namespace two
{
namespace ui
{
	bool overflow(Frame& frame, Frame& content, Axis dim)
	{
		float visible_size = frame.m_size[dim];
		float content_size = content.m_size[dim] * content.m_scale;
		return content_size - visible_size > 0.f;
	}

	void scroll_to(Frame& content, Axis dim, float offset)
	{
		content.set_position(dim, -offset);
		//content.layer().setForceRedraw();
	}

	bool scroller(Widget& parent, float& cursor, float overflow, float visible_size, Axis dim)
	{
		return slider(parent, scrollbar_styles().scroller, cursor, SliderMetrics{ 0.f, overflow, 1.f, visible_size },
					  dim, true, false, &scrollbar_styles().scroller_knob);
	}

	Widget& scrollbar(Widget& parent, Frame& frame, Frame& content, Axis dim, v2<uint> grid_index)
	{
		Widget& self = widget(parent, styles().row, false, dim, grid_index);

		float visible_size = frame.m_size[dim];
		float content_size = content.m_size[dim] * content.m_scale;
		float overflow = content_size - visible_size;

		if(overflow <= 0.f)
			return self;

		Widget& scrollbar = widget(self, scrollbar_styles().scrollbar, false, dim);

		float cursor = -content.m_position[dim];
		if(cursor > 0.f && content_size - cursor < visible_size)
			cursor = max(content_size - visible_size, 0.f);

		Widget& rewind = button(scrollbar, dim == Axis::Y ? scrollbar_styles().scroll_up
														: scrollbar_styles().scroll_left);

		scroller(scrollbar, cursor, overflow, visible_size, dim);

		Widget& forward = button(scrollbar, dim == Axis::Y ? scrollbar_styles().scroll_down
														 : scrollbar_styles().scroll_right);

		if(rewind.activated())
			cursor -= 22.f;

		if(forward.activated())
			cursor += 22.f;

		scroll_to(content, dim, max(0.f, min(overflow, cursor)));

		return self;
	}
}
}
