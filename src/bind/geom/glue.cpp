#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Distribution
	void EMSCRIPTEN_KEEPALIVE mud_Distribution___destroy__(mud::Distribution* self) {
		delete self;
	}
	// Face3
	mud::Face3* EMSCRIPTEN_KEEPALIVE mud_Face3_Face3_0() {
		return new mud::Face3();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Face3___destroy__(mud::Face3* self) {
		delete self;
	}
	// MeshPacker
	mud::MeshPacker* EMSCRIPTEN_KEEPALIVE mud_MeshPacker_MeshPacker_0() {
		return new mud::MeshPacker();
	}
	void EMSCRIPTEN_KEEPALIVE mud_MeshPacker___destroy__(mud::MeshPacker* self) {
		delete self;
	}
	// Plane
	mud::Plane* EMSCRIPTEN_KEEPALIVE mud_Plane_Plane_0() {
		return new mud::Plane();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Plane_get_normal(mud::Plane* self) {
		static mud::vec3 temp;
		return (temp = self->m_normal, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Plane_set_normal(mud::Plane* self, mud::vec3* value) {
		self->m_normal = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Plane_get_distance(mud::Plane* self) {
		return self->m_distance;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Plane_set_distance(mud::Plane* self, float value) {
		self->m_distance = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Plane___destroy__(mud::Plane* self) {
		delete self;
	}
	// Plane3
	mud::Plane3* EMSCRIPTEN_KEEPALIVE mud_Plane3_Plane3_0() {
		return new mud::Plane3();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Plane3_get_origin(mud::Plane3* self) {
		static mud::vec3 temp;
		return (temp = self->m_origin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Plane3_set_origin(mud::Plane3* self, mud::vec3* value) {
		self->m_origin = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Plane3_get_a(mud::Plane3* self) {
		static mud::vec3 temp;
		return (temp = self->m_a, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Plane3_set_a(mud::Plane3* self, mud::vec3* value) {
		self->m_a = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Plane3_get_b(mud::Plane3* self) {
		static mud::vec3 temp;
		return (temp = self->m_b, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Plane3_set_b(mud::Plane3* self, mud::vec3* value) {
		self->m_b = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Plane3___destroy__(mud::Plane3* self) {
		delete self;
	}
	// Ray
	mud::Ray* EMSCRIPTEN_KEEPALIVE mud_Ray_Ray_0() {
		return new mud::Ray();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Ray_get_start(mud::Ray* self) {
		static mud::vec3 temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ray_set_start(mud::Ray* self, mud::vec3* value) {
		self->m_start = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Ray_get_end(mud::Ray* self) {
		static mud::vec3 temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ray_set_end(mud::Ray* self, mud::vec3* value) {
		self->m_end = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Ray_get_dir(mud::Ray* self) {
		static mud::vec3 temp;
		return (temp = self->m_dir, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ray_set_dir(mud::Ray* self, mud::vec3* value) {
		self->m_dir = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Ray_get_inv_dir(mud::Ray* self) {
		static mud::vec3 temp;
		return (temp = self->m_inv_dir, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ray_set_inv_dir(mud::Ray* self, mud::vec3* value) {
		self->m_inv_dir = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ray___destroy__(mud::Ray* self) {
		delete self;
	}
	// Segment
	mud::Segment* EMSCRIPTEN_KEEPALIVE mud_Segment_Segment_0() {
		return new mud::Segment();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Segment_get_start(mud::Segment* self) {
		static mud::vec3 temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Segment_set_start(mud::Segment* self, mud::vec3* value) {
		self->m_start = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Segment_get_end(mud::Segment* self) {
		static mud::vec3 temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Segment_set_end(mud::Segment* self, mud::vec3* value) {
		self->m_end = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Segment___destroy__(mud::Segment* self) {
		delete self;
	}
	// Shape
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_Shape_get_type(mud::Shape* self) {
		return &self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Shape___destroy__(mud::Shape* self) {
		delete self;
	}
	// ShapeVar
	mud::ShapeVar* EMSCRIPTEN_KEEPALIVE mud_ShapeVar_ShapeVar_0() {
		return new mud::ShapeVar();
	}
	mud::ShapeVar* EMSCRIPTEN_KEEPALIVE mud_ShapeVar_ShapeVar_1(const mud::Shape* shape) {
		return new mud::ShapeVar(*shape);
	}
	mud::Shape* EMSCRIPTEN_KEEPALIVE mud_ShapeVar_get_shape(mud::ShapeVar* self) {
		return &self->shape();
	}
	void EMSCRIPTEN_KEEPALIVE mud_ShapeVar___destroy__(mud::ShapeVar* self) {
		delete self;
	}
	// Symbol
	mud::Symbol* EMSCRIPTEN_KEEPALIVE mud_Symbol_Symbol_0() {
		return new mud::Symbol();
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE mud_Symbol_Symbol_1(mud::Colour* fill) {
		return new mud::Symbol(*fill);
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE mud_Symbol_Symbol_2(mud::Colour* fill, mud::Colour* outline) {
		return new mud::Symbol(*fill, *outline);
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE mud_Symbol_Symbol_3(mud::Colour* fill, mud::Colour* outline, bool overlay) {
		return new mud::Symbol(*fill, *outline, overlay);
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE mud_Symbol_Symbol_4(mud::Colour* fill, mud::Colour* outline, bool overlay, bool double_sided) {
		return new mud::Symbol(*fill, *outline, overlay, double_sided);
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE mud_Symbol_Symbol_5(mud::Colour* fill, mud::Colour* outline, bool overlay, bool double_sided, mud::SymbolDetail detail) {
		return new mud::Symbol(*fill, *outline, overlay, double_sided, detail);
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Symbol_get_outline(mud::Symbol* self) {
		static mud::Colour temp;
		return (temp = self->m_outline, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol_set_outline(mud::Symbol* self, mud::Colour* value) {
		self->m_outline = *value;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE mud_Symbol_get_fill(mud::Symbol* self) {
		static mud::Colour temp;
		return (temp = self->m_fill, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol_set_fill(mud::Symbol* self, mud::Colour* value) {
		self->m_fill = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Symbol_get_overlay(mud::Symbol* self) {
		return self->m_overlay;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol_set_overlay(mud::Symbol* self, bool value) {
		self->m_overlay = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Symbol_get_double_sided(mud::Symbol* self) {
		return self->m_double_sided;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol_set_double_sided(mud::Symbol* self, bool value) {
		self->m_double_sided = value;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE mud_Symbol_get_detail(mud::Symbol* self) {
		return self->m_detail;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol_set_detail(mud::Symbol* self, mud::SymbolDetail value) {
		self->m_detail = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Symbol_get_image(mud::Symbol* self) {
		return self->m_image;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol_set_image(mud::Symbol* self, const char* value) {
		self->m_image = value;
	}
	mud::Image256* EMSCRIPTEN_KEEPALIVE mud_Symbol_get_image256(mud::Symbol* self) {
		return self->m_image256;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol_set_image256(mud::Symbol* self, mud::Image256* value) {
		self->m_image256 = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Symbol_get_program(mud::Symbol* self) {
		return self->m_program;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol_set_program(mud::Symbol* self, const char* value) {
		self->m_program = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Symbol___destroy__(mud::Symbol* self) {
		delete self;
	}
	// Arc
	mud::Arc* EMSCRIPTEN_KEEPALIVE mud_Arc_Arc_0() {
		return new mud::Arc();
	}
	mud::Arc* EMSCRIPTEN_KEEPALIVE mud_Arc_Arc_3(float radius, float start, float end) {
		return new mud::Arc(radius, start, end);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Arc_get_radius(mud::Arc* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Arc_set_radius(mud::Arc* self, float value) {
		self->m_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Arc_get_start(mud::Arc* self) {
		return self->m_start;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Arc_set_start(mud::Arc* self, float value) {
		self->m_start = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Arc_get_end(mud::Arc* self) {
		return self->m_end;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Arc_set_end(mud::Arc* self, float value) {
		self->m_end = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Arc___destroy__(mud::Arc* self) {
		delete self;
	}
	// ArcLine
	mud::ArcLine* EMSCRIPTEN_KEEPALIVE mud_ArcLine_ArcLine_0() {
		return new mud::ArcLine();
	}
	mud::ArcLine* EMSCRIPTEN_KEEPALIVE mud_ArcLine_ArcLine_3(const mud::vec3* center, const mud::vec3* start, const mud::vec3* middle) {
		return new mud::ArcLine(*center, *start, *middle);
	}
	mud::ArcLine* EMSCRIPTEN_KEEPALIVE mud_ArcLine_ArcLine_4(const mud::vec3* center, const mud::vec3* start, const mud::vec3* middle, const mud::vec3* end) {
		return new mud::ArcLine(*center, *start, *middle, *end);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_ArcLine_get_start(mud::ArcLine* self) {
		static mud::vec3 temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ArcLine_set_start(mud::ArcLine* self, mud::vec3* value) {
		self->m_start = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_ArcLine_get_middle(mud::ArcLine* self) {
		static mud::vec3 temp;
		return (temp = self->m_middle, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ArcLine_set_middle(mud::ArcLine* self, mud::vec3* value) {
		self->m_middle = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_ArcLine_get_end(mud::ArcLine* self) {
		static mud::vec3 temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ArcLine_set_end(mud::ArcLine* self, mud::vec3* value) {
		self->m_end = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_ArcLine___destroy__(mud::ArcLine* self) {
		delete self;
	}
	// Capsule
	mud::Capsule* EMSCRIPTEN_KEEPALIVE mud_Capsule_Capsule_0() {
		return new mud::Capsule();
	}
	mud::Capsule* EMSCRIPTEN_KEEPALIVE mud_Capsule_Capsule_2(float radius, float height) {
		return new mud::Capsule(radius, height);
	}
	mud::Capsule* EMSCRIPTEN_KEEPALIVE mud_Capsule_Capsule_3(float radius, float height, mud::Axis axis) {
		return new mud::Capsule(radius, height, axis);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Capsule_get_radius(mud::Capsule* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Capsule_set_radius(mud::Capsule* self, float value) {
		self->m_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Capsule_get_height(mud::Capsule* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Capsule_set_height(mud::Capsule* self, float value) {
		self->m_height = value;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE mud_Capsule_get_axis(mud::Capsule* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Capsule_set_axis(mud::Capsule* self, mud::Axis value) {
		self->m_axis = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Capsule___destroy__(mud::Capsule* self) {
		delete self;
	}
	// Cube
	mud::Cube* EMSCRIPTEN_KEEPALIVE mud_Cube_Cube_0() {
		return new mud::Cube();
	}
	mud::Cube* EMSCRIPTEN_KEEPALIVE mud_Cube_Cube_1(const mud::vec3* center) {
		return new mud::Cube(*center);
	}
	mud::Cube* EMSCRIPTEN_KEEPALIVE mud_Cube_Cube_2(const mud::vec3* center, const mud::vec3* extents) {
		return new mud::Cube(*center, *extents);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Cube_get_extents(mud::Cube* self) {
		static mud::vec3 temp;
		return (temp = self->m_extents, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Cube_set_extents(mud::Cube* self, mud::vec3* value) {
		self->m_extents = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Cube___destroy__(mud::Cube* self) {
		delete self;
	}
	// Aabb
	mud::Aabb* EMSCRIPTEN_KEEPALIVE mud_Aabb_Aabb_0() {
		return new mud::Aabb();
	}
	mud::Aabb* EMSCRIPTEN_KEEPALIVE mud_Aabb_Aabb_2(const mud::vec3* center, const mud::vec3* extents) {
		return new mud::Aabb(*center, *extents);
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Aabb_get_empty(mud::Aabb* self) {
		return self->m_empty;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Aabb_set_empty(mud::Aabb* self, bool value) {
		self->m_empty = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Aabb___destroy__(mud::Aabb* self) {
		delete self;
	}
	// Box
	mud::Box* EMSCRIPTEN_KEEPALIVE mud_Box_Box_0() {
		return new mud::Box();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Box___destroy__(mud::Box* self) {
		delete self;
	}
	// Circle
	mud::Circle* EMSCRIPTEN_KEEPALIVE mud_Circle_Circle_0() {
		return new mud::Circle();
	}
	mud::Circle* EMSCRIPTEN_KEEPALIVE mud_Circle_Circle_1(float radius) {
		return new mud::Circle(radius);
	}
	mud::Circle* EMSCRIPTEN_KEEPALIVE mud_Circle_Circle_2(float radius, mud::Axis axis) {
		return new mud::Circle(radius, axis);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Circle_get_radius(mud::Circle* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Circle_set_radius(mud::Circle* self, float value) {
		self->m_radius = value;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE mud_Circle_get_axis(mud::Circle* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Circle_set_axis(mud::Circle* self, mud::Axis value) {
		self->m_axis = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Circle___destroy__(mud::Circle* self) {
		delete self;
	}
	// ConvexHull
	mud::ConvexHull* EMSCRIPTEN_KEEPALIVE mud_ConvexHull_ConvexHull_0() {
		return new mud::ConvexHull();
	}
	mud::ConvexHull* EMSCRIPTEN_KEEPALIVE mud_ConvexHull_ConvexHull_1(const std::vector<mud::vec3>* vertices) {
		return new mud::ConvexHull(*vertices);
	}
	void EMSCRIPTEN_KEEPALIVE mud_ConvexHull___destroy__(mud::ConvexHull* self) {
		delete self;
	}
	// Cylinder
	mud::Cylinder* EMSCRIPTEN_KEEPALIVE mud_Cylinder_Cylinder_0() {
		return new mud::Cylinder();
	}
	mud::Cylinder* EMSCRIPTEN_KEEPALIVE mud_Cylinder_Cylinder_2(float radius, float height) {
		return new mud::Cylinder(radius, height);
	}
	mud::Cylinder* EMSCRIPTEN_KEEPALIVE mud_Cylinder_Cylinder_3(float radius, float height, mud::Axis axis) {
		return new mud::Cylinder(radius, height, axis);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Cylinder_get_radius(mud::Cylinder* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Cylinder_set_radius(mud::Cylinder* self, float value) {
		self->m_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Cylinder_get_height(mud::Cylinder* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Cylinder_set_height(mud::Cylinder* self, float value) {
		self->m_height = value;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE mud_Cylinder_get_axis(mud::Cylinder* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Cylinder_set_axis(mud::Cylinder* self, mud::Axis value) {
		self->m_axis = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Cylinder___destroy__(mud::Cylinder* self) {
		delete self;
	}
	// Ellipsis
	mud::Ellipsis* EMSCRIPTEN_KEEPALIVE mud_Ellipsis_Ellipsis_0() {
		return new mud::Ellipsis();
	}
	mud::Ellipsis* EMSCRIPTEN_KEEPALIVE mud_Ellipsis_Ellipsis_1(mud::vec2* radius) {
		return new mud::Ellipsis(*radius);
	}
	mud::Ellipsis* EMSCRIPTEN_KEEPALIVE mud_Ellipsis_Ellipsis_2(mud::vec2* radius, mud::Axis axis) {
		return new mud::Ellipsis(*radius, axis);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Ellipsis_get_radius(mud::Ellipsis* self) {
		static mud::vec2 temp;
		return (temp = self->m_radius, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ellipsis_set_radius(mud::Ellipsis* self, mud::vec2* value) {
		self->m_radius = *value;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE mud_Ellipsis_get_axis(mud::Ellipsis* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ellipsis_set_axis(mud::Ellipsis* self, mud::Axis value) {
		self->m_axis = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ellipsis___destroy__(mud::Ellipsis* self) {
		delete self;
	}
	// Geometry
	mud::Geometry* EMSCRIPTEN_KEEPALIVE mud_Geometry_Geometry_0() {
		return new mud::Geometry();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Geometry___destroy__(mud::Geometry* self) {
		delete self;
	}
	// Grid2
	mud::Grid2* EMSCRIPTEN_KEEPALIVE mud_Grid2_Grid2_0() {
		return new mud::Grid2();
	}
	mud::Grid2* EMSCRIPTEN_KEEPALIVE mud_Grid2_Grid2_1(const mud::vec2* size) {
		return new mud::Grid2(*size);
	}
	mud::Grid2* EMSCRIPTEN_KEEPALIVE mud_Grid2_Grid2_2(const mud::vec2* size, const mud::vec2* space) {
		return new mud::Grid2(*size, *space);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Grid2_get_size(mud::Grid2* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Grid2_set_size(mud::Grid2* self, mud::vec2* value) {
		self->m_size = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Grid2_get_space(mud::Grid2* self) {
		static mud::vec2 temp;
		return (temp = self->m_space, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Grid2_set_space(mud::Grid2* self, mud::vec2* value) {
		self->m_space = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Grid2___destroy__(mud::Grid2* self) {
		delete self;
	}
	// Grid3
	mud::Grid3* EMSCRIPTEN_KEEPALIVE mud_Grid3_Grid3_0() {
		return new mud::Grid3();
	}
	mud::Grid3* EMSCRIPTEN_KEEPALIVE mud_Grid3_Grid3_1(const mud::uvec2* size) {
		return new mud::Grid3(*size);
	}
	mud::Grid3* EMSCRIPTEN_KEEPALIVE mud_Grid3_Grid3_2(const mud::uvec2* size, const std::vector<mud::vec3>* points) {
		return new mud::Grid3(*size, *points);
	}
	mud::uvec2* EMSCRIPTEN_KEEPALIVE mud_Grid3_get_size(mud::Grid3* self) {
		static mud::uvec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Grid3_set_size(mud::Grid3* self, mud::uvec2* value) {
		self->m_size = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Grid3___destroy__(mud::Grid3* self) {
		delete self;
	}
	// Line
	mud::Line* EMSCRIPTEN_KEEPALIVE mud_Line_Line_0() {
		return new mud::Line();
	}
	mud::Line* EMSCRIPTEN_KEEPALIVE mud_Line_Line_2(const mud::vec3* start, const mud::vec3* end) {
		return new mud::Line(*start, *end);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Line_get_start(mud::Line* self) {
		static mud::vec3 temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Line_set_start(mud::Line* self, mud::vec3* value) {
		self->m_start = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_Line_get_end(mud::Line* self) {
		static mud::vec3 temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Line_set_end(mud::Line* self, mud::vec3* value) {
		self->m_end = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Line___destroy__(mud::Line* self) {
		delete self;
	}
	// Points
	mud::Points* EMSCRIPTEN_KEEPALIVE mud_Points_Points_0() {
		return new mud::Points();
	}
	mud::Points* EMSCRIPTEN_KEEPALIVE mud_Points_Points_1(const std::vector<mud::vec3>* points) {
		return new mud::Points(*points);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Points___destroy__(mud::Points* self) {
		delete self;
	}
	// Poisson
	mud::Poisson* EMSCRIPTEN_KEEPALIVE mud_Poisson_Poisson_2(mud::vec2* size, float maxRadius) {
		return new mud::Poisson(*size, maxRadius);
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Poisson_addPoint_2(mud::Poisson* self, float radius, mud::vec3* point) {
		return self->addPoint(radius, *point);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Poisson___destroy__(mud::Poisson* self) {
		delete self;
	}
	// Polygon
	mud::Polygon* EMSCRIPTEN_KEEPALIVE mud_Polygon_Polygon_0() {
		return new mud::Polygon();
	}
	mud::Polygon* EMSCRIPTEN_KEEPALIVE mud_Polygon_Polygon_1(std::vector<mud::vec3>* vertices) {
		return new mud::Polygon(*vertices);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Polygon___destroy__(mud::Polygon* self) {
		delete self;
	}
	// Quad
	mud::Quad* EMSCRIPTEN_KEEPALIVE mud_Quad_Quad_0() {
		return new mud::Quad();
	}
	mud::Quad* EMSCRIPTEN_KEEPALIVE mud_Quad_Quad_4(const mud::vec3* a, const mud::vec3* b, const mud::vec3* c, const mud::vec3* d) {
		return new mud::Quad(*a, *b, *c, *d);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Quad___destroy__(mud::Quad* self) {
		delete self;
	}
	// Rect
	mud::Rect* EMSCRIPTEN_KEEPALIVE mud_Rect_Rect_0() {
		return new mud::Rect();
	}
	mud::Rect* EMSCRIPTEN_KEEPALIVE mud_Rect_Rect_2(const mud::vec2* position, const mud::vec2* size) {
		return new mud::Rect(*position, *size);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Rect_get_position(mud::Rect* self) {
		static mud::vec2 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Rect_set_position(mud::Rect* self, mud::vec2* value) {
		self->m_position = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Rect_get_size(mud::Rect* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Rect_set_size(mud::Rect* self, mud::vec2* value) {
		self->m_size = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Rect___destroy__(mud::Rect* self) {
		delete self;
	}
	// Ring
	mud::Ring* EMSCRIPTEN_KEEPALIVE mud_Ring_Ring_0() {
		return new mud::Ring();
	}
	mud::Ring* EMSCRIPTEN_KEEPALIVE mud_Ring_Ring_3(float radius, float min, float max) {
		return new mud::Ring(radius, min, max);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Ring_get_radius(mud::Ring* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ring_set_radius(mud::Ring* self, float value) {
		self->m_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Ring_get_min(mud::Ring* self) {
		return self->m_min;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ring_set_min(mud::Ring* self, float value) {
		self->m_min = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Ring_get_max(mud::Ring* self) {
		return self->m_max;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ring_set_max(mud::Ring* self, float value) {
		self->m_max = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Ring___destroy__(mud::Ring* self) {
		delete self;
	}
	// Sphere
	mud::Sphere* EMSCRIPTEN_KEEPALIVE mud_Sphere_Sphere_0() {
		return new mud::Sphere();
	}
	mud::Sphere* EMSCRIPTEN_KEEPALIVE mud_Sphere_Sphere_1(float radius) {
		return new mud::Sphere(radius);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Sphere_get_radius(mud::Sphere* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Sphere_set_radius(mud::Sphere* self, float value) {
		self->m_radius = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Sphere___destroy__(mud::Sphere* self) {
		delete self;
	}
	// SphereRing
	mud::SphereRing* EMSCRIPTEN_KEEPALIVE mud_SphereRing_SphereRing_0() {
		return new mud::SphereRing();
	}
	mud::SphereRing* EMSCRIPTEN_KEEPALIVE mud_SphereRing_SphereRing_3(float radius, float min, float max) {
		return new mud::SphereRing(radius, min, max);
	}
	float EMSCRIPTEN_KEEPALIVE mud_SphereRing_get_radius(mud::SphereRing* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_SphereRing_set_radius(mud::SphereRing* self, float value) {
		self->m_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_SphereRing_get_min(mud::SphereRing* self) {
		return self->m_min;
	}
	void EMSCRIPTEN_KEEPALIVE mud_SphereRing_set_min(mud::SphereRing* self, float value) {
		self->m_min = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_SphereRing_get_max(mud::SphereRing* self) {
		return self->m_max;
	}
	void EMSCRIPTEN_KEEPALIVE mud_SphereRing_set_max(mud::SphereRing* self, float value) {
		self->m_max = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_SphereRing___destroy__(mud::SphereRing* self) {
		delete self;
	}
	// Spheroid
	mud::Spheroid* EMSCRIPTEN_KEEPALIVE mud_Spheroid_Spheroid_0() {
		return new mud::Spheroid();
	}
	mud::Spheroid* EMSCRIPTEN_KEEPALIVE mud_Spheroid_Spheroid_1(float radius) {
		return new mud::Spheroid(radius);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Spheroid_get_radius(mud::Spheroid* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Spheroid_set_radius(mud::Spheroid* self, float value) {
		self->m_radius = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Spheroid___destroy__(mud::Spheroid* self) {
		delete self;
	}
	// Torus
	mud::Torus* EMSCRIPTEN_KEEPALIVE mud_Torus_Torus_0() {
		return new mud::Torus();
	}
	mud::Torus* EMSCRIPTEN_KEEPALIVE mud_Torus_Torus_2(float radius, float solid_radius) {
		return new mud::Torus(radius, solid_radius);
	}
	mud::Torus* EMSCRIPTEN_KEEPALIVE mud_Torus_Torus_3(float radius, float solid_radius, mud::Axis axis) {
		return new mud::Torus(radius, solid_radius, axis);
	}
	float EMSCRIPTEN_KEEPALIVE mud_Torus_get_radius(mud::Torus* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Torus_set_radius(mud::Torus* self, float value) {
		self->m_radius = value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_Torus_get_solid_radius(mud::Torus* self) {
		return self->m_solid_radius;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Torus_set_solid_radius(mud::Torus* self, float value) {
		self->m_solid_radius = value;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE mud_Torus_get_axis(mud::Torus* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Torus_set_axis(mud::Torus* self, mud::Axis value) {
		self->m_axis = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Torus___destroy__(mud::Torus* self) {
		delete self;
	}
	// Triangle
	mud::Triangle* EMSCRIPTEN_KEEPALIVE mud_Triangle_Triangle_0() {
		return new mud::Triangle();
	}
	mud::Triangle* EMSCRIPTEN_KEEPALIVE mud_Triangle_Triangle_1(const mud::vec2* size) {
		return new mud::Triangle(*size);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Triangle_get_size(mud::Triangle* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Triangle_set_size(mud::Triangle* self, mud::vec2* value) {
		self->m_size = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Triangle___destroy__(mud::Triangle* self) {
		delete self;
	}
	// DrawMode
	mud::DrawMode EMSCRIPTEN_KEEPALIVE mud_DrawMode_OUTLINE() {
		return mud::OUTLINE;
	}
	mud::DrawMode EMSCRIPTEN_KEEPALIVE mud_DrawMode_PLAIN() {
		return mud::PLAIN;
	}
	// PrimitiveType
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE mud_PrimitiveType_Points() {
		return mud::PrimitiveType::Points;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE mud_PrimitiveType_Lines() {
		return mud::PrimitiveType::Lines;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE mud_PrimitiveType_LineLoop() {
		return mud::PrimitiveType::LineLoop;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE mud_PrimitiveType_LineStrip() {
		return mud::PrimitiveType::LineStrip;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE mud_PrimitiveType_Triangles() {
		return mud::PrimitiveType::Triangles;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE mud_PrimitiveType_TriangleStrip() {
		return mud::PrimitiveType::TriangleStrip;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE mud_PrimitiveType_TriangleFan() {
		return mud::PrimitiveType::TriangleFan;
	}
	// SymbolDetail
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE mud_SymbolDetail_Lowest() {
		return mud::SymbolDetail::Lowest;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE mud_SymbolDetail_Low() {
		return mud::SymbolDetail::Low;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE mud_SymbolDetail_Medium() {
		return mud::SymbolDetail::Medium;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE mud_SymbolDetail_High() {
		return mud::SymbolDetail::High;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE mud_SymbolDetail_Highest() {
		return mud::SymbolDetail::Highest;
	}
	
}


