//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
namespace ui
{
	ScrollSheet select_list(NodeKey id, Widget& parent)
	{
		return scroll_sheet(id, parent, styles().list);
	}

	// a table takes its weights, or its number of columns, when it's created
	Widget& table(NodeKey id, Widget& parent, size_t columns, span<float> weights)
	{
		Widget& self = widget(id, parent, styles().table);
		TableState& state = weights.size() > 0 ? self.state<TableState>(weights) : self.state<TableState>(columns);
		self.m_frame.d_columns = state.m_weights;
		return self;
	}

	Widget& columns(NodeKey id, Widget& parent, span<float> weights)
	{
		return table(id, parent, weights.size(), weights);
	}

	Widget& table(NodeKey id, Widget& parent, span<cstring> columns, span<float> weights)
	{
		Widget& self = table(id, parent, columns.size(), weights);
		TableState& state = self.state<TableState>(columns.size());

		Widget& header = grid_sheet(key(), self, styles().table_head, Axis::X, state.m_weights); // [this](Frame& first, Frame& second) { this->resize(first, second); }

		for(size_t i = 0; i < columns.size(); ++i)
		{
			Widget& column = spanner(key(), header, styles().column_header, Axis::X, state.m_weights[i]);
			label(key(), column, columns[i]);
		}

		return self;
	}

	Widget& table_row(NodeKey id, Widget& parent)
	{
		bool odd = parent.next() % 2 == 1;
		return button(id, parent, odd ? table_styles().row_odd : table_styles().row_even);
	}

	Widget& table_separator(NodeKey id, Widget& parent)
	{
		return widget(id, parent, table_styles().separator);
	}

	Widget& toggle_header(NodeKey id, Widget& parent, Style& header_style, Style& toggle_style, span<cstring> elements, bool& open)
	{
		Widget& self = button(id, parent, header_style);
		Widget& button = toggle(key(), self, toggle_style, open);
		multi_item(key(), self, styles().row, elements);
		self.set_state(HOVERED, self.hovered() || button.hovered());
		return self;
	}

	Expandbox expandbox(NodeKey id, Widget& parent, span<cstring> elements, bool open)
	{
		Widget& self = widget(id, parent, expandbox_styles().expandbox, open);
		bool is_open = self.open();
		Widget& header = toggle_header(key(), self, expandbox_styles().header, expandbox_styles().toggle, elements, is_open);
		self.set_open(is_open);
		Widget* body = is_open ? &widget(key(), self, expandbox_styles().body) : nullptr;
		return { self, header, body };
	}

	Expandbox expandbox(NodeKey id, Widget& parent, cstring name, bool open)
	{
		return expandbox(id, parent, { &name, 1 }, open);
	}

	TreeNode tree_node(NodeKey id, Widget& parent, span<cstring> elements, bool leaf, bool open)
	{
		Widget& self = widget(id, parent, treenode_styles().treenode, open);
		bool is_open = self.open();
		Widget& header = toggle_header(key(), self, treenode_styles().header, leaf ? treenode_styles().no_toggle : treenode_styles().toggle, elements, is_open);
		self.set_open(is_open);
		Widget* body = !leaf && is_open ? &widget(key(), self, treenode_styles().body) : nullptr;
		return { self, header, body };
	}

	TreeNode tree_node(NodeKey id, Widget& parent, cstring element, bool leaf, bool open)
	{
		return tree_node(id, parent, { &element, 1 }, leaf, open);
	}

	Widget& tree(NodeKey id, Widget& parent)
	{
		return sheet(id, parent);// , styles().tree);
	}

	Widget& tab_header(NodeKey id, Widget& parent, cstring name)
	{
		return button(id, parent, tabber_styles().tab_button, name);
	}

	Widget& tab_body(NodeKey id, Widget& parent)
	{
		return widget(id, parent, tabber_styles().tab);
	}

	Widget* tab(NodeKey id, Tabber& tabber, cstring name)
	{
		size_t index = tabber.state.m_index++;
		Widget& header = tab_header(id, tabber.head, name);
		if(header.activated())
			tabber.state.m_active = index;
		header.set_state(ACTIVE, tabber.state.m_active == index);
		if(index == tabber.state.m_active)
			return &tab_body(id, tabber.body);
		return nullptr;
	}

	Tabber tabber(NodeKey id, Widget& parent)
	{
		Widget& self = widget(id, parent, tabber_styles().tabber);
		Widget& head = widget(key(), self, tabber_styles().head);
		widget(key(), self, tabber_styles().edge);
		//separator(key(), self);
		Widget& body = widget(key(), self, tabber_styles().body);
		TabberState& state = self.state<TabberState>();
		state.m_index = 0;
		return { self, head, body, state };
	}
}
}
