#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <type/Forward.h>
#include <math/Forward.h>
#include <ctx/Forward.h>
#endif

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
    export_ enum class Axis : unsigned int;
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
    
#ifndef TWO_MODULES
    template <class T> struct v2;
#endif

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
#include <ui/Style/Style.h>
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
