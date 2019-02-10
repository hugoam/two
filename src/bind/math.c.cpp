#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// AutoStat<float>
	mud::Type* DECL mud_AutoStat_float__type() {
		return &mud::type<mud::AutoStat<float>>();
	}
	mud::AutoStat<float>* DECL mud_AutoStat_float__construct_0() {
		return new mud::AutoStat<float>();
	}
	float DECL mud_AutoStat_float__get_value(mud::AutoStat<float>* self) {
		return self->m_value;
	}
	void DECL mud_AutoStat_float__set_value(mud::AutoStat<float>* self, float value) {
		self->m_value = value;
	}
	void DECL mud_AutoStat_float__destroy(mud::AutoStat<float>* self) {
		delete self;
	}
	// AutoStat<int>
	mud::Type* DECL mud_AutoStat_int__type() {
		return &mud::type<mud::AutoStat<int>>();
	}
	mud::AutoStat<int>* DECL mud_AutoStat_int__construct_0() {
		return new mud::AutoStat<int>();
	}
	int DECL mud_AutoStat_int__get_value(mud::AutoStat<int>* self) {
		return self->m_value;
	}
	void DECL mud_AutoStat_int__set_value(mud::AutoStat<int>* self, int value) {
		self->m_value = value;
	}
	void DECL mud_AutoStat_int__destroy(mud::AutoStat<int>* self) {
		delete self;
	}
	// Colour
	mud::Type* DECL mud_Colour__type() {
		return &mud::type<mud::Colour>();
	}
	mud::Colour* DECL mud_Colour__construct_0() {
		return new mud::Colour();
	}
	mud::Colour* DECL mud_Colour__construct_1(float v) {
		return new mud::Colour(v);
	}
	mud::Colour* DECL mud_Colour__construct_2(float v, float a) {
		return new mud::Colour(v, a);
	}
	mud::Colour* DECL mud_Colour__construct_3(float r, float g, float b) {
		return new mud::Colour(r, g, b);
	}
	mud::Colour* DECL mud_Colour__construct_4(float r, float g, float b, float a) {
		return new mud::Colour(r, g, b, a);
	}
	float DECL mud_Colour__get_r(mud::Colour* self) {
		return self->m_r;
	}
	void DECL mud_Colour__set_r(mud::Colour* self, float value) {
		self->m_r = value;
	}
	float DECL mud_Colour__get_g(mud::Colour* self) {
		return self->m_g;
	}
	void DECL mud_Colour__set_g(mud::Colour* self, float value) {
		self->m_g = value;
	}
	float DECL mud_Colour__get_b(mud::Colour* self) {
		return self->m_b;
	}
	void DECL mud_Colour__set_b(mud::Colour* self, float value) {
		self->m_b = value;
	}
	float DECL mud_Colour__get_a(mud::Colour* self) {
		return self->m_a;
	}
	void DECL mud_Colour__set_a(mud::Colour* self, float value) {
		self->m_a = value;
	}
	void DECL mud_Colour__destroy(mud::Colour* self) {
		delete self;
	}
	// Image
	mud::Type* DECL mud_Image__type() {
		return &mud::type<mud::Image>();
	}
	mud::Image* DECL mud_Image__construct_0() {
		return new mud::Image();
	}
	const char* DECL mud_Image__get_d_name(mud::Image* self) {
		return self->d_name.c_str();
	}
	void DECL mud_Image__set_d_name(mud::Image* self, const char* value) {
		self->d_name = value;
	}
	const char* DECL mud_Image__get_d_path(mud::Image* self) {
		return self->d_path.c_str();
	}
	void DECL mud_Image__set_d_path(mud::Image* self, const char* value) {
		self->d_path = value;
	}
	void DECL mud_Image__destroy(mud::Image* self) {
		delete self;
	}
	// Image256
	mud::Type* DECL mud_Image256__type() {
		return &mud::type<mud::Image256>();
	}
	mud::Image256* DECL mud_Image256__construct_0() {
		return new mud::Image256();
	}
	mud::Image256* DECL mud_Image256__construct_1(uint16_t width) {
		return new mud::Image256(width);
	}
	mud::Image256* DECL mud_Image256__construct_2(uint16_t width, uint16_t height) {
		return new mud::Image256(width, height);
	}
	mud::Image256* DECL mud_Image256__construct_3(uint16_t width, uint16_t height, const mud::Palette* palette) {
		return new mud::Image256(width, height, *palette);
	}
	uint16_t DECL mud_Image256__get_width(mud::Image256* self) {
		return self->m_width;
	}
	void DECL mud_Image256__set_width(mud::Image256* self, uint16_t value) {
		self->m_width = value;
	}
	uint16_t DECL mud_Image256__get_height(mud::Image256* self) {
		return self->m_height;
	}
	void DECL mud_Image256__set_height(mud::Image256* self, uint16_t value) {
		self->m_height = value;
	}
	mud::Palette* DECL mud_Image256__get_palette(mud::Image256* self) {
		static mud::Palette temp;
		return (temp = self->m_palette, &temp);
	}
	void DECL mud_Image256__set_palette(mud::Image256* self, mud::Palette* value) {
		self->m_palette = *value;
	}
	void DECL mud_Image256__destroy(mud::Image256* self) {
		delete self;
	}
	// ImageAtlas
	mud::Type* DECL mud_ImageAtlas__type() {
		return &mud::type<mud::ImageAtlas>();
	}
	void DECL mud_ImageAtlas__destroy(mud::ImageAtlas* self) {
		delete self;
	}
	// Palette
	mud::Type* DECL mud_Palette__type() {
		return &mud::type<mud::Palette>();
	}
	mud::Palette* DECL mud_Palette__construct_0() {
		return new mud::Palette();
	}
	mud::Palette* DECL mud_Palette__construct_1(stl::vector<mud::Colour>* colours) {
		return new mud::Palette(*colours);
	}
	mud::Palette* DECL mud_Palette__construct_2(mud::Spectrum spectrum, size_t steps) {
		return new mud::Palette(spectrum, steps);
	}
	void DECL mud_Palette__destroy(mud::Palette* self) {
		delete self;
	}
	// Range<float>
	mud::Type* DECL mud_Range_float__type() {
		return &mud::type<mud::Range<float>>();
	}
	mud::Range<float>* DECL mud_Range_float__construct_0() {
		return new mud::Range<float>();
	}
	float DECL mud_Range_float__get_min(mud::Range<float>* self) {
		return self->m_min;
	}
	void DECL mud_Range_float__set_min(mud::Range<float>* self, float value) {
		self->m_min = value;
	}
	float DECL mud_Range_float__get_max(mud::Range<float>* self) {
		return self->m_max;
	}
	void DECL mud_Range_float__set_max(mud::Range<float>* self, float value) {
		self->m_max = value;
	}
	void DECL mud_Range_float__destroy(mud::Range<float>* self) {
		delete self;
	}
	// Range<mud::Colour>
	mud::Type* DECL mud_Range_mud_Colour__type() {
		return &mud::type<mud::Range<mud::Colour>>();
	}
	mud::Range<mud::Colour>* DECL mud_Range_mud_Colour__construct_0() {
		return new mud::Range<mud::Colour>();
	}
	mud::Colour* DECL mud_Range_mud_Colour__get_min(mud::Range<mud::Colour>* self) {
		static mud::Colour temp;
		return (temp = self->m_min, &temp);
	}
	void DECL mud_Range_mud_Colour__set_min(mud::Range<mud::Colour>* self, mud::Colour* value) {
		self->m_min = *value;
	}
	mud::Colour* DECL mud_Range_mud_Colour__get_max(mud::Range<mud::Colour>* self) {
		static mud::Colour temp;
		return (temp = self->m_max, &temp);
	}
	void DECL mud_Range_mud_Colour__set_max(mud::Range<mud::Colour>* self, mud::Colour* value) {
		self->m_max = *value;
	}
	void DECL mud_Range_mud_Colour__destroy(mud::Range<mud::Colour>* self) {
		delete self;
	}
	// Range<mud::quat>
	mud::Type* DECL mud_Range_mud_quat__type() {
		return &mud::type<mud::Range<mud::quat>>();
	}
	mud::Range<mud::quat>* DECL mud_Range_mud_quat__construct_0() {
		return new mud::Range<mud::quat>();
	}
	mud::quat* DECL mud_Range_mud_quat__get_min(mud::Range<mud::quat>* self) {
		static mud::quat temp;
		return (temp = self->m_min, &temp);
	}
	void DECL mud_Range_mud_quat__set_min(mud::Range<mud::quat>* self, mud::quat* value) {
		self->m_min = *value;
	}
	mud::quat* DECL mud_Range_mud_quat__get_max(mud::Range<mud::quat>* self) {
		static mud::quat temp;
		return (temp = self->m_max, &temp);
	}
	void DECL mud_Range_mud_quat__set_max(mud::Range<mud::quat>* self, mud::quat* value) {
		self->m_max = *value;
	}
	void DECL mud_Range_mud_quat__destroy(mud::Range<mud::quat>* self) {
		delete self;
	}
	// Range<mud::vec3>
	mud::Type* DECL mud_Range_mud_vec3__type() {
		return &mud::type<mud::Range<mud::vec3>>();
	}
	mud::Range<mud::vec3>* DECL mud_Range_mud_vec3__construct_0() {
		return new mud::Range<mud::vec3>();
	}
	mud::vec3* DECL mud_Range_mud_vec3__get_min(mud::Range<mud::vec3>* self) {
		static mud::vec3 temp;
		return (temp = self->m_min, &temp);
	}
	void DECL mud_Range_mud_vec3__set_min(mud::Range<mud::vec3>* self, mud::vec3* value) {
		self->m_min = *value;
	}
	mud::vec3* DECL mud_Range_mud_vec3__get_max(mud::Range<mud::vec3>* self) {
		static mud::vec3 temp;
		return (temp = self->m_max, &temp);
	}
	void DECL mud_Range_mud_vec3__set_max(mud::Range<mud::vec3>* self, mud::vec3* value) {
		self->m_max = *value;
	}
	void DECL mud_Range_mud_vec3__destroy(mud::Range<mud::vec3>* self) {
		delete self;
	}
	// Range<uint32_t>
	mud::Type* DECL mud_Range_uint32_t__type() {
		return &mud::type<mud::Range<uint32_t>>();
	}
	mud::Range<uint32_t>* DECL mud_Range_uint32_t__construct_0() {
		return new mud::Range<uint32_t>();
	}
	uint32_t DECL mud_Range_uint32_t__get_min(mud::Range<uint32_t>* self) {
		return self->m_min;
	}
	void DECL mud_Range_uint32_t__set_min(mud::Range<uint32_t>* self, uint32_t value) {
		self->m_min = value;
	}
	uint32_t DECL mud_Range_uint32_t__get_max(mud::Range<uint32_t>* self) {
		return self->m_max;
	}
	void DECL mud_Range_uint32_t__set_max(mud::Range<uint32_t>* self, uint32_t value) {
		self->m_max = value;
	}
	void DECL mud_Range_uint32_t__destroy(mud::Range<uint32_t>* self) {
		delete self;
	}
	// Time
	mud::Type* DECL mud_Time__type() {
		return &mud::type<mud::Time>();
	}
	mud::Time* DECL mud_Time__construct_1(double value) {
		return new mud::Time(value);
	}
	double DECL mud_Time__get_value(mud::Time* self) {
		return self->m_value;
	}
	void DECL mud_Time__set_value(mud::Time* self, double value) {
		self->m_value = value;
	}
	void DECL mud_Time__destroy(mud::Time* self) {
		delete self;
	}
	// TimeSpan
	mud::Type* DECL mud_TimeSpan__type() {
		return &mud::type<mud::TimeSpan>();
	}
	mud::TimeSpan* DECL mud_TimeSpan__construct_2(mud::Time* s, mud::Time* e) {
		return new mud::TimeSpan(*s, *e);
	}
	mud::Time* DECL mud_TimeSpan__get_start(mud::TimeSpan* self) {
		static mud::Time temp;
		return (temp = self->start, &temp);
	}
	void DECL mud_TimeSpan__set_start(mud::TimeSpan* self, mud::Time* value) {
		self->start = *value;
	}
	mud::Time* DECL mud_TimeSpan__get_end(mud::TimeSpan* self) {
		static mud::Time temp;
		return (temp = self->end, &temp);
	}
	void DECL mud_TimeSpan__set_end(mud::TimeSpan* self, mud::Time* value) {
		self->end = *value;
	}
	void DECL mud_TimeSpan__destroy(mud::TimeSpan* self) {
		delete self;
	}
	// Transform
	mud::Type* DECL mud_Transform__type() {
		return &mud::type<mud::Transform>();
	}
	mud::Transform* DECL mud_Transform__construct_0() {
		return new mud::Transform();
	}
	mud::vec3* DECL mud_Transform__get_position(mud::Transform* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void DECL mud_Transform__set_position(mud::Transform* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::quat* DECL mud_Transform__get_rotation(mud::Transform* self) {
		static mud::quat temp;
		return (temp = self->m_rotation, &temp);
	}
	void DECL mud_Transform__set_rotation(mud::Transform* self, mud::quat* value) {
		self->m_rotation = *value;
	}
	mud::vec3* DECL mud_Transform__get_scale(mud::Transform* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void DECL mud_Transform__set_scale(mud::Transform* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	void DECL mud_Transform__destroy(mud::Transform* self) {
		delete self;
	}
	// ValueCurve<float>
	mud::Type* DECL mud_ValueCurve_float__type() {
		return &mud::type<mud::ValueCurve<float>>();
	}
	mud::ValueCurve<float>* DECL mud_ValueCurve_float__construct_0() {
		return new mud::ValueCurve<float>();
	}
	mud::ValueCurve<float>* DECL mud_ValueCurve_float__construct_1(stl::vector<float>* keys) {
		return new mud::ValueCurve<float>(*keys);
	}
	void DECL mud_ValueCurve_float__destroy(mud::ValueCurve<float>* self) {
		delete self;
	}
	// ValueCurve<mud::Colour>
	mud::Type* DECL mud_ValueCurve_mud_Colour__type() {
		return &mud::type<mud::ValueCurve<mud::Colour>>();
	}
	mud::ValueCurve<mud::Colour>* DECL mud_ValueCurve_mud_Colour__construct_0() {
		return new mud::ValueCurve<mud::Colour>();
	}
	mud::ValueCurve<mud::Colour>* DECL mud_ValueCurve_mud_Colour__construct_1(stl::vector<mud::Colour>* keys) {
		return new mud::ValueCurve<mud::Colour>(*keys);
	}
	void DECL mud_ValueCurve_mud_Colour__destroy(mud::ValueCurve<mud::Colour>* self) {
		delete self;
	}
	// ValueCurve<mud::quat>
	mud::Type* DECL mud_ValueCurve_mud_quat__type() {
		return &mud::type<mud::ValueCurve<mud::quat>>();
	}
	mud::ValueCurve<mud::quat>* DECL mud_ValueCurve_mud_quat__construct_0() {
		return new mud::ValueCurve<mud::quat>();
	}
	mud::ValueCurve<mud::quat>* DECL mud_ValueCurve_mud_quat__construct_1(stl::vector<mud::quat>* keys) {
		return new mud::ValueCurve<mud::quat>(*keys);
	}
	void DECL mud_ValueCurve_mud_quat__destroy(mud::ValueCurve<mud::quat>* self) {
		delete self;
	}
	// ValueCurve<mud::vec3>
	mud::Type* DECL mud_ValueCurve_mud_vec3__type() {
		return &mud::type<mud::ValueCurve<mud::vec3>>();
	}
	mud::ValueCurve<mud::vec3>* DECL mud_ValueCurve_mud_vec3__construct_0() {
		return new mud::ValueCurve<mud::vec3>();
	}
	mud::ValueCurve<mud::vec3>* DECL mud_ValueCurve_mud_vec3__construct_1(stl::vector<mud::vec3>* keys) {
		return new mud::ValueCurve<mud::vec3>(*keys);
	}
	void DECL mud_ValueCurve_mud_vec3__destroy(mud::ValueCurve<mud::vec3>* self) {
		delete self;
	}
	// ValueCurve<uint32_t>
	mud::Type* DECL mud_ValueCurve_uint32_t__type() {
		return &mud::type<mud::ValueCurve<uint32_t>>();
	}
	mud::ValueCurve<uint32_t>* DECL mud_ValueCurve_uint32_t__construct_0() {
		return new mud::ValueCurve<uint32_t>();
	}
	mud::ValueCurve<uint32_t>* DECL mud_ValueCurve_uint32_t__construct_1(stl::vector<uint32_t>* keys) {
		return new mud::ValueCurve<uint32_t>(*keys);
	}
	void DECL mud_ValueCurve_uint32_t__destroy(mud::ValueCurve<uint32_t>* self) {
		delete self;
	}
	// ValueTrack<float>
	mud::Type* DECL mud_ValueTrack_float__type() {
		return &mud::type<mud::ValueTrack<float>>();
	}
	mud::ValueTrack<float>* DECL mud_ValueTrack_float__construct_0() {
		return new mud::ValueTrack<float>();
	}
	mud::ValueTrack<float>* DECL mud_ValueTrack_float__construct_4(mud::TrackMode mode, mud::ValueCurve<float>* curve, mud::ValueCurve<float>* min_curve, mud::ValueCurve<float>* max_curve) {
		return new mud::ValueTrack<float>(mode, *curve, *min_curve, *max_curve);
	}
	mud::TrackMode DECL mud_ValueTrack_float__get_mode(mud::ValueTrack<float>* self) {
		return self->m_mode;
	}
	void DECL mud_ValueTrack_float__set_mode(mud::ValueTrack<float>* self, mud::TrackMode value) {
		self->m_mode = value;
	}
	float DECL mud_ValueTrack_float__get_value(mud::ValueTrack<float>* self) {
		return self->m_value;
	}
	void DECL mud_ValueTrack_float__set_value(mud::ValueTrack<float>* self, float value) {
		self->m_value = value;
	}
	float DECL mud_ValueTrack_float__get_min(mud::ValueTrack<float>* self) {
		return self->m_min;
	}
	void DECL mud_ValueTrack_float__set_min(mud::ValueTrack<float>* self, float value) {
		self->m_min = value;
	}
	float DECL mud_ValueTrack_float__get_max(mud::ValueTrack<float>* self) {
		return self->m_max;
	}
	void DECL mud_ValueTrack_float__set_max(mud::ValueTrack<float>* self, float value) {
		self->m_max = value;
	}
	mud::ValueCurve<float>* DECL mud_ValueTrack_float__get_curve(mud::ValueTrack<float>* self) {
		static mud::ValueCurve<float> temp;
		return (temp = self->m_curve, &temp);
	}
	void DECL mud_ValueTrack_float__set_curve(mud::ValueTrack<float>* self, mud::ValueCurve<float>* value) {
		self->m_curve = *value;
	}
	mud::ValueCurve<float>* DECL mud_ValueTrack_float__get_min_curve(mud::ValueTrack<float>* self) {
		static mud::ValueCurve<float> temp;
		return (temp = self->m_min_curve, &temp);
	}
	void DECL mud_ValueTrack_float__set_min_curve(mud::ValueTrack<float>* self, mud::ValueCurve<float>* value) {
		self->m_min_curve = *value;
	}
	mud::ValueCurve<float>* DECL mud_ValueTrack_float__get_max_curve(mud::ValueTrack<float>* self) {
		static mud::ValueCurve<float> temp;
		return (temp = self->m_max_curve, &temp);
	}
	void DECL mud_ValueTrack_float__set_max_curve(mud::ValueTrack<float>* self, mud::ValueCurve<float>* value) {
		self->m_max_curve = *value;
	}
	void DECL mud_ValueTrack_float__destroy(mud::ValueTrack<float>* self) {
		delete self;
	}
	// ValueTrack<mud::Colour>
	mud::Type* DECL mud_ValueTrack_mud_Colour__type() {
		return &mud::type<mud::ValueTrack<mud::Colour>>();
	}
	mud::ValueTrack<mud::Colour>* DECL mud_ValueTrack_mud_Colour__construct_0() {
		return new mud::ValueTrack<mud::Colour>();
	}
	mud::ValueTrack<mud::Colour>* DECL mud_ValueTrack_mud_Colour__construct_4(mud::TrackMode mode, mud::ValueCurve<mud::Colour>* curve, mud::ValueCurve<mud::Colour>* min_curve, mud::ValueCurve<mud::Colour>* max_curve) {
		return new mud::ValueTrack<mud::Colour>(mode, *curve, *min_curve, *max_curve);
	}
	mud::TrackMode DECL mud_ValueTrack_mud_Colour__get_mode(mud::ValueTrack<mud::Colour>* self) {
		return self->m_mode;
	}
	void DECL mud_ValueTrack_mud_Colour__set_mode(mud::ValueTrack<mud::Colour>* self, mud::TrackMode value) {
		self->m_mode = value;
	}
	mud::Colour* DECL mud_ValueTrack_mud_Colour__get_value(mud::ValueTrack<mud::Colour>* self) {
		static mud::Colour temp;
		return (temp = self->m_value, &temp);
	}
	void DECL mud_ValueTrack_mud_Colour__set_value(mud::ValueTrack<mud::Colour>* self, mud::Colour* value) {
		self->m_value = *value;
	}
	mud::Colour* DECL mud_ValueTrack_mud_Colour__get_min(mud::ValueTrack<mud::Colour>* self) {
		static mud::Colour temp;
		return (temp = self->m_min, &temp);
	}
	void DECL mud_ValueTrack_mud_Colour__set_min(mud::ValueTrack<mud::Colour>* self, mud::Colour* value) {
		self->m_min = *value;
	}
	mud::Colour* DECL mud_ValueTrack_mud_Colour__get_max(mud::ValueTrack<mud::Colour>* self) {
		static mud::Colour temp;
		return (temp = self->m_max, &temp);
	}
	void DECL mud_ValueTrack_mud_Colour__set_max(mud::ValueTrack<mud::Colour>* self, mud::Colour* value) {
		self->m_max = *value;
	}
	mud::ValueCurve<mud::Colour>* DECL mud_ValueTrack_mud_Colour__get_curve(mud::ValueTrack<mud::Colour>* self) {
		static mud::ValueCurve<mud::Colour> temp;
		return (temp = self->m_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_Colour__set_curve(mud::ValueTrack<mud::Colour>* self, mud::ValueCurve<mud::Colour>* value) {
		self->m_curve = *value;
	}
	mud::ValueCurve<mud::Colour>* DECL mud_ValueTrack_mud_Colour__get_min_curve(mud::ValueTrack<mud::Colour>* self) {
		static mud::ValueCurve<mud::Colour> temp;
		return (temp = self->m_min_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_Colour__set_min_curve(mud::ValueTrack<mud::Colour>* self, mud::ValueCurve<mud::Colour>* value) {
		self->m_min_curve = *value;
	}
	mud::ValueCurve<mud::Colour>* DECL mud_ValueTrack_mud_Colour__get_max_curve(mud::ValueTrack<mud::Colour>* self) {
		static mud::ValueCurve<mud::Colour> temp;
		return (temp = self->m_max_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_Colour__set_max_curve(mud::ValueTrack<mud::Colour>* self, mud::ValueCurve<mud::Colour>* value) {
		self->m_max_curve = *value;
	}
	void DECL mud_ValueTrack_mud_Colour__destroy(mud::ValueTrack<mud::Colour>* self) {
		delete self;
	}
	// ValueTrack<mud::quat>
	mud::Type* DECL mud_ValueTrack_mud_quat__type() {
		return &mud::type<mud::ValueTrack<mud::quat>>();
	}
	mud::ValueTrack<mud::quat>* DECL mud_ValueTrack_mud_quat__construct_0() {
		return new mud::ValueTrack<mud::quat>();
	}
	mud::ValueTrack<mud::quat>* DECL mud_ValueTrack_mud_quat__construct_4(mud::TrackMode mode, mud::ValueCurve<mud::quat>* curve, mud::ValueCurve<mud::quat>* min_curve, mud::ValueCurve<mud::quat>* max_curve) {
		return new mud::ValueTrack<mud::quat>(mode, *curve, *min_curve, *max_curve);
	}
	mud::TrackMode DECL mud_ValueTrack_mud_quat__get_mode(mud::ValueTrack<mud::quat>* self) {
		return self->m_mode;
	}
	void DECL mud_ValueTrack_mud_quat__set_mode(mud::ValueTrack<mud::quat>* self, mud::TrackMode value) {
		self->m_mode = value;
	}
	mud::quat* DECL mud_ValueTrack_mud_quat__get_value(mud::ValueTrack<mud::quat>* self) {
		static mud::quat temp;
		return (temp = self->m_value, &temp);
	}
	void DECL mud_ValueTrack_mud_quat__set_value(mud::ValueTrack<mud::quat>* self, mud::quat* value) {
		self->m_value = *value;
	}
	mud::quat* DECL mud_ValueTrack_mud_quat__get_min(mud::ValueTrack<mud::quat>* self) {
		static mud::quat temp;
		return (temp = self->m_min, &temp);
	}
	void DECL mud_ValueTrack_mud_quat__set_min(mud::ValueTrack<mud::quat>* self, mud::quat* value) {
		self->m_min = *value;
	}
	mud::quat* DECL mud_ValueTrack_mud_quat__get_max(mud::ValueTrack<mud::quat>* self) {
		static mud::quat temp;
		return (temp = self->m_max, &temp);
	}
	void DECL mud_ValueTrack_mud_quat__set_max(mud::ValueTrack<mud::quat>* self, mud::quat* value) {
		self->m_max = *value;
	}
	mud::ValueCurve<mud::quat>* DECL mud_ValueTrack_mud_quat__get_curve(mud::ValueTrack<mud::quat>* self) {
		static mud::ValueCurve<mud::quat> temp;
		return (temp = self->m_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_quat__set_curve(mud::ValueTrack<mud::quat>* self, mud::ValueCurve<mud::quat>* value) {
		self->m_curve = *value;
	}
	mud::ValueCurve<mud::quat>* DECL mud_ValueTrack_mud_quat__get_min_curve(mud::ValueTrack<mud::quat>* self) {
		static mud::ValueCurve<mud::quat> temp;
		return (temp = self->m_min_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_quat__set_min_curve(mud::ValueTrack<mud::quat>* self, mud::ValueCurve<mud::quat>* value) {
		self->m_min_curve = *value;
	}
	mud::ValueCurve<mud::quat>* DECL mud_ValueTrack_mud_quat__get_max_curve(mud::ValueTrack<mud::quat>* self) {
		static mud::ValueCurve<mud::quat> temp;
		return (temp = self->m_max_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_quat__set_max_curve(mud::ValueTrack<mud::quat>* self, mud::ValueCurve<mud::quat>* value) {
		self->m_max_curve = *value;
	}
	void DECL mud_ValueTrack_mud_quat__destroy(mud::ValueTrack<mud::quat>* self) {
		delete self;
	}
	// ValueTrack<mud::vec3>
	mud::Type* DECL mud_ValueTrack_mud_vec3__type() {
		return &mud::type<mud::ValueTrack<mud::vec3>>();
	}
	mud::ValueTrack<mud::vec3>* DECL mud_ValueTrack_mud_vec3__construct_0() {
		return new mud::ValueTrack<mud::vec3>();
	}
	mud::ValueTrack<mud::vec3>* DECL mud_ValueTrack_mud_vec3__construct_4(mud::TrackMode mode, mud::ValueCurve<mud::vec3>* curve, mud::ValueCurve<mud::vec3>* min_curve, mud::ValueCurve<mud::vec3>* max_curve) {
		return new mud::ValueTrack<mud::vec3>(mode, *curve, *min_curve, *max_curve);
	}
	mud::TrackMode DECL mud_ValueTrack_mud_vec3__get_mode(mud::ValueTrack<mud::vec3>* self) {
		return self->m_mode;
	}
	void DECL mud_ValueTrack_mud_vec3__set_mode(mud::ValueTrack<mud::vec3>* self, mud::TrackMode value) {
		self->m_mode = value;
	}
	mud::vec3* DECL mud_ValueTrack_mud_vec3__get_value(mud::ValueTrack<mud::vec3>* self) {
		static mud::vec3 temp;
		return (temp = self->m_value, &temp);
	}
	void DECL mud_ValueTrack_mud_vec3__set_value(mud::ValueTrack<mud::vec3>* self, mud::vec3* value) {
		self->m_value = *value;
	}
	mud::vec3* DECL mud_ValueTrack_mud_vec3__get_min(mud::ValueTrack<mud::vec3>* self) {
		static mud::vec3 temp;
		return (temp = self->m_min, &temp);
	}
	void DECL mud_ValueTrack_mud_vec3__set_min(mud::ValueTrack<mud::vec3>* self, mud::vec3* value) {
		self->m_min = *value;
	}
	mud::vec3* DECL mud_ValueTrack_mud_vec3__get_max(mud::ValueTrack<mud::vec3>* self) {
		static mud::vec3 temp;
		return (temp = self->m_max, &temp);
	}
	void DECL mud_ValueTrack_mud_vec3__set_max(mud::ValueTrack<mud::vec3>* self, mud::vec3* value) {
		self->m_max = *value;
	}
	mud::ValueCurve<mud::vec3>* DECL mud_ValueTrack_mud_vec3__get_curve(mud::ValueTrack<mud::vec3>* self) {
		static mud::ValueCurve<mud::vec3> temp;
		return (temp = self->m_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_vec3__set_curve(mud::ValueTrack<mud::vec3>* self, mud::ValueCurve<mud::vec3>* value) {
		self->m_curve = *value;
	}
	mud::ValueCurve<mud::vec3>* DECL mud_ValueTrack_mud_vec3__get_min_curve(mud::ValueTrack<mud::vec3>* self) {
		static mud::ValueCurve<mud::vec3> temp;
		return (temp = self->m_min_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_vec3__set_min_curve(mud::ValueTrack<mud::vec3>* self, mud::ValueCurve<mud::vec3>* value) {
		self->m_min_curve = *value;
	}
	mud::ValueCurve<mud::vec3>* DECL mud_ValueTrack_mud_vec3__get_max_curve(mud::ValueTrack<mud::vec3>* self) {
		static mud::ValueCurve<mud::vec3> temp;
		return (temp = self->m_max_curve, &temp);
	}
	void DECL mud_ValueTrack_mud_vec3__set_max_curve(mud::ValueTrack<mud::vec3>* self, mud::ValueCurve<mud::vec3>* value) {
		self->m_max_curve = *value;
	}
	void DECL mud_ValueTrack_mud_vec3__destroy(mud::ValueTrack<mud::vec3>* self) {
		delete self;
	}
	// ValueTrack<uint32_t>
	mud::Type* DECL mud_ValueTrack_uint32_t__type() {
		return &mud::type<mud::ValueTrack<uint32_t>>();
	}
	mud::ValueTrack<uint32_t>* DECL mud_ValueTrack_uint32_t__construct_0() {
		return new mud::ValueTrack<uint32_t>();
	}
	mud::ValueTrack<uint32_t>* DECL mud_ValueTrack_uint32_t__construct_4(mud::TrackMode mode, mud::ValueCurve<uint32_t>* curve, mud::ValueCurve<uint32_t>* min_curve, mud::ValueCurve<uint32_t>* max_curve) {
		return new mud::ValueTrack<uint32_t>(mode, *curve, *min_curve, *max_curve);
	}
	mud::TrackMode DECL mud_ValueTrack_uint32_t__get_mode(mud::ValueTrack<uint32_t>* self) {
		return self->m_mode;
	}
	void DECL mud_ValueTrack_uint32_t__set_mode(mud::ValueTrack<uint32_t>* self, mud::TrackMode value) {
		self->m_mode = value;
	}
	uint32_t DECL mud_ValueTrack_uint32_t__get_value(mud::ValueTrack<uint32_t>* self) {
		return self->m_value;
	}
	void DECL mud_ValueTrack_uint32_t__set_value(mud::ValueTrack<uint32_t>* self, uint32_t value) {
		self->m_value = value;
	}
	uint32_t DECL mud_ValueTrack_uint32_t__get_min(mud::ValueTrack<uint32_t>* self) {
		return self->m_min;
	}
	void DECL mud_ValueTrack_uint32_t__set_min(mud::ValueTrack<uint32_t>* self, uint32_t value) {
		self->m_min = value;
	}
	uint32_t DECL mud_ValueTrack_uint32_t__get_max(mud::ValueTrack<uint32_t>* self) {
		return self->m_max;
	}
	void DECL mud_ValueTrack_uint32_t__set_max(mud::ValueTrack<uint32_t>* self, uint32_t value) {
		self->m_max = value;
	}
	mud::ValueCurve<uint32_t>* DECL mud_ValueTrack_uint32_t__get_curve(mud::ValueTrack<uint32_t>* self) {
		static mud::ValueCurve<uint32_t> temp;
		return (temp = self->m_curve, &temp);
	}
	void DECL mud_ValueTrack_uint32_t__set_curve(mud::ValueTrack<uint32_t>* self, mud::ValueCurve<uint32_t>* value) {
		self->m_curve = *value;
	}
	mud::ValueCurve<uint32_t>* DECL mud_ValueTrack_uint32_t__get_min_curve(mud::ValueTrack<uint32_t>* self) {
		static mud::ValueCurve<uint32_t> temp;
		return (temp = self->m_min_curve, &temp);
	}
	void DECL mud_ValueTrack_uint32_t__set_min_curve(mud::ValueTrack<uint32_t>* self, mud::ValueCurve<uint32_t>* value) {
		self->m_min_curve = *value;
	}
	mud::ValueCurve<uint32_t>* DECL mud_ValueTrack_uint32_t__get_max_curve(mud::ValueTrack<uint32_t>* self) {
		static mud::ValueCurve<uint32_t> temp;
		return (temp = self->m_max_curve, &temp);
	}
	void DECL mud_ValueTrack_uint32_t__set_max_curve(mud::ValueTrack<uint32_t>* self, mud::ValueCurve<uint32_t>* value) {
		self->m_max_curve = *value;
	}
	void DECL mud_ValueTrack_uint32_t__destroy(mud::ValueTrack<uint32_t>* self) {
		delete self;
	}
	// mat3
	mud::Type* DECL mud_mat3__type() {
		return &mud::type<mud::mat3>();
	}
	mud::mat3* DECL mud_mat3__construct_0() {
		return new mud::mat3();
	}
	mud::mat3* DECL mud_mat3__construct_3(const mud::float3* x, const mud::float3* y, const mud::float3* z) {
		return new mud::mat3(*x, *y, *z);
	}
	mud::mat3* DECL mud_mat3__construct_9(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8) {
		return new mud::mat3(f0, f1, f2, f3, f4, f5, f6, f7, f8);
	}
	float DECL mud_mat3__get_f(mud::mat3* self, unsigned int index) {
		return self->f[index];
	}
	void DECL mud_mat3__set_f(mud::mat3* self, unsigned int index, float value) {
		self->f[index] = value;
	}
	void DECL mud_mat3__destroy(mud::mat3* self) {
		delete self;
	}
	// mat4
	mud::Type* DECL mud_mat4__type() {
		return &mud::type<mud::mat4>();
	}
	mud::mat4* DECL mud_mat4__construct_0() {
		return new mud::mat4();
	}
	mud::mat4* DECL mud_mat4__construct_4(const mud::float4* x, const mud::float4* y, const mud::float4* z, const mud::float4* w) {
		return new mud::mat4(*x, *y, *z, *w);
	}
	mud::mat4* DECL mud_mat4__construct_16(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15) {
		return new mud::mat4(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15);
	}
	float DECL mud_mat4__get_f(mud::mat4* self, unsigned int index) {
		return self->f[index];
	}
	void DECL mud_mat4__set_f(mud::mat4* self, unsigned int index, float value) {
		self->f[index] = value;
	}
	void DECL mud_mat4__destroy(mud::mat4* self) {
		delete self;
	}
	// v2<bool>
	mud::Type* DECL mud_v2_bool__type() {
		return &mud::type<mud::v2<bool>>();
	}
	mud::v2<bool>* DECL mud_v2_bool__construct_0() {
		return new mud::v2<bool>();
	}
	mud::v2<bool>* DECL mud_v2_bool__construct_1(bool v) {
		return new mud::v2<bool>(v);
	}
	mud::v2<bool>* DECL mud_v2_bool__construct_2(bool x, bool y) {
		return new mud::v2<bool>(x, y);
	}
	bool DECL mud_v2_bool__get_x(mud::v2<bool>* self) {
		return self->x;
	}
	void DECL mud_v2_bool__set_x(mud::v2<bool>* self, bool value) {
		self->x = value;
	}
	bool DECL mud_v2_bool__get_y(mud::v2<bool>* self) {
		return self->y;
	}
	void DECL mud_v2_bool__set_y(mud::v2<bool>* self, bool value) {
		self->y = value;
	}
	void DECL mud_v2_bool__destroy(mud::v2<bool>* self) {
		delete self;
	}
	// v2<float>
	mud::Type* DECL mud_v2_float__type() {
		return &mud::type<mud::v2<float>>();
	}
	mud::v2<float>* DECL mud_v2_float__construct_0() {
		return new mud::v2<float>();
	}
	mud::v2<float>* DECL mud_v2_float__construct_1(float v) {
		return new mud::v2<float>(v);
	}
	mud::v2<float>* DECL mud_v2_float__construct_2(float x, float y) {
		return new mud::v2<float>(x, y);
	}
	float DECL mud_v2_float__get_x(mud::v2<float>* self) {
		return self->x;
	}
	void DECL mud_v2_float__set_x(mud::v2<float>* self, float value) {
		self->x = value;
	}
	float DECL mud_v2_float__get_y(mud::v2<float>* self) {
		return self->y;
	}
	void DECL mud_v2_float__set_y(mud::v2<float>* self, float value) {
		self->y = value;
	}
	void DECL mud_v2_float__destroy(mud::v2<float>* self) {
		delete self;
	}
	// v2<int>
	mud::Type* DECL mud_v2_int__type() {
		return &mud::type<mud::v2<int>>();
	}
	mud::v2<int>* DECL mud_v2_int__construct_0() {
		return new mud::v2<int>();
	}
	mud::v2<int>* DECL mud_v2_int__construct_1(int v) {
		return new mud::v2<int>(v);
	}
	mud::v2<int>* DECL mud_v2_int__construct_2(int x, int y) {
		return new mud::v2<int>(x, y);
	}
	int DECL mud_v2_int__get_x(mud::v2<int>* self) {
		return self->x;
	}
	void DECL mud_v2_int__set_x(mud::v2<int>* self, int value) {
		self->x = value;
	}
	int DECL mud_v2_int__get_y(mud::v2<int>* self) {
		return self->y;
	}
	void DECL mud_v2_int__set_y(mud::v2<int>* self, int value) {
		self->y = value;
	}
	void DECL mud_v2_int__destroy(mud::v2<int>* self) {
		delete self;
	}
	// v2<uint>
	mud::Type* DECL mud_v2_uint__type() {
		return &mud::type<mud::v2<uint>>();
	}
	mud::v2<uint>* DECL mud_v2_uint__construct_0() {
		return new mud::v2<uint>();
	}
	mud::v2<uint>* DECL mud_v2_uint__construct_1(uint v) {
		return new mud::v2<uint>(v);
	}
	mud::v2<uint>* DECL mud_v2_uint__construct_2(uint x, uint y) {
		return new mud::v2<uint>(x, y);
	}
	uint DECL mud_v2_uint__get_x(mud::v2<uint>* self) {
		return self->x;
	}
	void DECL mud_v2_uint__set_x(mud::v2<uint>* self, uint value) {
		self->x = value;
	}
	uint DECL mud_v2_uint__get_y(mud::v2<uint>* self) {
		return self->y;
	}
	void DECL mud_v2_uint__set_y(mud::v2<uint>* self, uint value) {
		self->y = value;
	}
	void DECL mud_v2_uint__destroy(mud::v2<uint>* self) {
		delete self;
	}
	// v3<bool>
	mud::Type* DECL mud_v3_bool__type() {
		return &mud::type<mud::v3<bool>>();
	}
	mud::v3<bool>* DECL mud_v3_bool__construct_0() {
		return new mud::v3<bool>();
	}
	mud::v3<bool>* DECL mud_v3_bool__construct_1(bool v) {
		return new mud::v3<bool>(v);
	}
	mud::v3<bool>* DECL mud_v3_bool__construct_3(bool x, bool y, bool z) {
		return new mud::v3<bool>(x, y, z);
	}
	bool DECL mud_v3_bool__get_x(mud::v3<bool>* self) {
		return self->x;
	}
	void DECL mud_v3_bool__set_x(mud::v3<bool>* self, bool value) {
		self->x = value;
	}
	bool DECL mud_v3_bool__get_y(mud::v3<bool>* self) {
		return self->y;
	}
	void DECL mud_v3_bool__set_y(mud::v3<bool>* self, bool value) {
		self->y = value;
	}
	bool DECL mud_v3_bool__get_z(mud::v3<bool>* self) {
		return self->z;
	}
	void DECL mud_v3_bool__set_z(mud::v3<bool>* self, bool value) {
		self->z = value;
	}
	void DECL mud_v3_bool__destroy(mud::v3<bool>* self) {
		delete self;
	}
	// v3<float>
	mud::Type* DECL mud_v3_float__type() {
		return &mud::type<mud::v3<float>>();
	}
	mud::v3<float>* DECL mud_v3_float__construct_0() {
		return new mud::v3<float>();
	}
	mud::v3<float>* DECL mud_v3_float__construct_1(float v) {
		return new mud::v3<float>(v);
	}
	mud::v3<float>* DECL mud_v3_float__construct_3(float x, float y, float z) {
		return new mud::v3<float>(x, y, z);
	}
	float DECL mud_v3_float__get_x(mud::v3<float>* self) {
		return self->x;
	}
	void DECL mud_v3_float__set_x(mud::v3<float>* self, float value) {
		self->x = value;
	}
	float DECL mud_v3_float__get_y(mud::v3<float>* self) {
		return self->y;
	}
	void DECL mud_v3_float__set_y(mud::v3<float>* self, float value) {
		self->y = value;
	}
	float DECL mud_v3_float__get_z(mud::v3<float>* self) {
		return self->z;
	}
	void DECL mud_v3_float__set_z(mud::v3<float>* self, float value) {
		self->z = value;
	}
	void DECL mud_v3_float__destroy(mud::v3<float>* self) {
		delete self;
	}
	// v3<int>
	mud::Type* DECL mud_v3_int__type() {
		return &mud::type<mud::v3<int>>();
	}
	mud::v3<int>* DECL mud_v3_int__construct_0() {
		return new mud::v3<int>();
	}
	mud::v3<int>* DECL mud_v3_int__construct_1(int v) {
		return new mud::v3<int>(v);
	}
	mud::v3<int>* DECL mud_v3_int__construct_3(int x, int y, int z) {
		return new mud::v3<int>(x, y, z);
	}
	int DECL mud_v3_int__get_x(mud::v3<int>* self) {
		return self->x;
	}
	void DECL mud_v3_int__set_x(mud::v3<int>* self, int value) {
		self->x = value;
	}
	int DECL mud_v3_int__get_y(mud::v3<int>* self) {
		return self->y;
	}
	void DECL mud_v3_int__set_y(mud::v3<int>* self, int value) {
		self->y = value;
	}
	int DECL mud_v3_int__get_z(mud::v3<int>* self) {
		return self->z;
	}
	void DECL mud_v3_int__set_z(mud::v3<int>* self, int value) {
		self->z = value;
	}
	void DECL mud_v3_int__destroy(mud::v3<int>* self) {
		delete self;
	}
	// v3<uint>
	mud::Type* DECL mud_v3_uint__type() {
		return &mud::type<mud::v3<uint>>();
	}
	mud::v3<uint>* DECL mud_v3_uint__construct_0() {
		return new mud::v3<uint>();
	}
	mud::v3<uint>* DECL mud_v3_uint__construct_1(uint v) {
		return new mud::v3<uint>(v);
	}
	mud::v3<uint>* DECL mud_v3_uint__construct_3(uint x, uint y, uint z) {
		return new mud::v3<uint>(x, y, z);
	}
	uint DECL mud_v3_uint__get_x(mud::v3<uint>* self) {
		return self->x;
	}
	void DECL mud_v3_uint__set_x(mud::v3<uint>* self, uint value) {
		self->x = value;
	}
	uint DECL mud_v3_uint__get_y(mud::v3<uint>* self) {
		return self->y;
	}
	void DECL mud_v3_uint__set_y(mud::v3<uint>* self, uint value) {
		self->y = value;
	}
	uint DECL mud_v3_uint__get_z(mud::v3<uint>* self) {
		return self->z;
	}
	void DECL mud_v3_uint__set_z(mud::v3<uint>* self, uint value) {
		self->z = value;
	}
	void DECL mud_v3_uint__destroy(mud::v3<uint>* self) {
		delete self;
	}
	// v4<bool>
	mud::Type* DECL mud_v4_bool__type() {
		return &mud::type<mud::v4<bool>>();
	}
	mud::v4<bool>* DECL mud_v4_bool__construct_0() {
		return new mud::v4<bool>();
	}
	mud::v4<bool>* DECL mud_v4_bool__construct_1(bool v) {
		return new mud::v4<bool>(v);
	}
	mud::v4<bool>* DECL mud_v4_bool__construct_4(bool x, bool y, bool z, bool w) {
		return new mud::v4<bool>(x, y, z, w);
	}
	bool DECL mud_v4_bool__get_x(mud::v4<bool>* self) {
		return self->x;
	}
	void DECL mud_v4_bool__set_x(mud::v4<bool>* self, bool value) {
		self->x = value;
	}
	bool DECL mud_v4_bool__get_y(mud::v4<bool>* self) {
		return self->y;
	}
	void DECL mud_v4_bool__set_y(mud::v4<bool>* self, bool value) {
		self->y = value;
	}
	bool DECL mud_v4_bool__get_z(mud::v4<bool>* self) {
		return self->z;
	}
	void DECL mud_v4_bool__set_z(mud::v4<bool>* self, bool value) {
		self->z = value;
	}
	bool DECL mud_v4_bool__get_w(mud::v4<bool>* self) {
		return self->w;
	}
	void DECL mud_v4_bool__set_w(mud::v4<bool>* self, bool value) {
		self->w = value;
	}
	void DECL mud_v4_bool__destroy(mud::v4<bool>* self) {
		delete self;
	}
	// v4<float>
	mud::Type* DECL mud_v4_float__type() {
		return &mud::type<mud::v4<float>>();
	}
	mud::v4<float>* DECL mud_v4_float__construct_0() {
		return new mud::v4<float>();
	}
	mud::v4<float>* DECL mud_v4_float__construct_1(float v) {
		return new mud::v4<float>(v);
	}
	mud::v4<float>* DECL mud_v4_float__construct_4(float x, float y, float z, float w) {
		return new mud::v4<float>(x, y, z, w);
	}
	float DECL mud_v4_float__get_x(mud::v4<float>* self) {
		return self->x;
	}
	void DECL mud_v4_float__set_x(mud::v4<float>* self, float value) {
		self->x = value;
	}
	float DECL mud_v4_float__get_y(mud::v4<float>* self) {
		return self->y;
	}
	void DECL mud_v4_float__set_y(mud::v4<float>* self, float value) {
		self->y = value;
	}
	float DECL mud_v4_float__get_z(mud::v4<float>* self) {
		return self->z;
	}
	void DECL mud_v4_float__set_z(mud::v4<float>* self, float value) {
		self->z = value;
	}
	float DECL mud_v4_float__get_w(mud::v4<float>* self) {
		return self->w;
	}
	void DECL mud_v4_float__set_w(mud::v4<float>* self, float value) {
		self->w = value;
	}
	void DECL mud_v4_float__destroy(mud::v4<float>* self) {
		delete self;
	}
	// v4<int>
	mud::Type* DECL mud_v4_int__type() {
		return &mud::type<mud::v4<int>>();
	}
	mud::v4<int>* DECL mud_v4_int__construct_0() {
		return new mud::v4<int>();
	}
	mud::v4<int>* DECL mud_v4_int__construct_1(int v) {
		return new mud::v4<int>(v);
	}
	mud::v4<int>* DECL mud_v4_int__construct_4(int x, int y, int z, int w) {
		return new mud::v4<int>(x, y, z, w);
	}
	int DECL mud_v4_int__get_x(mud::v4<int>* self) {
		return self->x;
	}
	void DECL mud_v4_int__set_x(mud::v4<int>* self, int value) {
		self->x = value;
	}
	int DECL mud_v4_int__get_y(mud::v4<int>* self) {
		return self->y;
	}
	void DECL mud_v4_int__set_y(mud::v4<int>* self, int value) {
		self->y = value;
	}
	int DECL mud_v4_int__get_z(mud::v4<int>* self) {
		return self->z;
	}
	void DECL mud_v4_int__set_z(mud::v4<int>* self, int value) {
		self->z = value;
	}
	int DECL mud_v4_int__get_w(mud::v4<int>* self) {
		return self->w;
	}
	void DECL mud_v4_int__set_w(mud::v4<int>* self, int value) {
		self->w = value;
	}
	void DECL mud_v4_int__destroy(mud::v4<int>* self) {
		delete self;
	}
	// v4<uint>
	mud::Type* DECL mud_v4_uint__type() {
		return &mud::type<mud::v4<uint>>();
	}
	mud::v4<uint>* DECL mud_v4_uint__construct_0() {
		return new mud::v4<uint>();
	}
	mud::v4<uint>* DECL mud_v4_uint__construct_1(uint v) {
		return new mud::v4<uint>(v);
	}
	mud::v4<uint>* DECL mud_v4_uint__construct_4(uint x, uint y, uint z, uint w) {
		return new mud::v4<uint>(x, y, z, w);
	}
	uint DECL mud_v4_uint__get_x(mud::v4<uint>* self) {
		return self->x;
	}
	void DECL mud_v4_uint__set_x(mud::v4<uint>* self, uint value) {
		self->x = value;
	}
	uint DECL mud_v4_uint__get_y(mud::v4<uint>* self) {
		return self->y;
	}
	void DECL mud_v4_uint__set_y(mud::v4<uint>* self, uint value) {
		self->y = value;
	}
	uint DECL mud_v4_uint__get_z(mud::v4<uint>* self) {
		return self->z;
	}
	void DECL mud_v4_uint__set_z(mud::v4<uint>* self, uint value) {
		self->z = value;
	}
	uint DECL mud_v4_uint__get_w(mud::v4<uint>* self) {
		return self->w;
	}
	void DECL mud_v4_uint__set_w(mud::v4<uint>* self, uint value) {
		self->w = value;
	}
	void DECL mud_v4_uint__destroy(mud::v4<uint>* self) {
		delete self;
	}
	// Sprite
	mud::Type* DECL mud_Sprite__type() {
		return &mud::type<mud::Sprite>();
	}
	void DECL mud_Sprite__destroy(mud::Sprite* self) {
		delete self;
	}
	// SpriteAtlas
	mud::Type* DECL mud_SpriteAtlas__type() {
		return &mud::type<mud::SpriteAtlas>();
	}
	void DECL mud_SpriteAtlas__destroy(mud::SpriteAtlas* self) {
		delete self;
	}
	// TextureAtlas
	mud::Type* DECL mud_TextureAtlas__type() {
		return &mud::type<mud::TextureAtlas>();
	}
	void DECL mud_TextureAtlas__destroy(mud::TextureAtlas* self) {
		delete self;
	}
	// quat
	mud::Type* DECL mud_quat__type() {
		return &mud::type<mud::quat>();
	}
	mud::quat* DECL mud_quat__construct_0() {
		return new mud::quat();
	}
	mud::quat* DECL mud_quat__construct_1(const mud::float3* euler_angles) {
		return new mud::quat(*euler_angles);
	}
	mud::quat* DECL mud_quat__construct_4(float x, float y, float z, float w) {
		return new mud::quat(x, y, z, w);
	}
	void DECL mud_quat__destroy(mud::quat* self) {
		delete self;
	}
	uint32_t DECL mud_to_rgba_1(const mud::Colour* colour) {
		return mud::to_rgba(*colour);
	}
	uint32_t DECL mud_to_abgr_1(const mud::Colour* colour) {
		return mud::to_abgr(*colour);
	}
	mud::Colour* DECL mud_from_rgba_1(uint32_t colour) {
		static mud::Colour temp;
		return (temp = mud::from_rgba(colour), &temp);
	}
	mud::Colour* DECL mud_from_abgr_1(uint32_t colour) {
		static mud::Colour temp;
		return (temp = mud::from_abgr(colour), &temp);
	}
	mud::Colour* DECL mud_to_linear_1(const mud::Colour* colour) {
		static mud::Colour temp;
		return (temp = mud::to_linear(*colour), &temp);
	}
	mud::Colour* DECL mud_to_gamma_1(const mud::Colour* colour) {
		static mud::Colour temp;
		return (temp = mud::to_gamma(*colour), &temp);
	}
	mud::Colour* DECL mud_to_srgb_1(const mud::Colour* colour) {
		static mud::Colour temp;
		return (temp = mud::to_srgb(*colour), &temp);
	}
	mud::Colour* DECL mud_hsl_to_rgb_3(float h, float s, float l) {
		static mud::Colour temp;
		return (temp = mud::hsl_to_rgb(h, s, l), &temp);
	}
	mud::Colour* DECL mud_rgb_to_hsl_3(float r, float g, float b) {
		static mud::Colour temp;
		return (temp = mud::rgb_to_hsl(r, g, b), &temp);
	}
	mud::Colour* DECL mud_rgba_to_hsla_1(const mud::Colour* colour) {
		static mud::Colour temp;
		return (temp = mud::rgba_to_hsla(*colour), &temp);
	}
	mud::Colour* DECL mud_hsla_to_rgba_1(const mud::Colour* colour) {
		static mud::Colour temp;
		return (temp = mud::hsla_to_rgba(*colour), &temp);
	}
	float DECL sinf_1(float a) {
		return sinf(a);
	}
	float DECL cosf_1(float a) {
		return cosf(a);
	}
	double DECL sin_1(double a) {
		return sin(a);
	}
	double DECL cos_1(double a) {
		return cos(a);
	}
	float DECL mud_add_2(float a, float b) {
		return mud::add(a, b);
	}
	float DECL mud_subtract_2(float a, float b) {
		return mud::subtract(a, b);
	}
	float DECL mud_multiply_2(float a, float b) {
		return mud::multiply(a, b);
	}
	float DECL mud_divide_2(float a, float b) {
		return mud::divide(a, b);
	}
	float DECL mud_nsinf_1(float a) {
		return mud::nsinf(a);
	}
	float DECL mud_ncosf_1(float a) {
		return mud::ncosf(a);
	}
	double DECL mud_nsin_1(double a) {
		return mud::nsin(a);
	}
	double DECL mud_ncos_1(double a) {
		return mud::ncos(a);
	}
	mud::quat* DECL mud_look_dir_1(const mud::vec3* direction) {
		static mud::quat temp;
		return (temp = mud::look_dir(*direction), &temp);
	}
	mud::quat* DECL mud_look_dir_2(const mud::vec3* direction, const mud::vec3* forward) {
		static mud::quat temp;
		return (temp = mud::look_dir(*direction, *forward), &temp);
	}
	mud::quat* DECL mud_look_at_2(const mud::vec3* eye, const mud::vec3* target) {
		static mud::quat temp;
		return (temp = mud::look_at(*eye, *target), &temp);
	}
	mud::quat* DECL mud_look_at_3(const mud::vec3* eye, const mud::vec3* target, const mud::vec3* forward) {
		static mud::quat temp;
		return (temp = mud::look_at(*eye, *target, *forward), &temp);
	}
	mud::vec3* DECL mud_grid_center_2(const mud::uvec3* coord, const mud::vec3* cell_size) {
		static mud::vec3 temp;
		return (temp = mud::grid_center(*coord, *cell_size), &temp);
	}
	// Axes
	mud::Axes DECL mud_Axes_None() {
		return mud::Axes::None;
	}
	mud::Axes DECL mud_Axes_X() {
		return mud::Axes::X;
	}
	mud::Axes DECL mud_Axes_Y() {
		return mud::Axes::Y;
	}
	mud::Axes DECL mud_Axes_Z() {
		return mud::Axes::Z;
	}
	// Axis
	mud::Axis DECL mud_Axis_X() {
		return mud::Axis::X;
	}
	mud::Axis DECL mud_Axis_Y() {
		return mud::Axis::Y;
	}
	mud::Axis DECL mud_Axis_Z() {
		return mud::Axis::Z;
	}
	// Clockwise
	mud::Clockwise DECL mud_Clockwise_CLOCKWISE() {
		return mud::CLOCKWISE;
	}
	mud::Clockwise DECL mud_Clockwise_ANTI_CLOCKWISE() {
		return mud::ANTI_CLOCKWISE;
	}
	// Side
	mud::Side DECL mud_Side_Right() {
		return mud::Side::Right;
	}
	mud::Side DECL mud_Side_Left() {
		return mud::Side::Left;
	}
	mud::Side DECL mud_Side_Up() {
		return mud::Side::Up;
	}
	mud::Side DECL mud_Side_Down() {
		return mud::Side::Down;
	}
	mud::Side DECL mud_Side_Back() {
		return mud::Side::Back;
	}
	mud::Side DECL mud_Side_Front() {
		return mud::Side::Front;
	}
	// SignedAxis
	mud::SignedAxis DECL mud_SignedAxis_PlusX() {
		return mud::SignedAxis::PlusX;
	}
	mud::SignedAxis DECL mud_SignedAxis_MinusX() {
		return mud::SignedAxis::MinusX;
	}
	mud::SignedAxis DECL mud_SignedAxis_PlusY() {
		return mud::SignedAxis::PlusY;
	}
	mud::SignedAxis DECL mud_SignedAxis_MinusY() {
		return mud::SignedAxis::MinusY;
	}
	mud::SignedAxis DECL mud_SignedAxis_PlusZ() {
		return mud::SignedAxis::PlusZ;
	}
	mud::SignedAxis DECL mud_SignedAxis_MinusZ() {
		return mud::SignedAxis::MinusZ;
	}
	// Spectrum
	mud::Spectrum DECL mud_Spectrum_Value() {
		return mud::Spectrum::Value;
	}
	mud::Spectrum DECL mud_Spectrum_Hue() {
		return mud::Spectrum::Hue;
	}
	// TrackMode
	mud::TrackMode DECL mud_TrackMode_Constant() {
		return mud::TrackMode::Constant;
	}
	mud::TrackMode DECL mud_TrackMode_ConstantRandom() {
		return mud::TrackMode::ConstantRandom;
	}
	mud::TrackMode DECL mud_TrackMode_Curve() {
		return mud::TrackMode::Curve;
	}
	mud::TrackMode DECL mud_TrackMode_CurveRandom() {
		return mud::TrackMode::CurveRandom;
	}
	
}


