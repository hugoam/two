//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/memory.h>
#include <stl/function.h>
#include <ui/Forward.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Layout.h>

namespace two
{
	using cstring = const char*;

	using LayoutDef = void(*)(Layout&);
	using InkStyleDef = void(*)(InkStyle&);
	using StyleDef = void(*)(Style&);

	export_ struct refl_ Subskin
	{
		attr_ InkStyle skin;
		attr_ WidgetState state;
	};

	export_ TWO_UI_EXPORT void register_styles(span<Style*> styles);

	export_ class refl_ TWO_UI_EXPORT Style
	{
	public:
		Style();
		Style(const string& name, Style* base, LayoutDef layout, InkStyleDef skin = nullptr, StyleDef style = nullptr);
		Style(const string& name, Style& base, LayoutDef layout, InkStyleDef skin = nullptr, StyleDef style = nullptr) : Style(name, &base, layout, skin, style) {}
		~Style();

		void prepare();

		InkStyle& state_skin(WidgetState state);
		InkStyle& decline_skin(WidgetState state, bool inherit = false);

		attr_ Style* m_base;

		attr_ string m_name;
		attr_ Layout m_layout;
		attr_ InkStyle m_skin;
		attr_ vector<Subskin> m_skins;
	};

	struct StyleSelector
	{
		using StyleDecl = function<void(Layout& l, InkStyle& i)>;
		using InkDecl = function<void(InkStyle& i)>;

		StyleSelector& declare(StyleDecl decl);
		StyleSelector& decline(span<uint32_t> states, InkDecl decl);
		StyleSelector& style(InkDecl decl);

		vector<Style*> styles;
	};

	StyleSelector select(span<string> styles);

	export_ TWO_UI_EXPORT func_ void layout_minimal(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_minimal(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_vector(UiWindow& ui_window);

	export_ TWO_UI_EXPORT func_ void style_blendish(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_blendish_light(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_blendish_dark(UiWindow& ui_window);

	export_ enum class ImguiStyle
	{
		Dark,
		Classic,
		Light
	};

	struct ImguiLook
	{
		float Alpha = 1.0f;                          // Global alpha applies to everything in ImGui
		vec2 WindowPadding = vec2(8, 8);             // Padding within a window
		float WindowRounding = 7.0f;                 // Radius of window corners rounding. Set to 0.0f to have rectangular windows
		float WindowBorderSize = 1.0f;               // Thickness of border around windows. Generally set to 0.0f or 1.0f. Other values not well tested.
		vec2 WindowMinSize = vec2(32, 32);           // Minimum window size
		vec2 WindowTitleAlign = vec2(0.0f, 0.5f);    // Alignment for title bar text
		float ChildRounding = 0.0f;                  // Radius of child window corners rounding. Set to 0.0f to have rectangular child windows
		float ChildBorderSize = 1.0f;                // Thickness of border around child windows. Generally set to 0.0f or 1.0f. Other values not well tested.
		float PopupRounding = 0.0f;                  // Radius of popup window corners rounding. Set to 0.0f to have rectangular child windows
		float PopupBorderSize = 1.0f;                // Thickness of border around popup or tooltip windows. Generally set to 0.0f or 1.0f. Other values not well tested.
		vec2 FramePadding = vec2(4, 3);              // Padding within a framed rectangle (used by most widgets)
		float FrameRounding = 0.0f;                  // Radius of frame corners rounding. Set to 0.0f to have rectangular frames (used by most widgets).
		float FrameBorderSize = 0.0f;                // Thickness of border around frames. Generally set to 0.0f or 1.0f. Other values not well tested.
		vec2 ItemSpacing = vec2(8, 4);               // Horizontal and vertical spacing between widgets/lines
		vec2 ItemInnerSpacing = vec2(4, 4);          // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
		vec2 TouchExtraPadding = vec2(0, 0);         // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
		float IndentSpacing = 21.0f;                 // Horizontal spacing when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
		float ColumnsMinSpacing = 6.0f;              // Minimum horizontal spacing between two columns
		float ScrollbarSize = 16.0f;                 // Width of the vertical scrollbar, Height of the horizontal scrollbar
		float ScrollbarRounding = 9.0f;              // Radius of grab corners rounding for scrollbar
		float GrabMinSize = 10.0f;                   // Minimum width/height of a grab box for slider/scrollbar
		float GrabRounding = 0.0f;                   // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
		float TabRounding = 4.0f;                    // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
		float TabBorderSize = 0.0f;                  // Thickness of border around tabs.
		vec2 ButtonTextAlign = vec2(0.5f, 0.5f);     // Alignment of button text when button is larger than text.
		vec2 SelectableTextAlign = vec2(0.0f, 0.0f); // Alignment of selectable text when button is larger than text.
		vec2 DisplayWindowPadding = vec2(19, 19);    // Window position are clamped to be visible within the display area by at least this amount. Only applies to regular windows.
		vec2 DisplaySafeAreaPadding = vec2(3, 3);    // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
		float MouseCursorScale = 1.0f;               // Scale software rendered mouse cursor (when io.MouseDrawCursor is enabled). May be removed later.
		float AntiAliasedLines = true;               // Enable anti-aliasing on lines/borders. Disable if you are really short on CPU/GPU.
		float AntiAliasedFill = true;                // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
		float CurveTessellationTol = 1.25f;          // Tessellation tolerance when using PathBezierCurveTo() without a specific number of segments. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
	};

	struct ImguiColours
	{
		Colour Text;
		Colour TextDisabled;
		Colour WindowBg;
		Colour ChildBg;
		Colour PopupBg;
		Colour Border;
		Colour BorderShadow;
		Colour FrameBg;
		Colour FrameBgHovered;
		Colour FrameBgActive;
		Colour TitleBg;
		Colour TitleBgActive;
		Colour TitleBgCollapsed;
		Colour MenuBarBg;
		Colour ScrollbarBg;
		Colour ScrollbarGrab;
		Colour ScrollbarGrabHovered;
		Colour ScrollbarGrabActive;
		Colour CheckMark;
		Colour SliderGrab;
		Colour SliderGrabActive;
		Colour Button;
		Colour ButtonHovered;
		Colour ButtonActive;
		Colour Header;
		Colour HeaderHovered;
		Colour HeaderActive;
		Colour Separator;
		Colour SeparatorHovered;
		Colour SeparatorActive;
		Colour ResizeGrip;
		Colour ResizeGripHovered;
		Colour ResizeGripActive;
		Colour Tab;
		Colour TabHovered;
		Colour TabActive;
		Colour TabUnfocused;
		Colour TabUnfocusedActive;
		Colour PlotLines;
		Colour PlotLinesHovered;
		Colour PlotHistogram;
		Colour PlotHistogramHovered;
		Colour TextSelectedBg;
		Colour DragDropTarget;
		Colour NavHighlight;
		Colour NavWindowingHighlight;
		Colour NavWindowingDimBg;
		Colour ModalWindowDimBg;
	};

	export_ TWO_UI_EXPORT func_ void style_imgui_dark(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_imgui_light(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_imgui_classic(UiWindow& ui_window);

	export_ TWO_UI_EXPORT void style_imgui(UiWindow& ui_window, ImguiStyle style = ImguiStyle::Dark);
}
