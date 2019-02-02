#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/new.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/geom/Convert.h>
#endif

#include <geom/Api.h>

using namespace mud;

void mud_DrawMode__to_string(void* val, string& str) { str = g_enu[type<mud::DrawMode>().m_id]->name(uint32_t((*static_cast<mud::DrawMode*>(val)))); }
void mud_DrawMode__to_value(const string& str, void* val) { (*static_cast<mud::DrawMode*>(val)) = mud::DrawMode(g_enu[type<mud::DrawMode>().m_id]->value(str.c_str())); }
void mud_PrimitiveType__to_string(void* val, string& str) { str = g_enu[type<mud::PrimitiveType>().m_id]->name(uint32_t((*static_cast<mud::PrimitiveType*>(val)))); }
void mud_PrimitiveType__to_value(const string& str, void* val) { (*static_cast<mud::PrimitiveType*>(val)) = mud::PrimitiveType(g_enu[type<mud::PrimitiveType>().m_id]->value(str.c_str())); }
void mud_SymbolDetail__to_string(void* val, string& str) { str = g_enu[type<mud::SymbolDetail>().m_id]->name(uint32_t((*static_cast<mud::SymbolDetail*>(val)))); }
void mud_SymbolDetail__to_value(const string& str, void* val) { (*static_cast<mud::SymbolDetail*>(val)) = mud::SymbolDetail(g_enu[type<mud::SymbolDetail>().m_id]->value(str.c_str())); }
size_t vector_mud_Circle___size(void* vec) { return (*static_cast<vector<mud::Circle>*>(vec)).size(); }
void* vector_mud_Circle___at(void* vec, size_t i) { return &(*static_cast<vector<mud::Circle>*>(vec))[i]; }
void vector_mud_Circle___add(void* vec, void* value) { (*static_cast<vector<mud::Circle>*>(vec)).push_back(*static_cast<mud::Circle*>(value)); }
void vector_mud_Circle___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Circle>*>(vec)), *static_cast<mud::Circle*>(value)); }
void mud_Face3__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Face3*>(ref))) mud::Face3(  ); }
void mud_Face3__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Face3*>(ref))) mud::Face3((*static_cast<mud::Face3*>(other))); }
void mud_MeshPacker__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::MeshPacker*>(ref))) mud::MeshPacker(  ); }
void mud_MeshPacker__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::MeshPacker*>(ref))) mud::MeshPacker((*static_cast<mud::MeshPacker*>(other))); }
void mud_Plane__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Plane*>(ref))) mud::Plane(  ); }
void mud_Plane__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Plane*>(ref))) mud::Plane((*static_cast<mud::Plane*>(other))); }
void mud_Plane3__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Plane3*>(ref))) mud::Plane3(  ); }
void mud_Plane3__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Plane3*>(ref))) mud::Plane3((*static_cast<mud::Plane3*>(other))); }
void mud_Ray__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Ray*>(ref))) mud::Ray(  ); }
void mud_Ray__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Ray*>(ref))) mud::Ray((*static_cast<mud::Ray*>(other))); }
void mud_Segment__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Segment*>(ref))) mud::Segment(  ); }
void mud_Segment__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Segment*>(ref))) mud::Segment((*static_cast<mud::Segment*>(other))); }
void* mud_Shape__get_type(void* object) { return &(*static_cast<mud::Shape*>(object)).m_type; }
void mud_ShapeVar__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ShapeVar*>(ref))) mud::ShapeVar(  ); }
void mud_ShapeVar__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ShapeVar*>(ref))) mud::ShapeVar( *static_cast<mud::Shape*>(args[0]) ); }
void mud_ShapeVar__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ShapeVar*>(ref))) mud::ShapeVar((*static_cast<mud::ShapeVar*>(other))); }
void* mud_ShapeVar__get_shape(void* object) { return &(*static_cast<mud::ShapeVar*>(object)).shape(); }
void mud_Symbol__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Symbol*>(ref))) mud::Symbol( *static_cast<mud::Colour*>(args[0]), *static_cast<mud::Colour*>(args[1]), *static_cast<bool*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<mud::SymbolDetail*>(args[4]) ); }
void mud_Symbol__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Symbol*>(ref))) mud::Symbol((*static_cast<mud::Symbol*>(other))); }
void mud_Arc__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Arc(  ); }
void mud_Arc__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Arc*>(ref))) mud::Arc( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_Arc__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Arc*>(ref))) mud::Arc((*static_cast<mud::Arc*>(other))); }
void mud_ArcLine__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ArcLine*>(ref))) mud::ArcLine(  ); }
void mud_ArcLine__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ArcLine*>(ref))) mud::ArcLine( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2]) ); }
void mud_ArcLine__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ArcLine*>(ref))) mud::ArcLine( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<mud::vec3*>(args[3]) ); }
void mud_ArcLine__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ArcLine*>(ref))) mud::ArcLine((*static_cast<mud::ArcLine*>(other))); }
void mud_Capsule__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Capsule*>(ref))) mud::Capsule(  ); }
void mud_Capsule__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Capsule*>(ref))) mud::Capsule( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2]) ); }
void mud_Capsule__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Capsule*>(ref))) mud::Capsule((*static_cast<mud::Capsule*>(other))); }
void mud_Cube__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Cube*>(ref))) mud::Cube(  ); }
void mud_Cube__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Cube*>(ref))) mud::Cube( *static_cast<mud::vec3*>(args[0]) ); }
void mud_Cube__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Cube*>(ref))) mud::Cube( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]) ); }
void mud_Cube__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Cube*>(ref))) mud::Cube((*static_cast<mud::Cube*>(other))); }
void mud_Aabb__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Aabb*>(ref))) mud::Aabb(  ); }
void mud_Aabb__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Aabb*>(ref))) mud::Aabb( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]) ); }
void mud_Aabb__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Aabb*>(ref))) mud::Aabb((*static_cast<mud::Aabb*>(other))); }
void mud_Box__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Box*>(ref))) mud::Box(  ); }
void mud_Box__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Box*>(ref))) mud::Box((*static_cast<mud::Box*>(other))); }
void mud_Circle__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Circle*>(ref))) mud::Circle(  ); }
void mud_Circle__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Circle*>(ref))) mud::Circle( *static_cast<float*>(args[0]), *static_cast<mud::Axis*>(args[1]) ); }
void mud_Circle__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Circle*>(ref))) mud::Circle( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2]) ); }
void mud_Circle__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Circle*>(ref))) mud::Circle((*static_cast<mud::Circle*>(other))); }
void mud_ConvexHull__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ConvexHull*>(ref))) mud::ConvexHull(  ); }
void mud_ConvexHull__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ConvexHull*>(ref))) mud::ConvexHull( *static_cast<vector<mud::vec3>*>(args[0]) ); }
void mud_ConvexHull__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ConvexHull*>(ref))) mud::ConvexHull((*static_cast<mud::ConvexHull*>(other))); }
void mud_Cylinder__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Cylinder*>(ref))) mud::Cylinder(  ); }
void mud_Cylinder__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Cylinder*>(ref))) mud::Cylinder( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2]) ); }
void mud_Cylinder__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Cylinder*>(ref))) mud::Cylinder((*static_cast<mud::Cylinder*>(other))); }
void mud_Ellipsis__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Ellipsis*>(ref))) mud::Ellipsis(  ); }
void mud_Ellipsis__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Ellipsis*>(ref))) mud::Ellipsis( *static_cast<mud::vec2*>(args[0]), *static_cast<mud::Axis*>(args[1]) ); }
void mud_Ellipsis__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Ellipsis*>(ref))) mud::Ellipsis((*static_cast<mud::Ellipsis*>(other))); }
void mud_Geometry__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Geometry*>(ref))) mud::Geometry(  ); }
void mud_Grid2__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Grid2*>(ref))) mud::Grid2(  ); }
void mud_Grid2__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Grid2*>(ref))) mud::Grid2( *static_cast<mud::vec2*>(args[0]), *static_cast<mud::vec2*>(args[1]) ); }
void mud_Grid2__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Grid2*>(ref))) mud::Grid2((*static_cast<mud::Grid2*>(other))); }
void mud_Grid3__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Grid3*>(ref))) mud::Grid3(  ); }
void mud_Grid3__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Grid3*>(ref))) mud::Grid3( *static_cast<mud::uvec2*>(args[0]), *static_cast<vector<mud::vec3>*>(args[1]) ); }
void mud_Grid3__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Grid3*>(ref))) mud::Grid3((*static_cast<mud::Grid3*>(other))); }
void mud_Line__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Line*>(ref))) mud::Line(  ); }
void mud_Line__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Line*>(ref))) mud::Line( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]) ); }
void mud_Line__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Line*>(ref))) mud::Line((*static_cast<mud::Line*>(other))); }
void mud_Points__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Points*>(ref))) mud::Points(  ); }
void mud_Points__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Points*>(ref))) mud::Points( *static_cast<vector<mud::vec3>*>(args[0]) ); }
void mud_Points__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Points*>(ref))) mud::Points((*static_cast<mud::Points*>(other))); }
void mud_Poisson__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Poisson*>(ref))) mud::Poisson( *static_cast<mud::vec2*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Poisson_distribute(void* object, array<void*> args, void*& result) { (*static_cast<vector<mud::vec3>*>(result)) = (*static_cast<mud::Poisson*>(object)).distribute(*static_cast<float*>(args[0])); }
void mud_Poisson_distribute_circles(void* object, array<void*> args, void*& result) { (*static_cast<vector<mud::Circle>*>(result)) = (*static_cast<mud::Poisson*>(object)).distribute_circles(*static_cast<float*>(args[0])); }
void mud_Poisson_addPoint(void* object, array<void*> args, void*& result) { (*static_cast<bool*>(result)) = (*static_cast<mud::Poisson*>(object)).addPoint(*static_cast<float*>(args[0]), *static_cast<mud::vec3*>(args[1])); }
void mud_Polygon__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Polygon*>(ref))) mud::Polygon(  ); }
void mud_Polygon__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Polygon*>(ref))) mud::Polygon( *static_cast<vector<mud::vec3>*>(args[0]) ); }
void mud_Polygon__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Polygon*>(ref))) mud::Polygon((*static_cast<mud::Polygon*>(other))); }
void mud_Quad__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Quad*>(ref))) mud::Quad(  ); }
void mud_Quad__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Quad*>(ref))) mud::Quad( *static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<mud::vec3*>(args[3]) ); }
void mud_Quad__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Quad*>(ref))) mud::Quad((*static_cast<mud::Quad*>(other))); }
void mud_Rect__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Rect*>(ref))) mud::Rect(  ); }
void mud_Rect__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Rect*>(ref))) mud::Rect( *static_cast<mud::vec2*>(args[0]), *static_cast<mud::vec2*>(args[1]) ); }
void mud_Rect__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Rect*>(ref))) mud::Rect( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3]) ); }
void mud_Rect__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Rect*>(ref))) mud::Rect((*static_cast<mud::Rect*>(other))); }
void mud_Ring__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Ring*>(ref))) mud::Ring(  ); }
void mud_Ring__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Ring*>(ref))) mud::Ring( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_Ring__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Ring*>(ref))) mud::Ring((*static_cast<mud::Ring*>(other))); }
void mud_Sphere__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Sphere*>(ref))) mud::Sphere(  ); }
void mud_Sphere__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Sphere*>(ref))) mud::Sphere( *static_cast<float*>(args[0]) ); }
void mud_Sphere__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Sphere*>(ref))) mud::Sphere( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Sphere__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Sphere*>(ref))) mud::Sphere((*static_cast<mud::Sphere*>(other))); }
void mud_SphereRing__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::SphereRing*>(ref))) mud::SphereRing(  ); }
void mud_SphereRing__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::SphereRing*>(ref))) mud::SphereRing( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]) ); }
void mud_SphereRing__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::SphereRing*>(ref))) mud::SphereRing((*static_cast<mud::SphereRing*>(other))); }
void mud_Spheroid__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Spheroid*>(ref))) mud::Spheroid(  ); }
void mud_Spheroid__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Spheroid*>(ref))) mud::Spheroid( *static_cast<float*>(args[0]) ); }
void mud_Spheroid__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Spheroid*>(ref))) mud::Spheroid( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]) ); }
void mud_Spheroid__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Spheroid*>(ref))) mud::Spheroid((*static_cast<mud::Spheroid*>(other))); }
void mud_Torus__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Torus*>(ref))) mud::Torus(  ); }
void mud_Torus__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Torus*>(ref))) mud::Torus( *static_cast<float*>(args[0]), *static_cast<float*>(args[1]), *static_cast<mud::Axis*>(args[2]) ); }
void mud_Torus__construct_2(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Torus*>(ref))) mud::Torus( *static_cast<mud::vec3*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<mud::Axis*>(args[3]) ); }
void mud_Torus__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Torus*>(ref))) mud::Torus((*static_cast<mud::Torus*>(other))); }
void mud_Triangle__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Triangle*>(ref))) mud::Triangle(  ); }
void mud_Triangle__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Triangle*>(ref))) mud::Triangle( *static_cast<mud::vec2*>(args[0]) ); }
void mud_Triangle__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Triangle*>(ref))) mud::Triangle((*static_cast<mud::Triangle*>(other))); }
void mud_to_ray_0(array<void*> args, void*& result) { (*static_cast<mud::Ray*>(result)) = mud::to_ray(*static_cast<mud::vec3*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<float*>(args[2])); }
void mud_to_segment_1(array<void*> args, void*& result) { (*static_cast<mud::Segment*>(result)) = mud::to_segment(*static_cast<mud::Ray*>(args[0])); }
void mud_distribute_poisson_2(array<void*> args, void*& result) { (*static_cast<vector<mud::vec3>*>(result)) = mud::distribute_poisson(*static_cast<mud::vec2*>(args[0]), *static_cast<float*>(args[1])); }

