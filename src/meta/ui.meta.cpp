#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/math.meta.h>
#include <meta/ctx.meta.h>
#include <meta/ui.meta.h>
#include <meta/ui.conv.h>
#endif

#include <ui/Api.h>

using namespace mud;

void mud_Align__to_string(void* val, string& str) { str = g_enu[type<mud::Align>().m_id]->name(uint32_t((*static_cast<mud::Align*>(val)))); }
void mud_Align__to_value(const string& str, void* val) { (*static_cast<mud::Align*>(val)) = mud::Align(g_enu[type<mud::Align>().m_id]->value(str.c_str())); }
void mud_AutoLayout__to_string(void* val, string& str) { str = g_enu[type<mud::AutoLayout>().m_id]->name(uint32_t((*static_cast<mud::AutoLayout*>(val)))); }
void mud_AutoLayout__to_value(const string& str, void* val) { (*static_cast<mud::AutoLayout*>(val)) = mud::AutoLayout(g_enu[type<mud::AutoLayout>().m_id]->value(str.c_str())); }
void mud_Clip__to_string(void* val, string& str) { str = g_enu[type<mud::Clip>().m_id]->name(uint32_t((*static_cast<mud::Clip*>(val)))); }
void mud_Clip__to_value(const string& str, void* val) { (*static_cast<mud::Clip*>(val)) = mud::Clip(g_enu[type<mud::Clip>().m_id]->value(str.c_str())); }
void mud_FlowAxis__to_string(void* val, string& str) { str = g_enu[type<mud::FlowAxis>().m_id]->name(uint32_t((*static_cast<mud::FlowAxis*>(val)))); }
void mud_FlowAxis__to_value(const string& str, void* val) { (*static_cast<mud::FlowAxis*>(val)) = mud::FlowAxis(g_enu[type<mud::FlowAxis>().m_id]->value(str.c_str())); }
void mud_LayoutFlow__to_string(void* val, string& str) { str = g_enu[type<mud::LayoutFlow>().m_id]->name(uint32_t((*static_cast<mud::LayoutFlow*>(val)))); }
void mud_LayoutFlow__to_value(const string& str, void* val) { (*static_cast<mud::LayoutFlow*>(val)) = mud::LayoutFlow(g_enu[type<mud::LayoutFlow>().m_id]->value(str.c_str())); }
void mud_Opacity__to_string(void* val, string& str) { str = g_enu[type<mud::Opacity>().m_id]->name(uint32_t((*static_cast<mud::Opacity*>(val)))); }
void mud_Opacity__to_value(const string& str, void* val) { (*static_cast<mud::Opacity*>(val)) = mud::Opacity(g_enu[type<mud::Opacity>().m_id]->value(str.c_str())); }
void mud_Pivot__to_string(void* val, string& str) { str = g_enu[type<mud::Pivot>().m_id]->name(uint32_t((*static_cast<mud::Pivot*>(val)))); }
void mud_Pivot__to_value(const string& str, void* val) { (*static_cast<mud::Pivot*>(val)) = mud::Pivot(g_enu[type<mud::Pivot>().m_id]->value(str.c_str())); }
void mud_ui_PopupFlags__to_string(void* val, string& str) { str = g_enu[type<mud::ui::PopupFlags>().m_id]->name(uint32_t((*static_cast<mud::ui::PopupFlags*>(val)))); }
void mud_ui_PopupFlags__to_value(const string& str, void* val) { (*static_cast<mud::ui::PopupFlags*>(val)) = mud::ui::PopupFlags(g_enu[type<mud::ui::PopupFlags>().m_id]->value(str.c_str())); }
void mud_Preset__to_string(void* val, string& str) { str = g_enu[type<mud::Preset>().m_id]->name(uint32_t((*static_cast<mud::Preset*>(val)))); }
void mud_Preset__to_value(const string& str, void* val) { (*static_cast<mud::Preset*>(val)) = mud::Preset(g_enu[type<mud::Preset>().m_id]->value(str.c_str())); }
void mud_Sizing__to_string(void* val, string& str) { str = g_enu[type<mud::Sizing>().m_id]->name(uint32_t((*static_cast<mud::Sizing*>(val)))); }
void mud_Sizing__to_value(const string& str, void* val) { (*static_cast<mud::Sizing*>(val)) = mud::Sizing(g_enu[type<mud::Sizing>().m_id]->value(str.c_str())); }
void mud_Solver__to_string(void* val, string& str) { str = g_enu[type<mud::Solver>().m_id]->name(uint32_t((*static_cast<mud::Solver*>(val)))); }
void mud_Solver__to_value(const string& str, void* val) { (*static_cast<mud::Solver*>(val)) = mud::Solver(g_enu[type<mud::Solver>().m_id]->value(str.c_str())); }
void mud_WidgetState__to_string(void* val, string& str) { str = g_enu[type<mud::WidgetState>().m_id]->name(uint32_t((*static_cast<mud::WidgetState*>(val)))); }
void mud_WidgetState__to_value(const string& str, void* val) { (*static_cast<mud::WidgetState*>(val)) = mud::WidgetState(g_enu[type<mud::WidgetState>().m_id]->value(str.c_str())); }
void mud_WindowState__to_string(void* val, string& str) { str = g_enu[type<mud::WindowState>().m_id]->name(uint32_t((*static_cast<mud::WindowState*>(val)))); }
void mud_WindowState__to_value(const string& str, void* val) { (*static_cast<mud::WindowState*>(val)) = mud::WindowState(g_enu[type<mud::WindowState>().m_id]->value(str.c_str())); }
size_t stl_span_const_char___size(void* vec) { return (*static_cast<stl::span<const char*>*>(vec)).size(); }
void* stl_span_const_char___at(void* vec, size_t i) { return &(*static_cast<stl::span<const char*>*>(vec))[i]; }
size_t stl_vector_mud_Space__size(void* vec) { return (*static_cast<stl::vector<mud::Space>*>(vec)).size(); }
void* stl_vector_mud_Space__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Space>*>(vec))[i]; }
void stl_vector_mud_Space__push(void* vec) { (*static_cast<stl::vector<mud::Space>*>(vec)).emplace_back(); }
void stl_vector_mud_Space__add(void* vec, void* value) { (*static_cast<stl::vector<mud::Space>*>(vec)).push_back(*static_cast<mud::Space*>(value)); }
void stl_vector_mud_Space__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Space>*>(vec)), *static_cast<mud::Space*>(value)); }
size_t stl_vector_mud_Subskin__size(void* vec) { return (*static_cast<stl::vector<mud::Subskin>*>(vec)).size(); }
void* stl_vector_mud_Subskin__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Subskin>*>(vec))[i]; }
void stl_vector_mud_Subskin__push(void* vec) { (*static_cast<stl::vector<mud::Subskin>*>(vec)).emplace_back(); }
void stl_vector_mud_Subskin__add(void* vec, void* value) { (*static_cast<stl::vector<mud::Subskin>*>(vec)).push_back(*static_cast<mud::Subskin*>(value)); }
void stl_vector_mud_Subskin__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Subskin>*>(vec)), *static_cast<mud::Subskin*>(value)); }
void mud_CanvasConnect__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CanvasConnect(  ); }
void mud_CanvasConnect__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CanvasConnect((*static_cast<mud::CanvasConnect*>(other))); }
void mud_Clipboard__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Clipboard(  ); }
void mud_Clipboard__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Clipboard((*static_cast<mud::Clipboard*>(other))); }
void mud_Dock__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Dock(  ); }
void mud_Dock__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Dock((*static_cast<mud::Dock*>(other))); }
void mud_Gradient__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Gradient(  ); }
void mud_Gradient__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Gradient((*static_cast<mud::Gradient*>(other))); }
void mud_ImageSkin__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ImageSkin( *static_cast<mud::Image*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]), *static_cast<int*>(args[3]), *static_cast<int*>(args[4]), *static_cast<int*>(args[5]), *static_cast<mud::Axis*>(args[6]) ); }
void mud_ImageSkin__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ImageSkin((*static_cast<mud::ImageSkin*>(other))); }
void mud_InkStyle__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::InkStyle(  ); }
void mud_InkStyle__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::InkStyle( *static_cast<stl::string*>(args[0]) ); }
void mud_InkStyle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::InkStyle((*static_cast<mud::InkStyle*>(other))); }
void mud_Layout__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Layout(  ); }
void mud_Layout__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Layout( *static_cast<stl::string*>(args[0]) ); }
void mud_Layout__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Layout((*static_cast<mud::Layout*>(other))); }
void mud_NodeConnection__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::NodeConnection(  ); }
void mud_NodeConnection__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::NodeConnection((*static_cast<mud::NodeConnection*>(other))); }
void mud_Paint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Paint(  ); }
void mud_Paint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Paint((*static_cast<mud::Paint*>(other))); }
void mud_Shadow__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Shadow( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<mud::Colour*>(args[4]) ); }
void mud_Shadow__construct_1(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Shadow(  ); }
void mud_Shadow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Shadow((*static_cast<mud::Shadow*>(other))); }
void mud_Space__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Space(  ); }
void mud_Space__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Space((*static_cast<mud::Space*>(other))); }
void mud_Subskin__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Subskin(  ); }
void mud_Subskin__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Subskin((*static_cast<mud::Subskin*>(other))); }
void mud_TextCursor__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::TextCursor(  ); }
void mud_TextCursor__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::TextCursor((*static_cast<mud::TextCursor*>(other))); }
void mud_TextMarker__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::TextMarker(  ); }
void mud_TextMarker__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::TextMarker((*static_cast<mud::TextMarker*>(other))); }
void mud_TextPaint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::TextPaint(  ); }
void mud_TextPaint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::TextPaint((*static_cast<mud::TextPaint*>(other))); }
void mud_TextSelection__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::TextSelection(  ); }
void mud_TextSelection__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::TextSelection((*static_cast<mud::TextSelection*>(other))); }
void mud_UiRect__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::UiRect(  ); }
void mud_UiRect__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::UiRect((*static_cast<mud::UiRect*>(other))); }
void* mud_UiWindow__get_context(void* object) { return &(*static_cast<mud::UiWindow*>(object)).m_context; }
void* mud_UiWindow__get_vg(void* object) { return &(*static_cast<mud::UiWindow*>(object)).m_vg; }
void mud_v2_mud_Align__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<mud::Align>(  ); }
void mud_v2_mud_Align__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<mud::Align>( *static_cast<mud::Align*>(args[0]) ); }
void mud_v2_mud_Align__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<mud::Align>( *static_cast<mud::Align*>(args[0]), *static_cast<mud::Align*>(args[1]) ); }
void mud_v2_mud_Align__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<mud::Align>((*static_cast<mud::v2<mud::Align>*>(other))); }
void mud_v2_mud_AutoLayout__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<mud::AutoLayout>(  ); }
void mud_v2_mud_AutoLayout__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<mud::AutoLayout>( *static_cast<mud::AutoLayout*>(args[0]) ); }
void mud_v2_mud_AutoLayout__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<mud::AutoLayout>( *static_cast<mud::AutoLayout*>(args[0]), *static_cast<mud::AutoLayout*>(args[1]) ); }
void mud_v2_mud_AutoLayout__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<mud::AutoLayout>((*static_cast<mud::v2<mud::AutoLayout>*>(other))); }
void mud_v2_mud_Pivot__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<mud::Pivot>(  ); }
void mud_v2_mud_Pivot__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<mud::Pivot>( *static_cast<mud::Pivot*>(args[0]) ); }
void mud_v2_mud_Pivot__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<mud::Pivot>( *static_cast<mud::Pivot*>(args[0]), *static_cast<mud::Pivot*>(args[1]) ); }
void mud_v2_mud_Pivot__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<mud::Pivot>((*static_cast<mud::v2<mud::Pivot>*>(other))); }
void mud_v2_mud_Sizing__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<mud::Sizing>(  ); }
void mud_v2_mud_Sizing__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<mud::Sizing>( *static_cast<mud::Sizing*>(args[0]) ); }
void mud_v2_mud_Sizing__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<mud::Sizing>( *static_cast<mud::Sizing*>(args[0]), *static_cast<mud::Sizing*>(args[1]) ); }
void mud_v2_mud_Sizing__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<mud::Sizing>((*static_cast<mud::v2<mud::Sizing>*>(other))); }
void mud_v2_size_t__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<size_t>(  ); }
void mud_v2_size_t__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<size_t>( *static_cast<size_t*>(args[0]) ); }
void mud_v2_size_t__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<size_t>( *static_cast<size_t*>(args[0]), *static_cast<size_t*>(args[1]) ); }
void mud_v2_size_t__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<size_t>((*static_cast<mud::v2<size_t>*>(other))); }
void mud_Widget_focused(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).focused(); }
void mud_Widget_hovered(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).hovered(); }
void mud_Widget_pressed(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).pressed(); }
void mud_Widget_activated(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).activated(); }
void mud_Widget_active(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).active(); }
void mud_Widget_selected(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).selected(); }
void mud_Widget_modal(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).modal(); }
void mud_Widget_closed(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).closed(); }
void mud_Widget_ui_window(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Widget*>(object)).ui_window(); }
void mud_Widget_ui(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Widget*>(object)).ui(); }
void mud_Widget_parent_modal(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Widget*>(object)).parent_modal(); }
void mud_Widget_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).clear(); }
void mud_Widget_toggle_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).toggle_state(*static_cast<mud::WidgetState*>(args[0])); }
void mud_Widget_disable_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).disable_state(*static_cast<mud::WidgetState*>(args[0])); }
void mud_Widget_set_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).set_state(*static_cast<mud::WidgetState*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_Widget_enable_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).enable_state(*static_cast<mud::WidgetState*>(args[0])); }
void mud_Widget_clear_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).clear_focus(); }
void mud_Widget_take_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).take_focus(); }
void mud_Widget_yield_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).yield_focus(); }
void mud_Widget_take_modal(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).take_modal(*static_cast<uint32_t*>(args[0])); }
void mud_Widget_yield_modal(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).yield_modal(); }
void mud_Widget_key_event(void* object, span<void*> args, void*& result) { (*static_cast<mud::KeyEvent*>(result)) = (*static_cast<mud::Widget*>(object)).key_event(*static_cast<mud::Key*>(args[0]), *static_cast<mud::EventType*>(args[1]), *static_cast<mud::InputMod*>(args[2])); }
void mud_Widget_key_stroke(void* object, span<void*> args, void*& result) { (*static_cast<mud::KeyEvent*>(result)) = (*static_cast<mud::Widget*>(object)).key_stroke(*static_cast<mud::Key*>(args[0]), *static_cast<mud::InputMod*>(args[1])); }
void mud_Widget_char_stroke(void* object, span<void*> args, void*& result) { (*static_cast<mud::KeyEvent*>(result)) = (*static_cast<mud::Widget*>(object)).char_stroke(*static_cast<mud::Key*>(args[0]), *static_cast<mud::InputMod*>(args[1])); }
void mud_Widget_mouse_event(void* object, span<void*> args, void*& result) { (*static_cast<mud::MouseEvent*>(result)) = (*static_cast<mud::Widget*>(object)).mouse_event(*static_cast<mud::DeviceType*>(args[0]), *static_cast<mud::EventType*>(args[1]), *static_cast<mud::InputMod*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_Ui_begin(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Ui*>(object)).begin(); }
void mud_ui_widget_0(span<void*> args, void*& result) { result = &mud::ui::widget(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<mud::Axis*>(args[3]), *static_cast<mud::v2<size_t>*>(args[4])); }
void mud_ui_item_1(span<void*> args, void*& result) { result = &mud::ui::item(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), static_cast<const char*>(args[2])); }
void mud_ui_multi_item_2(span<void*> args, void*& result) { result = &mud::ui::multi_item(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), static_cast<mud::Style*>(args[3])); }
void mud_ui_spanner_3(span<void*> args, void*& result) { result = &mud::ui::spanner(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), *static_cast<mud::Axis*>(args[2]), *static_cast<float*>(args[3])); }
void mud_ui_spacer_4(span<void*> args, void*& result) { result = &mud::ui::spacer(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_separator_5(span<void*> args, void*& result) { result = &mud::ui::separator(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_icon_6(span<void*> args, void*& result) { result = &mud::ui::icon(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_label_7(span<void*> args, void*& result) { result = &mud::ui::label(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_title_8(span<void*> args, void*& result) { result = &mud::ui::title(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_message_9(span<void*> args, void*& result) { result = &mud::ui::message(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_text_10(span<void*> args, void*& result) { result = &mud::ui::text(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_bullet_11(span<void*> args, void*& result) { result = &mud::ui::bullet(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_selectable_12(span<void*> args, void*& result) { result = &mud::ui::selectable(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_ui_button_13(span<void*> args, void*& result) { result = &mud::ui::button(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_toggle_14(span<void*> args, void*& result) { result = &mud::ui::toggle(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1]), static_cast<const char*>(args[2])); }
void mud_ui_button_15(span<void*> args, void*& result) { result = &mud::ui::button(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_ui_toggle_16(span<void*> args, void*& result) { result = &mud::ui::toggle(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<stl::string*>(args[2])); }
void mud_ui_multi_button_17(span<void*> args, void*& result) { result = &mud::ui::multi_button(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), static_cast<mud::Style*>(args[2])); }
void mud_ui_multi_toggle_18(span<void*> args, void*& result) { result = &mud::ui::multi_toggle(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), static_cast<mud::Style*>(args[3])); }
void mud_ui_modal_button_19(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::modal_button(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void mud_ui_modal_multi_button_20(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::modal_multi_button(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void mud_ui_checkbox_21(span<void*> args, void*& result) { result = &mud::ui::checkbox(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_ui_fill_bar_22(span<void*> args, void*& result) { result = &mud::ui::fill_bar(*static_cast<mud::Widget*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2])); }
void mud_ui_image256_23(span<void*> args, void*& result) { result = &mud::ui::image256(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::Image256*>(args[2])); }
void mud_ui_image256_24(span<void*> args, void*& result) { result = &mud::ui::image256(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::Image256*>(args[2]), *static_cast<mud::vec2*>(args[3])); }
void mud_ui_image256_25(span<void*> args, void*& result) { result = &mud::ui::image256(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::Image256*>(args[2])); }
void mud_ui_image256_26(span<void*> args, void*& result) { result = &mud::ui::image256(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::Image256*>(args[2]), *static_cast<mud::vec2*>(args[3])); }
void mud_ui_radio_choice_27(span<void*> args, void*& result) { result = &mud::ui::radio_choice(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_ui_radio_button_28(span<void*> args, void*& result) { result = &mud::ui::radio_button(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void mud_ui_radio_switch_29(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::radio_switch(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<mud::Axis*>(args[3])); }
void mud_ui_popdown_30(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::popdown(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<mud::vec2*>(args[3]), *static_cast<mud::ui::PopupFlags*>(args[4])); }
void mud_ui_dropdown_31(span<void*> args, void*& result) { result = &mud::ui::dropdown(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), static_cast<const char*>(args[2]), *static_cast<mud::ui::PopupFlags*>(args[3]), *static_cast<bool*>(args[4]), static_cast<mud::Style*>(args[5])); }
void mud_ui_dropdown_input_32(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::dropdown_input(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_typedown_input_33(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::typedown_input(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void mud_ui_menu_choice_34(span<void*> args, void*& result) { result = &mud::ui::menu_choice(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2])); }
void mud_ui_menu_option_35(span<void*> args, void*& result) { result = &mud::ui::menu_option(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_menu_36(span<void*> args, void*& result) { result = &mud::ui::menu(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_ui_menubar_37(span<void*> args, void*& result) { result = &mud::ui::menubar(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_toolbutton_38(span<void*> args, void*& result) { result = &mud::ui::toolbutton(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_tooldock_39(span<void*> args, void*& result) { result = &mud::ui::tooldock(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_toolbar_40(span<void*> args, void*& result) { result = &mud::ui::toolbar(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_ui_select_list_41(span<void*> args, void*& result) { result = &mud::ui::select_list(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_columns_42(span<void*> args, void*& result) { result = &mud::ui::columns(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<float>*>(args[1])); }
void mud_ui_table_43(span<void*> args, void*& result) { result = &mud::ui::table(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<stl::span<float>*>(args[2])); }
void mud_ui_table_row_44(span<void*> args, void*& result) { result = &mud::ui::table_row(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_table_separator_45(span<void*> args, void*& result) { result = &mud::ui::table_separator(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_expandbox_46(span<void*> args, void*& result) { result = &mud::ui::expandbox(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_ui_tree_node_47(span<void*> args, void*& result) { result = &mud::ui::tree_node(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_tree_48(span<void*> args, void*& result) { result = &mud::ui::tree(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_tab_49(span<void*> args, void*& result) { result = mud::ui::tab(*static_cast<mud::Tabber*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_tabber_50(span<void*> args, void*& result) { result = &mud::ui::tabber(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_row_51(span<void*> args, void*& result) { result = &mud::ui::row(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_header_52(span<void*> args, void*& result) { result = &mud::ui::header(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_div_53(span<void*> args, void*& result) { result = &mud::ui::div(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_stack_54(span<void*> args, void*& result) { result = &mud::ui::stack(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_sheet_55(span<void*> args, void*& result) { result = &mud::ui::sheet(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_board_56(span<void*> args, void*& result) { result = &mud::ui::board(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_layout_57(span<void*> args, void*& result) { result = &mud::ui::layout(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_indent_58(span<void*> args, void*& result) { result = &mud::ui::indent(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_screen_59(span<void*> args, void*& result) { result = &mud::ui::screen(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_decal_60(span<void*> args, void*& result) { result = &mud::ui::decal(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_overlay_61(span<void*> args, void*& result) { result = &mud::ui::overlay(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_title_header_62(span<void*> args, void*& result) { result = &mud::ui::title_header(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_dummy_63(span<void*> args, void*& result) { result = &mud::ui::dummy(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1])); }
void mud_ui_popup_64(span<void*> args, void*& result) { result = &mud::ui::popup(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::ui::PopupFlags*>(args[1])); }
void mud_ui_popup_65(span<void*> args, void*& result) { result = &mud::ui::popup(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1]), *static_cast<mud::ui::PopupFlags*>(args[2])); }
void mud_ui_popup_at_66(span<void*> args, void*& result) { result = &mud::ui::popup_at(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1]), *static_cast<mud::ui::PopupFlags*>(args[2])); }
void mud_ui_modal_67(span<void*> args, void*& result) { result = &mud::ui::modal(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_modal_68(span<void*> args, void*& result) { result = &mud::ui::modal(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1])); }
void mud_ui_auto_modal_69(span<void*> args, void*& result) { result = &mud::ui::auto_modal(*static_cast<mud::Widget*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void mud_ui_auto_modal_70(span<void*> args, void*& result) { result = &mud::ui::auto_modal(*static_cast<mud::Widget*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<mud::vec2*>(args[2])); }
void mud_ui_context_71(span<void*> args, void*& result) { result = mud::ui::context(*static_cast<mud::Widget*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<mud::ui::PopupFlags*>(args[2])); }
void mud_ui_hoverbox_72(span<void*> args, void*& result) { result = mud::ui::hoverbox(*static_cast<mud::Widget*>(args[0]), *static_cast<float*>(args[1])); }
void mud_ui_cursor_73(span<void*> args, void*& result) { result = &mud::ui::cursor(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1]), *static_cast<mud::Widget*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_rectangle_74(span<void*> args, void*& result) { result = &mud::ui::rectangle(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec4*>(args[1])); }
void mud_ui_viewport_75(span<void*> args, void*& result) { result = &mud::ui::viewport(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec4*>(args[1])); }
void mud_ui_dockspace_76(span<void*> args, void*& result) { result = &mud::ui::dockspace(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Docksystem*>(args[1])); }
void mud_ui_dockbar_77(span<void*> args, void*& result) { result = &mud::ui::dockbar(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Docksystem*>(args[1])); }
void mud_ui_dockitem_78(span<void*> args, void*& result) { result = mud::ui::dockitem(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Docksystem*>(args[1]), *static_cast<mud::Dock*>(args[2])); }
void mud_ui_drag_float_79(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::drag_float(*static_cast<mud::Widget*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_ui_float2_input_80(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::float2_input(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<stl::span<float>*>(args[2]), *static_cast<mud::StatDef<float>*>(args[3])); }
void mud_ui_float3_input_81(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::float3_input(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<stl::span<float>*>(args[2]), *static_cast<mud::StatDef<float>*>(args[3])); }
void mud_ui_float4_input_82(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::float4_input(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<stl::span<float>*>(args[2]), *static_cast<mud::StatDef<float>*>(args[3])); }
void mud_ui_float2_slider_83(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::float2_slider(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<mud::StatDef<float>*>(args[4])); }
void mud_ui_float3_slider_84(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::float3_slider(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<mud::StatDef<float>*>(args[4])); }
void mud_ui_float4_slider_85(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::float4_slider(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<mud::StatDef<float>*>(args[4])); }
void mud_ui_vec2_edit_86(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::vec2_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1])); }
void mud_ui_vec3_edit_87(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::vec3_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_ui_quat_edit_88(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::quat_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::quat*>(args[1])); }
void mud_ui_color_display_89(span<void*> args, void*& result) { result = &mud::ui::color_display(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_ui_color_edit_90(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_ui_color_edit_simple_91(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_edit_simple(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_ui_color_toggle_edit_92(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_toggle_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_ui_curve_graph_93(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::curve_graph(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<float>*>(args[1]), *static_cast<stl::span<float>*>(args[2])); }
void mud_ui_curve_edit_94(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::curve_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::span<float>*>(args[1]), *static_cast<stl::span<float>*>(args[2])); }
void mud_ui_flag_field_95(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::flag_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<uint8_t*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_ui_radio_field_96(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::radio_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<mud::Axis*>(args[4]), *static_cast<bool*>(args[5])); }
void mud_ui_dropdown_field_97(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::dropdown_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_ui_typedown_field_98(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::typedown_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_ui_color_field_99(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::Colour*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_color_display_field_100(span<void*> args, void*& result) { UNUSED(result);  mud::ui::color_display_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::Colour*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_text_box_101(span<void*> args, void*& result) { result = &mud::ui::text_box(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<size_t*>(args[4]), *static_cast<stl::string*>(args[5])); }
void mud_ui_type_in_102(span<void*> args, void*& result) { result = &mud::ui::type_in(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<size_t*>(args[2]), *static_cast<stl::string*>(args[3])); }
void mud_ui_text_edit_103(span<void*> args, void*& result) { result = &mud::ui::text_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<size_t*>(args[2]), static_cast<stl::vector<stl::string>*>(args[3])); }
void mud_ui_code_edit_104(span<void*> args, void*& result) { result = &mud::ui::code_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<size_t*>(args[2]), static_cast<stl::vector<stl::string>*>(args[3])); }
void mud_ui_node_input_105(span<void*> args, void*& result) { result = &mud::ui::node_input(*static_cast<mud::Node*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<mud::Colour*>(args[3]), *static_cast<bool*>(args[4]), *static_cast<bool*>(args[5])); }
void mud_ui_node_output_106(span<void*> args, void*& result) { result = &mud::ui::node_output(*static_cast<mud::Node*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<mud::Colour*>(args[3]), *static_cast<bool*>(args[4]), *static_cast<bool*>(args[5])); }
void mud_ui_node_107(span<void*> args, void*& result) { result = &mud::ui::node(*static_cast<mud::Canvas*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::vec2*>(args[2]), *static_cast<int*>(args[3]), *static_cast<mud::Ref*>(args[4])); }
void mud_ui_node_cable_108(span<void*> args, void*& result) { result = &mud::ui::node_cable(*static_cast<mud::Canvas*>(args[0]), *static_cast<mud::NodePlug*>(args[1]), *static_cast<mud::NodePlug*>(args[2])); }
void mud_ui_canvas_109(span<void*> args, void*& result) { result = &mud::ui::canvas(*static_cast<mud::Widget*>(args[0]), *static_cast<size_t*>(args[1])); }
void mud_ui_scrollable_110(span<void*> args, void*& result) { result = &mud::ui::scrollable(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_sequence_111(span<void*> args, void*& result) { result = &mud::ui::sequence(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_scroll_sequence_112(span<void*> args, void*& result) { result = &mud::ui::scroll_sequence(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_multiselect_logic_113(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::multiselect_logic(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1]), *static_cast<stl::vector<mud::Ref>*>(args[2])); }
void mud_ui_select_logic_114(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::select_logic(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1]), *static_cast<mud::Ref*>(args[2])); }
void mud_ui_element_115(span<void*> args, void*& result) { result = &mud::ui::element(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_ui_sequence_element_116(span<void*> args, void*& result) { result = &mud::ui::sequence_element(*static_cast<mud::ui::Sequence*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_ui_window_117(span<void*> args, void*& result) { result = &mud::ui::window(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::WindowState*>(args[2])); }
void mud_ui_dir_item_118(span<void*> args, void*& result) { result = &mud::ui::dir_item(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_ui_file_item_119(span<void*> args, void*& result) { result = &mud::ui::file_item(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_ui_file_list_120(span<void*> args, void*& result) { result = &mud::ui::file_list(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_ui_file_browser_121(span<void*> args, void*& result) { result = &mud::ui::file_browser(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_ui_dir_node_122(span<void*> args, void*& result) { result = &mud::ui::dir_node(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_file_node_123(span<void*> args, void*& result) { result = &mud::ui::file_node(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_ui_file_tree_124(span<void*> args, void*& result) { result = &mud::ui::file_tree(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void mud_ui_command_line_125(span<void*> args, void*& result) { result = &mud::ui::command_line(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<stl::string*>(args[2])); }
void mud_ui_console_126(span<void*> args, void*& result) { result = &mud::ui::console(*static_cast<mud::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<stl::string*>(args[3]), *static_cast<size_t*>(args[4])); }

namespace mud
{
	void mud_ui_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::Align>();
		static Meta meta = { t, &namspc({ "mud" }), "Align", sizeof(mud::Align), TypeClass::Enum };
		static cstring ids[] = { "Left", "Center", "Right", "OutLeft", "OutRight", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::Align vars[] = { mud::Align::Left, mud::Align::Center, mud::Align::Right, mud::Align::OutLeft, mud::Align::OutRight, mud::Align::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Align__to_string,
		                           mud_Align__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::AutoLayout>();
		static Meta meta = { t, &namspc({ "mud" }), "AutoLayout", sizeof(mud::AutoLayout), TypeClass::Enum };
		static cstring ids[] = { "None", "Size", "Layout" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::AutoLayout vars[] = { mud::AutoLayout::None, mud::AutoLayout::Size, mud::AutoLayout::Layout};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_AutoLayout__to_string,
		                           mud_AutoLayout__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Clip>();
		static Meta meta = { t, &namspc({ "mud" }), "Clip", sizeof(mud::Clip), TypeClass::Enum };
		static cstring ids[] = { "None", "Clip", "Unclip" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Clip vars[] = { mud::Clip::None, mud::Clip::Clip, mud::Clip::Unclip};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Clip__to_string,
		                           mud_Clip__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::FlowAxis>();
		static Meta meta = { t, &namspc({ "mud" }), "FlowAxis", sizeof(mud::FlowAxis), TypeClass::Enum };
		static cstring ids[] = { "Reading", "Paragraph", "Same", "Flip", "None" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::FlowAxis vars[] = { mud::FlowAxis::Reading, mud::FlowAxis::Paragraph, mud::FlowAxis::Same, mud::FlowAxis::Flip, mud::FlowAxis::None};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_FlowAxis__to_string,
		                           mud_FlowAxis__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::LayoutFlow>();
		static Meta meta = { t, &namspc({ "mud" }), "LayoutFlow", sizeof(mud::LayoutFlow), TypeClass::Enum };
		static cstring ids[] = { "Flow", "Overlay", "Align", "Free" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::LayoutFlow vars[] = { mud::LayoutFlow::Flow, mud::LayoutFlow::Overlay, mud::LayoutFlow::Align, mud::LayoutFlow::Free};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_LayoutFlow__to_string,
		                           mud_LayoutFlow__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Opacity>();
		static Meta meta = { t, &namspc({ "mud" }), "Opacity", sizeof(mud::Opacity), TypeClass::Enum };
		static cstring ids[] = { "Opaque", "Clear", "Hollow" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Opacity vars[] = { mud::Opacity::Opaque, mud::Opacity::Clear, mud::Opacity::Hollow};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Opacity__to_string,
		                           mud_Opacity__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Pivot>();
		static Meta meta = { t, &namspc({ "mud" }), "Pivot", sizeof(mud::Pivot), TypeClass::Enum };
		static cstring ids[] = { "Forward", "Reverse" };
		static uint32_t values[] = { 0, 1 };
		static mud::Pivot vars[] = { mud::Pivot::Forward, mud::Pivot::Reverse};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Pivot__to_string,
		                           mud_Pivot__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::ui::PopupFlags>();
		static Meta meta = { t, &namspc({ "mud", "ui" }), "PopupFlags", sizeof(mud::ui::PopupFlags), TypeClass::Enum };
		static cstring ids[] = { "None", "Modal", "Clamp", "AutoClose", "AutoModal" };
		static uint32_t values[] = { 0, 1, 2, 4, 5 };
		static mud::ui::PopupFlags vars[] = { mud::ui::PopupFlags::None, mud::ui::PopupFlags::Modal, mud::ui::PopupFlags::Clamp, mud::ui::PopupFlags::AutoClose, mud::ui::PopupFlags::AutoModal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_ui_PopupFlags__to_string,
		                           mud_ui_PopupFlags__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Preset>();
		static Meta meta = { t, &namspc({ "mud" }), "Preset", sizeof(mud::Preset), TypeClass::Enum };
		static cstring ids[] = { "Sheet", "Flex", "Item", "Unit", "Block", "Line", "Stack", "Div", "Spacer", "Board", "Layout" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static mud::Preset vars[] = { mud::Preset::Sheet, mud::Preset::Flex, mud::Preset::Item, mud::Preset::Unit, mud::Preset::Block, mud::Preset::Line, mud::Preset::Stack, mud::Preset::Div, mud::Preset::Spacer, mud::Preset::Board, mud::Preset::Layout};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Preset__to_string,
		                           mud_Preset__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Sizing>();
		static Meta meta = { t, &namspc({ "mud" }), "Sizing", sizeof(mud::Sizing), TypeClass::Enum };
		static cstring ids[] = { "Fixed", "Shrink", "Wrap", "Expand" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::Sizing vars[] = { mud::Sizing::Fixed, mud::Sizing::Shrink, mud::Sizing::Wrap, mud::Sizing::Expand};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Sizing__to_string,
		                           mud_Sizing__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Solver>();
		static Meta meta = { t, &namspc({ "mud" }), "Solver", sizeof(mud::Solver), TypeClass::Enum };
		static cstring ids[] = { "Frame", "Row", "Grid", "Table" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::Solver vars[] = { mud::Solver::Frame, mud::Solver::Row, mud::Solver::Grid, mud::Solver::Table};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Solver__to_string,
		                           mud_Solver__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::WidgetState>();
		static Meta meta = { t, &namspc({ "mud" }), "WidgetState", sizeof(mud::WidgetState), TypeClass::Enum };
		static cstring ids[] = { "NOSTATE", "CREATED", "HOVERED", "PRESSED", "ACTIVATED", "ACTIVE", "SELECTED", "DISABLED", "DRAGGED", "FOCUSED", "CLOSED" };
		static uint32_t values[] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
		static mud::WidgetState vars[] = { mud::NOSTATE, mud::CREATED, mud::HOVERED, mud::PRESSED, mud::ACTIVATED, mud::ACTIVE, mud::SELECTED, mud::DISABLED, mud::DRAGGED, mud::FOCUSED, mud::CLOSED};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_WidgetState__to_string,
		                           mud_WidgetState__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::WindowState>();
		static Meta meta = { t, &namspc({ "mud" }), "WindowState", sizeof(mud::WindowState), TypeClass::Enum };
		static cstring ids[] = { "None", "Header", "Dockable", "Closable", "Movable", "Sizable", "Scrollable", "Menu", "Default" };
		static uint32_t values[] = { 0, 2, 4, 8, 16, 32, 64, 128, 122 };
		static mud::WindowState vars[] = { mud::WindowState::None, mud::WindowState::Header, mud::WindowState::Dockable, mud::WindowState::Closable, mud::WindowState::Movable, mud::WindowState::Sizable, mud::WindowState::Scrollable, mud::WindowState::Menu, mud::WindowState::Default};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_WindowState__to_string,
		                           mud_WindowState__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::span<const char*>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<const char*>", sizeof(stl::span<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             stl_span_const_char___size,
		                             stl_span_const_char___at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::vector<mud::Space>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Space>", sizeof(stl::vector<mud::Space>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Space>(),
		                             stl_vector_mud_Space__size,
		                             stl_vector_mud_Space__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Space__push,
		                             stl_vector_mud_Space__add,
		                             stl_vector_mud_Space__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Subskin>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Subskin>", sizeof(stl::vector<mud::Subskin>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Subskin>(),
		                             stl_vector_mud_Subskin__size,
		                             stl_vector_mud_Subskin__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Subskin__push,
		                             stl_vector_mud_Subskin__add,
		                             stl_vector_mud_Subskin__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// mud::CanvasConnect
	{
		Type& t = type<mud::CanvasConnect>();
		static Meta meta = { t, &namspc({ "mud" }), "CanvasConnect", sizeof(mud::CanvasConnect), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CanvasConnect__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CanvasConnect__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Clipboard
	{
		Type& t = type<mud::Clipboard>();
		static Meta meta = { t, &namspc({ "mud" }), "Clipboard", sizeof(mud::Clipboard), TypeClass::Struct };
		// bases
		// defaults
		static stl::string text_default = "";
		static bool line_mode_default = false;
		static stl::vector<stl::string> pasted_default = {};
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Clipboard__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Clipboard__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Clipboard, m_text), type<stl::string>(), "text", &text_default, Member::Value, nullptr },
			{ t, offsetof(mud::Clipboard, m_line_mode), type<bool>(), "line_mode", &line_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::Clipboard, m_pasted), type<stl::vector<stl::string>>(), "pasted", &pasted_default, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Dock
	{
		Type& t = type<mud::Dock>();
		static Meta meta = { t, &namspc({ "mud" }), "Dock", sizeof(mud::Dock), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Dock__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Dock__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Docksystem
	{
		Type& t = type<mud::Docksystem>();
		static Meta meta = { t, &namspc({ "mud" }), "Docksystem", sizeof(mud::Docksystem), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Gradient
	{
		Type& t = type<mud::Gradient>();
		static Meta meta = { t, &namspc({ "mud" }), "Gradient", sizeof(mud::Gradient), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Gradient__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Gradient__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Gradient, m_start), type<mud::Colour>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Gradient, m_end), type<mud::Colour>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::GridSolver
	{
		Type& t = type<mud::GridSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "GridSolver", sizeof(mud::GridSolver), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::ImageSkin
	{
		Type& t = type<mud::ImageSkin>();
		static Meta meta = { t, &namspc({ "mud" }), "ImageSkin", sizeof(mud::ImageSkin), TypeClass::Struct };
		// bases
		// defaults
		static mud::Image* d_image_default = nullptr;
		static int d_left_default = 0;
		static int d_top_default = 0;
		static int d_right_default = 0;
		static int d_bottom_default = 0;
		static int margin_default = 0;
		static mud::Axis d_stretch_default = mud::Axis::None;
		static int construct_0_margin_default = 0;
		static mud::Axis construct_0_stretch_default = mud::Axis::None;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ImageSkin__construct_0, { { "image", type<mud::Image>(),  }, { "left", type<int>(),  }, { "top", type<int>(),  }, { "right", type<int>(),  }, { "bottom", type<int>(),  }, { "margin", type<int>(), Param::Default, &construct_0_margin_default }, { "stretch", type<mud::Axis>(), Param::Default, &construct_0_stretch_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ImageSkin__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ImageSkin, d_image), type<mud::Image>(), "d_image", d_image_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::ImageSkin, d_left), type<int>(), "d_left", &d_left_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImageSkin, d_top), type<int>(), "d_top", &d_top_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImageSkin, d_right), type<int>(), "d_right", &d_right_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImageSkin, d_bottom), type<int>(), "d_bottom", &d_bottom_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImageSkin, m_margin), type<int>(), "margin", &margin_default, Member::Value, nullptr },
			{ t, offsetof(mud::ImageSkin, d_stretch), type<mud::Axis>(), "d_stretch", &d_stretch_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::InkStyle
	{
		Type& t = type<mud::InkStyle>();
		static Meta meta = { t, &namspc({ "mud" }), "InkStyle", sizeof(mud::InkStyle), TypeClass::Struct };
		// bases
		// defaults
		static stl::string name_default = "";
		static bool empty_default = true;
		static mud::Colour background_colour_default = mud::Colour::None;
		static mud::Colour border_colour_default = mud::Colour::None;
		static mud::Colour image_colour_default = mud::Colour::None;
		static mud::Colour text_colour_default = mud::Colour::None;
		static stl::string text_font_default = "dejavu";
		static float text_size_default = 13.f;
		static bool text_break_default = false;
		static bool text_wrap_default = false;
		static bool weak_corners_default = false;
		static mud::v2<mud::Align> align_default = {Align::Left,Align::Left};
		static mud::Axis linear_gradient_dim_default = mud::Axis::Y;
		static mud::v2<bool> stretch_default = {false,false};
		static mud::Image* image_default = nullptr;
		static mud::Image* overlay_default = nullptr;
		static mud::Image* tile_default = nullptr;
		static mud::Style* hover_cursor_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_InkStyle__construct_0, {} },
			{ t, mud_InkStyle__construct_1, { { "name", type<stl::string>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_InkStyle__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::InkStyle, m_name), type<stl::string>(), "name", &name_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_empty), type<bool>(), "empty", &empty_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_background_colour), type<mud::Colour>(), "background_colour", &background_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_border_colour), type<mud::Colour>(), "border_colour", &border_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_image_colour), type<mud::Colour>(), "image_colour", &image_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_colour), type<mud::Colour>(), "text_colour", &text_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_font), type<stl::string>(), "text_font", &text_font_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_size), type<float>(), "text_size", &text_size_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_break), type<bool>(), "text_break", &text_break_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_wrap), type<bool>(), "text_wrap", &text_wrap_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_border_width), type<mud::vec4>(), "border_width", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_corner_radius), type<mud::vec4>(), "corner_radius", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_weak_corners), type<bool>(), "weak_corners", &weak_corners_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_padding), type<mud::vec4>(), "padding", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_margin), type<mud::vec4>(), "margin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_align), type<mud::v2<mud::Align>>(), "align", &align_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_linear_gradient), type<mud::vec2>(), "linear_gradient", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_linear_gradient_dim), type<mud::Axis>(), "linear_gradient_dim", &linear_gradient_dim_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_stretch), type<mud::v2<bool>>(), "stretch", &stretch_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_image), type<mud::Image>(), "image", image_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::InkStyle, m_overlay), type<mud::Image>(), "overlay", overlay_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::InkStyle, m_tile), type<mud::Image>(), "tile", tile_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::InkStyle, m_image_skin), type<mud::ImageSkin>(), "image_skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_shadow), type<mud::Shadow>(), "shadow", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_shadow_colour), type<mud::Colour>(), "shadow_colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_hover_cursor), type<mud::Style>(), "hover_cursor", hover_cursor_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Layer
	{
		Type& t = type<mud::Layer>();
		static Meta meta = { t, &namspc({ "mud" }), "Layer", sizeof(mud::Layer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Layout
	{
		Type& t = type<mud::Layout>();
		static Meta meta = { t, &namspc({ "mud" }), "Layout", sizeof(mud::Layout), TypeClass::Struct };
		// bases
		// defaults
		static stl::string name_default = "";
		static mud::Solver solver_default = mud::Solver::Frame;
		static mud::v2<mud::AutoLayout> layout_default = {AutoLayout::Layout,AutoLayout::Layout};
		static mud::LayoutFlow flow_default = mud::LayoutFlow::Flow;
		static mud::Space space_default = Preset::Sheet;
		static mud::Clip clipping_default = mud::Clip::None;
		static mud::Opacity opacity_default = mud::Opacity::Clear;
		static mud::v2<mud::Align> align_default = {Align::Left,Align::Left};
		static mud::v2<mud::Pivot> pivot_default = {Pivot::Forward,Pivot::Forward};
		static int zorder_default = 0;
		static bool no_grid_default = false;
		static size_t updated_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Layout__construct_0, {} },
			{ t, mud_Layout__construct_1, { { "name", type<stl::string>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Layout__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Layout, m_name), type<stl::string>(), "name", &name_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_solver), type<mud::Solver>(), "solver", &solver_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_layout), type<mud::v2<mud::AutoLayout>>(), "layout", &layout_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_flow), type<mud::LayoutFlow>(), "flow", &flow_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_space), type<mud::Space>(), "space", &space_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_clipping), type<mud::Clip>(), "clipping", &clipping_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_opacity), type<mud::Opacity>(), "opacity", &opacity_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_align), type<mud::v2<mud::Align>>(), "align", &align_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_span), type<mud::vec2>(), "span", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_size), type<mud::vec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_padding), type<mud::vec4>(), "padding", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_margin), type<mud::vec2>(), "margin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_spacing), type<mud::vec2>(), "spacing", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_pivot), type<mud::v2<mud::Pivot>>(), "pivot", &pivot_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_zorder), type<int>(), "zorder", &zorder_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_no_grid), type<bool>(), "no_grid", &no_grid_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_grid_division), type<stl::vector<mud::Space>>(), "grid_division", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Layout, m_table_division), type<stl::vector<float>>(), "table_division", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Layout, m_updated), type<size_t>(), "updated", &updated_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::NodeConnection
	{
		Type& t = type<mud::NodeConnection>();
		static Meta meta = { t, &namspc({ "mud" }), "NodeConnection", sizeof(mud::NodeConnection), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_NodeConnection__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_NodeConnection__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Paint
	{
		Type& t = type<mud::Paint>();
		static Meta meta = { t, &namspc({ "mud" }), "Paint", sizeof(mud::Paint), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Paint__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Paint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Paint, m_fill_colour), type<mud::Colour>(), "fill_colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Paint, m_stroke_colour), type<mud::Colour>(), "stroke_colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Paint, m_stroke_width), type<float>(), "stroke_width", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Shadow
	{
		Type& t = type<mud::Shadow>();
		static Meta meta = { t, &namspc({ "mud" }), "Shadow", sizeof(mud::Shadow), TypeClass::Struct };
		// bases
		// defaults
		static mud::Colour construct_0_colour_default = mud::Colour::AlphaBlack;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Shadow__construct_0, { { "xpos", type<float>(),  }, { "ypos", type<float>(),  }, { "blur", type<float>(),  }, { "spread", type<float>(),  }, { "colour", type<mud::Colour>(), Param::Default, &construct_0_colour_default } } },
			{ t, mud_Shadow__construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Shadow__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Shadow, d_xpos), type<float>(), "d_xpos", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shadow, d_ypos), type<float>(), "d_ypos", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shadow, d_blur), type<float>(), "d_blur", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shadow, d_spread), type<float>(), "d_spread", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Shadow, d_colour), type<mud::Colour>(), "d_colour", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Space
	{
		Type& t = type<mud::Space>();
		static Meta meta = { t, &namspc({ "mud" }), "Space", sizeof(mud::Space), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Space__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Space__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Space, direction), type<mud::FlowAxis>(), "direction", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Space, sizingLength), type<mud::Sizing>(), "sizingLength", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Space, sizingDepth), type<mud::Sizing>(), "sizingDepth", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Style
	{
		Type& t = type<mud::Style>();
		static Meta meta = { t, &namspc({ "mud" }), "Style", sizeof(mud::Style), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Style, m_base), type<mud::Style>(), "base", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Style, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Style, m_layout), type<mud::Layout>(), "layout", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Style, m_skin), type<mud::InkStyle>(), "skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Style, m_skins), type<stl::vector<mud::Subskin>>(), "skins", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Subskin
	{
		Type& t = type<mud::Subskin>();
		static Meta meta = { t, &namspc({ "mud" }), "Subskin", sizeof(mud::Subskin), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Subskin__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Subskin__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Subskin, skin), type<mud::InkStyle>(), "skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Subskin, state), type<mud::WidgetState>(), "state", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::TableSolver
	{
		Type& t = type<mud::TableSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "TableSolver", sizeof(mud::TableSolver), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Text
	{
		Type& t = type<mud::Text>();
		static Meta meta = { t, &namspc({ "mud" }), "Text", sizeof(mud::Text), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::TextCursor
	{
		Type& t = type<mud::TextCursor>();
		static Meta meta = { t, &namspc({ "mud" }), "TextCursor", sizeof(mud::TextCursor), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TextCursor__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_TextCursor__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::TextMarker
	{
		Type& t = type<mud::TextMarker>();
		static Meta meta = { t, &namspc({ "mud" }), "TextMarker", sizeof(mud::TextMarker), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TextMarker__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_TextMarker__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::TextPaint
	{
		Type& t = type<mud::TextPaint>();
		static Meta meta = { t, &namspc({ "mud" }), "TextPaint", sizeof(mud::TextPaint), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TextPaint__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_TextPaint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::TextPaint, m_font), type<const char*>(), "font", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::TextPaint, m_colour), type<mud::Colour>(), "colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TextPaint, m_size), type<float>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TextPaint, m_align), type<mud::v2<mud::Align>>(), "align", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TextPaint, m_text_break), type<bool>(), "text_break", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TextPaint, m_text_wrap), type<bool>(), "text_wrap", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::TextSelection
	{
		Type& t = type<mud::TextSelection>();
		static Meta meta = { t, &namspc({ "mud" }), "TextSelection", sizeof(mud::TextSelection), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TextSelection__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_TextSelection__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::UiRect
	{
		Type& t = type<mud::UiRect>();
		static Meta meta = { t, &namspc({ "mud" }), "UiRect", sizeof(mud::UiRect), TypeClass::Struct };
		// bases
		// defaults
		static float scale_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_UiRect__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_UiRect__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::UiRect, m_position), type<mud::vec2>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::UiRect, m_size), type<mud::vec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::UiRect, m_content), type<mud::vec2>(), "content", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::UiRect, m_span), type<mud::vec2>(), "span", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::UiRect, m_scale), type<float>(), "scale", &scale_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::UiWindow
	{
		Type& t = type<mud::UiWindow>();
		static Meta meta = { t, &namspc({ "mud" }), "UiWindow", sizeof(mud::UiWindow), TypeClass::Object };
		// bases
		// defaults
		static bool shutdown_default = false;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::UiWindow, m_resource_path), type<stl::string>(), "resource_path", nullptr, Member::Flags(Member::Value|Member::NonMutable), nullptr },
			{ t, SIZE_MAX, type<mud::Context>(), "context", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_UiWindow__get_context },
			{ t, SIZE_MAX, type<mud::Vg>(), "vg", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_UiWindow__get_vg },
			{ t, offsetof(mud::UiWindow, m_size), type<mud::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::UiWindow, m_colour), type<mud::Colour>(), "colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::UiWindow, m_shutdown), type<bool>(), "shutdown", &shutdown_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::User
	{
		Type& t = type<mud::User>();
		static Meta meta = { t, &namspc({ "mud" }), "User", sizeof(mud::User), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Vg
	{
		Type& t = type<mud::Vg>();
		static Meta meta = { t, &namspc({ "mud" }), "Vg", sizeof(mud::Vg), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::v2<mud::Align>
	{
		Type& t = type<mud::v2<mud::Align>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<mud::Align>", sizeof(mud::v2<mud::Align>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_mud_Align__construct_0, {} },
			{ t, mud_v2_mud_Align__construct_1, { { "v", type<mud::Align>(),  } } },
			{ t, mud_v2_mud_Align__construct_2, { { "x", type<mud::Align>(),  }, { "y", type<mud::Align>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_mud_Align__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<mud::Align>, x), type<mud::Align>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<mud::Align>, y), type<mud::Align>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v2<mud::AutoLayout>
	{
		Type& t = type<mud::v2<mud::AutoLayout>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<mud::AutoLayout>", sizeof(mud::v2<mud::AutoLayout>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_mud_AutoLayout__construct_0, {} },
			{ t, mud_v2_mud_AutoLayout__construct_1, { { "v", type<mud::AutoLayout>(),  } } },
			{ t, mud_v2_mud_AutoLayout__construct_2, { { "x", type<mud::AutoLayout>(),  }, { "y", type<mud::AutoLayout>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_mud_AutoLayout__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<mud::AutoLayout>, x), type<mud::AutoLayout>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<mud::AutoLayout>, y), type<mud::AutoLayout>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v2<mud::Pivot>
	{
		Type& t = type<mud::v2<mud::Pivot>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<mud::Pivot>", sizeof(mud::v2<mud::Pivot>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_mud_Pivot__construct_0, {} },
			{ t, mud_v2_mud_Pivot__construct_1, { { "v", type<mud::Pivot>(),  } } },
			{ t, mud_v2_mud_Pivot__construct_2, { { "x", type<mud::Pivot>(),  }, { "y", type<mud::Pivot>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_mud_Pivot__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<mud::Pivot>, x), type<mud::Pivot>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<mud::Pivot>, y), type<mud::Pivot>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v2<mud::Sizing>
	{
		Type& t = type<mud::v2<mud::Sizing>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<mud::Sizing>", sizeof(mud::v2<mud::Sizing>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_mud_Sizing__construct_0, {} },
			{ t, mud_v2_mud_Sizing__construct_1, { { "v", type<mud::Sizing>(),  } } },
			{ t, mud_v2_mud_Sizing__construct_2, { { "x", type<mud::Sizing>(),  }, { "y", type<mud::Sizing>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_mud_Sizing__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<mud::Sizing>, x), type<mud::Sizing>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<mud::Sizing>, y), type<mud::Sizing>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v2<size_t>
	{
		Type& t = type<mud::v2<size_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<size_t>", sizeof(mud::v2<size_t>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_size_t__construct_0, {} },
			{ t, mud_v2_size_t__construct_1, { { "v", type<size_t>(),  } } },
			{ t, mud_v2_size_t__construct_2, { { "x", type<size_t>(),  }, { "y", type<size_t>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_size_t__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<size_t>, x), type<size_t>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<size_t>, y), type<size_t>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Canvas
	{
		Type& t = type<mud::Canvas>();
		static Meta meta = { t, &namspc({ "mud" }), "Canvas", sizeof(mud::Canvas), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Canvas, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Dockable
	{
		Type& t = type<mud::Dockable>();
		static Meta meta = { t, &namspc({ "mud" }), "Dockable", sizeof(mud::Dockable), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Dockable, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Docker
	{
		Type& t = type<mud::Docker>();
		static Meta meta = { t, &namspc({ "mud" }), "Docker", sizeof(mud::Docker), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Docker, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Dockbar
	{
		Type& t = type<mud::Dockbar>();
		static Meta meta = { t, &namspc({ "mud" }), "Dockbar", sizeof(mud::Dockbar), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Docker>() };
		static size_t bases_offsets[] = { base_offset<mud::Dockbar, mud::Docker>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Dockspace
	{
		Type& t = type<mud::Dockspace>();
		static Meta meta = { t, &namspc({ "mud" }), "Dockspace", sizeof(mud::Dockspace), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Docker>() };
		static size_t bases_offsets[] = { base_offset<mud::Dockspace, mud::Docker>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Frame
	{
		Type& t = type<mud::Frame>();
		static Meta meta = { t, &namspc({ "mud" }), "Frame", sizeof(mud::Frame), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::UiRect>() };
		static size_t bases_offsets[] = { base_offset<mud::Frame, mud::UiRect>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::FrameSolver
	{
		Type& t = type<mud::FrameSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "FrameSolver", sizeof(mud::FrameSolver), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::UiRect>() };
		static size_t bases_offsets[] = { base_offset<mud::FrameSolver, mud::UiRect>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Node
	{
		Type& t = type<mud::Node>();
		static Meta meta = { t, &namspc({ "mud" }), "Node", sizeof(mud::Node), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Node, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::NodePlug
	{
		Type& t = type<mud::NodePlug>();
		static Meta meta = { t, &namspc({ "mud" }), "NodePlug", sizeof(mud::NodePlug), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::NodePlug, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::RowSolver
	{
		Type& t = type<mud::RowSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "RowSolver", sizeof(mud::RowSolver), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::FrameSolver>() };
		static size_t bases_offsets[] = { base_offset<mud::RowSolver, mud::FrameSolver>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::LineSolver
	{
		Type& t = type<mud::LineSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "LineSolver", sizeof(mud::LineSolver), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::RowSolver>() };
		static size_t bases_offsets[] = { base_offset<mud::LineSolver, mud::RowSolver>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Widget
	{
		Type& t = type<mud::Widget>();
		static Meta meta = { t, &namspc({ "mud" }), "Widget", sizeof(mud::Widget), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ControlNode>() };
		static size_t bases_offsets[] = { base_offset<mud::Widget, mud::ControlNode>() };
		// defaults
		static mud::WidgetState state_default = CREATED;
		static uint32_t switch_default = 0;
		static uint32_t index_default = 0;
		static bool open_default = false;
		static mud::Widget* body_default = nullptr;
		static mud::InputMod key_event_0_modifier_default = mud::InputMod::Any;
		static mud::InputMod key_stroke_0_modifier_default = mud::InputMod::Any;
		static mud::InputMod char_stroke_0_modifier_default = mud::InputMod::Any;
		static mud::InputMod mouse_event_0_modifier_default = mud::InputMod::None;
		static bool mouse_event_0_consume_default = true;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Widget, m_frame), type<mud::Frame>(), "frame", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Widget, m_state), type<mud::WidgetState>(), "state", &state_default, Member::Value, nullptr },
			{ t, offsetof(mud::Widget, m_switch), type<uint32_t>(), "switch", &switch_default, Member::Value, nullptr },
			{ t, offsetof(mud::Widget, m_index), type<uint32_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(mud::Widget, m_open), type<bool>(), "open", &open_default, Member::Value, nullptr },
			{ t, offsetof(mud::Widget, m_body), type<mud::Widget>(), "body", body_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "focused", Address(), mud_Widget_focused, {}, { &type<bool>(), QualType::None } },
			{ t, "hovered", Address(), mud_Widget_hovered, {}, { &type<bool>(), QualType::None } },
			{ t, "pressed", Address(), mud_Widget_pressed, {}, { &type<bool>(), QualType::None } },
			{ t, "activated", Address(), mud_Widget_activated, {}, { &type<bool>(), QualType::None } },
			{ t, "active", Address(), mud_Widget_active, {}, { &type<bool>(), QualType::None } },
			{ t, "selected", Address(), mud_Widget_selected, {}, { &type<bool>(), QualType::None } },
			{ t, "modal", Address(), mud_Widget_modal, {}, { &type<bool>(), QualType::None } },
			{ t, "closed", Address(), mud_Widget_closed, {}, { &type<bool>(), QualType::None } },
			{ t, "ui_window", Address(), mud_Widget_ui_window, {}, { &type<mud::UiWindow>(), QualType::None } },
			{ t, "ui", Address(), mud_Widget_ui, {}, { &type<mud::Ui>(), QualType::None } },
			{ t, "parent_modal", Address(), mud_Widget_parent_modal, {}, { &type<mud::Widget>(), QualType::None } },
			{ t, "clear", Address(), mud_Widget_clear, {}, g_qvoid },
			{ t, "toggle_state", Address(), mud_Widget_toggle_state, { { "state", type<mud::WidgetState>(),  } }, g_qvoid },
			{ t, "disable_state", Address(), mud_Widget_disable_state, { { "state", type<mud::WidgetState>(),  } }, g_qvoid },
			{ t, "set_state", Address(), mud_Widget_set_state, { { "state", type<mud::WidgetState>(),  }, { "enabled", type<bool>(),  } }, g_qvoid },
			{ t, "enable_state", Address(), mud_Widget_enable_state, { { "state", type<mud::WidgetState>(),  } }, g_qvoid },
			{ t, "clear_focus", Address(), mud_Widget_clear_focus, {}, g_qvoid },
			{ t, "take_focus", Address(), mud_Widget_take_focus, {}, g_qvoid },
			{ t, "yield_focus", Address(), mud_Widget_yield_focus, {}, g_qvoid },
			{ t, "take_modal", Address(), mud_Widget_take_modal, { { "device_filter", type<uint32_t>(),  } }, g_qvoid },
			{ t, "yield_modal", Address(), mud_Widget_yield_modal, {}, g_qvoid },
			{ t, "key_event", Address(), mud_Widget_key_event, { { "code", type<mud::Key>(),  }, { "event_type", type<mud::EventType>(),  }, { "modifier", type<mud::InputMod>(), Param::Default, &key_event_0_modifier_default } }, { &type<mud::KeyEvent>(), QualType::None } },
			{ t, "key_stroke", Address(), mud_Widget_key_stroke, { { "code", type<mud::Key>(),  }, { "modifier", type<mud::InputMod>(), Param::Default, &key_stroke_0_modifier_default } }, { &type<mud::KeyEvent>(), QualType::None } },
			{ t, "char_stroke", Address(), mud_Widget_char_stroke, { { "code", type<mud::Key>(),  }, { "modifier", type<mud::InputMod>(), Param::Default, &char_stroke_0_modifier_default } }, { &type<mud::KeyEvent>(), QualType::None } },
			{ t, "mouse_event", Address(), mud_Widget_mouse_event, { { "device", type<mud::DeviceType>(),  }, { "event_type", type<mud::EventType>(),  }, { "modifier", type<mud::InputMod>(), Param::Default, &mouse_event_0_modifier_default }, { "consume", type<bool>(), Param::Default, &mouse_event_0_consume_default } }, { &type<mud::MouseEvent>(), QualType::None } }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, methods, {}, };
	}
	// mud::Expandbox
	{
		Type& t = type<mud::Expandbox>();
		static Meta meta = { t, &namspc({ "mud" }), "Expandbox", sizeof(mud::Expandbox), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Expandbox, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ScrollSheet
	{
		Type& t = type<mud::ScrollSheet>();
		static Meta meta = { t, &namspc({ "mud" }), "ScrollSheet", sizeof(mud::ScrollSheet), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::ScrollSheet, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ui::Sequence
	{
		Type& t = type<mud::ui::Sequence>();
		static Meta meta = { t, &namspc({ "mud", "ui" }), "Sequence", sizeof(mud::ui::Sequence), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::ui::Sequence, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Tabber
	{
		Type& t = type<mud::Tabber>();
		static Meta meta = { t, &namspc({ "mud" }), "Tabber", sizeof(mud::Tabber), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Tabber, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Table
	{
		Type& t = type<mud::Table>();
		static Meta meta = { t, &namspc({ "mud" }), "Table", sizeof(mud::Table), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Table, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::TextEdit
	{
		Type& t = type<mud::TextEdit>();
		static Meta meta = { t, &namspc({ "mud" }), "TextEdit", sizeof(mud::TextEdit), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::TextEdit, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::TreeNode
	{
		Type& t = type<mud::TreeNode>();
		static Meta meta = { t, &namspc({ "mud" }), "TreeNode", sizeof(mud::TreeNode), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::TreeNode, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Ui
	{
		Type& t = type<mud::Ui>();
		static Meta meta = { t, &namspc({ "mud" }), "Ui", sizeof(mud::Ui), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Ui, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "begin", Address(), mud_Ui_begin, {}, { &type<mud::Widget>(), QualType::None } }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, methods, {}, };
	}
	// mud::Window
	{
		Type& t = type<mud::Window>();
		static Meta meta = { t, &namspc({ "mud" }), "Window", sizeof(mud::Window), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Dockable>() };
		static size_t bases_offsets[] = { base_offset<mud::Window, mud::Dockable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	
	{
		Type& t = type<ushort>();
		static Alias alias = { &t, &namspc({ "mud" }), "PaletteIndex" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<stl::span<uint32_t>>();
		static Alias alias = { &t, &namspc({ "mud" }), "ColourPalette" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<mud::Align>());
		m.m_types.push_back(&type<mud::AutoLayout>());
		m.m_types.push_back(&type<mud::CanvasConnect>());
		m.m_types.push_back(&type<mud::Clip>());
		m.m_types.push_back(&type<mud::Clipboard>());
		m.m_types.push_back(&type<mud::ColourPalette>());
		m.m_types.push_back(&type<mud::Dock>());
		m.m_types.push_back(&type<mud::Docksystem>());
		m.m_types.push_back(&type<mud::FlowAxis>());
		m.m_types.push_back(&type<mud::Gradient>());
		m.m_types.push_back(&type<mud::GridSolver>());
		m.m_types.push_back(&type<mud::ImageSkin>());
		m.m_types.push_back(&type<mud::InkStyle>());
		m.m_types.push_back(&type<mud::Layer>());
		m.m_types.push_back(&type<mud::Layout>());
		m.m_types.push_back(&type<mud::LayoutFlow>());
		m.m_types.push_back(&type<mud::NodeConnection>());
		m.m_types.push_back(&type<mud::Opacity>());
		m.m_types.push_back(&type<mud::Paint>());
		m.m_types.push_back(&type<mud::PaletteIndex>());
		m.m_types.push_back(&type<mud::Pivot>());
		m.m_types.push_back(&type<mud::ui::PopupFlags>());
		m.m_types.push_back(&type<mud::Preset>());
		m.m_types.push_back(&type<mud::Shadow>());
		m.m_types.push_back(&type<mud::Sizing>());
		m.m_types.push_back(&type<mud::Solver>());
		m.m_types.push_back(&type<mud::Space>());
		m.m_types.push_back(&type<mud::Style>());
		m.m_types.push_back(&type<mud::Subskin>());
		m.m_types.push_back(&type<mud::TableSolver>());
		m.m_types.push_back(&type<mud::Text>());
		m.m_types.push_back(&type<mud::TextCursor>());
		m.m_types.push_back(&type<mud::TextMarker>());
		m.m_types.push_back(&type<mud::TextPaint>());
		m.m_types.push_back(&type<mud::TextSelection>());
		m.m_types.push_back(&type<mud::UiRect>());
		m.m_types.push_back(&type<mud::UiWindow>());
		m.m_types.push_back(&type<mud::User>());
		m.m_types.push_back(&type<mud::Vg>());
		m.m_types.push_back(&type<mud::WidgetState>());
		m.m_types.push_back(&type<mud::WindowState>());
		m.m_types.push_back(&type<stl::span<const char*>>());
		m.m_types.push_back(&type<mud::v2<mud::Align>>());
		m.m_types.push_back(&type<mud::v2<mud::AutoLayout>>());
		m.m_types.push_back(&type<mud::v2<mud::Pivot>>());
		m.m_types.push_back(&type<mud::v2<mud::Sizing>>());
		m.m_types.push_back(&type<mud::v2<size_t>>());
		m.m_types.push_back(&type<stl::vector<mud::Space>>());
		m.m_types.push_back(&type<stl::vector<mud::Subskin>>());
		m.m_types.push_back(&type<mud::Canvas>());
		m.m_types.push_back(&type<mud::Dockable>());
		m.m_types.push_back(&type<mud::Docker>());
		m.m_types.push_back(&type<mud::Dockbar>());
		m.m_types.push_back(&type<mud::Dockspace>());
		m.m_types.push_back(&type<mud::Expandbox>());
		m.m_types.push_back(&type<mud::Frame>());
		m.m_types.push_back(&type<mud::FrameSolver>());
		m.m_types.push_back(&type<mud::Widget>());
		m.m_types.push_back(&type<mud::Node>());
		m.m_types.push_back(&type<mud::NodePlug>());
		m.m_types.push_back(&type<mud::RowSolver>());
		m.m_types.push_back(&type<mud::LineSolver>());
		m.m_types.push_back(&type<mud::ScrollSheet>());
		m.m_types.push_back(&type<mud::ui::Sequence>());
		m.m_types.push_back(&type<mud::Tabber>());
		m.m_types.push_back(&type<mud::Table>());
		m.m_types.push_back(&type<mud::TextEdit>());
		m.m_types.push_back(&type<mud::TreeNode>());
		m.m_types.push_back(&type<mud::Ui>());
		m.m_types.push_back(&type<mud::Window>());
		{
			static bool open_default = false;
			static mud::Axis length_default = mud::Axis::None;
			static mud::v2<size_t> index_default = {0,0};
			static Function f = { &namspc({ "mud", "ui" }), "widget", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, bool, mud::Axis, mud::v2<size_t>)>(mud::ui::widget), mud_ui_widget_0, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "open", type<bool>(), Param::Default, &open_default }, { "length", type<mud::Axis>(), Param::Default, &length_default }, { "index", type<mud::v2<size_t>>(), Param::Default, &index_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "item", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, const char*)>(mud::ui::item), mud_ui_item_1, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &content_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "multi_item", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, stl::span<const char*>, mud::Style*)>(mud::ui::multi_item), mud_ui_multi_item_2, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<mud::Style>(), Param::Flags(Param::Nullable|Param::Default), &element_style_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "spanner", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, mud::Axis, float)>(mud::ui::spanner), mud_ui_spanner_3, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "dim", type<mud::Axis>(),  }, { "span", type<float>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "spacer", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::spacer), mud_ui_spacer_4, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "separator", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::separator), mud_ui_separator_5, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "icon", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::icon), mud_ui_icon_6, { { "parent", type<mud::Widget>(),  }, { "image", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "label", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::label), mud_ui_label_7, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "title", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::title), mud_ui_title_8, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "message", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::message), mud_ui_message_9, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "text", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::text), mud_ui_text_10, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "bullet", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::bullet), mud_ui_bullet_11, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "selectable", funcptr<mud::Widget&(*)(mud::Widget&, const char*, bool&)>(mud::ui::selectable), mud_ui_selectable_12, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "selected", type<bool>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "button", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::button), mud_ui_button_13, { { "parent", type<mud::Widget>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &content_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "toggle", funcptr<mud::Widget&(*)(mud::Widget&, bool&, const char*)>(mud::ui::toggle), mud_ui_toggle_14, { { "parent", type<mud::Widget>(),  }, { "on", type<bool>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &content_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "button", funcptr<mud::Widget&(*)(mud::Widget&, const stl::string&)>(mud::ui::button), mud_ui_button_15, { { "parent", type<mud::Widget>(),  }, { "content", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "toggle", funcptr<mud::Widget&(*)(mud::Widget&, bool&, const stl::string&)>(mud::ui::toggle), mud_ui_toggle_16, { { "parent", type<mud::Widget>(),  }, { "on", type<bool>(),  }, { "content", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "multi_button", funcptr<mud::Widget&(*)(mud::Widget&, stl::span<const char*>, mud::Style*)>(mud::ui::multi_button), mud_ui_multi_button_17, { { "parent", type<mud::Widget>(),  }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<mud::Style>(), Param::Flags(Param::Nullable|Param::Default), &element_style_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "multi_toggle", funcptr<mud::Widget&(*)(mud::Widget&, bool&, stl::span<const char*>, mud::Style*)>(mud::ui::multi_toggle), mud_ui_multi_toggle_18, { { "parent", type<mud::Widget>(),  }, { "on", type<bool>(),  }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<mud::Style>(), Param::Flags(Param::Nullable|Param::Default), &element_style_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "modal_button", funcptr<bool(*)(mud::Widget&, mud::Widget&, const char*, uint32_t)>(mud::ui::modal_button), mud_ui_modal_button_19, { { "screen", type<mud::Widget>(),  }, { "parent", type<mud::Widget>(),  }, { "content", type<const char*>(), Param::Nullable }, { "mode", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "modal_multi_button", funcptr<bool(*)(mud::Widget&, mud::Widget&, stl::span<const char*>, uint32_t)>(mud::ui::modal_multi_button), mud_ui_modal_multi_button_20, { { "screen", type<mud::Widget>(),  }, { "parent", type<mud::Widget>(),  }, { "elements", type<stl::span<const char*>>(),  }, { "mode", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "checkbox", funcptr<mud::Widget&(*)(mud::Widget&, bool&)>(mud::ui::checkbox), mud_ui_checkbox_21, { { "parent", type<mud::Widget>(),  }, { "on", type<bool>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::Axis dim_default = mud::Axis::X;
			static Function f = { &namspc({ "mud", "ui" }), "fill_bar", funcptr<mud::Widget&(*)(mud::Widget&, float, mud::Axis)>(mud::ui::fill_bar), mud_ui_fill_bar_22, { { "parent", type<mud::Widget>(),  }, { "percentage", type<float>(),  }, { "dim", type<mud::Axis>(), Param::Default, &dim_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "image256", funcptr<mud::Widget&(*)(mud::Widget&, const char*, const mud::Image256&)>(mud::ui::image256), mud_ui_image256_23, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "source", type<mud::Image256>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "image256", funcptr<mud::Widget&(*)(mud::Widget&, const char*, const mud::Image256&, const mud::vec2&)>(mud::ui::image256), mud_ui_image256_24, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "source", type<mud::Image256>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "image256", funcptr<mud::Widget&(*)(mud::Widget&, const stl::string&, const mud::Image256&)>(mud::ui::image256), mud_ui_image256_25, { { "parent", type<mud::Widget>(),  }, { "name", type<stl::string>(),  }, { "source", type<mud::Image256>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "image256", funcptr<mud::Widget&(*)(mud::Widget&, const stl::string&, const mud::Image256&, const mud::vec2&)>(mud::ui::image256), mud_ui_image256_26, { { "parent", type<mud::Widget>(),  }, { "name", type<stl::string>(),  }, { "source", type<mud::Image256>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "radio_choice", funcptr<mud::Widget&(*)(mud::Widget&, const char*, bool)>(mud::ui::radio_choice), mud_ui_radio_choice_27, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "active", type<bool>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "radio_button", funcptr<mud::Widget&(*)(mud::Widget&, const char*, uint32_t&, uint32_t)>(mud::ui::radio_button), mud_ui_radio_button_28, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "value", type<uint32_t>(),  }, { "index", type<uint32_t>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::Axis dim_default = mud::Axis::X;
			static Function f = { &namspc({ "mud", "ui" }), "radio_switch", funcptr<bool(*)(mud::Widget&, stl::span<const char*>, uint32_t&, mud::Axis)>(mud::ui::radio_switch), mud_ui_radio_switch_29, { { "parent", type<mud::Widget>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "dim", type<mud::Axis>(), Param::Default, &dim_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "popdown", funcptr<bool(*)(mud::Widget&, stl::span<const char*>, uint32_t&, mud::vec2, mud::ui::PopupFlags)>(mud::ui::popdown), mud_ui_popdown_30, { { "parent", type<mud::Widget>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "position", type<mud::vec2>(),  }, { "flags", type<mud::ui::PopupFlags>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool no_toggle_default = false;
			static mud::Style* list_style_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "dropdown", funcptr<mud::Widget&(*)(mud::Widget&, mud::Style&, const char*, mud::ui::PopupFlags, bool, mud::Style*)>(mud::ui::dropdown), mud_ui_dropdown_31, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "value", type<const char*>(), Param::Nullable }, { "flags", type<mud::ui::PopupFlags>(),  }, { "no_toggle", type<bool>(), Param::Default, &no_toggle_default }, { "list_style", type<mud::Style>(), Param::Flags(Param::Nullable|Param::Default), &list_style_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool compact_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "dropdown_input", funcptr<bool(*)(mud::Widget&, stl::span<const char*>, uint32_t&, bool)>(mud::ui::dropdown_input), mud_ui_dropdown_input_32, { { "parent", type<mud::Widget>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "compact", type<bool>(), Param::Default, &compact_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "typedown_input", funcptr<bool(*)(mud::Widget&, stl::span<const char*>, uint32_t&)>(mud::ui::typedown_input), mud_ui_typedown_input_33, { { "parent", type<mud::Widget>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* shortcut_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "menu_choice", funcptr<mud::Widget&(*)(mud::Widget&, const char*, const char*)>(mud::ui::menu_choice), mud_ui_menu_choice_34, { { "parent", type<mud::Widget>(),  }, { "content", type<const char*>(), Param::Nullable }, { "shortcut", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &shortcut_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "menu_option", funcptr<mud::Widget&(*)(mud::Widget&, const char*, const char*, bool)>(mud::ui::menu_option), mud_ui_menu_option_35, { { "parent", type<mud::Widget>(),  }, { "content", type<const char*>(), Param::Nullable }, { "shortcut", type<const char*>(), Param::Nullable }, { "enabled", type<bool>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool submenu_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "menu", funcptr<mud::Widget&(*)(mud::Widget&, const char*, bool)>(mud::ui::menu), mud_ui_menu_36, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "submenu", type<bool>(), Param::Default, &submenu_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "menubar", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::menubar), mud_ui_menubar_37, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "toolbutton", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::toolbutton), mud_ui_toolbutton_38, { { "parent", type<mud::Widget>(),  }, { "icon", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tooldock", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::tooldock), mud_ui_tooldock_39, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool wrap_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "toolbar", funcptr<mud::Widget&(*)(mud::Widget&, bool)>(mud::ui::toolbar), mud_ui_toolbar_40, { { "parent", type<mud::Widget>(),  }, { "wrap", type<bool>(), Param::Default, &wrap_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "select_list", funcptr<mud::ScrollSheet&(*)(mud::Widget&)>(mud::ui::select_list), mud_ui_select_list_41, { { "parent", type<mud::Widget>(),  } }, { &type<mud::ScrollSheet>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "columns", funcptr<mud::Table&(*)(mud::Widget&, stl::span<float>)>(mud::ui::columns), mud_ui_columns_42, { { "parent", type<mud::Widget>(),  }, { "weights", type<stl::span<float>>(),  } }, { &type<mud::Table>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "table", funcptr<mud::Table&(*)(mud::Widget&, stl::span<const char*>, stl::span<float>)>(mud::ui::table), mud_ui_table_43, { { "parent", type<mud::Widget>(),  }, { "columns", type<stl::span<const char*>>(),  }, { "weights", type<stl::span<float>>(),  } }, { &type<mud::Table>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "table_row", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::table_row), mud_ui_table_row_44, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "table_separator", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::table_separator), mud_ui_table_separator_45, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool open_default = true;
			static Function f = { &namspc({ "mud", "ui" }), "expandbox", funcptr<mud::Expandbox&(*)(mud::Widget&, const char*, bool)>(mud::ui::expandbox), mud_ui_expandbox_46, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "open", type<bool>(), Param::Default, &open_default } }, { &type<mud::Expandbox>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool leaf_default = false;
			static bool open_default = true;
			static Function f = { &namspc({ "mud", "ui" }), "tree_node", funcptr<mud::TreeNode&(*)(mud::Widget&, const char*, bool, bool)>(mud::ui::tree_node), mud_ui_tree_node_47, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "leaf", type<bool>(), Param::Default, &leaf_default }, { "open", type<bool>(), Param::Default, &open_default } }, { &type<mud::TreeNode>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tree", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::tree), mud_ui_tree_48, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tab", funcptr<mud::Widget*(*)(mud::Tabber&, const char*)>(mud::ui::tab), mud_ui_tab_49, { { "tabber", type<mud::Tabber>(),  }, { "name", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tabber", funcptr<mud::Tabber&(*)(mud::Widget&)>(mud::ui::tabber), mud_ui_tabber_50, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Tabber>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "row", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::row), mud_ui_row_51, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "header", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::header), mud_ui_header_52, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "div", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::div), mud_ui_div_53, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "stack", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::stack), mud_ui_stack_54, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "sheet", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::sheet), mud_ui_sheet_55, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "board", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::board), mud_ui_board_56, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "layout", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::layout), mud_ui_layout_57, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "indent", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::indent), mud_ui_indent_58, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "screen", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::screen), mud_ui_screen_59, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "decal", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::decal), mud_ui_decal_60, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "overlay", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::overlay), mud_ui_overlay_61, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "title_header", funcptr<mud::Widget&(*)(mud::Widget&, const char*)>(mud::ui::title_header), mud_ui_title_header_62, { { "parent", type<mud::Widget>(),  }, { "title", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dummy", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&)>(mud::ui::dummy), mud_ui_dummy_63, { { "parent", type<mud::Widget>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "popup", funcptr<mud::Widget&(*)(mud::Widget&, mud::ui::PopupFlags)>(mud::ui::popup), mud_ui_popup_64, { { "parent", type<mud::Widget>(),  }, { "flags", type<mud::ui::PopupFlags>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::ui::PopupFlags flags_default = mud::ui::PopupFlags::None;
			static Function f = { &namspc({ "mud", "ui" }), "popup", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::ui::PopupFlags)>(mud::ui::popup), mud_ui_popup_65, { { "parent", type<mud::Widget>(),  }, { "size", type<mud::vec2>(),  }, { "flags", type<mud::ui::PopupFlags>(), Param::Default, &flags_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::ui::PopupFlags flags_default = mud::ui::PopupFlags::None;
			static Function f = { &namspc({ "mud", "ui" }), "popup_at", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::ui::PopupFlags)>(mud::ui::popup_at), mud_ui_popup_at_66, { { "parent", type<mud::Widget>(),  }, { "position", type<mud::vec2>(),  }, { "flags", type<mud::ui::PopupFlags>(), Param::Default, &flags_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "modal", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::modal), mud_ui_modal_67, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "modal", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&)>(mud::ui::modal), mud_ui_modal_68, { { "parent", type<mud::Widget>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "auto_modal", funcptr<mud::Widget&(*)(mud::Widget&, uint32_t)>(mud::ui::auto_modal), mud_ui_auto_modal_69, { { "parent", type<mud::Widget>(),  }, { "mode", type<uint32_t>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "auto_modal", funcptr<mud::Widget&(*)(mud::Widget&, uint32_t, const mud::vec2&)>(mud::ui::auto_modal), mud_ui_auto_modal_70, { { "parent", type<mud::Widget>(),  }, { "mode", type<uint32_t>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::ui::PopupFlags flags_default = mud::ui::PopupFlags::None;
			static Function f = { &namspc({ "mud", "ui" }), "context", funcptr<mud::Widget*(*)(mud::Widget&, uint32_t, mud::ui::PopupFlags)>(mud::ui::context), mud_ui_context_71, { { "parent", type<mud::Widget>(),  }, { "mode", type<uint32_t>(),  }, { "flags", type<mud::ui::PopupFlags>(), Param::Default, &flags_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float delay_default = 0.5f;
			static Function f = { &namspc({ "mud", "ui" }), "hoverbox", funcptr<mud::Widget*(*)(mud::Widget&, float)>(mud::ui::hoverbox), mud_ui_hoverbox_72, { { "parent", type<mud::Widget>(),  }, { "delay", type<float>(), Param::Default, &delay_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool locked_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "cursor", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec2&, mud::Widget&, bool)>(mud::ui::cursor), mud_ui_cursor_73, { { "parent", type<mud::Widget>(),  }, { "position", type<mud::vec2>(),  }, { "hovered", type<mud::Widget>(),  }, { "locked", type<bool>(), Param::Default, &locked_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "rectangle", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec4&)>(mud::ui::rectangle), mud_ui_rectangle_74, { { "parent", type<mud::Widget>(),  }, { "rect", type<mud::vec4>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "viewport", funcptr<mud::Widget&(*)(mud::Widget&, const mud::vec4&)>(mud::ui::viewport), mud_ui_viewport_75, { { "parent", type<mud::Widget>(),  }, { "rect", type<mud::vec4>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dockspace", funcptr<mud::Dockspace&(*)(mud::Widget&, mud::Docksystem&)>(mud::ui::dockspace), mud_ui_dockspace_76, { { "parent", type<mud::Widget>(),  }, { "docksystem", type<mud::Docksystem>(),  } }, { &type<mud::Dockspace>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dockbar", funcptr<mud::Dockbar&(*)(mud::Widget&, mud::Docksystem&)>(mud::ui::dockbar), mud_ui_dockbar_77, { { "parent", type<mud::Widget>(),  }, { "docksystem", type<mud::Docksystem>(),  } }, { &type<mud::Dockbar>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dockitem", funcptr<mud::Widget*(*)(mud::Widget&, mud::Docksystem&, mud::Dock&)>(mud::ui::dockitem), mud_ui_dockitem_78, { { "parent", type<mud::Widget>(),  }, { "docksystem", type<mud::Docksystem>(),  }, { "dock", type<mud::Dock>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float step_default = 0.1f;
			static Function f = { &namspc({ "mud", "ui" }), "drag_float", funcptr<bool(*)(mud::Widget&, float&, float)>(mud::ui::drag_float), mud_ui_drag_float_79, { { "parent", type<mud::Widget>(),  }, { "value", type<float>(),  }, { "step", type<float>(), Param::Default, &step_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "float2_input", funcptr<bool(*)(mud::Widget&, stl::span<const char*>, stl::span<float>, mud::StatDef<float>)>(mud::ui::float2_input), mud_ui_float2_input_80, { { "parent", type<mud::Widget>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<mud::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "float3_input", funcptr<bool(*)(mud::Widget&, stl::span<const char*>, stl::span<float>, mud::StatDef<float>)>(mud::ui::float3_input), mud_ui_float3_input_81, { { "parent", type<mud::Widget>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<mud::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "float4_input", funcptr<bool(*)(mud::Widget&, stl::span<const char*>, stl::span<float>, mud::StatDef<float>)>(mud::ui::float4_input), mud_ui_float4_input_82, { { "parent", type<mud::Widget>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<mud::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "float2_slider", funcptr<bool(*)(mud::Widget&, const char*, stl::span<const char*>, stl::span<float>, mud::StatDef<float>)>(mud::ui::float2_slider), mud_ui_float2_slider_83, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<mud::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "float3_slider", funcptr<bool(*)(mud::Widget&, const char*, stl::span<const char*>, stl::span<float>, mud::StatDef<float>)>(mud::ui::float3_slider), mud_ui_float3_slider_84, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<mud::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "float4_slider", funcptr<bool(*)(mud::Widget&, const char*, stl::span<const char*>, stl::span<float>, mud::StatDef<float>)>(mud::ui::float4_slider), mud_ui_float4_slider_85, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<mud::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "vec2_edit", funcptr<bool(*)(mud::Widget&, mud::vec2&)>(mud::ui::vec2_edit), mud_ui_vec2_edit_86, { { "parent", type<mud::Widget>(),  }, { "vec", type<mud::vec2>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "vec3_edit", funcptr<bool(*)(mud::Widget&, mud::vec3&)>(mud::ui::vec3_edit), mud_ui_vec3_edit_87, { { "parent", type<mud::Widget>(),  }, { "vec", type<mud::vec3>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "quat_edit", funcptr<bool(*)(mud::Widget&, mud::quat&)>(mud::ui::quat_edit), mud_ui_quat_edit_88, { { "parent", type<mud::Widget>(),  }, { "quat", type<mud::quat>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_display", funcptr<mud::Widget&(*)(mud::Widget&, const mud::Colour&)>(mud::ui::color_display), mud_ui_color_display_89, { { "parent", type<mud::Widget>(),  }, { "value", type<mud::Colour>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_edit", funcptr<bool(*)(mud::Widget&, mud::Colour&)>(mud::ui::color_edit), mud_ui_color_edit_90, { { "parent", type<mud::Widget>(),  }, { "value", type<mud::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_edit_simple", funcptr<bool(*)(mud::Widget&, mud::Colour&)>(mud::ui::color_edit_simple), mud_ui_color_edit_simple_91, { { "parent", type<mud::Widget>(),  }, { "value", type<mud::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_toggle_edit", funcptr<bool(*)(mud::Widget&, mud::Colour&)>(mud::ui::color_toggle_edit), mud_ui_color_toggle_edit_92, { { "parent", type<mud::Widget>(),  }, { "value", type<mud::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static stl::span<float> points_default = {};
			static Function f = { &namspc({ "mud", "ui" }), "curve_graph", funcptr<bool(*)(mud::Widget&, stl::span<float>, stl::span<float>)>(mud::ui::curve_graph), mud_ui_curve_graph_93, { { "parent", type<mud::Widget>(),  }, { "values", type<stl::span<float>>(),  }, { "points", type<stl::span<float>>(), Param::Default, &points_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static stl::span<float> points_default = {};
			static Function f = { &namspc({ "mud", "ui" }), "curve_edit", funcptr<bool(*)(mud::Widget&, stl::span<float>, stl::span<float>)>(mud::ui::curve_edit), mud_ui_curve_edit_94, { { "parent", type<mud::Widget>(),  }, { "values", type<stl::span<float>>(),  }, { "points", type<stl::span<float>>(), Param::Default, &points_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "flag_field", funcptr<bool(*)(mud::Widget&, const char*, uint32_t&, uint8_t, bool)>(mud::ui::flag_field), mud_ui_flag_field_95, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<uint32_t>(),  }, { "shift", type<uint8_t>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::Axis dim_default = mud::Axis::X;
			static bool reverse_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "radio_field", funcptr<bool(*)(mud::Widget&, const char*, stl::span<const char*>, uint32_t&, mud::Axis, bool)>(mud::ui::radio_field), mud_ui_radio_field_96, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "dim", type<mud::Axis>(), Param::Default, &dim_default }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "dropdown_field", funcptr<bool(*)(mud::Widget&, const char*, stl::span<const char*>, uint32_t&, bool)>(mud::ui::dropdown_field), mud_ui_dropdown_field_97, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "typedown_field", funcptr<bool(*)(mud::Widget&, const char*, stl::span<const char*>, uint32_t&, bool)>(mud::ui::typedown_field), mud_ui_typedown_field_98, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "color_field", funcptr<bool(*)(mud::Widget&, const char*, mud::Colour&, bool)>(mud::ui::color_field), mud_ui_color_field_99, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<mud::Colour>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "color_display_field", funcptr<void(*)(mud::Widget&, const char*, const mud::Colour&, bool)>(mud::ui::color_display_field), mud_ui_color_display_field_100, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<mud::Colour>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static bool editor_default = false;
			static size_t lines_default = 1;
			static stl::string allowed_chars_default = "";
			static Function f = { &namspc({ "mud", "ui" }), "text_box", funcptr<mud::TextEdit&(*)(mud::Widget&, mud::Style&, stl::string&, bool, size_t, const stl::string&)>(mud::ui::text_box), mud_ui_text_box_101, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "text", type<stl::string>(),  }, { "editor", type<bool>(), Param::Default, &editor_default }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "allowed_chars", type<stl::string>(), Param::Default, &allowed_chars_default } }, { &type<mud::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::string allowed_chars_default = "";
			static Function f = { &namspc({ "mud", "ui" }), "type_in", funcptr<mud::TextEdit&(*)(mud::Widget&, stl::string&, size_t, const stl::string&)>(mud::ui::type_in), mud_ui_type_in_102, { { "parent", type<mud::Widget>(),  }, { "text", type<stl::string>(),  }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "allowed_chars", type<stl::string>(), Param::Default, &allowed_chars_default } }, { &type<mud::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::vector<stl::string>* vocabulary_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "text_edit", funcptr<mud::TextEdit&(*)(mud::Widget&, stl::string&, size_t, stl::vector<stl::string>*)>(mud::ui::text_edit), mud_ui_text_edit_103, { { "parent", type<mud::Widget>(),  }, { "text", type<stl::string>(),  }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "vocabulary", type<stl::vector<stl::string>>(), Param::Flags(Param::Nullable|Param::Default), &vocabulary_default } }, { &type<mud::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::vector<stl::string>* vocabulary_default = nullptr;
			static Function f = { &namspc({ "mud", "ui" }), "code_edit", funcptr<mud::TextEdit&(*)(mud::Widget&, stl::string&, size_t, stl::vector<stl::string>*)>(mud::ui::code_edit), mud_ui_code_edit_104, { { "parent", type<mud::Widget>(),  }, { "text", type<stl::string>(),  }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "vocabulary", type<stl::vector<stl::string>>(), Param::Flags(Param::Nullable|Param::Default), &vocabulary_default } }, { &type<mud::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* icon_default = "";
			static mud::Colour colour_default = mud::Colour::NeonGreen;
			static bool active_default = true;
			static bool connected_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "node_input", funcptr<mud::NodePlug&(*)(mud::Node&, const char*, const char*, const mud::Colour&, bool, bool)>(mud::ui::node_input), mud_ui_node_input_105, { { "node", type<mud::Node>(),  }, { "name", type<const char*>(), Param::Nullable }, { "icon", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &icon_default }, { "colour", type<mud::Colour>(), Param::Default, &colour_default }, { "active", type<bool>(), Param::Default, &active_default }, { "connected", type<bool>(), Param::Default, &connected_default } }, { &type<mud::NodePlug>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* icon_default = "";
			static mud::Colour colour_default = mud::Colour::NeonGreen;
			static bool active_default = true;
			static bool connected_default = false;
			static Function f = { &namspc({ "mud", "ui" }), "node_output", funcptr<mud::NodePlug&(*)(mud::Node&, const char*, const char*, const mud::Colour&, bool, bool)>(mud::ui::node_output), mud_ui_node_output_106, { { "node", type<mud::Node>(),  }, { "name", type<const char*>(), Param::Nullable }, { "icon", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &icon_default }, { "colour", type<mud::Colour>(), Param::Default, &colour_default }, { "active", type<bool>(), Param::Default, &active_default }, { "connected", type<bool>(), Param::Default, &connected_default } }, { &type<mud::NodePlug>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static int order_default = 0;
			static mud::Ref identity_default = {};
			static Function f = { &namspc({ "mud", "ui" }), "node", funcptr<mud::Node&(*)(mud::Canvas&, const char*, mud::vec2&, int, mud::Ref)>(mud::ui::node), mud_ui_node_107, { { "parent", type<mud::Canvas>(),  }, { "title", type<const char*>(), Param::Nullable }, { "position", type<mud::vec2>(),  }, { "order", type<int>(), Param::Default, &order_default }, { "identity", type<mud::Ref>(), Param::Flags(Param::Nullable|Param::Default), &identity_default } }, { &type<mud::Node>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "node_cable", funcptr<mud::Widget&(*)(mud::Canvas&, mud::NodePlug&, mud::NodePlug&)>(mud::ui::node_cable), mud_ui_node_cable_108, { { "canvas", type<mud::Canvas>(),  }, { "plug_out", type<mud::NodePlug>(),  }, { "plug_in", type<mud::NodePlug>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t num_nodes_default = 0;
			static Function f = { &namspc({ "mud", "ui" }), "canvas", funcptr<mud::Canvas&(*)(mud::Widget&, size_t)>(mud::ui::canvas), mud_ui_canvas_109, { { "parent", type<mud::Widget>(),  }, { "num_nodes", type<size_t>(), Param::Default, &num_nodes_default } }, { &type<mud::Canvas>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "scrollable", funcptr<mud::Widget&(*)(mud::Widget&)>(mud::ui::scrollable), mud_ui_scrollable_110, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "sequence", funcptr<mud::ui::Sequence&(*)(mud::Widget&)>(mud::ui::sequence), mud_ui_sequence_111, { { "parent", type<mud::Widget>(),  } }, { &type<mud::ui::Sequence>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "scroll_sequence", funcptr<mud::ui::Sequence&(*)(mud::Widget&)>(mud::ui::scroll_sequence), mud_ui_scroll_sequence_112, { { "parent", type<mud::Widget>(),  } }, { &type<mud::ui::Sequence>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "multiselect_logic", funcptr<bool(*)(mud::Widget&, mud::Ref, stl::vector<mud::Ref>&)>(mud::ui::multiselect_logic), mud_ui_multiselect_logic_113, { { "element", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable }, { "selection", type<stl::vector<mud::Ref>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "select_logic", funcptr<bool(*)(mud::Widget&, mud::Ref, mud::Ref&)>(mud::ui::select_logic), mud_ui_select_logic_114, { { "element", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable }, { "selection", type<mud::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "element", funcptr<mud::Widget&(*)(mud::Widget&, mud::Ref)>(mud::ui::element), mud_ui_element_115, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "sequence_element", funcptr<mud::Widget&(*)(mud::ui::Sequence&, mud::Ref)>(mud::ui::sequence_element), mud_ui_sequence_element_116, { { "parent", type<mud::ui::Sequence>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::WindowState state_default = mud::WindowState::Default;
			static Function f = { &namspc({ "mud", "ui" }), "window", funcptr<mud::Window&(*)(mud::Widget&, const char*, mud::WindowState)>(mud::ui::window), mud_ui_window_117, { { "parent", type<mud::Widget>(),  }, { "title", type<const char*>(), Param::Nullable }, { "state", type<mud::WindowState>(), Param::Default, &state_default } }, { &type<mud::Window>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dir_item", funcptr<mud::Widget&(*)(mud::Widget&, const stl::string&)>(mud::ui::dir_item), mud_ui_dir_item_118, { { "parent", type<mud::Widget>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_item", funcptr<mud::Widget&(*)(mud::Widget&, const stl::string&)>(mud::ui::file_item), mud_ui_file_item_119, { { "parent", type<mud::Widget>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_list", funcptr<mud::Widget&(*)(mud::Widget&, stl::string&)>(mud::ui::file_list), mud_ui_file_list_120, { { "parent", type<mud::Widget>(),  }, { "path", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_browser", funcptr<mud::Widget&(*)(mud::Widget&, stl::string&)>(mud::ui::file_browser), mud_ui_file_browser_121, { { "parent", type<mud::Widget>(),  }, { "path", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dir_node", funcptr<mud::Widget&(*)(mud::Widget&, const stl::string&, const stl::string&, bool)>(mud::ui::dir_node), mud_ui_dir_node_122, { { "parent", type<mud::Widget>(),  }, { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  }, { "collapsed", type<bool>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_node", funcptr<mud::Widget&(*)(mud::Widget&, const stl::string&)>(mud::ui::file_node), mud_ui_file_node_123, { { "parent", type<mud::Widget>(),  }, { "name", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_tree", funcptr<mud::Widget&(*)(mud::Widget&, const stl::string&)>(mud::ui::file_tree), mud_ui_file_tree_124, { { "parent", type<mud::Widget>(),  }, { "path", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "command_line", funcptr<mud::Widget&(*)(mud::Widget&, stl::string&, stl::string&)>(mud::ui::command_line), mud_ui_command_line_125, { { "parent", type<mud::Widget>(),  }, { "text", type<stl::string>(),  }, { "command", type<stl::string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t num_lines_default = 0;
			static Function f = { &namspc({ "mud", "ui" }), "console", funcptr<mud::Widget&(*)(mud::Widget&, stl::string&, stl::string&, stl::string&, size_t)>(mud::ui::console), mud_ui_console_126, { { "parent", type<mud::Widget>(),  }, { "feed", type<stl::string>(),  }, { "line", type<stl::string>(),  }, { "command", type<stl::string>(),  }, { "num_lines", type<size_t>(), Param::Default, &num_lines_default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_ui::mud_ui()
		: Module("mud::ui", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_ctx::m() })
	{
		// setup reflection meta data
		mud_ui_meta(*this);
	}
}

#ifdef MUD_UI_MODULE
extern "C"
Module& getModule()
{
	return mud_ui::m();
}
#endif
