#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// CanvasConnect
	mud::Type* DECL mud_CanvasConnect__type() {
		return &mud::type<mud::CanvasConnect>();
	}
	mud::CanvasConnect* DECL mud_CanvasConnect_CanvasConnect_0() {
		return new mud::CanvasConnect();
	}
	void DECL mud_CanvasConnect__destroy(mud::CanvasConnect* self) {
		delete self;
	}
	// Clipboard
	mud::Type* DECL mud_Clipboard__type() {
		return &mud::type<mud::Clipboard>();
	}
	mud::Clipboard* DECL mud_Clipboard_Clipboard_0() {
		return new mud::Clipboard();
	}
	const char* DECL mud_Clipboard__get_text(mud::Clipboard* self) {
		return self->m_text.c_str();
	}
	void DECL mud_Clipboard__set_text(mud::Clipboard* self, const char* value) {
		self->m_text = value;
	}
	bool DECL mud_Clipboard__get_line_mode(mud::Clipboard* self) {
		return self->m_line_mode;
	}
	void DECL mud_Clipboard__set_line_mode(mud::Clipboard* self, bool value) {
		self->m_line_mode = value;
	}
	void DECL mud_Clipboard__destroy(mud::Clipboard* self) {
		delete self;
	}
	// Dock
	mud::Type* DECL mud_Dock__type() {
		return &mud::type<mud::Dock>();
	}
	mud::Dock* DECL mud_Dock_Dock_0() {
		return new mud::Dock();
	}
	void DECL mud_Dock__destroy(mud::Dock* self) {
		delete self;
	}
	// Docksystem
	mud::Type* DECL mud_Docksystem__type() {
		return &mud::type<mud::Docksystem>();
	}
	void DECL mud_Docksystem__destroy(mud::Docksystem* self) {
		delete self;
	}
	// Gradient
	mud::Type* DECL mud_Gradient__type() {
		return &mud::type<mud::Gradient>();
	}
	mud::Gradient* DECL mud_Gradient_Gradient_0() {
		return new mud::Gradient();
	}
	mud::Colour* DECL mud_Gradient__get_start(mud::Gradient* self) {
		static mud::Colour temp;
		return (temp = self->m_start, &temp);
	}
	void DECL mud_Gradient__set_start(mud::Gradient* self, mud::Colour* value) {
		self->m_start = *value;
	}
	mud::Colour* DECL mud_Gradient__get_end(mud::Gradient* self) {
		static mud::Colour temp;
		return (temp = self->m_end, &temp);
	}
	void DECL mud_Gradient__set_end(mud::Gradient* self, mud::Colour* value) {
		self->m_end = *value;
	}
	void DECL mud_Gradient__destroy(mud::Gradient* self) {
		delete self;
	}
	// GridSolver
	mud::Type* DECL mud_GridSolver__type() {
		return &mud::type<mud::GridSolver>();
	}
	void DECL mud_GridSolver__destroy(mud::GridSolver* self) {
		delete self;
	}
	// ImageSkin
	mud::Type* DECL mud_ImageSkin__type() {
		return &mud::type<mud::ImageSkin>();
	}
	mud::ImageSkin* DECL mud_ImageSkin_ImageSkin_5(mud::Image* image, int left, int top, int right, int bottom) {
		return new mud::ImageSkin(*image, left, top, right, bottom);
	}
	mud::ImageSkin* DECL mud_ImageSkin_ImageSkin_6(mud::Image* image, int left, int top, int right, int bottom, int margin) {
		return new mud::ImageSkin(*image, left, top, right, bottom, margin);
	}
	mud::ImageSkin* DECL mud_ImageSkin_ImageSkin_7(mud::Image* image, int left, int top, int right, int bottom, int margin, mud::Dim stretch) {
		return new mud::ImageSkin(*image, left, top, right, bottom, margin, stretch);
	}
	mud::Image* DECL mud_ImageSkin__get_d_image(mud::ImageSkin* self) {
		return self->d_image;
	}
	void DECL mud_ImageSkin__set_d_image(mud::ImageSkin* self, mud::Image* value) {
		self->d_image = value;
	}
	int DECL mud_ImageSkin__get_d_left(mud::ImageSkin* self) {
		return self->d_left;
	}
	void DECL mud_ImageSkin__set_d_left(mud::ImageSkin* self, int value) {
		self->d_left = value;
	}
	int DECL mud_ImageSkin__get_d_top(mud::ImageSkin* self) {
		return self->d_top;
	}
	void DECL mud_ImageSkin__set_d_top(mud::ImageSkin* self, int value) {
		self->d_top = value;
	}
	int DECL mud_ImageSkin__get_d_right(mud::ImageSkin* self) {
		return self->d_right;
	}
	void DECL mud_ImageSkin__set_d_right(mud::ImageSkin* self, int value) {
		self->d_right = value;
	}
	int DECL mud_ImageSkin__get_d_bottom(mud::ImageSkin* self) {
		return self->d_bottom;
	}
	void DECL mud_ImageSkin__set_d_bottom(mud::ImageSkin* self, int value) {
		self->d_bottom = value;
	}
	int DECL mud_ImageSkin__get_margin(mud::ImageSkin* self) {
		return self->m_margin;
	}
	void DECL mud_ImageSkin__set_margin(mud::ImageSkin* self, int value) {
		self->m_margin = value;
	}
	mud::Dim DECL mud_ImageSkin__get_d_stretch(mud::ImageSkin* self) {
		return self->d_stretch;
	}
	void DECL mud_ImageSkin__set_d_stretch(mud::ImageSkin* self, mud::Dim value) {
		self->d_stretch = value;
	}
	void DECL mud_ImageSkin__destroy(mud::ImageSkin* self) {
		delete self;
	}
	// InkStyle
	mud::Type* DECL mud_InkStyle__type() {
		return &mud::type<mud::InkStyle>();
	}
	mud::InkStyle* DECL mud_InkStyle_InkStyle_0() {
		return new mud::InkStyle();
	}
	mud::InkStyle* DECL mud_InkStyle_InkStyle_1(const char* name) {
		return new mud::InkStyle(name);
	}
	const char* DECL mud_InkStyle__get_name(mud::InkStyle* self) {
		return self->m_name.c_str();
	}
	void DECL mud_InkStyle__set_name(mud::InkStyle* self, const char* value) {
		self->m_name = value;
	}
	bool DECL mud_InkStyle__get_empty(mud::InkStyle* self) {
		return self->m_empty;
	}
	void DECL mud_InkStyle__set_empty(mud::InkStyle* self, bool value) {
		self->m_empty = value;
	}
	mud::Colour* DECL mud_InkStyle__get_background_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_background_colour, &temp);
	}
	void DECL mud_InkStyle__set_background_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_background_colour = *value;
	}
	mud::Colour* DECL mud_InkStyle__get_border_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_border_colour, &temp);
	}
	void DECL mud_InkStyle__set_border_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_border_colour = *value;
	}
	mud::Colour* DECL mud_InkStyle__get_image_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_image_colour, &temp);
	}
	void DECL mud_InkStyle__set_image_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_image_colour = *value;
	}
	mud::Colour* DECL mud_InkStyle__get_text_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_text_colour, &temp);
	}
	void DECL mud_InkStyle__set_text_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_text_colour = *value;
	}
	const char* DECL mud_InkStyle__get_text_font(mud::InkStyle* self) {
		return self->m_text_font.c_str();
	}
	void DECL mud_InkStyle__set_text_font(mud::InkStyle* self, const char* value) {
		self->m_text_font = value;
	}
	float DECL mud_InkStyle__get_text_size(mud::InkStyle* self) {
		return self->m_text_size;
	}
	void DECL mud_InkStyle__set_text_size(mud::InkStyle* self, float value) {
		self->m_text_size = value;
	}
	bool DECL mud_InkStyle__get_text_break(mud::InkStyle* self) {
		return self->m_text_break;
	}
	void DECL mud_InkStyle__set_text_break(mud::InkStyle* self, bool value) {
		self->m_text_break = value;
	}
	bool DECL mud_InkStyle__get_text_wrap(mud::InkStyle* self) {
		return self->m_text_wrap;
	}
	void DECL mud_InkStyle__set_text_wrap(mud::InkStyle* self, bool value) {
		self->m_text_wrap = value;
	}
	mud::vec4* DECL mud_InkStyle__get_border_width(mud::InkStyle* self) {
		static mud::vec4 temp;
		return (temp = self->m_border_width, &temp);
	}
	void DECL mud_InkStyle__set_border_width(mud::InkStyle* self, mud::vec4* value) {
		self->m_border_width = *value;
	}
	mud::vec4* DECL mud_InkStyle__get_corner_radius(mud::InkStyle* self) {
		static mud::vec4 temp;
		return (temp = self->m_corner_radius, &temp);
	}
	void DECL mud_InkStyle__set_corner_radius(mud::InkStyle* self, mud::vec4* value) {
		self->m_corner_radius = *value;
	}
	bool DECL mud_InkStyle__get_weak_corners(mud::InkStyle* self) {
		return self->m_weak_corners;
	}
	void DECL mud_InkStyle__set_weak_corners(mud::InkStyle* self, bool value) {
		self->m_weak_corners = value;
	}
	mud::vec4* DECL mud_InkStyle__get_padding(mud::InkStyle* self) {
		static mud::vec4 temp;
		return (temp = self->m_padding, &temp);
	}
	void DECL mud_InkStyle__set_padding(mud::InkStyle* self, mud::vec4* value) {
		self->m_padding = *value;
	}
	mud::vec4* DECL mud_InkStyle__get_margin(mud::InkStyle* self) {
		static mud::vec4 temp;
		return (temp = self->m_margin, &temp);
	}
	void DECL mud_InkStyle__set_margin(mud::InkStyle* self, mud::vec4* value) {
		self->m_margin = *value;
	}
	mud::vec2* DECL mud_InkStyle__get_linear_gradient(mud::InkStyle* self) {
		static mud::vec2 temp;
		return (temp = self->m_linear_gradient, &temp);
	}
	void DECL mud_InkStyle__set_linear_gradient(mud::InkStyle* self, mud::vec2* value) {
		self->m_linear_gradient = *value;
	}
	mud::Dim DECL mud_InkStyle__get_linear_gradient_dim(mud::InkStyle* self) {
		return self->m_linear_gradient_dim;
	}
	void DECL mud_InkStyle__set_linear_gradient_dim(mud::InkStyle* self, mud::Dim value) {
		self->m_linear_gradient_dim = value;
	}
	mud::Image* DECL mud_InkStyle__get_image(mud::InkStyle* self) {
		return self->m_image;
	}
	void DECL mud_InkStyle__set_image(mud::InkStyle* self, mud::Image* value) {
		self->m_image = value;
	}
	mud::Image* DECL mud_InkStyle__get_overlay(mud::InkStyle* self) {
		return self->m_overlay;
	}
	void DECL mud_InkStyle__set_overlay(mud::InkStyle* self, mud::Image* value) {
		self->m_overlay = value;
	}
	mud::Image* DECL mud_InkStyle__get_tile(mud::InkStyle* self) {
		return self->m_tile;
	}
	void DECL mud_InkStyle__set_tile(mud::InkStyle* self, mud::Image* value) {
		self->m_tile = value;
	}
	mud::ImageSkin* DECL mud_InkStyle__get_image_skin(mud::InkStyle* self) {
		static mud::ImageSkin temp;
		return (temp = self->m_image_skin, &temp);
	}
	void DECL mud_InkStyle__set_image_skin(mud::InkStyle* self, mud::ImageSkin* value) {
		self->m_image_skin = *value;
	}
	mud::Shadow* DECL mud_InkStyle__get_shadow(mud::InkStyle* self) {
		static mud::Shadow temp;
		return (temp = self->m_shadow, &temp);
	}
	void DECL mud_InkStyle__set_shadow(mud::InkStyle* self, mud::Shadow* value) {
		self->m_shadow = *value;
	}
	mud::Colour* DECL mud_InkStyle__get_shadow_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_shadow_colour, &temp);
	}
	void DECL mud_InkStyle__set_shadow_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_shadow_colour = *value;
	}
	mud::Style* DECL mud_InkStyle__get_hover_cursor(mud::InkStyle* self) {
		return self->m_hover_cursor;
	}
	void DECL mud_InkStyle__set_hover_cursor(mud::InkStyle* self, mud::Style* value) {
		self->m_hover_cursor = value;
	}
	void DECL mud_InkStyle__destroy(mud::InkStyle* self) {
		delete self;
	}
	// Layer
	mud::Type* DECL mud_Layer__type() {
		return &mud::type<mud::Layer>();
	}
	void DECL mud_Layer__destroy(mud::Layer* self) {
		delete self;
	}
	// Layout
	mud::Type* DECL mud_Layout__type() {
		return &mud::type<mud::Layout>();
	}
	mud::Layout* DECL mud_Layout_Layout_0() {
		return new mud::Layout();
	}
	mud::Layout* DECL mud_Layout_Layout_1(const char* name) {
		return new mud::Layout(name);
	}
	const char* DECL mud_Layout__get_name(mud::Layout* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Layout__set_name(mud::Layout* self, const char* value) {
		self->m_name = value;
	}
	mud::LayoutSolver DECL mud_Layout__get_solver(mud::Layout* self) {
		return self->m_solver;
	}
	void DECL mud_Layout__set_solver(mud::Layout* self, mud::LayoutSolver value) {
		self->m_solver = value;
	}
	mud::Flow DECL mud_Layout__get_flow(mud::Layout* self) {
		return self->m_flow;
	}
	void DECL mud_Layout__set_flow(mud::Layout* self, mud::Flow value) {
		self->m_flow = value;
	}
	mud::Space* DECL mud_Layout__get_space(mud::Layout* self) {
		static mud::Space temp;
		return (temp = self->m_space, &temp);
	}
	void DECL mud_Layout__set_space(mud::Layout* self, mud::Space* value) {
		self->m_space = *value;
	}
	mud::Clipping DECL mud_Layout__get_clipping(mud::Layout* self) {
		return self->m_clipping;
	}
	void DECL mud_Layout__set_clipping(mud::Layout* self, mud::Clipping value) {
		self->m_clipping = value;
	}
	mud::Opacity DECL mud_Layout__get_opacity(mud::Layout* self) {
		return self->m_opacity;
	}
	void DECL mud_Layout__set_opacity(mud::Layout* self, mud::Opacity value) {
		self->m_opacity = value;
	}
	mud::vec2* DECL mud_Layout__get_span(mud::Layout* self) {
		static mud::vec2 temp;
		return (temp = self->m_span, &temp);
	}
	void DECL mud_Layout__set_span(mud::Layout* self, mud::vec2* value) {
		self->m_span = *value;
	}
	mud::vec2* DECL mud_Layout__get_size(mud::Layout* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void DECL mud_Layout__set_size(mud::Layout* self, mud::vec2* value) {
		self->m_size = *value;
	}
	mud::vec4* DECL mud_Layout__get_padding(mud::Layout* self) {
		static mud::vec4 temp;
		return (temp = self->m_padding, &temp);
	}
	void DECL mud_Layout__set_padding(mud::Layout* self, mud::vec4* value) {
		self->m_padding = *value;
	}
	mud::vec2* DECL mud_Layout__get_margin(mud::Layout* self) {
		static mud::vec2 temp;
		return (temp = self->m_margin, &temp);
	}
	void DECL mud_Layout__set_margin(mud::Layout* self, mud::vec2* value) {
		self->m_margin = *value;
	}
	mud::vec2* DECL mud_Layout__get_spacing(mud::Layout* self) {
		static mud::vec2 temp;
		return (temp = self->m_spacing, &temp);
	}
	void DECL mud_Layout__set_spacing(mud::Layout* self, mud::vec2* value) {
		self->m_spacing = *value;
	}
	int DECL mud_Layout__get_zorder(mud::Layout* self) {
		return self->m_zorder;
	}
	void DECL mud_Layout__set_zorder(mud::Layout* self, int value) {
		self->m_zorder = value;
	}
	bool DECL mud_Layout__get_no_grid(mud::Layout* self) {
		return self->m_no_grid;
	}
	void DECL mud_Layout__set_no_grid(mud::Layout* self, bool value) {
		self->m_no_grid = value;
	}
	size_t DECL mud_Layout__get_updated(mud::Layout* self) {
		return self->m_updated;
	}
	void DECL mud_Layout__set_updated(mud::Layout* self, size_t value) {
		self->m_updated = value;
	}
	void DECL mud_Layout__destroy(mud::Layout* self) {
		delete self;
	}
	// NodeConnection
	mud::Type* DECL mud_NodeConnection__type() {
		return &mud::type<mud::NodeConnection>();
	}
	mud::NodeConnection* DECL mud_NodeConnection_NodeConnection_0() {
		return new mud::NodeConnection();
	}
	void DECL mud_NodeConnection__destroy(mud::NodeConnection* self) {
		delete self;
	}
	// Paint
	mud::Type* DECL mud_Paint__type() {
		return &mud::type<mud::Paint>();
	}
	mud::Paint* DECL mud_Paint_Paint_0() {
		return new mud::Paint();
	}
	mud::Colour* DECL mud_Paint__get_fill_colour(mud::Paint* self) {
		static mud::Colour temp;
		return (temp = self->m_fill_colour, &temp);
	}
	void DECL mud_Paint__set_fill_colour(mud::Paint* self, mud::Colour* value) {
		self->m_fill_colour = *value;
	}
	mud::Colour* DECL mud_Paint__get_stroke_colour(mud::Paint* self) {
		static mud::Colour temp;
		return (temp = self->m_stroke_colour, &temp);
	}
	void DECL mud_Paint__set_stroke_colour(mud::Paint* self, mud::Colour* value) {
		self->m_stroke_colour = *value;
	}
	float DECL mud_Paint__get_stroke_width(mud::Paint* self) {
		return self->m_stroke_width;
	}
	void DECL mud_Paint__set_stroke_width(mud::Paint* self, float value) {
		self->m_stroke_width = value;
	}
	void DECL mud_Paint__destroy(mud::Paint* self) {
		delete self;
	}
	// Shadow
	mud::Type* DECL mud_Shadow__type() {
		return &mud::type<mud::Shadow>();
	}
	mud::Shadow* DECL mud_Shadow_Shadow_4(float xpos, float ypos, float blur, float spread) {
		return new mud::Shadow(xpos, ypos, blur, spread);
	}
	mud::Shadow* DECL mud_Shadow_Shadow_5(float xpos, float ypos, float blur, float spread, mud::Colour* colour) {
		return new mud::Shadow(xpos, ypos, blur, spread, *colour);
	}
	float DECL mud_Shadow__get_d_xpos(mud::Shadow* self) {
		return self->d_xpos;
	}
	void DECL mud_Shadow__set_d_xpos(mud::Shadow* self, float value) {
		self->d_xpos = value;
	}
	float DECL mud_Shadow__get_d_ypos(mud::Shadow* self) {
		return self->d_ypos;
	}
	void DECL mud_Shadow__set_d_ypos(mud::Shadow* self, float value) {
		self->d_ypos = value;
	}
	float DECL mud_Shadow__get_d_blur(mud::Shadow* self) {
		return self->d_blur;
	}
	void DECL mud_Shadow__set_d_blur(mud::Shadow* self, float value) {
		self->d_blur = value;
	}
	float DECL mud_Shadow__get_d_spread(mud::Shadow* self) {
		return self->d_spread;
	}
	void DECL mud_Shadow__set_d_spread(mud::Shadow* self, float value) {
		self->d_spread = value;
	}
	mud::Colour* DECL mud_Shadow__get_d_colour(mud::Shadow* self) {
		static mud::Colour temp;
		return (temp = self->d_colour, &temp);
	}
	void DECL mud_Shadow__set_d_colour(mud::Shadow* self, mud::Colour* value) {
		self->d_colour = *value;
	}
	void DECL mud_Shadow__destroy(mud::Shadow* self) {
		delete self;
	}
	// Space
	mud::Type* DECL mud_Space__type() {
		return &mud::type<mud::Space>();
	}
	mud::Space* DECL mud_Space_Space_0() {
		return new mud::Space();
	}
	mud::FlowAxis DECL mud_Space__get_direction(mud::Space* self) {
		return self->direction;
	}
	void DECL mud_Space__set_direction(mud::Space* self, mud::FlowAxis value) {
		self->direction = value;
	}
	mud::Sizing DECL mud_Space__get_sizingLength(mud::Space* self) {
		return self->sizingLength;
	}
	void DECL mud_Space__set_sizingLength(mud::Space* self, mud::Sizing value) {
		self->sizingLength = value;
	}
	mud::Sizing DECL mud_Space__get_sizingDepth(mud::Space* self) {
		return self->sizingDepth;
	}
	void DECL mud_Space__set_sizingDepth(mud::Space* self, mud::Sizing value) {
		self->sizingDepth = value;
	}
	void DECL mud_Space__destroy(mud::Space* self) {
		delete self;
	}
	// Style
	mud::Type* DECL mud_Style__type() {
		return &mud::type<mud::Style>();
	}
	mud::Style* DECL mud_Style__get_base(mud::Style* self) {
		return self->m_base;
	}
	void DECL mud_Style__set_base(mud::Style* self, mud::Style* value) {
		self->m_base = value;
	}
	const char* DECL mud_Style__get_name(mud::Style* self) {
		return self->name();
	}
	mud::Layout* DECL mud_Style__get_layout(mud::Style* self) {
		return &self->layout();
	}
	mud::InkStyle* DECL mud_Style__get_skin(mud::Style* self) {
		return &self->skin();
	}
	void DECL mud_Style__destroy(mud::Style* self) {
		delete self;
	}
	// TableSolver
	mud::Type* DECL mud_TableSolver__type() {
		return &mud::type<mud::TableSolver>();
	}
	void DECL mud_TableSolver__destroy(mud::TableSolver* self) {
		delete self;
	}
	// Text
	mud::Type* DECL mud_Text__type() {
		return &mud::type<mud::Text>();
	}
	void DECL mud_Text__destroy(mud::Text* self) {
		delete self;
	}
	// TextCursor
	mud::Type* DECL mud_TextCursor__type() {
		return &mud::type<mud::TextCursor>();
	}
	mud::TextCursor* DECL mud_TextCursor_TextCursor_0() {
		return new mud::TextCursor();
	}
	void DECL mud_TextCursor__destroy(mud::TextCursor* self) {
		delete self;
	}
	// TextMarker
	mud::Type* DECL mud_TextMarker__type() {
		return &mud::type<mud::TextMarker>();
	}
	mud::TextMarker* DECL mud_TextMarker_TextMarker_0() {
		return new mud::TextMarker();
	}
	void DECL mud_TextMarker__destroy(mud::TextMarker* self) {
		delete self;
	}
	// TextPaint
	mud::Type* DECL mud_TextPaint__type() {
		return &mud::type<mud::TextPaint>();
	}
	mud::TextPaint* DECL mud_TextPaint_TextPaint_0() {
		return new mud::TextPaint();
	}
	const char* DECL mud_TextPaint__get_font(mud::TextPaint* self) {
		return self->m_font;
	}
	void DECL mud_TextPaint__set_font(mud::TextPaint* self, const char* value) {
		self->m_font = value;
	}
	mud::Colour* DECL mud_TextPaint__get_colour(mud::TextPaint* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void DECL mud_TextPaint__set_colour(mud::TextPaint* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	float DECL mud_TextPaint__get_size(mud::TextPaint* self) {
		return self->m_size;
	}
	void DECL mud_TextPaint__set_size(mud::TextPaint* self, float value) {
		self->m_size = value;
	}
	bool DECL mud_TextPaint__get_text_break(mud::TextPaint* self) {
		return self->m_text_break;
	}
	void DECL mud_TextPaint__set_text_break(mud::TextPaint* self, bool value) {
		self->m_text_break = value;
	}
	bool DECL mud_TextPaint__get_text_wrap(mud::TextPaint* self) {
		return self->m_text_wrap;
	}
	void DECL mud_TextPaint__set_text_wrap(mud::TextPaint* self, bool value) {
		self->m_text_wrap = value;
	}
	void DECL mud_TextPaint__destroy(mud::TextPaint* self) {
		delete self;
	}
	// TextSelection
	mud::Type* DECL mud_TextSelection__type() {
		return &mud::type<mud::TextSelection>();
	}
	mud::TextSelection* DECL mud_TextSelection_TextSelection_0() {
		return new mud::TextSelection();
	}
	void DECL mud_TextSelection__destroy(mud::TextSelection* self) {
		delete self;
	}
	// UiRect
	mud::Type* DECL mud_UiRect__type() {
		return &mud::type<mud::UiRect>();
	}
	mud::UiRect* DECL mud_UiRect_UiRect_0() {
		return new mud::UiRect();
	}
	mud::vec2* DECL mud_UiRect__get_position(mud::UiRect* self) {
		static mud::vec2 temp;
		return (temp = self->m_position, &temp);
	}
	void DECL mud_UiRect__set_position(mud::UiRect* self, mud::vec2* value) {
		self->m_position = *value;
	}
	mud::vec2* DECL mud_UiRect__get_size(mud::UiRect* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void DECL mud_UiRect__set_size(mud::UiRect* self, mud::vec2* value) {
		self->m_size = *value;
	}
	mud::vec2* DECL mud_UiRect__get_content(mud::UiRect* self) {
		static mud::vec2 temp;
		return (temp = self->m_content, &temp);
	}
	void DECL mud_UiRect__set_content(mud::UiRect* self, mud::vec2* value) {
		self->m_content = *value;
	}
	mud::vec2* DECL mud_UiRect__get_span(mud::UiRect* self) {
		static mud::vec2 temp;
		return (temp = self->m_span, &temp);
	}
	void DECL mud_UiRect__set_span(mud::UiRect* self, mud::vec2* value) {
		self->m_span = *value;
	}
	float DECL mud_UiRect__get_scale(mud::UiRect* self) {
		return self->m_scale;
	}
	void DECL mud_UiRect__set_scale(mud::UiRect* self, float value) {
		self->m_scale = value;
	}
	void DECL mud_UiRect__destroy(mud::UiRect* self) {
		delete self;
	}
	// UiWindow
	mud::Type* DECL mud_UiWindow__type() {
		return &mud::type<mud::UiWindow>();
	}
	void DECL mud_UiWindow__destroy(mud::UiWindow* self) {
		delete self;
	}
	// User
	mud::Type* DECL mud_User__type() {
		return &mud::type<mud::User>();
	}
	void DECL mud_User__destroy(mud::User* self) {
		delete self;
	}
	// Vg
	mud::Type* DECL mud_Vg__type() {
		return &mud::type<mud::Vg>();
	}
	void DECL mud_Vg__destroy(mud::Vg* self) {
		delete self;
	}
	// Frame
	mud::Type* DECL mud_Frame__type() {
		return &mud::type<mud::Frame>();
	}
	void DECL mud_Frame__destroy(mud::Frame* self) {
		delete self;
	}
	// FrameSolver
	mud::Type* DECL mud_FrameSolver__type() {
		return &mud::type<mud::FrameSolver>();
	}
	void DECL mud_FrameSolver__destroy(mud::FrameSolver* self) {
		delete self;
	}
	// LineSolver
	mud::Type* DECL mud_LineSolver__type() {
		return &mud::type<mud::LineSolver>();
	}
	void DECL mud_LineSolver__destroy(mud::LineSolver* self) {
		delete self;
	}
	// Widget
	mud::Type* DECL mud_Widget__type() {
		return &mud::type<mud::Widget>();
	}
	bool DECL mud_Widget_focused_0(mud::Widget* self) {
		return self->focused();
	}
	bool DECL mud_Widget_hovered_0(mud::Widget* self) {
		return self->hovered();
	}
	bool DECL mud_Widget_pressed_0(mud::Widget* self) {
		return self->pressed();
	}
	bool DECL mud_Widget_activated_0(mud::Widget* self) {
		return self->activated();
	}
	bool DECL mud_Widget_selected_0(mud::Widget* self) {
		return self->selected();
	}
	bool DECL mud_Widget_modal_0(mud::Widget* self) {
		return self->modal();
	}
	bool DECL mud_Widget_closed_0(mud::Widget* self) {
		return self->closed();
	}
	mud::UiWindow* DECL mud_Widget_ui_window_0(mud::Widget* self) {
		return &self->ui_window();
	}
	mud::Ui* DECL mud_Widget_ui_0(mud::Widget* self) {
		return &self->ui();
	}
	mud::Widget* DECL mud_Widget_parent_modal_0(mud::Widget* self) {
		return &self->parent_modal();
	}
	void DECL mud_Widget_toggle_state_1(mud::Widget* self, mud::WidgetState state) {
		self->toggle_state(state);
	}
	void DECL mud_Widget_disable_state_1(mud::Widget* self, mud::WidgetState state) {
		self->disable_state(state);
	}
	void DECL mud_Widget_set_state_2(mud::Widget* self, mud::WidgetState state, bool enabled) {
		self->set_state(state, enabled);
	}
	void DECL mud_Widget_enable_state_1(mud::Widget* self, mud::WidgetState state) {
		self->enable_state(state);
	}
	void DECL mud_Widget_clear_focus_0(mud::Widget* self) {
		self->clear_focus();
	}
	void DECL mud_Widget_take_focus_0(mud::Widget* self) {
		self->take_focus();
	}
	void DECL mud_Widget_yield_focus_0(mud::Widget* self) {
		self->yield_focus();
	}
	void DECL mud_Widget_take_modal_1(mud::Widget* self, uint32_t device_filter) {
		self->take_modal(device_filter);
	}
	void DECL mud_Widget_yield_modal_0(mud::Widget* self) {
		self->yield_modal();
	}
	mud::KeyEvent* DECL mud_Widget_key_event_2(mud::Widget* self, mud::Key code, mud::EventType event_type) {
		static mud::KeyEvent temp;
		return (temp = self->key_event(code, event_type), &temp);
	}
	mud::KeyEvent* DECL mud_Widget_key_event_3(mud::Widget* self, mud::Key code, mud::EventType event_type, mud::InputMod modifier) {
		static mud::KeyEvent temp;
		return (temp = self->key_event(code, event_type, modifier), &temp);
	}
	mud::KeyEvent* DECL mud_Widget_key_stroke_1(mud::Widget* self, mud::Key code) {
		static mud::KeyEvent temp;
		return (temp = self->key_stroke(code), &temp);
	}
	mud::KeyEvent* DECL mud_Widget_key_stroke_2(mud::Widget* self, mud::Key code, mud::InputMod modifier) {
		static mud::KeyEvent temp;
		return (temp = self->key_stroke(code, modifier), &temp);
	}
	mud::KeyEvent* DECL mud_Widget_char_stroke_1(mud::Widget* self, mud::Key code) {
		static mud::KeyEvent temp;
		return (temp = self->char_stroke(code), &temp);
	}
	mud::KeyEvent* DECL mud_Widget_char_stroke_2(mud::Widget* self, mud::Key code, mud::InputMod modifier) {
		static mud::KeyEvent temp;
		return (temp = self->char_stroke(code, modifier), &temp);
	}
	mud::MouseEvent* DECL mud_Widget_mouse_event_2(mud::Widget* self, mud::DeviceType device, mud::EventType event_type) {
		static mud::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type), &temp);
	}
	mud::MouseEvent* DECL mud_Widget_mouse_event_3(mud::Widget* self, mud::DeviceType device, mud::EventType event_type, mud::InputMod modifier) {
		static mud::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type, modifier), &temp);
	}
	mud::MouseEvent* DECL mud_Widget_mouse_event_4(mud::Widget* self, mud::DeviceType device, mud::EventType event_type, mud::InputMod modifier, bool consume) {
		static mud::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type, modifier, consume), &temp);
	}
	mud::Frame* DECL mud_Widget__get_frame(mud::Widget* self) {
		return &self->m_frame;
	}
	mud::WidgetState DECL mud_Widget__get_state(mud::Widget* self) {
		return self->m_state;
	}
	void DECL mud_Widget__set_state(mud::Widget* self, mud::WidgetState value) {
		self->m_state = value;
	}
	uint32_t DECL mud_Widget__get_switch(mud::Widget* self) {
		return self->m_switch;
	}
	void DECL mud_Widget__set_switch(mud::Widget* self, uint32_t value) {
		self->m_switch = value;
	}
	size_t DECL mud_Widget__get_index(mud::Widget* self) {
		return self->m_index;
	}
	void DECL mud_Widget__set_index(mud::Widget* self, size_t value) {
		self->m_index = value;
	}
	bool DECL mud_Widget__get_open(mud::Widget* self) {
		return self->m_open;
	}
	void DECL mud_Widget__set_open(mud::Widget* self, bool value) {
		self->m_open = value;
	}
	mud::Widget* DECL mud_Widget__get_body(mud::Widget* self) {
		return self->m_body;
	}
	void DECL mud_Widget__set_body(mud::Widget* self, mud::Widget* value) {
		self->m_body = value;
	}
	void DECL mud_Widget__destroy(mud::Widget* self) {
		delete self;
	}
	// Canvas
	mud::Type* DECL mud_Canvas__type() {
		return &mud::type<mud::Canvas>();
	}
	void DECL mud_Canvas__destroy(mud::Canvas* self) {
		delete self;
	}
	// Dockable
	mud::Type* DECL mud_Dockable__type() {
		return &mud::type<mud::Dockable>();
	}
	void DECL mud_Dockable__destroy(mud::Dockable* self) {
		delete self;
	}
	// Docker
	mud::Type* DECL mud_Docker__type() {
		return &mud::type<mud::Docker>();
	}
	void DECL mud_Docker__destroy(mud::Docker* self) {
		delete self;
	}
	// Dockbar
	mud::Type* DECL mud_Dockbar__type() {
		return &mud::type<mud::Dockbar>();
	}
	void DECL mud_Dockbar__destroy(mud::Dockbar* self) {
		delete self;
	}
	// Dockspace
	mud::Type* DECL mud_Dockspace__type() {
		return &mud::type<mud::Dockspace>();
	}
	void DECL mud_Dockspace__destroy(mud::Dockspace* self) {
		delete self;
	}
	// Expandbox
	mud::Type* DECL mud_Expandbox__type() {
		return &mud::type<mud::Expandbox>();
	}
	void DECL mud_Expandbox__destroy(mud::Expandbox* self) {
		delete self;
	}
	// Node
	mud::Type* DECL mud_Node__type() {
		return &mud::type<mud::Node>();
	}
	void DECL mud_Node__destroy(mud::Node* self) {
		delete self;
	}
	// NodePlug
	mud::Type* DECL mud_NodePlug__type() {
		return &mud::type<mud::NodePlug>();
	}
	void DECL mud_NodePlug__destroy(mud::NodePlug* self) {
		delete self;
	}
	// RowSolver
	mud::Type* DECL mud_RowSolver__type() {
		return &mud::type<mud::RowSolver>();
	}
	void DECL mud_RowSolver__destroy(mud::RowSolver* self) {
		delete self;
	}
	// ScrollSheet
	mud::Type* DECL mud_ScrollSheet__type() {
		return &mud::type<mud::ScrollSheet>();
	}
	void DECL mud_ScrollSheet__destroy(mud::ScrollSheet* self) {
		delete self;
	}
	// Sequence
	mud::Type* DECL mud_ui_Sequence__type() {
		return &mud::type<mud::ui::Sequence>();
	}
	void DECL mud_ui_Sequence__destroy(mud::ui::Sequence* self) {
		delete self;
	}
	// Tabber
	mud::Type* DECL mud_Tabber__type() {
		return &mud::type<mud::Tabber>();
	}
	void DECL mud_Tabber__destroy(mud::Tabber* self) {
		delete self;
	}
	// Table
	mud::Type* DECL mud_Table__type() {
		return &mud::type<mud::Table>();
	}
	void DECL mud_Table__destroy(mud::Table* self) {
		delete self;
	}
	// TextEdit
	mud::Type* DECL mud_TextEdit__type() {
		return &mud::type<mud::TextEdit>();
	}
	void DECL mud_TextEdit__destroy(mud::TextEdit* self) {
		delete self;
	}
	// TreeNode
	mud::Type* DECL mud_TreeNode__type() {
		return &mud::type<mud::TreeNode>();
	}
	void DECL mud_TreeNode__destroy(mud::TreeNode* self) {
		delete self;
	}
	// Ui
	mud::Type* DECL mud_Ui__type() {
		return &mud::type<mud::Ui>();
	}
	mud::Widget* DECL mud_Ui_begin_0(mud::Ui* self) {
		return &self->begin();
	}
	void DECL mud_Ui__destroy(mud::Ui* self) {
		delete self;
	}
	// Window
	mud::Type* DECL mud_Window__type() {
		return &mud::type<mud::Window>();
	}
	void DECL mud_Window__destroy(mud::Window* self) {
		delete self;
	}
	mud::Widget* DECL mud_ui_widget_2(mud::Widget* parent, mud::Style* style) {
		return &mud::ui::widget(*parent, *style);
	}
	mud::Widget* DECL mud_ui_widget_3(mud::Widget* parent, mud::Style* style, bool open) {
		return &mud::ui::widget(*parent, *style, open);
	}
	mud::Widget* DECL mud_ui_widget_4(mud::Widget* parent, mud::Style* style, bool open, mud::Dim length) {
		return &mud::ui::widget(*parent, *style, open, length);
	}
	mud::Widget* DECL mud_ui_widget_5(mud::Widget* parent, mud::Style* style, bool open, mud::Dim length, mud::Dim2<size_t>* index) {
		return &mud::ui::widget(*parent, *style, open, length, *index);
	}
	mud::Widget* DECL mud_ui_item_2(mud::Widget* parent, mud::Style* style) {
		return &mud::ui::item(*parent, *style);
	}
	mud::Widget* DECL mud_ui_item_3(mud::Widget* parent, mud::Style* style, const char* content) {
		return &mud::ui::item(*parent, *style, content);
	}
	mud::Widget* DECL mud_ui_spanner_4(mud::Widget* parent, mud::Style* style, mud::Dim dim, float span) {
		return &mud::ui::spanner(*parent, *style, dim, span);
	}
	mud::Widget* DECL mud_ui_spacer_1(mud::Widget* parent) {
		return &mud::ui::spacer(*parent);
	}
	mud::Widget* DECL mud_ui_icon_2(mud::Widget* parent, const char* image) {
		return &mud::ui::icon(*parent, image);
	}
	mud::Widget* DECL mud_ui_label_2(mud::Widget* parent, const char* label) {
		return &mud::ui::label(*parent, label);
	}
	mud::Widget* DECL mud_ui_title_2(mud::Widget* parent, const char* label) {
		return &mud::ui::title(*parent, label);
	}
	mud::Widget* DECL mud_ui_message_2(mud::Widget* parent, const char* label) {
		return &mud::ui::message(*parent, label);
	}
	mud::Widget* DECL mud_ui_text_2(mud::Widget* parent, const char* label) {
		return &mud::ui::text(*parent, label);
	}
	mud::Widget* DECL mud_ui_button_1(mud::Widget* parent) {
		return &mud::ui::button(*parent);
	}
	mud::Widget* DECL mud_ui_button_2(mud::Widget* parent, const char* content) {
		return &mud::ui::button(*parent, content);
	}
	mud::Widget* DECL mud_ui_toggle_2(mud::Widget* parent, bool on) {
		return &mud::ui::toggle(*parent, on);
	}
	mud::Widget* DECL mud_ui_toggle_3(mud::Widget* parent, bool on, const char* content) {
		return &mud::ui::toggle(*parent, on, content);
	}
	bool DECL mud_ui_modal_button_4(mud::Widget* screen, mud::Widget* parent, const char* content, uint32_t mode) {
		return mud::ui::modal_button(*screen, *parent, content, mode);
	}
	mud::Widget* DECL mud_ui_checkbox_2(mud::Widget* parent, bool on) {
		return &mud::ui::checkbox(*parent, on);
	}
	mud::Widget* DECL mud_ui_fill_bar_2(mud::Widget* parent, float percentage) {
		return &mud::ui::fill_bar(*parent, percentage);
	}
	mud::Widget* DECL mud_ui_fill_bar_3(mud::Widget* parent, float percentage, mud::Dim dim) {
		return &mud::ui::fill_bar(*parent, percentage, dim);
	}
	mud::Widget* DECL mud_ui_image256_3(mud::Widget* parent, const char* name, const mud::Image256* source) {
		return &mud::ui::image256(*parent, name, *source);
	}
	mud::Widget* DECL mud_ui_image256_4(mud::Widget* parent, const char* name, const mud::Image256* source, const mud::vec2* size) {
		return &mud::ui::image256(*parent, name, *source, *size);
	}
	mud::Widget* DECL mud_ui_radio_choice_3(mud::Widget* parent, const char* value, bool active) {
		return &mud::ui::radio_choice(*parent, value, active);
	}
	mud::Widget* DECL mud_ui_dropdown_4(mud::Widget* parent, mud::Style* style, const char* value, mud::ui::PopupFlags flags) {
		return &mud::ui::dropdown(*parent, *style, value, flags);
	}
	mud::Widget* DECL mud_ui_dropdown_5(mud::Widget* parent, mud::Style* style, const char* value, mud::ui::PopupFlags flags, mud::Style* list_style) {
		return &mud::ui::dropdown(*parent, *style, value, flags, list_style);
	}
	mud::Widget* DECL mud_ui_menu_choice_2(mud::Widget* parent, const char* content) {
		return &mud::ui::menu_choice(*parent, content);
	}
	mud::Widget* DECL mud_ui_menu_2(mud::Widget* parent, const char* label) {
		return &mud::ui::menu(*parent, label);
	}
	mud::Widget* DECL mud_ui_menu_3(mud::Widget* parent, const char* label, bool submenu) {
		return &mud::ui::menu(*parent, label, submenu);
	}
	mud::Widget* DECL mud_ui_menubar_1(mud::Widget* parent) {
		return &mud::ui::menubar(*parent);
	}
	mud::Widget* DECL mud_ui_toolbutton_2(mud::Widget* parent, const char* icon) {
		return &mud::ui::toolbutton(*parent, icon);
	}
	mud::Widget* DECL mud_ui_tooldock_1(mud::Widget* parent) {
		return &mud::ui::tooldock(*parent);
	}
	mud::Widget* DECL mud_ui_toolbar_1(mud::Widget* parent) {
		return &mud::ui::toolbar(*parent);
	}
	mud::Widget* DECL mud_ui_toolbar_2(mud::Widget* parent, bool wrap) {
		return &mud::ui::toolbar(*parent, wrap);
	}
	mud::ScrollSheet* DECL mud_ui_select_list_1(mud::Widget* parent) {
		return &mud::ui::select_list(*parent);
	}
	mud::Widget* DECL mud_ui_table_row_1(mud::Widget* parent) {
		return &mud::ui::table_row(*parent);
	}
	mud::Widget* DECL mud_ui_table_separator_1(mud::Widget* parent) {
		return &mud::ui::table_separator(*parent);
	}
	mud::Expandbox* DECL mud_ui_expandbox_2(mud::Widget* parent, const char* name) {
		return &mud::ui::expandbox(*parent, name);
	}
	mud::Expandbox* DECL mud_ui_expandbox_3(mud::Widget* parent, const char* name, bool open) {
		return &mud::ui::expandbox(*parent, name, open);
	}
	mud::TreeNode* DECL mud_ui_tree_node_2(mud::Widget* parent, const char* name) {
		return &mud::ui::tree_node(*parent, name);
	}
	mud::TreeNode* DECL mud_ui_tree_node_3(mud::Widget* parent, const char* name, bool leaf) {
		return &mud::ui::tree_node(*parent, name, leaf);
	}
	mud::TreeNode* DECL mud_ui_tree_node_4(mud::Widget* parent, const char* name, bool leaf, bool open) {
		return &mud::ui::tree_node(*parent, name, leaf, open);
	}
	mud::Widget* DECL mud_ui_tree_1(mud::Widget* parent) {
		return &mud::ui::tree(*parent);
	}
	mud::Widget* DECL mud_ui_tab_2(mud::Tabber* tabber, const char* name) {
		return mud::ui::tab(*tabber, name);
	}
	mud::Tabber* DECL mud_ui_tabber_1(mud::Widget* parent) {
		return &mud::ui::tabber(*parent);
	}
	mud::Widget* DECL mud_ui_row_1(mud::Widget* parent) {
		return &mud::ui::row(*parent);
	}
	mud::Widget* DECL mud_ui_header_1(mud::Widget* parent) {
		return &mud::ui::header(*parent);
	}
	mud::Widget* DECL mud_ui_div_1(mud::Widget* parent) {
		return &mud::ui::div(*parent);
	}
	mud::Widget* DECL mud_ui_stack_1(mud::Widget* parent) {
		return &mud::ui::stack(*parent);
	}
	mud::Widget* DECL mud_ui_sheet_1(mud::Widget* parent) {
		return &mud::ui::sheet(*parent);
	}
	mud::Widget* DECL mud_ui_board_1(mud::Widget* parent) {
		return &mud::ui::board(*parent);
	}
	mud::Widget* DECL mud_ui_layout_1(mud::Widget* parent) {
		return &mud::ui::layout(*parent);
	}
	mud::Widget* DECL mud_ui_screen_1(mud::Widget* parent) {
		return &mud::ui::screen(*parent);
	}
	mud::Widget* DECL mud_ui_decal_1(mud::Widget* parent) {
		return &mud::ui::decal(*parent);
	}
	mud::Widget* DECL mud_ui_overlay_1(mud::Widget* parent) {
		return &mud::ui::overlay(*parent);
	}
	mud::Widget* DECL mud_ui_title_header_2(mud::Widget* parent, const char* title) {
		return &mud::ui::title_header(*parent, title);
	}
	mud::Widget* DECL mud_ui_dummy_2(mud::Widget* parent, const mud::vec2* size) {
		return &mud::ui::dummy(*parent, *size);
	}
	mud::Widget* DECL mud_ui_popup_2(mud::Widget* parent, mud::ui::PopupFlags flags) {
		return &mud::ui::popup(*parent, flags);
	}
	mud::Widget* DECL mud_ui_popup_at_2(mud::Widget* parent, const mud::vec2* position) {
		return &mud::ui::popup_at(*parent, *position);
	}
	mud::Widget* DECL mud_ui_popup_at_3(mud::Widget* parent, const mud::vec2* position, mud::ui::PopupFlags flags) {
		return &mud::ui::popup_at(*parent, *position, flags);
	}
	mud::Widget* DECL mud_ui_modal_1(mud::Widget* parent) {
		return &mud::ui::modal(*parent);
	}
	mud::Widget* DECL mud_ui_modal_2(mud::Widget* parent, const mud::vec2* size) {
		return &mud::ui::modal(*parent, *size);
	}
	mud::Widget* DECL mud_ui_auto_modal_2(mud::Widget* parent, uint32_t mode) {
		return &mud::ui::auto_modal(*parent, mode);
	}
	mud::Widget* DECL mud_ui_auto_modal_3(mud::Widget* parent, uint32_t mode, const mud::vec2* size) {
		return &mud::ui::auto_modal(*parent, mode, *size);
	}
	mud::Widget* DECL mud_ui_context_2(mud::Widget* parent, uint32_t mode) {
		return mud::ui::context(*parent, mode);
	}
	mud::Widget* DECL mud_ui_context_3(mud::Widget* parent, uint32_t mode, mud::ui::PopupFlags flags) {
		return mud::ui::context(*parent, mode, flags);
	}
	mud::Widget* DECL mud_ui_hoverbox_1(mud::Widget* parent) {
		return mud::ui::hoverbox(*parent);
	}
	mud::Widget* DECL mud_ui_hoverbox_2(mud::Widget* parent, float delay) {
		return mud::ui::hoverbox(*parent, delay);
	}
	mud::Widget* DECL mud_ui_tooltip_3(mud::Widget* parent, const mud::vec2* position, const char* content) {
		return mud::ui::tooltip(*parent, *position, content);
	}
	mud::Widget* DECL mud_ui_cursor_3(mud::Widget* parent, const mud::vec2* position, mud::Widget* hovered) {
		return &mud::ui::cursor(*parent, *position, *hovered);
	}
	mud::Widget* DECL mud_ui_cursor_4(mud::Widget* parent, const mud::vec2* position, mud::Widget* hovered, bool locked) {
		return &mud::ui::cursor(*parent, *position, *hovered, locked);
	}
	mud::Widget* DECL mud_ui_rectangle_2(mud::Widget* parent, const mud::vec4* rect) {
		return &mud::ui::rectangle(*parent, *rect);
	}
	mud::Dockspace* DECL mud_ui_dockspace_2(mud::Widget* parent, mud::Docksystem* docksystem) {
		return &mud::ui::dockspace(*parent, *docksystem);
	}
	mud::Dockbar* DECL mud_ui_dockbar_2(mud::Widget* parent, mud::Docksystem* docksystem) {
		return &mud::ui::dockbar(*parent, *docksystem);
	}
	mud::Widget* DECL mud_ui_dockitem_3(mud::Widget* parent, mud::Docksystem* docksystem, mud::Dock* dock) {
		return mud::ui::dockitem(*parent, *docksystem, *dock);
	}
	bool DECL mud_ui_drag_float_2(mud::Widget* parent, float value) {
		return mud::ui::drag_float(*parent, value);
	}
	bool DECL mud_ui_drag_float_3(mud::Widget* parent, float value, float step) {
		return mud::ui::drag_float(*parent, value, step);
	}
	bool DECL mud_ui_vec2_edit_2(mud::Widget* parent, mud::vec2* vec) {
		return mud::ui::vec2_edit(*parent, *vec);
	}
	bool DECL mud_ui_vec3_edit_2(mud::Widget* parent, mud::vec3* vec) {
		return mud::ui::vec3_edit(*parent, *vec);
	}
	bool DECL mud_ui_quat_edit_2(mud::Widget* parent, mud::quat* quat) {
		return mud::ui::quat_edit(*parent, *quat);
	}
	bool DECL mud_ui_color_edit_hsl_3(mud::Widget* parent, const mud::Colour* colour, mud::Colour* value) {
		return mud::ui::color_edit_hsl(*parent, *colour, *value);
	}
	mud::Widget* DECL mud_ui_color_display_2(mud::Widget* parent, const mud::Colour* value) {
		return &mud::ui::color_display(*parent, *value);
	}
	bool DECL mud_ui_color_edit_2(mud::Widget* parent, mud::Colour* value) {
		return mud::ui::color_edit(*parent, *value);
	}
	bool DECL mud_ui_color_edit_simple_2(mud::Widget* parent, mud::Colour* value) {
		return mud::ui::color_edit_simple(*parent, *value);
	}
	bool DECL mud_ui_color_toggle_edit_2(mud::Widget* parent, mud::Colour* value) {
		return mud::ui::color_toggle_edit(*parent, *value);
	}
	bool DECL mud_ui_flag_field_4(mud::Widget* parent, const char* name, uint32_t value, uint8_t shift) {
		return mud::ui::flag_field(*parent, name, value, shift);
	}
	bool DECL mud_ui_flag_field_5(mud::Widget* parent, const char* name, uint32_t value, uint8_t shift, bool reverse) {
		return mud::ui::flag_field(*parent, name, value, shift, reverse);
	}
	bool DECL mud_ui_color_field_3(mud::Widget* parent, const char* name, mud::Colour* value) {
		return mud::ui::color_field(*parent, name, *value);
	}
	bool DECL mud_ui_color_field_4(mud::Widget* parent, const char* name, mud::Colour* value, bool reverse) {
		return mud::ui::color_field(*parent, name, *value, reverse);
	}
	void DECL mud_ui_color_display_field_3(mud::Widget* parent, const char* name, const mud::Colour* value) {
		mud::ui::color_display_field(*parent, name, *value);
	}
	void DECL mud_ui_color_display_field_4(mud::Widget* parent, const char* name, const mud::Colour* value, bool reverse) {
		mud::ui::color_display_field(*parent, name, *value, reverse);
	}
	mud::NodePlug* DECL mud_ui_node_input_2(mud::Node* node, const char* name) {
		return &mud::ui::node_input(*node, name);
	}
	mud::NodePlug* DECL mud_ui_node_input_3(mud::Node* node, const char* name, const char* icon) {
		return &mud::ui::node_input(*node, name, icon);
	}
	mud::NodePlug* DECL mud_ui_node_input_4(mud::Node* node, const char* name, const char* icon, const mud::Colour* colour) {
		return &mud::ui::node_input(*node, name, icon, *colour);
	}
	mud::NodePlug* DECL mud_ui_node_input_5(mud::Node* node, const char* name, const char* icon, const mud::Colour* colour, bool active) {
		return &mud::ui::node_input(*node, name, icon, *colour, active);
	}
	mud::NodePlug* DECL mud_ui_node_input_6(mud::Node* node, const char* name, const char* icon, const mud::Colour* colour, bool active, bool connected) {
		return &mud::ui::node_input(*node, name, icon, *colour, active, connected);
	}
	mud::NodePlug* DECL mud_ui_node_output_2(mud::Node* node, const char* name) {
		return &mud::ui::node_output(*node, name);
	}
	mud::NodePlug* DECL mud_ui_node_output_3(mud::Node* node, const char* name, const char* icon) {
		return &mud::ui::node_output(*node, name, icon);
	}
	mud::NodePlug* DECL mud_ui_node_output_4(mud::Node* node, const char* name, const char* icon, const mud::Colour* colour) {
		return &mud::ui::node_output(*node, name, icon, *colour);
	}
	mud::NodePlug* DECL mud_ui_node_output_5(mud::Node* node, const char* name, const char* icon, const mud::Colour* colour, bool active) {
		return &mud::ui::node_output(*node, name, icon, *colour, active);
	}
	mud::NodePlug* DECL mud_ui_node_output_6(mud::Node* node, const char* name, const char* icon, const mud::Colour* colour, bool active, bool connected) {
		return &mud::ui::node_output(*node, name, icon, *colour, active, connected);
	}
	mud::Node* DECL mud_ui_node_3(mud::Canvas* parent, const char* title, mud::vec2* position) {
		return &mud::ui::node(*parent, title, *position);
	}
	mud::Node* DECL mud_ui_node_4(mud::Canvas* parent, const char* title, mud::vec2* position, int order) {
		return &mud::ui::node(*parent, title, *position, order);
	}
	mud::Node* DECL mud_ui_node_5(mud::Canvas* parent, const char* title, mud::vec2* position, int order, void* identity, mud::Type* identity_type) {
		return &mud::ui::node(*parent, title, *position, order, { identity, *identity_type });
	}
	mud::Widget* DECL mud_ui_node_cable_3(mud::Canvas* canvas, mud::NodePlug* plug_out, mud::NodePlug* plug_in) {
		return &mud::ui::node_cable(*canvas, *plug_out, *plug_in);
	}
	mud::Canvas* DECL mud_ui_canvas_1(mud::Widget* parent) {
		return &mud::ui::canvas(*parent);
	}
	mud::Canvas* DECL mud_ui_canvas_2(mud::Widget* parent, size_t num_nodes) {
		return &mud::ui::canvas(*parent, num_nodes);
	}
	mud::Widget* DECL mud_ui_scrollable_1(mud::Widget* parent) {
		return &mud::ui::scrollable(*parent);
	}
	mud::ui::Sequence* DECL mud_ui_sequence_1(mud::Widget* parent) {
		return &mud::ui::sequence(*parent);
	}
	mud::ui::Sequence* DECL mud_ui_scroll_sequence_1(mud::Widget* parent) {
		return &mud::ui::scroll_sequence(*parent);
	}
	bool DECL mud_ui_select_logic_3(mud::Widget* element, void* object, mud::Type* object_type, void* selection, mud::Type* selection_type) {
		return mud::ui::select_logic(*element, { object, *object_type }, { selection, *selection_type });
	}
	mud::Widget* DECL mud_ui_element_2(mud::Widget* parent, void* object, mud::Type* object_type) {
		return &mud::ui::element(*parent, { object, *object_type });
	}
	mud::Widget* DECL mud_ui_sequence_element_2(mud::ui::Sequence* parent, void* object, mud::Type* object_type) {
		return &mud::ui::sequence_element(*parent, { object, *object_type });
	}
	mud::Window* DECL mud_ui_window_2(mud::Widget* parent, const char* title) {
		return &mud::ui::window(*parent, title);
	}
	mud::Window* DECL mud_ui_window_3(mud::Widget* parent, const char* title, mud::WindowState state) {
		return &mud::ui::window(*parent, title, state);
	}
	mud::Widget* DECL mud_ui_dir_item_2(mud::Widget* parent, const char* name) {
		return &mud::ui::dir_item(*parent, name);
	}
	mud::Widget* DECL mud_ui_file_item_2(mud::Widget* parent, const char* name) {
		return &mud::ui::file_item(*parent, name);
	}
	mud::Widget* DECL mud_ui_dir_node_4(mud::Widget* parent, const char* path, const char* name, bool collapsed) {
		return &mud::ui::dir_node(*parent, path, name, collapsed);
	}
	mud::Widget* DECL mud_ui_file_node_2(mud::Widget* parent, const char* name) {
		return &mud::ui::file_node(*parent, name);
	}
	mud::Widget* DECL mud_ui_file_tree_2(mud::Widget* parent, const char* path) {
		return &mud::ui::file_tree(*parent, path);
	}
	// Align
	mud::Align DECL mud_Align_Left() {
		return mud::Left;
	}
	mud::Align DECL mud_Align_CENTER() {
		return mud::CENTER;
	}
	mud::Align DECL mud_Align_Right() {
		return mud::Right;
	}
	mud::Align DECL mud_Align_OUT_LEFT() {
		return mud::OUT_LEFT;
	}
	mud::Align DECL mud_Align_OUT_RIGHT() {
		return mud::OUT_RIGHT;
	}
	// AutoLayout
	mud::AutoLayout DECL mud_AutoLayout_NO_LAYOUT() {
		return mud::NO_LAYOUT;
	}
	mud::AutoLayout DECL mud_AutoLayout_AUTO_SIZE() {
		return mud::AUTO_SIZE;
	}
	mud::AutoLayout DECL mud_AutoLayout_AUTO_LAYOUT() {
		return mud::AUTO_LAYOUT;
	}
	// Clipping
	mud::Clipping DECL mud_Clipping_NOCLIP() {
		return mud::NOCLIP;
	}
	mud::Clipping DECL mud_Clipping_CLIP() {
		return mud::CLIP;
	}
	mud::Clipping DECL mud_Clipping_UNCLIP() {
		return mud::UNCLIP;
	}
	// Dim
	mud::Dim DECL mud_Dim_DIM_X() {
		return mud::DIM_X;
	}
	mud::Dim DECL mud_Dim_DIM_Y() {
		return mud::DIM_Y;
	}
	mud::Dim DECL mud_Dim_DIM_NONE() {
		return mud::DIM_NONE;
	}
	// Flow
	mud::Flow DECL mud_Flow_FLOW() {
		return mud::FLOW;
	}
	mud::Flow DECL mud_Flow_OVERLAY() {
		return mud::OVERLAY;
	}
	mud::Flow DECL mud_Flow_ALIGN() {
		return mud::ALIGN;
	}
	mud::Flow DECL mud_Flow_FREE() {
		return mud::FREE;
	}
	// FlowAxis
	mud::FlowAxis DECL mud_FlowAxis_READING() {
		return mud::READING;
	}
	mud::FlowAxis DECL mud_FlowAxis_PARAGRAPH() {
		return mud::PARAGRAPH;
	}
	mud::FlowAxis DECL mud_FlowAxis_PARALLEL() {
		return mud::PARALLEL;
	}
	mud::FlowAxis DECL mud_FlowAxis_ORTHOGONAL() {
		return mud::ORTHOGONAL;
	}
	mud::FlowAxis DECL mud_FlowAxis_AXIS_NONE() {
		return mud::AXIS_NONE;
	}
	// LayoutSolver
	mud::LayoutSolver DECL mud_LayoutSolver_FRAME_SOLVER() {
		return mud::FRAME_SOLVER;
	}
	mud::LayoutSolver DECL mud_LayoutSolver_ROW_SOLVER() {
		return mud::ROW_SOLVER;
	}
	mud::LayoutSolver DECL mud_LayoutSolver_GRID_SOLVER() {
		return mud::GRID_SOLVER;
	}
	mud::LayoutSolver DECL mud_LayoutSolver_TABLE_SOLVER() {
		return mud::TABLE_SOLVER;
	}
	// Opacity
	mud::Opacity DECL mud_Opacity_OPAQUE() {
		return mud::OPAQUE;
	}
	mud::Opacity DECL mud_Opacity_CLEAR() {
		return mud::CLEAR;
	}
	mud::Opacity DECL mud_Opacity_HOLLOW() {
		return mud::HOLLOW;
	}
	// Pivot
	mud::Pivot DECL mud_Pivot_FORWARD() {
		return mud::FORWARD;
	}
	mud::Pivot DECL mud_Pivot_REVERSE() {
		return mud::REVERSE;
	}
	// PopupFlags
	mud::ui::PopupFlags DECL mud_ui_PopupFlags_None() {
		return mud::ui::PopupFlags::None;
	}
	mud::ui::PopupFlags DECL mud_ui_PopupFlags_Modal() {
		return mud::ui::PopupFlags::Modal;
	}
	mud::ui::PopupFlags DECL mud_ui_PopupFlags_Clamp() {
		return mud::ui::PopupFlags::Clamp;
	}
	mud::ui::PopupFlags DECL mud_ui_PopupFlags_AutoClose() {
		return mud::ui::PopupFlags::AutoClose;
	}
	mud::ui::PopupFlags DECL mud_ui_PopupFlags_AutoModal() {
		return mud::ui::PopupFlags::AutoModal;
	}
	// Sizing
	mud::Sizing DECL mud_Sizing_FIXED() {
		return mud::FIXED;
	}
	mud::Sizing DECL mud_Sizing_SHRINK() {
		return mud::SHRINK;
	}
	mud::Sizing DECL mud_Sizing_WRAP() {
		return mud::WRAP;
	}
	mud::Sizing DECL mud_Sizing_EXPAND() {
		return mud::EXPAND;
	}
	// SpacePreset
	mud::SpacePreset DECL mud_SpacePreset_SHEET() {
		return mud::SHEET;
	}
	mud::SpacePreset DECL mud_SpacePreset_FLEX() {
		return mud::FLEX;
	}
	mud::SpacePreset DECL mud_SpacePreset_ITEM() {
		return mud::ITEM;
	}
	mud::SpacePreset DECL mud_SpacePreset_UNIT() {
		return mud::UNIT;
	}
	mud::SpacePreset DECL mud_SpacePreset_BLOCK() {
		return mud::BLOCK;
	}
	mud::SpacePreset DECL mud_SpacePreset_LINE() {
		return mud::LINE;
	}
	mud::SpacePreset DECL mud_SpacePreset_STACK() {
		return mud::STACK;
	}
	mud::SpacePreset DECL mud_SpacePreset_DIV() {
		return mud::DIV;
	}
	mud::SpacePreset DECL mud_SpacePreset_SPACER() {
		return mud::SPACER;
	}
	mud::SpacePreset DECL mud_SpacePreset_BOARD() {
		return mud::BOARD;
	}
	mud::SpacePreset DECL mud_SpacePreset_LAYOUT() {
		return mud::LAYOUT;
	}
	// WidgetState
	mud::WidgetState DECL mud_WidgetState_NOSTATE() {
		return mud::NOSTATE;
	}
	mud::WidgetState DECL mud_WidgetState_CREATED() {
		return mud::CREATED;
	}
	mud::WidgetState DECL mud_WidgetState_HOVERED() {
		return mud::HOVERED;
	}
	mud::WidgetState DECL mud_WidgetState_PRESSED() {
		return mud::PRESSED;
	}
	mud::WidgetState DECL mud_WidgetState_ACTIVATED() {
		return mud::ACTIVATED;
	}
	mud::WidgetState DECL mud_WidgetState_ACTIVE() {
		return mud::ACTIVE;
	}
	mud::WidgetState DECL mud_WidgetState_SELECTED() {
		return mud::SELECTED;
	}
	mud::WidgetState DECL mud_WidgetState_DISABLED() {
		return mud::DISABLED;
	}
	mud::WidgetState DECL mud_WidgetState_DRAGGED() {
		return mud::DRAGGED;
	}
	mud::WidgetState DECL mud_WidgetState_FOCUSED() {
		return mud::FOCUSED;
	}
	mud::WidgetState DECL mud_WidgetState_CLOSED() {
		return mud::CLOSED;
	}
	// WindowState
	mud::WindowState DECL mud_WindowState_WINDOW_NOSTATE() {
		return mud::WINDOW_NOSTATE;
	}
	mud::WindowState DECL mud_WindowState_WINDOW_HEADER() {
		return mud::WINDOW_HEADER;
	}
	mud::WindowState DECL mud_WindowState_WINDOW_DOCKABLE() {
		return mud::WINDOW_DOCKABLE;
	}
	mud::WindowState DECL mud_WindowState_WINDOW_CLOSABLE() {
		return mud::WINDOW_CLOSABLE;
	}
	mud::WindowState DECL mud_WindowState_WINDOW_MOVABLE() {
		return mud::WINDOW_MOVABLE;
	}
	mud::WindowState DECL mud_WindowState_WINDOW_SIZABLE() {
		return mud::WINDOW_SIZABLE;
	}
	mud::WindowState DECL mud_WindowState_WINDOW_DEFAULT() {
		return mud::WINDOW_DEFAULT;
	}
	
}


