#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <ui/Types.h>
#include <ui/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    template <> TWO_UI_EXPORT Type& type<two::FlowAxis>() { static Type ty("FlowAxis", sizeof(two::FlowAxis)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Pivot>() { static Type ty("Pivot", sizeof(two::Pivot)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Align>() { static Type ty("Align", sizeof(two::Align)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Solver>() { static Type ty("Solver", sizeof(two::Solver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::AutoLayout>() { static Type ty("AutoLayout", sizeof(two::AutoLayout)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::LayoutFlow>() { static Type ty("LayoutFlow", sizeof(two::LayoutFlow)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Sizing>() { static Type ty("Sizing", sizeof(two::Sizing)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Preset>() { static Type ty("Preset", sizeof(two::Preset)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Clip>() { static Type ty("Clip", sizeof(two::Clip)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Opacity>() { static Type ty("Opacity", sizeof(two::Opacity)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::WidgetState>() { static Type ty("WidgetState", sizeof(two::WidgetState)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::ui::PopupFlags>() { static Type ty("PopupFlags", sizeof(two::ui::PopupFlags)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::WindowState>() { static Type ty("WindowState", sizeof(two::WindowState)); return ty; }
    
    template <> TWO_UI_EXPORT Type& type<stl::span<const char*>>() { static Type ty("span<const char*>", sizeof(stl::span<const char*>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<stl::vector<two::Space>>() { static Type ty("vector<two::Space>", sizeof(stl::vector<two::Space>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<stl::vector<two::Subskin>>() { static Type ty("vector<two::Subskin>", sizeof(stl::vector<two::Subskin>)); return ty; }
    
    template <> TWO_UI_EXPORT Type& type<two::Space>() { static Type ty("Space", sizeof(two::Space)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<two::AutoLayout>>() { static Type ty("v2<two::AutoLayout>", sizeof(two::v2<two::AutoLayout>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Sizing>>() { static Type ty("v2<two::Sizing>", sizeof(two::v2<two::Sizing>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Align>>() { static Type ty("v2<two::Align>", sizeof(two::v2<two::Align>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Pivot>>() { static Type ty("v2<two::Pivot>", sizeof(two::v2<two::Pivot>)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::ImageSkin>() { static Type ty("ImageSkin", sizeof(two::ImageSkin)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Shadow>() { static Type ty("Shadow", sizeof(two::Shadow)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Paint>() { static Type ty("Paint", sizeof(two::Paint)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextPaint>() { static Type ty("TextPaint", sizeof(two::TextPaint)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Gradient>() { static Type ty("Gradient", sizeof(two::Gradient)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::InkStyle>() { static Type ty("InkStyle", sizeof(two::InkStyle)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Layout>() { static Type ty("Layout", sizeof(two::Layout)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Subskin>() { static Type ty("Subskin", sizeof(two::Subskin)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Style>() { static Type ty("Style", sizeof(two::Style)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::UiRect>() { static Type ty("UiRect", sizeof(two::UiRect)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Frame>() { static Type ty("Frame", type<two::UiRect>(), sizeof(two::Frame)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Widget>() { static Type ty("Widget", type<two::ControlNode>(), sizeof(two::Widget)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextCursor>() { static Type ty("TextCursor", sizeof(two::TextCursor)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextSelection>() { static Type ty("TextSelection", sizeof(two::TextSelection)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextMarker>() { static Type ty("TextMarker", sizeof(two::TextMarker)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Text>() { static Type ty("Text", sizeof(two::Text)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TextEdit>() { static Type ty("TextEdit", type<two::Widget>(), sizeof(two::TextEdit)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::NodeConnection>() { static Type ty("NodeConnection", sizeof(two::NodeConnection)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Vg>() { static Type ty("Vg", sizeof(two::Vg)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Clipboard>() { static Type ty("Clipboard", sizeof(two::Clipboard)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::UiWindow>() { static Type ty("UiWindow", sizeof(two::UiWindow)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::User>() { static Type ty("User", sizeof(two::User)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Layer>() { static Type ty("Layer", sizeof(two::Layer)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::FrameSolver>() { static Type ty("FrameSolver", type<two::UiRect>(), sizeof(two::FrameSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::RowSolver>() { static Type ty("RowSolver", type<two::FrameSolver>(), sizeof(two::RowSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TableSolver>() { static Type ty("TableSolver", sizeof(two::TableSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::LineSolver>() { static Type ty("LineSolver", type<two::RowSolver>(), sizeof(two::LineSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::GridSolver>() { static Type ty("GridSolver", sizeof(two::GridSolver)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::ScrollSheet>() { static Type ty("ScrollSheet", type<two::Widget>(), sizeof(two::ScrollSheet)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::ui::Sequence>() { static Type ty("Sequence", type<two::Widget>(), sizeof(two::ui::Sequence)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Tabber>() { static Type ty("Tabber", type<two::Widget>(), sizeof(two::Tabber)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Expandbox>() { static Type ty("Expandbox", type<two::Widget>(), sizeof(two::Expandbox)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::TreeNode>() { static Type ty("TreeNode", type<two::Widget>(), sizeof(two::TreeNode)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Table>() { static Type ty("Table", type<two::Widget>(), sizeof(two::Table)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Dock>() { static Type ty("Dock", sizeof(two::Dock)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Docksystem>() { static Type ty("Docksystem", sizeof(two::Docksystem)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Dockable>() { static Type ty("Dockable", type<two::Widget>(), sizeof(two::Dockable)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Docker>() { static Type ty("Docker", type<two::Widget>(), sizeof(two::Docker)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Dockspace>() { static Type ty("Dockspace", type<two::Docker>(), sizeof(two::Dockspace)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Dockbar>() { static Type ty("Dockbar", type<two::Docker>(), sizeof(two::Dockbar)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::NodePlug>() { static Type ty("NodePlug", type<two::Widget>(), sizeof(two::NodePlug)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Node>() { static Type ty("Node", type<two::Widget>(), sizeof(two::Node)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::CanvasConnect>() { static Type ty("CanvasConnect", sizeof(two::CanvasConnect)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Canvas>() { static Type ty("Canvas", type<two::Widget>(), sizeof(two::Canvas)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Ui>() { static Type ty("Ui", type<two::Widget>(), sizeof(two::Ui)); return ty; }
    template <> TWO_UI_EXPORT Type& type<two::Window>() { static Type ty("Window", type<two::Dockable>(), sizeof(two::Window)); return ty; }
}
