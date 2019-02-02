#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/new.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/math/Convert.h>
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
size_t vector_float___size(void* vec) { return (*static_cast<vector<float>*>(vec)).size(); }
void* vector_float___at(void* vec, size_t i) { return &(*static_cast<vector<float>*>(vec))[i]; }
void vector_float___add(void* vec, void* value) { (*static_cast<vector<float>*>(vec)).push_back(*static_cast<float*>(value)); }
void vector_float___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<float>*>(vec)), *static_cast<float*>(value)); }
size_t vector_mud_Colour___size(void* vec) { return (*static_cast<vector<mud::Colour>*>(vec)).size(); }
void* vector_mud_Colour___at(void* vec, size_t i) { return &(*static_cast<vector<mud::Colour>*>(vec))[i]; }
void vector_mud_Colour___add(void* vec, void* value) { (*static_cast<vector<mud::Colour>*>(vec)).push_back(*static_cast<mud::Colour*>(value)); }
void vector_mud_Colour___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Colour>*>(vec)), *static_cast<mud::Colour*>(value)); }
size_t vector_mud_quat___size(void* vec) { return (*static_cast<vector<mud::quat>*>(vec)).size(); }
void* vector_mud_quat___at(void* vec, size_t i) { return &(*static_cast<vector<mud::quat>*>(vec))[i]; }
void vector_mud_quat___add(void* vec, void* value) { (*static_cast<vector<mud::quat>*>(vec)).push_back(*static_cast<mud::quat*>(value)); }
void vector_mud_quat___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::quat>*>(vec)), *static_cast<mud::quat*>(value)); }
size_t vector_mud_uvec3___size(void* vec) { return (*static_cast<vector<mud::uvec3>*>(vec)).size(); }
void* vector_mud_uvec3___at(void* vec, size_t i) { return &(*static_cast<vector<mud::uvec3>*>(vec))[i]; }
void vector_mud_uvec3___add(void* vec, void* value) { (*static_cast<vector<mud::uvec3>*>(vec)).push_back(*static_cast<mud::uvec3*>(value)); }
void vector_mud_uvec3___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::uvec3>*>(vec)), *static_cast<mud::uvec3*>(value)); }
size_t vector_mud_vec3___size(void* vec) { return (*static_cast<vector<mud::vec3>*>(vec)).size(); }
void* vector_mud_vec3___at(void* vec, size_t i) { return &(*static_cast<vector<mud::vec3>*>(vec))[i]; }
void vector_mud_vec3___add(void* vec, void* value) { (*static_cast<vector<mud::vec3>*>(vec)).push_back(*static_cast<mud::vec3*>(value)); }
void vector_mud_vec3___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::vec3>*>(vec)), *static_cast<mud::vec3*>(value)); }
size_t vector_uint32_t___size(void* vec) { return (*static_cast<vector<uint32_t>*>(vec)).size(); }
void* vector_uint32_t___at(void* vec, size_t i) { return &(*static_cast<vector<uint32_t>*>(vec))[i]; }
void vector_uint32_t___add(void* vec, void* value) { (*static_cast<vector<uint32_t>*>(vec)).push_back(*static_cast<uint32_t*>(value)); }
void vector_uint32_t___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<uint32_t>*>(vec)), *static_cast<uint32_t*>(value)); }
void mud_AutoStat_float___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::AutoStat<float>*>(ref))) mud::AutoStat<float>(  ); }
void mud_AutoStat_float___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::AutoStat<float>*>(ref))) mud::AutoStat<float>((*static_cast<mud::AutoStat<float>*>(other))); }
void mud_AutoStat_int___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::AutoStat<int>*>(ref))) mud::AutoStat<int>(  ); }
void mud_AutoStat_int___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::AutoStat<int>*>(ref))) mud::AutoStat<int>((*static_cast<mud::AutoStat<int>*>(other))); }
void mud_Colour__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Colour*>(ref))) mud::Colour(  ); }
void mud_Colour__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Colour*>(ref))) mud::Colour( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Colour__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Colour*>(ref))) mud::Colour( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_Colour__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Colour*>(ref))) mud::Colour((*static_cast<mud::Colour*>(other))); }
void mud_Image__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Image*>(ref))) mud::Image(  ); }
void mud_Image__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Image*>(ref))) mud::Image((*static_cast<mud::Image*>(other))); }
void mud_Image256__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Image256*>(ref))) mud::Image256( *static_cast<uint16_t*>(args[0]), *static_cast<uint16_t*>(args[1]), *static_cast<mud::Palette*>(args[2]) ); }
void mud_Image256__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Image256*>(ref))) mud::Image256((*static_cast<mud::Image256*>(other))); }
void mud_Palette__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Palette*>(ref))) mud::Palette( *static_cast<mud::Spectrum*>(args[0]), *static_cast<size_t*>(args[1]) ); }
void mud_Palette__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Palette*>(ref))) mud::Palette( *static_cast<vector<mud::Colour>*>(args[0]) ); }
void mud_Palette__construct_2(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Palette*>(ref))) mud::Palette(  ); }
void mud_Palette__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Palette*>(ref))) mud::Palette((*static_cast<mud::Palette*>(other))); }
void mud_Range_float___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Range<float>*>(ref))) mud::Range<float>(  ); }
void mud_Range_float___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Range<float>*>(ref))) mud::Range<float>((*static_cast<mud::Range<float>*>(other))); }
void mud_Range_mud_Colour___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Range<mud::Colour>*>(ref))) mud::Range<mud::Colour>(  ); }
void mud_Range_mud_Colour___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Range<mud::Colour>*>(ref))) mud::Range<mud::Colour>((*static_cast<mud::Range<mud::Colour>*>(other))); }
void mud_Range_mud_quat___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Range<mud::quat>*>(ref))) mud::Range<mud::quat>(  ); }
void mud_Range_mud_quat___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Range<mud::quat>*>(ref))) mud::Range<mud::quat>((*static_cast<mud::Range<mud::quat>*>(other))); }
void mud_Range_mud_vec3___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Range<mud::vec3>*>(ref))) mud::Range<mud::vec3>(  ); }
void mud_Range_mud_vec3___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Range<mud::vec3>*>(ref))) mud::Range<mud::vec3>((*static_cast<mud::Range<mud::vec3>*>(other))); }
void mud_Range_uint32_t___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Range<uint32_t>*>(ref))) mud::Range<uint32_t>(  ); }
void mud_Range_uint32_t___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Range<uint32_t>*>(ref))) mud::Range<uint32_t>((*static_cast<mud::Range<uint32_t>*>(other))); }
void mud_Time__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Time*>(ref))) mud::Time( *static_cast<double*>(args[0]) ); }
void mud_Time__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Time*>(ref))) mud::Time((*static_cast<mud::Time*>(other))); }
void mud_TimeSpan__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::TimeSpan*>(ref))) mud::TimeSpan( *static_cast<mud::Time*>(args[0]), *static_cast<mud::Time*>(args[1]) ); }
void mud_TimeSpan__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::TimeSpan*>(ref))) mud::TimeSpan((*static_cast<mud::TimeSpan*>(other))); }
//void mud_Transform__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Transform*>(ref))) mud::Transform(  ); }
//void mud_Transform__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Transform*>(ref))) mud::Transform( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::quat*>(args[1]), *static_cast<mud::vec3*>(args[2]) ); }
void mud_Transform__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Transform*>(ref))) mud::Transform((*static_cast<mud::Transform*>(other))); }
void mud_ValueCurve_float___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueCurve<float>*>(ref))) mud::ValueCurve<float>(  ); }
void mud_ValueCurve_float___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<float>*>(ref))) mud::ValueCurve<float>( *static_cast<vector<float>*>(args[0]) ); }
void mud_ValueCurve_float___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<float>*>(ref))) mud::ValueCurve<float>((*static_cast<mud::ValueCurve<float>*>(other))); }
void mud_ValueCurve_mud_Colour___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::Colour>*>(ref))) mud::ValueCurve<mud::Colour>(  ); }
void mud_ValueCurve_mud_Colour___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::Colour>*>(ref))) mud::ValueCurve<mud::Colour>( *static_cast<vector<mud::Colour>*>(args[0]) ); }
void mud_ValueCurve_mud_Colour___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::Colour>*>(ref))) mud::ValueCurve<mud::Colour>((*static_cast<mud::ValueCurve<mud::Colour>*>(other))); }
void mud_ValueCurve_mud_quat___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::quat>*>(ref))) mud::ValueCurve<mud::quat>(  ); }
void mud_ValueCurve_mud_quat___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::quat>*>(ref))) mud::ValueCurve<mud::quat>( *static_cast<vector<mud::quat>*>(args[0]) ); }
void mud_ValueCurve_mud_quat___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::quat>*>(ref))) mud::ValueCurve<mud::quat>((*static_cast<mud::ValueCurve<mud::quat>*>(other))); }
void mud_ValueCurve_mud_vec3___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::vec3>*>(ref))) mud::ValueCurve<mud::vec3>(  ); }
void mud_ValueCurve_mud_vec3___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::vec3>*>(ref))) mud::ValueCurve<mud::vec3>( *static_cast<vector<mud::vec3>*>(args[0]) ); }
void mud_ValueCurve_mud_vec3___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<mud::vec3>*>(ref))) mud::ValueCurve<mud::vec3>((*static_cast<mud::ValueCurve<mud::vec3>*>(other))); }
void mud_ValueCurve_uint32_t___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueCurve<uint32_t>*>(ref))) mud::ValueCurve<uint32_t>(  ); }
void mud_ValueCurve_uint32_t___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<uint32_t>*>(ref))) mud::ValueCurve<uint32_t>( *static_cast<vector<uint32_t>*>(args[0]) ); }
void mud_ValueCurve_uint32_t___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueCurve<uint32_t>*>(ref))) mud::ValueCurve<uint32_t>((*static_cast<mud::ValueCurve<uint32_t>*>(other))); }
void mud_ValueTrack_float___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueTrack<float>*>(ref))) mud::ValueTrack<float>(  ); }
void mud_ValueTrack_float___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<float>*>(ref))) mud::ValueTrack<float>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<float>*>(args[1]), *static_cast<mud::ValueCurve<float>*>(args[2]), *static_cast<mud::ValueCurve<float>*>(args[3]) ); }
void mud_ValueTrack_float___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<float>*>(ref))) mud::ValueTrack<float>((*static_cast<mud::ValueTrack<float>*>(other))); }
void mud_ValueTrack_mud_Colour___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::Colour>*>(ref))) mud::ValueTrack<mud::Colour>(  ); }
void mud_ValueTrack_mud_Colour___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::Colour>*>(ref))) mud::ValueTrack<mud::Colour>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<mud::Colour>*>(args[1]), *static_cast<mud::ValueCurve<mud::Colour>*>(args[2]), *static_cast<mud::ValueCurve<mud::Colour>*>(args[3]) ); }
void mud_ValueTrack_mud_Colour___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::Colour>*>(ref))) mud::ValueTrack<mud::Colour>((*static_cast<mud::ValueTrack<mud::Colour>*>(other))); }
void mud_ValueTrack_mud_quat___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::quat>*>(ref))) mud::ValueTrack<mud::quat>(  ); }
void mud_ValueTrack_mud_quat___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::quat>*>(ref))) mud::ValueTrack<mud::quat>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<mud::quat>*>(args[1]), *static_cast<mud::ValueCurve<mud::quat>*>(args[2]), *static_cast<mud::ValueCurve<mud::quat>*>(args[3]) ); }
void mud_ValueTrack_mud_quat___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::quat>*>(ref))) mud::ValueTrack<mud::quat>((*static_cast<mud::ValueTrack<mud::quat>*>(other))); }
void mud_ValueTrack_mud_vec3___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::vec3>*>(ref))) mud::ValueTrack<mud::vec3>(  ); }
void mud_ValueTrack_mud_vec3___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::vec3>*>(ref))) mud::ValueTrack<mud::vec3>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<mud::vec3>*>(args[1]), *static_cast<mud::ValueCurve<mud::vec3>*>(args[2]), *static_cast<mud::ValueCurve<mud::vec3>*>(args[3]) ); }
void mud_ValueTrack_mud_vec3___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<mud::vec3>*>(ref))) mud::ValueTrack<mud::vec3>((*static_cast<mud::ValueTrack<mud::vec3>*>(other))); }
void mud_ValueTrack_uint32_t___construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ValueTrack<uint32_t>*>(ref))) mud::ValueTrack<uint32_t>(  ); }
void mud_ValueTrack_uint32_t___construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<uint32_t>*>(ref))) mud::ValueTrack<uint32_t>( *static_cast<mud::TrackMode*>(args[0]), *static_cast<mud::ValueCurve<uint32_t>*>(args[1]), *static_cast<mud::ValueCurve<uint32_t>*>(args[2]), *static_cast<mud::ValueCurve<uint32_t>*>(args[3]) ); }
void mud_ValueTrack_uint32_t___copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ValueTrack<uint32_t>*>(ref))) mud::ValueTrack<uint32_t>((*static_cast<mud::ValueTrack<uint32_t>*>(other))); }
void mud_bvec3__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::bvec3*>(ref))) mud::bvec3(  ); }
void mud_bvec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::bvec3*>(ref))) mud::bvec3((*static_cast<mud::bvec3*>(other))); }
void mud_bvec4__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::bvec4*>(ref))) mud::bvec4(  ); }
void mud_bvec4__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::bvec4*>(ref))) mud::bvec4((*static_cast<mud::bvec4*>(other))); }
void mud_half2__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::half2*>(ref))) mud::half2(  ); }
void mud_half2__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::half2*>(ref))) mud::half2((*static_cast<mud::half2*>(other))); }
void mud_half3__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::half3*>(ref))) mud::half3(  ); }
void mud_half3__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::half3*>(ref))) mud::half3((*static_cast<mud::half3*>(other))); }
void mud_ivec2__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ivec2*>(ref))) mud::ivec2(  ); }
void mud_ivec2__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ivec2*>(ref))) mud::ivec2((*static_cast<mud::ivec2*>(other))); }
void mud_ivec3__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ivec3*>(ref))) mud::ivec3(  ); }
void mud_ivec3__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ivec3*>(ref))) mud::ivec3( *static_cast<int*>(args[0]) ); }
void mud_ivec3__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ivec3*>(ref))) mud::ivec3( *static_cast<int*>(args[0]), *static_cast<int*>(args[1]), *static_cast<int*>(args[2]) ); }
void mud_ivec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ivec3*>(ref))) mud::ivec3((*static_cast<mud::ivec3*>(other))); }
void mud_ivec4__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ivec4*>(ref))) mud::ivec4(  ); }
void mud_ivec4__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ivec4*>(ref))) mud::ivec4((*static_cast<mud::ivec4*>(other))); }
void mud_mat4__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::mat4*>(ref))) mud::mat4(  ); }
void mud_mat4__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::mat4*>(ref))) mud::mat4((*static_cast<mud::mat4*>(other))); }
void mud_quat__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::quat*>(ref))) mud::quat(  ); }
void mud_quat__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::quat*>(ref))) mud::quat( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_quat__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::quat*>(ref))) mud::quat( *static_cast<mud::vec3*>(args[0]) ); }
void mud_quat__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::quat*>(ref))) mud::quat((*static_cast<mud::quat*>(other))); }
void mud_uvec2__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::uvec2*>(ref))) mud::uvec2(  ); }
void mud_uvec2__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::uvec2*>(ref))) mud::uvec2( *static_cast<uint32_t*>(args[0]) ); }
void mud_uvec2__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::uvec2*>(ref))) mud::uvec2( *static_cast<uint32_t*>(args[0]), *static_cast<uint32_t*>(args[1]) ); }
void mud_uvec2__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::uvec2*>(ref))) mud::uvec2((*static_cast<mud::uvec2*>(other))); }
void mud_uvec3__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::uvec3*>(ref))) mud::uvec3(  ); }
void mud_uvec3__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::uvec3*>(ref))) mud::uvec3( *static_cast<uint32_t*>(args[0]) ); }
void mud_uvec3__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::uvec3*>(ref))) mud::uvec3( *static_cast<uint32_t*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<uint32_t*>(args[2]) ); }
void mud_uvec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::uvec3*>(ref))) mud::uvec3((*static_cast<mud::uvec3*>(other))); }
void mud_uvec4__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::uvec4*>(ref))) mud::uvec4(  ); }
void mud_uvec4__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::uvec4*>(ref))) mud::uvec4( *static_cast<uint32_t*>(args[0]) ); }
void mud_uvec4__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::uvec4*>(ref))) mud::uvec4( *static_cast<uint32_t*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<uint32_t*>(args[2]), *static_cast<uint32_t*>(args[3]) ); }
void mud_uvec4__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::uvec4*>(ref))) mud::uvec4((*static_cast<mud::uvec4*>(other))); }
void mud_vec2__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::vec2*>(ref))) mud::vec2(  ); }
void mud_vec2__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::vec2*>(ref))) mud::vec2( *static_cast<float*>(args[0]) ); }
void mud_vec2__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::vec2*>(ref))) mud::vec2( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_vec2__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::vec2*>(ref))) mud::vec2((*static_cast<mud::vec2*>(other))); }
void mud_vec3__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::vec3*>(ref))) mud::vec3(  ); }
void mud_vec3__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::vec3*>(ref))) mud::vec3( *static_cast<float*>(args[0]) ); }
void mud_vec3__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::vec3*>(ref))) mud::vec3( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_vec3__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::vec3*>(ref))) mud::vec3((*static_cast<mud::vec3*>(other))); }
void mud_vec4__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::vec4*>(ref))) mud::vec4(  ); }
void mud_vec4__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::vec4*>(ref))) mud::vec4( *static_cast<float*>(args[0]) ); }
void mud_vec4__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::vec4*>(ref))) mud::vec4( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_vec4__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::vec4*>(ref))) mud::vec4((*static_cast<mud::vec4*>(other))); }
void _sinf_0(array<void*> args, void*& result) { (*static_cast<float*>(result)) = sinf(*static_cast<float*>(args[0])); }
void _cosf_1(array<void*> args, void*& result) { (*static_cast<float*>(result)) = cosf(*static_cast<float*>(args[0])); }
void _sin_2(array<void*> args, void*& result) { (*static_cast<double*>(result)) = sin(*static_cast<double*>(args[0])); }
void _cos_3(array<void*> args, void*& result) { (*static_cast<double*>(result)) = cos(*static_cast<double*>(args[0])); }
void mud_add_float__4(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::add<float>(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void mud_subtract_float__5(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::subtract<float>(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void mud_multiply_float__6(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::multiply<float>(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void mud_divide_float__7(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::divide<float>(*static_cast<float*>(args[0]), *static_cast<float*>(args[1])); }
void mud_nsinf_8(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::nsinf(*static_cast<float*>(args[0])); }
void mud_ncosf_9(array<void*> args, void*& result) { (*static_cast<float*>(result)) = mud::ncosf(*static_cast<float*>(args[0])); }
void mud_nsin_10(array<void*> args, void*& result) { (*static_cast<double*>(result)) = mud::nsin(*static_cast<double*>(args[0])); }
void mud_ncos_11(array<void*> args, void*& result) { (*static_cast<double*>(result)) = mud::ncos(*static_cast<double*>(args[0])); }
void mud_to_rgba_12(array<void*> args, void*& result) { (*static_cast<uint32_t*>(result)) = mud::to_rgba(*static_cast<mud::Colour*>(args[0])); }
void mud_to_abgr_13(array<void*> args, void*& result) { (*static_cast<uint32_t*>(result)) = mud::to_abgr(*static_cast<mud::Colour*>(args[0])); }
void mud_from_rgba_14(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::from_rgba(*static_cast<uint32_t*>(args[0])); }
void mud_from_abgr_15(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::from_abgr(*static_cast<uint32_t*>(args[0])); }
void mud_to_linear_16(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::to_linear(*static_cast<mud::Colour*>(args[0])); }
void mud_to_gamma_17(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::to_gamma(*static_cast<mud::Colour*>(args[0])); }
void mud_to_srgb_18(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::to_srgb(*static_cast<mud::Colour*>(args[0])); }
void mud_hsl_to_rgb_19(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::hsl_to_rgb(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_rgb_to_hsl_20(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::rgb_to_hsl(*static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_rgba_to_hsla_21(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::rgba_to_hsla(*static_cast<mud::Colour*>(args[0])); }
void mud_hsla_to_rgba_22(array<void*> args, void*& result) { (*static_cast<mud::Colour*>(result)) = mud::hsla_to_rgba(*static_cast<mud::Colour*>(args[0])); }
void mud_look_dir_23(array<void*> args, void*& result) { (*static_cast<mud::quat*>(result)) = mud::look_dir(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_look_at_24(array<void*> args, void*& result) { (*static_cast<mud::quat*>(result)) = mud::look_at(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2])); }
void mud_add_mud_vec3__25(array<void*> args, void*& result) { (*static_cast<mud::vec3*>(result)) = mud::add<mud::vec3>(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_subtract_mud_vec3__26(array<void*> args, void*& result) { (*static_cast<mud::vec3*>(result)) = mud::subtract<mud::vec3>(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_multiply_mud_vec3__27(array<void*> args, void*& result) { (*static_cast<mud::vec3*>(result)) = mud::multiply<mud::vec3>(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_divide_mud_vec3__28(array<void*> args, void*& result) { (*static_cast<mud::vec3*>(result)) = mud::divide<mud::vec3>(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_grid_29(array<void*> args, void*& result) { UNUSED(result);  mud::grid(*static_cast<mud::uvec3*>(args[0]), *static_cast<vector<mud::uvec3>*>(args[1])); }
void mud_grid_center_30(array<void*> args, void*& result) { (*static_cast<mud::vec3*>(result)) = mud::grid_center(*static_cast<mud::uvec3*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_index_list_31(array<void*> args, void*& result) { UNUSED(result);  mud::index_list(*static_cast<uint32_t*>(args[0]), *static_cast<vector<uint32_t>*>(args[1])); }

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
		static cstring ids[] = { "X", "Y", "Z" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Axis vars[] = { mud::Axis::X, mud::Axis::Y, mud::Axis::Z};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
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
		static cstring ids[] = { "Right", "Left", "Up", "Down", "Back", "Front" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::Side vars[] = { mud::Side::Right, mud::Side::Left, mud::Side::Up, mud::Side::Down, mud::Side::Back, mud::Side::Front};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Side__to_string,
		                           mud_Side__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::SignedAxis>();
		static Meta meta = { t, &namspc({ "mud" }), "SignedAxis", sizeof(mud::SignedAxis), TypeClass::Enum };
		static cstring ids[] = { "PlusX", "MinusX", "PlusY", "MinusY", "PlusZ", "MinusZ" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::SignedAxis vars[] = { mud::SignedAxis::PlusX, mud::SignedAxis::MinusX, mud::SignedAxis::PlusY, mud::SignedAxis::MinusY, mud::SignedAxis::PlusZ, mud::SignedAxis::MinusZ};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
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
		Type& t = type<vector<float>>();
		static Meta meta = { t, &namspc({}), "vector<float>", sizeof(vector<float>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<float>(),
		                             vector_float___size,
		                             vector_float___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_float___add,
		                             vector_float___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<mud::Colour>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Colour>", sizeof(vector<mud::Colour>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Colour>(),
		                             vector_mud_Colour___size,
		                             vector_mud_Colour___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Colour___add,
		                             vector_mud_Colour___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<mud::quat>>();
		static Meta meta = { t, &namspc({}), "vector<mud::quat>", sizeof(vector<mud::quat>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::quat>(),
		                             vector_mud_quat___size,
		                             vector_mud_quat___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_quat___add,
		                             vector_mud_quat___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<mud::uvec3>>();
		static Meta meta = { t, &namspc({}), "vector<mud::uvec3>", sizeof(vector<mud::uvec3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::uvec3>(),
		                             vector_mud_uvec3___size,
		                             vector_mud_uvec3___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_uvec3___add,
		                             vector_mud_uvec3___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<mud::vec3>>();
		static Meta meta = { t, &namspc({}), "vector<mud::vec3>", sizeof(vector<mud::vec3>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::vec3>(),
		                             vector_mud_vec3___size,
		                             vector_mud_vec3___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_vec3___add,
		                             vector_mud_vec3___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<uint32_t>>();
		static Meta meta = { t, &namspc({}), "vector<uint32_t>", sizeof(vector<uint32_t>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<uint32_t>(),
		                             vector_uint32_t___size,
		                             vector_uint32_t___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_uint32_t___add,
		                             vector_uint32_t___remove };
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
			{ t, mud_AutoStat_float___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_AutoStat_float___copy_construct }
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
			{ t, mud_AutoStat_int___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_AutoStat_int___copy_construct }
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
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Colour__construct_0, {} },
			{ t, mud_Colour__construct_1, { { "v", type<float>(),  }, { "a", type<float>(), Param::Default } } },
			{ t, mud_Colour__construct_2, { { "r", type<float>(),  }, { "g", type<float>(),  }, { "b", type<float>(),  }, { "a", type<float>(), Param::Default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Colour__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Colour, m_r), type<float>(), "r", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Colour, m_g), type<float>(), "g", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Colour, m_b), type<float>(), "b", nullptr, Member::Value, nullptr },
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
			{ t, offsetof(mud::Image, d_name), type<string>(), "d_name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Image, d_path), type<string>(), "d_path", nullptr, Member::Value, nullptr }
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
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Image256__construct_0, { { "width", type<uint16_t>(), Param::Default }, { "height", type<uint16_t>(), Param::Default }, { "palette", type<mud::Palette>(), Param::Default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Image256__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Image256, m_pixels), type<vector<uint32_t>>(), "pixels", nullptr, Member::Value, nullptr },
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
			{ t, mud_Palette__construct_1, { { "colours", type<vector<mud::Colour>>(),  } } },
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
			{ t, mud_Range_float___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_float___copy_construct }
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
			{ t, mud_Range_mud_Colour___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_mud_Colour___copy_construct }
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
			{ t, mud_Range_mud_quat___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_mud_quat___copy_construct }
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
			{ t, mud_Range_mud_vec3___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_mud_vec3___copy_construct }
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
			{ t, mud_Range_uint32_t___construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Range_uint32_t___copy_construct }
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
		static mud::vec3 position_default = Zero3;
		static mud::quat rotation_default = ZeroQuat;
		static mud::vec3 scale_default = Unit3;
		// constructors
		//static Constructor constructors[] = {
		//	{ t, mud_Transform__construct_0, {} },
		//	{ t, mud_Transform__construct_1, { { "position", type<mud::vec3>(),  }, { "rotation", type<mud::quat>(),  }, { "scale", type<mud::vec3>(),  } } }
		//};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Transform__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Transform, m_position), type<mud::vec3>(), "position", &position_default, Member::Value, nullptr },
			{ t, offsetof(mud::Transform, m_rotation), type<mud::quat>(), "rotation", &rotation_default, Member::Value, nullptr },
			{ t, offsetof(mud::Transform, m_scale), type<mud::vec3>(), "scale", &scale_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, copy_constructor, members, {}, {}, };
	}
	// mud::ValueCurve<float>
	{
		Type& t = type<mud::ValueCurve<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<float>", sizeof(mud::ValueCurve<float>), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ValueCurve_float___construct_0, {} },
			{ t, mud_ValueCurve_float___construct_1, { { "keys", type<vector<float>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_float___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<float>, m_keys), type<vector<float>>(), "keys", nullptr, Member::Value, nullptr }
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
			{ t, mud_ValueCurve_mud_Colour___construct_0, {} },
			{ t, mud_ValueCurve_mud_Colour___construct_1, { { "keys", type<vector<mud::Colour>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_mud_Colour___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<mud::Colour>, m_keys), type<vector<mud::Colour>>(), "keys", nullptr, Member::Value, nullptr }
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
			{ t, mud_ValueCurve_mud_quat___construct_0, {} },
			{ t, mud_ValueCurve_mud_quat___construct_1, { { "keys", type<vector<mud::quat>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_mud_quat___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<mud::quat>, m_keys), type<vector<mud::quat>>(), "keys", nullptr, Member::Value, nullptr }
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
			{ t, mud_ValueCurve_mud_vec3___construct_0, {} },
			{ t, mud_ValueCurve_mud_vec3___construct_1, { { "keys", type<vector<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_mud_vec3___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<mud::vec3>, m_keys), type<vector<mud::vec3>>(), "keys", nullptr, Member::Value, nullptr }
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
			{ t, mud_ValueCurve_uint32_t___construct_0, {} },
			{ t, mud_ValueCurve_uint32_t___construct_1, { { "keys", type<vector<uint32_t>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueCurve_uint32_t___copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ValueCurve<uint32_t>, m_keys), type<vector<uint32_t>>(), "keys", nullptr, Member::Value, nullptr }
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
			{ t, mud_ValueTrack_float___construct_0, {} },
			{ t, mud_ValueTrack_float___construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<float>>(),  }, { "min_curve", type<mud::ValueCurve<float>>(),  }, { "max_curve", type<mud::ValueCurve<float>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_float___copy_construct }
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
			{ t, mud_ValueTrack_mud_Colour___construct_0, {} },
			{ t, mud_ValueTrack_mud_Colour___construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<mud::Colour>>(),  }, { "min_curve", type<mud::ValueCurve<mud::Colour>>(),  }, { "max_curve", type<mud::ValueCurve<mud::Colour>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_mud_Colour___copy_construct }
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
			{ t, mud_ValueTrack_mud_quat___construct_0, {} },
			{ t, mud_ValueTrack_mud_quat___construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<mud::quat>>(),  }, { "min_curve", type<mud::ValueCurve<mud::quat>>(),  }, { "max_curve", type<mud::ValueCurve<mud::quat>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_mud_quat___copy_construct }
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
			{ t, mud_ValueTrack_mud_vec3___construct_0, {} },
			{ t, mud_ValueTrack_mud_vec3___construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<mud::vec3>>(),  }, { "min_curve", type<mud::ValueCurve<mud::vec3>>(),  }, { "max_curve", type<mud::ValueCurve<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_mud_vec3___copy_construct }
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
			{ t, mud_ValueTrack_uint32_t___construct_0, {} },
			{ t, mud_ValueTrack_uint32_t___construct_1, { { "mode", type<mud::TrackMode>(),  }, { "curve", type<mud::ValueCurve<uint32_t>>(),  }, { "min_curve", type<mud::ValueCurve<uint32_t>>(),  }, { "max_curve", type<mud::ValueCurve<uint32_t>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ValueTrack_uint32_t___copy_construct }
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
	// mud::bvec3
	{
		Type& t = type<mud::bvec3>();
		static Meta meta = { t, &namspc({ "mud" }), "bvec3", sizeof(mud::bvec3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_bvec3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_bvec3__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::bvec4
	{
		Type& t = type<mud::bvec4>();
		static Meta meta = { t, &namspc({ "mud" }), "bvec4", sizeof(mud::bvec4), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_bvec4__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_bvec4__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::half2
	{
		Type& t = type<mud::half2>();
		static Meta meta = { t, &namspc({ "mud" }), "half2", sizeof(mud::half2), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_half2__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_half2__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::half3
	{
		Type& t = type<mud::half3>();
		static Meta meta = { t, &namspc({ "mud" }), "half3", sizeof(mud::half3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_half3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_half3__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::ivec2
	{
		Type& t = type<mud::ivec2>();
		static Meta meta = { t, &namspc({ "mud" }), "ivec2", sizeof(mud::ivec2), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ivec2__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ivec2__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::ivec3
	{
		Type& t = type<mud::ivec3>();
		static Meta meta = { t, &namspc({ "mud" }), "ivec3", sizeof(mud::ivec3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ivec3__construct_0, {} },
			{ t, mud_ivec3__construct_1, { { "a", type<int>(),  } } },
			{ t, mud_ivec3__construct_2, { { "x", type<int>(),  }, { "y", type<int>(),  }, { "z", type<int>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ivec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ivec3, x), type<int>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ivec3, y), type<int>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ivec3, z), type<int>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ivec4
	{
		Type& t = type<mud::ivec4>();
		static Meta meta = { t, &namspc({ "mud" }), "ivec4", sizeof(mud::ivec4), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ivec4__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ivec4__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::mat4
	{
		Type& t = type<mud::mat4>();
		static Meta meta = { t, &namspc({ "mud" }), "mat4", sizeof(mud::mat4), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_mat4__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_mat4__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::quat
	{
		Type& t = type<mud::quat>();
		static Meta meta = { t, &namspc({ "mud" }), "quat", sizeof(mud::quat), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_quat__construct_0, {} },
			{ t, mud_quat__construct_1, { { "w", type<float>(),  }, { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  } } },
			{ t, mud_quat__construct_2, { { "euler_angles", type<mud::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_quat__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::quat, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::quat, y), type<float>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::quat, z), type<float>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::quat, w), type<float>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::uvec2
	{
		Type& t = type<mud::uvec2>();
		static Meta meta = { t, &namspc({ "mud" }), "uvec2", sizeof(mud::uvec2), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_uvec2__construct_0, {} },
			{ t, mud_uvec2__construct_1, { { "a", type<uint32_t>(),  } } },
			{ t, mud_uvec2__construct_2, { { "x", type<uint32_t>(),  }, { "y", type<uint32_t>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_uvec2__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::uvec2, x), type<uint32_t>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::uvec2, y), type<uint32_t>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::uvec3
	{
		Type& t = type<mud::uvec3>();
		static Meta meta = { t, &namspc({ "mud" }), "uvec3", sizeof(mud::uvec3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_uvec3__construct_0, {} },
			{ t, mud_uvec3__construct_1, { { "a", type<uint32_t>(),  } } },
			{ t, mud_uvec3__construct_2, { { "x", type<uint32_t>(),  }, { "y", type<uint32_t>(),  }, { "z", type<uint32_t>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_uvec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::uvec3, x), type<uint32_t>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::uvec3, y), type<uint32_t>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::uvec3, z), type<uint32_t>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::uvec4
	{
		Type& t = type<mud::uvec4>();
		static Meta meta = { t, &namspc({ "mud" }), "uvec4", sizeof(mud::uvec4), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_uvec4__construct_0, {} },
			{ t, mud_uvec4__construct_1, { { "a", type<uint32_t>(),  } } },
			{ t, mud_uvec4__construct_2, { { "w", type<uint32_t>(),  }, { "x", type<uint32_t>(),  }, { "y", type<uint32_t>(),  }, { "z", type<uint32_t>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_uvec4__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::uvec4, x), type<uint32_t>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::uvec4, y), type<uint32_t>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::uvec4, z), type<uint32_t>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::uvec4, w), type<uint32_t>(), "w", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::vec2
	{
		Type& t = type<mud::vec2>();
		static Meta meta = { t, &namspc({ "mud" }), "vec2", sizeof(mud::vec2), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_vec2__construct_0, {} },
			{ t, mud_vec2__construct_1, { { "a", type<float>(),  } } },
			{ t, mud_vec2__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_vec2__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::vec2, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::vec2, y), type<float>(), "y", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::vec3
	{
		Type& t = type<mud::vec3>();
		static Meta meta = { t, &namspc({ "mud" }), "vec3", sizeof(mud::vec3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_vec3__construct_0, {} },
			{ t, mud_vec3__construct_1, { { "a", type<float>(),  } } },
			{ t, mud_vec3__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_vec3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::vec3, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::vec3, y), type<float>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::vec3, z), type<float>(), "z", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::vec4
	{
		Type& t = type<mud::vec4>();
		static Meta meta = { t, &namspc({ "mud" }), "vec4", sizeof(mud::vec4), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_vec4__construct_0, {} },
			{ t, mud_vec4__construct_1, { { "a", type<float>(),  } } },
			{ t, mud_vec4__construct_2, { { "w", type<float>(),  }, { "x", type<float>(),  }, { "y", type<float>(),  }, { "z", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_vec4__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::vec4, x), type<float>(), "x", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::vec4, y), type<float>(), "y", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::vec4, z), type<float>(), "z", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::vec4, w), type<float>(), "w", nullptr, Member::Value, nullptr }
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
		m.m_types.push_back(&type<mud::AutoStat<float>>());
		m.m_types.push_back(&type<mud::AutoStat<int>>());
		m.m_types.push_back(&type<mud::Axes>());
		m.m_types.push_back(&type<mud::Axis>());
		m.m_types.push_back(&type<mud::Clockwise>());
		m.m_types.push_back(&type<mud::Colour>());
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
		m.m_types.push_back(&type<mud::bvec3>());
		m.m_types.push_back(&type<mud::bvec4>());
		m.m_types.push_back(&type<mud::half2>());
		m.m_types.push_back(&type<mud::half3>());
		m.m_types.push_back(&type<mud::ivec2>());
		m.m_types.push_back(&type<mud::ivec3>());
		m.m_types.push_back(&type<mud::ivec4>());
		m.m_types.push_back(&type<mud::mat4>());
		m.m_types.push_back(&type<mud::quat>());
		m.m_types.push_back(&type<mud::uvec2>());
		m.m_types.push_back(&type<mud::uvec3>());
		m.m_types.push_back(&type<mud::uvec4>());
		m.m_types.push_back(&type<mud::vec2>());
		m.m_types.push_back(&type<mud::vec3>());
		m.m_types.push_back(&type<mud::vec4>());
		m.m_types.push_back(&type<vector<float>>());
		m.m_types.push_back(&type<vector<mud::Colour>>());
		m.m_types.push_back(&type<vector<mud::quat>>());
		m.m_types.push_back(&type<vector<mud::uvec3>>());
		m.m_types.push_back(&type<vector<mud::vec3>>());
		m.m_types.push_back(&type<vector<uint32_t>>());
		m.m_types.push_back(&type<mud::Sprite>());
		m.m_types.push_back(&type<mud::SpriteAtlas>());
		m.m_types.push_back(&type<mud::TextureAtlas>());
		{
			static Function f = { &namspc({}), "sinf", nullptr, _sinf_0, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "cosf", nullptr, _cosf_1, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "sin", nullptr, _sin_2, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({}), "cos", nullptr, _cos_3, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "add<float>", nullptr, mud_add_float__4, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "subtract<float>", nullptr, mud_subtract_float__5, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "multiply<float>", nullptr, mud_multiply_float__6, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "divide<float>", nullptr, mud_divide_float__7, { { "a", type<float>(),  }, { "b", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "nsinf", nullptr, mud_nsinf_8, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "ncosf", nullptr, mud_ncosf_9, { { "a", type<float>(),  } }, { &type<float>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "nsin", nullptr, mud_nsin_10, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "ncos", nullptr, mud_ncos_11, { { "a", type<double>(),  } }, { &type<double>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_rgba", nullptr, mud_to_rgba_12, { { "colour", type<mud::Colour>(),  } }, { &type<uint32_t>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_abgr", nullptr, mud_to_abgr_13, { { "colour", type<mud::Colour>(),  } }, { &type<uint32_t>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "from_rgba", nullptr, mud_from_rgba_14, { { "colour", type<uint32_t>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "from_abgr", nullptr, mud_from_abgr_15, { { "colour", type<uint32_t>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_linear", nullptr, mud_to_linear_16, { { "colour", type<mud::Colour>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_gamma", nullptr, mud_to_gamma_17, { { "colour", type<mud::Colour>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_srgb", nullptr, mud_to_srgb_18, { { "colour", type<mud::Colour>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "hsl_to_rgb", nullptr, mud_hsl_to_rgb_19, { { "h", type<float>(),  }, { "s", type<float>(),  }, { "l", type<float>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "rgb_to_hsl", nullptr, mud_rgb_to_hsl_20, { { "r", type<float>(),  }, { "g", type<float>(),  }, { "b", type<float>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "rgba_to_hsla", nullptr, mud_rgba_to_hsla_21, { { "colour", type<mud::Colour>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "hsla_to_rgba", nullptr, mud_hsla_to_rgba_22, { { "colour", type<mud::Colour>(),  } }, { &type<mud::Colour>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "look_dir", nullptr, mud_look_dir_23, { { "direction", type<mud::vec3>(),  }, { "forward", type<mud::vec3>(), Param::Default } }, { &type<mud::quat>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "look_at", nullptr, mud_look_at_24, { { "eye", type<mud::vec3>(),  }, { "target", type<mud::vec3>(),  }, { "forward", type<mud::vec3>(), Param::Default } }, { &type<mud::quat>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "add<mud::vec3>", nullptr, mud_add_mud_vec3__25, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "subtract<mud::vec3>", nullptr, mud_subtract_mud_vec3__26, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "multiply<mud::vec3>", nullptr, mud_multiply_mud_vec3__27, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "divide<mud::vec3>", nullptr, mud_divide_mud_vec3__28, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "grid", nullptr, mud_grid_29, { { "size", type<mud::uvec3>(),  }, { "output_coords", type<vector<mud::uvec3>>(), Param::Output } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "grid_center", nullptr, mud_grid_center_30, { { "coord", type<mud::uvec3>(),  }, { "cell_size", type<mud::vec3>(),  } }, { &type<mud::vec3>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "index_list", nullptr, mud_index_list_31, { { "size", type<uint32_t>(),  }, { "output_indices", type<vector<uint32_t>>(), Param::Output } }, g_qvoid };
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
