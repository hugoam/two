//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	Dock::Dock()
	{}

	Dock::Dock(Docker& docker, vector<uint16_t> dockid, float span)
		: m_docker(&docker)
		, m_dockid(dockid)
		, m_span(span)
	{}

	Dockable::Dockable(Widget* parent)
		: Widget(parent)
	{}

	Docker::Docker(Widget* parent, Docksystem& docksystem)
		: Widget(parent)
		, m_docksystem(&docksystem)
	{}

	Docker::~Docker()
	{
		for(auto& dock : m_docks)
			for(const string& item : dock->m_items)
				m_docksystem->m_item_docks.erase(item);
		remove(m_docksystem->m_dockers, this);
	}

	Dock& Docker::add_dock(vector<uint16_t> dockid, float span)
	{
		// docks are kept sorted by dock id, so the docks under a dock id are contiguous
		auto it = find_if(m_docks.begin(), m_docks.end(), [&](auto& dock) { return dockid < dock->m_dockid; });
		return **m_docks.insert(it, make_unique<Dock>(*this, dockid, span));
	}

	span<unique<Dock>> Docker::sub_docks(span<uint16_t> dockid)
	{
		auto under = [&](auto& dock) { return has_prefix(dock->m_dockid, dockid); };
		auto first = find_if(m_docks.begin(), m_docks.end(), under);
		auto last = find_if(first, m_docks.end(), [&](auto& dock) { return !under(dock); });
		return span<unique<Dock>>(m_docks.data() + (first - m_docks.begin()), size_t(last - first));
	}

	Dock& Docker::dock_split(Dock& target, bool after)
	{
		vector<uint16_t> dockid = target.m_dockid;
		dockid.push_back(after ? 1 : 0);
		target.m_dockid.push_back(after ? 0 : 1);
		return this->add_dock(dockid);
	}

	Dock& Docker::dock_insert(Dock& target, bool after)
	{
		vector<uint16_t> dockid = target.m_dockid;
		if(after) dockid.back()++;
		this->shift_add(dockid);
		return this->add_dock(dockid);
	}

	void Docker::dock_stack(Dock& dock, cstring name)
	{
		dock.m_items.push_back(name);
		m_docksystem->m_item_docks[name] = &dock;
	}

	void Docker::dock_remove(Dock& dock, cstring name)
	{
		remove(dock.m_items, string(name));
		m_docksystem->m_item_docks[name] = nullptr;

		if(dock.m_items.empty())
		{
			vector<uint16_t> line = dock.m_dockid;
			line.pop_back();
			this->shift_remove(dock.m_dockid);
			remove_pt(m_docks, dock);
			this->collapse(line);
		}
	}

	void Docker::collapse(const vector<uint16_t>& line)
	{
		// a line with a single child is not split anymore: its child takes its place, except in the root line
		span<unique<Dock>> docks = this->sub_docks(line);
		size_t level = line.size();
		if(line.empty() || docks.empty() || docks.front()->m_dockid[level] != docks.back()->m_dockid[level])
			return;

		if(docks.size() == 1 && docks[0]->m_dockid.size() == level + 1)
		{
			// the child is a dock: it takes the place of the line
			docks[0]->m_dockid.pop_back();
			return;
		}

		// the child is split: its children take the place of the line in the parent line, which lays them out along the same axis
		span<uint16_t> parent(line, 0, level - 1);
		uint16_t index = line.back();
		uint16_t count = docks.back()->m_dockid[level + 1] + 1;
		for(auto& dock : this->sub_docks(parent))
			if(dock->m_dockid[level - 1] > index)
				dock->m_dockid[level - 1] += count - 1;

		for(auto& dock : docks)
		{
			dock->m_dockid[level + 1] += index;
			dock->m_dockid.erase(dock->m_dockid.begin() + level - 1, dock->m_dockid.begin() + level + 1);
		}
	}

	void Docker::dock_create(cstring name, span<uint16_t> dockid, float span)
	{
		auto target = find(m_docks, [&](auto& look) { return equals(look->m_dockid, dockid); });
		Dock& dock = target ? **target : add_dock(to_vector(dockid), span);
		dock_stack(dock, name);
	}

	void Docker::undock(Dock& dock, cstring name)
	{
		// the drag continues on the floating window created for the item on the next frame
		m_docksystem->m_dragged = name;

		m_pending_undocks.push_back({ &dock, name });
	}

	void Docker::apply_pending()
	{
		for(PendingUndock& undock : m_pending_undocks)
			this->dock_remove(*undock.dock, undock.name.c_str());
		for(PendingDock& dock : m_pending_docks)
			this->dock(dock.name.c_str(), dock.pos);

		m_pending_undocks.clear();
		m_pending_docks.clear();
	}

	void Docker::shift_add(const vector<uint16_t>& dockid)
	{
		// the docks from dockid index in its line move one index forward
		uint16_t index = dockid.back();
		span<uint16_t> root(dockid, 0, dockid.size() - 1);

		size_t level = root.size();
		for(auto& dock : this->sub_docks(root))
			if(dock->m_dockid[level] >= index)
				dock->m_dockid[level]++;
	}

	void Docker::shift_remove(const vector<uint16_t>& dockid)
	{
		// the docks after dockid index in its line move one index back
		uint16_t index = dockid.back();
		span<uint16_t> root(dockid, 0, dockid.size() - 1);

		size_t level = root.size();
		for(auto& dock : this->sub_docks(root))
			if(dock->m_dockid[level] > index)
				dock->m_dockid[level]--;
	}

	Docksystem::Docksystem()
	{}

	void Docksystem::dock(Dockable& item, const vec2& pos)
	{
		for(Docker* docker : m_dockers)
			if(docker->m_frame.inside_abs(pos))
			{
				docker->m_pending_docks.push_back({ item.m_name, pos });
				return;
			}
	}

	Dockspace::Dockspace(Widget* parent, Docksystem& docksystem)
		: Docker(parent, docksystem)
	{}

	Dockable* Dockspace::pinpoint_dock(const vec2& pos)
	{
		Widget* widget = this->pinpoint(m_frame.local_position(pos), [](Frame& frame) { return frame.d_style == &ui::window_styles().dock_window; });
		return static_cast<Dockable*>(widget);
	}

	Widget* Dockspace::docksection(Dock& dock, cstring name, NodeKey id)
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
		size_t index = section.m_index;
		Widget* tab = ui::tab(id, section, name); // dock_styles().docktab, 

		Widget& header = section.m_head->child(uint32_t(index));
		if(header.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			this->undock(dock, name);
			return nullptr;
		}

		if(tab)
		{
			Window& container = ui::window(id, *tab, name, WindowState::Dockable, &dock);
			return container.m_body;
		}

		return tab;
	}

	void Dockspace::dock(cstring name, const vec2& pos)
	{
		Dockable* target = pinpoint_dock(pos);
		if(target)
			this->dock(name, *target->m_dock, target->m_frame, pos);
		else if(m_docks.empty())
		{
			// an empty dockspace receives the item in a root dock
			Dock& dock = this->add_dock({ 0U });
			this->dock_stack(dock, name);
		}
	}

	void Dockspace::dock(cstring name, Dock& target, Frame& frame, const vec2& pos)
	{
		vec2 local = frame.local_position(pos);

		// the target and its siblings are laid out along dim: dropping on the edges along dim inserts beside the target, on the other edges splits it
		Axis dim = Axis(target.m_dockid.size() % 2);
		Axis ortho = flip(dim);

		const bool before = local[dim] < frame.m_size[dim] * 0.25f;
		const bool after = local[dim] > frame.m_size[dim] * 0.75f;
		const bool first = local[ortho] < frame.m_size[ortho] * 0.25f;
		const bool second = local[ortho] > frame.m_size[ortho] * 0.75f;

		// docking on the target stacks the item to it, otherwise a new dock is split off
		if(first || second)
			this->dock_stack(this->dock_split(target, second), name); // dock split first / second
		else if(before || after)
			this->dock_stack(this->dock_insert(target, after), name); // dock before / after
		else
			this->dock_stack(target, name); // dock on
	}

	Dockbar::Dockbar(Widget* parent, Docksystem& docksystem)
		: Docker(parent, docksystem)
	{}

	Widget* Dockbar::docksection(Dock& dock, cstring name, NodeKey id)
	{
		string icon = "(" + to_lower(replace(name, " ", "")) + ")";
		Widget& toggle = ui::button(id, *m_togglebar, ui::dock_styles().docktoggle, icon.c_str());
		if(toggle.mouse_event(DeviceType::MouseLeft, EventType::DragStarted))
		{
			if(m_current_tab == dock.m_dockid.back())
				m_current_tab = SIZE_MAX;

			this->undock(dock, name);
			return nullptr;
		}

		if(toggle.activated())
			m_current_tab = m_current_tab == dock.m_dockid.back() ? SIZE_MAX : dock.m_dockid.back();
		toggle.set_state(ACTIVE, m_current_tab == dock.m_dockid.back());

		if(m_current_tab == dock.m_dockid.back())
			return ui::window(id, *m_dockzone, name, WindowState::Dockable, &dock).m_body; // dock_styles().dockbox
		else
			return nullptr;
	}

	void Dockbar::dock(cstring name, const vec2& pos)
	{
		UNUSED(pos);
		// the dockbar is a single row of tabs: a docked item is stacked after the last one, and opened
		uint16_t index = m_docks.empty() ? 0 : m_docks.back()->m_dockid.back() + 1;

		Dock& dock = this->add_dock({ index });
		this->dock_stack(dock, name);
		m_current_tab = index;
	}

	void Dockbar::apply_pending()
	{
		// the open tab moves back if the dock of a tab before it is removed
		for(PendingUndock& undock : m_pending_undocks)
			if(m_current_tab != SIZE_MAX && m_current_tab > undock.dock->m_dockid.back() && undock.dock->m_items.size() == 1)
				m_current_tab--;

		Docker::apply_pending();
	}
}
