//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.ui;
#else
#include <math/Vec.hpp>
#include <math/Timer.h>
#include <ui/Cursor.h>
#include <ui/WidgetStruct.h>
#include <ui/UiRoot.h>
#include <ui/Frame/Caption.h>
#include <ui/Style/Skin.h>
#endif

#include <cstdio>

namespace two
{
namespace ui
{
	Widget* hoverbox(Widget& parent, const vec2& position, float delay)
	{
		Ui& ui = parent.ui();

		if(&parent == ui.m_hovered && ui.m_tooltip_clock.read() > delay)
		{
			Widget& self = widget(ui, styles().tooltip).layer();
			self.m_frame.set_position(parent.m_frame.absolute_position() + position);
			return &self;
		}

		return nullptr;
	}

	Widget* hoverbox(Widget& parent, float delay)
	{
		const vec2 position = parent.ui().m_mouse.m_pos + vec2(4.f) - parent.m_frame.absolute_position();
		return hoverbox(parent, position, delay);
	}

	Widget* tooltip(Widget& parent, const vec2& position, span<cstring> elements)
	{
		Widget* self = hoverbox(parent, position);
		if(self)
			multi_item(*self, styles().tooltip, elements);
		return self;
	}

	Widget* tooltip(Widget& parent, span<cstring> elements)
	{
		const vec2 position = parent.ui().m_mouse.m_pos + vec2(4.f) - parent.m_frame.absolute_position();
		return tooltip(parent, position, elements);
	}

	Widget* tooltip(Widget& parent, cstring element)
	{
		return tooltip(parent, { &element, 1 });
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame)
	{
		return hoverbox(parent, vec2(0.f, 0.f + parent_frame.m_size.y));
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame, span<cstring> elements)
	{
		return tooltip(parent, vec2(parent_frame.m_position.x, parent_frame.m_position.y + parent_frame.m_size.y), elements);
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame, cstring element)
	{
		return tooltip(parent, parent_frame, { &element, 1 });
	}

	Widget& rectangle(Widget& parent, const vec4& rect)
	{
		Widget& self = widget(parent, styles().rectangle).layer();
		self.m_frame.set_position(rect.pos);
		self.m_frame.set_size(rect.size);
		return self;
	}

	Widget& viewport(Widget& parent, const vec4& rect)
	{
		Widget& self = widget(parent, styles().viewport).layer();
		self.m_frame.set_position(rect.pos);
		self.m_frame.set_size(rect.size);
		return self;
	}

	Widget& cursor(Widget& parent, const vec2& position, Style& style, bool locked)
	{
		UNUSED(locked);
		Widget& self = widget(parent, style).layer();
		self.m_frame.m_position = position;
		return self;
	}

	Widget& cursor(Widget& parent, const vec2& position, Widget& hovered, bool locked)
	{
		Style* style = hovered.m_frame.d_style->m_skin.m_hover_cursor ? hovered.m_frame.d_style->m_skin.m_hover_cursor : &cursor_styles().cursor;
		return cursor(parent, position, *style, locked);
	}
}
}
