//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	Table::Table(Widget* parent, span<float> weights)
		: Widget(parent)
		, m_weights(to_vector(weights))
	{
		m_frame.d_columns = m_weights;
	}

	Table::Table(Widget* parent, size_t columns)
		: Widget(parent)
		, m_weights(columns, 1.f)
	{
		m_frame.d_columns = m_weights;
	}

namespace ui
{
	ScrollSheet& select_list(NodeKey id, Widget& parent)
	{
		return scroll_sheet(id, parent, styles().list);
	}

	Table& columns(NodeKey id, Widget& parent, span<float> weights)
	{
		Table& self = parent.sub<Table, span<float>>(id, weights);
		self.init(styles().table);
		return self;
	}
	
	Table& table(NodeKey id, Widget& parent, size_t columns, span<float> weights)
	{
		if(weights.size() > 0)
			return parent.sub<Table, span<float>>(id, weights);
		else
			return parent.sub<Table, size_t>(id, columns);
	}

	Table& table(NodeKey id, Widget& parent, span<cstring> columns, span<float> weights)
	{
		Table& self = table(id, parent, columns.size(), weights);
		self.init(styles().table);

		Widget& header = grid_sheet(key(), self, styles().table_head, Axis::X, self.m_weights); // [this](Frame& first, Frame& second) { this->resize(first, second); }

		for(size_t i = 0; i < columns.size(); ++i)
		{
			Widget& column = spanner(key(), header, styles().column_header, Axis::X, self.m_weights[i]);
			label(key(), column, columns[i]);
		}

		return self;
	}

	Widget& table_row(NodeKey id, Widget& parent)
	{
		bool odd = parent.m_next % 2 == 1;
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

	Expandbox& expandbox(NodeKey id, Widget& parent, span<cstring> elements, bool open)
	{
		Expandbox& self = twidget<Expandbox>(id, parent, expandbox_styles().expandbox, open);
		self.m_header = &toggle_header(key(), self, expandbox_styles().header, expandbox_styles().toggle, elements, self.m_open);
		self.m_body = nullptr;
		if(self.m_open)
			self.m_body = &widget(key(), self, expandbox_styles().body);
		return self;
	}

	Expandbox& expandbox(NodeKey id, Widget& parent, cstring name, bool open)
	{
		return expandbox(id, parent, { &name, 1 }, open);
	}

	TreeNode& tree_node(NodeKey id, Widget& parent, span<cstring> elements, bool leaf, bool open)
	{
		TreeNode& self = twidget<TreeNode>(id, parent, treenode_styles().treenode, open);
		self.m_header = &toggle_header(key(), self, treenode_styles().header, leaf ? treenode_styles().no_toggle : treenode_styles().toggle, elements, self.m_open);
		self.m_body = nullptr;
		if(!leaf && self.m_open)
			self.m_body = &widget(key(), self, treenode_styles().body);
		return self;
	}

	TreeNode& tree_node(NodeKey id, Widget& parent, cstring element, bool leaf, bool open)
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
		size_t index = tabber.m_index++;
		Widget& header = tab_header(id, *tabber.m_head, name);
		if(header.activated())
			tabber.m_active = index;
		header.set_state(ACTIVE, tabber.m_active == index);
		if(index == tabber.m_active)
			return &tab_body(id, *tabber.m_body);
		return nullptr;
	}

	Tabber& tabber(NodeKey id, Widget& parent)
	{
		Tabber& self = twidget<Tabber>(id, parent, tabber_styles().tabber);
		self.m_head = &widget(key(), self, tabber_styles().head);
		widget(key(), self, tabber_styles().edge);
		//separator(key(), self);
		self.m_body = &widget(key(), self, tabber_styles().body);
		self.m_index = 0;
		return self;
	}
}
}
