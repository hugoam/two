#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <ui/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <ctx/Types.h>
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
    export_ template <> TWO_UI_EXPORT Type& type<two::v2<size_t>>();
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
