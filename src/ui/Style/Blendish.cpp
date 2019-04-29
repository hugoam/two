//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_MODULES
module mud.ui;
#else
#include <stl/hash_base.hpp>
#include <math/Vec.hpp>
#include <ui/Style/Styles.h>
#include <ui/UiWindow.h>
#include <ui/Widget.h>
#endif

namespace mud
{
	void style_blendish(UiWindow& ui_window)
	{
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

		select({ "Item, Label, Title, TextEdit, TypeLabel, TypeZone, SliderDisplay, RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
			i.m_padding = vec4(4.f);
		});

        select({ "Blendish, BlendishDark, BlendishClear" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//"copy_skin" : "Label",
			i.m_border_colour = grey146;
			i.m_border_width = vec4(1.f);
			i.m_corner_radius = vec4(4.f);
			i.m_linear_gradient = vec2(15.f, -15.f);
		});

        select({ "BlendishDark" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey275;
		});

        select({ "BlendishClear" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey600;
		});

        select({ "Dockbar, Menubar, WindowHeader, WindowHeaderMovable, WindowFooter, NodeBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//"copy_skin" : "BlendishDark"
		});

        select({ "Filler, Slider, Scroller, ScrollerKnob, NumberField" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//"copy_skin" : "Blendish"
		});

        select({ "Checkbox, Toggle, DockToggle, ToolButton, CloseButton, RadioChoice, Dropdown, DropdownInput, TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//"copy_skin" : "BlendishDark",
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = grey335;
		});

        select({ "Button, Slider, TypeIn, Input<string>, NumberField, TypedownInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//"copy_skin" : "BlendishClear",
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
            i.m_background_colour = grey650;
		});

		select({ "NumberField, Slider, TypeIn, Input<string>, TypedownInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_linear_gradient = vec2(0.f, 25.f);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
            i.m_background_colour = grey600;
		});

        select({ "Button, Toggle, DockToggle, ToolButton, RadioChoice, Dropdown, DropdownInput, TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
		})
		.decline({ PRESSED, SELECTED, ACTIVE, PRESSED|ACTIVE }, [&](InkStyle& i) {
			i.m_linear_gradient = vec2(-15.f, 15.f);
		});

        select({ "Toggle, DockToggle, ToolButton, RadioChoice, TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
		})
		.decline({ ACTIVE, ACTIVE|HOVERED, PRESSED|HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
        })
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_text_colour = black;
		});

        select({ "DropdownChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
			i.m_linear_gradient = vec2(-15.f, 15.f);
            i.m_text_colour = black;
		});

        select({ "TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_width = vec4(0.f);
			i.m_corner_radius = vec4(4.f, 4.f, 0.f, 0.f);
		});

        select({ "MultiButton, ExpandboxHeader, TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//"copy_skin" : "Label",
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = alphaGrey;
			i.m_border_width = vec4(2.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_background_colour = alphaGrey;
		});

        select({ "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_size = vec2(16.f);
		})
		.decline({ ACTIVE, ACTIVE|HOVERED }, [&](InkStyle& i) {
			//i.m_overlay = "blendish_check";
			i.m_padding = vec4(2.f, 2.f, 0.f, 0.f);
		});

        select({ "RadioSwitch, ColourSlab, ColourDisplay, ColourToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(4.f);
		});

        select({ "RadioChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_weak_corners = true;
		});

        select({ "Slider" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(10.f);
		});

        select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_flow = LayoutFlow::Overlay;
		});

        select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.447f);
			i.m_linear_gradient = vec2(15.f, -5.f);
			i.m_weak_corners = true;
		});

        select({ "Menubar, WindowHeader, WindowHeaderMovable, WindowFooter, NodeBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(4.f, 2.f, 4.f, 2.f);
			i.m_weak_corners = true;
		});

        select({ "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(0.f, 4.f, 4.f, 4.f);
		});

        select({ "DockWindow" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(3.f);
		});

        select({ "Window, Node" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
			i.m_corner_radius = vec4(10.f);
			i.m_shadow = Shadow(2.f, 2.f, 7.f, 2.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
            i.m_shadow = Shadow(0.f, 0.f, 7.f, 2.f);
            i.m_shadow_colour = black;
        });

        select({ "Node" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(-5.f, 0.f, -5.f, 0.f);
		});

        select({ "WindowBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(10.f, 4.f, 4.f, 4.f);
		});

        select({ "WindowSizerLeft, WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_size = vec2(0.f, 8.f);
		});

        select({ "CloseButton" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_width = vec4(0.f);
			i.m_padding = vec4(2.f);
		});

        select({ "Scroller, ScrollerKnob" })
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

        select({ "ExpandboxToggle, TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("arrow_right_15");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("arrow_down_15");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("empty_15");
		});

        select({ "Tooltip, DropdownList, MenuList, SubMenuList, Popup, ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = greyOverlay;
			i.m_text_colour = Colour(0.627f);
		});

        select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(8.f, 2.f, 8.f, 2.f);
		});

        select({ "Dockbar, Toolbar, Tab, Header, Scrollbar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(6.f);
		});

        select({ "Dockbar, Toolbar, Menubar, Header" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_spacing = vec2(6.f);
		});
	}

	void style_blendish_light(UiWindow& ui_window)
	{
		style_blendish(ui_window);

		const Colour black = Colour(0.f);
		const Colour white = Colour(1.f);
		const Colour grey600 = Colour(0.600f);
		const Colour grey447 = Colour(0.447f);
		const Colour grey367 = Colour(0.367f);
		const Colour grey275 = Colour(0.275f);
		const Colour grey146 = Colour(0.146f);

        select({ "Label, Title, SliderDisplay" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = black;
			i.m_padding = vec4(4.f);
		});

        select({ "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey367;
			i.m_border_colour = grey275;
		});

        select({ "Window, DockWindow, Expandbox, Tree, Header" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey447;
		});

        select({ "WindowHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		});

        select({ "WindowFooter" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey600;
		});

		//select({ "CloseButton" });

        select({ "Expandbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_linear_gradient = vec2(5.f, 0.f);
		});

        select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});
	}

	void style_blendish_dark(UiWindow& ui_window)
	{
		style_blendish(ui_window);

		const Colour black = Colour(0.f);
		const Colour grey275 = Colour(0.275f);
		const Colour grey090 = Colour(0.090f);

        select({ "Tab, DockWindow"})
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey090;
		});

        select({ "Window, Node, Tab, List, ColumnHeader"})
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_colour = grey275;
			i.m_border_width = vec4(1.f);
		});

        select({ "Window, Node"})
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

        select({ "Canvas"})
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});
	}
}
