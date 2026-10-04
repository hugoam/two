//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	// a flat dark theme modelled on Visual Studio 2026: near black surfaces, lighter inputs, a purple accent for focus and selection
	// the icons it uses are in uisprites/vs, rasterized from the Visual Studio Image Library
	void style_vs_dark(UiWindow& ui_window)
	{
		style_minimal(ui_window);

		const Colour transparent = Colour(0.f, 0.f);
		const Colour app = Colour(0x1C / 255.f);			// application background, title bar, status bar
		const Colour base = Colour(0x26 / 255.f);			// windows, panels, toolbars
		const Colour editor = Colour(0x1E / 255.f);			// text editors
		const Colour sunken = Colour(0x18 / 255.f);			// lists, table heads
		const Colour raised = Colour(0x2E / 255.f);			// inputs, dropdowns
		const Colour outline = Colour(0x43 / 255.f);		// the edge of docks
		const Colour hover = Colour(0x3D / 255.f);
		const Colour pressed = Colour(0x4D / 255.f);
		const Colour border = Colour(0x3C / 255.f);
		const Colour selection = Colour(0x37 / 255.f, 0x37 / 255.f, 0x3D / 255.f);
		const Colour text = Colour(0xCC / 255.f);
		const Colour bright = Colour(0xF0 / 255.f);
		const Colour dim = Colour(0x80 / 255.f);
		const Colour accent = Colour(0x71 / 255.f, 0x60 / 255.f, 0xE8 / 255.f);

		auto image = [&](cstring name) { return ui_window.find_image(name); };

		select({ "Label", "Text", "Title", "Message", "Control", "Tooltip", "TextEdit", "TypeZone", "SliderDisplay", "RadioChoiceItem" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = text;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = dim;
		});

		// buttons are flat: no surface until hovered
		select({ "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "DockToggle", "RadioChoice", "Menu", "MenuChoice", "DropdownChoice", "TreeNodeHeader", "Element" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = text;
			i.m_background_colour = transparent;
			i.m_border_colour = transparent;
			i.m_border_width = vec4(0.f);
			i.m_corner_radius = vec4(3.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = hover;
		})
		.decline({ PRESSED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = pressed;
		})
		.decline({ ACTIVE, ACTIVE|HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = pressed;
			i.m_text_colour = bright;
		})
		.decline({ SELECTED, FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = selection;
			i.m_text_colour = bright;
		});

		select({ "Button", "WrapButton" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = raised;
			i.m_border_colour = border;
			i.m_border_width = vec4(1.f);
		});

		select({ "TreeNodeHeader", "Element", "MenuChoice", "DropdownChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(0.f);
		});

		// inputs are slightly raised fields, outlined in the accent when focused
		select({ "TypeIn", "Input<string>", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Slider", "Fillbar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = text;
			i.m_background_colour = raised;
			i.m_border_colour = border;
			i.m_border_width = vec4(1.f);
			i.m_corner_radius = vec4(3.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = hover;
		})
		.decline({ FOCUSED, SELECTED, ACTIVE, ACTIVE|HOVERED, PRESSED, PRESSED|HOVERED }, [&](InkStyle& i) {
			i.m_border_colour = accent;
		});

		select({ "Fillbar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image_colour = accent;
		});

		select({ "SliderKnob", "ScrollerKnob", "DragHandle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0x4F / 255.f);
			i.m_border_width = vec4(0.f);
			i.m_corner_radius = vec4(3.f);
		})
		.decline({ HOVERED, PRESSED, PRESSED|HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = Colour(0x6F / 255.f);
		});

		select({ "Scrollbar", "Scroller", "ScrollSheet" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = transparent;
		});

		// surfaces: the application behind, the panels docked on it, the editors in the panels
		select({ "Ui", "Dockspace", "Dockline", "Board", "Layout" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = app;
			i.m_border_colour = transparent;
			i.m_border_width = vec4(0.f);
			i.m_shadow = {};
		});

		select({ "Window", "WindowBody", "DockWindow", "Tab", "Tabber", "TabberHead", "TabberBody" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = base;
			i.m_border_colour = transparent;
			i.m_border_width = vec4(0.f);
			i.m_shadow = {};
		});

		select({ "Tabber" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_colour = outline;
			i.m_border_width = vec4(1.f);
		});

		select({ "TextEdit", "TypeZone" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = editor;
			i.m_border_colour = transparent;
			i.m_border_width = vec4(0.f);
		});

		select({ "Window", "Popup", "Modal", "ColourPopup", "Tooltip", "DropdownList", "MenuList", "SubMenuList", "Popdown" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = Colour(0x25 / 255.f);
			i.m_text_colour = text;
			i.m_border_colour = Colour(0x45 / 255.f);
			i.m_border_width = vec4(1.f);
			i.m_shadow = { 2, 2, 7, 2 };
		});

		select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = app;
			i.m_border_width = vec4(0.f);
		});

		select({ "Toolbar", "Tooldock", "Header", "Dockbar", "Docktabs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = base;
			i.m_border_width = vec4(0.f);
		});

		select({ "List", "TableHead", "ColumnHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = sunken;
		});

		select({ "WindowHeader", "WindowHeaderMovable", "WindowFooter" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = sunken;
			i.m_border_width = vec4(0.f);
		});

		// tabs: the text of the current tab is bright, the edge under the strip is the accent
		select({ "TabHeader", "Docktab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = dim;
			i.m_background_colour = transparent;
			i.m_border_width = vec4(0.f);
			i.m_corner_radius = vec4(0.f);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_text_colour = text;
			i.m_background_colour = hover;
		})
		.decline({ ACTIVE, ACTIVE|HOVERED, SELECTED }, [&](InkStyle& i) {
			i.m_text_colour = bright;
			i.m_background_colour = base;
		});

		select({ "TabberEdge" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = accent;
		});

		select({ "TableRow", "TableRowOdd", "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = base;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = hover;
			i.m_border_width = vec4(0.f);
		})
		.decline({ SELECTED }, [&](InkStyle& i) {
			i.m_background_colour = selection;
			i.m_border_width = vec4(0.f);
		});

		select({ "Separator", "TableSeparator", "Filler" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = border;
		});

		// icons
		select({ "ExpandboxToggle", "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = image("vs/glyph_right");
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = image("vs/glyph_down");
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_image = image("empty_15");
		});

		select({ "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_image = image("vs/glyph_down");
			i.m_background_colour = transparent;
		});

		select({ "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = raised;
			i.m_border_colour = border;
			i.m_border_width = vec4(1.f);
			i.m_corner_radius = vec4(2.f);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_image = image("vs/checkmark");
		});

		ui::window_styles().close_button.m_skin.m_image = image("vs/close");

		TextEdit::s_default_palette = TextEdit::VisualStudioPalette();

		for(auto name_style : g_styles)
			name_style.second->prepare();
	}
}
