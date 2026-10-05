//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/WidgetStruct.h>
#include <ui/Container.h>

namespace two
{
	// a sheet scrolled in its scroll zone, by its scrollbars: the content goes in the body
	export_ struct ScrollSheet
	{
		Widget& self;
		Widget& scroll_zone;
		Widget& body;
		operator Widget&() const { return self; }
	};

namespace ui
{
	// a sequence of elements selected in the selection: the elements go in the body
	export_ struct Sequence
	{
		Widget& self;
		Widget& body;
		vector<Ref>* selection = nullptr;
		operator Widget&() const { return self; }
	};
}

	export_ class refl_ TWO_UI_EXPORT Tabber : public Widget
	{
	public:
		Tabber(Widget* parent) : Widget(parent) {}
		Widget* m_head = nullptr;
		Widget* m_body = nullptr;
		size_t m_index = 0;
		size_t m_active = 0;
	};

	// a box opened and closed by its header: the body is there when it's open
	export_ struct Expandbox
	{
		Widget& self;
		Widget& header;
		Widget* body;
		operator Widget&() const { return self; }
	};

	// a node of a tree opened and closed by its header: the body is there when it's open, the node has children
	export_ struct TreeNode
	{
		Widget& self;
		Widget& header;
		Widget* body;
		operator Widget&() const { return self; }
	};

	export_ class refl_ TWO_UI_EXPORT Table : public Widget
	{
	public:
		Table(Widget* parent, span<float> weights);
		Table(Widget* parent, size_t columns);
		vector<float> m_weights;
	};
}