namespace mud
{
	void mud_geom_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
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
		static cstring ids[] = { "Points", "Lines", "LineLoop", "LineStrip", "Triangles", "TriangleStrip", "TriangleFan" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static mud::PrimitiveType vars[] = { mud::PrimitiveType::Points, mud::PrimitiveType::Lines, mud::PrimitiveType::LineLoop, mud::PrimitiveType::LineStrip, mud::PrimitiveType::Triangles, mud::PrimitiveType::TriangleStrip, mud::PrimitiveType::TriangleFan};
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
		Type& t = type<vector<mud::Circle>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Circle>", sizeof(vector<mud::Circle>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Circle>(),
		                             vector_mud_Circle___size,
		                             vector_mud_Circle___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Circle___add,
		                             vector_mud_Circle___remove };
		g_sequence[t.m_id] = &sequence;
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
	// mud::MeshPacker
	{
		Type& t = type<mud::MeshPacker>();
		static Meta meta = { t, &namspc({ "mud" }), "MeshPacker", sizeof(mud::MeshPacker), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_MeshPacker__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_MeshPacker__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
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
		static Meta meta = { t, &namspc({ "mud" }), "ShapeVar", sizeof(mud::ShapeVar), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ShapeVar__construct_0, {} },
			{ t, mud_ShapeVar__construct_1, { { "shape", type<mud::Shape>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ShapeVar__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Shape>(), "shape", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_ShapeVar__get_shape }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
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
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Symbol__construct_0, { { "fill", type<mud::Colour>(), Param::Default }, { "outline", type<mud::Colour>(), Param::Default }, { "overlay", type<bool>(), Param::Default }, { "double_sided", type<bool>(), Param::Default }, { "detail", type<mud::SymbolDetail>(), Param::Default } } }
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
			{ t, offsetof(mud::Symbol, m_image256), type<mud::Image256>(), "image256", image256_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
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
		static mud::vec3 start_default = Zero3;
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
			{ t, offsetof(mud::ArcLine, m_start), type<mud::vec3>(), "start", &start_default, Member::Value, nullptr },
			{ t, offsetof(mud::ArcLine, m_middle), type<mud::vec3>(), "middle", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ArcLine, m_end), type<mud::vec3>(), "end", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
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
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Capsule__construct_0, {} },
			{ t, mud_Capsule__construct_1, { { "radius", type<float>(),  }, { "height", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default } } }
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
	// mud::Cube
	{
		Type& t = type<mud::Cube>();
		static Meta meta = { t, &namspc({ "mud" }), "Cube", sizeof(mud::Cube), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<mud::Shape>() };
		static size_t bases_offsets[] = { base_offset<mud::Cube, mud::Shape>() };
		// defaults
		static mud::vec3 extents_default = mud::vec3{0.5f};
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
			{ t, offsetof(mud::Cube, m_extents), type<mud::vec3>(), "extents", &extents_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Aabb
	{
		Type& t = type<mud::Aabb>();
		static Meta meta = { t, &namspc({ "mud" }), "Aabb", sizeof(mud::Aabb), TypeClass::Struct };
		// bases
		//static Type* bases[] = { &type<mud::Cube>() };
		//static size_t bases_offsets[] = { base_offset<mud::Aabb, mud::Cube>() };
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
			{ t, offsetof(mud::Aabb, m_empty), type<bool>(), "empty", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
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
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Circle__construct_0, {} },
			{ t, mud_Circle__construct_1, { { "radius", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default } } },
			{ t, mud_Circle__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default } } }
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
			{ t, mud_ConvexHull__construct_1, { { "vertices", type<vector<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ConvexHull__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::ConvexHull, m_vertices), type<vector<mud::vec3>>(), "vertices", nullptr, Member::Value, nullptr }
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
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Cylinder__construct_0, {} },
			{ t, mud_Cylinder__construct_1, { { "radius", type<float>(),  }, { "height", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default } } }
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
		static mud::vec2 radius_default = Unit2;
		static mud::Axis axis_default = mud::Axis::Y;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Ellipsis__construct_0, {} },
			{ t, mud_Ellipsis__construct_1, { { "radius", type<mud::vec2>(),  }, { "axis", type<mud::Axis>(), Param::Default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Ellipsis__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Ellipsis, m_radius), type<mud::vec2>(), "radius", &radius_default, Member::Value, nullptr },
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
		static mud::vec2 size_default = mud::vec2{1.f};
		static mud::vec2 space_default = mud::vec2{0.1f};
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Grid2__construct_0, {} },
			{ t, mud_Grid2__construct_1, { { "size", type<mud::vec2>(),  }, { "space", type<mud::vec2>(), Param::Default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Grid2__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Grid2, m_size), type<mud::vec2>(), "size", &size_default, Member::Value, nullptr },
			{ t, offsetof(mud::Grid2, m_space), type<mud::vec2>(), "space", &space_default, Member::Value, nullptr }
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
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Grid3__construct_0, {} },
			{ t, mud_Grid3__construct_1, { { "size", type<mud::uvec2>(),  }, { "points", type<vector<mud::vec3>>(), Param::Default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Grid3__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Grid3, m_size), type<mud::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Grid3, m_points), type<vector<mud::vec3>>(), "points", nullptr, Member::Value, nullptr }
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
		static mud::vec3 start_default = Zero3;
		static mud::vec3 end_default = Unit3;
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
			{ t, offsetof(mud::Line, m_start), type<mud::vec3>(), "start", &start_default, Member::Value, nullptr },
			{ t, offsetof(mud::Line, m_end), type<mud::vec3>(), "end", &end_default, Member::Value, nullptr }
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
			{ t, mud_Points__construct_1, { { "points", type<vector<mud::vec3>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Points__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Points, m_points), type<vector<mud::vec3>>(), "points", nullptr, Member::Value, nullptr }
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
			{ t, "distribute", Address(), mud_Poisson_distribute, { { "radius", type<float>(),  } }, { &type<vector<mud::vec3>>(), QualType::None } },
			{ t, "distribute_circles", Address(), mud_Poisson_distribute_circles, { { "radius", type<float>(),  } }, { &type<vector<mud::Circle>>(), QualType::None } },
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
			{ t, mud_Polygon__construct_1, { { "vertices", type<vector<mud::vec3>>(),  } } }
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
		static mud::vec2 position_default = Zero2;
		static mud::vec2 size_default = Unit2;
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
			{ t, offsetof(mud::Rect, m_position), type<mud::vec2>(), "position", &position_default, Member::Value, nullptr },
			{ t, offsetof(mud::Rect, m_size), type<mud::vec2>(), "size", &size_default, Member::Value, nullptr }
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
			{ t, offsetof(mud::SphereRing, m_min), type<float>(), "min", nullptr, Member::Value, nullptr },
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
		static float solid_radius_default = 1.f;
		static mud::Axis axis_default = mud::Axis::X;
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Torus__construct_0, {} },
			{ t, mud_Torus__construct_1, { { "radius", type<float>(),  }, { "solid_radius", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default } } },
			{ t, mud_Torus__construct_2, { { "center", type<mud::vec3>(),  }, { "radius", type<float>(),  }, { "solid_radius", type<float>(),  }, { "axis", type<mud::Axis>(), Param::Default } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Torus__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Torus, m_radius), type<float>(), "radius", &radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Torus, m_solid_radius), type<float>(), "solid_radius", &solid_radius_default, Member::Value, nullptr },
			{ t, offsetof(mud::Torus, m_axis), type<mud::Axis>(), "axis", &axis_default, Member::Value, nullptr }
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
		static mud::vec2 size_default = Unit2;
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
			{ t, offsetof(mud::Triangle, m_size), type<mud::vec2>(), "size", &size_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
		m.m_types.push_back(&type<mud::Distribution>());
		m.m_types.push_back(&type<mud::DrawMode>());
		m.m_types.push_back(&type<mud::Face3>());
		m.m_types.push_back(&type<mud::MeshPacker>());
		m.m_types.push_back(&type<mud::Plane>());
		m.m_types.push_back(&type<mud::Plane3>());
		m.m_types.push_back(&type<mud::PrimitiveType>());
		m.m_types.push_back(&type<mud::Ray>());
		m.m_types.push_back(&type<mud::Segment>());
		m.m_types.push_back(&type<mud::Shape>());
		m.m_types.push_back(&type<mud::ShapeVar>());
		m.m_types.push_back(&type<mud::Symbol>());
		m.m_types.push_back(&type<mud::SymbolDetail>());
		m.m_types.push_back(&type<vector<mud::Circle>>());
		m.m_types.push_back(&type<mud::Aabb>());
		m.m_types.push_back(&type<mud::Arc>());
		m.m_types.push_back(&type<mud::ArcLine>());
		m.m_types.push_back(&type<mud::Box>());
		m.m_types.push_back(&type<mud::Capsule>());
		m.m_types.push_back(&type<mud::Circle>());
		m.m_types.push_back(&type<mud::ConvexHull>());
		m.m_types.push_back(&type<mud::Cube>());
		m.m_types.push_back(&type<mud::Cylinder>());
		m.m_types.push_back(&type<mud::Ellipsis>());
		m.m_types.push_back(&type<mud::Geometry>());
		m.m_types.push_back(&type<mud::Grid2>());
		m.m_types.push_back(&type<mud::Grid3>());
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
		m.m_types.push_back(&type<mud::Triangle>());
		{
			static Function f = { &namspc({ "mud" }), "to_ray", nullptr, mud_to_ray_0, { { "pos", type<mud::vec3>(),  }, { "dir", type<mud::vec3>(),  }, { "distance", type<float>(), Param::Default } }, { &type<mud::Ray>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "to_segment", nullptr, mud_to_segment_1, { { "ray", type<mud::Ray>(),  } }, { &type<mud::Segment>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud" }), "distribute_poisson", nullptr, mud_distribute_poisson_2, { { "size", type<mud::vec2>(),  }, { "radius", type<float>(),  } }, { &type<vector<mud::vec3>>(), QualType::None } };
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
