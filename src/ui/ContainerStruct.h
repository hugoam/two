//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <type/Ref.h>
#endif
#include <ui/Forward.h>
#include <ui/WidgetStruct.h>
#include <ui/Container.h>

#define MUD_UI_SEQUENCE_REFS

namespace mud
{
	export_ class refl_ MUD_UI_EXPORT ScrollSheet : public Widget
	{
	public:
		ScrollSheet(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_scroll_zone;
	};

namespace ui
{
	export_ class refl_ MUD_UI_EXPORT Sequence : public Widget
	{
	public:
		Sequence(Widget* parent, void* identity) : Widget(parent, identity) {}
#ifdef MUD_UI_SEQUENCE_REFS
		vector<Ref>* m_selection = nullptr;
#else
		vector<Widget*> m_selection;
#endif
	};
}

	export_ class refl_ MUD_UI_EXPORT Tabber : public Widget
	{
	public:
		Tabber(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_head = nullptr;
		size_t m_index = 0;
		size_t m_active = 0;
	};

	export_ class refl_ MUD_UI_EXPORT Expandbox : public Widget
	{
	public:
		Expandbox(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_header = nullptr;
	};

	export_ class refl_ MUD_UI_EXPORT TreeNode : public Widget
	{
	public:
		TreeNode(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_header = nullptr;
	};

	export_ class refl_ MUD_UI_EXPORT Table : public Widget
	{
	public:
		Table(Widget* parent, void* identity, span<float> weights);
		Table(Widget* parent, void* identity, size_t columns);
		vector<float> m_weights;
	};
}
