//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Style/Style.h>
#include <ui/Widget.h>

namespace mud
{
	export_ enum refl_ WindowState : unsigned int
	{
		WINDOW_NOSTATE = 0,
		WINDOW_HEADER = 1 << 1,
		WINDOW_DOCKABLE = 1 << 2,
		WINDOW_CLOSABLE = 1 << 3,
		WINDOW_MOVABLE = 1 << 4,
		WINDOW_SIZABLE = 1 << 5,
		WINDOW_DEFAULT = WINDOW_HEADER | WINDOW_MOVABLE | WINDOW_SIZABLE | WINDOW_CLOSABLE
	};

namespace ui
{
	export_ struct WindowStyles
	{
		WindowStyles();
		Style window; Style body; Style close_button; Style header; Style header_movable; Style footer; Style sizer; Style sizer_left; Style sizer_right;
		Style dock_window; Style wrap_window;
	};

	export_ MUD_UI_EXPORT WindowStyles& window_styles();

	export_ func_ MUD_UI_EXPORT Window& window(Widget& parent, cstring title, WindowState state = WINDOW_DEFAULT);
	export_ MUD_UI_EXPORT Window& window(Widget& parent, cstring title, WindowState state, void* identity, Dock* dock = nullptr);
}
}
