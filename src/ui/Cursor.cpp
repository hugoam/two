//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

#include <cstdio>

namespace two
{
namespace ui
{
	Widget* hoverbox(NodeKey id, Widget& parent, const vec2& position, float delay)
	{
		Ui& ui = parent.ui();

		if(&parent == ui.m_hovered && ui.m_tooltip_clock.read() > delay)
		{
			Widget& self = widget(id, ui, styles().tooltip).layer();
			self.m_frame.set_position(parent.m_frame.absolute_position() + position);
			return &self;
		}

		return nullptr;
	}

	Widget* hoverbox(NodeKey id, Widget& parent, float delay)
	{
		const vec2 position = parent.ui().m_mouse.m_pos + vec2(4.f) - parent.m_frame.absolute_position();
		return hoverbox(id, parent, position, delay);
	}

	Widget* tooltip(NodeKey id, Widget& parent, const vec2& position, span<cstring> elements)
	{
		Widget* self = hoverbox(id, parent, position);
		if(self)
			multi_item(key(), *self, styles().tooltip, elements);
		return self;
	}

	Widget* tooltip(NodeKey id, Widget& parent, span<cstring> elements)
	{
		const vec2 position = parent.ui().m_mouse.m_pos + vec2(4.f) - parent.m_frame.absolute_position();
		return tooltip(id, parent, position, elements);
	}

	Widget* tooltip(NodeKey id, Widget& parent, cstring element)
	{
		return tooltip(id, parent, { &element, 1 });
	}

	Widget* tooltip(NodeKey id, Widget& parent, const Frame& parent_frame)
	{
		return hoverbox(id, parent, vec2(0.f, 0.f + parent_frame.m_size.y));
	}

	Widget* tooltip(NodeKey id, Widget& parent, const Frame& parent_frame, span<cstring> elements)
	{
		return tooltip(id, parent, vec2(parent_frame.m_position.x, parent_frame.m_position.y + parent_frame.m_size.y), elements);
	}

	Widget* tooltip(NodeKey id, Widget& parent, const Frame& parent_frame, cstring element)
	{
		return tooltip(id, parent, parent_frame, { &element, 1 });
	}

	Widget& rectangle(NodeKey id, Widget& parent, const vec4& rect)
	{
		Widget& self = widget(id, parent, styles().rectangle).layer();
		self.m_frame.set_position(rect.pos);
		self.m_frame.set_size(rect.size);
		return self;
	}

	Widget& viewport(NodeKey id, Widget& parent, const vec4& rect)
	{
		Widget& self = widget(id, parent, styles().viewport).layer();
		self.m_frame.set_position(rect.pos);
		self.m_frame.set_size(rect.size);
		return self;
	}

	Widget& cursor(NodeKey id, Widget& parent, const vec2& position, Style& style, bool locked)
	{
		UNUSED(locked);
		Widget& self = widget(id, parent, style).layer();
		self.m_frame.set_position(position);
		return self;
	}

	Widget& cursor(NodeKey id, Widget& parent, const vec2& position, Widget& hovered, bool locked)
	{
		Style* style = hovered.m_frame.d_style->m_skin.m_hover_cursor ? hovered.m_frame.d_style->m_skin.m_hover_cursor : &cursor_styles().cursor;
		return cursor(id, parent, position, *style, locked);
	}
}
}
