//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <stl/hash_base.hpp>
#include <math/Vec.hpp>
#include <ui/Style/Styles.h>
#include <ui/UiWindow.h>
#include <ui/Widget.h>
#endif

namespace two
{
	void style_blender_dark(UiWindow& ui_window)
	{
		layout_minimal(ui_window);

		const Colour active_blue_alpha = rgba(0x5680c2e6);
		const Colour active_blue = rgb(0x5680c2);
		const Colour grey_37 = rgb(0x373737);
		const Colour grey_44 = rgb(0x444444);
		const Colour grey_58 = rgb(0x585858);
		const Colour grey_59 = rgb(0x595959);
		const Colour white_d9 = rgb(0xd9d9d9);
		const Colour white_e6 = rgb(0xe6e6e6);
		const Colour white = rgb(0xffffff);

		auto wcol_regular = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = grey_58;
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0x3e3e3eff),
			i.m_text_colour = white_d9;
			s.m_text_colour = white;
			//.shadedown = -5,
			//.roundness = 0.2f,
		};
		auto wcol_tool = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = grey_58;
			s.m_background_colour = active_blue;
			//.item = RGBA(0xffffffff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadedown = -5,
			//.roundness = 0.2f,
		};
		auto wcol_toolbar_item = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = rgb(0x313131);
			s.m_background_colour = active_blue;
			//.item = RGBA(0xffffff8f);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_text = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = rgb(0x1f1f1f);
			s.m_background_colour = rgba(0xb3b3b333);
			//.item = RGBA(0x191919ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shaded = 1,
			//.shadetop = -3,
			//.roundness = 0.2f,
		};
		auto wcol_radio = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = grey_59;
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0xffffffff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadetop = 5,
			//.shadedown = -5,
			//.roundness = 0.2f,
		};
		auto wcol_option = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = rgb(0x666666);
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0xffffffff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadedown = -15,
			//.roundness = 0.2f,
		};
		auto wcol_toggle = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_37;
			i.m_background_colour = grey_59;
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0x191919ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_num = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = grey_59;
			s.m_background_colour = rgba(0xb3b3b333);
			//.item = RGBA(0x191919ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_numslider = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = grey_59;
			s.m_background_colour = rgba(0xb3b3b333);
			//.item = RGBA(0x5680c2e6);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shaded = 1,
			//.shadetop = -4,
			//.roundness = 0.2f,
		};
		auto wcol_tab = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x202020);
			i.m_background_colour = rgb(0x2b2b2b);
			s.m_background_colour = rgb(0x424242);
			//.item = RGBA(0x2d2d2dff);
			i.m_text_colour = rgb(0x989898);
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_menu = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = rgb(0x2c2c2c);
			s.m_background_colour = rgb(0x696e76);
			//.item = RGBA(0xe6e6e6ff);
			i.m_text_colour = white_d9;
			s.m_text_colour = white;
			//.shadetop = 10,
			//.shadedown = -10,
			//.roundness = 0.2f,
		};
		auto wcol_pulldown = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x4d4d4d);
			i.m_background_colour = rgba(0x2e2e2ecc);
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0x727272ff);
			i.m_text_colour = white_d9;
			s.m_text_colour = white;
			//.shadetop = 25,
			//.shadedown = -20,
			//.roundness = 0.2f,
		};
		auto wcol_menu_back = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x19191a);
			i.m_background_colour = rgba(0x1f1f1fef);
			s.m_background_colour = rgb(0x585858);
			//.item = RGBA(0x727272ff);
			i.m_text_colour = rgb(0xa5a5a5);
			s.m_text_colour = white;
			//.shadetop = 25,
			//.shadedown = -20,
			//.roundness = 0.2f,
		};
		auto wcol_menu_item = [=](InkStyle& i, InkStyle& s)
		{
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0xffffff8f);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadetop = 38,
			//.roundness = 0.2f,
		};
		auto wcol_tooltip = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x19191a);
			i.m_background_colour = rgba(0x19191aef);
			s.m_background_colour = rgba(0x19191aef);
			//.item = RGBA(0x19191aef);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadetop = 25,
			//.shadedown = -20,
			//.roundness = 0.2f,
		};
		auto wcol_box = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = grey_44;
			i.m_background_colour = rgba(0x00000033);
			s.m_background_colour = rgb(0x696e76);
			//.item = RGBA(0x191919ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_scroll = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x424242);
			i.m_background_colour = rgba(0x67676700);
			s.m_background_colour = rgb(0xb3b3b3);
			//.item = RGBA(0x676767ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.shadetop = 5,
			//.shadedown = -5,
			//.roundness = 0.5f,
		};
		auto wcol_progress = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x585858);
			i.m_background_colour = rgb(0x2c2c2c);
			s.m_background_colour = active_blue;
			//.item = RGBA(0x5680c2ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_list_item = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x2d2d2d);
			i.m_background_colour = rgba(0x2d2d2d00);
			s.m_background_colour = rgb(0x696e76);
			//.item = RGBA(0xb3b3b3ff);
			i.m_text_colour = white_e6;
			s.m_text_colour = white;
			//.roundness = 0.2f,
		};
		auto wcol_pie_menu = [=](InkStyle& i, InkStyle& s)
		{
			i.m_border_colour = rgb(0x333333);
			i.m_background_colour = rgba(0x212121ef);
			s.m_background_colour = active_blue_alpha;
			//.item = RGBA(0x585858ff);
			i.m_text_colour = white_d9;
			s.m_text_colour = white;
			//.shadetop = 10,
			//.shadedown = -10,
			//.roundness = 0.2f,
		};

		/*.tdefaults = {
			.back = RGBA(0x42424200),
			.title = RGBA(0xffffffff),
			.text = RGBA(0xe6e6e6ff),
			.text_hi = RGBA(0xffffffff),
			.header = RGBA(0x424242ff),
			.header_text = RGBA(0xeeeeeeff),
			.header_text_hi = RGBA(0xffffffff),
			.tab_active = RGBA(0x4b4b4bff),
			.tab_inactive = RGBA(0x2b2b2bff),
			.tab_back = RGBA(0x232323ff),
			.tab_outline = RGBA(0x232323ff),
			.button = RGBA(0x424242ff),
			.button_title = RGBA(0xffffffff),
			.button_text = RGBA(0xe5e5e5ff),
			.button_text_hi = RGBA(0xffffffff),
			.panelcolors = {
				.header = RGBA(0x424242cc),
				.back = RGBA(0x333333b3),
				.sub_back = RGBA(0x0000003e),
			},
		};*/

