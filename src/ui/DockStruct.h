//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
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
		Dock(Docker& docker, cstring name, vector<uint16_t> dockid, float span = 0.f);
		Docker* m_docker = nullptr;
		cstring m_name;
		vector<uint16_t> m_dockid;
		float m_span = 0.f;
	};

	export_ class refl_ TWO_UI_EXPORT Docksystem
	{
	public:
		Docksystem();

		void dock(Dockable& widget, const vec2& pos);

		map<string, Dock> m_docks;
		vector<Docker*> m_dockers;
	};

	export_ class refl_ TWO_UI_EXPORT Dockable : public Widget
	{
	public:
		Dockable(Widget* parent, void* identity);
		Dock* m_dock = nullptr;
	};

	export_ class refl_ TWO_UI_EXPORT Docker : public Widget
	{
	public:
		Docker(Widget* parent, void* identity, Docksystem& docksystem);

		virtual Widget* docksection(Dock& dock) = 0;

		virtual void dock(Dockable& widget, const vec2& pos) = 0;

		void dock_split(Dock& dock, Dock& target, bool after);
		void dock_insert(Dock& dock, Dock& target, bool after);

		void undock(Dockable& dockable);

		void shift(Dock& start, bool add);

		Docksystem* m_docksystem;
		vector<Dock*> m_docks;
	};

	export_ class refl_ TWO_UI_EXPORT Dockspace : public Docker
	{
	public:
		Dockspace(Widget* parent, void* identity, Docksystem& docksystem);
		~Dockspace();

		Dockable& pinpoint_dock(const vec2& pos);

		virtual Widget* docksection(Dock& dock) final;

		virtual void dock(Dockable& widget, const vec2& pos) final;

		void dock(Dock& dock, Dock& target, Frame& frame, const vec2& pos);

		Widget* m_mainline;
	};

	export_ class refl_ TWO_UI_EXPORT Dockbar : public Docker
	{
	public:
		Dockbar(Widget* parent, void* identity, Docksystem& docksystem);

		Widget* m_togglebar = nullptr;
		Widget* m_dockzone = nullptr;

		virtual Widget* docksection(Dock& dock) final;

		virtual void dock(Dockable& widget, const vec2& pos) final;

		float width = 300.f;
		size_t m_current_tab = SIZE_MAX;
	};
}
