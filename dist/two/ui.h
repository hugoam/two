#pragma once

#include <two/infra.h>
#include <two/type.h>





#ifndef TWO_UI_EXPORT
#define TWO_UI_EXPORT TWO_IMPORT
#endif

namespace two
{
namespace ui
{
    export_ enum class PopupFlags : unsigned int;
    
    
    export_ struct DropdownStyles;
    export_ struct MenuStyles;
    export_ struct ToolbarStyles;
    export_ struct TableStyles;
    export_ struct ExpandboxStyles;
    export_ struct TreeNodeStyles;
    export_ struct TabberStyles;
    export_ struct DragPoint;
    export_ struct CursorStyles;
    export_ struct DockStyles;
    export_ struct SliderState;
    export_ struct SliderMetrics;
    export_ struct NodeStyles;
    export_ struct CanvasStyles;
    export_ struct ScrollbarStyles;
    export_ struct WindowStyles;
    export_ struct FileStyles;
    export_ class Sequence;
}
}

namespace two
{
    export_ enum class FlowAxis : unsigned int;
    export_ enum class Pivot : unsigned int;
    export_ enum class Align : unsigned int;
    export_ enum class Solver : unsigned int;
    export_ enum class AutoLayout : unsigned int;
    export_ enum class LayoutFlow : unsigned int;
    export_ enum class Sizing : unsigned int;
    export_ enum class Preset : unsigned int;
    export_ enum class Clip : unsigned int;
    export_ enum class Opacity : unsigned int;
    export_ enum WidgetState : unsigned int;
    export_ enum DirtyLayout : unsigned int;
    export_ enum class CodePalette : unsigned char;
    export_ enum class TextFocusMode : unsigned int;
    export_ enum class WindowState : unsigned int;
    export_ enum class DropState : unsigned int;

    export_ class Style;
	export_ struct Subskin;
    export_ struct Space;
    export_ struct Styles;
    export_ struct UiRect;
    export_ class Frame;
    export_ class Widget;
    export_ struct TextGlyph;
    export_ struct TextRow;
    export_ struct Shadow;
    export_ struct Paint;
    export_ struct TextPaint;
	export_ struct TextMarker;
    export_ struct Gradient;
    export_ struct TextCursor;
    export_ struct TextSelection;
    export_ class Text;
    export_ class TextEdit;
	export_ struct Clipboard;
    export_ struct NodeConnection;
    export_ class Vg;
    export_ class UiRenderer;
    export_ class UiWindow;
    export_ class User;
    export_ struct KeyCombo;
    export_ class EventDispatch;
    export_ struct Identifier;
    export_ struct LanguageDefinition;
    export_ class Layer;
    export_ struct Layout;
    export_ class FrameSolver;
    export_ class RowSolver;
    export_ class CustomSolver;
    export_ class TableSolver;
    export_ class LineSolver;
    export_ class GridSolver;
    export_ class ScrollSheet;
    export_ class Tabber;
    export_ class Expandbox;
    export_ class TreeNode;
    export_ class Table;
    export_ struct Dock;
    export_ class Docksystem;
    export_ class Dockable;
    export_ class Docker;
    export_ class Dockspace;
    export_ class Dockbar;
    export_ class NodePlug;
    export_ class Node;
    export_ struct CanvasConnect;
    export_ class Canvas;
    export_ struct DropAction;
    export_ class Ui;
    export_ class Window;
    export_ struct ImageSkin;
    export_ struct InkStyle;
    export_ class Options;
    export_ class Styler;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
#include <stl/span.h>







namespace two
{
	//export_ enum class refl_ Dim : unsigned int
	//{
	//	X = 0,
	//	Y = 1,
	//	None = 2,
	//	Count
	//};

	inline Axis flip(Axis dim) { return dim == Axis::X ? Axis::Y : Axis::X; }

	export_ enum class refl_ FlowAxis : unsigned int
	{
		Reading = 0,
		Paragraph = 1,
		Same = 2,
		Flip = 3,
		None = 4,
	};

	export_ enum class refl_ Pivot : unsigned int
	{
		Forward = 0,
		Reverse = 1
	};

	export_ enum class refl_ Align : unsigned int
	{
		Left = 0,
		Center = 1,
		Right = 2,
		OutLeft = 3,
		OutRight = 4,
		Count
	};

	extern table<Align, float> c_align_extent;
	extern table<Align, float> c_align_space;

	export_ enum class refl_ Solver : unsigned int
	{
		Frame = 0,
		Row = 1,
		Grid = 2,
		Table = 3,
	};

	export_ enum class refl_ AutoLayout : unsigned int
	{
		None = 0,
		Size = 1,
		Layout = 2
	};

	export_ enum class refl_ LayoutFlow : unsigned int
	{
		Flow = 0,			// AutoLayout::Layout
		Overlay = 1,		// AutoLayout::Size
		Align = 2,			// AutoLayout::Position
		Free = 3			// AutoLayout::None
	};

	export_ enum class refl_ Sizing : unsigned int
	{
		Fixed,
		Shrink,
		Wrap,
		Expand
	};

	export_ enum class refl_ Preset : unsigned int
	{
		Sheet,   // Paragraph   direction, Sizing::Wrap   length, Sizing::Wrap   depth
		Flex,	 // Same		direction, Sizing::Wrap   length, Sizing::Wrap   depth
		Item,    // Reading     direction, Sizing::Shrink length, Sizing::Shrink depth
		Unit,    // Paragraph   direction, Sizing::Shrink length, Sizing::Shrink depth
		Block,   // Paragraph   direction, Sizing::Fixed  length, Sizing::Fixed  depth
		Line,	 // Reading     direction, Sizing::Wrap   length, Sizing::Shrink depth
		Stack,   // Paragraph   direction, Sizing::Shrink length, Sizing::Wrap   depth 
		Div,	 // Flip        direction, Sizing::Wrap   length, Sizing::Shrink depth
		Spacer,  // Same        direction, Sizing::Wrap   length, Sizing::Shrink depth
		Board,   // Reading     direction, Sizing::Expand length, Sizing::Expand depth
		Layout   // Paragraph   direction, Sizing::Expand length, Sizing::Expand depth
	};

	export_ struct refl_ TWO_UI_EXPORT Space
	{
		attr_ FlowAxis direction;
		attr_ Sizing sizingLength;
		attr_ Sizing sizingDepth;

		Space(FlowAxis dir, Sizing length, Sizing depth) : direction(dir), sizingLength(length), sizingDepth(depth) {}
		Space(Preset preset = Preset::Flex) { *this = Space::preset(preset); }

		bool operator==(const Space& other) const { return direction == other.direction && sizingLength == other.sizingLength && sizingDepth == other.sizingDepth; }

		static Space preset(Preset preset);
	};

	extern Space SpacePresets[11];

	export_ enum class refl_ Clip : unsigned int
	{
		None = 0,
		Clip = 1,
		Unclip = 2
	};

	export_ enum class refl_ Opacity : unsigned int
	{
		Opaque = 0,
		Clear = 1,
		Hollow = 2
	};

	extern template struct refl_ array_ struct_ v2<bool>;
	extern template struct refl_ array_ struct_ v2<AutoLayout>;
	extern template struct refl_ array_ struct_ v2<Sizing>;
	extern template struct refl_ array_ struct_ v2<Align>;
	extern template struct refl_ array_ struct_ v2<Pivot>;
}



namespace two
{
	export_ struct refl_ TWO_UI_EXPORT ImageSkin
	{
	public:
		enum Section
		{
			TopLeft = 0, // Corners
			TopRight = 1,
			BottomRight = 2,
			BottomLeft = 3,
			Top = 4, // Borders
			Right = 5,
			Bottom = 6,
			Left = 7,
			Fill = 8, // Fill
			Count
		};

	public:
		constr_ ImageSkin(Image& image, int left, int top, int right, int bottom, int margin = 0, Axis stretch = Axis::None);
		ImageSkin(Image& image, const ImageSkin& ref);
		ImageSkin();

		bool null() const { return d_image == nullptr; }

		void stretch_coords(vec2 offset, vec2 size, span<vec4> coords) const;

		attr_ Image* d_image = nullptr;

		attr_ int d_left = 0;
		attr_ int d_top = 0;
		attr_ int d_right = 0;
		attr_ int d_bottom = 0;
		attr_ int m_margin = 0;
		attr_ Axis d_stretch = Axis::None;

		vec2 d_size;
		vec2 d_solid_size;
		vec2 d_fill_size;
		vec2 m_min_size;

		Image d_images[9];
	};
}



namespace two
{
	using cstring = const char*;

	export_ struct refl_ TWO_UI_EXPORT Shadow
	{
	public:
		constr_ Shadow(float xpos, float ypos, float blur, float spread, Colour colour = Colour::AlphaBlack)
			: d_xpos(xpos), d_ypos(ypos), d_blur(blur), d_spread(spread), d_colour(colour), d_pos(xpos, ypos), d_null(false), d_radius(spread + blur)
		{}

		constr_ Shadow()
			: d_null(true)
		{}

		attr_ float d_xpos;
		attr_ float d_ypos;
		attr_ float d_blur;
		attr_ float d_spread;
		attr_ Colour d_colour;

		vec2 d_pos;
		bool d_null;
		float d_radius;
	};

	export_ struct refl_ TWO_UI_EXPORT Paint
	{
		Paint() {}
		Paint(Colour fill_colour) : m_fill_colour(fill_colour), m_stroke_colour(Colour::None), m_stroke_width(0.f) {}
		Paint(Colour stroke_colour, float stroke_width) : m_fill_colour(Colour::None), m_stroke_colour(stroke_colour), m_stroke_width(stroke_width) {}
		Paint(Colour fill_colour, Colour stroke_colour, float stroke_width) : m_fill_colour(fill_colour), m_stroke_colour(stroke_colour), m_stroke_width(stroke_width) {}
		attr_ Colour m_fill_colour;
		attr_ Colour m_stroke_colour;
		attr_ float m_stroke_width;
	};

	export_ struct refl_ TWO_UI_EXPORT TextPaint
	{
		attr_ cstring m_font;
		attr_ Colour m_colour;
		attr_ float m_size;
		attr_ v2<Align> m_align;
		attr_ bool m_text_break;
		attr_ bool m_text_wrap;
	};

	export_ struct refl_ TWO_UI_EXPORT Gradient
	{
		attr_ Colour m_start;
		attr_ Colour m_end;
	};
}

namespace two
{
	using CustomDraw = void(*)(const Frame&, const vec4&, Vg&);

	export_ struct refl_ TWO_UI_EXPORT InkStyle
	{
	public:
		constr_ InkStyle() {}
		constr_ InkStyle(const string& name) : m_name(name) {}

		template <class T_Initializer>
		InkStyle(T_Initializer func) { func(*this); }

		void prepare()
		{
			if(!m_background_colour.null() || !m_text_colour.null() || !m_border_colour.null() || m_image || !m_image_skin.null() || m_custom_draw)
				m_empty = false;
		}

		attr_ string m_name = "";
		attr_ bool m_empty = true;
		attr_ Colour m_background_colour = Colour::None;
		attr_ Colour m_border_colour = Colour::None;
		attr_ Colour m_image_colour = Colour::None;
		attr_ Colour m_text_colour = Colour::None;
		attr_ string m_text_font = "dejavu";
		attr_ float m_text_size = 13.f;
		attr_ bool m_text_break = false;
		attr_ bool m_text_wrap = false;
		attr_ vec4 m_border_width = vec4(0.f);
		attr_ vec4 m_corner_radius = vec4(0.f);
		attr_ bool m_weak_corners = false;
		attr_ vec4 m_padding = vec4(0.f);
		attr_ vec4 m_margin = vec4(0.f);
		attr_ v2<Align> m_align = { Align::Left, Align::Left };
		attr_ vec2 m_linear_gradient = vec2(0.f);
		attr_ Axis m_linear_gradient_dim = Axis::Y;
		attr_ v2<bool> m_stretch = { false, false };
		attr_ Image* m_image = nullptr;
		attr_ Image* m_overlay = nullptr;
		attr_ Image* m_tile = nullptr;
		attr_ ImageSkin m_image_skin;
		attr_ Shadow m_shadow;
		attr_ Colour m_shadow_colour;
		attr_ Style* m_hover_cursor = nullptr;
		/*attr_*/ CustomDraw m_custom_draw = nullptr;
	};

