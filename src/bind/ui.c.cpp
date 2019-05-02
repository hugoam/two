#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Space
	two::Type* DECL two_Space__type() {
		return &two::type<two::Space>();
	}
	two::Space* DECL two_Space__construct_0() {
		return new two::Space();
	}
	two::FlowAxis DECL two_Space__get_direction(two::Space* self) {
		return self->direction;
	}
	void DECL two_Space__set_direction(two::Space* self, two::FlowAxis value) {
		self->direction = value;
	}
	two::Sizing DECL two_Space__get_sizingLength(two::Space* self) {
		return self->sizingLength;
	}
	void DECL two_Space__set_sizingLength(two::Space* self, two::Sizing value) {
		self->sizingLength = value;
	}
	two::Sizing DECL two_Space__get_sizingDepth(two::Space* self) {
		return self->sizingDepth;
	}
	void DECL two_Space__set_sizingDepth(two::Space* self, two::Sizing value) {
		self->sizingDepth = value;
	}
	void DECL two_Space__destroy(two::Space* self) {
		delete self;
	}
	// v2<size_t>
	two::Type* DECL two_v2_size_t__type() {
		return &two::type<two::v2<size_t>>();
	}
	two::v2<size_t>* DECL two_v2_size_t__construct_0() {
		return new two::v2<size_t>();
	}
	two::v2<size_t>* DECL two_v2_size_t__construct_1(size_t v) {
		return new two::v2<size_t>(v);
	}
	two::v2<size_t>* DECL two_v2_size_t__construct_2(size_t x, size_t y) {
		return new two::v2<size_t>(x, y);
	}
	size_t DECL two_v2_size_t__get_x(two::v2<size_t>* self) {
		return self->x;
	}
	void DECL two_v2_size_t__set_x(two::v2<size_t>* self, size_t value) {
		self->x = value;
	}
	size_t DECL two_v2_size_t__get_y(two::v2<size_t>* self) {
		return self->y;
	}
	void DECL two_v2_size_t__set_y(two::v2<size_t>* self, size_t value) {
		self->y = value;
	}
	void DECL two_v2_size_t__destroy(two::v2<size_t>* self) {
		delete self;
	}
	// v2<two::AutoLayout>
	two::Type* DECL two_v2_two_AutoLayout__type() {
		return &two::type<two::v2<two::AutoLayout>>();
	}
	two::v2<two::AutoLayout>* DECL two_v2_two_AutoLayout__construct_0() {
		return new two::v2<two::AutoLayout>();
	}
	two::v2<two::AutoLayout>* DECL two_v2_two_AutoLayout__construct_1(two::AutoLayout v) {
		return new two::v2<two::AutoLayout>(v);
	}
	two::v2<two::AutoLayout>* DECL two_v2_two_AutoLayout__construct_2(two::AutoLayout x, two::AutoLayout y) {
		return new two::v2<two::AutoLayout>(x, y);
	}
	two::AutoLayout DECL two_v2_two_AutoLayout__get_x(two::v2<two::AutoLayout>* self) {
		return self->x;
	}
	void DECL two_v2_two_AutoLayout__set_x(two::v2<two::AutoLayout>* self, two::AutoLayout value) {
		self->x = value;
	}
	two::AutoLayout DECL two_v2_two_AutoLayout__get_y(two::v2<two::AutoLayout>* self) {
		return self->y;
	}
	void DECL two_v2_two_AutoLayout__set_y(two::v2<two::AutoLayout>* self, two::AutoLayout value) {
		self->y = value;
	}
	void DECL two_v2_two_AutoLayout__destroy(two::v2<two::AutoLayout>* self) {
		delete self;
	}
	// v2<two::Sizing>
	two::Type* DECL two_v2_two_Sizing__type() {
		return &two::type<two::v2<two::Sizing>>();
	}
	two::v2<two::Sizing>* DECL two_v2_two_Sizing__construct_0() {
		return new two::v2<two::Sizing>();
	}
	two::v2<two::Sizing>* DECL two_v2_two_Sizing__construct_1(two::Sizing v) {
		return new two::v2<two::Sizing>(v);
	}
	two::v2<two::Sizing>* DECL two_v2_two_Sizing__construct_2(two::Sizing x, two::Sizing y) {
		return new two::v2<two::Sizing>(x, y);
	}
	two::Sizing DECL two_v2_two_Sizing__get_x(two::v2<two::Sizing>* self) {
		return self->x;
	}
	void DECL two_v2_two_Sizing__set_x(two::v2<two::Sizing>* self, two::Sizing value) {
		self->x = value;
	}
	two::Sizing DECL two_v2_two_Sizing__get_y(two::v2<two::Sizing>* self) {
		return self->y;
	}
	void DECL two_v2_two_Sizing__set_y(two::v2<two::Sizing>* self, two::Sizing value) {
		self->y = value;
	}
	void DECL two_v2_two_Sizing__destroy(two::v2<two::Sizing>* self) {
		delete self;
	}
	// v2<two::Align>
	two::Type* DECL two_v2_two_Align__type() {
		return &two::type<two::v2<two::Align>>();
	}
	two::v2<two::Align>* DECL two_v2_two_Align__construct_0() {
		return new two::v2<two::Align>();
	}
	two::v2<two::Align>* DECL two_v2_two_Align__construct_1(two::Align v) {
		return new two::v2<two::Align>(v);
	}
	two::v2<two::Align>* DECL two_v2_two_Align__construct_2(two::Align x, two::Align y) {
		return new two::v2<two::Align>(x, y);
	}
	two::Align DECL two_v2_two_Align__get_x(two::v2<two::Align>* self) {
		return self->x;
	}
	void DECL two_v2_two_Align__set_x(two::v2<two::Align>* self, two::Align value) {
		self->x = value;
	}
	two::Align DECL two_v2_two_Align__get_y(two::v2<two::Align>* self) {
		return self->y;
	}
	void DECL two_v2_two_Align__set_y(two::v2<two::Align>* self, two::Align value) {
		self->y = value;
	}
	void DECL two_v2_two_Align__destroy(two::v2<two::Align>* self) {
		delete self;
	}
	// v2<two::Pivot>
	two::Type* DECL two_v2_two_Pivot__type() {
		return &two::type<two::v2<two::Pivot>>();
	}
	two::v2<two::Pivot>* DECL two_v2_two_Pivot__construct_0() {
		return new two::v2<two::Pivot>();
	}
	two::v2<two::Pivot>* DECL two_v2_two_Pivot__construct_1(two::Pivot v) {
		return new two::v2<two::Pivot>(v);
	}
	two::v2<two::Pivot>* DECL two_v2_two_Pivot__construct_2(two::Pivot x, two::Pivot y) {
		return new two::v2<two::Pivot>(x, y);
	}
	two::Pivot DECL two_v2_two_Pivot__get_x(two::v2<two::Pivot>* self) {
		return self->x;
	}
	void DECL two_v2_two_Pivot__set_x(two::v2<two::Pivot>* self, two::Pivot value) {
		self->x = value;
	}
	two::Pivot DECL two_v2_two_Pivot__get_y(two::v2<two::Pivot>* self) {
		return self->y;
	}
	void DECL two_v2_two_Pivot__set_y(two::v2<two::Pivot>* self, two::Pivot value) {
		self->y = value;
	}
	void DECL two_v2_two_Pivot__destroy(two::v2<two::Pivot>* self) {
		delete self;
	}
	// ImageSkin
	two::Type* DECL two_ImageSkin__type() {
		return &two::type<two::ImageSkin>();
	}
	two::ImageSkin* DECL two_ImageSkin__construct_5(two::Image* image, int left, int top, int right, int bottom) {
		return new two::ImageSkin(*image, left, top, right, bottom);
	}
	two::ImageSkin* DECL two_ImageSkin__construct_6(two::Image* image, int left, int top, int right, int bottom, int margin) {
		return new two::ImageSkin(*image, left, top, right, bottom, margin);
	}
	two::ImageSkin* DECL two_ImageSkin__construct_7(two::Image* image, int left, int top, int right, int bottom, int margin, two::Axis stretch) {
		return new two::ImageSkin(*image, left, top, right, bottom, margin, stretch);
	}
	two::Image* DECL two_ImageSkin__get_d_image(two::ImageSkin* self) {
		return self->d_image;
	}
	void DECL two_ImageSkin__set_d_image(two::ImageSkin* self, two::Image* value) {
		self->d_image = value;
	}
	int DECL two_ImageSkin__get_d_left(two::ImageSkin* self) {
		return self->d_left;
	}
	void DECL two_ImageSkin__set_d_left(two::ImageSkin* self, int value) {
		self->d_left = value;
	}
	int DECL two_ImageSkin__get_d_top(two::ImageSkin* self) {
		return self->d_top;
	}
	void DECL two_ImageSkin__set_d_top(two::ImageSkin* self, int value) {
		self->d_top = value;
	}
	int DECL two_ImageSkin__get_d_right(two::ImageSkin* self) {
		return self->d_right;
	}
	void DECL two_ImageSkin__set_d_right(two::ImageSkin* self, int value) {
		self->d_right = value;
	}
	int DECL two_ImageSkin__get_d_bottom(two::ImageSkin* self) {
		return self->d_bottom;
	}
	void DECL two_ImageSkin__set_d_bottom(two::ImageSkin* self, int value) {
		self->d_bottom = value;
	}
	int DECL two_ImageSkin__get_margin(two::ImageSkin* self) {
		return self->m_margin;
	}
	void DECL two_ImageSkin__set_margin(two::ImageSkin* self, int value) {
		self->m_margin = value;
	}
	two::Axis DECL two_ImageSkin__get_d_stretch(two::ImageSkin* self) {
		return self->d_stretch;
	}
	void DECL two_ImageSkin__set_d_stretch(two::ImageSkin* self, two::Axis value) {
		self->d_stretch = value;
	}
	void DECL two_ImageSkin__destroy(two::ImageSkin* self) {
		delete self;
	}
	// Shadow
	two::Type* DECL two_Shadow__type() {
		return &two::type<two::Shadow>();
	}
	two::Shadow* DECL two_Shadow__construct_0() {
		return new two::Shadow();
	}
	two::Shadow* DECL two_Shadow__construct_4(float xpos, float ypos, float blur, float spread) {
		return new two::Shadow(xpos, ypos, blur, spread);
	}
	two::Shadow* DECL two_Shadow__construct_5(float xpos, float ypos, float blur, float spread, two::Colour* colour) {
		return new two::Shadow(xpos, ypos, blur, spread, *colour);
	}
	float DECL two_Shadow__get_d_xpos(two::Shadow* self) {
		return self->d_xpos;
	}
	void DECL two_Shadow__set_d_xpos(two::Shadow* self, float value) {
		self->d_xpos = value;
	}
	float DECL two_Shadow__get_d_ypos(two::Shadow* self) {
		return self->d_ypos;
	}
	void DECL two_Shadow__set_d_ypos(two::Shadow* self, float value) {
		self->d_ypos = value;
	}
	float DECL two_Shadow__get_d_blur(two::Shadow* self) {
		return self->d_blur;
	}
	void DECL two_Shadow__set_d_blur(two::Shadow* self, float value) {
		self->d_blur = value;
	}
	float DECL two_Shadow__get_d_spread(two::Shadow* self) {
		return self->d_spread;
	}
	void DECL two_Shadow__set_d_spread(two::Shadow* self, float value) {
		self->d_spread = value;
	}
	two::Colour* DECL two_Shadow__get_d_colour(two::Shadow* self) {
		return &self->d_colour;
	}
	void DECL two_Shadow__set_d_colour(two::Shadow* self, two::Colour* value) {
		self->d_colour = *value;
	}
	void DECL two_Shadow__destroy(two::Shadow* self) {
		delete self;
	}
	// Paint
	two::Type* DECL two_Paint__type() {
		return &two::type<two::Paint>();
	}
	two::Paint* DECL two_Paint__construct_0() {
		return new two::Paint();
	}
	two::Colour* DECL two_Paint__get_fill_colour(two::Paint* self) {
		return &self->m_fill_colour;
	}
	void DECL two_Paint__set_fill_colour(two::Paint* self, two::Colour* value) {
		self->m_fill_colour = *value;
	}
	two::Colour* DECL two_Paint__get_stroke_colour(two::Paint* self) {
		return &self->m_stroke_colour;
	}
	void DECL two_Paint__set_stroke_colour(two::Paint* self, two::Colour* value) {
		self->m_stroke_colour = *value;
	}
	float DECL two_Paint__get_stroke_width(two::Paint* self) {
		return self->m_stroke_width;
	}
	void DECL two_Paint__set_stroke_width(two::Paint* self, float value) {
		self->m_stroke_width = value;
	}
	void DECL two_Paint__destroy(two::Paint* self) {
		delete self;
	}
	// TextPaint
	two::Type* DECL two_TextPaint__type() {
		return &two::type<two::TextPaint>();
	}
	two::TextPaint* DECL two_TextPaint__construct_0() {
		return new two::TextPaint();
	}
	const char* DECL two_TextPaint__get_font(two::TextPaint* self) {
		return self->m_font;
	}
	void DECL two_TextPaint__set_font(two::TextPaint* self, const char* value) {
		self->m_font = value;
	}
	two::Colour* DECL two_TextPaint__get_colour(two::TextPaint* self) {
		return &self->m_colour;
	}
	void DECL two_TextPaint__set_colour(two::TextPaint* self, two::Colour* value) {
		self->m_colour = *value;
	}
	float DECL two_TextPaint__get_size(two::TextPaint* self) {
		return self->m_size;
	}
	void DECL two_TextPaint__set_size(two::TextPaint* self, float value) {
		self->m_size = value;
	}
	two::v2<two::Align>* DECL two_TextPaint__get_align(two::TextPaint* self) {
		return &self->m_align;
	}
	void DECL two_TextPaint__set_align(two::TextPaint* self, two::v2<two::Align>* value) {
		self->m_align = *value;
	}
	bool DECL two_TextPaint__get_text_break(two::TextPaint* self) {
		return self->m_text_break;
	}
	void DECL two_TextPaint__set_text_break(two::TextPaint* self, bool value) {
		self->m_text_break = value;
	}
	bool DECL two_TextPaint__get_text_wrap(two::TextPaint* self) {
		return self->m_text_wrap;
	}
	void DECL two_TextPaint__set_text_wrap(two::TextPaint* self, bool value) {
		self->m_text_wrap = value;
	}
	void DECL two_TextPaint__destroy(two::TextPaint* self) {
		delete self;
	}
	// Gradient
	two::Type* DECL two_Gradient__type() {
		return &two::type<two::Gradient>();
	}
	two::Gradient* DECL two_Gradient__construct_0() {
		return new two::Gradient();
	}
	two::Colour* DECL two_Gradient__get_start(two::Gradient* self) {
		return &self->m_start;
	}
	void DECL two_Gradient__set_start(two::Gradient* self, two::Colour* value) {
		self->m_start = *value;
	}
	two::Colour* DECL two_Gradient__get_end(two::Gradient* self) {
		return &self->m_end;
	}
	void DECL two_Gradient__set_end(two::Gradient* self, two::Colour* value) {
		self->m_end = *value;
	}
	void DECL two_Gradient__destroy(two::Gradient* self) {
		delete self;
	}
	// InkStyle
	two::Type* DECL two_InkStyle__type() {
		return &two::type<two::InkStyle>();
	}
	two::InkStyle* DECL two_InkStyle__construct_0() {
		return new two::InkStyle();
	}
	two::InkStyle* DECL two_InkStyle__construct_1(const char* name) {
		return new two::InkStyle(name);
	}
	const char* DECL two_InkStyle__get_name(two::InkStyle* self) {
		return self->m_name.c_str();
	}
	void DECL two_InkStyle__set_name(two::InkStyle* self, const char* value) {
		self->m_name = value;
	}
	bool DECL two_InkStyle__get_empty(two::InkStyle* self) {
		return self->m_empty;
	}
	void DECL two_InkStyle__set_empty(two::InkStyle* self, bool value) {
		self->m_empty = value;
	}
	two::Colour* DECL two_InkStyle__get_background_colour(two::InkStyle* self) {
		return &self->m_background_colour;
	}
	void DECL two_InkStyle__set_background_colour(two::InkStyle* self, two::Colour* value) {
		self->m_background_colour = *value;
	}
	two::Colour* DECL two_InkStyle__get_border_colour(two::InkStyle* self) {
		return &self->m_border_colour;
	}
	void DECL two_InkStyle__set_border_colour(two::InkStyle* self, two::Colour* value) {
		self->m_border_colour = *value;
	}
	two::Colour* DECL two_InkStyle__get_image_colour(two::InkStyle* self) {
		return &self->m_image_colour;
	}
	void DECL two_InkStyle__set_image_colour(two::InkStyle* self, two::Colour* value) {
		self->m_image_colour = *value;
	}
	two::Colour* DECL two_InkStyle__get_text_colour(two::InkStyle* self) {
		return &self->m_text_colour;
	}
	void DECL two_InkStyle__set_text_colour(two::InkStyle* self, two::Colour* value) {
		self->m_text_colour = *value;
	}
	const char* DECL two_InkStyle__get_text_font(two::InkStyle* self) {
		return self->m_text_font.c_str();
	}
	void DECL two_InkStyle__set_text_font(two::InkStyle* self, const char* value) {
		self->m_text_font = value;
	}
	float DECL two_InkStyle__get_text_size(two::InkStyle* self) {
		return self->m_text_size;
	}
	void DECL two_InkStyle__set_text_size(two::InkStyle* self, float value) {
		self->m_text_size = value;
	}
	bool DECL two_InkStyle__get_text_break(two::InkStyle* self) {
		return self->m_text_break;
	}
	void DECL two_InkStyle__set_text_break(two::InkStyle* self, bool value) {
		self->m_text_break = value;
	}
	bool DECL two_InkStyle__get_text_wrap(two::InkStyle* self) {
		return self->m_text_wrap;
	}
	void DECL two_InkStyle__set_text_wrap(two::InkStyle* self, bool value) {
		self->m_text_wrap = value;
	}
	two::vec4* DECL two_InkStyle__get_border_width(two::InkStyle* self) {
		return &self->m_border_width;
	}
	void DECL two_InkStyle__set_border_width(two::InkStyle* self, two::vec4* value) {
		self->m_border_width = *value;
	}
	two::vec4* DECL two_InkStyle__get_corner_radius(two::InkStyle* self) {
		return &self->m_corner_radius;
	}
	void DECL two_InkStyle__set_corner_radius(two::InkStyle* self, two::vec4* value) {
		self->m_corner_radius = *value;
	}
	bool DECL two_InkStyle__get_weak_corners(two::InkStyle* self) {
		return self->m_weak_corners;
	}
	void DECL two_InkStyle__set_weak_corners(two::InkStyle* self, bool value) {
		self->m_weak_corners = value;
	}
	two::vec4* DECL two_InkStyle__get_padding(two::InkStyle* self) {
		return &self->m_padding;
	}
	void DECL two_InkStyle__set_padding(two::InkStyle* self, two::vec4* value) {
		self->m_padding = *value;
	}
	two::vec4* DECL two_InkStyle__get_margin(two::InkStyle* self) {
		return &self->m_margin;
	}
	void DECL two_InkStyle__set_margin(two::InkStyle* self, two::vec4* value) {
		self->m_margin = *value;
	}
	two::v2<two::Align>* DECL two_InkStyle__get_align(two::InkStyle* self) {
		return &self->m_align;
	}
	void DECL two_InkStyle__set_align(two::InkStyle* self, two::v2<two::Align>* value) {
		self->m_align = *value;
	}
	two::vec2* DECL two_InkStyle__get_linear_gradient(two::InkStyle* self) {
		return &self->m_linear_gradient;
	}
	void DECL two_InkStyle__set_linear_gradient(two::InkStyle* self, two::vec2* value) {
		self->m_linear_gradient = *value;
	}
	two::Axis DECL two_InkStyle__get_linear_gradient_dim(two::InkStyle* self) {
		return self->m_linear_gradient_dim;
	}
	void DECL two_InkStyle__set_linear_gradient_dim(two::InkStyle* self, two::Axis value) {
		self->m_linear_gradient_dim = value;
	}
	two::v2<bool>* DECL two_InkStyle__get_stretch(two::InkStyle* self) {
		return &self->m_stretch;
	}
	void DECL two_InkStyle__set_stretch(two::InkStyle* self, two::v2<bool>* value) {
		self->m_stretch = *value;
	}
	two::Image* DECL two_InkStyle__get_image(two::InkStyle* self) {
		return self->m_image;
	}
	void DECL two_InkStyle__set_image(two::InkStyle* self, two::Image* value) {
		self->m_image = value;
	}
	two::Image* DECL two_InkStyle__get_overlay(two::InkStyle* self) {
		return self->m_overlay;
	}
	void DECL two_InkStyle__set_overlay(two::InkStyle* self, two::Image* value) {
		self->m_overlay = value;
	}
	two::Image* DECL two_InkStyle__get_tile(two::InkStyle* self) {
		return self->m_tile;
	}
	void DECL two_InkStyle__set_tile(two::InkStyle* self, two::Image* value) {
		self->m_tile = value;
	}
	two::ImageSkin* DECL two_InkStyle__get_image_skin(two::InkStyle* self) {
		return &self->m_image_skin;
	}
	void DECL two_InkStyle__set_image_skin(two::InkStyle* self, two::ImageSkin* value) {
		self->m_image_skin = *value;
	}
	two::Shadow* DECL two_InkStyle__get_shadow(two::InkStyle* self) {
		return &self->m_shadow;
	}
	void DECL two_InkStyle__set_shadow(two::InkStyle* self, two::Shadow* value) {
		self->m_shadow = *value;
	}
	two::Colour* DECL two_InkStyle__get_shadow_colour(two::InkStyle* self) {
		return &self->m_shadow_colour;
	}
	void DECL two_InkStyle__set_shadow_colour(two::InkStyle* self, two::Colour* value) {
		self->m_shadow_colour = *value;
	}
	two::Style* DECL two_InkStyle__get_hover_cursor(two::InkStyle* self) {
		return self->m_hover_cursor;
	}
	void DECL two_InkStyle__set_hover_cursor(two::InkStyle* self, two::Style* value) {
		self->m_hover_cursor = value;
	}
	void DECL two_InkStyle__destroy(two::InkStyle* self) {
		delete self;
	}
	// Layout
	two::Type* DECL two_Layout__type() {
		return &two::type<two::Layout>();
	}
	two::Layout* DECL two_Layout__construct_0() {
		return new two::Layout();
	}
	two::Layout* DECL two_Layout__construct_1(const char* name) {
		return new two::Layout(name);
	}
	const char* DECL two_Layout__get_name(two::Layout* self) {
		return self->m_name.c_str();
	}
	void DECL two_Layout__set_name(two::Layout* self, const char* value) {
		self->m_name = value;
	}
	two::Solver DECL two_Layout__get_solver(two::Layout* self) {
		return self->m_solver;
	}
	void DECL two_Layout__set_solver(two::Layout* self, two::Solver value) {
		self->m_solver = value;
	}
	two::v2<two::AutoLayout>* DECL two_Layout__get_layout(two::Layout* self) {
		return &self->m_layout;
	}
	void DECL two_Layout__set_layout(two::Layout* self, two::v2<two::AutoLayout>* value) {
		self->m_layout = *value;
	}
	two::LayoutFlow DECL two_Layout__get_flow(two::Layout* self) {
		return self->m_flow;
	}
	void DECL two_Layout__set_flow(two::Layout* self, two::LayoutFlow value) {
		self->m_flow = value;
	}
	two::Space* DECL two_Layout__get_space(two::Layout* self) {
		return &self->m_space;
	}
	void DECL two_Layout__set_space(two::Layout* self, two::Space* value) {
		self->m_space = *value;
	}
	two::Clip DECL two_Layout__get_clipping(two::Layout* self) {
		return self->m_clipping;
	}
	void DECL two_Layout__set_clipping(two::Layout* self, two::Clip value) {
		self->m_clipping = value;
	}
	two::Opacity DECL two_Layout__get_opacity(two::Layout* self) {
		return self->m_opacity;
	}
	void DECL two_Layout__set_opacity(two::Layout* self, two::Opacity value) {
		self->m_opacity = value;
	}
	two::v2<two::Align>* DECL two_Layout__get_align(two::Layout* self) {
		return &self->m_align;
	}
	void DECL two_Layout__set_align(two::Layout* self, two::v2<two::Align>* value) {
		self->m_align = *value;
	}
	two::vec2* DECL two_Layout__get_span(two::Layout* self) {
		return &self->m_span;
	}
	void DECL two_Layout__set_span(two::Layout* self, two::vec2* value) {
		self->m_span = *value;
	}
	two::vec2* DECL two_Layout__get_size(two::Layout* self) {
		return &self->m_size;
	}
	void DECL two_Layout__set_size(two::Layout* self, two::vec2* value) {
		self->m_size = *value;
	}
	two::vec4* DECL two_Layout__get_padding(two::Layout* self) {
		return &self->m_padding;
	}
	void DECL two_Layout__set_padding(two::Layout* self, two::vec4* value) {
		self->m_padding = *value;
	}
	two::vec2* DECL two_Layout__get_margin(two::Layout* self) {
		return &self->m_margin;
	}
	void DECL two_Layout__set_margin(two::Layout* self, two::vec2* value) {
		self->m_margin = *value;
	}
	two::vec2* DECL two_Layout__get_spacing(two::Layout* self) {
		return &self->m_spacing;
	}
	void DECL two_Layout__set_spacing(two::Layout* self, two::vec2* value) {
		self->m_spacing = *value;
	}
	two::v2<two::Pivot>* DECL two_Layout__get_pivot(two::Layout* self) {
		return &self->m_pivot;
	}
	void DECL two_Layout__set_pivot(two::Layout* self, two::v2<two::Pivot>* value) {
		self->m_pivot = *value;
	}
	int DECL two_Layout__get_zorder(two::Layout* self) {
		return self->m_zorder;
	}
	void DECL two_Layout__set_zorder(two::Layout* self, int value) {
		self->m_zorder = value;
	}
	bool DECL two_Layout__get_no_grid(two::Layout* self) {
		return self->m_no_grid;
	}
	void DECL two_Layout__set_no_grid(two::Layout* self, bool value) {
		self->m_no_grid = value;
	}
	float* DECL two_Layout__get_table_division(two::Layout* self) {
		return (float*)self->m_table_division.data();
	}
	size_t DECL two_Layout__get_updated(two::Layout* self) {
		return self->m_updated;
	}
	void DECL two_Layout__set_updated(two::Layout* self, size_t value) {
		self->m_updated = value;
	}
	void DECL two_Layout__destroy(two::Layout* self) {
		delete self;
	}
	// Subskin
	two::Type* DECL two_Subskin__type() {
		return &two::type<two::Subskin>();
	}
	two::Subskin* DECL two_Subskin__construct_0() {
		return new two::Subskin();
	}
	two::InkStyle* DECL two_Subskin__get_skin(two::Subskin* self) {
		return &self->skin;
	}
	void DECL two_Subskin__set_skin(two::Subskin* self, two::InkStyle* value) {
		self->skin = *value;
	}
	two::WidgetState DECL two_Subskin__get_state(two::Subskin* self) {
		return self->state;
	}
	void DECL two_Subskin__set_state(two::Subskin* self, two::WidgetState value) {
		self->state = value;
	}
	void DECL two_Subskin__destroy(two::Subskin* self) {
		delete self;
	}
	// Style
	two::Type* DECL two_Style__type() {
		return &two::type<two::Style>();
	}
	two::Style* DECL two_Style__get_base(two::Style* self) {
		return self->m_base;
	}
	void DECL two_Style__set_base(two::Style* self, two::Style* value) {
		self->m_base = value;
	}
	const char* DECL two_Style__get_name(two::Style* self) {
		return self->m_name.c_str();
	}
	void DECL two_Style__set_name(two::Style* self, const char* value) {
		self->m_name = value;
	}
	two::Layout* DECL two_Style__get_layout(two::Style* self) {
		return &self->m_layout;
	}
	void DECL two_Style__set_layout(two::Style* self, two::Layout* value) {
		self->m_layout = *value;
	}
	two::InkStyle* DECL two_Style__get_skin(two::Style* self) {
		return &self->m_skin;
	}
	void DECL two_Style__set_skin(two::Style* self, two::InkStyle* value) {
		self->m_skin = *value;
	}
	void DECL two_Style__destroy(two::Style* self) {
		delete self;
	}
	// UiRect
	two::Type* DECL two_UiRect__type() {
		return &two::type<two::UiRect>();
	}
	two::UiRect* DECL two_UiRect__construct_0() {
		return new two::UiRect();
	}
	two::vec2* DECL two_UiRect__get_position(two::UiRect* self) {
		return &self->m_position;
	}
	void DECL two_UiRect__set_position(two::UiRect* self, two::vec2* value) {
		self->m_position = *value;
	}
	two::vec2* DECL two_UiRect__get_size(two::UiRect* self) {
		return &self->m_size;
	}
	void DECL two_UiRect__set_size(two::UiRect* self, two::vec2* value) {
		self->m_size = *value;
	}
	two::vec2* DECL two_UiRect__get_content(two::UiRect* self) {
		return &self->m_content;
	}
	void DECL two_UiRect__set_content(two::UiRect* self, two::vec2* value) {
		self->m_content = *value;
	}
	two::vec2* DECL two_UiRect__get_span(two::UiRect* self) {
		return &self->m_span;
	}
	void DECL two_UiRect__set_span(two::UiRect* self, two::vec2* value) {
		self->m_span = *value;
	}
	float DECL two_UiRect__get_scale(two::UiRect* self) {
		return self->m_scale;
	}
	void DECL two_UiRect__set_scale(two::UiRect* self, float value) {
		self->m_scale = value;
	}
	void DECL two_UiRect__destroy(two::UiRect* self) {
		delete self;
	}
	// Frame
	two::Type* DECL two_Frame__type() {
		return &two::type<two::Frame>();
	}
	void DECL two_Frame__destroy(two::Frame* self) {
		delete self;
	}
	// Widget
	two::Type* DECL two_Widget__type() {
		return &two::type<two::Widget>();
	}
	bool DECL two_Widget_focused_0(two::Widget* self) {
		return self->focused();
	}
	bool DECL two_Widget_hovered_0(two::Widget* self) {
		return self->hovered();
	}
	bool DECL two_Widget_pressed_0(two::Widget* self) {
		return self->pressed();
	}
	bool DECL two_Widget_activated_0(two::Widget* self) {
		return self->activated();
	}
	bool DECL two_Widget_active_0(two::Widget* self) {
		return self->active();
	}
	bool DECL two_Widget_selected_0(two::Widget* self) {
		return self->selected();
	}
	bool DECL two_Widget_modal_0(two::Widget* self) {
		return self->modal();
	}
	bool DECL two_Widget_closed_0(two::Widget* self) {
		return self->closed();
	}
	two::UiWindow* DECL two_Widget_ui_window_0(two::Widget* self) {
		return &self->ui_window();
	}
	two::Ui* DECL two_Widget_ui_0(two::Widget* self) {
		return &self->ui();
	}
	two::Widget* DECL two_Widget_parent_modal_0(two::Widget* self) {
		return &self->parent_modal();
	}
	void DECL two_Widget_clear_0(two::Widget* self) {
		self->clear();
	}
	void DECL two_Widget_toggle_state_1(two::Widget* self, two::WidgetState state) {
		self->toggle_state(state);
	}
	void DECL two_Widget_disable_state_1(two::Widget* self, two::WidgetState state) {
		self->disable_state(state);
	}
	void DECL two_Widget_set_state_2(two::Widget* self, two::WidgetState state, bool enabled) {
		self->set_state(state, enabled);
	}
	void DECL two_Widget_enable_state_1(two::Widget* self, two::WidgetState state) {
		self->enable_state(state);
	}
	void DECL two_Widget_clear_focus_0(two::Widget* self) {
		self->clear_focus();
	}
	void DECL two_Widget_take_focus_0(two::Widget* self) {
		self->take_focus();
	}
	void DECL two_Widget_yield_focus_0(two::Widget* self) {
		self->yield_focus();
	}
	void DECL two_Widget_take_modal_1(two::Widget* self, uint32_t device_filter) {
		self->take_modal(device_filter);
	}
	void DECL two_Widget_yield_modal_0(two::Widget* self) {
		self->yield_modal();
	}
	two::KeyEvent* DECL two_Widget_key_event_2(two::Widget* self, two::Key code, two::EventType event_type) {
		static two::KeyEvent temp;
		return (temp = self->key_event(code, event_type), &temp);
	}
	two::KeyEvent* DECL two_Widget_key_event_3(two::Widget* self, two::Key code, two::EventType event_type, two::InputMod modifier) {
		static two::KeyEvent temp;
		return (temp = self->key_event(code, event_type, modifier), &temp);
	}
	two::KeyEvent* DECL two_Widget_key_stroke_1(two::Widget* self, two::Key code) {
		static two::KeyEvent temp;
		return (temp = self->key_stroke(code), &temp);
	}
	two::KeyEvent* DECL two_Widget_key_stroke_2(two::Widget* self, two::Key code, two::InputMod modifier) {
		static two::KeyEvent temp;
		return (temp = self->key_stroke(code, modifier), &temp);
	}
	two::KeyEvent* DECL two_Widget_char_stroke_1(two::Widget* self, two::Key code) {
		static two::KeyEvent temp;
		return (temp = self->char_stroke(code), &temp);
	}
	two::KeyEvent* DECL two_Widget_char_stroke_2(two::Widget* self, two::Key code, two::InputMod modifier) {
		static two::KeyEvent temp;
		return (temp = self->char_stroke(code, modifier), &temp);
	}
	two::MouseEvent* DECL two_Widget_mouse_event_2(two::Widget* self, two::DeviceType device, two::EventType event_type) {
		static two::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type), &temp);
	}
	two::MouseEvent* DECL two_Widget_mouse_event_3(two::Widget* self, two::DeviceType device, two::EventType event_type, two::InputMod modifier) {
		static two::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type, modifier), &temp);
	}
	two::MouseEvent* DECL two_Widget_mouse_event_4(two::Widget* self, two::DeviceType device, two::EventType event_type, two::InputMod modifier, bool consume) {
		static two::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type, modifier, consume), &temp);
	}
	two::Frame* DECL two_Widget__get_frame(two::Widget* self) {
		return &self->m_frame;
	}
	two::WidgetState DECL two_Widget__get_state(two::Widget* self) {
		return self->m_state;
	}
	void DECL two_Widget__set_state(two::Widget* self, two::WidgetState value) {
		self->m_state = value;
	}
	uint32_t DECL two_Widget__get_switch(two::Widget* self) {
		return self->m_switch;
	}
	void DECL two_Widget__set_switch(two::Widget* self, uint32_t value) {
		self->m_switch = value;
	}
	uint32_t DECL two_Widget__get_index(two::Widget* self) {
		return self->m_index;
	}
	void DECL two_Widget__set_index(two::Widget* self, uint32_t value) {
		self->m_index = value;
	}
	bool DECL two_Widget__get_open(two::Widget* self) {
		return self->m_open;
	}
	void DECL two_Widget__set_open(two::Widget* self, bool value) {
		self->m_open = value;
	}
	two::Widget* DECL two_Widget__get_body(two::Widget* self) {
		return self->m_body;
	}
	void DECL two_Widget__set_body(two::Widget* self, two::Widget* value) {
		self->m_body = value;
	}
	void DECL two_Widget__destroy(two::Widget* self) {
		delete self;
	}
	// TextCursor
	two::Type* DECL two_TextCursor__type() {
		return &two::type<two::TextCursor>();
	}
	two::TextCursor* DECL two_TextCursor__construct_0() {
		return new two::TextCursor();
	}
	void DECL two_TextCursor__destroy(two::TextCursor* self) {
		delete self;
	}
	// TextSelection
	two::Type* DECL two_TextSelection__type() {
		return &two::type<two::TextSelection>();
	}
	two::TextSelection* DECL two_TextSelection__construct_0() {
		return new two::TextSelection();
	}
	void DECL two_TextSelection__destroy(two::TextSelection* self) {
		delete self;
	}
	// TextMarker
	two::Type* DECL two_TextMarker__type() {
		return &two::type<two::TextMarker>();
	}
	two::TextMarker* DECL two_TextMarker__construct_0() {
		return new two::TextMarker();
	}
	void DECL two_TextMarker__destroy(two::TextMarker* self) {
		delete self;
	}
	// Text
	two::Type* DECL two_Text__type() {
		return &two::type<two::Text>();
	}
	void DECL two_Text__destroy(two::Text* self) {
		delete self;
	}
	// TextEdit
	two::Type* DECL two_TextEdit__type() {
		return &two::type<two::TextEdit>();
	}
	void DECL two_TextEdit__destroy(two::TextEdit* self) {
		delete self;
	}
	// NodeConnection
	two::Type* DECL two_NodeConnection__type() {
		return &two::type<two::NodeConnection>();
	}
	two::NodeConnection* DECL two_NodeConnection__construct_0() {
		return new two::NodeConnection();
	}
	void DECL two_NodeConnection__destroy(two::NodeConnection* self) {
		delete self;
	}
	// Vg
	two::Type* DECL two_Vg__type() {
		return &two::type<two::Vg>();
	}
	void DECL two_Vg__destroy(two::Vg* self) {
		delete self;
	}
	// Clipboard
	two::Type* DECL two_Clipboard__type() {
		return &two::type<two::Clipboard>();
	}
	two::Clipboard* DECL two_Clipboard__construct_0() {
		return new two::Clipboard();
	}
	const char* DECL two_Clipboard__get_text(two::Clipboard* self) {
		return self->m_text.c_str();
	}
	void DECL two_Clipboard__set_text(two::Clipboard* self, const char* value) {
		self->m_text = value;
	}
	bool DECL two_Clipboard__get_line_mode(two::Clipboard* self) {
		return self->m_line_mode;
	}
	void DECL two_Clipboard__set_line_mode(two::Clipboard* self, bool value) {
		self->m_line_mode = value;
	}
	void DECL two_Clipboard__destroy(two::Clipboard* self) {
		delete self;
	}
	// UiWindow
	two::Type* DECL two_UiWindow__type() {
		return &two::type<two::UiWindow>();
	}
	void DECL two_UiWindow_reset_styles_0(two::UiWindow* self) {
		self->reset_styles();
	}
	const char* DECL two_UiWindow__get_resource_path(two::UiWindow* self) {
		return self->m_resource_path.c_str();
	}
	two::Context* DECL two_UiWindow__get_context(two::UiWindow* self) {
		return &self->m_context;
	}
	two::Vg* DECL two_UiWindow__get_vg(two::UiWindow* self) {
		return &self->m_vg;
	}
	two::uvec2* DECL two_UiWindow__get_size(two::UiWindow* self) {
		return &self->m_size;
	}
	void DECL two_UiWindow__set_size(two::UiWindow* self, two::uvec2* value) {
		self->m_size = *value;
	}
	two::Colour* DECL two_UiWindow__get_colour(two::UiWindow* self) {
		return &self->m_colour;
	}
	void DECL two_UiWindow__set_colour(two::UiWindow* self, two::Colour* value) {
		self->m_colour = *value;
	}
	bool DECL two_UiWindow__get_shutdown(two::UiWindow* self) {
		return self->m_shutdown;
	}
	void DECL two_UiWindow__set_shutdown(two::UiWindow* self, bool value) {
		self->m_shutdown = value;
	}
	void DECL two_UiWindow__destroy(two::UiWindow* self) {
		delete self;
	}
	// User
	two::Type* DECL two_User__type() {
		return &two::type<two::User>();
	}
	void DECL two_User__destroy(two::User* self) {
		delete self;
	}
	// Layer
	two::Type* DECL two_Layer__type() {
		return &two::type<two::Layer>();
	}
	void DECL two_Layer__destroy(two::Layer* self) {
		delete self;
	}
	// FrameSolver
	two::Type* DECL two_FrameSolver__type() {
		return &two::type<two::FrameSolver>();
	}
	void DECL two_FrameSolver__destroy(two::FrameSolver* self) {
		delete self;
	}
	// RowSolver
	two::Type* DECL two_RowSolver__type() {
		return &two::type<two::RowSolver>();
	}
	void DECL two_RowSolver__destroy(two::RowSolver* self) {
		delete self;
	}
	// TableSolver
	two::Type* DECL two_TableSolver__type() {
		return &two::type<two::TableSolver>();
	}
	void DECL two_TableSolver__destroy(two::TableSolver* self) {
		delete self;
	}
	// LineSolver
	two::Type* DECL two_LineSolver__type() {
		return &two::type<two::LineSolver>();
	}
	void DECL two_LineSolver__destroy(two::LineSolver* self) {
		delete self;
	}
	// GridSolver
	two::Type* DECL two_GridSolver__type() {
		return &two::type<two::GridSolver>();
	}
	void DECL two_GridSolver__destroy(two::GridSolver* self) {
		delete self;
	}
	// ScrollSheet
	two::Type* DECL two_ScrollSheet__type() {
		return &two::type<two::ScrollSheet>();
	}
	void DECL two_ScrollSheet__destroy(two::ScrollSheet* self) {
		delete self;
	}
	// Sequence
	two::Type* DECL two_ui_Sequence__type() {
		return &two::type<two::ui::Sequence>();
	}
	void DECL two_ui_Sequence__destroy(two::ui::Sequence* self) {
		delete self;
	}
	// Tabber
	two::Type* DECL two_Tabber__type() {
		return &two::type<two::Tabber>();
	}
	void DECL two_Tabber__destroy(two::Tabber* self) {
		delete self;
	}
	// Expandbox
	two::Type* DECL two_Expandbox__type() {
		return &two::type<two::Expandbox>();
	}
	void DECL two_Expandbox__destroy(two::Expandbox* self) {
		delete self;
	}
	// TreeNode
	two::Type* DECL two_TreeNode__type() {
		return &two::type<two::TreeNode>();
	}
	void DECL two_TreeNode__destroy(two::TreeNode* self) {
		delete self;
	}
	// Table
	two::Type* DECL two_Table__type() {
		return &two::type<two::Table>();
	}
	void DECL two_Table__destroy(two::Table* self) {
		delete self;
	}
	// Dock
	two::Type* DECL two_Dock__type() {
		return &two::type<two::Dock>();
	}
	two::Dock* DECL two_Dock__construct_0() {
		return new two::Dock();
	}
	void DECL two_Dock__destroy(two::Dock* self) {
		delete self;
	}
	// Docksystem
	two::Type* DECL two_Docksystem__type() {
		return &two::type<two::Docksystem>();
	}
	void DECL two_Docksystem__destroy(two::Docksystem* self) {
		delete self;
	}
	// Dockable
	two::Type* DECL two_Dockable__type() {
		return &two::type<two::Dockable>();
	}
	void DECL two_Dockable__destroy(two::Dockable* self) {
		delete self;
	}
	// Docker
	two::Type* DECL two_Docker__type() {
		return &two::type<two::Docker>();
	}
	void DECL two_Docker__destroy(two::Docker* self) {
		delete self;
	}
	// Dockspace
	two::Type* DECL two_Dockspace__type() {
		return &two::type<two::Dockspace>();
	}
	void DECL two_Dockspace__destroy(two::Dockspace* self) {
		delete self;
	}
	// Dockbar
	two::Type* DECL two_Dockbar__type() {
		return &two::type<two::Dockbar>();
	}
	void DECL two_Dockbar__destroy(two::Dockbar* self) {
		delete self;
	}
	// NodePlug
	two::Type* DECL two_NodePlug__type() {
		return &two::type<two::NodePlug>();
	}
	void DECL two_NodePlug__destroy(two::NodePlug* self) {
		delete self;
	}
	// Node
	two::Type* DECL two_Node__type() {
		return &two::type<two::Node>();
	}
	void DECL two_Node__destroy(two::Node* self) {
		delete self;
	}
	// CanvasConnect
	two::Type* DECL two_CanvasConnect__type() {
		return &two::type<two::CanvasConnect>();
	}
	two::CanvasConnect* DECL two_CanvasConnect__construct_0() {
		return new two::CanvasConnect();
	}
	void DECL two_CanvasConnect__destroy(two::CanvasConnect* self) {
		delete self;
	}
	// Canvas
	two::Type* DECL two_Canvas__type() {
		return &two::type<two::Canvas>();
	}
	void DECL two_Canvas__destroy(two::Canvas* self) {
		delete self;
	}
	// Ui
	two::Type* DECL two_Ui__type() {
		return &two::type<two::Ui>();
	}
	two::Widget* DECL two_Ui_begin_0(two::Ui* self) {
		return &self->begin();
	}
	void DECL two_Ui_reset_styles_0(two::Ui* self) {
		self->reset_styles();
	}
	void DECL two_Ui__destroy(two::Ui* self) {
		delete self;
	}
	// Window
	two::Type* DECL two_Window__type() {
		return &two::type<two::Window>();
	}
	two::WindowState DECL two_Window__get_window_state(two::Window* self) {
		return self->m_window_state;
	}
	void DECL two_Window__set_window_state(two::Window* self, two::WindowState value) {
		self->m_window_state = value;
	}
	two::Widget* DECL two_Window__get_menu(two::Window* self) {
		return self->m_menu;
	}
	void DECL two_Window__set_menu(two::Window* self, two::Widget* value) {
		self->m_menu = value;
	}
	void DECL two_Window__destroy(two::Window* self) {
		delete self;
	}
	void DECL two_layout_minimal_1(two::UiWindow* ui_window) {
		two::layout_minimal(*ui_window);
	}
	void DECL two_style_minimal_1(two::UiWindow* ui_window) {
		two::style_minimal(*ui_window);
	}
	void DECL two_style_vector_1(two::UiWindow* ui_window) {
		two::style_vector(*ui_window);
	}
	void DECL two_style_blendish_1(two::UiWindow* ui_window) {
		two::style_blendish(*ui_window);
	}
	void DECL two_style_blendish_light_1(two::UiWindow* ui_window) {
		two::style_blendish_light(*ui_window);
	}
	void DECL two_style_blendish_dark_1(two::UiWindow* ui_window) {
		two::style_blendish_dark(*ui_window);
	}
	void DECL two_style_imgui_dark_1(two::UiWindow* ui_window) {
		two::style_imgui_dark(*ui_window);
	}
	void DECL two_style_imgui_light_1(two::UiWindow* ui_window) {
		two::style_imgui_light(*ui_window);
	}
	void DECL two_style_imgui_classic_1(two::UiWindow* ui_window) {
		two::style_imgui_classic(*ui_window);
	}
	two::Widget* DECL two_ui_widget_2(two::Widget* parent, two::Style* style) {
		return &two::ui::widget(*parent, *style);
	}
	two::Widget* DECL two_ui_widget_3(two::Widget* parent, two::Style* style, bool open) {
		return &two::ui::widget(*parent, *style, open);
	}
	two::Widget* DECL two_ui_widget_4(two::Widget* parent, two::Style* style, bool open, two::Axis length) {
		return &two::ui::widget(*parent, *style, open, length);
	}
	two::Widget* DECL two_ui_widget_5(two::Widget* parent, two::Style* style, bool open, two::Axis length, two::v2<size_t>* index) {
		return &two::ui::widget(*parent, *style, open, length, *index);
	}
	two::Widget* DECL two_ui_item_2(two::Widget* parent, two::Style* style) {
		return &two::ui::item(*parent, *style);
	}
	two::Widget* DECL two_ui_item_3(two::Widget* parent, two::Style* style, const char* content) {
		return &two::ui::item(*parent, *style, content);
	}
	two::Widget* DECL two_ui_multi_item_3(two::Widget* parent, two::Style* style, const char** elements, int elements_size) {
		return &two::ui::multi_item(*parent, *style, { (const char**)elements, elements_size / (sizeof(const char*) / sizeof(const char*)) });
	}
	two::Widget* DECL two_ui_multi_item_4(two::Widget* parent, two::Style* style, const char** elements, int elements_size, two::Style* element_style) {
		return &two::ui::multi_item(*parent, *style, { (const char**)elements, elements_size / (sizeof(const char*) / sizeof(const char*)) }, element_style);
	}
	two::Widget* DECL two_ui_spanner_4(two::Widget* parent, two::Style* style, two::Axis dim, float span) {
		return &two::ui::spanner(*parent, *style, dim, span);
	}
	two::Widget* DECL two_ui_spacer_1(two::Widget* parent) {
		return &two::ui::spacer(*parent);
	}
	two::Widget* DECL two_ui_separator_1(two::Widget* parent) {
		return &two::ui::separator(*parent);
	}
	two::Widget* DECL two_ui_icon_2(two::Widget* parent, const char* image) {
		return &two::ui::icon(*parent, image);
	}
	two::Widget* DECL two_ui_label_2(two::Widget* parent, const char* label) {
		return &two::ui::label(*parent, label);
	}
	two::Widget* DECL two_ui_title_2(two::Widget* parent, const char* label) {
		return &two::ui::title(*parent, label);
	}
	two::Widget* DECL two_ui_message_2(two::Widget* parent, const char* label) {
		return &two::ui::message(*parent, label);
	}
	two::Widget* DECL two_ui_text_2(two::Widget* parent, const char* label) {
		return &two::ui::text(*parent, label);
	}
	two::Widget* DECL two_ui_bullet_2(two::Widget* parent, const char* label) {
		return &two::ui::bullet(*parent, label);
	}
	two::Widget* DECL two_ui_selectable_3(two::Widget* parent, const char* label, bool selected) {
		return &two::ui::selectable(*parent, label, selected);
	}
	two::Widget* DECL two_ui_button_1(two::Widget* parent) {
		return &two::ui::button(*parent);
	}
	two::Widget* DECL two_ui_button_2(two::Widget* parent, const char* content) {
		return &two::ui::button(*parent, content);
	}
	two::Widget* DECL two_ui_toggle_2(two::Widget* parent, bool on) {
		return &two::ui::toggle(*parent, on);
	}
	two::Widget* DECL two_ui_toggle_3(two::Widget* parent, bool on, const char* content) {
		return &two::ui::toggle(*parent, on, content);
	}
	two::Widget* DECL two_ui_multi_button_2(two::Widget* parent, const char** elements, int elements_size) {
		return &two::ui::multi_button(*parent, { (const char**)elements, elements_size / (sizeof(const char*) / sizeof(const char*)) });
	}
	two::Widget* DECL two_ui_multi_button_3(two::Widget* parent, const char** elements, int elements_size, two::Style* element_style) {
		return &two::ui::multi_button(*parent, { (const char**)elements, elements_size / (sizeof(const char*) / sizeof(const char*)) }, element_style);
	}
	two::Widget* DECL two_ui_multi_toggle_3(two::Widget* parent, bool on, const char** elements, int elements_size) {
		return &two::ui::multi_toggle(*parent, on, { (const char**)elements, elements_size / (sizeof(const char*) / sizeof(const char*)) });
	}
	two::Widget* DECL two_ui_multi_toggle_4(two::Widget* parent, bool on, const char** elements, int elements_size, two::Style* element_style) {
		return &two::ui::multi_toggle(*parent, on, { (const char**)elements, elements_size / (sizeof(const char*) / sizeof(const char*)) }, element_style);
	}
	bool DECL two_ui_modal_button_4(two::Widget* screen, two::Widget* parent, const char* content, uint32_t mode) {
		return two::ui::modal_button(*screen, *parent, content, mode);
	}
	bool DECL two_ui_modal_multi_button_4(two::Widget* screen, two::Widget* parent, const char** elements, int elements_size, uint32_t mode) {
		return two::ui::modal_multi_button(*screen, *parent, { (const char**)elements, elements_size / (sizeof(const char*) / sizeof(const char*)) }, mode);
	}
	two::Widget* DECL two_ui_checkbox_2(two::Widget* parent, bool on) {
		return &two::ui::checkbox(*parent, on);
	}
	two::Widget* DECL two_ui_fill_bar_2(two::Widget* parent, float percentage) {
		return &two::ui::fill_bar(*parent, percentage);
	}
	two::Widget* DECL two_ui_fill_bar_3(two::Widget* parent, float percentage, two::Axis dim) {
		return &two::ui::fill_bar(*parent, percentage, dim);
	}
	two::Widget* DECL two_ui_image256_3(two::Widget* parent, const char* name, const two::Image256* source) {
		return &two::ui::image256(*parent, name, *source);
	}
	two::Widget* DECL two_ui_image256_4(two::Widget* parent, const char* name, const two::Image256* source, const two::vec2* size) {
		return &two::ui::image256(*parent, name, *source, *size);
	}
	two::Widget* DECL two_ui_radio_choice_3(two::Widget* parent, const char* label, bool active) {
		return &two::ui::radio_choice(*parent, label, active);
	}
	two::Widget* DECL two_ui_radio_button_4(two::Widget* parent, const char* label, uint32_t value, uint32_t index) {
		return &two::ui::radio_button(*parent, label, value, index);
	}
	bool DECL two_ui_radio_switch_3(two::Widget* parent, const char** labels, int labels_size, uint32_t value) {
		return two::ui::radio_switch(*parent, { (const char**)labels, labels_size / (sizeof(const char*) / sizeof(const char*)) }, value);
	}
	bool DECL two_ui_radio_switch_4(two::Widget* parent, const char** labels, int labels_size, uint32_t value, two::Axis dim) {
		return two::ui::radio_switch(*parent, { (const char**)labels, labels_size / (sizeof(const char*) / sizeof(const char*)) }, value, dim);
	}
	bool DECL two_ui_popdown_5(two::Widget* parent, const char** choices, int choices_size, uint32_t value, two::vec2* position, two::ui::PopupFlags flags) {
		return two::ui::popdown(*parent, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value, *position, flags);
	}
	two::Widget* DECL two_ui_dropdown_4(two::Widget* parent, two::Style* style, const char* value, two::ui::PopupFlags flags) {
		return &two::ui::dropdown(*parent, *style, value, flags);
	}
	two::Widget* DECL two_ui_dropdown_5(two::Widget* parent, two::Style* style, const char* value, two::ui::PopupFlags flags, bool no_toggle) {
		return &two::ui::dropdown(*parent, *style, value, flags, no_toggle);
	}
	two::Widget* DECL two_ui_dropdown_6(two::Widget* parent, two::Style* style, const char* value, two::ui::PopupFlags flags, bool no_toggle, two::Style* list_style) {
		return &two::ui::dropdown(*parent, *style, value, flags, no_toggle, list_style);
	}
	bool DECL two_ui_dropdown_input_3(two::Widget* parent, const char** choices, int choices_size, uint32_t value) {
		return two::ui::dropdown_input(*parent, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value);
	}
	bool DECL two_ui_dropdown_input_4(two::Widget* parent, const char** choices, int choices_size, uint32_t value, bool compact) {
		return two::ui::dropdown_input(*parent, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value, compact);
	}
	bool DECL two_ui_typedown_input_3(two::Widget* parent, const char** choices, int choices_size, uint32_t value) {
		return two::ui::typedown_input(*parent, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value);
	}
	two::Widget* DECL two_ui_menu_choice_2(two::Widget* parent, const char* content) {
		return &two::ui::menu_choice(*parent, content);
	}
	two::Widget* DECL two_ui_menu_choice_3(two::Widget* parent, const char* content, const char* shortcut) {
		return &two::ui::menu_choice(*parent, content, shortcut);
	}
	two::Widget* DECL two_ui_menu_option_4(two::Widget* parent, const char* content, const char* shortcut, bool enabled) {
		return &two::ui::menu_option(*parent, content, shortcut, enabled);
	}
	two::Widget* DECL two_ui_menu_2(two::Widget* parent, const char* label) {
		return &two::ui::menu(*parent, label);
	}
	two::Widget* DECL two_ui_menu_3(two::Widget* parent, const char* label, bool submenu) {
		return &two::ui::menu(*parent, label, submenu);
	}
	two::Widget* DECL two_ui_menubar_1(two::Widget* parent) {
		return &two::ui::menubar(*parent);
	}
	two::Widget* DECL two_ui_toolbutton_2(two::Widget* parent, const char* icon) {
		return &two::ui::toolbutton(*parent, icon);
	}
	two::Widget* DECL two_ui_tooldock_1(two::Widget* parent) {
		return &two::ui::tooldock(*parent);
	}
	two::Widget* DECL two_ui_toolbar_1(two::Widget* parent) {
		return &two::ui::toolbar(*parent);
	}
	two::Widget* DECL two_ui_toolbar_2(two::Widget* parent, bool wrap) {
		return &two::ui::toolbar(*parent, wrap);
	}
	two::ScrollSheet* DECL two_ui_select_list_1(two::Widget* parent) {
		return &two::ui::select_list(*parent);
	}
	two::Table* DECL two_ui_columns_2(two::Widget* parent, float* weights, int weights_size) {
		return &two::ui::columns(*parent, { (float*)weights, weights_size / (sizeof(float) / sizeof(float)) });
	}
	two::Table* DECL two_ui_table_3(two::Widget* parent, const char** columns, int columns_size, float* weights, int weights_size) {
		return &two::ui::table(*parent, { (const char**)columns, columns_size / (sizeof(const char*) / sizeof(const char*)) }, { (float*)weights, weights_size / (sizeof(float) / sizeof(float)) });
	}
	two::Widget* DECL two_ui_table_row_1(two::Widget* parent) {
		return &two::ui::table_row(*parent);
	}
	two::Widget* DECL two_ui_table_separator_1(two::Widget* parent) {
		return &two::ui::table_separator(*parent);
	}
	two::Expandbox* DECL two_ui_expandbox_2(two::Widget* parent, const char* name) {
		return &two::ui::expandbox(*parent, name);
	}
	two::Expandbox* DECL two_ui_expandbox_3(two::Widget* parent, const char* name, bool open) {
		return &two::ui::expandbox(*parent, name, open);
	}
	two::TreeNode* DECL two_ui_tree_node_2(two::Widget* parent, const char* name) {
		return &two::ui::tree_node(*parent, name);
	}
	two::TreeNode* DECL two_ui_tree_node_3(two::Widget* parent, const char* name, bool leaf) {
		return &two::ui::tree_node(*parent, name, leaf);
	}
	two::TreeNode* DECL two_ui_tree_node_4(two::Widget* parent, const char* name, bool leaf, bool open) {
		return &two::ui::tree_node(*parent, name, leaf, open);
	}
	two::Widget* DECL two_ui_tree_1(two::Widget* parent) {
		return &two::ui::tree(*parent);
	}
	two::Widget* DECL two_ui_tab_2(two::Tabber* tabber, const char* name) {
		return two::ui::tab(*tabber, name);
	}
	two::Tabber* DECL two_ui_tabber_1(two::Widget* parent) {
		return &two::ui::tabber(*parent);
	}
	two::Widget* DECL two_ui_row_1(two::Widget* parent) {
		return &two::ui::row(*parent);
	}
	two::Widget* DECL two_ui_header_1(two::Widget* parent) {
		return &two::ui::header(*parent);
	}
	two::Widget* DECL two_ui_div_1(two::Widget* parent) {
		return &two::ui::div(*parent);
	}
	two::Widget* DECL two_ui_stack_1(two::Widget* parent) {
		return &two::ui::stack(*parent);
	}
	two::Widget* DECL two_ui_sheet_1(two::Widget* parent) {
		return &two::ui::sheet(*parent);
	}
	two::Widget* DECL two_ui_board_1(two::Widget* parent) {
		return &two::ui::board(*parent);
	}
	two::Widget* DECL two_ui_layout_1(two::Widget* parent) {
		return &two::ui::layout(*parent);
	}
	two::Widget* DECL two_ui_indent_1(two::Widget* parent) {
		return &two::ui::indent(*parent);
	}
	two::Widget* DECL two_ui_screen_1(two::Widget* parent) {
		return &two::ui::screen(*parent);
	}
	two::Widget* DECL two_ui_decal_1(two::Widget* parent) {
		return &two::ui::decal(*parent);
	}
	two::Widget* DECL two_ui_overlay_1(two::Widget* parent) {
		return &two::ui::overlay(*parent);
	}
	two::Widget* DECL two_ui_title_header_2(two::Widget* parent, const char* title) {
		return &two::ui::title_header(*parent, title);
	}
	two::Widget* DECL two_ui_dummy_2(two::Widget* parent, const two::vec2* size) {
		return &two::ui::dummy(*parent, *size);
	}
	two::Widget* DECL two_ui_popup_2(two::Widget* parent, two::ui::PopupFlags flags) {
		return &two::ui::popup(*parent, flags);
	}
	two::Widget* DECL two_ui_popup_3(two::Widget* parent, const two::vec2* size, two::ui::PopupFlags flags) {
		return &two::ui::popup(*parent, *size, flags);
	}
	two::Widget* DECL two_ui_popup_at_2(two::Widget* parent, const two::vec2* position) {
		return &two::ui::popup_at(*parent, *position);
	}
	two::Widget* DECL two_ui_popup_at_3(two::Widget* parent, const two::vec2* position, two::ui::PopupFlags flags) {
		return &two::ui::popup_at(*parent, *position, flags);
	}
	two::Widget* DECL two_ui_modal_1(two::Widget* parent) {
		return &two::ui::modal(*parent);
	}
	two::Widget* DECL two_ui_modal_2(two::Widget* parent, const two::vec2* size) {
		return &two::ui::modal(*parent, *size);
	}
	two::Widget* DECL two_ui_auto_modal_2(two::Widget* parent, uint32_t mode) {
		return &two::ui::auto_modal(*parent, mode);
	}
	two::Widget* DECL two_ui_auto_modal_3(two::Widget* parent, uint32_t mode, const two::vec2* size) {
		return &two::ui::auto_modal(*parent, mode, *size);
	}
	two::Widget* DECL two_ui_context_2(two::Widget* parent, uint32_t mode) {
		return two::ui::context(*parent, mode);
	}
	two::Widget* DECL two_ui_context_3(two::Widget* parent, uint32_t mode, two::ui::PopupFlags flags) {
		return two::ui::context(*parent, mode, flags);
	}
	two::Widget* DECL two_ui_hoverbox_1(two::Widget* parent) {
		return two::ui::hoverbox(*parent);
	}
	two::Widget* DECL two_ui_hoverbox_2(two::Widget* parent, float delay) {
		return two::ui::hoverbox(*parent, delay);
	}
	two::Widget* DECL two_ui_cursor_3(two::Widget* parent, const two::vec2* position, two::Widget* hovered) {
		return &two::ui::cursor(*parent, *position, *hovered);
	}
	two::Widget* DECL two_ui_cursor_4(two::Widget* parent, const two::vec2* position, two::Widget* hovered, bool locked) {
		return &two::ui::cursor(*parent, *position, *hovered, locked);
	}
	two::Widget* DECL two_ui_rectangle_2(two::Widget* parent, const two::vec4* rect) {
		return &two::ui::rectangle(*parent, *rect);
	}
	two::Widget* DECL two_ui_viewport_2(two::Widget* parent, const two::vec4* rect) {
		return &two::ui::viewport(*parent, *rect);
	}
	two::Dockspace* DECL two_ui_dockspace_2(two::Widget* parent, two::Docksystem* docksystem) {
		return &two::ui::dockspace(*parent, *docksystem);
	}
	two::Dockbar* DECL two_ui_dockbar_2(two::Widget* parent, two::Docksystem* docksystem) {
		return &two::ui::dockbar(*parent, *docksystem);
	}
	two::Widget* DECL two_ui_dockitem_3(two::Widget* parent, two::Docksystem* docksystem, two::Dock* dock) {
		return two::ui::dockitem(*parent, *docksystem, *dock);
	}
	bool DECL two_ui_drag_float_2(two::Widget* parent, float value) {
		return two::ui::drag_float(*parent, value);
	}
	bool DECL two_ui_drag_float_3(two::Widget* parent, float value, float step) {
		return two::ui::drag_float(*parent, value, step);
	}
	bool DECL two_ui_float2_input_4(two::Widget* parent, const char** labels, int labels_size, float* vals, int vals_size, two::StatDef<float>* def) {
		return two::ui::float2_input(*parent, { (const char**)labels, labels_size / (sizeof(const char*) / sizeof(const char*)) }, { (float*)vals, vals_size / (sizeof(float) / sizeof(float)) }, *def);
	}
	bool DECL two_ui_float3_input_4(two::Widget* parent, const char** labels, int labels_size, float* vals, int vals_size, two::StatDef<float>* def) {
		return two::ui::float3_input(*parent, { (const char**)labels, labels_size / (sizeof(const char*) / sizeof(const char*)) }, { (float*)vals, vals_size / (sizeof(float) / sizeof(float)) }, *def);
	}
	bool DECL two_ui_float4_input_4(two::Widget* parent, const char** labels, int labels_size, float* vals, int vals_size, two::StatDef<float>* def) {
		return two::ui::float4_input(*parent, { (const char**)labels, labels_size / (sizeof(const char*) / sizeof(const char*)) }, { (float*)vals, vals_size / (sizeof(float) / sizeof(float)) }, *def);
	}
	bool DECL two_ui_float2_slider_5(two::Widget* parent, const char* label, const char** labels, int labels_size, float* vals, int vals_size, two::StatDef<float>* def) {
		return two::ui::float2_slider(*parent, label, { (const char**)labels, labels_size / (sizeof(const char*) / sizeof(const char*)) }, { (float*)vals, vals_size / (sizeof(float) / sizeof(float)) }, *def);
	}
	bool DECL two_ui_float3_slider_5(two::Widget* parent, const char* label, const char** labels, int labels_size, float* vals, int vals_size, two::StatDef<float>* def) {
		return two::ui::float3_slider(*parent, label, { (const char**)labels, labels_size / (sizeof(const char*) / sizeof(const char*)) }, { (float*)vals, vals_size / (sizeof(float) / sizeof(float)) }, *def);
	}
	bool DECL two_ui_float4_slider_5(two::Widget* parent, const char* label, const char** labels, int labels_size, float* vals, int vals_size, two::StatDef<float>* def) {
		return two::ui::float4_slider(*parent, label, { (const char**)labels, labels_size / (sizeof(const char*) / sizeof(const char*)) }, { (float*)vals, vals_size / (sizeof(float) / sizeof(float)) }, *def);
	}
	bool DECL two_ui_vec2_edit_2(two::Widget* parent, two::vec2* vec) {
		return two::ui::vec2_edit(*parent, *vec);
	}
	bool DECL two_ui_vec3_edit_2(two::Widget* parent, two::vec3* vec) {
		return two::ui::vec3_edit(*parent, *vec);
	}
	bool DECL two_ui_quat_edit_2(two::Widget* parent, two::quat* quat) {
		return two::ui::quat_edit(*parent, *quat);
	}
	two::Widget* DECL two_ui_color_display_2(two::Widget* parent, const two::Colour* value) {
		return &two::ui::color_display(*parent, *value);
	}
	bool DECL two_ui_color_edit_2(two::Widget* parent, two::Colour* value) {
		return two::ui::color_edit(*parent, *value);
	}
	bool DECL two_ui_color_edit_simple_2(two::Widget* parent, two::Colour* value) {
		return two::ui::color_edit_simple(*parent, *value);
	}
	bool DECL two_ui_color_toggle_edit_2(two::Widget* parent, two::Colour* value) {
		return two::ui::color_toggle_edit(*parent, *value);
	}
	bool DECL two_ui_curve_graph_2(two::Widget* parent, float* values, int values_size) {
		return two::ui::curve_graph(*parent, { (float*)values, values_size / (sizeof(float) / sizeof(float)) });
	}
	bool DECL two_ui_curve_graph_3(two::Widget* parent, float* values, int values_size, float* points, int points_size) {
		return two::ui::curve_graph(*parent, { (float*)values, values_size / (sizeof(float) / sizeof(float)) }, { (float*)points, points_size / (sizeof(float) / sizeof(float)) });
	}
	bool DECL two_ui_curve_edit_2(two::Widget* parent, float* values, int values_size) {
		return two::ui::curve_edit(*parent, { (float*)values, values_size / (sizeof(float) / sizeof(float)) });
	}
	bool DECL two_ui_curve_edit_3(two::Widget* parent, float* values, int values_size, float* points, int points_size) {
		return two::ui::curve_edit(*parent, { (float*)values, values_size / (sizeof(float) / sizeof(float)) }, { (float*)points, points_size / (sizeof(float) / sizeof(float)) });
	}
	bool DECL two_ui_flag_field_4(two::Widget* parent, const char* name, uint32_t value, uint8_t shift) {
		return two::ui::flag_field(*parent, name, value, shift);
	}
	bool DECL two_ui_flag_field_5(two::Widget* parent, const char* name, uint32_t value, uint8_t shift, bool reverse) {
		return two::ui::flag_field(*parent, name, value, shift, reverse);
	}
	bool DECL two_ui_radio_field_4(two::Widget* parent, const char* name, const char** choices, int choices_size, uint32_t value) {
		return two::ui::radio_field(*parent, name, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value);
	}
	bool DECL two_ui_radio_field_5(two::Widget* parent, const char* name, const char** choices, int choices_size, uint32_t value, two::Axis dim) {
		return two::ui::radio_field(*parent, name, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value, dim);
	}
	bool DECL two_ui_radio_field_6(two::Widget* parent, const char* name, const char** choices, int choices_size, uint32_t value, two::Axis dim, bool reverse) {
		return two::ui::radio_field(*parent, name, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value, dim, reverse);
	}
	bool DECL two_ui_dropdown_field_4(two::Widget* parent, const char* name, const char** choices, int choices_size, uint32_t value) {
		return two::ui::dropdown_field(*parent, name, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value);
	}
	bool DECL two_ui_dropdown_field_5(two::Widget* parent, const char* name, const char** choices, int choices_size, uint32_t value, bool reverse) {
		return two::ui::dropdown_field(*parent, name, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value, reverse);
	}
	bool DECL two_ui_typedown_field_4(two::Widget* parent, const char* name, const char** choices, int choices_size, uint32_t value) {
		return two::ui::typedown_field(*parent, name, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value);
	}
	bool DECL two_ui_typedown_field_5(two::Widget* parent, const char* name, const char** choices, int choices_size, uint32_t value, bool reverse) {
		return two::ui::typedown_field(*parent, name, { (const char**)choices, choices_size / (sizeof(const char*) / sizeof(const char*)) }, value, reverse);
	}
	bool DECL two_ui_color_field_3(two::Widget* parent, const char* name, two::Colour* value) {
		return two::ui::color_field(*parent, name, *value);
	}
	bool DECL two_ui_color_field_4(two::Widget* parent, const char* name, two::Colour* value, bool reverse) {
		return two::ui::color_field(*parent, name, *value, reverse);
	}
	void DECL two_ui_color_display_field_3(two::Widget* parent, const char* name, const two::Colour* value) {
		two::ui::color_display_field(*parent, name, *value);
	}
	void DECL two_ui_color_display_field_4(two::Widget* parent, const char* name, const two::Colour* value, bool reverse) {
		two::ui::color_display_field(*parent, name, *value, reverse);
	}
	bool DECL two_ui_input_bool_2(two::Widget* parent, bool value) {
		return two::ui::input<bool>(*parent, value);
	}
	bool DECL two_ui_input_int_3(two::Widget* parent, int value, two::StatDef<int>* def) {
		return two::ui::input<int>(*parent, value, *def);
	}
	bool DECL two_ui_input_float_3(two::Widget* parent, float value, two::StatDef<float>* def) {
		return two::ui::input<float>(*parent, value, *def);
	}
	bool DECL two_ui_field_bool_3(two::Widget* parent, const char* name, bool value) {
		return two::ui::field<bool>(*parent, name, value);
	}
	bool DECL two_ui_field_bool_4(two::Widget* parent, const char* name, bool value, bool reverse) {
		return two::ui::field<bool>(*parent, name, value, reverse);
	}
	bool DECL two_ui_field_int_4(two::Widget* parent, const char* name, int value, two::StatDef<int>* def) {
		return two::ui::field<int>(*parent, name, value, *def);
	}
	bool DECL two_ui_field_int_5(two::Widget* parent, const char* name, int value, two::StatDef<int>* def, bool reverse) {
		return two::ui::field<int>(*parent, name, value, *def, reverse);
	}
	bool DECL two_ui_field_float_4(two::Widget* parent, const char* name, float value, two::StatDef<float>* def) {
		return two::ui::field<float>(*parent, name, value, *def);
	}
	bool DECL two_ui_field_float_5(two::Widget* parent, const char* name, float value, two::StatDef<float>* def, bool reverse) {
		return two::ui::field<float>(*parent, name, value, *def, reverse);
	}
	two::NodePlug* DECL two_ui_node_input_2(two::Node* node, const char* name) {
		return &two::ui::node_input(*node, name);
	}
	two::NodePlug* DECL two_ui_node_input_3(two::Node* node, const char* name, const char* icon) {
		return &two::ui::node_input(*node, name, icon);
	}
	two::NodePlug* DECL two_ui_node_input_4(two::Node* node, const char* name, const char* icon, const two::Colour* colour) {
		return &two::ui::node_input(*node, name, icon, *colour);
	}
	two::NodePlug* DECL two_ui_node_input_5(two::Node* node, const char* name, const char* icon, const two::Colour* colour, bool active) {
		return &two::ui::node_input(*node, name, icon, *colour, active);
	}
	two::NodePlug* DECL two_ui_node_input_6(two::Node* node, const char* name, const char* icon, const two::Colour* colour, bool active, bool connected) {
		return &two::ui::node_input(*node, name, icon, *colour, active, connected);
	}
	two::NodePlug* DECL two_ui_node_output_2(two::Node* node, const char* name) {
		return &two::ui::node_output(*node, name);
	}
	two::NodePlug* DECL two_ui_node_output_3(two::Node* node, const char* name, const char* icon) {
		return &two::ui::node_output(*node, name, icon);
	}
	two::NodePlug* DECL two_ui_node_output_4(two::Node* node, const char* name, const char* icon, const two::Colour* colour) {
		return &two::ui::node_output(*node, name, icon, *colour);
	}
	two::NodePlug* DECL two_ui_node_output_5(two::Node* node, const char* name, const char* icon, const two::Colour* colour, bool active) {
		return &two::ui::node_output(*node, name, icon, *colour, active);
	}
	two::NodePlug* DECL two_ui_node_output_6(two::Node* node, const char* name, const char* icon, const two::Colour* colour, bool active, bool connected) {
		return &two::ui::node_output(*node, name, icon, *colour, active, connected);
	}
	two::Node* DECL two_ui_node_3(two::Canvas* parent, const char* title, two::vec2* position) {
		return &two::ui::node(*parent, title, *position);
	}
	two::Node* DECL two_ui_node_4(two::Canvas* parent, const char* title, two::vec2* position, int order) {
		return &two::ui::node(*parent, title, *position, order);
	}
	two::Node* DECL two_ui_node_5(two::Canvas* parent, const char* title, two::vec2* position, int order, void* identity, two::Type* identity_type) {
		return &two::ui::node(*parent, title, *position, order, { identity, *identity_type });
	}
	two::Widget* DECL two_ui_node_cable_3(two::Canvas* canvas, two::NodePlug* plug_out, two::NodePlug* plug_in) {
		return &two::ui::node_cable(*canvas, *plug_out, *plug_in);
	}
	two::Canvas* DECL two_ui_canvas_1(two::Widget* parent) {
		return &two::ui::canvas(*parent);
	}
	two::Canvas* DECL two_ui_canvas_2(two::Widget* parent, size_t num_nodes) {
		return &two::ui::canvas(*parent, num_nodes);
	}
	two::ScrollSheet* DECL two_ui_scroll_sheet_2(two::Widget* parent, two::Style* style) {
		return &two::ui::scroll_sheet(*parent, *style);
	}
	two::ScrollSheet* DECL two_ui_scroll_sheet_3(two::Widget* parent, two::Style* style, two::Style* surface_style) {
		return &two::ui::scroll_sheet(*parent, *style, surface_style);
	}
	two::ScrollSheet* DECL two_ui_scroll_plan_2(two::Widget* parent, two::Style* style) {
		return &two::ui::scroll_plan(*parent, *style);
	}
	two::Widget* DECL two_ui_scrollable_1(two::Widget* parent) {
		return &two::ui::scrollable(*parent);
	}
	two::ui::Sequence* DECL two_ui_sequence_1(two::Widget* parent) {
		return &two::ui::sequence(*parent);
	}
	two::ui::Sequence* DECL two_ui_scroll_sequence_1(two::Widget* parent) {
		return &two::ui::scroll_sequence(*parent);
	}
	bool DECL two_ui_select_logic_3(two::Widget* element, void* object, two::Type* object_type, void* selection, two::Type* selection_type) {
		return two::ui::select_logic(*element, { object, *object_type }, { selection, *selection_type });
	}
	two::Widget* DECL two_ui_element_2(two::Widget* parent, void* object, two::Type* object_type) {
		return &two::ui::element(*parent, { object, *object_type });
	}
	two::Widget* DECL two_ui_sequence_element_2(two::ui::Sequence* parent, void* object, two::Type* object_type) {
		return &two::ui::sequence_element(*parent, { object, *object_type });
	}
	two::Window* DECL two_ui_window_2(two::Widget* parent, const char* title) {
		return &two::ui::window(*parent, title);
	}
	two::Window* DECL two_ui_window_3(two::Widget* parent, const char* title, two::WindowState state) {
		return &two::ui::window(*parent, title, state);
	}
	two::Widget* DECL two_ui_dir_item_2(two::Widget* parent, const char* name) {
		return &two::ui::dir_item(*parent, name);
	}
	two::Widget* DECL two_ui_file_item_2(two::Widget* parent, const char* name) {
		return &two::ui::file_item(*parent, name);
	}
	two::Widget* DECL two_ui_dir_node_4(two::Widget* parent, const char* path, const char* name, bool collapsed) {
		return &two::ui::dir_node(*parent, path, name, collapsed);
	}
	two::Widget* DECL two_ui_file_node_2(two::Widget* parent, const char* name) {
		return &two::ui::file_node(*parent, name);
	}
	two::Widget* DECL two_ui_file_tree_2(two::Widget* parent, const char* path) {
		return &two::ui::file_tree(*parent, path);
	}
	// FlowAxis
	two::FlowAxis DECL two_FlowAxis_Reading() {
		return two::FlowAxis::Reading;
	}
	two::FlowAxis DECL two_FlowAxis_Paragraph() {
		return two::FlowAxis::Paragraph;
	}
	two::FlowAxis DECL two_FlowAxis_Same() {
		return two::FlowAxis::Same;
	}
	two::FlowAxis DECL two_FlowAxis_Flip() {
		return two::FlowAxis::Flip;
	}
	two::FlowAxis DECL two_FlowAxis_None() {
		return two::FlowAxis::None;
	}
	// Pivot
	two::Pivot DECL two_Pivot_Forward() {
		return two::Pivot::Forward;
	}
	two::Pivot DECL two_Pivot_Reverse() {
		return two::Pivot::Reverse;
	}
	// Align
	two::Align DECL two_Align_Left() {
		return two::Align::Left;
	}
	two::Align DECL two_Align_Center() {
		return two::Align::Center;
	}
	two::Align DECL two_Align_Right() {
		return two::Align::Right;
	}
	two::Align DECL two_Align_OutLeft() {
		return two::Align::OutLeft;
	}
	two::Align DECL two_Align_OutRight() {
		return two::Align::OutRight;
	}
	two::Align DECL two_Align_Count() {
		return two::Align::Count;
	}
	// Solver
	two::Solver DECL two_Solver_Frame() {
		return two::Solver::Frame;
	}
	two::Solver DECL two_Solver_Row() {
		return two::Solver::Row;
	}
	two::Solver DECL two_Solver_Grid() {
		return two::Solver::Grid;
	}
	two::Solver DECL two_Solver_Table() {
		return two::Solver::Table;
	}
	// AutoLayout
	two::AutoLayout DECL two_AutoLayout_None() {
		return two::AutoLayout::None;
	}
	two::AutoLayout DECL two_AutoLayout_Size() {
		return two::AutoLayout::Size;
	}
	two::AutoLayout DECL two_AutoLayout_Layout() {
		return two::AutoLayout::Layout;
	}
	// LayoutFlow
	two::LayoutFlow DECL two_LayoutFlow_Flow() {
		return two::LayoutFlow::Flow;
	}
	two::LayoutFlow DECL two_LayoutFlow_Overlay() {
		return two::LayoutFlow::Overlay;
	}
	two::LayoutFlow DECL two_LayoutFlow_Align() {
		return two::LayoutFlow::Align;
	}
	two::LayoutFlow DECL two_LayoutFlow_Free() {
		return two::LayoutFlow::Free;
	}
	// Sizing
	two::Sizing DECL two_Sizing_Fixed() {
		return two::Sizing::Fixed;
	}
	two::Sizing DECL two_Sizing_Shrink() {
		return two::Sizing::Shrink;
	}
	two::Sizing DECL two_Sizing_Wrap() {
		return two::Sizing::Wrap;
	}
	two::Sizing DECL two_Sizing_Expand() {
		return two::Sizing::Expand;
	}
	// Preset
	two::Preset DECL two_Preset_Sheet() {
		return two::Preset::Sheet;
	}
	two::Preset DECL two_Preset_Flex() {
		return two::Preset::Flex;
	}
	two::Preset DECL two_Preset_Item() {
		return two::Preset::Item;
	}
	two::Preset DECL two_Preset_Unit() {
		return two::Preset::Unit;
	}
	two::Preset DECL two_Preset_Block() {
		return two::Preset::Block;
	}
	two::Preset DECL two_Preset_Line() {
		return two::Preset::Line;
	}
	two::Preset DECL two_Preset_Stack() {
		return two::Preset::Stack;
	}
	two::Preset DECL two_Preset_Div() {
		return two::Preset::Div;
	}
	two::Preset DECL two_Preset_Spacer() {
		return two::Preset::Spacer;
	}
	two::Preset DECL two_Preset_Board() {
		return two::Preset::Board;
	}
	two::Preset DECL two_Preset_Layout() {
		return two::Preset::Layout;
	}
	// Clip
	two::Clip DECL two_Clip_None() {
		return two::Clip::None;
	}
	two::Clip DECL two_Clip_Clip() {
		return two::Clip::Clip;
	}
	two::Clip DECL two_Clip_Unclip() {
		return two::Clip::Unclip;
	}
	// Opacity
	two::Opacity DECL two_Opacity_Opaque() {
		return two::Opacity::Opaque;
	}
	two::Opacity DECL two_Opacity_Clear() {
		return two::Opacity::Clear;
	}
	two::Opacity DECL two_Opacity_Hollow() {
		return two::Opacity::Hollow;
	}
	// WidgetState
	two::WidgetState DECL two_WidgetState_NOSTATE() {
		return two::NOSTATE;
	}
	two::WidgetState DECL two_WidgetState_CREATED() {
		return two::CREATED;
	}
	two::WidgetState DECL two_WidgetState_HOVERED() {
		return two::HOVERED;
	}
	two::WidgetState DECL two_WidgetState_PRESSED() {
		return two::PRESSED;
	}
	two::WidgetState DECL two_WidgetState_ACTIVATED() {
		return two::ACTIVATED;
	}
	two::WidgetState DECL two_WidgetState_ACTIVE() {
		return two::ACTIVE;
	}
	two::WidgetState DECL two_WidgetState_SELECTED() {
		return two::SELECTED;
	}
	two::WidgetState DECL two_WidgetState_DISABLED() {
		return two::DISABLED;
	}
	two::WidgetState DECL two_WidgetState_DRAGGED() {
		return two::DRAGGED;
	}
	two::WidgetState DECL two_WidgetState_FOCUSED() {
		return two::FOCUSED;
	}
	two::WidgetState DECL two_WidgetState_CLOSED() {
		return two::CLOSED;
	}
	// PopupFlags
	two::ui::PopupFlags DECL two_ui_PopupFlags_None() {
		return two::ui::PopupFlags::None;
	}
	two::ui::PopupFlags DECL two_ui_PopupFlags_Modal() {
		return two::ui::PopupFlags::Modal;
	}
	two::ui::PopupFlags DECL two_ui_PopupFlags_Clamp() {
		return two::ui::PopupFlags::Clamp;
	}
	two::ui::PopupFlags DECL two_ui_PopupFlags_AutoClose() {
		return two::ui::PopupFlags::AutoClose;
	}
	two::ui::PopupFlags DECL two_ui_PopupFlags_AutoModal() {
		return two::ui::PopupFlags::AutoModal;
	}
	// WindowState
	two::WindowState DECL two_WindowState_None() {
		return two::WindowState::None;
	}
	two::WindowState DECL two_WindowState_Header() {
		return two::WindowState::Header;
	}
	two::WindowState DECL two_WindowState_Dockable() {
		return two::WindowState::Dockable;
	}
	two::WindowState DECL two_WindowState_Closable() {
		return two::WindowState::Closable;
	}
	two::WindowState DECL two_WindowState_Movable() {
		return two::WindowState::Movable;
	}
	two::WindowState DECL two_WindowState_Sizable() {
		return two::WindowState::Sizable;
	}
	two::WindowState DECL two_WindowState_Scrollable() {
		return two::WindowState::Scrollable;
	}
	two::WindowState DECL two_WindowState_Menu() {
		return two::WindowState::Menu;
	}
	two::WindowState DECL two_WindowState_Default() {
		return two::WindowState::Default;
	}
	
}


