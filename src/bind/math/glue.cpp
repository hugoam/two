#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// Colour
	mud::Colour* EMSCRIPTEN_KEEPALIVE Colour_Colour_0() {
		return new mud::Colour();
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Colour_Colour_1(float r) {
		return new mud::Colour(r);
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Colour_Colour_2(float r, float g) {
		return new mud::Colour(r, g);
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Colour_Colour_3(float r, float g, float b) {
		return new mud::Colour(r, g, b);
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Colour_Colour_4(float r, float g, float b, float a) {
		return new mud::Colour(r, g, b, a);
	}
	float EMSCRIPTEN_KEEPALIVE Colour_get_r(mud::Colour* self) {
		return self->m_r;
	}
	void EMSCRIPTEN_KEEPALIVE Colour_set_r(mud::Colour* self, float value) {
		self->m_r = value;
	}
	float EMSCRIPTEN_KEEPALIVE Colour_get_g(mud::Colour* self) {
		return self->m_g;
	}
	void EMSCRIPTEN_KEEPALIVE Colour_set_g(mud::Colour* self, float value) {
		self->m_g = value;
	}
	float EMSCRIPTEN_KEEPALIVE Colour_get_b(mud::Colour* self) {
		return self->m_b;
	}
	void EMSCRIPTEN_KEEPALIVE Colour_set_b(mud::Colour* self, float value) {
		self->m_b = value;
	}
	float EMSCRIPTEN_KEEPALIVE Colour_get_a(mud::Colour* self) {
		return self->m_a;
	}
	void EMSCRIPTEN_KEEPALIVE Colour_set_a(mud::Colour* self, float value) {
		self->m_a = value;
	}
	void EMSCRIPTEN_KEEPALIVE Colour___destroy__(mud::Colour* self) {
		delete self;
	}
	// Gauge
	mud::Gauge* EMSCRIPTEN_KEEPALIVE Gauge_Gauge_0() {
		return new mud::Gauge();
	}
	mud::Gauge* EMSCRIPTEN_KEEPALIVE Gauge_Gauge_1(float value) {
		return new mud::Gauge(value);
	}
	void EMSCRIPTEN_KEEPALIVE Gauge___destroy__(mud::Gauge* self) {
		delete self;
	}
	// Image
	mud::Image* EMSCRIPTEN_KEEPALIVE Image_Image_0() {
		return new mud::Image();
	}
	void EMSCRIPTEN_KEEPALIVE Image___destroy__(mud::Image* self) {
		delete self;
	}
	// Image256
	mud::Image256* EMSCRIPTEN_KEEPALIVE Image256_Image256_0() {
		return new mud::Image256();
	}
	mud::Image256* EMSCRIPTEN_KEEPALIVE Image256_Image256_1(uint16_t width) {
		return new mud::Image256(width);
	}
	mud::Image256* EMSCRIPTEN_KEEPALIVE Image256_Image256_2(uint16_t width, uint16_t height) {
		return new mud::Image256(width, height);
	}
	mud::Image256* EMSCRIPTEN_KEEPALIVE Image256_Image256_3(uint16_t width, uint16_t height, const mud::Palette* palette) {
		return new mud::Image256(width, height, *palette);
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Image256_get_width(mud::Image256* self) {
		return self->m_width;
	}
	void EMSCRIPTEN_KEEPALIVE Image256_set_width(mud::Image256* self, uint16_t value) {
		self->m_width = value;
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Image256_get_height(mud::Image256* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE Image256_set_height(mud::Image256* self, uint16_t value) {
		self->m_height = value;
	}
	mud::Palette* EMSCRIPTEN_KEEPALIVE Image256_get_palette(mud::Image256* self) {
		static mud::Palette temp;
		return (temp = self->m_palette, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Image256_set_palette(mud::Image256* self, mud::Palette* value) {
		self->m_palette = *value;
	}
	void EMSCRIPTEN_KEEPALIVE Image256___destroy__(mud::Image256* self) {
		delete self;
	}
	// ImageAtlas
	void EMSCRIPTEN_KEEPALIVE ImageAtlas___destroy__(mud::ImageAtlas* self) {
		delete self;
	}
	// Palette
	mud::Palette* EMSCRIPTEN_KEEPALIVE Palette_Palette_2(mud::Spectrum spectrum, size_t steps) {
		return new mud::Palette(spectrum, steps);
	}
	void EMSCRIPTEN_KEEPALIVE Palette___destroy__(mud::Palette* self) {
		delete self;
	}
	// Ratio
	mud::Ratio* EMSCRIPTEN_KEEPALIVE Ratio_Ratio_0() {
		return new mud::Ratio();
	}
	mud::Ratio* EMSCRIPTEN_KEEPALIVE Ratio_Ratio_1(float value) {
		return new mud::Ratio(value);
	}
	void EMSCRIPTEN_KEEPALIVE Ratio___destroy__(mud::Ratio* self) {
		delete self;
	}
	// Time
	mud::Time* EMSCRIPTEN_KEEPALIVE Time_Time_1(double value) {
		return new mud::Time(value);
	}
	double EMSCRIPTEN_KEEPALIVE Time_get_value(mud::Time* self) {
		return self->m_value;
	}
	void EMSCRIPTEN_KEEPALIVE Time_set_value(mud::Time* self, double value) {
		self->m_value = value;
	}
	void EMSCRIPTEN_KEEPALIVE Time___destroy__(mud::Time* self) {
		delete self;
	}
	// TimeSpan
	mud::TimeSpan* EMSCRIPTEN_KEEPALIVE TimeSpan_TimeSpan_2(mud::Time* s, mud::Time* e) {
		return new mud::TimeSpan(*s, *e);
	}
	mud::Time* EMSCRIPTEN_KEEPALIVE TimeSpan_get_start(mud::TimeSpan* self) {
		static mud::Time temp;
		return (temp = self->start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE TimeSpan_set_start(mud::TimeSpan* self, mud::Time* value) {
		self->start = *value;
	}
	mud::Time* EMSCRIPTEN_KEEPALIVE TimeSpan_get_end(mud::TimeSpan* self) {
		static mud::Time temp;
		return (temp = self->end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE TimeSpan_set_end(mud::TimeSpan* self, mud::Time* value) {
		self->end = *value;
	}
	void EMSCRIPTEN_KEEPALIVE TimeSpan___destroy__(mud::TimeSpan* self) {
		delete self;
	}
	// Transform
	mud::Transform* EMSCRIPTEN_KEEPALIVE Transform_Transform_0() {
		return new mud::Transform();
	}
	mud::Transform* EMSCRIPTEN_KEEPALIVE Transform_Transform_3(const mud::vec3* position, const mud::quat* rotation, const mud::vec3* scale) {
		return new mud::Transform(*position, *rotation, *scale);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Transform_get_position(mud::Transform* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Transform_set_position(mud::Transform* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE Transform_get_rotation(mud::Transform* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Transform_set_rotation(mud::Transform* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Transform_get_scale(mud::Transform* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Transform_set_scale(mud::Transform* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	void EMSCRIPTEN_KEEPALIVE Transform___destroy__(mud::Transform* self) {
		delete self;
	}
	// bvec3
	mud::bvec3* EMSCRIPTEN_KEEPALIVE bvec3_bvec3_0() {
		return new mud::bvec3();
	}
	void EMSCRIPTEN_KEEPALIVE bvec3___destroy__(mud::bvec3* self) {
		delete self;
	}
	// bvec4
	mud::bvec4* EMSCRIPTEN_KEEPALIVE bvec4_bvec4_0() {
		return new mud::bvec4();
	}
	void EMSCRIPTEN_KEEPALIVE bvec4___destroy__(mud::bvec4* self) {
		delete self;
	}
	// half2
	mud::half2* EMSCRIPTEN_KEEPALIVE half2_half2_0() {
		return new mud::half2();
	}
	void EMSCRIPTEN_KEEPALIVE half2___destroy__(mud::half2* self) {
		delete self;
	}
	// half3
	mud::half3* EMSCRIPTEN_KEEPALIVE half3_half3_0() {
		return new mud::half3();
	}
	void EMSCRIPTEN_KEEPALIVE half3___destroy__(mud::half3* self) {
		delete self;
	}
	// ivec2
	mud::ivec2* EMSCRIPTEN_KEEPALIVE ivec2_ivec2_0() {
		return new mud::ivec2();
	}
	void EMSCRIPTEN_KEEPALIVE ivec2___destroy__(mud::ivec2* self) {
		delete self;
	}
	// ivec3
	mud::ivec3* EMSCRIPTEN_KEEPALIVE ivec3_ivec3_0() {
		return new mud::ivec3();
	}
	mud::ivec3* EMSCRIPTEN_KEEPALIVE ivec3_ivec3_1(int x) {
		return new mud::ivec3(x);
	}
	mud::ivec3* EMSCRIPTEN_KEEPALIVE ivec3_ivec3_3(int x, int y, int z) {
		return new mud::ivec3(x, y, z);
	}
	int EMSCRIPTEN_KEEPALIVE ivec3_get_x(mud::ivec3* self) {
		return self->x;
	}
	void EMSCRIPTEN_KEEPALIVE ivec3_set_x(mud::ivec3* self, int value) {
		self->x = value;
	}
	int EMSCRIPTEN_KEEPALIVE ivec3_get_y(mud::ivec3* self) {
		return self->y;
	}
	void EMSCRIPTEN_KEEPALIVE ivec3_set_y(mud::ivec3* self, int value) {
		self->y = value;
	}
	int EMSCRIPTEN_KEEPALIVE ivec3_get_z(mud::ivec3* self) {
		return self->z;
	}
	void EMSCRIPTEN_KEEPALIVE ivec3_set_z(mud::ivec3* self, int value) {
		self->z = value;
	}
	void EMSCRIPTEN_KEEPALIVE ivec3___destroy__(mud::ivec3* self) {
		delete self;
	}
	// ivec4
	mud::ivec4* EMSCRIPTEN_KEEPALIVE ivec4_ivec4_0() {
		return new mud::ivec4();
	}
	void EMSCRIPTEN_KEEPALIVE ivec4___destroy__(mud::ivec4* self) {
		delete self;
	}
	// mat4
	mud::mat4* EMSCRIPTEN_KEEPALIVE mat4_mat4_0() {
		return new mud::mat4();
	}
	void EMSCRIPTEN_KEEPALIVE mat4___destroy__(mud::mat4* self) {
		delete self;
	}
	// quat
	mud::quat* EMSCRIPTEN_KEEPALIVE quat_quat_0() {
		return new mud::quat();
	}
	mud::quat* EMSCRIPTEN_KEEPALIVE quat_quat_4(float w, float x, float y, float z) {
		return new mud::quat(w, x, y, z);
	}
	float EMSCRIPTEN_KEEPALIVE quat_get_x(mud::quat* self) {
		return self->x;
	}
	void EMSCRIPTEN_KEEPALIVE quat_set_x(mud::quat* self, float value) {
		self->x = value;
	}
	float EMSCRIPTEN_KEEPALIVE quat_get_y(mud::quat* self) {
		return self->y;
	}
	void EMSCRIPTEN_KEEPALIVE quat_set_y(mud::quat* self, float value) {
		self->y = value;
	}
	float EMSCRIPTEN_KEEPALIVE quat_get_z(mud::quat* self) {
		return self->z;
	}
	void EMSCRIPTEN_KEEPALIVE quat_set_z(mud::quat* self, float value) {
		self->z = value;
	}
	float EMSCRIPTEN_KEEPALIVE quat_get_w(mud::quat* self) {
		return self->w;
	}
	void EMSCRIPTEN_KEEPALIVE quat_set_w(mud::quat* self, float value) {
		self->w = value;
	}
	void EMSCRIPTEN_KEEPALIVE quat___destroy__(mud::quat* self) {
		delete self;
	}
	// uvec2
	mud::uvec2* EMSCRIPTEN_KEEPALIVE uvec2_uvec2_0() {
		return new mud::uvec2();
	}
	mud::uvec2* EMSCRIPTEN_KEEPALIVE uvec2_uvec2_1(uint32_t x) {
		return new mud::uvec2(x);
	}
	mud::uvec2* EMSCRIPTEN_KEEPALIVE uvec2_uvec2_2(uint32_t x, uint32_t y) {
		return new mud::uvec2(x, y);
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec2_get_x(mud::uvec2* self) {
		return self->x;
	}
	void EMSCRIPTEN_KEEPALIVE uvec2_set_x(mud::uvec2* self, uint32_t value) {
		self->x = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec2_get_y(mud::uvec2* self) {
		return self->y;
	}
	void EMSCRIPTEN_KEEPALIVE uvec2_set_y(mud::uvec2* self, uint32_t value) {
		self->y = value;
	}
	void EMSCRIPTEN_KEEPALIVE uvec2___destroy__(mud::uvec2* self) {
		delete self;
	}
	// uvec3
	mud::uvec3* EMSCRIPTEN_KEEPALIVE uvec3_uvec3_0() {
		return new mud::uvec3();
	}
	mud::uvec3* EMSCRIPTEN_KEEPALIVE uvec3_uvec3_1(uint32_t x) {
		return new mud::uvec3(x);
	}
	mud::uvec3* EMSCRIPTEN_KEEPALIVE uvec3_uvec3_3(uint32_t x, uint32_t y, uint32_t z) {
		return new mud::uvec3(x, y, z);
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec3_get_x(mud::uvec3* self) {
		return self->x;
	}
	void EMSCRIPTEN_KEEPALIVE uvec3_set_x(mud::uvec3* self, uint32_t value) {
		self->x = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec3_get_y(mud::uvec3* self) {
		return self->y;
	}
	void EMSCRIPTEN_KEEPALIVE uvec3_set_y(mud::uvec3* self, uint32_t value) {
		self->y = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec3_get_z(mud::uvec3* self) {
		return self->z;
	}
	void EMSCRIPTEN_KEEPALIVE uvec3_set_z(mud::uvec3* self, uint32_t value) {
		self->z = value;
	}
	void EMSCRIPTEN_KEEPALIVE uvec3___destroy__(mud::uvec3* self) {
		delete self;
	}
	// uvec4
	mud::uvec4* EMSCRIPTEN_KEEPALIVE uvec4_uvec4_0() {
		return new mud::uvec4();
	}
	mud::uvec4* EMSCRIPTEN_KEEPALIVE uvec4_uvec4_1(uint32_t w) {
		return new mud::uvec4(w);
	}
	mud::uvec4* EMSCRIPTEN_KEEPALIVE uvec4_uvec4_4(uint32_t w, uint32_t x, uint32_t y, uint32_t z) {
		return new mud::uvec4(w, x, y, z);
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec4_get_x(mud::uvec4* self) {
		return self->x;
	}
	void EMSCRIPTEN_KEEPALIVE uvec4_set_x(mud::uvec4* self, uint32_t value) {
		self->x = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec4_get_y(mud::uvec4* self) {
		return self->y;
	}
	void EMSCRIPTEN_KEEPALIVE uvec4_set_y(mud::uvec4* self, uint32_t value) {
		self->y = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec4_get_z(mud::uvec4* self) {
		return self->z;
	}
	void EMSCRIPTEN_KEEPALIVE uvec4_set_z(mud::uvec4* self, uint32_t value) {
		self->z = value;
	}
	uint32_t EMSCRIPTEN_KEEPALIVE uvec4_get_w(mud::uvec4* self) {
		return self->w;
	}
	void EMSCRIPTEN_KEEPALIVE uvec4_set_w(mud::uvec4* self, uint32_t value) {
		self->w = value;
	}
	void EMSCRIPTEN_KEEPALIVE uvec4___destroy__(mud::uvec4* self) {
		delete self;
	}
	// vec2
	mud::vec2* EMSCRIPTEN_KEEPALIVE vec2_vec2_0() {
		return new mud::vec2();
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE vec2_vec2_1(float x) {
		return new mud::vec2(x);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE vec2_vec2_2(float x, float y) {
		return new mud::vec2(x, y);
	}
	float EMSCRIPTEN_KEEPALIVE vec2_get_x(mud::vec2* self) {
		return self->x;
	}
	void EMSCRIPTEN_KEEPALIVE vec2_set_x(mud::vec2* self, float value) {
		self->x = value;
	}
	float EMSCRIPTEN_KEEPALIVE vec2_get_y(mud::vec2* self) {
		return self->y;
	}
	void EMSCRIPTEN_KEEPALIVE vec2_set_y(mud::vec2* self, float value) {
		self->y = value;
	}
	void EMSCRIPTEN_KEEPALIVE vec2___destroy__(mud::vec2* self) {
		delete self;
	}
	// vec3
	mud::vec3* EMSCRIPTEN_KEEPALIVE vec3_vec3_0() {
		return new mud::vec3();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE vec3_vec3_1(float x) {
		return new mud::vec3(x);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE vec3_vec3_3(float x, float y, float z) {
		return new mud::vec3(x, y, z);
	}
	float EMSCRIPTEN_KEEPALIVE vec3_get_x(mud::vec3* self) {
		return self->x;
	}
	void EMSCRIPTEN_KEEPALIVE vec3_set_x(mud::vec3* self, float value) {
		self->x = value;
	}
	float EMSCRIPTEN_KEEPALIVE vec3_get_y(mud::vec3* self) {
		return self->y;
	}
	void EMSCRIPTEN_KEEPALIVE vec3_set_y(mud::vec3* self, float value) {
		self->y = value;
	}
	float EMSCRIPTEN_KEEPALIVE vec3_get_z(mud::vec3* self) {
		return self->z;
	}
	void EMSCRIPTEN_KEEPALIVE vec3_set_z(mud::vec3* self, float value) {
		self->z = value;
	}
	void EMSCRIPTEN_KEEPALIVE vec3___destroy__(mud::vec3* self) {
		delete self;
	}
	// vec4
	mud::vec4* EMSCRIPTEN_KEEPALIVE vec4_vec4_0() {
		return new mud::vec4();
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE vec4_vec4_1(float w) {
		return new mud::vec4(w);
	}
	mud::vec4* EMSCRIPTEN_KEEPALIVE vec4_vec4_4(float w, float x, float y, float z) {
		return new mud::vec4(w, x, y, z);
	}
	float EMSCRIPTEN_KEEPALIVE vec4_get_x(mud::vec4* self) {
		return self->x;
	}
	void EMSCRIPTEN_KEEPALIVE vec4_set_x(mud::vec4* self, float value) {
		self->x = value;
	}
	float EMSCRIPTEN_KEEPALIVE vec4_get_y(mud::vec4* self) {
		return self->y;
	}
	void EMSCRIPTEN_KEEPALIVE vec4_set_y(mud::vec4* self, float value) {
		self->y = value;
	}
	float EMSCRIPTEN_KEEPALIVE vec4_get_z(mud::vec4* self) {
		return self->z;
	}
	void EMSCRIPTEN_KEEPALIVE vec4_set_z(mud::vec4* self, float value) {
		self->z = value;
	}
	float EMSCRIPTEN_KEEPALIVE vec4_get_w(mud::vec4* self) {
		return self->w;
	}
	void EMSCRIPTEN_KEEPALIVE vec4_set_w(mud::vec4* self, float value) {
		self->w = value;
	}
	void EMSCRIPTEN_KEEPALIVE vec4___destroy__(mud::vec4* self) {
		delete self;
	}
	// Sprite
	void EMSCRIPTEN_KEEPALIVE Sprite___destroy__(mud::Sprite* self) {
		delete self;
	}
	// SpriteAtlas
	void EMSCRIPTEN_KEEPALIVE SpriteAtlas___destroy__(mud::SpriteAtlas* self) {
		delete self;
	}
	// TextureAtlas
	void EMSCRIPTEN_KEEPALIVE TextureAtlas___destroy__(mud::TextureAtlas* self) {
		delete self;
	}
	// Axes
	mud::Axes EMSCRIPTEN_KEEPALIVE Axes_None() {
		return mud::Axes::None;
	}
	mud::Axes EMSCRIPTEN_KEEPALIVE Axes_X() {
		return mud::Axes::X;
	}
	mud::Axes EMSCRIPTEN_KEEPALIVE Axes_Y() {
		return mud::Axes::Y;
	}
	mud::Axes EMSCRIPTEN_KEEPALIVE Axes_Z() {
		return mud::Axes::Z;
	}
	// Axis
	mud::Axis EMSCRIPTEN_KEEPALIVE Axis_X() {
		return mud::Axis::X;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE Axis_Y() {
		return mud::Axis::Y;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE Axis_Z() {
		return mud::Axis::Z;
	}
	// Clockwise
	mud::Clockwise EMSCRIPTEN_KEEPALIVE Clockwise_CLOCKWISE() {
		return mud::CLOCKWISE;
	}
	mud::Clockwise EMSCRIPTEN_KEEPALIVE Clockwise_ANTI_CLOCKWISE() {
		return mud::ANTI_CLOCKWISE;
	}
	// Side
	mud::Side EMSCRIPTEN_KEEPALIVE Side_Right() {
		return mud::Side::Right;
	}
	mud::Side EMSCRIPTEN_KEEPALIVE Side_Left() {
		return mud::Side::Left;
	}
	mud::Side EMSCRIPTEN_KEEPALIVE Side_Up() {
		return mud::Side::Up;
	}
	mud::Side EMSCRIPTEN_KEEPALIVE Side_Down() {
		return mud::Side::Down;
	}
	mud::Side EMSCRIPTEN_KEEPALIVE Side_Back() {
		return mud::Side::Back;
	}
	mud::Side EMSCRIPTEN_KEEPALIVE Side_Front() {
		return mud::Side::Front;
	}
	// SignedAxis
	mud::SignedAxis EMSCRIPTEN_KEEPALIVE SignedAxis_PlusX() {
		return mud::SignedAxis::PlusX;
	}
	mud::SignedAxis EMSCRIPTEN_KEEPALIVE SignedAxis_MinusX() {
		return mud::SignedAxis::MinusX;
	}
	mud::SignedAxis EMSCRIPTEN_KEEPALIVE SignedAxis_PlusY() {
		return mud::SignedAxis::PlusY;
	}
	mud::SignedAxis EMSCRIPTEN_KEEPALIVE SignedAxis_MinusY() {
		return mud::SignedAxis::MinusY;
	}
	mud::SignedAxis EMSCRIPTEN_KEEPALIVE SignedAxis_PlusZ() {
		return mud::SignedAxis::PlusZ;
	}
	mud::SignedAxis EMSCRIPTEN_KEEPALIVE SignedAxis_MinusZ() {
		return mud::SignedAxis::MinusZ;
	}
	// Spectrum
	mud::Spectrum EMSCRIPTEN_KEEPALIVE Spectrum_Value() {
		return mud::Spectrum::Value;
	}
	mud::Spectrum EMSCRIPTEN_KEEPALIVE Spectrum_Hue() {
		return mud::Spectrum::Hue;
	}
	// TrackMode
	mud::TrackMode EMSCRIPTEN_KEEPALIVE TrackMode_Constant() {
		return mud::TrackMode::Constant;
	}
	mud::TrackMode EMSCRIPTEN_KEEPALIVE TrackMode_ConstantRandom() {
		return mud::TrackMode::ConstantRandom;
	}
	mud::TrackMode EMSCRIPTEN_KEEPALIVE TrackMode_Curve() {
		return mud::TrackMode::Curve;
	}
	mud::TrackMode EMSCRIPTEN_KEEPALIVE TrackMode_CurveRandom() {
		return mud::TrackMode::CurveRandom;
	}
	
}