#if 0
		select({ "Label", "Title", "Message", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_text_colour = white;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = grey248;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().label.skin();
			i.m_background_colour = grey204;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey312;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		});

		select({ "CloseButton", "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().button.skin();
		});

		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey86;
		});

		select({ "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_align = { CENTER, CENTER };
		});

		select({ "SliderKnob", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().button.skin();
			i.m_background_colour = grey176;
		});

		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey312;
			l.m_size = vec2(8, 22);
		});

		select({ "ScrollUp", "ScrollDown" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(10, 0);
		});

		select({ "ScrollLeft", "ScrollRight" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(0, 10);
		});

		select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("drop_down");
		});

		select({  "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) {
			l.m_size = vec2(15.f);
			i.m_padding = vec4(1);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("check_15");
		});

		select({ "Slider", "Fillbar", "TypeIn", "Input<string>"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey145;
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey204;
			i.m_border_colour = grey400;
			i.m_border_width = vec4(1);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
		});

		select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey248;
		});

		select({ "List", "Tree", "TabberHead", "TableHead", "Dockbar", "Header", "Menubar" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey117;
		});

		select({ "Window", "WindowFooter", "DockWindow", "Dockbox", "Tab", "TextEdit", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey52;
			i.m_border_colour = grey204;
			i.m_border_width = vec4(1);
		});

		select({ "Window", "Dockbox", "Node" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_shadow = { 2, 2, 7, 2 };
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = { 0, 0, 0, 1, grey600 };
		});

		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey204;
		});

		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("handle_x");
			i.m_padding = vec4(2);
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_align = { Right, Right };
		});

		select({  "Toolbar", "Tooldock"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey145;
		});

		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = black;
		});

		select({  "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = { 0.098, 0.098, 0.098, 0.802 };
			i.m_text_colour = clearGreyText;
		});

		select({ "DropdownChoice" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = transparent;
		});

		select({ "TableRow", "TableRowOdd", "TableRowEven"  })
		.declare([&](Layout& l, InkStyle& i) {
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
			i.m_border_width = vec4(1);
		});
#endif

