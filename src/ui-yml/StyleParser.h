//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>

namespace two
{
	using cstring = const char*;
	TWO_UI_EXPORT void load_style_sheet(UiWindow& ui_window, cstring path);
	TWO_UI_EXPORT void set_style_sheet(UiWindow& ui_window, cstring path);
	TWO_UI_EXPORT void set_default_style_sheet(UiWindow& ui_window);
}
