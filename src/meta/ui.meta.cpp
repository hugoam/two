module;
#include <infra/Cpp20.h>
module two.ui.meta;

using namespace two;

void two_FlowAxis__to_string(void* val, string& str) { str = g_enu[type<two::FlowAxis>().m_id]->name(uint32_t((*static_cast<two::FlowAxis*>(val)))); }
void two_FlowAxis__to_value(const string& str, void* val) { (*static_cast<two::FlowAxis*>(val)) = two::FlowAxis(g_enu[type<two::FlowAxis>().m_id]->value(str.c_str())); }
void two_Pivot__to_string(void* val, string& str) { str = g_enu[type<two::Pivot>().m_id]->name(uint32_t((*static_cast<two::Pivot*>(val)))); }
void two_Pivot__to_value(const string& str, void* val) { (*static_cast<two::Pivot*>(val)) = two::Pivot(g_enu[type<two::Pivot>().m_id]->value(str.c_str())); }
void two_Align__to_string(void* val, string& str) { str = g_enu[type<two::Align>().m_id]->name(uint32_t((*static_cast<two::Align*>(val)))); }
void two_Align__to_value(const string& str, void* val) { (*static_cast<two::Align*>(val)) = two::Align(g_enu[type<two::Align>().m_id]->value(str.c_str())); }
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
void two_Space__default_construct(void* ref) { new(stl::placeholder(), ref) two::Space(); }
void two_Space__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Space((*static_cast<two::Space*>(other))); }
void two_v2_two_AutoLayout__default_construct(void* ref) { new(stl::placeholder(), ref) two::v2<two::AutoLayout>(); }
void two_v2_two_AutoLayout__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<two::AutoLayout>((*static_cast<two::v2<two::AutoLayout>*>(other))); }
void two_v2_two_AutoLayout__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::AutoLayout>( *static_cast<two::AutoLayout*>(args[0]) ); }
void two_v2_two_AutoLayout__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::AutoLayout>( *static_cast<two::AutoLayout*>(args[0]), *static_cast<two::AutoLayout*>(args[1]) ); }
void two_v2_two_Sizing__default_construct(void* ref) { new(stl::placeholder(), ref) two::v2<two::Sizing>(); }
void two_v2_two_Sizing__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<two::Sizing>((*static_cast<two::v2<two::Sizing>*>(other))); }
void two_v2_two_Sizing__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Sizing>( *static_cast<two::Sizing*>(args[0]) ); }
void two_v2_two_Sizing__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Sizing>( *static_cast<two::Sizing*>(args[0]), *static_cast<two::Sizing*>(args[1]) ); }
void two_v2_two_Align__default_construct(void* ref) { new(stl::placeholder(), ref) two::v2<two::Align>(); }
void two_v2_two_Align__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<two::Align>((*static_cast<two::v2<two::Align>*>(other))); }
void two_v2_two_Align__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Align>( *static_cast<two::Align*>(args[0]) ); }
void two_v2_two_Align__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Align>( *static_cast<two::Align*>(args[0]), *static_cast<two::Align*>(args[1]) ); }
void two_v2_two_Pivot__default_construct(void* ref) { new(stl::placeholder(), ref) two::v2<two::Pivot>(); }
void two_v2_two_Pivot__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<two::Pivot>((*static_cast<two::v2<two::Pivot>*>(other))); }
void two_v2_two_Pivot__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Pivot>( *static_cast<two::Pivot*>(args[0]) ); }
void two_v2_two_Pivot__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<two::Pivot>( *static_cast<two::Pivot*>(args[0]), *static_cast<two::Pivot*>(args[1]) ); }
void two_ImageSkin__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ImageSkin((*static_cast<two::ImageSkin*>(other))); }
void two_ImageSkin__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ImageSkin( *static_cast<two::Image*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]), *static_cast<int*>(args[3]), *static_cast<int*>(args[4]), *static_cast<int*>(args[5]), *static_cast<two::Axis*>(args[6]) ); }
void two_Shadow__default_construct(void* ref) { new(stl::placeholder(), ref) two::Shadow(); }
void two_Shadow__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Shadow((*static_cast<two::Shadow*>(other))); }
void two_Shadow__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Shadow( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<two::Colour*>(args[4]) ); }
void two_Paint__default_construct(void* ref) { new(stl::placeholder(), ref) two::Paint(); }
void two_Paint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Paint((*static_cast<two::Paint*>(other))); }
void two_TextPaint__default_construct(void* ref) { new(stl::placeholder(), ref) two::TextPaint(); }
void two_TextPaint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextPaint((*static_cast<two::TextPaint*>(other))); }
void two_Gradient__default_construct(void* ref) { new(stl::placeholder(), ref) two::Gradient(); }
void two_Gradient__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Gradient((*static_cast<two::Gradient*>(other))); }
void two_InkStyle__default_construct(void* ref) { new(stl::placeholder(), ref) two::InkStyle(); }
void two_InkStyle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::InkStyle((*static_cast<two::InkStyle*>(other))); }
void two_InkStyle__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::InkStyle( *static_cast<stl::string*>(args[0]) ); }
void two_Layout__default_construct(void* ref) { new(stl::placeholder(), ref) two::Layout(); }
void two_Layout__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Layout((*static_cast<two::Layout*>(other))); }
void two_Layout__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Layout( *static_cast<stl::string*>(args[0]) ); }
void two_Subskin__default_construct(void* ref) { new(stl::placeholder(), ref) two::Subskin(); }
void two_Subskin__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Subskin((*static_cast<two::Subskin*>(other))); }
void two_UiRect__default_construct(void* ref) { new(stl::placeholder(), ref) two::UiRect(); }
void two_UiRect__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::UiRect((*static_cast<two::UiRect*>(other))); }
void* two_Widget__get_frame(void* object) { return &(*static_cast<two::Widget*>(object)).frame(); }
void two_Widget_focused(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).focused(); }
void two_Widget_hovered(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).hovered(); }
void two_Widget_pressed(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).pressed(); }
void two_Widget_activated(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).activated(); }
void two_Widget_active(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).active(); }
void two_Widget_selected(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).selected(); }
void two_Widget_modal(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).modal(); }
void two_Widget_closed(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).closed(); }
void two_Widget_open(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Widget*>(object)).open(); }
void two_Widget_ui_window(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Widget*>(object)).ui_window(); }
void two_Widget_ui(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Widget*>(object)).ui(); }
void two_Widget_parent_modal(void* object, span<void*> args, void*& result) { UNUSED(args); result = &(*static_cast<two::Widget*>(object)).parent_modal(); }
void two_Widget_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).clear(); }
void two_Widget_toggle_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).toggle_state(*static_cast<two::WidgetState*>(args[0])); }
void two_Widget_disable_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).disable_state(*static_cast<two::WidgetState*>(args[0])); }
void two_Widget_set_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).set_state(*static_cast<two::WidgetState*>(args[0]), *static_cast<bool*>(args[1])); }
void two_Widget_enable_state(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).enable_state(*static_cast<two::WidgetState*>(args[0])); }
void two_Widget_set_open(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).set_open(*static_cast<bool*>(args[0])); }
void two_Widget_clear_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).clear_focus(); }
void two_Widget_take_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).take_focus(); }
void two_Widget_yield_focus(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).yield_focus(); }
void two_Widget_take_modal(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Widget*>(object)).take_modal(*static_cast<uint32_t*>(args[0])); }
void two_Widget_yield_modal(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Widget*>(object)).yield_modal(); }
void two_Widget_key_event(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::Widget*>(object)).key_event(*static_cast<two::Key*>(args[0]), *static_cast<two::EventType*>(args[1]), *static_cast<two::InputMod*>(args[2])); }
void two_Widget_key_stroke(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::Widget*>(object)).key_stroke(*static_cast<two::Key*>(args[0]), *static_cast<two::InputMod*>(args[1])); }
void two_Widget_char_stroke(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::Widget*>(object)).char_stroke(*static_cast<two::Key*>(args[0]), *static_cast<two::InputMod*>(args[1])); }
void two_Widget_mouse_event(void* object, span<void*> args, void*& result) { (*static_cast<two::MouseEvent*>(result)) = (*static_cast<two::Widget*>(object)).mouse_event(*static_cast<two::DeviceType*>(args[0]), *static_cast<two::EventType*>(args[1]), *static_cast<two::InputMod*>(args[2]), *static_cast<bool*>(args[3])); }
void two_WidgetHandle__default_construct(void* ref) { new(stl::placeholder(), ref) two::WidgetHandle(); }
void two_WidgetHandle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::WidgetHandle((*static_cast<two::WidgetHandle*>(other))); }
void* two_WidgetHandle__get_widget(void* object) { return &(*static_cast<two::WidgetHandle*>(object)).widget(); }
void two_TextCursor__default_construct(void* ref) { new(stl::placeholder(), ref) two::TextCursor(); }
void two_TextCursor__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextCursor((*static_cast<two::TextCursor*>(other))); }
void two_TextSelection__default_construct(void* ref) { new(stl::placeholder(), ref) two::TextSelection(); }
void two_TextSelection__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextSelection((*static_cast<two::TextSelection*>(other))); }
void two_TextMarker__default_construct(void* ref) { new(stl::placeholder(), ref) two::TextMarker(); }
void two_TextMarker__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextMarker((*static_cast<two::TextMarker*>(other))); }
void two_TextEditHandle__default_construct(void* ref) { new(stl::placeholder(), ref) two::TextEditHandle(); }
void two_TextEditHandle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TextEditHandle((*static_cast<two::TextEditHandle*>(other))); }
void* two_TextEditHandle__get_self(void* object) { return &(*static_cast<two::TextEditHandle*>(object)).self(); }
void* two_TextEditHandle__get_edit(void* object) { return &(*static_cast<two::TextEditHandle*>(object)).edit(); }
void two_NodePlugHandle__default_construct(void* ref) { new(stl::placeholder(), ref) two::NodePlugHandle(); }
void two_NodePlugHandle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::NodePlugHandle((*static_cast<two::NodePlugHandle*>(other))); }
void* two_NodePlugHandle__get_self(void* object) { return &(*static_cast<two::NodePlugHandle*>(object)).self(); }
void* two_NodePlugHandle__get_plug(void* object) { return &(*static_cast<two::NodePlugHandle*>(object)).plug(); }
void* two_Node__get_header(void* object) { return &(*static_cast<two::Node*>(object)).header(); }
void* two_Node__get_inputs(void* object) { return &(*static_cast<two::Node*>(object)).inputs(); }
void* two_Node__get_outputs(void* object) { return &(*static_cast<two::Node*>(object)).outputs(); }
void* two_Node__get_body(void* object) { return &(*static_cast<two::Node*>(object)).body(); }
void two_CanvasConnect__default_construct(void* ref) { new(stl::placeholder(), ref) two::CanvasConnect(); }
void two_CanvasConnect__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CanvasConnect((*static_cast<two::CanvasConnect*>(other))); }
void two_CanvasHandle__default_construct(void* ref) { new(stl::placeholder(), ref) two::CanvasHandle(); }
void two_CanvasHandle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CanvasHandle((*static_cast<two::CanvasHandle*>(other))); }
void* two_CanvasHandle__get_self(void* object) { return &(*static_cast<two::CanvasHandle*>(object)).self(); }
void* two_CanvasHandle__get_canvas(void* object) { return &(*static_cast<two::CanvasHandle*>(object)).canvas(); }
void two_NodeConnection__default_construct(void* ref) { new(stl::placeholder(), ref) two::NodeConnection(); }
void two_NodeConnection__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::NodeConnection((*static_cast<two::NodeConnection*>(other))); }
void two_Clipboard__default_construct(void* ref) { new(stl::placeholder(), ref) two::Clipboard(); }
void two_Clipboard__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Clipboard((*static_cast<two::Clipboard*>(other))); }
void* two_UiWindow__get_context(void* object) { return &(*static_cast<two::UiWindow*>(object)).m_context; }
void* two_UiWindow__get_vg(void* object) { return &(*static_cast<two::UiWindow*>(object)).m_vg; }
void two_UiWindow_reset_styles(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::UiWindow*>(object)).reset_styles(); }
void two_Dock__default_construct(void* ref) { new(stl::placeholder(), ref) two::Dock(); }
void two_Dock__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Dock((*static_cast<two::Dock*>(other))); }
void two_DockerHandle__default_construct(void* ref) { new(stl::placeholder(), ref) two::DockerHandle(); }
void two_DockerHandle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::DockerHandle((*static_cast<two::DockerHandle*>(other))); }
void* two_DockerHandle__get_self(void* object) { return &(*static_cast<two::DockerHandle*>(object)).self(); }
void* two_DockerHandle__get_docker(void* object) { return &(*static_cast<two::DockerHandle*>(object)).docker(); }
void two_DockspaceHandle__default_construct(void* ref) { new(stl::placeholder(), ref) two::DockspaceHandle(); }
void two_DockspaceHandle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::DockspaceHandle((*static_cast<two::DockspaceHandle*>(other))); }
void two_DockbarHandle__default_construct(void* ref) { new(stl::placeholder(), ref) two::DockbarHandle(); }
void two_DockbarHandle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::DockbarHandle((*static_cast<two::DockbarHandle*>(other))); }
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
void two_ui_widget_9(span<void*> args, void*& result) { result = &two::ui::widget(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Style*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<two::Axis*>(args[4]), *static_cast<two::v2<uint>*>(args[5])); }
void two_ui_item_10(span<void*> args, void*& result) { result = &two::ui::item(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Style*>(args[2]), static_cast<const char*>(args[3])); }
void two_ui_multi_item_11(span<void*> args, void*& result) { result = &two::ui::multi_item(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Style*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), static_cast<two::Style*>(args[4])); }
void two_ui_spanner_12(span<void*> args, void*& result) { result = &two::ui::spanner(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Style*>(args[2]), *static_cast<two::Axis*>(args[3]), *static_cast<float*>(args[4])); }
void two_ui_spacer_13(span<void*> args, void*& result) { result = &two::ui::spacer(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_separator_14(span<void*> args, void*& result) { result = &two::ui::separator(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_icon_15(span<void*> args, void*& result) { result = &two::ui::icon(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_label_16(span<void*> args, void*& result) { result = &two::ui::label(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_title_17(span<void*> args, void*& result) { result = &two::ui::title(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_message_18(span<void*> args, void*& result) { result = &two::ui::message(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_text_19(span<void*> args, void*& result) { result = &two::ui::text(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_bullet_20(span<void*> args, void*& result) { result = &two::ui::bullet(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_selectable_21(span<void*> args, void*& result) { result = &two::ui::selectable(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_button_22(span<void*> args, void*& result) { result = &two::ui::button(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_toggle_23(span<void*> args, void*& result) { result = &two::ui::toggle(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<bool*>(args[2]), static_cast<const char*>(args[3])); }
void two_ui_button_24(span<void*> args, void*& result) { result = &two::ui::button(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_toggle_25(span<void*> args, void*& result) { result = &two::ui::toggle(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<stl::string*>(args[3])); }
void two_ui_multi_button_26(span<void*> args, void*& result) { result = &two::ui::multi_button(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), static_cast<two::Style*>(args[3])); }
void two_ui_multi_toggle_27(span<void*> args, void*& result) { result = &two::ui::multi_toggle(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), static_cast<two::Style*>(args[4])); }
void two_ui_modal_button_28(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::modal_button(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Widget*>(args[2]), static_cast<const char*>(args[3]), *static_cast<uint32_t*>(args[4])); }
void two_ui_modal_multi_button_29(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::modal_multi_button(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Widget*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), *static_cast<uint32_t*>(args[4])); }
void two_ui_checkbox_30(span<void*> args, void*& result) { result = &two::ui::checkbox(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<bool*>(args[2])); }
void two_ui_fill_bar_31(span<void*> args, void*& result) { result = &two::ui::fill_bar(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::Axis*>(args[3])); }
void two_ui_image256_32(span<void*> args, void*& result) { result = &two::ui::image256(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<two::Image256*>(args[3])); }
void two_ui_image256_33(span<void*> args, void*& result) { result = &two::ui::image256(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<two::Image256*>(args[3]), *static_cast<two::vec2*>(args[4])); }
void two_ui_image256_34(span<void*> args, void*& result) { result = &two::ui::image256(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<two::Image256*>(args[3])); }
void two_ui_image256_35(span<void*> args, void*& result) { result = &two::ui::image256(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<two::Image256*>(args[3]), *static_cast<two::vec2*>(args[4])); }
void two_ui_radio_choice_36(span<void*> args, void*& result) { result = &two::ui::radio_choice(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<bool*>(args[3])); }
void two_ui_radio_button_37(span<void*> args, void*& result) { result = &two::ui::radio_button(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<uint32_t*>(args[4])); }
void two_ui_radio_switch_38(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::radio_switch(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<two::Axis*>(args[4])); }
void two_ui_popdown_39(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::popdown(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<two::vec2*>(args[4]), *static_cast<two::ui::PopupFlags*>(args[5])); }
void two_ui_dropdown_input_40(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::dropdown_input(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_typedown_input_41(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::typedown_input(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<uint32_t*>(args[3])); }
void two_ui_menu_choice_42(span<void*> args, void*& result) { result = &two::ui::menu_choice(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), static_cast<const char*>(args[3])); }
void two_ui_menu_option_43(span<void*> args, void*& result) { result = &two::ui::menu_option(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), static_cast<const char*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_menubar_44(span<void*> args, void*& result) { result = &two::ui::menubar(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_toolbutton_45(span<void*> args, void*& result) { result = &two::ui::toolbutton(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_tooldock_46(span<void*> args, void*& result) { result = &two::ui::tooldock(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_toolbar_47(span<void*> args, void*& result) { result = &two::ui::toolbar(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<bool*>(args[2])); }
void two_ui_columns_48(span<void*> args, void*& result) { result = &two::ui::columns(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<float>*>(args[2])); }
void two_ui_table_49(span<void*> args, void*& result) { result = &two::ui::table(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3])); }
void two_ui_table_row_50(span<void*> args, void*& result) { result = &two::ui::table_row(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_table_separator_51(span<void*> args, void*& result) { result = &two::ui::table_separator(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_tree_52(span<void*> args, void*& result) { result = &two::ui::tree(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_row_53(span<void*> args, void*& result) { result = &two::ui::row(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_header_54(span<void*> args, void*& result) { result = &two::ui::header(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_div_55(span<void*> args, void*& result) { result = &two::ui::div(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_stack_56(span<void*> args, void*& result) { result = &two::ui::stack(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_sheet_57(span<void*> args, void*& result) { result = &two::ui::sheet(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_board_58(span<void*> args, void*& result) { result = &two::ui::board(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_layout_59(span<void*> args, void*& result) { result = &two::ui::layout(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_indent_60(span<void*> args, void*& result) { result = &two::ui::indent(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_screen_61(span<void*> args, void*& result) { result = &two::ui::screen(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_decal_62(span<void*> args, void*& result) { result = &two::ui::decal(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_overlay_63(span<void*> args, void*& result) { result = &two::ui::overlay(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_title_header_64(span<void*> args, void*& result) { result = &two::ui::title_header(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_dummy_65(span<void*> args, void*& result) { result = &two::ui::dummy(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::vec2*>(args[2])); }
void two_ui_popup_66(span<void*> args, void*& result) { result = &two::ui::popup(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::ui::PopupFlags*>(args[2])); }
void two_ui_popup_at_67(span<void*> args, void*& result) { result = &two::ui::popup_at(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::vec2*>(args[2]), *static_cast<two::ui::PopupFlags*>(args[3])); }
void two_ui_modal_68(span<void*> args, void*& result) { result = &two::ui::modal(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_auto_modal_69(span<void*> args, void*& result) { result = &two::ui::auto_modal(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void two_ui_context_70(span<void*> args, void*& result) { result = two::ui::context(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<two::ui::PopupFlags*>(args[3])); }
void two_ui_hoverbox_71(span<void*> args, void*& result) { result = two::ui::hoverbox(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<float*>(args[2])); }
void two_ui_cursor_72(span<void*> args, void*& result) { result = &two::ui::cursor(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::vec2*>(args[2]), *static_cast<two::Widget*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_rectangle_73(span<void*> args, void*& result) { result = &two::ui::rectangle(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::vec4*>(args[2])); }
void two_ui_viewport_74(span<void*> args, void*& result) { result = &two::ui::viewport(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::vec4*>(args[2])); }
void two_ui_dockspace_75(span<void*> args, void*& result) { (*static_cast<two::DockspaceHandle*>(result)) = two::ui::dockspace(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Docksystem*>(args[2])); }
void two_ui_dockbar_76(span<void*> args, void*& result) { (*static_cast<two::DockbarHandle*>(result)) = two::ui::dockbar(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Docksystem*>(args[2])); }
void two_ui_dockitem_77(span<void*> args, void*& result) { result = two::ui::dockitem(*static_cast<two::Widget*>(args[0]), *static_cast<two::Docksystem*>(args[1]), static_cast<const char*>(args[2])); }
void two_ui_drag_float_78(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::drag_float(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3])); }
void two_ui_float2_input_79(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float2_input(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<two::StatDef<float>*>(args[4])); }
void two_ui_float3_input_80(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float3_input(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<two::StatDef<float>*>(args[4])); }
void two_ui_float4_input_81(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float4_input(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<const char*>*>(args[2]), *static_cast<stl::span<float>*>(args[3]), *static_cast<two::StatDef<float>*>(args[4])); }
void two_ui_float2_slider_82(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float2_slider(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), *static_cast<stl::span<float>*>(args[4]), *static_cast<two::StatDef<float>*>(args[5])); }
void two_ui_float3_slider_83(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float3_slider(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), *static_cast<stl::span<float>*>(args[4]), *static_cast<two::StatDef<float>*>(args[5])); }
void two_ui_float4_slider_84(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::float4_slider(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), *static_cast<stl::span<float>*>(args[4]), *static_cast<two::StatDef<float>*>(args[5])); }
void two_ui_vec2_edit_85(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::vec2_edit(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::vec2*>(args[2])); }
void two_ui_vec3_edit_86(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::vec3_edit(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::vec3*>(args[2])); }
void two_ui_quat_edit_87(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::quat_edit(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::quat*>(args[2])); }
void two_ui_color_display_88(span<void*> args, void*& result) { result = &two::ui::color_display(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Colour*>(args[2])); }
void two_ui_color_edit_89(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::color_edit(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Colour*>(args[2])); }
void two_ui_color_edit_simple_90(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::color_edit_simple(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Colour*>(args[2])); }
void two_ui_color_toggle_edit_91(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::color_toggle_edit(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Colour*>(args[2])); }
void two_ui_curve_graph_92(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::curve_graph(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<float>*>(args[2]), *static_cast<stl::span<float>*>(args[3])); }
void two_ui_curve_edit_93(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::curve_edit(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::span<float>*>(args[2]), *static_cast<stl::span<float>*>(args[3])); }
void two_ui_flag_field_94(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::flag_field(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<uint32_t*>(args[3]), *static_cast<uint8_t*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_radio_field_95(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::radio_field(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), *static_cast<uint32_t*>(args[4]), *static_cast<two::Axis*>(args[5]), *static_cast<bool*>(args[6])); }
void two_ui_dropdown_field_96(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::dropdown_field(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), *static_cast<uint32_t*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_typedown_field_97(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::typedown_field(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<stl::span<const char*>*>(args[3]), *static_cast<uint32_t*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_color_field_98(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::color_field(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<two::Colour*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_color_display_field_99(span<void*> args, void*& result) { UNUSED(result);  two::ui::color_display_field(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<two::Colour*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_input_bool_100(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<bool>(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<bool*>(args[2])); }
void two_ui_input_stl_string_101(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<stl::string>(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_input_int_102(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<int>(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<int*>(args[2]), *static_cast<two::StatDef<int>*>(args[3])); }
void two_ui_input_float_103(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::input<float>(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::StatDef<float>*>(args[3])); }
void two_ui_field_bool_104(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::field<bool>(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_field_stl_string_105(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::field<stl::string>(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<stl::string*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_field_int_106(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::field<int>(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<int*>(args[3]), *static_cast<two::StatDef<int>*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_field_float_107(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::field<float>(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), static_cast<const char*>(args[2]), *static_cast<float*>(args[3]), *static_cast<two::StatDef<float>*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_text_box_108(span<void*> args, void*& result) { (*static_cast<two::TextEditHandle*>(result)) = two::ui::text_box(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Style*>(args[2]), *static_cast<stl::string*>(args[3]), *static_cast<bool*>(args[4]), *static_cast<size_t*>(args[5]), *static_cast<stl::string*>(args[6])); }
void two_ui_type_in_109(span<void*> args, void*& result) { (*static_cast<two::TextEditHandle*>(result)) = two::ui::type_in(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<size_t*>(args[3]), *static_cast<stl::string*>(args[4])); }
void two_ui_text_edit_110(span<void*> args, void*& result) { (*static_cast<two::TextEditHandle*>(result)) = two::ui::text_edit(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<size_t*>(args[3]), static_cast<stl::vector<stl::string>*>(args[4])); }
void two_ui_code_edit_111(span<void*> args, void*& result) { (*static_cast<two::TextEditHandle*>(result)) = two::ui::code_edit(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<size_t*>(args[3]), static_cast<stl::vector<stl::string>*>(args[4])); }
void two_ui_node_input_112(span<void*> args, void*& result) { (*static_cast<two::NodePlugHandle*>(result)) = two::ui::node_input(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Node*>(args[1]), static_cast<const char*>(args[2]), static_cast<const char*>(args[3]), *static_cast<two::Colour*>(args[4]), *static_cast<bool*>(args[5]), *static_cast<bool*>(args[6])); }
void two_ui_node_output_113(span<void*> args, void*& result) { (*static_cast<two::NodePlugHandle*>(result)) = two::ui::node_output(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Node*>(args[1]), static_cast<const char*>(args[2]), static_cast<const char*>(args[3]), *static_cast<two::Colour*>(args[4]), *static_cast<bool*>(args[5]), *static_cast<bool*>(args[6])); }
void two_ui_node_114(span<void*> args, void*& result) { result = &two::ui::node(*static_cast<two::Canvas*>(args[0]), static_cast<const char*>(args[1]), *static_cast<two::vec2*>(args[2]), *static_cast<int*>(args[3]), *static_cast<two::Ref*>(args[4])); }
void two_ui_node_cable_115(span<void*> args, void*& result) { result = &two::ui::node_cable(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Canvas*>(args[1]), *static_cast<two::NodePlug*>(args[2]), *static_cast<two::NodePlug*>(args[3])); }
void two_ui_canvas_116(span<void*> args, void*& result) { (*static_cast<two::CanvasHandle*>(result)) = two::ui::canvas(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<size_t*>(args[2])); }
void two_ui_scrollable_117(span<void*> args, void*& result) { result = &two::ui::scrollable(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1])); }
void two_ui_multiselect_logic_118(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::multiselect_logic(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1]), *static_cast<stl::vector<two::Ref>*>(args[2])); }
void two_ui_select_logic_119(span<void*> args, void*& result) { (*static_cast<bool*>(result)) = two::ui::select_logic(*static_cast<two::Widget*>(args[0]), *static_cast<two::Ref*>(args[1]), *static_cast<two::Ref*>(args[2])); }
void two_ui_element_120(span<void*> args, void*& result) { result = &two::ui::element(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<two::Ref*>(args[2])); }
void two_ui_dir_item_121(span<void*> args, void*& result) { result = &two::ui::dir_item(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_file_item_122(span<void*> args, void*& result) { result = &two::ui::file_item(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_file_list_123(span<void*> args, void*& result) { result = &two::ui::file_list(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_file_browser_124(span<void*> args, void*& result) { result = &two::ui::file_browser(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_dir_node_125(span<void*> args, void*& result) { result = &two::ui::dir_node(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<stl::string*>(args[3]), *static_cast<bool*>(args[4])); }
void two_ui_file_node_126(span<void*> args, void*& result) { result = &two::ui::file_node(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_file_tree_127(span<void*> args, void*& result) { result = &two::ui::file_tree(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2])); }
void two_ui_command_line_128(span<void*> args, void*& result) { result = &two::ui::command_line(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<stl::string*>(args[3])); }
void two_ui_console_129(span<void*> args, void*& result) { result = &two::ui::console(*static_cast<two::NodeKey*>(args[0]), *static_cast<two::Widget*>(args[1]), *static_cast<stl::string*>(args[2]), *static_cast<stl::string*>(args[3]), *static_cast<stl::string*>(args[4]), *static_cast<size_t*>(args[5])); }

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
		static cstring ids[] = { "NOSTATE", "CREATED", "HOVERED", "PRESSED", "ACTIVATED", "ACTIVE", "SELECTED", "DISABLED", "DRAGGED", "FOCUSED", "CLOSED", "OPEN" };
		static uint32_t values[] = { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
		static two::WidgetState vars[] = { two::NOSTATE, two::CREATED, two::HOVERED, two::PRESSED, two::ACTIVATED, two::ACTIVE, two::SELECTED, two::DISABLED, two::DRAGGED, two::FOCUSED, two::CLOSED, two::OPEN};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11]};
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
		meta.m_empty_var = var(stl::span<const char*>());
		static Iterable iterable = { &type<const char*>(),
		                             stl_span_const_char___size,
		                             stl_span_const_char___at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::vector<two::Space>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Space>", sizeof(stl::vector<two::Space>), TypeClass::Sequence };
		static Class cls = { t };
		meta.m_empty_var = var(stl::vector<two::Space>());
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
		meta.m_empty_var = var(stl::vector<two::Subskin>());
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
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_Space__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Space__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, offsetof(two::Space, direction), type<two::FlowAxis>(), "direction", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Space, sizingLength), type<two::Sizing>(), "sizingLength", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Space, sizingDepth), type<two::Sizing>(), "sizingDepth", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::Space());
	}
	// two::v2<two::AutoLayout>
	{
		Type& t = type<two::v2<two::AutoLayout>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<two::AutoLayout>", sizeof(two::v2<two::AutoLayout>), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_v2_two_AutoLayout__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_two_AutoLayout__copy_construct }
		};
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_two_AutoLayout__construct_0, { { "v", type<two::AutoLayout>(),  } } },
			{ t, two_v2_two_AutoLayout__construct_1, { { "x", type<two::AutoLayout>(),  }, { "y", type<two::AutoLayout>(),  } } }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<two::AutoLayout>, x), type<two::AutoLayout>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<two::AutoLayout>, y), type<two::AutoLayout>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, constructors, members, {}, {}, };
		meta.m_empty_var = var(two::v2<two::AutoLayout>());
	}
	// two::v2<two::Sizing>
	{
		Type& t = type<two::v2<two::Sizing>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<two::Sizing>", sizeof(two::v2<two::Sizing>), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_v2_two_Sizing__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_two_Sizing__copy_construct }
		};
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_two_Sizing__construct_0, { { "v", type<two::Sizing>(),  } } },
			{ t, two_v2_two_Sizing__construct_1, { { "x", type<two::Sizing>(),  }, { "y", type<two::Sizing>(),  } } }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<two::Sizing>, x), type<two::Sizing>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<two::Sizing>, y), type<two::Sizing>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, constructors, members, {}, {}, };
		meta.m_empty_var = var(two::v2<two::Sizing>());
	}
	// two::v2<two::Align>
	{
		Type& t = type<two::v2<two::Align>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<two::Align>", sizeof(two::v2<two::Align>), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_v2_two_Align__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_two_Align__copy_construct }
		};
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_two_Align__construct_0, { { "v", type<two::Align>(),  } } },
			{ t, two_v2_two_Align__construct_1, { { "x", type<two::Align>(),  }, { "y", type<two::Align>(),  } } }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<two::Align>, x), type<two::Align>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<two::Align>, y), type<two::Align>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, constructors, members, {}, {}, };
		meta.m_empty_var = var(two::v2<two::Align>());
	}
	// two::v2<two::Pivot>
	{
		Type& t = type<two::v2<two::Pivot>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<two::Pivot>", sizeof(two::v2<two::Pivot>), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_v2_two_Pivot__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_two_Pivot__copy_construct }
		};
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_two_Pivot__construct_0, { { "v", type<two::Pivot>(),  } } },
			{ t, two_v2_two_Pivot__construct_1, { { "x", type<two::Pivot>(),  }, { "y", type<two::Pivot>(),  } } }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<two::Pivot>, x), type<two::Pivot>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<two::Pivot>, y), type<two::Pivot>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, constructors, members, {}, {}, };
		meta.m_empty_var = var(two::v2<two::Pivot>());
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
		static two::Axis d_stretch_default = Axis::None;
		static int construct_0_margin_default = 0;
		static two::Axis construct_0_stretch_default = Axis::None;
		// default constructor
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ImageSkin__copy_construct }
		};
		// constructors
		static Constructor constructors[] = {
			{ t, two_ImageSkin__construct_0, { { "image", type<two::Image>(), Param::Reference }, { "left", type<int>(),  }, { "top", type<int>(),  }, { "right", type<int>(),  }, { "bottom", type<int>(),  }, { "margin", type<int>(), Param::Default, &construct_0_margin_default }, { "stretch", type<two::Axis>(), Param::Default, &construct_0_stretch_default } } }
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
		static Class cls = { t, {}, {}, {}, copy_constructor, constructors, members, {}, {}, };
	}
	// two::Shadow
	{
		Type& t = type<two::Shadow>();
		static Meta meta = { t, &namspc({ "two" }), "Shadow", sizeof(two::Shadow), TypeClass::Struct };
		// bases
		// defaults
		static two::Colour construct_0_colour_default = Colour::AlphaBlack;
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_Shadow__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Shadow__copy_construct }
		};
		// constructors
		static Constructor constructors[] = {
			{ t, two_Shadow__construct_0, { { "xpos", type<float>(),  }, { "ypos", type<float>(),  }, { "blur", type<float>(),  }, { "spread", type<float>(),  }, { "colour", type<two::Colour>(), Param::Default, &construct_0_colour_default } } }
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
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, constructors, members, {}, {}, };
		meta.m_empty_var = var(two::Shadow());
	}
	// two::Paint
	{
		Type& t = type<two::Paint>();
		static Meta meta = { t, &namspc({ "two" }), "Paint", sizeof(two::Paint), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_Paint__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Paint__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, offsetof(two::Paint, m_fill_colour), type<two::Colour>(), "fill_colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Paint, m_stroke_colour), type<two::Colour>(), "stroke_colour", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Paint, m_stroke_width), type<float>(), "stroke_width", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::Paint());
	}
	// two::TextPaint
	{
		Type& t = type<two::TextPaint>();
		static Meta meta = { t, &namspc({ "two" }), "TextPaint", sizeof(two::TextPaint), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_TextPaint__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextPaint__copy_construct }
		};
		// constructors
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
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::TextPaint());
	}
	// two::Gradient
	{
		Type& t = type<two::Gradient>();
		static Meta meta = { t, &namspc({ "two" }), "Gradient", sizeof(two::Gradient), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_Gradient__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Gradient__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, offsetof(two::Gradient, m_start), type<two::Colour>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Gradient, m_end), type<two::Colour>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::Gradient());
	}
	// two::InkStyle
	{
		Type& t = type<two::InkStyle>();
		static Meta meta = { t, &namspc({ "two" }), "InkStyle", sizeof(two::InkStyle), TypeClass::Struct };
		// bases
		// defaults
		static stl::string name_default = "";
		static bool empty_default = true;
		static two::Colour background_colour_default = Colour::None;
		static two::Colour border_colour_default = Colour::None;
		static two::Colour image_colour_default = Colour::None;
		static two::Colour text_colour_default = Colour::None;
		static stl::string text_font_default = "dejavu";
		static float text_size_default = 13.f;
		static bool text_break_default = false;
		static bool text_wrap_default = false;
		static bool weak_corners_default = false;
		static two::v2<two::Align> align_default = {Align::Left,Align::Left};
		static two::Axis linear_gradient_dim_default = Axis::Y;
		static two::v2<bool> stretch_default = {false,false};
		static two::Image* image_default = nullptr;
		static two::Image* overlay_default = nullptr;
		static two::Image* tile_default = nullptr;
		static two::Style* hover_cursor_default = nullptr;
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_InkStyle__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_InkStyle__copy_construct }
		};
		// constructors
		static Constructor constructors[] = {
			{ t, two_InkStyle__construct_0, { { "name", type<stl::string>(),  } } }
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
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, constructors, members, {}, {}, };
		meta.m_empty_var = var(two::InkStyle());
	}
	// two::Layout
	{
		Type& t = type<two::Layout>();
		static Meta meta = { t, &namspc({ "two" }), "Layout", sizeof(two::Layout), TypeClass::Struct };
		// bases
		// defaults
		static stl::string name_default = "";
		static two::v2<two::AutoLayout> layout_default = {AutoLayout::Layout,AutoLayout::Layout};
		static two::LayoutFlow flow_default = LayoutFlow::Flow;
		static two::Space space_default = Preset::Sheet;
		static two::Clip clipping_default = Clip::None;
		static two::Opacity opacity_default = Opacity::Clear;
		static two::v2<two::Align> align_default = {Align::Left,Align::Left};
		static two::v2<two::Pivot> pivot_default = {Pivot::Forward,Pivot::Forward};
		static int zorder_default = 0;
		static bool no_grid_default = false;
		static size_t updated_default = 0;
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_Layout__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Layout__copy_construct }
		};
		// constructors
		static Constructor constructors[] = {
			{ t, two_Layout__construct_0, { { "name", type<stl::string>(),  } } }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Layout, m_name), type<stl::string>(), "name", &name_default, Member::Value, nullptr },
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
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, constructors, members, {}, {}, };
		meta.m_empty_var = var(two::Layout());
	}
	// two::Subskin
	{
		Type& t = type<two::Subskin>();
		static Meta meta = { t, &namspc({ "two" }), "Subskin", sizeof(two::Subskin), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_Subskin__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Subskin__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, offsetof(two::Subskin, skin), type<two::InkStyle>(), "skin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Subskin, state), type<two::WidgetState>(), "state", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::Subskin());
	}
	// two::Style
	{
		Type& t = type<two::Style>();
		static Meta meta = { t, &namspc({ "two" }), "Style", sizeof(two::Style), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
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
		static Class cls = { t, {}, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::UiRect
	{
		Type& t = type<two::UiRect>();
		static Meta meta = { t, &namspc({ "two" }), "UiRect", sizeof(two::UiRect), TypeClass::Struct };
		// bases
		// defaults
		static float scale_default = 1.f;
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_UiRect__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_UiRect__copy_construct }
		};
		// constructors
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
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::UiRect());
	}
	// two::Frame
	{
		Type& t = type<two::Frame>();
		static Meta meta = { t, &namspc({ "two" }), "Frame", sizeof(two::Frame), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::UiRect>() };
		static size_t bases_offsets[] = { base_offset<two::Frame, two::UiRect>() };
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, {}, };
	}
	// two::Layer
	{
		Type& t = type<two::Layer>();
		static Meta meta = { t, &namspc({ "two" }), "Layer", sizeof(two::Layer), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Widget
	{
		Type& t = type<two::Widget>();
		static Meta meta = { t, &namspc({ "two" }), "Widget", sizeof(two::Widget), TypeClass::Object };
		// bases
		// defaults
		static two::WidgetState state_default = CREATED;
		static uint32_t switch_default = 0;
		static two::InputMod key_event_0_modifier_default = InputMod::Any;
		static two::InputMod key_stroke_0_modifier_default = InputMod::Any;
		static two::InputMod char_stroke_0_modifier_default = InputMod::Any;
		static two::InputMod mouse_event_0_modifier_default = InputMod::None;
		static bool mouse_event_0_consume_default = true;
		// default constructor
		// copy constructor
		// constructors
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Frame>(), "frame", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Widget__get_frame },
			{ t, offsetof(two::Widget, m_state), type<two::WidgetState>(), "state", &state_default, Member::Value, nullptr },
			{ t, offsetof(two::Widget, m_switch), type<uint32_t>(), "switch", &switch_default, Member::Value, nullptr }
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
			{ t, "open", Address(), two_Widget_open, {}, { &type<bool>(), QualType::None } },
			{ t, "ui_window", Address(), two_Widget_ui_window, {}, { &type<two::UiWindow>(), QualType::None } },
			{ t, "ui", Address(), two_Widget_ui, {}, { &type<two::Ui>(), QualType::None } },
			{ t, "parent_modal", Address(), two_Widget_parent_modal, {}, { &type<two::Widget>(), QualType::None } },
			{ t, "clear", Address(), two_Widget_clear, {}, g_qvoid },
			{ t, "toggle_state", Address(), two_Widget_toggle_state, { { "state", type<two::WidgetState>(),  } }, g_qvoid },
			{ t, "disable_state", Address(), two_Widget_disable_state, { { "state", type<two::WidgetState>(),  } }, g_qvoid },
			{ t, "set_state", Address(), two_Widget_set_state, { { "state", type<two::WidgetState>(),  }, { "enabled", type<bool>(),  } }, g_qvoid },
			{ t, "enable_state", Address(), two_Widget_enable_state, { { "state", type<two::WidgetState>(),  } }, g_qvoid },
			{ t, "set_open", Address(), two_Widget_set_open, { { "open", type<bool>(),  } }, g_qvoid },
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
		static Class cls = { t, {}, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::WidgetHandle
	{
		Type& t = type<two::WidgetHandle>();
		static Meta meta = { t, &namspc({ "two" }), "WidgetHandle", sizeof(two::WidgetHandle), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_WidgetHandle__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_WidgetHandle__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Widget>(), "widget", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_WidgetHandle__get_widget }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::WidgetHandle());
	}
	// two::TextCursor
	{
		Type& t = type<two::TextCursor>();
		static Meta meta = { t, &namspc({ "two" }), "TextCursor", sizeof(two::TextCursor), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_TextCursor__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextCursor__copy_construct }
		};
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, {}, {}, {}, };
		meta.m_empty_var = var(two::TextCursor());
	}
	// two::TextSelection
	{
		Type& t = type<two::TextSelection>();
		static Meta meta = { t, &namspc({ "two" }), "TextSelection", sizeof(two::TextSelection), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_TextSelection__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextSelection__copy_construct }
		};
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, {}, {}, {}, };
		meta.m_empty_var = var(two::TextSelection());
	}
	// two::TextMarker
	{
		Type& t = type<two::TextMarker>();
		static Meta meta = { t, &namspc({ "two" }), "TextMarker", sizeof(two::TextMarker), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_TextMarker__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextMarker__copy_construct }
		};
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, {}, {}, {}, };
		meta.m_empty_var = var(two::TextMarker());
	}
	// two::Text
	{
		Type& t = type<two::Text>();
		static Meta meta = { t, &namspc({ "two" }), "Text", sizeof(two::Text), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::TextEdit
	{
		Type& t = type<two::TextEdit>();
		static Meta meta = { t, &namspc({ "two" }), "TextEdit", sizeof(two::TextEdit), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::TextEditHandle
	{
		Type& t = type<two::TextEditHandle>();
		static Meta meta = { t, &namspc({ "two" }), "TextEditHandle", sizeof(two::TextEditHandle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::WidgetHandle>() };
		static size_t bases_offsets[] = { base_offset<two::TextEditHandle, two::WidgetHandle>() };
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_TextEditHandle__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TextEditHandle__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Widget>(), "self", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_TextEditHandle__get_self },
			{ t, SIZE_MAX, type<two::TextEdit>(), "edit", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_TextEditHandle__get_edit }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::TextEditHandle());
	}
	// two::NodePlug
	{
		Type& t = type<two::NodePlug>();
		static Meta meta = { t, &namspc({ "two" }), "NodePlug", sizeof(two::NodePlug), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::NodePlugHandle
	{
		Type& t = type<two::NodePlugHandle>();
		static Meta meta = { t, &namspc({ "two" }), "NodePlugHandle", sizeof(two::NodePlugHandle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::WidgetHandle>() };
		static size_t bases_offsets[] = { base_offset<two::NodePlugHandle, two::WidgetHandle>() };
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_NodePlugHandle__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_NodePlugHandle__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Widget>(), "self", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_NodePlugHandle__get_self },
			{ t, SIZE_MAX, type<two::NodePlug>(), "plug", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_NodePlugHandle__get_plug }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::NodePlugHandle());
	}
	// two::Node
	{
		Type& t = type<two::Node>();
		static Meta meta = { t, &namspc({ "two" }), "Node", sizeof(two::Node), TypeClass::Object };
		// bases
		// defaults
		static int order_default = 0;
		// default constructor
		// copy constructor
		// constructors
		// members
		static Member members[] = {
			{ t, offsetof(two::Node, m_order), type<int>(), "order", &order_default, Member::Value, nullptr },
			{ t, SIZE_MAX, type<two::Widget>(), "header", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Node__get_header },
			{ t, SIZE_MAX, type<two::Widget>(), "inputs", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Node__get_inputs },
			{ t, SIZE_MAX, type<two::Widget>(), "outputs", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Node__get_outputs },
			{ t, SIZE_MAX, type<two::Widget>(), "body", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Node__get_body }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::CanvasConnect
	{
		Type& t = type<two::CanvasConnect>();
		static Meta meta = { t, &namspc({ "two" }), "CanvasConnect", sizeof(two::CanvasConnect), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_CanvasConnect__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CanvasConnect__copy_construct }
		};
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, {}, {}, {}, };
		meta.m_empty_var = var(two::CanvasConnect());
	}
	// two::Canvas
	{
		Type& t = type<two::Canvas>();
		static Meta meta = { t, &namspc({ "two" }), "Canvas", sizeof(two::Canvas), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::CanvasHandle
	{
		Type& t = type<two::CanvasHandle>();
		static Meta meta = { t, &namspc({ "two" }), "CanvasHandle", sizeof(two::CanvasHandle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::WidgetHandle>() };
		static size_t bases_offsets[] = { base_offset<two::CanvasHandle, two::WidgetHandle>() };
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_CanvasHandle__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CanvasHandle__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Widget>(), "self", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_CanvasHandle__get_self },
			{ t, SIZE_MAX, type<two::Canvas>(), "canvas", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_CanvasHandle__get_canvas }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::CanvasHandle());
	}
	// two::NodeConnection
	{
		Type& t = type<two::NodeConnection>();
		static Meta meta = { t, &namspc({ "two" }), "NodeConnection", sizeof(two::NodeConnection), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_NodeConnection__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_NodeConnection__copy_construct }
		};
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, {}, {}, {}, };
		meta.m_empty_var = var(two::NodeConnection());
	}
	// two::Vg
	{
		Type& t = type<two::Vg>();
		static Meta meta = { t, &namspc({ "two" }), "Vg", sizeof(two::Vg), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
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
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_Clipboard__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Clipboard__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, offsetof(two::Clipboard, m_text), type<stl::string>(), "text", &text_default, Member::Value, nullptr },
			{ t, offsetof(two::Clipboard, m_line_mode), type<bool>(), "line_mode", &line_mode_default, Member::Value, nullptr },
			{ t, offsetof(two::Clipboard, m_pasted), type<stl::vector<stl::string>>(), "pasted", &pasted_default, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::Clipboard());
	}
	// two::UiWindow
	{
		Type& t = type<two::UiWindow>();
		static Meta meta = { t, &namspc({ "two" }), "UiWindow", sizeof(two::UiWindow), TypeClass::Object };
		// bases
		// defaults
		static bool shutdown_default = false;
		// default constructor
		// copy constructor
		// constructors
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
		static Class cls = { t, {}, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::User
	{
		Type& t = type<two::User>();
		static Meta meta = { t, &namspc({ "two" }), "User", sizeof(two::User), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Dock
	{
		Type& t = type<two::Dock>();
		static Meta meta = { t, &namspc({ "two" }), "Dock", sizeof(two::Dock), TypeClass::Struct };
		// bases
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_Dock__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Dock__copy_construct }
		};
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, {}, {}, {}, };
		meta.m_empty_var = var(two::Dock());
	}
	// two::DockerHandle
	{
		Type& t = type<two::DockerHandle>();
		static Meta meta = { t, &namspc({ "two" }), "DockerHandle", sizeof(two::DockerHandle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::WidgetHandle>() };
		static size_t bases_offsets[] = { base_offset<two::DockerHandle, two::WidgetHandle>() };
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_DockerHandle__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_DockerHandle__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Widget>(), "self", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_DockerHandle__get_self },
			{ t, SIZE_MAX, type<two::Docker>(), "docker", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_DockerHandle__get_docker }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::DockerHandle());
	}
	// two::Docksystem
	{
		Type& t = type<two::Docksystem>();
		static Meta meta = { t, &namspc({ "two" }), "Docksystem", sizeof(two::Docksystem), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Docker
	{
		Type& t = type<two::Docker>();
		static Meta meta = { t, &namspc({ "two" }), "Docker", sizeof(two::Docker), TypeClass::Object };
		// bases
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Dockspace
	{
		Type& t = type<two::Dockspace>();
		static Meta meta = { t, &namspc({ "two" }), "Dockspace", sizeof(two::Dockspace), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Docker>() };
		static size_t bases_offsets[] = { base_offset<two::Dockspace, two::Docker>() };
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, {}, };
	}
	// two::Dockbar
	{
		Type& t = type<two::Dockbar>();
		static Meta meta = { t, &namspc({ "two" }), "Dockbar", sizeof(two::Dockbar), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Docker>() };
		static size_t bases_offsets[] = { base_offset<two::Dockbar, two::Docker>() };
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, {}, };
	}
	// two::DockspaceHandle
	{
		Type& t = type<two::DockspaceHandle>();
		static Meta meta = { t, &namspc({ "two" }), "DockspaceHandle", sizeof(two::DockspaceHandle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::DockerHandle>() };
		static size_t bases_offsets[] = { base_offset<two::DockspaceHandle, two::DockerHandle>() };
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_DockspaceHandle__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_DockspaceHandle__copy_construct }
		};
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, default_constructor, copy_constructor, {}, {}, {}, {}, };
		meta.m_empty_var = var(two::DockspaceHandle());
	}
	// two::DockbarHandle
	{
		Type& t = type<two::DockbarHandle>();
		static Meta meta = { t, &namspc({ "two" }), "DockbarHandle", sizeof(two::DockbarHandle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::DockerHandle>() };
		static size_t bases_offsets[] = { base_offset<two::DockbarHandle, two::DockerHandle>() };
		// defaults
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_DockbarHandle__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_DockbarHandle__copy_construct }
		};
		// constructors
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, default_constructor, copy_constructor, {}, {}, {}, {}, };
		meta.m_empty_var = var(two::DockbarHandle());
	}
	// two::Ui
	{
		Type& t = type<two::Ui>();
		static Meta meta = { t, &namspc({ "two" }), "Ui", sizeof(two::Ui), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Ui, two::Widget>() };
		// defaults
		// default constructor
		// copy constructor
		// constructors
		// members
		// methods
		static Method methods[] = {
			{ t, "begin", Address(), two_Ui_begin, {}, { &type<two::Widget>(), QualType::None } },
			{ t, "reset_styles", Address(), two_Ui_reset_styles, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, methods, {}, };
	}
	
	{
		Type& t = type<uint16_t>();
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
		m.m_types.push_back(&type<two::Layer>());
		m.m_types.push_back(&type<two::Widget>());
		m.m_types.push_back(&type<two::WidgetHandle>());
		m.m_types.push_back(&type<two::TextCursor>());
		m.m_types.push_back(&type<two::TextSelection>());
		m.m_types.push_back(&type<two::PaletteIndex>());
		m.m_types.push_back(&type<two::ColourPalette>());
		m.m_types.push_back(&type<two::TextMarker>());
		m.m_types.push_back(&type<two::Text>());
		m.m_types.push_back(&type<two::TextEdit>());
		m.m_types.push_back(&type<two::TextEditHandle>());
		m.m_types.push_back(&type<two::NodePlug>());
		m.m_types.push_back(&type<two::NodePlugHandle>());
		m.m_types.push_back(&type<two::Node>());
		m.m_types.push_back(&type<two::CanvasConnect>());
		m.m_types.push_back(&type<two::Canvas>());
		m.m_types.push_back(&type<two::CanvasHandle>());
		m.m_types.push_back(&type<two::NodeConnection>());
		m.m_types.push_back(&type<two::WindowState>());
		m.m_types.push_back(&type<two::Vg>());
		m.m_types.push_back(&type<two::Clipboard>());
		m.m_types.push_back(&type<two::UiWindow>());
		m.m_types.push_back(&type<two::User>());
		m.m_types.push_back(&type<two::Dock>());
		m.m_types.push_back(&type<two::DockerHandle>());
		m.m_types.push_back(&type<two::Docksystem>());
		m.m_types.push_back(&type<two::Docker>());
		m.m_types.push_back(&type<two::Dockspace>());
		m.m_types.push_back(&type<two::Dockbar>());
		m.m_types.push_back(&type<two::DockspaceHandle>());
		m.m_types.push_back(&type<two::DockbarHandle>());
		m.m_types.push_back(&type<two::Ui>());
		{
			static Function f = { &namspc({ "two" }), "layout_minimal", funcptr<void(*)(two::UiWindow&)>(two::layout_minimal), two_layout_minimal_0, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_minimal", funcptr<void(*)(two::UiWindow&)>(two::style_minimal), two_style_minimal_1, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_vector", funcptr<void(*)(two::UiWindow&)>(two::style_vector), two_style_vector_2, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_blendish", funcptr<void(*)(two::UiWindow&)>(two::style_blendish), two_style_blendish_3, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_blendish_light", funcptr<void(*)(two::UiWindow&)>(two::style_blendish_light), two_style_blendish_light_4, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_blendish_dark", funcptr<void(*)(two::UiWindow&)>(two::style_blendish_dark), two_style_blendish_dark_5, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_imgui_dark", funcptr<void(*)(two::UiWindow&)>(two::style_imgui_dark), two_style_imgui_dark_6, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_imgui_light", funcptr<void(*)(two::UiWindow&)>(two::style_imgui_light), two_style_imgui_light_7, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "style_imgui_classic", funcptr<void(*)(two::UiWindow&)>(two::style_imgui_classic), two_style_imgui_classic_8, { { "ui_window", type<two::UiWindow>(), Param::Reference } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static bool open_default = false;
			static two::Axis length_default = Axis::None;
			static two::v2<uint> index_default = {0,0};
			static Function f = { &namspc({ "two", "ui" }), "widget", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, two::Style&, bool, two::Axis, two::v2<uint>)>(two::ui::widget), two_ui_widget_9, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "style", type<two::Style>(), Param::Reference }, { "open", type<bool>(), Param::Default, &open_default }, { "length", type<two::Axis>(), Param::Default, &length_default }, { "index", type<two::v2<uint>>(), Param::Default, &index_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "item", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, two::Style&, const char*)>(two::ui::item), two_ui_item_10, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "style", type<two::Style>(), Param::Reference }, { "content", type<const char*>(), Param::Default, (void*)content_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "multi_item", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, two::Style&, stl::span<const char*>, two::Style*)>(two::ui::multi_item), two_ui_multi_item_11, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "style", type<two::Style>(), Param::Reference }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<two::Style>(), Param::Flags(Param::Nullable|Param::Default), (void*)element_style_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "spanner", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, two::Style&, two::Axis, float)>(two::ui::spanner), two_ui_spanner_12, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "style", type<two::Style>(), Param::Reference }, { "dim", type<two::Axis>(),  }, { "span", type<float>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "spacer", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::spacer), two_ui_spacer_13, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "separator", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::separator), two_ui_separator_14, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "icon", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::icon), two_ui_icon_15, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "image", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "label", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::label), two_ui_label_16, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "title", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::title), two_ui_title_17, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "message", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::message), two_ui_message_18, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "text", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::text), two_ui_text_19, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "bullet", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::bullet), two_ui_bullet_20, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "selectable", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*, bool&)>(two::ui::selectable), two_ui_selectable_21, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  }, { "selected", type<bool>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "button", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::button), two_ui_button_22, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "content", type<const char*>(), Param::Default, (void*)content_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* content_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "toggle", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, bool&, const char*)>(two::ui::toggle), two_ui_toggle_23, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "on", type<bool>(), Param::Reference }, { "content", type<const char*>(), Param::Default, (void*)content_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "button", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const stl::string&)>(two::ui::button), two_ui_button_24, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "content", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "toggle", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, bool&, const stl::string&)>(two::ui::toggle), two_ui_toggle_25, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "on", type<bool>(), Param::Reference }, { "content", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "multi_button", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, stl::span<const char*>, two::Style*)>(two::ui::multi_button), two_ui_multi_button_26, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<two::Style>(), Param::Flags(Param::Nullable|Param::Default), (void*)element_style_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Style* element_style_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "multi_toggle", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, bool&, stl::span<const char*>, two::Style*)>(two::ui::multi_toggle), two_ui_multi_toggle_27, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "on", type<bool>(), Param::Reference }, { "elements", type<stl::span<const char*>>(),  }, { "element_style", type<two::Style>(), Param::Flags(Param::Nullable|Param::Default), (void*)element_style_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "modal_button", funcptr<bool(*)(two::NodeKey, two::Widget&, two::Widget&, const char*, uint32_t)>(two::ui::modal_button), two_ui_modal_button_28, { { "id", type<two::NodeKey>(),  }, { "screen", type<two::Widget>(), Param::Reference }, { "parent", type<two::Widget>(), Param::Reference }, { "content", type<const char*>(),  }, { "mode", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "modal_multi_button", funcptr<bool(*)(two::NodeKey, two::Widget&, two::Widget&, stl::span<const char*>, uint32_t)>(two::ui::modal_multi_button), two_ui_modal_multi_button_29, { { "id", type<two::NodeKey>(),  }, { "screen", type<two::Widget>(), Param::Reference }, { "parent", type<two::Widget>(), Param::Reference }, { "elements", type<stl::span<const char*>>(),  }, { "mode", type<uint32_t>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "checkbox", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, bool&)>(two::ui::checkbox), two_ui_checkbox_30, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "on", type<bool>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Axis dim_default = Axis::X;
			static Function f = { &namspc({ "two", "ui" }), "fill_bar", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, float, two::Axis)>(two::ui::fill_bar), two_ui_fill_bar_31, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "percentage", type<float>(),  }, { "dim", type<two::Axis>(), Param::Default, &dim_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "image256", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*, const two::Image256&)>(two::ui::image256), two_ui_image256_32, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "source", type<two::Image256>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "image256", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*, const two::Image256&, const two::vec2&)>(two::ui::image256), two_ui_image256_33, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "source", type<two::Image256>(),  }, { "size", type<two::vec2>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "image256", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const stl::string&, const two::Image256&)>(two::ui::image256), two_ui_image256_34, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<stl::string>(),  }, { "source", type<two::Image256>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "image256", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const stl::string&, const two::Image256&, const two::vec2&)>(two::ui::image256), two_ui_image256_35, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<stl::string>(),  }, { "source", type<two::Image256>(),  }, { "size", type<two::vec2>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "radio_choice", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*, bool)>(two::ui::radio_choice), two_ui_radio_choice_36, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  }, { "active", type<bool>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "radio_button", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*, uint32_t&, uint32_t)>(two::ui::radio_button), two_ui_radio_button_37, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  }, { "value", type<uint32_t>(), Param::Reference }, { "index", type<uint32_t>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Axis dim_default = Axis::X;
			static Function f = { &namspc({ "two", "ui" }), "radio_switch", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<const char*>, uint32_t&, two::Axis)>(two::ui::radio_switch), two_ui_radio_switch_38, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "labels", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(), Param::Reference }, { "dim", type<two::Axis>(), Param::Default, &dim_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "popdown", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<const char*>, uint32_t&, two::vec2, two::ui::PopupFlags)>(two::ui::popdown), two_ui_popdown_39, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(), Param::Reference }, { "position", type<two::vec2>(),  }, { "flags", type<two::ui::PopupFlags>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool compact_default = false;
			static Function f = { &namspc({ "two", "ui" }), "dropdown_input", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<const char*>, uint32_t&, bool)>(two::ui::dropdown_input), two_ui_dropdown_input_40, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(), Param::Reference }, { "compact", type<bool>(), Param::Default, &compact_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "typedown_input", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<const char*>, uint32_t&)>(two::ui::typedown_input), two_ui_typedown_input_41, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* shortcut_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "menu_choice", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*, const char*)>(two::ui::menu_choice), two_ui_menu_choice_42, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "content", type<const char*>(),  }, { "shortcut", type<const char*>(), Param::Default, (void*)shortcut_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "menu_option", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*, const char*, bool)>(two::ui::menu_option), two_ui_menu_option_43, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "content", type<const char*>(),  }, { "shortcut", type<const char*>(),  }, { "enabled", type<bool>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "menubar", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::menubar), two_ui_menubar_44, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "toolbutton", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::toolbutton), two_ui_toolbutton_45, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "icon", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "tooldock", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::tooldock), two_ui_tooldock_46, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool wrap_default = false;
			static Function f = { &namspc({ "two", "ui" }), "toolbar", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, bool)>(two::ui::toolbar), two_ui_toolbar_47, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "wrap", type<bool>(), Param::Default, &wrap_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "columns", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, stl::span<float>)>(two::ui::columns), two_ui_columns_48, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "weights", type<stl::span<float>>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "table", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, stl::span<const char*>, stl::span<float>)>(two::ui::table), two_ui_table_49, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "columns", type<stl::span<const char*>>(),  }, { "weights", type<stl::span<float>>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "table_row", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::table_row), two_ui_table_row_50, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "table_separator", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::table_separator), two_ui_table_separator_51, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "tree", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::tree), two_ui_tree_52, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "row", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::row), two_ui_row_53, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "header", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::header), two_ui_header_54, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "div", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::div), two_ui_div_55, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "stack", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::stack), two_ui_stack_56, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "sheet", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::sheet), two_ui_sheet_57, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "board", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::board), two_ui_board_58, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "layout", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::layout), two_ui_layout_59, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "indent", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::indent), two_ui_indent_60, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "screen", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::screen), two_ui_screen_61, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "decal", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::decal), two_ui_decal_62, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "overlay", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::overlay), two_ui_overlay_63, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "title_header", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const char*)>(two::ui::title_header), two_ui_title_header_64, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "title", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dummy", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const two::vec2&)>(two::ui::dummy), two_ui_dummy_65, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "size", type<two::vec2>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "popup", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, two::ui::PopupFlags)>(two::ui::popup), two_ui_popup_66, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "flags", type<two::ui::PopupFlags>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::ui::PopupFlags flags_default = ui::PopupFlags::None;
			static Function f = { &namspc({ "two", "ui" }), "popup_at", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const two::vec2&, two::ui::PopupFlags)>(two::ui::popup_at), two_ui_popup_at_67, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "position", type<two::vec2>(),  }, { "flags", type<two::ui::PopupFlags>(), Param::Default, &flags_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "modal", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::modal), two_ui_modal_68, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "auto_modal", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, uint32_t)>(two::ui::auto_modal), two_ui_auto_modal_69, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "mode", type<uint32_t>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::ui::PopupFlags flags_default = ui::PopupFlags::None;
			static Function f = { &namspc({ "two", "ui" }), "context", funcptr<two::Widget*(*)(two::NodeKey, two::Widget&, uint32_t, two::ui::PopupFlags)>(two::ui::context), two_ui_context_70, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "mode", type<uint32_t>(),  }, { "flags", type<two::ui::PopupFlags>(), Param::Default, &flags_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float delay_default = 0.5f;
			static Function f = { &namspc({ "two", "ui" }), "hoverbox", funcptr<two::Widget*(*)(two::NodeKey, two::Widget&, float)>(two::ui::hoverbox), two_ui_hoverbox_71, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "delay", type<float>(), Param::Default, &delay_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool locked_default = false;
			static Function f = { &namspc({ "two", "ui" }), "cursor", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const two::vec2&, two::Widget&, bool)>(two::ui::cursor), two_ui_cursor_72, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "position", type<two::vec2>(),  }, { "hovered", type<two::Widget>(), Param::Reference }, { "locked", type<bool>(), Param::Default, &locked_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "rectangle", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const two::vec4&)>(two::ui::rectangle), two_ui_rectangle_73, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "rect", type<two::vec4>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "viewport", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const two::vec4&)>(two::ui::viewport), two_ui_viewport_74, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "rect", type<two::vec4>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dockspace", funcptr<two::DockspaceHandle(*)(two::NodeKey, two::Widget&, two::Docksystem&)>(two::ui::dockspace), two_ui_dockspace_75, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "docksystem", type<two::Docksystem>(), Param::Reference } }, { &type<two::DockspaceHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dockbar", funcptr<two::DockbarHandle(*)(two::NodeKey, two::Widget&, two::Docksystem&)>(two::ui::dockbar), two_ui_dockbar_76, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "docksystem", type<two::Docksystem>(), Param::Reference } }, { &type<two::DockbarHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dockitem", funcptr<two::Widget*(*)(two::Widget&, two::Docksystem&, const char*)>(two::ui::dockitem), two_ui_dockitem_77, { { "parent", type<two::Widget>(), Param::Reference }, { "docksystem", type<two::Docksystem>(), Param::Reference }, { "name", type<const char*>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float step_default = 0.1f;
			static Function f = { &namspc({ "two", "ui" }), "drag_float", funcptr<bool(*)(two::NodeKey, two::Widget&, float&, float)>(two::ui::drag_float), two_ui_drag_float_78, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<float>(), Param::Reference }, { "step", type<float>(), Param::Default, &step_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float2_input", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float2_input), two_ui_float2_input_79, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float3_input", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float3_input), two_ui_float3_input_80, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float4_input", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float4_input), two_ui_float4_input_81, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float2_slider", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float2_slider), two_ui_float2_slider_82, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float3_slider", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float3_slider), two_ui_float3_slider_83, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "float4_slider", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, stl::span<const char*>, stl::span<float>, two::StatDef<float>)>(two::ui::float4_slider), two_ui_float4_slider_84, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "label", type<const char*>(),  }, { "labels", type<stl::span<const char*>>(),  }, { "vals", type<stl::span<float>>(),  }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "vec2_edit", funcptr<bool(*)(two::NodeKey, two::Widget&, two::vec2&)>(two::ui::vec2_edit), two_ui_vec2_edit_85, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "vec", type<two::vec2>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "vec3_edit", funcptr<bool(*)(two::NodeKey, two::Widget&, two::vec3&)>(two::ui::vec3_edit), two_ui_vec3_edit_86, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "vec", type<two::vec3>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "quat_edit", funcptr<bool(*)(two::NodeKey, two::Widget&, two::quat&)>(two::ui::quat_edit), two_ui_quat_edit_87, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "quat", type<two::quat>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "color_display", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const two::Colour&)>(two::ui::color_display), two_ui_color_display_88, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<two::Colour>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "color_edit", funcptr<bool(*)(two::NodeKey, two::Widget&, two::Colour&)>(two::ui::color_edit), two_ui_color_edit_89, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<two::Colour>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "color_edit_simple", funcptr<bool(*)(two::NodeKey, two::Widget&, two::Colour&)>(two::ui::color_edit_simple), two_ui_color_edit_simple_90, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<two::Colour>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "color_toggle_edit", funcptr<bool(*)(two::NodeKey, two::Widget&, two::Colour&)>(two::ui::color_toggle_edit), two_ui_color_toggle_edit_91, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<two::Colour>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static stl::span<float> points_default = {};
			static Function f = { &namspc({ "two", "ui" }), "curve_graph", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<float>, stl::span<float>)>(two::ui::curve_graph), two_ui_curve_graph_92, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "values", type<stl::span<float>>(),  }, { "points", type<stl::span<float>>(), Param::Default, &points_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static stl::span<float> points_default = {};
			static Function f = { &namspc({ "two", "ui" }), "curve_edit", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::span<float>, stl::span<float>)>(two::ui::curve_edit), two_ui_curve_edit_93, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "values", type<stl::span<float>>(),  }, { "points", type<stl::span<float>>(), Param::Default, &points_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "flag_field", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, uint32_t&, uint8_t, bool)>(two::ui::flag_field), two_ui_flag_field_94, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "value", type<uint32_t>(), Param::Reference }, { "shift", type<uint8_t>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::Axis dim_default = Axis::X;
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "radio_field", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, stl::span<const char*>, uint32_t&, two::Axis, bool)>(two::ui::radio_field), two_ui_radio_field_95, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(), Param::Reference }, { "dim", type<two::Axis>(), Param::Default, &dim_default }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "dropdown_field", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, stl::span<const char*>, uint32_t&, bool)>(two::ui::dropdown_field), two_ui_dropdown_field_96, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(), Param::Reference }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "typedown_field", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, stl::span<const char*>, uint32_t&, bool)>(two::ui::typedown_field), two_ui_typedown_field_97, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "choices", type<stl::span<const char*>>(),  }, { "value", type<uint32_t>(), Param::Reference }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "color_field", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, two::Colour&, bool)>(two::ui::color_field), two_ui_color_field_98, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "value", type<two::Colour>(), Param::Reference }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "color_display_field", funcptr<void(*)(two::NodeKey, two::Widget&, const char*, const two::Colour&, bool)>(two::ui::color_display_field), two_ui_color_display_field_99, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "value", type<two::Colour>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<bool>", funcptr<bool(*)(two::NodeKey, two::Widget&, bool&)>(two::ui::input<bool>), two_ui_input_bool_100, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<bool>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<stl::string>", funcptr<bool(*)(two::NodeKey, two::Widget&, stl::string&)>(two::ui::input<stl::string>), two_ui_input_stl_string_101, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<stl::string>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<int>", funcptr<bool(*)(two::NodeKey, two::Widget&, int&, two::StatDef<int>)>(two::ui::input<int>), two_ui_input_int_102, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<int>(), Param::Reference }, { "def", type<two::StatDef<int>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "input<float>", funcptr<bool(*)(two::NodeKey, two::Widget&, float&, two::StatDef<float>)>(two::ui::input<float>), two_ui_input_float_103, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "value", type<float>(), Param::Reference }, { "def", type<two::StatDef<float>>(),  } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "field<bool>", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, bool&, bool)>(two::ui::field<bool>), two_ui_field_bool_104, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "value", type<bool>(), Param::Reference }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "field<stl::string>", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, stl::string&, bool)>(two::ui::field<stl::string>), two_ui_field_stl_string_105, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "value", type<stl::string>(), Param::Reference }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "field<int>", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, int&, two::StatDef<int>, bool)>(two::ui::field<int>), two_ui_field_int_106, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "value", type<int>(), Param::Reference }, { "def", type<two::StatDef<int>>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool reverse_default = false;
			static Function f = { &namspc({ "two", "ui" }), "field<float>", funcptr<bool(*)(two::NodeKey, two::Widget&, const char*, float&, two::StatDef<float>, bool)>(two::ui::field<float>), two_ui_field_float_107, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<const char*>(),  }, { "value", type<float>(), Param::Reference }, { "def", type<two::StatDef<float>>(),  }, { "reverse", type<bool>(), Param::Default, &reverse_default } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool editor_default = false;
			static size_t lines_default = 1;
			static stl::string allowed_chars_default = "";
			static Function f = { &namspc({ "two", "ui" }), "text_box", funcptr<two::TextEditHandle(*)(two::NodeKey, two::Widget&, two::Style&, stl::string&, bool, size_t, const stl::string&)>(two::ui::text_box), two_ui_text_box_108, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "style", type<two::Style>(), Param::Reference }, { "text", type<stl::string>(), Param::Reference }, { "editor", type<bool>(), Param::Default, &editor_default }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "allowed_chars", type<stl::string>(), Param::Default, &allowed_chars_default } }, { &type<two::TextEditHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::string allowed_chars_default = "";
			static Function f = { &namspc({ "two", "ui" }), "type_in", funcptr<two::TextEditHandle(*)(two::NodeKey, two::Widget&, stl::string&, size_t, const stl::string&)>(two::ui::type_in), two_ui_type_in_109, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "text", type<stl::string>(), Param::Reference }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "allowed_chars", type<stl::string>(), Param::Default, &allowed_chars_default } }, { &type<two::TextEditHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::vector<stl::string>* vocabulary_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "text_edit", funcptr<two::TextEditHandle(*)(two::NodeKey, two::Widget&, stl::string&, size_t, stl::vector<stl::string>*)>(two::ui::text_edit), two_ui_text_edit_110, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "text", type<stl::string>(), Param::Reference }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "vocabulary", type<stl::vector<stl::string>>(), Param::Flags(Param::Nullable|Param::Default), (void*)vocabulary_default } }, { &type<two::TextEditHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t lines_default = 1;
			static stl::vector<stl::string>* vocabulary_default = nullptr;
			static Function f = { &namspc({ "two", "ui" }), "code_edit", funcptr<two::TextEditHandle(*)(two::NodeKey, two::Widget&, stl::string&, size_t, stl::vector<stl::string>*)>(two::ui::code_edit), two_ui_code_edit_111, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "text", type<stl::string>(), Param::Reference }, { "lines", type<size_t>(), Param::Default, &lines_default }, { "vocabulary", type<stl::vector<stl::string>>(), Param::Flags(Param::Nullable|Param::Default), (void*)vocabulary_default } }, { &type<two::TextEditHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* icon_default = "";
			static two::Colour colour_default = Colour::NeonGreen;
			static bool active_default = true;
			static bool connected_default = false;
			static Function f = { &namspc({ "two", "ui" }), "node_input", funcptr<two::NodePlugHandle(*)(two::NodeKey, two::Node&, const char*, const char*, const two::Colour&, bool, bool)>(two::ui::node_input), two_ui_node_input_112, { { "id", type<two::NodeKey>(),  }, { "node", type<two::Node>(), Param::Reference }, { "name", type<const char*>(),  }, { "icon", type<const char*>(), Param::Default, (void*)icon_default }, { "colour", type<two::Colour>(), Param::Default, &colour_default }, { "active", type<bool>(), Param::Default, &active_default }, { "connected", type<bool>(), Param::Default, &connected_default } }, { &type<two::NodePlugHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static const char* icon_default = "";
			static two::Colour colour_default = Colour::NeonGreen;
			static bool active_default = true;
			static bool connected_default = false;
			static Function f = { &namspc({ "two", "ui" }), "node_output", funcptr<two::NodePlugHandle(*)(two::NodeKey, two::Node&, const char*, const char*, const two::Colour&, bool, bool)>(two::ui::node_output), two_ui_node_output_113, { { "id", type<two::NodeKey>(),  }, { "node", type<two::Node>(), Param::Reference }, { "name", type<const char*>(),  }, { "icon", type<const char*>(), Param::Default, (void*)icon_default }, { "colour", type<two::Colour>(), Param::Default, &colour_default }, { "active", type<bool>(), Param::Default, &active_default }, { "connected", type<bool>(), Param::Default, &connected_default } }, { &type<two::NodePlugHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static int order_default = 0;
			static two::Ref identity_default = {};
			static Function f = { &namspc({ "two", "ui" }), "node", funcptr<two::Node&(*)(two::Canvas&, const char*, two::vec2&, int, two::Ref)>(two::ui::node), two_ui_node_114, { { "parent", type<two::Canvas>(), Param::Reference }, { "title", type<const char*>(),  }, { "position", type<two::vec2>(), Param::Reference }, { "order", type<int>(), Param::Default, &order_default }, { "identity", type<two::Ref>(), Param::Flags(Param::Nullable|Param::Default), &identity_default } }, { &type<two::Node>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "node_cable", funcptr<two::Widget&(*)(two::NodeKey, two::Canvas&, two::NodePlug&, two::NodePlug&)>(two::ui::node_cable), two_ui_node_cable_115, { { "id", type<two::NodeKey>(),  }, { "canvas", type<two::Canvas>(), Param::Reference }, { "plug_out", type<two::NodePlug>(), Param::Reference }, { "plug_in", type<two::NodePlug>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t num_nodes_default = 0;
			static Function f = { &namspc({ "two", "ui" }), "canvas", funcptr<two::CanvasHandle(*)(two::NodeKey, two::Widget&, size_t)>(two::ui::canvas), two_ui_canvas_116, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "num_nodes", type<size_t>(), Param::Default, &num_nodes_default } }, { &type<two::CanvasHandle>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "scrollable", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&)>(two::ui::scrollable), two_ui_scrollable_117, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "multiselect_logic", funcptr<bool(*)(two::Widget&, two::Ref, stl::vector<two::Ref>&)>(two::ui::multiselect_logic), two_ui_multiselect_logic_118, { { "element", type<two::Widget>(), Param::Reference }, { "object", type<two::Ref>(), Param::Nullable }, { "selection", type<stl::vector<two::Ref>>(), Param::Reference } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "select_logic", funcptr<bool(*)(two::Widget&, two::Ref, two::Ref&)>(two::ui::select_logic), two_ui_select_logic_119, { { "element", type<two::Widget>(), Param::Reference }, { "object", type<two::Ref>(), Param::Nullable }, { "selection", type<two::Ref>(), Param::Flags(Param::Nullable|Param::Reference) } }, { &type<bool>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "element", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, two::Ref)>(two::ui::element), two_ui_element_120, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "object", type<two::Ref>(), Param::Nullable } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dir_item", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const stl::string&)>(two::ui::dir_item), two_ui_dir_item_121, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_item", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const stl::string&)>(two::ui::file_item), two_ui_file_item_122, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_list", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, stl::string&)>(two::ui::file_list), two_ui_file_list_123, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "path", type<stl::string>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_browser", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, stl::string&)>(two::ui::file_browser), two_ui_file_browser_124, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "path", type<stl::string>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "dir_node", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const stl::string&, const stl::string&, bool)>(two::ui::dir_node), two_ui_dir_node_125, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "path", type<stl::string>(),  }, { "name", type<stl::string>(),  }, { "collapsed", type<bool>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_node", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const stl::string&)>(two::ui::file_node), two_ui_file_node_126, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "name", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "file_tree", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, const stl::string&)>(two::ui::file_tree), two_ui_file_tree_127, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "path", type<stl::string>(),  } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "command_line", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, stl::string&, stl::string&)>(two::ui::command_line), two_ui_command_line_128, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "text", type<stl::string>(), Param::Reference }, { "command", type<stl::string>(), Param::Reference } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static size_t num_lines_default = 0;
			static Function f = { &namspc({ "two", "ui" }), "console", funcptr<two::Widget&(*)(two::NodeKey, two::Widget&, stl::string&, stl::string&, stl::string&, size_t)>(two::ui::console), two_ui_console_129, { { "id", type<two::NodeKey>(),  }, { "parent", type<two::Widget>(), Param::Reference }, { "feed", type<stl::string>(), Param::Reference }, { "line", type<stl::string>(), Param::Reference }, { "command", type<stl::string>(), Param::Reference }, { "num_lines", type<size_t>(), Param::Default, &num_lines_default } }, { &type<two::Widget>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_ui::two_ui()
		: Module("two::ui", { &two_infra::m(), &two_type::m(), &two_tree::m(), &two_math::m(), &two_ctx::m() })
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
