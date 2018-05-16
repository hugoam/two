//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <ui/Generated/Forward.h>
#include <ui/Style/Style.h>

namespace mud
{
namespace ui
{
	struct TableStyles
	{
		TableStyles();
		Style row; Style row_odd; Style row_even;
	};

	MUD_UI_EXPORT TableStyles& table_styles();

	struct ExpandboxStyles
	{
		ExpandboxStyles();
		Style expandbox; Style header; Style toggle; Style body;
	};

	MUD_UI_EXPORT ExpandboxStyles& expandbox_styles();

	struct TreeNodeStyles
	{
		TreeNodeStyles();
		Style treenode; Style header; Style toggle; Style no_toggle; Style body;
	};

	MUD_UI_EXPORT TreeNodeStyles& treenode_styles();

	struct TabberStyles
	{
		TabberStyles();
		Style tab; Style tab_button; Style tabber; Style head; Style body;
	};

	MUD_UI_EXPORT TabberStyles& tabber_styles();

	MUD_UI_EXPORT _func_ ScrollSheet& select_list(Widget& parent);

	// @todo reflection for array<T>
	MUD_UI_EXPORT _func_ Table& columns(Widget& parent, array<float> weights);
	MUD_UI_EXPORT _func_ Table& table(Widget& parent, array<cstring> columns, array<float> weights);
	MUD_UI_EXPORT _func_ Widget& table_row(Widget& parent);

	MUD_UI_EXPORT _func_ Expandbox& expandbox(Widget& parent, array<cstring> elements, bool open = true);
	MUD_UI_EXPORT _func_ Expandbox& expandbox(Widget& parent, cstring name, bool open = true);

	MUD_UI_EXPORT _func_ TreeNode& tree_node(Widget& parent, array<cstring> elements, bool leaf = false, bool open = true);
	MUD_UI_EXPORT _func_ TreeNode& tree_node(Widget& parent, cstring name, bool leaf = false, bool open = true);
	MUD_UI_EXPORT _func_ Widget& tree(Widget& parent);

	MUD_UI_EXPORT _func_ Widget* tab(Tabber& tabber, cstring name);
	MUD_UI_EXPORT _func_ Tabber& tabber(Widget& parent);
}
}
