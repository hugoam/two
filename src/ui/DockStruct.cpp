//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	Dock::Dock()
	{}

	Dock::Dock(Docker& docker, cstring name, vector<uint16_t> dockid, float span)
		: m_docker(&docker)
		, m_name(name)
		, m_dockid(dockid)
		, m_span(span)
	{}

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
		remove(m_docks, (Dock*)&dockable);

		dockable.m_dock->m_dockid = {};
	}

	void Docker::shift(Dock& start, bool add)
	{
		vector<uint16_t> root = start.m_dockid;
		uint16_t index = pop(root);

		size_t level = root.size();
		for(Dock* dock : m_docks)
			if(contains(dock->m_dockid, root)
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

	Dockspace::~Dockspace()
	{
		for(Dock* dock : m_docks)
		{
			m_docksystem->m_docks.erase(dock->m_name);
		}
	}

	Dockable& Dockspace::pinpoint_dock(const vec2& pos)
	{
		Widget* widget = this->pinpoint(pos, [](Frame& frame) { return frame.d_style == &ui::dock_styles().docksection; });
		return static_cast<Dockable&>(*widget);
	}

	Widget* Dockspace::docksection(Dock& dock)
	{
		vector<uint16_t> dockid = reverse(dock.m_dockid);
		Widget* line = m_mainline;

		Axis dim = Axis::Y;
		while(dockid.size() > 0)
		{
			uint16_t index = pop(dockid);
			dim = flip(dim);
			line = &ui::dockline(*line, index, dim);
			if(dockid.size() == 0 && dock.m_span > 0.f && line->m_frame.m_span[flip(dim)] == 1.f)
				line->m_frame.set_span(flip(dim), dock.m_span);
		}

		Tabber& section = ui::docksection(*line);
		Widget* tab = ui::tab(section, dock.m_name); // dock_styles().docktab, 

		if(tab)
		{
			Window& container = ui::window(*tab, dock.m_name, WindowState::Dockable, nullptr, &dock);
			return container.m_body;
		}

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

		Axis dim = Axis(target.m_dockid.size() % 2);
		Axis ortho = flip(dim);

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
		string icon = "(" + to_lower(replace(dock.m_name, " ", "")) + ")";
		Widget& toggle = ui::button(*m_togglebar, ui::dock_styles().docktoggle, icon.c_str());
		if(toggle.activated())
			m_current_tab = m_current_tab == dock.m_dockid.back() ? SIZE_MAX : dock.m_dockid.back();
		toggle.set_state(ACTIVE, m_current_tab == dock.m_dockid.back());

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
