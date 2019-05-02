#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <math/Forward.h>
#include <ctx/Forward.h>

#ifndef TWO_UI_EXPORT
#define TWO_UI_EXPORT TWO_IMPORT
#endif

#undef TWO_UI_DRAW_CACHE

namespace two
{
namespace ui
{
    enum class PopupFlags : unsigned int;
    
    
    struct DropdownStyles;
    struct MenuStyles;
    struct ToolbarStyles;
    struct TableStyles;
    struct ExpandboxStyles;
    struct TreeNodeStyles;
    struct TabberStyles;
    struct DragPoint;
    struct CursorStyles;
    struct DockStyles;
    struct SliderState;
    struct SliderMetrics;
    struct NodeStyles;
    struct CanvasStyles;
    struct ScrollbarStyles;
    struct WindowStyles;
    struct FileStyles;
    class Sequence;
}
}

namespace two
{
    enum class Axis : unsigned int;
    enum class FlowAxis : unsigned int;
    enum class Pivot : unsigned int;
    enum class Align : unsigned int;
    enum class Solver : unsigned int;
    enum class AutoLayout : unsigned int;
    enum class LayoutFlow : unsigned int;
    enum class Sizing : unsigned int;
    enum class Preset : unsigned int;
    enum class Clip : unsigned int;
    enum class Opacity : unsigned int;
    enum WidgetState : unsigned int;
    enum DirtyLayout : unsigned int;
    enum class CodePalette : unsigned char;
    enum class TextFocusMode : unsigned int;
    enum class WindowState : unsigned int;
    enum class DropState : unsigned int;
    
    template <class T> struct v2;
    
    class Style;
	struct Subskin;
    struct Space;
    struct Styles;
    struct UiRect;
    class Frame;
    class Widget;
    struct TextGlyph;
    struct TextRow;
    struct Shadow;
    struct Paint;
    struct TextPaint;
	struct TextMarker;
    struct Gradient;
    struct TextCursor;
    struct TextSelection;
    class Text;
    class TextEdit;
	struct Clipboard;
    struct NodeConnection;
    class Vg;
    class UiRenderer;
    class UiWindow;
    class User;
    struct KeyCombo;
    class EventDispatch;
    struct Identifier;
    struct LanguageDefinition;
    class Layer;
    struct Layout;
    class FrameSolver;
    class RowSolver;
    class CustomSolver;
    class TableSolver;
    class LineSolver;
    class GridSolver;
    class ScrollSheet;
    class Tabber;
    class Expandbox;
    class TreeNode;
    class Table;
    struct Dock;
    class Docksystem;
    class Dockable;
    class Docker;
    class Dockspace;
    class Dockbar;
    class NodePlug;
    class Node;
    struct CanvasConnect;
    class Canvas;
    struct DropAction;
    class Ui;
    class Window;
    struct ImageSkin;
    struct InkStyle;
    class Options;
    class Styler;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
#include <stl/span.h>
#include <ui/Style/Style.h>
namespace stl
{
	export_ using cstring = const char*;
	export_ extern template struct refl_ span_ span<float>;
	export_ extern template struct refl_ span_ span<cstring>;

	//export_ extern template class refl_ seque_ vector<string>;
	export_ extern template class refl_ seque_ vector<two::Space>;
	export_ extern template class refl_ seque_ vector<two::Subskin>;
}
#endif
