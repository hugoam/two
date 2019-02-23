#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/math.meta.h>
#include <meta/math.conv.h>
#endif

#include <math/Api.h>

using namespace mud;

void mud_Axes__to_string(void* val, string& str) { str = g_enu[type<mud::Axes>().m_id]->name(uint32_t((*static_cast<mud::Axes*>(val)))); }
void mud_Axes__to_value(const string& str, void* val) { (*static_cast<mud::Axes*>(val)) = mud::Axes(g_enu[type<mud::Axes>().m_id]->value(str.c_str())); }
void mud_Axis__to_string(void* val, string& str) { str = g_enu[type<mud::Axis>().m_id]->name(uint32_t((*static_cast<mud::Axis*>(val)))); }
void mud_Axis__to_value(const string& str, void* val) { (*static_cast<mud::Axis*>(val)) = mud::Axis(g_enu[type<mud::Axis>().m_id]->value(str.c_str())); }
void mud_Clockwise__to_string(void* val, string& str) { str = g_enu[type<mud::Clockwise>().m_id]->name(uint32_t((*static_cast<mud::Clockwise*>(val)))); }
void mud_Clockwise__to_value(const string& str, void* val) { (*static_cast<mud::Clockwise*>(val)) = mud::Clockwise(g_enu[type<mud::Clockwise>().m_id]->value(str.c_str())); }
void mud_Side__to_string(void* val, string& str) { str = g_enu[type<mud::Side>().m_id]->name(uint32_t((*static_cast<mud::Side*>(val)))); }
void mud_Side__to_value(const string& str, void* val) { (*static_cast<mud::Side*>(val)) = mud::Side(g_enu[type<mud::Side>().m_id]->value(str.c_str())); }
void mud_SignedAxis__to_string(void* val, string& str) { str = g_enu[type<mud::SignedAxis>().m_id]->name(uint32_t((*static_cast<mud::SignedAxis*>(val)))); }
void mud_SignedAxis__to_value(const string& str, void* val) { (*static_cast<mud::SignedAxis*>(val)) = mud::SignedAxis(g_enu[type<mud::SignedAxis>().m_id]->value(str.c_str())); }
void mud_Spectrum__to_string(void* val, string& str) { str = g_enu[type<mud::Spectrum>().m_id]->name(uint32_t((*static_cast<mud::Spectrum*>(val)))); }
void mud_Spectrum__to_value(const string& str, void* val) { (*static_cast<mud::Spectrum*>(val)) = mud::Spectrum(g_enu[type<mud::Spectrum>().m_id]->value(str.c_str())); }
void mud_TrackMode__to_string(void* val, string& str) { str = g_enu[type<mud::TrackMode>().m_id]->name(uint32_t((*static_cast<mud::TrackMode*>(val)))); }
void mud_TrackMode__to_value(const string& str, void* val) { (*static_cast<mud::TrackMode*>(val)) = mud::TrackMode(g_enu[type<mud::TrackMode>().m_id]->value(str.c_str())); }
size_t stl_vector_float__size(void* vec) { return (*static_cast<stl::vector<float>*>(vec)).size(); }
void* stl_vector_float__at(void* vec, size_t i) { return &(*static_cast<stl::vector<float>*>(vec))[i]; }
void stl_vector_float__push(void* vec) { (*static_cast<stl::vector<float>*>(vec)).emplace_back(); }
void stl_vector_float__add(void* vec, void* value) { (*static_cast<stl::vector<float>*>(vec)).push_back(*static_cast<float*>(value)); }
void stl_vector_float__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<float>*>(vec)), *static_cast<float*>(value)); }
size_t stl_vector_int__size(void* vec) { return (*static_cast<stl::vector<int>*>(vec)).size(); }
void* stl_vector_int__at(void* vec, size_t i) { return &(*static_cast<stl::vector<int>*>(vec))[i]; }
void stl_vector_int__push(void* vec) { (*static_cast<stl::vector<int>*>(vec)).emplace_back(); }
void stl_vector_int__add(void* vec, void* value) { (*static_cast<stl::vector<int>*>(vec)).push_back(*static_cast<int*>(value)); }
void stl_vector_int__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<int>*>(vec)), *static_cast<int*>(value)); }
size_t stl_vector_mud_Colour__size(void* vec) { return (*static_cast<stl::vector<mud::Colour>*>(vec)).size(); }
void* stl_vector_mud_Colour__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Colour>*>(vec))[i]; }
void stl_vector_mud_Colour__push(void* vec) { (*static_cast<stl::vector<mud::Colour>*>(vec)).emplace_back(); }
void stl_vector_mud_Colour__add(void* vec, void* value) { (*static_cast<stl::vector<mud::Colour>*>(vec)).push_back(*static_cast<mud::Colour*>(value)); }
void stl_vector_mud_Colour__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Colour>*>(vec)), *static_cast<mud::Colour*>(value)); }
size_t stl_vector_mud_quat__size(void* vec) { return (*static_cast<stl::vector<mud::quat>*>(vec)).size(); }
void* stl_vector_mud_quat__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::quat>*>(vec))[i]; }
void stl_vector_mud_quat__push(void* vec) { (*static_cast<stl::vector<mud::quat>*>(vec)).emplace_back(); }
void stl_vector_mud_quat__add(void* vec, void* value) { (*static_cast<stl::vector<mud::quat>*>(vec)).push_back(*static_cast<mud::quat*>(value)); }
void stl_vector_mud_quat__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::quat>*>(vec)), *static_cast<mud::quat*>(value)); }
size_t stl_vector_mud_uvec3__size(void* vec) { return (*static_cast<stl::vector<mud::uvec3>*>(vec)).size(); }
void* stl_vector_mud_uvec3__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::uvec3>*>(vec))[i]; }
void stl_vector_mud_uvec3__push(void* vec) { (*static_cast<stl::vector<mud::uvec3>*>(vec)).emplace_back(); }
void stl_vector_mud_uvec3__add(void* vec, void* value) { (*static_cast<stl::vector<mud::uvec3>*>(vec)).push_back(*static_cast<mud::uvec3*>(value)); }
void stl_vector_mud_uvec3__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::uvec3>*>(vec)), *static_cast<mud::uvec3*>(value)); }
size_t stl_vector_mud_vec3__size(void* vec) { return (*static_cast<stl::vector<mud::vec3>*>(vec)).size(); }
void* stl_vector_mud_vec3__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::vec3>*>(vec))[i]; }
void stl_vector_mud_vec3__push(void* vec) { (*static_cast<stl::vector<mud::vec3>*>(vec)).emplace_back(); }
void stl_vector_mud_vec3__add(void* vec, void* value) { (*static_cast<stl::vector<mud::vec3>*>(vec)).push_back(*static_cast<mud::vec3*>(value)); }
void stl_vector_mud_vec3__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::vec3>*>(vec)), *static_cast<mud::vec3*>(value)); }
size_t stl_vector_uint32_t__size(void* vec) { return (*static_cast<stl::vector<uint32_t>*>(vec)).size(); }
void* stl_vector_uint32_t__at(void* vec, size_t i) { return &(*static_cast<stl::vector<uint32_t>*>(vec))[i]; }
void stl_vector_uint32_t__push(void* vec) { (*static_cast<stl::vector<uint32_t>*>(vec)).emplace_back(); }
void stl_vector_uint32_t__add(void* vec, void* value) { (*static_cast<stl::vector<uint32_t>*>(vec)).push_back(*static_cast<uint32_t*>(value)); }
void stl_vector_uint32_t__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<uint32_t>*>(vec)), *static_cast<uint32_t*>(value)); }
void mud_AutoStat_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::AutoStat<float>(  ); }
void mud_AutoStat_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::AutoStat<float>((*static_cast<mud::AutoStat<float>*>(other))); }
void mud_AutoStat_int__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::AutoStat<int>(  ); }
void mud_AutoStat_int__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::AutoStat<int>((*static_cast<mud::AutoStat<int>*>(other))); }
void mud_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Colour(  ); }
void mud_Colour__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Colour( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Colour__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Colour( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Colour((*static_cast<mud::Colour*>(other))); }
void mud_ColourHSL__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ColourHSL(  ); }
void mud_ColourHSL__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ColourHSL((*static_cast<mud::ColourHSL*>(other))); }
void mud_Image__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Image(  ); }
void mud_Image__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Image((*static_cast<mud::Image*>(other))); }
void mud_Image256__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Image256( *static_cast<uint16_t*>(args[0]), *static_cast<uint16_t*>(args[1]), *static_cast<mud::Palette*>(args[2]) ); }
void mud_Image256__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Image256((*static_cast<mud::Image256*>(other))); }
void mud_Palette__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Palette( *static_cast<mud::Spectrum*>(args[0]), *static_cast<size_t*>(args[1]) ); }
void mud_Palette__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Palette( *static_cast<stl::vector<mud::Colour>*>(args[0]) ); }
void mud_Palette__construct_2(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Palette(  ); }
void mud_Palette__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Palette((*static_cast<mud::Palette*>(other))); }
void mud_Range_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Range<float>(  ); }
void mud_Range_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Range<float>((*static_cast<mud::Range<float>*>(other))); }
void mud_Range_mud_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Range<mud::Colour>(  ); }
void mud_Range_mud_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Range<mud::Colour>((*static_cast<mud::Range<mud::Colour>*>(other))); }
void mud_Range_mud_quat__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Range<mud::quat>(  ); }
void mud_Range_mud_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Range<mud::quat>((*static_cast<mud::Range<mud::quat>*>(other))); }
void mud_Range_mud_vec3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Range<mud::vec3>(  ); }
void mud_Range_mud_vec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Range<mud::vec3>((*static_cast<mud::Range<mud::vec3>*>(other))); }
void mud_Range_uint32_t__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Range<uint32_t>(  ); }
void mud_Range_uint32_t__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Range<uint32_t>((*static_cast<mud::Range<uint32_t>*>(other))); }
void mud_Time__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Time( *static_cast<double*>(args[0]) ); }
void mud_Time__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Time((*static_cast<mud::Time*>(other))); }
void mud_TimeSpan__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::TimeSpan( *static_cast<mud::Time*>(args[0]), *static_cast<mud::Time*>(args[1]) ); }
void mud_TimeSpan__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::TimeSpan((*static_cast<mud::TimeSpan*>(other))); }
void mud_Transform__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Transform(  ); }
void mud_Transform__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Transform((*static_cast<mud::Transform*>(other))); }
void mud_ValueCurve_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueCurve<float>(  ); }
void mud_ValueCurve_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueCurve<float>( *static_cast<stl::vector<float>*>(args[0]) ); }
void mud_ValueCurve_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueCurve<float>((*static_cast<mud::ValueCurve<float>*>(other))); }
void mud_ValueCurve_mud_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueCurve<mud::Colour>(  ); }
void mud_ValueCurve_mud_Colour__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueCurve<mud::Colour>( *static_cast<stl::vector<mud::Colour>*>(args[0]) ); }
void mud_ValueCurve_mud_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueCurve<mud::Colour>((*static_cast<mud::ValueCurve<mud::Colour>*>(other))); }
void mud_ValueCurve_mud_quat__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueCurve<mud::quat>(  ); }
void mud_ValueCurve_mud_quat__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueCurve<mud::quat>( *static_cast<stl::vector<mud::quat>*>(args[0]) ); }
void mud_ValueCurve_mud_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueCurve<mud::quat>((*static_cast<mud::ValueCurve<mud::quat>*>(other))); }
void mud_ValueCurve_mud_vec3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueCurve<mud::vec3>(  ); }
void mud_ValueCurve_mud_vec3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueCurve<mud::vec3>( *static_cast<stl::vector<mud::vec3>*>(args[0]) ); }
void mud_ValueCurve_mud_vec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueCurve<mud::vec3>((*static_cast<mud::ValueCurve<mud::vec3>*>(other))); }
void mud_ValueCurve_uint32_t__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueCurve<uint32_t>(  ); }
void mud_ValueCurve_uint32_t__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueCurve<uint32_t>( *static_cast<stl::vector<uint32_t>*>(args[0]) ); }
void mud_ValueCurve_uint32_t__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueCurve<uint32_t>((*static_cast<mud::ValueCurve<uint32_t>*>(other))); }
void mud_ValueTrack_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueTrack<float>(  ); }
void mud_ValueTrack_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueTrack<float>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<float>*>(args[1]), *static_cast<mud::ValueCurve<float>*>(args[2]), *static_cast<mud::ValueCurve<float>*>(args[3]) ); }
void mud_ValueTrack_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueTrack<float>((*static_cast<mud::ValueTrack<float>*>(other))); }
void mud_ValueTrack_mud_Colour__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueTrack<mud::Colour>(  ); }
void mud_ValueTrack_mud_Colour__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueTrack<mud::Colour>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<mud::Colour>*>(args[1]), *static_cast<mud::ValueCurve<mud::Colour>*>(args[2]), *static_cast<mud::ValueCurve<mud::Colour>*>(args[3]) ); }
void mud_ValueTrack_mud_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueTrack<mud::Colour>((*static_cast<mud::ValueTrack<mud::Colour>*>(other))); }
void mud_ValueTrack_mud_quat__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueTrack<mud::quat>(  ); }
void mud_ValueTrack_mud_quat__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueTrack<mud::quat>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<mud::quat>*>(args[1]), *static_cast<mud::ValueCurve<mud::quat>*>(args[2]), *static_cast<mud::ValueCurve<mud::quat>*>(args[3]) ); }
void mud_ValueTrack_mud_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueTrack<mud::quat>((*static_cast<mud::ValueTrack<mud::quat>*>(other))); }
void mud_ValueTrack_mud_vec3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueTrack<mud::vec3>(  ); }
void mud_ValueTrack_mud_vec3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueTrack<mud::vec3>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<mud::vec3>*>(args[1]), *static_cast<mud::ValueCurve<mud::vec3>*>(args[2]), *static_cast<mud::ValueCurve<mud::vec3>*>(args[3]) ); }
void mud_ValueTrack_mud_vec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueTrack<mud::vec3>((*static_cast<mud::ValueTrack<mud::vec3>*>(other))); }
void mud_ValueTrack_uint32_t__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ValueTrack<uint32_t>(  ); }
void mud_ValueTrack_uint32_t__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ValueTrack<uint32_t>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<uint32_t>*>(args[1]), *static_cast<mud::ValueCurve<uint32_t>*>(args[2]), *static_cast<mud::ValueCurve<uint32_t>*>(args[3]) ); }
void mud_ValueTrack_uint32_t__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ValueTrack<uint32_t>((*static_cast<mud::ValueTrack<uint32_t>*>(other))); }
void mud_mat3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::mat3(  ); }
void mud_mat3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::mat3( *static_cast<mud::float3*>(args[0]), *static_cast<mud::float3*>(args[1]), *static_cast<mud::float3*>(args[2]) ); }
void mud_mat3__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::mat3( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5]), *static_cast<float*>(args[6]), *static_cast<float*>(args[7]), *static_cast<float*>(args[8]) ); }
void mud_mat3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::mat3((*static_cast<mud::mat3*>(other))); }
void mud_mat4__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::mat4(  ); }
void mud_mat4__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::mat4( *static_cast<mud::float4*>(args[0]), *static_cast<mud::float4*>(args[1]), *static_cast<mud::float4*>(args[2]), *static_cast<mud::float4*>(args[3]) ); }
void mud_mat4__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::mat4( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4]), *static_cast<float*>(args[5]), *static_cast<float*>(args[6]), *static_cast<float*>(args[7]), *static_cast<float*>(args[8]), *static_cast<float*>(args[9]), *static_cast<float*>(args[10]), *static_cast<float*>(args[11]), *static_cast<float*>(args[12]), *static_cast<float*>(args[13]), *static_cast<float*>(args[14]), *static_cast<float*>(args[15]) ); }
void mud_mat4__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::mat4((*static_cast<mud::mat4*>(other))); }
void mud_v2_bool__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<bool>(  ); }
void mud_v2_bool__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<bool>( *static_cast<bool*>(args[0]) ); }
void mud_v2_bool__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<bool>( *static_cast<bool*>(args[0]), *static_cast<bool*>(args[1]) ); }
void mud_v2_bool__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<bool>((*static_cast<mud::v2<bool>*>(other))); }
void mud_v2_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<float>(  ); }
void mud_v2_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<float>( *static_cast<float*>(args[0]) ); }
void mud_v2_float__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<float>( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_v2_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<float>((*static_cast<mud::v2<float>*>(other))); }
void mud_v2_int__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<int>(  ); }
void mud_v2_int__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<int>( *static_cast<int*>(args[0]) ); }
void mud_v2_int__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<int>( *static_cast<int*>(args[0]), *static_cast<int*>(args[1]) ); }
void mud_v2_int__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<int>((*static_cast<mud::v2<int>*>(other))); }
void mud_v2_uint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v2<uint>(  ); }
void mud_v2_uint__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<uint>( *static_cast<uint*>(args[0]) ); }
void mud_v2_uint__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v2<uint>( *static_cast<uint*>(args[0]), *static_cast<uint*>(args[1]) ); }
void mud_v2_uint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v2<uint>((*static_cast<mud::v2<uint>*>(other))); }
void mud_v3_bool__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v3<bool>(  ); }
void mud_v3_bool__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v3<bool>( *static_cast<bool*>(args[0]) ); }
void mud_v3_bool__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v3<bool>( *static_cast<bool*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<bool*>(args[2]) ); }
void mud_v3_bool__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v3<bool>((*static_cast<mud::v3<bool>*>(other))); }
void mud_v3_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v3<float>(  ); }
void mud_v3_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v3<float>( *static_cast<float*>(args[0]) ); }
void mud_v3_float__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v3<float>( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_v3_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v3<float>((*static_cast<mud::v3<float>*>(other))); }
void mud_v3_int__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v3<int>(  ); }
void mud_v3_int__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v3<int>( *static_cast<int*>(args[0]) ); }
void mud_v3_int__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v3<int>( *static_cast<int*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]) ); }
void mud_v3_int__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v3<int>((*static_cast<mud::v3<int>*>(other))); }
void mud_v3_uint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v3<uint>(  ); }
void mud_v3_uint__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v3<uint>( *static_cast<uint*>(args[0]) ); }
void mud_v3_uint__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v3<uint>( *static_cast<uint*>(args[0]), *static_cast<uint*>(args[1]), *static_cast<uint*>(args[2]) ); }
void mud_v3_uint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v3<uint>((*static_cast<mud::v3<uint>*>(other))); }
void mud_v4_bool__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v4<bool>(  ); }
void mud_v4_bool__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v4<bool>( *static_cast<bool*>(args[0]) ); }
void mud_v4_bool__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v4<bool>( *static_cast<bool*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3]) ); }
void mud_v4_bool__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v4<bool>((*static_cast<mud::v4<bool>*>(other))); }
void mud_v4_float__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v4<float>(  ); }
void mud_v4_float__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v4<float>( *static_cast<float*>(args[0]) ); }
void mud_v4_float__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v4<float>( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_v4_float__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v4<float>((*static_cast<mud::v4<float>*>(other))); }
void mud_v4_int__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v4<int>(  ); }
void mud_v4_int__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v4<int>( *static_cast<int*>(args[0]) ); }
void mud_v4_int__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v4<int>( *static_cast<int*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]), *static_cast<int*>(args[3]) ); }
void mud_v4_int__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v4<int>((*static_cast<mud::v4<int>*>(other))); }
void mud_v4_uint__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::v4<uint>(  ); }
void mud_v4_uint__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v4<uint>( *static_cast<uint*>(args[0]) ); }
void mud_v4_uint__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::v4<uint>( *static_cast<uint*>(args[0]), *static_cast<uint*>(args[1]), *static_cast<uint*>(args[2]), *static_cast<uint*>(args[3]) ); }
void mud_v4_uint__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::v4<uint>((*static_cast<mud::v4<uint>*>(other))); }
void mud_quat__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::quat(  ); }
void mud_quat__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::quat( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_quat__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::quat( *static_cast<mud::float3*>(args[0]) ); }
void mud_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::quat((*static_cast<mud::quat*>(other))); }
void mud_rgba_0(span<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::rgba(*static_cast<uint32_t*>(args[0])); }
void mud_abgr_1(span<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::abgr(*static_cast<uint32_t*>(args[0])); }
void mud_hsl_2(span<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::hsl(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_to_rgba_3(span<void*> args, void*& result) { (*static_cast<uint*>(result)) = mud::to_rgba(*static_cast<mud::Colour*>(args[0])); }
void mud_to_abgr_4(span<void*> args, void*& result) { (*static_cast<uint*>(result)) = mud::to_abgr(*static_cast<mud::Colour*>(args[0])); }
void mud_to_linear_5(span<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::to_linear(*static_cast<mud::Colour*>(args[0])); }
void mud_to_gamma_6(span<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::to_gamma(*static_cast<mud::Colour*>(args[0])); }
void mud_to_srgb_7(span<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::to_srgb(*static_cast<mud::Colour*>(args[0])); }
void mud_to_hsl_8(span<void*> args, void*& result) { (*static_cast<mud::ColourHSL*>(result)) = mud::to_hsl(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_to_hsl_9(span<void*> args, void*& result) { (*static_cast<mud::ColourHSL*>(result)) = mud::to_hsl(*static_cast<mud::Colour*>(args[0])); }
void mud_to_hsla_10(span<void*> args, void*& result) { (*static_cast<mud::ColourHSL*>(result)) = mud::to_hsla(*static_cast<mud::Colour*>(args[0])); }
void mud_to_rgba_11(span<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::to_rgba(*static_cast<mud::ColourHSL*>(args[0])); }
void sinf_12(span<void*> args, void*& result) { (*static_cast<float*>(result)) = sinf(*static_cast<float*>(args[0])); }
void cosf_13(span<void*> args, void*& result) { (*static_cast<float*>(result)) = cosf(*static_cast<float*>(args[0])); }
void sin_14(span<void*> args, void*& result) { (*static_cast<double*>(result)) = sin(*static_cast<double*>(args[0])); }
void cos_15(span<void*> args, void*& result) { (*static_cast<double*>(result)) = cos(*static_cast<double*>(args[0])); }
void mud_add_16(span<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::add(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void mud_subtract_17(span<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::subtract(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void mud_multiply_18(span<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::multiply(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void mud_divide_19(span<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::divide(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void mud_nsinf_20(span<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::nsinf(*static_cast<float*>(args[0])); }
void mud_ncosf_21(span<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::ncosf(*static_cast<float*>(args[0])); }
void mud_nsin_22(span<void*> args, void*& result) { (*static_cast<double*>(result)) = mud::nsin(*static_cast<double*>(args[0])); }
void mud_ncos_23(span<void*> args, void*& result) { (*static_cast<double*>(result)) = mud::ncos(*static_cast<double*>(args[0])); }
void mud_add_24(span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = mud::add(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_subtract_25(span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = mud::subtract(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_multiply_26(span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = mud::multiply(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_divide_27(span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = mud::divide(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_look_dir_28(span<void*> args, void*& result) { (*static_cast<mud::quat*>(result)) = mud::look_dir(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_look_at_29(span<void*> args, void*& result) { (*static_cast<mud::quat*>(result)) = mud::look_at(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_grid_30(span<void*> args, void*& result) { UNUSED(result);  mud::grid(*static_cast<mud::uvec3*>(args[0]), *static_cast<stl::vector<mud::uvec3>*>(args[1])); }
void mud_grid_center_31(span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = mud::grid_center(*static_cast<mud::uvec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_index_list_32(span<void*> args, void*& result) { UNUSED(result);  mud::index_list(*static_cast<uint32_t*>(args[0]), *static_cast<stl::vector<uint32_t>*>(args[1])); }

namespace mud
{
	void mud_math_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::Axes>();
		static Meta meta = { t, &namspc({ "mud" }), "Axes", sizeof(mud::Axes), TypeClass::Enum };
		static cstring ids[] = { "None", "X", "Y", "Z" };
		static uint32_t values[] = { 0, 1, 2, 4 };
		static mud::Axes vars[] = { mud::Axes::None, mud::Axes::X, mud::Axes::Y, mud::Axes::Z};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Axes__to_string,
		                           mud_Axes__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Axis>();
		static Meta meta = { t, &namspc({ "mud" }), "Axis", sizeof(mud::Axis), TypeClass::Enum };
		static cstring ids[] = { "X", "Y", "Z", "None", "Count" };
		static uint32_t values[] = { 0, 1, 2, 2, 3 };
		static mud::Axis vars[] = { mud::Axis::X, mud::Axis::Y, mud::Axis::Z, mud::Axis::None, mud::Axis::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Axis__to_string,
		                           mud_Axis__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Clockwise>();
		static Meta meta = { t, &namspc({ "mud" }), "Clockwise", sizeof(mud::Clockwise), TypeClass::Enum };
		static cstring ids[] = { "CLOCKWISE", "ANTI_CLOCKWISE" };
		static uint32_t values[] = { 0, 1 };
		static mud::Clockwise vars[] = { mud::CLOCKWISE, mud::ANTI_CLOCKWISE};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_Clockwise__to_string,
		                           mud_Clockwise__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Side>();
		static Meta meta = { t, &namspc({ "mud" }), "Side", sizeof(mud::Side), TypeClass::Enum };
		static cstring ids[] = { "Right", "Left", "Up", "Down", "Back", "Front", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static mud::Side vars[] = { mud::Side::Right, mud::Side::Left, mud::Side::Up, mud::Side::Down, mud::Side::Back, mud::Side::Front, mud::Side::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Side__to_string,
		                           mud_Side__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::SignedAxis>();
		static Meta meta = { t, &namspc({ "mud" }), "SignedAxis", sizeof(mud::SignedAxis), TypeClass::Enum };
		static cstring ids[] = { "PlusX", "MinusX", "PlusY", "MinusY", "PlusZ", "MinusZ", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static mud::SignedAxis vars[] = { mud::SignedAxis::PlusX, mud::SignedAxis::MinusX, mud::SignedAxis::PlusY, mud::SignedAxis::MinusY, mud::SignedAxis::PlusZ, mud::SignedAxis::MinusZ, mud::SignedAxis::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_SignedAxis__to_string,
		                           mud_SignedAxis__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::Spectrum>();
		static Meta meta = { t, &namspc({ "mud" }), "Spectrum", sizeof(mud::Spectrum), TypeClass::Enum };
		static cstring ids[] = { "Value", "Hue" };
		static uint32_t values[] = { 0, 1 };
		static mud::Spectrum vars[] = { mud::Spectrum::Value, mud::Spectrum::Hue};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Spectrum__to_string,
		                           mud_Spectrum__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::TrackMode>();
		static Meta meta = { t, &namspc({ "mud" }), "TrackMode", sizeof(mud::TrackMode), TypeClass::Enum };
		static cstring ids[] = { "Constant", "ConstantRandom", "Curve", "CurveRandom" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::TrackMode vars[] = { mud::TrackMode::Constant, mud::TrackMode::ConstantRandom, mud::TrackMode::Curve, mud::TrackMode::CurveRandom};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_TrackMode__to_string,
		                           mud_TrackMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
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
		Type& t = type<stl::vector<mud::Colour>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Colour>", sizeof(stl::vector<mud::Colour>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Colour>(),
		                             stl_vector_mud_Colour__size,
		                             stl_vector_mud_Colour__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Colour__push,
		                             stl_vector_mud_Colour__add,
		                             stl_vector_mud_Colour__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::quat>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::quat>", sizeof(stl::vector<mud::quat>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::quat>(),
		                             stl_vector_mud_quat__size,
		                             stl_vector_mud_quat__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_quat__push,
		                             stl_vector_mud_quat__add,
		                             stl_vector_mud_quat__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::uvec3>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::uvec3>", sizeof(stl::vector<mud::uvec3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::uvec3>(),
		                             stl_vector_mud_uvec3__size,
		                             stl_vector_mud_uvec3__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_uvec3__push,
		                             stl_vector_mud_uvec3__add,
		                             stl_vector_mud_uvec3__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::vec3>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::vec3>", sizeof(stl::vector<mud::vec3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::vec3>(),
		                             stl_vector_mud_vec3__size,
		                             stl_vector_mud_vec3__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_vec3__push,
		                             stl_vector_mud_vec3__add,
		                             stl_vector_mud_vec3__remove };
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
	
	// mud::AutoStat<float>
	{
		Type& t = type<mud::AutoStat<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "AutoStat<float>", sizeof(mud::AutoStat<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_AutoStat_float__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_AutoStat_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::AutoStat<float>, m_value), type<float>(), "value", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::AutoStat<int>
	{
		Type& t = type<mud::AutoStat<int>>();
		static Meta meta = { t, &namspc({ "mud" }), "AutoStat<int>", sizeof(mud::AutoStat<int>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_AutoStat_int__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_AutoStat_int__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::AutoStat<int>, m_value), type<int>(), "value", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Colour
	{
		Type& t = type<mud::Colour>();
		static Meta meta = { t, &namspc({ "mud" }), "Colour", sizeof(mud::Colour), TypeClass::Struct };
		meta.m_empty_var = var(Colour());
		// bases
		// defaults
		static float construct_1_a_default = 1.f;
		static float construct_2_a_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Colour__construct_0, {} },
			{ t, mud_Colour__construct_1, { { "v", type<float>(),  }, { "a", type<float>(), Param::Default, &construct_1_a_default } } },
			{ t, mud_Colour__construct_2, { { "r", type<float>(),  }, { "g", type<float>(),  }, { "b", type<float>(),  }, { "a", type<float>(), Param::Default, &construct_2_a_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Colour, r), type<float>(), "r", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Colour, g), type<float>(), "g", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Colour, b), type<float>(), "b", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Colour, m_a), type<float>(), "a", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Static statics[] = {
			{ t, "Black", Ref(&mud::Colour::Black) },
			{ t, "AlphaBlack", Ref(&mud::Colour::AlphaBlack) },
			{ t, "Red", Ref(&mud::Colour::Red) },
			{ t, "Green", Ref(&mud::Colour::Green) },
			{ t, "NeonGreen", Ref(&mud::Colour::NeonGreen) },
			{ t, "Blue", Ref(&mud::Colour::Blue) },
			{ t, "Pink", Ref(&mud::Colour::Pink) },
			{ t, "Cyan", Ref(&mud::Colour::Cyan) },
			{ t, "Yellow", Ref(&mud::Colour::Yellow) },
			{ t, "White", Ref(&mud::Colour::White) },
			{ t, "AlphaWhite", Ref(&mud::Colour::AlphaWhite) },
			{ t, "LightGrey", Ref(&mud::Colour::LightGrey) },
			{ t, "MidGrey", Ref(&mud::Colour::MidGrey) },
			{ t, "DarkGrey", Ref(&mud::Colour::DarkGrey) },
			{ t, "AlphaGrey", Ref(&mud::Colour::AlphaGrey) },
			{ t, "Transparent", Ref(&mud::Colour::Transparent) },
			{ t, "Invisible", Ref(&mud::Colour::Invisible) },
			{ t, "None", Ref(&mud::Colour::None) }
		};
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, statics, };
	}
	// mud::ColourHSL
	{
		Type& t = type<mud::ColourHSL>();
		static Meta meta = { t, &namspc({ "mud" }), "ColourHSL", sizeof(mud::ColourHSL), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ColourHSL__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ColourHSL__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ColourHSL, h), type<float>(), "h", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ColourHSL, s), type<float>(), "s", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ColourHSL, l), type<float>(), "l", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ColourHSL, a), type<float>(), "a", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Image
	{
		Type& t = type<mud::Image>();
		static Meta meta = { t, &namspc({ "mud" }), "Image", sizeof(mud::Image), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Image__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Image__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Image, d_name), type<stl::string>(), "d_name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Image, d_path), type<stl::string>(), "d_path", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Image256
	{
		Type& t = type<mud::Image256>();
		static Meta meta = { t, &namspc({ "mud" }), "Image256", sizeof(mud::Image256), TypeClass::Struct };
		// bases
		// defaults
		static uint16_t construct_0_width_default = 0;
		static uint16_t construct_0_height_default = 0;
		static mud::Palette construct_0_palette_default = mud::Palette();
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Image256__construct_0, { { "width", type<uint16_t>(), Param::Default, &construct_0_width_default }, { "height", type<uint16_t>(), Param::Default, &construct_0_height_default }, { "palette", type<mud::Palette>(), Param::Default, &construct_0_palette_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Image256__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Image256, m_pixels), type<stl::vector<uint32_t>>(), "pixels", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Image256, m_width), type<uint16_t>(), "width", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Image256, m_height), type<uint16_t>(), "height", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Image256, m_palette), type<mud::Palette>(), "palette", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ImageAtlas
	{
		Type& t = type<mud::ImageAtlas>();
		static Meta meta = { t, &namspc({ "mud" }), "ImageAtlas", sizeof(mud::ImageAtlas), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Palette
	{
		Type& t = type<mud::Palette>();
		static Meta meta = { t, &namspc({ "mud" }), "Palette", sizeof(mud::Palette), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Palette__construct_0, { { "spectrum", type<mud::Spectrum>(),  }, { "steps", type<size_t>(),  } } },
			{ t, mud_Palette__construct_1, { { "colours", type<stl::vector<mud::Colour>>(),  } } },
			{ t, mud_Palette__construct_2, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Palette__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Range<float>
	{
		Type& t = type<mud::Range<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<float>", sizeof(mud::Range<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Range_float__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Range<float>, m_min), type<float>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Range<float>, m_max), type<float>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Range<mud::Colour>
	{
		Type& t = type<mud::Range<mud::Colour>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<mud::Colour>", sizeof(mud::Range<mud::Colour>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Range_mud_Colour__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_mud_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Range<mud::Colour>, m_min), type<mud::Colour>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Range<mud::Colour>, m_max), type<mud::Colour>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Range<mud::quat>
	{
		Type& t = type<mud::Range<mud::quat>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<mud::quat>", sizeof(mud::Range<mud::quat>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Range_mud_quat__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_mud_quat__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Range<mud::quat>, m_min), type<mud::quat>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Range<mud::quat>, m_max), type<mud::quat>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Range<mud::vec3>
	{
		Type& t = type<mud::Range<mud::vec3>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<mud::vec3>", sizeof(mud::Range<mud::vec3>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Range_mud_vec3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_mud_vec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Range<mud::vec3>, m_min), type<mud::vec3>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Range<mud::vec3>, m_max), type<mud::vec3>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Range<uint32_t>
	{
		Type& t = type<mud::Range<uint32_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<uint32_t>", sizeof(mud::Range<uint32_t>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Range_uint32_t__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_uint32_t__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Range<uint32_t>, m_min), type<uint32_t>(), "min", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Range<uint32_t>, m_max), type<uint32_t>(), "max", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Time
	{
		Type& t = type<mud::Time>();
		static Meta meta = { t, &namspc({ "mud" }), "Time", sizeof(mud::Time), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Time__construct_0, { { "value", type<double>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Time__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Time, m_value), type<double>(), "value", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::TimeSpan
	{
		Type& t = type<mud::TimeSpan>();
		static Meta meta = { t, &namspc({ "mud" }), "TimeSpan", sizeof(mud::TimeSpan), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TimeSpan__construct_0, { { "s", type<mud::Time>(),  }, { "e", type<mud::Time>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_TimeSpan__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::TimeSpan, start), type<mud::Time>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TimeSpan, end), type<mud::Time>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Transform
	{
		Type& t = type<mud::Transform>();
		static Meta meta = { t, &namspc({ "mud" }), "Transform", sizeof(mud::Transform), TypeClass::Struct };
		// bases
		// defaults
		static mud::quat rotation_default = ZeroQuat;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Transform__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Transform__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Transform, m_position), type<mud::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Transform, m_rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(mud::Transform, m_scale), type<mud::vec3>(), "scale", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueCurve<float>
	{
		Type& t = type<mud::ValueCurve<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<float>", sizeof(mud::ValueCurve<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueCurve_float__construct_0, {} },
			{ t, mud_ValueCurve_float__construct_1, { { "keys", type<stl::vector<float>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<float>, m_keys), type<stl::vector<float>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueCurve<mud::Colour>
	{
		Type& t = type<mud::ValueCurve<mud::Colour>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<mud::Colour>", sizeof(mud::ValueCurve<mud::Colour>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueCurve_mud_Colour__construct_0, {} },
			{ t, mud_ValueCurve_mud_Colour__construct_1, { { "keys", type<stl::vector<mud::Colour>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_mud_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<mud::Colour>, m_keys), type<stl::vector<mud::Colour>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueCurve<mud::quat>
	{
		Type& t = type<mud::ValueCurve<mud::quat>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<mud::quat>", sizeof(mud::ValueCurve<mud::quat>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueCurve_mud_quat__construct_0, {} },
			{ t, mud_ValueCurve_mud_quat__construct_1, { { "keys", type<stl::vector<mud::quat>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_mud_quat__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<mud::quat>, m_keys), type<stl::vector<mud::quat>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueCurve<mud::vec3>
	{
		Type& t = type<mud::ValueCurve<mud::vec3>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<mud::vec3>", sizeof(mud::ValueCurve<mud::vec3>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueCurve_mud_vec3__construct_0, {} },
			{ t, mud_ValueCurve_mud_vec3__construct_1, { { "keys", type<stl::vector<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_mud_vec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<mud::vec3>, m_keys), type<stl::vector<mud::vec3>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueCurve<uint32_t>
	{
		Type& t = type<mud::ValueCurve<uint32_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<uint32_t>", sizeof(mud::ValueCurve<uint32_t>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueCurve_uint32_t__construct_0, {} },
			{ t, mud_ValueCurve_uint32_t__construct_1, { { "keys", type<stl::vector<uint32_t>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_uint32_t__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<uint32_t>, m_keys), type<stl::vector<uint32_t>>(), "keys", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueTrack<float>
	{
		Type& t = type<mud::ValueTrack<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<float>", sizeof(mud::ValueTrack<float>), TypeClass::Struct };
		// bases
		// defaults
		static float value_default = One<float>::value();
		static float min_default = One<float>::value();
		static float max_default = One<float>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueTrack_float__construct_0, {} },
			{ t, mud_ValueTrack_float__construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<float>>(),  }, { "min_curve", type<mud::ValueCurve<float>>(),  }, { "max_curve", type<mud::ValueCurve<float>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueTrack<float>, m_mode), type<mud::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<float>, m_value), type<float>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<float>, m_min), type<float>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<float>, m_max), type<float>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<float>, m_curve), type<mud::ValueCurve<float>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<float>, m_min_curve), type<mud::ValueCurve<float>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<float>, m_max_curve), type<mud::ValueCurve<float>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueTrack<mud::Colour>
	{
		Type& t = type<mud::ValueTrack<mud::Colour>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<mud::Colour>", sizeof(mud::ValueTrack<mud::Colour>), TypeClass::Struct };
		// bases
		// defaults
		static mud::Colour value_default = One<mud::Colour>::value();
		static mud::Colour min_default = One<mud::Colour>::value();
		static mud::Colour max_default = One<mud::Colour>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueTrack_mud_Colour__construct_0, {} },
			{ t, mud_ValueTrack_mud_Colour__construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<mud::Colour>>(),  }, { "min_curve", type<mud::ValueCurve<mud::Colour>>(),  }, { "max_curve", type<mud::ValueCurve<mud::Colour>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_mud_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueTrack<mud::Colour>, m_mode), type<mud::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::Colour>, m_value), type<mud::Colour>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::Colour>, m_min), type<mud::Colour>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::Colour>, m_max), type<mud::Colour>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::Colour>, m_curve), type<mud::ValueCurve<mud::Colour>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::Colour>, m_min_curve), type<mud::ValueCurve<mud::Colour>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::Colour>, m_max_curve), type<mud::ValueCurve<mud::Colour>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueTrack<mud::quat>
	{
		Type& t = type<mud::ValueTrack<mud::quat>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<mud::quat>", sizeof(mud::ValueTrack<mud::quat>), TypeClass::Struct };
		// bases
		// defaults
		static mud::quat value_default = One<mud::quat>::value();
		static mud::quat min_default = One<mud::quat>::value();
		static mud::quat max_default = One<mud::quat>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueTrack_mud_quat__construct_0, {} },
			{ t, mud_ValueTrack_mud_quat__construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<mud::quat>>(),  }, { "min_curve", type<mud::ValueCurve<mud::quat>>(),  }, { "max_curve", type<mud::ValueCurve<mud::quat>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_mud_quat__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueTrack<mud::quat>, m_mode), type<mud::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::quat>, m_value), type<mud::quat>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::quat>, m_min), type<mud::quat>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::quat>, m_max), type<mud::quat>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::quat>, m_curve), type<mud::ValueCurve<mud::quat>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::quat>, m_min_curve), type<mud::ValueCurve<mud::quat>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::quat>, m_max_curve), type<mud::ValueCurve<mud::quat>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueTrack<mud::vec3>
	{
		Type& t = type<mud::ValueTrack<mud::vec3>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<mud::vec3>", sizeof(mud::ValueTrack<mud::vec3>), TypeClass::Struct };
		// bases
		// defaults
		static mud::vec3 value_default = One<mud::vec3>::value();
		static mud::vec3 min_default = One<mud::vec3>::value();
		static mud::vec3 max_default = One<mud::vec3>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueTrack_mud_vec3__construct_0, {} },
			{ t, mud_ValueTrack_mud_vec3__construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<mud::vec3>>(),  }, { "min_curve", type<mud::ValueCurve<mud::vec3>>(),  }, { "max_curve", type<mud::ValueCurve<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_mud_vec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueTrack<mud::vec3>, m_mode), type<mud::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::vec3>, m_value), type<mud::vec3>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::vec3>, m_min), type<mud::vec3>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::vec3>, m_max), type<mud::vec3>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::vec3>, m_curve), type<mud::ValueCurve<mud::vec3>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::vec3>, m_min_curve), type<mud::ValueCurve<mud::vec3>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<mud::vec3>, m_max_curve), type<mud::ValueCurve<mud::vec3>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ValueTrack<uint32_t>
	{
		Type& t = type<mud::ValueTrack<uint32_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<uint32_t>", sizeof(mud::ValueTrack<uint32_t>), TypeClass::Struct };
		// bases
		// defaults
		static uint32_t value_default = One<uint32_t>::value();
		static uint32_t min_default = One<uint32_t>::value();
		static uint32_t max_default = One<uint32_t>::value();
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueTrack_uint32_t__construct_0, {} },
			{ t, mud_ValueTrack_uint32_t__construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<uint32_t>>(),  }, { "min_curve", type<mud::ValueCurve<uint32_t>>(),  }, { "max_curve", type<mud::ValueCurve<uint32_t>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_uint32_t__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueTrack<uint32_t>, m_mode), type<mud::TrackMode>(), "mode", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<uint32_t>, m_value), type<uint32_t>(), "value", &value_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<uint32_t>, m_min), type<uint32_t>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<uint32_t>, m_max), type<uint32_t>(), "max", &max_default, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<uint32_t>, m_curve), type<mud::ValueCurve<uint32_t>>(), "curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<uint32_t>, m_min_curve), type<mud::ValueCurve<uint32_t>>(), "min_curve", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ValueTrack<uint32_t>, m_max_curve), type<mud::ValueCurve<uint32_t>>(), "max_curve", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::mat3
	{
		Type& t = type<mud::mat3>();
		static Meta meta = { t, &namspc({ "mud" }), "mat3", sizeof(mud::mat3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_mat3__construct_0, {} },
			{ t, mud_mat3__construct_1, { { "x", type<mud::float3>(),  }, { "y", type<mud::float3>(),  }, { "z", type<mud::float3>(),  } } },
			{ t, mud_mat3__construct_2, { { "f0", type<float>(),  }, { "f1", type<float>(),  }, { "f2", type<float>(),  }, { "f3", type<float>(),  }, { "f4", type<float>(),  }, { "f5", type<float>(),  }, { "f6", type<float>(),  }, { "f7", type<float>(),  }, { "f8", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_mat3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::mat3, f), type<float>(), "f", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::mat4
	{
		Type& t = type<mud::mat4>();
		static Meta meta = { t, &namspc({ "mud" }), "mat4", sizeof(mud::mat4), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_mat4__construct_0, {} },
			{ t, mud_mat4__construct_1, { { "x", type<mud::float4>(),  }, { "y", type<mud::float4>(),  }, { "z", type<mud::float4>(),  }, { "w", type<mud::float4>(),  } } },
			{ t, mud_mat4__construct_2, { { "f0", type<float>(),  }, { "f1", type<float>(),  }, { "f2", type<float>(),  }, { "f3", type<float>(),  }, { "f4", type<float>(),  }, { "f5", type<float>(),  }, { "f6", type<float>(),  }, { "f7", type<float>(),  }, { "f8", type<float>(),  }, { "f9", type<float>(),  }, { "f10", type<float>(),  }, { "f11", type<float>(),  }, { "f12", type<float>(),  }, { "f13", type<float>(),  }, { "f14", type<float>(),  }, { "f15", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_mat4__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::mat4, f), type<float>(), "f", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v2<bool>
	{
		Type& t = type<mud::v2<bool>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<bool>", sizeof(mud::v2<bool>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_bool__construct_0, {} },
			{ t, mud_v2_bool__construct_1, { { "v", type<bool>(),  } } },
			{ t, mud_v2_bool__construct_2, { { "x", type<bool>(),  }, { "y", type<bool>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_bool__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<bool>, x), type<bool>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<bool>, y), type<bool>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v2<float>
	{
		Type& t = type<mud::v2<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<float>", sizeof(mud::v2<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_float__construct_0, {} },
			{ t, mud_v2_float__construct_1, { { "v", type<float>(),  } } },
			{ t, mud_v2_float__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<float>, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<float>, y), type<float>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v2<int>
	{
		Type& t = type<mud::v2<int>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<int>", sizeof(mud::v2<int>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_int__construct_0, {} },
			{ t, mud_v2_int__construct_1, { { "v", type<int>(),  } } },
			{ t, mud_v2_int__construct_2, { { "x", type<int>(),  }, { "y", type<int>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_int__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<int>, x), type<int>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<int>, y), type<int>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v2<uint>
	{
		Type& t = type<mud::v2<uint>>();
		static Meta meta = { t, &namspc({ "mud" }), "v2<uint>", sizeof(mud::v2<uint>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v2_uint__construct_0, {} },
			{ t, mud_v2_uint__construct_1, { { "v", type<uint>(),  } } },
			{ t, mud_v2_uint__construct_2, { { "x", type<uint>(),  }, { "y", type<uint>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v2_uint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v2<uint>, x), type<uint>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v2<uint>, y), type<uint>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v3<bool>
	{
		Type& t = type<mud::v3<bool>>();
		static Meta meta = { t, &namspc({ "mud" }), "v3<bool>", sizeof(mud::v3<bool>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v3_bool__construct_0, {} },
			{ t, mud_v3_bool__construct_1, { { "v", type<bool>(),  } } },
			{ t, mud_v3_bool__construct_2, { { "x", type<bool>(),  }, { "y", type<bool>(),  }, { "z", type<bool>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v3_bool__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v3<bool>, x), type<bool>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v3<bool>, y), type<bool>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v3<bool>, z), type<bool>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v3<float>
	{
		Type& t = type<mud::v3<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "v3<float>", sizeof(mud::v3<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v3_float__construct_0, {} },
			{ t, mud_v3_float__construct_1, { { "v", type<float>(),  } } },
			{ t, mud_v3_float__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v3_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v3<float>, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v3<float>, y), type<float>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v3<float>, z), type<float>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v3<int>
	{
		Type& t = type<mud::v3<int>>();
		static Meta meta = { t, &namspc({ "mud" }), "v3<int>", sizeof(mud::v3<int>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v3_int__construct_0, {} },
			{ t, mud_v3_int__construct_1, { { "v", type<int>(),  } } },
			{ t, mud_v3_int__construct_2, { { "x", type<int>(),  }, { "y", type<int>(),  }, { "z", type<int>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v3_int__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v3<int>, x), type<int>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v3<int>, y), type<int>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v3<int>, z), type<int>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v3<uint>
	{
		Type& t = type<mud::v3<uint>>();
		static Meta meta = { t, &namspc({ "mud" }), "v3<uint>", sizeof(mud::v3<uint>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v3_uint__construct_0, {} },
			{ t, mud_v3_uint__construct_1, { { "v", type<uint>(),  } } },
			{ t, mud_v3_uint__construct_2, { { "x", type<uint>(),  }, { "y", type<uint>(),  }, { "z", type<uint>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v3_uint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v3<uint>, x), type<uint>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v3<uint>, y), type<uint>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v3<uint>, z), type<uint>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v4<bool>
	{
		Type& t = type<mud::v4<bool>>();
		static Meta meta = { t, &namspc({ "mud" }), "v4<bool>", sizeof(mud::v4<bool>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v4_bool__construct_0, {} },
			{ t, mud_v4_bool__construct_1, { { "v", type<bool>(),  } } },
			{ t, mud_v4_bool__construct_2, { { "x", type<bool>(),  }, { "y", type<bool>(),  }, { "z", type<bool>(),  }, { "w", type<bool>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v4_bool__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v4<bool>, x), type<bool>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<bool>, y), type<bool>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<bool>, z), type<bool>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<bool>, w), type<bool>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v4<float>
	{
		Type& t = type<mud::v4<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "v4<float>", sizeof(mud::v4<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v4_float__construct_0, {} },
			{ t, mud_v4_float__construct_1, { { "v", type<float>(),  } } },
			{ t, mud_v4_float__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  }, { "w", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v4_float__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v4<float>, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<float>, y), type<float>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<float>, z), type<float>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<float>, w), type<float>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v4<int>
	{
		Type& t = type<mud::v4<int>>();
		static Meta meta = { t, &namspc({ "mud" }), "v4<int>", sizeof(mud::v4<int>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v4_int__construct_0, {} },
			{ t, mud_v4_int__construct_1, { { "v", type<int>(),  } } },
			{ t, mud_v4_int__construct_2, { { "x", type<int>(),  }, { "y", type<int>(),  }, { "z", type<int>(),  }, { "w", type<int>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v4_int__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v4<int>, x), type<int>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<int>, y), type<int>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<int>, z), type<int>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<int>, w), type<int>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::v4<uint>
	{
		Type& t = type<mud::v4<uint>>();
		static Meta meta = { t, &namspc({ "mud" }), "v4<uint>", sizeof(mud::v4<uint>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_v4_uint__construct_0, {} },
			{ t, mud_v4_uint__construct_1, { { "v", type<uint>(),  } } },
			{ t, mud_v4_uint__construct_2, { { "x", type<uint>(),  }, { "y", type<uint>(),  }, { "z", type<uint>(),  }, { "w", type<uint>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_v4_uint__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::v4<uint>, x), type<uint>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<uint>, y), type<uint>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<uint>, z), type<uint>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::v4<uint>, w), type<uint>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Sprite
	{
		Type& t = type<mud::Sprite>();
		static Meta meta = { t, &namspc({ "mud" }), "Sprite", sizeof(mud::Sprite), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Image>() };
		static size_t bases_offsets[] = { base_offset<mud::Sprite, mud::Image>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::SpriteAtlas
	{
		Type& t = type<mud::SpriteAtlas>();
		static Meta meta = { t, &namspc({ "mud" }), "SpriteAtlas", sizeof(mud::SpriteAtlas), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ImageAtlas>() };
		static size_t bases_offsets[] = { base_offset<mud::SpriteAtlas, mud::ImageAtlas>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::TextureAtlas
	{
		Type& t = type<mud::TextureAtlas>();
		static Meta meta = { t, &namspc({ "mud" }), "TextureAtlas", sizeof(mud::TextureAtlas), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ImageAtlas>() };
		static size_t bases_offsets[] = { base_offset<mud::TextureAtlas, mud::ImageAtlas>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::quat
	{
		Type& t = type<mud::quat>();
		static Meta meta = { t, &namspc({ "mud" }), "quat", sizeof(mud::quat), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::float4>() };
		static size_t bases_offsets[] = { base_offset<mud::quat, mud::float4>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_quat__construct_0, {} },
			{ t, mud_quat__construct_1, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  }, { "w", type<float>(),  } } },
			{ t, mud_quat__construct_2, { { "euler_angles", type<mud::float3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_quat__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	
	{
		Type& t = type<mud::v2<float>>();
		static Alias alias = { &t, &namspc({ "mud" }), "float2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v3<float>>();
		static Alias alias = { &t, &namspc({ "mud" }), "float3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v4<float>>();
		static Alias alias = { &t, &namspc({ "mud" }), "float4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v2<int>>();
		static Alias alias = { &t, &namspc({ "mud" }), "int2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v3<int>>();
		static Alias alias = { &t, &namspc({ "mud" }), "int3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v4<int>>();
		static Alias alias = { &t, &namspc({ "mud" }), "int4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v2<uint>>();
		static Alias alias = { &t, &namspc({ "mud" }), "uint2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v3<uint>>();
		static Alias alias = { &t, &namspc({ "mud" }), "uint3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v4<uint>>();
		static Alias alias = { &t, &namspc({ "mud" }), "uint4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v2<bool>>();
		static Alias alias = { &t, &namspc({ "mud" }), "bool2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v3<bool>>();
		static Alias alias = { &t, &namspc({ "mud" }), "bool3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v4<bool>>();
		static Alias alias = { &t, &namspc({ "mud" }), "bool4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v2<float>>();
		static Alias alias = { &t, &namspc({ "mud" }), "vec2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v3<float>>();
		static Alias alias = { &t, &namspc({ "mud" }), "vec3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v4<float>>();
		static Alias alias = { &t, &namspc({ "mud" }), "vec4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v2<uint>>();
		static Alias alias = { &t, &namspc({ "mud" }), "uvec2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v3<uint>>();
		static Alias alias = { &t, &namspc({ "mud" }), "uvec3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v4<uint>>();
		static Alias alias = { &t, &namspc({ "mud" }), "uvec4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v2<int>>();
		static Alias alias = { &t, &namspc({ "mud" }), "ivec2" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v3<int>>();
		static Alias alias = { &t, &namspc({ "mud" }), "ivec3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v4<int>>();
		static Alias alias = { &t, &namspc({ "mud" }), "ivec4" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v3<bool>>();
		static Alias alias = { &t, &namspc({ "mud" }), "bvec3" };
		m.m_aliases.push_back(&alias);
	}
	{
		Type& t = type<mud::v4<bool>>();
		static Alias alias = { &t, &namspc({ "mud" }), "bvec4" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<mud::AutoStat<float>>());
		m.m_types.push_back(&type<mud::AutoStat<int>>());
		m.m_types.push_back(&type<mud::Axes>());
		m.m_types.push_back(&type<mud::Axis>());
		m.m_types.push_back(&type<mud::Clockwise>());
		m.m_types.push_back(&type<mud::Colour>());
		m.m_types.push_back(&type<mud::ColourHSL>());
		m.m_types.push_back(&type<mud::Image>());
		m.m_types.push_back(&type<mud::Image256>());
		m.m_types.push_back(&type<mud::ImageAtlas>());
		m.m_types.push_back(&type<mud::Palette>());
		m.m_types.push_back(&type<mud::Range<float>>());
		m.m_types.push_back(&type<mud::Range<mud::Colour>>());
		m.m_types.push_back(&type<mud::Range<mud::quat>>());
		m.m_types.push_back(&type<mud::Range<mud::vec3>>());
		m.m_types.push_back(&type<mud::Range<uint32_t>>());
		m.m_types.push_back(&type<mud::Side>());
		m.m_types.push_back(&type<mud::SignedAxis>());
		m.m_types.push_back(&type<mud::Spectrum>());
		m.m_types.push_back(&type<mud::Time>());
		m.m_types.push_back(&type<mud::TimeSpan>());
		m.m_types.push_back(&type<mud::TrackMode>());
		m.m_types.push_back(&type<mud::Transform>());
		m.m_types.push_back(&type<mud::ValueCurve<float>>());
		m.m_types.push_back(&type<mud::ValueCurve<mud::Colour>>());
		m.m_types.push_back(&type<mud::ValueCurve<mud::quat>>());
		m.m_types.push_back(&type<mud::ValueCurve<mud::vec3>>());
		m.m_types.push_back(&type<mud::ValueCurve<uint32_t>>());
		m.m_types.push_back(&type<mud::ValueTrack<float>>());
		m.m_types.push_back(&type<mud::ValueTrack<mud::Colour>>());
		m.m_types.push_back(&type<mud::ValueTrack<mud::quat>>());
		m.m_types.push_back(&type<mud::ValueTrack<mud::vec3>>());
		m.m_types.push_back(&type<mud::ValueTrack<uint32_t>>());
		m.m_types.push_back(&type<mud::bool2>());
		m.m_types.push_back(&type<mud::bool3>());
		m.m_types.push_back(&type<mud::bool4>());
		m.m_types.push_back(&type<mud::bvec3>());
		m.m_types.push_back(&type<mud::bvec4>());
		m.m_types.push_back(&type<mud::float2>());
		m.m_types.push_back(&type<mud::float3>());
		m.m_types.push_back(&type<mud::float4>());
		m.m_types.push_back(&type<mud::int2>());
		m.m_types.push_back(&type<mud::int3>());
		m.m_types.push_back(&type<mud::int4>());
		m.m_types.push_back(&type<mud::ivec2>());
		m.m_types.push_back(&type<mud::ivec3>());
		m.m_types.push_back(&type<mud::ivec4>());
		m.m_types.push_back(&type<mud::mat3>());
		m.m_types.push_back(&type<mud::mat4>());
		m.m_types.push_back(&type<mud::uint2>());
		m.m_types.push_back(&type<mud::uint3>());
		m.m_types.push_back(&type<mud::uint4>());
		m.m_types.push_back(&type<mud::uvec2>());
		m.m_types.push_back(&type<mud::uvec3>());
		m.m_types.push_back(&type<mud::uvec4>());
		m.m_types.push_back(&type<mud::v2<bool>>());
		m.m_types.push_back(&type<mud::v2<float>>());
		m.m_types.push_back(&type<mud::v2<int>>());
		m.m_types.push_back(&type<mud::v2<uint>>());
		m.m_types.push_back(&type<mud::v3<bool>>());
		m.m_types.push_back(&type<mud::v3<float>>());
		m.m_types.push_back(&type<mud::v3<int>>());
		m.m_types.push_back(&type<mud::v3<uint>>());
		m.m_types.push_back(&type<mud::v4<bool>>());
		m.m_types.push_back(&type<mud::v4<float>>());
		m.m_types.push_back(&type<mud::v4<int>>());
		m.m_types.push_back(&type<mud::v4<uint>>());
		m.m_types.push_back(&type<mud::vec2>());
		m.m_types.push_back(&type<mud::vec3>());
		m.m_types.push_back(&type<mud::vec4>());
		m.m_types.push_back(&type<stl::vector<float>>());
		m.m_types.push_back(&type<stl::vector<int>>());
		m.m_types.push_back(&type<stl::vector<mud::Colour>>());
		m.m_types.push_back(&type<stl::vector<mud::quat>>());
		m.m_types.push_back(&type<stl::vector<mud::uvec3>>());
		m.m_types.push_back(&type<stl::vector<mud::vec3>>());
		m.m_types.push_back(&type<stl::vector<uint32_t>>());
		m.m_types.push_back(&type<mud::Sprite>());
		m.m_types.push_back(&type<mud::SpriteAtlas>());
		m.m_types.push_back(&type<mud::TextureAtlas>());
		m.m_types.push_back(&type<mud::quat>());
		{
			static Function f = { &namspc({ "mud" }), "rgba", nullptr, mud_rgba_0, { { "colour", type<uint32_t>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "abgr", nullptr, mud_abgr_1, { { "colour", type<uint32_t>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "hsl", nullptr, mud_hsl_2, { { "h", type<float>(),  }, { "s", type<float>(),  }, { "l", type<float>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_rgba", nullptr, mud_to_rgba_3, { { "colour", type<mud::Colour>(),  } }, { &type<uint32_t>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_abgr", nullptr, mud_to_abgr_4, { { "colour", type<mud::Colour>(),  } }, { &type<uint32_t>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_linear", nullptr, mud_to_linear_5, { { "colour", type<mud::Colour>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_gamma", nullptr, mud_to_gamma_6, { { "colour", type<mud::Colour>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_srgb", nullptr, mud_to_srgb_7, { { "colour", type<mud::Colour>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_hsl", nullptr, mud_to_hsl_8, { { "r", type<float>(),  }, { "g", type<float>(),  }, { "b", type<float>(),  } }, { &type<mud::ColourHSL>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_hsl", nullptr, mud_to_hsl_9, { { "colour", type<mud::Colour>(),  } }, { &type<mud::ColourHSL>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_hsla", nullptr, mud_to_hsla_10, { { "colour", type<mud::Colour>(),  } }, { &type<mud::ColourHSL>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_rgba", nullptr, mud_to_rgba_11, { { "colour", type<mud::ColourHSL>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "sinf", nullptr, sinf_12, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "cosf", nullptr, cosf_13, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "sin", nullptr, sin_14, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "cos", nullptr, cos_15, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "add", nullptr, mud_add_16, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "subtract", nullptr, mud_subtract_17, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "multiply", nullptr, mud_multiply_18, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "divide", nullptr, mud_divide_19, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "nsinf", nullptr, mud_nsinf_20, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "ncosf", nullptr, mud_ncosf_21, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "nsin", nullptr, mud_nsin_22, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "ncos", nullptr, mud_ncos_23, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "add", nullptr, mud_add_24, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "subtract", nullptr, mud_subtract_25, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "multiply", nullptr, mud_multiply_26, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "divide", nullptr, mud_divide_27, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::vec3 forward_default = -Z3;
			static Function f = { &namspc({ "mud" }), "look_dir", nullptr, mud_look_dir_28, { { "direction", type<mud::vec3>(),  }, { "forward", type<mud::vec3>(), Param::Default, &forward_default } }, { &type<mud::quat>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static mud::vec3 forward_default = -Z3;
			static Function f = { &namspc({ "mud" }), "look_at", nullptr, mud_look_at_29, { { "eye", type<mud::vec3>(),  }, { "target", type<mud::vec3>(),  }, { "forward", type<mud::vec3>(), Param::Default, &forward_default } }, { &type<mud::quat>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "grid", nullptr, mud_grid_30, { { "size", type<mud::uvec3>(),  }, { "output_coords", type<stl::vector<mud::uvec3>>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "grid_center", nullptr, mud_grid_center_31, { { "coord", type<mud::uvec3>(),  }, { "cell_size", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "index_list", nullptr, mud_index_list_32, { { "size", type<uint32_t>(),  }, { "output_indices", type<stl::vector<uint32_t>>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_math::mud_math()
		: Module("mud::math", { &mud_infra::m(), &mud_type::m() })
	{
		// setup reflection meta data
		mud_math_meta(*this);
	}
}

#ifdef MUD_MATH_MODULE
extern "C"
Module& getModule()
{
		return mud_math::m();
}
#endif
