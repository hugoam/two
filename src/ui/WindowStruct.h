//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/WidgetStruct.h>
#include <ui/DockStruct.h>
#include <ui/Window.h>

namespace two
{
	export_ class refl_ TWO_UI_EXPORT Window : public Dockable
	{
	public:
		Window(Widget* parent, void* identity)
			: Dockable(parent, identity)
		{}

		bool header()   { return (uint(m_window_state) & uint(WindowState::Header)) != 0; }
		bool closable() { return (uint(m_window_state) & uint(WindowState::Closable)) != 0; }
		bool dockable() { return (uint(m_window_state) & uint(WindowState::Dockable)) != 0; }
		bool movable()  { return (uint(m_window_state) & uint(WindowState::Movable)) != 0; }
		bool sizable()  { return (uint(m_window_state) & uint(WindowState::Sizable)) != 0; }
		bool hasmenu()  { return (uint(m_window_state) & uint(WindowState::Menu)) != 0; }

		attr_ WindowState m_window_state;

		attr_ Widget* m_menu = nullptr;
	};
}
