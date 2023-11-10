//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <stl/string.h>
#include <stl/map.h>
#include <stl/algorithm.h>
#include <infra/Vector.h>
#include <tree/Graph.hpp>
#include <ui/Dock.h>
#include <ui/DockStruct.h>
#include <ui/WindowStruct.h>
#include <ui/ContainerStruct.h>
#endif

namespace two
{
namespace ui
{
	Widget& dockline(Widget& parent, uint16_t index, Axis dim)
	{
		if(parent.m_nodes.size() > index && parent.m_nodes[index]->m_heartbeat == parent.m_heartbeat)
			return *parent.m_nodes[index];
		for(uint16_t i = 0; i < index; ++i)
			parent.subx(i).init(dock_styles().dockline, false, dim);
		Widget& self = parent.subx(index).init(dock_styles().dockline, false, dim);
		grid_sheet_logic(self, dim);
		return self;
	}
	
	Tabber& docksection(Widget& parent)
	{
		if(parent.m_nodes.size() > 0 && parent.m_nodes[0]->m_heartbeat == parent.m_heartbeat)
			return as<Tabber>(*parent.m_nodes[0]);
		//Widget& section = ui::widget(parent, dock_styles().docksection); // dockid.back()
		Tabber& tabber = ui::tabber(parent); // dockspace_styles().docksection, 
		return tabber;
	}

	Dockspace& dockspace(Widget& parent, Docksystem& docksystem)
	{
		Dockspace& self = parent.suba<Dockspace, Docksystem&>(docksystem);
		self.init(dock_styles().dockspace);
		self.m_mainline = &dockline(self, 0, Axis::Y);
		return self;
	}

	Dockbar& dockbar(Widget& parent, Docksystem& docksystem)
	{
		Dockbar& self = parent.suba<Dockbar, Docksystem&>(docksystem);
		self.init(dock_styles().dockbar).layer();

		self.m_togglebar = &widget(self, dock_styles().docktabs);

		Widget& drag_handle = widget(self, styles().drag_handle);
		if(MouseEvent event = drag_handle.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
			self.width -= event.m_delta.x;

		self.m_dockzone = &widget(self, dock_styles().dockdiv);
		if(self.m_current_tab == SIZE_MAX)
			self.m_dockzone->m_frame.m_size = vec2(0.f);
		else
			self.m_dockzone->m_frame.m_size = vec2(self.width, 0.f);

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
			Window& container = window(parent, dock.m_name, WindowState(uint(WindowState::Dockable) | uint(WindowState::Default)), &dock);
			container.m_dock = &dock;
			return &container;
		}
	}

	Widget* dockitem(Docker& docker, cstring name, span<uint16_t> dockid, float span)
	{
		if(docker.m_docksystem->m_docks.find(name) == docker.m_docksystem->m_docks.end())
		{
			docker.m_docksystem->m_docks[name] = { docker, name, to_vector(dockid), span };
			docker.m_docks.push_back(&docker.m_docksystem->m_docks[name]);
		}

		return dockitem(docker, *docker.m_docksystem, docker.m_docksystem->m_docks[name]);
	}
}
}
