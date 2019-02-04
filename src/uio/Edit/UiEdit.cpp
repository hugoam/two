//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <infra/ToString.h>
#include <ui/Ui.h>
#include <ui/Section.h>
#include <ui/Frame/Layer.h>
#include <ui/Structs/Container.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Controller/Controller.h>
#include <uio/Edit/UiEdit.h>
#include <uio/Edit/Inspector.h>
#include <uio/Edit/Structure.h>
#endif

namespace mud
{
	void ui_debug_modal(Widget& parent, Widget& target)
	{
		Widget* current_node = &parent;
		Widget* current_target = &target.ui();
		while(current_target && current_node)
		{
			string elements[2] = { current_target->m_frame.d_style->name(), to_string(current_target->m_control.m_mask) };
			current_node = ui::tree_node(*current_node, { elements[0].c_str(), elements[1].c_str() }).m_body;
			current_target = static_cast<Widget*>(current_target->m_control.m_modal);
		}
	}

	void ui_debug_layout_node(Widget& parent, Widget& target, Widget*& selected)
	{
		for(auto& widget : target.m_nodes)
		{
			string size = "size : " + truncate_number(to_string(widget->m_frame.m_size.x)) + ", " + truncate_number(to_string(widget->m_frame.m_size.y));
			TreeNode& node = ui::tree_node(parent, { widget->m_frame.d_style->name(), size.c_str() });
			node.m_header->set_state(SELECTED, selected == widget.get());
			if(node.m_header->activated())
				selected = widget.get();
			if(node.m_body)
				ui_debug_layout_node(*node.m_body, *widget, selected);
		}
	}

	void ui_debug_layout(Widget& parent, Widget& target, Widget*& selected)
	{
		ScrollSheet& scroll_sheet = ui::scroll_sheet(parent);
		ui_debug_layout_node(*scroll_sheet.m_body, target, selected);
	}

	void ui_debug(Widget& parent, Widget& target)
	{
		static Widget* selected = nullptr;
		static bool selecting = false;

		Section& self = section(parent, "Ui Edit");
		ui::toggle(*self.m_toolbar, selecting, "Select Mode");

		Tabber& tabber = ui::tabber(*self.m_body);
		if(Widget* tab = ui::tab(tabber, "Modal"))
			ui_debug_modal(*tab, target);
		if(Widget* tab = ui::tab(tabber, "Layout"))
			ui_debug_layout(*tab, target, selected);

		if(selected)
			ui::rectangle(parent.ui(), { selected->m_frame.absolute_position(), selected->m_frame.m_size });

		if(selecting)
		{
			Widget* highlighted = target.pinpoint(target.ui().m_mouse.m_pos);
			if(highlighted)
				ui::rectangle(parent.ui(), { highlighted->m_frame.absolute_position(), highlighted->m_frame.m_size });
		}

		if(selected)
		{
			if(Widget* tab = ui::tab(tabber, "Widget"))
				object_edit(*tab, Ref(selected));

			if(Widget* tab = ui::tab(tabber, "Style"))
				object_edit(*tab, Ref(selected->m_frame.d_layout));
			if(Widget* tab = ui::tab(tabber, "Skin"))
				object_edit(*tab, Ref(&selected->m_frame.d_style->skin()));
		}
	}
}
