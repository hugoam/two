//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module two.ui;
#else
#include <stl/hash_base.hpp>
#include <math/Vec.hpp>
#include <math/Interp.h>
#include <ui/Style/Styles.h>
#include <ui/UiWindow.h>
#include <ui/Widget.h>
#include <ui/Button.h>
#include <ui/Container.h>
#endif

#include <cstdio>

namespace two
{
	void layout_imgui(UiWindow& ui_window, const ImguiLook& look)
	{
		UNUSED(ui_window);

		select({ "Button", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoiceItem", "TypeIn", "Input<string>" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_padding = vec4(look.FramePadding, look.FramePadding);
		});
		
		select({ "DropdownHead", "DropdownChoice", "MenuChoice" }) // "DropdownInput", "DropdownInputCompact", "TypedownInput", 
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_padding = vec4(look.FramePadding, look.FramePadding);
		});

		select({ "Header", "ExpandboxHeader", "WindowHeader", "WindowHeaderMovable", "Scrollbar", "NodePlug" }) // , "Menu"
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.FramePadding, look.FramePadding);
		});
		
		select({ "Slider" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.FramePadding - 1.f, look.FramePadding - 1.f);
		});

		select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.FramePadding.x, 0.f, look.FramePadding.x, 0.f);
		});

		select({ "TreeNodeBody", "IndentBlock" }) // , "ExpandboxBody"
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.IndentSpacing, look.FramePadding.y, look.FramePadding);
		});

		select({ "Row", "ExpandboxHeader", "TreeNodeHeader", "WrapButton", "MultiButton" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(look.ItemSpacing.x, 0.f);
		});
		
		select({ "ExpandboxBody", "TreeNodeBody", "WindowBody", "Table", "Tab", "Dockbar", "Toolbar", "Header", "TabberHead", "ScrollSurface", "IndentBlock" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing = vec2(look.ItemSpacing);
		});
		
		select({ "TabberHead", "NumberInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_spacing.x = look.ItemInnerSpacing.x;
		});

		select({ "ExpandboxBody", "Dockbar", "Toolbar", "Header", "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			//l.m_padding = vec4(look.ItemSpacing, look.ItemSpacing);
			l.m_padding = vec4(look.FramePadding, look.FramePadding);
		});
		
		select({ "Header", "Modal", "Popup", "ColourPopup", "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList", "ScrollSurface" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(look.WindowPadding, look.WindowPadding);
		});

		select({ "DropdownList", "MenuList", "SubMenuList" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			const vec2 padding = vec2(look.FramePadding.x, look.WindowPadding.y);
			l.m_padding = vec4(padding, padding);
		});
		
		select({ "NodePlugs" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_padding = vec4(-5.f - look.FramePadding.x, 0.f, -5.f - look.FramePadding.x, 0.f);
		});
	}

	void style_imgui(UiWindow& ui_window, const ImguiLook& look, const ImguiColours& style)
	{
		//layout_minimal(ui_window);
		layout_imgui(ui_window, look);

		const Colour none = Colour(0.f, 0.f);

		// Render an arrow aimed to be aligned with text (offset is a position in the same space text would be positioned). To e.g. denote expanded/collapsed state
		static auto render_arrow = [](Vg& vg, vec2 offset, SignedAxis dir, float fontsize, float scale, Colour colour)
		{
			const float h = fontsize * 1.00f;
			float r = h * 0.40f * scale;
			vec2 center = offset + vec2(h * 0.50f, h * 0.50f * scale);

			vec2 a, b, c;
			switch(dir)
			{
			case SignedAxis::PlusY:
			case SignedAxis::MinusY:
				if(dir == SignedAxis::PlusY) r = -r;
				a = vec2(+0.000f, +0.750f) * r;
				b = vec2(-0.866f, -0.750f) * r;
				c = vec2(+0.866f, -0.750f) * r;
				break;
			case SignedAxis::PlusX:
			case SignedAxis::MinusX:
				if(dir == SignedAxis::MinusX) r = -r;
				a = vec2(+0.750f, +0.000f) * r;
				b = vec2(-0.750f, +0.866f) * r;
				c = vec2(-0.750f, -0.866f) * r;
				break;
			default:
				break;
			}

			vg.begin_path();
			vg.move_to(center + a);
			vg.line_to(center + b);
			vg.line_to(center + c);
			vg.close_path();
			vg.fill(Paint(colour));
		};

		static auto render_bullet = [](Vg& vg, vec2 pos, float fontsize, Colour colour)
		{
			vg.path_circle(pos, fontsize * 0.20f);
			vg.fill(Paint(colour));
		};

		static auto render_checkmark = [](Vg& vg, vec2 pos, Colour colour, float sz)
		{
			float thickness = max(sz / 5.0f, 1.0f);
			sz -= thickness * 0.5f;
			pos += vec2(thickness * 0.25f);

			float third = sz / 3.0f;
			float bx = pos.x + third;
			float by = pos.y + sz - third * 0.5f;

			vg.begin_path();
			vg.move_to(vec2(bx - third, by - third));
			//vg.line_to(vec2(bx - third, by - third));
			vg.line_to(vec2(bx, by));
			vg.line_to(vec2(bx + third * 2, by - third * 2));
			vg.stroke(Paint(colour, thickness));
		};
		
		select({ "Label", "Text", "Title", "Message", "Control", "Tooltip", "TextEdit", "TypeLabel", "TypeZone", "SliderDisplay", "RadioChoiceItem",
				 "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "TabHeader", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_text_colour = style.Text;
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_text_colour = style.TextDisabled;
		});
		
		select({ "Separator" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.Separator;
		});

		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "DockToggle", "RadioChoice", "DropdownChoice", "SliderKnob", "ScrollerKnob", "DragHandle", "DropdownInput", "DropdownInputCompact", "TypedownInput", "Menu", "TypeIn", "Input<string>" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_border_width = vec4(look.FrameBorderSize);
			i.m_corner_radius = vec4(look.FrameRounding);
		});
		
		//"Menu",
		select({ "Element", "Button", "WrapButton", "MultiButton", "Toggle", "ToolButton", "DockToggle", "SliderKnob", "DragHandle", "DropdownToggle" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.Button;
			i.m_border_colour = style.Border;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.ButtonHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.ButtonActive;
		});
		
		select({ "Checkbox", "TypeIn", "Input<string>", "Slider", "Fillbar", "DropdownInput", "DropdownInputCompact", "TypedownInput" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.FrameBg;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.FrameBgHovered;
		});

		select({ "ExpandboxHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.Header;
			i.m_border_colour = style.Border;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.HeaderHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.HeaderActive;
		});

		select({ "TreeNodeHeader", "RadioChoice", "DropdownChoice", "Menu", "MenuChoice" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l); UNUSED(i);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.HeaderHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.Header;
		});

		select({ "TabberEdge" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_background_colour = style.TabActive;
			l.m_size = vec2(2.f);
		});

		select({ "TabHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.Tab;
			i.m_border_colour = style.Border;
			i.m_corner_radius = vec4(look.TabRounding, look.TabRounding, 0.f, 0.f);
			i.m_border_width = vec4(look.TabBorderSize);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.TabHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.TabActive;
		});

		Style& dropdown_toggle = ui::dropdown_styles().toggle;

		dropdown_toggle.m_layout.m_size = vec2(13.f + 6.f);
		dropdown_toggle.m_skin.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg)
		{
			draw_frame(vg, frame, rect);
			render_arrow(vg, rect.pos + vec2(3.f), SignedAxis::MinusY, 13.f, 1.f, Colour(1.f));
		};
		
		for(Subskin& subskin : dropdown_toggle.m_skins)
		{
			subskin.skin.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg)
			{
				draw_frame(vg, frame, rect);
				render_arrow(vg, rect.pos + vec2(3.f), SignedAxis::MinusY, 13.f, 1.f, Colour(1.f));
			};
		}

		Style& treenode_header = ui::treenode_styles().header;

		select({ "ExpandboxToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_arrow(vg, rect.pos, SignedAxis::PlusX, 13.f, 1.f, Colour(1.f)); };
			l.m_size = vec2(13.f);
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_arrow(vg, rect.pos, SignedAxis::MinusY, 13.f, 1.f, Colour(1.f)); };
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) {};
		});
		
		select({ "TreeNodeNoToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			l.m_size = vec2(13.f) * 0.7f;
		});

		select({ "TreeNodeToggle" })
		.declare([&](Layout& l, InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_arrow(vg, rect.pos, SignedAxis::PlusX, 13.f, 0.7f, Colour(1.f)); };
			l.m_size = vec2(13.f) * 0.7f;
		})
		.decline({ ACTIVE }, [&](InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_arrow(vg, rect.pos, SignedAxis::MinusY, 13.f, 0.7f, Colour(1.f)); };
		})
		.decline({ DISABLED }, [&](InkStyle& i) {
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) {};
		});
