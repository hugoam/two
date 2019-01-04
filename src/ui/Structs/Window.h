//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Structs/Widget.h>
#include <ui/Structs/Dock.h>
#include <ui/Window.h>

namespace mud
{
	export_ class refl_ MUD_UI_EXPORT Window : public Dockable
	{
	public:
		Window(Widget* parent, void* identity)
			: Dockable(parent, identity)
		{}

		bool header() { return (m_window_state & WINDOW_HEADER) != 0; }
		bool closable() { return (m_window_state & WINDOW_CLOSABLE) != 0; }
		bool dockable() { return (m_window_state & WINDOW_DOCKABLE) != 0; }
		bool movable() { return (m_window_state & WINDOW_MOVABLE) != 0; }
		bool sizable() { return (m_window_state & WINDOW_SIZABLE) != 0; }

		WindowState m_window_state;
	};
}
