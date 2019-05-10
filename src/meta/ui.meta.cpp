#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.ui;
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

using namespace two;

void two_FlowAxis__to_string(void* val, string& str) { str = g_enu[type<two::FlowAxis>().m_id]->name(uint32_t((*static_cast<two::FlowAxis*>(val)))); }
void two_FlowAxis__to_value(const string& str, void* val) { (*static_cast<two::FlowAxis*>(val)) = two::FlowAxis(g_enu[type<two::FlowAxis>().m_id]->value(str.c_str())); }
void two_Pivot__to_string(void* val, string& str) { str = g_enu[type<two::Pivot>().m_id]->name(uint32_t((*static_cast<two::Pivot*>(val)))); }
void two_Pivot__to_value(const string& str, void* val) { (*static_cast<two::Pivot*>(val)) = two::Pivot(g_enu[type<two::Pivot>().m_id]->value(str.c_str())); }
void two_Align__to_string(void* val, string& str) { str = g_enu[type<two::Align>().m_id]->name(uint32_t((*static_cast<two::Align*>(val)))); }
void two_Align__to_value(const string& str, void* val) { (*static_cast<two::Align*>(val)) = two::Align(g_enu[type<two::Align>().m_id]->value(str.c_str())); }
void two_Solver__to_string(void* val, string& str) { str = g_enu[type<two::Solver>().m_id]->name(uint32_t((*static_cast<two::Solver*>(val)))); }
void two_Solver__to_value(const string& str, void* val) { (*static_cast<two::Solver*>(val)) = two::Solver(g_enu[type<two::Solver>().m_id]->value(str.c_str())); }
void two_AutoLayout__to_string(void* val, string& str) { str = g_enu[type<two::AutoLayout>().m_id]->name(uint32_t((*static_cast<two::AutoLayout*>(val)))); }
void two_AutoLayout__to_value(const string& str, void* val) { (*static_cast<two::AutoLayout*>(val)) = two::AutoLayout(g_enu[type<two::AutoLayout>().m_id]->value(str.c_str())); }
void two_LayoutFlow__to_string(void* val, string& str) { str = g_enu[type<two::LayoutFlow>().m_id]->name(uint32_t((*static_cast<two::LayoutFlow*>(val)))); }
void two_LayoutFlow__to_value(const string& str, void* val) { (*static_cast<two::LayoutFlow*>(val)) = two::LayoutFlow(g_enu[type<two::LayoutFlow>().m_id]->value(str.c_str())); }
void two_Sizing__to_string(void* val, string& str) { str = g_enu[type<two::Sizing>().m_id]->name(uint32_t((*static_cast<two::Sizing*>(val)))); }
void two_Sizing__to_value(const string& str, void* val) { (*static_cast<two::Sizing*>(val)) = two::Sizing(g_enu[type<two::Sizing>().m_id]->value(str.c_str())); }
void two_Preset__to_string(void* val, string& str) { str = g_enu[type<two::Preset>().m_id]->name(uint32_t((*static_cast<two::Preset*>(val)))); }
void two_Preset__to_value(const string& str, void* val) { (*static_cast<two::Preset*>(val)) = two::Preset(g_enu[type<two::Preset>().m_id]->value(str.c_str())); }
void two_Clip__to_string(void* val, string& str) { str = g_enu[type<two::Clip>().m_id]->name(uint32_t((*static_cast<two::Clip*>(val)))); }
void two_Clip__to_value(const string& str, void* val) { (*static_cast<two::Clip*>(val)) = two::Clip(g_enu[type<two::Clip>().m_id]->value(str.c_str())); }
void two_Opacity__to_string(void* val, string& str) { str = g_enu[type<two::Opacity>().m_id]->name(uint32_t((*static_cast<two::Opacity*>(val)))); }
void two_Opacity__to_value(const string& str, void* val) { (*static_cast<two::Opacity*>(val)) = two::Opacity(g_enu[type<two::Opacity>().m_id]->value(str.c_str())); }
void two_WidgetState__to_string(void* val, string& str) { str = g_enu[type<two::WidgetState>().m_id]->name(uint32_t((*static_cast<two::WidgetState*>(val)))); }
void two_WidgetState__to_value(const string& str, void* val) { (*static_cast<two::WidgetState*>(val)) = two::WidgetState(g_enu[type<two::WidgetState>().m_id]->value(str.c_str())); }
void two_ui_PopupFlags__to_string(void* val, string& str) { str = g_enu[type<two::ui::PopupFlags>().m_id]->name(uint32_t((*static_cast<two::ui::PopupFlags*>(val)))); }
void two_ui_PopupFlags__to_value(const string& str, void* val) { (*static_cast<two::ui::PopupFlags*>(val)) = two::ui::PopupFlags(g_enu[type<two::ui::PopupFlags>().m_id]->value(str.c_str())); }
void two_WindowState__to_string(void* val, string& str) { str = g_enu[type<two::WindowState>().m_id]->name(uint32_t((*static_cast<two::WindowState*>(val)))); }
void two_WindowState__to_value(const string& str, void* val) { (*static_cast<two::WindowState*>(val)) = two::WindowState(g_enu[type<two::WindowState>().m_id]->value(str.c_str())); }
size_t stl_span_const_char___size(void* vec) { return (*static_cast<stl::span<const char*>*>(vec)).size(); }
void* stl_span_const_char___at(void* vec, size_t i) { return &(*static_cast<stl::span<const char*>*>(vec))[i]; }
size_t stl_vector_two_Space__size(void* vec) { return (*static_cast<stl::vector<two::Space>*>(vec)).size(); }
void* stl_vector_two_Space__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Space>*>(vec))[i]; }
void stl_vector_two_Space__push(void* vec) { (*static_cast<stl::vector<two::Space>*>(vec)).emplace_back(); }
void stl_vector_two_Space__add(void* vec, void* value) { (*static_cast<stl::vector<two::Space>*>(vec)).push_back(*static_cast<two::Space*>(value)); }
void stl_vector_two_Space__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Space>*>(vec)), *static_cast<two::Space*>(value)); }
size_t stl_vector_two_Subskin__size(void* vec) { return (*static_cast<stl::vector<two::Subskin>*>(vec)).size(); }
void* stl_vector_two_Subskin__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Subskin>*>(vec))[i]; }
void stl_vector_two_Subskin__push(void* vec) { (*static_cast<stl::vector<two::Subskin>*>(vec)).emplace_back(); }
void stl_vector_two_Subskin__add(void* vec, void* value) { (*static_cast<stl::vector<two::Subskin>*>(vec)).push_back(*static_cast<two::Subskin*>(value)); }
void stl_vector_two_Subskin__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Subskin>*>(vec)), *static_cast<two::Subskin*>(value)); }
void two_Space__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Space(  ); }
void two_Space__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Space((*static_cast<two::Space*>(other))); }
void two_v2_two_AutoLayout__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v2<two::AutoLayout>(  ); }
void two_v2_two_AutoLayout__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::AutoLayout>( *static_cast<two::AutoLayout*>(args[0]) ); }
void two_v2_two_AutoLayout__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::AutoLayout>( *static_cast<two::AutoLayout*>(args[0]), *static_cast<two::AutoLayout*>(args[1]) ); }
void two_v2_two_AutoLayout__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<two::AutoLayout>((*static_cast<two::v2<two::AutoLayout>*>(other))); }
void two_v2_two_Sizing__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v2<two::Sizing>(  ); }
void two_v2_two_Sizing__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Sizing>( *static_cast<two::Sizing*>(args[0]) ); }
void two_v2_two_Sizing__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Sizing>( *static_cast<two::Sizing*>(args[0]), *static_cast<two::Sizing*>(args[1]) ); }
void two_v2_two_Sizing__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<two::Sizing>((*static_cast<two::v2<two::Sizing>*>(other))); }
void two_v2_two_Align__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v2<two::Align>(  ); }
void two_v2_two_Align__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Align>( *static_cast<two::Align*>(args[0]) ); }
void two_v2_two_Align__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Align>( *static_cast<two::Align*>(args[0]), *static_cast<two::Align*>(args[1]) ); }
void two_v2_two_Align__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<two::Align>((*static_cast<two::v2<two::Align>*>(other))); }
void two_v2_two_Pivot__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v2<two::Pivot>(  ); }
void two_v2_two_Pivot__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Pivot>( *static_cast<two::Pivot*>(args[0]) ); }
void two_v2_two_Pivot__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Pivot>( *static_cast<two::Pivot*>(args[0]), *static_cast<two::Pivot*>(args[1]) ); }
void two_v2_two_Pivot__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<two::Pivot>((*static_cast<two::v2<two::Pivot>*>(other))); }
void two_ImageSkin__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ImageSkin( *static_cast<two::Image*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]), *static_cast<int*>(args[3]), *static_cast<int*>(args[4]), *static_cast<int*>(args[5]), *static_cast<two::Axis*>(args[6]) ); }
void two_ImageSkin__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ImageSkin((*static_cast<two::ImageSkin*>(other))); }
void two_Shadow__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Shadow( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<two::Colour*>(args[4]) ); }
void two_Shadow__construct_1(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Shadow(  ); }
void two_Shadow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Shadow((*static_cast<two::Shadow*>(other))); }
void two_Paint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Paint(  ); }
void two_Paint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Paint((*static_cast<two::Paint*>(other))); }
void two_TextPaint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::TextPaint(  ); }
void two_TextPaint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextPaint((*static_cast<two::TextPaint*>(other))); }
void two_Gradient__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Gradient(  ); }
void two_Gradient__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Gradient((*static_cast<two::Gradient*>(other))); }
void two_InkStyle__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::InkStyle(  ); }
void two_InkStyle__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::InkStyle( *static_cast<stl::string*>(args[0]) ); }
void two_InkStyle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::InkStyle((*static_cast<two::InkStyle*>(other))); }
void two_Layout__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Layout(  ); }
void two_Layout__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Layout( *static_cast<stl::string*>(args[0]) ); }
void two_Layout__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Layout((*static_cast<two::Layout*>(other))); }
void two_Subskin__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Subskin(  ); }
void two_Subskin__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Subskin((*static_cast<two::Subskin*>(other))); }
void two_UiRect__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::UiRect(  ); }
void two_UiRect__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::UiRect((*static_cast<two::UiRect*>(other))); }
void two_Widget_focused(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).focused(); }
void two_Widget_hovered(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).hovered(); }
void two_Widget_pressed(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).pressed(); }
void two_Widget_activated(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).activated(); }
void two_Widget_active(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).active(); }
void two_Widget_selected(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).selected(); }
void two_Widget_modal(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).modal(); }
void two_Widget_closed(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).closed(); }
void two_Widget_ui_window(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Widget*>(object)).ui_window(); }
void two_Widget_ui(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Widget*>(object)).ui(); }
void two_Widget_parent_modal(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Widget*>(object)).parent_modal(); }
void two_Widget_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).clear(); }
void two_Widget_toggle_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).toggle_state(*static_cast<two::WidgetState*>(args[0])); }
void two_Widget_disable_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).disable_state(*static_cast<two::WidgetState*>(args[0])); }
void two_Widget_set_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).set_state(*static_cast<two::WidgetState*>(args[0]), *static_cast<bool*>(args[1])); }
void two_Widget_enable_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).enable_state(*static_cast<two::WidgetState*>(args[0])); }
void two_Widget_clear_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).clear_focus(); }
void two_Widget_take_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).take_focus(); }
void two_Widget_yield_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).yield_focus(); }
void two_Widget_take_modal(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).take_modal(*static_cast<uint32_t*>(args[0])); }
void two_Widget_yield_modal(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).yield_modal(); }
void two_Widget_key_event(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::Widget*>(object)).key_event(*static_cast<two::Key*>(args[0]), *static_cast<two::EventType*>(args[1]), *static_cast<two::InputMod*>(args[2])); }
void two_Widget_key_stroke(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::Widget*>(object)).key_stroke(*static_cast<two::Key*>(args[0]), *static_cast<two::InputMod*>(args[1])); }
void two_Widget_char_stroke(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::Widget*>(object)).char_stroke(*static_cast<two::Key*>(args[0]), *static_cast<two::InputMod*>(args[1])); }
void two_Widget_mouse_event(void* object, span<void*> args, void*& result) { (*static_cast<two::MouseEvent*>(result)) = (*static_cast<two::Widget*>(object)).mouse_event(*static_cast<two::DeviceType*>(args[0]), *static_cast<two::EventType*>(args[1]), *static_cast<two::InputMod*>(args[2]), *static_cast<bool*>(args[3])); }
void two_TextCursor__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::TextCursor(  ); }
void two_TextCursor__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextCursor((*static_cast<two::TextCursor*>(other))); }
void two_TextSelection__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::TextSelection(  ); }
void two_TextSelection__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextSelection((*static_cast<two::TextSelection*>(other))); }
void two_TextMarker__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::TextMarker(  ); }
void two_TextMarker__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextMarker((*static_cast<two::TextMarker*>(other))); }
void two_NodeConnection__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::NodeConnection(  ); }
void two_NodeConnection__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::NodeConnection((*static_cast<two::NodeConnection*>(other))); }
void two_Clipboard__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Clipboard(  ); }
void two_Clipboard__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Clipboard((*static_cast<two::Clipboard*>(other))); }
void* two_UiWindow__get_context(void* object) { return &(*static_cast<two::UiWindow*>(object)).m_context; }
void* two_UiWindow__get_vg(void* object) { return &(*static_cast<two::UiWindow*>(object)).m_vg; }
void two_UiWindow_reset_styles(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::UiWindow*>(object)).reset_styles(); }
void two_Dock__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Dock(  ); }
void two_Dock__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Dock((*static_cast<two::Dock*>(other))); }
void two_CanvasConnect__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CanvasConnect(  ); }
void two_CanvasConnect__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CanvasConnect((*static_cast<two::CanvasConnect*>(other))); }
void two_Ui_begin(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Ui*>(object)).begin(); }
void two_Ui_reset_styles(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Ui*>(object)).reset_styles(); }
void two_layout_minimal_0(span<void*> args, void*& result) { UNUSED(result);  two::layout_minimal(*static_cast<two::UiWindow*>(args[0])); }
void two_style_minimal_1(span<void*> args, void*& result) { UNUSED(result);  two::style_minimal(*static_cast<two::UiWindow*>(args[0])); }
void two_style_vector_2(span<void*> args, void*& result) { UNUSED(result);  two::style_vector(*static_cast<two::UiWindow*>(args[0])); }
void two_style_blendish_3(span<void*> args, void*& result) { UNUSED(result);  two::style_blendish(*static_cast<two::UiWindow*>(args[0])); }
void two_style_blendish_light_4(span<void*> args, void*& result) { UNUSED(result);  two::style_blendish_light(*static_cast<two::UiWindow*>(args[0])); }
void two_style_blendish_dark_5(span<void*> args, void*& result) { UNUSED(result);  two::style_blendish_dark(*static_cast<two::UiWindow*>(args[0])); }
void two_style_imgui_dark_6(span<void*> args, void*& result) { UNUSED(result);  two::style_imgui_dark(*static_cast<two::UiWindow*>(args[0])); }
void two_style_imgui_light_7(span<void*> args, void*& result) { UNUSED(result);  two::style_imgui_light(*static_cast<two::UiWindow*>(args[0])); }
void two_style_imgui_classic_8(span<void*> args, void*& result) { UNUSED(result);  two::style_imgui_classic(*static_cast<two::UiWindow*>(args[0])); }
void two_ui_widget_9(span<void*> args, void*& result) { result = &two::ui::widget(*static_cast<two::Widget*>(args[0]), *static_cast<two::Style*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<two::Axis*>(args[3]), *static_cast<two::v2<uint>*>(args[4])); }
void two_ui_item_10(span<void*> args, void*& result) { result = &two::ui::item(*static_cast<two::Widget*>(args[0]), *static_cast<two::Style*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_multi_item_11(span<void*> args, void*& result) { result = &two::ui::multi_item(*static_cast<two::Widget*>(args[0]), *static_cast<two::Style*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), static_cast<two::Style*>(args[3])); }
void two_ui_spanner_12(span<void*> args, void*& result) { result = &two::ui::spanner(*static_cast<two::Widget*>(args[0]), *static_cast<two::Style*>(args[1]), *static_cast<two::Axis*>(args[2]), *static_cast<float*>(args[3])); }
void two_ui_spacer_13(span<void*> args, void*& result) { result = &two::ui::spacer(*static_cast<two::Widget*>(args[0])); }
void two_ui_separator_14(span<void*> args, void*& result) { result = &two::ui::separator(*static_cast<two::Widget*>(args[0])); }
void two_ui_icon_15(span<void*> args, void*& result) { result = &two::ui::icon(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_label_16(span<void*> args, void*& result) { result = &two::ui::label(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_title_17(span<void*> args, void*& result) { result = &two::ui::title(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_message_18(span<void*> args, void*& result) { result = &two::ui::message(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_text_19(span<void*> args, void*& result) { result = &two::ui::text(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_bullet_20(span<void*> args, void*& result) { result = &two::ui::bullet(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_selectable_21(span<void*> args, void*& result) { result = &two::ui::selectable(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void two_ui_button_22(span<void*> args, void*& result) { result = &two::ui::button(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_toggle_23(span<void*> args, void*& result) { result = &two::ui::toggle(*static_cast<two::Widget*>(args[0]), *static_cast<bool*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_button_24(span<void*> args, void*& result) { result = &two::ui::button(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_toggle_25(span<void*> args, void*& result) { result = &two::ui::toggle(*static_cast<two::Widget*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_multi_button_26(span<void*> args, void*& result) { result = &two::ui::multi_button(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), static_cast<two::Style*>(args[2])); }
void two_ui_multi_toggle_27(span<void*> args, void*& result) { result = &two::ui::multi_toggle(*static_cast<two::Widget*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), static_cast<two::Style*>(args[3])); }
void two_ui_modal_button_28(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::modal_button(*static_cast<two::Widget*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void two_ui_modal_multi_button_29(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::modal_multi_button(*static_cast<two::Widget*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void two_ui_checkbox_30(span<void*> args, void*& result) { result = &two::ui::checkbox(*static_cast<two::Widget*>(args[0]), *static_cast<bool*>(args[1])); }
void two_ui_fill_bar_31(span<void*> args, void*& result) { result = &two::ui::fill_bar(*static_cast<two::Widget*>(args[0]), *static_cast<float*>(args[1]), *static_cast<two::Axis*>(args[2])); }
void two_ui_image256_32(span<void*> args, void*& result) { result = &two::ui::image256(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<two::Image256*>(args[2])); }
void two_ui_image256_33(span<void*> args, void*& result) { result = &two::ui::image256(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<two::Image256*>(args[2]), *static_cast<two::vec2*>(args[3])); }
void two_ui_image256_34(span<void*> args, void*& result) { result = &two::ui::image256(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::Image256*>(args[2])); }
void two_ui_image256_35(span<void*> args, void*& result) { result = &two::ui::image256(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::Image256*>(args[2]), *static_cast<two::vec2*>(args[3])); }
void two_ui_radio_choice_36(span<void*> args, void*& result) { result = &two::ui::radio_choice(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void two_ui_radio_button_37(span<void*> args, void*& result) { result = &two::ui::radio_button(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void two_ui_radio_switch_38(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::radio_switch(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<two::Axis*>(args[3])); }
void two_ui_popdown_39(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::popdown(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<two::vec2*>(args[3]), *static_cast<two::ui::PopupFlags*>(args[4])); }
void two_ui_dropdown_40(span<void*> args, void*& result) { result = &two::ui::dropdown(*static_cast<two::Widget*>(args[0]), *static_cast<two::Style*>(args[1]), static_cast<const char*>(args[2]), *static_cast<two::ui::PopupFlags*>(args[3]), *static_cast<bool*>(args[4]), static_cast<two::Style*>(args[5])); }
void two_ui_dropdown_input_41(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::dropdown_input(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_typedown_input_42(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::typedown_input(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void two_ui_menu_choice_43(span<void*> args, void*& result) { result = &two::ui::menu_choice(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_menu_option_44(span<void*> args, void*& result) { result = &two::ui::menu_option(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_menu_45(span<void*> args, void*& result) { result = &two::ui::menu(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void two_ui_menubar_46(span<void*> args, void*& result) { result = &two::ui::menubar(*static_cast<two::Widget*>(args[0])); }
void two_ui_toolbutton_47(span<void*> args, void*& result) { result = &two::ui::toolbutton(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_tooldock_48(span<void*> args, void*& result) { result = &two::ui::tooldock(*static_cast<two::Widget*>(args[0])); }
void two_ui_toolbar_49(span<void*> args, void*& result) { result = &two::ui::toolbar(*static_cast<two::Widget*>(args[0]), *static_cast<bool*>(args[1])); }
void two_ui_select_list_50(span<void*> args, void*& result) { result = &two::ui::select_list(*static_cast<two::Widget*>(args[0])); }
void two_ui_columns_51(span<void*> args, void*& result) { result = &two::ui::columns(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<float>*>(args[1])); }
void two_ui_table_52(span<void*> args, void*& result) { result = &two::ui::table(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<stl::span<float>*>(args[2])); }
void two_ui_table_row_53(span<void*> args, void*& result) { result = &two::ui::table_row(*static_cast<two::Widget*>(args[0])); }
void two_ui_table_separator_54(span<void*> args, void*& result) { result = &two::ui::table_separator(*static_cast<two::Widget*>(args[0])); }
void two_ui_expandbox_55(span<void*> args, void*& result) { result = &two::ui::expandbox(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void two_ui_tree_node_56(span<void*> args, void*& result) { result = &two::ui::tree_node(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_tree_57(span<void*> args, void*& result) { result = &two::ui::tree(*static_cast<two::Widget*>(args[0])); }
void two_ui_tab_58(span<void*> args, void*& result) { result = two::ui::tab(*static_cast<two::Tabber*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_tabber_59(span<void*> args, void*& result) { result = &two::ui::tabber(*static_cast<two::Widget*>(args[0])); }
void two_ui_row_60(span<void*> args, void*& result) { result = &two::ui::row(*static_cast<two::Widget*>(args[0])); }
void two_ui_header_61(span<void*> args, void*& result) { result = &two::ui::header(*static_cast<two::Widget*>(args[0])); }
void two_ui_div_62(span<void*> args, void*& result) { result = &two::ui::div(*static_cast<two::Widget*>(args[0])); }
void two_ui_stack_63(span<void*> args, void*& result) { result = &two::ui::stack(*static_cast<two::Widget*>(args[0])); }
void two_ui_sheet_64(span<void*> args, void*& result) { result = &two::ui::sheet(*static_cast<two::Widget*>(args[0])); }
void two_ui_board_65(span<void*> args, void*& result) { result = &two::ui::board(*static_cast<two::Widget*>(args[0])); }
void two_ui_layout_66(span<void*> args, void*& result) { result = &two::ui::layout(*static_cast<two::Widget*>(args[0])); }
void two_ui_indent_67(span<void*> args, void*& result) { result = &two::ui::indent(*static_cast<two::Widget*>(args[0])); }
void two_ui_screen_68(span<void*> args, void*& result) { result = &two::ui::screen(*static_cast<two::Widget*>(args[0])); }
void two_ui_decal_69(span<void*> args, void*& result) { result = &two::ui::decal(*static_cast<two::Widget*>(args[0])); }
void two_ui_overlay_70(span<void*> args, void*& result) { result = &two::ui::overlay(*static_cast<two::Widget*>(args[0])); }
void two_ui_title_header_71(span<void*> args, void*& result) { result = &two::ui::title_header(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void two_ui_dummy_72(span<void*> args, void*& result) { result = &two::ui::dummy(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec2*>(args[1])); }
void two_ui_popup_73(span<void*> args, void*& result) { result = &two::ui::popup(*static_cast<two::Widget*>(args[0]), *static_cast<two::ui::PopupFlags*>(args[1])); }
void two_ui_popup_74(span<void*> args, void*& result) { result = &two::ui::popup(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec2*>(args[1]), *static_cast<two::ui::PopupFlags*>(args[2])); }
void two_ui_popup_at_75(span<void*> args, void*& result) { result = &two::ui::popup_at(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec2*>(args[1]), *static_cast<two::ui::PopupFlags*>(args[2])); }
void two_ui_modal_76(span<void*> args, void*& result) { result = &two::ui::modal(*static_cast<two::Widget*>(args[0])); }
void two_ui_modal_77(span<void*> args, void*& result) { result = &two::ui::modal(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec2*>(args[1])); }
void two_ui_auto_modal_78(span<void*> args, void*& result) { result = &two::ui::auto_modal(*static_cast<two::Widget*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void two_ui_auto_modal_79(span<void*> args, void*& result) { result = &two::ui::auto_modal(*static_cast<two::Widget*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<two::vec2*>(args[2])); }
void two_ui_context_80(span<void*> args, void*& result) { result = two::ui::context(*static_cast<two::Widget*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<two::ui::PopupFlags*>(args[2])); }
void two_ui_hoverbox_81(span<void*> args, void*& result) { result = two::ui::hoverbox(*static_cast<two::Widget*>(args[0]), *static_cast<float*>(args[1])); }
void two_ui_cursor_82(span<void*> args, void*& result) { result = &two::ui::cursor(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec2*>(args[1]), *static_cast<two::Widget*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_rectangle_83(span<void*> args, void*& result) { result = &two::ui::rectangle(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec4*>(args[1])); }
void two_ui_viewport_84(span<void*> args, void*& result) { result = &two::ui::viewport(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec4*>(args[1])); }
void two_ui_dockspace_85(span<void*> args, void*& result) { result = &two::ui::dockspace(*static_cast<two::Widget*>(args[0]), *static_cast<two::Docksystem*>(args[1])); }
void two_ui_dockbar_86(span<void*> args, void*& result) { result = &two::ui::dockbar(*static_cast<two::Widget*>(args[0]), *static_cast<two::Docksystem*>(args[1])); }
void two_ui_dockitem_87(span<void*> args, void*& result) { result = two::ui::dockitem(*static_cast<two::Widget*>(args[0]), *static_cast<two::Docksystem*>(args[1]), *static_cast<two::Dock*>(args[2])); }
void two_ui_drag_float_88(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::drag_float(*static_cast<two::Widget*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void two_ui_float2_input_89(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float2_input(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<stl::span<float>*>(args[2]), *static_cast<two::StatDef<float>*>(args[3])); }
void two_ui_float3_input_90(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float3_input(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<stl::span<float>*>(args[2]), *static_cast<two::StatDef<float>*>(args[3])); }
void two_ui_float4_input_91(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float4_input(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<const char*>*>(args[1]), *static_cast<stl::span<float>*>(args[2]), *static_cast<two::StatDef<float>*>(args[3])); }
void two_ui_float2_slider_92(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float2_slider(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<two::StatDef<float>*>(args[4])); }
void two_ui_float3_slider_93(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float3_slider(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<two::StatDef<float>*>(args[4])); }
void two_ui_float4_slider_94(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float4_slider(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<two::StatDef<float>*>(args[4])); }
void two_ui_vec2_edit_95(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::vec2_edit(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec2*>(args[1])); }
void two_ui_vec3_edit_96(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::vec3_edit(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_ui_quat_edit_97(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::quat_edit(*static_cast<two::Widget*>(args[0]), *static_cast<two::quat*>(args[1])); }
void two_ui_color_display_98(span<void*> args, void*& result) { result = &two::ui::color_display(*static_cast<two::Widget*>(args[0]), *static_cast<two::Colour*>(args[1])); }
void two_ui_color_edit_99(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::color_edit(*static_cast<two::Widget*>(args[0]), *static_cast<two::Colour*>(args[1])); }
void two_ui_color_edit_simple_100(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::color_edit_simple(*static_cast<two::Widget*>(args[0]), *static_cast<two::Colour*>(args[1])); }
void two_ui_color_toggle_edit_101(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::color_toggle_edit(*static_cast<two::Widget*>(args[0]), *static_cast<two::Colour*>(args[1])); }
void two_ui_curve_graph_102(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::curve_graph(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<float>*>(args[1]), *static_cast<stl::span<float>*>(args[2])); }
void two_ui_curve_edit_103(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::curve_edit(*static_cast<two::Widget*>(args[0]), *static_cast<stl::span<float>*>(args[1]), *static_cast<stl::span<float>*>(args[2])); }
void two_ui_flag_field_104(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::flag_field(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<uint8_t*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_radio_field_105(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::radio_field(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<two::Axis*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_dropdown_field_106(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::dropdown_field(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_typedown_field_107(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::typedown_field(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_color_field_108(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::color_field(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<two::Colour*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_color_display_field_109(span<void*> args, void*& result) { UNUSED(result);  two::ui::color_display_field(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<two::Colour*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_input_bool_110(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<bool>(*static_cast<two::Widget*>(args[0]), *static_cast<bool*>(args[1])); }
void two_ui_input_stl_basic_string___stl_allocator_111(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<stl::basic_string< ::stl::allocator>>(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_input_int_112(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<int>(*static_cast<two::Widget*>(args[0]), *static_cast<int*>(args[1]), *static_cast<two::StatDef<int>*>(args[2])); }
void two_ui_input_float_113(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<float>(*static_cast<two::Widget*>(args[0]), *static_cast<float*>(args[1]), *static_cast<two::StatDef<float>*>(args[2])); }
void two_ui_field_bool_114(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::field<bool>(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_field_stl_basic_string___stl_allocator_115(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::field<stl::basic_string< ::stl::allocator>>(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_field_int_116(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::field<int>(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<int*>(args[2]), *static_cast<two::StatDef<int>*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_field_float_117(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::field<float>(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::StatDef<float>*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_text_box_118(span<void*> args, void*& result) { result = &two::ui::text_box(*static_cast<two::Widget*>(args[0]), *static_cast<two::Style*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<size_t*>(args[4]), *static_cast<stl::string*>(args[5])); }
void two_ui_type_in_119(span<void*> args, void*& result) { result = &two::ui::type_in(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<size_t*>(args[2]), *static_cast<stl::string*>(args[3])); }
void two_ui_text_edit_120(span<void*> args, void*& result) { result = &two::ui::text_edit(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<size_t*>(args[2]), static_cast<stl::vector<stl::string>*>(args[3])); }
void two_ui_code_edit_121(span<void*> args, void*& result) { result = &two::ui::code_edit(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<size_t*>(args[2]), static_cast<stl::vector<stl::string>*>(args[3])); }
void two_ui_input_bool_122(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<bool>(*static_cast<two::Widget*>(args[0]), *static_cast<bool*>(args[1])); }
void two_ui_input_stl_basic_string___stl_allocator_123(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<stl::basic_string< ::stl::allocator>>(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_node_input_124(span<void*> args, void*& result) { result = &two::ui::node_input(*static_cast<two::Node*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<two::Colour*>(args[3]), *static_cast<bool*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_node_output_125(span<void*> args, void*& result) { result = &two::ui::node_output(*static_cast<two::Node*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<two::Colour*>(args[3]), *static_cast<bool*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_node_126(span<void*> args, void*& result) { result = &two::ui::node(*static_cast<two::Canvas*>(args[0]), static_cast<const char*>(args[1]), *static_cast<two::vec2*>(args[2]), *static_cast<int*>(args[3]), *static_cast<two::Ref*>(args[4])); }
void two_ui_node_cable_127(span<void*> args, void*& result) { result = &two::ui::node_cable(*static_cast<two::Canvas*>(args[0]), *static_cast<two::NodePlug*>(args[1]), *static_cast<two::NodePlug*>(args[2])); }
void two_ui_canvas_128(span<void*> args, void*& result) { result = &two::ui::canvas(*static_cast<two::Widget*>(args[0]), *static_cast<size_t*>(args[1])); }
void two_ui_scroll_sheet_129(span<void*> args, void*& result) { result = &two::ui::scroll_sheet(*static_cast<two::Widget*>(args[0]), *static_cast<two::Style*>(args[1]), static_cast<two::Style*>(args[2])); }
void two_ui_scroll_plan_130(span<void*> args, void*& result) { result = &two::ui::scroll_plan(*static_cast<two::Widget*>(args[0]), *static_cast<two::Style*>(args[1])); }
void two_ui_scrollable_131(span<void*> args, void*& result) { result = &two::ui::scrollable(*static_cast<two::Widget*>(args[0])); }
void two_ui_sequence_132(span<void*> args, void*& result) { result = &two::ui::sequence(*static_cast<two::Widget*>(args[0])); }
void two_ui_scroll_sequence_133(span<void*> args, void*& result) { result = &two::ui::scroll_sequence(*static_cast<two::Widget*>(args[0])); }
void two_ui_multiselect_logic_134(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::multiselect_logic(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1]), *static_cast<stl::vector<two::Ref>*>(args[2])); }
void two_ui_select_logic_135(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::select_logic(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1]), *static_cast<two::Ref*>(args[2])); }
void two_ui_element_136(span<void*> args, void*& result) { result = &two::ui::element(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1])); }
void two_ui_sequence_element_137(span<void*> args, void*& result) { result = &two::ui::sequence_element(*static_cast<two::ui::Sequence*>(args[0]), *static_cast<two::Ref*>(args[1])); }
void two_ui_window_138(span<void*> args, void*& result) { result = &two::ui::window(*static_cast<two::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<two::WindowState*>(args[2])); }
void two_ui_dir_item_139(span<void*> args, void*& result) { result = &two::ui::dir_item(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_file_item_140(span<void*> args, void*& result) { result = &two::ui::file_item(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_file_list_141(span<void*> args, void*& result) { result = &two::ui::file_list(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_file_browser_142(span<void*> args, void*& result) { result = &two::ui::file_browser(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_dir_node_143(span<void*> args, void*& result) { result = &two::ui::dir_node(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_file_node_144(span<void*> args, void*& result) { result = &two::ui::file_node(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_file_tree_145(span<void*> args, void*& result) { result = &two::ui::file_tree(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1])); }
void two_ui_command_line_146(span<void*> args, void*& result) { result = &two::ui::command_line(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_console_147(span<void*> args, void*& result) { result = &two::ui::console(*static_cast<two::Widget*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<stl::string*>(args[3]), *static_cast<size_t*>(args[4])); }

namespace two
{
	void two_ui_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::FlowAxis>();
		static Meta meta = { t, &namspc({ "two" }), "FlowAxis", sizeof(two::FlowAxis), TypeClass::Enum };
		static cstring ids[] = { "Reading", "Paragraph", "Same", "Flip", "None" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static two::FlowAxis vars[] = { two::FlowAxis::Reading, two::FlowAxis::Paragraph, two::FlowAxis::Same, two::FlowAxis::Flip, two::FlowAxis::None};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_FlowAxis__to_string,
		                           two_FlowAxis__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Pivot>();
		static Meta meta = { t, &namspc({ "two" }), "Pivot", sizeof(two::Pivot), TypeClass::Enum };
		static cstring ids[] = { "Forward", "Reverse" };
		static uint32_t values[] = { 0, 1 };
		static two::Pivot vars[] = { two::Pivot::Forward, two::Pivot::Reverse};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Pivot__to_string,
		                           two_Pivot__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Align>();
		static Meta meta = { t, &namspc({ "two" }), "Align", sizeof(two::Align), TypeClass::Enum };
		static cstring ids[] = { "Left", "Center", "Right", "OutLeft", "OutRight", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static two::Align vars[] = { two::Align::Left, two::Align::Center, two::Align::Right, two::Align::OutLeft, two::Align::OutRight, two::Align::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Align__to_string,
		                           two_Align__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Solver>();
		static Meta meta = { t, &namspc({ "two" }), "Solver", sizeof(two::Solver), TypeClass::Enum };
		static cstring ids[] = { "Frame", "Row", "Grid", "Table" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::Solver vars[] = { two::Solver::Frame, two::Solver::Row, two::Solver::Grid, two::Solver::Table};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Solver__to_string,
		                           two_Solver__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::AutoLayout>();
		static Meta meta = { t, &namspc({ "two" }), "AutoLayout", sizeof(two::AutoLayout), TypeClass::Enum };
		static cstring ids[] = { "None", "Size", "Layout" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::AutoLayout vars[] = { two::AutoLayout::None, two::AutoLayout::Size, two::AutoLayout::Layout};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_AutoLayout__to_string,
		                           two_AutoLayout__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::LayoutFlow>();
		static Meta meta = { t, &namspc({ "two" }), "LayoutFlow", sizeof(two::LayoutFlow), TypeClass::Enum };
		static cstring ids[] = { "Flow", "Overlay", "Align", "Free" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::LayoutFlow vars[] = { two::LayoutFlow::Flow, two::LayoutFlow::Overlay, two::LayoutFlow::Align, two::LayoutFlow::Free};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_LayoutFlow__to_string,
		                           two_LayoutFlow__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Sizing>();
		static Meta meta = { t, &namspc({ "two" }), "Sizing", sizeof(two::Sizing), TypeClass::Enum };
		static cstring ids[] = { "Fixed", "Shrink", "Wrap", "Expand" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::Sizing vars[] = { two::Sizing::Fixed, two::Sizing::Shrink, two::Sizing::Wrap, two::Sizing::Expand};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Sizing__to_string,
		                           two_Sizing__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Preset>();
		static Meta meta = { t, &namspc({ "two" }), "Preset", sizeof(two::Preset), TypeClass::Enum };
		static cstring ids[] = { "Sheet", "Flex", "Item", "Unit", "Block", "Line", "Stack", "Div", "Spacer", "Board", "Layout" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static two::Preset vars[] = { two::Preset::Sheet, two::Preset::Flex, two::Preset::Item, two::Preset::Unit, two::Preset::Block, two::Preset::Line, two::Preset::Stack, two::Preset::Div, two::Preset::Spacer, two::Preset::Board, two::Preset::Layout};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Preset__to_string,
		                           two_Preset__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Clip>();
		static Meta meta = { t, &namspc({ "two" }), "Clip", sizeof(two::Clip), TypeClass::Enum };
		static cstring ids[] = { "None", "Clip", "Unclip" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::Clip vars[] = { two::Clip::None, two::Clip::Clip, two::Clip::Unclip};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Clip__to_string,
		                           two_Clip__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Opacity>();
		static Meta meta = { t, &namspc({ "two" }), "Opacity", sizeof(two::Opacity), TypeClass::Enum };
		static cstring ids[] = { "Opaque", "Clear", "Hollow" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::Opacity vars[] = { two::Opacity::Opaque, two::Opacity::Clear, two::Opacity::Hollow};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Opacity__to_string,
		                           two_Opacity__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::WidgetState>();
		static Meta meta = { t, &namspc({ "two" }), "WidgetState", sizeof(two::WidgetState), TypeClass::Enum };
		static cstring ids[] = { "NOSTATE", "CREATED", "HOVERED", "PRESSED", "ACTIVATED", "ACTIVE", "SELECTED", "DISABLED", "DRAGGED", "FOCUSED", "CLOSED" };
		static uint32_t values[] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
		static two::WidgetState vars[] = { two::NOSTATE, two::CREATED, two::HOVERED, two::PRESSED, two::ACTIVATED, two::ACTIVE, two::SELECTED, two::DISABLED, two::DRAGGED, two::FOCUSED, two::CLOSED};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_WidgetState__to_string,
		                           two_WidgetState__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::ui::PopupFlags>();
		static Meta meta = { t, &namspc({ "two", "ui" }), "PopupFlags", sizeof(two::ui::PopupFlags), TypeClass::Enum };
		static cstring ids[] = { "None", "Modal", "Clamp", "AutoClose", "AutoModal" };
		static uint32_t values[] = { 0, 1, 2, 4, 5 };
		static two::ui::PopupFlags vars[] = { two::ui::PopupFlags::None, two::ui::PopupFlags::Modal, two::ui::PopupFlags::Clamp, two::ui::PopupFlags::AutoClose, two::ui::PopupFlags::AutoModal};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_ui_PopupFlags__to_string,
		                           two_ui_PopupFlags__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::WindowState>();
		static Meta meta = { t, &namspc({ "two" }), "WindowState", sizeof(two::WindowState), TypeClass::Enum };
		static cstring ids[] = { "None", "Header", "Dockable", "Closable", "Movable", "Sizable", "Scrollable", "Menu", "Default" };
		static uint32_t values[] = { 0, 2, 4, 8, 16, 32, 64, 128, 122 };
		static two::WindowState vars[] = { two::WindowState::None, two::WindowState::Header, two::WindowState::Dockable, two::WindowState::Closable, two::WindowState::Movable, two::WindowState::Sizable, two::WindowState::Scrollable, two::WindowState::Menu, two::WindowState::Default};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_WindowState__to_string,
		                           two_WindowState__to_value };
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
		Type& t = type<stl::vector<two::Space>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Space>", sizeof(stl::vector<two::Space>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Space>(),
		                             stl_vector_two_Space__size,
		                             stl_vector_two_Space__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Space__push,
		                             stl_vector_two_Space__add,
		                             stl_vector_two_Space__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Subskin>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Subskin>", sizeof(stl::vector<two::Subskin>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Subskin>(),
		                             stl_vector_two_Subskin__size,
		                             stl_vector_two_Subskin__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Subskin__push,
		                             stl_vector_two_Subskin__add,
		                             stl_vector_two_Subskin__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// two::Space
	{
		Type& t = type<two::Space>();
		static Meta meta = { t, &namspc({ "two" }), "Space", sizeof(two::Space), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Space__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Space__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Space, direction), type<two::FlowAxis>(), "direction", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Space, sizingLength), type<two::Sizing>(), "sizingLength", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Space, sizingDepth), type<two::Sizing>(), "sizingDepth", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v2<two::AutoLayout>
	{
		Type& t = type<two::v2<two::AutoLayout>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<two::AutoLayout>", sizeof(two::v2<two::AutoLayout>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_two_AutoLayout__construct_0, {} },
			{ t, two_v2_two_AutoLayout__construct_1, { { "v", type<two::AutoLayout>(),  } } },
			{ t, two_v2_two_AutoLayout__construct_2, { { "x", type<two::AutoLayout>(),  }, { "y", type<two::AutoLayout>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_two_AutoLayout__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<two::AutoLayout>, x), type<two::AutoLayout>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<two::AutoLayout>, y), type<two::AutoLayout>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v2<two::Sizing>
	{
		Type& t = type<two::v2<two::Sizing>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<two::Sizing>", sizeof(two::v2<two::Sizing>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_two_Sizing__construct_0, {} },
			{ t, two_v2_two_Sizing__construct_1, { { "v", type<two::Sizing>(),  } } },
			{ t, two_v2_two_Sizing__construct_2, { { "x", type<two::Sizing>(),  }, { "y", type<two::Sizing>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_two_Sizing__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<two::Sizing>, x), type<two::Sizing>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<two::Sizing>, y), type<two::Sizing>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v2<two::Align>
	{
		Type& t = type<two::v2<two::Align>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<two::Align>", sizeof(two::v2<two::Align>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_two_Align__construct_0, {} },
			{ t, two_v2_two_Align__construct_1, { { "v", type<two::Align>(),  } } },
			{ t, two_v2_two_Align__construct_2, { { "x", type<two::Align>(),  }, { "y", type<two::Align>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_two_Align__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<two::Align>, x), type<two::Align>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<two::Align>, y), type<two::Align>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v2<two::Pivot>
	{
		Type& t = type<two::v2<two::Pivot>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<two::Pivot>", sizeof(two::v2<two::Pivot>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_two_Pivot__construct_0, {} },
			{ t, two_v2_two_Pivot__construct_1, { { "v", type<two::Pivot>(),  } } },
			{ t, two_v2_two_Pivot__construct_2, { { "x", type<two::Pivot>(),  }, { "y", type<two::Pivot>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_two_Pivot__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<two::Pivot>, x), type<two::Pivot>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<two::Pivot>, y), type<two::Pivot>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ImageSkin
	{
		Type& t = type<two::ImageSkin>();
		static Meta meta = { t, &namspc({ "two" }), "ImageSkin", sizeof(two::ImageSkin), TypeClass::Struct };
		// bases
		// defaults
		static two::Image* d_image_default = nullptr;
		static int d_left_default = 0;
		static int d_top_default = 0;
		static int d_right_default = 0;
		static int d_bottom_default = 0;
		static int margin_default = 0;
		static two::Axis d_stretch_default = two::Axis::None;
		static int construct_0_margin_default = 0;
		static two::Axis construct_0_stretch_default = two::Axis::None;
		// constructors
		static Constructor constructors[] = {
			{ t, two_ImageSkin__construct_0, { { "image", type<two::Image>(),  }, { "left", type<int>(),  }, { "top", type<int>(),  }, { "right", type<int>(),  }, { "bottom", type<int>(),  }, { "margin", type<int>(), Param::Default, &construct_0_margin_default }, { "stretch", type<two::Axis>(), Param::Default, &construct_0_stretch_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ImageSkin__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ImageSkin, d_image), type<two::Image>(), "d_image", d_image_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::ImageSkin, d_left), type<int>(), "d_left", &d_left_default, Member::Value, nullptr },
			{ t, offsetof(two::ImageSkin, d_top), type<int>(), "d_top", &d_top_default, Member::Value, nullptr },
			{ t, offsetof(two::ImageSkin, d_right), type<int>(), "d_right", &d_right_default, Member::Value, nullptr },
			{ t, offsetof(two::ImageSkin, d_bottom), type<int>(), "d_bottom", &d_bottom_default, Member::Value, nullptr },
			{ t, offsetof(two::ImageSkin, m_margin), type<int>(), "margin", &margin_default, Member::Value, nullptr },
			{ t, offsetof(two::ImageSkin, d_stretch), type<two::Axis>(), "d_stretch", &d_stretch_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Shadow
	{
		Type& t = type<two::Shadow>();
		static Meta meta = { t, &namspc({ "two" }), "Shadow", sizeof(two::Shadow), TypeClass::Struct };
		// bases
		// defaults
		static two::Colour construct_0_colour_default = two::Colour::AlphaBlack;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Shadow__construct_0, { { "xpos", type<float>(),  }, { "ypos", type<float>(),  }, { "blur", type<float>(),  }, { "spread", type<float>(),  }, { "colour", type<two::Colour>(), Param::Default, &construct_0_colour_default } } },
			{ t, two_Shadow__construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Shadow__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Shadow, d_xpos), type<float>(), "d_xpos", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Shadow, d_ypos), type<float>(), "d_ypos", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Shadow, d_blur), type<float>(), "d_blur", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Shadow, d_spread), type<float>(), "d_spread", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Shadow, d_colour), type<two::Colour>(), "d_colour", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Paint
	{
		Type& t = type<two::Paint>();
		static Meta meta = { t, &namspc({ "two" }), "Paint", sizeof(two::Paint), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Paint__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Paint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Paint, m_fill_colour), type<two::Colour>(), "fill_colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Paint, m_stroke_colour), type<two::Colour>(), "stroke_colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Paint, m_stroke_width), type<float>(), "stroke_width", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::TextPaint
	{
		Type& t = type<two::TextPaint>();
		static Meta meta = { t, &namspc({ "two" }), "TextPaint", sizeof(two::TextPaint), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_TextPaint__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextPaint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::TextPaint, m_font), type<const char*>(), "font", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::TextPaint, m_colour), type<two::Colour>(), "colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::TextPaint, m_size), type<float>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::TextPaint, m_align), type<two::v2<two::Align>>(), "align", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::TextPaint, m_text_break), type<bool>(), "text_break", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::TextPaint, m_text_wrap), type<bool>(), "text_wrap", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Gradient
	{
		Type& t = type<two::Gradient>();
		static Meta meta = { t, &namspc({ "two" }), "Gradient", sizeof(two::Gradient), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Gradient__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Gradient__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Gradient, m_start), type<two::Colour>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Gradient, m_end), type<two::Colour>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::InkStyle
	{
		Type& t = type<two::InkStyle>();
		static Meta meta = { t, &namspc({ "two" }), "InkStyle", sizeof(two::InkStyle), TypeClass::Struct };
		// bases
		// defaults
		static stl::string name_default = "";
		static bool empty_default = true;
		static two::Colour background_colour_default = two::Colour::None;
		static two::Colour border_colour_default = two::Colour::None;
		static two::Colour image_colour_default = two::Colour::None;
		static two::Colour text_colour_default = two::Colour::None;
		static stl::string text_font_default = "dejavu";
		static float text_size_default = 13.f;
		static bool text_break_default = false;
		static bool text_wrap_default = false;
		static bool weak_corners_default = false;
		static two::v2<two::Align> align_default = {Align::Left,Align::Left};
		static two::Axis linear_gradient_dim_default = two::Axis::Y;
		static two::v2<bool> stretch_default = {false,false};
		static two::Image* image_default = nullptr;
		static two::Image* overlay_default = nullptr;
		static two::Image* tile_default = nullptr;
		static two::Style* hover_cursor_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, two_InkStyle__construct_0, {} },
			{ t, two_InkStyle__construct_1, { { "name", type<stl::string>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_InkStyle__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::InkStyle, m_name), type<stl::string>(), "name", &name_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_empty), type<bool>(), "empty", &empty_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_background_colour), type<two::Colour>(), "background_colour", &background_colour_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_border_colour), type<two::Colour>(), "border_colour", &border_colour_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_image_colour), type<two::Colour>(), "image_colour", &image_colour_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_text_colour), type<two::Colour>(), "text_colour", &text_colour_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_text_font), type<stl::string>(), "text_font", &text_font_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_text_size), type<float>(), "text_size", &text_size_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_text_break), type<bool>(), "text_break", &text_break_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_text_wrap), type<bool>(), "text_wrap", &text_wrap_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_border_width), type<two::vec4>(), "border_width", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_corner_radius), type<two::vec4>(), "corner_radius", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_weak_corners), type<bool>(), "weak_corners", &weak_corners_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_padding), type<two::vec4>(), "padding", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_margin), type<two::vec4>(), "margin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_align), type<two::v2<two::Align>>(), "align", &align_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_linear_gradient), type<two::vec2>(), "linear_gradient", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_linear_gradient_dim), type<two::Axis>(), "linear_gradient_dim", &linear_gradient_dim_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_stretch), type<two::v2<bool>>(), "stretch", &stretch_default, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_image), type<two::Image>(), "image", image_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::InkStyle, m_overlay), type<two::Image>(), "overlay", overlay_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::InkStyle, m_tile), type<two::Image>(), "tile", tile_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::InkStyle, m_image_skin), type<two::ImageSkin>(), "image_skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_shadow), type<two::Shadow>(), "shadow", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_shadow_colour), type<two::Colour>(), "shadow_colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::InkStyle, m_hover_cursor), type<two::Style>(), "hover_cursor", hover_cursor_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Layout
	{
		Type& t = type<two::Layout>();
		static Meta meta = { t, &namspc({ "two" }), "Layout", sizeof(two::Layout), TypeClass::Struct };
		// bases
		// defaults
		static stl::string name_default = "";
		static two::Solver solver_default = two::Solver::Frame;
		static two::v2<two::AutoLayout> layout_default = {AutoLayout::Layout,AutoLayout::Layout};
		static two::LayoutFlow flow_default = two::LayoutFlow::Flow;
		static two::Space space_default = Preset::Sheet;
		static two::Clip clipping_default = two::Clip::None;
		static two::Opacity opacity_default = two::Opacity::Clear;
		static two::v2<two::Align> align_default = {Align::Left,Align::Left};
		static two::v2<two::Pivot> pivot_default = {Pivot::Forward,Pivot::Forward};
		static int zorder_default = 0;
		static bool no_grid_default = false;
		static size_t updated_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Layout__construct_0, {} },
			{ t, two_Layout__construct_1, { { "name", type<stl::string>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Layout__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Layout, m_name), type<stl::string>(), "name", &name_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_solver), type<two::Solver>(), "solver", &solver_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_layout), type<two::v2<two::AutoLayout>>(), "layout", &layout_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_flow), type<two::LayoutFlow>(), "flow", &flow_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_space), type<two::Space>(), "space", &space_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_clipping), type<two::Clip>(), "clipping", &clipping_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_opacity), type<two::Opacity>(), "opacity", &opacity_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_align), type<two::v2<two::Align>>(), "align", &align_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_span), type<two::vec2>(), "span", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_size), type<two::vec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_padding), type<two::vec4>(), "padding", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_margin), type<two::vec2>(), "margin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_spacing), type<two::vec2>(), "spacing", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_pivot), type<two::v2<two::Pivot>>(), "pivot", &pivot_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_zorder), type<int>(), "zorder", &zorder_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_no_grid), type<bool>(), "no_grid", &no_grid_default, Member::Value, nullptr },
			{ t, offsetof(two::Layout, m_grid_division), type<stl::vector<two::Space>>(), "grid_division", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Layout, m_table_division), type<stl::vector<float>>(), "table_division", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Layout, m_updated), type<size_t>(), "updated", &updated_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Subskin
	{
		Type& t = type<two::Subskin>();
		static Meta meta = { t, &namspc({ "two" }), "Subskin", sizeof(two::Subskin), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Subskin__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Subskin__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Subskin, skin), type<two::InkStyle>(), "skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Subskin, state), type<two::WidgetState>(), "state", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Style
	{
		Type& t = type<two::Style>();
		static Meta meta = { t, &namspc({ "two" }), "Style", sizeof(two::Style), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Style, m_base), type<two::Style>(), "base", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Style, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Style, m_layout), type<two::Layout>(), "layout", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Style, m_skin), type<two::InkStyle>(), "skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Style, m_skins), type<stl::vector<two::Subskin>>(), "skins", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::UiRect
	{
		Type& t = type<two::UiRect>();
		static Meta meta = { t, &namspc({ "two" }), "UiRect", sizeof(two::UiRect), TypeClass::Struct };
		// bases
		// defaults
		static float scale_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_UiRect__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_UiRect__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::UiRect, m_position), type<two::vec2>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::UiRect, m_size), type<two::vec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::UiRect, m_content), type<two::vec2>(), "content", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::UiRect, m_span), type<two::vec2>(), "span", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::UiRect, m_scale), type<float>(), "scale", &scale_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Frame
	{
		Type& t = type<two::Frame>();
		static Meta meta = { t, &namspc({ "two" }), "Frame", sizeof(two::Frame), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::UiRect>() };
		static size_t bases_offsets[] = { base_offset<two::Frame, two::UiRect>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Widget
	{
		Type& t = type<two::Widget>();
		static Meta meta = { t, &namspc({ "two" }), "Widget", sizeof(two::Widget), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ControlNode>() };
		static size_t bases_offsets[] = { base_offset<two::Widget, two::ControlNode>() };
		// defaults
		static two::WidgetState state_default = CREATED;
		static uint32_t switch_default = 0;
		static uint32_t index_default = 0;
		static bool open_default = false;
		static two::Widget* body_default = nullptr;
		static two::InputMod key_event_0_modifier_default = two::InputMod::Any;
		static two::InputMod key_stroke_0_modifier_default = two::InputMod::Any;
		static two::InputMod char_stroke_0_modifier_default = two::InputMod::Any;
		static two::InputMod mouse_event_0_modifier_default = two::InputMod::None;
		static bool mouse_event_0_consume_default = true;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Widget, m_frame), type<two::Frame>(), "frame", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Widget, m_state), type<two::WidgetState>(), "state", &state_default, Member::Value, nullptr },
			{ t, offsetof(two::Widget, m_switch), type<uint32_t>(), "switch", &switch_default, Member::Value, nullptr },
			{ t, offsetof(two::Widget, m_index), type<uint32_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(two::Widget, m_open), type<bool>(), "open", &open_default, Member::Value, nullptr },
			{ t, offsetof(two::Widget, m_body), type<two::Widget>(), "body", body_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "focused", Address(), two_Widget_focused, {}, { &type<bool>(), QualType::None } },
			{ t, "hovered", Address(), two_Widget_hovered, {}, { &type<bool>(), QualType::None } },
			{ t, "pressed", Address(), two_Widget_pressed, {}, { &type<bool>(), QualType::None } },
			{ t, "activated", Address(), two_Widget_activated, {}, { &type<bool>(), QualType::None } },
			{ t, "active", Address(), two_Widget_active, {}, { &type<bool>(), QualType::None } },
			{ t, "selected", Address(), two_Widget_selected, {}, { &type<bool>(), QualType::None } },
			{ t, "modal", Address(), two_Widget_modal, {}, { &type<bool>(), QualType::None } },
			{ t, "closed", Address(), two_Widget_closed, {}, { &type<bool>(), QualType::None } },
			{ t, "ui_window", Address(), two_Widget_ui_window, {}, { &type<two::UiWindow>(), QualType::None } },
			{ t, "ui", Address(), two_Widget_ui, {}, { &type<two::Ui>(), QualType::None } },
			{ t, "parent_modal", Address(), two_Widget_parent_modal, {}, { &type<two::Widget>(), QualType::None } },
			{ t, "clear", Address(), two_Widget_clear, {}, g_qvoid },
			{ t, "toggle_state", Address(), two_Widget_toggle_state, { { "state", type<two::WidgetState>(),  } }, g_qvoid },
			{ t, "disable_state", Address(), two_Widget_disable_state, { { "state", type<two::WidgetState>(),  } }, g_qvoid },
			{ t, "set_state", Address(), two_Widget_set_state, { { "state", type<two::WidgetState>(),  }, { "enabled", type<bool>(),  } }, g_qvoid },
			{ t, "enable_state", Address(), two_Widget_enable_state, { { "state", type<two::WidgetState>(),  } }, g_qvoid },
			{ t, "clear_focus", Address(), two_Widget_clear_focus, {}, g_qvoid },
			{ t, "take_focus", Address(), two_Widget_take_focus, {}, g_qvoid },
			{ t, "yield_focus", Address(), two_Widget_yield_focus, {}, g_qvoid },
			{ t, "take_modal", Address(), two_Widget_take_modal, { { "device_filter", type<uint32_t>(),  } }, g_qvoid },
			{ t, "yield_modal", Address(), two_Widget_yield_modal, {}, g_qvoid },
			{ t, "key_event", Address(), two_Widget_key_event, { { "code", type<two::Key>(),  }, { "event_type", type<two::EventType>(),  }, { "modifier", type<two::InputMod>(), Param::Default, &key_event_0_modifier_default } }, { &type<two::KeyEvent>(), QualType::None } },
			{ t, "key_stroke", Address(), two_Widget_key_stroke, { { "code", type<two::Key>(),  }, { "modifier", type<two::InputMod>(), Param::Default, &key_stroke_0_modifier_default } }, { &type<two::KeyEvent>(), QualType::None } },
			{ t, "char_stroke", Address(), two_Widget_char_stroke, { { "code", type<two::Key>(),  }, { "modifier", type<two::InputMod>(), Param::Default, &char_stroke_0_modifier_default } }, { &type<two::KeyEvent>(), QualType::None } },
			{ t, "mouse_event", Address(), two_Widget_mouse_event, { { "device", type<two::DeviceType>(),  }, { "event_type", type<two::EventType>(),  }, { "modifier", type<two::InputMod>(), Param::Default, &mouse_event_0_modifier_default }, { "consume", type<bool>(), Param::Default, &mouse_event_0_consume_default } }, { &type<two::MouseEvent>(), QualType::None } }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, methods, {}, };
	}
	// two::TextCursor
	{
		Type& t = type<two::TextCursor>();
		static Meta meta = { t, &namspc({ "two" }), "TextCursor", sizeof(two::TextCursor), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_TextCursor__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextCursor__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::TextSelection
	{
		Type& t = type<two::TextSelection>();
		static Meta meta = { t, &namspc({ "two" }), "TextSelection", sizeof(two::TextSelection), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_TextSelection__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextSelection__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::TextMarker
	{
		Type& t = type<two::TextMarker>();
		static Meta meta = { t, &namspc({ "two" }), "TextMarker", sizeof(two::TextMarker), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_TextMarker__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextMarker__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Text
	{
		Type& t = type<two::Text>();
		static Meta meta = { t, &namspc({ "two" }), "Text", sizeof(two::Text), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::TextEdit
	{
		Type& t = type<two::TextEdit>();
		static Meta meta = { t, &namspc({ "two" }), "TextEdit", sizeof(two::TextEdit), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::TextEdit, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::NodeConnection
	{
		Type& t = type<two::NodeConnection>();
		static Meta meta = { t, &namspc({ "two" }), "NodeConnection", sizeof(two::NodeConnection), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_NodeConnection__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_NodeConnection__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Vg
	{
		Type& t = type<two::Vg>();
		static Meta meta = { t, &namspc({ "two" }), "Vg", sizeof(two::Vg), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Clipboard
	{
		Type& t = type<two::Clipboard>();
		static Meta meta = { t, &namspc({ "two" }), "Clipboard", sizeof(two::Clipboard), TypeClass::Struct };
		// bases
		// defaults
		static stl::string text_default = "";
		static bool line_mode_default = false;
		static stl::vector<stl::string> pasted_default = {};
		// constructors
		static Constructor constructors[] = {
			{ t, two_Clipboard__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Clipboard__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Clipboard, m_text), type<stl::string>(), "text", &text_default, Member::Value, nullptr },
			{ t, offsetof(two::Clipboard, m_line_mode), type<bool>(), "line_mode", &line_mode_default, Member::Value, nullptr },
			{ t, offsetof(two::Clipboard, m_pasted), type<stl::vector<stl::string>>(), "pasted", &pasted_default, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::UiWindow
	{
		Type& t = type<two::UiWindow>();
		static Meta meta = { t, &namspc({ "two" }), "UiWindow", sizeof(two::UiWindow), TypeClass::Object };
		// bases
		// defaults
		static bool shutdown_default = false;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::UiWindow, m_resource_path), type<stl::string>(), "resource_path", nullptr, Member::Flags(Member::Value|Member::NonMutable), nullptr },
			{ t, SIZE_MAX, type<two::Context>(), "context", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_UiWindow__get_context },
			{ t, SIZE_MAX, type<two::Vg>(), "vg", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_UiWindow__get_vg },
			{ t, offsetof(two::UiWindow, m_size), type<two::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::UiWindow, m_colour), type<two::Colour>(), "colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::UiWindow, m_shutdown), type<bool>(), "shutdown", &shutdown_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "reset_styles", Address(), two_UiWindow_reset_styles, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::User
	{
		Type& t = type<two::User>();
		static Meta meta = { t, &namspc({ "two" }), "User", sizeof(two::User), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Layer
	{
		Type& t = type<two::Layer>();
		static Meta meta = { t, &namspc({ "two" }), "Layer", sizeof(two::Layer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::FrameSolver
	{
		Type& t = type<two::FrameSolver>();
		static Meta meta = { t, &namspc({ "two" }), "FrameSolver", sizeof(two::FrameSolver), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::UiRect>() };
		static size_t bases_offsets[] = { base_offset<two::FrameSolver, two::UiRect>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::RowSolver
	{
		Type& t = type<two::RowSolver>();
		static Meta meta = { t, &namspc({ "two" }), "RowSolver", sizeof(two::RowSolver), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::FrameSolver>() };
		static size_t bases_offsets[] = { base_offset<two::RowSolver, two::FrameSolver>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::TableSolver
	{
		Type& t = type<two::TableSolver>();
		static Meta meta = { t, &namspc({ "two" }), "TableSolver", sizeof(two::TableSolver), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::LineSolver
	{
		Type& t = type<two::LineSolver>();
		static Meta meta = { t, &namspc({ "two" }), "LineSolver", sizeof(two::LineSolver), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::RowSolver>() };
		static size_t bases_offsets[] = { base_offset<two::LineSolver, two::RowSolver>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::GridSolver
	{
		Type& t = type<two::GridSolver>();
		static Meta meta = { t, &namspc({ "two" }), "GridSolver", sizeof(two::GridSolver), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::ScrollSheet
	{
		Type& t = type<two::ScrollSheet>();
		static Meta meta = { t, &namspc({ "two" }), "ScrollSheet", sizeof(two::ScrollSheet), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::ScrollSheet, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::ui::Sequence
	{
		Type& t = type<two::ui::Sequence>();
		static Meta meta = { t, &namspc({ "two", "ui" }), "Sequence", sizeof(two::ui::Sequence), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::ui::Sequence, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Tabber
	{
		Type& t = type<two::Tabber>();
		static Meta meta = { t, &namspc({ "two" }), "Tabber", sizeof(two::Tabber), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Tabber, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Expandbox
	{
		Type& t = type<two::Expandbox>();
		static Meta meta = { t, &namspc({ "two" }), "Expandbox", sizeof(two::Expandbox), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Expandbox, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::TreeNode
	{
		Type& t = type<two::TreeNode>();
		static Meta meta = { t, &namspc({ "two" }), "TreeNode", sizeof(two::TreeNode), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::TreeNode, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Table
	{
		Type& t = type<two::Table>();
		static Meta meta = { t, &namspc({ "two" }), "Table", sizeof(two::Table), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Table, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Dock
	{
		Type& t = type<two::Dock>();
		static Meta meta = { t, &namspc({ "two" }), "Dock", sizeof(two::Dock), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Dock__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Dock__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Docksystem
	{
		Type& t = type<two::Docksystem>();
		static Meta meta = { t, &namspc({ "two" }), "Docksystem", sizeof(two::Docksystem), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Dockable
	{
		Type& t = type<two::Dockable>();
		static Meta meta = { t, &namspc({ "two" }), "Dockable", sizeof(two::Dockable), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Dockable, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Docker
	{
		Type& t = type<two::Docker>();
		static Meta meta = { t, &namspc({ "two" }), "Docker", sizeof(two::Docker), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Docker, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Dockspace
	{
		Type& t = type<two::Dockspace>();
		static Meta meta = { t, &namspc({ "two" }), "Dockspace", sizeof(two::Dockspace), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Docker>() };
		static size_t bases_offsets[] = { base_offset<two::Dockspace, two::Docker>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Dockbar
	{
		Type& t = type<two::Dockbar>();
		static Meta meta = { t, &namspc({ "two" }), "Dockbar", sizeof(two::Dockbar), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Docker>() };
		static size_t bases_offsets[] = { base_offset<two::Dockbar, two::Docker>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::NodePlug
	{
		Type& t = type<two::NodePlug>();
		static Meta meta = { t, &namspc({ "two" }), "NodePlug", sizeof(two::NodePlug), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::NodePlug, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Node
	{
		Type& t = type<two::Node>();
		static Meta meta = { t, &namspc({ "two" }), "Node", sizeof(two::Node), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Node, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::CanvasConnect
	{
		Type& t = type<two::CanvasConnect>();
		static Meta meta = { t, &namspc({ "two" }), "CanvasConnect", sizeof(two::CanvasConnect), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CanvasConnect__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CanvasConnect__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Canvas
	{
		Type& t = type<two::Canvas>();
		static Meta meta = { t, &namspc({ "two" }), "Canvas", sizeof(two::Canvas), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Canvas, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Ui
	{
		Type& t = type<two::Ui>();
		static Meta meta = { t, &namspc({ "two" }), "Ui", sizeof(two::Ui), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Ui, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "begin", Address(), two_Ui_begin, {}, { &type<two::Widget>(), QualType::None } },
			{ t, "reset_styles", Address(), two_Ui_reset_styles, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, methods, {}, };
	}
	// two::Window
	{
		Type& t = type<two::Window>();
		static Meta meta = { t, &namspc({ "two" }), "Window", sizeof(two::Window), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Dockable>() };
		static size_t bases_offsets[] = { base_offset<two::Window, two::Dockable>() };
		// defaults
		static two::Widget* menu_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Window, m_window_state), type<two::WindowState>(), "window_state", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Window, m_menu), type<two::Widget>(), "menu", menu_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	
	{
		Type& t = type<ushort>();
		static Alias alias = { &t, &namspc({ "two" }), "PaletteIndex" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<stl::span<uint32_t>>();
		static Alias alias = { &t, &namspc({ "two" }), "ColourPalette" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<two::FlowAxis>());
		m.m_types.push_back(&type<two::Pivot>());
		m.m_types.push_back(&type<two::Align>());
		m.m_types.push_back(&type<two::Solver>());
		m.m_types.push_back(&type<two::AutoLayout>());
		m.m_types.push_back(&type<two::LayoutFlow>());
		m.m_types.push_back(&type<two::Sizing>());
		m.m_types.push_back(&type<two::Preset>());
		m.m_types.push_back(&type<two::Space>());
		m.m_types.push_back(&type<two::Clip>());
		m.m_types.push_back(&type<two::Opacity>());
		m.m_types.push_back(&type<two::v2<two::AutoLayout>>());
		m.m_types.push_back(&type<two::v2<two::Sizing>>());
		m.m_types.push_back(&type<two::v2<two::Align>>());
		m.m_types.push_back(&type<two::v2<two::Pivot>>());
		m.m_types.push_back(&type<two::ImageSkin>());
		m.m_types.push_back(&type<two::Shadow>());
		m.m_types.push_back(&type<two::Paint>());
		m.m_types.push_back(&type<two::TextPaint>());
		m.m_types.push_back(&type<two::Gradient>());
		m.m_types.push_back(&type<two::InkStyle>());
		m.m_types.push_back(&type<two::Layout>());
		m.m_types.push_back(&type<two::Subskin>());
		m.m_types.push_back(&type<two::Style>());
		m.m_types.push_back(&type<stl::span<const char*>>());
		m.m_types.push_back(&type<stl::vector<two::Space>>());
		m.m_types.push_back(&type<stl::vector<two::Subskin>>());
		m.m_types.push_back(&type<two::WidgetState>());
		m.m_types.push_back(&type<two::ui::PopupFlags>());
		m.m_types.push_back(&type<two::UiRect>());
		m.m_types.push_back(&type<two::Frame>());
		m.m_types.push_back(&type<two::Widget>());
		m.m_types.push_back(&type<two::TextCursor>());
		m.m_types.push_back(&type<two::TextSelection>());
		m.m_types.push_back(&type<two::PaletteIndex>());
		m.m_types.push_back(&type<two::ColourPalette>());
		m.m_types.push_back(&type<two::TextMarker>());
		m.m_types.push_back(&type<two::Text>());
		m.m_types.push_back(&type<two::TextEdit>());
		m.m_types.push_back(&type<two::NodeConnection>());
		m.m_types.push_back(&type<two::WindowState>());
		m.m_types.push_back(&type<two::Vg>());
		m.m_types.push_back(&type<two::Clipboard>());
		m.m_types.push_back(&type<two::UiWindow>());
		m.m_types.push_back(&type<two::User>());
		m.m_types.push_back(&type<two::Layer>());
		m.m_types.push_back(&type<two::FrameSolver>());
		m.m_types.push_back(&type<two::RowSolver>());
		m.m_types.push_back(&type<two::TableSolver>());
		m.m_types.push_back(&type<two::LineSolver>());
		m.m_types.push_back(&type<two::GridSolver>());
		m.m_types.push_back(&type<two::ScrollSheet>());
		m.m_types.push_back(&type<two::ui::Sequence>());
		m.m_types.push_back(&type<two::Tabber>());
		m.m_types.push_back(&type<two::Expandbox>());
		m.m_types.push_back(&type<two::TreeNode>());
		m.m_types.push_back(&type<two::Table>());
		m.m_types.push_back(&type<two::Dock>());
		m.m_types.push_back(&type<two::Docksystem>());
		m.m_types.push_back(&type<two::Dockable>());
		m.m_types.push_back(&type<two::Docker>());
		m.m_types.push_back(&type<two::Dockspace>());
		m.m_types.push_back(&type<two::Dockbar>());
		m.m_types.push_back(&type<two::NodePlug>());
		m.m_types.push_back(&type<two::Node>());
		m.m_types.push_back(&type<two::CanvasConnect>());
		m.m_types.push_back(&type<two::Canvas>());
		m.m_types.push_back(&type<two::Ui>());
		m.m_types.push_back(&type<two::Window>());
		{
			static Function f = { &namspc({ "two" }), "layout_minimal", funcptr<void(*)(two::UiWindow&)>(two::layout_minimal), two_layout_minimal_0, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_minimal", funcptr<void(*)(two::UiWindow&)>(two::style_minimal), two_style_minimal_1, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_vector", funcptr<void(*)(two::UiWindow&)>(two::style_vector), two_style_vector_2, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_blendish", funcptr<void(*)(two::UiWindow&)>(two::style_blendish), two_style_blendish_3, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_blendish_light", funcptr<void(*)(two::UiWindow&)>(two::style_blendish_light), two_style_blendish_light_4, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_blendish_dark", funcptr<void(*)(two::UiWindow&)>(two::style_blendish_dark), two_style_blendish_dark_5, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_imgui_dark", funcptr<void(*)(two::UiWindow&)>(two::style_imgui_dark), two_style_imgui_dark_6, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_imgui_light", funcptr<void(*)(two::UiWindow&)>(two::style_imgui_light), two_style_imgui_light_7, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_imgui_classic", funcptr<void(*)(two::UiWindow&)>(two::style_imgui_classic), two_style_imgui_classic_8, { { "ui_window", type<two::UiWindow>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static bool open_default = false;
			static two::Axis length_default = two::Axis::None;
			static two::v2<uint> index_default = {0,0};
			static Function f = { &namspc({ "two", "ui" }), "widget", funcptr<two::Widget&(*)(two::Widget&, two::Style&, bool, two::Axis, two::v2<uint>)>(two::ui::widget), two_ui_widget_9, { { "parent", type<two::Widget>(),  }, { "style", type<two::Style>(),  }, { "open", type<bool>(), Param::Default, &open_default }, { "length", type<two::Axis>(), Param::Default, &length_default }, { "index", type<two::v2<uint>>(), Param::Default, &index_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "item", funcptr<two::Widget&(*)(two::Widget&, two::Style&, const char*)>(two::ui::item), two_ui_item_10, { { "parent", type<two::Widget>(),  }, { "style", type<two::Style>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &content_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "multi_item", funcptr<two::Widget&(*)(two::Widget&, two::Style&, stl::span<const char*>, two::Style*)>(two::ui::multi_item), two_ui_multi_item_11, { { "parent", type<two::Widget>(),  }, { "style", type<two::Style>(),  }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<two::Style>(), Param::Flags(Param::Nullable|Param::Default), &element_style_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "spanner", funcptr<two::Widget&(*)(two::Widget&, two::Style&, two::Axis, float)>(two::ui::spanner), two_ui_spanner_12, { { "parent", type<two::Widget>(),  }, { "style", type<two::Style>(),  }, { "dim", type<two::Axis>(),  }, { "span", type<float>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "spacer", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::spacer), two_ui_spacer_13, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "separator", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::separator), two_ui_separator_14, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "icon", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::icon), two_ui_icon_15, { { "parent", type<two::Widget>(),  }, { "image", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "label", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::label), two_ui_label_16, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "title", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::title), two_ui_title_17, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "message", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::message), two_ui_message_18, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "text", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::text), two_ui_text_19, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "bullet", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::bullet), two_ui_bullet_20, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "selectable", funcptr<two::Widget&(*)(two::Widget&, const char*, bool&)>(two::ui::selectable), two_ui_selectable_21, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "selected", type<bool>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "button", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::button), two_ui_button_22, { { "parent", type<two::Widget>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &content_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "toggle", funcptr<two::Widget&(*)(two::Widget&, bool&, const char*)>(two::ui::toggle), two_ui_toggle_23, { { "parent", type<two::Widget>(),  }, { "on", type<bool>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &content_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "button", funcptr<two::Widget&(*)(two::Widget&, const stl::string&)>(two::ui::button), two_ui_button_24, { { "parent", type<two::Widget>(),  }, { "content", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "toggle", funcptr<two::Widget&(*)(two::Widget&, bool&, const stl::string&)>(two::ui::toggle), two_ui_toggle_25, { { "parent", type<two::Widget>(),  }, { "on", type<bool>(),  }, { "content", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "multi_button", funcptr<two::Widget&(*)(two::Widget&, stl::span<const char*>, two::Style*)>(two::ui::multi_button), two_ui_multi_button_26, { { "parent", type<two::Widget>(),  }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<two::Style>(), Param::Flags(Param::Nullable|Param::Default), &element_style_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "multi_toggle", funcptr<two::Widget&(*)(two::Widget&, bool&, stl::span<const char*>, two::Style*)>(two::ui::multi_toggle), two_ui_multi_toggle_27, { { "parent", type<two::Widget>(),  }, { "on", type<bool>(),  }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<two::Style>(), Param::Flags(Param::Nullable|Param::Default), &element_style_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "modal_button", funcptr<bool(*)(two::Widget&, two::Widget&, const char*, uint32_t)>(two::ui::modal_button), two_ui_modal_button_28, { { "screen", type<two::Widget>(),  }, { "parent", type<two::Widget>(),  }, { "content", type<const char*>(), Param::Nullable }, { "mode", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "modal_multi_button", funcptr<bool(*)(two::Widget&, two::Widget&, stl::span<const char*>, uint32_t)>(two::ui::modal_multi_button), two_ui_modal_multi_button_29, { { "screen", type<two::Widget>(),  }, { "parent", type<two::Widget>(),  }, { "elements", type<stl::span<const char*>>(),  }, { "mode", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "checkbox", funcptr<two::Widget&(*)(two::Widget&, bool&)>(two::ui::checkbox), two_ui_checkbox_30, { { "parent", type<two::Widget>(),  }, { "on", type<bool>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Axis dim_default = two::Axis::X;
			static Function f = { &namspc({ "two", "ui" }), "fill_bar", funcptr<two::Widget&(*)(two::Widget&, float, two::Axis)>(two::ui::fill_bar), two_ui_fill_bar_31, { { "parent", type<two::Widget>(),  }, { "percentage", type<float>(),  }, { "dim", type<two::Axis>(), Param::Default, &dim_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "image256", funcptr<two::Widget&(*)(two::Widget&, const char*, const two::Image256&)>(two::ui::image256), two_ui_image256_32, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "source", type<two::Image256>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "image256", funcptr<two::Widget&(*)(two::Widget&, const char*, const two::Image256&, const two::vec2&)>(two::ui::image256), two_ui_image256_33, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "source", type<two::Image256>(),  }, { "size", type<two::vec2>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "image256", funcptr<two::Widget&(*)(two::Widget&, const stl::string&, const two::Image256&)>(two::ui::image256), two_ui_image256_34, { { "parent", type<two::Widget>(),  }, { "name", type<stl::string>(),  }, { "source", type<two::Image256>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "image256", funcptr<two::Widget&(*)(two::Widget&, const stl::string&, const two::Image256&, const two::vec2&)>(two::ui::image256), two_ui_image256_35, { { "parent", type<two::Widget>(),  }, { "name", type<stl::string>(),  }, { "source", type<two::Image256>(),  }, { "size", type<two::vec2>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "radio_choice", funcptr<two::Widget&(*)(two::Widget&, const char*, bool)>(two::ui::radio_choice), two_ui_radio_choice_36, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "active", type<bool>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "radio_button", funcptr<two::Widget&(*)(two::Widget&, const char*, uint32_t&, uint32_t)>(two::ui::radio_button), two_ui_radio_button_37, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "value", type<uint32_t>(),  }, { "index", type<uint32_t>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Axis dim_default = two::Axis::X;
			static Function f = { &namspc({ "two", "ui" }), "radio_switch", funcptr<bool(*)(two::Widget&, stl::span<const char*>, uint32_t&, two::Axis)>(two::ui::radio_switch), two_ui_radio_switch_38, { { "parent", type<two::Widget>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "dim", type<two::Axis>(), Param::Default, &dim_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "popdown", funcptr<bool(*)(two::Widget&, stl::span<const char*>, uint32_t&, two::vec2, two::ui::PopupFlags)>(two::ui::popdown), two_ui_popdown_39, { { "parent", type<two::Widget>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "position", type<two::vec2>(),  }, { "flags", type<two::ui::PopupFlags>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool no_toggle_default = false;
			static two::Style* list_style_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "dropdown", funcptr<two::Widget&(*)(two::Widget&, two::Style&, const char*, two::ui::PopupFlags, bool, two::Style*)>(two::ui::dropdown), two_ui_dropdown_40, { { "parent", type<two::Widget>(),  }, { "style", type<two::Style>(),  }, { "value", type<const char*>(), Param::Nullable }, { "flags", type<two::ui::PopupFlags>(),  }, { "no_toggle", type<bool>(), Param::Default, &no_toggle_default }, { "list_style", type<two::Style>(), Param::Flags(Param::Nullable|Param::Default), &list_style_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool compact_default = false;
			static Function f = { &namspc({ "two", "ui" }), "dropdown_input", funcptr<bool(*)(two::Widget&, stl::span<const char*>, uint32_t&, bool)>(two::ui::dropdown_input), two_ui_dropdown_input_41, { { "parent", type<two::Widget>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "compact", type<bool>(), Param::Default, &compact_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "typedown_input", funcptr<bool(*)(two::Widget&, stl::span<const char*>, uint32_t&)>(two::ui::typedown_input), two_ui_typedown_input_42, { { "parent", type<two::Widget>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* shortcut_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "menu_choice", funcptr<two::Widget&(*)(two::Widget&, const char*, const char*)>(two::ui::menu_choice), two_ui_menu_choice_43, { { "parent", type<two::Widget>(),  }, { "content", type<const char*>(), Param::Nullable }, { "shortcut", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &shortcut_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "menu_option", funcptr<two::Widget&(*)(two::Widget&, const char*, const char*, bool)>(two::ui::menu_option), two_ui_menu_option_44, { { "parent", type<two::Widget>(),  }, { "content", type<const char*>(), Param::Nullable }, { "shortcut", type<const char*>(), Param::Nullable }, { "enabled", type<bool>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool submenu_default = false;
			static Function f = { &namspc({ "two", "ui" }), "menu", funcptr<two::Widget&(*)(two::Widget&, const char*, bool)>(two::ui::menu), two_ui_menu_45, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "submenu", type<bool>(), Param::Default, &submenu_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "menubar", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::menubar), two_ui_menubar_46, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "toolbutton", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::toolbutton), two_ui_toolbutton_47, { { "parent", type<two::Widget>(),  }, { "icon", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "tooldock", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::tooldock), two_ui_tooldock_48, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool wrap_default = false;
			static Function f = { &namspc({ "two", "ui" }), "toolbar", funcptr<two::Widget&(*)(two::Widget&, bool)>(two::ui::toolbar), two_ui_toolbar_49, { { "parent", type<two::Widget>(),  }, { "wrap", type<bool>(), Param::Default, &wrap_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "select_list", funcptr<two::ScrollSheet&(*)(two::Widget&)>(two::ui::select_list), two_ui_select_list_50, { { "parent", type<two::Widget>(),  } }, { &type<two::ScrollSheet>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "columns", funcptr<two::Table&(*)(two::Widget&, stl::span<float>)>(two::ui::columns), two_ui_columns_51, { { "parent", type<two::Widget>(),  }, { "weights", type<stl::span<float>>(),  } }, { &type<two::Table>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "table", funcptr<two::Table&(*)(two::Widget&, stl::span<const char*>, stl::span<float>)>(two::ui::table), two_ui_table_52, { { "parent", type<two::Widget>(),  }, { "columns", type<stl::span<const char*>>(),  }, { "weights", type<stl::span<float>>(),  } }, { &type<two::Table>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "table_row", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::table_row), two_ui_table_row_53, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "table_separator", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::table_separator), two_ui_table_separator_54, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool open_default = true;
			static Function f = { &namspc({ "two", "ui" }), "expandbox", funcptr<two::Expandbox&(*)(two::Widget&, const char*, bool)>(two::ui::expandbox), two_ui_expandbox_55, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "open", type<bool>(), Param::Default, &open_default } }, { &type<two::Expandbox>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool leaf_default = false;
			static bool open_default = true;
			static Function f = { &namspc({ "two", "ui" }), "tree_node", funcptr<two::TreeNode&(*)(two::Widget&, const char*, bool, bool)>(two::ui::tree_node), two_ui_tree_node_56, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "leaf", type<bool>(), Param::Default, &leaf_default }, { "open", type<bool>(), Param::Default, &open_default } }, { &type<two::TreeNode>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "tree", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::tree), two_ui_tree_57, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "tab", funcptr<two::Widget*(*)(two::Tabber&, const char*)>(two::ui::tab), two_ui_tab_58, { { "tabber", type<two::Tabber>(),  }, { "name", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "tabber", funcptr<two::Tabber&(*)(two::Widget&)>(two::ui::tabber), two_ui_tabber_59, { { "parent", type<two::Widget>(),  } }, { &type<two::Tabber>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "row", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::row), two_ui_row_60, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "header", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::header), two_ui_header_61, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "div", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::div), two_ui_div_62, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "stack", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::stack), two_ui_stack_63, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "sheet", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::sheet), two_ui_sheet_64, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "board", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::board), two_ui_board_65, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "layout", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::layout), two_ui_layout_66, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "indent", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::indent), two_ui_indent_67, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "screen", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::screen), two_ui_screen_68, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "decal", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::decal), two_ui_decal_69, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "overlay", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::overlay), two_ui_overlay_70, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "title_header", funcptr<two::Widget&(*)(two::Widget&, const char*)>(two::ui::title_header), two_ui_title_header_71, { { "parent", type<two::Widget>(),  }, { "title", type<const char*>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dummy", funcptr<two::Widget&(*)(two::Widget&, const two::vec2&)>(two::ui::dummy), two_ui_dummy_72, { { "parent", type<two::Widget>(),  }, { "size", type<two::vec2>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "popup", funcptr<two::Widget&(*)(two::Widget&, two::ui::PopupFlags)>(two::ui::popup), two_ui_popup_73, { { "parent", type<two::Widget>(),  }, { "flags", type<two::ui::PopupFlags>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::ui::PopupFlags flags_default = two::ui::PopupFlags::None;
			static Function f = { &namspc({ "two", "ui" }), "popup", funcptr<two::Widget&(*)(two::Widget&, const two::vec2&, two::ui::PopupFlags)>(two::ui::popup), two_ui_popup_74, { { "parent", type<two::Widget>(),  }, { "size", type<two::vec2>(),  }, { "flags", type<two::ui::PopupFlags>(), Param::Default, &flags_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::ui::PopupFlags flags_default = two::ui::PopupFlags::None;
			static Function f = { &namspc({ "two", "ui" }), "popup_at", funcptr<two::Widget&(*)(two::Widget&, const two::vec2&, two::ui::PopupFlags)>(two::ui::popup_at), two_ui_popup_at_75, { { "parent", type<two::Widget>(),  }, { "position", type<two::vec2>(),  }, { "flags", type<two::ui::PopupFlags>(), Param::Default, &flags_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "modal", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::modal), two_ui_modal_76, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "modal", funcptr<two::Widget&(*)(two::Widget&, const two::vec2&)>(two::ui::modal), two_ui_modal_77, { { "parent", type<two::Widget>(),  }, { "size", type<two::vec2>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "auto_modal", funcptr<two::Widget&(*)(two::Widget&, uint32_t)>(two::ui::auto_modal), two_ui_auto_modal_78, { { "parent", type<two::Widget>(),  }, { "mode", type<uint32_t>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "auto_modal", funcptr<two::Widget&(*)(two::Widget&, uint32_t, const two::vec2&)>(two::ui::auto_modal), two_ui_auto_modal_79, { { "parent", type<two::Widget>(),  }, { "mode", type<uint32_t>(),  }, { "size", type<two::vec2>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::ui::PopupFlags flags_default = two::ui::PopupFlags::None;
			static Function f = { &namspc({ "two", "ui" }), "context", funcptr<two::Widget*(*)(two::Widget&, uint32_t, two::ui::PopupFlags)>(two::ui::context), two_ui_context_80, { { "parent", type<two::Widget>(),  }, { "mode", type<uint32_t>(),  }, { "flags", type<two::ui::PopupFlags>(), Param::Default, &flags_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float delay_default = 0.5f;
			static Function f = { &namspc({ "two", "ui" }), "hoverbox", funcptr<two::Widget*(*)(two::Widget&, float)>(two::ui::hoverbox), two_ui_hoverbox_81, { { "parent", type<two::Widget>(),  }, { "delay", type<float>(), Param::Default, &delay_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool locked_default = false;
			static Function f = { &namspc({ "two", "ui" }), "cursor", funcptr<two::Widget&(*)(two::Widget&, const two::vec2&, two::Widget&, bool)>(two::ui::cursor), two_ui_cursor_82, { { "parent", type<two::Widget>(),  }, { "position", type<two::vec2>(),  }, { "hovered", type<two::Widget>(),  }, { "locked", type<bool>(), Param::Default, &locked_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "rectangle", funcptr<two::Widget&(*)(two::Widget&, const two::vec4&)>(two::ui::rectangle), two_ui_rectangle_83, { { "parent", type<two::Widget>(),  }, { "rect", type<two::vec4>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "viewport", funcptr<two::Widget&(*)(two::Widget&, const two::vec4&)>(two::ui::viewport), two_ui_viewport_84, { { "parent", type<two::Widget>(),  }, { "rect", type<two::vec4>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dockspace", funcptr<two::Dockspace&(*)(two::Widget&, two::Docksystem&)>(two::ui::dockspace), two_ui_dockspace_85, { { "parent", type<two::Widget>(),  }, { "docksystem", type<two::Docksystem>(),  } }, { &type<two::Dockspace>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dockbar", funcptr<two::Dockbar&(*)(two::Widget&, two::Docksystem&)>(two::ui::dockbar), two_ui_dockbar_86, { { "parent", type<two::Widget>(),  }, { "docksystem", type<two::Docksystem>(),  } }, { &type<two::Dockbar>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dockitem", funcptr<two::Widget*(*)(two::Widget&, two::Docksystem&, two::Dock&)>(two::ui::dockitem), two_ui_dockitem_87, { { "parent", type<two::Widget>(),  }, { "docksystem", type<two::Docksystem>(),  }, { "dock", type<two::Dock>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float step_default = 0.1f;
			static Function f = { &namspc({ "two", "ui" }), "drag_float", funcptr<bool(*)(two::Widget&, float&, float)>(two::ui::drag_float), two_ui_drag_float_88, { { "parent", type<two::Widget>(),  }, { "value", type<float>(),  }, { "step", type<float>(), Param::Default, &step_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float2_input", funcptr<bool(*)(two::Widget&, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float2_input), two_ui_float2_input_89, { { "parent", type<two::Widget>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float3_input", funcptr<bool(*)(two::Widget&, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float3_input), two_ui_float3_input_90, { { "parent", type<two::Widget>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float4_input", funcptr<bool(*)(two::Widget&, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float4_input), two_ui_float4_input_91, { { "parent", type<two::Widget>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float2_slider", funcptr<bool(*)(two::Widget&, const char*, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float2_slider), two_ui_float2_slider_92, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float3_slider", funcptr<bool(*)(two::Widget&, const char*, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float3_slider), two_ui_float3_slider_93, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float4_slider", funcptr<bool(*)(two::Widget&, const char*, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float4_slider), two_ui_float4_slider_94, { { "parent", type<two::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "vec2_edit", funcptr<bool(*)(two::Widget&, two::vec2&)>(two::ui::vec2_edit), two_ui_vec2_edit_95, { { "parent", type<two::Widget>(),  }, { "vec", type<two::vec2>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "vec3_edit", funcptr<bool(*)(two::Widget&, two::vec3&)>(two::ui::vec3_edit), two_ui_vec3_edit_96, { { "parent", type<two::Widget>(),  }, { "vec", type<two::vec3>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "quat_edit", funcptr<bool(*)(two::Widget&, two::quat&)>(two::ui::quat_edit), two_ui_quat_edit_97, { { "parent", type<two::Widget>(),  }, { "quat", type<two::quat>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "color_display", funcptr<two::Widget&(*)(two::Widget&, const two::Colour&)>(two::ui::color_display), two_ui_color_display_98, { { "parent", type<two::Widget>(),  }, { "value", type<two::Colour>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "color_edit", funcptr<bool(*)(two::Widget&, two::Colour&)>(two::ui::color_edit), two_ui_color_edit_99, { { "parent", type<two::Widget>(),  }, { "value", type<two::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "color_edit_simple", funcptr<bool(*)(two::Widget&, two::Colour&)>(two::ui::color_edit_simple), two_ui_color_edit_simple_100, { { "parent", type<two::Widget>(),  }, { "value", type<two::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "color_toggle_edit", funcptr<bool(*)(two::Widget&, two::Colour&)>(two::ui::color_toggle_edit), two_ui_color_toggle_edit_101, { { "parent", type<two::Widget>(),  }, { "value", type<two::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static stl::span<float> points_default = {};
			static Function f = { &namspc({ "two", "ui" }), "curve_graph", funcptr<bool(*)(two::Widget&, stl::span<float>, stl::span<float>)>(two::ui::curve_graph), two_ui_curve_graph_102, { { "parent", type<two::Widget>(),  }, { "values", type<stl::span<float>>(),  }, { "points", type<stl::span<float>>(), Param::Default, &points_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static stl::span<float> points_default = {};
			static Function f = { &namspc({ "two", "ui" }), "curve_edit", funcptr<bool(*)(two::Widget&, stl::span<float>, stl::span<float>)>(two::ui::curve_edit), two_ui_curve_edit_103, { { "parent", type<two::Widget>(),  }, { "values", type<stl::span<float>>(),  }, { "points", type<stl::span<float>>(), Param::Default, &points_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "flag_field", funcptr<bool(*)(two::Widget&, const char*, uint32_t&, uint8_t, bool)>(two::ui::flag_field), two_ui_flag_field_104, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<uint32_t>(),  }, { "shift", type<uint8_t>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Axis dim_default = two::Axis::X;
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "radio_field", funcptr<bool(*)(two::Widget&, const char*, stl::span<const char*>, uint32_t&, two::Axis, bool)>(two::ui::radio_field), two_ui_radio_field_105, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "dim", type<two::Axis>(), Param::Default, &dim_default }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "dropdown_field", funcptr<bool(*)(two::Widget&, const char*, stl::span<const char*>, uint32_t&, bool)>(two::ui::dropdown_field), two_ui_dropdown_field_106, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "typedown_field", funcptr<bool(*)(two::Widget&, const char*, stl::span<const char*>, uint32_t&, bool)>(two::ui::typedown_field), two_ui_typedown_field_107, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "color_field", funcptr<bool(*)(two::Widget&, const char*, two::Colour&, bool)>(two::ui::color_field), two_ui_color_field_108, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<two::Colour>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "color_display_field", funcptr<void(*)(two::Widget&, const char*, const two::Colour&, bool)>(two::ui::color_display_field), two_ui_color_display_field_109, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<two::Colour>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<bool>", funcptr<bool(*)(two::Widget&, bool&)>(two::ui::input<bool>), two_ui_input_bool_110, { { "parent", type<two::Widget>(),  }, { "value", type<bool>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<stl::basic_string< ::stl::allocator>>", funcptr<bool(*)(two::Widget&, stl::string&)>(two::ui::input<stl::basic_string< ::stl::allocator>>), two_ui_input_stl_basic_string___stl_allocator_111, { { "parent", type<two::Widget>(),  }, { "value", type<stl::string>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<int>", funcptr<bool(*)(two::Widget&, int&, two::StatDef<int>)>(two::ui::input<int>), two_ui_input_int_112, { { "parent", type<two::Widget>(),  }, { "value", type<int>(),  }, { "def", type<two::StatDef<int>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<float>", funcptr<bool(*)(two::Widget&, float&, two::StatDef<float>)>(two::ui::input<float>), two_ui_input_float_113, { { "parent", type<two::Widget>(),  }, { "value", type<float>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "field<bool>", funcptr<bool(*)(two::Widget&, const char*, bool&, bool)>(two::ui::field<bool>), two_ui_field_bool_114, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<bool>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "field<stl::basic_string< ::stl::allocator>>", funcptr<bool(*)(two::Widget&, const char*, stl::string&, bool)>(two::ui::field<stl::basic_string< ::stl::allocator>>), two_ui_field_stl_basic_string___stl_allocator_115, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<stl::string>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "field<int>", funcptr<bool(*)(two::Widget&, const char*, int&, two::StatDef<int>, bool)>(two::ui::field<int>), two_ui_field_int_116, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<int>(),  }, { "def", type<two::StatDef<int>>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "field<float>", funcptr<bool(*)(two::Widget&, const char*, float&, two::StatDef<float>, bool)>(two::ui::field<float>), two_ui_field_float_117, { { "parent", type<two::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<float>(),  }, { "def", type<two::StatDef<float>>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool editor_default = false;
			static size_t lines_default = 1;
			static stl::string allowed_chars_default = "";
			static Function f = { &namspc({ "two", "ui" }), "text_box", funcptr<two::TextEdit&(*)(two::Widget&, two::Style&, stl::string&, bool, size_t, const stl::string&)>(two::ui::text_box), two_ui_text_box_118, { { "parent", type<two::Widget>(),  }, { "style", type<two::Style>(),  }, { "text", type<stl::string>(),  }, { "editor", type<bool>(), Param::Default, &editor_default }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "allowed_chars", type<stl::string>(), Param::Default, &allowed_chars_default } }, { &type<two::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::string allowed_chars_default = "";
			static Function f = { &namspc({ "two", "ui" }), "type_in", funcptr<two::TextEdit&(*)(two::Widget&, stl::string&, size_t, const stl::string&)>(two::ui::type_in), two_ui_type_in_119, { { "parent", type<two::Widget>(),  }, { "text", type<stl::string>(),  }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "allowed_chars", type<stl::string>(), Param::Default, &allowed_chars_default } }, { &type<two::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::vector<stl::string>* vocabulary_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "text_edit", funcptr<two::TextEdit&(*)(two::Widget&, stl::string&, size_t, stl::vector<stl::string>*)>(two::ui::text_edit), two_ui_text_edit_120, { { "parent", type<two::Widget>(),  }, { "text", type<stl::string>(),  }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "vocabulary", type<stl::vector<stl::string>>(), Param::Flags(Param::Nullable|Param::Default), &vocabulary_default } }, { &type<two::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::vector<stl::string>* vocabulary_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "code_edit", funcptr<two::TextEdit&(*)(two::Widget&, stl::string&, size_t, stl::vector<stl::string>*)>(two::ui::code_edit), two_ui_code_edit_121, { { "parent", type<two::Widget>(),  }, { "text", type<stl::string>(),  }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "vocabulary", type<stl::vector<stl::string>>(), Param::Flags(Param::Nullable|Param::Default), &vocabulary_default } }, { &type<two::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<bool>", funcptr<bool(*)(two::Widget&, bool&)>(two::ui::input<bool>), two_ui_input_bool_122, { { "parent", type<two::Widget>(),  }, { "value", type<bool>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<stl::basic_string< ::stl::allocator>>", funcptr<bool(*)(two::Widget&, stl::string&)>(two::ui::input<stl::basic_string< ::stl::allocator>>), two_ui_input_stl_basic_string___stl_allocator_123, { { "parent", type<two::Widget>(),  }, { "value", type<stl::string>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* icon_default = "";
			static two::Colour colour_default = two::Colour::NeonGreen;
			static bool active_default = true;
			static bool connected_default = false;
			static Function f = { &namspc({ "two", "ui" }), "node_input", funcptr<two::NodePlug&(*)(two::Node&, const char*, const char*, const two::Colour&, bool, bool)>(two::ui::node_input), two_ui_node_input_124, { { "node", type<two::Node>(),  }, { "name", type<const char*>(), Param::Nullable }, { "icon", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &icon_default }, { "colour", type<two::Colour>(), Param::Default, &colour_default }, { "active", type<bool>(), Param::Default, &active_default }, { "connected", type<bool>(), Param::Default, &connected_default } }, { &type<two::NodePlug>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* icon_default = "";
			static two::Colour colour_default = two::Colour::NeonGreen;
			static bool active_default = true;
			static bool connected_default = false;
			static Function f = { &namspc({ "two", "ui" }), "node_output", funcptr<two::NodePlug&(*)(two::Node&, const char*, const char*, const two::Colour&, bool, bool)>(two::ui::node_output), two_ui_node_output_125, { { "node", type<two::Node>(),  }, { "name", type<const char*>(), Param::Nullable }, { "icon", type<const char*>(), Param::Flags(Param::Nullable|Param::Default), &icon_default }, { "colour", type<two::Colour>(), Param::Default, &colour_default }, { "active", type<bool>(), Param::Default, &active_default }, { "connected", type<bool>(), Param::Default, &connected_default } }, { &type<two::NodePlug>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static int order_default = 0;
			static two::Ref identity_default = {};
			static Function f = { &namspc({ "two", "ui" }), "node", funcptr<two::Node&(*)(two::Canvas&, const char*, two::vec2&, int, two::Ref)>(two::ui::node), two_ui_node_126, { { "parent", type<two::Canvas>(),  }, { "title", type<const char*>(), Param::Nullable }, { "position", type<two::vec2>(),  }, { "order", type<int>(), Param::Default, &order_default }, { "identity", type<two::Ref>(), Param::Flags(Param::Nullable|Param::Default), &identity_default } }, { &type<two::Node>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "node_cable", funcptr<two::Widget&(*)(two::Canvas&, two::NodePlug&, two::NodePlug&)>(two::ui::node_cable), two_ui_node_cable_127, { { "canvas", type<two::Canvas>(),  }, { "plug_out", type<two::NodePlug>(),  }, { "plug_in", type<two::NodePlug>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t num_nodes_default = 0;
			static Function f = { &namspc({ "two", "ui" }), "canvas", funcptr<two::Canvas&(*)(two::Widget&, size_t)>(two::ui::canvas), two_ui_canvas_128, { { "parent", type<two::Widget>(),  }, { "num_nodes", type<size_t>(), Param::Default, &num_nodes_default } }, { &type<two::Canvas>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Style* surface_style_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "scroll_sheet", funcptr<two::ScrollSheet&(*)(two::Widget&, two::Style&, two::Style*)>(two::ui::scroll_sheet), two_ui_scroll_sheet_129, { { "parent", type<two::Widget>(),  }, { "style", type<two::Style>(),  }, { "surface_style", type<two::Style>(), Param::Flags(Param::Nullable|Param::Default), &surface_style_default } }, { &type<two::ScrollSheet>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "scroll_plan", funcptr<two::ScrollSheet&(*)(two::Widget&, two::Style&)>(two::ui::scroll_plan), two_ui_scroll_plan_130, { { "parent", type<two::Widget>(),  }, { "style", type<two::Style>(),  } }, { &type<two::ScrollSheet>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "scrollable", funcptr<two::Widget&(*)(two::Widget&)>(two::ui::scrollable), two_ui_scrollable_131, { { "parent", type<two::Widget>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "sequence", funcptr<two::ui::Sequence&(*)(two::Widget&)>(two::ui::sequence), two_ui_sequence_132, { { "parent", type<two::Widget>(),  } }, { &type<two::ui::Sequence>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "scroll_sequence", funcptr<two::ui::Sequence&(*)(two::Widget&)>(two::ui::scroll_sequence), two_ui_scroll_sequence_133, { { "parent", type<two::Widget>(),  } }, { &type<two::ui::Sequence>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "multiselect_logic", funcptr<bool(*)(two::Widget&, two::Ref, stl::vector<two::Ref>&)>(two::ui::multiselect_logic), two_ui_multiselect_logic_134, { { "element", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable }, { "selection", type<stl::vector<two::Ref>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "select_logic", funcptr<bool(*)(two::Widget&, two::Ref, two::Ref&)>(two::ui::select_logic), two_ui_select_logic_135, { { "element", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable }, { "selection", type<two::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "element", funcptr<two::Widget&(*)(two::Widget&, two::Ref)>(two::ui::element), two_ui_element_136, { { "parent", type<two::Widget>(),  }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "sequence_element", funcptr<two::Widget&(*)(two::ui::Sequence&, two::Ref)>(two::ui::sequence_element), two_ui_sequence_element_137, { { "parent", type<two::ui::Sequence>(),  }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::WindowState state_default = two::WindowState::Default;
			static Function f = { &namspc({ "two", "ui" }), "window", funcptr<two::Window&(*)(two::Widget&, const char*, two::WindowState)>(two::ui::window), two_ui_window_138, { { "parent", type<two::Widget>(),  }, { "title", type<const char*>(), Param::Nullable }, { "state", type<two::WindowState>(), Param::Default, &state_default } }, { &type<two::Window>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dir_item", funcptr<two::Widget&(*)(two::Widget&, const stl::string&)>(two::ui::dir_item), two_ui_dir_item_139, { { "parent", type<two::Widget>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_item", funcptr<two::Widget&(*)(two::Widget&, const stl::string&)>(two::ui::file_item), two_ui_file_item_140, { { "parent", type<two::Widget>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_list", funcptr<two::Widget&(*)(two::Widget&, stl::string&)>(two::ui::file_list), two_ui_file_list_141, { { "parent", type<two::Widget>(),  }, { "path", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_browser", funcptr<two::Widget&(*)(two::Widget&, stl::string&)>(two::ui::file_browser), two_ui_file_browser_142, { { "parent", type<two::Widget>(),  }, { "path", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dir_node", funcptr<two::Widget&(*)(two::Widget&, const stl::string&, const stl::string&, bool)>(two::ui::dir_node), two_ui_dir_node_143, { { "parent", type<two::Widget>(),  }, { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  }, { "collapsed", type<bool>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_node", funcptr<two::Widget&(*)(two::Widget&, const stl::string&)>(two::ui::file_node), two_ui_file_node_144, { { "parent", type<two::Widget>(),  }, { "name", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_tree", funcptr<two::Widget&(*)(two::Widget&, const stl::string&)>(two::ui::file_tree), two_ui_file_tree_145, { { "parent", type<two::Widget>(),  }, { "path", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "command_line", funcptr<two::Widget&(*)(two::Widget&, stl::string&, stl::string&)>(two::ui::command_line), two_ui_command_line_146, { { "parent", type<two::Widget>(),  }, { "text", type<stl::string>(),  }, { "command", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t num_lines_default = 0;
			static Function f = { &namspc({ "two", "ui" }), "console", funcptr<two::Widget&(*)(two::Widget&, stl::string&, stl::string&, stl::string&, size_t)>(two::ui::console), two_ui_console_147, { { "parent", type<two::Widget>(),  }, { "feed", type<stl::string>(),  }, { "line", type<stl::string>(),  }, { "command", type<stl::string>(),  }, { "num_lines", type<size_t>(), Param::Default, &num_lines_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_ui::two_ui()
		: Module("two::ui", { &two_infra::m(), &two_type::m(), &two_math::m(), &two_ctx::m() })
	{
		// setup reflection meta data
		two_ui_meta(*this);
	}
}

#ifdef TWO_UI_MODULE
extern "C"
Module& getModule()
{
	return two_ui::m();
}
#endif
