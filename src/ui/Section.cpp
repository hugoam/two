//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	Style& section_style()
	{
		// Preset::Stack
		static Style style = { "Section", styles().sheet, [](Layout& l) { l.m_padding = vec4(2.f); } };
		return style;
	}

	bool section_action(Section& parent, const string& name)
	{
		return ui::button(key(), *parent.toolbar, name).activated();
	}

	Section section(NodeKey id, Widget parent, const string& name, bool no_toolbar)
	{
		Widget self = ui::widget(id, parent, section_style());
		ui::title_header(key(), self, name.c_str());

		Widget toolbar = !no_toolbar ? ui::toolbar(key(), self) : nullptr;

		ScrollSheet scroll_sheet = ui::scroll_sheet(key(), self);
		Widget body = ui::sheet(key(), scroll_sheet.body);
		return { self, toolbar, body };
	}
}
