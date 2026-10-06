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
		if(parent.child_count() > index && parent.child(index).heartbeat() == parent.heartbeat())
			return parent.child(index);
		for(uint16_t i = 0; i < index; ++i)
			parent.subx(i).init(dock_styles().dockline, false, dim);
		Widget& self = parent.subx(index).init(dock_styles().dockline, false, dim);
		grid_sheet_logic(self, dim);
		return self;
	}
	
	Tabber docksection(Widget& parent)
	{
		// the docks stacked in a section share its tabber, declared by the first of them in the frame
		if(parent.child_count() > 0 && parent.child(0).heartbeat() == parent.heartbeat())
		{
			Widget& self = parent.child(0);
			return { self, self.child(0), self.child(2), self.state<TabberState>() };
		}
		//Widget& section = ui::widget(id, parent, dock_styles().docksection); // dockid.back()
		Tabber tabber = ui::tabber(key(), parent); // dockspace_styles().docksection, 
		return tabber;
	}

	DockspaceHandle dockspace(NodeKey id, Widget& parent, Docksystem& docksystem)
	{
		Widget& self = widget(id, parent, dock_styles().dockspace);
		Dockspace& dockspace = self.state<Dockspace>(docksystem);
		add(docksystem.m_dockers, DockerHandle(self));
		dockspace.apply_pending(self);
		dockspace.m_docked.clear();
		dockspace.m_mainline = &dockline(self, 0, Axis::Y);
		return DockspaceHandle(self);
	}

	DockbarHandle dockbar(NodeKey id, Widget& parent, Docksystem& docksystem)
	{
		Widget& self = widget(id, parent, dock_styles().dockbar).layer();
		Dockbar& dockbar = self.state<Dockbar>(docksystem);
		add(docksystem.m_dockers, DockerHandle(self));
		dockbar.apply_pending(self);

		dockbar.m_togglebar = &widget(key(), self, dock_styles().docktabs);

		Widget& drag_handle = widget(key(), self, styles().drag_handle);
		if(MouseEvent event = drag_handle.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			dockbar.width -= event.m_delta.x;

		dockbar.m_dockzone = &widget(key(), self, dock_styles().dockdiv);
		if(dockbar.m_current_tab == SIZE_MAX)
			dockbar.m_dockzone->frame().m_size = vec2(0.f);
		else
			dockbar.m_dockzone->frame().m_size = vec2(dockbar.width, 0.f);

		return DockbarHandle(self);
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
				container.self.set_position(mouse.m_pos - parent.absolute_position() - vec2(10.f));
				mouse.fix_press(container.header->control_id());
				docksystem.m_dragged.clear();
			}

			return &container.self;
		}
	}

	Widget* dockitem(DockerHandle docker, cstring name, span<uint16_t> dockid, float span)
	{
		// the first time an item is seen, it's stacked in the dock at dockid, or left floating if there is none
		if(!dockid.empty() && !docker->m_docksystem->m_item_docks.contains(name))
			docker->dock_create(name, dockid, span);

		return dockitem(docker.self(), *docker->m_docksystem, name);
	}
}
}
