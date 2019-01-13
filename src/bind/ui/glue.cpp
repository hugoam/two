#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// CanvasConnect
	mud::CanvasConnect* EMSCRIPTEN_KEEPALIVE CanvasConnect_CanvasConnect_0() {
		return new mud::CanvasConnect();
	}
	void EMSCRIPTEN_KEEPALIVE CanvasConnect___destroy__(mud::CanvasConnect* self) {
		delete self;
	}
	// Clipboard
	mud::Clipboard* EMSCRIPTEN_KEEPALIVE Clipboard_Clipboard_0() {
		return new mud::Clipboard();
	}
	std::string EMSCRIPTEN_KEEPALIVE Clipboard_get_text(mud::Clipboard* self) {
		return self->m_text;
	}
	bool EMSCRIPTEN_KEEPALIVE Clipboard_get_line_mode(mud::Clipboard* self) {
		return self->m_line_mode;
	}
	std::vector<std::string> EMSCRIPTEN_KEEPALIVE Clipboard_get_pasted(mud::Clipboard* self) {
		return self->m_pasted;
	}
	void EMSCRIPTEN_KEEPALIVE Clipboard___destroy__(mud::Clipboard* self) {
		delete self;
	}
	// Dock
	mud::Dock* EMSCRIPTEN_KEEPALIVE Dock_Dock_0() {
		return new mud::Dock();
	}
	void EMSCRIPTEN_KEEPALIVE Dock___destroy__(mud::Dock* self) {
		delete self;
	}
	// Docksystem
	void EMSCRIPTEN_KEEPALIVE Docksystem___destroy__(mud::Docksystem* self) {
		delete self;
	}
	// Gradient
	mud::Gradient* EMSCRIPTEN_KEEPALIVE Gradient_Gradient_0() {
		return new mud::Gradient();
	}
	Colour EMSCRIPTEN_KEEPALIVE Gradient_get_start(mud::Gradient* self) {
		return self->m_start;
	}
	Colour EMSCRIPTEN_KEEPALIVE Gradient_get_end(mud::Gradient* self) {
		return self->m_end;
	}
	void EMSCRIPTEN_KEEPALIVE Gradient___destroy__(mud::Gradient* self) {
		delete self;
	}
	// GridSolver
	void EMSCRIPTEN_KEEPALIVE GridSolver___destroy__(mud::GridSolver* self) {
		delete self;
	}
	// ImageSkin
	mud::ImageSkin* EMSCRIPTEN_KEEPALIVE ImageSkin_ImageSkin_0() {
		return new mud::ImageSkin();
	}
	mud::ImageSkin* EMSCRIPTEN_KEEPALIVE ImageSkin_ImageSkin_5(Image image, int left, int top, int right, int bottom) {
		return new mud::ImageSkin(*image, left, top, right, bottom, margin, stretch);
	}
	mud::ImageSkin* EMSCRIPTEN_KEEPALIVE ImageSkin_ImageSkin_6(Image image, int left, int top, int right, int bottom, int margin) {
		return new mud::ImageSkin(*image, left, top, right, bottom, margin, stretch);
	}
	mud::ImageSkin* EMSCRIPTEN_KEEPALIVE ImageSkin_ImageSkin_7(Image image, int left, int top, int right, int bottom, int margin, Dim stretch) {
		return new mud::ImageSkin(*image, left, top, right, bottom, margin, stretch);
	}
	Image EMSCRIPTEN_KEEPALIVE ImageSkin_get_d_image(mud::ImageSkin* self) {
		return self->d_image;
	}
	int EMSCRIPTEN_KEEPALIVE ImageSkin_get_d_left(mud::ImageSkin* self) {
		return self->d_left;
	}
	int EMSCRIPTEN_KEEPALIVE ImageSkin_get_d_top(mud::ImageSkin* self) {
		return self->d_top;
	}
	int EMSCRIPTEN_KEEPALIVE ImageSkin_get_d_right(mud::ImageSkin* self) {
		return self->d_right;
	}
	int EMSCRIPTEN_KEEPALIVE ImageSkin_get_d_bottom(mud::ImageSkin* self) {
		return self->d_bottom;
	}
	int EMSCRIPTEN_KEEPALIVE ImageSkin_get_margin(mud::ImageSkin* self) {
		return self->m_margin;
	}
	Dim EMSCRIPTEN_KEEPALIVE ImageSkin_get_d_stretch(mud::ImageSkin* self) {
		return self->d_stretch;
	}
	void EMSCRIPTEN_KEEPALIVE ImageSkin___destroy__(mud::ImageSkin* self) {
		delete self;
	}
	// InkStyle
	mud::InkStyle* EMSCRIPTEN_KEEPALIVE InkStyle_InkStyle_0() {
		return new mud::InkStyle();
	}
	mud::InkStyle* EMSCRIPTEN_KEEPALIVE InkStyle_InkStyle_0() {
		return new mud::InkStyle();
	}
	mud::InkStyle* EMSCRIPTEN_KEEPALIVE InkStyle_InkStyle_1(const char* name) {
		return new mud::InkStyle(name);
	}
	std::string EMSCRIPTEN_KEEPALIVE InkStyle_get_name(mud::InkStyle* self) {
		return self->m_name;
	}
	bool EMSCRIPTEN_KEEPALIVE InkStyle_get_empty(mud::InkStyle* self) {
		return self->m_empty;
	}
	Colour EMSCRIPTEN_KEEPALIVE InkStyle_get_background_colour(mud::InkStyle* self) {
		return self->m_background_colour;
	}
	Colour EMSCRIPTEN_KEEPALIVE InkStyle_get_border_colour(mud::InkStyle* self) {
		return self->m_border_colour;
	}
	Colour EMSCRIPTEN_KEEPALIVE InkStyle_get_image_colour(mud::InkStyle* self) {
		return self->m_image_colour;
	}
	Colour EMSCRIPTEN_KEEPALIVE InkStyle_get_text_colour(mud::InkStyle* self) {
		return self->m_text_colour;
	}
	std::string EMSCRIPTEN_KEEPALIVE InkStyle_get_text_font(mud::InkStyle* self) {
		return self->m_text_font;
	}
	float EMSCRIPTEN_KEEPALIVE InkStyle_get_text_size(mud::InkStyle* self) {
		return self->m_text_size;
	}
	bool EMSCRIPTEN_KEEPALIVE InkStyle_get_text_break(mud::InkStyle* self) {
		return self->m_text_break;
	}
	bool EMSCRIPTEN_KEEPALIVE InkStyle_get_text_wrap(mud::InkStyle* self) {
		return self->m_text_wrap;
	}
	vec4 EMSCRIPTEN_KEEPALIVE InkStyle_get_border_width(mud::InkStyle* self) {
		return self->m_border_width;
	}
	vec4 EMSCRIPTEN_KEEPALIVE InkStyle_get_corner_radius(mud::InkStyle* self) {
		return self->m_corner_radius;
	}
	bool EMSCRIPTEN_KEEPALIVE InkStyle_get_weak_corners(mud::InkStyle* self) {
		return self->m_weak_corners;
	}
	vec4 EMSCRIPTEN_KEEPALIVE InkStyle_get_padding(mud::InkStyle* self) {
		return self->m_padding;
	}
	vec4 EMSCRIPTEN_KEEPALIVE InkStyle_get_margin(mud::InkStyle* self) {
		return self->m_margin;
	}
	vec2 EMSCRIPTEN_KEEPALIVE InkStyle_get_linear_gradient(mud::InkStyle* self) {
		return self->m_linear_gradient;
	}
	Dim EMSCRIPTEN_KEEPALIVE InkStyle_get_linear_gradient_dim(mud::InkStyle* self) {
		return self->m_linear_gradient_dim;
	}
	Image EMSCRIPTEN_KEEPALIVE InkStyle_get_image(mud::InkStyle* self) {
		return self->m_image;
	}
	Image EMSCRIPTEN_KEEPALIVE InkStyle_get_overlay(mud::InkStyle* self) {
		return self->m_overlay;
	}
	Image EMSCRIPTEN_KEEPALIVE InkStyle_get_tile(mud::InkStyle* self) {
		return self->m_tile;
	}
	ImageSkin EMSCRIPTEN_KEEPALIVE InkStyle_get_image_skin(mud::InkStyle* self) {
		return self->m_image_skin;
	}
	Shadow EMSCRIPTEN_KEEPALIVE InkStyle_get_shadow(mud::InkStyle* self) {
		return self->m_shadow;
	}
	Colour EMSCRIPTEN_KEEPALIVE InkStyle_get_shadow_colour(mud::InkStyle* self) {
		return self->m_shadow_colour;
	}
	Style EMSCRIPTEN_KEEPALIVE InkStyle_get_hover_cursor(mud::InkStyle* self) {
		return self->m_hover_cursor;
	}
	void EMSCRIPTEN_KEEPALIVE InkStyle___destroy__(mud::InkStyle* self) {
		delete self;
	}
	// Layer
	void EMSCRIPTEN_KEEPALIVE Layer___destroy__(mud::Layer* self) {
		delete self;
	}
	// Layout
	mud::Layout* EMSCRIPTEN_KEEPALIVE Layout_Layout_0() {
		return new mud::Layout();
	}
	mud::Layout* EMSCRIPTEN_KEEPALIVE Layout_Layout_0() {
		return new mud::Layout();
	}
	mud::Layout* EMSCRIPTEN_KEEPALIVE Layout_Layout_1(const char* name) {
		return new mud::Layout(name);
	}
	std::string EMSCRIPTEN_KEEPALIVE Layout_get_name(mud::Layout* self) {
		return self->m_name;
	}
	LayoutSolver EMSCRIPTEN_KEEPALIVE Layout_get_solver(mud::Layout* self) {
		return self->m_solver;
	}
	Flow EMSCRIPTEN_KEEPALIVE Layout_get_flow(mud::Layout* self) {
		return self->m_flow;
	}
	Space EMSCRIPTEN_KEEPALIVE Layout_get_space(mud::Layout* self) {
		return self->m_space;
	}
	Clipping EMSCRIPTEN_KEEPALIVE Layout_get_clipping(mud::Layout* self) {
		return self->m_clipping;
	}
	Opacity EMSCRIPTEN_KEEPALIVE Layout_get_opacity(mud::Layout* self) {
		return self->m_opacity;
	}
	vec2 EMSCRIPTEN_KEEPALIVE Layout_get_span(mud::Layout* self) {
		return self->m_span;
	}
	vec2 EMSCRIPTEN_KEEPALIVE Layout_get_size(mud::Layout* self) {
		return self->m_size;
	}
	vec4 EMSCRIPTEN_KEEPALIVE Layout_get_padding(mud::Layout* self) {
		return self->m_padding;
	}
	vec2 EMSCRIPTEN_KEEPALIVE Layout_get_margin(mud::Layout* self) {
		return self->m_margin;
	}
	vec2 EMSCRIPTEN_KEEPALIVE Layout_get_spacing(mud::Layout* self) {
		return self->m_spacing;
	}
	int EMSCRIPTEN_KEEPALIVE Layout_get_zorder(mud::Layout* self) {
		return self->m_zorder;
	}
	bool EMSCRIPTEN_KEEPALIVE Layout_get_no_grid(mud::Layout* self) {
		return self->m_no_grid;
	}
	std::vector<mud::Space> EMSCRIPTEN_KEEPALIVE Layout_get_grid_division(mud::Layout* self) {
		return self->m_grid_division;
	}
	std::vector<float> EMSCRIPTEN_KEEPALIVE Layout_get_table_division(mud::Layout* self) {
		return self->m_table_division;
	}
	size_t EMSCRIPTEN_KEEPALIVE Layout_get_updated(mud::Layout* self) {
		return self->m_updated;
	}
	void EMSCRIPTEN_KEEPALIVE Layout___destroy__(mud::Layout* self) {
		delete self;
	}
	// NodeConnection
	mud::NodeConnection* EMSCRIPTEN_KEEPALIVE NodeConnection_NodeConnection_0() {
		return new mud::NodeConnection();
	}
	void EMSCRIPTEN_KEEPALIVE NodeConnection___destroy__(mud::NodeConnection* self) {
		delete self;
	}
	// Paint
	mud::Paint* EMSCRIPTEN_KEEPALIVE Paint_Paint_0() {
		return new mud::Paint();
	}
	Colour EMSCRIPTEN_KEEPALIVE Paint_get_fill_colour(mud::Paint* self) {
		return self->m_fill_colour;
	}
	Colour EMSCRIPTEN_KEEPALIVE Paint_get_stroke_colour(mud::Paint* self) {
		return self->m_stroke_colour;
	}
	float EMSCRIPTEN_KEEPALIVE Paint_get_stroke_width(mud::Paint* self) {
		return self->m_stroke_width;
	}
	void EMSCRIPTEN_KEEPALIVE Paint___destroy__(mud::Paint* self) {
		delete self;
	}
	// Shadow
	mud::Shadow* EMSCRIPTEN_KEEPALIVE Shadow_Shadow_0() {
		return new mud::Shadow();
	}
	mud::Shadow* EMSCRIPTEN_KEEPALIVE Shadow_Shadow_4(float xpos, float ypos, float blur, float spread) {
		return new mud::Shadow(xpos, ypos, blur, spread, colour);
	}
	mud::Shadow* EMSCRIPTEN_KEEPALIVE Shadow_Shadow_5(float xpos, float ypos, float blur, float spread, Colour colour) {
		return new mud::Shadow(xpos, ypos, blur, spread, colour);
	}
	mud::Shadow* EMSCRIPTEN_KEEPALIVE Shadow_Shadow_0() {
		return new mud::Shadow();
	}
	float EMSCRIPTEN_KEEPALIVE Shadow_get_d_xpos(mud::Shadow* self) {
		return self->d_xpos;
	}
	float EMSCRIPTEN_KEEPALIVE Shadow_get_d_ypos(mud::Shadow* self) {
		return self->d_ypos;
	}
	float EMSCRIPTEN_KEEPALIVE Shadow_get_d_blur(mud::Shadow* self) {
		return self->d_blur;
	}
	float EMSCRIPTEN_KEEPALIVE Shadow_get_d_spread(mud::Shadow* self) {
		return self->d_spread;
	}
	Colour EMSCRIPTEN_KEEPALIVE Shadow_get_d_colour(mud::Shadow* self) {
		return self->d_colour;
	}
	void EMSCRIPTEN_KEEPALIVE Shadow___destroy__(mud::Shadow* self) {
		delete self;
	}
	// Space
	mud::Space* EMSCRIPTEN_KEEPALIVE Space_Space_0() {
		return new mud::Space();
	}
	FlowAxis EMSCRIPTEN_KEEPALIVE Space_get_direction(mud::Space* self) {
		return self->direction;
	}
	Sizing EMSCRIPTEN_KEEPALIVE Space_get_sizingLength(mud::Space* self) {
		return self->sizingLength;
	}
	Sizing EMSCRIPTEN_KEEPALIVE Space_get_sizingDepth(mud::Space* self) {
		return self->sizingDepth;
	}
	void EMSCRIPTEN_KEEPALIVE Space___destroy__(mud::Space* self) {
		delete self;
	}
	// Style
	Style EMSCRIPTEN_KEEPALIVE Style_get_base(mud::Style* self) {
		return self->m_base;
	}
	const char* EMSCRIPTEN_KEEPALIVE Style_get_name(mud::Style* self) {
		return self->name;
	}
	Layout EMSCRIPTEN_KEEPALIVE Style_get_layout(mud::Style* self) {
		return self->layout;
	}
	InkStyle EMSCRIPTEN_KEEPALIVE Style_get_skin(mud::Style* self) {
		return self->skin;
	}
	void EMSCRIPTEN_KEEPALIVE Style___destroy__(mud::Style* self) {
		delete self;
	}
	// TableSolver
	void EMSCRIPTEN_KEEPALIVE TableSolver___destroy__(mud::TableSolver* self) {
		delete self;
	}
	// Text
	void EMSCRIPTEN_KEEPALIVE Text___destroy__(mud::Text* self) {
		delete self;
	}
	// TextCursor
	mud::TextCursor* EMSCRIPTEN_KEEPALIVE TextCursor_TextCursor_0() {
		return new mud::TextCursor();
	}
	void EMSCRIPTEN_KEEPALIVE TextCursor___destroy__(mud::TextCursor* self) {
		delete self;
	}
	// TextMarker
	mud::TextMarker* EMSCRIPTEN_KEEPALIVE TextMarker_TextMarker_0() {
		return new mud::TextMarker();
	}
	void EMSCRIPTEN_KEEPALIVE TextMarker___destroy__(mud::TextMarker* self) {
		delete self;
	}
	// TextPaint
	mud::TextPaint* EMSCRIPTEN_KEEPALIVE TextPaint_TextPaint_0() {
		return new mud::TextPaint();
	}
	const char* EMSCRIPTEN_KEEPALIVE TextPaint_get_font(mud::TextPaint* self) {
		return self->m_font;
	}
	Colour EMSCRIPTEN_KEEPALIVE TextPaint_get_colour(mud::TextPaint* self) {
		return self->m_colour;
	}
	float EMSCRIPTEN_KEEPALIVE TextPaint_get_size(mud::TextPaint* self) {
		return self->m_size;
	}
	bool EMSCRIPTEN_KEEPALIVE TextPaint_get_text_break(mud::TextPaint* self) {
		return self->m_text_break;
	}
	bool EMSCRIPTEN_KEEPALIVE TextPaint_get_text_wrap(mud::TextPaint* self) {
		return self->m_text_wrap;
	}
	void EMSCRIPTEN_KEEPALIVE TextPaint___destroy__(mud::TextPaint* self) {
		delete self;
	}
	// TextSelection
	mud::TextSelection* EMSCRIPTEN_KEEPALIVE TextSelection_TextSelection_0() {
		return new mud::TextSelection();
	}
	void EMSCRIPTEN_KEEPALIVE TextSelection___destroy__(mud::TextSelection* self) {
		delete self;
	}
	// UiRect
	mud::UiRect* EMSCRIPTEN_KEEPALIVE UiRect_UiRect_0() {
		return new mud::UiRect();
	}
	vec2 EMSCRIPTEN_KEEPALIVE UiRect_get_position(mud::UiRect* self) {
		return self->m_position;
	}
	vec2 EMSCRIPTEN_KEEPALIVE UiRect_get_size(mud::UiRect* self) {
		return self->m_size;
	}
	vec2 EMSCRIPTEN_KEEPALIVE UiRect_get_content(mud::UiRect* self) {
		return self->m_content;
	}
	vec2 EMSCRIPTEN_KEEPALIVE UiRect_get_span(mud::UiRect* self) {
		return self->m_span;
	}
	float EMSCRIPTEN_KEEPALIVE UiRect_get_scale(mud::UiRect* self) {
		return self->m_scale;
	}
	void EMSCRIPTEN_KEEPALIVE UiRect___destroy__(mud::UiRect* self) {
		delete self;
	}
	// UiWindow
	void EMSCRIPTEN_KEEPALIVE UiWindow___destroy__(mud::UiWindow* self) {
		delete self;
	}
	// User
	void EMSCRIPTEN_KEEPALIVE User___destroy__(mud::User* self) {
		delete self;
	}
	// Vg
	void EMSCRIPTEN_KEEPALIVE Vg___destroy__(mud::Vg* self) {
		delete self;
	}
	// Frame
	void EMSCRIPTEN_KEEPALIVE Frame___destroy__(mud::Frame* self) {
		delete self;
	}
	// FrameSolver
	void EMSCRIPTEN_KEEPALIVE FrameSolver___destroy__(mud::FrameSolver* self) {
		delete self;
	}
	// LineSolver
	void EMSCRIPTEN_KEEPALIVE LineSolver___destroy__(mud::LineSolver* self) {
		delete self;
	}
	// Widget
	bool EMSCRIPTEN_KEEPALIVE Widget_focused_0(mud::Widget* self) {
		return self->focused();
	}
	bool EMSCRIPTEN_KEEPALIVE Widget_hovered_0(mud::Widget* self) {
		return self->hovered();
	}
	bool EMSCRIPTEN_KEEPALIVE Widget_pressed_0(mud::Widget* self) {
		return self->pressed();
	}
	bool EMSCRIPTEN_KEEPALIVE Widget_activated_0(mud::Widget* self) {
		return self->activated();
	}
	bool EMSCRIPTEN_KEEPALIVE Widget_selected_0(mud::Widget* self) {
		return self->selected();
	}
	bool EMSCRIPTEN_KEEPALIVE Widget_modal_0(mud::Widget* self) {
		return self->modal();
	}
	bool EMSCRIPTEN_KEEPALIVE Widget_closed_0(mud::Widget* self) {
		return self->closed();
	}
	UiWindow EMSCRIPTEN_KEEPALIVE Widget_ui_window_0(mud::Widget* self) {
		return self->ui_window();
	}
	Ui EMSCRIPTEN_KEEPALIVE Widget_ui_0(mud::Widget* self) {
		return self->ui();
	}
	Widget EMSCRIPTEN_KEEPALIVE Widget_parent_modal_0(mud::Widget* self) {
		return self->parent_modal();
	}
	void EMSCRIPTEN_KEEPALIVE Widget_toggle_state_1(mud::Widget* self, WidgetState state) {
		self->toggle_state(state);
	}
	void EMSCRIPTEN_KEEPALIVE Widget_disable_state_1(mud::Widget* self, WidgetState state) {
		self->disable_state(state);
	}
	void EMSCRIPTEN_KEEPALIVE Widget_set_state_2(mud::Widget* self, WidgetState state, bool enabled) {
		self->set_state(state, enabled);
	}
	void EMSCRIPTEN_KEEPALIVE Widget_enable_state_1(mud::Widget* self, WidgetState state) {
		self->enable_state(state);
	}
	void EMSCRIPTEN_KEEPALIVE Widget_clear_focus_0(mud::Widget* self) {
		self->clear_focus();
	}
	void EMSCRIPTEN_KEEPALIVE Widget_take_focus_0(mud::Widget* self) {
		self->take_focus();
	}
	void EMSCRIPTEN_KEEPALIVE Widget_yield_focus_0(mud::Widget* self) {
		self->yield_focus();
	}
	void EMSCRIPTEN_KEEPALIVE Widget_take_modal_1(mud::Widget* self, uint32_t device_filter) {
		self->take_modal(device_filter);
	}
	void EMSCRIPTEN_KEEPALIVE Widget_yield_modal_0(mud::Widget* self) {
		self->yield_modal();
	}
	KeyEvent EMSCRIPTEN_KEEPALIVE Widget_key_event_2(mud::Widget* self, Key code, EventType event_type) {
		return self->key_event(code, event_type, modifier);
	}
	KeyEvent EMSCRIPTEN_KEEPALIVE Widget_key_event_3(mud::Widget* self, Key code, EventType event_type, InputMod modifier) {
		return self->key_event(code, event_type, modifier);
	}
	KeyEvent EMSCRIPTEN_KEEPALIVE Widget_key_stroke_1(mud::Widget* self, Key code) {
		return self->key_stroke(code, modifier);
	}
	KeyEvent EMSCRIPTEN_KEEPALIVE Widget_key_stroke_2(mud::Widget* self, Key code, InputMod modifier) {
		return self->key_stroke(code, modifier);
	}
	KeyEvent EMSCRIPTEN_KEEPALIVE Widget_char_stroke_1(mud::Widget* self, Key code) {
		return self->char_stroke(code, modifier);
	}
	KeyEvent EMSCRIPTEN_KEEPALIVE Widget_char_stroke_2(mud::Widget* self, Key code, InputMod modifier) {
		return self->char_stroke(code, modifier);
	}
	MouseEvent EMSCRIPTEN_KEEPALIVE Widget_mouse_event_2(mud::Widget* self, DeviceType device, EventType event_type) {
		return self->mouse_event(device, event_type, modifier, consume);
	}
	MouseEvent EMSCRIPTEN_KEEPALIVE Widget_mouse_event_3(mud::Widget* self, DeviceType device, EventType event_type, InputMod modifier) {
		return self->mouse_event(device, event_type, modifier, consume);
	}
	MouseEvent EMSCRIPTEN_KEEPALIVE Widget_mouse_event_4(mud::Widget* self, DeviceType device, EventType event_type, InputMod modifier, bool consume) {
		return self->mouse_event(device, event_type, modifier, consume);
	}
	Frame EMSCRIPTEN_KEEPALIVE Widget_get_frame(mud::Widget* self) {
		return self->m_frame;
	}
	WidgetState EMSCRIPTEN_KEEPALIVE Widget_get_state(mud::Widget* self) {
		return self->m_state;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Widget_get_switch(mud::Widget* self) {
		return self->m_switch;
	}
	size_t EMSCRIPTEN_KEEPALIVE Widget_get_index(mud::Widget* self) {
		return self->m_index;
	}
	bool EMSCRIPTEN_KEEPALIVE Widget_get_open(mud::Widget* self) {
		return self->m_open;
	}
	Widget EMSCRIPTEN_KEEPALIVE Widget_get_body(mud::Widget* self) {
		return self->m_body;
	}
	void EMSCRIPTEN_KEEPALIVE Widget___destroy__(mud::Widget* self) {
		delete self;
	}
	// Canvas
	void EMSCRIPTEN_KEEPALIVE Canvas___destroy__(mud::Canvas* self) {
		delete self;
	}
	// Dockable
	void EMSCRIPTEN_KEEPALIVE Dockable___destroy__(mud::Dockable* self) {
		delete self;
	}
	// Docker
	void EMSCRIPTEN_KEEPALIVE Docker___destroy__(mud::Docker* self) {
		delete self;
	}
	// Dockbar
	void EMSCRIPTEN_KEEPALIVE Dockbar___destroy__(mud::Dockbar* self) {
		delete self;
	}
	// Dockspace
	void EMSCRIPTEN_KEEPALIVE Dockspace___destroy__(mud::Dockspace* self) {
		delete self;
	}
	// Expandbox
	void EMSCRIPTEN_KEEPALIVE Expandbox___destroy__(mud::Expandbox* self) {
		delete self;
	}
	// Node
	void EMSCRIPTEN_KEEPALIVE Node___destroy__(mud::Node* self) {
		delete self;
	}
	// NodePlug
	void EMSCRIPTEN_KEEPALIVE NodePlug___destroy__(mud::NodePlug* self) {
		delete self;
	}
	// RowSolver
	void EMSCRIPTEN_KEEPALIVE RowSolver___destroy__(mud::RowSolver* self) {
		delete self;
	}
	// ScrollSheet
	void EMSCRIPTEN_KEEPALIVE ScrollSheet___destroy__(mud::ScrollSheet* self) {
		delete self;
	}
	// Sequence
	void EMSCRIPTEN_KEEPALIVE Sequence___destroy__(mud::ui::Sequence* self) {
		delete self;
	}
	// Tabber
	void EMSCRIPTEN_KEEPALIVE Tabber___destroy__(mud::Tabber* self) {
		delete self;
	}
	// Table
	void EMSCRIPTEN_KEEPALIVE Table___destroy__(mud::Table* self) {
		delete self;
	}
	// TextEdit
	void EMSCRIPTEN_KEEPALIVE TextEdit___destroy__(mud::TextEdit* self) {
		delete self;
	}
	// TreeNode
	void EMSCRIPTEN_KEEPALIVE TreeNode___destroy__(mud::TreeNode* self) {
		delete self;
	}
	// Ui
	Widget EMSCRIPTEN_KEEPALIVE Ui_begin_0(mud::Ui* self) {
		return self->begin();
	}
	void EMSCRIPTEN_KEEPALIVE Ui___destroy__(mud::Ui* self) {
		delete self;
	}
	// Window
	void EMSCRIPTEN_KEEPALIVE Window___destroy__(mud::Window* self) {
		delete self;
	}
	
}


