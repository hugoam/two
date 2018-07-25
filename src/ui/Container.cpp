//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <infra/Vector.h>
#include <ui/Container.h>
#include <ui/Structs/Container.h>
#include <ui/Structs/Widget.h>
#include <ui/Sheet.h>
#include <ui/ScrollSheet.h>
#include <ui/Frame/Solver.h>
#endif

namespace mud
{
	Table::Table(Widget* parent, void* identity, array<float> weights)
		: Widget(parent, identity)
		, m_weights(to_vector(weights))
	{}

	Table::Table(Widget* parent, void* identity, size_t columns)
		: Widget(parent, identity)
		, m_weights(columns, 1.f)
	{}

namespace ui
{
	ScrollSheet& select_list(Widget& parent)
	{
		return scroll_sheet(parent, styles().list);
	}

	Table& columns(Widget& parent, array<float> weights)
	{
		Table& self = parent.suba<Table, array<float>>(weights);
		self.init(styles().table);

		as<TableSolver>(*self.m_frame.m_solver).update(self.m_weights);

		return self;
	}
	
	Table& table(Widget& parent, size_t columns, array<float> weights)
	{
		if(weights.size() > 0)
			return parent.suba<Table, array<float>>(weights);
		else
			return parent.suba<Table, size_t>(columns);
	}

	Table& table(Widget& parent, array<cstring> columns, array<float> weights)
	{
		Table& self = table(parent, columns.size(), weights);
		self.init(styles().table);

		Widget& header = grid_sheet(self, styles().table_head, DIM_X, self.m_weights); // [this](Frame& first, Frame& second) { this->resize(first, second); }

		as<TableSolver>(*self.m_frame.m_solver).update(self.m_weights);

		for(size_t i = 0; i < columns.size(); ++i)
		{
			Widget& column = spanner(header, styles().column_header, DIM_X, self.m_weights[i]);
			label(column, columns[i]);
		}

		return self;
	}

	Widget& table_row(Widget& parent)
	{
		bool odd = parent.m_next % 2 == 1;
		return button(parent, odd ? table_styles().row_odd : table_styles().row_even);
	}

	Widget& table_separator(Widget& parent)
	{
		return widget(parent, table_styles().separator);
	}

	Widget& toggle_header(Widget& parent, Style& header_style, Style& toggle_style, array<cstring> elements, bool& open)
	{
		Widget& self = button(parent, header_style);
		Widget& button = toggle(self, toggle_style, open);
		multi_item(self, styles().row, elements);
		self.set_state(HOVERED, self.hovered() || button.hovered());
		return self;
	}

	Expandbox& expandbox(Widget& parent, array<cstring> elements, bool open)
	{
		Expandbox& self = twidget<Expandbox>(parent, expandbox_styles().expandbox, open);
		self.m_header = &toggle_header(self, expandbox_styles().header, expandbox_styles().toggle, elements, self.m_open);
		self.m_body = nullptr;
		if(self.m_open)
			self.m_body = &widget(self, expandbox_styles().body);
		return self;
	}

	Expandbox& expandbox(Widget& parent, cstring name, bool open)
	{
		return expandbox(parent, { &name, 1 }, open);
	}

	TreeNode& tree_node(Widget& parent, array<cstring> elements, bool leaf, bool open)
	{
		TreeNode& self = twidget<TreeNode>(parent, treenode_styles().treenode, open);
		self.m_header = &toggle_header(self, treenode_styles().header, leaf ? treenode_styles().no_toggle : treenode_styles().toggle, elements, self.m_open);
		self.m_body = nullptr;
		if(!leaf && self.m_open)
			self.m_body = &widget(self, treenode_styles().body);
		return self;
	}

	TreeNode& tree_node(Widget& parent, cstring element, bool leaf, bool open)
	{
		return tree_node(parent, { &element, 1 }, leaf, open);
	}

	Widget& tree(Widget& parent)
	{
		return sheet(parent);// , styles().tree);
	}

	Widget& tab_header(Widget& parent, cstring name)
	{
		return button(parent, tabber_styles().tab_button, name);
	}

	Widget& tab_body(Widget& parent, size_t index)
	{
		return widget(parent, tabber_styles().tab, (void*) index);
	}

	Widget* tab(Tabber& tabber, cstring name)
	{
		size_t index = tabber.m_index++;
		Widget& header = tab_header(*tabber.m_head, name);
		if(header.activated())
			tabber.m_active = index;
		header.set_state(ACTIVE, tabber.m_active == index);
		if(index == tabber.m_active)
			return &tab_body(*tabber.m_body, index);
		return nullptr;
	}

	Tabber& tabber(Widget& parent)
	{
		Tabber& self = twidget<Tabber>(parent, tabber_styles().tabber);
		self.m_head = &widget(self, tabber_styles().head);
		self.m_body = &widget(self, tabber_styles().body);
		self.m_index = 0;
		return self;
	}
}
}
