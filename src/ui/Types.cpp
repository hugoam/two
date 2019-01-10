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
    template <> MUD_UI_EXPORT Type& type<mud::Align>() { static Type ty("mud::Align"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::AutoLayout>() { static Type ty("mud::AutoLayout"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Clipping>() { static Type ty("mud::Clipping"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim>() { static Type ty("mud::Dim"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Flow>() { static Type ty("mud::Flow"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::FlowAxis>() { static Type ty("mud::FlowAxis"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::LayoutSolver>() { static Type ty("mud::LayoutSolver"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Opacity>() { static Type ty("mud::Opacity"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Pivot>() { static Type ty("mud::Pivot"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ui::PopupFlags>() { static Type ty("mud::ui::PopupFlags"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Sizing>() { static Type ty("mud::Sizing"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::SpacePreset>() { static Type ty("mud::SpacePreset"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::WidgetState>() { static Type ty("mud::WidgetState"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::WindowState>() { static Type ty("mud::WindowState"); return ty; }
    
    template <> MUD_UI_EXPORT Type& type<mud::CanvasConnect>() { static Type ty("CanvasConnect"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Clipboard>() { static Type ty("Clipboard"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<bool>>() { static Type ty("Dim2<bool>"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Align>>() { static Type ty("Dim2<mud::Align>"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::AutoLayout>>() { static Type ty("Dim2<mud::AutoLayout>"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Pivot>>() { static Type ty("Dim2<mud::Pivot>"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Sizing>>() { static Type ty("Dim2<mud::Sizing>"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<size_t>>() { static Type ty("Dim2<size_t>"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dock>() { static Type ty("Dock"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Docksystem>() { static Type ty("Docksystem"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Gradient>() { static Type ty("Gradient"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::GridSolver>() { static Type ty("GridSolver"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ImageSkin>() { static Type ty("ImageSkin"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::InkStyle>() { static Type ty("InkStyle"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Layer>() { static Type ty("Layer"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Layout>() { static Type ty("Layout"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::NodeConnection>() { static Type ty("NodeConnection"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Paint>() { static Type ty("Paint"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Shadow>() { static Type ty("Shadow"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Space>() { static Type ty("Space"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Style>() { static Type ty("Style"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TableSolver>() { static Type ty("TableSolver"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Text>() { static Type ty("Text"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextCursor>() { static Type ty("TextCursor"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextMarker>() { static Type ty("TextMarker"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextPaint>() { static Type ty("TextPaint"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextSelection>() { static Type ty("TextSelection"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::UiRect>() { static Type ty("UiRect"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::UiWindow>() { static Type ty("UiWindow"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::User>() { static Type ty("User"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Vg>() { static Type ty("Vg"); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Frame>() { static Type ty("Frame", type<mud::UiRect>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::FrameSolver>() { static Type ty("FrameSolver", type<mud::UiRect>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::LineSolver>() { static Type ty("LineSolver", type<mud::RowSolver>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Widget>() { static Type ty("Widget", type<mud::ControlNode>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Canvas>() { static Type ty("Canvas", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockable>() { static Type ty("Dockable", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Docker>() { static Type ty("Docker", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockbar>() { static Type ty("Dockbar", type<mud::Docker>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Dockspace>() { static Type ty("Dockspace", type<mud::Docker>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Expandbox>() { static Type ty("Expandbox", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Node>() { static Type ty("Node", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::NodePlug>() { static Type ty("NodePlug", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::RowSolver>() { static Type ty("RowSolver", type<mud::FrameSolver>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ScrollSheet>() { static Type ty("ScrollSheet", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::ui::Sequence>() { static Type ty("Sequence", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Tabber>() { static Type ty("Tabber", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Table>() { static Type ty("Table", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TextEdit>() { static Type ty("TextEdit", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::TreeNode>() { static Type ty("TreeNode", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Ui>() { static Type ty("Ui", type<mud::Widget>()); return ty; }
    template <> MUD_UI_EXPORT Type& type<mud::Window>() { static Type ty("Window", type<mud::Dockable>()); return ty; }
}
