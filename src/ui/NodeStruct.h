//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <math/Colour.h>
#endif
#include <ui/Forward.h>
#include <ui/WidgetStruct.h>

namespace two
{
	export_ struct NodeKnob
	{
		vec2 m_end;
		Colour m_colour;
	};

	export_ class refl_ TWO_UI_EXPORT NodePlug : public Widget, public NodeKnob
	{
	public:
		NodePlug(Widget* parent, void* identity) : Widget(parent, identity) {}
		Node* m_node;
		Widget* m_knob;
	};

	export_ class refl_ TWO_UI_EXPORT Node : public Widget
	{
	public:
		Node(Widget* parent, void* identity) : Widget(parent, identity) {}
		Canvas* m_canvas;
		Widget* m_header;
		Widget* m_inputs;
		Widget* m_outputs;
		int m_order = 0;
	};

	export_ struct refl_ TWO_UI_EXPORT CanvasConnect
	{
		NodePlug* m_origin = nullptr;
		NodePlug* m_in = nullptr;
		NodePlug* m_out = nullptr;
		NodeKnob m_end;
		vec2 m_position;
		bool m_done = false;
	};

	export_ class refl_ TWO_UI_EXPORT Canvas : public Widget
	{
	public:
		Canvas(Widget* parent, void* identity) : Widget(parent, identity) {}

		ScrollSheet* m_scroll_plan;
		Widget* m_plan;
		bool m_rounded_links = true;

		CanvasConnect m_connect;

		vector<Node*> m_nodes;
		vector<Node*> m_selection;
	};
}
