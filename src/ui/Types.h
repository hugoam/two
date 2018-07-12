#pragma once

#include <ui/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <refl/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <ctx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_UI_EXPORT Type& type<mud::Align>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::AutoLayout>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Clipping>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::CodePalette>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dim>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::DirtyLayout>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::DropState>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Flow>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::FlowAxis>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::LayoutSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Opacity>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Pivot>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::ui::PopupFlags>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Sizing>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::SpacePreset>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextFocusMode>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::WidgetState>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::WindowState>();
    
    export_ template <> MUD_UI_EXPORT Type& type<mud::CanvasConnect>();
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
    export_ template <> MUD_UI_EXPORT Type& type<mud::Styler>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TableSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Text>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextCursor>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextPaint>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextSelection>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::UiRect>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::UiWindow>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::User>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Widget>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Frame>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::FrameSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Canvas>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dockable>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Docker>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Expandbox>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Node>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::NodePlug>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::RootSheet>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::ScrollSheet>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::ui::Sequence>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Tabber>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Table>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TextEdit>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::TreeNode>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::RowSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::LineSolver>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dockbar>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Dockspace>();
    export_ template <> MUD_UI_EXPORT Type& type<mud::Window>();
    
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::CanvasConnect*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dim2<bool>*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dim2<mud::Align>*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dim2<mud::AutoLayout>*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dim2<mud::Pivot>*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dim2<mud::Sizing>*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dim2<size_t>*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dock*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Docksystem*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Gradient*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::GridSolver*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::ImageSkin*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::InkStyle*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Layer*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Layout*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::NodeConnection*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Paint*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Shadow*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Space*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Style*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Styler*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::TableSolver*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Text*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::TextCursor*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::TextPaint*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::TextSelection*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::UiRect*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::UiWindow*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::User*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Widget*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Frame*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::FrameSolver*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Canvas*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dockable*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Docker*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Expandbox*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Node*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::NodePlug*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::RootSheet*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::ScrollSheet*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::ui::Sequence*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Tabber*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Table*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::TextEdit*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::TreeNode*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::RowSolver*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::LineSolver*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dockbar*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Dockspace*>>;
	export_ template struct MUD_UI_EXPORT Typed<std::vector<mud::Window*>>;
}