	inline TextPaint text_paint(InkStyle& inkstyle)
	{
		return { inkstyle.m_text_font.c_str(), inkstyle.m_text_colour, inkstyle.m_text_size, inkstyle.m_align, inkstyle.m_text_break, inkstyle.m_text_wrap };
	}
}



namespace two
{
	export_ struct refl_ TWO_UI_EXPORT Layout
	{
	public:
		constr_ Layout() {}
		constr_ Layout(const string& name) : m_name(name) {}

		template <class T_Initializer>
		Layout(T_Initializer func) { func(*this); }

		attr_ string m_name = "";
		attr_ Solver m_solver = Solver::Frame;
		attr_ v2<AutoLayout> m_layout = { AutoLayout::Layout, AutoLayout::Layout };
		attr_ LayoutFlow m_flow = LayoutFlow::Flow;
		attr_ Space m_space = Preset::Sheet;
		attr_ Clip m_clipping = Clip::None;
		attr_ Opacity m_opacity = Opacity::Clear;
		attr_ v2<Align> m_align = { Align::Left, Align::Left };
		attr_ vec2 m_span = vec2(1.f);
		attr_ vec2 m_size = vec2(0.f);
		attr_ vec4 m_padding = vec4(0.f);
		attr_ vec2 m_margin = vec2(0.f);
		attr_ vec2 m_spacing = vec2(0.f);
		attr_ v2<Pivot> m_pivot = { Pivot::Forward, Pivot::Forward };
		attr_ int m_zorder = 0;
		attr_ bool m_no_grid = false;

		attr_ vector<Space> m_grid_division;
		attr_ vector<float> m_table_division;

		attr_ size_t m_updated = 0;
	};
}

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
namespace stl
{
	export_ using cstring = const char*;
	extern template struct refl_ span_ span<float>;
	extern template struct refl_ span_ span<cstring>;

	//extern template class refl_ seque_ vector<string>;
	extern template class refl_ seque_ vector<two::Space>;
	extern template class refl_ seque_ vector<two::Subskin>;
}
#endif

namespace two
{
namespace ui
{
	export_ struct TableStyles
	{
		void reset();
		Style row; Style row_odd; Style row_even; Style separator;
	};

	export_ TWO_UI_EXPORT TableStyles& table_styles();

	export_ struct ExpandboxStyles
	{
		void reset();
		Style expandbox; Style header; Style toggle; Style body;
	};

	export_ TWO_UI_EXPORT ExpandboxStyles& expandbox_styles();

	export_ struct TreeNodeStyles
	{
		void reset();
		Style treenode; Style header; Style toggle; Style no_toggle; Style body;
	};

	export_ TWO_UI_EXPORT TreeNodeStyles& treenode_styles();

	export_ struct TabberStyles
	{
		void reset();
		Style tab; Style tab_button; Style tabber; Style head; Style edge; Style body;
	};

	export_ TWO_UI_EXPORT TabberStyles& tabber_styles();

	export_ TWO_UI_EXPORT func_ ScrollSheet& select_list(Widget& parent);

	// @todo reflection for span<T>
	export_ TWO_UI_EXPORT func_ Table& columns(Widget& parent, span<float> weights);
	export_ TWO_UI_EXPORT func_ Table& table(Widget& parent, span<cstring> columns, span<float> weights);
	export_ TWO_UI_EXPORT func_ Widget& table_row(Widget& parent);
	export_ TWO_UI_EXPORT func_ Widget& table_separator(Widget& parent);

	export_ TWO_UI_EXPORT Expandbox& expandbox(Widget& parent, span<cstring> elements, bool open = true);
	export_ TWO_UI_EXPORT func_ Expandbox& expandbox(Widget& parent, cstring name, bool open = true);

	export_ TWO_UI_EXPORT TreeNode& tree_node(Widget& parent, span<cstring> elements, bool leaf = false, bool open = true);
	export_ TWO_UI_EXPORT func_ TreeNode& tree_node(Widget& parent, cstring name, bool leaf = false, bool open = true);
	export_ TWO_UI_EXPORT func_ Widget& tree(Widget& parent);

	export_ TWO_UI_EXPORT func_ Widget* tab(Tabber& tabber, cstring name);
	export_ TWO_UI_EXPORT func_ Tabber& tabber(Widget& parent);
}
}







namespace two
{
	export_ struct TWO_UI_EXPORT TextGlyph
	{
		const char* m_position;
		vec4 m_rect;
	};

	export_ struct TWO_UI_EXPORT TextRow
	{
		const char* m_start;
		const char* m_end;
		size_t m_start_index;
		size_t m_end_index;
		vec4 m_rect;

		vector<TextGlyph> m_glyphs;
	};

	export_ inline TextRow text_row(const char* str, const char* start, const char* end, const vec4& rect)
	{
		return { start, end, size_t(start - str), size_t(end - str), rect, {} };
	}

	TWO_UI_EXPORT bool is_separator(char c);

	TWO_UI_EXPORT size_t word_begin(const string& text, size_t index);
	TWO_UI_EXPORT size_t word_end(const string& text, size_t index);
	TWO_UI_EXPORT string word_at(const string& text, size_t index);

	TWO_UI_EXPORT size_t line_begin(const string& text, size_t index);
	TWO_UI_EXPORT size_t line_end(const string& text, size_t index);

	TWO_UI_EXPORT string text_line(const string& text, size_t index);
	TWO_UI_EXPORT size_t text_column(const string& text, size_t index);

	TWO_UI_EXPORT void replace_tabs(string& text, size_t tab_size = 4);

	export_ struct refl_ TWO_UI_EXPORT TextCursor
	{
		TextCursor() {}
		TextCursor(size_t index, uvec2 grid_index) : m_index(index), m_grid_index(grid_index) {}

		bool operator==(const TextCursor& other) const { return m_index == other.m_index && m_grid_index == other.m_grid_index; }

		operator size_t() const { return size_t(m_index); }

		size_t m_index = SIZE_MAX;
		uvec2 m_grid_index = { UINT_MAX, UINT_MAX };
	};

	export_ struct refl_ TWO_UI_EXPORT TextSelection
	{
		TextSelection() {}
		TextSelection(TextCursor cursor, size_t start, size_t end, bool insert_mode) : m_cursor(cursor), m_start(start), m_end(end), m_insert_mode(insert_mode) {}
		TextCursor m_cursor;
		size_t m_start = SIZE_MAX;
		size_t m_end = SIZE_MAX;
		bool m_insert_mode = false;
	};

	using PaletteIndex = uint16_t;
	using ColourPalette = span<uint32_t>;

	export_ enum class TextMarkerKind
	{
		Error,
	};

	export_ struct refl_ TWO_UI_EXPORT TextMarker
	{
		TextMarkerKind m_type;
		size_t m_line;
		size_t m_column;
		string m_message;
		PaletteIndex m_colour;
		PaletteIndex m_highlight;
	};

	export_ class refl_ TWO_UI_EXPORT Text
	{
	public:
		Text(Frame& frame);

		void update_style();

		void set_lines(size_t lines);
		void set_text(const string& text);

		float line_height() const;
		float compute_height() const;
		float compute_width() const;
		vec2 compute_text_size();

		void break_text_rows();

		vec4 interval_rect(const TextRow& row, size_t start, size_t end) const;
		vec4 interval_rect(size_t start, size_t end) const;

		size_t text_row_index(size_t index) const;
		const TextRow& text_row_at(size_t index) const;

		size_t char_at(const vec2& pos) const;
		TextCursor cursor_at(const vec2& pos) const;

		TextCursor to_cursor(size_t index) const;
		TextCursor to_cursor(const uvec2& grid_index) const;

		TextCursor clamp_cursor(int index) const;
		TextCursor clamp_cursor(const ivec2& grid_index) const;

		vec4 cursor_rect(size_t index) const;

		enum Palette : uint8_t
		{
			Default = 0,
			Background,
			Cursor,
			Selection,
			LineNumber,
			CurrentLineFill,
			CurrentLineFillInactive,
			CurrentLineEdge,
			Count
		};

	public:
		Frame& m_frame;
		string m_text;
		size_t m_num_lines;

		vector<TextRow> m_text_rows;

		TextPaint m_text_paint;

		struct ColorSection
		{
			size_t m_start;
			size_t m_end;
			PaletteIndex m_colour;
		};

		vector<ColorSection> m_sections;

		vector<TextMarker> m_markers;

	public:
		static Vg* s_vg;
	};

	TWO_UI_EXPORT Colour palette_colour(const ColourPalette& palette, PaletteIndex color_index);
	TWO_UI_EXPORT Paint palette_paint(const ColourPalette& palette, PaletteIndex color_index);
	TWO_UI_EXPORT TextPaint palette_text_paint(const Text& text, const ColourPalette& palette, PaletteIndex color_index);

	TWO_UI_EXPORT void draw_text(Vg& vg, const vec2& padding, const Text& text);
	TWO_UI_EXPORT void draw_editor_text(Vg& vg, const Frame& frame, const vec2& padding, const vec2& text_offset, const Text& text, const ColourPalette& palette);
	TWO_UI_EXPORT void draw_text_selection(Vg& vg, const Frame& frame, const vec2& padding, const vec2& text_offset, const Text& text, const TextSelection& selection, const ColourPalette& palette, bool current_line);
}

namespace two
{
	using cstring = const char*;

	export_ class refl_ TWO_UI_EXPORT Vg
	{
	public:
		Vg(cstring resource_path);
		virtual ~Vg();

		// init
		virtual void setup_context() = 0;
		virtual void release_context() = 0;

		// setup
		virtual void load_default_font() = 0;
		virtual void load_font(cstring name) = 0;
		virtual void load_image_RGBA(Image& image, const unsigned char* data) = 0;
		virtual void load_image(Image& image) = 0;
		virtual void unload_image(Image& image) = 0;
		virtual uint16_t load_texture(uint16_t texture) = 0;

		// rendering
		virtual void begin_frame(uint16_t view, const vec4& rect, float pixel_ratio = 1.f, const Colour& colour = Colour(0.f)) = 0;
		virtual void end_frame(uint16_t view) = 0;

		// drawing
		virtual void begin_target() = 0;
		virtual void end_target() = 0;

#ifdef TWO_UI_DRAW_CACHE
		virtual void begin_cached(Layer& layer) = 0;
		virtual void end_cached() = 0;

		virtual void draw_layer(Layer& layer, const vec2& position = vec2(0.f), float scale = 1.f) = 0;
#endif

		virtual void begin_layer(Layer& layer, const vec2& position = vec2(0.f), float scale = 1.f) = 0;
		virtual void end_layer() = 0;

		virtual void begin_update(const vec2& position, float scale) = 0;
		virtual void end_update() = 0;

		virtual bool clipped(const vec4& rect) = 0;
		virtual void clip(const vec4& rect) = 0;
		virtual void unclip() = 0;

		virtual void begin_path() = 0;
		virtual void move_to(const vec2& p) = 0;
		virtual void line_to(const vec2& p) = 0;
		virtual void close_path() = 0;

		virtual void path_line(const vec2& p1, const vec2& p2) = 0;
		virtual void path_bezier(const vec2& p1, const vec2& c1, const vec2& c2, const vec2& p2, bool straighten = false) = 0;
		virtual void path_rect(const vec4& rect, const vec4& corners, float border) = 0;
		virtual void path_circle(const vec2& center, float r) = 0;

		virtual void fill(const Gradient& gradient, const vec2& start, const vec2& end) = 0;
		virtual void fill(const Paint& paint) = 0;
		virtual void stroke(const Paint& paint) = 0;

		virtual void stroke_gradient(const Gradient& paint, float width, const vec2& start, const vec2& end) = 0;

		virtual void draw_shadow(const vec4& rect, const vec4& corner, const Shadow& shadows) = 0;
		virtual void draw_texture(uint16_t texture, const vec4& rect, const vec4& image_rect) = 0;
		virtual void draw_text(const vec2& offset, const char* start, const char* end, const TextPaint& paint) = 0;

		virtual void draw_color_wheel(const vec2& center, float r0, float r1) = 0;
		virtual void draw_color_triangle(const vec2& center, float r0, float hue, float s, float l) = 0;

		virtual void debug_rect(const vec4& rect, const Colour& colour);

		virtual void break_text(cstring text, size_t len, const vec2& space, const TextPaint& paint, vector<TextRow>& rows);

		void fill_text(cstring text, size_t len, const vec4& rect, const TextPaint& paint, TextRow& row);
		void break_text_width(const char* text, const char* start, const char* end, const vec4& rect, const TextPaint& paint, TextRow& textRow);
		void break_text_returns(const char* text, const char* start, const char* end, const vec4& rect, const TextPaint& paint, TextRow& textRow);

		virtual void break_next_row(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row) = 0;
		virtual void break_glyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow) = 0;

