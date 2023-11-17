//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <cassert>
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
namespace ui
{
	void widget_logic(Widget& self)
	{
		if(MouseEvent event = self.mouse_event(DeviceType::Mouse, EventType::Heartbeat))
			self.enable_state(HOVERED);
		else
			self.disable_state(HOVERED);
	}

	Widget& widget(Widget& parent, Style& style, void* identity)
	{
		Widget& self = parent.subi(identity).init(style);
		assert(self.m_frame.d_style);
		widget_logic(self);
		return self;
	}

	Widget& widget(Widget& parent, Style& style, bool open, Axis length, v2<uint> index)
	{

		Widget& self = parent.subi(&style).init(style, open, length, index);
		assert(self.m_frame.d_style);
		widget_logic(self);
		return self;
	}

	Widget& item(Widget& parent, Style& style, cstring content)
	{
		Widget& self = widget(parent, style);
		if(content != nullptr)
			self.set_content(content);
		return self;
	}

	Widget& item(Widget& parent, Style& style, const string& content)
	{
		return item(parent, style, content.c_str());
	}

	Widget& multi_item(Widget& parent, Style& style, span<cstring> elements, Style* element_style)
	{
		Widget& self = widget(parent, style);
		for(cstring value : elements)
			item(self, element_style ? *element_style : styles().item, value);
		return self;
	}

	Widget& multi_item(Widget& parent, span<cstring> elements, Style* element_style)
	{
		return multi_item(parent, styles().row, elements, element_style);
	}

	Widget& spanner(Widget& parent, Style& style, Axis dim, float span)
	{
		Widget& self = widget(parent, style);
		self.m_frame.set_span(dim, span);
		return self;
	}
}
}
