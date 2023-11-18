module;
#include <infra/Cpp20.h>
module two.math.meta;

using namespace two;

#ifdef TWO_MODULES
namespace two { using stl::string; }
#endif

void two_Axis__to_string(void* val, string& str) { str = g_enu[type<two::Axis>().m_id]->name(uint32_t((*static_cast<two::Axis*>(val)))); }
void two_Axis__to_value(const string& str, void* val) { (*static_cast<two::Axis*>(val)) = two::Axis(g_enu[type<two::Axis>().m_id]->value(str.c_str())); }
void two_Axes__to_string(void* val, string& str) { str = g_enu[type<two::Axes>().m_id]->name(uint32_t((*static_cast<two::Axes*>(val)))); }
void two_Axes__to_value(const string& str, void* val) { (*static_cast<two::Axes*>(val)) = two::Axes(g_enu[type<two::Axes>().m_id]->value(str.c_str())); }
void two_SignedAxis__to_string(void* val, string& str) { str = g_enu[type<two::SignedAxis>().m_id]->name(uint32_t((*static_cast<two::SignedAxis*>(val)))); }
void two_SignedAxis__to_value(const string& str, void* val) { (*static_cast<two::SignedAxis*>(val)) = two::SignedAxis(g_enu[type<two::SignedAxis>().m_id]->value(str.c_str())); }
void two_Side__to_string(void* val, string& str) { str = g_enu[type<two::Side>().m_id]->name(uint32_t((*static_cast<two::Side*>(val)))); }
void two_Side__to_value(const string& str, void* val) { (*static_cast<two::Side*>(val)) = two::Side(g_enu[type<two::Side>().m_id]->value(str.c_str())); }
void two_Clockwise__to_string(void* val, string& str) { str = g_enu[type<two::Clockwise>().m_id]->name(uint32_t((*static_cast<two::Clockwise*>(val)))); }
void two_Clockwise__to_value(const string& str, void* val) { (*static_cast<two::Clockwise*>(val)) = two::Clockwise(g_enu[type<two::Clockwise>().m_id]->value(str.c_str())); }
void two_TrackMode__to_string(void* val, string& str) { str = g_enu[type<two::TrackMode>().m_id]->name(uint32_t((*static_cast<two::TrackMode*>(val)))); }
void two_TrackMode__to_value(const string& str, void* val) { (*static_cast<two::TrackMode*>(val)) = two::TrackMode(g_enu[type<two::TrackMode>().m_id]->value(str.c_str())); }
void two_Spectrum__to_string(void* val, string& str) { str = g_enu[type<two::Spectrum>().m_id]->name(uint32_t((*static_cast<two::Spectrum*>(val)))); }
void two_Spectrum__to_value(const string& str, void* val) { (*static_cast<two::Spectrum*>(val)) = two::Spectrum(g_enu[type<two::Spectrum>().m_id]->value(str.c_str())); }
size_t stl_span_uint8_t__size(void* vec) { return (*static_cast<stl::span<uint8_t>*>(vec)).size(); }
void* stl_span_uint8_t__at(void* vec, size_t i) { return &(*static_cast<stl::span<uint8_t>*>(vec))[i]; }
size_t stl_span_int__size(void* vec) { return (*static_cast<stl::span<int>*>(vec)).size(); }
void* stl_span_int__at(void* vec, size_t i) { return &(*static_cast<stl::span<int>*>(vec))[i]; }
size_t stl_span_float__size(void* vec) { return (*static_cast<stl::span<float>*>(vec)).size(); }
void* stl_span_float__at(void* vec, size_t i) { return &(*static_cast<stl::span<float>*>(vec))[i]; }
size_t stl_span_uint32_t__size(void* vec) { return (*static_cast<stl::span<uint32_t>*>(vec)).size(); }
void* stl_span_uint32_t__at(void* vec, size_t i) { return &(*static_cast<stl::span<uint32_t>*>(vec))[i]; }
size_t stl_span_two_vec3__size(void* vec) { return (*static_cast<stl::span<two::vec3>*>(vec)).size(); }
void* stl_span_two_vec3__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::vec3>*>(vec))[i]; }
size_t stl_span_two_quat__size(void* vec) { return (*static_cast<stl::span<two::quat>*>(vec)).size(); }
void* stl_span_two_quat__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::quat>*>(vec))[i]; }
size_t stl_span_two_Colour__size(void* vec) { return (*static_cast<stl::span<two::Colour>*>(vec)).size(); }
void* stl_span_two_Colour__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Colour>*>(vec))[i]; }
size_t stl_span_two_uvec3__size(void* vec) { return (*static_cast<stl::span<two::uvec3>*>(vec)).size(); }
void* stl_span_two_uvec3__at(void* vec, size_t i) { return &(*static_cast<stl::span<two::uvec3>*>(vec))[i]; }
size_t stl_vector_int__size(void* vec) { return (*static_cast<stl::vector<int>*>(vec)).size(); }
void* stl_vector_int__at(void* vec, size_t i) { return &(*static_cast<stl::vector<int>*>(vec))[i]; }
void stl_vector_int__push(void* vec) { (*static_cast<stl::vector<int>*>(vec)).emplace_back(); }
void stl_vector_int__add(void* vec, void* value) { (*static_cast<stl::vector<int>*>(vec)).push_back(*static_cast<int*>(value)); }
void stl_vector_int__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<int>*>(vec)), *static_cast<int*>(value)); }
size_t stl_vector_float__size(void* vec) { return (*static_cast<stl::vector<float>*>(vec)).size(); }
void* stl_vector_float__at(void* vec, size_t i) { return &(*static_cast<stl::vector<float>*>(vec))[i]; }
void stl_vector_float__push(void* vec) { (*static_cast<stl::vector<float>*>(vec)).emplace_back(); }
void stl_vector_float__add(void* vec, void* value) { (*static_cast<stl::vector<float>*>(vec)).push_back(*static_cast<float*>(value)); }
void stl_vector_float__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<float>*>(vec)), *static_cast<float*>(value)); }
size_t stl_vector_uint32_t__size(void* vec) { return (*static_cast<stl::vector<uint32_t>*>(vec)).size(); }
void* stl_vector_uint32_t__at(void* vec, size_t i) { return &(*static_cast<stl::vector<uint32_t>*>(vec))[i]; }
void stl_vector_uint32_t__push(void* vec) { (*static_cast<stl::vector<uint32_t>*>(vec)).emplace_back(); }
void stl_vector_uint32_t__add(void* vec, void* value) { (*static_cast<stl::vector<uint32_t>*>(vec)).push_back(*static_cast<uint32_t*>(value)); }
void stl_vector_uint32_t__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<uint32_t>*>(vec)), *static_cast<uint32_t*>(value)); }
size_t stl_vector_two_vec3__size(void* vec) { return (*static_cast<stl::vector<two::vec3>*>(vec)).size(); }
void* stl_vector_two_vec3__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::vec3>*>(vec))[i]; }
void stl_vector_two_vec3__push(void* vec) { (*static_cast<stl::vector<two::vec3>*>(vec)).emplace_back(); }
void stl_vector_two_vec3__add(void* vec, void* value) { (*static_cast<stl::vector<two::vec3>*>(vec)).push_back(*static_cast<two::vec3*>(value)); }
void stl_vector_two_vec3__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::vec3>*>(vec)), *static_cast<two::vec3*>(value)); }
size_t stl_vector_two_quat__size(void* vec) { return (*static_cast<stl::vector<two::quat>*>(vec)).size(); }
void* stl_vector_two_quat__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::quat>*>(vec))[i]; }
void stl_vector_two_quat__push(void* vec) { (*static_cast<stl::vector<two::quat>*>(vec)).emplace_back(); }
void stl_vector_two_quat__add(void* vec, void* value) { (*static_cast<stl::vector<two::quat>*>(vec)).push_back(*static_cast<two::quat*>(value)); }
void stl_vector_two_quat__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::quat>*>(vec)), *static_cast<two::quat*>(value)); }
size_t stl_vector_two_Colour__size(void* vec) { return (*static_cast<stl::vector<two::Colour>*>(vec)).size(); }
void* stl_vector_two_Colour__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Colour>*>(vec))[i]; }
void stl_vector_two_Colour__push(void* vec) { (*static_cast<stl::vector<two::Colour>*>(vec)).emplace_back(); }
void stl_vector_two_Colour__add(void* vec, void* value) { (*static_cast<stl::vector<two::Colour>*>(vec)).push_back(*static_cast<two::Colour*>(value)); }
void stl_vector_two_Colour__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Colour>*>(vec)), *static_cast<two::Colour*>(value)); }
size_t stl_vector_two_uvec3__size(void* vec) { return (*static_cast<stl::vector<two::uvec3>*>(vec)).size(); }
void* stl_vector_two_uvec3__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::uvec3>*>(vec))[i]; }
void stl_vector_two_uvec3__push(void* vec) { (*static_cast<stl::vector<two::uvec3>*>(vec)).emplace_back(); }
void stl_vector_two_uvec3__add(void* vec, void* value) { (*static_cast<stl::vector<two::uvec3>*>(vec)).push_back(*static_cast<two::uvec3*>(value)); }
void stl_vector_two_uvec3__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::uvec3>*>(vec)), *static_cast<two::uvec3*>(value)); }
void two_v2_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v2<float>(  ); }
void two_v2_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<float>( *static_cast<float*>(args[0]) ); }
void two_v2_float__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<float>( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]) ); }
void two_v2_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<float>((*static_cast<two::v2<float>*>(other))); }
void two_v3_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v3<float>(  ); }
void two_v3_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v3<float>( *static_cast<float*>(args[0]) ); }
void two_v3_float__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v3<float>( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void two_v3_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v3<float>((*static_cast<two::v3<float>*>(other))); }
void two_v4_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v4<float>(  ); }
void two_v4_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v4<float>( *static_cast<float*>(args[0]) ); }
void two_v4_float__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v4<float>( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void two_v4_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v4<float>((*static_cast<two::v4<float>*>(other))); }
void two_v2_int__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v2<int>(  ); }
void two_v2_int__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<int>( *static_cast<int*>(args[0]) ); }
void two_v2_int__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<int>( *static_cast<int*>(args[0]), *static_cast<int*>(args[1]) ); }
void two_v2_int__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<int>((*static_cast<two::v2<int>*>(other))); }
void two_v3_int__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v3<int>(  ); }
void two_v3_int__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v3<int>( *static_cast<int*>(args[0]) ); }
void two_v3_int__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v3<int>( *static_cast<int*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]) ); }
void two_v3_int__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v3<int>((*static_cast<two::v3<int>*>(other))); }
void two_v4_int__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v4<int>(  ); }
void two_v4_int__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v4<int>( *static_cast<int*>(args[0]) ); }
void two_v4_int__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v4<int>( *static_cast<int*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]), *static_cast<int*>(args[3]) ); }
void two_v4_int__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v4<int>((*static_cast<two::v4<int>*>(other))); }
void two_v2_uint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v2<uint>(  ); }
void two_v2_uint__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<uint>( *static_cast<uint*>(args[0]) ); }
void two_v2_uint__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<uint>( *static_cast<uint*>(args[0]), *static_cast<uint*>(args[1]) ); }
void two_v2_uint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<uint>((*static_cast<two::v2<uint>*>(other))); }
void two_v3_uint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v3<uint>(  ); }
void two_v3_uint__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v3<uint>( *static_cast<uint*>(args[0]) ); }
void two_v3_uint__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v3<uint>( *static_cast<uint*>(args[0]), *static_cast<uint*>(args[1]), *static_cast<uint*>(args[2]) ); }
void two_v3_uint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v3<uint>((*static_cast<two::v3<uint>*>(other))); }
void two_v4_uint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v4<uint>(  ); }
void two_v4_uint__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v4<uint>( *static_cast<uint*>(args[0]) ); }
void two_v4_uint__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v4<uint>( *static_cast<uint*>(args[0]), *static_cast<uint*>(args[1]), *static_cast<uint*>(args[2]), *static_cast<uint*>(args[3]) ); }
void two_v4_uint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v4<uint>((*static_cast<two::v4<uint>*>(other))); }
void two_v2_bool__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v2<bool>(  ); }
void two_v2_bool__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<bool>( *static_cast<bool*>(args[0]) ); }
void two_v2_bool__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v2<bool>( *static_cast<bool*>(args[0]), *static_cast<bool*>(args[1]) ); }
void two_v2_bool__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v2<bool>((*static_cast<two::v2<bool>*>(other))); }
void two_v3_bool__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v3<bool>(  ); }
void two_v3_bool__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v3<bool>( *static_cast<bool*>(args[0]) ); }
void two_v3_bool__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v3<bool>( *static_cast<bool*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<bool*>(args[2]) ); }
void two_v3_bool__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v3<bool>((*static_cast<two::v3<bool>*>(other))); }
void two_v4_bool__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::v4<bool>(  ); }
void two_v4_bool__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v4<bool>( *static_cast<bool*>(args[0]) ); }
void two_v4_bool__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::v4<bool>( *static_cast<bool*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3]) ); }
void two_v4_bool__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::v4<bool>((*static_cast<two::v4<bool>*>(other))); }
void two_mat3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::mat3(  ); }
void two_mat3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::mat3( *static_cast<two::float3*>(args[0]), *static_cast<two::float3*>(args[1]), *static_cast<two::float3*>(args[2]) ); }
void two_mat3__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::mat3( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5]), *static_cast<float*>(args[6]), *static_cast<float*>(args[7]), *static_cast<float*>(args[8]) ); }
void two_mat3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::mat3((*static_cast<two::mat3*>(other))); }
void two_mat4__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::mat4(  ); }
void two_mat4__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::mat4( *static_cast<two::float4*>(args[0]), *static_cast<two::float4*>(args[1]), *static_cast<two::float4*>(args[2]), *static_cast<two::float4*>(args[3]) ); }
void two_mat4__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::mat4( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5]), *static_cast<float*>(args[6]), *static_cast<float*>(args[7]), *static_cast<float*>(args[8]), *static_cast<float*>(args[9]), *static_cast<float*>(args[10]), *static_cast<float*>(args[11]), *static_cast<float*>(args[12]), *static_cast<float*>(args[13]), *static_cast<float*>(args[14]), *static_cast<float*>(args[15]) ); }
void two_mat4__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::mat4((*static_cast<two::mat4*>(other))); }
void two_quat__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::quat(  ); }
void two_quat__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::quat( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void two_quat__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::quat( *static_cast<two::float3*>(args[0]) ); }
void two_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::quat((*static_cast<two::quat*>(other))); }
void two_Transform__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Transform(  ); }
void two_Transform__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Transform((*static_cast<two::Transform*>(other))); }
void two_ColourHSL__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ColourHSL(  ); }
void two_ColourHSL__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ColourHSL((*static_cast<two::ColourHSL*>(other))); }
void two_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Colour(  ); }
void two_Colour__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Colour( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]) ); }
void two_Colour__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Colour( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void two_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Colour((*static_cast<two::Colour*>(other))); }
void two_ValueCurve_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueCurve<float>(  ); }
void two_ValueCurve_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueCurve<float>( *static_cast<stl::span<float>*>(args[0]) ); }
void two_ValueCurve_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueCurve<float>((*static_cast<two::ValueCurve<float>*>(other))); }
void two_ValueCurve_uint32_t__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueCurve<uint32_t>(  ); }
void two_ValueCurve_uint32_t__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueCurve<uint32_t>( *static_cast<stl::span<uint32_t>*>(args[0]) ); }
void two_ValueCurve_uint32_t__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueCurve<uint32_t>((*static_cast<two::ValueCurve<uint32_t>*>(other))); }
void two_ValueCurve_two_vec3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueCurve<two::vec3>(  ); }
void two_ValueCurve_two_vec3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueCurve<two::vec3>( *static_cast<stl::span<two::vec3>*>(args[0]) ); }
void two_ValueCurve_two_vec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueCurve<two::vec3>((*static_cast<two::ValueCurve<two::vec3>*>(other))); }
void two_ValueCurve_two_quat__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueCurve<two::quat>(  ); }
void two_ValueCurve_two_quat__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueCurve<two::quat>( *static_cast<stl::span<two::quat>*>(args[0]) ); }
void two_ValueCurve_two_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueCurve<two::quat>((*static_cast<two::ValueCurve<two::quat>*>(other))); }
void two_ValueCurve_two_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueCurve<two::Colour>(  ); }
void two_ValueCurve_two_Colour__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueCurve<two::Colour>( *static_cast<stl::span<two::Colour>*>(args[0]) ); }
void two_ValueCurve_two_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueCurve<two::Colour>((*static_cast<two::ValueCurve<two::Colour>*>(other))); }
void two_ValueTrack_two_vec3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueTrack<two::vec3>(  ); }
void two_ValueTrack_two_vec3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueTrack<two::vec3>( *static_cast<two::TrackMode*>(args[0]), *static_cast<two::ValueCurve<two::vec3>*>(args[1]), *static_cast<two::ValueCurve<two::vec3>*>(args[2]), *static_cast<two::ValueCurve<two::vec3>*>(args[3]) ); }
void two_ValueTrack_two_vec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueTrack<two::vec3>((*static_cast<two::ValueTrack<two::vec3>*>(other))); }
void two_ValueTrack_two_quat__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueTrack<two::quat>(  ); }
void two_ValueTrack_two_quat__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueTrack<two::quat>( *static_cast<two::TrackMode*>(args[0]), *static_cast<two::ValueCurve<two::quat>*>(args[1]), *static_cast<two::ValueCurve<two::quat>*>(args[2]), *static_cast<two::ValueCurve<two::quat>*>(args[3]) ); }
void two_ValueTrack_two_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueTrack<two::quat>((*static_cast<two::ValueTrack<two::quat>*>(other))); }
void two_ValueTrack_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueTrack<float>(  ); }
void two_ValueTrack_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueTrack<float>( *static_cast<two::TrackMode*>(args[0]), *static_cast<two::ValueCurve<float>*>(args[1]), *static_cast<two::ValueCurve<float>*>(args[2]), *static_cast<two::ValueCurve<float>*>(args[3]) ); }
void two_ValueTrack_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueTrack<float>((*static_cast<two::ValueTrack<float>*>(other))); }
void two_ValueTrack_uint32_t__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueTrack<uint32_t>(  ); }
void two_ValueTrack_uint32_t__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueTrack<uint32_t>( *static_cast<two::TrackMode*>(args[0]), *static_cast<two::ValueCurve<uint32_t>*>(args[1]), *static_cast<two::ValueCurve<uint32_t>*>(args[2]), *static_cast<two::ValueCurve<uint32_t>*>(args[3]) ); }
void two_ValueTrack_uint32_t__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueTrack<uint32_t>((*static_cast<two::ValueTrack<uint32_t>*>(other))); }
void two_ValueTrack_two_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ValueTrack<two::Colour>(  ); }
void two_ValueTrack_two_Colour__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ValueTrack<two::Colour>( *static_cast<two::TrackMode*>(args[0]), *static_cast<two::ValueCurve<two::Colour>*>(args[1]), *static_cast<two::ValueCurve<two::Colour>*>(args[2]), *static_cast<two::ValueCurve<two::Colour>*>(args[3]) ); }
void two_ValueTrack_two_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ValueTrack<two::Colour>((*static_cast<two::ValueTrack<two::Colour>*>(other))); }
void two_Image__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Image(  ); }
void two_Image__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Image((*static_cast<two::Image*>(other))); }
void two_Palette__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Palette( *static_cast<two::Spectrum*>(args[0]), *static_cast<size_t*>(args[1]) ); }
void two_Palette__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Palette( *static_cast<stl::span<two::Colour>*>(args[0]) ); }
void two_Palette__construct_2(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Palette(  ); }
void two_Palette__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Palette((*static_cast<two::Palette*>(other))); }
void two_Image256__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Image256( *static_cast<two::uvec2*>(args[0]), *static_cast<two::Palette*>(args[1]) ); }
void two_Image256__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Image256((*static_cast<two::Image256*>(other))); }
void two_Range_two_vec3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Range<two::vec3>(  ); }
void two_Range_two_vec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Range<two::vec3>((*static_cast<two::Range<two::vec3>*>(other))); }
void two_Range_two_quat__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Range<two::quat>(  ); }
void two_Range_two_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Range<two::quat>((*static_cast<two::Range<two::quat>*>(other))); }
void two_Range_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Range<float>(  ); }
void two_Range_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Range<float>((*static_cast<two::Range<float>*>(other))); }
void two_Range_uint32_t__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Range<uint32_t>(  ); }
void two_Range_uint32_t__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Range<uint32_t>((*static_cast<two::Range<uint32_t>*>(other))); }
void two_Range_two_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Range<two::Colour>(  ); }
void two_Range_two_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Range<two::Colour>((*static_cast<two::Range<two::Colour>*>(other))); }
void two_StatDef_int__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::StatDef<int>(  ); }
void two_StatDef_int__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::StatDef<int>((*static_cast<two::StatDef<int>*>(other))); }
void two_StatDef_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::StatDef<float>(  ); }
void two_StatDef_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::StatDef<float>((*static_cast<two::StatDef<float>*>(other))); }
void two_Time__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Time( *static_cast<double*>(args[0]) ); }
void two_Time__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Time((*static_cast<two::Time*>(other))); }
void two_TimeSpan__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::TimeSpan( *static_cast<two::Time*>(args[0]), *static_cast<two::Time*>(args[1]) ); }
void two_TimeSpan__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TimeSpan((*static_cast<two::TimeSpan*>(other))); }
void two_rgb_0(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::rgb(*static_cast<uint32_t*>(args[0])); }
void two_rgba_1(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::rgba(*static_cast<uint32_t*>(args[0])); }
void two_abgr_2(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::abgr(*static_cast<uint32_t*>(args[0])); }
void two_hsv_3(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::hsv(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void two_hsl_4(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::hsl(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void two_to_rgba_5(span<void*> args, void*& result) { (*static_cast<uint*>(result)) = two::to_rgba(*static_cast<two::Colour*>(args[0])); }
void two_to_abgr_6(span<void*> args, void*& result) { (*static_cast<uint*>(result)) = two::to_abgr(*static_cast<two::Colour*>(args[0])); }
void two_to_abgr_7(span<void*> args, void*& result) { (*static_cast<uint*>(result)) = two::to_abgr(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3])); }
void two_to_linear_8(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::to_linear(*static_cast<two::Colour*>(args[0])); }
void two_to_gamma_9(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::to_gamma(*static_cast<two::Colour*>(args[0])); }
void two_to_srgb_10(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::to_srgb(*static_cast<two::Colour*>(args[0])); }
void two_to_hsl_11(span<void*> args, void*& result) { (*static_cast<two::ColourHSL*>(result)) = two::to_hsl(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void two_to_hsl_12(span<void*> args, void*& result) { (*static_cast<two::ColourHSL*>(result)) = two::to_hsl(*static_cast<two::Colour*>(args[0])); }
void two_to_hsla_13(span<void*> args, void*& result) { (*static_cast<two::ColourHSL*>(result)) = two::to_hsla(*static_cast<two::Colour*>(args[0])); }
void two_to_rgba_14(span<void*> args, void*& result) { (*static_cast<two::Colour*>(result)) = two::to_rgba(*static_cast<two::ColourHSL*>(args[0])); }
void sinf_15(span<void*> args, void*& result) { (*static_cast<float*>(result)) = sinf(*static_cast<float*>(args[0])); }
void cosf_16(span<void*> args, void*& result) { (*static_cast<float*>(result)) = cosf(*static_cast<float*>(args[0])); }
void sin_17(span<void*> args, void*& result) { (*static_cast<double*>(result)) = sin(*static_cast<double*>(args[0])); }
void cos_18(span<void*> args, void*& result) { (*static_cast<double*>(result)) = cos(*static_cast<double*>(args[0])); }
void two_add_float_19(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::add<float>(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void two_subtract_float_20(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::subtract<float>(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void two_multiply_float_21(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::multiply<float>(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void two_divide_float_22(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::divide<float>(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void two_nsinf_23(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::nsinf(*static_cast<float*>(args[0])); }
void two_ncosf_24(span<void*> args, void*& result) { (*static_cast<float*>(result)) = two::ncosf(*static_cast<float*>(args[0])); }
void two_nsin_25(span<void*> args, void*& result) { (*static_cast<double*>(result)) = two::nsin(*static_cast<double*>(args[0])); }
void two_ncos_26(span<void*> args, void*& result) { (*static_cast<double*>(result)) = two::ncos(*static_cast<double*>(args[0])); }
void two_add_two_v3_float_27(span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = two::add<two::v3<float>>(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_subtract_two_v3_float_28(span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = two::subtract<two::v3<float>>(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_multiply_two_v3_float_29(span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = two::multiply<two::v3<float>>(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_divide_two_v3_float_30(span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = two::divide<two::v3<float>>(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_look_dir_31(span<void*> args, void*& result) { (*static_cast<two::quat*>(result)) = two::look_dir(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_look_at_32(span<void*> args, void*& result) { (*static_cast<two::quat*>(result)) = two::look_at(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::vec3*>(args[2])); }
void two_grid_33(span<void*> args, void*& result) { UNUSED(result);  two::grid(*static_cast<two::uvec3*>(args[0]), *static_cast<stl::vector<two::uvec3>*>(args[1])); }
void two_grid_center_34(span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = two::grid_center(*static_cast<two::uvec3*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_index_list_35(span<void*> args, void*& result) { UNUSED(result);  two::index_list(*static_cast<uint32_t*>(args[0]), *static_cast<stl::vector<uint32_t>*>(args[1])); }

namespace two
{
	void two_math_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::Axis>();
		static Meta meta = { t, &namspc({ "two" }), "Axis", sizeof(two::Axis), TypeClass::Enum };
		static cstring ids[] = { "X", "Y", "Z", "None", "Count" };
		static uint32_t values[] = { 0, 1, 2, 2, 3 };
		static two::Axis vars[] = { two::Axis::X, two::Axis::Y, two::Axis::Z, two::Axis::None, two::Axis::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Axis__to_string,
		                           two_Axis__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Axes>();
		static Meta meta = { t, &namspc({ "two" }), "Axes", sizeof(two::Axes), TypeClass::Enum };
		static cstring ids[] = { "None", "X", "Y", "Z" };
		static uint32_t values[] = { 0, 1, 2, 4 };
		static two::Axes vars[] = { two::Axes::None, two::Axes::X, two::Axes::Y, two::Axes::Z};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Axes__to_string,
		                           two_Axes__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::SignedAxis>();
		static Meta meta = { t, &namspc({ "two" }), "SignedAxis", sizeof(two::SignedAxis), TypeClass::Enum };
		static cstring ids[] = { "PlusX", "MinusX", "PlusY", "MinusY", "PlusZ", "MinusZ", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static two::SignedAxis vars[] = { two::SignedAxis::PlusX, two::SignedAxis::MinusX, two::SignedAxis::PlusY, two::SignedAxis::MinusY, two::SignedAxis::PlusZ, two::SignedAxis::MinusZ, two::SignedAxis::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_SignedAxis__to_string,
		                           two_SignedAxis__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Side>();
		static Meta meta = { t, &namspc({ "two" }), "Side", sizeof(two::Side), TypeClass::Enum };
		static cstring ids[] = { "Right", "Left", "Up", "Down", "Back", "Front", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static two::Side vars[] = { two::Side::Right, two::Side::Left, two::Side::Up, two::Side::Down, two::Side::Back, two::Side::Front, two::Side::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Side__to_string,
		                           two_Side__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Clockwise>();
		static Meta meta = { t, &namspc({ "two" }), "Clockwise", sizeof(two::Clockwise), TypeClass::Enum };
		static cstring ids[] = { "CLOCKWISE", "ANTI_CLOCKWISE" };
		static uint32_t values[] = { 0, 1 };
		static two::Clockwise vars[] = { two::CLOCKWISE, two::ANTI_CLOCKWISE};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_Clockwise__to_string,
		                           two_Clockwise__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::TrackMode>();
		static Meta meta = { t, &namspc({ "two" }), "TrackMode", sizeof(two::TrackMode), TypeClass::Enum };
		static cstring ids[] = { "Constant", "ConstantRandom", "Curve", "CurveRandom" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::TrackMode vars[] = { two::TrackMode::Constant, two::TrackMode::ConstantRandom, two::TrackMode::Curve, two::TrackMode::CurveRandom};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_TrackMode__to_string,
		                           two_TrackMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::Spectrum>();
		static Meta meta = { t, &namspc({ "two" }), "Spectrum", sizeof(two::Spectrum), TypeClass::Enum };
		static cstring ids[] = { "Value", "Hue" };
		static uint32_t values[] = { 0, 1 };
		static two::Spectrum vars[] = { two::Spectrum::Value, two::Spectrum::Hue};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Spectrum__to_string,
		                           two_Spectrum__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::span<uint8_t>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<uint8_t>", sizeof(stl::span<uint8_t>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<uint8_t>(),
		                             stl_span_uint8_t__size,
		                             stl_span_uint8_t__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<int>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<int>", sizeof(stl::span<int>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<int>(),
		                             stl_span_int__size,
		                             stl_span_int__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<float>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<float>", sizeof(stl::span<float>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<float>(),
		                             stl_span_float__size,
		                             stl_span_float__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<uint32_t>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<uint32_t>", sizeof(stl::span<uint32_t>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<uint32_t>(),
		                             stl_span_uint32_t__size,
		                             stl_span_uint32_t__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::vec3>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::vec3>", sizeof(stl::span<two::vec3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::vec3>(),
		                             stl_span_two_vec3__size,
		                             stl_span_two_vec3__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::quat>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::quat>", sizeof(stl::span<two::quat>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::quat>(),
		                             stl_span_two_quat__size,
		                             stl_span_two_quat__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::Colour>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Colour>", sizeof(stl::span<two::Colour>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Colour>(),
		                             stl_span_two_Colour__size,
		                             stl_span_two_Colour__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::span<two::uvec3>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::uvec3>", sizeof(stl::span<two::uvec3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::uvec3>(),
		                             stl_span_two_uvec3__size,
		                             stl_span_two_uvec3__at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::vector<int>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<int>", sizeof(stl::vector<int>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<int>(),
		                             stl_vector_int__size,
		                             stl_vector_int__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_int__push,
		                             stl_vector_int__add,
		                             stl_vector_int__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<float>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<float>", sizeof(stl::vector<float>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<float>(),
		                             stl_vector_float__size,
		                             stl_vector_float__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_float__push,
		                             stl_vector_float__add,
		                             stl_vector_float__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<uint32_t>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<uint32_t>", sizeof(stl::vector<uint32_t>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<uint32_t>(),
		                             stl_vector_uint32_t__size,
		                             stl_vector_uint32_t__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_uint32_t__push,
		                             stl_vector_uint32_t__add,
		                             stl_vector_uint32_t__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::vec3>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::vec3>", sizeof(stl::vector<two::vec3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::vec3>(),
		                             stl_vector_two_vec3__size,
		                             stl_vector_two_vec3__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_vec3__push,
		                             stl_vector_two_vec3__add,
		                             stl_vector_two_vec3__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::quat>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::quat>", sizeof(stl::vector<two::quat>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::quat>(),
		                             stl_vector_two_quat__size,
		                             stl_vector_two_quat__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_quat__push,
		                             stl_vector_two_quat__add,
		                             stl_vector_two_quat__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Colour>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Colour>", sizeof(stl::vector<two::Colour>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Colour>(),
		                             stl_vector_two_Colour__size,
		                             stl_vector_two_Colour__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Colour__push,
		                             stl_vector_two_Colour__add,
		                             stl_vector_two_Colour__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::uvec3>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::uvec3>", sizeof(stl::vector<two::uvec3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::uvec3>(),
		                             stl_vector_two_uvec3__size,
		                             stl_vector_two_uvec3__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_uvec3__push,
		                             stl_vector_two_uvec3__add,
		                             stl_vector_two_uvec3__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// two::v2<float>
	{
		Type& t = type<two::v2<float>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<float>", sizeof(two::v2<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_float__construct_0, {} },
			{ t, two_v2_float__construct_1, { { "v", type<float>(),  } } },
			{ t, two_v2_float__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<float>, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<float>, y), type<float>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v3<float>
	{
		Type& t = type<two::v3<float>>();
		static Meta meta = { t, &namspc({ "two" }), "v3<float>", sizeof(two::v3<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v3_float__construct_0, {} },
			{ t, two_v3_float__construct_1, { { "v", type<float>(),  } } },
			{ t, two_v3_float__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v3_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v3<float>, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v3<float>, y), type<float>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v3<float>, z), type<float>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v4<float>
	{
		Type& t = type<two::v4<float>>();
		static Meta meta = { t, &namspc({ "two" }), "v4<float>", sizeof(two::v4<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v4_float__construct_0, {} },
			{ t, two_v4_float__construct_1, { { "v", type<float>(),  } } },
			{ t, two_v4_float__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  }, { "w", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v4_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v4<float>, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<float>, y), type<float>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<float>, z), type<float>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<float>, w), type<float>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v2<int>
	{
		Type& t = type<two::v2<int>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<int>", sizeof(two::v2<int>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_int__construct_0, {} },
			{ t, two_v2_int__construct_1, { { "v", type<int>(),  } } },
			{ t, two_v2_int__construct_2, { { "x", type<int>(),  }, { "y", type<int>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_int__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<int>, x), type<int>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<int>, y), type<int>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v3<int>
	{
		Type& t = type<two::v3<int>>();
		static Meta meta = { t, &namspc({ "two" }), "v3<int>", sizeof(two::v3<int>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v3_int__construct_0, {} },
			{ t, two_v3_int__construct_1, { { "v", type<int>(),  } } },
			{ t, two_v3_int__construct_2, { { "x", type<int>(),  }, { "y", type<int>(),  }, { "z", type<int>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v3_int__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v3<int>, x), type<int>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v3<int>, y), type<int>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v3<int>, z), type<int>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v4<int>
	{
		Type& t = type<two::v4<int>>();
		static Meta meta = { t, &namspc({ "two" }), "v4<int>", sizeof(two::v4<int>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v4_int__construct_0, {} },
			{ t, two_v4_int__construct_1, { { "v", type<int>(),  } } },
			{ t, two_v4_int__construct_2, { { "x", type<int>(),  }, { "y", type<int>(),  }, { "z", type<int>(),  }, { "w", type<int>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v4_int__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v4<int>, x), type<int>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<int>, y), type<int>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<int>, z), type<int>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<int>, w), type<int>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v2<uint>
	{
		Type& t = type<two::v2<uint>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<uint>", sizeof(two::v2<uint>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_uint__construct_0, {} },
			{ t, two_v2_uint__construct_1, { { "v", type<uint>(),  } } },
			{ t, two_v2_uint__construct_2, { { "x", type<uint>(),  }, { "y", type<uint>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_uint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<uint>, x), type<uint>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<uint>, y), type<uint>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v3<uint>
	{
		Type& t = type<two::v3<uint>>();
		static Meta meta = { t, &namspc({ "two" }), "v3<uint>", sizeof(two::v3<uint>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v3_uint__construct_0, {} },
			{ t, two_v3_uint__construct_1, { { "v", type<uint>(),  } } },
			{ t, two_v3_uint__construct_2, { { "x", type<uint>(),  }, { "y", type<uint>(),  }, { "z", type<uint>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v3_uint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v3<uint>, x), type<uint>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v3<uint>, y), type<uint>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v3<uint>, z), type<uint>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v4<uint>
	{
		Type& t = type<two::v4<uint>>();
		static Meta meta = { t, &namspc({ "two" }), "v4<uint>", sizeof(two::v4<uint>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v4_uint__construct_0, {} },
			{ t, two_v4_uint__construct_1, { { "v", type<uint>(),  } } },
			{ t, two_v4_uint__construct_2, { { "x", type<uint>(),  }, { "y", type<uint>(),  }, { "z", type<uint>(),  }, { "w", type<uint>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v4_uint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v4<uint>, x), type<uint>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<uint>, y), type<uint>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<uint>, z), type<uint>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<uint>, w), type<uint>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v2<bool>
	{
		Type& t = type<two::v2<bool>>();
		static Meta meta = { t, &namspc({ "two" }), "v2<bool>", sizeof(two::v2<bool>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v2_bool__construct_0, {} },
			{ t, two_v2_bool__construct_1, { { "v", type<bool>(),  } } },
			{ t, two_v2_bool__construct_2, { { "x", type<bool>(),  }, { "y", type<bool>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v2_bool__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v2<bool>, x), type<bool>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v2<bool>, y), type<bool>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v3<bool>
	{
		Type& t = type<two::v3<bool>>();
		static Meta meta = { t, &namspc({ "two" }), "v3<bool>", sizeof(two::v3<bool>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v3_bool__construct_0, {} },
			{ t, two_v3_bool__construct_1, { { "v", type<bool>(),  } } },
			{ t, two_v3_bool__construct_2, { { "x", type<bool>(),  }, { "y", type<bool>(),  }, { "z", type<bool>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v3_bool__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v3<bool>, x), type<bool>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v3<bool>, y), type<bool>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v3<bool>, z), type<bool>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::v4<bool>
	{
		Type& t = type<two::v4<bool>>();
		static Meta meta = { t, &namspc({ "two" }), "v4<bool>", sizeof(two::v4<bool>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_v4_bool__construct_0, {} },
			{ t, two_v4_bool__construct_1, { { "v", type<bool>(),  } } },
			{ t, two_v4_bool__construct_2, { { "x", type<bool>(),  }, { "y", type<bool>(),  }, { "z", type<bool>(),  }, { "w", type<bool>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_v4_bool__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::v4<bool>, x), type<bool>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<bool>, y), type<bool>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<bool>, z), type<bool>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::v4<bool>, w), type<bool>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::mat3
	{
		Type& t = type<two::mat3>();
		static Meta meta = { t, &namspc({ "two" }), "mat3", sizeof(two::mat3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_mat3__construct_0, {} },
			{ t, two_mat3__construct_1, { { "x", type<two::float3>(),  }, { "y", type<two::float3>(),  }, { "z", type<two::float3>(),  } } },
			{ t, two_mat3__construct_2, { { "f0", type<float>(),  }, { "f1", type<float>(),  }, { "f2", type<float>(),  }, { "f3", type<float>(),  }, { "f4", type<float>(),  }, { "f5", type<float>(),  }, { "f6", type<float>(),  }, { "f7", type<float>(),  }, { "f8", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_mat3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::mat3, f), type<float>(), "f", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::mat4
	{
		Type& t = type<two::mat4>();
		static Meta meta = { t, &namspc({ "two" }), "mat4", sizeof(two::mat4), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_mat4__construct_0, {} },
			{ t, two_mat4__construct_1, { { "x", type<two::float4>(),  }, { "y", type<two::float4>(),  }, { "z", type<two::float4>(),  }, { "w", type<two::float4>(),  } } },
			{ t, two_mat4__construct_2, { { "f0", type<float>(),  }, { "f1", type<float>(),  }, { "f2", type<float>(),  }, { "f3", type<float>(),  }, { "f4", type<float>(),  }, { "f5", type<float>(),  }, { "f6", type<float>(),  }, { "f7", type<float>(),  }, { "f8", type<float>(),  }, { "f9", type<float>(),  }, { "f10", type<float>(),  }, { "f11", type<float>(),  }, { "f12", type<float>(),  }, { "f13", type<float>(),  }, { "f14", type<float>(),  }, { "f15", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_mat4__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::mat4, f), type<float>(), "f", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::quat
	{
		Type& t = type<two::quat>();
		static Meta meta = { t, &namspc({ "two" }), "quat", sizeof(two::quat), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::v4<float>>() };
		static size_t bases_offsets[] = { base_offset<two::quat, two::v4<float>>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_quat__construct_0, {} },
			{ t, two_quat__construct_1, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  }, { "w", type<float>(),  } } },
			{ t, two_quat__construct_2, { { "euler_angles", type<two::float3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_quat__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Transform
	{
		Type& t = type<two::Transform>();
		static Meta meta = { t, &namspc({ "two" }), "Transform", sizeof(two::Transform), TypeClass::Struct };
		// bases
		// defaults
		static two::quat rotation_default = ZeroQuat;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Transform__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Transform__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Transform, m_position), type<two::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Transform, m_rotation), type<two::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(two::Transform, m_scale), type<two::vec3>(), "scale", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ColourHSL
	{
		Type& t = type<two::ColourHSL>();
		static Meta meta = { t, &namspc({ "two" }), "ColourHSL", sizeof(two::ColourHSL), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ColourHSL__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ColourHSL__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ColourHSL, h), type<float>(), "h", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ColourHSL, s), type<float>(), "s", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ColourHSL, l), type<float>(), "l", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ColourHSL, a), type<float>(), "a", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Colour
	{
		Type& t = type<two::Colour>();
		static Meta meta = { t, &namspc({ "two" }), "Colour", sizeof(two::Colour), TypeClass::Struct };
		// bases
		// defaults
		static float construct_1_a_default = 1.f;
		static float construct_2_a_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Colour__construct_0, {} },
			{ t, two_Colour__construct_1, { { "v", type<float>(),  }, { "a", type<float>(), Param::Default, &construct_1_a_default } } },
			{ t, two_Colour__construct_2, { { "r", type<float>(),  }, { "g", type<float>(),  }, { "b", type<float>(),  }, { "a", type<float>(), Param::Default, &construct_2_a_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Colour, r), type<float>(), "r", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Colour, g), type<float>(), "g", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Colour, b), type<float>(), "b", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Colour, a), type<float>(), "a", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Static statics[] = {
			{ t, "Black", Ref(&two::Colour::Black) },
			{ t, "AlphaBlack", Ref(&two::Colour::AlphaBlack) },
			{ t, "Red", Ref(&two::Colour::Red) },
			{ t, "Green", Ref(&two::Colour::Green) },
			{ t, "NeonGreen", Ref(&two::Colour::NeonGreen) },
			{ t, "Blue", Ref(&two::Colour::Blue) },
			{ t, "Pink", Ref(&two::Colour::Pink) },
			{ t, "Cyan", Ref(&two::Colour::Cyan) },
			{ t, "Yellow", Ref(&two::Colour::Yellow) },
			{ t, "White", Ref(&two::Colour::White) },
			{ t, "AlphaWhite", Ref(&two::Colour::AlphaWhite) },
			{ t, "LightGrey", Ref(&two::Colour::LightGrey) },
			{ t, "MidGrey", Ref(&two::Colour::MidGrey) },
			{ t, "DarkGrey", Ref(&two::Colour::DarkGrey) },
			{ t, "AlphaGrey", Ref(&two::Colour::AlphaGrey) },
			{ t, "Transparent", Ref(&two::Colour::Transparent) },
			{ t, "Invisible", Ref(&two::Colour::Invisible) },
			{ t, "None", Ref(&two::Colour::None) }
		};
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, statics, };
	}
	// two::ValueCurve<float>
	{
		Type& t = type<two::ValueCurve<float>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueCurve<float>", sizeof(two::ValueCurve<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueCurve_float__construct_0, {} },
			{ t, two_ValueCurve_float__construct_1, { { "keys", type<stl::span<float>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueCurve_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueCurve<float>, m_keys), type<stl::vector<float>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueCurve<uint32_t>
	{
		Type& t = type<two::ValueCurve<uint32_t>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueCurve<uint32_t>", sizeof(two::ValueCurve<uint32_t>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueCurve_uint32_t__construct_0, {} },
			{ t, two_ValueCurve_uint32_t__construct_1, { { "keys", type<stl::span<uint32_t>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueCurve_uint32_t__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueCurve<uint32_t>, m_keys), type<stl::vector<uint32_t>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueCurve<two::vec3>
	{
		Type& t = type<two::ValueCurve<two::vec3>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueCurve<two::vec3>", sizeof(two::ValueCurve<two::vec3>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueCurve_two_vec3__construct_0, {} },
			{ t, two_ValueCurve_two_vec3__construct_1, { { "keys", type<stl::span<two::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueCurve_two_vec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueCurve<two::vec3>, m_keys), type<stl::vector<two::vec3>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueCurve<two::quat>
	{
		Type& t = type<two::ValueCurve<two::quat>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueCurve<two::quat>", sizeof(two::ValueCurve<two::quat>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueCurve_two_quat__construct_0, {} },
			{ t, two_ValueCurve_two_quat__construct_1, { { "keys", type<stl::span<two::quat>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueCurve_two_quat__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueCurve<two::quat>, m_keys), type<stl::vector<two::quat>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueCurve<two::Colour>
	{
		Type& t = type<two::ValueCurve<two::Colour>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueCurve<two::Colour>", sizeof(two::ValueCurve<two::Colour>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueCurve_two_Colour__construct_0, {} },
			{ t, two_ValueCurve_two_Colour__construct_1, { { "keys", type<stl::span<two::Colour>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueCurve_two_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueCurve<two::Colour>, m_keys), type<stl::vector<two::Colour>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueTrack<two::vec3>
	{
		Type& t = type<two::ValueTrack<two::vec3>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueTrack<two::vec3>", sizeof(two::ValueTrack<two::vec3>), TypeClass::Struct };
		// bases
		// defaults
		static two::vec3 value_default = One<two::vec3>::value();
		static two::vec3 min_default = One<two::vec3>::value();
		static two::vec3 max_default = One<two::vec3>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueTrack_two_vec3__construct_0, {} },
			{ t, two_ValueTrack_two_vec3__construct_1, { { "mode", type<two::TrackMode>(),  }, { "curve", type<two::ValueCurve<two::vec3>>(),  }, { "min_curve", type<two::ValueCurve<two::vec3>>(),  }, { "max_curve", type<two::ValueCurve<two::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueTrack_two_vec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueTrack<two::vec3>, m_mode), type<two::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::vec3>, m_value), type<two::vec3>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::vec3>, m_min), type<two::vec3>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::vec3>, m_max), type<two::vec3>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::vec3>, m_curve), type<two::ValueCurve<two::vec3>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::vec3>, m_min_curve), type<two::ValueCurve<two::vec3>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::vec3>, m_max_curve), type<two::ValueCurve<two::vec3>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueTrack<two::quat>
	{
		Type& t = type<two::ValueTrack<two::quat>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueTrack<two::quat>", sizeof(two::ValueTrack<two::quat>), TypeClass::Struct };
		// bases
		// defaults
		static two::quat value_default = One<two::quat>::value();
		static two::quat min_default = One<two::quat>::value();
		static two::quat max_default = One<two::quat>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueTrack_two_quat__construct_0, {} },
			{ t, two_ValueTrack_two_quat__construct_1, { { "mode", type<two::TrackMode>(),  }, { "curve", type<two::ValueCurve<two::quat>>(),  }, { "min_curve", type<two::ValueCurve<two::quat>>(),  }, { "max_curve", type<two::ValueCurve<two::quat>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueTrack_two_quat__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueTrack<two::quat>, m_mode), type<two::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::quat>, m_value), type<two::quat>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::quat>, m_min), type<two::quat>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::quat>, m_max), type<two::quat>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::quat>, m_curve), type<two::ValueCurve<two::quat>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::quat>, m_min_curve), type<two::ValueCurve<two::quat>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::quat>, m_max_curve), type<two::ValueCurve<two::quat>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueTrack<float>
	{
		Type& t = type<two::ValueTrack<float>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueTrack<float>", sizeof(two::ValueTrack<float>), TypeClass::Struct };
		// bases
		// defaults
		static float value_default = One<float>::value();
		static float min_default = One<float>::value();
		static float max_default = One<float>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueTrack_float__construct_0, {} },
			{ t, two_ValueTrack_float__construct_1, { { "mode", type<two::TrackMode>(),  }, { "curve", type<two::ValueCurve<float>>(),  }, { "min_curve", type<two::ValueCurve<float>>(),  }, { "max_curve", type<two::ValueCurve<float>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueTrack_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueTrack<float>, m_mode), type<two::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<float>, m_value), type<float>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<float>, m_min), type<float>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<float>, m_max), type<float>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<float>, m_curve), type<two::ValueCurve<float>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<float>, m_min_curve), type<two::ValueCurve<float>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<float>, m_max_curve), type<two::ValueCurve<float>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueTrack<uint32_t>
	{
		Type& t = type<two::ValueTrack<uint32_t>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueTrack<uint32_t>", sizeof(two::ValueTrack<uint32_t>), TypeClass::Struct };
		// bases
		// defaults
		static uint32_t value_default = One<uint32_t>::value();
		static uint32_t min_default = One<uint32_t>::value();
		static uint32_t max_default = One<uint32_t>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueTrack_uint32_t__construct_0, {} },
			{ t, two_ValueTrack_uint32_t__construct_1, { { "mode", type<two::TrackMode>(),  }, { "curve", type<two::ValueCurve<uint32_t>>(),  }, { "min_curve", type<two::ValueCurve<uint32_t>>(),  }, { "max_curve", type<two::ValueCurve<uint32_t>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueTrack_uint32_t__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueTrack<uint32_t>, m_mode), type<two::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<uint32_t>, m_value), type<uint32_t>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<uint32_t>, m_min), type<uint32_t>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<uint32_t>, m_max), type<uint32_t>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<uint32_t>, m_curve), type<two::ValueCurve<uint32_t>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<uint32_t>, m_min_curve), type<two::ValueCurve<uint32_t>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<uint32_t>, m_max_curve), type<two::ValueCurve<uint32_t>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ValueTrack<two::Colour>
	{
		Type& t = type<two::ValueTrack<two::Colour>>();
		static Meta meta = { t, &namspc({ "two" }), "ValueTrack<two::Colour>", sizeof(two::ValueTrack<two::Colour>), TypeClass::Struct };
		// bases
		// defaults
		static two::Colour value_default = One<two::Colour>::value();
		static two::Colour min_default = One<two::Colour>::value();
		static two::Colour max_default = One<two::Colour>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, two_ValueTrack_two_Colour__construct_0, {} },
			{ t, two_ValueTrack_two_Colour__construct_1, { { "mode", type<two::TrackMode>(),  }, { "curve", type<two::ValueCurve<two::Colour>>(),  }, { "min_curve", type<two::ValueCurve<two::Colour>>(),  }, { "max_curve", type<two::ValueCurve<two::Colour>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ValueTrack_two_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ValueTrack<two::Colour>, m_mode), type<two::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::Colour>, m_value), type<two::Colour>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::Colour>, m_min), type<two::Colour>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::Colour>, m_max), type<two::Colour>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::Colour>, m_curve), type<two::ValueCurve<two::Colour>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::Colour>, m_min_curve), type<two::ValueCurve<two::Colour>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ValueTrack<two::Colour>, m_max_curve), type<two::ValueCurve<two::Colour>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Image
	{
		Type& t = type<two::Image>();
		static Meta meta = { t, &namspc({ "two" }), "Image", sizeof(two::Image), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Image__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Image__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Image, d_name), type<stl::string>(), "d_name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Image, d_path), type<stl::string>(), "d_path", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Palette
	{
		Type& t = type<two::Palette>();
		static Meta meta = { t, &namspc({ "two" }), "Palette", sizeof(two::Palette), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Palette__construct_0, { { "spectrum", type<two::Spectrum>(),  }, { "steps", type<size_t>(),  } } },
			{ t, two_Palette__construct_1, { { "colours", type<stl::span<two::Colour>>(),  } } },
			{ t, two_Palette__construct_2, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Palette__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Image256
	{
		Type& t = type<two::Image256>();
		static Meta meta = { t, &namspc({ "two" }), "Image256", sizeof(two::Image256), TypeClass::Struct };
		// bases
		// defaults
		static two::uvec2 construct_0_size_default = uvec2(0U);
		static two::Palette construct_0_palette_default = two::Palette();
		// constructors
		static Constructor constructors[] = {
			{ t, two_Image256__construct_0, { { "size", type<two::uvec2>(), Param::Default, &construct_0_size_default }, { "palette", type<two::Palette>(), Param::Default, &construct_0_palette_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Image256__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Image256, m_pixels), type<stl::vector<uint32_t>>(), "pixels", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Image256, m_size), type<two::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Image256, m_palette), type<two::Palette>(), "palette", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ImageAtlas
	{
		Type& t = type<two::ImageAtlas>();
		static Meta meta = { t, &namspc({ "two" }), "ImageAtlas", sizeof(two::ImageAtlas), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::TextureAtlas
	{
		Type& t = type<two::TextureAtlas>();
		static Meta meta = { t, &namspc({ "two" }), "TextureAtlas", sizeof(two::TextureAtlas), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ImageAtlas>() };
		static size_t bases_offsets[] = { base_offset<two::TextureAtlas, two::ImageAtlas>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Sprite
	{
		Type& t = type<two::Sprite>();
		static Meta meta = { t, &namspc({ "two" }), "Sprite", sizeof(two::Sprite), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Image>() };
		static size_t bases_offsets[] = { base_offset<two::Sprite, two::Image>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::SpriteAtlas
	{
		Type& t = type<two::SpriteAtlas>();
		static Meta meta = { t, &namspc({ "two" }), "SpriteAtlas", sizeof(two::SpriteAtlas), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ImageAtlas>() };
		static size_t bases_offsets[] = { base_offset<two::SpriteAtlas, two::ImageAtlas>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Range<two::vec3>
	{
		Type& t = type<two::Range<two::vec3>>();
		static Meta meta = { t, &namspc({ "two" }), "Range<two::vec3>", sizeof(two::Range<two::vec3>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Range_two_vec3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Range_two_vec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Range<two::vec3>, m_min), type<two::vec3>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Range<two::vec3>, m_max), type<two::vec3>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Range<two::quat>
	{
		Type& t = type<two::Range<two::quat>>();
		static Meta meta = { t, &namspc({ "two" }), "Range<two::quat>", sizeof(two::Range<two::quat>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Range_two_quat__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Range_two_quat__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Range<two::quat>, m_min), type<two::quat>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Range<two::quat>, m_max), type<two::quat>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Range<float>
	{
		Type& t = type<two::Range<float>>();
		static Meta meta = { t, &namspc({ "two" }), "Range<float>", sizeof(two::Range<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Range_float__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Range_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Range<float>, m_min), type<float>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Range<float>, m_max), type<float>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Range<uint32_t>
	{
		Type& t = type<two::Range<uint32_t>>();
		static Meta meta = { t, &namspc({ "two" }), "Range<uint32_t>", sizeof(two::Range<uint32_t>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Range_uint32_t__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Range_uint32_t__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Range<uint32_t>, m_min), type<uint32_t>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Range<uint32_t>, m_max), type<uint32_t>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Range<two::Colour>
	{
		Type& t = type<two::Range<two::Colour>>();
		static Meta meta = { t, &namspc({ "two" }), "Range<two::Colour>", sizeof(two::Range<two::Colour>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Range_two_Colour__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Range_two_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Range<two::Colour>, m_min), type<two::Colour>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Range<two::Colour>, m_max), type<two::Colour>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::StatDef<int>
	{
		Type& t = type<two::StatDef<int>>();
		static Meta meta = { t, &namspc({ "two" }), "StatDef<int>", sizeof(two::StatDef<int>), TypeClass::Struct };
		// bases
		// defaults
		static int min_default = limits<int>::min();
		static int max_default = limits<int>::max();
		static int step_default = int(1);
		// constructors
		static Constructor constructors[] = {
			{ t, two_StatDef_int__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_StatDef_int__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::StatDef<int>, m_min), type<int>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::StatDef<int>, m_max), type<int>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(two::StatDef<int>, m_step), type<int>(), "step", &step_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::StatDef<float>
	{
		Type& t = type<two::StatDef<float>>();
		static Meta meta = { t, &namspc({ "two" }), "StatDef<float>", sizeof(two::StatDef<float>), TypeClass::Struct };
		// bases
		// defaults
		static float min_default = limits<float>::min();
		static float max_default = limits<float>::max();
		static float step_default = float(1);
		// constructors
		static Constructor constructors[] = {
			{ t, two_StatDef_float__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_StatDef_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::StatDef<float>, m_min), type<float>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::StatDef<float>, m_max), type<float>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(two::StatDef<float>, m_step), type<float>(), "step", &step_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Time
	{
		Type& t = type<two::Time>();
		static Meta meta = { t, &namspc({ "two" }), "Time", sizeof(two::Time), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Time__construct_0, { { "value", type<double>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Time__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Time, m_value), type<double>(), "value", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::TimeSpan
	{
		Type& t = type<two::TimeSpan>();
		static Meta meta = { t, &namspc({ "two" }), "TimeSpan", sizeof(two::TimeSpan), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_TimeSpan__construct_0, { { "s", type<two::Time>(),  }, { "e", type<two::Time>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TimeSpan__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::TimeSpan, start), type<two::Time>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::TimeSpan, end), type<two::Time>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	
	{
		Type& t = type<two::v2<float>>();
		static Alias alias = { &t, &namspc({ "two" }), "float2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v3<float>>();
		static Alias alias = { &t, &namspc({ "two" }), "float3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v4<float>>();
		static Alias alias = { &t, &namspc({ "two" }), "float4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v2<int>>();
		static Alias alias = { &t, &namspc({ "two" }), "int2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v3<int>>();
		static Alias alias = { &t, &namspc({ "two" }), "int3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v4<int>>();
		static Alias alias = { &t, &namspc({ "two" }), "int4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v2<uint>>();
		static Alias alias = { &t, &namspc({ "two" }), "uint2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v3<uint>>();
		static Alias alias = { &t, &namspc({ "two" }), "uint3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v4<uint>>();
		static Alias alias = { &t, &namspc({ "two" }), "uint4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v2<bool>>();
		static Alias alias = { &t, &namspc({ "two" }), "bool2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v3<bool>>();
		static Alias alias = { &t, &namspc({ "two" }), "bool3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v4<bool>>();
		static Alias alias = { &t, &namspc({ "two" }), "bool4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v2<float>>();
		static Alias alias = { &t, &namspc({ "two" }), "vec2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v3<float>>();
		static Alias alias = { &t, &namspc({ "two" }), "vec3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v4<float>>();
		static Alias alias = { &t, &namspc({ "two" }), "vec4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v2<uint>>();
		static Alias alias = { &t, &namspc({ "two" }), "uvec2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v3<uint>>();
		static Alias alias = { &t, &namspc({ "two" }), "uvec3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v4<uint>>();
		static Alias alias = { &t, &namspc({ "two" }), "uvec4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v2<int>>();
		static Alias alias = { &t, &namspc({ "two" }), "ivec2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v3<int>>();
		static Alias alias = { &t, &namspc({ "two" }), "ivec3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v4<int>>();
		static Alias alias = { &t, &namspc({ "two" }), "ivec4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v3<bool>>();
		static Alias alias = { &t, &namspc({ "two" }), "bvec3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<two::v4<bool>>();
		static Alias alias = { &t, &namspc({ "two" }), "bvec4" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<stl::span<uint8_t>>());
		m.m_types.push_back(&type<stl::span<int>>());
		m.m_types.push_back(&type<stl::span<float>>());
		m.m_types.push_back(&type<stl::span<uint32_t>>());
		m.m_types.push_back(&type<stl::span<two::vec3>>());
		m.m_types.push_back(&type<stl::span<two::quat>>());
		m.m_types.push_back(&type<stl::span<two::Colour>>());
		m.m_types.push_back(&type<stl::span<two::uvec3>>());
		m.m_types.push_back(&type<stl::vector<int>>());
		m.m_types.push_back(&type<stl::vector<float>>());
		m.m_types.push_back(&type<stl::vector<uint32_t>>());
		m.m_types.push_back(&type<stl::vector<two::vec3>>());
		m.m_types.push_back(&type<stl::vector<two::quat>>());
		m.m_types.push_back(&type<stl::vector<two::Colour>>());
		m.m_types.push_back(&type<stl::vector<two::uvec3>>());
		m.m_types.push_back(&type<two::Axis>());
		m.m_types.push_back(&type<two::Axes>());
		m.m_types.push_back(&type<two::SignedAxis>());
		m.m_types.push_back(&type<two::Side>());
		m.m_types.push_back(&type<two::v2<float>>());
		m.m_types.push_back(&type<two::v3<float>>());
		m.m_types.push_back(&type<two::v4<float>>());
		m.m_types.push_back(&type<two::v2<int>>());
		m.m_types.push_back(&type<two::v3<int>>());
		m.m_types.push_back(&type<two::v4<int>>());
		m.m_types.push_back(&type<two::v2<uint>>());
		m.m_types.push_back(&type<two::v3<uint>>());
		m.m_types.push_back(&type<two::v4<uint>>());
		m.m_types.push_back(&type<two::v2<bool>>());
		m.m_types.push_back(&type<two::v3<bool>>());
		m.m_types.push_back(&type<two::v4<bool>>());
		m.m_types.push_back(&type<two::float2>());
		m.m_types.push_back(&type<two::float3>());
		m.m_types.push_back(&type<two::float4>());
		m.m_types.push_back(&type<two::int2>());
		m.m_types.push_back(&type<two::int3>());
		m.m_types.push_back(&type<two::int4>());
		m.m_types.push_back(&type<two::uint2>());
		m.m_types.push_back(&type<two::uint3>());
		m.m_types.push_back(&type<two::uint4>());
		m.m_types.push_back(&type<two::bool2>());
		m.m_types.push_back(&type<two::bool3>());
		m.m_types.push_back(&type<two::bool4>());
		m.m_types.push_back(&type<two::vec2>());
		m.m_types.push_back(&type<two::vec3>());
		m.m_types.push_back(&type<two::vec4>());
		m.m_types.push_back(&type<two::uvec2>());
		m.m_types.push_back(&type<two::uvec3>());
		m.m_types.push_back(&type<two::uvec4>());
		m.m_types.push_back(&type<two::ivec2>());
		m.m_types.push_back(&type<two::ivec3>());
		m.m_types.push_back(&type<two::ivec4>());
		m.m_types.push_back(&type<two::bvec3>());
		m.m_types.push_back(&type<two::bvec4>());
		m.m_types.push_back(&type<two::mat3>());
		m.m_types.push_back(&type<two::mat4>());
		m.m_types.push_back(&type<two::quat>());
		m.m_types.push_back(&type<two::Clockwise>());
		m.m_types.push_back(&type<two::Transform>());
		m.m_types.push_back(&type<two::ColourHSL>());
		m.m_types.push_back(&type<two::Colour>());
		m.m_types.push_back(&type<two::TrackMode>());
		m.m_types.push_back(&type<two::ValueCurve<float>>());
		m.m_types.push_back(&type<two::ValueCurve<uint32_t>>());
		m.m_types.push_back(&type<two::ValueCurve<two::vec3>>());
		m.m_types.push_back(&type<two::ValueCurve<two::quat>>());
		m.m_types.push_back(&type<two::ValueCurve<two::Colour>>());
		m.m_types.push_back(&type<two::ValueTrack<two::vec3>>());
		m.m_types.push_back(&type<two::ValueTrack<two::quat>>());
		m.m_types.push_back(&type<two::ValueTrack<float>>());
		m.m_types.push_back(&type<two::ValueTrack<uint32_t>>());
		m.m_types.push_back(&type<two::ValueTrack<two::Colour>>());
		m.m_types.push_back(&type<two::Image>());
		m.m_types.push_back(&type<two::Spectrum>());
		m.m_types.push_back(&type<two::Palette>());
		m.m_types.push_back(&type<two::Image256>());
		m.m_types.push_back(&type<two::ImageAtlas>());
		m.m_types.push_back(&type<two::TextureAtlas>());
		m.m_types.push_back(&type<two::Sprite>());
		m.m_types.push_back(&type<two::SpriteAtlas>());
		m.m_types.push_back(&type<two::Range<two::vec3>>());
		m.m_types.push_back(&type<two::Range<two::quat>>());
		m.m_types.push_back(&type<two::Range<float>>());
		m.m_types.push_back(&type<two::Range<uint32_t>>());
		m.m_types.push_back(&type<two::Range<two::Colour>>());
		m.m_types.push_back(&type<two::StatDef<int>>());
		m.m_types.push_back(&type<two::StatDef<float>>());
		m.m_types.push_back(&type<two::Time>());
		m.m_types.push_back(&type<two::TimeSpan>());
		{
			static Function f = { &namspc({ "two" }), "rgb", funcptr<two::Colour(*)(uint32_t)>(two::rgb), two_rgb_0, { { "colour", type<uint32_t>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "rgba", funcptr<two::Colour(*)(uint32_t)>(two::rgba), two_rgba_1, { { "colour", type<uint32_t>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "abgr", funcptr<two::Colour(*)(uint32_t)>(two::abgr), two_abgr_2, { { "colour", type<uint32_t>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "hsv", funcptr<two::Colour(*)(float, float, float)>(two::hsv), two_hsv_3, { { "h", type<float>(),  }, { "s", type<float>(),  }, { "v", type<float>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "hsl", funcptr<two::Colour(*)(float, float, float)>(two::hsl), two_hsl_4, { { "h", type<float>(),  }, { "s", type<float>(),  }, { "l", type<float>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_rgba", funcptr<uint32_t(*)(const two::Colour&)>(two::to_rgba), two_to_rgba_5, { { "colour", type<two::Colour>(),  } }, { &type<uint32_t>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_abgr", funcptr<uint32_t(*)(const two::Colour&)>(two::to_abgr), two_to_abgr_6, { { "colour", type<two::Colour>(),  } }, { &type<uint32_t>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float a_default = 1.f;
			static Function f = { &namspc({ "two" }), "to_abgr", funcptr<uint32_t(*)(float, float, float, float)>(two::to_abgr), two_to_abgr_7, { { "r", type<float>(),  }, { "g", type<float>(),  }, { "b", type<float>(),  }, { "a", type<float>(), Param::Default, &a_default } }, { &type<uint32_t>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_linear", funcptr<two::Colour(*)(const two::Colour&)>(two::to_linear), two_to_linear_8, { { "colour", type<two::Colour>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_gamma", funcptr<two::Colour(*)(const two::Colour&)>(two::to_gamma), two_to_gamma_9, { { "colour", type<two::Colour>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_srgb", funcptr<two::Colour(*)(const two::Colour&)>(two::to_srgb), two_to_srgb_10, { { "colour", type<two::Colour>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_hsl", funcptr<two::ColourHSL(*)(float, float, float)>(two::to_hsl), two_to_hsl_11, { { "r", type<float>(),  }, { "g", type<float>(),  }, { "b", type<float>(),  } }, { &type<two::ColourHSL>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_hsl", funcptr<two::ColourHSL(*)(const two::Colour&)>(two::to_hsl), two_to_hsl_12, { { "colour", type<two::Colour>(),  } }, { &type<two::ColourHSL>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_hsla", funcptr<two::ColourHSL(*)(const two::Colour&)>(two::to_hsla), two_to_hsla_13, { { "colour", type<two::Colour>(),  } }, { &type<two::ColourHSL>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_rgba", funcptr<two::Colour(*)(const two::ColourHSL&)>(two::to_rgba), two_to_rgba_14, { { "colour", type<two::ColourHSL>(),  } }, { &type<two::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "sinf", funcptr<float(*)(float)>(sinf), sinf_15, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "cosf", funcptr<float(*)(float)>(cosf), cosf_16, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "sin", funcptr<double(*)(double)>(sin), sin_17, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "cos", funcptr<double(*)(double)>(cos), cos_18, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "add<float>", funcptr<float(*)(float, float)>(two::add<float>), two_add_float_19, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "subtract<float>", funcptr<float(*)(float, float)>(two::subtract<float>), two_subtract_float_20, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "multiply<float>", funcptr<float(*)(float, float)>(two::multiply<float>), two_multiply_float_21, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "divide<float>", funcptr<float(*)(float, float)>(two::divide<float>), two_divide_float_22, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "nsinf", funcptr<float(*)(float)>(two::nsinf), two_nsinf_23, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "ncosf", funcptr<float(*)(float)>(two::ncosf), two_ncosf_24, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "nsin", funcptr<double(*)(double)>(two::nsin), two_nsin_25, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "ncos", funcptr<double(*)(double)>(two::ncos), two_ncos_26, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "add<two::v3<float>>", funcptr<two::vec3(*)(two::vec3, two::vec3)>(two::add<two::v3<float>>), two_add_two_v3_float_27, { { "a", type<two::vec3>(),  }, { "b", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "subtract<two::v3<float>>", funcptr<two::vec3(*)(two::vec3, two::vec3)>(two::subtract<two::v3<float>>), two_subtract_two_v3_float_28, { { "a", type<two::vec3>(),  }, { "b", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "multiply<two::v3<float>>", funcptr<two::vec3(*)(two::vec3, two::vec3)>(two::multiply<two::v3<float>>), two_multiply_two_v3_float_29, { { "a", type<two::vec3>(),  }, { "b", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "divide<two::v3<float>>", funcptr<two::vec3(*)(two::vec3, two::vec3)>(two::divide<two::v3<float>>), two_divide_two_v3_float_30, { { "a", type<two::vec3>(),  }, { "b", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::vec3 forward_default = -z3;
			static Function f = { &namspc({ "two" }), "look_dir", funcptr<two::quat(*)(const two::vec3&, const two::vec3&)>(two::look_dir), two_look_dir_31, { { "direction", type<two::vec3>(),  }, { "forward", type<two::vec3>(), Param::Default, &forward_default } }, { &type<two::quat>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::vec3 forward_default = -z3;
			static Function f = { &namspc({ "two" }), "look_at", funcptr<two::quat(*)(const two::vec3&, const two::vec3&, const two::vec3&)>(two::look_at), two_look_at_32, { { "eye", type<two::vec3>(),  }, { "target", type<two::vec3>(),  }, { "forward", type<two::vec3>(), Param::Default, &forward_default } }, { &type<two::quat>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "grid", funcptr<void(*)(const two::uvec3&, stl::vector<two::uvec3>&)>(two::grid), two_grid_33, { { "size", type<two::uvec3>(),  }, { "output_coords", type<stl::vector<two::uvec3>>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "grid_center", funcptr<two::vec3(*)(const two::uvec3&, const two::vec3&)>(two::grid_center), two_grid_center_34, { { "coord", type<two::uvec3>(),  }, { "cell_size", type<two::vec3>(),  } }, { &type<two::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "index_list", funcptr<void(*)(uint32_t, stl::vector<uint32_t>&)>(two::index_list), two_index_list_35, { { "size", type<uint32_t>(),  }, { "output_indices", type<stl::vector<uint32_t>>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_math::two_math()
		: Module("two::math", { &two_infra::m(), &two_type::m() })
	{
		// setup reflection meta data
		two_math_meta(*this);
	}
}

#ifdef TWO_MATH_MODULE
extern "C"
Module& getModule()
{
	return two_math::m();
}
#endif
