//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <uio/Generated/Types.h>
#include <uio/Edit/Section.h>

#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/Structs/Container.h>

namespace mud
{
	Style& section_style()
	{
		// STACK
		static Style style = { "Section", styles().sheet, [](Layout& l) { l.m_padding = vec4{ 2.f }; } };
		return style;
	}

	Widget& section_actions(Widget& parent, const ActionList& actions)
	{
		Widget& self = ui::toolbar(parent);
		for(const SectionAction& action : actions)
			if(ui::button(self, action.m_name.c_str()).activated())
				action.m_action();
		return self;
	}

	Section& section(Widget& parent, cstring name, const ActionList& actions, bool no_toolbar)
	{
		Section& self = ui::twidget<Section>(parent, section_style());
		ui::title_header(self, name);

		if(!no_toolbar)
			self.m_toolbar = &section_actions(self, actions);

		ScrollSheet& scroll_sheet = ui::scroll_sheet(self);
		self.m_body = &ui::sheet(*scroll_sheet.m_body);
		return self;
	}
}
