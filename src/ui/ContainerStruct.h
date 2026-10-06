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
		Widget self;
		Widget scroll_zone;
		Widget body;
		operator Widget() const { return self; }
	};

namespace ui
{
	// a sequence of elements selected in the selection: the elements go in the body
	export_ struct Sequence
	{
		Widget self;
		Widget body;
		vector<Ref>* selection = nullptr;
		operator Widget() const { return self; }
	};
}

	// the active tab of a tabber, and the index of the next tab declared in the frame
	export_ struct TabberState : public NodeState
	{
		size_t m_index = 0;
		size_t m_active = 0;
	};

	// a tabber, with the headers of its tabs in the head: the active tab goes in the body
	export_ struct Tabber
	{
		Widget self;
		Widget head;
		Widget body;
		TabberState& state;
		operator Widget() const { return self; }
	};

	// a box opened and closed by its header: the body is there when it's open
	export_ struct Expandbox
	{
		Widget self;
		Widget header;
		Widget body;
		operator Widget() const { return self; }
	};

	// a node of a tree opened and closed by its header: the body is there when it's open, the node has children
	export_ struct TreeNode
	{
		Widget self;
		Widget header;
		Widget body;
		operator Widget() const { return self; }
	};

	// the weights of the columns of a table
	export_ struct TableState : public NodeState
	{
		TableState(span<float> weights) : m_weights(to_vector(weights)) {}
		TableState(size_t columns) : m_weights(columns, 1.f) {}
		vector<float> m_weights;
	};
}
