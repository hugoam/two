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
		return ui::button(*parent.m_toolbar, name).activated();
	}

	Section& section(Widget& parent, const string& name, bool no_toolbar)
	{
		Section& self = ui::twidget<Section>(parent, section_style());
		ui::title_header(self, name.c_str());

		if(!no_toolbar)
			self.m_toolbar = &ui::toolbar(self);

		ScrollSheet& scroll_sheet = ui::scroll_sheet(self);
		self.m_body = &ui::sheet(*scroll_sheet.m_body);
		return self;
	}
}
