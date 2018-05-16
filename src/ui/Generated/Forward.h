

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <math/Generated/Forward.h>
#include <ctx/Generated/Forward.h>

#if defined MUD_UI_LIB
#define MUD_UI_EXPORT MUD_EXPORT
#else
#define MUD_UI_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace mud {
namespace ui {

    enum PopupFlags : unsigned int;
    
    
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
}
}

namespace glm {

    
    
}

namespace mud {

    enum Dim : unsigned int;
    enum FlowAxis : unsigned int;
    enum Pivot : unsigned int;
    enum Align : unsigned int;
    enum LayoutSolver : unsigned int;
    enum AutoLayout : unsigned int;
    enum Flow : unsigned int;
    enum Sizing : unsigned int;
    enum SpacePreset : unsigned int;
    enum Clipping : unsigned int;
    enum Opacity : unsigned int;
    enum WidgetState : unsigned int;
    enum DirtyLayout : unsigned int;
    enum class CodePalette : unsigned char;
    enum class TextFocusMode : unsigned int;
    enum WindowState : unsigned int;
    
    template <class T> struct Dim2;
    
    class Style;
    struct Space;
    struct Styles;
    struct Image;
    class ImageAtlas;
    class Sprite;
    class SpriteAtlas;
    struct UiRect;
    class Frame;
    class Widget;
    struct TextGlyph;
    struct TextRow;
    struct Shadow;
    struct Paint;
    struct TextPaint;
    struct Gradient;
    struct TextCursor;
    struct TextSelection;
    class Text;
    class TextEdit;
    struct NodeConnection;
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
    class UiRenderTarget;
    class VgRenderer;
    class ScrollSheet;
    class Tabber;
    class Expandbox;
    class TreeNode;
    class Table;
    struct Dock;
    class Dockable;
    class Docker;
    class Docksystem;
    class Dockspace;
    class Dockbar;
    class NodePlug;
    class Node;
    struct CanvasConnect;
    class Canvas;
    class RootSheet;
    class Window;
    struct ImageSkin;
    struct InkStyle;
    class Options;
    class Styler;
}

namespace mud {
namespace detail {

    
    
}
}

