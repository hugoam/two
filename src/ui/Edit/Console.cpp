//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Edit/Console.h>
#endif

namespace mud
{
namespace ui
{
	Widget& command_line(Widget& parent, string& text, string& command)
	{
		string console_chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,:;+-*=~!()[]{}'\"\t";
		Widget& self = ui::type_in(parent, text, 1, console_chars);

		if(self.key_event(KC_RETURN))
		{
			command = text;
			text = "";
			self.key_event(KC_RETURN).consume(self);
		}

		return self;
	}

	Widget& console(Widget& parent, string& feed, string& line, string& command, size_t num_lines)
	{
		//ui::stack(self);
		Widget& self = ui::sheet(parent);
		ui::text_edit(self, feed, num_lines);
		ui::command_line(self, line, command);
		
		if(command != "")
			feed += "\n>> " + command;

		return self;
	}
}
}
