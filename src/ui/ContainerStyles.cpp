//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Container.h>
#include <ui/Edit/Directory.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Styles.h>
#endif

namespace mud
{
namespace ui
{
	TableStyles::TableStyles()
		: row("TableRow", styles().wrap_button, {})
		, row_odd("TableRowOdd", row, {}, [](InkStyle& l) { l.m_empty = false; l.m_background_colour = Colour{ 0.1f, 0.1f, 0.1f }; })
		, row_even("TableRowEven", row, {}, [](InkStyle& l) { l.m_empty = false; l.m_background_colour = Colour::Black; })
	{}

	ExpandboxStyles::ExpandboxStyles()
		: expandbox("Expandbox", styles().stack, {})
		, header("ExpandboxHeader", styles().wrap_button, {})
		, toggle("ExpandboxToggle", styles().toggle, {})
		, body("ExpandboxBody", styles().stack, [](Layout& l) { l.m_padding = { 12.f, 2.f, 0.f, 2.f }; l.m_spacing = vec2(6.f); })
	{}

	TreeNodeStyles::TreeNodeStyles()
		: treenode("TreeNode", expandbox_styles().expandbox, {})
		, header("TreeNodeHeader", expandbox_styles().header, {})
		, toggle("TreeNodeToggle", expandbox_styles().toggle, {})
		, no_toggle("TreeNodeNoToggle", toggle, {})
		, body("TreeNodeBody", expandbox_styles().body, [](Layout& l) { l.m_padding = { 18.f, 0.f, 0.f, 0.f }; l.m_spacing = vec2(0.f); })
	{}

	TabberStyles::TabberStyles()
		: tab("Tab", styles().wedge, [](Layout& l) { l.m_clipping = CLIP; })
		, tab_button("TabHeader", styles().button, {})
		, tabber("Tabber", styles().wedge, {})
		, head("TabberHead", styles().row, {})
		, body("TabberBody", styles().sheet, {})
	{}

	FileStyles::FileStyles()
		: dir("Dir", styles().multi_button, {})
		, file("File", styles().multi_button, {})
	{}

	TableStyles& table_styles() { static TableStyles styles; return styles; }
	ExpandboxStyles& expandbox_styles() { static ExpandboxStyles styles; return styles; }
	TreeNodeStyles& treenode_styles() { static TreeNodeStyles styles; return styles; }
	TabberStyles& tabber_styles() { static TabberStyles styles; return styles; }
	FileStyles& file_styles() { static FileStyles styles; return styles; }
}
}
