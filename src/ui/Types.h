#pragma once

#include <ui/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_UI_EXPORT Type& type<two::FlowAxis>();
    template <> TWO_UI_EXPORT Type& type<two::Pivot>();
    template <> TWO_UI_EXPORT Type& type<two::Align>();
    template <> TWO_UI_EXPORT Type& type<two::AutoLayout>();
    template <> TWO_UI_EXPORT Type& type<two::LayoutFlow>();
    template <> TWO_UI_EXPORT Type& type<two::Sizing>();
    template <> TWO_UI_EXPORT Type& type<two::Preset>();
    template <> TWO_UI_EXPORT Type& type<two::Clip>();
    template <> TWO_UI_EXPORT Type& type<two::Opacity>();
    template <> TWO_UI_EXPORT Type& type<two::WidgetState>();
    template <> TWO_UI_EXPORT Type& type<two::ui::PopupFlags>();
    template <> TWO_UI_EXPORT Type& type<two::WindowState>();
    
    template <> TWO_UI_EXPORT Type& type<stl::span<const char*>>();
    template <> TWO_UI_EXPORT Type& type<stl::vector<two::Space>>();
    template <> TWO_UI_EXPORT Type& type<stl::vector<two::Subskin>>();
    
    template <> TWO_UI_EXPORT Type& type<two::Space>();
    template <> TWO_UI_EXPORT Type& type<two::v2<two::AutoLayout>>();
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Sizing>>();
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Align>>();
    template <> TWO_UI_EXPORT Type& type<two::v2<two::Pivot>>();
    template <> TWO_UI_EXPORT Type& type<two::ImageSkin>();
    template <> TWO_UI_EXPORT Type& type<two::Shadow>();
    template <> TWO_UI_EXPORT Type& type<two::Paint>();
    template <> TWO_UI_EXPORT Type& type<two::TextPaint>();
    template <> TWO_UI_EXPORT Type& type<two::Gradient>();
    template <> TWO_UI_EXPORT Type& type<two::InkStyle>();
    template <> TWO_UI_EXPORT Type& type<two::Layout>();
    template <> TWO_UI_EXPORT Type& type<two::Subskin>();
    template <> TWO_UI_EXPORT Type& type<two::Style>();
    template <> TWO_UI_EXPORT Type& type<two::UiRect>();
    template <> TWO_UI_EXPORT Type& type<two::Frame>();
    template <> TWO_UI_EXPORT Type& type<two::Widget>();
    template <> TWO_UI_EXPORT Type& type<two::TextCursor>();
    template <> TWO_UI_EXPORT Type& type<two::TextSelection>();
    template <> TWO_UI_EXPORT Type& type<two::TextMarker>();
    template <> TWO_UI_EXPORT Type& type<two::Text>();
    template <> TWO_UI_EXPORT Type& type<two::TextEdit>();
    template <> TWO_UI_EXPORT Type& type<two::NodeConnection>();
    template <> TWO_UI_EXPORT Type& type<two::Vg>();
    template <> TWO_UI_EXPORT Type& type<two::Clipboard>();
    template <> TWO_UI_EXPORT Type& type<two::UiWindow>();
    template <> TWO_UI_EXPORT Type& type<two::User>();
    template <> TWO_UI_EXPORT Type& type<two::Layer>();
    template <> TWO_UI_EXPORT Type& type<two::Tabber>();
    template <> TWO_UI_EXPORT Type& type<two::Table>();
    template <> TWO_UI_EXPORT Type& type<two::Dock>();
    template <> TWO_UI_EXPORT Type& type<two::Docksystem>();
    template <> TWO_UI_EXPORT Type& type<two::Docker>();
    template <> TWO_UI_EXPORT Type& type<two::Dockspace>();
    template <> TWO_UI_EXPORT Type& type<two::Dockbar>();
    template <> TWO_UI_EXPORT Type& type<two::NodePlug>();
    template <> TWO_UI_EXPORT Type& type<two::Node>();
    template <> TWO_UI_EXPORT Type& type<two::CanvasConnect>();
    template <> TWO_UI_EXPORT Type& type<two::Canvas>();
    template <> TWO_UI_EXPORT Type& type<two::Ui>();
}