#if 0
		select({ "Element", "TreeNodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = grey86;
		});

#endif
		
		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.SliderGrab;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.SliderGrabActive;
		});
		
		select({ "SliderKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(i);
			l.m_size = vec2(8, 15);
		});

		select({ "Scrollbar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.ScrollbarBg;
		});

		select({ "ScrollerKnob" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//i = styles().button.m_skin;
			i.m_background_colour = style.ScrollbarGrab;
			i.m_corner_radius = vec4(look.ScrollbarRounding);
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.ScrollbarGrabHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.ScrollbarGrabActive;
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
		
		select({  "Checkbox" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			l.m_size = vec2(13.f + 6.f);
		});
		
		static Colour Checkmark = style.CheckMark;
		select({  "Checkmark" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_custom_draw = [](const Frame& frame, const vec4& rect, Vg& vg) { render_checkmark(vg, rect.pos + vec2(3.f), Checkmark, 13.f); };
		});
		
		select({ "Menubar" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.MenuBarBg;
		});

		select({ "Popup", "Modal" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.PopupBg;
		});
		
		select({  "Tooltip", "Popdown", "DropdownList", "MenuList", "SubMenuList"  })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//i.m_background_colour = style.PopupBg;
			i.m_background_colour = style.WindowBg;
			i.m_border_colour = style.Border;
			i.m_border_width = vec4(1.f);
		});


		select({ "Window", "DockWindow", "Dockbox", "Node", "Section", "Popup", "Modal", "ColourPopup" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			//i.m_background_colour = grey52;
			i.m_border_colour = style.Border;
			i.m_border_width = vec4(1.f);
		});

		select({ "Window", "DockWindow", "Dockbox", "Node", "ColourPopup", "Header", "Tab" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.WindowBg;
		});

		select({ "Window", "Dockbox", "Node" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(look.WindowRounding);
		});
		
		select({ "WindowHeader", "WindowHeaderMovable" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_corner_radius = vec4(look.WindowRounding, look.WindowRounding, 0.f, 0.f);
		});
		
		select({ "WindowHeader", "WindowHeaderMovable", "NodeHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.TitleBg;
		})
		.decline({ ACTIVE, FOCUSED }, [&](InkStyle& i) {
			i.m_background_colour = style.TitleBgActive;
		});

		
		select({  "WindowSizer", "WindowSizerLeft", "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.ResizeGrip;
		})
		.decline({ HOVERED }, [&](InkStyle& i) {
			i.m_background_colour = style.ResizeGripHovered;
		})
		.decline({ ACTIVE, SELECTED, PRESSED, FOCUSED, ACTIVE|HOVERED, PRESSED|HOVERED, ACTIVE|PRESSED }, [&](InkStyle& i) {
			i.m_background_colour = style.ResizeGripActive;
		});

		select({ "WindowSizerRight" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_align = { Align::Right, Align::Right };
		});
		
		select({ "ColumnHeader" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.FrameBg;
		});

		select({ "TableRowOdd" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = none;
		});

		select({ "TableRowEven" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = style.FrameBg;
		});
