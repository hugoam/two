#include <type/Api.h>
#include <math/Api.h>
#include <geom/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Aabb
	two::Type* DECL two_Aabb__type() {
		return &two::type<two::Aabb>();
	}
	two::Aabb* DECL two_Aabb__construct_0() {
		return new two::Aabb();
	}
	two::Aabb* DECL two_Aabb__construct_2(const two::vec3* center, const two::vec3* extents) {
		return new two::Aabb(*center, *extents);
	}
	two::vec3* DECL two_Aabb__get_center(two::Aabb* self) {
		return &self->m_center;
	}
	void DECL two_Aabb__set_center(two::Aabb* self, two::vec3* value) {
		self->m_center = *value;
	}
	two::vec3* DECL two_Aabb__get_extents(two::Aabb* self) {
		return &self->m_extents;
	}
	void DECL two_Aabb__set_extents(two::Aabb* self, two::vec3* value) {
		self->m_extents = *value;
	}
	bool DECL two_Aabb__get_empty(two::Aabb* self) {
		return self->m_empty;
	}
	void DECL two_Aabb__set_empty(two::Aabb* self, bool value) {
		self->m_empty = value;
	}
	void DECL two_Aabb__destroy(two::Aabb* self) {
		delete self;
	}
	// Curve2
	two::Type* DECL two_Curve2__type() {
		return &two::type<two::Curve2>();
	}
	two::vec2* DECL two_Curve2_point_1(two::Curve2* self, float t) {
		static two::vec2 temp;
		return (temp = self->point(t), &temp);
	}
	void DECL two_Curve2__destroy(two::Curve2* self) {
		delete self;
	}
	// Curve3
	two::Type* DECL two_Curve3__type() {
		return &two::type<two::Curve3>();
	}
	two::vec3* DECL two_Curve3_point_1(two::Curve3* self, float t) {
		static two::vec3 temp;
		return (temp = self->point(t), &temp);
	}
	void DECL two_Curve3__destroy(two::Curve3* self) {
		delete self;
	}
	// CurveSpline
	two::Type* DECL two_CurveSpline__type() {
		return &two::type<two::CurveSpline>();
	}
	two::CurveSpline* DECL two_CurveSpline__construct_0() {
		return new two::CurveSpline();
	}
	float* DECL two_CurveSpline__get_points(two::CurveSpline* self) {
		return (float*)self->m_points.data();
	}
	void DECL two_CurveSpline__destroy(two::CurveSpline* self) {
		delete self;
	}
	// CurveSpline3
	two::Type* DECL two_CurveSpline3__type() {
		return &two::type<two::CurveSpline3>();
	}
	two::CurveSpline3* DECL two_CurveSpline3__construct_0() {
		return new two::CurveSpline3();
	}
	float* DECL two_CurveSpline3__get_points(two::CurveSpline3* self) {
		return (float*)self->m_points.data();
	}
	void DECL two_CurveSpline3__destroy(two::CurveSpline3* self) {
		delete self;
	}
	// CurveBezierCubic
	two::Type* DECL two_CurveBezierCubic__type() {
		return &two::type<two::CurveBezierCubic>();
	}
	two::CurveBezierCubic* DECL two_CurveBezierCubic__construct_0() {
		return new two::CurveBezierCubic();
	}
	two::vec2* DECL two_CurveBezierCubic__get_v0(two::CurveBezierCubic* self) {
		return &self->v0;
	}
	void DECL two_CurveBezierCubic__set_v0(two::CurveBezierCubic* self, two::vec2* value) {
		self->v0 = *value;
	}
	two::vec2* DECL two_CurveBezierCubic__get_v1(two::CurveBezierCubic* self) {
		return &self->v1;
	}
	void DECL two_CurveBezierCubic__set_v1(two::CurveBezierCubic* self, two::vec2* value) {
		self->v1 = *value;
	}
	two::vec2* DECL two_CurveBezierCubic__get_v2(two::CurveBezierCubic* self) {
		return &self->v2;
	}
	void DECL two_CurveBezierCubic__set_v2(two::CurveBezierCubic* self, two::vec2* value) {
		self->v2 = *value;
	}
	two::vec2* DECL two_CurveBezierCubic__get_v3(two::CurveBezierCubic* self) {
		return &self->v3;
	}
	void DECL two_CurveBezierCubic__set_v3(two::CurveBezierCubic* self, two::vec2* value) {
		self->v3 = *value;
	}
	void DECL two_CurveBezierCubic__destroy(two::CurveBezierCubic* self) {
		delete self;
	}
	// CurveBezierCubic3
	two::Type* DECL two_CurveBezierCubic3__type() {
		return &two::type<two::CurveBezierCubic3>();
	}
	two::CurveBezierCubic3* DECL two_CurveBezierCubic3__construct_0() {
		return new two::CurveBezierCubic3();
	}
	two::vec3* DECL two_CurveBezierCubic3__get_v0(two::CurveBezierCubic3* self) {
		return &self->v0;
	}
	void DECL two_CurveBezierCubic3__set_v0(two::CurveBezierCubic3* self, two::vec3* value) {
		self->v0 = *value;
	}
	two::vec3* DECL two_CurveBezierCubic3__get_v1(two::CurveBezierCubic3* self) {
		return &self->v1;
	}
	void DECL two_CurveBezierCubic3__set_v1(two::CurveBezierCubic3* self, two::vec3* value) {
		self->v1 = *value;
	}
	two::vec3* DECL two_CurveBezierCubic3__get_v2(two::CurveBezierCubic3* self) {
		return &self->v2;
	}
	void DECL two_CurveBezierCubic3__set_v2(two::CurveBezierCubic3* self, two::vec3* value) {
		self->v2 = *value;
	}
	two::vec3* DECL two_CurveBezierCubic3__get_v3(two::CurveBezierCubic3* self) {
		return &self->v3;
	}
	void DECL two_CurveBezierCubic3__set_v3(two::CurveBezierCubic3* self, two::vec3* value) {
		self->v3 = *value;
	}
	void DECL two_CurveBezierCubic3__destroy(two::CurveBezierCubic3* self) {
		delete self;
	}
	// CurveLine
	two::Type* DECL two_CurveLine__type() {
		return &two::type<two::CurveLine>();
	}
	two::CurveLine* DECL two_CurveLine__construct_0() {
		return new two::CurveLine();
	}
	two::vec2* DECL two_CurveLine__get_v0(two::CurveLine* self) {
		return &self->v0;
	}
	void DECL two_CurveLine__set_v0(two::CurveLine* self, two::vec2* value) {
		self->v0 = *value;
	}
	two::vec2* DECL two_CurveLine__get_v1(two::CurveLine* self) {
		return &self->v1;
	}
	void DECL two_CurveLine__set_v1(two::CurveLine* self, two::vec2* value) {
		self->v1 = *value;
	}
	void DECL two_CurveLine__destroy(two::CurveLine* self) {
		delete self;
	}
	// CurveLine3
	two::Type* DECL two_CurveLine3__type() {
		return &two::type<two::CurveLine3>();
	}
	two::CurveLine3* DECL two_CurveLine3__construct_0() {
		return new two::CurveLine3();
	}
	two::vec3* DECL two_CurveLine3__get_v0(two::CurveLine3* self) {
		return &self->v0;
	}
	void DECL two_CurveLine3__set_v0(two::CurveLine3* self, two::vec3* value) {
		self->v0 = *value;
	}
	two::vec3* DECL two_CurveLine3__get_v1(two::CurveLine3* self) {
		return &self->v1;
	}
	void DECL two_CurveLine3__set_v1(two::CurveLine3* self, two::vec3* value) {
		self->v1 = *value;
	}
	void DECL two_CurveLine3__destroy(two::CurveLine3* self) {
		delete self;
	}
	// CurveBezierQuadratic
	two::Type* DECL two_CurveBezierQuadratic__type() {
		return &two::type<two::CurveBezierQuadratic>();
	}
	two::CurveBezierQuadratic* DECL two_CurveBezierQuadratic__construct_0() {
		return new two::CurveBezierQuadratic();
	}
	two::vec2* DECL two_CurveBezierQuadratic__get_v0(two::CurveBezierQuadratic* self) {
		return &self->v0;
	}
	void DECL two_CurveBezierQuadratic__set_v0(two::CurveBezierQuadratic* self, two::vec2* value) {
		self->v0 = *value;
	}
	two::vec2* DECL two_CurveBezierQuadratic__get_v1(two::CurveBezierQuadratic* self) {
		return &self->v1;
	}
	void DECL two_CurveBezierQuadratic__set_v1(two::CurveBezierQuadratic* self, two::vec2* value) {
		self->v1 = *value;
	}
	two::vec2* DECL two_CurveBezierQuadratic__get_v2(two::CurveBezierQuadratic* self) {
		return &self->v2;
	}
	void DECL two_CurveBezierQuadratic__set_v2(two::CurveBezierQuadratic* self, two::vec2* value) {
		self->v2 = *value;
	}
	void DECL two_CurveBezierQuadratic__destroy(two::CurveBezierQuadratic* self) {
		delete self;
	}
	// CurveBezierQuadratic3
	two::Type* DECL two_CurveBezierQuadratic3__type() {
		return &two::type<two::CurveBezierQuadratic3>();
	}
	two::CurveBezierQuadratic3* DECL two_CurveBezierQuadratic3__construct_0() {
		return new two::CurveBezierQuadratic3();
	}
	two::vec3* DECL two_CurveBezierQuadratic3__get_v0(two::CurveBezierQuadratic3* self) {
		return &self->v0;
	}
	void DECL two_CurveBezierQuadratic3__set_v0(two::CurveBezierQuadratic3* self, two::vec3* value) {
		self->v0 = *value;
	}
	two::vec3* DECL two_CurveBezierQuadratic3__get_v1(two::CurveBezierQuadratic3* self) {
		return &self->v1;
	}
	void DECL two_CurveBezierQuadratic3__set_v1(two::CurveBezierQuadratic3* self, two::vec3* value) {
		self->v1 = *value;
	}
	two::vec3* DECL two_CurveBezierQuadratic3__get_v2(two::CurveBezierQuadratic3* self) {
		return &self->v2;
	}
	void DECL two_CurveBezierQuadratic3__set_v2(two::CurveBezierQuadratic3* self, two::vec3* value) {
		self->v2 = *value;
	}
	void DECL two_CurveBezierQuadratic3__destroy(two::CurveBezierQuadratic3* self) {
		delete self;
	}
	// CurveCatmullRom3
	two::Type* DECL two_CurveCatmullRom3__type() {
		return &two::type<two::CurveCatmullRom3>();
	}
	two::CurveCatmullRom3* DECL two_CurveCatmullRom3__construct_0() {
		return new two::CurveCatmullRom3();
	}
	void DECL two_CurveCatmullRom3_add_point_1(two::CurveCatmullRom3* self, const two::vec3* point) {
		self->add_point(*point);
	}
	float* DECL two_CurveCatmullRom3__get_points(two::CurveCatmullRom3* self) {
		return (float*)self->m_points.data();
	}
	bool DECL two_CurveCatmullRom3__get_closed(two::CurveCatmullRom3* self) {
		return self->m_closed;
	}
	void DECL two_CurveCatmullRom3__set_closed(two::CurveCatmullRom3* self, bool value) {
		self->m_closed = value;
	}
	two::CatmullType DECL two_CurveCatmullRom3__get_curve_type(two::CurveCatmullRom3* self) {
		return self->m_curve_type;
	}
	void DECL two_CurveCatmullRom3__set_curve_type(two::CurveCatmullRom3* self, two::CatmullType value) {
		self->m_curve_type = value;
	}
	float DECL two_CurveCatmullRom3__get_tension(two::CurveCatmullRom3* self) {
		return self->m_tension;
	}
	void DECL two_CurveCatmullRom3__set_tension(two::CurveCatmullRom3* self, float value) {
		self->m_tension = value;
	}
	void DECL two_CurveCatmullRom3__destroy(two::CurveCatmullRom3* self) {
		delete self;
	}
	// Plane
	two::Type* DECL two_Plane__type() {
		return &two::type<two::Plane>();
	}
	two::Plane* DECL two_Plane__construct_0() {
		return new two::Plane();
	}
	two::vec3* DECL two_Plane__get_normal(two::Plane* self) {
		return &self->m_normal;
	}
	void DECL two_Plane__set_normal(two::Plane* self, two::vec3* value) {
		self->m_normal = *value;
	}
	float DECL two_Plane__get_distance(two::Plane* self) {
		return self->m_distance;
	}
	void DECL two_Plane__set_distance(two::Plane* self, float value) {
		self->m_distance = value;
	}
	void DECL two_Plane__destroy(two::Plane* self) {
		delete self;
	}
	// Plane3
	two::Type* DECL two_Plane3__type() {
		return &two::type<two::Plane3>();
	}
	two::Plane3* DECL two_Plane3__construct_0() {
		return new two::Plane3();
	}
	two::vec3* DECL two_Plane3__get_origin(two::Plane3* self) {
		return &self->m_origin;
	}
	void DECL two_Plane3__set_origin(two::Plane3* self, two::vec3* value) {
		self->m_origin = *value;
	}
	two::vec3* DECL two_Plane3__get_a(two::Plane3* self) {
		return &self->m_a;
	}
	void DECL two_Plane3__set_a(two::Plane3* self, two::vec3* value) {
		self->m_a = *value;
	}
	two::vec3* DECL two_Plane3__get_b(two::Plane3* self) {
		return &self->m_b;
	}
	void DECL two_Plane3__set_b(two::Plane3* self, two::vec3* value) {
		self->m_b = *value;
	}
	void DECL two_Plane3__destroy(two::Plane3* self) {
		delete self;
	}
	// Face3
	two::Type* DECL two_Face3__type() {
		return &two::type<two::Face3>();
	}
	two::Face3* DECL two_Face3__construct_0() {
		return new two::Face3();
	}
	void DECL two_Face3__destroy(two::Face3* self) {
		delete self;
	}
	// Segment
	two::Type* DECL two_Segment__type() {
		return &two::type<two::Segment>();
	}
	two::Segment* DECL two_Segment__construct_0() {
		return new two::Segment();
	}
	two::vec3* DECL two_Segment__get_start(two::Segment* self) {
		return &self->m_start;
	}
	void DECL two_Segment__set_start(two::Segment* self, two::vec3* value) {
		self->m_start = *value;
	}
	two::vec3* DECL two_Segment__get_end(two::Segment* self) {
		return &self->m_end;
	}
	void DECL two_Segment__set_end(two::Segment* self, two::vec3* value) {
		self->m_end = *value;
	}
	void DECL two_Segment__destroy(two::Segment* self) {
		delete self;
	}
	// Ray
	two::Type* DECL two_Ray__type() {
		return &two::type<two::Ray>();
	}
	two::Ray* DECL two_Ray__construct_0() {
		return new two::Ray();
	}
	two::vec3* DECL two_Ray__get_start(two::Ray* self) {
		return &self->m_start;
	}
	void DECL two_Ray__set_start(two::Ray* self, two::vec3* value) {
		self->m_start = *value;
	}
	two::vec3* DECL two_Ray__get_end(two::Ray* self) {
		return &self->m_end;
	}
	void DECL two_Ray__set_end(two::Ray* self, two::vec3* value) {
		self->m_end = *value;
	}
	two::vec3* DECL two_Ray__get_dir(two::Ray* self) {
		return &self->m_dir;
	}
	void DECL two_Ray__set_dir(two::Ray* self, two::vec3* value) {
		self->m_dir = *value;
	}
	two::vec3* DECL two_Ray__get_inv_dir(two::Ray* self) {
		return &self->m_inv_dir;
	}
	void DECL two_Ray__set_inv_dir(two::Ray* self, two::vec3* value) {
		self->m_inv_dir = *value;
	}
	void DECL two_Ray__destroy(two::Ray* self) {
		delete self;
	}
	// MeshAdapter
	two::Type* DECL two_MeshAdapter__type() {
		return &two::type<two::MeshAdapter>();
	}
	two::MeshAdapter* DECL two_MeshAdapter__construct_0() {
		return new two::MeshAdapter();
	}
	void DECL two_MeshAdapter_rewind_0(two::MeshAdapter* self) {
		self->rewind();
	}
	void DECL two_MeshAdapter_copy_1(two::MeshAdapter* self, two::MeshAdapter* dest) {
		self->copy(*dest);
	}
	void DECL two_MeshAdapter_xcopy_2(two::MeshAdapter* self, two::MeshAdapter* dest, const two::mat4* transform) {
		self->xcopy(*dest, *transform);
	}
	void DECL two_MeshAdapter_next_0(two::MeshAdapter* self) {
		self->next();
	}
	two::MeshAdapter* DECL two_MeshAdapter_position_1(two::MeshAdapter* self, const two::vec3* p) {
		return &self->position(*p);
	}
	two::MeshAdapter* DECL two_MeshAdapter_position4_1(two::MeshAdapter* self, const two::vec4* p) {
		return &self->position4(*p);
	}
	two::MeshAdapter* DECL two_MeshAdapter_normal_1(two::MeshAdapter* self, const two::vec3* n) {
		return &self->normal(*n);
	}
	two::MeshAdapter* DECL two_MeshAdapter_colour_1(two::MeshAdapter* self, const two::Colour* c) {
		return &self->colour(*c);
	}
	two::MeshAdapter* DECL two_MeshAdapter_tangent_1(two::MeshAdapter* self, const two::vec4* t) {
		return &self->tangent(*t);
	}
	two::MeshAdapter* DECL two_MeshAdapter_bitangent_1(two::MeshAdapter* self, const two::vec3* b) {
		return &self->bitangent(*b);
	}
	two::MeshAdapter* DECL two_MeshAdapter_uv0_1(two::MeshAdapter* self, const two::vec2* uv) {
		return &self->uv0(*uv);
	}
	two::MeshAdapter* DECL two_MeshAdapter_uv1_1(two::MeshAdapter* self, const two::vec2* uv) {
		return &self->uv1(*uv);
	}
	two::MeshAdapter* DECL two_MeshAdapter_joints_1(two::MeshAdapter* self, const uint32_t j) {
		return &self->joints(j);
	}
	two::MeshAdapter* DECL two_MeshAdapter_weights_1(two::MeshAdapter* self, const two::vec4* w) {
		return &self->weights(*w);
	}
	uint32_t DECL two_MeshAdapter__get_vertex_format(two::MeshAdapter* self) {
		return self->m_vertex_format;
	}
	void DECL two_MeshAdapter__set_vertex_format(two::MeshAdapter* self, uint32_t value) {
		self->m_vertex_format = value;
	}
	bool DECL two_MeshAdapter__get_index32(two::MeshAdapter* self) {
		return self->m_index32;
	}
	void DECL two_MeshAdapter__set_index32(two::MeshAdapter* self, bool value) {
		self->m_index32 = value;
	}
	uint32_t DECL two_MeshAdapter__get_vertex_count(two::MeshAdapter* self) {
		return self->m_vertex_count;
	}
	void DECL two_MeshAdapter__set_vertex_count(two::MeshAdapter* self, uint32_t value) {
		self->m_vertex_count = value;
	}
	uint32_t DECL two_MeshAdapter__get_index_count(two::MeshAdapter* self) {
		return self->m_index_count;
	}
	void DECL two_MeshAdapter__set_index_count(two::MeshAdapter* self, uint32_t value) {
		self->m_index_count = value;
	}
	uint32_t DECL two_MeshAdapter__get_vertex_stride(two::MeshAdapter* self) {
		return self->m_vertex_stride;
	}
	void DECL two_MeshAdapter__set_vertex_stride(two::MeshAdapter* self, uint32_t value) {
		self->m_vertex_stride = value;
	}
	void DECL two_MeshAdapter__destroy(two::MeshAdapter* self) {
		delete self;
	}
	// Shape
	two::Type* DECL two_Shape__type() {
		return &two::type<two::Shape>();
	}
	two::Type* DECL two_Shape__get_type(two::Shape* self) {
		return &self->m_type;
	}
	void DECL two_Shape__destroy(two::Shape* self) {
		delete self;
	}
	// ShapeVar
	two::Type* DECL two_ShapeVar__type() {
		return &two::type<two::ShapeVar>();
	}
	two::ShapeVar* DECL two_ShapeVar__construct_0() {
		return new two::ShapeVar();
	}
	two::ShapeVar* DECL two_ShapeVar__construct_1(const two::Shape* shape) {
		return new two::ShapeVar(*shape);
	}
	two::Shape* DECL two_ShapeVar__get_shape(two::ShapeVar* self) {
		return &self->shape();
	}
	void DECL two_ShapeVar__destroy(two::ShapeVar* self) {
		delete self;
	}
	// Geometry
	two::Type* DECL two_Geometry__type() {
		return &two::type<two::Geometry>();
	}
	two::Geometry* DECL two_Geometry__construct_0() {
		return new two::Geometry();
	}
	void DECL two_Geometry__destroy(two::Geometry* self) {
		delete self;
	}
	// MeshPacker
	two::Type* DECL two_MeshPacker__type() {
		return &two::type<two::MeshPacker>();
	}
	two::MeshPacker* DECL two_MeshPacker__construct_0() {
		return new two::MeshPacker();
	}
	void DECL two_MeshPacker_position_1(two::MeshPacker* self, const two::vec3* p) {
		self->position(*p);
	}
	void DECL two_MeshPacker_normal_1(two::MeshPacker* self, const two::vec3* n) {
		self->normal(*n);
	}
	void DECL two_MeshPacker_colour_1(two::MeshPacker* self, const two::Colour* c) {
		self->colour(*c);
	}
	void DECL two_MeshPacker_tangent_1(two::MeshPacker* self, const two::vec4* t) {
		self->tangent(*t);
	}
	void DECL two_MeshPacker_bitangent_1(two::MeshPacker* self, const two::vec3* b) {
		self->bitangent(*b);
	}
	void DECL two_MeshPacker_uv0_1(two::MeshPacker* self, const two::vec2* uv) {
		self->uv0(*uv);
	}
	void DECL two_MeshPacker_uv1_1(two::MeshPacker* self, const two::vec2* uv) {
		self->uv1(*uv);
	}
	void DECL two_MeshPacker_bones_1(two::MeshPacker* self, const two::ivec4* j) {
		self->bones(*j);
	}
	void DECL two_MeshPacker_weights_1(two::MeshPacker* self, const two::vec4* w) {
		self->weights(*w);
	}
	void DECL two_MeshPacker_index_1(two::MeshPacker* self, uint32_t i) {
		self->index(i);
	}
	void DECL two_MeshPacker_resize_3(two::MeshPacker* self, uint32_t vertex_count, uint32_t index_count, uint32_t vertex_format) {
		self->resize(vertex_count, index_count, vertex_format);
	}
	void DECL two_MeshPacker_clear_0(two::MeshPacker* self) {
		self->clear();
	}
	void DECL two_MeshPacker_pack_1(two::MeshPacker* self, two::MeshAdapter* writer) {
		self->pack(*writer);
	}
	void DECL two_MeshPacker_xpack_2(two::MeshPacker* self, two::MeshAdapter* writer, const two::mat4* transform) {
		self->xpack(*writer, *transform);
	}
	void DECL two_MeshPacker_unpack_2(two::MeshPacker* self, const two::MeshAdapter* reader, const two::mat4* transform) {
		self->unpack(*reader, *transform);
	}
	void DECL two_MeshPacker_gen_normals_0(two::MeshPacker* self) {
		self->gen_normals();
	}
	void DECL two_MeshPacker_gen_normals_1(two::MeshPacker* self, bool area_weighted) {
		self->gen_normals(area_weighted);
	}
	void DECL two_MeshPacker_gen_flat_normals_0(two::MeshPacker* self) {
		self->gen_flat_normals();
	}
	void DECL two_MeshPacker_gen_tangents_0(two::MeshPacker* self) {
		self->gen_tangents();
	}
	void DECL two_MeshPacker_smooth_normals_0(two::MeshPacker* self) {
		self->smooth_normals();
	}
	two::PrimitiveType DECL two_MeshPacker__get_primitive(two::MeshPacker* self) {
		return self->m_primitive;
	}
	void DECL two_MeshPacker__set_primitive(two::MeshPacker* self, two::PrimitiveType value) {
		self->m_primitive = value;
	}
	float* DECL two_MeshPacker__get_positions(two::MeshPacker* self) {
		return (float*)self->m_positions.data();
	}
	float* DECL two_MeshPacker__get_normals(two::MeshPacker* self) {
		return (float*)self->m_normals.data();
	}
	float* DECL two_MeshPacker__get_colours(two::MeshPacker* self) {
		return (float*)self->m_colours.data();
	}
	uint* DECL two_MeshPacker__get_ucolours(two::MeshPacker* self) {
		return (uint*)self->m_ucolours.data();
	}
	float* DECL two_MeshPacker__get_tangents(two::MeshPacker* self) {
		return (float*)self->m_tangents.data();
	}
	float* DECL two_MeshPacker__get_bitangents(two::MeshPacker* self) {
		return (float*)self->m_bitangents.data();
	}
	float* DECL two_MeshPacker__get_uv0s(two::MeshPacker* self) {
		return (float*)self->m_uv0s.data();
	}
	float* DECL two_MeshPacker__get_uv1s(two::MeshPacker* self) {
		return (float*)self->m_uv1s.data();
	}
	int* DECL two_MeshPacker__get_bones(two::MeshPacker* self) {
		return (int*)self->m_bones.data();
	}
	float* DECL two_MeshPacker__get_weights(two::MeshPacker* self) {
		return (float*)self->m_weights.data();
	}
	uint* DECL two_MeshPacker__get_indices(two::MeshPacker* self) {
		return (uint*)self->m_indices.data();
	}
	bool DECL two_MeshPacker__get_quantize(two::MeshPacker* self) {
		return self->m_quantize;
	}
	void DECL two_MeshPacker__set_quantize(two::MeshPacker* self, bool value) {
		self->m_quantize = value;
	}
	void DECL two_MeshPacker__destroy(two::MeshPacker* self) {
		delete self;
	}
	// Line
	two::Type* DECL two_Line__type() {
		return &two::type<two::Line>();
	}
	two::Line* DECL two_Line__construct_0() {
		return new two::Line();
	}
	two::Line* DECL two_Line__construct_2(const two::vec3* start, const two::vec3* end) {
		return new two::Line(*start, *end);
	}
	two::vec3* DECL two_Line__get_start(two::Line* self) {
		return &self->m_start;
	}
	void DECL two_Line__set_start(two::Line* self, two::vec3* value) {
		self->m_start = *value;
	}
	two::vec3* DECL two_Line__get_end(two::Line* self) {
		return &self->m_end;
	}
	void DECL two_Line__set_end(two::Line* self, two::vec3* value) {
		self->m_end = *value;
	}
	void DECL two_Line__destroy(two::Line* self) {
		delete self;
	}
	// Rect
	two::Type* DECL two_Rect__type() {
		return &two::type<two::Rect>();
	}
	two::Rect* DECL two_Rect__construct_0() {
		return new two::Rect();
	}
	two::Rect* DECL two_Rect__construct_2(const two::vec2* position, const two::vec2* size) {
		return new two::Rect(*position, *size);
	}
	two::Rect* DECL two_Rect__construct_4(float x, float y, float w, float h) {
		return new two::Rect(x, y, w, h);
	}
	two::vec2* DECL two_Rect__get_position(two::Rect* self) {
		return &self->m_position;
	}
	void DECL two_Rect__set_position(two::Rect* self, two::vec2* value) {
		self->m_position = *value;
	}
	two::vec2* DECL two_Rect__get_size(two::Rect* self) {
		return &self->m_size;
	}
	void DECL two_Rect__set_size(two::Rect* self, two::vec2* value) {
		self->m_size = *value;
	}
	void DECL two_Rect__destroy(two::Rect* self) {
		delete self;
	}
	// Quad
	two::Type* DECL two_Quad__type() {
		return &two::type<two::Quad>();
	}
	two::Quad* DECL two_Quad__construct_0() {
		return new two::Quad();
	}
	two::Quad* DECL two_Quad__construct_4(const two::vec3* a, const two::vec3* b, const two::vec3* c, const two::vec3* d) {
		return new two::Quad(*a, *b, *c, *d);
	}
	void DECL two_Quad__destroy(two::Quad* self) {
		delete self;
	}
	// Grid2
	two::Type* DECL two_Grid2__type() {
		return &two::type<two::Grid2>();
	}
	two::Grid2* DECL two_Grid2__construct_0() {
		return new two::Grid2();
	}
	two::Grid2* DECL two_Grid2__construct_1(const two::vec2* size) {
		return new two::Grid2(*size);
	}
	two::Grid2* DECL two_Grid2__construct_2(const two::vec2* size, const two::vec2* space) {
		return new two::Grid2(*size, *space);
	}
	two::vec2* DECL two_Grid2__get_size(two::Grid2* self) {
		return &self->m_size;
	}
	void DECL two_Grid2__set_size(two::Grid2* self, two::vec2* value) {
		self->m_size = *value;
	}
	two::vec2* DECL two_Grid2__get_space(two::Grid2* self) {
		return &self->m_space;
	}
	void DECL two_Grid2__set_space(two::Grid2* self, two::vec2* value) {
		self->m_space = *value;
	}
	void DECL two_Grid2__destroy(two::Grid2* self) {
		delete self;
	}
	// Triangle
	two::Type* DECL two_Triangle__type() {
		return &two::type<two::Triangle>();
	}
	two::Triangle* DECL two_Triangle__construct_0() {
		return new two::Triangle();
	}
	two::Triangle* DECL two_Triangle__construct_1(const two::vec2* size) {
		return new two::Triangle(*size);
	}
	two::vec2* DECL two_Triangle__get_size(two::Triangle* self) {
		return &self->m_size;
	}
	void DECL two_Triangle__set_size(two::Triangle* self, two::vec2* value) {
		self->m_size = *value;
	}
	void DECL two_Triangle__destroy(two::Triangle* self) {
		delete self;
	}
	// Circle
	two::Type* DECL two_Circle__type() {
		return &two::type<two::Circle>();
	}
	two::Circle* DECL two_Circle__construct_0() {
		return new two::Circle();
	}
	two::Circle* DECL two_Circle__construct_1(float radius) {
		return new two::Circle(radius);
	}
	two::Circle* DECL two_Circle__construct_2(float radius, two::Axis axis) {
		return new two::Circle(radius, axis);
	}
	two::Circle* DECL two_Circle__construct_3(const two::vec3* center, float radius, two::Axis axis) {
		return new two::Circle(*center, radius, axis);
	}
	float DECL two_Circle__get_radius(two::Circle* self) {
		return self->m_radius;
	}
	void DECL two_Circle__set_radius(two::Circle* self, float value) {
		self->m_radius = value;
	}
	two::Axis DECL two_Circle__get_axis(two::Circle* self) {
		return self->m_axis;
	}
	void DECL two_Circle__set_axis(two::Circle* self, two::Axis value) {
		self->m_axis = value;
	}
	void DECL two_Circle__destroy(two::Circle* self) {
		delete self;
	}
	// Torus
	two::Type* DECL two_Torus__type() {
		return &two::type<two::Torus>();
	}
	two::Torus* DECL two_Torus__construct_0() {
		return new two::Torus();
	}
	two::Torus* DECL two_Torus__construct_2(float radius, float tube) {
		return new two::Torus(radius, tube);
	}
	two::Torus* DECL two_Torus__construct_3(float radius, float tube, two::Axis axis) {
		return new two::Torus(radius, tube, axis);
	}
	two::Torus* DECL two_Torus__construct_4(const two::vec3* center, float radius, float tube, two::Axis axis) {
		return new two::Torus(*center, radius, tube, axis);
	}
	float DECL two_Torus__get_radius(two::Torus* self) {
		return self->m_radius;
	}
	void DECL two_Torus__set_radius(two::Torus* self, float value) {
		self->m_radius = value;
	}
	float DECL two_Torus__get_tube(two::Torus* self) {
		return self->m_tube;
	}
	void DECL two_Torus__set_tube(two::Torus* self, float value) {
		self->m_tube = value;
	}
	two::Axis DECL two_Torus__get_axis(two::Torus* self) {
		return self->m_axis;
	}
	void DECL two_Torus__set_axis(two::Torus* self, two::Axis value) {
		self->m_axis = value;
	}
	void DECL two_Torus__destroy(two::Torus* self) {
		delete self;
	}
	// TorusKnot
	two::Type* DECL two_TorusKnot__type() {
		return &two::type<two::TorusKnot>();
	}
	two::TorusKnot* DECL two_TorusKnot__construct_0() {
		return new two::TorusKnot();
	}
	two::TorusKnot* DECL two_TorusKnot__construct_2(float radius, float tube) {
		return new two::TorusKnot(radius, tube);
	}
	two::TorusKnot* DECL two_TorusKnot__construct_3(float radius, float tube, float p) {
		return new two::TorusKnot(radius, tube, p);
	}
	two::TorusKnot* DECL two_TorusKnot__construct_4(float radius, float tube, float p, float q) {
		return new two::TorusKnot(radius, tube, p, q);
	}
	two::TorusKnot* DECL two_TorusKnot__construct_5(const two::vec3* center, float radius, float tube, float p, float q) {
		return new two::TorusKnot(*center, radius, tube, p, q);
	}
	float DECL two_TorusKnot__get_radius(two::TorusKnot* self) {
		return self->m_radius;
	}
	void DECL two_TorusKnot__set_radius(two::TorusKnot* self, float value) {
		self->m_radius = value;
	}
	float DECL two_TorusKnot__get_tube(two::TorusKnot* self) {
		return self->m_tube;
	}
	void DECL two_TorusKnot__set_tube(two::TorusKnot* self, float value) {
		self->m_tube = value;
	}
	float DECL two_TorusKnot__get_p(two::TorusKnot* self) {
		return self->m_p;
	}
	void DECL two_TorusKnot__set_p(two::TorusKnot* self, float value) {
		self->m_p = value;
	}
	float DECL two_TorusKnot__get_q(two::TorusKnot* self) {
		return self->m_q;
	}
	void DECL two_TorusKnot__set_q(two::TorusKnot* self, float value) {
		self->m_q = value;
	}
	void DECL two_TorusKnot__destroy(two::TorusKnot* self) {
		delete self;
	}
	// Ring
	two::Type* DECL two_Ring__type() {
		return &two::type<two::Ring>();
	}
	two::Ring* DECL two_Ring__construct_0() {
		return new two::Ring();
	}
	two::Ring* DECL two_Ring__construct_3(float radius, float min, float max) {
		return new two::Ring(radius, min, max);
	}
	float DECL two_Ring__get_radius(two::Ring* self) {
		return self->m_radius;
	}
	void DECL two_Ring__set_radius(two::Ring* self, float value) {
		self->m_radius = value;
	}
	float DECL two_Ring__get_min(two::Ring* self) {
		return self->m_min;
	}
	void DECL two_Ring__set_min(two::Ring* self, float value) {
		self->m_min = value;
	}
	float DECL two_Ring__get_max(two::Ring* self) {
		return self->m_max;
	}
	void DECL two_Ring__set_max(two::Ring* self, float value) {
		self->m_max = value;
	}
	void DECL two_Ring__destroy(two::Ring* self) {
		delete self;
	}
	// Ellipsis
	two::Type* DECL two_Ellipsis__type() {
		return &two::type<two::Ellipsis>();
	}
	two::Ellipsis* DECL two_Ellipsis__construct_0() {
		return new two::Ellipsis();
	}
	two::Ellipsis* DECL two_Ellipsis__construct_1(two::vec2* radius) {
		return new two::Ellipsis(*radius);
	}
	two::Ellipsis* DECL two_Ellipsis__construct_2(two::vec2* radius, two::Axis axis) {
		return new two::Ellipsis(*radius, axis);
	}
	two::vec2* DECL two_Ellipsis__get_radius(two::Ellipsis* self) {
		return &self->m_radius;
	}
	void DECL two_Ellipsis__set_radius(two::Ellipsis* self, two::vec2* value) {
		self->m_radius = *value;
	}
	two::Axis DECL two_Ellipsis__get_axis(two::Ellipsis* self) {
		return self->m_axis;
	}
	void DECL two_Ellipsis__set_axis(two::Ellipsis* self, two::Axis value) {
		self->m_axis = value;
	}
	void DECL two_Ellipsis__destroy(two::Ellipsis* self) {
		delete self;
	}
	// Arc
	two::Type* DECL two_Arc__type() {
		return &two::type<two::Arc>();
	}
	two::Arc* DECL two_Arc__construct_0() {
		return new two::Arc();
	}
	two::Arc* DECL two_Arc__construct_3(float radius, float start, float end) {
		return new two::Arc(radius, start, end);
	}
	float DECL two_Arc__get_radius(two::Arc* self) {
		return self->m_radius;
	}
	void DECL two_Arc__set_radius(two::Arc* self, float value) {
		self->m_radius = value;
	}
	float DECL two_Arc__get_start(two::Arc* self) {
		return self->m_start;
	}
	void DECL two_Arc__set_start(two::Arc* self, float value) {
		self->m_start = value;
	}
	float DECL two_Arc__get_end(two::Arc* self) {
		return self->m_end;
	}
	void DECL two_Arc__set_end(two::Arc* self, float value) {
		self->m_end = value;
	}
	void DECL two_Arc__destroy(two::Arc* self) {
		delete self;
	}
	// ArcLine
	two::Type* DECL two_ArcLine__type() {
		return &two::type<two::ArcLine>();
	}
	two::ArcLine* DECL two_ArcLine__construct_0() {
		return new two::ArcLine();
	}
	two::ArcLine* DECL two_ArcLine__construct_3(const two::vec3* start, const two::vec3* middle, const two::vec3* end) {
		return new two::ArcLine(*start, *middle, *end);
	}
	two::ArcLine* DECL two_ArcLine__construct_4(const two::vec3* center, const two::vec3* start, const two::vec3* middle, const two::vec3* end) {
		return new two::ArcLine(*center, *start, *middle, *end);
	}
	two::vec3* DECL two_ArcLine__get_start(two::ArcLine* self) {
		return &self->m_start;
	}
	void DECL two_ArcLine__set_start(two::ArcLine* self, two::vec3* value) {
		self->m_start = *value;
	}
	two::vec3* DECL two_ArcLine__get_middle(two::ArcLine* self) {
		return &self->m_middle;
	}
	void DECL two_ArcLine__set_middle(two::ArcLine* self, two::vec3* value) {
		self->m_middle = *value;
	}
	two::vec3* DECL two_ArcLine__get_end(two::ArcLine* self) {
		return &self->m_end;
	}
	void DECL two_ArcLine__set_end(two::ArcLine* self, two::vec3* value) {
		self->m_end = *value;
	}
	void DECL two_ArcLine__destroy(two::ArcLine* self) {
		delete self;
	}
	// Cylinder
	two::Type* DECL two_Cylinder__type() {
		return &two::type<two::Cylinder>();
	}
	two::Cylinder* DECL two_Cylinder__construct_0() {
		return new two::Cylinder();
	}
	two::Cylinder* DECL two_Cylinder__construct_2(float radius, float height) {
		return new two::Cylinder(radius, height);
	}
	two::Cylinder* DECL two_Cylinder__construct_3(float radius, float height, two::Axis axis) {
		return new two::Cylinder(radius, height, axis);
	}
	two::Cylinder* DECL two_Cylinder__construct_4(const two::vec3* center, float radius, float height, two::Axis axis) {
		return new two::Cylinder(*center, radius, height, axis);
	}
	float DECL two_Cylinder__get_radius(two::Cylinder* self) {
		return self->m_radius;
	}
	void DECL two_Cylinder__set_radius(two::Cylinder* self, float value) {
		self->m_radius = value;
	}
	float DECL two_Cylinder__get_height(two::Cylinder* self) {
		return self->m_height;
	}
	void DECL two_Cylinder__set_height(two::Cylinder* self, float value) {
		self->m_height = value;
	}
	two::Axis DECL two_Cylinder__get_axis(two::Cylinder* self) {
		return self->m_axis;
	}
	void DECL two_Cylinder__set_axis(two::Cylinder* self, two::Axis value) {
		self->m_axis = value;
	}
	void DECL two_Cylinder__destroy(two::Cylinder* self) {
		delete self;
	}
	// Capsule
	two::Type* DECL two_Capsule__type() {
		return &two::type<two::Capsule>();
	}
	two::Capsule* DECL two_Capsule__construct_0() {
		return new two::Capsule();
	}
	two::Capsule* DECL two_Capsule__construct_2(float radius, float height) {
		return new two::Capsule(radius, height);
	}
	two::Capsule* DECL two_Capsule__construct_3(float radius, float height, two::Axis axis) {
		return new two::Capsule(radius, height, axis);
	}
	float DECL two_Capsule__get_radius(two::Capsule* self) {
		return self->m_radius;
	}
	void DECL two_Capsule__set_radius(two::Capsule* self, float value) {
		self->m_radius = value;
	}
	float DECL two_Capsule__get_height(two::Capsule* self) {
		return self->m_height;
	}
	void DECL two_Capsule__set_height(two::Capsule* self, float value) {
		self->m_height = value;
	}
	two::Axis DECL two_Capsule__get_axis(two::Capsule* self) {
		return self->m_axis;
	}
	void DECL two_Capsule__set_axis(two::Capsule* self, two::Axis value) {
		self->m_axis = value;
	}
	void DECL two_Capsule__destroy(two::Capsule* self) {
		delete self;
	}
	// Cube
	two::Type* DECL two_Cube__type() {
		return &two::type<two::Cube>();
	}
	two::Cube* DECL two_Cube__construct_0() {
		return new two::Cube();
	}
	two::Cube* DECL two_Cube__construct_1(const two::vec3* extents) {
		return new two::Cube(*extents);
	}
	two::Cube* DECL two_Cube__construct_2(const two::vec3* center, const two::vec3* extents) {
		return new two::Cube(*center, *extents);
	}
	two::vec3* DECL two_Cube__get_extents(two::Cube* self) {
		return &self->m_extents;
	}
	void DECL two_Cube__set_extents(two::Cube* self, two::vec3* value) {
		self->m_extents = *value;
	}
	void DECL two_Cube__destroy(two::Cube* self) {
		delete self;
	}
	// Tetraedr
	two::Type* DECL two_Tetraedr__type() {
		return &two::type<two::Tetraedr>();
	}
	two::Tetraedr* DECL two_Tetraedr__construct_0() {
		return new two::Tetraedr();
	}
	two::Tetraedr* DECL two_Tetraedr__construct_1(float radius) {
		return new two::Tetraedr(radius);
	}
	two::Tetraedr* DECL two_Tetraedr__construct_2(const two::vec3* center, float radius) {
		return new two::Tetraedr(*center, radius);
	}
	float DECL two_Tetraedr__get_radius(two::Tetraedr* self) {
		return self->m_radius;
	}
	void DECL two_Tetraedr__set_radius(two::Tetraedr* self, float value) {
		self->m_radius = value;
	}
	void DECL two_Tetraedr__destroy(two::Tetraedr* self) {
		delete self;
	}
	// Sphere
	two::Type* DECL two_Sphere__type() {
		return &two::type<two::Sphere>();
	}
	two::Sphere* DECL two_Sphere__construct_0() {
		return new two::Sphere();
	}
	two::Sphere* DECL two_Sphere__construct_1(float radius) {
		return new two::Sphere(radius);
	}
	two::Sphere* DECL two_Sphere__construct_2(float radius, float start) {
		return new two::Sphere(radius, start);
	}
	two::Sphere* DECL two_Sphere__construct_3(float radius, float start, float end) {
		return new two::Sphere(radius, start, end);
	}
	two::Sphere* DECL two_Sphere__construct_4(const two::vec3* center, float radius, float start, float end) {
		return new two::Sphere(*center, radius, start, end);
	}
	float DECL two_Sphere__get_radius(two::Sphere* self) {
		return self->m_radius;
	}
	void DECL two_Sphere__set_radius(two::Sphere* self, float value) {
		self->m_radius = value;
	}
	float DECL two_Sphere__get_start(two::Sphere* self) {
		return self->m_start;
	}
	void DECL two_Sphere__set_start(two::Sphere* self, float value) {
		self->m_start = value;
	}
	float DECL two_Sphere__get_end(two::Sphere* self) {
		return self->m_end;
	}
	void DECL two_Sphere__set_end(two::Sphere* self, float value) {
		self->m_end = value;
	}
	void DECL two_Sphere__destroy(two::Sphere* self) {
		delete self;
	}
	// SphereRing
	two::Type* DECL two_SphereRing__type() {
		return &two::type<two::SphereRing>();
	}
	two::SphereRing* DECL two_SphereRing__construct_0() {
		return new two::SphereRing();
	}
	two::SphereRing* DECL two_SphereRing__construct_3(float radius, float min, float max) {
		return new two::SphereRing(radius, min, max);
	}
	float DECL two_SphereRing__get_radius(two::SphereRing* self) {
		return self->m_radius;
	}
	void DECL two_SphereRing__set_radius(two::SphereRing* self, float value) {
		self->m_radius = value;
	}
	float DECL two_SphereRing__get_min(two::SphereRing* self) {
		return self->m_min;
	}
	void DECL two_SphereRing__set_min(two::SphereRing* self, float value) {
		self->m_min = value;
	}
	float DECL two_SphereRing__get_max(two::SphereRing* self) {
		return self->m_max;
	}
	void DECL two_SphereRing__set_max(two::SphereRing* self, float value) {
		self->m_max = value;
	}
	void DECL two_SphereRing__destroy(two::SphereRing* self) {
		delete self;
	}
	// Spheroid
	two::Type* DECL two_Spheroid__type() {
		return &two::type<two::Spheroid>();
	}
	two::Spheroid* DECL two_Spheroid__construct_0() {
		return new two::Spheroid();
	}
	two::Spheroid* DECL two_Spheroid__construct_1(float radius) {
		return new two::Spheroid(radius);
	}
	two::Spheroid* DECL two_Spheroid__construct_2(const two::vec3* center, float radius) {
		return new two::Spheroid(*center, radius);
	}
	float DECL two_Spheroid__get_radius(two::Spheroid* self) {
		return self->m_radius;
	}
	void DECL two_Spheroid__set_radius(two::Spheroid* self, float value) {
		self->m_radius = value;
	}
	void DECL two_Spheroid__destroy(two::Spheroid* self) {
		delete self;
	}
	// Icosaedr
	two::Type* DECL two_Icosaedr__type() {
		return &two::type<two::Icosaedr>();
	}
	two::Icosaedr* DECL two_Icosaedr__construct_0() {
		return new two::Icosaedr();
	}
	two::Icosaedr* DECL two_Icosaedr__construct_1(float radius) {
		return new two::Icosaedr(radius);
	}
	two::Icosaedr* DECL two_Icosaedr__construct_2(const two::vec3* center, float radius) {
		return new two::Icosaedr(*center, radius);
	}
	float DECL two_Icosaedr__get_radius(two::Icosaedr* self) {
		return self->m_radius;
	}
	void DECL two_Icosaedr__set_radius(two::Icosaedr* self, float value) {
		self->m_radius = value;
	}
	void DECL two_Icosaedr__destroy(two::Icosaedr* self) {
		delete self;
	}
	// Distribution
	two::Type* DECL two_Distribution__type() {
		return &two::type<two::Distribution>();
	}
	void DECL two_Distribution__destroy(two::Distribution* self) {
		delete self;
	}
	// Poisson
	two::Type* DECL two_Poisson__type() {
		return &two::type<two::Poisson>();
	}
	two::Poisson* DECL two_Poisson__construct_2(two::vec2* size, float maxRadius) {
		return new two::Poisson(*size, maxRadius);
	}
	float* DECL two_Poisson_distribute_1(two::Poisson* self, float radius) {
		return (float*)self->distribute(radius).data();
	}
	bool DECL two_Poisson_addPoint_2(two::Poisson* self, float radius, two::vec3* point) {
		return self->addPoint(radius, *point);
	}
	void DECL two_Poisson__destroy(two::Poisson* self) {
		delete self;
	}
	// Polygon
	two::Type* DECL two_Polygon__type() {
		return &two::type<two::Polygon>();
	}
	two::Polygon* DECL two_Polygon__construct_0() {
		return new two::Polygon();
	}
	two::Polygon* DECL two_Polygon__construct_1(float* vertices, int vertices_size) {
		return new two::Polygon({ (two::vec3*)vertices, vertices_size / (sizeof(two::vec3) / sizeof(float)) });
	}
	void DECL two_Polygon__destroy(two::Polygon* self) {
		delete self;
	}
	// Box
	two::Type* DECL two_Box__type() {
		return &two::type<two::Box>();
	}
	two::Box* DECL two_Box__construct_0() {
		return new two::Box();
	}
	void DECL two_Box__destroy(two::Box* self) {
		delete self;
	}
	// Points
	two::Type* DECL two_Points__type() {
		return &two::type<two::Points>();
	}
	two::Points* DECL two_Points__construct_0() {
		return new two::Points();
	}
	two::Points* DECL two_Points__construct_1(float* points, int points_size) {
		return new two::Points({ (two::vec3*)points, points_size / (sizeof(two::vec3) / sizeof(float)) });
	}
	float* DECL two_Points__get_points(two::Points* self) {
		return (float*)self->m_points.data();
	}
	void DECL two_Points__destroy(two::Points* self) {
		delete self;
	}
	// Grid3
	two::Type* DECL two_Grid3__type() {
		return &two::type<two::Grid3>();
	}
	two::Grid3* DECL two_Grid3__construct_0() {
		return new two::Grid3();
	}
	two::Grid3* DECL two_Grid3__construct_1(const two::uvec2* size) {
		return new two::Grid3(*size);
	}
	two::Grid3* DECL two_Grid3__construct_2(const two::uvec2* size, float* points, int points_size) {
		return new two::Grid3(*size, { (two::vec3*)points, points_size / (sizeof(two::vec3) / sizeof(float)) });
	}
	two::uvec2* DECL two_Grid3__get_size(two::Grid3* self) {
		return &self->m_size;
	}
	void DECL two_Grid3__set_size(two::Grid3* self, two::uvec2* value) {
		self->m_size = *value;
	}
	float* DECL two_Grid3__get_points(two::Grid3* self) {
		return (float*)self->m_points.data();
	}
	void DECL two_Grid3__destroy(two::Grid3* self) {
		delete self;
	}
	// ConvexHull
	two::Type* DECL two_ConvexHull__type() {
		return &two::type<two::ConvexHull>();
	}
	two::ConvexHull* DECL two_ConvexHull__construct_0() {
		return new two::ConvexHull();
	}
	two::ConvexHull* DECL two_ConvexHull__construct_1(float* vertices, int vertices_size) {
		return new two::ConvexHull({ (two::vec3*)vertices, vertices_size / (sizeof(two::vec3) / sizeof(float)) });
	}
	float* DECL two_ConvexHull__get_vertices(two::ConvexHull* self) {
		return (float*)self->m_vertices.data();
	}
	void DECL two_ConvexHull__destroy(two::ConvexHull* self) {
		delete self;
	}
	// Symbol
	two::Type* DECL two_Symbol__type() {
		return &two::type<two::Symbol>();
	}
	two::Symbol* DECL two_Symbol__construct_1(two::Colour* fill) {
		return new two::Symbol(*fill);
	}
	two::Symbol* DECL two_Symbol__construct_2(two::Colour* fill, two::Colour* outline) {
		return new two::Symbol(*fill, *outline);
	}
	two::Symbol* DECL two_Symbol__construct_3(two::Colour* fill, two::Colour* outline, bool overlay) {
		return new two::Symbol(*fill, *outline, overlay);
	}
	two::Symbol* DECL two_Symbol__construct_4(two::Colour* fill, two::Colour* outline, bool overlay, bool double_sided) {
		return new two::Symbol(*fill, *outline, overlay, double_sided);
	}
	two::Symbol* DECL two_Symbol__construct_5(two::Colour* fill, two::Colour* outline, bool overlay, bool double_sided, two::SymbolDetail detail) {
		return new two::Symbol(*fill, *outline, overlay, double_sided, detail);
	}
	two::Colour* DECL two_Symbol__get_outline(two::Symbol* self) {
		return &self->m_outline;
	}
	void DECL two_Symbol__set_outline(two::Symbol* self, two::Colour* value) {
		self->m_outline = *value;
	}
	two::Colour* DECL two_Symbol__get_fill(two::Symbol* self) {
		return &self->m_fill;
	}
	void DECL two_Symbol__set_fill(two::Symbol* self, two::Colour* value) {
		self->m_fill = *value;
	}
	bool DECL two_Symbol__get_overlay(two::Symbol* self) {
		return self->m_overlay;
	}
	void DECL two_Symbol__set_overlay(two::Symbol* self, bool value) {
		self->m_overlay = value;
	}
	bool DECL two_Symbol__get_double_sided(two::Symbol* self) {
		return self->m_double_sided;
	}
	void DECL two_Symbol__set_double_sided(two::Symbol* self, bool value) {
		self->m_double_sided = value;
	}
	two::SymbolDetail DECL two_Symbol__get_detail(two::Symbol* self) {
		return self->m_detail;
	}
	void DECL two_Symbol__set_detail(two::Symbol* self, two::SymbolDetail value) {
		self->m_detail = value;
	}
	two::uvec2* DECL two_Symbol__get_subdiv(two::Symbol* self) {
		return &self->m_subdiv;
	}
	void DECL two_Symbol__set_subdiv(two::Symbol* self, two::uvec2* value) {
		self->m_subdiv = *value;
	}
	const char* DECL two_Symbol__get_image(two::Symbol* self) {
		return self->m_image;
	}
	void DECL two_Symbol__set_image(two::Symbol* self, const char* value) {
		self->m_image = value;
	}
	two::Image256* DECL two_Symbol__get_image256(two::Symbol* self) {
		return self->m_image256;
	}
	void DECL two_Symbol__set_image256(two::Symbol* self, two::Image256* value) {
		self->m_image256 = value;
	}
	const char* DECL two_Symbol__get_program(two::Symbol* self) {
		return self->m_program;
	}
	void DECL two_Symbol__set_program(two::Symbol* self, const char* value) {
		self->m_program = value;
	}
	void DECL two_Symbol__destroy(two::Symbol* self) {
		delete self;
	}
	// MarchingCubes
	two::Type* DECL two_MarchingCubes__type() {
		return &two::type<two::MarchingCubes>();
	}
	two::MarchingCubes* DECL two_MarchingCubes__construct_1(uint32_t resolution) {
		return new two::MarchingCubes(resolution);
	}
	void DECL two_MarchingCubes_reset_0(two::MarchingCubes* self) {
		self->reset();
	}
	uint32_t DECL two_MarchingCubes_count_0(two::MarchingCubes* self) {
		return self->count();
	}
	void DECL two_MarchingCubes_direct_1(two::MarchingCubes* self, two::MeshAdapter* output) {
		self->direct(*output);
	}
	void DECL two_MarchingCubes_render_1(two::MarchingCubes* self, two::MeshPacker* output) {
		self->render(*output);
	}
	float DECL two_MarchingCubes__get_isolation(two::MarchingCubes* self) {
		return self->m_isolation;
	}
	void DECL two_MarchingCubes__set_isolation(two::MarchingCubes* self, float value) {
		self->m_isolation = value;
	}
	uint32_t DECL two_MarchingCubes__get_subdiv(two::MarchingCubes* self) {
		return self->m_subdiv;
	}
	void DECL two_MarchingCubes__set_subdiv(two::MarchingCubes* self, uint32_t value) {
		self->m_subdiv = value;
	}
	void DECL two_MarchingCubes__destroy(two::MarchingCubes* self) {
		delete self;
	}
	two::Ray* DECL two_to_ray_2(const two::vec3* pos, const two::vec3* dir) {
		static two::Ray temp;
		return (temp = two::to_ray(*pos, *dir), &temp);
	}
	two::Ray* DECL two_to_ray_3(const two::vec3* pos, const two::vec3* dir, float distance) {
		static two::Ray temp;
		return (temp = two::to_ray(*pos, *dir, distance), &temp);
	}
	two::Segment* DECL two_to_segment_1(const two::Ray* ray) {
		static two::Segment temp;
		return (temp = two::to_segment(*ray), &temp);
	}
	float* DECL two_distribute_poisson_2(two::vec2* size, float radius) {
		return (float*)two::distribute_poisson(*size, radius).data();
	}
	void DECL two_add_ball_4(two::MarchingCubes* cubes, const two::vec3* ball, float strength, float subtract) {
		two::add_ball(*cubes, *ball, strength, subtract);
	}
	void DECL two_add_ball_5(two::MarchingCubes* cubes, const two::vec3* ball, float strength, float subtract, const two::Colour* colour) {
		two::add_ball(*cubes, *ball, strength, subtract, *colour);
	}
	void DECL two_add_planeX_3(two::MarchingCubes* cubes, float strength, float subtract) {
		two::add_planeX(*cubes, strength, subtract);
	}
	void DECL two_add_planeY_3(two::MarchingCubes* cubes, float strength, float subtract) {
		two::add_planeY(*cubes, strength, subtract);
	}
	void DECL two_add_planeZ_3(two::MarchingCubes* cubes, float strength, float subtract) {
		two::add_planeZ(*cubes, strength, subtract);
	}
	// CatmullType
	two::CatmullType DECL two_CatmullType_Centripetal() {
		return two::CatmullType::Centripetal;
	}
	two::CatmullType DECL two_CatmullType_Chordal() {
		return two::CatmullType::Chordal;
	}
	two::CatmullType DECL two_CatmullType_CatmullRom() {
		return two::CatmullType::CatmullRom;
	}
	// DrawMode
	two::DrawMode DECL two_DrawMode_OUTLINE() {
		return two::OUTLINE;
	}
	two::DrawMode DECL two_DrawMode_PLAIN() {
		return two::PLAIN;
	}
	// PrimitiveType
	two::PrimitiveType DECL two_PrimitiveType_Points() {
		return two::PrimitiveType::Points;
	}
	two::PrimitiveType DECL two_PrimitiveType_Lines() {
		return two::PrimitiveType::Lines;
	}
	two::PrimitiveType DECL two_PrimitiveType_LineStrip() {
		return two::PrimitiveType::LineStrip;
	}
	two::PrimitiveType DECL two_PrimitiveType_Triangles() {
		return two::PrimitiveType::Triangles;
	}
	two::PrimitiveType DECL two_PrimitiveType_TriangleStrip() {
		return two::PrimitiveType::TriangleStrip;
	}
	two::PrimitiveType DECL two_PrimitiveType_TriangleFan() {
		return two::PrimitiveType::TriangleFan;
	}
	two::PrimitiveType DECL two_PrimitiveType_Count() {
		return two::PrimitiveType::Count;
	}
	// SymbolDetail
	two::SymbolDetail DECL two_SymbolDetail_Lowest() {
		return two::SymbolDetail::Lowest;
	}
	two::SymbolDetail DECL two_SymbolDetail_Low() {
		return two::SymbolDetail::Low;
	}
	two::SymbolDetail DECL two_SymbolDetail_Medium() {
		return two::SymbolDetail::Medium;
	}
	two::SymbolDetail DECL two_SymbolDetail_High() {
		return two::SymbolDetail::High;
	}
	two::SymbolDetail DECL two_SymbolDetail_Highest() {
		return two::SymbolDetail::Highest;
	}
	
}


