//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui/Dock.h>
#include <ui/Structs/Dock.h>
#include <ui/Structs/Window.h>
#include <ui/Structs/Container.h>

#include <obj/Vector.h>

#include <map>
#include <string>

namespace mud
{
	using string = std::string;

namespace ui
{
	Widget& dockline(Widget& parent, size_t index, Dim dim)
	{
		if(parent.m_nodes.size() > index && parent.m_nodes[index]->m_heartbeat == parent.m_heartbeat)
			return *parent.m_nodes[index];
		Widget& self = parent.sub(index).init(dock_styles().dockline, false, dim);
		grid_sheet_logic(self, dim);
		return self;
	}

	Tabber& docksection(Widget& parent)
	{
		if(parent.m_nodes.size() > 0 && parent.m_nodes[0]->m_heartbeat == parent.m_heartbeat)
			return as<Tabber>(*parent.m_nodes[0]);
		Widget& section = ui::widget(parent, dock_styles().docksection); // dockid.back()
		Tabber& tabber = ui::tabber(section); // dockspace_styles().docksection, 
		return tabber;
	}

	Dockspace& dockspace(Widget& parent, Docksystem& docksystem)
	{
		Dockspace& self = parent.child_args<Dockspace, Docksystem&>(docksystem);
		self.init(dock_styles().dockspace);
		self.m_mainline = &dockline(self, 0, DIM_Y);
		return self;
	}

	Dockbar& dockbar(Widget& parent, Docksystem& docksystem)
	{
		Dockbar& self = parent.child_args<Dockbar, Docksystem&>(docksystem);
		self.init(dock_styles().dockbar);

		self.m_togglebar = &widget(self, dock_styles().docktabs);

		static float width = 300.f;

		Widget& drag_handle = widget(self, styles().drag_handle);
		if(MouseEvent mouse_event = drag_handle.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			width -= mouse_event.m_delta.x;

		self.m_dockzone = &widget(self, dock_styles().dockdiv);
		if(self.m_current_tab == SIZE_MAX)
			self.m_dockzone->m_frame.m_size = { 0.f, 0.f };
		else
			self.m_dockzone->m_frame.m_size = { width, 0.f };

		return self;
	}

	Widget* dockitem(Widget& parent, Docksystem& docksystem, Dock& dock)
	{
		UNUSED(docksystem);
		if(dock.m_dockid.size() > 0)
		{
			return dock.m_docker->docksection(dock);
		}
		else
		{
			Window& container = window(parent, dock.m_name, static_cast<WindowState>(WINDOW_DOCKABLE | WINDOW_DEFAULT), &dock);
			container.m_dock = &dock;
			return &container;
		}
	}

	Widget* dockitem(Docker& docker, cstring name, array<size_t> dockid)
	{
		static std::map<string, Dock> docks;
		if(docks.find(name) == docks.end())
		{
			docks[name] = { docker, name, to_vector(dockid) };
		}
		return dockitem(docker, *docker.m_docksystem, docks[name]);
	}
}
}
