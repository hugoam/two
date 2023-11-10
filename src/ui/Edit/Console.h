//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Sheet.h>
#include <ui/Edit/TypeIn.h>

namespace two
{
namespace ui
{
	export_ TWO_UI_EXPORT func_ Widget& command_line(Widget& parent, string& text, string& command);
	export_ TWO_UI_EXPORT func_ Widget& console(Widget& parent, string& feed, string& line, string& command, size_t num_lines = 0);
}
}