		virtual float line_height(const TextPaint& paint) = 0;
		virtual float text_size(cstring text, size_t len, Axis dim, const TextPaint& paint) = 0;
		virtual vec2 text_size(cstring text, size_t len, const TextPaint& paint) = 0;

		void draw_rect(const vec4& rect, const Paint& paint, const vec4& corners = vec4(0.f));

		cstring font_path(cstring font);

	protected:
		struct Impl;
		unique<Impl> m_impl;

		bool m_null = false;
	};

	export_ TWO_UI_EXPORT vec4 select_corners(const Frame& frame);
	export_ TWO_UI_EXPORT float content_position(const Frame& frame, const vec2& content, const vec2& padded_pos, const vec2& padded_size, Axis dim);

	export_ TWO_UI_EXPORT void draw_frame(Vg& vg, const Frame& frame, const vec4& rect);
	export_ TWO_UI_EXPORT void draw_content(Vg& vg, const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect);
	export_ TWO_UI_EXPORT void draw_background(Vg& vg, const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect);
	export_ TWO_UI_EXPORT void draw_rect(Vg& vg, const vec4& rect, const vec4& corners, const InkStyle& inkstyle);
	export_ TWO_UI_EXPORT void draw_image(Vg& vg, const Image& image, const vec4& rect);
	export_ TWO_UI_EXPORT void draw_image_stretch(Vg& vg, const Image& image, const vec4& rect, const vec2& stretch = { 1.f, 1.f });
	export_ TWO_UI_EXPORT void draw_skin_image(Vg& vg, const Frame& frame, int section, vec4 rect);

	export_ class TWO_UI_EXPORT UiRenderer
	{
	public:
		UiRenderer(Vg& vg);
		virtual ~UiRenderer();

		void render(Layer& layer, uint16_t view, float pixel_ratio, const Colour& colour = Colour(0.f));// = 1.f);

		// drawing implementation
		void render_layer(Layer& layer);

		void begin_layer(Frame& frame);
		void begin_frame(Frame& frame);
		void render_frame(Frame& frame);
		void end_frame(Frame& frame);
		void end_layer(Frame& frame);
		void draw_frame(const Frame& frame);

		void log_FPS();

	protected:
		Vg& m_vg;
		size_t m_debug_batch = 0;

		struct Impl;
		unique<Impl> m_impl;

		Clock m_clock;
	};
}

namespace two
{
	export_ struct refl_ TWO_UI_EXPORT Clipboard
	{
		Clipboard() {}
		Clipboard(const string& text, bool line_mode) : m_text(text), m_line_mode(line_mode) {}
		attr_ string m_text = "";
		attr_ bool m_line_mode = false;
		attr_ vector<string> m_pasted = {};
	};

	export_ class refl_ TWO_UI_EXPORT UiWindow
	{
	public:
		UiWindow(Context& context, Vg& vg, User* user = nullptr);
		~UiWindow();

		void init();
		bool input_frame();
		void render_frame(uint16_t view);
		void shutdown();

		meth_ void reset_styles();

		void resize(const uvec2& size, const uvec2& fb_size);

		Image& create_image(cstring image, const uvec2& size, span<uint8_t> data, bool filtering = true);
		void remove_image(Image& image);
		Image* find_image(cstring name);

	protected:
		void init_resources();
		void load_resources();

	public:
		attr_ const string m_resource_path;

		attr_ Context& m_context;
		attr_ Vg& m_vg;

		UiRenderer m_renderer;

		vector<unique<Image>> m_images;
		ImageAtlas m_atlas;

		attr_ uvec2 m_size;
		attr_ Colour m_colour = Colour(0.f);
		attr_ bool m_shutdown = false;

		Clipboard m_clipboard;

		unique<Ui> m_ui;

		User* m_user = nullptr;
	};
}







namespace two
{
	export_ struct refl_ TWO_UI_EXPORT UiRect
	{
		attr_ vec2 m_position = vec2(0.f);
		attr_ vec2 m_size = vec2(0.f);
		attr_ vec2 m_content = vec2(0.f);
		attr_ vec2 m_span = vec2(1.f);
		attr_ float m_scale = 1.f;
	};
}

namespace two
{
	using cstring = const char*;

	enum DirtyLayout : unsigned int
	{
		CLEAN,				// Frame doesn't need update
		DIRTY_REDRAW,		// The parent layout has changed
		DIRTY_PARENT,		// The parent layout has changed
		DIRTY_LAYOUT,		// The frame layout has changed
		DIRTY_FORCE_LAYOUT	// The frame layout has changed
	};

	export_ class refl_ TWO_UI_EXPORT Frame : public UiRect
	{
	public:
		Frame(Frame* parent, Widget& widget);
		virtual ~Frame();

		bool empty() const;

		inline bool opaque() const { return m_opacity == Opacity::Opaque; }
		inline bool hollow() const { return m_opacity == Opacity::Hollow; }

		void set_caption(cstring text);
		void set_icon(Image* image);
		Image* icon() const;
		cstring caption() const;

		void size_caption();

		Frame& root();
		Layer& layer();

		FrameSolver& solver(Style& style, Axis length = Axis::None, v2<uint> index = { 0, 0 });

		DirtyLayout clearDirty() { DirtyLayout dirty = d_dirty; d_dirty = CLEAN; return dirty; }
		void set_dirty(DirtyLayout dirty) { if(dirty > d_dirty) d_dirty = dirty; }
		void mark_dirty(DirtyLayout dirty);

		void update_style(bool reset = false);
		void update_state(WidgetState state);
		void update_inkstyle(InkStyle& inkstyle, bool reset = false);

		void set_size(Axis dim, float size);
		void set_span(Axis dim, float span);
		void set_position(Axis dim, float position);

		inline void set_position(const vec2& pos) { set_position(Axis::X, pos.x), set_position(Axis::Y, pos.y); }
		inline void set_size(const vec2& size) { set_size(Axis::X, size.x); set_size(Axis::Y, size.y); }

		// global to local
		void integrate_position(Frame& root, vec2& global);
		inline vec2 integrate_position(const vec2& pos, Frame& root) { vec2 local = pos; integrate_position(root, local); return local; }
		inline vec2 local_position(const vec2& pos) { return integrate_position(pos, root()); }

		// local to global
		void derive_position(Frame& root, vec2& local);
		inline vec2 derive_position(const vec2& pos, Frame& root) { vec2 local = pos; derive_position(root, local); return local; }
		inline vec2 derive_position(const vec2& pos) { return derive_position(pos, root()); }
		inline vec2 absolute_position() { return derive_position({ 0.f, 0.f }); }

		float derive_scale(Frame& root);
		inline float absolute_scale() { return this->derive_scale(root()); }

		void clamp_to_parent();

		vec4 content_rect() const;

		bool inside(const vec2& pos);
		bool inside_abs(const vec2& pos) { return this->inside(local_position(pos)); }

		bool first(const Frame& frame);
		bool last(const Frame& frame);

		void transfer_pixel_span(Frame& prev, Frame& next, Axis dim, float pixelSpan);

		void relayout();

		void sync_solver(FrameSolver& solver);
		void read_solver(FrameSolver& solver);

		void debug_print(bool commit);

	public:
		Widget& d_widget;
		Frame* d_parent;
		DirtyLayout d_dirty = DIRTY_FORCE_LAYOUT;
		v2<uint> d_index = { 0, 0 };

		Opacity m_opacity = Opacity::Clear;

		Style* d_style = nullptr;
		Layout* d_layout = nullptr;
		InkStyle* d_inkstyle = nullptr;

	public:
		string d_caption = "";
		Image* d_icon = nullptr;

		unique<FrameSolver> m_solver;

		unique<Layer> m_layer;
		unique<Text> m_text;

		static Vg* s_vg;
	};
}



namespace two
{
	export_ namespace ui
	{}

	using cstring = const char*;

	export_ enum refl_ WidgetState : unsigned int
	{
		NOSTATE = 0,			// default state
		CREATED = 1 << 0,		// just created
		HOVERED = 1 << 1,		// hovered by an input device
		PRESSED = 1 << 2,		// pressed by an input device
		ACTIVATED = 1 << 3,		// activated (event-like state)
		ACTIVE = 1 << 4,		// active (on/off state)
		SELECTED = 1 << 5,		// selected (on/off state)
		DISABLED = 1 << 6,		// disabled (on/off state)
		DRAGGED = 1 << 7,		// dragged by input device
		FOCUSED = 1 << 8,		// has exclusive focus in the widget hierarchy
		CLOSED = 1 << 9			// widget has just been closed
	};

namespace ui
{
	export_ TWO_UI_EXPORT func_ Widget& widget(Widget& parent, Style& style, bool open = false, Axis length = Axis::None, v2<uint> index = { 0, 0 });
	export_ TWO_UI_EXPORT Widget& widget(Widget& parent, Style& style, void* identity);

	export_ TWO_UI_EXPORT func_ Widget& item(Widget& parent, Style& style, cstring content = nullptr);
	export_ TWO_UI_EXPORT Widget& item(Widget& parent, Style& style, const string& content);

	export_ TWO_UI_EXPORT func_ Widget& multi_item(Widget& parent, Style& style, span<cstring> elements, Style* element_style = nullptr);
	export_ TWO_UI_EXPORT Widget& multi_item(Widget& parent, span<cstring> elements, Style* element_style = nullptr);

	export_ TWO_UI_EXPORT func_ Widget& spanner(Widget& parent, Style& style, Axis dim, float span);
}
}

namespace two
{
	using FrameFilter = bool(*)(Frame&);

#ifndef _MSC_VER
	extern template class Graph<Widget>;
#endif

