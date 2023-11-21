//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
namespace ui
{
	Widget& command_line(Widget& parent, string& text, string& command)
	{
		string console_chars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,:;+-*=~!()[]{}'\"\t";
		Widget& self = ui::type_in(parent, text, 1, console_chars);

		if(self.key_stroke(Key::Return))
		{
			command = text;
			text = "";
			self.key_stroke(Key::Return).consume(self);
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
