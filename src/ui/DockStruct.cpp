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

	Dockable::Dockable(Widget* parent, void* identity)
		: Widget(parent, identity)
	{}

	Docker::Docker(Widget* parent, void* identity, Docksystem& docksystem)
		: Widget(parent, identity)
		, m_docksystem(&docksystem)
	{}

	Docker::~Docker()
	{
		for(auto& dock : m_docks)
			for(const string& item : dock->m_items)
				m_docksystem->m_item_docks.erase(item);
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
			this->shift_remove(dock.m_dockid);
			remove_pt(m_docks, dock);
		}
	}

	void Docker::dock_create(cstring name, span<uint16_t> dockid, float span)
	{
		auto target = find(m_docks, [&](auto& look) { return equals(look->m_dockid, dockid); });
		Dock& dock = target ? **target : add_dock(to_vector(dockid), span);
		dock_stack(dock, name);
	}

	void Docker::undock(Dockable& dockable)
	{
		vec2 absolute = dockable.m_frame.absolute_position();
		dockable.m_frame.set_position(absolute);
		dockable.m_frame.m_layer->moveToTop();

		this->dock_remove(*dockable.m_dock, dockable.m_name);
		dockable.m_dock = nullptr;
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
				docker->dock(item, pos);
				return;
			}
	}

	Dockspace::Dockspace(Widget* parent, void* identity, Docksystem& docksystem)
		: Docker(parent, identity, docksystem)
	{}

	Dockable& Dockspace::pinpoint_dock(const vec2& pos)
	{
		Widget* widget = this->pinpoint(pos, [](Frame& frame) { return frame.d_style == &ui::window_styles().dock_window; });
		return static_cast<Dockable&>(*widget);
	}

	Widget* Dockspace::docksection(Dock& dock, cstring name)
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
		Widget* tab = ui::tab(section, name); // dock_styles().docktab, 

		if(tab)
		{
			Window& container = ui::window(*tab, name, WindowState::Dockable, nullptr, &dock);
			return container.m_body;
		}

		return tab;
	}

	void Dockspace::dock(Dockable& widget, const vec2& pos)
	{
		Dockable& target = pinpoint_dock(pos);
		this->dock(widget.m_name, *target.m_dock, target.m_frame, pos);
	}

	void Dockspace::dock(cstring name, Dock& target, Frame& frame, const vec2& pos)
	{
		vec2 local = frame.local_position(pos);

		Axis dim = Axis(target.m_dockid.size() % 2);
		Axis ortho = flip(dim);

		const bool first = local[dim] < frame.m_size[dim] * 0.25f;
		const bool second = local[dim] > frame.m_size[dim] * 0.75f;
		const bool before = local[ortho] < frame.m_size[ortho] * 0.25f;
		const bool after = local[ortho] > frame.m_size[ortho] * 0.75f;

		// docking on the target stacks the item to it, otherwise a new dock is split off
		if(first || second)
			this->dock_stack(this->dock_split(target, second), name); // dock split first / second
		else if(before || after)
			this->dock_stack(this->dock_insert(target, after), name); // dock before / after
		else
			this->dock_stack(target, name); // dock on
	}

	Dockbar::Dockbar(Widget* parent, void* identity, Docksystem& docksystem)
		: Docker(parent, identity, docksystem)
	{}

	Widget* Dockbar::docksection(Dock& dock, cstring name)
	{
		string icon = "(" + to_lower(replace(name, " ", "")) + ")";
		Widget& toggle = ui::button(*m_togglebar, ui::dock_styles().docktoggle, icon.c_str());
		if(toggle.activated())
			m_current_tab = m_current_tab == dock.m_dockid.back() ? SIZE_MAX : dock.m_dockid.back();
		toggle.set_state(ACTIVE, m_current_tab == dock.m_dockid.back());

		if(m_current_tab == dock.m_dockid.back())
			return ui::window(*m_dockzone, name, static_cast<WindowState>(0), &dock, &dock).m_body; // dock_styles().dockbox
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
