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
		Node* m_node = nullptr;
		WidgetHandle m_knob;
	};

	// a handle to the widget of a plug, the plug in its state reached through ->
	export_ struct refl_ struct_ NodePlugHandle : public WidgetHandle
	{
		NodePlugHandle() {}
		explicit NodePlugHandle(Widget self) : WidgetHandle(self) {}

		attr_ inline Widget self() const { return this->widget(); }
		attr_ inline NodePlug& plug() const { return *this->get()->find_state<NodePlug>(); }

		NodePlug* operator->() const { return &this->plug(); }
		NodePlug& operator*() const { return this->plug(); }
	};

	// a node of a canvas, kept in the state of its widget, with its parts in the frame: the content goes in the body
	export_ class refl_ TWO_UI_EXPORT Node : public NodeState
	{
	public:
		Canvas* m_canvas = nullptr;
		WidgetHandle m_header;
		WidgetHandle m_inputs;
		WidgetHandle m_outputs;
		WidgetHandle m_body;
		attr_ int m_order = 0;
		uint32_t m_index = 0;

		attr_ inline Widget header() const { return m_header.widget(); }
		attr_ inline Widget inputs() const { return m_inputs.widget(); }
		attr_ inline Widget outputs() const { return m_outputs.widget(); }
		attr_ inline Widget body() const { return m_body.widget(); }
	};

	// a handle to the widget of a node, the node in its state reached through ->
	export_ struct NodeHandle : public WidgetHandle
	{
		NodeHandle() {}
		explicit NodeHandle(Widget self) : WidgetHandle(self) {}

		inline Widget self() const { return this->widget(); }
		inline Node& node() const { return *this->get()->find_state<Node>(); }

		Node* operator->() const { return &this->node(); }
		Node& operator*() const { return this->node(); }
	};

	export_ struct refl_ TWO_UI_EXPORT CanvasConnect
	{
		NodePlugHandle m_origin;
		NodePlugHandle m_in;
		NodePlugHandle m_out;
		NodeKnob m_end;
		vec2 m_position;
		bool m_done = false;
	};

	// a canvas of nodes, kept in the state of its widget, with the nodes declared in the frame
	export_ class refl_ TWO_UI_EXPORT Canvas : public NodeState
	{
	public:
		WidgetHandle m_scroll_plan;
		WidgetHandle m_plan;
		bool m_rounded_links = true;

		CanvasConnect m_connect;

		vector<NodeHandle> m_nodes;
		vector<NodeHandle> m_selection;
	};

	// a handle to the widget of a canvas, the canvas in its state reached through ->
	export_ struct refl_ struct_ CanvasHandle : public WidgetHandle
	{
		CanvasHandle() {}
		explicit CanvasHandle(Widget self) : WidgetHandle(self) {}

		attr_ inline Widget self() const { return this->widget(); }
		attr_ inline Canvas& canvas() const { return *this->get()->find_state<Canvas>(); }

		Canvas* operator->() const { return &this->canvas(); }
		Canvas& operator*() const { return this->canvas(); }
	};
}
