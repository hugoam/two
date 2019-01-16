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
#include <cstdint>
#include <stl/vector.h>
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
    
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::CanvasConnect*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Clipboard*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dim2<bool>*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dim2<mud::Align>*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dim2<mud::AutoLayout>*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dim2<mud::Pivot>*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dim2<mud::Sizing>*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dim2<size_t>*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dock*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Docksystem*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Gradient*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::GridSolver*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::ImageSkin*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::InkStyle*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Layer*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Layout*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::NodeConnection*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Paint*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Shadow*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Space*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Style*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::TableSolver*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Text*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::TextCursor*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::TextMarker*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::TextPaint*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::TextSelection*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::UiRect*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::UiWindow*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::User*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Vg*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Frame*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::FrameSolver*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::LineSolver*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Widget*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Canvas*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dockable*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Docker*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dockbar*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Dockspace*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Expandbox*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Node*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::NodePlug*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::RowSolver*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::ScrollSheet*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::ui::Sequence*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Tabber*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Table*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::TextEdit*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::TreeNode*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Ui*>>;
    export_ template struct MUD_UI_EXPORT Typed<vector<mud::Window*>>;
}