// 'Align'
Align EMSCRIPTEN_KEEPALIVE emscripten_enum_Align_Left() {
	return mud::Left;
}
Align EMSCRIPTEN_KEEPALIVE emscripten_enum_Align_CENTER() {
	return mud::CENTER;
}
Align EMSCRIPTEN_KEEPALIVE emscripten_enum_Align_Right() {
	return mud::Right;
}
Align EMSCRIPTEN_KEEPALIVE emscripten_enum_Align_OUT_LEFT() {
	return mud::OUT_LEFT;
}
Align EMSCRIPTEN_KEEPALIVE emscripten_enum_Align_OUT_RIGHT() {
	return mud::OUT_RIGHT;
}
// 'AutoLayout'
AutoLayout EMSCRIPTEN_KEEPALIVE emscripten_enum_AutoLayout_NO_LAYOUT() {
	return mud::NO_LAYOUT;
}
AutoLayout EMSCRIPTEN_KEEPALIVE emscripten_enum_AutoLayout_AUTO_SIZE() {
	return mud::AUTO_SIZE;
}
AutoLayout EMSCRIPTEN_KEEPALIVE emscripten_enum_AutoLayout_AUTO_LAYOUT() {
	return mud::AUTO_LAYOUT;
}
// 'Clipping'
Clipping EMSCRIPTEN_KEEPALIVE emscripten_enum_Clipping_NOCLIP() {
	return mud::NOCLIP;
}
Clipping EMSCRIPTEN_KEEPALIVE emscripten_enum_Clipping_CLIP() {
	return mud::CLIP;
}
Clipping EMSCRIPTEN_KEEPALIVE emscripten_enum_Clipping_UNCLIP() {
	return mud::UNCLIP;
}
// 'Dim'
Dim EMSCRIPTEN_KEEPALIVE emscripten_enum_Dim_DIM_X() {
	return mud::DIM_X;
}
Dim EMSCRIPTEN_KEEPALIVE emscripten_enum_Dim_DIM_Y() {
	return mud::DIM_Y;
}
Dim EMSCRIPTEN_KEEPALIVE emscripten_enum_Dim_DIM_NONE() {
	return mud::DIM_NONE;
}
// 'Flow'
Flow EMSCRIPTEN_KEEPALIVE emscripten_enum_Flow_FLOW() {
	return mud::FLOW;
}
Flow EMSCRIPTEN_KEEPALIVE emscripten_enum_Flow_OVERLAY() {
	return mud::OVERLAY;
}
Flow EMSCRIPTEN_KEEPALIVE emscripten_enum_Flow_ALIGN() {
	return mud::ALIGN;
}
Flow EMSCRIPTEN_KEEPALIVE emscripten_enum_Flow_FREE() {
	return mud::FREE;
}
// 'FlowAxis'
FlowAxis EMSCRIPTEN_KEEPALIVE emscripten_enum_FlowAxis_READING() {
	return mud::READING;
}
FlowAxis EMSCRIPTEN_KEEPALIVE emscripten_enum_FlowAxis_PARAGRAPH() {
	return mud::PARAGRAPH;
}
FlowAxis EMSCRIPTEN_KEEPALIVE emscripten_enum_FlowAxis_PARALLEL() {
	return mud::PARALLEL;
}
FlowAxis EMSCRIPTEN_KEEPALIVE emscripten_enum_FlowAxis_ORTHOGONAL() {
	return mud::ORTHOGONAL;
}
FlowAxis EMSCRIPTEN_KEEPALIVE emscripten_enum_FlowAxis_AXIS_NONE() {
	return mud::AXIS_NONE;
}
// 'LayoutSolver'
LayoutSolver EMSCRIPTEN_KEEPALIVE emscripten_enum_LayoutSolver_FRAME_SOLVER() {
	return mud::FRAME_SOLVER;
}
LayoutSolver EMSCRIPTEN_KEEPALIVE emscripten_enum_LayoutSolver_ROW_SOLVER() {
	return mud::ROW_SOLVER;
}
LayoutSolver EMSCRIPTEN_KEEPALIVE emscripten_enum_LayoutSolver_GRID_SOLVER() {
	return mud::GRID_SOLVER;
}
LayoutSolver EMSCRIPTEN_KEEPALIVE emscripten_enum_LayoutSolver_TABLE_SOLVER() {
	return mud::TABLE_SOLVER;
}
// 'Opacity'
Opacity EMSCRIPTEN_KEEPALIVE emscripten_enum_Opacity_OPAQUE() {
	return mud::OPAQUE;
}
Opacity EMSCRIPTEN_KEEPALIVE emscripten_enum_Opacity_CLEAR() {
	return mud::CLEAR;
}
Opacity EMSCRIPTEN_KEEPALIVE emscripten_enum_Opacity_HOLLOW() {
	return mud::HOLLOW;
}
// 'Pivot'
Pivot EMSCRIPTEN_KEEPALIVE emscripten_enum_Pivot_FORWARD() {
	return mud::FORWARD;
}
Pivot EMSCRIPTEN_KEEPALIVE emscripten_enum_Pivot_REVERSE() {
	return mud::REVERSE;
}
// 'PopupFlags'
PopupFlags EMSCRIPTEN_KEEPALIVE emscripten_enum_PopupFlags_None() {
	return mud::ui::PopupFlags::None;
}
PopupFlags EMSCRIPTEN_KEEPALIVE emscripten_enum_PopupFlags_Modal() {
	return mud::ui::PopupFlags::Modal;
}
PopupFlags EMSCRIPTEN_KEEPALIVE emscripten_enum_PopupFlags_Clamp() {
	return mud::ui::PopupFlags::Clamp;
}
PopupFlags EMSCRIPTEN_KEEPALIVE emscripten_enum_PopupFlags_AutoClose() {
	return mud::ui::PopupFlags::AutoClose;
}
PopupFlags EMSCRIPTEN_KEEPALIVE emscripten_enum_PopupFlags_AutoModal() {
	return mud::ui::PopupFlags::AutoModal;
}
// 'Sizing'
Sizing EMSCRIPTEN_KEEPALIVE emscripten_enum_Sizing_FIXED() {
	return mud::FIXED;
}
Sizing EMSCRIPTEN_KEEPALIVE emscripten_enum_Sizing_SHRINK() {
	return mud::SHRINK;
}
Sizing EMSCRIPTEN_KEEPALIVE emscripten_enum_Sizing_WRAP() {
	return mud::WRAP;
}
Sizing EMSCRIPTEN_KEEPALIVE emscripten_enum_Sizing_EXPAND() {
	return mud::EXPAND;
}
// 'SpacePreset'
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_SHEET() {
	return mud::SHEET;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_FLEX() {
	return mud::FLEX;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_ITEM() {
	return mud::ITEM;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_UNIT() {
	return mud::UNIT;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_BLOCK() {
	return mud::BLOCK;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_LINE() {
	return mud::LINE;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_STACK() {
	return mud::STACK;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_DIV() {
	return mud::DIV;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_SPACER() {
	return mud::SPACER;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_BOARD() {
	return mud::BOARD;
}
SpacePreset EMSCRIPTEN_KEEPALIVE emscripten_enum_SpacePreset_LAYOUT() {
	return mud::LAYOUT;
}
// 'WidgetState'
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_NOSTATE() {
	return mud::NOSTATE;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_CREATED() {
	return mud::CREATED;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_HOVERED() {
	return mud::HOVERED;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_PRESSED() {
	return mud::PRESSED;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_ACTIVATED() {
	return mud::ACTIVATED;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_ACTIVE() {
	return mud::ACTIVE;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_SELECTED() {
	return mud::SELECTED;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_DISABLED() {
	return mud::DISABLED;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_DRAGGED() {
	return mud::DRAGGED;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_FOCUSED() {
	return mud::FOCUSED;
}
WidgetState EMSCRIPTEN_KEEPALIVE emscripten_enum_WidgetState_CLOSED() {
	return mud::CLOSED;
}
// 'WindowState'
WindowState EMSCRIPTEN_KEEPALIVE emscripten_enum_WindowState_WINDOW_NOSTATE() {
	return mud::WINDOW_NOSTATE;
}
WindowState EMSCRIPTEN_KEEPALIVE emscripten_enum_WindowState_WINDOW_HEADER() {
	return mud::WINDOW_HEADER;
}
WindowState EMSCRIPTEN_KEEPALIVE emscripten_enum_WindowState_WINDOW_DOCKABLE() {
	return mud::WINDOW_DOCKABLE;
}
WindowState EMSCRIPTEN_KEEPALIVE emscripten_enum_WindowState_WINDOW_CLOSABLE() {
	return mud::WINDOW_CLOSABLE;
}
WindowState EMSCRIPTEN_KEEPALIVE emscripten_enum_WindowState_WINDOW_MOVABLE() {
	return mud::WINDOW_MOVABLE;
}
WindowState EMSCRIPTEN_KEEPALIVE emscripten_enum_WindowState_WINDOW_SIZABLE() {
	return mud::WINDOW_SIZABLE;
}
WindowState EMSCRIPTEN_KEEPALIVE emscripten_enum_WindowState_WINDOW_DEFAULT() {
	return mud::WINDOW_DEFAULT;
}
