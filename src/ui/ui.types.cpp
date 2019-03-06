#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <ui/Types.h>
#include <ui/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_UI_EXPORT Type& type<mud::Align>() { static Type ty("Align", sizeof(mud::Align)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::AutoLayout>() { static Type ty("AutoLayout", sizeof(mud::AutoLayout)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Clip>() { static Type ty("Clip", sizeof(mud::Clip)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::FlowAxis>() { static Type ty("FlowAxis", sizeof(mud::FlowAxis)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::LayoutFlow>() { static Type ty("LayoutFlow", sizeof(mud::LayoutFlow)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Opacity>() { static Type ty("Opacity", sizeof(mud::Opacity)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Pivot>() { static Type ty("Pivot", sizeof(mud::Pivot)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ui::PopupFlags>() { static Type ty("PopupFlags", sizeof(mud::ui::PopupFlags)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Preset>() { static Type ty("Preset", sizeof(mud::Preset)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Sizing>() { static Type ty("Sizing", sizeof(mud::Sizing)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Solver>() { static Type ty("Solver", sizeof(mud::Solver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::WidgetState>() { static Type ty("WidgetState", sizeof(mud::WidgetState)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::WindowState>() { static Type ty("WindowState", sizeof(mud::WindowState)); return ty; }
    
    template <> MUD_UI_EXPORT Type& type<stl::span<const char*>>() { static Type ty("span<const char*>", sizeof(stl::span<const char*>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<stl::vector<mud::Space>>() { static Type ty("vector<mud::Space>", sizeof(stl::vector<mud::Space>)); return ty; }
    
    template <> MUD_UI_EXPORT Type& type<mud::CanvasConnect>() { static Type ty("CanvasConnect", sizeof(mud::CanvasConnect)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Clipboard>() { static Type ty("Clipboard", sizeof(mud::Clipboard)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dock>() { static Type ty("Dock", sizeof(mud::Dock)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Docksystem>() { static Type ty("Docksystem", sizeof(mud::Docksystem)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Gradient>() { static Type ty("Gradient", sizeof(mud::Gradient)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::GridSolver>() { static Type ty("GridSolver", sizeof(mud::GridSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ImageSkin>() { static Type ty("ImageSkin", sizeof(mud::ImageSkin)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::InkStyle>() { static Type ty("InkStyle", sizeof(mud::InkStyle)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Layer>() { static Type ty("Layer", sizeof(mud::Layer)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Layout>() { static Type ty("Layout", sizeof(mud::Layout)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::NodeConnection>() { static Type ty("NodeConnection", sizeof(mud::NodeConnection)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Paint>() { static Type ty("Paint", sizeof(mud::Paint)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Shadow>() { static Type ty("Shadow", sizeof(mud::Shadow)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Space>() { static Type ty("Space", sizeof(mud::Space)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Style>() { static Type ty("Style", sizeof(mud::Style)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TableSolver>() { static Type ty("TableSolver", sizeof(mud::TableSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Text>() { static Type ty("Text", sizeof(mud::Text)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextCursor>() { static Type ty("TextCursor", sizeof(mud::TextCursor)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextMarker>() { static Type ty("TextMarker", sizeof(mud::TextMarker)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextPaint>() { static Type ty("TextPaint", sizeof(mud::TextPaint)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextSelection>() { static Type ty("TextSelection", sizeof(mud::TextSelection)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::UiRect>() { static Type ty("UiRect", sizeof(mud::UiRect)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::UiWindow>() { static Type ty("UiWindow", sizeof(mud::UiWindow)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::User>() { static Type ty("User", sizeof(mud::User)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Vg>() { static Type ty("Vg", sizeof(mud::Vg)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::v2<mud::Align>>() { static Type ty("v2<mud::Align>", sizeof(mud::v2<mud::Align>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::v2<mud::AutoLayout>>() { static Type ty("v2<mud::AutoLayout>", sizeof(mud::v2<mud::AutoLayout>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::v2<mud::Pivot>>() { static Type ty("v2<mud::Pivot>", sizeof(mud::v2<mud::Pivot>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::v2<mud::Sizing>>() { static Type ty("v2<mud::Sizing>", sizeof(mud::v2<mud::Sizing>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::v2<size_t>>() { static Type ty("v2<size_t>", sizeof(mud::v2<size_t>)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Canvas>() { static Type ty("Canvas", type<mud::Widget>(), sizeof(mud::Canvas)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockable>() { static Type ty("Dockable", type<mud::Widget>(), sizeof(mud::Dockable)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Docker>() { static Type ty("Docker", type<mud::Widget>(), sizeof(mud::Docker)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockbar>() { static Type ty("Dockbar", type<mud::Docker>(), sizeof(mud::Dockbar)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockspace>() { static Type ty("Dockspace", type<mud::Docker>(), sizeof(mud::Dockspace)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Expandbox>() { static Type ty("Expandbox", type<mud::Widget>(), sizeof(mud::Expandbox)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Frame>() { static Type ty("Frame", type<mud::UiRect>(), sizeof(mud::Frame)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::FrameSolver>() { static Type ty("FrameSolver", type<mud::UiRect>(), sizeof(mud::FrameSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Node>() { static Type ty("Node", type<mud::Widget>(), sizeof(mud::Node)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::NodePlug>() { static Type ty("NodePlug", type<mud::Widget>(), sizeof(mud::NodePlug)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::RowSolver>() { static Type ty("RowSolver", type<mud::FrameSolver>(), sizeof(mud::RowSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::LineSolver>() { static Type ty("LineSolver", type<mud::RowSolver>(), sizeof(mud::LineSolver)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ScrollSheet>() { static Type ty("ScrollSheet", type<mud::Widget>(), sizeof(mud::ScrollSheet)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ui::Sequence>() { static Type ty("Sequence", type<mud::Widget>(), sizeof(mud::ui::Sequence)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Tabber>() { static Type ty("Tabber", type<mud::Widget>(), sizeof(mud::Tabber)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Table>() { static Type ty("Table", type<mud::Widget>(), sizeof(mud::Table)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextEdit>() { static Type ty("TextEdit", type<mud::Widget>(), sizeof(mud::TextEdit)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Widget>() { static Type ty("Widget", type<mud::ControlNode>(), sizeof(mud::Widget)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TreeNode>() { static Type ty("TreeNode", type<mud::Widget>(), sizeof(mud::TreeNode)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Ui>() { static Type ty("Ui", type<mud::Widget>(), sizeof(mud::Ui)); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Window>() { static Type ty("Window", type<mud::Dockable>(), sizeof(mud::Window)); return ty; }
}
