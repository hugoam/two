#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/type.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/geom.conv.h>
#endif

#include <geom/Api.h>

using namespace mud;

void mud_CatmullType__to_string(void* val, string& str) { str = g_enu[type<mud::CatmullType>().m_id]->name(uint32_t((*static_cast<mud::CatmullType*>(val)))); }
void mud_CatmullType__to_value(const string& str, void* val) { (*static_cast<mud::CatmullType*>(val)) = mud::CatmullType(g_enu[type<mud::CatmullType>().m_id]->value(str.c_str())); }
void mud_DrawMode__to_string(void* val, string& str) { str = g_enu[type<mud::DrawMode>().m_id]->name(uint32_t((*static_cast<mud::DrawMode*>(val)))); }
void mud_DrawMode__to_value(const string& str, void* val) { (*static_cast<mud::DrawMode*>(val)) = mud::DrawMode(g_enu[type<mud::DrawMode>().m_id]->value(str.c_str())); }
void mud_PrimitiveType__to_string(void* val, string& str) { str = g_enu[type<mud::PrimitiveType>().m_id]->name(uint32_t((*static_cast<mud::PrimitiveType*>(val)))); }
void mud_PrimitiveType__to_value(const string& str, void* val) { (*static_cast<mud::PrimitiveType*>(val)) = mud::PrimitiveType(g_enu[type<mud::PrimitiveType>().m_id]->value(str.c_str())); }
void mud_SymbolDetail__to_string(void* val, string& str) { str = g_enu[type<mud::SymbolDetail>().m_id]->name(uint32_t((*static_cast<mud::SymbolDetail*>(val)))); }
void mud_SymbolDetail__to_value(const string& str, void* val) { (*static_cast<mud::SymbolDetail*>(val)) = mud::SymbolDetail(g_enu[type<mud::SymbolDetail>().m_id]->value(str.c_str())); }
size_t stl_vector_mud_Circle__size(void* vec) { return (*static_cast<stl::vector<mud::Circle>*>(vec)).size(); }
void* stl_vector_mud_Circle__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Circle>*>(vec))[i]; }
void stl_vector_mud_Circle__push(void* vec) { (*static_cast<stl::vector<mud::Circle>*>(vec)).emplace_back(); }
void stl_vector_mud_Circle__add(void* vec, void* value) { (*static_cast<stl::vector<mud::Circle>*>(vec)).push_back(*static_cast<mud::Circle*>(value)); }
void stl_vector_mud_Circle__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Circle>*>(vec)), *static_cast<mud::Circle*>(value)); }
size_t stl_vector_mud_ivec4__size(void* vec) { return (*static_cast<stl::vector<mud::ivec4>*>(vec)).size(); }
void* stl_vector_mud_ivec4__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::ivec4>*>(vec))[i]; }
void stl_vector_mud_ivec4__push(void* vec) { (*static_cast<stl::vector<mud::ivec4>*>(vec)).emplace_back(); }
void stl_vector_mud_ivec4__add(void* vec, void* value) { (*static_cast<stl::vector<mud::ivec4>*>(vec)).push_back(*static_cast<mud::ivec4*>(value)); }
void stl_vector_mud_ivec4__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::ivec4>*>(vec)), *static_cast<mud::ivec4*>(value)); }
size_t stl_vector_mud_vec2__size(void* vec) { return (*static_cast<stl::vector<mud::vec2>*>(vec)).size(); }
void* stl_vector_mud_vec2__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::vec2>*>(vec))[i]; }
void stl_vector_mud_vec2__push(void* vec) { (*static_cast<stl::vector<mud::vec2>*>(vec)).emplace_back(); }
void stl_vector_mud_vec2__add(void* vec, void* value) { (*static_cast<stl::vector<mud::vec2>*>(vec)).push_back(*static_cast<mud::vec2*>(value)); }
void stl_vector_mud_vec2__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::vec2>*>(vec)), *static_cast<mud::vec2*>(value)); }
size_t stl_vector_mud_vec4__size(void* vec) { return (*static_cast<stl::vector<mud::vec4>*>(vec)).size(); }
void* stl_vector_mud_vec4__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::vec4>*>(vec))[i]; }
void stl_vector_mud_vec4__push(void* vec) { (*static_cast<stl::vector<mud::vec4>*>(vec)).emplace_back(); }
void stl_vector_mud_vec4__add(void* vec, void* value) { (*static_cast<stl::vector<mud::vec4>*>(vec)).push_back(*static_cast<mud::vec4*>(value)); }
void stl_vector_mud_vec4__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::vec4>*>(vec)), *static_cast<mud::vec4*>(value)); }
void mud_Aabb__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Aabb(  ); }
void mud_Aabb__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Aabb( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]) ); }
void mud_Aabb__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Aabb((*static_cast<mud::Aabb*>(other))); }
void mud_Curve2_point(void* object, span<void*> args, void*& result) { (*static_cast<mud::v2<float>*>(result)) = (*static_cast<mud::Curve2*>(object)).point(*static_cast<float*>(args[0])); }
void mud_Curve3_point(void* object, span<void*> args, void*& result) { (*static_cast<mud::v3<float>*>(result)) = (*static_cast<mud::Curve3*>(object)).point(*static_cast<float*>(args[0])); }
void mud_Face3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Face3(  ); }
void mud_Face3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Face3((*static_cast<mud::Face3*>(other))); }
void mud_MarchingCubes__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::MarchingCubes( *static_cast<uint32_t*>(args[0]) ); }
void mud_MarchingCubes_reset(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::MarchingCubes*>(object)).reset(); }
void mud_MarchingCubes_count(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<uint*>(result)) = (*static_cast<mud::MarchingCubes*>(object)).count(); }
void mud_MarchingCubes_direct(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MarchingCubes*>(object)).direct(*static_cast<mud::MeshAdapter*>(args[0])); }
void mud_MarchingCubes_render(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MarchingCubes*>(object)).render(*static_cast<mud::MeshPacker*>(args[0])); }
void mud_MeshAdapter__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MeshAdapter(  ); }
void mud_MeshAdapter__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MeshAdapter((*static_cast<mud::MeshAdapter*>(other))); }
void mud_MeshAdapter_rewind(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::MeshAdapter*>(object)).rewind(); }
void mud_MeshAdapter_copy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshAdapter*>(object)).copy(*static_cast<mud::MeshAdapter*>(args[0])); }
void mud_MeshAdapter_xcopy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshAdapter*>(object)).xcopy(*static_cast<mud::MeshAdapter*>(args[0]), *static_cast<mud::mat4*>(args[1])); }
void mud_MeshAdapter_next(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::MeshAdapter*>(object)).next(); }
void mud_MeshAdapter_position(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).position(*static_cast<mud::vec3*>(args[0])); }
void mud_MeshAdapter_position4(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).position4(*static_cast<mud::vec4*>(args[0])); }
void mud_MeshAdapter_normal(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).normal(*static_cast<mud::vec3*>(args[0])); }
void mud_MeshAdapter_colour(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).colour(*static_cast<mud::Colour*>(args[0])); }
void mud_MeshAdapter_tangent(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).tangent(*static_cast<mud::vec4*>(args[0])); }
void mud_MeshAdapter_bitangent(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).bitangent(*static_cast<mud::vec3*>(args[0])); }
void mud_MeshAdapter_uv0(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).uv0(*static_cast<mud::vec2*>(args[0])); }
void mud_MeshAdapter_uv1(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).uv1(*static_cast<mud::vec2*>(args[0])); }
void mud_MeshAdapter_joints(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).joints(*static_cast<uint32_t*>(args[0])); }
void mud_MeshAdapter_weights(void* object, span<void*> args, void*& result) { result = &(*static_cast<mud::MeshAdapter*>(object)).weights(*static_cast<mud::vec4*>(args[0])); }
void mud_MeshPacker__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::MeshPacker(  ); }
void mud_MeshPacker__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::MeshPacker((*static_cast<mud::MeshPacker*>(other))); }
void mud_MeshPacker_position(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).position(*static_cast<mud::vec3*>(args[0])); }
void mud_MeshPacker_normal(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).normal(*static_cast<mud::vec3*>(args[0])); }
void mud_MeshPacker_colour(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).colour(*static_cast<mud::Colour*>(args[0])); }
void mud_MeshPacker_tangent(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).tangent(*static_cast<mud::vec4*>(args[0])); }
void mud_MeshPacker_bitangent(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).bitangent(*static_cast<mud::vec3*>(args[0])); }
void mud_MeshPacker_uv0(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).uv0(*static_cast<mud::vec2*>(args[0])); }
void mud_MeshPacker_uv1(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).uv1(*static_cast<mud::vec2*>(args[0])); }
void mud_MeshPacker_bones(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).bones(*static_cast<mud::ivec4*>(args[0])); }
void mud_MeshPacker_weights(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).weights(*static_cast<mud::vec4*>(args[0])); }
void mud_MeshPacker_index(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).index(*static_cast<uint32_t*>(args[0])); }
void mud_MeshPacker_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::MeshPacker*>(object)).clear(); }
void mud_MeshPacker_pack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).pack(*static_cast<mud::MeshAdapter*>(args[0])); }
void mud_MeshPacker_xpack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).xpack(*static_cast<mud::MeshAdapter*>(args[0]), *static_cast<mud::mat4*>(args[1])); }
void mud_MeshPacker_unpack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::MeshPacker*>(object)).unpack(*static_cast<mud::MeshAdapter*>(args[0]), *static_cast<mud::mat4*>(args[1])); }
void mud_MeshPacker_gen_normals(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::MeshPacker*>(object)).gen_normals(); }
void mud_MeshPacker_gen_tangents(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<mud::MeshPacker*>(object)).gen_tangents(); }
void mud_Plane__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Plane(  ); }
void mud_Plane__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Plane((*static_cast<mud::Plane*>(other))); }
void mud_Plane3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Plane3(  ); }
void mud_Plane3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Plane3((*static_cast<mud::Plane3*>(other))); }
void mud_Ray__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Ray(  ); }
void mud_Ray__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Ray((*static_cast<mud::Ray*>(other))); }
void mud_Segment__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Segment(  ); }
void mud_Segment__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Segment((*static_cast<mud::Segment*>(other))); }
void* mud_Shape__get_type(void* object) { return &(*static_cast<mud::Shape*>(object)).m_type; }
void mud_ShapeVar__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ShapeVar(  ); }
void mud_ShapeVar__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ShapeVar( *static_cast<mud::Shape*>(args[0]) ); }
void* mud_ShapeVar__get_shape(void* object) { return &(*static_cast<mud::ShapeVar*>(object)).shape(); }
void mud_Symbol__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Symbol( *static_cast<mud::Colour*>(args[0]), *static_cast<mud::Colour*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<mud::SymbolDetail*>(args[4]) ); }
void mud_Symbol__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Symbol((*static_cast<mud::Symbol*>(other))); }
void mud_Arc__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Arc(  ); }
void mud_Arc__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Arc( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_Arc__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Arc((*static_cast<mud::Arc*>(other))); }
void mud_ArcLine__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ArcLine(  ); }
void mud_ArcLine__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ArcLine( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2]) ); }
void mud_ArcLine__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ArcLine( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<mud::vec3*>(args[3]) ); }
void mud_ArcLine__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ArcLine((*static_cast<mud::ArcLine*>(other))); }
void mud_Box__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Box(  ); }
void mud_Box__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Box((*static_cast<mud::Box*>(other))); }
void mud_Capsule__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Capsule(  ); }
void mud_Capsule__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Capsule( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2]) ); }
void mud_Capsule__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Capsule((*static_cast<mud::Capsule*>(other))); }
void mud_Circle__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Circle(  ); }
void mud_Circle__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Circle( *static_cast<float*>(args[0]), *static_cast<mud::Axis*>(args[1]) ); }
void mud_Circle__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Circle( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2]) ); }
void mud_Circle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Circle((*static_cast<mud::Circle*>(other))); }
void mud_ConvexHull__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::ConvexHull(  ); }
void mud_ConvexHull__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ConvexHull( *static_cast<stl::span<mud::vec3>*>(args[0]) ); }
void mud_ConvexHull__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::ConvexHull((*static_cast<mud::ConvexHull*>(other))); }
void mud_Cube__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Cube(  ); }
void mud_Cube__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Cube( *static_cast<mud::vec3*>(args[0]) ); }
void mud_Cube__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Cube( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]) ); }
void mud_Cube__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Cube((*static_cast<mud::Cube*>(other))); }
void mud_CurveBezierCubic__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveBezierCubic(  ); }
void mud_CurveBezierCubic__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveBezierCubic((*static_cast<mud::CurveBezierCubic*>(other))); }
void mud_CurveBezierCubic3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveBezierCubic3(  ); }
void mud_CurveBezierCubic3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveBezierCubic3((*static_cast<mud::CurveBezierCubic3*>(other))); }
void mud_CurveBezierQuadratic__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveBezierQuadratic(  ); }
void mud_CurveBezierQuadratic__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveBezierQuadratic((*static_cast<mud::CurveBezierQuadratic*>(other))); }
void mud_CurveBezierQuadratic3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveBezierQuadratic3(  ); }
void mud_CurveBezierQuadratic3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveBezierQuadratic3((*static_cast<mud::CurveBezierQuadratic3*>(other))); }
void mud_CurveCatmullRom3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveCatmullRom3(  ); }
void mud_CurveCatmullRom3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::CurveCatmullRom3( *static_cast<stl::vector<mud::vec3>*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<mud::CatmullType*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_CurveCatmullRom3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveCatmullRom3((*static_cast<mud::CurveCatmullRom3*>(other))); }
void mud_CurveCatmullRom3_add_point(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::CurveCatmullRom3*>(object)).add_point(*static_cast<mud::vec3*>(args[0])); }
void mud_CurveLine__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveLine(  ); }
void mud_CurveLine__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveLine((*static_cast<mud::CurveLine*>(other))); }
void mud_CurveLine3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveLine3(  ); }
void mud_CurveLine3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveLine3((*static_cast<mud::CurveLine3*>(other))); }
void mud_CurveSpline__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveSpline(  ); }
void mud_CurveSpline__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveSpline((*static_cast<mud::CurveSpline*>(other))); }
void mud_CurveSpline3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::CurveSpline3(  ); }
void mud_CurveSpline3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::CurveSpline3((*static_cast<mud::CurveSpline3*>(other))); }
void mud_Cylinder__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Cylinder(  ); }
void mud_Cylinder__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Cylinder( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2]) ); }
void mud_Cylinder__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Cylinder( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<mud::Axis*>(args[3]) ); }
void mud_Cylinder__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Cylinder((*static_cast<mud::Cylinder*>(other))); }
void mud_Ellipsis__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Ellipsis(  ); }
void mud_Ellipsis__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Ellipsis( *static_cast<mud::vec2*>(args[0]), *static_cast<mud::Axis*>(args[1]) ); }
void mud_Ellipsis__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Ellipsis((*static_cast<mud::Ellipsis*>(other))); }
void mud_Geometry__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Geometry(  ); }
void mud_Grid2__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Grid2(  ); }
void mud_Grid2__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Grid2( *static_cast<mud::vec2*>(args[0]), *static_cast<mud::vec2*>(args[1]) ); }
void mud_Grid2__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Grid2((*static_cast<mud::Grid2*>(other))); }
void mud_Grid3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Grid3(  ); }
void mud_Grid3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Grid3( *static_cast<mud::uvec2*>(args[0]), *static_cast<stl::span<mud::vec3>*>(args[1]) ); }
void mud_Grid3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Grid3((*static_cast<mud::Grid3*>(other))); }
void mud_Icosahedron__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Icosaedr(  ); }
void mud_Icosahedron__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Icosaedr( *static_cast<float*>(args[0]) ); }
void mud_Icosahedron__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Icosaedr( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Icosahedron__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Icosaedr((*static_cast<mud::Icosaedr*>(other))); }
void mud_Line__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Line(  ); }
void mud_Line__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Line( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]) ); }
void mud_Line__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Line((*static_cast<mud::Line*>(other))); }
void mud_Points__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Points(  ); }
void mud_Points__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Points( *static_cast<stl::span<mud::vec3>*>(args[0]) ); }
void mud_Points__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Points((*static_cast<mud::Points*>(other))); }
void mud_Poisson__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Poisson( *static_cast<mud::vec2*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Poisson_distribute(void* object, span<void*> args, void*& result) { (*static_cast<stl::vector<mud::vec3>*>(result)) = (*static_cast<mud::Poisson*>(object)).distribute(*static_cast<float*>(args[0])); }
void mud_Poisson_distribute_circles(void* object, span<void*> args, void*& result) { (*static_cast<stl::vector<mud::Circle>*>(result)) = (*static_cast<mud::Poisson*>(object)).distribute_circles(*static_cast<float*>(args[0])); }
void mud_Poisson_addPoint(void* object, span<void*> args, void*& result) { (*static_cast<bool*>(result)) = (*static_cast<mud::Poisson*>(object)).addPoint(*static_cast<float*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_Polygon__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Polygon(  ); }
void mud_Polygon__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Polygon( *static_cast<stl::span<mud::vec3>*>(args[0]) ); }
void mud_Polygon__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Polygon((*static_cast<mud::Polygon*>(other))); }
void mud_Quad__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Quad(  ); }
void mud_Quad__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Quad( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<mud::vec3*>(args[3]) ); }
void mud_Quad__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Quad((*static_cast<mud::Quad*>(other))); }
void mud_Rect__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Rect(  ); }
void mud_Rect__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Rect( *static_cast<mud::vec2*>(args[0]), *static_cast<mud::vec2*>(args[1]) ); }
void mud_Rect__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Rect( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_Rect__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Rect((*static_cast<mud::Rect*>(other))); }
void mud_Ring__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Ring(  ); }
void mud_Ring__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Ring( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_Ring__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Ring((*static_cast<mud::Ring*>(other))); }
void mud_Sphere__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Sphere(  ); }
void mud_Sphere__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Sphere( *static_cast<float*>(args[0]) ); }
void mud_Sphere__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Sphere( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Sphere__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Sphere((*static_cast<mud::Sphere*>(other))); }
void mud_SphereRing__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::SphereRing(  ); }
void mud_SphereRing__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::SphereRing( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_SphereRing__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::SphereRing((*static_cast<mud::SphereRing*>(other))); }
void mud_Spheroid__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Spheroid(  ); }
void mud_Spheroid__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Spheroid( *static_cast<float*>(args[0]) ); }
void mud_Spheroid__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Spheroid( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Spheroid__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Spheroid((*static_cast<mud::Spheroid*>(other))); }
void mud_Torus__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Torus(  ); }
void mud_Torus__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Torus( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2]) ); }
void mud_Torus__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Torus( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<mud::Axis*>(args[3]) ); }
void mud_Torus__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Torus((*static_cast<mud::Torus*>(other))); }
void mud_TorusKnot__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::TorusKnot(  ); }
void mud_TorusKnot__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::TorusKnot( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_TorusKnot__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::TorusKnot( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_TorusKnot__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::TorusKnot((*static_cast<mud::TorusKnot*>(other))); }
void mud_Triangle__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Triangle(  ); }
void mud_Triangle__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Triangle( *static_cast<mud::vec2*>(args[0]) ); }
void mud_Triangle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Triangle((*static_cast<mud::Triangle*>(other))); }
void mud_to_ray_0(span<void*> args, void*& result) { (*static_cast<mud::Ray*>(result)) = mud::to_ray(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<float*>(args[2])); }
void mud_to_segment_1(span<void*> args, void*& result) { (*static_cast<mud::Segment*>(result)) = mud::to_segment(*static_cast<mud::Ray*>(args[0])); }
void mud_to_ray_2(span<void*> args, void*& result) { (*static_cast<mud::Ray*>(result)) = mud::to_ray(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<float*>(args[2])); }
void mud_to_segment_3(span<void*> args, void*& result) { (*static_cast<mud::Segment*>(result)) = mud::to_segment(*static_cast<mud::Ray*>(args[0])); }
void mud_distribute_poisson_4(span<void*> args, void*& result) { (*static_cast<stl::vector<mud::vec3>*>(result)) = mud::distribute_poisson(*static_cast<mud::vec2*>(args[0]), *static_cast<float*>(args[1])); }
void mud_add_ball_5(span<void*> args, void*& result) { UNUSED(result);  mud::add_ball(*static_cast<mud::MarchingCubes*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3])); }
void mud_add_planeX_6(span<void*> args, void*& result) { UNUSED(result);  mud::add_planeX(*static_cast<mud::MarchingCubes*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_add_planeY_7(span<void*> args, void*& result) { UNUSED(result);  mud::add_planeY(*static_cast<mud::MarchingCubes*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void mud_add_planeZ_8(span<void*> args, void*& result) { UNUSED(result);  mud::add_planeZ(*static_cast<mud::MarchingCubes*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }

namespace mud
{
	void mud_geom_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::CatmullType>();
		static Meta meta = { t, &namspc({ "mud" }), "CatmullType", sizeof(mud::CatmullType), TypeClass::Enum };
		static cstring ids[] = { "Centripetal", "Chordal", "CatmullRom" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::CatmullType vars[] = { mud::CatmullType::Centripetal, mud::CatmullType::Chordal, mud::CatmullType::CatmullRom};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_CatmullType__to_string,
		                           mud_CatmullType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::DrawMode>();
		static Meta meta = { t, &namspc({ "mud" }), "DrawMode", sizeof(mud::DrawMode), TypeClass::Enum };
		static cstring ids[] = { "OUTLINE", "PLAIN" };
		static uint32_t values[] = { 0, 1 };
		static mud::DrawMode vars[] = { mud::OUTLINE, mud::PLAIN};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { mud_DrawMode__to_string,
		                           mud_DrawMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::PrimitiveType>();
		static Meta meta = { t, &namspc({ "mud" }), "PrimitiveType", sizeof(mud::PrimitiveType), TypeClass::Enum };
		static cstring ids[] = { "Points", "Lines", "LineStrip", "Triangles", "TriangleStrip", "TriangleFan", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static mud::PrimitiveType vars[] = { mud::PrimitiveType::Points, mud::PrimitiveType::Lines, mud::PrimitiveType::LineStrip, mud::PrimitiveType::Triangles, mud::PrimitiveType::TriangleStrip, mud::PrimitiveType::TriangleFan, mud::PrimitiveType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_PrimitiveType__to_string,
		                           mud_PrimitiveType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<mud::SymbolDetail>();
		static Meta meta = { t, &namspc({ "mud" }), "SymbolDetail", sizeof(mud::SymbolDetail), TypeClass::Enum };
		static cstring ids[] = { "Lowest", "Low", "Medium", "High", "Highest" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::SymbolDetail vars[] = { mud::SymbolDetail::Lowest, mud::SymbolDetail::Low, mud::SymbolDetail::Medium, mud::SymbolDetail::High, mud::SymbolDetail::Highest};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_SymbolDetail__to_string,
		                           mud_SymbolDetail__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::vector<mud::Circle>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Circle>", sizeof(stl::vector<mud::Circle>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Circle>(),
		                             stl_vector_mud_Circle__size,
		                             stl_vector_mud_Circle__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Circle__push,
		                             stl_vector_mud_Circle__add,
		                             stl_vector_mud_Circle__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::ivec4>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::ivec4>", sizeof(stl::vector<mud::ivec4>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::ivec4>(),
		                             stl_vector_mud_ivec4__size,
		                             stl_vector_mud_ivec4__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_ivec4__push,
		                             stl_vector_mud_ivec4__add,
		                             stl_vector_mud_ivec4__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::vec2>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::vec2>", sizeof(stl::vector<mud::vec2>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::vec2>(),
		                             stl_vector_mud_vec2__size,
		                             stl_vector_mud_vec2__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_vec2__push,
		                             stl_vector_mud_vec2__add,
		                             stl_vector_mud_vec2__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::vec4>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::vec4>", sizeof(stl::vector<mud::vec4>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::vec4>(),
		                             stl_vector_mud_vec4__size,
		                             stl_vector_mud_vec4__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_vec4__push,
		                             stl_vector_mud_vec4__add,
		                             stl_vector_mud_vec4__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// mud::Aabb
	{
		Type& t = type<mud::Aabb>();
		static Meta meta = { t, &namspc({ "mud" }), "Aabb", sizeof(mud::Aabb), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Aabb__construct_0, {} },
			{ t, mud_Aabb__construct_1, { { "center", type<mud::vec3>(),  }, { "extents", type<mud::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Aabb__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Aabb, m_center), type<mud::vec3>(), "center", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Aabb, m_extents), type<mud::vec3>(), "extents", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Aabb, m_empty), type<bool>(), "empty", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Curve2
	{
		Type& t = type<mud::Curve2>();
		static Meta meta = { t, &namspc({ "mud" }), "Curve2", sizeof(mud::Curve2), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "point", Address(), mud_Curve2_point, { { "t", type<float>(),  } }, { &type<mud::vec2>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::Curve3
	{
		Type& t = type<mud::Curve3>();
		static Meta meta = { t, &namspc({ "mud" }), "Curve3", sizeof(mud::Curve3), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "point", Address(), mud_Curve3_point, { { "t", type<float>(),  } }, { &type<mud::vec3>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// mud::Distribution
	{
		Type& t = type<mud::Distribution>();
		static Meta meta = { t, &namspc({ "mud" }), "Distribution", sizeof(mud::Distribution), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Face3
	{
		Type& t = type<mud::Face3>();
		static Meta meta = { t, &namspc({ "mud" }), "Face3", sizeof(mud::Face3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Face3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Face3__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::MarchingCubes
	{
		Type& t = type<mud::MarchingCubes>();
		static Meta meta = { t, &namspc({ "mud" }), "MarchingCubes", sizeof(mud::MarchingCubes), TypeClass::Object };
		// bases
		// defaults
		static float isolation_default = 80.f;
		static uint32_t subdiv_default = 32;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MarchingCubes__construct_0, { { "resolution", type<uint32_t>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::MarchingCubes, m_isolation), type<float>(), "isolation", &isolation_default, Member::Value, nullptr },
			{ t, offsetof(mud::MarchingCubes, m_subdiv), type<uint32_t>(), "subdiv", &subdiv_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "reset", Address(), mud_MarchingCubes_reset, {}, g_qvoid },
			{ t, "count", Address(), mud_MarchingCubes_count, {}, { &type<uint32_t>(), QualType::None } },
			{ t, "direct", Address(), mud_MarchingCubes_direct, { { "output", type<mud::MeshAdapter>(), Param::Output } }, g_qvoid },
			{ t, "render", Address(), mud_MarchingCubes_render, { { "output", type<mud::MeshPacker>(), Param::Output } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::MeshAdapter
	{
		Type& t = type<mud::MeshAdapter>();
		static Meta meta = { t, &namspc({ "mud" }), "MeshAdapter", sizeof(mud::MeshAdapter), TypeClass::Struct };
		// bases
		// defaults
		static uint32_t vertex_format_default = 0;
		static bool index32_default = false;
		static uint32_t vertex_stride_default = 0;
		static uint32_t index_stride_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MeshAdapter__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MeshAdapter__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MeshAdapter, m_vertex_format), type<uint32_t>(), "vertex_format", &vertex_format_default, Member::Value, nullptr },
			{ t, offsetof(mud::MeshAdapter, m_index32), type<bool>(), "index32", &index32_default, Member::Value, nullptr },
			{ t, offsetof(mud::MeshAdapter, m_vertex_stride), type<uint32_t>(), "vertex_stride", &vertex_stride_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "rewind", Address(), mud_MeshAdapter_rewind, {}, g_qvoid },
			{ t, "copy", Address(), mud_MeshAdapter_copy, { { "dest", type<mud::MeshAdapter>(),  } }, g_qvoid },
			{ t, "xcopy", Address(), mud_MeshAdapter_xcopy, { { "dest", type<mud::MeshAdapter>(),  }, { "transform", type<mud::mat4>(),  } }, g_qvoid },
			{ t, "next", Address(), mud_MeshAdapter_next, {}, g_qvoid },
			{ t, "position", Address(), mud_MeshAdapter_position, { { "p", type<mud::vec3>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "position4", Address(), mud_MeshAdapter_position4, { { "p", type<mud::vec4>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "normal", Address(), mud_MeshAdapter_normal, { { "n", type<mud::vec3>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "colour", Address(), mud_MeshAdapter_colour, { { "c", type<mud::Colour>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "tangent", Address(), mud_MeshAdapter_tangent, { { "t", type<mud::vec4>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "bitangent", Address(), mud_MeshAdapter_bitangent, { { "b", type<mud::vec3>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "uv0", Address(), mud_MeshAdapter_uv0, { { "uv", type<mud::vec2>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "uv1", Address(), mud_MeshAdapter_uv1, { { "uv", type<mud::vec2>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "joints", Address(), mud_MeshAdapter_joints, { { "j", type<uint32_t>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } },
			{ t, "weights", Address(), mud_MeshAdapter_weights, { { "w", type<mud::vec4>(),  } }, { &type<mud::MeshAdapter>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// mud::MeshPacker
	{
		Type& t = type<mud::MeshPacker>();
		static Meta meta = { t, &namspc({ "mud" }), "MeshPacker", sizeof(mud::MeshPacker), TypeClass::Struct };
		// bases
		// defaults
		static mud::PrimitiveType primitive_default = mud::PrimitiveType::Triangles;
		static bool quantize_default = false;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MeshPacker__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MeshPacker__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::MeshPacker, m_primitive), type<mud::PrimitiveType>(), "primitive", &primitive_default, Member::Value, nullptr },
			{ t, offsetof(mud::MeshPacker, m_positions), type<stl::vector<mud::vec3>>(), "positions", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_normals), type<stl::vector<mud::vec3>>(), "normals", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_colours), type<stl::vector<mud::Colour>>(), "colours", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_tangents), type<stl::vector<mud::vec4>>(), "tangents", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_bitangents), type<stl::vector<mud::vec3>>(), "bitangents", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_uv0s), type<stl::vector<mud::vec2>>(), "uv0s", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_uv1s), type<stl::vector<mud::vec2>>(), "uv1s", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_bones), type<stl::vector<mud::ivec4>>(), "bones", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_weights), type<stl::vector<mud::vec4>>(), "weights", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_indices), type<stl::vector<uint32_t>>(), "indices", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::MeshPacker, m_quantize), type<bool>(), "quantize", &quantize_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "position", Address(), mud_MeshPacker_position, { { "p", type<mud::vec3>(),  } }, g_qvoid },
			{ t, "normal", Address(), mud_MeshPacker_normal, { { "n", type<mud::vec3>(),  } }, g_qvoid },
			{ t, "colour", Address(), mud_MeshPacker_colour, { { "c", type<mud::Colour>(),  } }, g_qvoid },
			{ t, "tangent", Address(), mud_MeshPacker_tangent, { { "t", type<mud::vec4>(),  } }, g_qvoid },
			{ t, "bitangent", Address(), mud_MeshPacker_bitangent, { { "b", type<mud::vec3>(),  } }, g_qvoid },
			{ t, "uv0", Address(), mud_MeshPacker_uv0, { { "uv", type<mud::vec2>(),  } }, g_qvoid },
			{ t, "uv1", Address(), mud_MeshPacker_uv1, { { "uv", type<mud::vec2>(),  } }, g_qvoid },
			{ t, "bones", Address(), mud_MeshPacker_bones, { { "j", type<mud::ivec4>(),  } }, g_qvoid },
			{ t, "weights", Address(), mud_MeshPacker_weights, { { "w", type<mud::vec4>(),  } }, g_qvoid },
			{ t, "index", Address(), mud_MeshPacker_index, { { "i", type<uint32_t>(),  } }, g_qvoid },
			{ t, "clear", Address(), mud_MeshPacker_clear, {}, g_qvoid },
			{ t, "pack", Address(), mud_MeshPacker_pack, { { "writer", type<mud::MeshAdapter>(),  } }, g_qvoid },
			{ t, "xpack", Address(), mud_MeshPacker_xpack, { { "writer", type<mud::MeshAdapter>(),  }, { "transform", type<mud::mat4>(),  } }, g_qvoid },
			{ t, "unpack", Address(), mud_MeshPacker_unpack, { { "reader", type<mud::MeshAdapter>(),  }, { "transform", type<mud::mat4>(),  } }, g_qvoid },
			{ t, "generate_normals", Address(), mud_MeshPacker_gen_normals, {}, g_qvoid },
			{ t, "generate_tangents", Address(), mud_MeshPacker_gen_tangents, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// mud::Plane
	{
		Type& t = type<mud::Plane>();
		static Meta meta = { t, &namspc({ "mud" }), "Plane", sizeof(mud::Plane), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Plane__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Plane__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Plane, m_normal), type<mud::vec3>(), "normal", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Plane, m_distance), type<float>(), "distance", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Plane3
	{
		Type& t = type<mud::Plane3>();
		static Meta meta = { t, &namspc({ "mud" }), "Plane3", sizeof(mud::Plane3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Plane3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Plane3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Plane3, m_origin), type<mud::vec3>(), "origin", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Plane3, m_a), type<mud::vec3>(), "a", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Plane3, m_b), type<mud::vec3>(), "b", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Ray
	{
		Type& t = type<mud::Ray>();
		static Meta meta = { t, &namspc({ "mud" }), "Ray", sizeof(mud::Ray), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Ray__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Ray__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Ray, m_start), type<mud::vec3>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Ray, m_end), type<mud::vec3>(), "end", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Ray, m_dir), type<mud::vec3>(), "dir", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Ray, m_inv_dir), type<mud::vec3>(), "inv_dir", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Segment
	{
		Type& t = type<mud::Segment>();
		static Meta meta = { t, &namspc({ "mud" }), "Segment", sizeof(mud::Segment), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Segment__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Segment__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Segment, m_start), type<mud::vec3>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Segment, m_end), type<mud::vec3>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Shape
	{
		Type& t = type<mud::Shape>();
		static Meta meta = { t, &namspc({ "mud" }), "Shape", sizeof(mud::Shape), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Shape__get_type }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::ShapeVar
	{
		Type& t = type<mud::ShapeVar>();
		static Meta meta = { t, &namspc({ "mud" }), "ShapeVar", sizeof(mud::ShapeVar), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ShapeVar__construct_0, {} },
			{ t, mud_ShapeVar__construct_1, { { "shape", type<mud::Shape>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Shape>(), "shape", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_ShapeVar__get_shape }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, {}, {}, };
	}
	// mud::Symbol
	{
		Type& t = type<mud::Symbol>();
		static Meta meta = { t, &namspc({ "mud" }), "Symbol", sizeof(mud::Symbol), TypeClass::Struct };
		// bases
		// defaults
		static const char* image_default = nullptr;
		static mud::Image256* image256_default = nullptr;
		static const char* program_default = nullptr;
		static mud::Colour construct_0_fill_default = mud::Colour::White;
		static mud::Colour construct_0_outline_default = mud::Colour::None;
		static bool construct_0_overlay_default = false;
		static bool construct_0_double_sided_default = false;
		static mud::SymbolDetail construct_0_detail_default = mud::SymbolDetail::Medium;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Symbol__construct_0, { { "fill", type<mud::Colour>(), Param::Default, &construct_0_fill_default }, { "outline", type<mud::Colour>(), Param::Default, &construct_0_outline_default }, { "overlay", type<bool>(), Param::Default, &construct_0_overlay_default }, { "double_sided", type<bool>(), Param::Default, &construct_0_double_sided_default }, { "detail", type<mud::SymbolDetail>(), Param::Default, &construct_0_detail_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Symbol__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Symbol, m_outline), type<mud::Colour>(), "outline", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Symbol, m_fill), type<mud::Colour>(), "fill", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Symbol, m_overlay), type<bool>(), "overlay", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Symbol, m_double_sided), type<bool>(), "double_sided", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Symbol, m_detail), type<mud::SymbolDetail>(), "detail", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Symbol, m_image), type<const char*>(), "image", image_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Symbol, m_image256), type<mud::Image256>(), "image256", image256_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Symbol, m_program), type<const char*>(), "program", program_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Arc
	{
		Type& t = type<mud::Arc>();
		static Meta meta = { t, &namspc({ "mud" }), "Arc", sizeof(mud::Arc), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Arc, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float start_default = 0.f;
		static float end_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Arc__construct_0, {} },
			{ t, mud_Arc__construct_1, { { "radius", type<float>(),  }, { "start", type<float>(),  }, { "end", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Arc__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Arc, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Arc, m_start), type<float>(), "start", &start_default, Member::Value, nullptr },
			{ t, offsetof(mud::Arc, m_end), type<float>(), "end", &end_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ArcLine
	{
		Type& t = type<mud::ArcLine>();
		static Meta meta = { t, &namspc({ "mud" }), "ArcLine", sizeof(mud::ArcLine), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::ArcLine, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ArcLine__construct_0, {} },
			{ t, mud_ArcLine__construct_1, { { "start", type<mud::vec3>(),  }, { "middle", type<mud::vec3>(),  }, { "end", type<mud::vec3>(),  } } },
			{ t, mud_ArcLine__construct_2, { { "center", type<mud::vec3>(),  }, { "start", type<mud::vec3>(),  }, { "middle", type<mud::vec3>(),  }, { "end", type<mud::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ArcLine__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ArcLine, m_start), type<mud::vec3>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ArcLine, m_middle), type<mud::vec3>(), "middle", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ArcLine, m_end), type<mud::vec3>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Box
	{
		Type& t = type<mud::Box>();
		static Meta meta = { t, &namspc({ "mud" }), "Box", sizeof(mud::Box), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Box, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Box__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Box__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Capsule
	{
		Type& t = type<mud::Capsule>();
		static Meta meta = { t, &namspc({ "mud" }), "Capsule", sizeof(mud::Capsule), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Capsule, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float height_default = 2.f;
		static mud::Axis axis_default = mud::Axis::X;
		static mud::Axis construct_1_axis_default = mud::Axis::X;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Capsule__construct_0, {} },
			{ t, mud_Capsule__construct_1, { { "radius", type<float>(),  }, { "height", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default, &construct_1_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Capsule__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Capsule, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Capsule, m_height), type<float>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(mud::Capsule, m_axis), type<mud::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Circle
	{
		Type& t = type<mud::Circle>();
		static Meta meta = { t, &namspc({ "mud" }), "Circle", sizeof(mud::Circle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Circle, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static mud::Axis axis_default = mud::Axis::X;
		static mud::Axis construct_1_axis_default = mud::Axis::Y;
		static mud::Axis construct_2_axis_default = mud::Axis::Y;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Circle__construct_0, {} },
			{ t, mud_Circle__construct_1, { { "radius", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default, &construct_1_axis_default } } },
			{ t, mud_Circle__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default, &construct_2_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Circle__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Circle, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Circle, m_axis), type<mud::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::ConvexHull
	{
		Type& t = type<mud::ConvexHull>();
		static Meta meta = { t, &namspc({ "mud" }), "ConvexHull", sizeof(mud::ConvexHull), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::ConvexHull, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ConvexHull__construct_0, {} },
			{ t, mud_ConvexHull__construct_1, { { "vertices", type<stl::span<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ConvexHull__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ConvexHull, m_vertices), type<stl::vector<mud::vec3>>(), "vertices", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Cube
	{
		Type& t = type<mud::Cube>();
		static Meta meta = { t, &namspc({ "mud" }), "Cube", sizeof(mud::Cube), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Cube, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Cube__construct_0, {} },
			{ t, mud_Cube__construct_1, { { "extents", type<mud::vec3>(),  } } },
			{ t, mud_Cube__construct_2, { { "center", type<mud::vec3>(),  }, { "extents", type<mud::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Cube__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Cube, m_extents), type<mud::vec3>(), "extents", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CurveBezierCubic
	{
		Type& t = type<mud::CurveBezierCubic>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveBezierCubic", sizeof(mud::CurveBezierCubic), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve2>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveBezierCubic, mud::Curve2>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveBezierCubic__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveBezierCubic__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveBezierCubic, v0), type<mud::vec2>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierCubic, v1), type<mud::vec2>(), "v1", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierCubic, v2), type<mud::vec2>(), "v2", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierCubic, v3), type<mud::vec2>(), "v3", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CurveBezierCubic3
	{
		Type& t = type<mud::CurveBezierCubic3>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveBezierCubic3", sizeof(mud::CurveBezierCubic3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve3>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveBezierCubic3, mud::Curve3>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveBezierCubic3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveBezierCubic3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveBezierCubic3, v0), type<mud::vec3>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierCubic3, v1), type<mud::vec3>(), "v1", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierCubic3, v2), type<mud::vec3>(), "v2", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierCubic3, v3), type<mud::vec3>(), "v3", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CurveBezierQuadratic
	{
		Type& t = type<mud::CurveBezierQuadratic>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveBezierQuadratic", sizeof(mud::CurveBezierQuadratic), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve2>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveBezierQuadratic, mud::Curve2>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveBezierQuadratic__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveBezierQuadratic__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveBezierQuadratic, v0), type<mud::vec2>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierQuadratic, v1), type<mud::vec2>(), "v1", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierQuadratic, v2), type<mud::vec2>(), "v2", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CurveBezierQuadratic3
	{
		Type& t = type<mud::CurveBezierQuadratic3>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveBezierQuadratic3", sizeof(mud::CurveBezierQuadratic3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve3>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveBezierQuadratic3, mud::Curve3>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveBezierQuadratic3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveBezierQuadratic3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveBezierQuadratic3, v0), type<mud::vec3>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierQuadratic3, v1), type<mud::vec3>(), "v1", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveBezierQuadratic3, v2), type<mud::vec3>(), "v2", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CurveCatmullRom3
	{
		Type& t = type<mud::CurveCatmullRom3>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveCatmullRom3", sizeof(mud::CurveCatmullRom3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve3>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveCatmullRom3, mud::Curve3>() };
		// defaults
		static stl::vector<mud::vec3> points_default = {};
		static bool closed_default = false;
		static mud::CatmullType curve_type_default = mud::CatmullType::Centripetal;
		static float tension_default = 0.5f;
		static bool construct_1_closed_default = false;
		static mud::CatmullType construct_1_curve_type_default = mud::CatmullType::Centripetal;
		static float construct_1_tension_default = 0.5f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveCatmullRom3__construct_0, {} },
			{ t, mud_CurveCatmullRom3__construct_1, { { "points", type<stl::vector<mud::vec3>>(),  }, { "closed", type<bool>(), Param::Default, &construct_1_closed_default }, { "curve_type", type<mud::CatmullType>(), Param::Default, &construct_1_curve_type_default }, { "tension", type<float>(), Param::Default, &construct_1_tension_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveCatmullRom3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveCatmullRom3, m_points), type<stl::vector<mud::vec3>>(), "points", &points_default, Member::NonMutable, nullptr },
			{ t, offsetof(mud::CurveCatmullRom3, m_closed), type<bool>(), "closed", &closed_default, Member::Value, nullptr },
			{ t, offsetof(mud::CurveCatmullRom3, m_curve_type), type<mud::CatmullType>(), "curve_type", &curve_type_default, Member::Value, nullptr },
			{ t, offsetof(mud::CurveCatmullRom3, m_tension), type<float>(), "tension", &tension_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "add_point", Address(), mud_CurveCatmullRom3_add_point, { { "point", type<mud::vec3>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, methods, {}, };
	}
	// mud::CurveLine
	{
		Type& t = type<mud::CurveLine>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveLine", sizeof(mud::CurveLine), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve2>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveLine, mud::Curve2>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveLine__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveLine__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveLine, v0), type<mud::vec2>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveLine, v1), type<mud::vec2>(), "v1", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CurveLine3
	{
		Type& t = type<mud::CurveLine3>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveLine3", sizeof(mud::CurveLine3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve3>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveLine3, mud::Curve3>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveLine3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveLine3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveLine3, v0), type<mud::vec3>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::CurveLine3, v1), type<mud::vec3>(), "v1", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CurveSpline
	{
		Type& t = type<mud::CurveSpline>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveSpline", sizeof(mud::CurveSpline), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve2>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveSpline, mud::Curve2>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveSpline__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveSpline__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveSpline, m_points), type<stl::vector<mud::vec2>>(), "points", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::CurveSpline3
	{
		Type& t = type<mud::CurveSpline3>();
		static Meta meta = { t, &namspc({ "mud" }), "CurveSpline3", sizeof(mud::CurveSpline3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Curve3>() };
		static size_t bases_offsets[] = { base_offset<mud::CurveSpline3, mud::Curve3>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_CurveSpline3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_CurveSpline3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::CurveSpline3, m_points), type<stl::vector<mud::vec3>>(), "points", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Cylinder
	{
		Type& t = type<mud::Cylinder>();
		static Meta meta = { t, &namspc({ "mud" }), "Cylinder", sizeof(mud::Cylinder), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Cylinder, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float height_default = 2.f;
		static mud::Axis axis_default = mud::Axis::X;
		static mud::Axis construct_1_axis_default = mud::Axis::X;
		static mud::Axis construct_2_axis_default = mud::Axis::X;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Cylinder__construct_0, {} },
			{ t, mud_Cylinder__construct_1, { { "radius", type<float>(),  }, { "height", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default, &construct_1_axis_default } } },
			{ t, mud_Cylinder__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  }, { "height", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default, &construct_2_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Cylinder__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Cylinder, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Cylinder, m_height), type<float>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(mud::Cylinder, m_axis), type<mud::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Ellipsis
	{
		Type& t = type<mud::Ellipsis>();
		static Meta meta = { t, &namspc({ "mud" }), "Ellipsis", sizeof(mud::Ellipsis), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Ellipsis, mud::Shape>() };
		// defaults
		static mud::Axis axis_default = mud::Axis::Y;
		static mud::Axis construct_1_axis_default = mud::Axis::Y;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Ellipsis__construct_0, {} },
			{ t, mud_Ellipsis__construct_1, { { "radius", type<mud::vec2>(),  }, { "axis", type<mud::Axis>(), Param::Default, &construct_1_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Ellipsis__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Ellipsis, m_radius), type<mud::vec2>(), "radius", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Ellipsis, m_axis), type<mud::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Geometry
	{
		Type& t = type<mud::Geometry>();
		static Meta meta = { t, &namspc({ "mud" }), "Geometry", sizeof(mud::Geometry), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Geometry, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Geometry__construct_0, {} }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::Grid2
	{
		Type& t = type<mud::Grid2>();
		static Meta meta = { t, &namspc({ "mud" }), "Grid2", sizeof(mud::Grid2), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Grid2, mud::Shape>() };
		// defaults
		static mud::vec2 construct_1_space_default = vec2(1.f);
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Grid2__construct_0, {} },
			{ t, mud_Grid2__construct_1, { { "size", type<mud::vec2>(),  }, { "space", type<mud::vec2>(), Param::Default, &construct_1_space_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Grid2__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Grid2, m_size), type<mud::vec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Grid2, m_space), type<mud::vec2>(), "space", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Grid3
	{
		Type& t = type<mud::Grid3>();
		static Meta meta = { t, &namspc({ "mud" }), "Grid3", sizeof(mud::Grid3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Grid3, mud::Shape>() };
		// defaults
		static stl::span<mud::vec3> construct_1_points_default = {};
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Grid3__construct_0, {} },
			{ t, mud_Grid3__construct_1, { { "size", type<mud::uvec2>(),  }, { "points", type<stl::span<mud::vec3>>(), Param::Default, &construct_1_points_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Grid3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Grid3, m_size), type<mud::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Grid3, m_points), type<stl::vector<mud::vec3>>(), "points", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Icosaedr
	{
		Type& t = type<mud::Icosaedr>();
		static Meta meta = { t, &namspc({ "mud" }), "Icosaedr", sizeof(mud::Icosaedr), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Icosaedr, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Icosahedron__construct_0, {} },
			{ t, mud_Icosahedron__construct_1, { { "radius", type<float>(),  } } },
			{ t, mud_Icosahedron__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Icosahedron__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Icosaedr, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Line
	{
		Type& t = type<mud::Line>();
		static Meta meta = { t, &namspc({ "mud" }), "Line", sizeof(mud::Line), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Line, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Line__construct_0, {} },
			{ t, mud_Line__construct_1, { { "start", type<mud::vec3>(),  }, { "end", type<mud::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Line__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Line, m_start), type<mud::vec3>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Line, m_end), type<mud::vec3>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Points
	{
		Type& t = type<mud::Points>();
		static Meta meta = { t, &namspc({ "mud" }), "Points", sizeof(mud::Points), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Points, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Points__construct_0, {} },
			{ t, mud_Points__construct_1, { { "points", type<stl::span<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Points__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Points, m_points), type<stl::vector<mud::vec3>>(), "points", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Poisson
	{
		Type& t = type<mud::Poisson>();
		static Meta meta = { t, &namspc({ "mud" }), "Poisson", sizeof(mud::Poisson), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Distribution>() };
		static size_t bases_offsets[] = { base_offset<mud::Poisson, mud::Distribution>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Poisson__construct_0, { { "size", type<mud::vec2>(),  }, { "maxRadius", type<float>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "distribute", Address(), mud_Poisson_distribute, { { "radius", type<float>(),  } }, { &type<stl::vector<mud::vec3>>(), QualType::None } },
			{ t, "distribute_circles", Address(), mud_Poisson_distribute_circles, { { "radius", type<float>(),  } }, { &type<stl::vector<mud::Circle>>(), QualType::None } },
			{ t, "addPoint", Address(), mud_Poisson_addPoint, { { "radius", type<float>(),  }, { "point", type<mud::vec3>(),  } }, { &type<bool>(), QualType::None } }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, methods, {}, };
	}
	// mud::Polygon
	{
		Type& t = type<mud::Polygon>();
		static Meta meta = { t, &namspc({ "mud" }), "Polygon", sizeof(mud::Polygon), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Polygon, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Polygon__construct_0, {} },
			{ t, mud_Polygon__construct_1, { { "vertices", type<stl::span<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Polygon__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Quad
	{
		Type& t = type<mud::Quad>();
		static Meta meta = { t, &namspc({ "mud" }), "Quad", sizeof(mud::Quad), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Quad, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Quad__construct_0, {} },
			{ t, mud_Quad__construct_1, { { "a", type<mud::vec3>(),  }, { "b", type<mud::vec3>(),  }, { "c", type<mud::vec3>(),  }, { "d", type<mud::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Quad__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Rect
	{
		Type& t = type<mud::Rect>();
		static Meta meta = { t, &namspc({ "mud" }), "Rect", sizeof(mud::Rect), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Rect, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Rect__construct_0, {} },
			{ t, mud_Rect__construct_1, { { "position", type<mud::vec2>(),  }, { "size", type<mud::vec2>(),  } } },
			{ t, mud_Rect__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "w", type<float>(),  }, { "h", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Rect__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Rect, m_position), type<mud::vec2>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Rect, m_size), type<mud::vec2>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Ring
	{
		Type& t = type<mud::Ring>();
		static Meta meta = { t, &namspc({ "mud" }), "Ring", sizeof(mud::Ring), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Ring, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float min_default = 0.f;
		static float max_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Ring__construct_0, {} },
			{ t, mud_Ring__construct_1, { { "radius", type<float>(),  }, { "min", type<float>(),  }, { "max", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Ring__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Ring, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Ring, m_min), type<float>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(mud::Ring, m_max), type<float>(), "max", &max_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Sphere
	{
		Type& t = type<mud::Sphere>();
		static Meta meta = { t, &namspc({ "mud" }), "Sphere", sizeof(mud::Sphere), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Sphere, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Sphere__construct_0, {} },
			{ t, mud_Sphere__construct_1, { { "radius", type<float>(),  } } },
			{ t, mud_Sphere__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Sphere__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Sphere, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::SphereRing
	{
		Type& t = type<mud::SphereRing>();
		static Meta meta = { t, &namspc({ "mud" }), "SphereRing", sizeof(mud::SphereRing), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::SphereRing, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float min_default = -1.f;
		static float max_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_SphereRing__construct_0, {} },
			{ t, mud_SphereRing__construct_1, { { "radius", type<float>(),  }, { "min", type<float>(),  }, { "max", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_SphereRing__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::SphereRing, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::SphereRing, m_min), type<float>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(mud::SphereRing, m_max), type<float>(), "max", &max_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Spheroid
	{
		Type& t = type<mud::Spheroid>();
		static Meta meta = { t, &namspc({ "mud" }), "Spheroid", sizeof(mud::Spheroid), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Spheroid, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Spheroid__construct_0, {} },
			{ t, mud_Spheroid__construct_1, { { "radius", type<float>(),  } } },
			{ t, mud_Spheroid__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Spheroid__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Spheroid, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Torus
	{
		Type& t = type<mud::Torus>();
		static Meta meta = { t, &namspc({ "mud" }), "Torus", sizeof(mud::Torus), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Torus, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float tube_default = 1.f;
		static mud::Axis axis_default = mud::Axis::X;
		static mud::Axis construct_1_axis_default = mud::Axis::Y;
		static mud::Axis construct_2_axis_default = mud::Axis::Y;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Torus__construct_0, {} },
			{ t, mud_Torus__construct_1, { { "radius", type<float>(),  }, { "tube", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default, &construct_1_axis_default } } },
			{ t, mud_Torus__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  }, { "tube", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default, &construct_2_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Torus__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Torus, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Torus, m_tube), type<float>(), "tube", &tube_default, Member::Value, nullptr },
			{ t, offsetof(mud::Torus, m_axis), type<mud::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::TorusKnot
	{
		Type& t = type<mud::TorusKnot>();
		static Meta meta = { t, &namspc({ "mud" }), "TorusKnot", sizeof(mud::TorusKnot), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::TorusKnot, mud::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float tube_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TorusKnot__construct_0, {} },
			{ t, mud_TorusKnot__construct_1, { { "radius", type<float>(),  }, { "tube", type<float>(),  } } },
			{ t, mud_TorusKnot__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  }, { "tube", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_TorusKnot__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::TorusKnot, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::TorusKnot, m_tube), type<float>(), "tube", &tube_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Triangle
	{
		Type& t = type<mud::Triangle>();
		static Meta meta = { t, &namspc({ "mud" }), "Triangle", sizeof(mud::Triangle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Triangle, mud::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Triangle__construct_0, {} },
			{ t, mud_Triangle__construct_1, { { "size", type<mud::vec2>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Triangle__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Triangle, m_size), type<mud::vec2>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	
	{
		Type& t = type<ushort>();
		static Alias alias = { &t, &namspc({ "mud" }), "ShapeIndex" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<mud::Aabb>());
		m.m_types.push_back(&type<mud::CatmullType>());
		m.m_types.push_back(&type<mud::Curve2>());
		m.m_types.push_back(&type<mud::Curve3>());
		m.m_types.push_back(&type<mud::Distribution>());
		m.m_types.push_back(&type<mud::DrawMode>());
		m.m_types.push_back(&type<mud::Face3>());
		m.m_types.push_back(&type<mud::MarchingCubes>());
		m.m_types.push_back(&type<mud::MeshAdapter>());
		m.m_types.push_back(&type<mud::MeshPacker>());
		m.m_types.push_back(&type<mud::Plane>());
		m.m_types.push_back(&type<mud::Plane3>());
		m.m_types.push_back(&type<mud::PrimitiveType>());
		m.m_types.push_back(&type<mud::Ray>());
		m.m_types.push_back(&type<mud::Segment>());
		m.m_types.push_back(&type<mud::Shape>());
		m.m_types.push_back(&type<mud::ShapeIndex>());
		m.m_types.push_back(&type<mud::ShapeVar>());
		m.m_types.push_back(&type<mud::Symbol>());
		m.m_types.push_back(&type<mud::SymbolDetail>());
		m.m_types.push_back(&type<stl::vector<mud::Circle>>());
		m.m_types.push_back(&type<stl::vector<mud::ivec4>>());
		m.m_types.push_back(&type<stl::vector<mud::vec2>>());
		m.m_types.push_back(&type<stl::vector<mud::vec4>>());
		m.m_types.push_back(&type<mud::Arc>());
		m.m_types.push_back(&type<mud::ArcLine>());
		m.m_types.push_back(&type<mud::Box>());
		m.m_types.push_back(&type<mud::Capsule>());
		m.m_types.push_back(&type<mud::Circle>());
		m.m_types.push_back(&type<mud::ConvexHull>());
		m.m_types.push_back(&type<mud::Cube>());
		m.m_types.push_back(&type<mud::CurveBezierCubic>());
		m.m_types.push_back(&type<mud::CurveBezierCubic3>());
		m.m_types.push_back(&type<mud::CurveBezierQuadratic>());
		m.m_types.push_back(&type<mud::CurveBezierQuadratic3>());
		m.m_types.push_back(&type<mud::CurveCatmullRom3>());
		m.m_types.push_back(&type<mud::CurveLine>());
		m.m_types.push_back(&type<mud::CurveLine3>());
		m.m_types.push_back(&type<mud::CurveSpline>());
		m.m_types.push_back(&type<mud::CurveSpline3>());
		m.m_types.push_back(&type<mud::Cylinder>());
		m.m_types.push_back(&type<mud::Ellipsis>());
		m.m_types.push_back(&type<mud::Geometry>());
		m.m_types.push_back(&type<mud::Grid2>());
		m.m_types.push_back(&type<mud::Grid3>());
		m.m_types.push_back(&type<mud::Icosaedr>());
		m.m_types.push_back(&type<mud::Line>());
		m.m_types.push_back(&type<mud::Points>());
		m.m_types.push_back(&type<mud::Poisson>());
		m.m_types.push_back(&type<mud::Polygon>());
		m.m_types.push_back(&type<mud::Quad>());
		m.m_types.push_back(&type<mud::Rect>());
		m.m_types.push_back(&type<mud::Ring>());
		m.m_types.push_back(&type<mud::Sphere>());
		m.m_types.push_back(&type<mud::SphereRing>());
		m.m_types.push_back(&type<mud::Spheroid>());
		m.m_types.push_back(&type<mud::Torus>());
		m.m_types.push_back(&type<mud::TorusKnot>());
		m.m_types.push_back(&type<mud::Triangle>());
		{
			static float distance_default = 1000.f;
			static Function f = { &namspc({ "mud" }), "to_ray", nullptr, mud_to_ray_0, { { "pos", type<mud::vec3>(),  }, { "dir", type<mud::vec3>(),  }, { "distance", type<float>(), Param::Default, &distance_default } }, { &type<mud::Ray>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_segment", nullptr, mud_to_segment_1, { { "ray", type<mud::Ray>(),  } }, { &type<mud::Segment>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float distance_default = 1000.f;
			static Function f = { &namspc({ "mud" }), "to_ray", nullptr, mud_to_ray_2, { { "pos", type<mud::vec3>(),  }, { "dir", type<mud::vec3>(),  }, { "distance", type<float>(), Param::Default, &distance_default } }, { &type<mud::Ray>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_segment", nullptr, mud_to_segment_3, { { "ray", type<mud::Ray>(),  } }, { &type<mud::Segment>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "distribute_poisson", nullptr, mud_distribute_poisson_4, { { "size", type<mud::vec2>(),  }, { "radius", type<float>(),  } }, { &type<stl::vector<mud::vec3>>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "add_ball", nullptr, mud_add_ball_5, { { "cubes", type<mud::MarchingCubes>(),  }, { "ball", type<mud::vec3>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "add_planeX", nullptr, mud_add_planeX_6, { { "cubes", type<mud::MarchingCubes>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "add_planeY", nullptr, mud_add_planeY_7, { { "cubes", type<mud::MarchingCubes>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "add_planeZ", nullptr, mud_add_planeZ_8, { { "cubes", type<mud::MarchingCubes>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_geom::mud_geom()
		: Module("mud::geom", { &mud_type::m(), &mud_math::m() })
	{
		// setup reflection meta data
		mud_geom_meta(*this);
	}
}

#ifdef MUD_GEOM_MODULE
extern "C"
Module& getModule()
{
	return mud_geom::m();
}
#endif