	export_ class refl_ TWO_UI_EXPORT Widget : public Graph<Widget>, public ControlNode
	{
	public:
		Widget();
		Widget(Widget* parent, void* identity);
		~Widget();

		meth_ inline bool focused() { return (m_state & FOCUSED) != 0; }
		meth_ inline bool hovered() { return (m_state & HOVERED) != 0; }
		meth_ inline bool pressed() { return (m_state & PRESSED) != 0; }
		meth_ inline bool activated() { return (m_state & ACTIVATED) != 0; }
		meth_ inline bool active() { return (m_state & ACTIVE) != 0; }
		meth_ inline bool selected() { return (m_state & SELECTED) != 0; }
		meth_ inline bool modal() { return (m_state & FOCUSED) != 0; }
		meth_ inline bool closed() { return (m_state & CLOSED) != 0; }

		meth_ UiWindow& ui_window();
		meth_ Ui& ui();
		meth_ Widget& parent_modal();

		meth_ void clear();

		void set_content(cstring content);

		meth_ void toggle_state(WidgetState state);

		meth_ inline void disable_state(WidgetState state) { if(m_state & state) this->toggle_state(state); }
		meth_ inline void set_state(WidgetState state, bool enabled) { enabled ? enable_state(state) : disable_state(state); }
		meth_ inline void enable_state(WidgetState state) { if(!(m_state & state)) this->toggle_state(state); }

		meth_ inline void clear_focus() { this->parent_modal().set_modal(nullptr, device_mask(DeviceType::Keyboard)); }
		meth_ inline void take_focus() { if(!this->modal()) this->take_modal(device_mask(DeviceType::Keyboard)); }
		meth_ inline void yield_focus() { this->yield_modal(); }

		meth_ inline void take_modal(uint32_t device_filter = uint32_t(DeviceMask::All)) { this->parent_modal().set_modal(this, device_filter); }
		meth_ inline void yield_modal() { this->parent_modal().set_modal(nullptr, 0); }

		void set_modal(Widget* widget, uint32_t device_filter);

		Widget* pinpoint(vec2 pos);
		Widget* pinpoint(vec2 pos, const FrameFilter& filter);

		//inline bool fits_modifier(InputMod modifier, InputMod mask) { return mask == InputMod::Any || modifier == mask; }
		//
		//meth_ KeyEvent key_event(Key code, EventType event_type, InputMod modifier = InputMod::Any);
		//meth_ KeyEvent key_stroke(Key code, InputMod modifier = InputMod::Any) { return key_event(code, EventType::Stroked, modifier); }
		//meth_ KeyEvent char_stroke(Key code, InputMod modifier = InputMod::Any) { return key_event(translate(code), EventType::Stroked, modifier); }
		//
		//meth_ MouseEvent mouse_event(DeviceType device, EventType event_type, InputMod modifier = InputMod::None, bool consume = true);
		
		void transform_event(InputEvent& event);

		virtual ControlNode* control_event(InputEvent& event) override;
		virtual void receive_event(InputEvent& event) override;
		//virtual ControlNode* propagate_event(InputEvent& event) override;

		attr_ Frame m_frame;
		attr_ WidgetState m_state = CREATED;
		attr_ uint32_t m_switch = 0;
		attr_ uint32_t m_index = 0;
		attr_ bool m_open = false;
		attr_ Widget* m_body = nullptr;

		using CustomRender = function<void(const Frame&, const vec4&, Vg&)>;
		CustomRender m_custom_draw;

		Widget& layer();

		inline bool once() { if((m_state & CREATED) != 0) { disable_state(CREATED); return true; } return false; }
		inline Widget& init(Style& style, bool open = false, Axis length = Axis::None, v2<uint> index = { 0, 0 }) { if(!m_frame.d_style) { m_frame.solver(style, length, index); m_open = open; } return *this; }
	};

namespace ui
{
	export_ template <class T>
	inline T& twidget(Widget& parent, Style& style, bool open = false, Axis length = Axis::None, v2<uint> index = { 0, 0 })
	{
		T& self = parent.subi<T>(&style); self.init(style, open, length, index); return self;
	}
}
}



#define TWO_UI_SEQUENCE_REFS

