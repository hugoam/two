#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// Distribution
	void EMSCRIPTEN_KEEPALIVE Distribution___destroy__(mud::Distribution* self) {
		delete self;
	}
	// Face3
	mud::Face3* EMSCRIPTEN_KEEPALIVE Face3_Face3_0() {
		return new mud::Face3();
	}
	void EMSCRIPTEN_KEEPALIVE Face3___destroy__(mud::Face3* self) {
		delete self;
	}
	// MeshPacker
	mud::MeshPacker* EMSCRIPTEN_KEEPALIVE MeshPacker_MeshPacker_0() {
		return new mud::MeshPacker();
	}
	void EMSCRIPTEN_KEEPALIVE MeshPacker___destroy__(mud::MeshPacker* self) {
		delete self;
	}
	// Plane
	mud::Plane* EMSCRIPTEN_KEEPALIVE Plane_Plane_0() {
		return new mud::Plane();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Plane_get_normal(mud::Plane* self) {
		static mud::vec3 temp;
		return (temp = self->m_normal, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Plane_set_normal(mud::Plane* self, mud::vec3* normal) {
		self->m_normal = *normal;
	}
	float EMSCRIPTEN_KEEPALIVE Plane_get_distance(mud::Plane* self) {
		return self->m_distance;
	}
	void EMSCRIPTEN_KEEPALIVE Plane_set_distance(mud::Plane* self, float distance) {
		self->m_distance = distance;
	}
	void EMSCRIPTEN_KEEPALIVE Plane___destroy__(mud::Plane* self) {
		delete self;
	}
	// Plane3
	mud::Plane3* EMSCRIPTEN_KEEPALIVE Plane3_Plane3_0() {
		return new mud::Plane3();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Plane3_get_origin(mud::Plane3* self) {
		static mud::vec3 temp;
		return (temp = self->m_origin, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Plane3_set_origin(mud::Plane3* self, mud::vec3* origin) {
		self->m_origin = *origin;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Plane3_get_a(mud::Plane3* self) {
		static mud::vec3 temp;
		return (temp = self->m_a, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Plane3_set_a(mud::Plane3* self, mud::vec3* a) {
		self->m_a = *a;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Plane3_get_b(mud::Plane3* self) {
		static mud::vec3 temp;
		return (temp = self->m_b, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Plane3_set_b(mud::Plane3* self, mud::vec3* b) {
		self->m_b = *b;
	}
	void EMSCRIPTEN_KEEPALIVE Plane3___destroy__(mud::Plane3* self) {
		delete self;
	}
	// Ray
	mud::Ray* EMSCRIPTEN_KEEPALIVE Ray_Ray_0() {
		return new mud::Ray();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Ray_get_start(mud::Ray* self) {
		static mud::vec3 temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Ray_set_start(mud::Ray* self, mud::vec3* start) {
		self->m_start = *start;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Ray_get_end(mud::Ray* self) {
		static mud::vec3 temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Ray_set_end(mud::Ray* self, mud::vec3* end) {
		self->m_end = *end;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Ray_get_dir(mud::Ray* self) {
		static mud::vec3 temp;
		return (temp = self->m_dir, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Ray_set_dir(mud::Ray* self, mud::vec3* dir) {
		self->m_dir = *dir;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Ray_get_inv_dir(mud::Ray* self) {
		static mud::vec3 temp;
		return (temp = self->m_inv_dir, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Ray_set_inv_dir(mud::Ray* self, mud::vec3* inv_dir) {
		self->m_inv_dir = *inv_dir;
	}
	void EMSCRIPTEN_KEEPALIVE Ray___destroy__(mud::Ray* self) {
		delete self;
	}
	// Segment
	mud::Segment* EMSCRIPTEN_KEEPALIVE Segment_Segment_0() {
		return new mud::Segment();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Segment_get_start(mud::Segment* self) {
		static mud::vec3 temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Segment_set_start(mud::Segment* self, mud::vec3* start) {
		self->m_start = *start;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Segment_get_end(mud::Segment* self) {
		static mud::vec3 temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Segment_set_end(mud::Segment* self, mud::vec3* end) {
		self->m_end = *end;
	}
	void EMSCRIPTEN_KEEPALIVE Segment___destroy__(mud::Segment* self) {
		delete self;
	}
	// Shape
	mud::Type* EMSCRIPTEN_KEEPALIVE Shape_get_type(mud::Shape* self) {
		return &self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE Shape___destroy__(mud::Shape* self) {
		delete self;
	}
	// ShapeVar
	mud::ShapeVar* EMSCRIPTEN_KEEPALIVE ShapeVar_ShapeVar_0() {
		return new mud::ShapeVar();
	}
	mud::ShapeVar* EMSCRIPTEN_KEEPALIVE ShapeVar_ShapeVar_1(const mud::Shape* shape) {
		return new mud::ShapeVar(*shape);
	}
	mud::Shape* EMSCRIPTEN_KEEPALIVE ShapeVar_get_shape(mud::ShapeVar* self) {
		return &self->shape();
	}
	void EMSCRIPTEN_KEEPALIVE ShapeVar___destroy__(mud::ShapeVar* self) {
		delete self;
	}
	// Symbol
	mud::Symbol* EMSCRIPTEN_KEEPALIVE Symbol_Symbol_0() {
		return new mud::Symbol();
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE Symbol_Symbol_1(mud::Colour* fill) {
		return new mud::Symbol(*fill);
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE Symbol_Symbol_2(mud::Colour* fill, mud::Colour* outline) {
		return new mud::Symbol(*fill, *outline);
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE Symbol_Symbol_3(mud::Colour* fill, mud::Colour* outline, bool overlay) {
		return new mud::Symbol(*fill, *outline, overlay);
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE Symbol_Symbol_4(mud::Colour* fill, mud::Colour* outline, bool overlay, bool double_sided) {
		return new mud::Symbol(*fill, *outline, overlay, double_sided);
	}
	mud::Symbol* EMSCRIPTEN_KEEPALIVE Symbol_Symbol_5(mud::Colour* fill, mud::Colour* outline, bool overlay, bool double_sided, mud::SymbolDetail detail) {
		return new mud::Symbol(*fill, *outline, overlay, double_sided, detail);
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Symbol_get_outline(mud::Symbol* self) {
		static mud::Colour temp;
		return (temp = self->m_outline, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Symbol_set_outline(mud::Symbol* self, mud::Colour* outline) {
		self->m_outline = *outline;
	}
	mud::Colour* EMSCRIPTEN_KEEPALIVE Symbol_get_fill(mud::Symbol* self) {
		static mud::Colour temp;
		return (temp = self->m_fill, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Symbol_set_fill(mud::Symbol* self, mud::Colour* fill) {
		self->m_fill = *fill;
	}
	bool EMSCRIPTEN_KEEPALIVE Symbol_get_overlay(mud::Symbol* self) {
		return self->m_overlay;
	}
	void EMSCRIPTEN_KEEPALIVE Symbol_set_overlay(mud::Symbol* self, bool overlay) {
		self->m_overlay = overlay;
	}
	bool EMSCRIPTEN_KEEPALIVE Symbol_get_double_sided(mud::Symbol* self) {
		return self->m_double_sided;
	}
	void EMSCRIPTEN_KEEPALIVE Symbol_set_double_sided(mud::Symbol* self, bool double_sided) {
		self->m_double_sided = double_sided;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE Symbol_get_detail(mud::Symbol* self) {
		return self->m_detail;
	}
	void EMSCRIPTEN_KEEPALIVE Symbol_set_detail(mud::Symbol* self, mud::SymbolDetail detail) {
		self->m_detail = detail;
	}
	const char* EMSCRIPTEN_KEEPALIVE Symbol_get_image(mud::Symbol* self) {
		return self->m_image;
	}
	void EMSCRIPTEN_KEEPALIVE Symbol_set_image(mud::Symbol* self, const char* image) {
		self->m_image = image;
	}
	mud::Image256* EMSCRIPTEN_KEEPALIVE Symbol_get_image256(mud::Symbol* self) {
		return self->m_image256;
	}
	void EMSCRIPTEN_KEEPALIVE Symbol_set_image256(mud::Symbol* self, mud::Image256* image256) {
		self->m_image256 = image256;
	}
	const char* EMSCRIPTEN_KEEPALIVE Symbol_get_program(mud::Symbol* self) {
		return self->m_program;
	}
	void EMSCRIPTEN_KEEPALIVE Symbol_set_program(mud::Symbol* self, const char* program) {
		self->m_program = program;
	}
	void EMSCRIPTEN_KEEPALIVE Symbol___destroy__(mud::Symbol* self) {
		delete self;
	}
	// Arc
	mud::Arc* EMSCRIPTEN_KEEPALIVE Arc_Arc_0() {
		return new mud::Arc();
	}
	mud::Arc* EMSCRIPTEN_KEEPALIVE Arc_Arc_3(float radius, float start, float end) {
		return new mud::Arc(radius, start, end);
	}
	float EMSCRIPTEN_KEEPALIVE Arc_get_radius(mud::Arc* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Arc_set_radius(mud::Arc* self, float radius) {
		self->m_radius = radius;
	}
	float EMSCRIPTEN_KEEPALIVE Arc_get_start(mud::Arc* self) {
		return self->m_start;
	}
	void EMSCRIPTEN_KEEPALIVE Arc_set_start(mud::Arc* self, float start) {
		self->m_start = start;
	}
	float EMSCRIPTEN_KEEPALIVE Arc_get_end(mud::Arc* self) {
		return self->m_end;
	}
	void EMSCRIPTEN_KEEPALIVE Arc_set_end(mud::Arc* self, float end) {
		self->m_end = end;
	}
	void EMSCRIPTEN_KEEPALIVE Arc___destroy__(mud::Arc* self) {
		delete self;
	}
	// ArcLine
	mud::ArcLine* EMSCRIPTEN_KEEPALIVE ArcLine_ArcLine_0() {
		return new mud::ArcLine();
	}
	mud::ArcLine* EMSCRIPTEN_KEEPALIVE ArcLine_ArcLine_3(const mud::vec3* center, const mud::vec3* start, const mud::vec3* middle) {
		return new mud::ArcLine(*center, *start, *middle);
	}
	mud::ArcLine* EMSCRIPTEN_KEEPALIVE ArcLine_ArcLine_4(const mud::vec3* center, const mud::vec3* start, const mud::vec3* middle, const mud::vec3* end) {
		return new mud::ArcLine(*center, *start, *middle, *end);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE ArcLine_get_start(mud::ArcLine* self) {
		static mud::vec3 temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ArcLine_set_start(mud::ArcLine* self, mud::vec3* start) {
		self->m_start = *start;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE ArcLine_get_middle(mud::ArcLine* self) {
		static mud::vec3 temp;
		return (temp = self->m_middle, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ArcLine_set_middle(mud::ArcLine* self, mud::vec3* middle) {
		self->m_middle = *middle;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE ArcLine_get_end(mud::ArcLine* self) {
		static mud::vec3 temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE ArcLine_set_end(mud::ArcLine* self, mud::vec3* end) {
		self->m_end = *end;
	}
	void EMSCRIPTEN_KEEPALIVE ArcLine___destroy__(mud::ArcLine* self) {
		delete self;
	}
	// Capsule
	mud::Capsule* EMSCRIPTEN_KEEPALIVE Capsule_Capsule_0() {
		return new mud::Capsule();
	}
	mud::Capsule* EMSCRIPTEN_KEEPALIVE Capsule_Capsule_2(float radius, float height) {
		return new mud::Capsule(radius, height);
	}
	mud::Capsule* EMSCRIPTEN_KEEPALIVE Capsule_Capsule_3(float radius, float height, mud::Axis axis) {
		return new mud::Capsule(radius, height, axis);
	}
	float EMSCRIPTEN_KEEPALIVE Capsule_get_radius(mud::Capsule* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Capsule_set_radius(mud::Capsule* self, float radius) {
		self->m_radius = radius;
	}
	float EMSCRIPTEN_KEEPALIVE Capsule_get_height(mud::Capsule* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE Capsule_set_height(mud::Capsule* self, float height) {
		self->m_height = height;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE Capsule_get_axis(mud::Capsule* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE Capsule_set_axis(mud::Capsule* self, mud::Axis axis) {
		self->m_axis = axis;
	}
	void EMSCRIPTEN_KEEPALIVE Capsule___destroy__(mud::Capsule* self) {
		delete self;
	}
	// Cube
	mud::Cube* EMSCRIPTEN_KEEPALIVE Cube_Cube_0() {
		return new mud::Cube();
	}
	mud::Cube* EMSCRIPTEN_KEEPALIVE Cube_Cube_1(const mud::vec3* center) {
		return new mud::Cube(*center);
	}
	mud::Cube* EMSCRIPTEN_KEEPALIVE Cube_Cube_2(const mud::vec3* center, const mud::vec3* extents) {
		return new mud::Cube(*center, *extents);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Cube_get_extents(mud::Cube* self) {
		static mud::vec3 temp;
		return (temp = self->m_extents, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Cube_set_extents(mud::Cube* self, mud::vec3* extents) {
		self->m_extents = *extents;
	}
	void EMSCRIPTEN_KEEPALIVE Cube___destroy__(mud::Cube* self) {
		delete self;
	}
	// Aabb
	mud::Aabb* EMSCRIPTEN_KEEPALIVE Aabb_Aabb_0() {
		return new mud::Aabb();
	}
	mud::Aabb* EMSCRIPTEN_KEEPALIVE Aabb_Aabb_2(const mud::vec3* center, const mud::vec3* extents) {
		return new mud::Aabb(*center, *extents);
	}
	bool EMSCRIPTEN_KEEPALIVE Aabb_get_empty(mud::Aabb* self) {
		return self->m_empty;
	}
	void EMSCRIPTEN_KEEPALIVE Aabb_set_empty(mud::Aabb* self, bool empty) {
		self->m_empty = empty;
	}
	void EMSCRIPTEN_KEEPALIVE Aabb___destroy__(mud::Aabb* self) {
		delete self;
	}
	// Box
	mud::Box* EMSCRIPTEN_KEEPALIVE Box_Box_0() {
		return new mud::Box();
	}
	void EMSCRIPTEN_KEEPALIVE Box___destroy__(mud::Box* self) {
		delete self;
	}
	// Circle
	mud::Circle* EMSCRIPTEN_KEEPALIVE Circle_Circle_0() {
		return new mud::Circle();
	}
	mud::Circle* EMSCRIPTEN_KEEPALIVE Circle_Circle_1(float radius) {
		return new mud::Circle(radius);
	}
	mud::Circle* EMSCRIPTEN_KEEPALIVE Circle_Circle_2(float radius, mud::Axis axis) {
		return new mud::Circle(radius, axis);
	}
	float EMSCRIPTEN_KEEPALIVE Circle_get_radius(mud::Circle* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Circle_set_radius(mud::Circle* self, float radius) {
		self->m_radius = radius;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE Circle_get_axis(mud::Circle* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE Circle_set_axis(mud::Circle* self, mud::Axis axis) {
		self->m_axis = axis;
	}
	void EMSCRIPTEN_KEEPALIVE Circle___destroy__(mud::Circle* self) {
		delete self;
	}
	// ConvexHull
	mud::ConvexHull* EMSCRIPTEN_KEEPALIVE ConvexHull_ConvexHull_0() {
		return new mud::ConvexHull();
	}
	mud::ConvexHull* EMSCRIPTEN_KEEPALIVE ConvexHull_ConvexHull_1(const std::vector<mud::vec3>* vertices) {
		return new mud::ConvexHull(*vertices);
	}
	void EMSCRIPTEN_KEEPALIVE ConvexHull___destroy__(mud::ConvexHull* self) {
		delete self;
	}
	// Cylinder
	mud::Cylinder* EMSCRIPTEN_KEEPALIVE Cylinder_Cylinder_0() {
		return new mud::Cylinder();
	}
	mud::Cylinder* EMSCRIPTEN_KEEPALIVE Cylinder_Cylinder_2(float radius, float height) {
		return new mud::Cylinder(radius, height);
	}
	mud::Cylinder* EMSCRIPTEN_KEEPALIVE Cylinder_Cylinder_3(float radius, float height, mud::Axis axis) {
		return new mud::Cylinder(radius, height, axis);
	}
	float EMSCRIPTEN_KEEPALIVE Cylinder_get_radius(mud::Cylinder* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Cylinder_set_radius(mud::Cylinder* self, float radius) {
		self->m_radius = radius;
	}
	float EMSCRIPTEN_KEEPALIVE Cylinder_get_height(mud::Cylinder* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE Cylinder_set_height(mud::Cylinder* self, float height) {
		self->m_height = height;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE Cylinder_get_axis(mud::Cylinder* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE Cylinder_set_axis(mud::Cylinder* self, mud::Axis axis) {
		self->m_axis = axis;
	}
	void EMSCRIPTEN_KEEPALIVE Cylinder___destroy__(mud::Cylinder* self) {
		delete self;
	}
	// Ellipsis
	mud::Ellipsis* EMSCRIPTEN_KEEPALIVE Ellipsis_Ellipsis_0() {
		return new mud::Ellipsis();
	}
	mud::Ellipsis* EMSCRIPTEN_KEEPALIVE Ellipsis_Ellipsis_1(mud::vec2* radius) {
		return new mud::Ellipsis(*radius);
	}
	mud::Ellipsis* EMSCRIPTEN_KEEPALIVE Ellipsis_Ellipsis_2(mud::vec2* radius, mud::Axis axis) {
		return new mud::Ellipsis(*radius, axis);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Ellipsis_get_radius(mud::Ellipsis* self) {
		static mud::vec2 temp;
		return (temp = self->m_radius, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Ellipsis_set_radius(mud::Ellipsis* self, mud::vec2* radius) {
		self->m_radius = *radius;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE Ellipsis_get_axis(mud::Ellipsis* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE Ellipsis_set_axis(mud::Ellipsis* self, mud::Axis axis) {
		self->m_axis = axis;
	}
	void EMSCRIPTEN_KEEPALIVE Ellipsis___destroy__(mud::Ellipsis* self) {
		delete self;
	}
	// Geometry
	mud::Geometry* EMSCRIPTEN_KEEPALIVE Geometry_Geometry_0() {
		return new mud::Geometry();
	}
	void EMSCRIPTEN_KEEPALIVE Geometry___destroy__(mud::Geometry* self) {
		delete self;
	}
	// Grid2
	mud::Grid2* EMSCRIPTEN_KEEPALIVE Grid2_Grid2_0() {
		return new mud::Grid2();
	}
	mud::Grid2* EMSCRIPTEN_KEEPALIVE Grid2_Grid2_1(const mud::vec2* size) {
		return new mud::Grid2(*size);
	}
	mud::Grid2* EMSCRIPTEN_KEEPALIVE Grid2_Grid2_2(const mud::vec2* size, const mud::vec2* space) {
		return new mud::Grid2(*size, *space);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Grid2_get_size(mud::Grid2* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Grid2_set_size(mud::Grid2* self, mud::vec2* size) {
		self->m_size = *size;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Grid2_get_space(mud::Grid2* self) {
		static mud::vec2 temp;
		return (temp = self->m_space, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Grid2_set_space(mud::Grid2* self, mud::vec2* space) {
		self->m_space = *space;
	}
	void EMSCRIPTEN_KEEPALIVE Grid2___destroy__(mud::Grid2* self) {
		delete self;
	}
	// Grid3
	mud::Grid3* EMSCRIPTEN_KEEPALIVE Grid3_Grid3_0() {
		return new mud::Grid3();
	}
	mud::Grid3* EMSCRIPTEN_KEEPALIVE Grid3_Grid3_1(const mud::uvec2* size) {
		return new mud::Grid3(*size);
	}
	mud::Grid3* EMSCRIPTEN_KEEPALIVE Grid3_Grid3_2(const mud::uvec2* size, const std::vector<mud::vec3>* points) {
		return new mud::Grid3(*size, *points);
	}
	mud::uvec2* EMSCRIPTEN_KEEPALIVE Grid3_get_size(mud::Grid3* self) {
		static mud::uvec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Grid3_set_size(mud::Grid3* self, mud::uvec2* size) {
		self->m_size = *size;
	}
	void EMSCRIPTEN_KEEPALIVE Grid3___destroy__(mud::Grid3* self) {
		delete self;
	}
	// Line
	mud::Line* EMSCRIPTEN_KEEPALIVE Line_Line_0() {
		return new mud::Line();
	}
	mud::Line* EMSCRIPTEN_KEEPALIVE Line_Line_2(const mud::vec3* start, const mud::vec3* end) {
		return new mud::Line(*start, *end);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Line_get_start(mud::Line* self) {
		static mud::vec3 temp;
		return (temp = self->m_start, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Line_set_start(mud::Line* self, mud::vec3* start) {
		self->m_start = *start;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Line_get_end(mud::Line* self) {
		static mud::vec3 temp;
		return (temp = self->m_end, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Line_set_end(mud::Line* self, mud::vec3* end) {
		self->m_end = *end;
	}
	void EMSCRIPTEN_KEEPALIVE Line___destroy__(mud::Line* self) {
		delete self;
	}
	// Points
	mud::Points* EMSCRIPTEN_KEEPALIVE Points_Points_0() {
		return new mud::Points();
	}
	mud::Points* EMSCRIPTEN_KEEPALIVE Points_Points_1(const std::vector<mud::vec3>* points) {
		return new mud::Points(*points);
	}
	void EMSCRIPTEN_KEEPALIVE Points___destroy__(mud::Points* self) {
		delete self;
	}
	// Poisson
	mud::Poisson* EMSCRIPTEN_KEEPALIVE Poisson_Poisson_2(mud::vec2* size, float maxRadius) {
		return new mud::Poisson(*size, maxRadius);
	}
	bool EMSCRIPTEN_KEEPALIVE Poisson_addPoint_2(mud::Poisson* self, float radius, mud::vec3* point) {
		return self->addPoint(radius, *point);
	}
	void EMSCRIPTEN_KEEPALIVE Poisson___destroy__(mud::Poisson* self) {
		delete self;
	}
	// Polygon
	mud::Polygon* EMSCRIPTEN_KEEPALIVE Polygon_Polygon_0() {
		return new mud::Polygon();
	}
	mud::Polygon* EMSCRIPTEN_KEEPALIVE Polygon_Polygon_1(std::vector<mud::vec3>* vertices) {
		return new mud::Polygon(*vertices);
	}
	void EMSCRIPTEN_KEEPALIVE Polygon___destroy__(mud::Polygon* self) {
		delete self;
	}
	// Quad
	mud::Quad* EMSCRIPTEN_KEEPALIVE Quad_Quad_0() {
		return new mud::Quad();
	}
	mud::Quad* EMSCRIPTEN_KEEPALIVE Quad_Quad_4(const mud::vec3* a, const mud::vec3* b, const mud::vec3* c, const mud::vec3* d) {
		return new mud::Quad(*a, *b, *c, *d);
	}
	void EMSCRIPTEN_KEEPALIVE Quad___destroy__(mud::Quad* self) {
		delete self;
	}
	// Rect
	mud::Rect* EMSCRIPTEN_KEEPALIVE Rect_Rect_0() {
		return new mud::Rect();
	}
	mud::Rect* EMSCRIPTEN_KEEPALIVE Rect_Rect_2(const mud::vec2* position, const mud::vec2* size) {
		return new mud::Rect(*position, *size);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Rect_get_position(mud::Rect* self) {
		static mud::vec2 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Rect_set_position(mud::Rect* self, mud::vec2* position) {
		self->m_position = *position;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Rect_get_size(mud::Rect* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Rect_set_size(mud::Rect* self, mud::vec2* size) {
		self->m_size = *size;
	}
	void EMSCRIPTEN_KEEPALIVE Rect___destroy__(mud::Rect* self) {
		delete self;
	}
	// Ring
	mud::Ring* EMSCRIPTEN_KEEPALIVE Ring_Ring_0() {
		return new mud::Ring();
	}
	mud::Ring* EMSCRIPTEN_KEEPALIVE Ring_Ring_3(float radius, float min, float max) {
		return new mud::Ring(radius, min, max);
	}
	float EMSCRIPTEN_KEEPALIVE Ring_get_radius(mud::Ring* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Ring_set_radius(mud::Ring* self, float radius) {
		self->m_radius = radius;
	}
	float EMSCRIPTEN_KEEPALIVE Ring_get_min(mud::Ring* self) {
		return self->m_min;
	}
	void EMSCRIPTEN_KEEPALIVE Ring_set_min(mud::Ring* self, float min) {
		self->m_min = min;
	}
	float EMSCRIPTEN_KEEPALIVE Ring_get_max(mud::Ring* self) {
		return self->m_max;
	}
	void EMSCRIPTEN_KEEPALIVE Ring_set_max(mud::Ring* self, float max) {
		self->m_max = max;
	}
	void EMSCRIPTEN_KEEPALIVE Ring___destroy__(mud::Ring* self) {
		delete self;
	}
	// Sphere
	mud::Sphere* EMSCRIPTEN_KEEPALIVE Sphere_Sphere_0() {
		return new mud::Sphere();
	}
	mud::Sphere* EMSCRIPTEN_KEEPALIVE Sphere_Sphere_1(float radius) {
		return new mud::Sphere(radius);
	}
	float EMSCRIPTEN_KEEPALIVE Sphere_get_radius(mud::Sphere* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Sphere_set_radius(mud::Sphere* self, float radius) {
		self->m_radius = radius;
	}
	void EMSCRIPTEN_KEEPALIVE Sphere___destroy__(mud::Sphere* self) {
		delete self;
	}
	// SphereRing
	mud::SphereRing* EMSCRIPTEN_KEEPALIVE SphereRing_SphereRing_0() {
		return new mud::SphereRing();
	}
	mud::SphereRing* EMSCRIPTEN_KEEPALIVE SphereRing_SphereRing_3(float radius, float min, float max) {
		return new mud::SphereRing(radius, min, max);
	}
	float EMSCRIPTEN_KEEPALIVE SphereRing_get_radius(mud::SphereRing* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE SphereRing_set_radius(mud::SphereRing* self, float radius) {
		self->m_radius = radius;
	}
	float EMSCRIPTEN_KEEPALIVE SphereRing_get_min(mud::SphereRing* self) {
		return self->m_min;
	}
	void EMSCRIPTEN_KEEPALIVE SphereRing_set_min(mud::SphereRing* self, float min) {
		self->m_min = min;
	}
	float EMSCRIPTEN_KEEPALIVE SphereRing_get_max(mud::SphereRing* self) {
		return self->m_max;
	}
	void EMSCRIPTEN_KEEPALIVE SphereRing_set_max(mud::SphereRing* self, float max) {
		self->m_max = max;
	}
	void EMSCRIPTEN_KEEPALIVE SphereRing___destroy__(mud::SphereRing* self) {
		delete self;
	}
	// Spheroid
	mud::Spheroid* EMSCRIPTEN_KEEPALIVE Spheroid_Spheroid_0() {
		return new mud::Spheroid();
	}
	mud::Spheroid* EMSCRIPTEN_KEEPALIVE Spheroid_Spheroid_1(float radius) {
		return new mud::Spheroid(radius);
	}
	float EMSCRIPTEN_KEEPALIVE Spheroid_get_radius(mud::Spheroid* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Spheroid_set_radius(mud::Spheroid* self, float radius) {
		self->m_radius = radius;
	}
	void EMSCRIPTEN_KEEPALIVE Spheroid___destroy__(mud::Spheroid* self) {
		delete self;
	}
	// Torus
	mud::Torus* EMSCRIPTEN_KEEPALIVE Torus_Torus_0() {
		return new mud::Torus();
	}
	mud::Torus* EMSCRIPTEN_KEEPALIVE Torus_Torus_2(float radius, float solid_radius) {
		return new mud::Torus(radius, solid_radius);
	}
	mud::Torus* EMSCRIPTEN_KEEPALIVE Torus_Torus_3(float radius, float solid_radius, mud::Axis axis) {
		return new mud::Torus(radius, solid_radius, axis);
	}
	float EMSCRIPTEN_KEEPALIVE Torus_get_radius(mud::Torus* self) {
		return self->m_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Torus_set_radius(mud::Torus* self, float radius) {
		self->m_radius = radius;
	}
	float EMSCRIPTEN_KEEPALIVE Torus_get_solid_radius(mud::Torus* self) {
		return self->m_solid_radius;
	}
	void EMSCRIPTEN_KEEPALIVE Torus_set_solid_radius(mud::Torus* self, float solid_radius) {
		self->m_solid_radius = solid_radius;
	}
	mud::Axis EMSCRIPTEN_KEEPALIVE Torus_get_axis(mud::Torus* self) {
		return self->m_axis;
	}
	void EMSCRIPTEN_KEEPALIVE Torus_set_axis(mud::Torus* self, mud::Axis axis) {
		self->m_axis = axis;
	}
	void EMSCRIPTEN_KEEPALIVE Torus___destroy__(mud::Torus* self) {
		delete self;
	}
	// Triangle
	mud::Triangle* EMSCRIPTEN_KEEPALIVE Triangle_Triangle_0() {
		return new mud::Triangle();
	}
	mud::Triangle* EMSCRIPTEN_KEEPALIVE Triangle_Triangle_1(const mud::vec2* size) {
		return new mud::Triangle(*size);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Triangle_get_size(mud::Triangle* self) {
		static mud::vec2 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Triangle_set_size(mud::Triangle* self, mud::vec2* size) {
		self->m_size = *size;
	}
	void EMSCRIPTEN_KEEPALIVE Triangle___destroy__(mud::Triangle* self) {
		delete self;
	}
	// DrawMode
	mud::DrawMode EMSCRIPTEN_KEEPALIVE DrawMode_OUTLINE() {
		return mud::OUTLINE;
	}
	mud::DrawMode EMSCRIPTEN_KEEPALIVE DrawMode_PLAIN() {
		return mud::PLAIN;
	}
	// PrimitiveType
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE PrimitiveType_Points() {
		return mud::PrimitiveType::Points;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE PrimitiveType_Lines() {
		return mud::PrimitiveType::Lines;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE PrimitiveType_LineLoop() {
		return mud::PrimitiveType::LineLoop;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE PrimitiveType_LineStrip() {
		return mud::PrimitiveType::LineStrip;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE PrimitiveType_Triangles() {
		return mud::PrimitiveType::Triangles;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE PrimitiveType_TriangleStrip() {
		return mud::PrimitiveType::TriangleStrip;
	}
	mud::PrimitiveType EMSCRIPTEN_KEEPALIVE PrimitiveType_TriangleFan() {
		return mud::PrimitiveType::TriangleFan;
	}
	// SymbolDetail
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE SymbolDetail_Lowest() {
		return mud::SymbolDetail::Lowest;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE SymbolDetail_Low() {
		return mud::SymbolDetail::Low;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE SymbolDetail_Medium() {
		return mud::SymbolDetail::Medium;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE SymbolDetail_High() {
		return mud::SymbolDetail::High;
	}
	mud::SymbolDetail EMSCRIPTEN_KEEPALIVE SymbolDetail_Highest() {
		return mud::SymbolDetail::Highest;
	}
	
}


