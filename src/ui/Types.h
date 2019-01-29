#pragma once

#include <ui/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <ctx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_UI_EXPORT Type& type<mud::Align>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::AutoLayout>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Clipping>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dim>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Flow>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::FlowAxis>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::LayoutSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Opacity>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Pivot>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::ui::PopupFlags>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Sizing>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::SpacePreset>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::WidgetState>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::WindowState>();
    
    export_ template <> MUD_UI_EXPORT Type& type<mud::CanvasConnect>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Clipboard>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dim2<bool>>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Align>>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::AutoLayout>>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Pivot>>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Sizing>>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dim2<size_t>>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dock>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Docksystem>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Gradient>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::GridSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::ImageSkin>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::InkStyle>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Layer>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Layout>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::NodeConnection>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Paint>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Shadow>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Space>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Style>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TableSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Text>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextCursor>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextMarker>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextPaint>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextSelection>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::UiRect>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::UiWindow>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::User>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Vg>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Frame>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::FrameSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::LineSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Widget>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Canvas>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dockable>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Docker>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dockbar>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dockspace>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Expandbox>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Node>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::NodePlug>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::RowSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::ScrollSheet>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::ui::Sequence>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Tabber>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Table>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextEdit>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TreeNode>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Ui>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Window>();
    
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::CanvasConnect*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Clipboard*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dim2<bool>*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dim2<mud::Align>*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dim2<mud::AutoLayout>*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dim2<mud::Pivot>*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dim2<mud::Sizing>*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dim2<size_t>*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dock*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Docksystem*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Gradient*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::GridSolver*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::ImageSkin*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::InkStyle*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Layer*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Layout*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::NodeConnection*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Paint*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Shadow*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Space*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Style*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::TableSolver*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Text*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::TextCursor*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::TextMarker*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::TextPaint*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::TextSelection*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::UiRect*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::UiWindow*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::User*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Vg*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Frame*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::FrameSolver*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::LineSolver*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Widget*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Canvas*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dockable*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Docker*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dockbar*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Dockspace*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Expandbox*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Node*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::NodePlug*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::RowSolver*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::ScrollSheet*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::ui::Sequence*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Tabber*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Table*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::TextEdit*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::TreeNode*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Ui*>>();
    export_ template <> MUD_UI_EXPORT Type& type<vector<mud::Window*>>();
}
