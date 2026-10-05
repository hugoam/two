//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
namespace ui
{
	Widget& dockline(Widget& parent, uint16_t index, Axis dim)
	{
		if(parent.child_count() > index && parent.child(index).m_heartbeat == parent.m_heartbeat)
			return parent.child(index);
		for(uint16_t i = 0; i < index; ++i)
			parent.subx(i).init(dock_styles().dockline, false, dim);
		Widget& self = parent.subx(index).init(dock_styles().dockline, false, dim);
		grid_sheet_logic(self, dim);
		return self;
	}
	
	Tabber& docksection(Widget& parent)
	{
		if(parent.child_count() > 0 && parent.child(0).m_heartbeat == parent.m_heartbeat)
			return as<Tabber>(parent.child(0));
		//Widget& section = ui::widget(id, parent, dock_styles().docksection); // dockid.back()
		Tabber& tabber = ui::tabber(key(), parent); // dockspace_styles().docksection, 
		return tabber;
	}

	Dockspace& dockspace(NodeKey id, Widget& parent, Docksystem& docksystem)
	{
		Dockspace& self = parent.sub<Dockspace, Docksystem&>(id, docksystem);
		self.init(dock_styles().dockspace);
		add(docksystem.m_dockers, &self);
		self.apply_pending();
		self.m_docked.clear();
		self.m_mainline = &dockline(self, 0, Axis::Y);
		return self;
	}

	Dockbar& dockbar(NodeKey id, Widget& parent, Docksystem& docksystem)
	{
		Dockbar& self = parent.sub<Dockbar, Docksystem&>(id, docksystem);
		self.init(dock_styles().dockbar).layer();
		add(docksystem.m_dockers, &self);
		self.apply_pending();

		self.m_togglebar = &widget(key(), self, dock_styles().docktabs);

		Widget& drag_handle = widget(key(), self, styles().drag_handle);
		if(MouseEvent event = drag_handle.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			self.width -= event.m_delta.x;

		self.m_dockzone = &widget(key(), self, dock_styles().dockdiv);
		if(self.m_current_tab == SIZE_MAX)
			self.m_dockzone->m_frame.m_size = vec2(0.f);
		else
			self.m_dockzone->m_frame.m_size = vec2(self.width, 0.f);

		return self;
	}

	Widget* dockitem(Widget& parent, Docksystem& docksystem, cstring name)
	{
		Dock*& dock = docksystem.m_item_docks[name];
		// the window of an item is the same top node, docked or floating
		NodeKey id = key(&dock);
		if(dock)
		{
			return dock->m_docker->docksection(*dock, name, id);
		}
		else
		{
			Window container = window(id, parent, name, WindowState(uint(WindowState::Dockable) | uint(WindowState::Default)), nullptr, &docksystem);

			if(docksystem.m_dragged == name)
			{
				// the item was just undocked: the drag continues on its floating window, from under the cursor
				Mouse& mouse = container.self.ui().m_mouse;
				container.self.m_frame.set_position(mouse.m_pos - parent.m_frame.absolute_position() - vec2(10.f));
				mouse.fix_press(*container.header);
				docksystem.m_dragged.clear();
			}

			return &container.self;
		}
	}

	Widget* dockitem(Docker& docker, cstring name, span<uint16_t> dockid, float span)
	{
		// the first time an item is seen, it's stacked in the dock at dockid, or left floating if there is none
		if(!dockid.empty() && !docker.m_docksystem->m_item_docks.contains(name))
			docker.dock_create(name, dockid, span);

		return dockitem(docker, *docker.m_docksystem, name);
	}
}
}
