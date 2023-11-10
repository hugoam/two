//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/span.h>
#endif
#include <ui/Forward.h>
#include <ui/Style/Style.h>

namespace two
{
namespace ui
{
	export_ struct TableStyles
	{
		void reset();
		Style row; Style row_odd; Style row_even; Style separator;
	};

	export_ TWO_UI_EXPORT TableStyles& table_styles();

	export_ struct ExpandboxStyles
	{
		void reset();
		Style expandbox; Style header; Style toggle; Style body;
	};

	export_ TWO_UI_EXPORT ExpandboxStyles& expandbox_styles();

	export_ struct TreeNodeStyles
	{
		void reset();
		Style treenode; Style header; Style toggle; Style no_toggle; Style body;
	};

	export_ TWO_UI_EXPORT TreeNodeStyles& treenode_styles();

	export_ struct TabberStyles
	{
		void reset();
		Style tab; Style tab_button; Style tabber; Style head; Style edge; Style body;
	};

	export_ TWO_UI_EXPORT TabberStyles& tabber_styles();

	export_ TWO_UI_EXPORT func_ ScrollSheet& select_list(Widget& parent);

	// @todo reflection for span<T>
	export_ TWO_UI_EXPORT func_ Table& columns(Widget& parent, span<float> weights);
	export_ TWO_UI_EXPORT func_ Table& table(Widget& parent, span<cstring> columns, span<float> weights);
	export_ TWO_UI_EXPORT func_ Widget& table_row(Widget& parent);
	export_ TWO_UI_EXPORT func_ Widget& table_separator(Widget& parent);

	export_ TWO_UI_EXPORT Expandbox& expandbox(Widget& parent, span<cstring> elements, bool open = true);
	export_ TWO_UI_EXPORT func_ Expandbox& expandbox(Widget& parent, cstring name, bool open = true);

	export_ TWO_UI_EXPORT TreeNode& tree_node(Widget& parent, span<cstring> elements, bool leaf = false, bool open = true);
	export_ TWO_UI_EXPORT func_ TreeNode& tree_node(Widget& parent, cstring name, bool leaf = false, bool open = true);
	export_ TWO_UI_EXPORT func_ Widget& tree(Widget& parent);

	export_ TWO_UI_EXPORT func_ Widget* tab(Tabber& tabber, cstring name);
	export_ TWO_UI_EXPORT func_ Tabber& tabber(Widget& parent);
}
}
