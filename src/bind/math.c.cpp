#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// v2<float>
	two::Type* DECL two_v2_float__type() {
		return &two::type<two::v2<float>>();
	}
	two::v2<float>* DECL two_v2_float__construct_0() {
		return new two::v2<float>();
	}
	two::v2<float>* DECL two_v2_float__construct_1(float v) {
		return new two::v2<float>(v);
	}
	two::v2<float>* DECL two_v2_float__construct_2(float x, float y) {
		return new two::v2<float>(x, y);
	}
	float DECL two_v2_float__get_x(two::v2<float>* self) {
		return self->x;
	}
	void DECL two_v2_float__set_x(two::v2<float>* self, float value) {
		self->x = value;
	}
	float DECL two_v2_float__get_y(two::v2<float>* self) {
		return self->y;
	}
	void DECL two_v2_float__set_y(two::v2<float>* self, float value) {
		self->y = value;
	}
	void DECL two_v2_float__destroy(two::v2<float>* self) {
		delete self;
	}
	// v3<float>
	two::Type* DECL two_v3_float__type() {
		return &two::type<two::v3<float>>();
	}
	two::v3<float>* DECL two_v3_float__construct_0() {
		return new two::v3<float>();
	}
	two::v3<float>* DECL two_v3_float__construct_1(float v) {
		return new two::v3<float>(v);
	}
	two::v3<float>* DECL two_v3_float__construct_3(float x, float y, float z) {
		return new two::v3<float>(x, y, z);
	}
	float DECL two_v3_float__get_x(two::v3<float>* self) {
		return self->x;
	}
	void DECL two_v3_float__set_x(two::v3<float>* self, float value) {
		self->x = value;
	}
	float DECL two_v3_float__get_y(two::v3<float>* self) {
		return self->y;
	}
	void DECL two_v3_float__set_y(two::v3<float>* self, float value) {
		self->y = value;
	}
	float DECL two_v3_float__get_z(two::v3<float>* self) {
		return self->z;
	}
	void DECL two_v3_float__set_z(two::v3<float>* self, float value) {
		self->z = value;
	}
	void DECL two_v3_float__destroy(two::v3<float>* self) {
		delete self;
	}
	// v4<float>
	two::Type* DECL two_v4_float__type() {
		return &two::type<two::v4<float>>();
	}
	two::v4<float>* DECL two_v4_float__construct_0() {
		return new two::v4<float>();
	}
	two::v4<float>* DECL two_v4_float__construct_1(float v) {
		return new two::v4<float>(v);
	}
	two::v4<float>* DECL two_v4_float__construct_4(float x, float y, float z, float w) {
		return new two::v4<float>(x, y, z, w);
	}
	float DECL two_v4_float__get_x(two::v4<float>* self) {
		return self->x;
	}
	void DECL two_v4_float__set_x(two::v4<float>* self, float value) {
		self->x = value;
	}
	float DECL two_v4_float__get_y(two::v4<float>* self) {
		return self->y;
	}
	void DECL two_v4_float__set_y(two::v4<float>* self, float value) {
		self->y = value;
	}
	float DECL two_v4_float__get_z(two::v4<float>* self) {
		return self->z;
	}
	void DECL two_v4_float__set_z(two::v4<float>* self, float value) {
		self->z = value;
	}
	float DECL two_v4_float__get_w(two::v4<float>* self) {
		return self->w;
	}
	void DECL two_v4_float__set_w(two::v4<float>* self, float value) {
		self->w = value;
	}
	void DECL two_v4_float__destroy(two::v4<float>* self) {
		delete self;
	}
	// v2<int>
	two::Type* DECL two_v2_int__type() {
		return &two::type<two::v2<int>>();
	}
	two::v2<int>* DECL two_v2_int__construct_0() {
		return new two::v2<int>();
	}
	two::v2<int>* DECL two_v2_int__construct_1(int v) {
		return new two::v2<int>(v);
	}
	two::v2<int>* DECL two_v2_int__construct_2(int x, int y) {
		return new two::v2<int>(x, y);
	}
	int DECL two_v2_int__get_x(two::v2<int>* self) {
		return self->x;
	}
	void DECL two_v2_int__set_x(two::v2<int>* self, int value) {
		self->x = value;
	}
	int DECL two_v2_int__get_y(two::v2<int>* self) {
		return self->y;
	}
	void DECL two_v2_int__set_y(two::v2<int>* self, int value) {
		self->y = value;
	}
	void DECL two_v2_int__destroy(two::v2<int>* self) {
		delete self;
	}
	// v3<int>
	two::Type* DECL two_v3_int__type() {
		return &two::type<two::v3<int>>();
	}
	two::v3<int>* DECL two_v3_int__construct_0() {
		return new two::v3<int>();
	}
	two::v3<int>* DECL two_v3_int__construct_1(int v) {
		return new two::v3<int>(v);
	}
	two::v3<int>* DECL two_v3_int__construct_3(int x, int y, int z) {
		return new two::v3<int>(x, y, z);
	}
	int DECL two_v3_int__get_x(two::v3<int>* self) {
		return self->x;
	}
	void DECL two_v3_int__set_x(two::v3<int>* self, int value) {
		self->x = value;
	}
	int DECL two_v3_int__get_y(two::v3<int>* self) {
		return self->y;
	}
	void DECL two_v3_int__set_y(two::v3<int>* self, int value) {
		self->y = value;
	}
	int DECL two_v3_int__get_z(two::v3<int>* self) {
		return self->z;
	}
	void DECL two_v3_int__set_z(two::v3<int>* self, int value) {
		self->z = value;
	}
	void DECL two_v3_int__destroy(two::v3<int>* self) {
		delete self;
	}
	// v4<int>
	two::Type* DECL two_v4_int__type() {
		return &two::type<two::v4<int>>();
	}
	two::v4<int>* DECL two_v4_int__construct_0() {
		return new two::v4<int>();
	}
	two::v4<int>* DECL two_v4_int__construct_1(int v) {
		return new two::v4<int>(v);
	}
	two::v4<int>* DECL two_v4_int__construct_4(int x, int y, int z, int w) {
		return new two::v4<int>(x, y, z, w);
	}
	int DECL two_v4_int__get_x(two::v4<int>* self) {
		return self->x;
	}
	void DECL two_v4_int__set_x(two::v4<int>* self, int value) {
		self->x = value;
	}
	int DECL two_v4_int__get_y(two::v4<int>* self) {
		return self->y;
	}
	void DECL two_v4_int__set_y(two::v4<int>* self, int value) {
		self->y = value;
	}
	int DECL two_v4_int__get_z(two::v4<int>* self) {
		return self->z;
	}
	void DECL two_v4_int__set_z(two::v4<int>* self, int value) {
		self->z = value;
	}
	int DECL two_v4_int__get_w(two::v4<int>* self) {
		return self->w;
	}
	void DECL two_v4_int__set_w(two::v4<int>* self, int value) {
		self->w = value;
	}
	void DECL two_v4_int__destroy(two::v4<int>* self) {
		delete self;
	}
	// v2<uint>
	two::Type* DECL two_v2_uint__type() {
		return &two::type<two::v2<uint>>();
	}
	two::v2<uint>* DECL two_v2_uint__construct_0() {
		return new two::v2<uint>();
	}
	two::v2<uint>* DECL two_v2_uint__construct_1(uint v) {
		return new two::v2<uint>(v);
	}
	two::v2<uint>* DECL two_v2_uint__construct_2(uint x, uint y) {
		return new two::v2<uint>(x, y);
	}
	uint DECL two_v2_uint__get_x(two::v2<uint>* self) {
		return self->x;
	}
	void DECL two_v2_uint__set_x(two::v2<uint>* self, uint value) {
		self->x = value;
	}
	uint DECL two_v2_uint__get_y(two::v2<uint>* self) {
		return self->y;
	}
	void DECL two_v2_uint__set_y(two::v2<uint>* self, uint value) {
		self->y = value;
	}
	void DECL two_v2_uint__destroy(two::v2<uint>* self) {
		delete self;
	}
	// v3<uint>
	two::Type* DECL two_v3_uint__type() {
		return &two::type<two::v3<uint>>();
	}
	two::v3<uint>* DECL two_v3_uint__construct_0() {
		return new two::v3<uint>();
	}
	two::v3<uint>* DECL two_v3_uint__construct_1(uint v) {
		return new two::v3<uint>(v);
	}
	two::v3<uint>* DECL two_v3_uint__construct_3(uint x, uint y, uint z) {
		return new two::v3<uint>(x, y, z);
	}
	uint DECL two_v3_uint__get_x(two::v3<uint>* self) {
		return self->x;
	}
	void DECL two_v3_uint__set_x(two::v3<uint>* self, uint value) {
		self->x = value;
	}
	uint DECL two_v3_uint__get_y(two::v3<uint>* self) {
		return self->y;
	}
	void DECL two_v3_uint__set_y(two::v3<uint>* self, uint value) {
		self->y = value;
	}
	uint DECL two_v3_uint__get_z(two::v3<uint>* self) {
		return self->z;
	}
	void DECL two_v3_uint__set_z(two::v3<uint>* self, uint value) {
		self->z = value;
	}
	void DECL two_v3_uint__destroy(two::v3<uint>* self) {
		delete self;
	}
	// v4<uint>
	two::Type* DECL two_v4_uint__type() {
		return &two::type<two::v4<uint>>();
	}
	two::v4<uint>* DECL two_v4_uint__construct_0() {
		return new two::v4<uint>();
	}
	two::v4<uint>* DECL two_v4_uint__construct_1(uint v) {
		return new two::v4<uint>(v);
	}
	two::v4<uint>* DECL two_v4_uint__construct_4(uint x, uint y, uint z, uint w) {
		return new two::v4<uint>(x, y, z, w);
	}
	uint DECL two_v4_uint__get_x(two::v4<uint>* self) {
		return self->x;
	}
	void DECL two_v4_uint__set_x(two::v4<uint>* self, uint value) {
		self->x = value;
	}
	uint DECL two_v4_uint__get_y(two::v4<uint>* self) {
		return self->y;
	}
	void DECL two_v4_uint__set_y(two::v4<uint>* self, uint value) {
		self->y = value;
	}
	uint DECL two_v4_uint__get_z(two::v4<uint>* self) {
		return self->z;
	}
	void DECL two_v4_uint__set_z(two::v4<uint>* self, uint value) {
		self->z = value;
	}
	uint DECL two_v4_uint__get_w(two::v4<uint>* self) {
		return self->w;
	}
	void DECL two_v4_uint__set_w(two::v4<uint>* self, uint value) {
		self->w = value;
	}
	void DECL two_v4_uint__destroy(two::v4<uint>* self) {
		delete self;
	}
	// v2<bool>
	two::Type* DECL two_v2_bool__type() {
		return &two::type<two::v2<bool>>();
	}
	two::v2<bool>* DECL two_v2_bool__construct_0() {
		return new two::v2<bool>();
	}
	two::v2<bool>* DECL two_v2_bool__construct_1(bool v) {
		return new two::v2<bool>(v);
	}
	two::v2<bool>* DECL two_v2_bool__construct_2(bool x, bool y) {
		return new two::v2<bool>(x, y);
	}
	bool DECL two_v2_bool__get_x(two::v2<bool>* self) {
		return self->x;
	}
	void DECL two_v2_bool__set_x(two::v2<bool>* self, bool value) {
		self->x = value;
	}
	bool DECL two_v2_bool__get_y(two::v2<bool>* self) {
		return self->y;
	}
	void DECL two_v2_bool__set_y(two::v2<bool>* self, bool value) {
		self->y = value;
	}
	void DECL two_v2_bool__destroy(two::v2<bool>* self) {
		delete self;
	}
	// v3<bool>
	two::Type* DECL two_v3_bool__type() {
		return &two::type<two::v3<bool>>();
	}
	two::v3<bool>* DECL two_v3_bool__construct_0() {
		return new two::v3<bool>();
	}
	two::v3<bool>* DECL two_v3_bool__construct_1(bool v) {
		return new two::v3<bool>(v);
	}
	two::v3<bool>* DECL two_v3_bool__construct_3(bool x, bool y, bool z) {
		return new two::v3<bool>(x, y, z);
	}
	bool DECL two_v3_bool__get_x(two::v3<bool>* self) {
		return self->x;
	}
	void DECL two_v3_bool__set_x(two::v3<bool>* self, bool value) {
		self->x = value;
	}
	bool DECL two_v3_bool__get_y(two::v3<bool>* self) {
		return self->y;
	}
	void DECL two_v3_bool__set_y(two::v3<bool>* self, bool value) {
		self->y = value;
	}
	bool DECL two_v3_bool__get_z(two::v3<bool>* self) {
		return self->z;
	}
	void DECL two_v3_bool__set_z(two::v3<bool>* self, bool value) {
		self->z = value;
	}
	void DECL two_v3_bool__destroy(two::v3<bool>* self) {
		delete self;
	}
	// v4<bool>
	two::Type* DECL two_v4_bool__type() {
		return &two::type<two::v4<bool>>();
	}
	two::v4<bool>* DECL two_v4_bool__construct_0() {
		return new two::v4<bool>();
	}
	two::v4<bool>* DECL two_v4_bool__construct_1(bool v) {
		return new two::v4<bool>(v);
	}
	two::v4<bool>* DECL two_v4_bool__construct_4(bool x, bool y, bool z, bool w) {
		return new two::v4<bool>(x, y, z, w);
	}
	bool DECL two_v4_bool__get_x(two::v4<bool>* self) {
		return self->x;
	}
	void DECL two_v4_bool__set_x(two::v4<bool>* self, bool value) {
		self->x = value;
	}
	bool DECL two_v4_bool__get_y(two::v4<bool>* self) {
		return self->y;
	}
	void DECL two_v4_bool__set_y(two::v4<bool>* self, bool value) {
		self->y = value;
	}
	bool DECL two_v4_bool__get_z(two::v4<bool>* self) {
		return self->z;
	}
	void DECL two_v4_bool__set_z(two::v4<bool>* self, bool value) {
		self->z = value;
	}
	bool DECL two_v4_bool__get_w(two::v4<bool>* self) {
		return self->w;
	}
	void DECL two_v4_bool__set_w(two::v4<bool>* self, bool value) {
		self->w = value;
	}
	void DECL two_v4_bool__destroy(two::v4<bool>* self) {
		delete self;
	}
	// mat3
	two::Type* DECL two_mat3__type() {
		return &two::type<two::mat3>();
	}
	two::mat3* DECL two_mat3__construct_0() {
		return new two::mat3();
	}
	two::mat3* DECL two_mat3__construct_3(const two::float3* x, const two::float3* y, const two::float3* z) {
		return new two::mat3(*x, *y, *z);
	}
	two::mat3* DECL two_mat3__construct_9(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8) {
		return new two::mat3(f0, f1, f2, f3, f4, f5, f6, f7, f8);
	}
	float DECL two_mat3__get_f(two::mat3* self, unsigned int index) {
		return self->f[index];
	}
	void DECL two_mat3__set_f(two::mat3* self, unsigned int index, float value) {
		self->f[index] = value;
	}
	void DECL two_mat3__destroy(two::mat3* self) {
		delete self;
	}
	// mat4
	two::Type* DECL two_mat4__type() {
		return &two::type<two::mat4>();
	}
	two::mat4* DECL two_mat4__construct_0() {
		return new two::mat4();
	}
	two::mat4* DECL two_mat4__construct_4(const two::float4* x, const two::float4* y, const two::float4* z, const two::float4* w) {
		return new two::mat4(*x, *y, *z, *w);
	}
	two::mat4* DECL two_mat4__construct_16(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15) {
		return new two::mat4(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15);
	}
	float DECL two_mat4__get_f(two::mat4* self, unsigned int index) {
		return self->f[index];
	}
	void DECL two_mat4__set_f(two::mat4* self, unsigned int index, float value) {
		self->f[index] = value;
	}
	void DECL two_mat4__destroy(two::mat4* self) {
		delete self;
	}
	// quat
	two::Type* DECL two_quat__type() {
		return &two::type<two::quat>();
	}
	two::quat* DECL two_quat__construct_0() {
		return new two::quat();
	}
	two::quat* DECL two_quat__construct_1(const two::float3* euler_angles) {
		return new two::quat(*euler_angles);
	}
	two::quat* DECL two_quat__construct_4(float x, float y, float z, float w) {
		return new two::quat(x, y, z, w);
	}
	void DECL two_quat__destroy(two::quat* self) {
		delete self;
	}
	// Transform
	two::Type* DECL two_Transform__type() {
		return &two::type<two::Transform>();
	}
	two::Transform* DECL two_Transform__construct_0() {
		return new two::Transform();
	}
	two::vec3* DECL two_Transform__get_position(two::Transform* self) {
		return &self->m_position;
	}
	void DECL two_Transform__set_position(two::Transform* self, two::vec3* value) {
		self->m_position = *value;
	}
	two::quat* DECL two_Transform__get_rotation(two::Transform* self) {
		return &self->m_rotation;
	}
	void DECL two_Transform__set_rotation(two::Transform* self, two::quat* value) {
		self->m_rotation = *value;
	}
	two::vec3* DECL two_Transform__get_scale(two::Transform* self) {
		return &self->m_scale;
	}
	void DECL two_Transform__set_scale(two::Transform* self, two::vec3* value) {
		self->m_scale = *value;
	}
	void DECL two_Transform__destroy(two::Transform* self) {
		delete self;
	}
	// ColourHSL
	two::Type* DECL two_ColourHSL__type() {
		return &two::type<two::ColourHSL>();
	}
	two::ColourHSL* DECL two_ColourHSL__construct_0() {
		return new two::ColourHSL();
	}
	float DECL two_ColourHSL__get_h(two::ColourHSL* self) {
		return self->h;
	}
	void DECL two_ColourHSL__set_h(two::ColourHSL* self, float value) {
		self->h = value;
	}
	float DECL two_ColourHSL__get_s(two::ColourHSL* self) {
		return self->s;
	}
	void DECL two_ColourHSL__set_s(two::ColourHSL* self, float value) {
		self->s = value;
	}
	float DECL two_ColourHSL__get_l(two::ColourHSL* self) {
		return self->l;
	}
	void DECL two_ColourHSL__set_l(two::ColourHSL* self, float value) {
		self->l = value;
	}
	float DECL two_ColourHSL__get_a(two::ColourHSL* self) {
		return self->a;
	}
	void DECL two_ColourHSL__set_a(two::ColourHSL* self, float value) {
		self->a = value;
	}
	void DECL two_ColourHSL__destroy(two::ColourHSL* self) {
		delete self;
	}
	// Colour
	two::Type* DECL two_Colour__type() {
		return &two::type<two::Colour>();
	}
	two::Colour* DECL two_Colour__construct_0() {
		return new two::Colour();
	}
	two::Colour* DECL two_Colour__construct_1(float v) {
		return new two::Colour(v);
	}
	two::Colour* DECL two_Colour__construct_2(float v, float a) {
		return new two::Colour(v, a);
	}
	two::Colour* DECL two_Colour__construct_3(float r, float g, float b) {
		return new two::Colour(r, g, b);
	}
	two::Colour* DECL two_Colour__construct_4(float r, float g, float b, float a) {
		return new two::Colour(r, g, b, a);
	}
	float DECL two_Colour__get_r(two::Colour* self) {
		return self->r;
	}
	void DECL two_Colour__set_r(two::Colour* self, float value) {
		self->r = value;
	}
	float DECL two_Colour__get_g(two::Colour* self) {
		return self->g;
	}
	void DECL two_Colour__set_g(two::Colour* self, float value) {
		self->g = value;
	}
	float DECL two_Colour__get_b(two::Colour* self) {
		return self->b;
	}
	void DECL two_Colour__set_b(two::Colour* self, float value) {
		self->b = value;
	}
	float DECL two_Colour__get_a(two::Colour* self) {
		return self->a;
	}
	void DECL two_Colour__set_a(two::Colour* self, float value) {
		self->a = value;
	}
	void DECL two_Colour__destroy(two::Colour* self) {
		delete self;
	}
	// ValueCurve<float>
	two::Type* DECL two_ValueCurve_float__type() {
		return &two::type<two::ValueCurve<float>>();
	}
	two::ValueCurve<float>* DECL two_ValueCurve_float__construct_0() {
		return new two::ValueCurve<float>();
	}
	two::ValueCurve<float>* DECL two_ValueCurve_float__construct_1(float* keys, int keys_size) {
		return new two::ValueCurve<float>({ (float*)keys, keys_size / (sizeof(float) / sizeof(float)) });
	}
	float* DECL two_ValueCurve_float__get_keys(two::ValueCurve<float>* self) {
		return (float*)self->m_keys.data();
	}
	void DECL two_ValueCurve_float__destroy(two::ValueCurve<float>* self) {
		delete self;
	}
	// ValueCurve<uint32_t>
	two::Type* DECL two_ValueCurve_uint32_t__type() {
		return &two::type<two::ValueCurve<uint32_t>>();
	}
	two::ValueCurve<uint32_t>* DECL two_ValueCurve_uint32_t__construct_0() {
		return new two::ValueCurve<uint32_t>();
	}
	two::ValueCurve<uint32_t>* DECL two_ValueCurve_uint32_t__construct_1(uint* keys, int keys_size) {
		return new two::ValueCurve<uint32_t>({ (uint32_t*)keys, keys_size / (sizeof(uint32_t) / sizeof(uint)) });
	}
	uint* DECL two_ValueCurve_uint32_t__get_keys(two::ValueCurve<uint32_t>* self) {
		return (uint*)self->m_keys.data();
	}
	void DECL two_ValueCurve_uint32_t__destroy(two::ValueCurve<uint32_t>* self) {
		delete self;
	}
	// ValueCurve<two::vec3>
	two::Type* DECL two_ValueCurve_two_vec3__type() {
		return &two::type<two::ValueCurve<two::vec3>>();
	}
	two::ValueCurve<two::vec3>* DECL two_ValueCurve_two_vec3__construct_0() {
		return new two::ValueCurve<two::vec3>();
	}
	two::ValueCurve<two::vec3>* DECL two_ValueCurve_two_vec3__construct_1(float* keys, int keys_size) {
		return new two::ValueCurve<two::vec3>({ (two::vec3*)keys, keys_size / (sizeof(two::vec3) / sizeof(float)) });
	}
	float* DECL two_ValueCurve_two_vec3__get_keys(two::ValueCurve<two::vec3>* self) {
		return (float*)self->m_keys.data();
	}
	void DECL two_ValueCurve_two_vec3__destroy(two::ValueCurve<two::vec3>* self) {
		delete self;
	}
	// ValueCurve<two::quat>
	two::Type* DECL two_ValueCurve_two_quat__type() {
		return &two::type<two::ValueCurve<two::quat>>();
	}
	two::ValueCurve<two::quat>* DECL two_ValueCurve_two_quat__construct_0() {
		return new two::ValueCurve<two::quat>();
	}
	void DECL two_ValueCurve_two_quat__destroy(two::ValueCurve<two::quat>* self) {
		delete self;
	}
	// ValueCurve<two::Colour>
	two::Type* DECL two_ValueCurve_two_Colour__type() {
		return &two::type<two::ValueCurve<two::Colour>>();
	}
	two::ValueCurve<two::Colour>* DECL two_ValueCurve_two_Colour__construct_0() {
		return new two::ValueCurve<two::Colour>();
	}
	two::ValueCurve<two::Colour>* DECL two_ValueCurve_two_Colour__construct_1(float* keys, int keys_size) {
		return new two::ValueCurve<two::Colour>({ (two::Colour*)keys, keys_size / (sizeof(two::Colour) / sizeof(float)) });
	}
	float* DECL two_ValueCurve_two_Colour__get_keys(two::ValueCurve<two::Colour>* self) {
		return (float*)self->m_keys.data();
	}
	void DECL two_ValueCurve_two_Colour__destroy(two::ValueCurve<two::Colour>* self) {
		delete self;
	}
	// ValueTrack<two::vec3>
	two::Type* DECL two_ValueTrack_two_vec3__type() {
		return &two::type<two::ValueTrack<two::vec3>>();
	}
	two::ValueTrack<two::vec3>* DECL two_ValueTrack_two_vec3__construct_0() {
		return new two::ValueTrack<two::vec3>();
	}
	two::ValueTrack<two::vec3>* DECL two_ValueTrack_two_vec3__construct_4(two::TrackMode mode, two::ValueCurve<two::vec3>* curve, two::ValueCurve<two::vec3>* min_curve, two::ValueCurve<two::vec3>* max_curve) {
		return new two::ValueTrack<two::vec3>(mode, *curve, *min_curve, *max_curve);
	}
	two::TrackMode DECL two_ValueTrack_two_vec3__get_mode(two::ValueTrack<two::vec3>* self) {
		return self->m_mode;
	}
	void DECL two_ValueTrack_two_vec3__set_mode(two::ValueTrack<two::vec3>* self, two::TrackMode value) {
		self->m_mode = value;
	}
	two::vec3* DECL two_ValueTrack_two_vec3__get_value(two::ValueTrack<two::vec3>* self) {
		return &self->m_value;
	}
	void DECL two_ValueTrack_two_vec3__set_value(two::ValueTrack<two::vec3>* self, two::vec3* value) {
		self->m_value = *value;
	}
	two::vec3* DECL two_ValueTrack_two_vec3__get_min(two::ValueTrack<two::vec3>* self) {
		return &self->m_min;
	}
	void DECL two_ValueTrack_two_vec3__set_min(two::ValueTrack<two::vec3>* self, two::vec3* value) {
		self->m_min = *value;
	}
	two::vec3* DECL two_ValueTrack_two_vec3__get_max(two::ValueTrack<two::vec3>* self) {
		return &self->m_max;
	}
	void DECL two_ValueTrack_two_vec3__set_max(two::ValueTrack<two::vec3>* self, two::vec3* value) {
		self->m_max = *value;
	}
	two::ValueCurve<two::vec3>* DECL two_ValueTrack_two_vec3__get_curve(two::ValueTrack<two::vec3>* self) {
		return &self->m_curve;
	}
	void DECL two_ValueTrack_two_vec3__set_curve(two::ValueTrack<two::vec3>* self, two::ValueCurve<two::vec3>* value) {
		self->m_curve = *value;
	}
	two::ValueCurve<two::vec3>* DECL two_ValueTrack_two_vec3__get_min_curve(two::ValueTrack<two::vec3>* self) {
		return &self->m_min_curve;
	}
	void DECL two_ValueTrack_two_vec3__set_min_curve(two::ValueTrack<two::vec3>* self, two::ValueCurve<two::vec3>* value) {
		self->m_min_curve = *value;
	}
	two::ValueCurve<two::vec3>* DECL two_ValueTrack_two_vec3__get_max_curve(two::ValueTrack<two::vec3>* self) {
		return &self->m_max_curve;
	}
	void DECL two_ValueTrack_two_vec3__set_max_curve(two::ValueTrack<two::vec3>* self, two::ValueCurve<two::vec3>* value) {
		self->m_max_curve = *value;
	}
	void DECL two_ValueTrack_two_vec3__destroy(two::ValueTrack<two::vec3>* self) {
		delete self;
	}
	// ValueTrack<two::quat>
	two::Type* DECL two_ValueTrack_two_quat__type() {
		return &two::type<two::ValueTrack<two::quat>>();
	}
	two::ValueTrack<two::quat>* DECL two_ValueTrack_two_quat__construct_0() {
		return new two::ValueTrack<two::quat>();
	}
	two::ValueTrack<two::quat>* DECL two_ValueTrack_two_quat__construct_4(two::TrackMode mode, two::ValueCurve<two::quat>* curve, two::ValueCurve<two::quat>* min_curve, two::ValueCurve<two::quat>* max_curve) {
		return new two::ValueTrack<two::quat>(mode, *curve, *min_curve, *max_curve);
	}
	two::TrackMode DECL two_ValueTrack_two_quat__get_mode(two::ValueTrack<two::quat>* self) {
		return self->m_mode;
	}
	void DECL two_ValueTrack_two_quat__set_mode(two::ValueTrack<two::quat>* self, two::TrackMode value) {
		self->m_mode = value;
	}
	two::quat* DECL two_ValueTrack_two_quat__get_value(two::ValueTrack<two::quat>* self) {
		return &self->m_value;
	}
	void DECL two_ValueTrack_two_quat__set_value(two::ValueTrack<two::quat>* self, two::quat* value) {
		self->m_value = *value;
	}
	two::quat* DECL two_ValueTrack_two_quat__get_min(two::ValueTrack<two::quat>* self) {
		return &self->m_min;
	}
	void DECL two_ValueTrack_two_quat__set_min(two::ValueTrack<two::quat>* self, two::quat* value) {
		self->m_min = *value;
	}
	two::quat* DECL two_ValueTrack_two_quat__get_max(two::ValueTrack<two::quat>* self) {
		return &self->m_max;
	}
	void DECL two_ValueTrack_two_quat__set_max(two::ValueTrack<two::quat>* self, two::quat* value) {
		self->m_max = *value;
	}
	two::ValueCurve<two::quat>* DECL two_ValueTrack_two_quat__get_curve(two::ValueTrack<two::quat>* self) {
		return &self->m_curve;
	}
	void DECL two_ValueTrack_two_quat__set_curve(two::ValueTrack<two::quat>* self, two::ValueCurve<two::quat>* value) {
		self->m_curve = *value;
	}
	two::ValueCurve<two::quat>* DECL two_ValueTrack_two_quat__get_min_curve(two::ValueTrack<two::quat>* self) {
		return &self->m_min_curve;
	}
	void DECL two_ValueTrack_two_quat__set_min_curve(two::ValueTrack<two::quat>* self, two::ValueCurve<two::quat>* value) {
		self->m_min_curve = *value;
	}
	two::ValueCurve<two::quat>* DECL two_ValueTrack_two_quat__get_max_curve(two::ValueTrack<two::quat>* self) {
		return &self->m_max_curve;
	}
	void DECL two_ValueTrack_two_quat__set_max_curve(two::ValueTrack<two::quat>* self, two::ValueCurve<two::quat>* value) {
		self->m_max_curve = *value;
	}
	void DECL two_ValueTrack_two_quat__destroy(two::ValueTrack<two::quat>* self) {
		delete self;
	}
	// ValueTrack<float>
	two::Type* DECL two_ValueTrack_float__type() {
		return &two::type<two::ValueTrack<float>>();
	}
	two::ValueTrack<float>* DECL two_ValueTrack_float__construct_0() {
		return new two::ValueTrack<float>();
	}
	two::ValueTrack<float>* DECL two_ValueTrack_float__construct_4(two::TrackMode mode, two::ValueCurve<float>* curve, two::ValueCurve<float>* min_curve, two::ValueCurve<float>* max_curve) {
		return new two::ValueTrack<float>(mode, *curve, *min_curve, *max_curve);
	}
	two::TrackMode DECL two_ValueTrack_float__get_mode(two::ValueTrack<float>* self) {
		return self->m_mode;
	}
	void DECL two_ValueTrack_float__set_mode(two::ValueTrack<float>* self, two::TrackMode value) {
		self->m_mode = value;
	}
	float DECL two_ValueTrack_float__get_value(two::ValueTrack<float>* self) {
		return self->m_value;
	}
	void DECL two_ValueTrack_float__set_value(two::ValueTrack<float>* self, float value) {
		self->m_value = value;
	}
	float DECL two_ValueTrack_float__get_min(two::ValueTrack<float>* self) {
		return self->m_min;
	}
	void DECL two_ValueTrack_float__set_min(two::ValueTrack<float>* self, float value) {
		self->m_min = value;
	}
	float DECL two_ValueTrack_float__get_max(two::ValueTrack<float>* self) {
		return self->m_max;
	}
	void DECL two_ValueTrack_float__set_max(two::ValueTrack<float>* self, float value) {
		self->m_max = value;
	}
	two::ValueCurve<float>* DECL two_ValueTrack_float__get_curve(two::ValueTrack<float>* self) {
		return &self->m_curve;
	}
	void DECL two_ValueTrack_float__set_curve(two::ValueTrack<float>* self, two::ValueCurve<float>* value) {
		self->m_curve = *value;
	}
	two::ValueCurve<float>* DECL two_ValueTrack_float__get_min_curve(two::ValueTrack<float>* self) {
		return &self->m_min_curve;
	}
	void DECL two_ValueTrack_float__set_min_curve(two::ValueTrack<float>* self, two::ValueCurve<float>* value) {
		self->m_min_curve = *value;
	}
	two::ValueCurve<float>* DECL two_ValueTrack_float__get_max_curve(two::ValueTrack<float>* self) {
		return &self->m_max_curve;
	}
	void DECL two_ValueTrack_float__set_max_curve(two::ValueTrack<float>* self, two::ValueCurve<float>* value) {
		self->m_max_curve = *value;
	}
	void DECL two_ValueTrack_float__destroy(two::ValueTrack<float>* self) {
		delete self;
	}
	// ValueTrack<uint32_t>
	two::Type* DECL two_ValueTrack_uint32_t__type() {
		return &two::type<two::ValueTrack<uint32_t>>();
	}
	two::ValueTrack<uint32_t>* DECL two_ValueTrack_uint32_t__construct_0() {
		return new two::ValueTrack<uint32_t>();
	}
	two::ValueTrack<uint32_t>* DECL two_ValueTrack_uint32_t__construct_4(two::TrackMode mode, two::ValueCurve<uint32_t>* curve, two::ValueCurve<uint32_t>* min_curve, two::ValueCurve<uint32_t>* max_curve) {
		return new two::ValueTrack<uint32_t>(mode, *curve, *min_curve, *max_curve);
	}
	two::TrackMode DECL two_ValueTrack_uint32_t__get_mode(two::ValueTrack<uint32_t>* self) {
		return self->m_mode;
	}
	void DECL two_ValueTrack_uint32_t__set_mode(two::ValueTrack<uint32_t>* self, two::TrackMode value) {
		self->m_mode = value;
	}
	uint32_t DECL two_ValueTrack_uint32_t__get_value(two::ValueTrack<uint32_t>* self) {
		return self->m_value;
	}
	void DECL two_ValueTrack_uint32_t__set_value(two::ValueTrack<uint32_t>* self, uint32_t value) {
		self->m_value = value;
	}
	uint32_t DECL two_ValueTrack_uint32_t__get_min(two::ValueTrack<uint32_t>* self) {
		return self->m_min;
	}
	void DECL two_ValueTrack_uint32_t__set_min(two::ValueTrack<uint32_t>* self, uint32_t value) {
		self->m_min = value;
	}
	uint32_t DECL two_ValueTrack_uint32_t__get_max(two::ValueTrack<uint32_t>* self) {
		return self->m_max;
	}
	void DECL two_ValueTrack_uint32_t__set_max(two::ValueTrack<uint32_t>* self, uint32_t value) {
		self->m_max = value;
	}
	two::ValueCurve<uint32_t>* DECL two_ValueTrack_uint32_t__get_curve(two::ValueTrack<uint32_t>* self) {
		return &self->m_curve;
	}
	void DECL two_ValueTrack_uint32_t__set_curve(two::ValueTrack<uint32_t>* self, two::ValueCurve<uint32_t>* value) {
		self->m_curve = *value;
	}
	two::ValueCurve<uint32_t>* DECL two_ValueTrack_uint32_t__get_min_curve(two::ValueTrack<uint32_t>* self) {
		return &self->m_min_curve;
	}
	void DECL two_ValueTrack_uint32_t__set_min_curve(two::ValueTrack<uint32_t>* self, two::ValueCurve<uint32_t>* value) {
		self->m_min_curve = *value;
	}
	two::ValueCurve<uint32_t>* DECL two_ValueTrack_uint32_t__get_max_curve(two::ValueTrack<uint32_t>* self) {
		return &self->m_max_curve;
	}
	void DECL two_ValueTrack_uint32_t__set_max_curve(two::ValueTrack<uint32_t>* self, two::ValueCurve<uint32_t>* value) {
		self->m_max_curve = *value;
	}
	void DECL two_ValueTrack_uint32_t__destroy(two::ValueTrack<uint32_t>* self) {
		delete self;
	}
	// ValueTrack<two::Colour>
	two::Type* DECL two_ValueTrack_two_Colour__type() {
		return &two::type<two::ValueTrack<two::Colour>>();
	}
	two::ValueTrack<two::Colour>* DECL two_ValueTrack_two_Colour__construct_0() {
		return new two::ValueTrack<two::Colour>();
	}
	two::ValueTrack<two::Colour>* DECL two_ValueTrack_two_Colour__construct_4(two::TrackMode mode, two::ValueCurve<two::Colour>* curve, two::ValueCurve<two::Colour>* min_curve, two::ValueCurve<two::Colour>* max_curve) {
		return new two::ValueTrack<two::Colour>(mode, *curve, *min_curve, *max_curve);
	}
	two::TrackMode DECL two_ValueTrack_two_Colour__get_mode(two::ValueTrack<two::Colour>* self) {
		return self->m_mode;
	}
	void DECL two_ValueTrack_two_Colour__set_mode(two::ValueTrack<two::Colour>* self, two::TrackMode value) {
		self->m_mode = value;
	}
	two::Colour* DECL two_ValueTrack_two_Colour__get_value(two::ValueTrack<two::Colour>* self) {
		return &self->m_value;
	}
	void DECL two_ValueTrack_two_Colour__set_value(two::ValueTrack<two::Colour>* self, two::Colour* value) {
		self->m_value = *value;
	}
	two::Colour* DECL two_ValueTrack_two_Colour__get_min(two::ValueTrack<two::Colour>* self) {
		return &self->m_min;
	}
	void DECL two_ValueTrack_two_Colour__set_min(two::ValueTrack<two::Colour>* self, two::Colour* value) {
		self->m_min = *value;
	}
	two::Colour* DECL two_ValueTrack_two_Colour__get_max(two::ValueTrack<two::Colour>* self) {
		return &self->m_max;
	}
	void DECL two_ValueTrack_two_Colour__set_max(two::ValueTrack<two::Colour>* self, two::Colour* value) {
		self->m_max = *value;
	}
	two::ValueCurve<two::Colour>* DECL two_ValueTrack_two_Colour__get_curve(two::ValueTrack<two::Colour>* self) {
		return &self->m_curve;
	}
	void DECL two_ValueTrack_two_Colour__set_curve(two::ValueTrack<two::Colour>* self, two::ValueCurve<two::Colour>* value) {
		self->m_curve = *value;
	}
	two::ValueCurve<two::Colour>* DECL two_ValueTrack_two_Colour__get_min_curve(two::ValueTrack<two::Colour>* self) {
		return &self->m_min_curve;
	}
	void DECL two_ValueTrack_two_Colour__set_min_curve(two::ValueTrack<two::Colour>* self, two::ValueCurve<two::Colour>* value) {
		self->m_min_curve = *value;
	}
	two::ValueCurve<two::Colour>* DECL two_ValueTrack_two_Colour__get_max_curve(two::ValueTrack<two::Colour>* self) {
		return &self->m_max_curve;
	}
	void DECL two_ValueTrack_two_Colour__set_max_curve(two::ValueTrack<two::Colour>* self, two::ValueCurve<two::Colour>* value) {
		self->m_max_curve = *value;
	}
	void DECL two_ValueTrack_two_Colour__destroy(two::ValueTrack<two::Colour>* self) {
		delete self;
	}
	// Image
	two::Type* DECL two_Image__type() {
		return &two::type<two::Image>();
	}
	two::Image* DECL two_Image__construct_0() {
		return new two::Image();
	}
	const char* DECL two_Image__get_d_name(two::Image* self) {
		return self->d_name.c_str();
	}
	void DECL two_Image__set_d_name(two::Image* self, const char* value) {
		self->d_name = value;
	}
	const char* DECL two_Image__get_d_path(two::Image* self) {
		return self->d_path.c_str();
	}
	void DECL two_Image__set_d_path(two::Image* self, const char* value) {
		self->d_path = value;
	}
	void DECL two_Image__destroy(two::Image* self) {
		delete self;
	}
	// Palette
	two::Type* DECL two_Palette__type() {
		return &two::type<two::Palette>();
	}
	two::Palette* DECL two_Palette__construct_0() {
		return new two::Palette();
	}
	two::Palette* DECL two_Palette__construct_1(float* colours, int colours_size) {
		return new two::Palette({ (two::Colour*)colours, colours_size / (sizeof(two::Colour) / sizeof(float)) });
	}
	two::Palette* DECL two_Palette__construct_2(two::Spectrum spectrum, size_t steps) {
		return new two::Palette(spectrum, steps);
	}
	void DECL two_Palette__destroy(two::Palette* self) {
		delete self;
	}
	// Image256
	two::Type* DECL two_Image256__type() {
		return &two::type<two::Image256>();
	}
	two::Image256* DECL two_Image256__construct_0() {
		return new two::Image256();
	}
	two::Image256* DECL two_Image256__construct_1(const two::uvec2* size) {
		return new two::Image256(*size);
	}
	two::Image256* DECL two_Image256__construct_2(const two::uvec2* size, const two::Palette* palette) {
		return new two::Image256(*size, *palette);
	}
	uint* DECL two_Image256__get_pixels(two::Image256* self) {
		return (uint*)self->m_pixels.data();
	}
	two::uvec2* DECL two_Image256__get_size(two::Image256* self) {
		return &self->m_size;
	}
	void DECL two_Image256__set_size(two::Image256* self, two::uvec2* value) {
		self->m_size = *value;
	}
	two::Palette* DECL two_Image256__get_palette(two::Image256* self) {
		return &self->m_palette;
	}
	void DECL two_Image256__set_palette(two::Image256* self, two::Palette* value) {
		self->m_palette = *value;
	}
	void DECL two_Image256__destroy(two::Image256* self) {
		delete self;
	}
	// ImageAtlas
	two::Type* DECL two_ImageAtlas__type() {
		return &two::type<two::ImageAtlas>();
	}
	void DECL two_ImageAtlas__destroy(two::ImageAtlas* self) {
		delete self;
	}
	// TextureAtlas
	two::Type* DECL two_TextureAtlas__type() {
		return &two::type<two::TextureAtlas>();
	}
	void DECL two_TextureAtlas__destroy(two::TextureAtlas* self) {
		delete self;
	}
	// Sprite
	two::Type* DECL two_Sprite__type() {
		return &two::type<two::Sprite>();
	}
	void DECL two_Sprite__destroy(two::Sprite* self) {
		delete self;
	}
	// SpriteAtlas
	two::Type* DECL two_SpriteAtlas__type() {
		return &two::type<two::SpriteAtlas>();
	}
	void DECL two_SpriteAtlas__destroy(two::SpriteAtlas* self) {
		delete self;
	}
	// Range<two::vec3>
	two::Type* DECL two_Range_two_vec3__type() {
		return &two::type<two::Range<two::vec3>>();
	}
	two::Range<two::vec3>* DECL two_Range_two_vec3__construct_0() {
		return new two::Range<two::vec3>();
	}
	two::vec3* DECL two_Range_two_vec3__get_min(two::Range<two::vec3>* self) {
		return &self->m_min;
	}
	void DECL two_Range_two_vec3__set_min(two::Range<two::vec3>* self, two::vec3* value) {
		self->m_min = *value;
	}
	two::vec3* DECL two_Range_two_vec3__get_max(two::Range<two::vec3>* self) {
		return &self->m_max;
	}
	void DECL two_Range_two_vec3__set_max(two::Range<two::vec3>* self, two::vec3* value) {
		self->m_max = *value;
	}
	void DECL two_Range_two_vec3__destroy(two::Range<two::vec3>* self) {
		delete self;
	}
	// Range<two::quat>
	two::Type* DECL two_Range_two_quat__type() {
		return &two::type<two::Range<two::quat>>();
	}
	two::Range<two::quat>* DECL two_Range_two_quat__construct_0() {
		return new two::Range<two::quat>();
	}
	two::quat* DECL two_Range_two_quat__get_min(two::Range<two::quat>* self) {
		return &self->m_min;
	}
	void DECL two_Range_two_quat__set_min(two::Range<two::quat>* self, two::quat* value) {
		self->m_min = *value;
	}
	two::quat* DECL two_Range_two_quat__get_max(two::Range<two::quat>* self) {
		return &self->m_max;
	}
	void DECL two_Range_two_quat__set_max(two::Range<two::quat>* self, two::quat* value) {
		self->m_max = *value;
	}
	void DECL two_Range_two_quat__destroy(two::Range<two::quat>* self) {
		delete self;
	}
	// Range<float>
	two::Type* DECL two_Range_float__type() {
		return &two::type<two::Range<float>>();
	}
	two::Range<float>* DECL two_Range_float__construct_0() {
		return new two::Range<float>();
	}
	float DECL two_Range_float__get_min(two::Range<float>* self) {
		return self->m_min;
	}
	void DECL two_Range_float__set_min(two::Range<float>* self, float value) {
		self->m_min = value;
	}
	float DECL two_Range_float__get_max(two::Range<float>* self) {
		return self->m_max;
	}
	void DECL two_Range_float__set_max(two::Range<float>* self, float value) {
		self->m_max = value;
	}
	void DECL two_Range_float__destroy(two::Range<float>* self) {
		delete self;
	}
	// Range<uint32_t>
	two::Type* DECL two_Range_uint32_t__type() {
		return &two::type<two::Range<uint32_t>>();
	}
	two::Range<uint32_t>* DECL two_Range_uint32_t__construct_0() {
		return new two::Range<uint32_t>();
	}
	uint32_t DECL two_Range_uint32_t__get_min(two::Range<uint32_t>* self) {
		return self->m_min;
	}
	void DECL two_Range_uint32_t__set_min(two::Range<uint32_t>* self, uint32_t value) {
		self->m_min = value;
	}
	uint32_t DECL two_Range_uint32_t__get_max(two::Range<uint32_t>* self) {
		return self->m_max;
	}
	void DECL two_Range_uint32_t__set_max(two::Range<uint32_t>* self, uint32_t value) {
		self->m_max = value;
	}
	void DECL two_Range_uint32_t__destroy(two::Range<uint32_t>* self) {
		delete self;
	}
	// Range<two::Colour>
	two::Type* DECL two_Range_two_Colour__type() {
		return &two::type<two::Range<two::Colour>>();
	}
	two::Range<two::Colour>* DECL two_Range_two_Colour__construct_0() {
		return new two::Range<two::Colour>();
	}
	two::Colour* DECL two_Range_two_Colour__get_min(two::Range<two::Colour>* self) {
		return &self->m_min;
	}
	void DECL two_Range_two_Colour__set_min(two::Range<two::Colour>* self, two::Colour* value) {
		self->m_min = *value;
	}
	two::Colour* DECL two_Range_two_Colour__get_max(two::Range<two::Colour>* self) {
		return &self->m_max;
	}
	void DECL two_Range_two_Colour__set_max(two::Range<two::Colour>* self, two::Colour* value) {
		self->m_max = *value;
	}
	void DECL two_Range_two_Colour__destroy(two::Range<two::Colour>* self) {
		delete self;
	}
	// StatDef<int>
	two::Type* DECL two_StatDef_int__type() {
		return &two::type<two::StatDef<int>>();
	}
	two::StatDef<int>* DECL two_StatDef_int__construct_0() {
		return new two::StatDef<int>();
	}
	int DECL two_StatDef_int__get_min(two::StatDef<int>* self) {
		return self->m_min;
	}
	void DECL two_StatDef_int__set_min(two::StatDef<int>* self, int value) {
		self->m_min = value;
	}
	int DECL two_StatDef_int__get_max(two::StatDef<int>* self) {
		return self->m_max;
	}
	void DECL two_StatDef_int__set_max(two::StatDef<int>* self, int value) {
		self->m_max = value;
	}
	int DECL two_StatDef_int__get_step(two::StatDef<int>* self) {
		return self->m_step;
	}
	void DECL two_StatDef_int__set_step(two::StatDef<int>* self, int value) {
		self->m_step = value;
	}
	void DECL two_StatDef_int__destroy(two::StatDef<int>* self) {
		delete self;
	}
	// StatDef<float>
	two::Type* DECL two_StatDef_float__type() {
		return &two::type<two::StatDef<float>>();
	}
	two::StatDef<float>* DECL two_StatDef_float__construct_0() {
		return new two::StatDef<float>();
	}
	float DECL two_StatDef_float__get_min(two::StatDef<float>* self) {
		return self->m_min;
	}
	void DECL two_StatDef_float__set_min(two::StatDef<float>* self, float value) {
		self->m_min = value;
	}
	float DECL two_StatDef_float__get_max(two::StatDef<float>* self) {
		return self->m_max;
	}
	void DECL two_StatDef_float__set_max(two::StatDef<float>* self, float value) {
		self->m_max = value;
	}
	float DECL two_StatDef_float__get_step(two::StatDef<float>* self) {
		return self->m_step;
	}
	void DECL two_StatDef_float__set_step(two::StatDef<float>* self, float value) {
		self->m_step = value;
	}
	void DECL two_StatDef_float__destroy(two::StatDef<float>* self) {
		delete self;
	}
	// Time
	two::Type* DECL two_Time__type() {
		return &two::type<two::Time>();
	}
	two::Time* DECL two_Time__construct_1(double value) {
		return new two::Time(value);
	}
	double DECL two_Time__get_value(two::Time* self) {
		return self->m_value;
	}
	void DECL two_Time__set_value(two::Time* self, double value) {
		self->m_value = value;
	}
	void DECL two_Time__destroy(two::Time* self) {
		delete self;
	}
	// TimeSpan
	two::Type* DECL two_TimeSpan__type() {
		return &two::type<two::TimeSpan>();
	}
	two::TimeSpan* DECL two_TimeSpan__construct_2(two::Time* s, two::Time* e) {
		return new two::TimeSpan(*s, *e);
	}
	two::Time* DECL two_TimeSpan__get_start(two::TimeSpan* self) {
		return &self->start;
	}
	void DECL two_TimeSpan__set_start(two::TimeSpan* self, two::Time* value) {
		self->start = *value;
	}
	two::Time* DECL two_TimeSpan__get_end(two::TimeSpan* self) {
		return &self->end;
	}
	void DECL two_TimeSpan__set_end(two::TimeSpan* self, two::Time* value) {
		self->end = *value;
	}
	void DECL two_TimeSpan__destroy(two::TimeSpan* self) {
		delete self;
	}
	two::Colour* DECL two_rgb_1(uint32_t colour) {
		static two::Colour temp;
		return (temp = two::rgb(colour), &temp);
	}
	two::Colour* DECL two_rgba_1(uint32_t colour) {
		static two::Colour temp;
		return (temp = two::rgba(colour), &temp);
	}
	two::Colour* DECL two_abgr_1(uint32_t colour) {
		static two::Colour temp;
		return (temp = two::abgr(colour), &temp);
	}
	two::Colour* DECL two_hsv_3(float h, float s, float v) {
		static two::Colour temp;
		return (temp = two::hsv(h, s, v), &temp);
	}
	two::Colour* DECL two_hsl_3(float h, float s, float l) {
		static two::Colour temp;
		return (temp = two::hsl(h, s, l), &temp);
	}
	uint32_t DECL two_to_rgba_1(const two::Colour* colour) {
		return two::to_rgba(*colour);
	}
	uint32_t DECL two_to_abgr_1(const two::Colour* colour) {
		return two::to_abgr(*colour);
	}
	uint32_t DECL two_to_abgr_3(float r, float g, float b) {
		return two::to_abgr(r, g, b);
	}
	uint32_t DECL two_to_abgr_4(float r, float g, float b, float a) {
		return two::to_abgr(r, g, b, a);
	}
	two::Colour* DECL two_to_linear_1(const two::Colour* colour) {
		static two::Colour temp;
		return (temp = two::to_linear(*colour), &temp);
	}
	two::Colour* DECL two_to_gamma_1(const two::Colour* colour) {
		static two::Colour temp;
		return (temp = two::to_gamma(*colour), &temp);
	}
	two::Colour* DECL two_to_srgb_1(const two::Colour* colour) {
		static two::Colour temp;
		return (temp = two::to_srgb(*colour), &temp);
	}
	two::ColourHSL* DECL two_to_hsl_1(const two::Colour* colour) {
		static two::ColourHSL temp;
		return (temp = two::to_hsl(*colour), &temp);
	}
	two::ColourHSL* DECL two_to_hsl_3(float r, float g, float b) {
		static two::ColourHSL temp;
		return (temp = two::to_hsl(r, g, b), &temp);
	}
	two::ColourHSL* DECL two_to_hsla_1(const two::Colour* colour) {
		static two::ColourHSL temp;
		return (temp = two::to_hsla(*colour), &temp);
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
	float DECL two_add_float_2(float a, float b) {
		return two::add<float>(a, b);
	}
	float DECL two_subtract_float_2(float a, float b) {
		return two::subtract<float>(a, b);
	}
	float DECL two_multiply_float_2(float a, float b) {
		return two::multiply<float>(a, b);
	}
	float DECL two_divide_float_2(float a, float b) {
		return two::divide<float>(a, b);
	}
	float DECL two_nsinf_1(float a) {
		return two::nsinf(a);
	}
	float DECL two_ncosf_1(float a) {
		return two::ncosf(a);
	}
	double DECL two_nsin_1(double a) {
		return two::nsin(a);
	}
	double DECL two_ncos_1(double a) {
		return two::ncos(a);
	}
	two::vec3* DECL two_add_two_v3_float_2(two::vec3* a, two::vec3* b) {
		static two::vec3 temp;
		return (temp = two::add<two::v3<float>>(*a, *b), &temp);
	}
	two::vec3* DECL two_subtract_two_v3_float_2(two::vec3* a, two::vec3* b) {
		static two::vec3 temp;
		return (temp = two::subtract<two::v3<float>>(*a, *b), &temp);
	}
	two::vec3* DECL two_multiply_two_v3_float_2(two::vec3* a, two::vec3* b) {
		static two::vec3 temp;
		return (temp = two::multiply<two::v3<float>>(*a, *b), &temp);
	}
	two::vec3* DECL two_divide_two_v3_float_2(two::vec3* a, two::vec3* b) {
		static two::vec3 temp;
		return (temp = two::divide<two::v3<float>>(*a, *b), &temp);
	}
	two::quat* DECL two_look_dir_1(const two::vec3* direction) {
		static two::quat temp;
		return (temp = two::look_dir(*direction), &temp);
	}
	two::quat* DECL two_look_dir_2(const two::vec3* direction, const two::vec3* forward) {
		static two::quat temp;
		return (temp = two::look_dir(*direction, *forward), &temp);
	}
	two::quat* DECL two_look_at_2(const two::vec3* eye, const two::vec3* target) {
		static two::quat temp;
		return (temp = two::look_at(*eye, *target), &temp);
	}
	two::quat* DECL two_look_at_3(const two::vec3* eye, const two::vec3* target, const two::vec3* forward) {
		static two::quat temp;
		return (temp = two::look_at(*eye, *target, *forward), &temp);
	}
	two::vec3* DECL two_grid_center_2(const two::uvec3* coord, const two::vec3* cell_size) {
		static two::vec3 temp;
		return (temp = two::grid_center(*coord, *cell_size), &temp);
	}
	// Axis
	two::Axis DECL two_Axis_X() {
		return two::Axis::X;
	}
	two::Axis DECL two_Axis_Y() {
		return two::Axis::Y;
	}
	two::Axis DECL two_Axis_Z() {
		return two::Axis::Z;
	}
	two::Axis DECL two_Axis_None() {
		return two::Axis::None;
	}
	two::Axis DECL two_Axis_Count() {
		return two::Axis::Count;
	}
	// Axes
	two::Axes DECL two_Axes_None() {
		return two::Axes::None;
	}
	two::Axes DECL two_Axes_X() {
		return two::Axes::X;
	}
	two::Axes DECL two_Axes_Y() {
		return two::Axes::Y;
	}
	two::Axes DECL two_Axes_Z() {
		return two::Axes::Z;
	}
	// SignedAxis
	two::SignedAxis DECL two_SignedAxis_PlusX() {
		return two::SignedAxis::PlusX;
	}
	two::SignedAxis DECL two_SignedAxis_MinusX() {
		return two::SignedAxis::MinusX;
	}
	two::SignedAxis DECL two_SignedAxis_PlusY() {
		return two::SignedAxis::PlusY;
	}
	two::SignedAxis DECL two_SignedAxis_MinusY() {
		return two::SignedAxis::MinusY;
	}
	two::SignedAxis DECL two_SignedAxis_PlusZ() {
		return two::SignedAxis::PlusZ;
	}
	two::SignedAxis DECL two_SignedAxis_MinusZ() {
		return two::SignedAxis::MinusZ;
	}
	two::SignedAxis DECL two_SignedAxis_Count() {
		return two::SignedAxis::Count;
	}
	// Side
	two::Side DECL two_Side_Right() {
		return two::Side::Right;
	}
	two::Side DECL two_Side_Left() {
		return two::Side::Left;
	}
	two::Side DECL two_Side_Up() {
		return two::Side::Up;
	}
	two::Side DECL two_Side_Down() {
		return two::Side::Down;
	}
	two::Side DECL two_Side_Back() {
		return two::Side::Back;
	}
	two::Side DECL two_Side_Front() {
		return two::Side::Front;
	}
	two::Side DECL two_Side_Count() {
		return two::Side::Count;
	}
	// Clockwise
	two::Clockwise DECL two_Clockwise_CLOCKWISE() {
		return two::CLOCKWISE;
	}
	two::Clockwise DECL two_Clockwise_ANTI_CLOCKWISE() {
		return two::ANTI_CLOCKWISE;
	}
	// TrackMode
	two::TrackMode DECL two_TrackMode_Constant() {
		return two::TrackMode::Constant;
	}
	two::TrackMode DECL two_TrackMode_ConstantRandom() {
		return two::TrackMode::ConstantRandom;
	}
	two::TrackMode DECL two_TrackMode_Curve() {
		return two::TrackMode::Curve;
	}
	two::TrackMode DECL two_TrackMode_CurveRandom() {
		return two::TrackMode::CurveRandom;
	}
	// Spectrum
	two::Spectrum DECL two_Spectrum_Value() {
		return two::Spectrum::Value;
	}
	two::Spectrum DECL two_Spectrum_Hue() {
		return two::Spectrum::Hue;
	}
	
}


