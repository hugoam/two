//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

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

	export_ TWO_UI_EXPORT void style_vs_dark(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_blendish_light(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_blendish_dark(UiWindow& ui_window);

	export_ enum class ImguiStyle
	{
		Dark,
		Classic,
		Light
	};

	// The sizes of the dear imgui style (ImGuiStyle), and their defaults, as of dear imgui v1.93
	export_ struct ImguiLook
	{
		// Font scaling
		float FontSizeBase = 13.0f;                     // Current base font size before external global factors are applied.
		float FontScaleMain = 1.0f;                     // Main global scale factor.
		float FontScaleDpi = 1.0f;                      // Additional global scale factor from viewport/monitor contents scale.

		float Alpha = 1.0f;                             // Global alpha applies to everything in Dear ImGui.
		float DisabledAlpha = 0.60f;                    // Additional alpha multiplier applied by BeginDisabled(). Multiply over current value of Alpha.
		vec2 WindowPadding = vec2(8, 8);                // Padding within a window.
		float WindowRounding = 0.0f;                    // Radius of window corners rounding. Set to 0.0f to have rectangular windows.
		float WindowBorderSize = 1.0f;                  // Thickness of border around windows. Generally set to 0.0f or 1.0f.
		float WindowBorderHoverPadding = 4.0f;          // Hit-testing extent outside/inside resizing border.
		vec2 WindowMinSize = vec2(32, 32);              // Minimum window size.
		vec2 WindowTitleAlign = vec2(0.0f, 0.5f);       // Alignment for title bar text.
		int WindowMenuButtonPosition = 0;               // Side of the collapsing/docking button in the title bar (-1: None, 0: Left, 1: Right).
		float ChildRounding = 0.0f;                     // Radius of child window corners rounding.
		float ChildBorderSize = 1.0f;                   // Thickness of border around child windows.
		float PopupRounding = 0.0f;                     // Radius of popup window corners rounding.
		float PopupBorderSize = 1.0f;                   // Thickness of border around popup/tooltip windows.
		vec2 FramePadding = vec2(4, 3);                 // Padding within a framed rectangle (used by most widgets).
		float FrameRounding = 0.0f;                     // Radius of frame corners rounding (used by most widgets).
		float FrameBorderSize = 0.0f;                   // Thickness of border around frames.
		vec2 ItemSpacing = vec2(8, 4);                  // Horizontal and vertical spacing between widgets/lines.
		vec2 ItemInnerSpacing = vec2(4, 4);             // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label).
		vec2 CellPadding = vec2(4, 2);                  // Padding within a table cell.
		vec2 TouchExtraPadding = vec2(0, 0);            // Expand reactive bounding box for touch-based system where touch position is not accurate enough.
		float IndentSpacing = 21.0f;                    // Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
		float ColumnsMinSpacing = 6.0f;                 // Minimum horizontal spacing between two columns.
		float ScrollbarSize = 14.0f;                    // Width of the vertical scrollbar, Height of the horizontal scrollbar.
		float ScrollbarRounding = 9.0f;                 // Radius of grab corners for scrollbar.
		float ScrollbarPadding = 2.0f;                  // Padding of scrollbar grab within its frame (same for both axes).
		float GrabMinSize = 12.0f;                      // Minimum width/height of a grab box for slider/scrollbar.
		float GrabRounding = 0.0f;                      // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
		float LogSliderDeadzone = 4.0f;                 // The size in pixels of the dead-zone around zero on logarithmic sliders that cross zero.
		float ImageRounding = 0.0f;                     // Rounding of Image() calls.
		float ImageBorderSize = 0.0f;                   // Thickness of border around Image() calls.
		float TabRounding = 5.0f;                       // Radius of upper corners of a tab. Set to 0.0f to have rectangular tabs.
		float TabBorderSize = 0.0f;                     // Thickness of border around tabs.
		float TabMinWidthBase = 1.0f;                   // Minimum tab width, to make tabs larger than their contents.
		float TabMinWidthShrink = 80.0f;                // Minimum tab width after shrinking.
		float TabCloseButtonMinWidthSelected = -1.0f;   // -1: always visible. 0.0f: visible when hovered. >0.0f: visible when hovered if minimum width.
		float TabCloseButtonMinWidthUnselected = 0.0f;  // -1: always visible. 0.0f: visible when hovered. >0.0f: visible when hovered if minimum width.
		float TabBarBorderSize = 1.0f;                  // Thickness of tab-bar separator, which takes on the tab active color to denote focus.
		float TabBarOverlineSize = 1.0f;                // Thickness of tab-bar overline, which highlights the selected tab-bar.
		float TableAngledHeadersAngle = 35.0f * (3.14159265f / 180.0f); // Angle of angled headers (supported values range from -50.0f degrees to +50.0f degrees).
		vec2 TableAngledHeadersTextAlign = vec2(0.5f, 0.0f); // Alignment of angled headers within the cell
		int TreeLinesFlags = 0;                         // Default way to draw lines connecting TreeNode hierarchy (ImGuiTreeNodeFlags_DrawLinesXXX).
		float TreeLinesSize = 1.0f;                     // Thickness of outlines when using ImGuiTreeNodeFlags_DrawLines.
		float TreeLinesRounding = 0.0f;                 // Radius of lines connecting child nodes to the vertical line.
		float MenuItemRounding = 0.0f;                  // Radius of MenuItem, BeginMenu rounding.
		float SelectableRounding = 0.0f;                // Radius of Selectable rounding.
		float DragDropTargetRounding = 0.0f;            // Radius of the drag and drop target frame.
		float DragDropTargetBorderSize = 2.0f;          // Thickness of the drag and drop target border.
		float DragDropTargetPadding = 3.0f;             // Size to expand the drag and drop target from actual target item size.
		float ColorMarkerSize = 3.0f;                   // Size of R/G/B/A color markers for ColorEdit4() and for Drags/Sliders.
		int ColorButtonPosition = 1;                    // Side of the color button in the ColorEdit4 widget (0: left, 1: right).
		vec2 ButtonTextAlign = vec2(0.5f, 0.5f);        // Alignment of button text when button is larger than text.
		vec2 SelectableTextAlign = vec2(0.0f, 0.0f);    // Alignment of selectable text.
		float InputTextCursorSize = 1.0f;               // Thickness of cursor/caret in InputText().
		float SeparatorSize = 1.0f;                     // Thickness of border in Separator().
		float SeparatorTextBorderSize = 3.0f;           // Thickness of border in SeparatorText()
		vec2 SeparatorTextAlign = vec2(0.0f, 0.5f);     // Alignment of text within the separator.
		vec2 SeparatorTextPadding = vec2(20.0f, 3.f);   // Horizontal offset of text from each edge of the separator + spacing on other axis.
		vec2 DisplayWindowPadding = vec2(19, 19);       // Apply to regular windows: amount which we enforce to keep visible when moving near edges of your screen.
		vec2 DisplaySafeAreaPadding = vec2(3, 3);       // Apply to every windows, menus, popups, tooltips: amount where we avoid displaying contents.
		float MouseCursorScale = 1.0f;                  // Scale software rendered mouse cursor.

		// Rendering & Tessellation
		bool AntiAliasedLines = true;                   // Enable anti-aliased lines/borders.
		bool AntiAliasedLinesUseTex = true;             // Enable anti-aliased lines/borders using textures where possible.
		bool AntiAliasedFill = true;                    // Enable anti-aliased edges around filled shapes.
		float CurveTessellationMaxError = 1.12f;        // Maximum error (in pixels) when using PathBezierCurveTo() without a specific number of segments.
		float CircleTessellationMaxError = 0.30f;       // Maximum error (in pixels) allowed when using AddCircle()/AddCircleFilled().

		// Behaviors
		float HoverStationaryDelay = 0.15f;             // Delay for IsItemHovered(ImGuiHoveredFlags_Stationary).
		float HoverDelayShort = 0.15f;                  // Delay for IsItemHovered(ImGuiHoveredFlags_DelayShort).
		float HoverDelayNormal = 0.40f;                 // Delay for IsItemHovered(ImGuiHoveredFlags_DelayNormal).
		int HoverFlagsForTooltipMouse = 0;              // Default flags when using IsItemHovered(ImGuiHoveredFlags_ForTooltip) while using mouse.
		int HoverFlagsForTooltipNav = 0;                // Default flags when using IsItemHovered(ImGuiHoveredFlags_ForTooltip) while using keyboard/gamepad.
	};

	// The colors of the dear imgui style (ImGuiStyle::Colors), in the order of ImGuiCol_, as of dear imgui v1.93
	export_ struct ImguiColours
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
		Colour CheckboxSelectedBg;
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
		Colour InputTextCursor;
		Colour TabHovered;
		Colour Tab;
		Colour TabSelected;
		Colour TabSelectedOverline;
		Colour TabDimmed;
		Colour TabDimmedSelected;
		Colour TabDimmedSelectedOverline;
		Colour PlotLines;
		Colour PlotLinesHovered;
		Colour PlotHistogram;
		Colour PlotHistogramHovered;
		Colour TableHeaderBg;
		Colour TableBorderStrong;
		Colour TableBorderLight;
		Colour TableRowBg;
		Colour TableRowBgAlt;
		Colour TextLink;
		Colour TextSelectedBg;
		Colour TreeLines;
		Colour DragDropTarget;
		Colour DragDropTargetBg;
		Colour UnsavedMarker;
		Colour NavCursor;
		Colour NavWindowingHighlight;
		Colour NavWindowingDimBg;
		Colour ModalWindowDimBg;

		static constexpr size_t Count = 61;
		Colour& operator[](size_t index) { return (&Text)[index]; }
		const Colour& operator[](size_t index) const { return (&Text)[index]; }
	};

	// A dear imgui style: its sizes and its colors
	export_ struct ImguiTheme
	{
		ImguiLook look;
		ImguiColours colours;
	};

	export_ TWO_UI_EXPORT ImguiColours imgui_colours_dark();
	export_ TWO_UI_EXPORT ImguiColours imgui_colours_light();
	export_ TWO_UI_EXPORT ImguiColours imgui_colours_classic();

	// applies a dear imgui style to the styles of two.ui
	export_ TWO_UI_EXPORT void style_imgui(UiWindow& ui_window, const ImguiLook& look, const ImguiColours& colours);

	export_ TWO_UI_EXPORT func_ void style_imgui_dark(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_imgui_light(UiWindow& ui_window);
	export_ TWO_UI_EXPORT func_ void style_imgui_classic(UiWindow& ui_window);

	export_ TWO_UI_EXPORT void style_imgui(UiWindow& ui_window, ImguiStyle style = ImguiStyle::Dark);

	// the style of the Wonderland editor, on top of the dear imgui dark style
	export_ TWO_UI_EXPORT ImguiLook imgui_look_wonderland();
	export_ TWO_UI_EXPORT ImguiColours imgui_colours_wonderland();
	export_ TWO_UI_EXPORT void style_imgui_wonderland(UiWindow& ui_window);

	// the dear imgui v1.70 styles, kept for reference
	export_ TWO_UI_EXPORT void style_imgui_legacy_dark(UiWindow& ui_window);
	export_ TWO_UI_EXPORT void style_imgui_legacy_light(UiWindow& ui_window);
	export_ TWO_UI_EXPORT void style_imgui_legacy_classic(UiWindow& ui_window);
}
