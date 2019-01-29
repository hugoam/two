#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/ui/Convert.h>
#endif

#include <ui/Api.h>

using namespace mud;

void mud_Align__to_string(void* val, string& str) { str = g_enu[type<mud::Align>().m_id]->name(uint32_t((*static_cast<mud::Align*>(val)))); }
void mud_Align__to_value(const string& str, void* val) { (*static_cast<mud::Align*>(val)) = mud::Align(g_enu[type<mud::Align>().m_id]->value(str.c_str())); }
void mud_AutoLayout__to_string(void* val, string& str) { str = g_enu[type<mud::AutoLayout>().m_id]->name(uint32_t((*static_cast<mud::AutoLayout*>(val)))); }
void mud_AutoLayout__to_value(const string& str, void* val) { (*static_cast<mud::AutoLayout*>(val)) = mud::AutoLayout(g_enu[type<mud::AutoLayout>().m_id]->value(str.c_str())); }
void mud_Clipping__to_string(void* val, string& str) { str = g_enu[type<mud::Clipping>().m_id]->name(uint32_t((*static_cast<mud::Clipping*>(val)))); }
void mud_Clipping__to_value(const string& str, void* val) { (*static_cast<mud::Clipping*>(val)) = mud::Clipping(g_enu[type<mud::Clipping>().m_id]->value(str.c_str())); }
void mud_Dim__to_string(void* val, string& str) { str = g_enu[type<mud::Dim>().m_id]->name(uint32_t((*static_cast<mud::Dim*>(val)))); }
void mud_Dim__to_value(const string& str, void* val) { (*static_cast<mud::Dim*>(val)) = mud::Dim(g_enu[type<mud::Dim>().m_id]->value(str.c_str())); }
void mud_Flow__to_string(void* val, string& str) { str = g_enu[type<mud::Flow>().m_id]->name(uint32_t((*static_cast<mud::Flow*>(val)))); }
void mud_Flow__to_value(const string& str, void* val) { (*static_cast<mud::Flow*>(val)) = mud::Flow(g_enu[type<mud::Flow>().m_id]->value(str.c_str())); }
void mud_FlowAxis__to_string(void* val, string& str) { str = g_enu[type<mud::FlowAxis>().m_id]->name(uint32_t((*static_cast<mud::FlowAxis*>(val)))); }
void mud_FlowAxis__to_value(const string& str, void* val) { (*static_cast<mud::FlowAxis*>(val)) = mud::FlowAxis(g_enu[type<mud::FlowAxis>().m_id]->value(str.c_str())); }
void mud_LayoutSolver__to_string(void* val, string& str) { str = g_enu[type<mud::LayoutSolver>().m_id]->name(uint32_t((*static_cast<mud::LayoutSolver*>(val)))); }
void mud_LayoutSolver__to_value(const string& str, void* val) { (*static_cast<mud::LayoutSolver*>(val)) = mud::LayoutSolver(g_enu[type<mud::LayoutSolver>().m_id]->value(str.c_str())); }
void mud_Opacity__to_string(void* val, string& str) { str = g_enu[type<mud::Opacity>().m_id]->name(uint32_t((*static_cast<mud::Opacity*>(val)))); }
void mud_Opacity__to_value(const string& str, void* val) { (*static_cast<mud::Opacity*>(val)) = mud::Opacity(g_enu[type<mud::Opacity>().m_id]->value(str.c_str())); }
void mud_Pivot__to_string(void* val, string& str) { str = g_enu[type<mud::Pivot>().m_id]->name(uint32_t((*static_cast<mud::Pivot*>(val)))); }
void mud_Pivot__to_value(const string& str, void* val) { (*static_cast<mud::Pivot*>(val)) = mud::Pivot(g_enu[type<mud::Pivot>().m_id]->value(str.c_str())); }
void mud_ui_PopupFlags__to_string(void* val, string& str) { str = g_enu[type<mud::ui::PopupFlags>().m_id]->name(uint32_t((*static_cast<mud::ui::PopupFlags*>(val)))); }
void mud_ui_PopupFlags__to_value(const string& str, void* val) { (*static_cast<mud::ui::PopupFlags*>(val)) = mud::ui::PopupFlags(g_enu[type<mud::ui::PopupFlags>().m_id]->value(str.c_str())); }
void mud_Sizing__to_string(void* val, string& str) { str = g_enu[type<mud::Sizing>().m_id]->name(uint32_t((*static_cast<mud::Sizing*>(val)))); }
void mud_Sizing__to_value(const string& str, void* val) { (*static_cast<mud::Sizing*>(val)) = mud::Sizing(g_enu[type<mud::Sizing>().m_id]->value(str.c_str())); }
void mud_SpacePreset__to_string(void* val, string& str) { str = g_enu[type<mud::SpacePreset>().m_id]->name(uint32_t((*static_cast<mud::SpacePreset*>(val)))); }
void mud_SpacePreset__to_value(const string& str, void* val) { (*static_cast<mud::SpacePreset*>(val)) = mud::SpacePreset(g_enu[type<mud::SpacePreset>().m_id]->value(str.c_str())); }
void mud_WidgetState__to_string(void* val, string& str) { str = g_enu[type<mud::WidgetState>().m_id]->name(uint32_t((*static_cast<mud::WidgetState*>(val)))); }
void mud_WidgetState__to_value(const string& str, void* val) { (*static_cast<mud::WidgetState*>(val)) = mud::WidgetState(g_enu[type<mud::WidgetState>().m_id]->value(str.c_str())); }
void mud_WindowState__to_string(void* val, string& str) { str = g_enu[type<mud::WindowState>().m_id]->name(uint32_t((*static_cast<mud::WindowState*>(val)))); }
void mud_WindowState__to_value(const string& str, void* val) { (*static_cast<mud::WindowState*>(val)) = mud::WindowState(g_enu[type<mud::WindowState>().m_id]->value(str.c_str())); }
size_t array_const_char____size(void* vec) { return (*static_cast<array<const char*>*>(vec)).size(); }
void* array_const_char____at(void* vec, size_t i) { return &(*static_cast<array<const char*>*>(vec))[i]; }
size_t array_float___size(void* vec) { return (*static_cast<array<float>*>(vec)).size(); }
void* array_float___at(void* vec, size_t i) { return &(*static_cast<array<float>*>(vec))[i]; }
size_t vector_mud_Space___size(void* vec) { return (*static_cast<vector<mud::Space>*>(vec)).size(); }
void* vector_mud_Space___at(void* vec, size_t i) { return &(*static_cast<vector<mud::Space>*>(vec))[i]; }
void vector_mud_Space___add(void* vec, void* value) { (*static_cast<vector<mud::Space>*>(vec)).push_back(*static_cast<mud::Space*>(value)); }
void vector_mud_Space___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Space>*>(vec)), *static_cast<mud::Space*>(value)); }
size_t vector_string___size(void* vec) { return (*static_cast<vector<string>*>(vec)).size(); }
void* vector_string___at(void* vec, size_t i) { return &(*static_cast<vector<string>*>(vec))[i]; }
void vector_string___add(void* vec, void* value) { (*static_cast<vector<string>*>(vec)).push_back(*static_cast<string*>(value)); }
void vector_string___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<string>*>(vec)), *static_cast<string*>(value)); }
void mud_CanvasConnect__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::CanvasConnect*>(ref))) mud::CanvasConnect(  ); }
void mud_CanvasConnect__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::CanvasConnect*>(ref))) mud::CanvasConnect((*static_cast<mud::CanvasConnect*>(other))); }
void mud_Clipboard__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Clipboard*>(ref))) mud::Clipboard(  ); }
void mud_Clipboard__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Clipboard*>(ref))) mud::Clipboard((*static_cast<mud::Clipboard*>(other))); }
void mud_Dim2_bool___construct_0(void* ref, array<void*> args) { new(&(*static_cast<mud::Dim2<bool>*>(ref))) mud::Dim2<bool>( *static_cast<bool*>(args[0]), *static_cast<bool*>(args[1]) ); }
void mud_Dim2_bool___construct_1(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Dim2<bool>*>(ref))) mud::Dim2<bool>(  ); }
void mud_Dim2_bool___copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Dim2<bool>*>(ref))) mud::Dim2<bool>((*static_cast<mud::Dim2<bool>*>(other))); }
void mud_Dim2_mud_Align___construct_0(void* ref, array<void*> args) { new(&(*static_cast<mud::Dim2<mud::Align>*>(ref))) mud::Dim2<mud::Align>( *static_cast<mud::Align*>(args[0]), *static_cast<mud::Align*>(args[1]) ); }
void mud_Dim2_mud_Align___construct_1(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Dim2<mud::Align>*>(ref))) mud::Dim2<mud::Align>(  ); }
void mud_Dim2_mud_Align___copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Dim2<mud::Align>*>(ref))) mud::Dim2<mud::Align>((*static_cast<mud::Dim2<mud::Align>*>(other))); }
void mud_Dim2_mud_AutoLayout___construct_0(void* ref, array<void*> args) { new(&(*static_cast<mud::Dim2<mud::AutoLayout>*>(ref))) mud::Dim2<mud::AutoLayout>( *static_cast<mud::AutoLayout*>(args[0]), *static_cast<mud::AutoLayout*>(args[1]) ); }
void mud_Dim2_mud_AutoLayout___construct_1(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Dim2<mud::AutoLayout>*>(ref))) mud::Dim2<mud::AutoLayout>(  ); }
void mud_Dim2_mud_AutoLayout___copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Dim2<mud::AutoLayout>*>(ref))) mud::Dim2<mud::AutoLayout>((*static_cast<mud::Dim2<mud::AutoLayout>*>(other))); }
void mud_Dim2_mud_Pivot___construct_0(void* ref, array<void*> args) { new(&(*static_cast<mud::Dim2<mud::Pivot>*>(ref))) mud::Dim2<mud::Pivot>( *static_cast<mud::Pivot*>(args[0]), *static_cast<mud::Pivot*>(args[1]) ); }
void mud_Dim2_mud_Pivot___construct_1(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Dim2<mud::Pivot>*>(ref))) mud::Dim2<mud::Pivot>(  ); }
void mud_Dim2_mud_Pivot___copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Dim2<mud::Pivot>*>(ref))) mud::Dim2<mud::Pivot>((*static_cast<mud::Dim2<mud::Pivot>*>(other))); }
void mud_Dim2_mud_Sizing___construct_0(void* ref, array<void*> args) { new(&(*static_cast<mud::Dim2<mud::Sizing>*>(ref))) mud::Dim2<mud::Sizing>( *static_cast<mud::Sizing*>(args[0]), *static_cast<mud::Sizing*>(args[1]) ); }
void mud_Dim2_mud_Sizing___construct_1(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Dim2<mud::Sizing>*>(ref))) mud::Dim2<mud::Sizing>(  ); }
void mud_Dim2_mud_Sizing___copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Dim2<mud::Sizing>*>(ref))) mud::Dim2<mud::Sizing>((*static_cast<mud::Dim2<mud::Sizing>*>(other))); }
void mud_Dim2_size_t___construct_0(void* ref, array<void*> args) { new(&(*static_cast<mud::Dim2<size_t>*>(ref))) mud::Dim2<size_t>( *static_cast<size_t*>(args[0]), *static_cast<size_t*>(args[1]) ); }
void mud_Dim2_size_t___construct_1(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Dim2<size_t>*>(ref))) mud::Dim2<size_t>(  ); }
void mud_Dim2_size_t___copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Dim2<size_t>*>(ref))) mud::Dim2<size_t>((*static_cast<mud::Dim2<size_t>*>(other))); }
void mud_Dock__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Dock*>(ref))) mud::Dock(  ); }
void mud_Dock__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Dock*>(ref))) mud::Dock((*static_cast<mud::Dock*>(other))); }
void mud_Gradient__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Gradient*>(ref))) mud::Gradient(  ); }
void mud_Gradient__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Gradient*>(ref))) mud::Gradient((*static_cast<mud::Gradient*>(other))); }
void mud_ImageSkin__construct_0(void* ref, array<void*> args) { new(&(*static_cast<mud::ImageSkin*>(ref))) mud::ImageSkin( *static_cast<mud::Image*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]), *static_cast<int*>(args[3]), *static_cast<int*>(args[4]), *static_cast<int*>(args[5]), *static_cast<mud::Dim*>(args[6]) ); }
void mud_ImageSkin__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::ImageSkin*>(ref))) mud::ImageSkin((*static_cast<mud::ImageSkin*>(other))); }
void mud_InkStyle__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::InkStyle*>(ref))) mud::InkStyle(  ); }
void mud_InkStyle__construct_1(void* ref, array<void*> args) { new(&(*static_cast<mud::InkStyle*>(ref))) mud::InkStyle( static_cast<const char*>(args[0]) ); }
void mud_InkStyle__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::InkStyle*>(ref))) mud::InkStyle((*static_cast<mud::InkStyle*>(other))); }
void mud_Layout__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Layout*>(ref))) mud::Layout(  ); }
void mud_Layout__construct_1(void* ref, array<void*> args) { new(&(*static_cast<mud::Layout*>(ref))) mud::Layout( static_cast<const char*>(args[0]) ); }
void mud_Layout__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Layout*>(ref))) mud::Layout((*static_cast<mud::Layout*>(other))); }
void mud_NodeConnection__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::NodeConnection*>(ref))) mud::NodeConnection(  ); }
void mud_NodeConnection__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::NodeConnection*>(ref))) mud::NodeConnection((*static_cast<mud::NodeConnection*>(other))); }
void mud_Paint__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Paint*>(ref))) mud::Paint(  ); }
void mud_Paint__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Paint*>(ref))) mud::Paint((*static_cast<mud::Paint*>(other))); }
void mud_Shadow__construct_0(void* ref, array<void*> args) { new(&(*static_cast<mud::Shadow*>(ref))) mud::Shadow( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<mud::Colour*>(args[4]) ); }
void mud_Shadow__construct_1(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Shadow*>(ref))) mud::Shadow(  ); }
void mud_Shadow__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Shadow*>(ref))) mud::Shadow((*static_cast<mud::Shadow*>(other))); }
void mud_Space__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::Space*>(ref))) mud::Space(  ); }
void mud_Space__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::Space*>(ref))) mud::Space((*static_cast<mud::Space*>(other))); }
//void* mud_Style__get_name(void* object) { return (*static_cast<mud::Style*>(object)).name(); }
void* mud_Style__get_layout(void* object) { return &(*static_cast<mud::Style*>(object)).layout(); }
void* mud_Style__get_skin(void* object) { return &(*static_cast<mud::Style*>(object)).skin(); }
void mud_TextCursor__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::TextCursor*>(ref))) mud::TextCursor(  ); }
void mud_TextCursor__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::TextCursor*>(ref))) mud::TextCursor((*static_cast<mud::TextCursor*>(other))); }
void mud_TextMarker__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::TextMarker*>(ref))) mud::TextMarker(  ); }
void mud_TextMarker__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::TextMarker*>(ref))) mud::TextMarker((*static_cast<mud::TextMarker*>(other))); }
void mud_TextPaint__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::TextPaint*>(ref))) mud::TextPaint(  ); }
void mud_TextPaint__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::TextPaint*>(ref))) mud::TextPaint((*static_cast<mud::TextPaint*>(other))); }
void mud_TextSelection__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::TextSelection*>(ref))) mud::TextSelection(  ); }
void mud_TextSelection__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::TextSelection*>(ref))) mud::TextSelection((*static_cast<mud::TextSelection*>(other))); }
void mud_UiRect__construct_0(void* ref, array<void*> args) { UNUSED(args); new(&(*static_cast<mud::UiRect*>(ref))) mud::UiRect(  ); }
void mud_UiRect__copy_construct(void* ref, void* other) { new(&(*static_cast<mud::UiRect*>(ref))) mud::UiRect((*static_cast<mud::UiRect*>(other))); }
void mud_Widget_focused(void* object, array<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).focused(); }
void mud_Widget_hovered(void* object, array<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).hovered(); }
void mud_Widget_pressed(void* object, array<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).pressed(); }
void mud_Widget_activated(void* object, array<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).activated(); }
void mud_Widget_selected(void* object, array<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).selected(); }
void mud_Widget_modal(void* object, array<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).modal(); }
void mud_Widget_closed(void* object, array<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<mud::Widget*>(object)).closed(); }
void mud_Widget_ui_window(void* object, array<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Widget*>(object)).ui_window(); }
void mud_Widget_ui(void* object, array<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Widget*>(object)).ui(); }
void mud_Widget_parent_modal(void* object, array<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Widget*>(object)).parent_modal(); }
void mud_Widget_toggle_state(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).toggle_state(*static_cast<mud::WidgetState*>(args[0])); }
void mud_Widget_disable_state(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).disable_state(*static_cast<mud::WidgetState*>(args[0])); }
void mud_Widget_set_state(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).set_state(*static_cast<mud::WidgetState*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_Widget_enable_state(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).enable_state(*static_cast<mud::WidgetState*>(args[0])); }
void mud_Widget_clear_focus(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).clear_focus(); }
void mud_Widget_take_focus(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).take_focus(); }
void mud_Widget_yield_focus(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).yield_focus(); }
void mud_Widget_take_modal(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Widget*>(object)).take_modal(*static_cast<uint32_t*>(args[0])); }
void mud_Widget_yield_modal(void* object, array<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::Widget*>(object)).yield_modal(); }
void mud_Widget_key_event(void* object, array<void*> args, void*& result) { (*static_cast<mud::KeyEvent*>(result)) = (*static_cast<mud::Widget*>(object)).key_event(*static_cast<mud::Key*>(args[0]), *static_cast<mud::EventType*>(args[1]), *static_cast<mud::InputMod*>(args[2])); }
void mud_Widget_key_stroke(void* object, array<void*> args, void*& result) { (*static_cast<mud::KeyEvent*>(result)) = (*static_cast<mud::Widget*>(object)).key_stroke(*static_cast<mud::Key*>(args[0]), *static_cast<mud::InputMod*>(args[1])); }
void mud_Widget_char_stroke(void* object, array<void*> args, void*& result) { (*static_cast<mud::KeyEvent*>(result)) = (*static_cast<mud::Widget*>(object)).char_stroke(*static_cast<mud::Key*>(args[0]), *static_cast<mud::InputMod*>(args[1])); }
void mud_Widget_mouse_event(void* object, array<void*> args, void*& result) { (*static_cast<mud::MouseEvent*>(result)) = (*static_cast<mud::Widget*>(object)).mouse_event(*static_cast<mud::DeviceType*>(args[0]), *static_cast<mud::EventType*>(args[1]), *static_cast<mud::InputMod*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_Ui_begin(void* object, array<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<mud::Ui*>(object)).begin(); }
void mud_ui_widget_0(array<void*> args, void*& result) { result = &mud::ui::widget(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<mud::Dim*>(args[3]), *static_cast<mud::Dim2<size_t>*>(args[4])); }
void mud_ui_item_1(array<void*> args, void*& result) { result = &mud::ui::item(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), static_cast<const char*>(args[2])); }
void mud_ui_multi_item_2(array<void*> args, void*& result) { result = &mud::ui::multi_item(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), *static_cast<array<const char*>*>(args[2]), static_cast<mud::Style*>(args[3])); }
void mud_ui_spanner_3(array<void*> args, void*& result) { result = &mud::ui::spanner(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), *static_cast<mud::Dim*>(args[2]), *static_cast<float*>(args[3])); }
void mud_ui_spacer_4(array<void*> args, void*& result) { result = &mud::ui::spacer(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_icon_5(array<void*> args, void*& result) { result = &mud::ui::icon(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_label_6(array<void*> args, void*& result) { result = &mud::ui::label(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_title_7(array<void*> args, void*& result) { result = &mud::ui::title(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_message_8(array<void*> args, void*& result) { result = &mud::ui::message(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_text_9(array<void*> args, void*& result) { result = &mud::ui::text(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_button_10(array<void*> args, void*& result) { result = &mud::ui::button(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_toggle_11(array<void*> args, void*& result) { result = &mud::ui::toggle(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1]), static_cast<const char*>(args[2])); }
void mud_ui_button_12(array<void*> args, void*& result) { result = &mud::ui::button(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1])); }
void mud_ui_toggle_13(array<void*> args, void*& result) { result = &mud::ui::toggle(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<string*>(args[2])); }
void mud_ui_multi_button_14(array<void*> args, void*& result) { result = &mud::ui::multi_button(*static_cast<mud::Widget*>(args[0]), *static_cast<array<const char*>*>(args[1]), static_cast<mud::Style*>(args[2])); }
void mud_ui_multi_toggle_15(array<void*> args, void*& result) { result = &mud::ui::multi_toggle(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<array<const char*>*>(args[2]), static_cast<mud::Style*>(args[3])); }
void mud_ui_modal_button_16(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::modal_button(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void mud_ui_modal_multi_button_17(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::modal_multi_button(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Widget*>(args[1]), *static_cast<array<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void mud_ui_checkbox_18(array<void*> args, void*& result) { result = &mud::ui::checkbox(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_ui_fill_bar_19(array<void*> args, void*& result) { result = &mud::ui::fill_bar(*static_cast<mud::Widget*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Dim*>(args[2])); }
void mud_ui_image256_20(array<void*> args, void*& result) { result = &mud::ui::image256(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::Image256*>(args[2])); }
void mud_ui_image256_21(array<void*> args, void*& result) { result = &mud::ui::image256(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::Image256*>(args[2]), *static_cast<mud::vec2*>(args[3])); }
void mud_ui_image256_22(array<void*> args, void*& result) { result = &mud::ui::image256(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1]), *static_cast<mud::Image256*>(args[2])); }
void mud_ui_image256_23(array<void*> args, void*& result) { result = &mud::ui::image256(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1]), *static_cast<mud::Image256*>(args[2]), *static_cast<mud::vec2*>(args[3])); }
void mud_ui_radio_choice_24(array<void*> args, void*& result) { result = &mud::ui::radio_choice(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_ui_radio_switch_25(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::radio_switch(*static_cast<mud::Widget*>(args[0]), *static_cast<array<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<mud::Dim*>(args[3])); }
void mud_ui_popdown_26(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::popdown(*static_cast<mud::Widget*>(args[0]), *static_cast<array<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<mud::vec2*>(args[3]), *static_cast<mud::ui::PopupFlags*>(args[4])); }
void mud_ui_dropdown_27(array<void*> args, void*& result) { result = &mud::ui::dropdown(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), static_cast<const char*>(args[2]), *static_cast<mud::ui::PopupFlags*>(args[3]), static_cast<mud::Style*>(args[4])); }
void mud_ui_dropdown_input_28(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::dropdown_input(*static_cast<mud::Widget*>(args[0]), *static_cast<array<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_typedown_input_29(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::typedown_input(*static_cast<mud::Widget*>(args[0]), *static_cast<array<const char*>*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void mud_ui_menu_choice_30(array<void*> args, void*& result) { result = &mud::ui::menu_choice(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_menu_31(array<void*> args, void*& result) { result = &mud::ui::menu(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_ui_menubar_32(array<void*> args, void*& result) { result = &mud::ui::menubar(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_toolbutton_33(array<void*> args, void*& result) { result = &mud::ui::toolbutton(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_tooldock_34(array<void*> args, void*& result) { result = &mud::ui::tooldock(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_toolbar_35(array<void*> args, void*& result) { result = &mud::ui::toolbar(*static_cast<mud::Widget*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_ui_select_list_36(array<void*> args, void*& result) { result = &mud::ui::select_list(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_columns_37(array<void*> args, void*& result) { result = &mud::ui::columns(*static_cast<mud::Widget*>(args[0]), *static_cast<array<float>*>(args[1])); }
void mud_ui_table_38(array<void*> args, void*& result) { result = &mud::ui::table(*static_cast<mud::Widget*>(args[0]), *static_cast<array<const char*>*>(args[1]), *static_cast<array<float>*>(args[2])); }
void mud_ui_table_row_39(array<void*> args, void*& result) { result = &mud::ui::table_row(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_table_separator_40(array<void*> args, void*& result) { result = &mud::ui::table_separator(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_expandbox_41(array<void*> args, void*& result) { result = &mud::ui::expandbox(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2])); }
void mud_ui_tree_node_42(array<void*> args, void*& result) { result = &mud::ui::tree_node(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_tree_43(array<void*> args, void*& result) { result = &mud::ui::tree(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_tab_44(array<void*> args, void*& result) { result = mud::ui::tab(*static_cast<mud::Tabber*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_tabber_45(array<void*> args, void*& result) { result = &mud::ui::tabber(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_row_46(array<void*> args, void*& result) { result = &mud::ui::row(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_header_47(array<void*> args, void*& result) { result = &mud::ui::header(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_div_48(array<void*> args, void*& result) { result = &mud::ui::div(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_stack_49(array<void*> args, void*& result) { result = &mud::ui::stack(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_sheet_50(array<void*> args, void*& result) { result = &mud::ui::sheet(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_board_51(array<void*> args, void*& result) { result = &mud::ui::board(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_layout_52(array<void*> args, void*& result) { result = &mud::ui::layout(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_screen_53(array<void*> args, void*& result) { result = &mud::ui::screen(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_decal_54(array<void*> args, void*& result) { result = &mud::ui::decal(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_overlay_55(array<void*> args, void*& result) { result = &mud::ui::overlay(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_title_header_56(array<void*> args, void*& result) { result = &mud::ui::title_header(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_dummy_57(array<void*> args, void*& result) { result = &mud::ui::dummy(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1])); }
void mud_ui_popup_58(array<void*> args, void*& result) { result = &mud::ui::popup(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::ui::PopupFlags*>(args[1])); }
void mud_ui_popup_59(array<void*> args, void*& result) { result = &mud::ui::popup(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1]), *static_cast<mud::ui::PopupFlags*>(args[2])); }
void mud_ui_popup_at_60(array<void*> args, void*& result) { result = &mud::ui::popup_at(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1]), *static_cast<mud::ui::PopupFlags*>(args[2])); }
void mud_ui_modal_61(array<void*> args, void*& result) { result = &mud::ui::modal(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_modal_62(array<void*> args, void*& result) { result = &mud::ui::modal(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1])); }
void mud_ui_auto_modal_63(array<void*> args, void*& result) { result = &mud::ui::auto_modal(*static_cast<mud::Widget*>(args[0]), *static_cast<uint32_t*>(args[1])); }
void mud_ui_auto_modal_64(array<void*> args, void*& result) { result = &mud::ui::auto_modal(*static_cast<mud::Widget*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<mud::vec2*>(args[2])); }
void mud_ui_context_65(array<void*> args, void*& result) { result = mud::ui::context(*static_cast<mud::Widget*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<mud::ui::PopupFlags*>(args[2])); }
void mud_ui_hoverbox_66(array<void*> args, void*& result) { result = mud::ui::hoverbox(*static_cast<mud::Widget*>(args[0]), *static_cast<float*>(args[1])); }
void mud_ui_tooltip_67(array<void*> args, void*& result) { result = mud::ui::tooltip(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1]), static_cast<const char*>(args[2])); }
void mud_ui_cursor_68(array<void*> args, void*& result) { result = &mud::ui::cursor(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1]), *static_cast<mud::Widget*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_rectangle_69(array<void*> args, void*& result) { result = &mud::ui::rectangle(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec4*>(args[1])); }
void mud_ui_dockspace_70(array<void*> args, void*& result) { result = &mud::ui::dockspace(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Docksystem*>(args[1])); }
void mud_ui_dockbar_71(array<void*> args, void*& result) { result = &mud::ui::dockbar(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Docksystem*>(args[1])); }
void mud_ui_dockitem_72(array<void*> args, void*& result) { result = mud::ui::dockitem(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Docksystem*>(args[1]), *static_cast<mud::Dock*>(args[2])); }
void mud_ui_text_box_73(array<void*> args, void*& result) { result = &mud::ui::text_box(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Style*>(args[1]), *static_cast<string*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<size_t*>(args[4]), *static_cast<string*>(args[5])); }
void mud_ui_type_in_74(array<void*> args, void*& result) { result = &mud::ui::type_in(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1]), *static_cast<size_t*>(args[2]), *static_cast<string*>(args[3])); }
void mud_ui_text_edit_75(array<void*> args, void*& result) { result = &mud::ui::text_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1]), *static_cast<size_t*>(args[2]), static_cast<vector<string>*>(args[3])); }
void mud_ui_code_edit_76(array<void*> args, void*& result) { result = &mud::ui::code_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1]), *static_cast<size_t*>(args[2]), static_cast<vector<string>*>(args[3])); }
void mud_ui_drag_float_77(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::drag_float(*static_cast<mud::Widget*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_ui_vec2_edit_78(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::vec2_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1])); }
void mud_ui_vec3_edit_79(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::vec3_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_ui_quat_edit_80(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::quat_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::quat*>(args[1])); }
void mud_ui_color_edit_hsl_81(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_edit_hsl(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1]), *static_cast<mud::Colour*>(args[2])); }
void mud_ui_color_display_82(array<void*> args, void*& result) { result = &mud::ui::color_display(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_ui_color_edit_83(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_ui_color_edit_simple_84(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_edit_simple(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_ui_color_toggle_edit_85(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_toggle_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Colour*>(args[1])); }
void mud_ui_curve_graph_86(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::curve_graph(*static_cast<mud::Widget*>(args[0]), *static_cast<array<float>*>(args[1]), *static_cast<array<float>*>(args[2])); }
void mud_ui_curve_edit_87(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::curve_edit(*static_cast<mud::Widget*>(args[0]), *static_cast<array<float>*>(args[1]), *static_cast<array<float>*>(args[2])); }
void mud_ui_flag_field_88(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::flag_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<uint8_t*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_ui_radio_field_89(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::radio_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<array<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<mud::Dim*>(args[4]), *static_cast<bool*>(args[5])); }
void mud_ui_dropdown_field_90(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::dropdown_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<array<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_ui_typedown_field_91(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::typedown_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<array<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<bool*>(args[4])); }
void mud_ui_color_field_92(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::color_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::Colour*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_color_display_field_93(array<void*> args, void*& result) { UNUSED(result);  mud::ui::color_display_field(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::Colour*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_node_input_94(array<void*> args, void*& result) { result = &mud::ui::node_input(*static_cast<mud::Node*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<mud::Colour*>(args[3]), *static_cast<bool*>(args[4]), *static_cast<bool*>(args[5])); }
void mud_ui_node_output_95(array<void*> args, void*& result) { result = &mud::ui::node_output(*static_cast<mud::Node*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<mud::Colour*>(args[3]), *static_cast<bool*>(args[4]), *static_cast<bool*>(args[5])); }
void mud_ui_node_96(array<void*> args, void*& result) { result = &mud::ui::node(*static_cast<mud::Canvas*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::vec2*>(args[2]), *static_cast<int*>(args[3]), *static_cast<mud::Ref*>(args[4])); }
void mud_ui_node_cable_97(array<void*> args, void*& result) { result = &mud::ui::node_cable(*static_cast<mud::Canvas*>(args[0]), *static_cast<mud::NodePlug*>(args[1]), *static_cast<mud::NodePlug*>(args[2])); }
void mud_ui_canvas_98(array<void*> args, void*& result) { result = &mud::ui::canvas(*static_cast<mud::Widget*>(args[0]), *static_cast<size_t*>(args[1])); }
void mud_ui_scrollable_99(array<void*> args, void*& result) { result = &mud::ui::scrollable(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_sequence_100(array<void*> args, void*& result) { result = &mud::ui::sequence(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_scroll_sequence_101(array<void*> args, void*& result) { result = &mud::ui::scroll_sequence(*static_cast<mud::Widget*>(args[0])); }
void mud_ui_multiselect_logic_102(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::multiselect_logic(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1]), *static_cast<vector<mud::Ref>*>(args[2])); }
void mud_ui_select_logic_103(array<void*> args, void*& result) { (*static_cast<bool*>(result)) = mud::ui::select_logic(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1]), *static_cast<mud::Ref*>(args[2])); }
void mud_ui_element_104(array<void*> args, void*& result) { result = &mud::ui::element(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_ui_sequence_element_105(array<void*> args, void*& result) { result = &mud::ui::sequence_element(*static_cast<mud::ui::Sequence*>(args[0]), *static_cast<mud::Ref*>(args[1])); }
void mud_ui_window_106(array<void*> args, void*& result) { result = &mud::ui::window(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), *static_cast<mud::WindowState*>(args[2])); }
void mud_ui_dir_item_107(array<void*> args, void*& result) { result = &mud::ui::dir_item(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_file_item_108(array<void*> args, void*& result) { result = &mud::ui::file_item(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_file_list_109(array<void*> args, void*& result) { result = &mud::ui::file_list(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1])); }
void mud_ui_file_browser_110(array<void*> args, void*& result) { result = &mud::ui::file_browser(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1])); }
void mud_ui_dir_node_111(array<void*> args, void*& result) { result = &mud::ui::dir_node(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1]), static_cast<const char*>(args[2]), *static_cast<bool*>(args[3])); }
void mud_ui_file_node_112(array<void*> args, void*& result) { result = &mud::ui::file_node(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_file_tree_113(array<void*> args, void*& result) { result = &mud::ui::file_tree(*static_cast<mud::Widget*>(args[0]), static_cast<const char*>(args[1])); }
void mud_ui_command_line_114(array<void*> args, void*& result) { result = &mud::ui::command_line(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1]), *static_cast<string*>(args[2])); }
void mud_ui_console_115(array<void*> args, void*& result) { result = &mud::ui::console(*static_cast<mud::Widget*>(args[0]), *static_cast<string*>(args[1]), *static_cast<string*>(args[2]), *static_cast<string*>(args[3]), *static_cast<size_t*>(args[4])); }

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
		static cstring ids[] = { "Left", "CENTER", "Right", "OUT_LEFT", "OUT_RIGHT" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::Align vars[] = { mud::Left, mud::CENTER, mud::Right, mud::OUT_LEFT, mud::OUT_RIGHT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Align__to_string,
		                           mud_Align__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::AutoLayout>();
		static Meta meta = { t, &namspc({ "mud" }), "AutoLayout", sizeof(mud::AutoLayout), TypeClass::Enum };
		static cstring ids[] = { "NO_LAYOUT", "AUTO_SIZE", "AUTO_LAYOUT" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::AutoLayout vars[] = { mud::NO_LAYOUT, mud::AUTO_SIZE, mud::AUTO_LAYOUT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_AutoLayout__to_string,
		                           mud_AutoLayout__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Clipping>();
		static Meta meta = { t, &namspc({ "mud" }), "Clipping", sizeof(mud::Clipping), TypeClass::Enum };
		static cstring ids[] = { "NOCLIP", "CLIP", "UNCLIP" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Clipping vars[] = { mud::NOCLIP, mud::CLIP, mud::UNCLIP};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Clipping__to_string,
		                           mud_Clipping__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Dim>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim", sizeof(mud::Dim), TypeClass::Enum };
		static cstring ids[] = { "DIM_X", "DIM_Y", "DIM_NONE" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Dim vars[] = { mud::DIM_X, mud::DIM_Y, mud::DIM_NONE};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Dim__to_string,
		                           mud_Dim__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Flow>();
		static Meta meta = { t, &namspc({ "mud" }), "Flow", sizeof(mud::Flow), TypeClass::Enum };
		static cstring ids[] = { "FLOW", "OVERLAY", "ALIGN", "FREE" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::Flow vars[] = { mud::FLOW, mud::OVERLAY, mud::ALIGN, mud::FREE};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Flow__to_string,
		                           mud_Flow__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::FlowAxis>();
		static Meta meta = { t, &namspc({ "mud" }), "FlowAxis", sizeof(mud::FlowAxis), TypeClass::Enum };
		static cstring ids[] = { "READING", "PARAGRAPH", "PARALLEL", "ORTHOGONAL", "AXIS_NONE" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::FlowAxis vars[] = { mud::READING, mud::PARAGRAPH, mud::PARALLEL, mud::ORTHOGONAL, mud::AXIS_NONE};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_FlowAxis__to_string,
		                           mud_FlowAxis__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::LayoutSolver>();
		static Meta meta = { t, &namspc({ "mud" }), "LayoutSolver", sizeof(mud::LayoutSolver), TypeClass::Enum };
		static cstring ids[] = { "FRAME_SOLVER", "ROW_SOLVER", "GRID_SOLVER", "TABLE_SOLVER" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::LayoutSolver vars[] = { mud::FRAME_SOLVER, mud::ROW_SOLVER, mud::GRID_SOLVER, mud::TABLE_SOLVER};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_LayoutSolver__to_string,
		                           mud_LayoutSolver__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Opacity>();
		static Meta meta = { t, &namspc({ "mud" }), "Opacity", sizeof(mud::Opacity), TypeClass::Enum };
		static cstring ids[] = { "OPAQUE", "CLEAR", "HOLLOW" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Opacity vars[] = { mud::OPAQUE, mud::CLEAR, mud::HOLLOW};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Opacity__to_string,
		                           mud_Opacity__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Pivot>();
		static Meta meta = { t, &namspc({ "mud" }), "Pivot", sizeof(mud::Pivot), TypeClass::Enum };
		static cstring ids[] = { "FORWARD", "REVERSE" };
		static uint32_t values[] = { 0, 1 };
		static mud::Pivot vars[] = { mud::FORWARD, mud::REVERSE};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, false, ids, values, refs };
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
		Type& t = type<mud::Sizing>();
		static Meta meta = { t, &namspc({ "mud" }), "Sizing", sizeof(mud::Sizing), TypeClass::Enum };
		static cstring ids[] = { "FIXED", "SHRINK", "WRAP", "EXPAND" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::Sizing vars[] = { mud::FIXED, mud::SHRINK, mud::WRAP, mud::EXPAND};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Sizing__to_string,
		                           mud_Sizing__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::SpacePreset>();
		static Meta meta = { t, &namspc({ "mud" }), "SpacePreset", sizeof(mud::SpacePreset), TypeClass::Enum };
		static cstring ids[] = { "SHEET", "FLEX", "ITEM", "UNIT", "BLOCK", "LINE", "STACK", "DIV", "SPACER", "BOARD", "LAYOUT" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		static mud::SpacePreset vars[] = { mud::SHEET, mud::FLEX, mud::ITEM, mud::UNIT, mud::BLOCK, mud::LINE, mud::STACK, mud::DIV, mud::SPACER, mud::BOARD, mud::LAYOUT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_SpacePreset__to_string,
		                           mud_SpacePreset__to_value };
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
		static cstring ids[] = { "WINDOW_NOSTATE", "WINDOW_HEADER", "WINDOW_DOCKABLE", "WINDOW_CLOSABLE", "WINDOW_MOVABLE", "WINDOW_SIZABLE", "WINDOW_DEFAULT" };
		static uint32_t values[] = { 0, 2, 4, 8, 16, 32, 58 };
		static mud::WindowState vars[] = { mud::WINDOW_NOSTATE, mud::WINDOW_HEADER, mud::WINDOW_DOCKABLE, mud::WINDOW_CLOSABLE, mud::WINDOW_MOVABLE, mud::WINDOW_SIZABLE, mud::WINDOW_DEFAULT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_WindowState__to_string,
		                           mud_WindowState__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<const char*>>();
		static Meta meta = { t, &namspc({}), "array<const char*>", sizeof(array<const char*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<const char*>(),
		                             array_const_char____size,
		                             array_const_char____at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<array<float>>();
		static Meta meta = { t, &namspc({}), "array<float>", sizeof(array<float>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<float>(),
		                             array_float___size,
		                             array_float___at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<vector<mud::Space>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Space>", sizeof(vector<mud::Space>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Space>(),
		                             vector_mud_Space___size,
		                             vector_mud_Space___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Space___add,
		                             vector_mud_Space___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<string>(),
		                             vector_string___size,
		                             vector_string___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_string___add,
		                             vector_string___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<string>(),
		                             vector_string___size,
		                             vector_string___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_string___add,
		                             vector_string___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<string>>();
		static Meta meta = { t, &namspc({}), "vector<string>", sizeof(vector<string>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<string>(),
		                             vector_string___size,
		                             vector_string___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_string___add,
		                             vector_string___remove };
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
		static string text_default = "";
		static bool line_mode_default = false;
		static vector<string> pasted_default = {};
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
			{ t, offsetof(mud::Clipboard, m_text), type<string>(), "text", &text_default, Member::Value, nullptr },
			{ t, offsetof(mud::Clipboard, m_line_mode), type<bool>(), "line_mode", &line_mode_default, Member::Value, nullptr },
			{ t, offsetof(mud::Clipboard, m_pasted), type<vector<string>>(), "pasted", &pasted_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Dim2<bool>
	{
		Type& t = type<mud::Dim2<bool>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<bool>", sizeof(mud::Dim2<bool>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Dim2_bool___construct_0, { { "a", type<bool>(),  }, { "b", type<bool>(),  } } },
			{ t, mud_Dim2_bool___construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Dim2_bool___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Dim2<bool>, x), type<bool>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Dim2<bool>, y), type<bool>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Dim2<mud::Align>
	{
		Type& t = type<mud::Dim2<mud::Align>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<mud::Align>", sizeof(mud::Dim2<mud::Align>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Dim2_mud_Align___construct_0, { { "a", type<mud::Align>(),  }, { "b", type<mud::Align>(),  } } },
			{ t, mud_Dim2_mud_Align___construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Dim2_mud_Align___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Dim2<mud::Align>, x), type<mud::Align>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Dim2<mud::Align>, y), type<mud::Align>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Dim2<mud::AutoLayout>
	{
		Type& t = type<mud::Dim2<mud::AutoLayout>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<mud::AutoLayout>", sizeof(mud::Dim2<mud::AutoLayout>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Dim2_mud_AutoLayout___construct_0, { { "a", type<mud::AutoLayout>(),  }, { "b", type<mud::AutoLayout>(),  } } },
			{ t, mud_Dim2_mud_AutoLayout___construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Dim2_mud_AutoLayout___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Dim2<mud::AutoLayout>, x), type<mud::AutoLayout>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Dim2<mud::AutoLayout>, y), type<mud::AutoLayout>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Dim2<mud::Pivot>
	{
		Type& t = type<mud::Dim2<mud::Pivot>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<mud::Pivot>", sizeof(mud::Dim2<mud::Pivot>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Dim2_mud_Pivot___construct_0, { { "a", type<mud::Pivot>(),  }, { "b", type<mud::Pivot>(),  } } },
			{ t, mud_Dim2_mud_Pivot___construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Dim2_mud_Pivot___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Dim2<mud::Pivot>, x), type<mud::Pivot>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Dim2<mud::Pivot>, y), type<mud::Pivot>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Dim2<mud::Sizing>
	{
		Type& t = type<mud::Dim2<mud::Sizing>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<mud::Sizing>", sizeof(mud::Dim2<mud::Sizing>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Dim2_mud_Sizing___construct_0, { { "a", type<mud::Sizing>(),  }, { "b", type<mud::Sizing>(),  } } },
			{ t, mud_Dim2_mud_Sizing___construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Dim2_mud_Sizing___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Dim2<mud::Sizing>, x), type<mud::Sizing>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Dim2<mud::Sizing>, y), type<mud::Sizing>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Dim2<size_t>
	{
		Type& t = type<mud::Dim2<size_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "Dim2<size_t>", sizeof(mud::Dim2<size_t>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Dim2_size_t___construct_0, { { "a", type<size_t>(),  }, { "b", type<size_t>(),  } } },
			{ t, mud_Dim2_size_t___construct_1, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Dim2_size_t___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Dim2<size_t>, x), type<size_t>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Dim2<size_t>, y), type<size_t>(), "y", nullptr, Member::Value, nullptr }
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
		static mud::Dim d_stretch_default = DIM_NONE;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ImageSkin__construct_0, { { "image", type<mud::Image>(),  }, { "left", type<int>(),  }, { "top", type<int>(),  }, { "right", type<int>(),  }, { "bottom", type<int>(),  }, { "margin", type<int>(), Param::Default }, { "stretch", type<mud::Dim>(), Param::Default } } }
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
			{ t, offsetof(mud::ImageSkin, d_stretch), type<mud::Dim>(), "d_stretch", &d_stretch_default, Member::Value, nullptr }
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
		static string name_default = "";
		static bool empty_default = true;
		static mud::Colour background_colour_default = mud::Colour::None;
		static mud::Colour border_colour_default = mud::Colour::None;
		static mud::Colour image_colour_default = mud::Colour::None;
		static mud::Colour text_colour_default = mud::Colour::None;
		static string text_font_default = "dejavu";
		static float text_size_default = 14.f;
		static bool text_break_default = false;
		static bool text_wrap_default = false;
		static bool weak_corners_default = false;
		static mud::Dim2<mud::Align> align_default = {Left,Left};
		static mud::Dim linear_gradient_dim_default = DIM_Y;
		static mud::Dim2<bool> stretch_default = {false,false};
		static mud::Image* image_default = nullptr;
		static mud::Image* overlay_default = nullptr;
		static mud::Image* tile_default = nullptr;
		static mud::Style* hover_cursor_default = nullptr;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_InkStyle__construct_0, {} },
			{ t, mud_InkStyle__construct_1, { { "name", type<const char*>(), Param::Nullable } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_InkStyle__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::InkStyle, m_name), type<string>(), "name", &name_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_empty), type<bool>(), "empty", &empty_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_background_colour), type<mud::Colour>(), "background_colour", &background_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_border_colour), type<mud::Colour>(), "border_colour", &border_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_image_colour), type<mud::Colour>(), "image_colour", &image_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_colour), type<mud::Colour>(), "text_colour", &text_colour_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_font), type<string>(), "text_font", &text_font_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_size), type<float>(), "text_size", &text_size_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_break), type<bool>(), "text_break", &text_break_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_text_wrap), type<bool>(), "text_wrap", &text_wrap_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_border_width), type<mud::vec4>(), "border_width", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_corner_radius), type<mud::vec4>(), "corner_radius", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_weak_corners), type<bool>(), "weak_corners", &weak_corners_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_padding), type<mud::vec4>(), "padding", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_margin), type<mud::vec4>(), "margin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_align), type<mud::Dim2<mud::Align>>(), "align", &align_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_linear_gradient), type<mud::vec2>(), "linear_gradient", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_linear_gradient_dim), type<mud::Dim>(), "linear_gradient_dim", &linear_gradient_dim_default, Member::Value, nullptr },
			{ t, offsetof(mud::InkStyle, m_stretch), type<mud::Dim2<bool>>(), "stretch", &stretch_default, Member::Value, nullptr },
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
		static string name_default = "";
		static mud::LayoutSolver solver_default = FRAME_SOLVER;
		static mud::Dim2<mud::AutoLayout> layout_default = {AUTO_LAYOUT,AUTO_LAYOUT};
		static mud::Flow flow_default = FLOW;
		static mud::Space space_default = SHEET;
		static mud::Clipping clipping_default = NOCLIP;
		static mud::Opacity opacity_default = CLEAR;
		static mud::Dim2<mud::Align> align_default = {Left,Left};
		static mud::Dim2<mud::Pivot> pivot_default = {FORWARD,FORWARD};
		static int zorder_default = 0;
		static bool no_grid_default = false;
		static size_t updated_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Layout__construct_0, {} },
			{ t, mud_Layout__construct_1, { { "name", type<const char*>(), Param::Nullable } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Layout__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Layout, m_name), type<string>(), "name", &name_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_solver), type<mud::LayoutSolver>(), "solver", &solver_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_layout), type<mud::Dim2<mud::AutoLayout>>(), "layout", &layout_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_flow), type<mud::Flow>(), "flow", &flow_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_space), type<mud::Space>(), "space", &space_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_clipping), type<mud::Clipping>(), "clipping", &clipping_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_opacity), type<mud::Opacity>(), "opacity", &opacity_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_align), type<mud::Dim2<mud::Align>>(), "align", &align_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_span), type<mud::vec2>(), "span", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_size), type<mud::vec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_padding), type<mud::vec4>(), "padding", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_margin), type<mud::vec2>(), "margin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_spacing), type<mud::vec2>(), "spacing", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_pivot), type<mud::Dim2<mud::Pivot>>(), "pivot", &pivot_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_zorder), type<int>(), "zorder", &zorder_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_no_grid), type<bool>(), "no_grid", &no_grid_default, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_grid_division), type<vector<mud::Space>>(), "grid_division", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Layout, m_table_division), type<vector<float>>(), "table_division", nullptr, Member::Value, nullptr },
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
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Shadow__construct_0, { { "xpos", type<float>(),  }, { "ypos", type<float>(),  }, { "blur", type<float>(),  }, { "spread", type<float>(),  }, { "colour", type<mud::Colour>(), Param::Default } } },
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
			{ t, SIZE_MAX, type<mud::Layout>(), "layout", nullptr, Member::Flags(Member::Value|Member::NonMutable|Member::Link), mud_Style__get_layout },
			{ t, SIZE_MAX, type<mud::InkStyle>(), "skin", nullptr, Member::Flags(Member::Value|Member::NonMutable|Member::Link), mud_Style__get_skin }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
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
			{ t, offsetof(mud::TextPaint, m_colour), type<mud::Colour>(), "colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TextPaint, m_size), type<float>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TextPaint, m_align), type<mud::Dim2<mud::Align>>(), "align", nullptr, Member::Value, nullptr },
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
		static mud::vec2 position_default = Zero2;
		static mud::vec2 size_default = Zero2;
		static mud::vec2 content_default = Zero2;
		static mud::vec2 span_default = Unit2;
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
			{ t, offsetof(mud::UiRect, m_position), type<mud::vec2>(), "position", &position_default, Member::Value, nullptr },
			{ t, offsetof(mud::UiRect, m_size), type<mud::vec2>(), "size", &size_default, Member::Value, nullptr },
			{ t, offsetof(mud::UiRect, m_content), type<mud::vec2>(), "content", &content_default, Member::Value, nullptr },
			{ t, offsetof(mud::UiRect, m_span), type<mud::vec2>(), "span", &span_default, Member::Value, nullptr },
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
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
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
		static size_t index_default = 0;
		static bool open_default = false;
		static mud::Widget* body_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Widget, m_frame), type<mud::Frame>(), "frame", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Widget, m_state), type<mud::WidgetState>(), "state", &state_default, Member::Value, nullptr },
			{ t, offsetof(mud::Widget, m_switch), type<uint32_t>(), "switch", &switch_default, Member::Value, nullptr },
			{ t, offsetof(mud::Widget, m_index), type<size_t>(), "index", &index_default, Member::Value, nullptr },
			{ t, offsetof(mud::Widget, m_open), type<bool>(), "open", &open_default, Member::Value, nullptr },
			{ t, offsetof(mud::Widget, m_body), type<mud::Widget>(), "body", body_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "focused", Address(), mud_Widget_focused, {}, { &type<bool>(), QualType::None } },
			{ t, "hovered", Address(), mud_Widget_hovered, {}, { &type<bool>(), QualType::None } },
			{ t, "pressed", Address(), mud_Widget_pressed, {}, { &type<bool>(), QualType::None } },
			{ t, "activated", Address(), mud_Widget_activated, {}, { &type<bool>(), QualType::None } },
			{ t, "selected", Address(), mud_Widget_selected, {}, { &type<bool>(), QualType::None } },
			{ t, "modal", Address(), mud_Widget_modal, {}, { &type<bool>(), QualType::None } },
			{ t, "closed", Address(), mud_Widget_closed, {}, { &type<bool>(), QualType::None } },
			{ t, "ui_window", Address(), mud_Widget_ui_window, {}, { &type<mud::UiWindow>(), QualType::None } },
			{ t, "ui", Address(), mud_Widget_ui, {}, { &type<mud::Ui>(), QualType::None } },
			{ t, "parent_modal", Address(), mud_Widget_parent_modal, {}, { &type<mud::Widget>(), QualType::None } },
			{ t, "toggle_state", Address(), mud_Widget_toggle_state, { { "state", type<mud::WidgetState>(),  } }, g_qvoid },
			{ t, "disable_state", Address(), mud_Widget_disable_state, { { "state", type<mud::WidgetState>(),  } }, g_qvoid },
			{ t, "set_state", Address(), mud_Widget_set_state, { { "state", type<mud::WidgetState>(),  }, { "enabled", type<bool>(),  } }, g_qvoid },
			{ t, "enable_state", Address(), mud_Widget_enable_state, { { "state", type<mud::WidgetState>(),  } }, g_qvoid },
			{ t, "clear_focus", Address(), mud_Widget_clear_focus, {}, g_qvoid },
			{ t, "take_focus", Address(), mud_Widget_take_focus, {}, g_qvoid },
			{ t, "yield_focus", Address(), mud_Widget_yield_focus, {}, g_qvoid },
			{ t, "take_modal", Address(), mud_Widget_take_modal, { { "device_filter", type<uint32_t>(),  } }, g_qvoid },
			{ t, "yield_modal", Address(), mud_Widget_yield_modal, {}, g_qvoid },
			{ t, "key_event", Address(), mud_Widget_key_event, { { "code", type<mud::Key>(),  }, { "event_type", type<mud::EventType>(),  }, { "modifier", type<mud::InputMod>(), Param::Default } }, { &type<mud::KeyEvent>(), QualType::None } },
			{ t, "key_stroke", Address(), mud_Widget_key_stroke, { { "code", type<mud::Key>(),  }, { "modifier", type<mud::InputMod>(), Param::Default } }, { &type<mud::KeyEvent>(), QualType::None } },
			{ t, "char_stroke", Address(), mud_Widget_char_stroke, { { "code", type<mud::Key>(),  }, { "modifier", type<mud::InputMod>(), Param::Default } }, { &type<mud::KeyEvent>(), QualType::None } },
			{ t, "mouse_event", Address(), mud_Widget_mouse_event, { { "device", type<mud::DeviceType>(),  }, { "event_type", type<mud::EventType>(),  }, { "modifier", type<mud::InputMod>(), Param::Default }, { "consume", type<bool>(), Param::Default } }, { &type<mud::MouseEvent>(), QualType::None } }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, methods, {}, };
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
		m.m_types.push_back(&type<mud::Align>());
		m.m_types.push_back(&type<mud::AutoLayout>());
		m.m_types.push_back(&type<mud::CanvasConnect>());
		m.m_types.push_back(&type<mud::Clipboard>());
		m.m_types.push_back(&type<mud::Clipping>());
		m.m_types.push_back(&type<mud::Dim>());
		m.m_types.push_back(&type<mud::Dim2<bool>>());
		m.m_types.push_back(&type<mud::Dim2<mud::Align>>());
		m.m_types.push_back(&type<mud::Dim2<mud::AutoLayout>>());
		m.m_types.push_back(&type<mud::Dim2<mud::Pivot>>());
		m.m_types.push_back(&type<mud::Dim2<mud::Sizing>>());
		m.m_types.push_back(&type<mud::Dim2<size_t>>());
		m.m_types.push_back(&type<mud::Dock>());
		m.m_types.push_back(&type<mud::Docksystem>());
		m.m_types.push_back(&type<mud::Flow>());
		m.m_types.push_back(&type<mud::FlowAxis>());
		m.m_types.push_back(&type<mud::Gradient>());
		m.m_types.push_back(&type<mud::GridSolver>());
		m.m_types.push_back(&type<mud::ImageSkin>());
		m.m_types.push_back(&type<mud::InkStyle>());
		m.m_types.push_back(&type<mud::Layer>());
		m.m_types.push_back(&type<mud::Layout>());
		m.m_types.push_back(&type<mud::LayoutSolver>());
		m.m_types.push_back(&type<mud::NodeConnection>());
		m.m_types.push_back(&type<mud::Opacity>());
		m.m_types.push_back(&type<mud::Paint>());
		m.m_types.push_back(&type<mud::Pivot>());
		m.m_types.push_back(&type<mud::ui::PopupFlags>());
		m.m_types.push_back(&type<mud::Shadow>());
		m.m_types.push_back(&type<mud::Sizing>());
		m.m_types.push_back(&type<mud::Space>());
		m.m_types.push_back(&type<mud::SpacePreset>());
		m.m_types.push_back(&type<mud::Style>());
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
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<const char*>>());
		m.m_types.push_back(&type<array<float>>());
		m.m_types.push_back(&type<vector<mud::Space>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<vector<string>>());
		m.m_types.push_back(&type<mud::Dockable>());
		m.m_types.push_back(&type<mud::Frame>());
		m.m_types.push_back(&type<mud::Widget>());
		m.m_types.push_back(&type<mud::Canvas>());
		m.m_types.push_back(&type<mud::Docker>());
		m.m_types.push_back(&type<mud::Dockbar>());
		m.m_types.push_back(&type<mud::Dockspace>());
		m.m_types.push_back(&type<mud::Expandbox>());
		m.m_types.push_back(&type<mud::FrameSolver>());
		m.m_types.push_back(&type<mud::RowSolver>());
		m.m_types.push_back(&type<mud::LineSolver>());
		m.m_types.push_back(&type<mud::Node>());
		m.m_types.push_back(&type<mud::NodePlug>());
		m.m_types.push_back(&type<mud::ScrollSheet>());
		m.m_types.push_back(&type<mud::ui::Sequence>());
		m.m_types.push_back(&type<mud::Tabber>());
		m.m_types.push_back(&type<mud::Table>());
		m.m_types.push_back(&type<mud::TextEdit>());
		m.m_types.push_back(&type<mud::TreeNode>());
		m.m_types.push_back(&type<mud::Ui>());
		m.m_types.push_back(&type<mud::Window>());
		{
			static Function f = { &namspc({ "mud", "ui" }), "widget", nullptr, mud_ui_widget_0, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "open", type<bool>(), Param::Default }, { "length", type<mud::Dim>(), Param::Default }, { "index", type<mud::Dim2<size_t>>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "item", nullptr, mud_ui_item_1, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "multi_item", nullptr, mud_ui_multi_item_2, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "elements", type<array<const char*>>(),  }, { "element_style", type<mud::Style>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "spanner", nullptr, mud_ui_spanner_3, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "dim", type<mud::Dim>(),  }, { "span", type<float>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "spacer", nullptr, mud_ui_spacer_4, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "icon", nullptr, mud_ui_icon_5, { { "parent", type<mud::Widget>(),  }, { "image", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "label", nullptr, mud_ui_label_6, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "title", nullptr, mud_ui_title_7, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "message", nullptr, mud_ui_message_8, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "text", nullptr, mud_ui_text_9, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "button", nullptr, mud_ui_button_10, { { "parent", type<mud::Widget>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "toggle", nullptr, mud_ui_toggle_11, { { "parent", type<mud::Widget>(),  }, { "on", type<bool>(),  }, { "content", type<const char*>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "button", nullptr, mud_ui_button_12, { { "parent", type<mud::Widget>(),  }, { "content", type<string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "toggle", nullptr, mud_ui_toggle_13, { { "parent", type<mud::Widget>(),  }, { "on", type<bool>(),  }, { "content", type<string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "multi_button", nullptr, mud_ui_multi_button_14, { { "parent", type<mud::Widget>(),  }, { "elements", type<array<const char*>>(),  }, { "element_style", type<mud::Style>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "multi_toggle", nullptr, mud_ui_multi_toggle_15, { { "parent", type<mud::Widget>(),  }, { "on", type<bool>(),  }, { "elements", type<array<const char*>>(),  }, { "element_style", type<mud::Style>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "modal_button", nullptr, mud_ui_modal_button_16, { { "screen", type<mud::Widget>(),  }, { "parent", type<mud::Widget>(),  }, { "content", type<const char*>(), Param::Nullable }, { "mode", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "modal_multi_button", nullptr, mud_ui_modal_multi_button_17, { { "screen", type<mud::Widget>(),  }, { "parent", type<mud::Widget>(),  }, { "elements", type<array<const char*>>(),  }, { "mode", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "checkbox", nullptr, mud_ui_checkbox_18, { { "parent", type<mud::Widget>(),  }, { "on", type<bool>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "fill_bar", nullptr, mud_ui_fill_bar_19, { { "parent", type<mud::Widget>(),  }, { "percentage", type<float>(),  }, { "dim", type<mud::Dim>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "image256", nullptr, mud_ui_image256_20, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "source", type<mud::Image256>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "image256", nullptr, mud_ui_image256_21, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "source", type<mud::Image256>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "image256", nullptr, mud_ui_image256_22, { { "parent", type<mud::Widget>(),  }, { "name", type<string>(),  }, { "source", type<mud::Image256>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "image256", nullptr, mud_ui_image256_23, { { "parent", type<mud::Widget>(),  }, { "name", type<string>(),  }, { "source", type<mud::Image256>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "radio_choice", nullptr, mud_ui_radio_choice_24, { { "parent", type<mud::Widget>(),  }, { "value", type<const char*>(), Param::Nullable }, { "active", type<bool>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "radio_switch", nullptr, mud_ui_radio_switch_25, { { "parent", type<mud::Widget>(),  }, { "labels", type<array<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "dim", type<mud::Dim>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "popdown", nullptr, mud_ui_popdown_26, { { "parent", type<mud::Widget>(),  }, { "choices", type<array<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "position", type<mud::vec2>(),  }, { "flags", type<mud::ui::PopupFlags>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dropdown", nullptr, mud_ui_dropdown_27, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "value", type<const char*>(), Param::Nullable }, { "flags", type<mud::ui::PopupFlags>(),  }, { "list_style", type<mud::Style>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dropdown_input", nullptr, mud_ui_dropdown_input_28, { { "parent", type<mud::Widget>(),  }, { "choices", type<array<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "compact", type<bool>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "typedown_input", nullptr, mud_ui_typedown_input_29, { { "parent", type<mud::Widget>(),  }, { "choices", type<array<const char*>>(),  }, { "value", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "menu_choice", nullptr, mud_ui_menu_choice_30, { { "parent", type<mud::Widget>(),  }, { "content", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "menu", nullptr, mud_ui_menu_31, { { "parent", type<mud::Widget>(),  }, { "label", type<const char*>(), Param::Nullable }, { "submenu", type<bool>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "menubar", nullptr, mud_ui_menubar_32, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "toolbutton", nullptr, mud_ui_toolbutton_33, { { "parent", type<mud::Widget>(),  }, { "icon", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tooldock", nullptr, mud_ui_tooldock_34, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "toolbar", nullptr, mud_ui_toolbar_35, { { "parent", type<mud::Widget>(),  }, { "wrap", type<bool>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "select_list", nullptr, mud_ui_select_list_36, { { "parent", type<mud::Widget>(),  } }, { &type<mud::ScrollSheet>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "columns", nullptr, mud_ui_columns_37, { { "parent", type<mud::Widget>(),  }, { "weights", type<array<float>>(),  } }, { &type<mud::Table>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "table", nullptr, mud_ui_table_38, { { "parent", type<mud::Widget>(),  }, { "columns", type<array<const char*>>(),  }, { "weights", type<array<float>>(),  } }, { &type<mud::Table>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "table_row", nullptr, mud_ui_table_row_39, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "table_separator", nullptr, mud_ui_table_separator_40, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "expandbox", nullptr, mud_ui_expandbox_41, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "open", type<bool>(), Param::Default } }, { &type<mud::Expandbox>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tree_node", nullptr, mud_ui_tree_node_42, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "leaf", type<bool>(), Param::Default }, { "open", type<bool>(), Param::Default } }, { &type<mud::TreeNode>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tree", nullptr, mud_ui_tree_43, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tab", nullptr, mud_ui_tab_44, { { "tabber", type<mud::Tabber>(),  }, { "name", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tabber", nullptr, mud_ui_tabber_45, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Tabber>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "row", nullptr, mud_ui_row_46, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "header", nullptr, mud_ui_header_47, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "div", nullptr, mud_ui_div_48, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "stack", nullptr, mud_ui_stack_49, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "sheet", nullptr, mud_ui_sheet_50, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "board", nullptr, mud_ui_board_51, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "layout", nullptr, mud_ui_layout_52, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "screen", nullptr, mud_ui_screen_53, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "decal", nullptr, mud_ui_decal_54, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "overlay", nullptr, mud_ui_overlay_55, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "title_header", nullptr, mud_ui_title_header_56, { { "parent", type<mud::Widget>(),  }, { "title", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dummy", nullptr, mud_ui_dummy_57, { { "parent", type<mud::Widget>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "popup", nullptr, mud_ui_popup_58, { { "parent", type<mud::Widget>(),  }, { "flags", type<mud::ui::PopupFlags>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "popup", nullptr, mud_ui_popup_59, { { "parent", type<mud::Widget>(),  }, { "size", type<mud::vec2>(),  }, { "flags", type<mud::ui::PopupFlags>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "popup_at", nullptr, mud_ui_popup_at_60, { { "parent", type<mud::Widget>(),  }, { "position", type<mud::vec2>(),  }, { "flags", type<mud::ui::PopupFlags>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "modal", nullptr, mud_ui_modal_61, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "modal", nullptr, mud_ui_modal_62, { { "parent", type<mud::Widget>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "auto_modal", nullptr, mud_ui_auto_modal_63, { { "parent", type<mud::Widget>(),  }, { "mode", type<uint32_t>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "auto_modal", nullptr, mud_ui_auto_modal_64, { { "parent", type<mud::Widget>(),  }, { "mode", type<uint32_t>(),  }, { "size", type<mud::vec2>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "context", nullptr, mud_ui_context_65, { { "parent", type<mud::Widget>(),  }, { "mode", type<uint32_t>(),  }, { "flags", type<mud::ui::PopupFlags>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "hoverbox", nullptr, mud_ui_hoverbox_66, { { "parent", type<mud::Widget>(),  }, { "delay", type<float>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "tooltip", nullptr, mud_ui_tooltip_67, { { "parent", type<mud::Widget>(),  }, { "position", type<mud::vec2>(),  }, { "content", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "cursor", nullptr, mud_ui_cursor_68, { { "parent", type<mud::Widget>(),  }, { "position", type<mud::vec2>(),  }, { "hovered", type<mud::Widget>(),  }, { "locked", type<bool>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "rectangle", nullptr, mud_ui_rectangle_69, { { "parent", type<mud::Widget>(),  }, { "rect", type<mud::vec4>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dockspace", nullptr, mud_ui_dockspace_70, { { "parent", type<mud::Widget>(),  }, { "docksystem", type<mud::Docksystem>(),  } }, { &type<mud::Dockspace>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dockbar", nullptr, mud_ui_dockbar_71, { { "parent", type<mud::Widget>(),  }, { "docksystem", type<mud::Docksystem>(),  } }, { &type<mud::Dockbar>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dockitem", nullptr, mud_ui_dockitem_72, { { "parent", type<mud::Widget>(),  }, { "docksystem", type<mud::Docksystem>(),  }, { "dock", type<mud::Dock>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "text_box", nullptr, mud_ui_text_box_73, { { "parent", type<mud::Widget>(),  }, { "style", type<mud::Style>(),  }, { "text", type<string>(),  }, { "editor", type<bool>(), Param::Default }, { "lines", type<size_t>(), Param::Default }, { "allowed_chars", type<string>(), Param::Default } }, { &type<mud::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "type_in", nullptr, mud_ui_type_in_74, { { "parent", type<mud::Widget>(),  }, { "text", type<string>(),  }, { "lines", type<size_t>(), Param::Default }, { "allowed_chars", type<string>(), Param::Default } }, { &type<mud::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "text_edit", nullptr, mud_ui_text_edit_75, { { "parent", type<mud::Widget>(),  }, { "text", type<string>(),  }, { "lines", type<size_t>(), Param::Default }, { "vocabulary", type<vector<string>>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "code_edit", nullptr, mud_ui_code_edit_76, { { "parent", type<mud::Widget>(),  }, { "text", type<string>(),  }, { "lines", type<size_t>(), Param::Default }, { "vocabulary", type<vector<string>>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::TextEdit>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "drag_float", nullptr, mud_ui_drag_float_77, { { "parent", type<mud::Widget>(),  }, { "value", type<float>(),  }, { "step", type<float>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "vec2_edit", nullptr, mud_ui_vec2_edit_78, { { "parent", type<mud::Widget>(),  }, { "vec", type<mud::vec2>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "vec3_edit", nullptr, mud_ui_vec3_edit_79, { { "parent", type<mud::Widget>(),  }, { "vec", type<mud::vec3>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "quat_edit", nullptr, mud_ui_quat_edit_80, { { "parent", type<mud::Widget>(),  }, { "quat", type<mud::quat>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_edit_hsl", nullptr, mud_ui_color_edit_hsl_81, { { "parent", type<mud::Widget>(),  }, { "colour", type<mud::Colour>(),  }, { "value", type<mud::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_display", nullptr, mud_ui_color_display_82, { { "parent", type<mud::Widget>(),  }, { "value", type<mud::Colour>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_edit", nullptr, mud_ui_color_edit_83, { { "parent", type<mud::Widget>(),  }, { "value", type<mud::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_edit_simple", nullptr, mud_ui_color_edit_simple_84, { { "parent", type<mud::Widget>(),  }, { "value", type<mud::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_toggle_edit", nullptr, mud_ui_color_toggle_edit_85, { { "parent", type<mud::Widget>(),  }, { "value", type<mud::Colour>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "curve_graph", nullptr, mud_ui_curve_graph_86, { { "parent", type<mud::Widget>(),  }, { "values", type<array<float>>(),  }, { "points", type<array<float>>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "curve_edit", nullptr, mud_ui_curve_edit_87, { { "parent", type<mud::Widget>(),  }, { "values", type<array<float>>(),  }, { "points", type<array<float>>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "flag_field", nullptr, mud_ui_flag_field_88, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<uint32_t>(),  }, { "shift", type<uint8_t>(),  }, { "reverse", type<bool>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "radio_field", nullptr, mud_ui_radio_field_89, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<array<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "dim", type<mud::Dim>(), Param::Default }, { "reverse", type<bool>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dropdown_field", nullptr, mud_ui_dropdown_field_90, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<array<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "reverse", type<bool>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "typedown_field", nullptr, mud_ui_typedown_field_91, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "choices", type<array<const char*>>(),  }, { "value", type<uint32_t>(),  }, { "reverse", type<bool>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_field", nullptr, mud_ui_color_field_92, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<mud::Colour>(),  }, { "reverse", type<bool>(), Param::Default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "color_display_field", nullptr, mud_ui_color_display_field_93, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable }, { "value", type<mud::Colour>(),  }, { "reverse", type<bool>(), Param::Default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "node_input", nullptr, mud_ui_node_input_94, { { "node", type<mud::Node>(),  }, { "name", type<const char*>(), Param::Nullable }, { "icon", type<const char*>(), Param::Flags(Param::Nullable|Param::Default) }, { "colour", type<mud::Colour>(), Param::Default }, { "active", type<bool>(), Param::Default }, { "connected", type<bool>(), Param::Default } }, { &type<mud::NodePlug>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "node_output", nullptr, mud_ui_node_output_95, { { "node", type<mud::Node>(),  }, { "name", type<const char*>(), Param::Nullable }, { "icon", type<const char*>(), Param::Flags(Param::Nullable|Param::Default) }, { "colour", type<mud::Colour>(), Param::Default }, { "active", type<bool>(), Param::Default }, { "connected", type<bool>(), Param::Default } }, { &type<mud::NodePlug>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "node", nullptr, mud_ui_node_96, { { "parent", type<mud::Canvas>(),  }, { "title", type<const char*>(), Param::Nullable }, { "position", type<mud::vec2>(),  }, { "order", type<int>(), Param::Default }, { "identity", type<mud::Ref>(), Param::Flags(Param::Nullable|Param::Default) } }, { &type<mud::Node>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "node_cable", nullptr, mud_ui_node_cable_97, { { "canvas", type<mud::Canvas>(),  }, { "plug_out", type<mud::NodePlug>(),  }, { "plug_in", type<mud::NodePlug>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "canvas", nullptr, mud_ui_canvas_98, { { "parent", type<mud::Widget>(),  }, { "num_nodes", type<size_t>(), Param::Default } }, { &type<mud::Canvas>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "scrollable", nullptr, mud_ui_scrollable_99, { { "parent", type<mud::Widget>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "sequence", nullptr, mud_ui_sequence_100, { { "parent", type<mud::Widget>(),  } }, { &type<mud::ui::Sequence>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "scroll_sequence", nullptr, mud_ui_scroll_sequence_101, { { "parent", type<mud::Widget>(),  } }, { &type<mud::ui::Sequence>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "multiselect_logic", nullptr, mud_ui_multiselect_logic_102, { { "element", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable }, { "selection", type<vector<mud::Ref>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "select_logic", nullptr, mud_ui_select_logic_103, { { "element", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable }, { "selection", type<mud::Ref>(), Param::Nullable } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "element", nullptr, mud_ui_element_104, { { "parent", type<mud::Widget>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "sequence_element", nullptr, mud_ui_sequence_element_105, { { "parent", type<mud::ui::Sequence>(),  }, { "object", type<mud::Ref>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "window", nullptr, mud_ui_window_106, { { "parent", type<mud::Widget>(),  }, { "title", type<const char*>(), Param::Nullable }, { "state", type<mud::WindowState>(), Param::Default } }, { &type<mud::Window>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dir_item", nullptr, mud_ui_dir_item_107, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_item", nullptr, mud_ui_file_item_108, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_list", nullptr, mud_ui_file_list_109, { { "parent", type<mud::Widget>(),  }, { "path", type<string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_browser", nullptr, mud_ui_file_browser_110, { { "parent", type<mud::Widget>(),  }, { "path", type<string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "dir_node", nullptr, mud_ui_dir_node_111, { { "parent", type<mud::Widget>(),  }, { "path", type<const char*>(), Param::Nullable }, { "name", type<const char*>(), Param::Nullable }, { "collapsed", type<bool>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_node", nullptr, mud_ui_file_node_112, { { "parent", type<mud::Widget>(),  }, { "name", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "file_tree", nullptr, mud_ui_file_tree_113, { { "parent", type<mud::Widget>(),  }, { "path", type<const char*>(), Param::Nullable } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "command_line", nullptr, mud_ui_command_line_114, { { "parent", type<mud::Widget>(),  }, { "text", type<string>(),  }, { "command", type<string>(),  } }, { &type<mud::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "console", nullptr, mud_ui_console_115, { { "parent", type<mud::Widget>(),  }, { "feed", type<string>(),  }, { "line", type<string>(),  }, { "command", type<string>(),  }, { "num_lines", type<size_t>(), Param::Default } }, { &type<mud::Widget>(), QualType::None } };
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
