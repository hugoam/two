//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Cursor.h>
#include <ui/Structs/Widget.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Frame/Caption.h>
#include <ui/Style/Skin.h>
#endif

namespace mud
{
namespace ui
{
	Widget* tooltip(Widget& parent, const vec2& position, float delay)
	{
		RootSheet& root_sheet = parent.root_sheet();

		if(&parent == root_sheet.m_hovered && root_sheet.m_tooltip_clock.read() > delay)
		{
			Widget& self = widget(root_sheet, styles().tooltip).layer();
			self.m_frame.set_position(parent.m_frame.absolute_position() + position);
			return &self;
		}

		return nullptr;
	}

	Widget* tooltip(Widget& parent, float delay)
	{
		return tooltip(parent, parent.root_sheet().m_mouse.m_pos + vec2(4.f) - parent.m_frame.absolute_position(), delay);
	}

	Widget* tooltip(Widget& parent, const vec2& position, array<cstring> elements)
	{
		Widget* self = tooltip(parent, position);
		if(self)
			multi_item(parent, styles().tooltip, elements).layer();
		return self;
	}

	Widget* tooltip(Widget& parent, const vec2& position, cstring content)
	{
		return tooltip(parent, position, { &content, 1 });
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame)
	{
		return tooltip(parent, vec2{ 0.f, 0.f + parent_frame.m_size.y });
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame, array<cstring> elements)
	{
		return tooltip(parent, vec2{ parent_frame.m_position.x, parent_frame.m_position.y + parent_frame.m_size.y }, elements);
	}

	Widget* tooltip(Widget& parent, const Frame& parent_frame, cstring element)
	{
		return tooltip(parent, parent_frame, { &element, 1 });
	}

	Widget& rectangle(Widget& parent, const vec4& rect)
	{
		Widget& self = widget(parent, styles().rectangle).layer();
		self.m_frame.set_position(rect_offset(rect));
		self.m_frame.set_size(rect_size(rect));
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
		Style* style = hovered.m_frame.d_style->skin().m_hover_cursor ? hovered.m_frame.d_style->skin().m_hover_cursor : &cursor_styles().cursor;
		return cursor(parent, position, *style, locked);
	}
}
}
