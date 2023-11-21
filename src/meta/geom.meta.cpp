module;
#include <infra/Cpp20.h>
module two.geom.meta;

using namespace two;

void two_CatmullType__to_string(void* val, string& str) { str = g_enu[type<two::CatmullType>().m_id]->name(uint32_t((*static_cast<two::CatmullType*>(val)))); }
void two_CatmullType__to_value(const string& str, void* val) { (*static_cast<two::CatmullType*>(val)) = two::CatmullType(g_enu[type<two::CatmullType>().m_id]->value(str.c_str())); }
void two_DrawMode__to_string(void* val, string& str) { str = g_enu[type<two::DrawMode>().m_id]->name(uint32_t((*static_cast<two::DrawMode*>(val)))); }
void two_DrawMode__to_value(const string& str, void* val) { (*static_cast<two::DrawMode*>(val)) = two::DrawMode(g_enu[type<two::DrawMode>().m_id]->value(str.c_str())); }
void two_PrimitiveType__to_string(void* val, string& str) { str = g_enu[type<two::PrimitiveType>().m_id]->name(uint32_t((*static_cast<two::PrimitiveType*>(val)))); }
void two_PrimitiveType__to_value(const string& str, void* val) { (*static_cast<two::PrimitiveType*>(val)) = two::PrimitiveType(g_enu[type<two::PrimitiveType>().m_id]->value(str.c_str())); }
void two_SymbolDetail__to_string(void* val, string& str) { str = g_enu[type<two::SymbolDetail>().m_id]->name(uint32_t((*static_cast<two::SymbolDetail*>(val)))); }
void two_SymbolDetail__to_value(const string& str, void* val) { (*static_cast<two::SymbolDetail*>(val)) = two::SymbolDetail(g_enu[type<two::SymbolDetail>().m_id]->value(str.c_str())); }
size_t stl_vector_two_vec2__size(void* vec) { return (*static_cast<stl::vector<two::vec2>*>(vec)).size(); }
void* stl_vector_two_vec2__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::vec2>*>(vec))[i]; }
void stl_vector_two_vec2__push(void* vec) { (*static_cast<stl::vector<two::vec2>*>(vec)).emplace_back(); }
void stl_vector_two_vec2__add(void* vec, void* value) { (*static_cast<stl::vector<two::vec2>*>(vec)).push_back(*static_cast<two::vec2*>(value)); }
void stl_vector_two_vec2__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::vec2>*>(vec)), *static_cast<two::vec2*>(value)); }
size_t stl_vector_two_vec4__size(void* vec) { return (*static_cast<stl::vector<two::vec4>*>(vec)).size(); }
void* stl_vector_two_vec4__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::vec4>*>(vec))[i]; }
void stl_vector_two_vec4__push(void* vec) { (*static_cast<stl::vector<two::vec4>*>(vec)).emplace_back(); }
void stl_vector_two_vec4__add(void* vec, void* value) { (*static_cast<stl::vector<two::vec4>*>(vec)).push_back(*static_cast<two::vec4*>(value)); }
void stl_vector_two_vec4__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::vec4>*>(vec)), *static_cast<two::vec4*>(value)); }
size_t stl_vector_two_ivec4__size(void* vec) { return (*static_cast<stl::vector<two::ivec4>*>(vec)).size(); }
void* stl_vector_two_ivec4__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::ivec4>*>(vec))[i]; }
void stl_vector_two_ivec4__push(void* vec) { (*static_cast<stl::vector<two::ivec4>*>(vec)).emplace_back(); }
void stl_vector_two_ivec4__add(void* vec, void* value) { (*static_cast<stl::vector<two::ivec4>*>(vec)).push_back(*static_cast<two::ivec4*>(value)); }
void stl_vector_two_ivec4__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::ivec4>*>(vec)), *static_cast<two::ivec4*>(value)); }
size_t stl_vector_two_Circle__size(void* vec) { return (*static_cast<stl::vector<two::Circle>*>(vec)).size(); }
void* stl_vector_two_Circle__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Circle>*>(vec))[i]; }
void stl_vector_two_Circle__push(void* vec) { (*static_cast<stl::vector<two::Circle>*>(vec)).emplace_back(); }
void stl_vector_two_Circle__add(void* vec, void* value) { (*static_cast<stl::vector<two::Circle>*>(vec)).push_back(*static_cast<two::Circle*>(value)); }
void stl_vector_two_Circle__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Circle>*>(vec)), *static_cast<two::Circle*>(value)); }
void two_Aabb__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Aabb(  ); }
void two_Aabb__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Aabb( *static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]) ); }
void two_Aabb__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Aabb((*static_cast<two::Aabb*>(other))); }
void two_Curve2_point(void* object, span<void*> args, void*& result) { (*static_cast<two::v2<float>*>(result)) = (*static_cast<two::Curve2*>(object)).point(*static_cast<float*>(args[0])); }
void two_Curve3_point(void* object, span<void*> args, void*& result) { (*static_cast<two::v3<float>*>(result)) = (*static_cast<two::Curve3*>(object)).point(*static_cast<float*>(args[0])); }
void two_CurveSpline__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveSpline(  ); }
void two_CurveSpline__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveSpline((*static_cast<two::CurveSpline*>(other))); }
void two_CurveSpline3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveSpline3(  ); }
void two_CurveSpline3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveSpline3((*static_cast<two::CurveSpline3*>(other))); }
void two_CurveBezierCubic__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveBezierCubic(  ); }
void two_CurveBezierCubic__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveBezierCubic((*static_cast<two::CurveBezierCubic*>(other))); }
void two_CurveBezierCubic3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveBezierCubic3(  ); }
void two_CurveBezierCubic3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveBezierCubic3((*static_cast<two::CurveBezierCubic3*>(other))); }
void two_CurveLine__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveLine(  ); }
void two_CurveLine__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveLine((*static_cast<two::CurveLine*>(other))); }
void two_CurveLine3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveLine3(  ); }
void two_CurveLine3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveLine3((*static_cast<two::CurveLine3*>(other))); }
void two_CurveBezierQuadratic__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveBezierQuadratic(  ); }
void two_CurveBezierQuadratic__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveBezierQuadratic((*static_cast<two::CurveBezierQuadratic*>(other))); }
void two_CurveBezierQuadratic3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveBezierQuadratic3(  ); }
void two_CurveBezierQuadratic3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveBezierQuadratic3((*static_cast<two::CurveBezierQuadratic3*>(other))); }
void two_CurveCatmullRom3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::CurveCatmullRom3(  ); }
void two_CurveCatmullRom3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::CurveCatmullRom3( *static_cast<stl::vector<two::vec3>*>(args[0]), *static_cast<bool*>(args[1]), *static_cast<two::CatmullType*>(args[2]), *static_cast<float*>(args[3]) ); }
void two_CurveCatmullRom3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::CurveCatmullRom3((*static_cast<two::CurveCatmullRom3*>(other))); }
void two_CurveCatmullRom3_add_point(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::CurveCatmullRom3*>(object)).add_point(*static_cast<two::vec3*>(args[0])); }
void two_Plane__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Plane(  ); }
void two_Plane__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Plane((*static_cast<two::Plane*>(other))); }
void two_Plane3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Plane3(  ); }
void two_Plane3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Plane3((*static_cast<two::Plane3*>(other))); }
void two_Face3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Face3(  ); }
void two_Face3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Face3((*static_cast<two::Face3*>(other))); }
void two_Segment__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Segment(  ); }
void two_Segment__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Segment((*static_cast<two::Segment*>(other))); }
void two_Ray__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Ray(  ); }
void two_Ray__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Ray((*static_cast<two::Ray*>(other))); }
void two_MeshAdapter__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MeshAdapter(  ); }
void two_MeshAdapter__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MeshAdapter((*static_cast<two::MeshAdapter*>(other))); }
void two_MeshAdapter_rewind(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::MeshAdapter*>(object)).rewind(); }
void two_MeshAdapter_copy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshAdapter*>(object)).copy(*static_cast<two::MeshAdapter*>(args[0])); }
void two_MeshAdapter_xcopy(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshAdapter*>(object)).xcopy(*static_cast<two::MeshAdapter*>(args[0]), *static_cast<two::mat4*>(args[1])); }
void two_MeshAdapter_next(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::MeshAdapter*>(object)).next(); }
void two_MeshAdapter_position(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).position(*static_cast<two::vec3*>(args[0])); }
void two_MeshAdapter_position4(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).position4(*static_cast<two::vec4*>(args[0])); }
void two_MeshAdapter_normal(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).normal(*static_cast<two::vec3*>(args[0])); }
void two_MeshAdapter_colour(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).colour(*static_cast<two::Colour*>(args[0])); }
void two_MeshAdapter_tangent(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).tangent(*static_cast<two::vec4*>(args[0])); }
void two_MeshAdapter_bitangent(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).bitangent(*static_cast<two::vec3*>(args[0])); }
void two_MeshAdapter_uv0(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).uv0(*static_cast<two::vec2*>(args[0])); }
void two_MeshAdapter_uv1(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).uv1(*static_cast<two::vec2*>(args[0])); }
void two_MeshAdapter_joints(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).joints(*static_cast<uint32_t*>(args[0])); }
void two_MeshAdapter_weights(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::MeshAdapter*>(object)).weights(*static_cast<two::vec4*>(args[0])); }
void* two_Shape__get_type(void* object) { return &(*static_cast<two::Shape*>(object)).m_type; }
void two_ShapeVar__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ShapeVar(  ); }
void two_ShapeVar__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ShapeVar( *static_cast<two::Shape*>(args[0]) ); }
void* two_ShapeVar__get_shape(void* object) { return &(*static_cast<two::ShapeVar*>(object)).shape(); }
void two_Geometry__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Geometry(  ); }
void two_MeshPacker__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MeshPacker(  ); }
void two_MeshPacker__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MeshPacker((*static_cast<two::MeshPacker*>(other))); }
void two_MeshPacker_position(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).position(*static_cast<two::vec3*>(args[0])); }
void two_MeshPacker_normal(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).normal(*static_cast<two::vec3*>(args[0])); }
void two_MeshPacker_colour(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).colour(*static_cast<two::Colour*>(args[0])); }
void two_MeshPacker_tangent(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).tangent(*static_cast<two::vec4*>(args[0])); }
void two_MeshPacker_bitangent(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).bitangent(*static_cast<two::vec3*>(args[0])); }
void two_MeshPacker_uv0(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).uv0(*static_cast<two::vec2*>(args[0])); }
void two_MeshPacker_uv1(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).uv1(*static_cast<two::vec2*>(args[0])); }
void two_MeshPacker_bones(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).bones(*static_cast<two::ivec4*>(args[0])); }
void two_MeshPacker_weights(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).weights(*static_cast<two::vec4*>(args[0])); }
void two_MeshPacker_index(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).index(*static_cast<uint32_t*>(args[0])); }
void two_MeshPacker_resize(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).resize(*static_cast<uint32_t*>(args[0]), *static_cast<uint32_t*>(args[1]), *static_cast<uint32_t*>(args[2])); }
void two_MeshPacker_clear(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::MeshPacker*>(object)).clear(); }
void two_MeshPacker_pack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).pack(*static_cast<two::MeshAdapter*>(args[0])); }
void two_MeshPacker_xpack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).xpack(*static_cast<two::MeshAdapter*>(args[0]), *static_cast<two::mat4*>(args[1])); }
void two_MeshPacker_unpack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).unpack(*static_cast<two::MeshAdapter*>(args[0]), *static_cast<two::mat4*>(args[1])); }
void two_MeshPacker_gen_normals(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MeshPacker*>(object)).gen_normals(*static_cast<bool*>(args[0])); }
void two_MeshPacker_gen_flat_normals(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::MeshPacker*>(object)).gen_flat_normals(); }
void two_MeshPacker_gen_tangents(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::MeshPacker*>(object)).gen_tangents(); }
void two_MeshPacker_smooth_normals(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::MeshPacker*>(object)).smooth_normals(); }
void two_Line__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Line(  ); }
void two_Line__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Line( *static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]) ); }
void two_Line__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Line((*static_cast<two::Line*>(other))); }
void two_Rect__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Rect(  ); }
void two_Rect__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Rect( *static_cast<two::vec2*>(args[0]), *static_cast<two::vec2*>(args[1]) ); }
void two_Rect__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Rect( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void two_Rect__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Rect((*static_cast<two::Rect*>(other))); }
void two_Quad__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Quad(  ); }
void two_Quad__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Quad( *static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::vec3*>(args[2]), *static_cast<two::vec3*>(args[3]) ); }
void two_Quad__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Quad((*static_cast<two::Quad*>(other))); }
void two_Grid2__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Grid2(  ); }
void two_Grid2__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Grid2( *static_cast<two::vec2*>(args[0]), *static_cast<two::vec2*>(args[1]) ); }
void two_Grid2__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Grid2((*static_cast<two::Grid2*>(other))); }
void two_Triangle__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Triangle(  ); }
void two_Triangle__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Triangle( *static_cast<two::vec2*>(args[0]) ); }
void two_Triangle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Triangle((*static_cast<two::Triangle*>(other))); }
void two_Circle__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Circle(  ); }
void two_Circle__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Circle( *static_cast<float*>(args[0]), *static_cast<two::Axis*>(args[1]) ); }
void two_Circle__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Circle( *static_cast<two::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<two::Axis*>(args[2]) ); }
void two_Circle__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Circle((*static_cast<two::Circle*>(other))); }
void two_Torus__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Torus(  ); }
void two_Torus__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Torus( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<two::Axis*>(args[2]) ); }
void two_Torus__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Torus( *static_cast<two::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::Axis*>(args[3]) ); }
void two_Torus__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Torus((*static_cast<two::Torus*>(other))); }
void two_TorusKnot__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::TorusKnot(  ); }
void two_TorusKnot__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::TorusKnot( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void two_TorusKnot__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::TorusKnot( *static_cast<two::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<float*>(args[4]) ); }
void two_TorusKnot__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::TorusKnot((*static_cast<two::TorusKnot*>(other))); }
void two_Ring__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Ring(  ); }
void two_Ring__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Ring( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void two_Ring__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Ring((*static_cast<two::Ring*>(other))); }
void two_Ellipsis__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Ellipsis(  ); }
void two_Ellipsis__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Ellipsis( *static_cast<two::vec2*>(args[0]), *static_cast<two::Axis*>(args[1]) ); }
void two_Ellipsis__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Ellipsis((*static_cast<two::Ellipsis*>(other))); }
void two_Arc__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Arc(  ); }
void two_Arc__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Arc( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void two_Arc__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Arc((*static_cast<two::Arc*>(other))); }
void two_ArcLine__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ArcLine(  ); }
void two_ArcLine__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ArcLine( *static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::vec3*>(args[2]) ); }
void two_ArcLine__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ArcLine( *static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::vec3*>(args[2]), *static_cast<two::vec3*>(args[3]) ); }
void two_ArcLine__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ArcLine((*static_cast<two::ArcLine*>(other))); }
void two_Cylinder__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Cylinder(  ); }
void two_Cylinder__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Cylinder( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<two::Axis*>(args[2]) ); }
void two_Cylinder__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Cylinder( *static_cast<two::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<two::Axis*>(args[3]) ); }
void two_Cylinder__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Cylinder((*static_cast<two::Cylinder*>(other))); }
void two_Capsule__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Capsule(  ); }
void two_Capsule__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Capsule( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<two::Axis*>(args[2]) ); }
void two_Capsule__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Capsule((*static_cast<two::Capsule*>(other))); }
void two_Cube__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Cube(  ); }
void two_Cube__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Cube( *static_cast<two::vec3*>(args[0]) ); }
void two_Cube__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Cube( *static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]) ); }
void two_Cube__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Cube((*static_cast<two::Cube*>(other))); }
void two_Tetraedr__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Tetraedr(  ); }
void two_Tetraedr__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Tetraedr( *static_cast<float*>(args[0]) ); }
void two_Tetraedr__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Tetraedr( *static_cast<two::vec3*>(args[0]), *static_cast<float*>(args[1]) ); }
void two_Tetraedr__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Tetraedr((*static_cast<two::Tetraedr*>(other))); }
void two_Sphere__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Sphere(  ); }
void two_Sphere__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Sphere( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void two_Sphere__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Sphere( *static_cast<two::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void two_Sphere__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Sphere((*static_cast<two::Sphere*>(other))); }
void two_SphereRing__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::SphereRing(  ); }
void two_SphereRing__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::SphereRing( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void two_SphereRing__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::SphereRing((*static_cast<two::SphereRing*>(other))); }
void two_Spheroid__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Spheroid(  ); }
void two_Spheroid__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Spheroid( *static_cast<float*>(args[0]) ); }
void two_Spheroid__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Spheroid( *static_cast<two::vec3*>(args[0]), *static_cast<float*>(args[1]) ); }
void two_Spheroid__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Spheroid((*static_cast<two::Spheroid*>(other))); }
void two_Icosaedr__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Icosaedr(  ); }
void two_Icosaedr__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Icosaedr( *static_cast<float*>(args[0]) ); }
void two_Icosaedr__construct_2(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Icosaedr( *static_cast<two::vec3*>(args[0]), *static_cast<float*>(args[1]) ); }
void two_Icosaedr__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Icosaedr((*static_cast<two::Icosaedr*>(other))); }
void two_Poisson__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Poisson( *static_cast<two::vec2*>(args[0]), *static_cast<float*>(args[1]) ); }
void two_Poisson_distribute(void* object, span<void*> args, void*& result) { (*static_cast<stl::vector<two::vec3>*>(result)) = (*static_cast<two::Poisson*>(object)).distribute(*static_cast<float*>(args[0])); }
void two_Poisson_distribute_circles(void* object, span<void*> args, void*& result) { (*static_cast<stl::vector<two::Circle>*>(result)) = (*static_cast<two::Poisson*>(object)).distribute_circles(*static_cast<float*>(args[0])); }
void two_Poisson_addPoint(void* object, span<void*> args, void*& result) { (*static_cast<bool*>(result)) = (*static_cast<two::Poisson*>(object)).addPoint(*static_cast<float*>(args[0]), *static_cast<two::vec3*>(args[1])); }
void two_Polygon__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Polygon(  ); }
void two_Polygon__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Polygon( *static_cast<stl::span<two::vec3>*>(args[0]) ); }
void two_Polygon__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Polygon((*static_cast<two::Polygon*>(other))); }
void two_Box__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Box(  ); }
void two_Box__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Box((*static_cast<two::Box*>(other))); }
void two_Points__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Points(  ); }
void two_Points__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Points( *static_cast<stl::span<two::vec3>*>(args[0]) ); }
void two_Points__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Points((*static_cast<two::Points*>(other))); }
void two_Grid3__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Grid3(  ); }
void two_Grid3__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Grid3( *static_cast<two::uvec2*>(args[0]), *static_cast<stl::span<two::vec3>*>(args[1]) ); }
void two_Grid3__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Grid3((*static_cast<two::Grid3*>(other))); }
void two_ConvexHull__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ConvexHull(  ); }
void two_ConvexHull__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ConvexHull( *static_cast<stl::span<two::vec3>*>(args[0]) ); }
void two_ConvexHull__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ConvexHull((*static_cast<two::ConvexHull*>(other))); }
void two_Symbol__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Symbol( *static_cast<two::Colour*>(args[0]), *static_cast<two::Colour*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<two::SymbolDetail*>(args[4]) ); }
void two_Symbol__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Symbol((*static_cast<two::Symbol*>(other))); }
void two_MarchingCubes__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::MarchingCubes( *static_cast<uint32_t*>(args[0]) ); }
void two_MarchingCubes_reset(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::MarchingCubes*>(object)).reset(); }
void two_MarchingCubes_count(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<uint*>(result)) = (*static_cast<two::MarchingCubes*>(object)).count(); }
void two_MarchingCubes_direct(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MarchingCubes*>(object)).direct(*static_cast<two::MeshAdapter*>(args[0])); }
void two_MarchingCubes_render(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::MarchingCubes*>(object)).render(*static_cast<two::MeshPacker*>(args[0])); }
void two_to_ray_0(span<void*> args, void*& result) { (*static_cast<two::Ray*>(result)) = two::to_ray(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<float*>(args[2])); }
void two_to_segment_1(span<void*> args, void*& result) { (*static_cast<two::Segment*>(result)) = two::to_segment(*static_cast<two::Ray*>(args[0])); }
void two_to_ray_2(span<void*> args, void*& result) { (*static_cast<two::Ray*>(result)) = two::to_ray(*static_cast<two::vec3*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<float*>(args[2])); }
void two_to_segment_3(span<void*> args, void*& result) { (*static_cast<two::Segment*>(result)) = two::to_segment(*static_cast<two::Ray*>(args[0])); }
void two_distribute_poisson_4(span<void*> args, void*& result) { (*static_cast<stl::vector<two::vec3>*>(result)) = two::distribute_poisson(*static_cast<two::vec2*>(args[0]), *static_cast<float*>(args[1])); }
void two_add_ball_5(span<void*> args, void*& result) { UNUSED(result);  two::add_ball(*static_cast<two::MarchingCubes*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]), *static_cast<two::Colour*>(args[4])); }
void two_add_ball_6(span<void*> args, void*& result) { UNUSED(result);  two::add_ball(*static_cast<two::MarchingCubes*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3])); }
void two_add_planeX_7(span<void*> args, void*& result) { UNUSED(result);  two::add_planeX(*static_cast<two::MarchingCubes*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void two_add_planeY_8(span<void*> args, void*& result) { UNUSED(result);  two::add_planeY(*static_cast<two::MarchingCubes*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }
void two_add_planeZ_9(span<void*> args, void*& result) { UNUSED(result);  two::add_planeZ(*static_cast<two::MarchingCubes*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2])); }

namespace two
{
	void two_geom_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::CatmullType>();
		static Meta meta = { t, &namspc({ "two" }), "CatmullType", sizeof(two::CatmullType), TypeClass::Enum };
		static cstring ids[] = { "Centripetal", "Chordal", "CatmullRom" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::CatmullType vars[] = { two::CatmullType::Centripetal, two::CatmullType::Chordal, two::CatmullType::CatmullRom};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_CatmullType__to_string,
		                           two_CatmullType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::DrawMode>();
		static Meta meta = { t, &namspc({ "two" }), "DrawMode", sizeof(two::DrawMode), TypeClass::Enum };
		static cstring ids[] = { "OUTLINE", "PLAIN" };
		static uint32_t values[] = { 0, 1 };
		static two::DrawMode vars[] = { two::OUTLINE, two::PLAIN};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_DrawMode__to_string,
		                           two_DrawMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::PrimitiveType>();
		static Meta meta = { t, &namspc({ "two" }), "PrimitiveType", sizeof(two::PrimitiveType), TypeClass::Enum };
		static cstring ids[] = { "Points", "Lines", "LineStrip", "Triangles", "TriangleStrip", "TriangleFan", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static two::PrimitiveType vars[] = { two::PrimitiveType::Points, two::PrimitiveType::Lines, two::PrimitiveType::LineStrip, two::PrimitiveType::Triangles, two::PrimitiveType::TriangleStrip, two::PrimitiveType::TriangleFan, two::PrimitiveType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_PrimitiveType__to_string,
		                           two_PrimitiveType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::SymbolDetail>();
		static Meta meta = { t, &namspc({ "two" }), "SymbolDetail", sizeof(two::SymbolDetail), TypeClass::Enum };
		static cstring ids[] = { "Lowest", "Low", "Medium", "High", "Highest" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static two::SymbolDetail vars[] = { two::SymbolDetail::Lowest, two::SymbolDetail::Low, two::SymbolDetail::Medium, two::SymbolDetail::High, two::SymbolDetail::Highest};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_SymbolDetail__to_string,
		                           two_SymbolDetail__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::vector<two::vec2>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::vec2>", sizeof(stl::vector<two::vec2>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::vec2>(),
		                             stl_vector_two_vec2__size,
		                             stl_vector_two_vec2__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_vec2__push,
		                             stl_vector_two_vec2__add,
		                             stl_vector_two_vec2__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::vec4>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::vec4>", sizeof(stl::vector<two::vec4>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::vec4>(),
		                             stl_vector_two_vec4__size,
		                             stl_vector_two_vec4__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_vec4__push,
		                             stl_vector_two_vec4__add,
		                             stl_vector_two_vec4__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::ivec4>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::ivec4>", sizeof(stl::vector<two::ivec4>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::ivec4>(),
		                             stl_vector_two_ivec4__size,
		                             stl_vector_two_ivec4__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_ivec4__push,
		                             stl_vector_two_ivec4__add,
		                             stl_vector_two_ivec4__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Circle>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Circle>", sizeof(stl::vector<two::Circle>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Circle>(),
		                             stl_vector_two_Circle__size,
		                             stl_vector_two_Circle__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Circle__push,
		                             stl_vector_two_Circle__add,
		                             stl_vector_two_Circle__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// two::Aabb
	{
		Type& t = type<two::Aabb>();
		static Meta meta = { t, &namspc({ "two" }), "Aabb", sizeof(two::Aabb), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Aabb__construct_0, {} },
			{ t, two_Aabb__construct_1, { { "center", type<two::vec3>(),  }, { "extents", type<two::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Aabb__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Aabb, m_center), type<two::vec3>(), "center", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Aabb, m_extents), type<two::vec3>(), "extents", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Aabb, m_empty), type<bool>(), "empty", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Curve2
	{
		Type& t = type<two::Curve2>();
		static Meta meta = { t, &namspc({ "two" }), "Curve2", sizeof(two::Curve2), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "point", Address(), two_Curve2_point, { { "t", type<float>(),  } }, { &type<two::vec2>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::Curve3
	{
		Type& t = type<two::Curve3>();
		static Meta meta = { t, &namspc({ "two" }), "Curve3", sizeof(two::Curve3), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "point", Address(), two_Curve3_point, { { "t", type<float>(),  } }, { &type<two::vec3>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::CurveSpline
	{
		Type& t = type<two::CurveSpline>();
		static Meta meta = { t, &namspc({ "two" }), "CurveSpline", sizeof(two::CurveSpline), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve2>() };
		static size_t bases_offsets[] = { base_offset<two::CurveSpline, two::Curve2>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveSpline__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveSpline__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveSpline, m_points), type<stl::vector<two::vec2>>(), "points", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::CurveSpline3
	{
		Type& t = type<two::CurveSpline3>();
		static Meta meta = { t, &namspc({ "two" }), "CurveSpline3", sizeof(two::CurveSpline3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve3>() };
		static size_t bases_offsets[] = { base_offset<two::CurveSpline3, two::Curve3>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveSpline3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveSpline3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveSpline3, m_points), type<stl::vector<two::vec3>>(), "points", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::CurveBezierCubic
	{
		Type& t = type<two::CurveBezierCubic>();
		static Meta meta = { t, &namspc({ "two" }), "CurveBezierCubic", sizeof(two::CurveBezierCubic), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve2>() };
		static size_t bases_offsets[] = { base_offset<two::CurveBezierCubic, two::Curve2>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveBezierCubic__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveBezierCubic__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveBezierCubic, v0), type<two::vec2>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierCubic, v1), type<two::vec2>(), "v1", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierCubic, v2), type<two::vec2>(), "v2", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierCubic, v3), type<two::vec2>(), "v3", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::CurveBezierCubic3
	{
		Type& t = type<two::CurveBezierCubic3>();
		static Meta meta = { t, &namspc({ "two" }), "CurveBezierCubic3", sizeof(two::CurveBezierCubic3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve3>() };
		static size_t bases_offsets[] = { base_offset<two::CurveBezierCubic3, two::Curve3>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveBezierCubic3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveBezierCubic3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveBezierCubic3, v0), type<two::vec3>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierCubic3, v1), type<two::vec3>(), "v1", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierCubic3, v2), type<two::vec3>(), "v2", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierCubic3, v3), type<two::vec3>(), "v3", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::CurveLine
	{
		Type& t = type<two::CurveLine>();
		static Meta meta = { t, &namspc({ "two" }), "CurveLine", sizeof(two::CurveLine), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve2>() };
		static size_t bases_offsets[] = { base_offset<two::CurveLine, two::Curve2>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveLine__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveLine__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveLine, v0), type<two::vec2>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveLine, v1), type<two::vec2>(), "v1", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::CurveLine3
	{
		Type& t = type<two::CurveLine3>();
		static Meta meta = { t, &namspc({ "two" }), "CurveLine3", sizeof(two::CurveLine3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve3>() };
		static size_t bases_offsets[] = { base_offset<two::CurveLine3, two::Curve3>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveLine3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveLine3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveLine3, v0), type<two::vec3>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveLine3, v1), type<two::vec3>(), "v1", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::CurveBezierQuadratic
	{
		Type& t = type<two::CurveBezierQuadratic>();
		static Meta meta = { t, &namspc({ "two" }), "CurveBezierQuadratic", sizeof(two::CurveBezierQuadratic), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve2>() };
		static size_t bases_offsets[] = { base_offset<two::CurveBezierQuadratic, two::Curve2>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveBezierQuadratic__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveBezierQuadratic__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveBezierQuadratic, v0), type<two::vec2>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierQuadratic, v1), type<two::vec2>(), "v1", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierQuadratic, v2), type<two::vec2>(), "v2", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::CurveBezierQuadratic3
	{
		Type& t = type<two::CurveBezierQuadratic3>();
		static Meta meta = { t, &namspc({ "two" }), "CurveBezierQuadratic3", sizeof(two::CurveBezierQuadratic3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve3>() };
		static size_t bases_offsets[] = { base_offset<two::CurveBezierQuadratic3, two::Curve3>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveBezierQuadratic3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveBezierQuadratic3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveBezierQuadratic3, v0), type<two::vec3>(), "v0", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierQuadratic3, v1), type<two::vec3>(), "v1", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::CurveBezierQuadratic3, v2), type<two::vec3>(), "v2", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::CurveCatmullRom3
	{
		Type& t = type<two::CurveCatmullRom3>();
		static Meta meta = { t, &namspc({ "two" }), "CurveCatmullRom3", sizeof(two::CurveCatmullRom3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Curve3>() };
		static size_t bases_offsets[] = { base_offset<two::CurveCatmullRom3, two::Curve3>() };
		// defaults
		static stl::vector<two::vec3> points_default = {};
		static bool closed_default = false;
		static two::CatmullType curve_type_default = two::CatmullType::Centripetal;
		static float tension_default = 0.5f;
		static bool construct_1_closed_default = false;
		static two::CatmullType construct_1_curve_type_default = two::CatmullType::Centripetal;
		static float construct_1_tension_default = 0.5f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_CurveCatmullRom3__construct_0, {} },
			{ t, two_CurveCatmullRom3__construct_1, { { "points", type<stl::vector<two::vec3>>(),  }, { "closed", type<bool>(), Param::Default, &construct_1_closed_default }, { "curve_type", type<two::CatmullType>(), Param::Default, &construct_1_curve_type_default }, { "tension", type<float>(), Param::Default, &construct_1_tension_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_CurveCatmullRom3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::CurveCatmullRom3, m_points), type<stl::vector<two::vec3>>(), "points", &points_default, Member::NonMutable, nullptr },
			{ t, offsetof(two::CurveCatmullRom3, m_closed), type<bool>(), "closed", &closed_default, Member::Value, nullptr },
			{ t, offsetof(two::CurveCatmullRom3, m_curve_type), type<two::CatmullType>(), "curve_type", &curve_type_default, Member::Value, nullptr },
			{ t, offsetof(two::CurveCatmullRom3, m_tension), type<float>(), "tension", &tension_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "add_point", Address(), two_CurveCatmullRom3_add_point, { { "point", type<two::vec3>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, methods, {}, };
	}
	// two::Plane
	{
		Type& t = type<two::Plane>();
		static Meta meta = { t, &namspc({ "two" }), "Plane", sizeof(two::Plane), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Plane__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Plane__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Plane, m_normal), type<two::vec3>(), "normal", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Plane, m_distance), type<float>(), "distance", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Plane3
	{
		Type& t = type<two::Plane3>();
		static Meta meta = { t, &namspc({ "two" }), "Plane3", sizeof(two::Plane3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Plane3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Plane3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Plane3, m_origin), type<two::vec3>(), "origin", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Plane3, m_a), type<two::vec3>(), "a", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Plane3, m_b), type<two::vec3>(), "b", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Face3
	{
		Type& t = type<two::Face3>();
		static Meta meta = { t, &namspc({ "two" }), "Face3", sizeof(two::Face3), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Face3__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Face3__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Segment
	{
		Type& t = type<two::Segment>();
		static Meta meta = { t, &namspc({ "two" }), "Segment", sizeof(two::Segment), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Segment__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Segment__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Segment, m_start), type<two::vec3>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Segment, m_end), type<two::vec3>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Ray
	{
		Type& t = type<two::Ray>();
		static Meta meta = { t, &namspc({ "two" }), "Ray", sizeof(two::Ray), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Ray__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Ray__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Ray, m_start), type<two::vec3>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Ray, m_end), type<two::vec3>(), "end", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Ray, m_dir), type<two::vec3>(), "dir", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Ray, m_inv_dir), type<two::vec3>(), "inv_dir", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MeshAdapter
	{
		Type& t = type<two::MeshAdapter>();
		static Meta meta = { t, &namspc({ "two" }), "MeshAdapter", sizeof(two::MeshAdapter), TypeClass::Struct };
		// bases
		// defaults
		static uint32_t vertex_format_default = 0;
		static bool index32_default = false;
		static uint32_t vertex_count_default = 0;
		static uint32_t index_count_default = 0;
		static uint32_t vertex_stride_default = 0;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MeshAdapter__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MeshAdapter__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MeshAdapter, m_vertex_format), type<uint32_t>(), "vertex_format", &vertex_format_default, Member::Value, nullptr },
			{ t, offsetof(two::MeshAdapter, m_index32), type<bool>(), "index32", &index32_default, Member::Value, nullptr },
			{ t, offsetof(two::MeshAdapter, m_vertex_count), type<uint32_t>(), "vertex_count", &vertex_count_default, Member::Value, nullptr },
			{ t, offsetof(two::MeshAdapter, m_index_count), type<uint32_t>(), "index_count", &index_count_default, Member::Value, nullptr },
			{ t, offsetof(two::MeshAdapter, m_vertex_stride), type<uint32_t>(), "vertex_stride", &vertex_stride_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "rewind", Address(), two_MeshAdapter_rewind, {}, g_qvoid },
			{ t, "copy", Address(), two_MeshAdapter_copy, { { "dest", type<two::MeshAdapter>(),  } }, g_qvoid },
			{ t, "xcopy", Address(), two_MeshAdapter_xcopy, { { "dest", type<two::MeshAdapter>(),  }, { "transform", type<two::mat4>(),  } }, g_qvoid },
			{ t, "next", Address(), two_MeshAdapter_next, {}, g_qvoid },
			{ t, "position", Address(), two_MeshAdapter_position, { { "p", type<two::vec3>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "position4", Address(), two_MeshAdapter_position4, { { "p", type<two::vec4>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "normal", Address(), two_MeshAdapter_normal, { { "n", type<two::vec3>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "colour", Address(), two_MeshAdapter_colour, { { "c", type<two::Colour>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "tangent", Address(), two_MeshAdapter_tangent, { { "t", type<two::vec4>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "bitangent", Address(), two_MeshAdapter_bitangent, { { "b", type<two::vec3>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "uv0", Address(), two_MeshAdapter_uv0, { { "uv", type<two::vec2>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "uv1", Address(), two_MeshAdapter_uv1, { { "uv", type<two::vec2>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "joints", Address(), two_MeshAdapter_joints, { { "j", type<uint32_t>(),  } }, { &type<two::MeshAdapter>(), QualType::None } },
			{ t, "weights", Address(), two_MeshAdapter_weights, { { "w", type<two::vec4>(),  } }, { &type<two::MeshAdapter>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// two::Shape
	{
		Type& t = type<two::Shape>();
		static Meta meta = { t, &namspc({ "two" }), "Shape", sizeof(two::Shape), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Shape__get_type }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::ShapeVar
	{
		Type& t = type<two::ShapeVar>();
		static Meta meta = { t, &namspc({ "two" }), "ShapeVar", sizeof(two::ShapeVar), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ShapeVar__construct_0, {} },
			{ t, two_ShapeVar__construct_1, { { "shape", type<two::Shape>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Shape>(), "shape", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_ShapeVar__get_shape }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, {}, {}, };
	}
	// two::Geometry
	{
		Type& t = type<two::Geometry>();
		static Meta meta = { t, &namspc({ "two" }), "Geometry", sizeof(two::Geometry), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Geometry, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Geometry__construct_0, {} }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::MeshPacker
	{
		Type& t = type<two::MeshPacker>();
		static Meta meta = { t, &namspc({ "two" }), "MeshPacker", sizeof(two::MeshPacker), TypeClass::Struct };
		// bases
		// defaults
		static two::PrimitiveType primitive_default = two::PrimitiveType::Triangles;
		static bool quantize_default = false;
		static bool gen_normals_0_area_weighted_default = true;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MeshPacker__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MeshPacker__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MeshPacker, m_primitive), type<two::PrimitiveType>(), "primitive", &primitive_default, Member::Value, nullptr },
			{ t, offsetof(two::MeshPacker, m_positions), type<stl::vector<two::vec3>>(), "positions", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_normals), type<stl::vector<two::vec3>>(), "normals", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_colours), type<stl::vector<two::Colour>>(), "colours", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_ucolours), type<stl::vector<uint32_t>>(), "ucolours", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_tangents), type<stl::vector<two::vec4>>(), "tangents", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_bitangents), type<stl::vector<two::vec3>>(), "bitangents", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_uv0s), type<stl::vector<two::vec2>>(), "uv0s", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_uv1s), type<stl::vector<two::vec2>>(), "uv1s", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_bones), type<stl::vector<two::ivec4>>(), "bones", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_weights), type<stl::vector<two::vec4>>(), "weights", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_indices), type<stl::vector<uint32_t>>(), "indices", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::MeshPacker, m_quantize), type<bool>(), "quantize", &quantize_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "position", Address(), two_MeshPacker_position, { { "p", type<two::vec3>(),  } }, g_qvoid },
			{ t, "normal", Address(), two_MeshPacker_normal, { { "n", type<two::vec3>(),  } }, g_qvoid },
			{ t, "colour", Address(), two_MeshPacker_colour, { { "c", type<two::Colour>(),  } }, g_qvoid },
			{ t, "tangent", Address(), two_MeshPacker_tangent, { { "t", type<two::vec4>(),  } }, g_qvoid },
			{ t, "bitangent", Address(), two_MeshPacker_bitangent, { { "b", type<two::vec3>(),  } }, g_qvoid },
			{ t, "uv0", Address(), two_MeshPacker_uv0, { { "uv", type<two::vec2>(),  } }, g_qvoid },
			{ t, "uv1", Address(), two_MeshPacker_uv1, { { "uv", type<two::vec2>(),  } }, g_qvoid },
			{ t, "bones", Address(), two_MeshPacker_bones, { { "j", type<two::ivec4>(),  } }, g_qvoid },
			{ t, "weights", Address(), two_MeshPacker_weights, { { "w", type<two::vec4>(),  } }, g_qvoid },
			{ t, "index", Address(), two_MeshPacker_index, { { "i", type<uint32_t>(),  } }, g_qvoid },
			{ t, "resize", Address(), two_MeshPacker_resize, { { "vertex_count", type<uint32_t>(),  }, { "index_count", type<uint32_t>(),  }, { "vertex_format", type<uint32_t>(),  } }, g_qvoid },
			{ t, "clear", Address(), two_MeshPacker_clear, {}, g_qvoid },
			{ t, "pack", Address(), two_MeshPacker_pack, { { "writer", type<two::MeshAdapter>(),  } }, g_qvoid },
			{ t, "xpack", Address(), two_MeshPacker_xpack, { { "writer", type<two::MeshAdapter>(),  }, { "transform", type<two::mat4>(),  } }, g_qvoid },
			{ t, "unpack", Address(), two_MeshPacker_unpack, { { "reader", type<two::MeshAdapter>(),  }, { "transform", type<two::mat4>(),  } }, g_qvoid },
			{ t, "gen_normals", Address(), two_MeshPacker_gen_normals, { { "area_weighted", type<bool>(), Param::Default, &gen_normals_0_area_weighted_default } }, g_qvoid },
			{ t, "gen_flat_normals", Address(), two_MeshPacker_gen_flat_normals, {}, g_qvoid },
			{ t, "gen_tangents", Address(), two_MeshPacker_gen_tangents, {}, g_qvoid },
			{ t, "smooth_normals", Address(), two_MeshPacker_smooth_normals, {}, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// two::Line
	{
		Type& t = type<two::Line>();
		static Meta meta = { t, &namspc({ "two" }), "Line", sizeof(two::Line), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Line, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Line__construct_0, {} },
			{ t, two_Line__construct_1, { { "start", type<two::vec3>(),  }, { "end", type<two::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Line__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Line, m_start), type<two::vec3>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Line, m_end), type<two::vec3>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Rect
	{
		Type& t = type<two::Rect>();
		static Meta meta = { t, &namspc({ "two" }), "Rect", sizeof(two::Rect), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Rect, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Rect__construct_0, {} },
			{ t, two_Rect__construct_1, { { "position", type<two::vec2>(),  }, { "size", type<two::vec2>(),  } } },
			{ t, two_Rect__construct_2, { { "x", type<float>(),  }, { "y", type<float>(),  }, { "w", type<float>(),  }, { "h", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Rect__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Rect, m_position), type<two::vec2>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Rect, m_size), type<two::vec2>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Quad
	{
		Type& t = type<two::Quad>();
		static Meta meta = { t, &namspc({ "two" }), "Quad", sizeof(two::Quad), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Quad, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Quad__construct_0, {} },
			{ t, two_Quad__construct_1, { { "a", type<two::vec3>(),  }, { "b", type<two::vec3>(),  }, { "c", type<two::vec3>(),  }, { "d", type<two::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Quad__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Grid2
	{
		Type& t = type<two::Grid2>();
		static Meta meta = { t, &namspc({ "two" }), "Grid2", sizeof(two::Grid2), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Grid2, two::Shape>() };
		// defaults
		static two::vec2 construct_1_space_default = vec2(1.f);
		// constructors
		static Constructor constructors[] = {
			{ t, two_Grid2__construct_0, {} },
			{ t, two_Grid2__construct_1, { { "size", type<two::vec2>(),  }, { "space", type<two::vec2>(), Param::Default, &construct_1_space_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Grid2__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Grid2, m_size), type<two::vec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Grid2, m_space), type<two::vec2>(), "space", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Triangle
	{
		Type& t = type<two::Triangle>();
		static Meta meta = { t, &namspc({ "two" }), "Triangle", sizeof(two::Triangle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Triangle, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Triangle__construct_0, {} },
			{ t, two_Triangle__construct_1, { { "size", type<two::vec2>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Triangle__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Triangle, m_size), type<two::vec2>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Circle
	{
		Type& t = type<two::Circle>();
		static Meta meta = { t, &namspc({ "two" }), "Circle", sizeof(two::Circle), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Circle, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static two::Axis axis_default = two::Axis::X;
		static two::Axis construct_1_axis_default = two::Axis::Y;
		static two::Axis construct_2_axis_default = two::Axis::Y;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Circle__construct_0, {} },
			{ t, two_Circle__construct_1, { { "radius", type<float>(),  }, { "axis", type<two::Axis>(), Param::Default, &construct_1_axis_default } } },
			{ t, two_Circle__construct_2, { { "center", type<two::vec3>(),  }, { "radius", type<float>(),  }, { "axis", type<two::Axis>(), Param::Default, &construct_2_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Circle__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Circle, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Circle, m_axis), type<two::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Torus
	{
		Type& t = type<two::Torus>();
		static Meta meta = { t, &namspc({ "two" }), "Torus", sizeof(two::Torus), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Torus, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float tube_default = 1.f;
		static two::Axis axis_default = two::Axis::X;
		static two::Axis construct_1_axis_default = two::Axis::Y;
		static two::Axis construct_2_axis_default = two::Axis::Y;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Torus__construct_0, {} },
			{ t, two_Torus__construct_1, { { "radius", type<float>(),  }, { "tube", type<float>(),  }, { "axis", type<two::Axis>(), Param::Default, &construct_1_axis_default } } },
			{ t, two_Torus__construct_2, { { "center", type<two::vec3>(),  }, { "radius", type<float>(),  }, { "tube", type<float>(),  }, { "axis", type<two::Axis>(), Param::Default, &construct_2_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Torus__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Torus, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Torus, m_tube), type<float>(), "tube", &tube_default, Member::Value, nullptr },
			{ t, offsetof(two::Torus, m_axis), type<two::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::TorusKnot
	{
		Type& t = type<two::TorusKnot>();
		static Meta meta = { t, &namspc({ "two" }), "TorusKnot", sizeof(two::TorusKnot), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::TorusKnot, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float tube_default = 1.f;
		static float p_default = 2.f;
		static float q_default = 3.f;
		static float construct_1_p_default = 2.f;
		static float construct_1_q_default = 3.f;
		static float construct_2_p_default = 2.f;
		static float construct_2_q_default = 3.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_TorusKnot__construct_0, {} },
			{ t, two_TorusKnot__construct_1, { { "radius", type<float>(),  }, { "tube", type<float>(),  }, { "p", type<float>(), Param::Default, &construct_1_p_default }, { "q", type<float>(), Param::Default, &construct_1_q_default } } },
			{ t, two_TorusKnot__construct_2, { { "center", type<two::vec3>(),  }, { "radius", type<float>(),  }, { "tube", type<float>(),  }, { "p", type<float>(), Param::Default, &construct_2_p_default }, { "q", type<float>(), Param::Default, &construct_2_q_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_TorusKnot__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::TorusKnot, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::TorusKnot, m_tube), type<float>(), "tube", &tube_default, Member::Value, nullptr },
			{ t, offsetof(two::TorusKnot, m_p), type<float>(), "p", &p_default, Member::Value, nullptr },
			{ t, offsetof(two::TorusKnot, m_q), type<float>(), "q", &q_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Ring
	{
		Type& t = type<two::Ring>();
		static Meta meta = { t, &namspc({ "two" }), "Ring", sizeof(two::Ring), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Ring, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float min_default = 0.f;
		static float max_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Ring__construct_0, {} },
			{ t, two_Ring__construct_1, { { "radius", type<float>(),  }, { "min", type<float>(),  }, { "max", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Ring__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Ring, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Ring, m_min), type<float>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::Ring, m_max), type<float>(), "max", &max_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Ellipsis
	{
		Type& t = type<two::Ellipsis>();
		static Meta meta = { t, &namspc({ "two" }), "Ellipsis", sizeof(two::Ellipsis), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Ellipsis, two::Shape>() };
		// defaults
		static two::Axis axis_default = two::Axis::Y;
		static two::Axis construct_1_axis_default = two::Axis::Y;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Ellipsis__construct_0, {} },
			{ t, two_Ellipsis__construct_1, { { "radius", type<two::vec2>(),  }, { "axis", type<two::Axis>(), Param::Default, &construct_1_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Ellipsis__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Ellipsis, m_radius), type<two::vec2>(), "radius", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Ellipsis, m_axis), type<two::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Arc
	{
		Type& t = type<two::Arc>();
		static Meta meta = { t, &namspc({ "two" }), "Arc", sizeof(two::Arc), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Arc, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float start_default = 0.f;
		static float end_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Arc__construct_0, {} },
			{ t, two_Arc__construct_1, { { "radius", type<float>(),  }, { "start", type<float>(),  }, { "end", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Arc__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Arc, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Arc, m_start), type<float>(), "start", &start_default, Member::Value, nullptr },
			{ t, offsetof(two::Arc, m_end), type<float>(), "end", &end_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ArcLine
	{
		Type& t = type<two::ArcLine>();
		static Meta meta = { t, &namspc({ "two" }), "ArcLine", sizeof(two::ArcLine), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::ArcLine, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ArcLine__construct_0, {} },
			{ t, two_ArcLine__construct_1, { { "start", type<two::vec3>(),  }, { "middle", type<two::vec3>(),  }, { "end", type<two::vec3>(),  } } },
			{ t, two_ArcLine__construct_2, { { "center", type<two::vec3>(),  }, { "start", type<two::vec3>(),  }, { "middle", type<two::vec3>(),  }, { "end", type<two::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ArcLine__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ArcLine, m_start), type<two::vec3>(), "start", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ArcLine, m_middle), type<two::vec3>(), "middle", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ArcLine, m_end), type<two::vec3>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Cylinder
	{
		Type& t = type<two::Cylinder>();
		static Meta meta = { t, &namspc({ "two" }), "Cylinder", sizeof(two::Cylinder), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Cylinder, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float height_default = 2.f;
		static two::Axis axis_default = two::Axis::X;
		static two::Axis construct_1_axis_default = two::Axis::X;
		static two::Axis construct_2_axis_default = two::Axis::X;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Cylinder__construct_0, {} },
			{ t, two_Cylinder__construct_1, { { "radius", type<float>(),  }, { "height", type<float>(),  }, { "axis", type<two::Axis>(), Param::Default, &construct_1_axis_default } } },
			{ t, two_Cylinder__construct_2, { { "center", type<two::vec3>(),  }, { "radius", type<float>(),  }, { "height", type<float>(),  }, { "axis", type<two::Axis>(), Param::Default, &construct_2_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Cylinder__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Cylinder, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Cylinder, m_height), type<float>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(two::Cylinder, m_axis), type<two::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Capsule
	{
		Type& t = type<two::Capsule>();
		static Meta meta = { t, &namspc({ "two" }), "Capsule", sizeof(two::Capsule), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Capsule, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float height_default = 2.f;
		static two::Axis axis_default = two::Axis::X;
		static two::Axis construct_1_axis_default = two::Axis::X;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Capsule__construct_0, {} },
			{ t, two_Capsule__construct_1, { { "radius", type<float>(),  }, { "height", type<float>(),  }, { "axis", type<two::Axis>(), Param::Default, &construct_1_axis_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Capsule__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Capsule, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Capsule, m_height), type<float>(), "height", &height_default, Member::Value, nullptr },
			{ t, offsetof(two::Capsule, m_axis), type<two::Axis>(), "axis", &axis_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Cube
	{
		Type& t = type<two::Cube>();
		static Meta meta = { t, &namspc({ "two" }), "Cube", sizeof(two::Cube), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Cube, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Cube__construct_0, {} },
			{ t, two_Cube__construct_1, { { "extents", type<two::vec3>(),  } } },
			{ t, two_Cube__construct_2, { { "center", type<two::vec3>(),  }, { "extents", type<two::vec3>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Cube__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Cube, m_extents), type<two::vec3>(), "extents", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Tetraedr
	{
		Type& t = type<two::Tetraedr>();
		static Meta meta = { t, &namspc({ "two" }), "Tetraedr", sizeof(two::Tetraedr), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Tetraedr, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Tetraedr__construct_0, {} },
			{ t, two_Tetraedr__construct_1, { { "radius", type<float>(),  } } },
			{ t, two_Tetraedr__construct_2, { { "center", type<two::vec3>(),  }, { "radius", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Tetraedr__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Tetraedr, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Sphere
	{
		Type& t = type<two::Sphere>();
		static Meta meta = { t, &namspc({ "two" }), "Sphere", sizeof(two::Sphere), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Sphere, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float start_default = 0.f;
		static float end_default = c_2pi;
		static float construct_1_start_default = 0.f;
		static float construct_1_end_default = c_2pi;
		static float construct_2_start_default = 0.f;
		static float construct_2_end_default = c_2pi;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Sphere__construct_0, {} },
			{ t, two_Sphere__construct_1, { { "radius", type<float>(),  }, { "start", type<float>(), Param::Default, &construct_1_start_default }, { "end", type<float>(), Param::Default, &construct_1_end_default } } },
			{ t, two_Sphere__construct_2, { { "center", type<two::vec3>(),  }, { "radius", type<float>(),  }, { "start", type<float>(), Param::Default, &construct_2_start_default }, { "end", type<float>(), Param::Default, &construct_2_end_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Sphere__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Sphere, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::Sphere, m_start), type<float>(), "start", &start_default, Member::Value, nullptr },
			{ t, offsetof(two::Sphere, m_end), type<float>(), "end", &end_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::SphereRing
	{
		Type& t = type<two::SphereRing>();
		static Meta meta = { t, &namspc({ "two" }), "SphereRing", sizeof(two::SphereRing), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::SphereRing, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		static float min_default = -1.f;
		static float max_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_SphereRing__construct_0, {} },
			{ t, two_SphereRing__construct_1, { { "radius", type<float>(),  }, { "min", type<float>(),  }, { "max", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_SphereRing__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::SphereRing, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(two::SphereRing, m_min), type<float>(), "min", &min_default, Member::Value, nullptr },
			{ t, offsetof(two::SphereRing, m_max), type<float>(), "max", &max_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Spheroid
	{
		Type& t = type<two::Spheroid>();
		static Meta meta = { t, &namspc({ "two" }), "Spheroid", sizeof(two::Spheroid), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Spheroid, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Spheroid__construct_0, {} },
			{ t, two_Spheroid__construct_1, { { "radius", type<float>(),  } } },
			{ t, two_Spheroid__construct_2, { { "center", type<two::vec3>(),  }, { "radius", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Spheroid__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Spheroid, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Icosaedr
	{
		Type& t = type<two::Icosaedr>();
		static Meta meta = { t, &namspc({ "two" }), "Icosaedr", sizeof(two::Icosaedr), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Icosaedr, two::Shape>() };
		// defaults
		static float radius_default = 1.f;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Icosaedr__construct_0, {} },
			{ t, two_Icosaedr__construct_1, { { "radius", type<float>(),  } } },
			{ t, two_Icosaedr__construct_2, { { "center", type<two::vec3>(),  }, { "radius", type<float>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Icosaedr__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Icosaedr, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Distribution
	{
		Type& t = type<two::Distribution>();
		static Meta meta = { t, &namspc({ "two" }), "Distribution", sizeof(two::Distribution), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Poisson
	{
		Type& t = type<two::Poisson>();
		static Meta meta = { t, &namspc({ "two" }), "Poisson", sizeof(two::Poisson), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Distribution>() };
		static size_t bases_offsets[] = { base_offset<two::Poisson, two::Distribution>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Poisson__construct_0, { { "size", type<two::vec2>(),  }, { "maxRadius", type<float>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "distribute", Address(), two_Poisson_distribute, { { "radius", type<float>(),  } }, { &type<stl::vector<two::vec3>>(), QualType::None } },
			{ t, "distribute_circles", Address(), two_Poisson_distribute_circles, { { "radius", type<float>(),  } }, { &type<stl::vector<two::Circle>>(), QualType::None } },
			{ t, "addPoint", Address(), two_Poisson_addPoint, { { "radius", type<float>(),  }, { "point", type<two::vec3>(),  } }, { &type<bool>(), QualType::None } }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, methods, {}, };
	}
	// two::Polygon
	{
		Type& t = type<two::Polygon>();
		static Meta meta = { t, &namspc({ "two" }), "Polygon", sizeof(two::Polygon), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Polygon, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Polygon__construct_0, {} },
			{ t, two_Polygon__construct_1, { { "vertices", type<stl::span<two::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Polygon__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Box
	{
		Type& t = type<two::Box>();
		static Meta meta = { t, &namspc({ "two" }), "Box", sizeof(two::Box), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Box, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Box__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Box__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Points
	{
		Type& t = type<two::Points>();
		static Meta meta = { t, &namspc({ "two" }), "Points", sizeof(two::Points), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Points, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Points__construct_0, {} },
			{ t, two_Points__construct_1, { { "points", type<stl::span<two::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Points__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Points, m_points), type<stl::vector<two::vec3>>(), "points", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Grid3
	{
		Type& t = type<two::Grid3>();
		static Meta meta = { t, &namspc({ "two" }), "Grid3", sizeof(two::Grid3), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::Grid3, two::Shape>() };
		// defaults
		static stl::span<two::vec3> construct_1_points_default = {};
		// constructors
		static Constructor constructors[] = {
			{ t, two_Grid3__construct_0, {} },
			{ t, two_Grid3__construct_1, { { "size", type<two::uvec2>(),  }, { "points", type<stl::span<two::vec3>>(), Param::Default, &construct_1_points_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Grid3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Grid3, m_size), type<two::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Grid3, m_points), type<stl::vector<two::vec3>>(), "points", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ConvexHull
	{
		Type& t = type<two::ConvexHull>();
		static Meta meta = { t, &namspc({ "two" }), "ConvexHull", sizeof(two::ConvexHull), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::Shape>() };
		static size_t bases_offsets[] = { base_offset<two::ConvexHull, two::Shape>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ConvexHull__construct_0, {} },
			{ t, two_ConvexHull__construct_1, { { "vertices", type<stl::span<two::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ConvexHull__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::ConvexHull, m_vertices), type<stl::vector<two::vec3>>(), "vertices", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Symbol
	{
		Type& t = type<two::Symbol>();
		static Meta meta = { t, &namspc({ "two" }), "Symbol", sizeof(two::Symbol), TypeClass::Struct };
		// bases
		// defaults
		static const char* image_default = nullptr;
		static two::Image256* image256_default = nullptr;
		static const char* program_default = nullptr;
		static two::Colour construct_0_outline_default = two::Colour(0.f,0.f);
		static bool construct_0_overlay_default = false;
		static bool construct_0_double_sided_default = false;
		static two::SymbolDetail construct_0_detail_default = two::SymbolDetail::Medium;
		// constructors
		static Constructor constructors[] = {
			{ t, two_Symbol__construct_0, { { "fill", type<two::Colour>(),  }, { "outline", type<two::Colour>(), Param::Default, &construct_0_outline_default }, { "overlay", type<bool>(), Param::Default, &construct_0_overlay_default }, { "double_sided", type<bool>(), Param::Default, &construct_0_double_sided_default }, { "detail", type<two::SymbolDetail>(), Param::Default, &construct_0_detail_default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Symbol__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Symbol, m_outline), type<two::Colour>(), "outline", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Symbol, m_fill), type<two::Colour>(), "fill", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Symbol, m_overlay), type<bool>(), "overlay", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Symbol, m_double_sided), type<bool>(), "double_sided", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Symbol, m_detail), type<two::SymbolDetail>(), "detail", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Symbol, m_subdiv), type<two::uvec2>(), "subdiv", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Symbol, m_image), type<const char*>(), "image", image_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Symbol, m_image256), type<two::Image256>(), "image256", image256_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Symbol, m_program), type<const char*>(), "program", program_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::MarchingCubes
	{
		Type& t = type<two::MarchingCubes>();
		static Meta meta = { t, &namspc({ "two" }), "MarchingCubes", sizeof(two::MarchingCubes), TypeClass::Object };
		// bases
		// defaults
		static float isolation_default = 80.f;
		static uint32_t subdiv_default = 32;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MarchingCubes__construct_0, { { "resolution", type<uint32_t>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::MarchingCubes, m_isolation), type<float>(), "isolation", &isolation_default, Member::Value, nullptr },
			{ t, offsetof(two::MarchingCubes, m_subdiv), type<uint32_t>(), "subdiv", &subdiv_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "reset", Address(), two_MarchingCubes_reset, {}, g_qvoid },
			{ t, "count", Address(), two_MarchingCubes_count, {}, { &type<uint32_t>(), QualType::None } },
			{ t, "direct", Address(), two_MarchingCubes_direct, { { "output", type<two::MeshAdapter>(), Param::Output } }, g_qvoid },
			{ t, "render", Address(), two_MarchingCubes_render, { { "output", type<two::MeshPacker>(), Param::Output } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	
	{
		Type& t = type<ushort>();
		static Alias alias = { &t, &namspc({ "two" }), "ShapeIndex" };
		m.m_aliases.push_back(&alias);
	}
	
		m.m_types.push_back(&type<stl::vector<two::vec2>>());
		m.m_types.push_back(&type<stl::vector<two::vec4>>());
		m.m_types.push_back(&type<stl::vector<two::ivec4>>());
		m.m_types.push_back(&type<stl::vector<two::Circle>>());
		m.m_types.push_back(&type<two::Aabb>());
		m.m_types.push_back(&type<two::Curve2>());
		m.m_types.push_back(&type<two::Curve3>());
		m.m_types.push_back(&type<two::CurveSpline>());
		m.m_types.push_back(&type<two::CurveSpline3>());
		m.m_types.push_back(&type<two::CurveBezierCubic>());
		m.m_types.push_back(&type<two::CurveBezierCubic3>());
		m.m_types.push_back(&type<two::CurveLine>());
		m.m_types.push_back(&type<two::CurveLine3>());
		m.m_types.push_back(&type<two::CurveBezierQuadratic>());
		m.m_types.push_back(&type<two::CurveBezierQuadratic3>());
		m.m_types.push_back(&type<two::CatmullType>());
		m.m_types.push_back(&type<two::CurveCatmullRom3>());
		m.m_types.push_back(&type<two::Plane>());
		m.m_types.push_back(&type<two::Plane3>());
		m.m_types.push_back(&type<two::Face3>());
		m.m_types.push_back(&type<two::Segment>());
		m.m_types.push_back(&type<two::Ray>());
		m.m_types.push_back(&type<two::DrawMode>());
		m.m_types.push_back(&type<two::PrimitiveType>());
		m.m_types.push_back(&type<two::ShapeIndex>());
		m.m_types.push_back(&type<two::MeshAdapter>());
		m.m_types.push_back(&type<two::Shape>());
		m.m_types.push_back(&type<two::ShapeVar>());
		m.m_types.push_back(&type<two::Geometry>());
		m.m_types.push_back(&type<two::MeshPacker>());
		m.m_types.push_back(&type<two::Line>());
		m.m_types.push_back(&type<two::Rect>());
		m.m_types.push_back(&type<two::Quad>());
		m.m_types.push_back(&type<two::Grid2>());
		m.m_types.push_back(&type<two::Triangle>());
		m.m_types.push_back(&type<two::Circle>());
		m.m_types.push_back(&type<two::Torus>());
		m.m_types.push_back(&type<two::TorusKnot>());
		m.m_types.push_back(&type<two::Ring>());
		m.m_types.push_back(&type<two::Ellipsis>());
		m.m_types.push_back(&type<two::Arc>());
		m.m_types.push_back(&type<two::ArcLine>());
		m.m_types.push_back(&type<two::Cylinder>());
		m.m_types.push_back(&type<two::Capsule>());
		m.m_types.push_back(&type<two::Cube>());
		m.m_types.push_back(&type<two::Tetraedr>());
		m.m_types.push_back(&type<two::Sphere>());
		m.m_types.push_back(&type<two::SphereRing>());
		m.m_types.push_back(&type<two::Spheroid>());
		m.m_types.push_back(&type<two::Icosaedr>());
		m.m_types.push_back(&type<two::Distribution>());
		m.m_types.push_back(&type<two::Poisson>());
		m.m_types.push_back(&type<two::Polygon>());
		m.m_types.push_back(&type<two::Box>());
		m.m_types.push_back(&type<two::Points>());
		m.m_types.push_back(&type<two::Grid3>());
		m.m_types.push_back(&type<two::ConvexHull>());
		m.m_types.push_back(&type<two::SymbolDetail>());
		m.m_types.push_back(&type<two::Symbol>());
		m.m_types.push_back(&type<two::MarchingCubes>());
		{
			static float distance_default = 1000.f;
			static Function f = { &namspc({ "two" }), "to_ray", funcptr<two::Ray(*)(const two::vec3&, const two::vec3&, float)>(two::to_ray), two_to_ray_0, { { "pos", type<two::vec3>(),  }, { "dir", type<two::vec3>(),  }, { "distance", type<float>(), Param::Default, &distance_default } }, { &type<two::Ray>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_segment", funcptr<two::Segment(*)(const two::Ray&)>(two::to_segment), two_to_segment_1, { { "ray", type<two::Ray>(),  } }, { &type<two::Segment>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float distance_default = 1000.f;
			static Function f = { &namspc({ "two" }), "to_ray", funcptr<two::Ray(*)(const two::vec3&, const two::vec3&, float)>(two::to_ray), two_to_ray_2, { { "pos", type<two::vec3>(),  }, { "dir", type<two::vec3>(),  }, { "distance", type<float>(), Param::Default, &distance_default } }, { &type<two::Ray>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "to_segment", funcptr<two::Segment(*)(const two::Ray&)>(two::to_segment), two_to_segment_3, { { "ray", type<two::Ray>(),  } }, { &type<two::Segment>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "distribute_poisson", funcptr<stl::vector<two::vec3>(*)(two::vec2, float)>(two::distribute_poisson), two_distribute_poisson_4, { { "size", type<two::vec2>(),  }, { "radius", type<float>(),  } }, { &type<stl::vector<two::vec3>>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "add_ball", funcptr<void(*)(two::MarchingCubes&, const two::vec3&, float, float, const two::Colour&)>(two::add_ball), two_add_ball_5, { { "cubes", type<two::MarchingCubes>(),  }, { "ball", type<two::vec3>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  }, { "colour", type<two::Colour>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "add_ball", funcptr<void(*)(two::MarchingCubes&, const two::vec3&, float, float)>(two::add_ball), two_add_ball_6, { { "cubes", type<two::MarchingCubes>(),  }, { "ball", type<two::vec3>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "add_planeX", funcptr<void(*)(two::MarchingCubes&, float, float)>(two::add_planeX), two_add_planeX_7, { { "cubes", type<two::MarchingCubes>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "add_planeY", funcptr<void(*)(two::MarchingCubes&, float, float)>(two::add_planeY), two_add_planeY_8, { { "cubes", type<two::MarchingCubes>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two" }), "add_planeZ", funcptr<void(*)(two::MarchingCubes&, float, float)>(two::add_planeZ), two_add_planeZ_9, { { "cubes", type<two::MarchingCubes>(),  }, { "strength", type<float>(),  }, { "subtract", type<float>(),  } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_geom::two_geom()
		: Module("two::geom", { &two_type::m(), &two_math::m() })
	{
		// setup reflection meta data
		two_geom_meta(*this);
	}
}

#ifdef TWO_GEOM_MODULE
extern "C"
Module& getModule()
{
	return two_geom::m();
}
#endif
