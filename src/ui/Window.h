//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Style/Style.h>
#include <ui/Widget.h>

namespace two
{
	export_ enum class refl_ WindowState : unsigned int
	{
		None = 0,
		Header = 1 << 1,
		Dockable = 1 << 2,
		Closable = 1 << 3,
		Movable = 1 << 4,
		Sizable = 1 << 5,
		Scrollable = 1 << 6,
		Menu = 1 << 7,
		Default = Header | Movable | Sizable | Closable | Scrollable
	};

namespace ui
{
	export_ struct WindowStyles
	{
		void reset();
		Style window; Style body; Style close_button; Style header; Style header_movable; Style footer; Style sizer; Style sizer_left; Style sizer_right;
		Style dock_window; Style wrap_window;
	};

	export_ TWO_UI_EXPORT WindowStyles& window_styles();

	export_ func_ TWO_UI_EXPORT Window& window(Widget& parent, cstring title, WindowState state = WindowState::Default);
	export_ TWO_UI_EXPORT Window& window(Widget& parent, cstring title, WindowState state, void* identity, Dock* dock = nullptr);
}
}