namespace two
{
	export_ class refl_ TWO_UI_EXPORT ScrollSheet : public Widget
	{
	public:
		ScrollSheet(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_scroll_zone;
	};

namespace ui
{
	export_ class refl_ TWO_UI_EXPORT Sequence : public Widget
	{
	public:
		Sequence(Widget* parent, void* identity) : Widget(parent, identity) {}
#ifdef TWO_UI_SEQUENCE_REFS
		vector<Ref>* m_selection = nullptr;
#else
		vector<Widget*> m_selection;
#endif
	};
}

	export_ class refl_ TWO_UI_EXPORT Tabber : public Widget
	{
	public:
		Tabber(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_head = nullptr;
		size_t m_index = 0;
		size_t m_active = 0;
	};

	export_ class refl_ TWO_UI_EXPORT Expandbox : public Widget
	{
	public:
		Expandbox(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_header = nullptr;
	};

	export_ class refl_ TWO_UI_EXPORT TreeNode : public Widget
	{
	public:
		TreeNode(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_header = nullptr;
	};

	export_ class refl_ TWO_UI_EXPORT Table : public Widget
	{
	public:
		Table(Widget* parent, void* identity, span<float> weights);
		Table(Widget* parent, void* identity, size_t columns);
		vector<float> m_weights;
	};
}







namespace two
{
namespace ui
{
	export_ struct DropdownStyles
	{
		void reset();
		Style popdown; Style dropdown; Style toggle; Style head; Style list; Style choice; Style dropdown_input; Style dropdown_input_compact; Style typedown_input;
	};

	export_ TWO_UI_EXPORT DropdownStyles& dropdown_styles();

	export_ struct MenuStyles
	{
		void reset();
		Style menubar; Style menu; Style list; Style sublist; Style choice;
	};

	export_ TWO_UI_EXPORT MenuStyles& menu_styles();

	export_ struct ToolbarStyles
	{
		void reset();
		Style toolbutton; Style tooldock; Style toolbar; Style toolbar_wrap; Style mover;
	};

	export_ TWO_UI_EXPORT ToolbarStyles& toolbar_styles();

	export_ enum class refl_ PopupFlags : unsigned int
	{
		None = 0,
		Modal = (1 << 0),
		Clamp = (1 << 1),
		AutoClose = (1 << 2),
		AutoModal = Modal | AutoClose,
	};

	export_ TWO_UI_EXPORT func_ Widget& spacer(Widget& parent);
	export_ TWO_UI_EXPORT func_ Widget& separator(Widget& parent);

	export_ TWO_UI_EXPORT func_ Widget& icon(Widget& parent, cstring image);
	export_ TWO_UI_EXPORT func_ Widget& label(Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& title(Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& message(Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& text(Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& bullet(Widget& parent, cstring label);
	export_ TWO_UI_EXPORT func_ Widget& selectable(Widget& parent, cstring label, bool& selected);

	export_ TWO_UI_EXPORT Widget& labelf(Widget& parent, cstring label, ...);

	export_ TWO_UI_EXPORT Widget& icon(Widget& parent, const string& image);
	export_ TWO_UI_EXPORT Widget& label(Widget& parent, const string& text);
	export_ TWO_UI_EXPORT Widget& title(Widget& parent, const string& label);
	export_ TWO_UI_EXPORT Widget& message(Widget& parent, const string& label);
	export_ TWO_UI_EXPORT Widget& text(Widget& parent, const string& label);
	export_ TWO_UI_EXPORT Widget& bullet(Widget& parent, const string& label);
	export_ TWO_UI_EXPORT Widget& selectable(Widget& parent, const string& label, bool& selected);

	export_ TWO_UI_EXPORT void button_logic(Widget& self);
	export_ TWO_UI_EXPORT void toggle_logic(Widget& self, bool& on);

	export_ TWO_UI_EXPORT Widget& button(Widget& parent, Style& style, cstring content = nullptr);
	export_ TWO_UI_EXPORT Widget& toggle(Widget& parent, Style& style, bool& on, cstring content = nullptr);

	export_ TWO_UI_EXPORT Widget& multi_button(Widget& parent, Style& style, span<cstring> elements, Style* element_style = nullptr);
	export_ TWO_UI_EXPORT Widget& multi_toggle(Widget& parent, Style& style, bool& on, span<cstring> elements, Style* element_style = nullptr);

	export_ TWO_UI_EXPORT func_ Widget& button(Widget& parent, cstring content = nullptr);
	export_ TWO_UI_EXPORT func_ Widget& toggle(Widget& parent, bool& on, cstring content = nullptr);

	export_ TWO_UI_EXPORT func_ Widget& button(Widget& parent, const string& content);
	export_ TWO_UI_EXPORT func_ Widget& toggle(Widget& parent, bool& on, const string& content);

	export_ TWO_UI_EXPORT func_ Widget& multi_button(Widget& parent, span<cstring> elements, Style* element_style = nullptr);
	export_ TWO_UI_EXPORT func_ Widget& multi_toggle(Widget& parent, bool& on, span<cstring> elements, Style* element_style = nullptr);

	export_ TWO_UI_EXPORT func_ bool modal_button(Widget& screen, Widget& parent, cstring content, uint32_t mode);
	export_ TWO_UI_EXPORT func_ bool modal_multi_button(Widget& screen, Widget& parent, span<cstring> elements, uint32_t mode);

	export_ TWO_UI_EXPORT func_ Widget& checkbox(Widget& parent, bool& on);
	export_ TWO_UI_EXPORT func_ Widget& fill_bar(Widget& parent, float percentage, Axis dim = Axis::X);

	export_ TWO_UI_EXPORT func_ Widget& image256(Widget& parent, cstring name, const Image256& source);
	export_ TWO_UI_EXPORT func_ Widget& image256(Widget& parent, cstring name, const Image256& source, const vec2& size);

	export_ TWO_UI_EXPORT func_ Widget& image256(Widget& parent, const string& name, const Image256& source);
	export_ TWO_UI_EXPORT func_ Widget& image256(Widget& parent, const string& name, const Image256& source, const vec2& size);

	export_ TWO_UI_EXPORT func_ Widget& radio_choice(Widget& parent, cstring label, bool active);
	export_ TWO_UI_EXPORT func_ Widget& radio_button(Widget& parent, cstring label, uint32_t& value, uint32_t index);

	export_ TWO_UI_EXPORT func_ bool radio_switch(Widget& parent, span<cstring> labels, uint32_t& value, Axis dim = Axis::X);
	//TWO_UI_EXPORT bool radio_switch(Widget& parent, span<cstring> labels, string& value, Axis dim = Axis::X);

	//inline bool radio_switch_string(Widget& parent, span<cstring> labels, string& value) { return radio_switch(parent, labels, value); }

	export_ TWO_UI_EXPORT func_ bool popdown(Widget& parent, span<cstring> choices, uint32_t& value, vec2 position, PopupFlags flags);
	export_ TWO_UI_EXPORT func_ Widget& dropdown(Widget& parent, Style& style, cstring value, PopupFlags flags, bool no_toggle = false, Style* list_style = nullptr);
	export_ TWO_UI_EXPORT func_ bool dropdown_input(Widget& parent, span<cstring> choices, uint32_t& value, bool compact = false);
	export_ TWO_UI_EXPORT func_ bool typedown_input(Widget& parent, span<cstring> choices, uint32_t& value);

	export_ TWO_UI_EXPORT Widget& menu_choice(Widget& parent, span<cstring> elements);
	export_ TWO_UI_EXPORT func_ Widget& menu_choice(Widget& parent, cstring content, cstring shortcut = nullptr);
	export_ TWO_UI_EXPORT func_ Widget& menu_option(Widget& parent, cstring content, cstring shortcut, bool enabled);
	export_ TWO_UI_EXPORT func_ Widget& menu(Widget& parent, cstring label, bool submenu = false);
	export_ TWO_UI_EXPORT func_ Widget& menubar(Widget& parent);

	export_ TWO_UI_EXPORT func_ Widget& toolbutton(Widget& parent, cstring icon);
	export_ TWO_UI_EXPORT func_ Widget& tooldock(Widget& parent);
	export_ TWO_UI_EXPORT func_ Widget& toolbar(Widget& parent, bool wrap = false);
}
}



namespace two
{
	export_ struct TWO_UI_EXPORT Styles
	{
		void setup(UiWindow& window);
		void reset();

		Style widget; Style wedge; Style ui; Style unit; Style item; Style control; Style wrap_control; Style spacer; Style separator; Style filler; Style drag_handle;
		Style div; Style row; Style stack; Style sheet; Style flex; Style list; Style header; Style board; Style layout; Style indent;
		Style screen; Style decal; Style overlay; Style gridsheet; Style sequence; Style element;
		Style label; Style title; Style message; Style text; Style bullet; Style button; Style wrap_button; Style multi_button; Style toggle; Style checkbox; Style checkmark;
		Style dummy; Style tooltip; Style rectangle; Style viewport; Style type_in; Style text_edit; Style type_zone; Style caret; Style image; Style image_stretch;
		Style radio_switch; Style radio_switch_h; Style radio_choice; Style radio_choice_item;
		Style slider; Style slider_knob; Style slider_display; Style fill_bar; Style number_input;
		Style slider_input; Style field_input; Style curve_graph; Style curve_input; Style input_bool; Style input_string; Style input_color;
		Style color_wheel; Style color_slab; Style color_display; Style color_toggle;
		Style scrollsheet; Style scroll_zone; Style scroll_surface; Style scroll_plan; Style table; Style table_head; Style column_header;
		Style popup; Style modal; Style color_popup;
	};

	export_ TWO_UI_EXPORT Styles& styles();

	extern map<string, Style*> g_styles;
}

namespace two
{
namespace ui
{
	export_ struct DragPoint
	{
		Frame* prev = nullptr;
		Frame* next = nullptr;
	};

	export_ func_ inline Widget& row(Widget& parent) { return widget(parent, styles().row); }
	export_ func_ inline Widget& header(Widget& parent) { return widget(parent, styles().header); }
	export_ func_ inline Widget& div(Widget& parent) { return widget(parent, styles().div); }
	export_ func_ inline Widget& stack(Widget& parent) { return widget(parent, styles().stack); }
	export_ func_ inline Widget& sheet(Widget& parent) { return widget(parent, styles().sheet); }
	export_ func_ inline Widget& board(Widget& parent) { return widget(parent, styles().board); }
	export_ func_ inline Widget& layout(Widget& parent) { return widget(parent, styles().layout); }
	export_ func_ inline Widget& indent(Widget& parent) { return widget(parent, styles().indent); }
	export_ func_ inline Widget& screen(Widget& parent) { return widget(parent, styles().screen); }
	export_ func_ inline Widget& decal(Widget& parent) { return widget(parent, styles().decal); }
	export_ func_ inline Widget& overlay(Widget& parent) { return widget(parent, styles().overlay); }

	export_ func_ inline Widget& title_header(Widget& parent, cstring title)
	{
		Widget& self = ui::header(parent);
		ui::label(self, title);
		return self;
	}

	export_ TWO_UI_EXPORT func_ Widget& dummy(Widget& parent, const vec2& size);

	export_ TWO_UI_EXPORT Widget& layout_span(Widget& parent, float span);

	export_ TWO_UI_EXPORT Widget& popup(Widget& parent, Style& style, PopupFlags flags);
	export_ TWO_UI_EXPORT Widget& popup(Widget& parent, Style& style, const vec2& size, PopupFlags flags);
	export_ TWO_UI_EXPORT Widget& popup_at(Widget& parent, Style& style, const vec2& position, PopupFlags flags);

	export_ func_ inline Widget& popup(Widget& parent, PopupFlags flags) { return popup(parent, styles().popup, flags); }
	export_ func_ inline Widget& popup(Widget& parent, const vec2& size, PopupFlags flags = PopupFlags::None) { return popup(parent, styles().popup, size, flags); }
	export_ func_ inline Widget& popup_at(Widget& parent, const vec2& position, PopupFlags flags = PopupFlags::None) { return popup_at(parent, styles().popup, position, flags); }

	export_ func_ inline Widget& modal(Widget& parent) { return popup(parent, styles().modal, PopupFlags::Modal); }
	export_ func_ inline Widget& modal(Widget& parent, const vec2& size) { return popup(parent, styles().modal, size, PopupFlags::Modal); }

	export_ func_ TWO_UI_EXPORT Widget& auto_modal(Widget& parent, uint32_t mode);
	export_ func_ TWO_UI_EXPORT Widget& auto_modal(Widget& parent, uint32_t mode, const vec2& size);

	export_ func_ TWO_UI_EXPORT Widget* context(Widget& parent, uint32_t mode, PopupFlags flags = PopupFlags::None);

	export_ TWO_UI_EXPORT DragPoint grid_sheet_logic(Widget& self, Axis dim);
	export_ TWO_UI_EXPORT Widget& grid_sheet(Widget& parent, Style& style, Axis dim);
	export_ TWO_UI_EXPORT Widget& grid_sheet(Widget& parent, Style& style, Axis dim, span<float> spans);
}
}

namespace two
{
namespace ui
{
	export_ struct DockStyles
	{
		void reset();
		Style docktab; Style placeholder; Style docksection; Style dockline; Style dockspace; Style docktoggle; Style dockdiv; Style docktabs; Style dockbar;
		//Style dockdiv; Style dockbox;
	};

	export_ TWO_UI_EXPORT DockStyles& dock_styles();

	export_ TWO_UI_EXPORT Widget& dockline(Widget& parent, uint16_t index, Axis dim);
	export_ TWO_UI_EXPORT Tabber& docksection(Widget& parent);

	export_ TWO_UI_EXPORT func_ Dockspace& dockspace(Widget& parent, Docksystem& docksystem);
	export_ TWO_UI_EXPORT func_ Dockbar& dockbar(Widget& parent, Docksystem& docksystem);

	export_ TWO_UI_EXPORT func_ Widget* dockitem(Widget& parent, Docksystem& docksystem, Dock& dock);

	export_ TWO_UI_EXPORT Widget* dockitem(Docker& docker, cstring name, span<uint16_t> dockid = {}, float span = 0.f);
}
}







namespace two
{
namespace ui
{
	export_ struct TWO_UI_EXPORT SliderState
	{
		float m_pre_span;
		float m_knob_span;
		float m_post_span;
	};

	export_ struct TWO_UI_EXPORT SliderMetrics
	{
		SliderMetrics(float min, float max, float step_length = 1.f, float knob_length = 0.f);

		float m_min;
		float m_max;
		float m_range;
		float m_step_length;
		float m_knob_length;

		float m_num_steps;

		float offset(float cursor) const;
		float cursor(float value, float cursor) const;

		SliderState compute(float value);
	};

	export_ TWO_UI_EXPORT bool slider(Widget& parent, Style& style, float& value, SliderMetrics metrics, Axis dim = Axis::X, bool relative = false, bool fill = true, Style* knob_style = nullptr);
	export_ TWO_UI_EXPORT bool slider(Widget& parent, float& value, SliderMetrics metrics, Axis dim = Axis::X, bool relative = false, bool fill = true, Style* knob_style = nullptr);
}
}

namespace two
{
namespace ui
{
	export_ struct ScrollbarStyles
	{
		void reset();
		Style scrollbar; Style scroll_up; Style scroll_down; Style scroll_left; Style scroll_right; Style scroller; Style scroller_knob;
	};

	export_ TWO_UI_EXPORT ScrollbarStyles& scrollbar_styles();

	export_ TWO_UI_EXPORT bool overflow(Frame& frame, Frame& content, Axis dim);
	export_ TWO_UI_EXPORT Widget& scrollbar(Widget& parent, Frame& frame, Frame& content, Axis dim, v2<uint> grid_index = { 0, 0 });
}
}

namespace two
{
namespace ui
{
	export_ TWO_UI_EXPORT void draw_grid(const Frame& frame, const vec4& rect, Vg& vg);

	export_ TWO_UI_EXPORT func_ ScrollSheet& scroll_sheet(Widget& parent, Style& style = styles().scrollsheet, Style* surface_style = nullptr);
	export_ TWO_UI_EXPORT func_ ScrollSheet& scroll_plan(Widget& parent, Style& style = styles().scrollsheet);

	export_ TWO_UI_EXPORT func_ Widget& scrollable(Widget& parent);

	export_ TWO_UI_EXPORT void autofit_scroll_plan(ScrollSheet& scroll_sheet, span<Widget*> elements);
}
}



namespace two
{
namespace ui
{
	export_ struct CursorStyles
	{
		void reset();
		Style cursor; Style resize_x; Style resize_y; Style move; Style resize_diag_left; Style resize_diag_right; Style caret;
	};

	export_ TWO_UI_EXPORT CursorStyles& cursor_styles();

	export_ TWO_UI_EXPORT Widget* hoverbox(Widget& parent, const vec2& position, float delay = 0.5f);
	export_ TWO_UI_EXPORT func_ Widget* hoverbox(Widget& parent, float delay = 0.5f);

	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, const vec2& position, span<cstring> elements);

	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, cstring content);
	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, span<cstring> elements);

	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, const Frame& parent_frame);
	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, const Frame& parent_frame, cstring content);
	export_ TWO_UI_EXPORT Widget* tooltip(Widget& parent, const Frame& parent_frame, span<cstring> elements);

	export_ TWO_UI_EXPORT Widget& cursor(Widget& parent, const vec2& position, Style& style, bool locked = false);
	export_ TWO_UI_EXPORT func_ Widget& cursor(Widget& parent, const vec2& position, Widget& hovered, bool locked = false);

	export_ TWO_UI_EXPORT func_ Widget& rectangle(Widget& parent, const vec4& rect);
	export_ TWO_UI_EXPORT func_ Widget& viewport(Widget& parent, const vec4& rect);
}
}



namespace two
{
namespace ui
{
	export_ template <class T>
	bool slider_input(Widget& parent, T& value, StatDef<T> def = {}, Axis dim = Axis::X);

	export_ template <class T>
	bool number_type_in(Widget& parent, T& value);

	export_ template <class T>
	bool number_input(Widget& parent, T& value, StatDef<T> def = {});

	export_ template <class T>
	bool drag_input(Widget& parent, T& value, StatDef<T> def = {}) { return number_input<T>(parent, value, def); }

	export_ TWO_UI_EXPORT func_ bool drag_float(Widget& parent, float& value, float step = 0.1f);
	
	export_ template <class T>
	enable_if<!is_number<T>, bool> input(Widget& parent, T& value);

	export_ template <class T>
	enable_if<is_number<T>, bool> input(Widget& parent, T& value, StatDef<T> def = {});

	export_ TWO_UI_EXPORT func_ bool float2_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });
	export_ TWO_UI_EXPORT func_ bool float3_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });
	export_ TWO_UI_EXPORT func_ bool float4_input(Widget& parent, span<cstring> labels, span<float> vals, StatDef<float> def = { limits<float>::min(), limits<float>::max(), 0.01f });

	//export_ TWO_UI_EXPORT func_ bool float2_slider(Widget& parent, span<cstring> labels, span<float> vals);
	//export_ TWO_UI_EXPORT func_ bool float3_slider(Widget& parent, span<cstring> labels, span<float> vals);
	//export_ TWO_UI_EXPORT func_ bool float4_slider(Widget& parent, span<cstring> labels, span<float> vals);