#if 0
		Colour white = { 1.f };
		Colour black = { 0.f };
		Colour transparent = { 0.f, 0.f };
		Colour clearGreyText = { 0.627f };
		Colour grey600 = { 0.600f };
		Colour grey400 = { 0.400f };
		Colour grey312 = { 0.312f };
		Colour grey248 = { 0.248f };
		Colour grey204 = { 0.204f };
		Colour grey176 = { 0.176f };
		Colour grey145 = { 0.145f };
		Colour grey117 = { 0.117f };
		Colour grey86  = { 0.086f };
		Colour grey69  = { 0.069f };
		Colour grey52  = { 0.052f };
		Colour activeBlue = { 0.145f, 0.5f, 1.f, 1.f };

		select({ "Label", "Title", "Message", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_text_colour = white;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = grey248;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().label.skin();
			i.m_background_colour = grey204;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey312;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		});

		select({ "CloseButton", "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().button.skin();
		});

		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey86;
		});

		select({ "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_align = { CENTER, CENTER };
		});

		select({ "SliderKnob", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) {
			i = styles().button.skin();
			i.m_background_colour = grey176;
		});

		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey312;
			l.m_size = vec2(8, 22);
		});

		select({ "ScrollUp", "ScrollDown" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(10, 0);
		});

		select({ "ScrollLeft", "ScrollRight" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(0, 10);
		});

		select({ "ExpandboxToggle", "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_closed");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("toggle_open");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("empty_15");
		});

		select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("drop_down");
		});

		select({  "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) {
			l.m_size = vec2(15.f);
			i.m_padding = vec4(1);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("check_15");
		});

		select({ "Slider", "Fillbar", "TypeIn", "Input<string>"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey145;
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey204;
			i.m_border_colour = grey400;
			i.m_border_width = vec4(1);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
		});

		select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey248;
		});

		select({ "List", "Tree", "TabberHead", "TableHead", "Dockbar", "Header", "Menubar" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey117;
		});

		select({ "Window", "WindowFooter", "DockWindow", "Dockbox", "Tab", "TextEdit", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey52;
			i.m_border_colour = grey204;
			i.m_border_width = vec4(1);
		});

		select({ "Window", "Dockbox", "Node" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_shadow = { 2, 2, 7, 2 };
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = { 0, 0, 0, 1, grey600 };
		});

		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey204;
		});

		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_image = ui_window.find_image("handle_x");
			i.m_padding = vec4(2);
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_align = { Right, Right };
		});

		select({  "Toolbar", "Tooldock"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey145;
		});

		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = black;
		});

		select({  "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = { 0.098, 0.098, 0.098, 0.802 };
			i.m_text_colour = clearGreyText;
		});

		select({ "DropdownChoice" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = transparent;
		});

		select({ "TableRow", "TableRowOdd", "TableRowEven"  })
		.declare([&](Layout& l, InkStyle& i) {
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
			i.m_border_width = vec4(1);
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = grey117;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = black;
		});
#endif
	}
}

