//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/hash_base.hpp>
#include <math/Vec.hpp>
#include <ui/Style/Styles.h>
#include <ui/UiWindow.h>
#include <ui/Ui.h>
#endif

#include <cstdio>

namespace two
{
	StyleSelector& StyleSelector::declare(StyleDecl decl)
	{
		for(Style* style : styles)
			decl(style->m_layout, style->m_skin);
		return *this;
	}

	StyleSelector& StyleSelector::decline(span<uint32_t> states, InkDecl decl)
	{
		for(Style* style : styles)
			for(uint32_t state : states)
			{
				InkStyle& i = style->decline_skin(WidgetState(state));
				decl(i);
			}
		return *this;
	}

	StyleSelector& StyleSelector::style(InkDecl decl)
	{
		for(Style* style : styles)
		{
			decl(style->m_skin);
			for(Subskin& subskin : style->m_skins)
			{
				decl(subskin.skin);
			}
		}
		return *this;
	}

	StyleSelector select(span<string> styles)
	{
		StyleSelector selector;
		for(const string& name : styles)
			if(g_styles.find(name) != g_styles.end())
				selector.styles.push_back(g_styles[name]);
			else
				printf("[warning] ui - style %s not found\n", name.c_str());
		return selector;
	}

	void layout_minimal(UiWindow& ui_window)
	{
		UNUSED(ui_window);

		select({ "Label", "Title", "Message", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "Title" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(8.f);
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "Item", "DropdownToggle", "ExpandboxToggle", "TreeNodeToggle", "TreeNodeNoToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(4.f);
		});

		select({ "TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(6.f);
		});

		select({ "Tooltip", "ToolButton", "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(4.f);
		});

		select({ "Dockspace", "Toolbar", "Header", "Popup", "ScrollSurface" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(6.f);
		});

		select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(6.f, 0.f, 6.f, 0.f);
		});

		select({ "Modal" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12.f);
		});
		
		select({ "TreeNodeBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12.f, 0.f, 0.f, 0.f);
		});

		select({ "ExpandboxBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(12.f, 6.f, 8.f, 6.f);
		});

		select({ "ExpandboxBody", "WindowBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(4.f);
		});

		select({ "Dockbar", "Toolbar", "Header" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(6.f);
		});
		
		select({ "NodePlugs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(-5.f, 0.f, -5.f, 0.f);
		});
	}

	void style_minimal(UiWindow& ui_window, bool vector)
	{
		layout_minimal(ui_window);

		const Colour white = Colour(1.f);
		const Colour black = Colour(0.f);
		const Colour transparent = Colour(0.f, 0.f);
		const Colour clearGreyText = Colour(0.627f);
		const Colour grey600 = Colour(0.600f);
		const Colour grey400 = Colour(0.400f);
		const Colour grey312 = Colour(0.312f);
		const Colour grey248 = Colour(0.248f);
		const Colour grey204 = Colour(0.204f);
		const Colour grey176 = Colour(0.176f);
		const Colour grey145 = Colour(0.145f);
		const Colour grey117 = Colour(0.117f);
		const Colour grey86  = Colour(0.086f);
		const Colour grey69  = Colour(0.069f);
		const Colour grey52  = Colour(0.052f);
		const Colour activeBlue = Colour(0.145f, 0.5f, 1.f, 1.f);

		auto colour = [&](InkStyle& i, Colour colour)
		{
			if(vector)
				i.m_border_colour = colour;
			else
				i.m_background_colour = colour;
		};

		select({ "Label", "Text", "Title", "Message", "Control", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = white;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = grey248;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "ColumnHeader", "DockToggle", "RadioChoice", "DropdownChoice", "MenuChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().label.m_skin;
			colour(i, grey204);
			if(vector)
				i.m_border_width = vec4(1.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			colour(i, grey312);
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		});

		select({ "CloseButton", "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().button.m_skin;
		});

		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey86);
		});

		select({ "SliderKnob", "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i = styles().button.m_skin;
			colour(i, grey176);
		});

		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey312);
			l.m_size = vec2(8, 22);
		});

		select({ "ScrollUp", "ScrollDown" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("null");
			l.m_size = vec2(10, 0);
		});

		select({ "ScrollLeft", "ScrollRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
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
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("drop_down");
		});

		select({ "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_size = vec2(15.f);
			i.m_padding = vec4(1.f);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = ui_window.find_image("check_15");
		});

		select({ "Slider", "Fillbar", "TypeIn", "Input<string>"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey145);
			if(!vector)
				i.m_border_colour = grey312;
			i.m_border_width = vec4(1.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			colour(i, grey204);
			if(!vector)
				i.m_border_colour = grey400;
			i.m_border_width = vec4(1.f);
		})
		.decline({ FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = activeBlue;
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
		});

		select({ "Filler" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey248);
		});
		
		select({ "TabberEdge" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = activeBlue;
		});

		select({ "List", "Tree", "TabberHead", "TableHead", "Dockbar", "Header", "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey117);
		});

		select({ "Window", "WindowFooter", "DockWindow", "Dockbox", "Tab", "TextEdit", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = vector ? black : grey52;
			i.m_border_colour = grey204;
			i.m_border_width = vec4(1.f);
		});

		select({ "Window", "Dockbox", "Node", "Popup", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_shadow = { 2, 2, 7, 2 };
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_shadow = { 0, 0, 0, 1, grey600 };
		});

		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey204);
			if(vector)
				i.m_border_width = vec4(1.f);
		});

		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = ui_window.find_image("handle_x");
			i.m_padding = vec4(2.f);
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_align = { Align::Right, Align::Right };
		});

		select({ "Toolbar", "Tooldock"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			colour(i, grey145);
		});

		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		select({ "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0.098f, 0.802f);
			i.m_text_colour = clearGreyText;
		});

		select({ "DropdownChoice", "MenuChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = transparent;
			i.m_border_colour = transparent;
		});

		select({ "TableRow", "TableRowOdd", "TableRowEven"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l); UNUSED(i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = grey312;
			i.m_border_width = vec4(1.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_border_colour = activeBlue;
			i.m_border_width = vec4(1.f);
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey117;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});

		ui::window_styles().close_button.m_skin.m_image = ui_window.find_image("close_15");

		for(auto name_style : g_styles)
			name_style.second->prepare();
	}

	void style_minimal(UiWindow& ui_window)
	{
		style_minimal(ui_window, false);
	}

	void style_vector(UiWindow& ui_window)
	{
		style_minimal(ui_window, true);
	}
}
