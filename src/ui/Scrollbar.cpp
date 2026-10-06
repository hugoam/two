//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

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

	void scroll_to(Widget content, Axis dim, float offset)
	{
		content.set_position(dim, -offset);
		//content.layer().setForceRedraw();
	}

	bool scroller(NodeKey id, Widget parent, float& cursor, float overflow, float visible_size, Axis dim)
	{
		return slider(id, parent, scrollbar_styles().scroller, cursor, SliderMetrics{ 0.f, overflow, 1.f, visible_size },
					  dim, true, false, &scrollbar_styles().scroller_knob);
	}

	Widget scrollbar(NodeKey id, Widget parent, Widget frame, Widget content, Axis dim, v2<uint> grid_index)
	{
		Widget self = widget(id, parent, styles().row, false, dim, grid_index);

		float visible_size = frame.frame().m_size[dim];
		float content_size = content.frame().m_size[dim] * content.frame().m_scale;
		float overflow = content_size - visible_size;

		if(overflow <= 0.f)
			return self;

		Widget scrollbar = widget(key(), self, scrollbar_styles().scrollbar, false, dim);

		float cursor = -content.frame().m_position[dim];
		if(cursor > 0.f && content_size - cursor < visible_size)
			cursor = max(content_size - visible_size, 0.f);

		Widget rewind = button(key(), scrollbar, dim == Axis::Y ? scrollbar_styles().scroll_up
														  : scrollbar_styles().scroll_left);

		scroller(key(), scrollbar, cursor, overflow, visible_size, dim);

		Widget forward = button(key(), scrollbar, dim == Axis::Y ? scrollbar_styles().scroll_down
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