	export_ TWO_UI_EXPORT func_ bool float2_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);
	export_ TWO_UI_EXPORT func_ bool float3_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);
	export_ TWO_UI_EXPORT func_ bool float4_slider(Widget& parent, cstring label, span<cstring> labels, span<float> vals, StatDef<float> def);

	export_ TWO_UI_EXPORT func_ bool vec2_edit(Widget& parent, vec2& vec);
	export_ TWO_UI_EXPORT func_ bool vec3_edit(Widget& parent, vec3& vec);
	export_ TWO_UI_EXPORT func_ bool quat_edit(Widget& parent, quat& quat);

	export_ TWO_UI_EXPORT Widget& color_slab(Widget& parent, Style& style, const Colour& value);
	export_ TWO_UI_EXPORT bool color_edit_hsl(Widget& parent, const Colour& colour, ColourHSL& value);
	export_ TWO_UI_EXPORT func_ Widget& color_display(Widget& parent, const Colour& value);
	export_ TWO_UI_EXPORT func_ bool color_edit(Widget& parent, Colour& value);
	export_ TWO_UI_EXPORT func_ bool color_edit_simple(Widget& parent, Colour& value);
	export_ TWO_UI_EXPORT func_ bool color_toggle_edit(Widget& parent, Colour& value);

	export_ TWO_UI_EXPORT func_ bool curve_graph(Widget& parent, span<float> values, span<float> points = {});

	export_ TWO_UI_EXPORT func_ bool curve_edit(Widget& parent, span<float> values, span<float> points = {});

	export_ TWO_UI_EXPORT bool curve_edit(Widget& parent, span<Colour> values, span<float> points = {});

	export_ TWO_UI_EXPORT bool flag_input(Widget& parent, uint32_t& value, uint8_t shift);

	export_ template <class T_Input>
	bool do_field(T_Input input, Widget& parent, cstring name, bool reverse)
	{
		Widget& self = row(parent);
		if(!reverse) label(self, name);
		bool changed = input(self);
		if(reverse) label(self, name);
		return changed;
	}

	export_ template <class T>
	inline enable_if<!is_number<T>, bool> field(Widget& parent, cstring name, T& value, bool reverse = false) { return do_field([&](Widget& self) { return input<T>(self, value); }, parent, name, reverse); }

	export_ template <class T>
	inline enable_if<is_number<T>, bool> field(Widget& parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field([&](Widget& self) { return number_input<T>(self, value, def); }, parent, name, reverse); }
	
	export_ template <class T>
	inline bool drag_field(Widget& parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field([&](Widget& self) { return drag_input<T>(self, value, def); }, parent, name, reverse); }

	export_ template <class T>
	inline bool slider_field(Widget& parent, cstring name, T& value, StatDef<T> def = {}, bool reverse = false) { return do_field([&](Widget& self) { return slider_input<T>(self, value, def); }, parent, name, reverse); }

	export_ func_ inline bool flag_field(Widget& parent, cstring name, uint32_t& value, uint8_t shift, bool reverse = false) { return do_field([&](Widget& self) { return flag_input(self, value, shift); }, parent, name, reverse); }
	export_ func_ inline bool radio_field(Widget& parent, cstring name, span<cstring> choices, uint32_t& value, Axis dim = Axis::X, bool reverse = false) { return do_field([&](Widget& self) { return radio_switch(self, choices, value, dim); }, parent, name, reverse); }
	export_ func_ inline bool dropdown_field(Widget& parent, cstring name, span<cstring> choices, uint32_t& value, bool reverse = false) { return do_field([&](Widget& self) { return dropdown_input(self, choices, value); }, parent, name, reverse); }
	export_ func_ inline bool typedown_field(Widget& parent, cstring name, span<cstring> choices, uint32_t& value, bool reverse = false) { return do_field([&](Widget& self) { return typedown_input(self, choices, value); }, parent, name, reverse); }
	export_ func_ inline bool color_field(Widget& parent, cstring name, Colour& value, bool reverse = false) { return do_field([&](Widget& self) { return color_toggle_edit(self, value); }, parent, name, reverse); }
	export_ func_ inline void color_display_field(Widget& parent, cstring name, const Colour& value, bool reverse = false) { do_field([&](Widget& self) { color_display(self, value); return false; }, parent, name, reverse); }

	export_ template <> func_ bool input<bool>(Widget& parent, bool& value);
	export_ template <> func_ bool input<string>(Widget& parent, string& value);

#ifndef TWO_META_GENERATOR
	export_ func_ extern template bool input<int>(Widget& parent, int& value, StatDef<int> def);
	export_ func_ extern template bool input<float>(Widget& parent, float& value, StatDef<float> def);

	//export_ func_ template bool field<bool>(Widget& parent, cstring name, bool& value, bool reverse);
	//export_ func_ template bool field<string>(Widget& parent, cstring name, string& value, bool reverse);
	//export_ func_ template bool field<int>(Widget& parent, cstring name, int& value, StatDef<int> def, bool reverse);
	//export_ func_ template bool field<float>(Widget& parent, cstring name, float& value, StatDef<float> def, bool reverse);
#else
	template <> func_ bool input<int>(Widget& parent, int& value, StatDef<int> def);
	template <> func_ bool input<float>(Widget& parent, float& value, StatDef<float> def);

	template <> func_ bool field<bool>(Widget& parent, cstring name, bool& value, bool reverse = false);
	template <> func_ bool field<string>(Widget& parent, cstring name, string& value, bool reverse = false);
	template <> func_ bool field<int>(Widget& parent, cstring name, int& value, StatDef<int> def, bool reverse = false);
	template <> func_ bool field<float>(Widget& parent, cstring name, float& value, StatDef<float> def, bool reverse = false
#endif

	export_ inline void field_label(Widget& parent, cstring field, cstring value)
	{
		Widget& self = row(parent);
		label(self, field);
		label(self, value);
	}
}
}





namespace two
{
	enum class CodePalette : unsigned char
	{
		Word = Text::Palette::Count,
		Keyword,
		Number,
		String,
		CharLiteral,
		Punctuation,
		Operator,
		Preprocessor,
		Variable,
		Identifier,
		Function,
		Parameter,
		Field,
		PreprocIdentifier,
		Comment,
		Error,
		ErrorMarker,
		Breakpoint,
		Count
	};

	enum class TextFocusMode : unsigned int
	{
		Press,
		Click
	};

	export_ class refl_ TWO_UI_EXPORT TextEdit : public Widget
	{
	public:
		class Action
		{
		public:
			void Undo(TextEdit* aEditor);
			void Redo(TextEdit* aEditor);

			string mAdded;
			size_t mAddedStart;
			size_t mAddedEnd;

			string mRemoved;
			size_t mRemovedStart;
			size_t mRemovedEnd;

			TextSelection mBefore;
			TextSelection mAfter;
		};

		using Callback = string(*)(const string&);

	public:
		TextEdit(Widget* parent, void* identity, bool editor, string allowed_chars);
		~TextEdit();

		bool m_editor;
		Text m_text;
		TextSelection m_selection;
		string& m_string;

		bool m_changed = false;
		bool m_entered = false;

		void update_style();
		vec2 frame_size();

		void update();
		void update_scroll(Frame& frame, Frame& content);
		void render(Vg& vg);

		void set_text(const string& text);

		void erase(size_t start, size_t end);
		void erase(size_t start, size_t end, size_t cursor, Action& action);

		void insert(size_t index, const string& text);
		void insert(size_t index, const string& text, size_t cursor, Action& action);

		void erase_selected(Action& action);

		void enter();
		void escape();
		void erase();
		void backspace();
		void insert(unsigned char c);
		void insert(const string& text);

		void copy();
		void cut();
		void paste();

		void undo();
		void redo();

		void changed();

		size_t visible_lines() const;

		bool has_selection() const { return m_selection.m_end > m_selection.m_start; }

		string selected_text() const;

		void cursor(size_t index, bool word_mode = false);
		void select(size_t first, size_t second, bool word_mode = false);

		void move_select(TextCursor dest, bool select, bool word_mode = false);

		void select_none();
		void select_all();
		void select_word();

		void scroll_to_cursor(Frame& frame, Frame& content);

		void move_right(size_t count, bool select = false, bool word_mode = false);
		void move_left(size_t count, bool select = false, bool word_mode = false);
		void move_up(bool select = false);
		void move_down(bool select = false);
		void move_page_up(bool select = false);
		void move_page_down(bool select = false);
		void move_top(bool select = false);
		void move_bottom(bool select = false);
		void move_home(bool select = false);
		void move_end(bool select = false);

		bool allowed(char c) { return m_allowed_chars.empty() || m_allowed_chars.find(c) != string::npos; }

		void clear(size_t start, size_t end);
		void shift(size_t start, int offset);

		void recolorize();
		void colorize(size_t start, size_t end);
		void mark_dirty(size_t start, size_t end);

		uvec2 m_dirty;

		template <class T_Func>
		void CommitAction(T_Func func)
		{
			Action action;
			action.mBefore = m_selection;

			func(action);

			action.mAfter = m_selection;
			AddUndo(action);
		}

	public:
		TextFocusMode m_focus_mode = TextFocusMode::Press;
		bool m_read_only = false;
		string m_allowed_chars;

		TextCursor m_select_from;

		vec2 m_text_offset;

		string m_hovered_word = "";
		vec4 m_hovered_word_rect = vec4(0.f);

		using AllowChar = bool(*)(char); AllowChar m_allow_char;

		int m_tab_size = 4;
		bool m_completing = false;
		bool m_follow_cursor = false;
		bool m_word_selection_mode = false;

		ColourPalette m_palette;

		static vector<uint32_t>& DarkPalette();
		static vector<uint32_t>& OkaidaPalette();

	public:
		bool CanUndo() const { return m_undo_index > 0; }
		bool CanRedo() const { return m_undo_index < (int)m_undo_stack.size(); }

	public:
		void AddUndo(Action& aValue);
		
		vector<Action> m_undo_stack;
		int m_undo_index = 0;

		LanguageDefinition* m_language = nullptr;
	};

namespace ui
{
	TWO_UI_EXPORT bool filter(const string& filter, const string& value);

	export_ TWO_UI_EXPORT func_ TextEdit& text_box(Widget& parent, Style& style, string& text, bool editor = false, size_t lines = 1, const string& allowed_chars = "");
	export_ TWO_UI_EXPORT func_ TextEdit& type_in(Widget& parent, string& text, size_t lines = 1, const string& allowed_chars = "");
	export_ TWO_UI_EXPORT func_ TextEdit& text_edit(Widget& parent, string& text, size_t lines = 1, vector<string>* vocabulary = nullptr);
	export_ TWO_UI_EXPORT func_ TextEdit& code_edit(Widget& parent, string& text, size_t lines = 1, vector<string>* vocabulary = nullptr);

	export_ TWO_UI_EXPORT string auto_indent(TextEdit& edit);
}
}

namespace two
{
namespace ui
{
	export_ template <class T>
	bool slider_input(Widget& parent, T& value, StatDef<T> def, Axis dim)
	{
		Widget& self = widget(parent, styles().slider_input);
		const SliderMetrics metrics = { float(def.m_min), float(def.m_max), float(def.m_step) };
		float slider_value = float(value);
		const bool changed = slider(self, slider_value, metrics, dim);
		value = T(slider_value);
		item(self, styles().slider_display, truncate_number(to_string(slider_value)));
		return changed;
	}

	export_ template <class T>
	bool number_type_in(Widget& parent, T& value)
	{
		string text = truncate_number(to_string(value));
		TextEdit& self = type_in(parent, text, 0, is_float<T> ? "1234567890." : "1234567890");
		if(self.m_changed)
		{
			value = to_value<T>(text);
			return true;
		}
		return false;
	}

	export_ template <class T>
	bool number_input(Widget& parent, T& value, StatDef<T> def)
	{
		Widget& self = widget(parent, styles().number_input);
		bool changed = false;

		changed |= number_type_in<T>(self, value);
		if(button(self, "+").activated())
		{
			changed = true;
			def.increment(value);
		}
		if(button(self, "-").activated())
		{
			changed |= true;
			def.decrement(value);
		}

		return changed;
	}

	export_ template <>
	inline bool number_input(Widget& parent, float& value, StatDef<float> def)
	{
		return drag_float(parent, value, def.m_step);
	}

	export_ template <class T>
	inline enable_if<is_number<T>, bool> input(Widget& parent, T& value, StatDef<T> def)
	{
		return number_input(parent, value, def);
	}

	export_ template <>
	inline bool input(Widget& parent, bool& value)
	{
		Widget& self = widget(parent, styles().input_bool);
		return checkbox(self, value).activated();
	}

	export_ template <>
	inline bool input(Widget& parent, string& value)
	{
		Widget& self = widget(parent, styles().input_string);
		return text_box(self, styles().type_in, value, false, 1).m_changed;
	}

	export_ template <>
	inline bool input(Widget& parent, vec3& value) { return vec3_edit(parent, value); }

	export_ template <>
	inline bool input(Widget& parent, quat& value) { return quat_edit(parent, value); }

	export_ template <>
	inline bool input(Widget& parent, Colour& value) { return color_toggle_edit(parent, value); }
}
}



namespace two
{
	export_ struct refl_ TWO_UI_EXPORT NodeConnection
	{
		uint32_t m_out_node = UINT32_MAX;
		uint32_t m_out_plug;

		uint32_t m_in_node;
		uint32_t m_in_plug;

		bool valid() { return m_out_node != UINT32_MAX; }
	};

namespace ui
{
	export_ struct NodeStyles
	{
		void reset();
		Style node; Style body; Style plugs; Style inputs; Style outputs; Style knob; Style knob_output; Style knob_proxy; Style plug; Style cable; Style header;
	};

