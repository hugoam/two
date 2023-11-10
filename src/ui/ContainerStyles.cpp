//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <ui/Container.h>
#include <ui/Edit/Directory.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Styles.h>
#endif

namespace two
{
namespace ui
{
	void TableStyles::reset()
	{
		row = Style("TableRow", styles().wrap_button, {});
		row_odd = Style("TableRowOdd", row, {}, [](InkStyle& l) { l.m_empty = false; });
		row_even = Style("TableRowEven", row, {}, [](InkStyle& l) { l.m_empty = false; });
		separator = Style("TableSeparator", styles().row, [](Layout& l) { l.m_no_grid = true; });

		register_styles({ &row, &row_odd, &row_even, &separator });
	}

	void ExpandboxStyles::reset()
	{
		expandbox = Style("Expandbox", styles().stack, {});
		header = Style("ExpandboxHeader", styles().wrap_button, {});
		toggle = Style("ExpandboxToggle", styles().toggle, {});
		body = Style("ExpandboxBody", styles().stack, [](Layout& l) { UNUSED(l); }); //  l.m_padding = vec4(12.f, 2.f, 0.f, 2.f); l.m_spacing = vec2(0.f); 

		register_styles({ &expandbox, &header, &toggle, &body });
	}

	void TreeNodeStyles::reset()
	{
		treenode = Style("TreeNode", expandbox_styles().expandbox, {});
		header = Style("TreeNodeHeader", expandbox_styles().header, {});
		toggle = Style("TreeNodeToggle", expandbox_styles().toggle, {});
		no_toggle = Style("TreeNodeNoToggle", toggle, {});
		body = Style("TreeNodeBody", expandbox_styles().body, [](Layout& l) { UNUSED(l); }); // l.m_padding = vec4(18.f, 0.f, 0.f, 0.f); l.m_spacing = vec2(0.f); 

		register_styles({ &treenode, &header, &toggle, &no_toggle, &body });
	}

	void TabberStyles::reset()
	{
		tab = Style("Tab", styles().wedge, [](Layout& l) { l.m_clipping = Clip::Clip; });
		tab_button = Style("TabHeader", styles().button, {});
		tabber = Style("Tabber", styles().wedge, {});
		head = Style("TabberHead", styles().row, {});
		edge = Style("TabberEdge", styles().separator, {});
		body = Style("TabberBody", styles().sheet, {});

		register_styles({ &tab, &tab_button, &tabber, &head, &edge, &body });
	}

	void FileStyles::reset()
	{
		dir = Style("Dir", styles().multi_button, {});
		file = Style("File", styles().multi_button, {});

		register_styles({ &dir, &file });
	}

	TableStyles& table_styles() { static TableStyles styles; return styles; }
	ExpandboxStyles& expandbox_styles() { static ExpandboxStyles styles; return styles; }
	TreeNodeStyles& treenode_styles() { static TreeNodeStyles styles; return styles; }
	TabberStyles& tabber_styles() { static TabberStyles styles; return styles; }
	FileStyles& file_styles() { static FileStyles styles; return styles; }
}
}
