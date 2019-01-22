//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/stringfwd.h>
#include <infra/Array.h>
#include <ui/Forward.h>
#include <ui/Frame/Dim.h>

namespace mud
{
	export_ namespace ui
	{}

	using cstring = const char*;

	export_ enum refl_ WidgetState : unsigned int
	{
		NOSTATE = 0,			// default state
		CREATED = 1 << 0,		// just created
		HOVERED = 1 << 1,		// hovered by an input device
		PRESSED = 1 << 2,		// pressed by an input device
		ACTIVATED = 1 << 3,		// activated (event-like state)
		ACTIVE = 1 << 4,		// active (on/off state)
		SELECTED = 1 << 5,		// selected (on/off state)
		DISABLED = 1 << 6,		// disabled (on/off state)
		DRAGGED = 1 << 7,		// dragged by input device
		FOCUSED = 1 << 8,		// has exclusive focus in the widget hierarchy
		CLOSED = 1 << 9			// widget has just been closed
	};

namespace ui
{
	export_ MUD_UI_EXPORT func_ Widget& widget(Widget& parent, Style& style, bool open = false, Dim length = DIM_NONE, Dim2<size_t> index = { 0, 0 });
	export_ MUD_UI_EXPORT Widget& widget(Widget& parent, Style& style, void* identity);

	export_ MUD_UI_EXPORT func_ Widget& item(Widget& parent, Style& style, cstring content = nullptr);
	export_ MUD_UI_EXPORT Widget& item(Widget& parent, Style& style, const string& content);

	export_ MUD_UI_EXPORT func_ Widget& multi_item(Widget& parent, Style& style, array<cstring> elements, Style* element_style = nullptr);
	export_ MUD_UI_EXPORT Widget& multi_item(Widget& parent, array<cstring> elements, Style* element_style = nullptr);

	export_ MUD_UI_EXPORT func_ Widget& spanner(Widget& parent, Style& style, Dim dim, float span);
}
}
