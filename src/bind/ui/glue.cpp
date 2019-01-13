#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// CanvasConnect
	mud::CanvasConnect* EMSCRIPTEN_KEEPALIVE mud_CanvasConnect_CanvasConnect_0() {
		return new mud::CanvasConnect();
	}
	void EMSCRIPTEN_KEEPALIVE mud_CanvasConnect___destroy__(mud::CanvasConnect* self) {
		delete self;
	}
	// Clipboard
	mud::Clipboard* EMSCRIPTEN_KEEPALIVE mud_Clipboard_Clipboard_0() {
		return new mud::Clipboard();
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Clipboard_get_text(mud::Clipboard* self) {
		return self->m_text.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Clipboard_set_text(mud::Clipboard* self, const char* value) {
		self->m_text = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Clipboard_get_line_mode(mud::Clipboard* self) {
		return self->m_line_mode;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Clipboard_set_line_mode(mud::Clipboard* self, bool value) {
		self->m_line_mode = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Clipboard___destroy__(mud::Clipboard* self) {
		delete self;
	}
	// Dock
	mud::Dock* EMSCRIPTEN_KEEPALIVE mud_Dock_Dock_0() {
		return new mud::Dock();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Dock___destroy__(mud::Dock* self) {
		delete self;
	}
	// Docksystem
	void EMSCRIPTEN_KEEPALIVE mud_Docksystem___destroy__(mud::Docksystem* self) {
		delete self;
	}
	// Gradient
	mud::Gradient* EMSCRIPTEN_KEEPALIVE mud_Gradient_Gradient_0() {
		return new mud::Gradient();
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Gradient_get_start(mud::Gradient* self) {
		static mud::Colour temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Gradient_set_start(mud::Gradient* self, mud::Colour* value) {
		self->m_start = *value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Gradient_get_end(mud::Gradient* self) {
		static mud::Colour temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Gradient_set_end(mud::Gradient* self, mud::Colour* value) {
		self->m_end = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Gradient___destroy__(mud::Gradient* self) {
		delete self;
	}
	// GridSolver
	void EMSCRIPTEN_KEEPALIVE mud_GridSolver___destroy__(mud::GridSolver* self) {
		delete self;
	}
	// ImageSkin
	mud::ImageSkin* EMSCRIPTEN_KEEPALIVE mud_ImageSkin_ImageSkin_5(mud::Image* image, int left, int top, int right, int bottom) {
		return new mud::ImageSkin(*image, left, top, right, bottom);
	}
	mud::ImageSkin* EMSCRIPTEN_KEEPALIVE mud_ImageSkin_ImageSkin_6(mud::Image* image, int left, int top, int right, int bottom, int margin) {
		return new mud::ImageSkin(*image, left, top, right, bottom, margin);
	}
	mud::ImageSkin* EMSCRIPTEN_KEEPALIVE mud_ImageSkin_ImageSkin_7(mud::Image* image, int left, int top, int right, int bottom, int margin, mud::Dim stretch) {
		return new mud::ImageSkin(*image, left, top, right, bottom, margin, stretch);
	}
	mud::Image* EMSCRIPTEN_KEEPALIVE mud_ImageSkin_get_d_image(mud::ImageSkin* self) {
		return self->d_image;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImageSkin_set_d_image(mud::ImageSkin* self, mud::Image* value) {
		self->d_image = value;
	}
	int EMSCRIPTEN_KEEPALIVE mud_ImageSkin_get_d_left(mud::ImageSkin* self) {
		return self->d_left;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImageSkin_set_d_left(mud::ImageSkin* self, int value) {
		self->d_left = value;
	}
	int EMSCRIPTEN_KEEPALIVE mud_ImageSkin_get_d_top(mud::ImageSkin* self) {
		return self->d_top;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImageSkin_set_d_top(mud::ImageSkin* self, int value) {
		self->d_top = value;
	}
	int EMSCRIPTEN_KEEPALIVE mud_ImageSkin_get_d_right(mud::ImageSkin* self) {
		return self->d_right;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImageSkin_set_d_right(mud::ImageSkin* self, int value) {
		self->d_right = value;
	}
	int EMSCRIPTEN_KEEPALIVE mud_ImageSkin_get_d_bottom(mud::ImageSkin* self) {
		return self->d_bottom;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImageSkin_set_d_bottom(mud::ImageSkin* self, int value) {
		self->d_bottom = value;
	}
	int EMSCRIPTEN_KEEPALIVE mud_ImageSkin_get_margin(mud::ImageSkin* self) {
		return self->m_margin;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImageSkin_set_margin(mud::ImageSkin* self, int value) {
		self->m_margin = value;
	}
	mud::Dim EMSCRIPTEN_KEEPALIVE mud_ImageSkin_get_d_stretch(mud::ImageSkin* self) {
		return self->d_stretch;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImageSkin_set_d_stretch(mud::ImageSkin* self, mud::Dim value) {
		self->d_stretch = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ImageSkin___destroy__(mud::ImageSkin* self) {
		delete self;
	}
	// InkStyle
	mud::InkStyle* EMSCRIPTEN_KEEPALIVE mud_InkStyle_InkStyle_0() {
		return new mud::InkStyle();
	}
	mud::InkStyle* EMSCRIPTEN_KEEPALIVE mud_InkStyle_InkStyle_1(const char* name) {
		return new mud::InkStyle(name);
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_name(mud::InkStyle* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_name(mud::InkStyle* self, const char* value) {
		self->m_name = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_empty(mud::InkStyle* self) {
		return self->m_empty;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_empty(mud::InkStyle* self, bool value) {
		self->m_empty = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_background_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_background_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_background_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_background_colour = *value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_border_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_border_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_border_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_border_colour = *value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_image_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_image_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_image_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_image_colour = *value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_text_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_text_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_text_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_text_colour = *value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_text_font(mud::InkStyle* self) {
		return self->m_text_font.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_text_font(mud::InkStyle* self, const char* value) {
		self->m_text_font = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_text_size(mud::InkStyle* self) {
		return self->m_text_size;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_text_size(mud::InkStyle* self, float value) {
		self->m_text_size = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_text_break(mud::InkStyle* self) {
		return self->m_text_break;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_text_break(mud::InkStyle* self, bool value) {
		self->m_text_break = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_text_wrap(mud::InkStyle* self) {
		return self->m_text_wrap;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_text_wrap(mud::InkStyle* self, bool value) {
		self->m_text_wrap = value;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_border_width(mud::InkStyle* self) {
		static mud::vec4 temp;
		return (temp = self->m_border_width, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_border_width(mud::InkStyle* self, mud::vec4* value) {
		self->m_border_width = *value;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_corner_radius(mud::InkStyle* self) {
		static mud::vec4 temp;
		return (temp = self->m_corner_radius, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_corner_radius(mud::InkStyle* self, mud::vec4* value) {
		self->m_corner_radius = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_weak_corners(mud::InkStyle* self) {
		return self->m_weak_corners;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_weak_corners(mud::InkStyle* self, bool value) {
		self->m_weak_corners = value;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_padding(mud::InkStyle* self) {
		static mud::vec4 temp;
		return (temp = self->m_padding, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_padding(mud::InkStyle* self, mud::vec4* value) {
		self->m_padding = *value;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_margin(mud::InkStyle* self) {
		static mud::vec4 temp;
		return (temp = self->m_margin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_margin(mud::InkStyle* self, mud::vec4* value) {
		self->m_margin = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_linear_gradient(mud::InkStyle* self) {
		static mud::vec2 temp;
		return (temp = self->m_linear_gradient, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_linear_gradient(mud::InkStyle* self, mud::vec2* value) {
		self->m_linear_gradient = *value;
	}
	mud::Dim EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_linear_gradient_dim(mud::InkStyle* self) {
		return self->m_linear_gradient_dim;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_linear_gradient_dim(mud::InkStyle* self, mud::Dim value) {
		self->m_linear_gradient_dim = value;
	}
	mud::Image* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_image(mud::InkStyle* self) {
		return self->m_image;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_image(mud::InkStyle* self, mud::Image* value) {
		self->m_image = value;
	}
	mud::Image* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_overlay(mud::InkStyle* self) {
		return self->m_overlay;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_overlay(mud::InkStyle* self, mud::Image* value) {
		self->m_overlay = value;
	}
	mud::Image* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_tile(mud::InkStyle* self) {
		return self->m_tile;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_tile(mud::InkStyle* self, mud::Image* value) {
		self->m_tile = value;
	}
	mud::ImageSkin* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_image_skin(mud::InkStyle* self) {
		static mud::ImageSkin temp;
		return (temp = self->m_image_skin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_image_skin(mud::InkStyle* self, mud::ImageSkin* value) {
		self->m_image_skin = *value;
	}
	mud::Shadow* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_shadow(mud::InkStyle* self) {
		static mud::Shadow temp;
		return (temp = self->m_shadow, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_shadow(mud::InkStyle* self, mud::Shadow* value) {
		self->m_shadow = *value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_shadow_colour(mud::InkStyle* self) {
		static mud::Colour temp;
		return (temp = self->m_shadow_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_shadow_colour(mud::InkStyle* self, mud::Colour* value) {
		self->m_shadow_colour = *value;
	}
	mud::Style* EMSCRIPTEN_KEEPALIVE mud_InkStyle_get_hover_cursor(mud::InkStyle* self) {
		return self->m_hover_cursor;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle_set_hover_cursor(mud::InkStyle* self, mud::Style* value) {
		self->m_hover_cursor = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InkStyle___destroy__(mud::InkStyle* self) {
		delete self;
	}
	// Layer
	void EMSCRIPTEN_KEEPALIVE mud_Layer___destroy__(mud::Layer* self) {
		delete self;
	}
	// Layout
	mud::Layout* EMSCRIPTEN_KEEPALIVE mud_Layout_Layout_0() {
		return new mud::Layout();
	}
	mud::Layout* EMSCRIPTEN_KEEPALIVE mud_Layout_Layout_1(const char* name) {
		return new mud::Layout(name);
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Layout_get_name(mud::Layout* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_name(mud::Layout* self, const char* value) {
		self->m_name = value;
	}
	mud::LayoutSolver EMSCRIPTEN_KEEPALIVE mud_Layout_get_solver(mud::Layout* self) {
		return self->m_solver;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_solver(mud::Layout* self, mud::LayoutSolver value) {
		self->m_solver = value;
	}
	mud::Flow EMSCRIPTEN_KEEPALIVE mud_Layout_get_flow(mud::Layout* self) {
		return self->m_flow;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_flow(mud::Layout* self, mud::Flow value) {
		self->m_flow = value;
	}
	mud::Space* EMSCRIPTEN_KEEPALIVE mud_Layout_get_space(mud::Layout* self) {
		static mud::Space temp;
		return (temp = self->m_space, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_space(mud::Layout* self, mud::Space* value) {
		self->m_space = *value;
	}
	mud::Clipping EMSCRIPTEN_KEEPALIVE mud_Layout_get_clipping(mud::Layout* self) {
		return self->m_clipping;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_clipping(mud::Layout* self, mud::Clipping value) {
		self->m_clipping = value;
	}
	mud::Opacity EMSCRIPTEN_KEEPALIVE mud_Layout_get_opacity(mud::Layout* self) {
		return self->m_opacity;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_opacity(mud::Layout* self, mud::Opacity value) {
		self->m_opacity = value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Layout_get_span(mud::Layout* self) {
		static mud::vec2 temp;
		return (temp = self->m_span, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_span(mud::Layout* self, mud::vec2* value) {
		self->m_span = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Layout_get_size(mud::Layout* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_size(mud::Layout* self, mud::vec2* value) {
		self->m_size = *value;
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE mud_Layout_get_padding(mud::Layout* self) {
		static mud::vec4 temp;
		return (temp = self->m_padding, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_padding(mud::Layout* self, mud::vec4* value) {
		self->m_padding = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Layout_get_margin(mud::Layout* self) {
		static mud::vec2 temp;
		return (temp = self->m_margin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_margin(mud::Layout* self, mud::vec2* value) {
		self->m_margin = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Layout_get_spacing(mud::Layout* self) {
		static mud::vec2 temp;
		return (temp = self->m_spacing, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_spacing(mud::Layout* self, mud::vec2* value) {
		self->m_spacing = *value;
	}
	int EMSCRIPTEN_KEEPALIVE mud_Layout_get_zorder(mud::Layout* self) {
		return self->m_zorder;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_zorder(mud::Layout* self, int value) {
		self->m_zorder = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Layout_get_no_grid(mud::Layout* self) {
		return self->m_no_grid;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_no_grid(mud::Layout* self, bool value) {
		self->m_no_grid = value;
	}
	size_t EMSCRIPTEN_KEEPALIVE mud_Layout_get_updated(mud::Layout* self) {
		return self->m_updated;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout_set_updated(mud::Layout* self, size_t value) {
		self->m_updated = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Layout___destroy__(mud::Layout* self) {
		delete self;
	}
	// NodeConnection
	mud::NodeConnection* EMSCRIPTEN_KEEPALIVE mud_NodeConnection_NodeConnection_0() {
		return new mud::NodeConnection();
	}
	void EMSCRIPTEN_KEEPALIVE mud_NodeConnection___destroy__(mud::NodeConnection* self) {
		delete self;
	}
	// Paint
	mud::Paint* EMSCRIPTEN_KEEPALIVE mud_Paint_Paint_0() {
		return new mud::Paint();
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Paint_get_fill_colour(mud::Paint* self) {
		static mud::Colour temp;
		return (temp = self->m_fill_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Paint_set_fill_colour(mud::Paint* self, mud::Colour* value) {
		self->m_fill_colour = *value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Paint_get_stroke_colour(mud::Paint* self) {
		static mud::Colour temp;
		return (temp = self->m_stroke_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Paint_set_stroke_colour(mud::Paint* self, mud::Colour* value) {
		self->m_stroke_colour = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Paint_get_stroke_width(mud::Paint* self) {
		return self->m_stroke_width;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Paint_set_stroke_width(mud::Paint* self, float value) {
		self->m_stroke_width = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Paint___destroy__(mud::Paint* self) {
		delete self;
	}
	// Shadow
	mud::Shadow* EMSCRIPTEN_KEEPALIVE mud_Shadow_Shadow_4(float xpos, float ypos, float blur, float spread) {
		return new mud::Shadow(xpos, ypos, blur, spread);
	}
	mud::Shadow* EMSCRIPTEN_KEEPALIVE mud_Shadow_Shadow_5(float xpos, float ypos, float blur, float spread, mud::Colour* colour) {
		return new mud::Shadow(xpos, ypos, blur, spread, *colour);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Shadow_get_d_xpos(mud::Shadow* self) {
		return self->d_xpos;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Shadow_set_d_xpos(mud::Shadow* self, float value) {
		self->d_xpos = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Shadow_get_d_ypos(mud::Shadow* self) {
		return self->d_ypos;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Shadow_set_d_ypos(mud::Shadow* self, float value) {
		self->d_ypos = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Shadow_get_d_blur(mud::Shadow* self) {
		return self->d_blur;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Shadow_set_d_blur(mud::Shadow* self, float value) {
		self->d_blur = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Shadow_get_d_spread(mud::Shadow* self) {
		return self->d_spread;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Shadow_set_d_spread(mud::Shadow* self, float value) {
		self->d_spread = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Shadow_get_d_colour(mud::Shadow* self) {
		static mud::Colour temp;
		return (temp = self->d_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Shadow_set_d_colour(mud::Shadow* self, mud::Colour* value) {
		self->d_colour = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Shadow___destroy__(mud::Shadow* self) {
		delete self;
	}
	// Space
	mud::Space* EMSCRIPTEN_KEEPALIVE mud_Space_Space_0() {
		return new mud::Space();
	}
	mud::FlowAxis EMSCRIPTEN_KEEPALIVE mud_Space_get_direction(mud::Space* self) {
		return self->direction;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Space_set_direction(mud::Space* self, mud::FlowAxis value) {
		self->direction = value;
	}
	mud::Sizing EMSCRIPTEN_KEEPALIVE mud_Space_get_sizingLength(mud::Space* self) {
		return self->sizingLength;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Space_set_sizingLength(mud::Space* self, mud::Sizing value) {
		self->sizingLength = value;
	}
	mud::Sizing EMSCRIPTEN_KEEPALIVE mud_Space_get_sizingDepth(mud::Space* self) {
		return self->sizingDepth;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Space_set_sizingDepth(mud::Space* self, mud::Sizing value) {
		self->sizingDepth = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Space___destroy__(mud::Space* self) {
		delete self;
	}
	// Style
	mud::Style* EMSCRIPTEN_KEEPALIVE mud_Style_get_base(mud::Style* self) {
		return self->m_base;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Style_set_base(mud::Style* self, mud::Style* value) {
		self->m_base = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Style_get_name(mud::Style* self) {
		return self->name();
	}
	mud::Layout* EMSCRIPTEN_KEEPALIVE mud_Style_get_layout(mud::Style* self) {
		return &self->layout();
	}
	mud::InkStyle* EMSCRIPTEN_KEEPALIVE mud_Style_get_skin(mud::Style* self) {
		return &self->skin();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Style___destroy__(mud::Style* self) {
		delete self;
	}
	// TableSolver
	void EMSCRIPTEN_KEEPALIVE mud_TableSolver___destroy__(mud::TableSolver* self) {
		delete self;
	}
	// Text
	void EMSCRIPTEN_KEEPALIVE mud_Text___destroy__(mud::Text* self) {
		delete self;
	}
	// TextCursor
	mud::TextCursor* EMSCRIPTEN_KEEPALIVE mud_TextCursor_TextCursor_0() {
		return new mud::TextCursor();
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextCursor___destroy__(mud::TextCursor* self) {
		delete self;
	}
	// TextMarker
	mud::TextMarker* EMSCRIPTEN_KEEPALIVE mud_TextMarker_TextMarker_0() {
		return new mud::TextMarker();
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextMarker___destroy__(mud::TextMarker* self) {
		delete self;
	}
	// TextPaint
	mud::TextPaint* EMSCRIPTEN_KEEPALIVE mud_TextPaint_TextPaint_0() {
		return new mud::TextPaint();
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_TextPaint_get_font(mud::TextPaint* self) {
		return self->m_font;
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextPaint_set_font(mud::TextPaint* self, const char* value) {
		self->m_font = value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_TextPaint_get_colour(mud::TextPaint* self) {
		static mud::Colour temp;
		return (temp = self->m_colour, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextPaint_set_colour(mud::TextPaint* self, mud::Colour* value) {
		self->m_colour = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_TextPaint_get_size(mud::TextPaint* self) {
		return self->m_size;
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextPaint_set_size(mud::TextPaint* self, float value) {
		self->m_size = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_TextPaint_get_text_break(mud::TextPaint* self) {
		return self->m_text_break;
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextPaint_set_text_break(mud::TextPaint* self, bool value) {
		self->m_text_break = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_TextPaint_get_text_wrap(mud::TextPaint* self) {
		return self->m_text_wrap;
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextPaint_set_text_wrap(mud::TextPaint* self, bool value) {
		self->m_text_wrap = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextPaint___destroy__(mud::TextPaint* self) {
		delete self;
	}
	// TextSelection
	mud::TextSelection* EMSCRIPTEN_KEEPALIVE mud_TextSelection_TextSelection_0() {
		return new mud::TextSelection();
	}
	void EMSCRIPTEN_KEEPALIVE mud_TextSelection___destroy__(mud::TextSelection* self) {
		delete self;
	}
	// UiRect
	mud::UiRect* EMSCRIPTEN_KEEPALIVE mud_UiRect_UiRect_0() {
		return new mud::UiRect();
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_UiRect_get_position(mud::UiRect* self) {
		static mud::vec2 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_UiRect_set_position(mud::UiRect* self, mud::vec2* value) {
		self->m_position = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_UiRect_get_size(mud::UiRect* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_UiRect_set_size(mud::UiRect* self, mud::vec2* value) {
		self->m_size = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_UiRect_get_content(mud::UiRect* self) {
		static mud::vec2 temp;
		return (temp = self->m_content, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_UiRect_set_content(mud::UiRect* self, mud::vec2* value) {
		self->m_content = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_UiRect_get_span(mud::UiRect* self) {
		static mud::vec2 temp;
		return (temp = self->m_span, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_UiRect_set_span(mud::UiRect* self, mud::vec2* value) {
		self->m_span = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_UiRect_get_scale(mud::UiRect* self) {
		return self->m_scale;
	}
	void EMSCRIPTEN_KEEPALIVE mud_UiRect_set_scale(mud::UiRect* self, float value) {
		self->m_scale = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_UiRect___destroy__(mud::UiRect* self) {
		delete self;
	}
	// UiWindow
	void EMSCRIPTEN_KEEPALIVE mud_UiWindow___destroy__(mud::UiWindow* self) {
		delete self;
	}
	// User
	void EMSCRIPTEN_KEEPALIVE mud_User___destroy__(mud::User* self) {
		delete self;
	}
	// Vg
	void EMSCRIPTEN_KEEPALIVE mud_Vg___destroy__(mud::Vg* self) {
		delete self;
	}
	// Frame
	void EMSCRIPTEN_KEEPALIVE mud_Frame___destroy__(mud::Frame* self) {
		delete self;
	}
	// FrameSolver
	void EMSCRIPTEN_KEEPALIVE mud_FrameSolver___destroy__(mud::FrameSolver* self) {
		delete self;
	}
	// LineSolver
	void EMSCRIPTEN_KEEPALIVE mud_LineSolver___destroy__(mud::LineSolver* self) {
		delete self;
	}
	// Widget
	bool EMSCRIPTEN_KEEPALIVE mud_Widget_activated_0(mud::Widget* self) {
		return self->activated();
	}
	mud::KeyEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_char_stroke_1(mud::Widget* self, mud::Key code) {
		static mud::KeyEvent temp;
		return (temp = self->char_stroke(code), &temp);
	}
	mud::KeyEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_char_stroke_2(mud::Widget* self, mud::Key code, mud::InputMod modifier) {
		static mud::KeyEvent temp;
		return (temp = self->char_stroke(code, modifier), &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_clear_focus_0(mud::Widget* self) {
		self->clear_focus();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Widget_closed_0(mud::Widget* self) {
		return self->closed();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_disable_state_1(mud::Widget* self, mud::WidgetState state) {
		self->disable_state(state);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_enable_state_1(mud::Widget* self, mud::WidgetState state) {
		self->enable_state(state);
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Widget_focused_0(mud::Widget* self) {
		return self->focused();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Widget_hovered_0(mud::Widget* self) {
		return self->hovered();
	}
	mud::KeyEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_key_event_2(mud::Widget* self, mud::Key code, mud::EventType event_type) {
		static mud::KeyEvent temp;
		return (temp = self->key_event(code, event_type), &temp);
	}
	mud::KeyEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_key_event_3(mud::Widget* self, mud::Key code, mud::EventType event_type, mud::InputMod modifier) {
		static mud::KeyEvent temp;
		return (temp = self->key_event(code, event_type, modifier), &temp);
	}
	mud::KeyEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_key_stroke_1(mud::Widget* self, mud::Key code) {
		static mud::KeyEvent temp;
		return (temp = self->key_stroke(code), &temp);
	}
	mud::KeyEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_key_stroke_2(mud::Widget* self, mud::Key code, mud::InputMod modifier) {
		static mud::KeyEvent temp;
		return (temp = self->key_stroke(code, modifier), &temp);
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Widget_modal_0(mud::Widget* self) {
		return self->modal();
	}
	mud::MouseEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_mouse_event_2(mud::Widget* self, mud::DeviceType device, mud::EventType event_type) {
		static mud::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type), &temp);
	}
	mud::MouseEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_mouse_event_3(mud::Widget* self, mud::DeviceType device, mud::EventType event_type, mud::InputMod modifier) {
		static mud::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type, modifier), &temp);
	}
	mud::MouseEvent* EMSCRIPTEN_KEEPALIVE mud_Widget_mouse_event_4(mud::Widget* self, mud::DeviceType device, mud::EventType event_type, mud::InputMod modifier, bool consume) {
		static mud::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type, modifier, consume), &temp);
	}
	mud::Widget* EMSCRIPTEN_KEEPALIVE mud_Widget_parent_modal_0(mud::Widget* self) {
		return &self->parent_modal();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Widget_pressed_0(mud::Widget* self) {
		return self->pressed();
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Widget_selected_0(mud::Widget* self) {
		return self->selected();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_set_state_2(mud::Widget* self, mud::WidgetState state, bool enabled) {
		self->set_state(state, enabled);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_take_focus_0(mud::Widget* self) {
		self->take_focus();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_take_modal_1(mud::Widget* self, uint32_t device_filter) {
		self->take_modal(device_filter);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_toggle_state_1(mud::Widget* self, mud::WidgetState state) {
		self->toggle_state(state);
	}
	mud::Ui* EMSCRIPTEN_KEEPALIVE mud_Widget_ui_0(mud::Widget* self) {
		return &self->ui();
	}
	mud::UiWindow* EMSCRIPTEN_KEEPALIVE mud_Widget_ui_window_0(mud::Widget* self) {
		return &self->ui_window();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_yield_focus_0(mud::Widget* self) {
		self->yield_focus();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_yield_modal_0(mud::Widget* self) {
		self->yield_modal();
	}
	mud::Frame* EMSCRIPTEN_KEEPALIVE mud_Widget_get_frame(mud::Widget* self) {
		return &self->m_frame;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_Widget_get_state(mud::Widget* self) {
		return self->m_state;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_set_state(mud::Widget* self, mud::WidgetState value) {
		self->m_state = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE mud_Widget_get_switch(mud::Widget* self) {
		return self->m_switch;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_set_switch(mud::Widget* self, uint32_t value) {
		self->m_switch = value;
	}
	size_t EMSCRIPTEN_KEEPALIVE mud_Widget_get_index(mud::Widget* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_set_index(mud::Widget* self, size_t value) {
		self->m_index = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Widget_get_open(mud::Widget* self) {
		return self->m_open;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_set_open(mud::Widget* self, bool value) {
		self->m_open = value;
	}
	mud::Widget* EMSCRIPTEN_KEEPALIVE mud_Widget_get_body(mud::Widget* self) {
		return self->m_body;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget_set_body(mud::Widget* self, mud::Widget* value) {
		self->m_body = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Widget___destroy__(mud::Widget* self) {
		delete self;
	}
	// Canvas
	void EMSCRIPTEN_KEEPALIVE mud_Canvas___destroy__(mud::Canvas* self) {
		delete self;
	}
	// Dockable
	void EMSCRIPTEN_KEEPALIVE mud_Dockable___destroy__(mud::Dockable* self) {
		delete self;
	}
	// Docker
	void EMSCRIPTEN_KEEPALIVE mud_Docker___destroy__(mud::Docker* self) {
		delete self;
	}
	// Dockbar
	void EMSCRIPTEN_KEEPALIVE mud_Dockbar___destroy__(mud::Dockbar* self) {
		delete self;
	}
	// Dockspace
	void EMSCRIPTEN_KEEPALIVE mud_Dockspace___destroy__(mud::Dockspace* self) {
		delete self;
	}
	// Expandbox
	void EMSCRIPTEN_KEEPALIVE mud_Expandbox___destroy__(mud::Expandbox* self) {
		delete self;
	}
	// Node
	void EMSCRIPTEN_KEEPALIVE mud_Node___destroy__(mud::Node* self) {
		delete self;
	}
	// NodePlug
	void EMSCRIPTEN_KEEPALIVE mud_NodePlug___destroy__(mud::NodePlug* self) {
		delete self;
	}
	// RowSolver
	void EMSCRIPTEN_KEEPALIVE mud_RowSolver___destroy__(mud::RowSolver* self) {
		delete self;
	}
	// ScrollSheet
	void EMSCRIPTEN_KEEPALIVE mud_ScrollSheet___destroy__(mud::ScrollSheet* self) {
		delete self;
	}
	// Sequence
	void EMSCRIPTEN_KEEPALIVE mud_ui_Sequence___destroy__(mud::ui::Sequence* self) {
		delete self;
	}
	// Tabber
	void EMSCRIPTEN_KEEPALIVE mud_Tabber___destroy__(mud::Tabber* self) {
		delete self;
	}
	// Table
	void EMSCRIPTEN_KEEPALIVE mud_Table___destroy__(mud::Table* self) {
		delete self;
	}
	// TextEdit
	void EMSCRIPTEN_KEEPALIVE mud_TextEdit___destroy__(mud::TextEdit* self) {
		delete self;
	}
	// TreeNode
	void EMSCRIPTEN_KEEPALIVE mud_TreeNode___destroy__(mud::TreeNode* self) {
		delete self;
	}
	// Ui
	mud::Widget* EMSCRIPTEN_KEEPALIVE mud_Ui_begin_0(mud::Ui* self) {
		return &self->begin();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ui___destroy__(mud::Ui* self) {
		delete self;
	}
	// Window
	void EMSCRIPTEN_KEEPALIVE mud_Window___destroy__(mud::Window* self) {
		delete self;
	}
	// Align
	mud::Align EMSCRIPTEN_KEEPALIVE mud_Align_Left() {
		return mud::Left;
	}
	mud::Align EMSCRIPTEN_KEEPALIVE mud_Align_CENTER() {
		return mud::CENTER;
	}
	mud::Align EMSCRIPTEN_KEEPALIVE mud_Align_Right() {
		return mud::Right;
	}
	mud::Align EMSCRIPTEN_KEEPALIVE mud_Align_OUT_LEFT() {
		return mud::OUT_LEFT;
	}
	mud::Align EMSCRIPTEN_KEEPALIVE mud_Align_OUT_RIGHT() {
		return mud::OUT_RIGHT;
	}
	// AutoLayout
	mud::AutoLayout EMSCRIPTEN_KEEPALIVE mud_AutoLayout_NO_LAYOUT() {
		return mud::NO_LAYOUT;
	}
	mud::AutoLayout EMSCRIPTEN_KEEPALIVE mud_AutoLayout_AUTO_SIZE() {
		return mud::AUTO_SIZE;
	}
	mud::AutoLayout EMSCRIPTEN_KEEPALIVE mud_AutoLayout_AUTO_LAYOUT() {
		return mud::AUTO_LAYOUT;
	}
	// Clipping
	mud::Clipping EMSCRIPTEN_KEEPALIVE mud_Clipping_NOCLIP() {
		return mud::NOCLIP;
	}
	mud::Clipping EMSCRIPTEN_KEEPALIVE mud_Clipping_CLIP() {
		return mud::CLIP;
	}
	mud::Clipping EMSCRIPTEN_KEEPALIVE mud_Clipping_UNCLIP() {
		return mud::UNCLIP;
	}
	// Dim
	mud::Dim EMSCRIPTEN_KEEPALIVE mud_Dim_DIM_X() {
		return mud::DIM_X;
	}
	mud::Dim EMSCRIPTEN_KEEPALIVE mud_Dim_DIM_Y() {
		return mud::DIM_Y;
	}
	mud::Dim EMSCRIPTEN_KEEPALIVE mud_Dim_DIM_NONE() {
		return mud::DIM_NONE;
	}
	// Flow
	mud::Flow EMSCRIPTEN_KEEPALIVE mud_Flow_FLOW() {
		return mud::FLOW;
	}
	mud::Flow EMSCRIPTEN_KEEPALIVE mud_Flow_OVERLAY() {
		return mud::OVERLAY;
	}
	mud::Flow EMSCRIPTEN_KEEPALIVE mud_Flow_ALIGN() {
		return mud::ALIGN;
	}
	mud::Flow EMSCRIPTEN_KEEPALIVE mud_Flow_FREE() {
		return mud::FREE;
	}
	// FlowAxis
	mud::FlowAxis EMSCRIPTEN_KEEPALIVE mud_FlowAxis_READING() {
		return mud::READING;
	}
	mud::FlowAxis EMSCRIPTEN_KEEPALIVE mud_FlowAxis_PARAGRAPH() {
		return mud::PARAGRAPH;
	}
	mud::FlowAxis EMSCRIPTEN_KEEPALIVE mud_FlowAxis_PARALLEL() {
		return mud::PARALLEL;
	}
	mud::FlowAxis EMSCRIPTEN_KEEPALIVE mud_FlowAxis_ORTHOGONAL() {
		return mud::ORTHOGONAL;
	}
	mud::FlowAxis EMSCRIPTEN_KEEPALIVE mud_FlowAxis_AXIS_NONE() {
		return mud::AXIS_NONE;
	}
	// LayoutSolver
	mud::LayoutSolver EMSCRIPTEN_KEEPALIVE mud_LayoutSolver_FRAME_SOLVER() {
		return mud::FRAME_SOLVER;
	}
	mud::LayoutSolver EMSCRIPTEN_KEEPALIVE mud_LayoutSolver_ROW_SOLVER() {
		return mud::ROW_SOLVER;
	}
	mud::LayoutSolver EMSCRIPTEN_KEEPALIVE mud_LayoutSolver_GRID_SOLVER() {
		return mud::GRID_SOLVER;
	}
	mud::LayoutSolver EMSCRIPTEN_KEEPALIVE mud_LayoutSolver_TABLE_SOLVER() {
		return mud::TABLE_SOLVER;
	}
	// Opacity
	mud::Opacity EMSCRIPTEN_KEEPALIVE mud_Opacity_OPAQUE() {
		return mud::OPAQUE;
	}
	mud::Opacity EMSCRIPTEN_KEEPALIVE mud_Opacity_CLEAR() {
		return mud::CLEAR;
	}
	mud::Opacity EMSCRIPTEN_KEEPALIVE mud_Opacity_HOLLOW() {
		return mud::HOLLOW;
	}
	// Pivot
	mud::Pivot EMSCRIPTEN_KEEPALIVE mud_Pivot_FORWARD() {
		return mud::FORWARD;
	}
	mud::Pivot EMSCRIPTEN_KEEPALIVE mud_Pivot_REVERSE() {
		return mud::REVERSE;
	}
	// PopupFlags
	mud::ui::PopupFlags EMSCRIPTEN_KEEPALIVE mud_ui_PopupFlags_None() {
		return mud::ui::PopupFlags::None;
	}
	mud::ui::PopupFlags EMSCRIPTEN_KEEPALIVE mud_ui_PopupFlags_Modal() {
		return mud::ui::PopupFlags::Modal;
	}
	mud::ui::PopupFlags EMSCRIPTEN_KEEPALIVE mud_ui_PopupFlags_Clamp() {
		return mud::ui::PopupFlags::Clamp;
	}
	mud::ui::PopupFlags EMSCRIPTEN_KEEPALIVE mud_ui_PopupFlags_AutoClose() {
		return mud::ui::PopupFlags::AutoClose;
	}
	mud::ui::PopupFlags EMSCRIPTEN_KEEPALIVE mud_ui_PopupFlags_AutoModal() {
		return mud::ui::PopupFlags::AutoModal;
	}
	// Sizing
	mud::Sizing EMSCRIPTEN_KEEPALIVE mud_Sizing_FIXED() {
		return mud::FIXED;
	}
	mud::Sizing EMSCRIPTEN_KEEPALIVE mud_Sizing_SHRINK() {
		return mud::SHRINK;
	}
	mud::Sizing EMSCRIPTEN_KEEPALIVE mud_Sizing_WRAP() {
		return mud::WRAP;
	}
	mud::Sizing EMSCRIPTEN_KEEPALIVE mud_Sizing_EXPAND() {
		return mud::EXPAND;
	}
	// SpacePreset
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_SHEET() {
		return mud::SHEET;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_FLEX() {
		return mud::FLEX;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_ITEM() {
		return mud::ITEM;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_UNIT() {
		return mud::UNIT;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_BLOCK() {
		return mud::BLOCK;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_LINE() {
		return mud::LINE;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_STACK() {
		return mud::STACK;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_DIV() {
		return mud::DIV;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_SPACER() {
		return mud::SPACER;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_BOARD() {
		return mud::BOARD;
	}
	mud::SpacePreset EMSCRIPTEN_KEEPALIVE mud_SpacePreset_LAYOUT() {
		return mud::LAYOUT;
	}
	// WidgetState
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_NOSTATE() {
		return mud::NOSTATE;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_CREATED() {
		return mud::CREATED;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_HOVERED() {
		return mud::HOVERED;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_PRESSED() {
		return mud::PRESSED;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_ACTIVATED() {
		return mud::ACTIVATED;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_ACTIVE() {
		return mud::ACTIVE;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_SELECTED() {
		return mud::SELECTED;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_DISABLED() {
		return mud::DISABLED;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_DRAGGED() {
		return mud::DRAGGED;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_FOCUSED() {
		return mud::FOCUSED;
	}
	mud::WidgetState EMSCRIPTEN_KEEPALIVE mud_WidgetState_CLOSED() {
		return mud::CLOSED;
	}
	// WindowState
	mud::WindowState EMSCRIPTEN_KEEPALIVE mud_WindowState_WINDOW_NOSTATE() {
		return mud::WINDOW_NOSTATE;
	}
	mud::WindowState EMSCRIPTEN_KEEPALIVE mud_WindowState_WINDOW_HEADER() {
		return mud::WINDOW_HEADER;
	}
	mud::WindowState EMSCRIPTEN_KEEPALIVE mud_WindowState_WINDOW_DOCKABLE() {
		return mud::WINDOW_DOCKABLE;
	}
	mud::WindowState EMSCRIPTEN_KEEPALIVE mud_WindowState_WINDOW_CLOSABLE() {
		return mud::WINDOW_CLOSABLE;
	}
	mud::WindowState EMSCRIPTEN_KEEPALIVE mud_WindowState_WINDOW_MOVABLE() {
		return mud::WINDOW_MOVABLE;
	}
	mud::WindowState EMSCRIPTEN_KEEPALIVE mud_WindowState_WINDOW_SIZABLE() {
		return mud::WINDOW_SIZABLE;
	}
	mud::WindowState EMSCRIPTEN_KEEPALIVE mud_WindowState_WINDOW_DEFAULT() {
		return mud::WINDOW_DEFAULT;
	}
	
}


