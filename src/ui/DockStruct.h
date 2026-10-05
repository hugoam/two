//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/WidgetStruct.h>
#include <ui/Container.h>

namespace two
{
	export_ struct refl_ TWO_UI_EXPORT Dock
	{
		Dock();
		Dock(Docker& docker, vector<uint16_t> dockid, float span = 0.f);
		Docker* m_docker = nullptr;
		vector<uint16_t> m_dockid;
		float m_span = 0.f;
		vector<string> m_items;
	};

	export_ class refl_ TWO_UI_EXPORT Docksystem
	{
	public:
		Docksystem();

		void dock(cstring name, const vec2& pos);

		map<string, Dock*> m_item_docks;
		vector<Docker*> m_dockers;
		string m_dragged;
	};

	export_ class refl_ TWO_UI_EXPORT Docker : public Widget
	{
	public:
		Docker(Widget* parent, Docksystem& docksystem);
		~Docker();

		virtual Widget* docksection(Dock& dock, cstring name, NodeKey id) = 0;

		virtual void dock(cstring name, const vec2& pos) = 0;

		Dock& dock_split(Dock& target, bool after);
		Dock& dock_insert(Dock& target, bool after);
		void dock_stack(Dock& dock, cstring name);
		void dock_remove(Dock& dock, cstring name);

		void dock_create(cstring name, span<uint16_t> dockid, float span);
		void undock(Dock& dock, cstring name);
		virtual void apply_pending();

		Dock& add_dock(vector<uint16_t> dockid, float span = 0.f);

		span<unique<Dock>> sub_docks(span<uint16_t> dockid);

		void shift_add(const vector<uint16_t>& dockid);
		void shift_remove(const vector<uint16_t>& dockid);
		void collapse(const vector<uint16_t>& line);

		Docksystem* m_docksystem;
		vector<unique<Dock>> m_docks;

		// the dock ids only change between frames, so that no index in the widget tree shifts during a frame
		struct PendingUndock { Dock* dock; string name; };
		struct PendingDock { string name; vec2 pos; };
		vector<PendingUndock> m_pending_undocks;
		vector<PendingDock> m_pending_docks;
	};

	export_ class refl_ TWO_UI_EXPORT Dockspace : public Docker
	{
	public:
		Dockspace(Widget* parent, Docksystem& docksystem);

		// the windows of the docks shown in this frame
		struct DockedWindow { Widget* window; Dock* dock; };
		vector<DockedWindow> m_docked;

		DockedWindow* pinpoint_dock(const vec2& pos);

		virtual Widget* docksection(Dock& dock, cstring name, NodeKey id) final;

		virtual void dock(cstring name, const vec2& pos) final;

		void dock(cstring name, Dock& target, Frame& frame, const vec2& pos);

		Widget* m_mainline;
	};

	export_ class refl_ TWO_UI_EXPORT Dockbar : public Docker
	{
	public:
		Dockbar(Widget* parent, Docksystem& docksystem);

		Widget* m_togglebar = nullptr;
		Widget* m_dockzone = nullptr;

		virtual Widget* docksection(Dock& dock, cstring name, NodeKey id) final;

		virtual void dock(cstring name, const vec2& pos) final;
		virtual void apply_pending() final;

		float width = 300.f;
		size_t m_current_tab = SIZE_MAX;
	};
}
