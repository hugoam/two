//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui/Generated/Types.h>
#include <ui/Structs/Dock.h>
#include <ui/Structs/Window.h>
#include <ui/Dock.h>
#include <ui/Window.h>

#include <obj/Vector.h>
#include <ui/Frame/Layer.h>
#include <obj/String/String.h>

namespace mud
{
	Dock::Dock()
	{}

	Dock::Dock(Docker& docker, cstring name, std::vector<size_t> dockid)
		: m_docker(&docker)
		, m_name(name)
		, m_dockid(dockid)
	{
		docker.m_docks.push_back(this);
	}

	Dockable::Dockable(Widget* parent, void* identity)
		: Widget(parent, identity)
	{}

	Docker::Docker(Widget* parent, void* identity, Docksystem& docksystem)
		: Widget(parent, identity)
		, m_docksystem(&docksystem)
	{}

	void Docker::dock_split(Dock& dock, Dock& target, bool after)
	{
		m_docks.push_back(&dock);
		dock.m_dockid = target.m_dockid;
		dock.m_dockid.push_back(after ? 0 : 1);
		target.m_dockid.push_back(after ? 1 : 0);
	}

	void Docker::dock_insert(Dock& dock, Dock& target, bool after)
	{
		m_docks.push_back(&dock);
		dock.m_dockid = target.m_dockid;
		after ? dock.m_dockid.back()++
			  : target.m_dockid.back()++;
		this->shift(after ? dock : target, true);
	}

	void Docker::undock(Dockable& dockable)
	{
		vec2 absolute = dockable.m_frame.absolute_position();
		dockable.m_frame.set_position(absolute);
		dockable.m_frame.m_layer->moveToTop();

		this->shift(*dockable.m_dock, false);
		vector_remove(m_docks, (Dock*)&dockable);

		dockable.m_dock->m_dockid = {};
	}

	void Docker::shift(Dock& start, bool add)
	{
		std::vector<size_t> root = start.m_dockid;
		size_t index = vector_pop(root);

		size_t level = root.size();

		for(Dock* dock : m_docks)
			if(vector_contains(dock->m_dockid, root)
				&& dock->m_dockid[level] > index)
			{
				dock->m_dockid[level] += (add ? 1 : -1);
			}
	}

	Docksystem::Docksystem()
	{}

	void Docksystem::dock(Dockable& item, const vec2& pos)
	{
		for(Docker* docker : m_dockers)
			if(docker->m_frame.inside_abs(pos))
				docker->dock(item, pos);
	}

	Dockspace::Dockspace(Widget* parent, void* identity, Docksystem& docksystem)
		: Docker(parent, identity, docksystem)
	{}

	Dockable& Dockspace::pinpoint_dock(const vec2& pos)
	{
		Widget* widget = this->pinpoint(pos, [](Frame& frame) { return frame.d_style == &ui::dock_styles().docksection; });
		return as<Dockable>(*widget);
	}

	Widget* Dockspace::docksection(Dock& dock)
	{
		std::vector<size_t> dockid = vector_reverse(dock.m_dockid);
		Widget* line = m_mainline;

		Dim dim = DIM_Y;
		while(dockid.size() > 0)
		{
			uint16_t index = vector_pop(dockid);
			dim = flip_dim(dim);
			line = &ui::dockline(*line, index, dim);
		}

		Tabber& section = ui::docksection(*line);
		Widget* tab = ui::tab(section, dock.m_name); // dock_styles().docktab, 
#if 1
		if(tab)
		{
			Window& container = ui::window(*tab, dock.m_name, static_cast<WindowState>(WINDOW_DOCKABLE | WINDOW_DEFAULT), nullptr, &dock);
			return container.m_body;
		}
#endif
		return tab;
	}

	void Dockspace::dock(Dockable& widget, const vec2& pos)
	{
		Dockable& target = pinpoint_dock(pos);
		this->dock(*widget.m_dock, *target.m_dock, target.m_frame, pos);
	}

	void Dockspace::dock(Dock& dock, Dock& target, Frame& frame, const vec2& pos)
	{
		vec2 local = frame.local_position(pos);

		Dim dim = Dim(target.m_dockid.size() % 2);
		Dim ortho = flip_dim(dim);

		if(local[dim] < frame.m_size[dim] * 0.25f)
			this->dock_split(dock, target, false); // dock split first
		else if(local[dim] > frame.m_size[dim] * 0.75f)
			this->dock_split(dock, target, true); // dock split second
		else if(local[ortho] < frame.m_size[ortho] * 0.25f)
			this->dock_insert(dock, target, false); // dock before
		else if(local[ortho] > frame.m_size[ortho] * 0.75f)
			this->dock_insert(dock, target, true); // dock after
		else
			dock.m_dockid = target.m_dockid; // dock on
	}

	Dockbar::Dockbar(Widget* parent, void* identity, Docksystem& docksystem)
		: Docker(parent, identity, docksystem)
	{}

	Widget* Dockbar::docksection(Dock& dock)
	{
		string icon = "(" + to_lower(replace_all(dock.m_name, " ", "")) + ")";
		Widget& toggle = ui::button(*m_togglebar, ui::dock_styles().docktoggle, icon.c_str());
		if(toggle.activated())
			m_current_tab = m_current_tab == dock.m_dockid.back() ? SIZE_MAX : dock.m_dockid.back();
		toggle.setState(ACTIVE, m_current_tab == dock.m_dockid.back());

		if(m_current_tab == dock.m_dockid.back())
			return ui::window(*m_dockzone, dock.m_name, static_cast<WindowState>(0), &dock, &dock).m_body; // dock_styles().dockbox
		else
			return nullptr;
	}

	void Dockbar::dock(Dockable& widget, const vec2& pos)
	{
		UNUSED(widget); UNUSED(pos);
#if 0
		Dock* target = m_docks[0];
		for(Dock* dock : m_docks)
			if(pos.y < dock->m_frame->absolute_position().y)
			{
				target = dock;
				break;
			}

		this->dock_insert(*widget.m_dock, *target, false);
#endif
	}
}
