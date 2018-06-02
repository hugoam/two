//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Colour.h>
#include <ui/Generated/Forward.h>
#include <ui/Structs/Widget.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ class _refl_ MUD_UI_EXPORT NodePlug : public Widget
	{
	public:
		NodePlug(Widget* parent, void* identity) : Widget(parent, identity) {}
		Node* m_node;
		Widget* m_knob;
		Colour m_colour;
	};

	export_ class _refl_ MUD_UI_EXPORT Node : public Widget
	{
	public:
		Node(Widget* parent, void* identity) : Widget(parent, identity) {}
		Canvas* m_canvas;
		Widget* m_header;
		Widget* m_inputs;
		Widget* m_outputs;
		int m_order = 0;
	};

	export_ struct _refl_ MUD_UI_EXPORT CanvasConnect
	{
		NodePlug* m_origin = nullptr;
		NodePlug* m_in = nullptr;
		NodePlug* m_out = nullptr;
		vec2 m_position;
		bool m_done = false;
	};

	export_ class _refl_ MUD_UI_EXPORT Canvas : public Widget
	{
	public:
		Canvas(Widget* parent, void* identity) : Widget(parent, identity) {}

		ScrollSheet* m_scroll_plan;
		Widget* m_plan;
		bool m_rounded_links = true;

		CanvasConnect m_connect;

		std::vector<Node*> m_nodes;
		std::vector<Node*> m_selection;
	};
}
