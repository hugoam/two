//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <uio/Edit/UiEdit.h>

#include <ui/Frame/Layer.h>
#include <ui/Structs/Container.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Controller/Controller.h>
#include <ui/Generated/Convert.h>

#include <uio/Edit/Section.h>
#include <uio/Edit/Inspector.h>
#include <uio/Edit/Structure.h>

namespace mud
{
	void ui_debug_modal(Widget& parent, Widget& target)
	{
		Widget* current_node = &parent;
		Widget* current_target = &target.root_sheet();
		while(current_target)
		{
			string elements[2] = { current_target->m_frame.d_style->name(), to_string(current_target->m_control.m_mask) };
			current_node = ui::tree_node(*current_node, carray<cstring, 2>{ elements[0].c_str(), elements[1].c_str() }).m_body;
			current_target = static_cast<Widget*>(current_target->m_control.m_modal);
		}
	}

	void ui_debug_layout_node(Widget& parent, Widget& target, Widget*& selected)
	{
		for(auto& widget : target.m_nodes)
		{
			string size = "size : " + truncate_number(to_string(widget->m_frame.m_size.x)) + ", " + truncate_number(to_string(widget->m_frame.m_size.y));
			TreeNode& node = ui::tree_node(parent, carray<cstring, 2>{ widget->m_frame.d_style->name(), size.c_str() });
			node.m_header->setState(SELECTED, selected == widget.get());
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
			ui::rectangle(parent.root_sheet(), { selected->m_frame.absolute_position(), selected->m_frame.m_size });

		if(selecting)
		{
			Widget* highlighted = target.pinpoint(target.root_sheet().m_mouse.m_last_pos);
			if(highlighted)
				ui::rectangle(parent.root_sheet(), { highlighted->m_frame.absolute_position(), highlighted->m_frame.m_size });
		}

		if(selected)
		{
			if(Widget* tab = ui::tab(tabber, "Widget"))
				object_edit(*tab, selected);

			if(Widget* tab = ui::tab(tabber, "Style"))
				object_edit(*tab, &selected->m_frame.d_style->layout());
			if(Widget* tab = ui::tab(tabber, "Skin"))
				object_edit(*tab, &selected->m_frame.d_style->skin());
		}
	}
}