/*
const bTheme U_theme_default = {
	.name = "Default",
	.tui = {
		.wcol_regular = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x585858ff),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0x3e3e3eff),
			.text = RGBA(0xd9d9d9ff),
			.text_sel = RGBA(0xffffffff),
			.shadedown = -5,
			.roundness = 0.2f,
		},
		.wcol_tool = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x585858ff),
			.inner_sel = RGBA(0x5680c2ff),
			.item = RGBA(0xffffffff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadedown = -5,
			.roundness = 0.2f,
		},
		.wcol_toolbar_item = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x313131ff),
			.inner_sel = RGBA(0x5680c2ff),
			.item = RGBA(0xffffff8f),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_text = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x1f1f1fff),
			.inner_sel = RGBA(0xb3b3b333),
			.item = RGBA(0x191919ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shaded = 1,
			.shadetop = -3,
			.roundness = 0.2f,
		},
		.wcol_radio = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x595959ff),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0xffffffff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 5,
			.shadedown = -5,
			.roundness = 0.2f,
		},
		.wcol_option = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x666666ff),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0xffffffff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadedown = -15,
			.roundness = 0.2f,
		},
		.wcol_toggle = {
			.outline = RGBA(0x373737ff),
			.inner = RGBA(0x595959ff),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0x191919ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_num = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x595959ff),
			.inner_sel = RGBA(0xb3b3b333),
			.item = RGBA(0x191919ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_numslider = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x595959ff),
			.inner_sel = RGBA(0xb3b3b333),
			.item = RGBA(0x5680c2e6),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shaded = 1,
			.shadetop = -4,
			.roundness = 0.2f,
		},
		.wcol_tab = {
			.outline = RGBA(0x202020ff),
			.inner = RGBA(0x2b2b2bff),
			.inner_sel = RGBA(0x424242ff),
			.item = RGBA(0x2d2d2dff),
			.text = RGBA(0x989898ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_menu = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x2c2c2cff),
			.inner_sel = RGBA(0x696e76ff),
			.item = RGBA(0xe6e6e6ff),
			.text = RGBA(0xd9d9d9ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 10,
			.shadedown = -10,
			.roundness = 0.2f,
		},
		.wcol_pulldown = {
			.outline = RGBA(0x4d4d4dff),
			.inner = RGBA(0x2e2e2ecc),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0x727272ff),
			.text = RGBA(0xd9d9d9ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 25,
			.shadedown = -20,
			.roundness = 0.2f,
		},
		.wcol_menu_back = {
			.outline = RGBA(0x19191aff),
			.inner = RGBA(0x1f1f1fef),
			.inner_sel = RGBA(0x585858ff),
			.item = RGBA(0x727272ff),
			.text = RGBA(0xa5a5a5ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 25,
			.shadedown = -20,
			.roundness = 0.2f,
		},
		.wcol_menu_item = {
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0xffffff8f),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 38,
			.roundness = 0.2f,
		},
		.wcol_tooltip = {
			.outline = RGBA(0x19191aff),
			.inner = RGBA(0x19191aef),
			.inner_sel = RGBA(0x19191aef),
			.item = RGBA(0x19191aef),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 25,
			.shadedown = -20,
			.roundness = 0.2f,
		},
		.wcol_box = {
			.outline = RGBA(0x444444ff),
			.inner = RGBA(0x00000033),
			.inner_sel = RGBA(0x696e76ff),
			.item = RGBA(0x191919ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_scroll = {
			.outline = RGBA(0x424242ff),
			.inner = RGBA(0x67676700),
			.inner_sel = RGBA(0xb3b3b3ff),
			.item = RGBA(0x676767ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 5,
			.shadedown = -5,
			.roundness = 0.5f,
		},
		.wcol_progress = {
			.outline = RGBA(0x585858ff),
			.inner = RGBA(0x2c2c2cff),
			.inner_sel = RGBA(0x5680c2ff),
			.item = RGBA(0x5680c2ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_list_item = {
			.outline = RGBA(0x2d2d2dff),
			.inner = RGBA(0x2d2d2d00),
			.inner_sel = RGBA(0x696e76ff),
			.item = RGBA(0xb3b3b3ff),
			.text = RGBA(0xe6e6e6ff),
			.text_sel = RGBA(0xffffffff),
			.roundness = 0.2f,
		},
		.wcol_pie_menu = {
			.outline = RGBA(0x333333ff),
			.inner = RGBA(0x212121ef),
			.inner_sel = RGBA(0x5680c2e6),
			.item = RGBA(0x585858ff),
			.text = RGBA(0xd9d9d9ff),
			.text_sel = RGBA(0xffffffff),
			.shadetop = 10,
			.shadedown = -10,
			.roundness = 0.2f,
		},
		.wcol_state = {
			.inner_anim = RGBA(0x53992eff),
			.inner_anim_sel = RGBA(0x5aa633ff),
			.inner_key = RGBA(0xb3ae36ff),
			.inner_key_sel = RGBA(0xd7d34bff),
			.inner_driven = RGBA(0x9000ccff),
			.inner_driven_sel = RGBA(0x9900e6ff),
			.inner_overridden = RGBA(0x19c3c300),
			.inner_overridden_sel = RGBA(0x118f8f00),
			.inner_changed = RGBA(0xcc7529ff),
			.inner_changed_sel = RGBA(0xe6852dff),
			.blend = 0.5f,
		},
		.widget_emboss = RGBA(0x00000005),
		.menu_shadow_fac = 0.3f,
		.menu_shadow_width = 4,
		.editor_outline = RGBA(0x1f1f1fff),
		.icon_alpha = 1.0f,
		.icon_saturation = 0.5f,
		.xaxis = RGBA(0xff3352ff),
		.yaxis = RGBA(0x8bdc00ff),
		.zaxis = RGBA(0x2890ffff),
		.gizmo_hi = RGBA(0xffffffff),
		.gizmo_primary = RGBA(0xf5f14dff),
		.gizmo_secondary = RGBA(0x63ffffff),
		.gizmo_a = RGBA(0x4da84dff),
		.gizmo_b = RGBA(0xa33535ff),
		.icon_collection = RGBA(0xe6e6e6ff),
		.icon_object = RGBA(0xe49759ff),
		.icon_object_data = RGBA(0x89e689ff),
		.icon_modifier = RGBA(0x84b8ffff),
		.icon_shading = RGBA(0xff6060ff),
	},
	.tdefaults = {
		.back = RGBA(0x42424200),
		.title = RGBA(0xffffffff),
		.text = RGBA(0xe6e6e6ff),
		.text_hi = RGBA(0xffffffff),
		.header = RGBA(0x424242ff),
		.header_text = RGBA(0xeeeeeeff),
		.header_text_hi = RGBA(0xffffffff),
		.tab_active = RGBA(0x4b4b4bff),
		.tab_inactive = RGBA(0x2b2b2bff),
		.tab_back = RGBA(0x232323ff),
		.tab_outline = RGBA(0x232323ff),
		.button = RGBA(0x424242ff),
		.button_title = RGBA(0xffffffff),
		.button_text = RGBA(0xe5e5e5ff),
		.button_text_hi = RGBA(0xffffffff),
		.panelcolors = {
			.header = RGBA(0x424242cc),
			.back = RGBA(0x333333b3),
			.sub_back = RGBA(0x0000003e),
		},
	},
	.tbuts = {
		.title = RGBA(0xd4d4d4ff),
		.navigation_bar = RGBA(0x232323ff),
		.panelcolors = {
			.header = RGBA(0x42424200),
			.back = RGBA(0x00000028),
			.sub_back = RGBA(0x00000024),
		},
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tv3d = {
		.title = RGBA(0xeeeeeeff),
		.button = RGBA(0x35353500),
		.button_text = RGBA(0xe5e5e5ff),
		.panelcolors = {
			.header = RGBA(0x424242e6),
			.back = RGBA(0x333333f0),
			.sub_back = RGBA(0x0000003e),
		},
		.gradients = {
			.gradient = RGBA(0x39393900),
			.high_gradient = RGBA(0x393939ff),
		},
		.grid = RGBA(0xa7a7a733),
		.wire = RGBA(0x000000ff),
		.wire_edit = RGBA(0x111111ff),
		.select = RGBA(0xed5700ff),
		.lamp = RGBA(0x00000028),
		.speaker = RGBA(0x000000ff),
		.empty = RGBA(0x000000ff),
		.camera = RGBA(0x000000ff),
		.active = RGBA(0xffa028ff),
		.transform = RGBA(0xffffffff),
		.vertex = RGBA(0x000000ff),
		.vertex_select = RGBA(0xff8500ff),
		.vertex_bevel = RGBA(0x00a5ffff),
		.edge = RGBA(0x000000ff),
		.edge_select = RGBA(0xffa000ff),
		.edge_seam = RGBA(0xdb2512ff),
		.edge_sharp = RGBA(0x00ffffff),
		.edge_facesel = RGBA(0x4b4b4bff),
		.edge_crease = RGBA(0xcc0099ff),
		.edge_bevel = RGBA(0x00a5ffff),
		.face = RGBA(0x00000012),
		.face_select = RGBA(0xff85004d),
		.face_dot = RGBA(0xff8500ff),
		.extra_edge_len = RGBA(0x150806ff),
		.extra_edge_angle = RGBA(0x4d4d00ff),
		.extra_face_angle = RGBA(0x0000ccff),
		.extra_face_area = RGBA(0x004d00ff),
		.normal = RGBA(0x22ddddff),
		.vertex_normal = RGBA(0x2361ddff),
		.loop_normal = RGBA(0xdd23ddff),
		.bone_solid = RGBA(0xc8c8c8ff),
		.bone_pose = RGBA(0x50c8ff50),
		.bone_pose_active = RGBA(0x8cffff50),
		.cframe = RGBA(0x60c040ff),
		.time_keyframe = RGBA(0xddd700ff),
		.time_gp_keyframe = RGBA(0xb5e61dff),
		.freestyle_edge_mark = RGBA(0x7fff7fff),
		.freestyle_face_mark = RGBA(0x7fff7f33),
		.nurb_uline = RGBA(0x909000ff),
		.nurb_vline = RGBA(0x803060ff),
		.act_spline = RGBA(0xdb2512ff),
		.nurb_sel_uline = RGBA(0xf0ff40ff),
		.nurb_sel_vline = RGBA(0xf090a0ff),
		.lastsel_point = RGBA(0xffffffff),
		.handle_free = RGBA(0x000000ff),
		.handle_auto = RGBA(0x909000ff),
		.handle_vect = RGBA(0x409030ff),
		.handle_align = RGBA(0x803060ff),
		.handle_sel_free = RGBA(0x000000ff),
		.handle_sel_auto = RGBA(0xf0ff40ff),
		.handle_sel_vect = RGBA(0x40c030ff),
		.handle_sel_align = RGBA(0xf090a0ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 3,
		.editmesh_active = RGBA(0xffffff80),
		.clipping_border_3d = RGBA(0x313131ff),
		.bundle_solid = RGBA(0xc8c8c8ff),
		.camera_path = RGBA(0x000000ff),
		.gp_vertex_size = 3,
		.gp_vertex = RGBA(0x000000ff),
		.gp_vertex_select = RGBA(0xff8500ff),
		.skin_root = RGBA(0xb44d4dff),
		.paint_curve_pivot = RGBA(0xff7f7f7f),
		.paint_curve_handle = RGBA(0x7fff7f7f),
	},
	.tfile = {
		.back = RGBA(0x35353500),
		.header = RGBA(0x2e2e2eff),
		.hilite = RGBA(0x4f76b3ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tipo = {
		.text = RGBA(0x000000ff),
		.header = RGBA(0x2e2e2eff),
		.list = RGBA(0x333333ff),
		.list_title = RGBA(0xffffffff),
		.list_text = RGBA(0xb8b8b8ff),
		.list_text_hi = RGBA(0xffffffff),
		.shade1 = RGBA(0x96969600),
		.shade2 = RGBA(0x33333364),
		.grid = RGBA(0x2a2a2aff),
		.group = RGBA(0x16330fff),
		.group_active = RGBA(0x368024ff),
		.vertex = RGBA(0x000000ff),
		.vertex_select = RGBA(0xff8500ff),
		.cframe = RGBA(0x5680c2ff),
		.lastsel_point = RGBA(0xffffffff),
		.handle_auto = RGBA(0x909000ff),
		.handle_vect = RGBA(0x409030ff),
		.handle_align = RGBA(0x803060ff),
		.handle_auto_clamped = RGBA(0x994030ff),
		.handle_sel_auto = RGBA(0xf0ff40ff),
		.handle_sel_vect = RGBA(0x40c030ff),
		.handle_sel_align = RGBA(0xf090a0ff),
		.handle_sel_auto_clamped = RGBA(0xf0af90ff),
		.ds_channel = RGBA(0x0f2c4dff),
		.ds_subchannel = RGBA(0x143e66ff),
		.vertex_size = 6,
		.outline_width = 1,
		.facedot_size = 4,
		.handle_vertex_select = RGBA(0xff8500ff),
		.handle_vertex_size = 5,
		.anim_preview_range = RGBA(0xa14d0066),
	},
	.tinfo = {
		.title = RGBA(0xeeeeeeff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.info_selected = RGBA(0x6080ffff),
		.info_selected_text = RGBA(0xffffffff),
		.info_error = RGBA(0x990000ff),
		.info_error_text = RGBA(0xffffffff),
		.info_warning = RGBA(0xb36a00ff),
		.info_warning_text = RGBA(0xffffffff),
		.info_info = RGBA(0x668000ff),
		.info_info_text = RGBA(0xffffffff),
		.info_debug = RGBA(0xd3d3d3ff),
	},
	.tact = {
		.title = RGBA(0xeeeeeeff),
		.text = RGBA(0x000000ff),
		.list = RGBA(0x333333ff),
		.list_title = RGBA(0xffffffff),
		.list_text = RGBA(0xb8b8b8ff),
		.list_text_hi = RGBA(0xffffffff),
		.shade1 = RGBA(0xc0c0c000),
		.shade2 = RGBA(0x333333ff),
		.hilite = RGBA(0x60c04044),
		.grid = RGBA(0x2a2a2aff),
		.group = RGBA(0x16330f37),
		.group_active = RGBA(0x36802455),
		.strip = RGBA(0x1a151580),
		.strip_select = RGBA(0xff8c00cc),
		.cframe = RGBA(0x5680c2ff),
		.ds_channel = RGBA(0x0f2c4d24),
		.ds_subchannel = RGBA(0x143e6624),
		.ds_ipoline = RGBA(0x94e575cc),
		.keytype_keyframe = RGBA(0xe8e8e8ff),
		.keytype_extreme = RGBA(0xe8b3ccff),
		.keytype_breakdown = RGBA(0xb3dbe8ff),
		.keytype_jitter = RGBA(0x94e575ff),
		.keytype_movehold = RGBA(0x5c5656ff),
		.keytype_keyframe_select = RGBA(0xffbe33ff),
		.keytype_extreme_select = RGBA(0xf28080ff),
		.keytype_breakdown_select = RGBA(0x54bfedff),
		.keytype_jitter_select = RGBA(0x61c042ff),
		.keytype_movehold_select = RGBA(0xffaf23ff),
		.keyborder = RGBA(0x000000ff),
		.keyborder_select = RGBA(0x000000ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.keyframe_scale_fac = 1.0f,
		.handle_vertex_size = 4,
		.anim_active = RGBA(0x4d250066),
		.anim_preview_range = RGBA(0xa14d0066),
	},
	.tnla = {
		.text = RGBA(0x000000ff),
		.list = RGBA(0x333333ff),
		.list_title = RGBA(0xffffffff),
		.list_text = RGBA(0xb8b8b8ff),
		.list_text_hi = RGBA(0xccccccff),
		.shade1 = RGBA(0x96969600),
		.grid = RGBA(0x2a2a2aff),
		.strip = RGBA(0x0c0a0a80),
		.strip_select = RGBA(0xff8c00ff),
		.cframe = RGBA(0x5680c2ff),
		.ds_channel = RGBA(0x5a85b2ff),
		.ds_subchannel = RGBA(0x7d98b3ff),
		.keyborder = RGBA(0x000000ff),
		.keyborder_select = RGBA(0x000000ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.handle_vertex_size = 4,
		.anim_active = RGBA(0xcc701a66),
		.anim_non_active = RGBA(0x9987614d),
		.anim_preview_range = RGBA(0xa14d0066),
		.nla_tweaking = RGBA(0x4df31a4d),
		.nla_tweakdupli = RGBA(0xd90000ff),
		.nla_transition = RGBA(0x1c2630ff),
		.nla_transition_sel = RGBA(0x2e75dbff),
		.nla_meta = RGBA(0x332642ff),
		.nla_meta_sel = RGBA(0x692196ff),
		.nla_sound = RGBA(0x2b3d3dff),
		.nla_sound_sel = RGBA(0x1f7a7aff),
	},
	.tseq = {
		.title = RGBA(0xeeeeeeff),
		.text = RGBA(0x000000ff),
		.shade1 = RGBA(0xa0a0a000),
		.grid = RGBA(0x404040ff),
		.vertex_select = RGBA(0xff8500ff),
		.bone_pose = RGBA(0x50c8ff50),
		.cframe = RGBA(0x5680c2ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.movie = RGBA(0x516987ff),
		.movieclip = RGBA(0x20208fff),
		.image = RGBA(0x6d5881ff),
		.scene = RGBA(0x4e983eff),
		.audio = RGBA(0x2e8f8fff),
		.effect = RGBA(0xa9547cff),
		.transition = RGBA(0xa25f6fff),
		.meta = RGBA(0x6d9183ff),
		.text_strip = RGBA(0xa29700ff),
		.gp_vertex_size = 3,
		.gp_vertex_select = RGBA(0xff8500ff),
		.metadatatext = RGBA(0xffffffff),
	},
	.tima = {
		.back = RGBA(0x44444400),
		.title = RGBA(0xeeeeeeff),
		.button = RGBA(0x35353500),
		.button_text = RGBA(0xe5e5e5ff),
		.wire_edit = RGBA(0xc0c0c0ff),
		.vertex_select = RGBA(0xff8500ff),
		.edge_select = RGBA(0xff8500ff),
		.face = RGBA(0xffffff0a),
		.face_select = RGBA(0xff85003c),
		.face_dot = RGBA(0xff8500ff),
		.cframe = RGBA(0x60c040ff),
		.freestyle_face_mark = RGBA(0x7fff7f33),
		.handle_auto = RGBA(0x909000ff),
		.handle_align = RGBA(0x803060ff),
		.handle_sel_auto = RGBA(0xf0ff40ff),
		.handle_sel_align = RGBA(0xf090a0ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 3,
		.editmesh_active = RGBA(0xffffff80),
		.handle_vertex_select = RGBA(0xffff00ff),
		.handle_vertex_size = 5,
		.gp_vertex_size = 3,
		.gp_vertex_select = RGBA(0xff8500ff),
		.preview_back = RGBA(0x727272ff),
		.preview_stitch_face = RGBA(0x7f7f0033),
		.preview_stitch_edge = RGBA(0xff00ff33),
		.preview_stitch_vert = RGBA(0x0000ff33),
		.preview_stitch_stitchable = RGBA(0x00ff00ff),
		.preview_stitch_unstitchable = RGBA(0xff0000ff),
		.preview_stitch_active = RGBA(0xe1d2c323),
		.uv_shadow = RGBA(0x707070ff),
		.uv_others = RGBA(0x606060ff),
		.paint_curve_pivot = RGBA(0xff7f7f7f),
		.paint_curve_handle = RGBA(0x7fff7f7f),
		.metadatatext = RGBA(0xffffffff),
	},
	.text = {
		.back = RGBA(0x30303000),
		.title = RGBA(0xeeeeeeff),
		.panelcolors = {
			.header = RGBA(0x42424200),
			.back = RGBA(0x333333b3),
			.sub_back = RGBA(0x0000003e),
		},
		.shade2 = RGBA(0x19191aff),
		.hilite = RGBA(0xff0000ff),
		.grid = RGBA(0x313133ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.syntaxl = RGBA(0xf6e162ff),
		.syntaxs = RGBA(0xff734dff),
		.syntaxb = RGBA(0xff1961ff),
		.syntaxn = RGBA(0x50dbffff),
		.syntaxv = RGBA(0x95d600ff),
		.syntaxc = RGBA(0x939393ff),
		.syntaxd = RGBA(0xad80ffff),
		.syntaxr = RGBA(0xc4753bff),
	},
	.toops = {
		.back = RGBA(0x28282800),
		.text = RGBA(0xc3c3c3ff),
		.header = RGBA(0x454545ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.match = RGBA(0x337f334c),
		.selected_highlight = RGBA(0x314e784c),
	},
	.ttime = {
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tnode = {
		.back = RGBA(0x23232300),
		.title = RGBA(0xeeeeeeff),
		.list = RGBA(0x2e2e2eff),
		.list_title = RGBA(0xffffffff),
		.list_text = RGBA(0xccccccff),
		.list_text_hi = RGBA(0xffffffff),
		.shade2 = RGBA(0x7f707064),
		.wire = RGBA(0x808080ff),
		.select = RGBA(0xed5700ff),
		.active = RGBA(0xffffffff),
		.edge_select = RGBA(0xffffffff),
		.console_output = RGBA(0x1a1a1aff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.syntaxl = RGBA(0x565656ff),
		.syntaxs = RGBA(0x975b5bff),
		.syntaxb = RGBA(0xccb83dff),
		.syntaxn = RGBA(0xe64555ff),
		.syntaxv = RGBA(0x66c4ffff),
		.syntaxc = RGBA(0x426628ff),
		.syntaxd = RGBA(0x749797ff),
		.syntaxr = RGBA(0x808080ff),
		.nodeclass_output = RGBA(0xb33641ff),
		.nodeclass_filter = RGBA(0x584d80ff),
		.nodeclass_vector = RGBA(0x9b80ffff),
		.nodeclass_texture = RGBA(0xe68745ff),
		.nodeclass_shader = RGBA(0x39c884ff),
		.nodeclass_script = RGBA(0x084d4dff),
		.nodeclass_pattern = RGBA(0x6c696fff),
		.nodeclass_layout = RGBA(0x6c696fff),
		.movie = RGBA(0x1a1a1acc),
		.gp_vertex_size = 3,
		.gp_vertex = RGBA(0x97979700),
		.gp_vertex_select = RGBA(0xff8500ff),
	},
	.tuserpref = {
		.title = RGBA(0xeeeeeeff),
		.navigation_bar = RGBA(0x373737ff),
		.panelcolors = {
			.header = RGBA(0x42424200),
			.back = RGBA(0x333333b3),
			.sub_back = RGBA(0x0000003e),
		},
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tconsole = {
		.back = RGBA(0x30303000),
		.title = RGBA(0xeeeeeeff),
		.console_output = RGBA(0x71a8ffff),
		.console_input = RGBA(0xf2f2f2ff),
		.console_info = RGBA(0x95d600ff),
		.console_error = RGBA(0xff4d84ff),
		.console_cursor = RGBA(0xff0000ff),
		.console_select = RGBA(0xffffff30),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
	},
	.tclip = {
		.title = RGBA(0xeeeeeeff),
		.list = RGBA(0x666666ff),
		.list_text = RGBA(0x000000ff),
		.list_text_hi = RGBA(0xffffffff),
		.strip = RGBA(0x0c0a0a80),
		.strip_select = RGBA(0xff8c00ff),
		.cframe = RGBA(0x5680c2ff),
		.handle_auto = RGBA(0x909000ff),
		.handle_align = RGBA(0x803060ff),
		.handle_sel_auto = RGBA(0xf0ff40ff),
		.handle_sel_align = RGBA(0xf090a0ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.handle_vertex_select = RGBA(0xffff00ff),
		.handle_vertex_size = 5,
		.marker = RGBA(0x7f7f00ff),
		.act_marker = RGBA(0xffffffff),
		.sel_marker = RGBA(0xffff00ff),
		.dis_marker = RGBA(0x7f0000ff),
		.lock_marker = RGBA(0x7f7f7fff),
		.path_before = RGBA(0xff0000ff),
		.path_after = RGBA(0x0000ffff),
		.gp_vertex_size = 1,
		.metadatatext = RGBA(0xffffffff),
	},
	.ttopbar = {
		.header = RGBA(0x232323ff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.gp_vertex_size = 3,
	},
	.tstatusbar = {
		.back = RGBA(0x2e2e2e00),
		.text = RGBA(0x838383ff),
		.header = RGBA(0x303030ff),
		.header_text = RGBA(0xaaaaaaff),
		.button = RGBA(0x353535ff),
		.button_text_hi = RGBA(0xffffffff),
		.vertex_size = 3,
		.outline_width = 1,
		.facedot_size = 4,
		.gp_vertex_size = 3,
	},
	.tarm = {
		{
			.solid = RGBA(0x9a0000ff),
			.select = RGBA(0xbd1111ff),
			.active = RGBA(0xf70a0aff),
		},
		{
			.solid = RGBA(0xf74018ff),
			.select = RGBA(0xf66913ff),
			.active = RGBA(0xfa9900ff),
		},
		{
			.solid = RGBA(0x1e9109ff),
			.select = RGBA(0x59b70bff),
			.active = RGBA(0x83ef1dff),
		},
		{
			.solid = RGBA(0x0a3694ff),
			.select = RGBA(0x3667dfff),
			.active = RGBA(0x5ec1efff),
		},
		{
			.solid = RGBA(0xa9294eff),
			.select = RGBA(0xc1416aff),
			.active = RGBA(0xf05d91ff),
		},
		{
			.solid = RGBA(0x430c78ff),
			.select = RGBA(0x543aa3ff),
			.active = RGBA(0x8764d5ff),
		},
		{
			.solid = RGBA(0x24785aff),
			.select = RGBA(0x3c9579ff),
			.active = RGBA(0x6fb6abff),
		},
		{
			.solid = RGBA(0x4b707cff),
			.select = RGBA(0x6a8691ff),
			.active = RGBA(0x9bc2cdff),
		},
		{
			.solid = RGBA(0xf4c90cff),
			.select = RGBA(0xeec236ff),
			.active = RGBA(0xf3ff00ff),
		},
		{
			.solid = RGBA(0x1e2024ff),
			.select = RGBA(0x484c56ff),
			.active = RGBA(0xffffffff),
		},
		{
			.solid = RGBA(0x6f2f6aff),
			.select = RGBA(0x9845beff),
			.active = RGBA(0xd330d6ff),
		},
		{
			.solid = RGBA(0x6c8e22ff),
			.select = RGBA(0x7fb022ff),
			.active = RGBA(0xbbef5bff),
		},
		{
			.solid = RGBA(0x8d8d8dff),
			.select = RGBA(0xb0b0b0ff),
			.active = RGBA(0xdededeff),
		},
		{
			.solid = RGBA(0x834326ff),
			.select = RGBA(0x8b5811ff),
			.active = RGBA(0xbd6a11ff),
		},
		{
			.solid = RGBA(0x08310eff),
			.select = RGBA(0x1c430bff),
			.active = RGBA(0x34622bff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
		{
			.solid = RGBA(0x000000ff),
			.select = RGBA(0x000000ff),
			.active = RGBA(0x000000ff),
		},
	},
};
*/