	export_ TWO_UI_EXPORT NodeStyles& node_styles();

	export_ struct CanvasStyles
	{
		void reset();
		Style canvas;
	};

	export_ TWO_UI_EXPORT CanvasStyles& canvas_styles();

	export_ TWO_UI_EXPORT NodePlug& node_plug(Node& node, cstring name, cstring icon, const Colour& colour, bool input, bool active, bool connected);
	
	export_ func_ inline NodePlug& node_input(Node& node, cstring name, cstring icon = "", const Colour& colour = Colour::NeonGreen, bool active = true, bool connected = false)
	{
		return node_plug(node, name, icon, colour, true, active, connected);
	}

	export_ func_ inline NodePlug& node_output(Node& node, cstring name, cstring icon = "", const Colour& colour = Colour::NeonGreen, bool active = true, bool connected = false)
	{
		return node_plug(node, name, icon, colour, false, active, connected);
	}

	export_ TWO_UI_EXPORT Node& node(Canvas& parent, span<cstring> title, int order = 0, Ref identity = {});
	export_ TWO_UI_EXPORT Node& node(Canvas& parent, span<cstring> title, float* position, int order = 0, Ref identity = {});
	export_ TWO_UI_EXPORT Node& node(Canvas& parent, span<cstring> title, vec2& position, int order = 0, Ref identity = {});
	export_ TWO_UI_EXPORT func_ Node& node(Canvas& parent, cstring title, vec2& position, int order = 0, Ref identity = {});

	export_ TWO_UI_EXPORT func_ Widget& node_cable(Canvas& canvas, NodePlug& plug_out, NodePlug& plug_in);

	export_ TWO_UI_EXPORT func_ Canvas& canvas(Widget& parent, size_t num_nodes = 0);
	export_ TWO_UI_EXPORT NodeConnection canvas_connect(Canvas& canvas);
	export_ TWO_UI_EXPORT void canvas_autolayout(Canvas& canvas);
}
}



namespace two
{
	export_ struct TWO_UI_EXPORT Section : public Widget
	{
		Section(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_toolbar = nullptr;
	};

	export_ TWO_UI_EXPORT Section& section(Widget& parent, const string& name, bool no_toolbar = false);
	export_ TWO_UI_EXPORT bool section_action(Section& parent, const string& name);
}



namespace two
{
namespace ui
{
	export_ TWO_UI_EXPORT func_ Sequence& sequence(Widget& parent);
	export_ TWO_UI_EXPORT func_ Sequence& scroll_sequence(Widget& parent);

	export_ TWO_UI_EXPORT func_ bool multiselect_logic(Widget& element, Ref object, vector<Ref>& selection);
	export_ TWO_UI_EXPORT func_ bool select_logic(Widget& element, Ref object, Ref& selection);

	export_ TWO_UI_EXPORT func_ Widget& element(Widget& parent, Ref object);
	export_ TWO_UI_EXPORT Widget& element(Widget& parent, Ref object, vector<Ref>& selection);

	export_ TWO_UI_EXPORT func_ Widget& sequence_element(Sequence& parent, Ref object);
}
}


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
    // Exported types
    export_ template <> TWO_UI_EXPORT Type& type<two::FlowAxis>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Pivot>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Align>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Solver>();
    export_ template <> TWO_UI_EXPORT Type& type<two::AutoLayout>();
    export_ template <> TWO_UI_EXPORT Type& type<two::LayoutFlow>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Sizing>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Preset>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Clip>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Opacity>();
    export_ template <> TWO_UI_EXPORT Type& type<two::WidgetState>();
    export_ template <> TWO_UI_EXPORT Type& type<two::ui::PopupFlags>();
    export_ template <> TWO_UI_EXPORT Type& type<two::WindowState>();
    
    export_ template <> TWO_UI_EXPORT Type& type<stl::span<const char*>>();
    export_ template <> TWO_UI_EXPORT Type& type<stl::vector<two::Space>>();
    export_ template <> TWO_UI_EXPORT Type& type<stl::vector<two::Subskin>>();
    
    export_ template <> TWO_UI_EXPORT Type& type<two::Space>();
    export_ template <> TWO_UI_EXPORT Type& type<two::v2<two::AutoLayout>>();
    export_ template <> TWO_UI_EXPORT Type& type<two::v2<two::Sizing>>();
    export_ template <> TWO_UI_EXPORT Type& type<two::v2<two::Align>>();
    export_ template <> TWO_UI_EXPORT Type& type<two::v2<two::Pivot>>();
    export_ template <> TWO_UI_EXPORT Type& type<two::ImageSkin>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Shadow>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Paint>();
    export_ template <> TWO_UI_EXPORT Type& type<two::TextPaint>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Gradient>();
    export_ template <> TWO_UI_EXPORT Type& type<two::InkStyle>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Layout>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Subskin>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Style>();
    export_ template <> TWO_UI_EXPORT Type& type<two::UiRect>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Frame>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Widget>();
    export_ template <> TWO_UI_EXPORT Type& type<two::TextCursor>();
    export_ template <> TWO_UI_EXPORT Type& type<two::TextSelection>();
    export_ template <> TWO_UI_EXPORT Type& type<two::TextMarker>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Text>();
    export_ template <> TWO_UI_EXPORT Type& type<two::TextEdit>();
    export_ template <> TWO_UI_EXPORT Type& type<two::NodeConnection>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Vg>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Clipboard>();
    export_ template <> TWO_UI_EXPORT Type& type<two::UiWindow>();
    export_ template <> TWO_UI_EXPORT Type& type<two::User>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Layer>();
    export_ template <> TWO_UI_EXPORT Type& type<two::FrameSolver>();
    export_ template <> TWO_UI_EXPORT Type& type<two::RowSolver>();
    export_ template <> TWO_UI_EXPORT Type& type<two::TableSolver>();
    export_ template <> TWO_UI_EXPORT Type& type<two::LineSolver>();
    export_ template <> TWO_UI_EXPORT Type& type<two::GridSolver>();
    export_ template <> TWO_UI_EXPORT Type& type<two::ScrollSheet>();
    export_ template <> TWO_UI_EXPORT Type& type<two::ui::Sequence>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Tabber>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Expandbox>();
    export_ template <> TWO_UI_EXPORT Type& type<two::TreeNode>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Table>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Dock>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Docksystem>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Dockable>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Docker>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Dockspace>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Dockbar>();
    export_ template <> TWO_UI_EXPORT Type& type<two::NodePlug>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Node>();
    export_ template <> TWO_UI_EXPORT Type& type<two::CanvasConnect>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Canvas>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Ui>();
    export_ template <> TWO_UI_EXPORT Type& type<two::Window>();
}





namespace two
{
	export_ enum class refl_ WindowState : unsigned int
	{
		None = 0,
		Header = 1 << 1,
		Dockable = 1 << 2,
		Closable = 1 << 3,
		Movable = 1 << 4,
		Sizable = 1 << 5,
		Scrollable = 1 << 6,
		Menu = 1 << 7,
		Default = Header | Movable | Sizable | Closable | Scrollable
	};

namespace ui
{
	export_ struct WindowStyles
	{
		void reset();
		Style window; Style body; Style close_button; Style header; Style header_movable; Style footer; Style sizer; Style sizer_left; Style sizer_right;
		Style dock_window; Style wrap_window;
	};

	export_ TWO_UI_EXPORT WindowStyles& window_styles();

	export_ func_ TWO_UI_EXPORT Window& window(Widget& parent, cstring title, WindowState state = WindowState::Default);
	export_ TWO_UI_EXPORT Window& window(Widget& parent, cstring title, WindowState state, void* identity, Dock* dock = nullptr);
}
}



struct dirent;

namespace two
{
namespace ui
{
	export_ struct FileStyles
	{
		void reset();
		Style dir; Style file;
	};

	export_ TWO_UI_EXPORT FileStyles& file_styles();

	export_ TWO_UI_EXPORT func_ Widget& dir_item(Widget& parent, const string& name);
	export_ TWO_UI_EXPORT func_ Widget& file_item(Widget& parent, const string& name);
	export_ TWO_UI_EXPORT func_ Widget& file_list(Widget& parent, string& path);

	export_ TWO_UI_EXPORT func_ Widget& file_browser(Widget& parent, string& path);

	export_ TWO_UI_EXPORT func_ Widget& dir_node(Widget& parent, const string& path, const string& name, bool collapsed);
	export_ TWO_UI_EXPORT func_ Widget& file_node(Widget& parent, const string& name);
	export_ TWO_UI_EXPORT func_ Widget& file_tree(Widget& parent, const string& path);
}
}



namespace two
{
	export_ class refl_ TWO_UI_EXPORT User
	{
	public:
		vector<Ref> m_selection;
	};
}



namespace two
{
	export_ struct TWO_UI_EXPORT KeyCombo
	{
		KeyCombo(Key key) : m_modifier(InputMod::Any), m_key(key) {}
		KeyCombo(InputMod modifier, Key key) : m_modifier(modifier), m_key(key) {}
		InputMod m_modifier;
		Key m_key;
		uint32_t value() const { return uint32_t(m_modifier) << 24 | uint32_t(m_key); }
		explicit operator uint32_t() const { return value(); }
	};

	inline size_t hash(const KeyCombo& value)
	{
		return value.value();
	}

	inline bool operator<(const KeyCombo& lhs, const KeyCombo& rhs) { return lhs.value() < rhs.value(); }
	inline bool operator==(const KeyCombo& lhs, const KeyCombo& rhs) { return lhs.value() == rhs.value(); }

	using KeyHandler = void(*)();

	export_ class TWO_UI_EXPORT EventDispatch
	{
	public:
		EventDispatch();

		virtual void process(Widget& widget);
		
		//EventMap<KeyHandler> m_handlers;

		map<KeyCombo, KeyHandler> m_key_down_handlers;
		map<KeyCombo, KeyHandler> m_key_up_handlers;
	};
}



namespace two
{
namespace ui
{
	export_ TWO_UI_EXPORT func_ Widget& command_line(Widget& parent, string& text, string& command);
	export_ TWO_UI_EXPORT func_ Widget& console(Widget& parent, string& feed, string& line, string& command, size_t num_lines = 0);
}
}



namespace two
{
	struct Identifier
	{
		uvec2 m_location;
		string m_declaration;
	};

	struct LanguageDefinition
	{
		string m_name;
		vector<string> m_punctuation;
		vector<string> m_operators;
		unordered_set<string> m_keywords;
		unordered_map<string, Identifier> m_identifiers;
		unordered_map<string, Identifier> m_functions;
		unordered_map<string, Identifier> m_preproc_identifiers;
		string m_comment_start;
		string m_comment_end;

		struct StringToken { string token; PaletteIndex color; };
		struct RegexToken { std::regex token; PaletteIndex color; };
		vector<StringToken> m_regex_string_tokens;
		vector<RegexToken> m_regex_tokens;

		bool m_case_sensitive;
	};

	export_ LanguageDefinition& LanguageCpp();
	export_ LanguageDefinition& LanguageHLSL();
	export_ LanguageDefinition& LanguageGLSL();
	export_ LanguageDefinition& LanguageC();
	export_ LanguageDefinition& LanguageLua();
	export_ LanguageDefinition& LanguageWren();
}



namespace two
{
	export_ class refl_ TWO_UI_EXPORT Layer
	{
	public:
		Layer(Frame& frame);
		~Layer();

		enum Redraw
		{
			NO_REDRAW = 0,
			REDRAW = 1,
			FORCE_REDRAW = 2
		};

		size_t z() const;

		bool master() { return d_parentLayer == nullptr; }
		bool redraw() const { return d_redraw >= REDRAW; }
		bool forceRedraw() const { return d_redraw >= FORCE_REDRAW; }

		void setRedraw() { if(d_redraw < REDRAW) d_redraw = REDRAW; }
		void setForceRedraw() { d_redraw = FORCE_REDRAW; }

		void endRedraw() { d_redraw = NO_REDRAW; }

		void addLayer(Layer& layer);
		void removeLayer(Layer& layer);

		void moveToTop();

		void reindex();
		void reorder();

		template <class Visitor>
		void visit(const Visitor& visitor)
		{
			visitor(*this);
			for(Layer* layer : d_sublayers)
				layer->visit(visitor);
		}

	public:
		Frame& m_frame;
		Layer* d_parentLayer = nullptr;
		size_t d_index = SIZE_MAX;
		size_t d_z = 0;

		Redraw d_redraw = REDRAW;
		size_t d_handle = SIZE_MAX;

		vector<Layer*> d_sublayers;
	};
}



