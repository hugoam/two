//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

#include <cstdio>

namespace two
{
	void style_blendish(UiWindow& ui_window)
	{
		//layout_minimal(ui_window);

		const Colour white = Colour(1.f);
		const Colour black = Colour(0.f);
		const Colour activeBlue = Colour(0.337f, 0.502f, 0.761f);
		const Colour alphaGrey = Colour(1.f, 0.3f);
		const Colour greyOverlay = Colour(0.098f, 0.902f);
		const Colour grey706 = Colour(0.706f);
		const Colour grey650 = Colour(0.650f);
		const Colour grey600 = Colour(0.600f);
		const Colour grey392 = Colour(0.392f);
		const Colour grey335 = Colour(0.335f);
		const Colour grey275 = Colour(0.275f);
		const Colour grey146 = Colour(0.146f);
		const Colour grey090 = Colour(0.090f);

		auto blendish_text = [&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
			i.m_padding = vec4(4.f);
		};

        auto blendish = [&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_text(l, i);
			i.m_border_colour = grey146;
			i.m_border_width = vec4(1.f);
			i.m_corner_radius = vec4(4.f);
			i.m_linear_gradient = vec2(15.f, -15.f);
		};

        auto blendish_dark = [&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish(l, i);
			i.m_background_colour = grey275;
		};
		
        auto blendish_clear = [&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish(l, i);
			i.m_background_colour = grey600;
		};
		
		select({ "Item", "Label", "Text", "Title", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_text(l, i);
		});

        select({ "Dockbar", "Menubar", "WindowHeader", "WindowHeaderMovable", "WindowFooter", "NodeBody", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_dark(l, i);
		});
		
        select({ "Menubar", "WindowHeader", "WindowHeaderMovable", "WindowFooter", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_width = vec4(0.f);
		});

        select({ "Filler", "Slider", "Scroller", "ScrollerKnob", "NumberField" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish(l, i);
		});

        select({ "Checkbox", "Toggle", "DockToggle", "ToolButton", "CloseButton", "RadioChoice", "Dropdown", "DropdownInput", "TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_dark(l, i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey335;
		});

        select({ "Button", "Slider", "TypeIn", "Input<string>", "NumberField", "TypedownInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_clear(l, i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
            i.m_background_colour = grey650;
		});

		select({ "NumberField", "Slider", "TypeIn", "Input<string>", "TypedownInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_linear_gradient = vec2(0.f, 25.f);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
            i.m_background_colour = grey600;
		});

        select({ "Button", "Toggle", "DockToggle", "ToolButton", "RadioChoice", "Dropdown", "DropdownInput", "TabHeader" })
		.decline({ PRESSED, SELECTED, ACTIVE, PRESSED|ACTIVE }, [&](InkStyle& i) {
			i.m_linear_gradient = vec2(-15.f, 15.f);
		});

        select({ "Toggle", "DockToggle", "ToolButton", "RadioChoice", "TabHeader" })
		.decline({ ACTIVE, ACTIVE|HOVERED, PRESSED|HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
        })
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_text_colour = black;
		});
		
        select({ "TabberEdge" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = activeBlue;
		});

        select({ "DropdownChoice", "Menu", "MenuChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
			i.m_linear_gradient = vec2(-15.f, 15.f);
            i.m_text_colour = black;
		});

        select({ "TabHeader" })
		.style([&](InkStyle& i) {
			i.m_border_width = vec4(0.f);
			i.m_corner_radius = vec4(4.f, 4.f, 0.f, 0.f);
		});

        select({ "MultiButton", "ExpandboxHeader", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			blendish_text(l, i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = alphaGrey;
			i.m_border_width = vec4(2.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_background_colour = alphaGrey;
		});

        select({ "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_size = vec2(16.f);
		})
		.decline({ ACTIVE, ACTIVE|HOVERED }, [&](InkStyle& i) {
			i.m_overlay = ui_window.find_image("blendish_check");
			i.m_padding = vec4(2.f, 2.f, 0.f, 0.f);
		});

        select({ "RadioSwitch", "ColourSlab", "ColourDisplay", "ColourToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(4.f);
		});

        select({ "RadioChoice" })
		.style([&](InkStyle& i) {
			i.m_weak_corners = true;
		});

        select({ "Slider" })
		.style([&](InkStyle& i) {
			i.m_corner_radius = vec4(10.f);
		});

        select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_flow = LayoutFlow::Overlay;
		});

        select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.447f);
			i.m_linear_gradient = vec2(15.f, -5.f);
			i.m_weak_corners = true;
		});

        select({ "Menubar", "WindowHeader", "WindowHeaderMovable", "WindowFooter", "NodeBody", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(4.f, 2.f, 4.f, 2.f);
			i.m_weak_corners = true;
		});

        select({ "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(0.f, 0.f, 4.f, 4.f);
		});

        select({ "DockWindow" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(3.f);
		});

        select({ "Window", "Node", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
			i.m_corner_radius = vec4(10.f);
			i.m_shadow = Shadow(2.f, 2.f, 7.f, 2.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = Shadow(0.f, 0.f, 0.f, 1.f, grey600);
        });
		
		select({ "NodePlugs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(-5.f, 0.f, -5.f, 0.f);
		});

        select({ "WindowBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(10.f, 4.f, 4.f, 4.f);
		});
		
		select({ "TreeNodeBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12, 0, 0, 0);
		});

		select({ "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12, 6, 8, 6);
		});

        select({ "WindowSizerLeft", "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_size = vec2(0.f, 8.f);
		});

        select({ "CloseButton" })
		.style([&](InkStyle& i) {
			i.m_border_width = vec4(0.f);
			i.m_padding = vec4(2.f);
		});

        select({ "Scroller", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(6.f);
		});

        select({ "Scroller" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.314f, 0.706f);
			i.m_linear_gradient = vec2(-15.f, 15.f);
		});

        select({ "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.502f);
			i.m_linear_gradient = vec2(5.f, -5.f);
		})
		.decline({ HOVERED, PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = Colour(0.542f);
        });

        select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("blendish_updown");
		});

        select({ "ExpandboxToggle", "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("arrow_right_15");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("arrow_down_15");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("empty_15");
		});

        select({ "Tooltip", "DropdownList", "MenuList", "SubMenuList", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = greyOverlay;
			i.m_text_colour = Colour(0.627f);
		});

        select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(8.f, 2.f, 8.f, 2.f);
		});

        select({ "Toolbar", "Tab", "Header", "Scrollbar", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(6.f);
		});

        select({ "Dockbar", "Toolbar", "Menubar", "Header" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(6.f);
		});

		ui::scrollbar_styles().scroll_up.m_skin.m_image = ui_window.find_image("arrow_up_15");
		ui::scrollbar_styles().scroll_down.m_skin.m_image = ui_window.find_image("arrow_down_15");
		ui::scrollbar_styles().scroll_left.m_skin.m_image = ui_window.find_image("arrow_left_15");
		ui::scrollbar_styles().scroll_right.m_skin.m_image = ui_window.find_image("arrow_right_15");
		
        select({ "CloseButton" })
		.style([&](InkStyle& i) {
			i.m_image = ui_window.find_image("close_15");
		});
		
        select({ "Canvas"})
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		//ui::toolbar_styles().mover.m_skin.m_image = ui_window.find_image("handle");

		//ui::treenode_styles().no_toggle.m_skin.m_image = ui_window.find_image("empty_15");

		//ui::treenode_styles().toggle.m_skin.m_image = ui_window.find_image("toggle_closed");
		//ui::treenode_styles().toggle.decline_skin(ACTIVE).m_image = ui_window.find_image("toggle_open");
		//ui::treenode_styles().toggle.decline_skin(DISABLED).m_image = ui_window.find_image("empty_15");
	}

	void style_blendish_light(UiWindow& ui_window)
	{
		style_blendish(ui_window);

		const Colour black = Colour(0.f);
		const Colour white = Colour(1.f);
		const Colour none = Colour(0.f, 0.f);
		const Colour grey600 = Colour(0.600f);
		const Colour grey447 = Colour(0.447f);
		const Colour grey407 = Colour(0.407f);
		const Colour grey367 = Colour(0.367f);
		const Colour grey275 = Colour(0.275f);
		const Colour grey146 = Colour(0.146f);

        select({ "Label", "Text", "Title", "SliderDisplay", "ExpandboxHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = black;
			i.m_padding = vec4(4.f);
		});

        select({ "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey407;
			i.m_border_colour = grey275;
		});

        select({ "Window", "DockWindow", "Expandbox", "Tree", "Header", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey447;
		});

        select({ "Title", "WindowHeader", "WindowHeaderMovable" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		});

        select({ "WindowFooter" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey600;
		});
		
        select({ "ColumnHeader", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_colour = grey275;
			i.m_border_width = vec4(1.f);
		});

		//select({ "CloseButton" });

        select({ "Expandbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_linear_gradient = vec2(5.f, 0.f);
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey447; // grey117;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = none;
		});

		for(auto name_style : g_styles)
			name_style.second->prepare();
	}

	void style_blendish_dark(UiWindow& ui_window)
	{
		style_blendish(ui_window);

		const Colour black = Colour(0.f);
		const Colour grey275 = Colour(0.275f);
		const Colour grey090 = Colour(0.090f);

        select({ "Tab", "DockWindow" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey090;
		});

        select({ "Window", "Node", "Tab", "List", "ColumnHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_colour = grey275;
			i.m_border_width = vec4(1.f);
		});

        select({ "Window", "Node" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.1f);
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.f);
		});

		for(auto name_style : g_styles)
			name_style.second->prepare();
	}
}
