#pragma once

#include <ui/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <ctx/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_UI_EXPORT Type& type<mud::Align>();
    template <> MUD_UI_EXPORT Type& type<mud::AutoLayout>();
    template <> MUD_UI_EXPORT Type& type<mud::Clipping>();
    template <> MUD_UI_EXPORT Type& type<mud::CodePalette>();
    template <> MUD_UI_EXPORT Type& type<mud::Dim>();
    template <> MUD_UI_EXPORT Type& type<mud::DirtyLayout>();
    template <> MUD_UI_EXPORT Type& type<mud::DropState>();
    template <> MUD_UI_EXPORT Type& type<mud::Flow>();
    template <> MUD_UI_EXPORT Type& type<mud::FlowAxis>();
    template <> MUD_UI_EXPORT Type& type<mud::LayoutSolver>();
    template <> MUD_UI_EXPORT Type& type<mud::Opacity>();
    template <> MUD_UI_EXPORT Type& type<mud::Pivot>();
    template <> MUD_UI_EXPORT Type& type<mud::ui::PopupFlags>();
    template <> MUD_UI_EXPORT Type& type<mud::Sizing>();
    template <> MUD_UI_EXPORT Type& type<mud::SpacePreset>();
    template <> MUD_UI_EXPORT Type& type<mud::TextFocusMode>();
    template <> MUD_UI_EXPORT Type& type<mud::WidgetState>();
    template <> MUD_UI_EXPORT Type& type<mud::WindowState>();
    template <> MUD_UI_EXPORT Type& type<std::vector<mud::Space>>();
    template <> MUD_UI_EXPORT Type& type<std::vector<std::string>>();
    
    template <> MUD_UI_EXPORT Type& type<mud::CanvasConnect>();
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Align>>();
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::AutoLayout>>();
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Pivot>>();
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<mud::Sizing>>();
    template <> MUD_UI_EXPORT Type& type<mud::Dim2<size_t>>();
    template <> MUD_UI_EXPORT Type& type<mud::Dock>();
    template <> MUD_UI_EXPORT Type& type<mud::Docksystem>();
    template <> MUD_UI_EXPORT Type& type<mud::Gradient>();
    template <> MUD_UI_EXPORT Type& type<mud::GridSolver>();
    template <> MUD_UI_EXPORT Type& type<mud::Image>();
    template <> MUD_UI_EXPORT Type& type<mud::ImageAtlas>();
    template <> MUD_UI_EXPORT Type& type<mud::ImageSkin>();
    template <> MUD_UI_EXPORT Type& type<mud::InkStyle>();
    template <> MUD_UI_EXPORT Type& type<mud::Layer>();
    template <> MUD_UI_EXPORT Type& type<mud::Layout>();
    template <> MUD_UI_EXPORT Type& type<mud::NodeConnection>();
    template <> MUD_UI_EXPORT Type& type<mud::Paint>();
    template <> MUD_UI_EXPORT Type& type<mud::Shadow>();
    template <> MUD_UI_EXPORT Type& type<mud::Space>();
    template <> MUD_UI_EXPORT Type& type<mud::Style>();
    template <> MUD_UI_EXPORT Type& type<mud::Styler>();
    template <> MUD_UI_EXPORT Type& type<mud::TableSolver>();
    template <> MUD_UI_EXPORT Type& type<mud::Text>();
    template <> MUD_UI_EXPORT Type& type<mud::TextCursor>();
    template <> MUD_UI_EXPORT Type& type<mud::TextPaint>();
    template <> MUD_UI_EXPORT Type& type<mud::TextSelection>();
    template <> MUD_UI_EXPORT Type& type<mud::UiRect>();
    template <> MUD_UI_EXPORT Type& type<mud::UiTarget>();
    template <> MUD_UI_EXPORT Type& type<mud::UiWindow>();
    template <> MUD_UI_EXPORT Type& type<mud::User>();
    template <> MUD_UI_EXPORT Type& type<mud::Widget>();
    template <> MUD_UI_EXPORT Type& type<mud::Sprite>();
    template <> MUD_UI_EXPORT Type& type<mud::Dockbar>();
    template <> MUD_UI_EXPORT Type& type<mud::Dockspace>();
    template <> MUD_UI_EXPORT Type& type<mud::SpriteAtlas>();
    template <> MUD_UI_EXPORT Type& type<mud::Frame>();
    template <> MUD_UI_EXPORT Type& type<mud::FrameSolver>();
    template <> MUD_UI_EXPORT Type& type<mud::Canvas>();
    template <> MUD_UI_EXPORT Type& type<mud::Dockable>();
    template <> MUD_UI_EXPORT Type& type<mud::Docker>();
    template <> MUD_UI_EXPORT Type& type<mud::Expandbox>();
    template <> MUD_UI_EXPORT Type& type<mud::Node>();
    template <> MUD_UI_EXPORT Type& type<mud::NodePlug>();
    template <> MUD_UI_EXPORT Type& type<mud::RootSheet>();
    template <> MUD_UI_EXPORT Type& type<mud::ScrollSheet>();
    template <> MUD_UI_EXPORT Type& type<mud::ui::Sequence>();
    template <> MUD_UI_EXPORT Type& type<mud::Tabber>();
    template <> MUD_UI_EXPORT Type& type<mud::Table>();
    template <> MUD_UI_EXPORT Type& type<mud::TextEdit>();
    template <> MUD_UI_EXPORT Type& type<mud::TreeNode>();
    template <> MUD_UI_EXPORT Type& type<mud::RowSolver>();
    template <> MUD_UI_EXPORT Type& type<mud::LineSolver>();
    template <> MUD_UI_EXPORT Type& type<mud::Window>();
}
