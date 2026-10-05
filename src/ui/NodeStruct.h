//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/WidgetStruct.h>

namespace two
{
	export_ struct NodeKnob
	{
		vec2 m_end;
		Colour m_colour;
	};

	// a plug of a node, kept in the state of its widget
	export_ class refl_ TWO_UI_EXPORT NodePlug : public NodeState, public NodeKnob
	{
	public:
		Widget* m_self = nullptr;
		Node* m_node = nullptr;
		Widget* m_knob = nullptr;
	};

	// a node of a canvas, kept in the state of its widget, with its parts in the frame: the content goes in the body
	export_ class refl_ TWO_UI_EXPORT Node : public NodeState
	{
	public:
		Widget* m_self = nullptr;
		Canvas* m_canvas = nullptr;
		attr_ Widget* m_header = nullptr;
		attr_ Widget* m_inputs = nullptr;
		attr_ Widget* m_outputs = nullptr;
		attr_ Widget* m_body = nullptr;
		attr_ int m_order = 0;
		uint32_t m_index = 0;
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

	// a canvas of nodes, kept in the state of its widget, with the nodes declared in the frame
	export_ class refl_ TWO_UI_EXPORT Canvas : public NodeState
	{
	public:
		Widget* m_self = nullptr;

		Widget* m_scroll_plan = nullptr;
		Widget* m_plan = nullptr;
		bool m_rounded_links = true;

		CanvasConnect m_connect;

		vector<Node*> m_nodes;
		vector<Node*> m_selection;
	};
}