#if 0
		select({ "Canvas" })
		.declare([&](Layout& l, InkStyle& i) { UNUSED(l);
			i.m_background_colour = black;
		});
#endif

		for(auto name_style : g_styles)
		{
			Style& s = *name_style.second;

			s.m_skin.m_text_font = "proggy";
			s.m_skin.m_text_size = 13.f;
			s.m_skin.m_text_colour = style.Text;

			for(Subskin& subskin : s.m_skins)
			{
				subskin.skin.m_text_font = "proggy";
				subskin.skin.m_text_size = 13.f;
				s.m_skin.m_text_colour = style.Text;
			}

			s.prepare();
		}
	}

	void style_imgui_dark(UiWindow& ui_window)
	{
		ImguiLook look;
		ImguiColours dark;

		dark.Text = Colour(1.00f, 1.00f, 1.00f, 1.00f);
		dark.TextDisabled = Colour(0.50f, 0.50f, 0.50f, 1.00f);
		dark.WindowBg = Colour(0.06f, 0.06f, 0.06f, 0.94f);
		dark.ChildBg = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		dark.PopupBg = Colour(0.08f, 0.08f, 0.08f, 0.94f);
		dark.Border = Colour(0.43f, 0.43f, 0.50f, 0.50f);
		dark.BorderShadow = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		dark.FrameBg = Colour(0.16f, 0.29f, 0.48f, 0.54f);
		dark.FrameBgHovered = Colour(0.26f, 0.59f, 0.98f, 0.40f);
		dark.FrameBgActive = Colour(0.26f, 0.59f, 0.98f, 0.67f);
		dark.TitleBg = Colour(0.04f, 0.04f, 0.04f, 1.00f);
		dark.TitleBgActive = Colour(0.16f, 0.29f, 0.48f, 1.00f);
		dark.TitleBgCollapsed = Colour(0.00f, 0.00f, 0.00f, 0.51f);
		dark.MenuBarBg = Colour(0.14f, 0.14f, 0.14f, 1.00f);
		dark.ScrollbarBg = Colour(0.02f, 0.02f, 0.02f, 0.53f);
		dark.ScrollbarGrab = Colour(0.31f, 0.31f, 0.31f, 1.00f);
		dark.ScrollbarGrabHovered = Colour(0.41f, 0.41f, 0.41f, 1.00f);
		dark.ScrollbarGrabActive = Colour(0.51f, 0.51f, 0.51f, 1.00f);
		dark.CheckMark = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.SliderGrab = Colour(0.24f, 0.52f, 0.88f, 1.00f);
		dark.SliderGrabActive = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.Button = Colour(0.26f, 0.59f, 0.98f, 0.40f);
		dark.ButtonHovered = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.ButtonActive = Colour(0.06f, 0.53f, 0.98f, 1.00f);
		dark.Header = Colour(0.26f, 0.59f, 0.98f, 0.31f);
		dark.HeaderHovered = Colour(0.26f, 0.59f, 0.98f, 0.80f);
		dark.HeaderActive = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.Separator = dark.Border;
		dark.SeparatorHovered = Colour(0.10f, 0.40f, 0.75f, 0.78f);
		dark.SeparatorActive = Colour(0.10f, 0.40f, 0.75f, 1.00f);
		dark.ResizeGrip = Colour(0.26f, 0.59f, 0.98f, 0.25f);
		dark.ResizeGripHovered = Colour(0.26f, 0.59f, 0.98f, 0.67f);
		dark.ResizeGripActive = Colour(0.26f, 0.59f, 0.98f, 0.95f);
		dark.Tab = lerp(dark.Header, dark.TitleBgActive, 0.80f);
		dark.TabHovered = dark.HeaderHovered;
		dark.TabActive = lerp(dark.HeaderActive, dark.TitleBgActive, 0.60f);
		dark.TabUnfocused = lerp(dark.Tab, dark.TitleBg, 0.80f);
		dark.TabUnfocusedActive = lerp(dark.TabActive, dark.TitleBg, 0.40f);
		dark.PlotLines = Colour(0.61f, 0.61f, 0.61f, 1.00f);
		dark.PlotLinesHovered = Colour(1.00f, 0.43f, 0.35f, 1.00f);
		dark.PlotHistogram = Colour(0.90f, 0.70f, 0.00f, 1.00f);
		dark.PlotHistogramHovered = Colour(1.00f, 0.60f, 0.00f, 1.00f);
		dark.TextSelectedBg = Colour(0.26f, 0.59f, 0.98f, 0.35f);
		dark.DragDropTarget = Colour(1.00f, 1.00f, 0.00f, 0.90f);
		dark.NavHighlight = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		dark.NavWindowingHighlight = Colour(1.00f, 1.00f, 1.00f, 0.70f);
		dark.NavWindowingDimBg = Colour(0.80f, 0.80f, 0.80f, 0.20f);
		dark.ModalWindowDimBg = Colour(0.80f, 0.80f, 0.80f, 0.35f);

		style_imgui(ui_window, look, dark);
	}

	void style_imgui_classic(UiWindow& ui_window)
	{
		ImguiLook look;
		ImguiColours classic;

		classic.Text = Colour(0.90f, 0.90f, 0.90f, 1.00f);
		classic.TextDisabled = Colour(0.60f, 0.60f, 0.60f, 1.00f);
		classic.WindowBg = Colour(0.00f, 0.00f, 0.00f, 0.70f);
		classic.ChildBg = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		classic.PopupBg = Colour(0.11f, 0.11f, 0.14f, 0.92f);
		classic.Border = Colour(0.50f, 0.50f, 0.50f, 0.50f);
		classic.BorderShadow = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		classic.FrameBg = Colour(0.43f, 0.43f, 0.43f, 0.39f);
		classic.FrameBgHovered = Colour(0.47f, 0.47f, 0.69f, 0.40f);
		classic.FrameBgActive = Colour(0.42f, 0.41f, 0.64f, 0.69f);
		classic.TitleBg = Colour(0.27f, 0.27f, 0.54f, 0.83f);
		classic.TitleBgActive = Colour(0.32f, 0.32f, 0.63f, 0.87f);
		classic.TitleBgCollapsed = Colour(0.40f, 0.40f, 0.80f, 0.20f);
		classic.MenuBarBg = Colour(0.40f, 0.40f, 0.55f, 0.80f);
		classic.ScrollbarBg = Colour(0.20f, 0.25f, 0.30f, 0.60f);
		classic.ScrollbarGrab = Colour(0.40f, 0.40f, 0.80f, 0.30f);
		classic.ScrollbarGrabHovered = Colour(0.40f, 0.40f, 0.80f, 0.40f);
		classic.ScrollbarGrabActive = Colour(0.41f, 0.39f, 0.80f, 0.60f);
		classic.CheckMark = Colour(0.90f, 0.90f, 0.90f, 0.50f);
		classic.SliderGrab = Colour(1.00f, 1.00f, 1.00f, 0.30f);
		classic.SliderGrabActive = Colour(0.41f, 0.39f, 0.80f, 0.60f);
		classic.Button = Colour(0.35f, 0.40f, 0.61f, 0.62f);
		classic.ButtonHovered = Colour(0.40f, 0.48f, 0.71f, 0.79f);
		classic.ButtonActive = Colour(0.46f, 0.54f, 0.80f, 1.00f);
		classic.Header = Colour(0.40f, 0.40f, 0.90f, 0.45f);
		classic.HeaderHovered = Colour(0.45f, 0.45f, 0.90f, 0.80f);
		classic.HeaderActive = Colour(0.53f, 0.53f, 0.87f, 0.80f);
		classic.Separator = Colour(0.50f, 0.50f, 0.50f, 1.00f);
		classic.SeparatorHovered = Colour(0.60f, 0.60f, 0.70f, 1.00f);
		classic.SeparatorActive = Colour(0.70f, 0.70f, 0.90f, 1.00f);
		classic.ResizeGrip = Colour(1.00f, 1.00f, 1.00f, 0.16f);
		classic.ResizeGripHovered = Colour(0.78f, 0.82f, 1.00f, 0.60f);
		classic.ResizeGripActive = Colour(0.78f, 0.82f, 1.00f, 0.90f);
		classic.Tab = lerp(classic.Header, classic.TitleBgActive, 0.80f);
		classic.TabHovered = classic.HeaderHovered;
		classic.TabActive = lerp(classic.HeaderActive, classic.TitleBgActive, 0.60f);
		classic.TabUnfocused = lerp(classic.Tab, classic.TitleBg, 0.80f);
		classic.TabUnfocusedActive = lerp(classic.TabActive, classic.TitleBg, 0.40f);
		classic.PlotLines = Colour(1.00f, 1.00f, 1.00f, 1.00f);
		classic.PlotLinesHovered = Colour(0.90f, 0.70f, 0.00f, 1.00f);
		classic.PlotHistogram = Colour(0.90f, 0.70f, 0.00f, 1.00f);
		classic.PlotHistogramHovered = Colour(1.00f, 0.60f, 0.00f, 1.00f);
		classic.TextSelectedBg = Colour(0.00f, 0.00f, 1.00f, 0.35f);
		classic.DragDropTarget = Colour(1.00f, 1.00f, 0.00f, 0.90f);
		classic.NavHighlight = classic.HeaderHovered;
		classic.NavWindowingHighlight = Colour(1.00f, 1.00f, 1.00f, 0.70f);
		classic.NavWindowingDimBg = Colour(0.80f, 0.80f, 0.80f, 0.20f);
		classic.ModalWindowDimBg = Colour(0.20f, 0.20f, 0.20f, 0.35f);

		style_imgui(ui_window, look, classic);
	}

	void style_imgui_light(UiWindow& ui_window)
	{
		ImguiLook look;
		ImguiColours light;

		// Those light colors are better suited with a thicker font than the default one + FrameBorder

		light.Text = Colour(0.00f, 0.00f, 0.00f, 1.00f);
		light.TextDisabled = Colour(0.60f, 0.60f, 0.60f, 1.00f);
		light.WindowBg = Colour(0.94f, 0.94f, 0.94f, 1.00f);
		light.ChildBg = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		light.PopupBg = Colour(1.00f, 1.00f, 1.00f, 0.98f);
		light.Border = Colour(0.00f, 0.00f, 0.00f, 0.30f);
		light.BorderShadow = Colour(0.00f, 0.00f, 0.00f, 0.00f);
		light.FrameBg = Colour(1.00f, 1.00f, 1.00f, 1.00f);
		light.FrameBgHovered = Colour(0.26f, 0.59f, 0.98f, 0.40f);
		light.FrameBgActive = Colour(0.26f, 0.59f, 0.98f, 0.67f);
		light.TitleBg = Colour(0.96f, 0.96f, 0.96f, 1.00f);
		light.TitleBgActive = Colour(0.82f, 0.82f, 0.82f, 1.00f);
		light.TitleBgCollapsed = Colour(1.00f, 1.00f, 1.00f, 0.51f);
		light.MenuBarBg = Colour(0.86f, 0.86f, 0.86f, 1.00f);
		light.ScrollbarBg = Colour(0.98f, 0.98f, 0.98f, 0.53f);
		light.ScrollbarGrab = Colour(0.69f, 0.69f, 0.69f, 0.80f);
		light.ScrollbarGrabHovered = Colour(0.49f, 0.49f, 0.49f, 0.80f);
		light.ScrollbarGrabActive = Colour(0.49f, 0.49f, 0.49f, 1.00f);
		light.CheckMark = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		light.SliderGrab = Colour(0.26f, 0.59f, 0.98f, 0.78f);
		light.SliderGrabActive = Colour(0.46f, 0.54f, 0.80f, 0.60f);
		light.Button = Colour(0.26f, 0.59f, 0.98f, 0.40f);
		light.ButtonHovered = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		light.ButtonActive = Colour(0.06f, 0.53f, 0.98f, 1.00f);
		light.Header = Colour(0.26f, 0.59f, 0.98f, 0.31f);
		light.HeaderHovered = Colour(0.26f, 0.59f, 0.98f, 0.80f);
		light.HeaderActive = Colour(0.26f, 0.59f, 0.98f, 1.00f);
		light.Separator = Colour(0.39f, 0.39f, 0.39f, 1.00f);
		light.SeparatorHovered = Colour(0.14f, 0.44f, 0.80f, 0.78f);
		light.SeparatorActive = Colour(0.14f, 0.44f, 0.80f, 1.00f);
		light.ResizeGrip = Colour(0.80f, 0.80f, 0.80f, 0.56f);
		light.ResizeGripHovered = Colour(0.26f, 0.59f, 0.98f, 0.67f);
		light.ResizeGripActive = Colour(0.26f, 0.59f, 0.98f, 0.95f);
		light.Tab = lerp(light.Header, light.TitleBgActive, 0.90f);
		light.TabHovered = light.HeaderHovered;
		light.TabActive = lerp(light.HeaderActive, light.TitleBgActive, 0.60f);
		light.TabUnfocused = lerp(light.Tab, light.TitleBg, 0.80f);
		light.TabUnfocusedActive = lerp(light.TabActive, light.TitleBg, 0.40f);
		light.PlotLines = Colour(0.39f, 0.39f, 0.39f, 1.00f);
		light.PlotLinesHovered = Colour(1.00f, 0.43f, 0.35f, 1.00f);
		light.PlotHistogram = Colour(0.90f, 0.70f, 0.00f, 1.00f);
		light.PlotHistogramHovered = Colour(1.00f, 0.45f, 0.00f, 1.00f);
		light.TextSelectedBg = Colour(0.26f, 0.59f, 0.98f, 0.35f);
		light.DragDropTarget = Colour(0.26f, 0.59f, 0.98f, 0.95f);
		light.NavHighlight = light.HeaderHovered;
		light.NavWindowingHighlight = Colour(0.70f, 0.70f, 0.70f, 0.70f);
		light.NavWindowingDimBg = Colour(0.20f, 0.20f, 0.20f, 0.20f);
		light.ModalWindowDimBg = Colour(0.20f, 0.20f, 0.20f, 0.35f);

		style_imgui(ui_window, look, light);
	}

	void style_imgui(UiWindow& ui_window, ImguiStyle style)
	{
		if(style == ImguiStyle::Dark)
			style_imgui_dark(ui_window);
		else if(style == ImguiStyle::Light)
			style_imgui_light(ui_window);
		else if(style == ImguiStyle::Classic)
			style_imgui_classic(ui_window);
	}
}