namespace two
{
	using SolverVector = vector<FrameSolver*>;

	void collect_solvers(Frame& frame, SolverVector& solvers, DirtyLayout dirtyTop);
	void relayout(SolverVector& solvers);

	export_ class refl_ TWO_UI_EXPORT FrameSolver : public UiRect
	{
	public:
		FrameSolver();
		FrameSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);
		virtual ~FrameSolver() {}

		inline bool flow() { return d_layout->m_flow == LayoutFlow::Flow; }
		inline bool posflow() { return d_layout->m_flow <= LayoutFlow::Align; }
		inline bool sizeflow() { return d_layout->m_flow <= LayoutFlow::Overlay; }

		inline float dpadding(Axis dim) { return d_layout->m_padding[size_t(dim)]; }
		inline float dbackpadding(Axis dim) { return d_layout->m_padding[size_t(dim) + 2]; }
		inline float dmargin(Axis dim) { return d_layout->m_margin[dim]; }

		inline Align dalign(Axis dim) { return d_layout->m_align[dim]; }

		inline float dcontent(Axis dim) { return d_content[dim] + dpadding(dim) + dbackpadding(dim); }
		inline float dbounds(Axis dim) { return dcontent(dim) + dmargin(dim) * 2.f; }

		inline float dextent(Axis dim) { return m_size[dim] + dmargin(dim) * 2.f; }
		inline float doffset(Axis dim) { return m_position[dim] + m_size[dim] + dmargin(dim); }
		inline float dspace(Axis dim) { return m_size[dim] - dpadding(dim) - dbackpadding(dim); }

		//inline float spacing(FrameSolver& frame) { return d_prev ? d_layout->m_spacing[d_length] : 0.f; }
		inline float spacing() { return d_layout->m_spacing[d_length]; }

		void setup(const vec2& position, const vec2& size, const vec2& span, const vec2* content)
		{
			m_position = position;
			m_span = span;
			m_size = size;

			if(d_sizing.x == Sizing::Fixed) d_content.x = (content ? content->x : m_size.x - dpadding(Axis::X) - dbackpadding(Axis::X));
			if(d_sizing.y == Sizing::Fixed) d_content.y = (content ? content->y : m_size.y - dpadding(Axis::Y) - dbackpadding(Axis::Y));
			if(d_sizing.x == Sizing::Fixed) m_size.x = d_content.x + dpadding(Axis::X) + dbackpadding(Axis::X);
			if(d_sizing.y == Sizing::Fixed) m_size.y = d_content.y + dpadding(Axis::Y) + dbackpadding(Axis::Y);
		}

		void reset(bool partial = false)
		{
			m_size = { 0.f, 0.f };
			if(!partial)
				d_content = { 0.f, 0.f };
			d_spacing = { 0.f, 0.f };
			m_space_content = { 0.f, 0.f };
			d_content_expand = false;
			d_total_span = 0.f;
			d_prev = nullptr;
			d_count = 0;
		}

		void applySpace(Axis length = Axis::None);

		virtual void collect(SolverVector& solvers);

		virtual FrameSolver& solver(FrameSolver& frame, Axis dim);
		virtual FrameSolver* grid() { return nullptr; }

		void sync();
		void compute();
		void layout();
		void read();

		virtual void compute(FrameSolver& frame, Axis dim);
		virtual void layout(FrameSolver& frame, Axis dim);

	public:
		Frame* d_frame;
		FrameSolver* d_parent;
		Layout* d_layout;

		table<Axis, FrameSolver*> m_solvers;
		//FrameSolver* m_solvers[2];
		FrameSolver* d_grid;

		Axis d_length = Axis::None;
		Axis d_depth = Axis::None;

		v2<Sizing> d_sizing = { Sizing::Shrink, Sizing::Shrink };

		vec2 d_content = { 0.f, 0.f };
		vec2 d_spacing = { 0.f, 0.f };
		vec2 m_space_content = { 0.f, 0.f };
		bool d_content_expand = false;
		float d_total_span;

		v2<uint> d_index;

		FrameSolver* d_prev = nullptr;
		size_t d_count = 0;
	};

	export_ class refl_ TWO_UI_EXPORT RowSolver : public FrameSolver
	{
	public:
		RowSolver();
		RowSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		virtual void compute(FrameSolver& frame, Axis dim);
		virtual void layout(FrameSolver& frame, Axis dim);

	protected:
		void measure(FrameSolver& frame, Axis dim);
		void resize(FrameSolver& frame, Axis dim);
		void position(FrameSolver& frame, Axis dim);

		float positionFree(FrameSolver& frame, Axis dim, float space);
		float positionSequence(FrameSolver& frame, float space);
	};

	export_ class TWO_UI_EXPORT CustomSolver : public RowSolver
	{
	public:
		CustomSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		CustomSolver(const CustomSolver& other) = delete;
		CustomSolver& operator=(const CustomSolver& other) = delete;

		virtual void collect(SolverVector& solvers);

	protected:
		vector<unique<FrameSolver>> m_solvers;
	};

	export_ class refl_ TWO_UI_EXPORT TableSolver : public CustomSolver
	{
	public:
		TableSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		void divide(span<float> spans);
		void update(span<float> spans);

		virtual FrameSolver& solver(FrameSolver& frame, Axis dim);
		virtual FrameSolver* grid() { return this; }
	};

	export_ class refl_ TWO_UI_EXPORT LineSolver : public RowSolver
	{
	public:
		LineSolver(FrameSolver* solver, Space space);
		LineSolver(const LineSolver& other) = delete; // @kludge for clang modules bug
		LineSolver& operator=(const LineSolver& other) = delete;
		
		Layout d_layout;
	};

	export_ class refl_ TWO_UI_EXPORT GridSolver : public CustomSolver
	{
	public:
		GridSolver(FrameSolver* solver, Layout* layout, Frame* frame = nullptr);

		void divide(span<Space> spaces);

		virtual FrameSolver& solver(FrameSolver& frame, Axis dim);
	};
}



namespace two
{
	export_ struct refl_ TWO_UI_EXPORT Dock
	{
		Dock();
		Dock(Docker& docker, cstring name, vector<uint16_t> dockid, float span = 0.f);
		Docker* m_docker = nullptr;
		cstring m_name;
		vector<uint16_t> m_dockid;
		float m_span = 0.f;
	};

	export_ class refl_ TWO_UI_EXPORT Docksystem
	{
	public:
		Docksystem();

		void dock(Dockable& widget, const vec2& pos);

		map<string, Dock> m_docks;
		vector<Docker*> m_dockers;
	};

	export_ class refl_ TWO_UI_EXPORT Dockable : public Widget
	{
	public:
		Dockable(Widget* parent, void* identity);
		Dock* m_dock = nullptr;
	};

	export_ class refl_ TWO_UI_EXPORT Docker : public Widget
	{
	public:
		Docker(Widget* parent, void* identity, Docksystem& docksystem);

		virtual Widget* docksection(Dock& dock) = 0;

		virtual void dock(Dockable& widget, const vec2& pos) = 0;

		void dock_split(Dock& dock, Dock& target, bool after);
		void dock_insert(Dock& dock, Dock& target, bool after);

		void undock(Dockable& dockable);

		void shift(Dock& start, bool add);

		Docksystem* m_docksystem;
		vector<Dock*> m_docks;
	};

	export_ class refl_ TWO_UI_EXPORT Dockspace : public Docker
	{
	public:
		Dockspace(Widget* parent, void* identity, Docksystem& docksystem);
		~Dockspace();

		Dockable& pinpoint_dock(const vec2& pos);

		virtual Widget* docksection(Dock& dock) final;

		virtual void dock(Dockable& widget, const vec2& pos) final;

		void dock(Dock& dock, Dock& target, Frame& frame, const vec2& pos);

		Widget* m_mainline;
	};

	export_ class refl_ TWO_UI_EXPORT Dockbar : public Docker
	{
	public:
		Dockbar(Widget* parent, void* identity, Docksystem& docksystem);

		Widget* m_togglebar = nullptr;
		Widget* m_dockzone = nullptr;

		virtual Widget* docksection(Dock& dock) final;

		virtual void dock(Dockable& widget, const vec2& pos) final;

		float width = 300.f;
		size_t m_current_tab = SIZE_MAX;
	};
}



namespace two
{
	export_ struct NodeKnob
	{
		vec2 m_end;
		Colour m_colour;
	};

	export_ class refl_ TWO_UI_EXPORT NodePlug : public Widget, public NodeKnob
	{
	public:
		NodePlug(Widget* parent, void* identity) : Widget(parent, identity) {}
		Node* m_node;
		Widget* m_knob;
	};

	export_ class refl_ TWO_UI_EXPORT Node : public Widget
	{
	public:
		Node(Widget* parent, void* identity) : Widget(parent, identity) {}
		Canvas* m_canvas;
		Widget* m_header;
		Widget* m_inputs;
		Widget* m_outputs;
		int m_order = 0;
	};

	export_ struct refl_ TWO_UI_EXPORT CanvasConnect
	{
		NodePlug* m_origin = nullptr;
		NodePlug* m_in = nullptr;
		NodePlug* m_out = nullptr;
		NodeKnob m_end;
		vec2 m_position;
		bool m_done = false;
	};

	export_ class refl_ TWO_UI_EXPORT Canvas : public Widget
	{
	public:
		Canvas(Widget* parent, void* identity) : Widget(parent, identity) {}

		ScrollSheet* m_scroll_plan;
		Widget* m_plan;
		bool m_rounded_links = true;

		CanvasConnect m_connect;

		vector<Node*> m_nodes;
		vector<Node*> m_selection;
	};
}



namespace two
{
	enum class DropState : unsigned int
	{
		None,
		Preview,
		Done
	};

	struct DropAction
	{
		DropAction() {}
		DropAction(Widget* target, Ref object, DropState state) : m_target(target), m_object(object), m_state(state) {}
		Widget* m_target = nullptr;
		Ref m_object = {};
		DropState m_state = DropState::None;
	};

	export_ class refl_ TWO_UI_EXPORT Ui : public Widget, public EventDispatcher
	{
	public:
		Ui(UiWindow& window);
		~Ui();

		meth_ Widget& begin();

		void input_frame();
		void render_frame();

		void clear_events();

		meth_ void reset_styles();

	public:
		UiWindow& m_window;
		Keyboard m_keyboard;
		Mouse m_mouse;

		Style* m_cursor_style = nullptr;
		Widget* m_hovered = nullptr;
		DropAction m_drop = {};
		Clock m_tooltip_clock;
	};
}



namespace two
{
	export_ class refl_ TWO_UI_EXPORT Window : public Dockable
	{
	public:
		Window(Widget* parent, void* identity)
			: Dockable(parent, identity)
		{}

		bool header()   { return (uint(m_window_state) & uint(WindowState::Header)) != 0; }
		bool closable() { return (uint(m_window_state) & uint(WindowState::Closable)) != 0; }
		bool dockable() { return (uint(m_window_state) & uint(WindowState::Dockable)) != 0; }
		bool movable()  { return (uint(m_window_state) & uint(WindowState::Movable)) != 0; }
		bool sizable()  { return (uint(m_window_state) & uint(WindowState::Sizable)) != 0; }
		bool hasmenu()  { return (uint(m_window_state) & uint(WindowState::Menu)) != 0; }

		attr_ WindowState m_window_state;

		attr_ Widget* m_menu = nullptr;
	};
}

