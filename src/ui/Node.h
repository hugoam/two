//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Style/Style.h>
#include <ui/Widget.h>

namespace two
{
	export_ struct refl_ TWO_UI_EXPORT NodeConnection
	{
		uint32_t m_out_node = UINT32_MAX;
		uint32_t m_out_plug;

		uint32_t m_in_node;
		uint32_t m_in_plug;

		bool valid() { return m_out_node != UINT32_MAX; }
	};

namespace ui
{
	export_ struct NodeStyles
	{
		void reset();
		Style node; Style body; Style plugs; Style inputs; Style outputs; Style knob; Style knob_output; Style knob_proxy; Style plug; Style cable; Style header;
	};

	export_ TWO_UI_EXPORT NodeStyles& node_styles();

	export_ struct CanvasStyles
	{
		void reset();
		Style canvas;
	};

	export_ TWO_UI_EXPORT CanvasStyles& canvas_styles();

	export_ TWO_UI_EXPORT NodePlug& node_plug(Node& node, cstring name, cstring icon, const Colour& colour, bool input, bool active, bool connected);
	
	export_ func_ inline NodePlug& node_input(Node& node, cstring name, cstring icon = "", const Colour& colour = Colour::NeonGreen, bool active = true, bool connected = false)
	{
		return node_plug(node, name, icon, colour, true, active, connected);
	}

	export_ func_ inline NodePlug& node_output(Node& node, cstring name, cstring icon = "", const Colour& colour = Colour::NeonGreen, bool active = true, bool connected = false)
	{
		return node_plug(node, name, icon, colour, false, active, connected);
	}

	export_ TWO_UI_EXPORT Node& node(Canvas& parent, span<cstring> title, int order = 0, Ref identity = {});
	export_ TWO_UI_EXPORT Node& node(Canvas& parent, span<cstring> title, float* position, int order = 0, Ref identity = {});
	export_ TWO_UI_EXPORT Node& node(Canvas& parent, span<cstring> title, vec2& position, int order = 0, Ref identity = {});
	export_ TWO_UI_EXPORT func_ Node& node(Canvas& parent, cstring title, vec2& position, int order = 0, Ref identity = {});

	export_ TWO_UI_EXPORT func_ Widget& node_cable(Canvas& canvas, NodePlug& plug_out, NodePlug& plug_in);

	export_ TWO_UI_EXPORT func_ Canvas& canvas(Widget& parent, size_t num_nodes = 0);
	export_ TWO_UI_EXPORT NodeConnection canvas_connect(Canvas& canvas);
	export_ TWO_UI_EXPORT void canvas_autolayout(Canvas& canvas);
}
}
