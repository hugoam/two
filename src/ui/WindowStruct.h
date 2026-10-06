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
	// a window, with its header and its menu if it has them: the content goes in the body, which is there when it's open
	export_ struct Window
	{
		Widget self;
		Widget header;
		Widget menu;
		Widget body;
		operator Widget() const { return self; }
	};
}
