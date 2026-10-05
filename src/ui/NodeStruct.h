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
		WidgetHandle m_knob = nullptr;
	};

	// a handle to a plug: for now the widget of the plug and the plug in its state, the plug's members reached through ->
	export_ struct refl_ struct_ NodePlugHandle
	{
		attr_ Widget* self = nullptr;	// a WidgetHandle
		attr_ NodePlug* plug = nullptr;

		NodePlug* operator->() const { return plug; }
		NodePlug& operator*() const { return *plug; }
		explicit operator bool() const { return plug != nullptr; }
		bool operator==(const NodePlugHandle& other) const { return plug == other.plug; }
	};

	// a node of a canvas, kept in the state of its widget, with its parts in the frame: the content goes in the body
	export_ class refl_ TWO_UI_EXPORT Node : public NodeState
	{
	public:
		Canvas* m_canvas = nullptr;
		attr_ Widget* m_header = nullptr;	// a WidgetHandle
		attr_ Widget* m_inputs = nullptr;	// a WidgetHandle
		attr_ Widget* m_outputs = nullptr;	// a WidgetHandle
		attr_ Widget* m_body = nullptr;	// a WidgetHandle
		attr_ int m_order = 0;
		uint32_t m_index = 0;
	};

	// a handle to a node: for now the widget of the node and the node in its state, the node's members reached through ->
	export_ struct NodeHandle
	{
		WidgetHandle self = nullptr;
		Node* node = nullptr;

		Node* operator->() const { return node; }
		Node& operator*() const { return *node; }
		bool operator==(const NodeHandle& other) const { return node == other.node; }
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
		WidgetHandle m_scroll_plan = nullptr;
		WidgetHandle m_plan = nullptr;
		bool m_rounded_links = true;

		CanvasConnect m_connect;

		vector<NodeHandle> m_nodes;
		vector<NodeHandle> m_selection;
	};

	// a handle to a canvas: for now the widget of the canvas and the canvas in its state, the canvas' members reached through ->
	export_ struct refl_ struct_ CanvasHandle
	{
		attr_ Widget* self = nullptr;	// a WidgetHandle
		attr_ Canvas* canvas = nullptr;

		Canvas* operator->() const { return canvas; }
		Canvas& operator*() const { return *canvas; }
	};
}
