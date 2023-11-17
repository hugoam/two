#pragma once

#include <two/infra.h>
#include <two/type.h>





#ifndef TWO_GEOM_EXPORT
#define TWO_GEOM_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum DrawMode : unsigned int;
    export_ enum class PrimitiveType : unsigned int;
    export_ enum class SymbolDetail : unsigned short;
	export_ enum class CatmullType : unsigned int;
    
    export_ class Shape;
    export_ class ShapeVar;
    export_ struct Line;
    export_ struct Rect;
    export_ struct Quad;
    export_ struct Grid2;
    export_ struct Triangle;
    export_ struct Circle;
    export_ struct Torus;
	export_ struct TorusKnot;
    export_ struct Ring;
    export_ struct Ellipsis;
    export_ struct Arc;
    export_ struct ArcLine;
    export_ struct Cylinder;
    export_ struct Capsule;
    export_ struct Cube;
	export_ struct Tetraedr;
    export_ struct Sphere;
    export_ struct SphereRing;
    export_ struct Spheroid;
	export_ struct Icosaedr;
    export_ struct Aabb;
	export_ class Curve2;
	export_ class Curve3;
	export_ struct CurveBezierCubic;
	export_ struct CurveBezierCubic3;
	export_ struct CurveBezierQuadratic;
	export_ struct CurveBezierQuadratic3;
	export_ struct CurveCatmullRom3;
	export_ struct CurveLine;
	export_ struct CurveLine3;
	export_ struct CurveSpline;
	export_ struct CurveSpline3;
    export_ struct Plane;
    export_ struct Plane3;
    export_ struct Face3;
    export_ struct Segment;
    export_ struct Ray;
    export_ struct Plane6;
    export_ struct Point8;
    export_ struct VertexAttribute;
    export_ struct Vertex;
    export_ struct Tri;
    export_ struct ShapeVertex;
    export_ struct ShapeTriangle;
    export_ struct MeshAdapter;
    export_ class Geometry;
    export_ struct MeshPacker;
	export_ class MarchingCubes;
    export_ class Distribution;
    export_ class Poisson;
    export_ class RandomShapePoint;
    export_ struct Polygon;
    export_ struct Box;
    export_ struct Points;
    export_ struct Grid3;
    export_ struct ConvexHull;
    export_ struct Symbol;
    export_ struct ShapeSize;
    export_ struct ProcShape;
    export_ struct CompoundShape;
    export_ struct DispatchDrawProcShape;
    export_ class IcoSphere;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
#include <stl/span.h>
namespace stl
{
	extern template struct refl_ span_ span<two::vec3>;

	extern template class refl_ seque_ vector<two::vec2>;
	extern template class refl_ seque_ vector<two::vec4>;
	extern template class refl_ seque_ vector<two::ivec4>;

	extern template class refl_ seque_ vector<two::Circle>;
}
#endif

namespace two
{
	export_ TWO_GEOM_EXPORT Aabb transform_aabb(const Aabb& source, const mat4& transform);
	export_ TWO_GEOM_EXPORT Aabb translate_aabb(const Aabb& source, const vec3& offset);
	export_ TWO_GEOM_EXPORT vec2 project_aabb_in_plane(const Plane& plane, const Aabb& aabb);

	export_ constexpr inline float c_cmp_epsilon = 0.00001f;
	export_ constexpr inline float c_cmp_epsilon2 = c_cmp_epsilon * c_cmp_epsilon;

	export_ struct refl_ Plane
	{
		attr_ vec3 m_normal;
		attr_ float m_distance;

		Plane(const vec3& normal = vec3(0.f), float distance = 0.f);
		Plane(float a, float b, float c, float d);
		Plane(const vec3& point, const vec3& normal);
		Plane(const vec3& p1, const vec3& p2, const vec3& p3, Clockwise dir = ANTI_CLOCKWISE);
	};

	export_ struct refl_ Plane3
	{
		attr_ vec3 m_origin;
		attr_ vec3 m_a;
		attr_ vec3 m_b;
	};

	export_ struct refl_ Face3
	{
		vec3 m_vertices[3];

		Face3() {}
		Face3(const vec3& a, const vec3& b, const vec3& c) : m_vertices{ a, b, c } {}

		Face3& operator=(const Face3& other) = default; // @kludge: might be a clang modules bug ?
	};

	export_ inline float distance(const Plane& plane, const vec3& p);
	export_ inline vec3 project(const Plane& plane, const vec3& p);
	export_ inline Plane operator*(const mat4& mat, const Plane& p);

	export_ inline Plane normalize(const Plane& plane);

	export_ struct refl_ Segment
	{
		attr_ vec3 m_start;
		attr_ vec3 m_end;
	};

	export_ struct refl_ Ray
	{
		attr_ vec3 m_start;
		attr_ vec3 m_end;
		attr_ vec3 m_dir;
		attr_ vec3 m_inv_dir;
	};

	export_ func_ inline Ray to_ray(const vec3& pos, const vec3& dir, float distance = 1000.f);
	export_ func_ inline Segment to_segment(const Ray& ray);

	export_ struct Plane6
	{
		Plane6();
		Plane6(Plane right, Plane left, Plane up, Plane down, Plane near, Plane far);
		const Plane& operator[](size_t index) const { return *((Plane*)&m_right + index); }
		Plane& operator[](size_t index) { return *((Plane*)&m_right + index); }
		Plane m_right, m_left, m_up, m_down, m_near, m_far;
	};

	export_ struct Point8
	{
		Point8();
		Point8(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e, vec3 f, vec3 g, vec3 h);
		const vec3& operator[](size_t index) const { return *((vec3*)&m_a + index); }
		vec3& operator[](size_t index) { return *(&m_a + index); }
		vec3 m_a, m_b, m_c, m_d, m_e, m_f, g, m_h;
	};
}





namespace two
{
	export_ class refl_ TWO_GEOM_EXPORT Shape
	{
	public:
		inline Shape(Type& type) : m_type(type), m_center(vec3(0.f)) {}
		inline Shape(Type& type, const vec3& center) : m_type(type), m_center(center) {}
		virtual ~Shape() {}

		inline Shape(const Shape& other) : m_type(other.m_type) { *this = other; }
		inline Shape& operator=(const Shape& other) { m_center = other.m_center; return *this; }

		attr_ Type& m_type;
		// @todo add this to reflection need to fix serialization (must either be an argument of child constructors or init members directly)
		vec3 m_center;

		virtual object<Shape> clone() const = 0;
	};

	export_ class refl_ TWO_GEOM_EXPORT ShapeVar
	{
	public:
		constr_ inline ShapeVar() : m_shape() {}
		constr_ inline ShapeVar(const Shape& shape) : m_shape(shape.clone()) {}

		inline ShapeVar(const ShapeVar& other) { *this = other; }
		inline ShapeVar& operator=(const ShapeVar& other) { if(other.m_shape) m_shape = other.m_shape->clone(); return *this; }

		attr_ inline Shape& shape() { return *m_shape; }

		inline operator Shape&() { return *m_shape; }
		inline operator const Shape&() const { return *m_shape; }
		inline Shape& operator*() const { return *m_shape; }

		object<Shape> m_shape;
	};
}

namespace two
{
	export_ struct refl_ TWO_GEOM_EXPORT Line final : public Shape
	{
	public:
		constr_ Line();
		constr_ Line(const vec3& start, const vec3& end);

		attr_ vec3 m_start = vec3(0.f);
		attr_ vec3 m_end = vec3(1.f);

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Rect final : public Shape
	{
	public:
		constr_ Rect();
		constr_ Rect(const vec2& position, const vec2& size);
		constr_ Rect(float x, float y, float w, float h);

		attr_ vec2 m_position = vec2(0.f);
		attr_ vec2 m_size = vec2(1.f);

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Quad final : public Shape
	{
	public:
		constr_ Quad();
		constr_ Quad(const vec3& a, const vec3& b, const vec3& c, const vec3& d);

		Quad(const vec2& size, const vec3& x = x3, const vec3& y = y3);
		Quad(const vec2& offset, const vec2& size, const vec3& x = x3, const vec3& y = y3);
		Quad(const vec3& center, const vec2& size, const vec3& x = x3, const vec3& y = y3);
		Quad(const vec3& center, const vec2& offset, const vec2& size, const vec3& x = x3, const vec3& y = y3);
		Quad(float size, const vec3& x = x3, const vec3& y = y3);
		Quad(const Rect& rect);

		Quad& operator=(const Quad& other) = default;

		/*attr_ mut_*/ vec3 m_vertices[4];

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Grid2 final : public Shape
	{
	public:
		constr_ Grid2();
		constr_ Grid2(const vec2& size, const vec2& space = vec2(1.f));

		attr_ vec2 m_size = vec2(1.f);
		attr_ vec2 m_space = vec2(0.1f);

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Triangle final : public Shape
	{
	public:
		constr_ Triangle();
		constr_ Triangle(const vec2& size);

		attr_ vec2 m_size = vec2(1.f);

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Circle final : public Shape
	{
	public:
		constr_ Circle();
		constr_ Circle(float radius, Axis axis = Axis::Y);
		constr_ Circle(const vec3& center, float radius, Axis axis = Axis::Y);

		bool operator==(const Circle& other) const;

		attr_ float m_radius = 1.f;
		attr_ Axis m_axis = Axis::X;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Torus final : public Shape
	{
	public:
		constr_ Torus();
		constr_ Torus(float radius, float tube, Axis axis = Axis::Y);
		constr_ Torus(const vec3& center, float radius, float tube, Axis axis = Axis::Y);

		//bool operator==(const Torus& other) const;

		attr_ float m_radius = 1.f;
		attr_ float m_tube = 1.f;
		attr_ Axis m_axis = Axis::X;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT TorusKnot final : public Shape
	{
	public:
		constr_ TorusKnot();
		constr_ TorusKnot(float radius, float tube, float p = 2.f, float q = 3.f);
		constr_ TorusKnot(const vec3& center, float radius, float tube, float p = 2.f, float q = 3.f);

		attr_ float m_radius = 1.f;
		attr_ float m_tube = 1.f;
		attr_ float m_p = 2.f;
		attr_ float m_q = 3.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Ring final : public Shape
	{
	public:
		constr_ Ring();
		constr_ Ring(float radius, float min, float max);

		attr_ float m_radius = 1.f;
		attr_ float m_min = 0.f;
		attr_ float m_max = 1.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Ellipsis final : public Shape
	{
	public:
		constr_ Ellipsis();
		constr_ Ellipsis(vec2 radius, Axis axis = Axis::Y);

		attr_ vec2 m_radius = vec2(1.f);
		attr_ Axis m_axis = Axis::Y;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Arc final : public Shape
	{
	public:
		constr_ Arc();
		constr_ Arc(float radius, float start, float end);

		attr_ float m_radius = 1.f;
		attr_ float m_start = 0.f;
		attr_ float m_end = 1.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT ArcLine final : public Shape
	{
	public:
		constr_ ArcLine();
		constr_ ArcLine(const vec3& start, const vec3& middle, const vec3& end);
		constr_ ArcLine(const vec3& center, const vec3& start, const vec3& middle, const vec3& end);

		attr_ vec3 m_start = vec3(0.f);
		attr_ vec3 m_middle;
		attr_ vec3 m_end;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Cylinder final : public Shape
	{
	public:
		constr_ Cylinder();
		constr_ Cylinder(float radius, float height, Axis axis = Axis::X);
		constr_ Cylinder(const vec3& center, float radius, float height, Axis axis = Axis::X);

		attr_ float m_radius = 1.f;
		attr_ float m_height = 2.f;
		attr_ Axis m_axis = Axis::X;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Capsule final : public Shape
	{
	public:
		constr_ Capsule();
		constr_ Capsule(float radius, float height, Axis axis = Axis::X);

		attr_ float m_radius = 1.f;
		attr_ float m_height = 2.f;
		attr_ Axis m_axis = Axis::X;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Cube : public Shape
	{
	public:
		constr_ Cube();
		constr_ Cube(const vec3& extents);
		constr_ Cube(const vec3& center, const vec3& extents);
		Cube(float side);
		Cube(const Aabb& aabb);

		attr_ vec3 m_extents = vec3(0.5f);

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Tetraedr : public Shape
	{
	public:
		constr_ Tetraedr();
		constr_ Tetraedr(float radius);
		constr_ Tetraedr(const vec3& center, float radius);

		attr_ float m_radius = 1.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Sphere final : public Shape
	{
	public:
		constr_ Sphere();
		constr_ Sphere(float radius, float start = 0.f, float end = c_2pi);
		constr_ Sphere(const vec3& center, float radius, float start = 0.f, float end = c_2pi);

		attr_ float m_radius = 1.f;
		attr_ float m_start = 0.f;
		attr_ float m_end = c_2pi;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT SphereRing final : public Shape
	{
	public:
		constr_ SphereRing();
		constr_ SphereRing(float radius, float min, float max);

		attr_ float m_radius = 1.f;
		attr_ float m_min = -1.f;
		attr_ float m_max = 1.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Spheroid final : public Shape
	{
	public:
		constr_ Spheroid();
		constr_ Spheroid(float radius);
		constr_ Spheroid(const vec3& center, float radius);

		attr_ float m_radius = 1.f;

		Circle m_circleX;
		Circle m_circleY;
		Circle m_circleZ;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Icosaedr final : public Shape
	{
	public:
		constr_ Icosaedr();
		constr_ Icosaedr(float radius);
		constr_ Icosaedr(const vec3& center, float radius);

		attr_ float m_radius = 1.f;

		virtual object<Shape> clone() const;
	};
}



namespace two
{
	export_ enum refl_ DrawMode : unsigned int
	{
		OUTLINE = 0,
		PLAIN = 1
	};

	export_ enum class refl_ PrimitiveType : unsigned int
	{
		Points = 0,
		Lines = 1,
		LineStrip = 2,
		Triangles = 3,
		TriangleStrip = 4,
		TriangleFan = 5,
		Count
	};

	export_ struct VertexAttribute
	{
		enum Enum
		{
			Position = 1 << 0,
			Position4 = 1 << 1,
			QPosition = 1 << 2,
			Normal = 1 << 3,
			QNormal = 1 << 4,
			Colour = 1 << 5,
			Tangent = 1 << 6,
			QTangent = 1 << 7,
			Bitangent = 1 << 8,
			TexCoord0 = 1 << 9,
			QTexCoord0 = 1 << 10,
			TexCoord1 = 1 << 11,
			QTexCoord1 = 1 << 12,
			Joints = 1 << 13,
			Weights = 1 << 14,
			MorphPosition0 = 1 << 15,
			MorphPosition1 = 1 << 16,
			MorphPosition2 = 1 << 17,
			MorphPosition3 = 1 << 18,
			MorphNormal0 = 1 << 19,
			MorphNormal1 = 1 << 20,
			MorphNormal2 = 1 << 21,
			MorphNormal3 = 1 << 22,

			Count = 1 << 17
		};
	};

	export_ using ShapeIndex = uint16_t;
	
	export_ struct TWO_GEOM_EXPORT Vertex
	{
		static const uint32_t vertex_format = VertexAttribute::Position;
		vec3 m_position;
	};

	export_ struct TWO_GEOM_EXPORT Tri
	{
		uint32_t a, b, c;
	};

	export_ struct TWO_GEOM_EXPORT ShapeVertex
	{
		static const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::Colour
										    | VertexAttribute::Tangent| VertexAttribute::TexCoord0 | VertexAttribute::Joints | VertexAttribute::Weights;
		vec3 m_position; vec3 m_normal; uint32_t m_colour; vec4 m_tangent; vec2 m_uv0; uint32_t m_joints; vec4 m_weights;
	};

	export_ struct TWO_GEOM_EXPORT ShapeTriangle
	{
		uint32_t a, b, c;
	};

	export_ size_t vertex_attribute_size(VertexAttribute::Enum attribute);

	export_ uint32_t vertex_size(uint32_t vertex_format);

	export_ size_t vertex_offset(uint32_t vertex_format, VertexAttribute::Enum attribute);

	export_ struct refl_ TWO_GEOM_EXPORT MeshAdapter
	{
		MeshAdapter() {}
		MeshAdapter(uint32_t vertex_format, span<void> vertices, span<void> indices = {}, bool index32 = false);
		MeshAdapter(uint32_t vertex_count, MeshPacker& geom);

		attr_ uint32_t m_vertex_format = 0;
		attr_ bool m_index32 = false;

		attr_ uint32_t m_vertex_count = 0;
		attr_ uint32_t m_index_count = 0;

		attr_ uint32_t m_vertex_stride = 0;

		template <class T>
		struct Cursor
		{
			T* p = nullptr; uint32_t s;
			inline void init(void* data) { p = (T*)data; s = uint32_t(sizeof(T)); }
			inline void init(uint32_t vertex_format, VertexAttribute::Enum attr, void* data)
			{
				if((vertex_format & attr) != 0) this->init(data);
			}
			inline void init(uint32_t vertex_format, VertexAttribute::Enum attr, void* data, uint32_t stride)
			{
				if((vertex_format & attr) != 0)
					p = (T*)((char*)data + vertex_offset(vertex_format, attr));
				s = stride;
			}
			inline void next() { p = (T*)((char*)p + s); }
			inline void write(const T& val) { *p = val; this->next(); }
			inline T read() { T val = *p; this->next(); return val; }
			inline operator bool() { return p != nullptr; }
		};

		struct Pointers
		{
			Cursor<uint16_t> m_index;
			Cursor<uint32_t> m_index32;

			Cursor<vec3> m_position;
			Cursor<vec4> m_position4;
			Cursor<vec3> m_normal;
			Cursor<uint32_t> m_colour;
			Cursor<vec4> m_tangent;
			Cursor<vec3> m_bitangent;
			Cursor<vec2> m_uv0;
			Cursor<vec2> m_uv1;
			Cursor<uint32_t> m_joints;
			Cursor<vec4> m_weights;

			Cursor<half3> m_qposition;
			Cursor<uint32_t> m_qnormal;
			Cursor<uint32_t> m_qtangent;
			Cursor<half2> m_quv0;
			Cursor<half2> m_quv1;
		};

		Pointers m_start;
		Pointers m_cursor;

		//void* m_index = nullptr;

		uint32_t m_vertex = 0;
		uint32_t m_offset = 0;

		template <class T>
		struct Bounds { T lo = T(FLT_MAX); T hi = T(-FLT_MAX); void add(const T& val) { lo = min(val, lo); hi = max(val, hi); } };
		Bounds<vec3> m_aabb = {};
		Bounds<vec2> m_uv0_rect = {};
		Bounds<vec2> m_uv1_rect = {};

		meth_ void rewind();
		meth_ void copy(MeshAdapter& dest);
		meth_ void xcopy(MeshAdapter& dest, const mat4& transform);
		meth_ void next();

		MeshAdapter read() const;

		meth_ MeshAdapter& position(const vec3& p);
		meth_ MeshAdapter& position4(const vec4& p);
		meth_ MeshAdapter& normal(const vec3& n);
		meth_ MeshAdapter& colour(const Colour& c);
		meth_ MeshAdapter& tangent(const vec4& t);
		meth_ MeshAdapter& bitangent(const vec3& b);
		meth_ MeshAdapter& uv0(const vec2& uv);
		meth_ MeshAdapter& uv1(const vec2& uv);
		meth_ MeshAdapter& joints(const uint32_t& j);
		meth_ MeshAdapter& weights(const vec4& w);

		MeshAdapter& colour(const vec3& c);

		// direct functions (faster, no bounds computation)
		MeshAdapter& dposition(const vec3& p);
		MeshAdapter& duv0(const vec2& uv);
		MeshAdapter& duv1(const vec2& uv);

		vec3 position();
		vec3 normal();
		Colour colour();
		vec4 tangent();
		vec3 bitangent();
		vec2 uv0();
		vec2 uv1();
		uint32_t joints();
		vec4 weights();
		uint16_t index();
		uint32_t index32();

		void index(uint32_t i);
		void line(uint32_t a, uint32_t b);
		void tri(uint32_t a, uint32_t b, uint32_t c);
		void quad(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

		MeshAdapter& qposition(const vec3& p);
		MeshAdapter& qnormal(const vec3& n);
		MeshAdapter& qtangent(const vec4& t);
		MeshAdapter& quv0(const vec2& uv);
		MeshAdapter& quv1(const vec2& uv);
	};
}



namespace two
{
	export_ TWO_GEOM_EXPORT vec3 circumcenter(const vec3& a, const vec3& b, const vec3& c);

	export_ TWO_GEOM_EXPORT bool segment_triangle_intersection(const vec3& sp, const vec3& sq, const vec3& a, const vec3& b, const vec3& c, float& t);
	export_ TWO_GEOM_EXPORT bool segment_aabb_intersection(const vec3& sp, const vec3& sq, const vec3& amin, const vec3& amax, float& tmin, float& tmax);
	export_ TWO_GEOM_EXPORT bool segment_aabb_intersection_2d(const vec2& p, const vec2& q, const vec2& bmin, const vec2& bmax);

	export_ TWO_GEOM_EXPORT bool ray_aabb_intersection(const vec3& min, const vec3& max, const Ray& R);
	export_ TWO_GEOM_EXPORT bool ray_aabb_intersection(const vec3& min, const vec3& max, const Ray& R, vec3& result);
	export_ TWO_GEOM_EXPORT bool line_circle_intersection(const vec3& l0, const vec3& l1, const vec3& c0, float r, vec3& r0, vec3& r1);
	export_ TWO_GEOM_EXPORT bool circle_circle_intersection(const vec3& c0, float r0, const vec3& c1, float r1, vec3& p1, vec3& p2);
	export_ TWO_GEOM_EXPORT vec3 plane_segment_intersection(const Plane& P, const Segment& S);
	export_ TWO_GEOM_EXPORT vec3 plane_segment_intersection(const vec3& N, float d, const vec3& L1, const vec3& L2);
	export_ TWO_GEOM_EXPORT vec3 plane_segment_intersection(const vec3& P1, const vec3& P2, const vec3& P3, const vec3& L1, const vec3& L2);
	export_ TWO_GEOM_EXPORT vec3 plane_3_intersection(const Plane& plane0, const Plane& plane1, const Plane& plane2);
	export_ TWO_GEOM_EXPORT bool frustum_aabb_intersection(const Plane6& planes, const Aabb& aabb);
	export_ TWO_GEOM_EXPORT bool sphere_aabb_intersection(const vec3& center, float radius, const Aabb& aabb);

	export_ TWO_GEOM_EXPORT vec3 nearest_point_on_face(const Face3& face, const vec3& point);
	export_ TWO_GEOM_EXPORT vec3 nearest_point_on_line(const vec3& origin, const vec3& dir, const vec3& point);

	export_ inline vec4 sphere_plane_intersection(const vec3& sphere_position, float sphere_radius_squared, const vec3& plane_normal, float plane_d)
	{
		const float d = dot(sphere_position, plane_normal) + plane_d;
		const float rr = sphere_radius_squared - d * d;
		return { sphere_position - plane_normal * d, rr };
	}

	// this version returns a false-positive intersection in a small area near the origin of the cone extended outward by the sphere's radius.
	export_ inline bool sphere_cone_intersection_fast(const vec3& sphere_position, float sphere_radius_squared, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared)
	{
		const vec3 u = cone_position - (sphere_radius_squared * cone_sin_inverse) * cone_axis;
		vec3 d = sphere_position - u;
		float e = dot(cone_axis, d);
		float dd = dot(d, d);
		// we do the e>0 last here to avoid a branch
		return (e * e >= dd * cone_cos_squared && e > 0);
	}

	export_ inline bool sphere_cone_intersection(const vec3& sphere_position, float sphere_radius_squared, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared)
	{
		if(sphere_cone_intersection_fast(sphere_position, sphere_radius_squared, cone_position, cone_axis, cone_sin_inverse, cone_cos_squared))
		{
			vec3 d = sphere_position - cone_position;
			float e = -dot(cone_axis, d);
			float dd = dot(d, d);
			if(e * e >= dd * (1 - cone_cos_squared) && e > 0)
				return dd <= sphere_radius_squared * sphere_radius_squared;
			return true;
		}
		return false;
	}
}


//#include <geom/Shapes.h>

namespace two
{
	export_ struct refl_ TWO_GEOM_EXPORT Aabb
	{
	public:
		constr_ Aabb();
		constr_ Aabb(const vec3& center, const vec3& extents);

		attr_ vec3 m_center;
		attr_ vec3 m_extents;
		attr_ bool m_empty;

		vec3 bmin() const;
		vec3 bmax() const;

		bool intersects(const Aabb& other) const;

		void merge(const vec3& point);
		void merge(const Aabb& other);

		bool cull(const vec3& point) const;
		bool cull(span<vec3> points) const;
	};

	export_ TWO_GEOM_EXPORT Aabb aabb(const vec3& min, const vec3& max);

	export_ TWO_GEOM_EXPORT Aabb face_aabb(const vec3* vertices);
	export_ TWO_GEOM_EXPORT Aabb face_aabb(const Face3& face);
}



namespace two
{
	class refl_ Curve2
	{
	public:
		meth_ virtual vec2 point(float t) const = 0;
	};

	class refl_ Curve3
	{
	public:
		meth_ virtual vec3 point(float t) const = 0;
		//virtual vec2 point(float t) const = 0;

		//meth_ float length() const;

		vec3 tangent(float t) const;

		vector<vec3> points(size_t subdiv = 5) const;

		vector<float> lengths() const;
		vector<float> lengths(size_t subdiv) const;

		struct FrenetFrames
		{
			vector<vec3> tangents;
			vector<vec3> normals;
			vector<vec3> binormals;
		};

		// see http://www.cs.indiana.edu/pub/techreports/TR425.pdf
		FrenetFrames frenet_frames(size_t segments, bool closed);

		size_t m_curved_subdiv = 200;
	};

	struct Curve3Sampler
	{
		Curve3Sampler(Curve3& curve);

		void subdiv(size_t subdiv);
		vector<vec3> points(size_t subdiv = 5) const;
		vec3 point(float u) const;
		vec3 tangent(float u) const;
		float at(float u) const;
		float at_distance(float distance) const;

		Curve3& m_curve;
		vector<float> m_lengths;
		bool m_dirty = false;
	};

	struct refl_ CurveSpline : public Curve2
	{
		virtual vec2 point(float t) const override;

		attr_ vector<vec2> m_points;
	};

	struct refl_ CurveSpline3 : public Curve3
	{
		virtual vec3 point(float t) const override;

		attr_ vector<vec3> m_points;
	};

	struct CurveEllipse
	{
		vec2 m_a = vec2(0.f);
		vec2 m_radius = vec2(1.f);
		float m_angle[2] = { 0.f, c_2pi };

		bool m_clockwise = false;
		float m_rotation = 0.f;

		vec2 point(float t);
	};

	struct CurveArcCurve : public CurveEllipse
	{};

	struct refl_ CurveBezierCubic : public Curve2
	{
		virtual vec2 point(float t) const override;

		attr_ vec2 v0;
		attr_ vec2 v1;
		attr_ vec2 v2;
		attr_ vec2 v3;
	};

	struct refl_ CurveBezierCubic3 : public Curve3
	{
		virtual vec3 point(float t) const override;

		attr_ vec3 v0;
		attr_ vec3 v1;
		attr_ vec3 v2;
		attr_ vec3 v3;
	};

	struct refl_ CurveLine : public Curve2
	{
		virtual vec2 point(float t) const override;

		attr_ vec2 v0;
		attr_ vec2 v1;
	};

	struct refl_ CurveLine3 : public Curve3
	{
		virtual vec3 point(float t) const override;

		attr_ vec3 v0;
		attr_ vec3 v1;
	};

	struct refl_ CurveBezierQuadratic : public Curve2
	{
		virtual vec2 point(float t) const override;

		attr_ vec2 v0;
		attr_ vec2 v1;
		attr_ vec2 v2;
	};

	struct refl_ CurveBezierQuadratic3 : public Curve3
	{
		virtual vec3 point(float t) const override;

		attr_ vec3 v0;
		attr_ vec3 v1;
		attr_ vec3 v2;
	};

	enum class refl_ CatmullType : unsigned int
	{
		Centripetal,
		Chordal,
		CatmullRom
	};

	struct refl_ CurveCatmullRom3 : public Curve3
	{
		constr_ CurveCatmullRom3();
		constr_ CurveCatmullRom3(const vector<vec3>& points, bool closed = false, CatmullType curve_type = CatmullType::Centripetal, float tension = 0.5f);

		virtual vec3 point(float t) const override;

		meth_ void add_point(const vec3& point);

		attr_ vector<vec3> m_points = {};
		attr_ bool m_closed = false;
		attr_ CatmullType m_curve_type = CatmullType::Centripetal;
		attr_ float m_tension = 0.5f;
	};
}



namespace two
{
	inline float distance(const Plane& plane, const vec3& p)
	{
		return dot(plane.m_normal, p) - plane.m_distance;
	}

	inline vec3 project(const Plane& plane, const vec3& p)
	{
		return p - plane.m_normal * distance(plane, p);
	}	// Implementation

	inline Plane operator*(const mat4& mat, const Plane& p)
	{
		//const mat4 normalmat = transpose(inverse(mat));
		const vec3 point = p.m_normal * -p.m_distance;
		const vec3 refpoint = mulp(mat, point);
		const vec3 normal = muln(mat, p.m_normal);
		const float d = dot(-refpoint, normal);
		return { normal, d };
	}

	inline Plane::Plane(const vec3& normal, float distance)
		: m_normal(normal), m_distance(distance)
	{}

	inline Plane::Plane(float a, float b, float c, float d)
		: m_normal(a, b, c), m_distance(d)
	{}

	inline Plane::Plane(const vec3& point, const vec3& normal)
		: m_normal(normal), m_distance(dot(normal, point))
	{}

	inline Plane::Plane(const vec3& p1, const vec3& p2, const vec3& p3, Clockwise dir)
		: m_normal(normalize(dir == CLOCKWISE ? cross(p1 - p3, p1 - p2)
											  : cross(p1 - p2, p1 - p3)))
		, m_distance(dot(m_normal, p1))
	{}

	inline Plane normalize(const Plane& plane)
	{
		float l = length(plane.m_normal);
		if(l == 0)
			return { vec3(0.f), 0.f };
		return { plane.m_normal / l, plane.m_distance / l };
	}

	inline Ray to_ray(const vec3& pos, const vec3& dir, float distance) { return { pos, pos + dir * distance, dir, 1.f / dir }; };
	inline Segment to_segment(const Ray& ray) { return { ray.m_start, ray.m_end }; }

	inline Plane6::Plane6() {}
	inline Plane6::Plane6(Plane right, Plane left, Plane up, Plane down, Plane near, Plane far) : m_right(right), m_left(left), m_up(up), m_down(down), m_near(near), m_far(far) {}

	inline Point8::Point8() {}
	inline Point8::Point8(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e, vec3 f, vec3 g, vec3 h) : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e), m_f(f), g(g), m_h(h) {}
}



namespace two
{
	export_ class refl_ TWO_GEOM_EXPORT Geometry final : public Shape
	{
	public:
		constr_ Geometry();

		vector<Vertex> m_vertices;
		vector<Tri> m_triangles;

		vec3 m_bounds_min;
		vec3 m_bounds_max;

		void allocate(size_t vertex_count, size_t tri_count);

		span<Vertex> vertices() { return { &m_vertices[0], m_vertices.size() }; }
		span<uint32_t> indices() { return { &m_triangles[0].a, m_triangles.size() / 3 }; }

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT MeshPacker
	{
		constr_ MeshPacker();

		uint32_t vertex_format() const;
		uint32_t vertex_count() const { return uint32_t(m_positions.size()); }
		uint32_t index_count() const { return uint32_t(m_indices.size()); }
		uint32_t face_count() const { return m_indices.empty() ? this->vertex_count() / 3 : this->index_count() / 3; }

		attr_ PrimitiveType m_primitive = PrimitiveType::Triangles;

		attr_ vector<vec3> m_positions;		// Position
		attr_ vector<vec3> m_normals;		// Normal
		attr_ vector<Colour> m_colours;		// Colour
		attr_ vector<uint32_t> m_ucolours;	// Colour
		attr_ vector<vec4> m_tangents;		// Tangent
		attr_ vector<vec3> m_bitangents;	// Bitangent
		attr_ vector<vec2> m_uv0s;			// Texture Coordinates 0
		attr_ vector<vec2> m_uv1s;			// Texture Coordinates 1
		attr_ vector<ivec4> m_bones;		// Bones Indices
		attr_ vector<vec4> m_weights;		// Bones Weights

		attr_ vector<uint32_t> m_indices;

		meth_ void position(const vec3& p) { m_positions.push_back(p); }
		meth_ void normal(const vec3& n) { m_normals.push_back(n); }
		meth_ void colour(const Colour& c) { m_colours.push_back(c); }
		meth_ void tangent(const vec4& t) { m_tangents.push_back(t); }
		meth_ void bitangent(const vec3& b) { m_bitangents.push_back(b); }
		meth_ void uv0(const vec2& uv) { m_uv0s.push_back(uv); }
		meth_ void uv1(const vec2& uv) { m_uv1s.push_back(uv); }
		meth_ void bones(const ivec4& j) { m_bones.push_back(j); }
		meth_ void weights(const vec4& w) { m_weights.push_back(w); }

		meth_ void index(uint32_t i) { m_indices.push_back(i); }

		attr_ bool m_quantize = false;

		meth_ void resize(uint32_t vertex_count, uint32_t index_count, uint32_t vertex_format);
		meth_ void clear();
		meth_ void pack(MeshAdapter& writer) const;
		meth_ void xpack(MeshAdapter& writer, const mat4& transform) const;
		meth_ void unpack(const MeshAdapter& reader, const mat4& transform);

		void bake(bool normals, bool tangents);

		meth_ void gen_normals(bool area_weighted = true);
		meth_ void gen_flat_normals();
		meth_ void gen_tangents();

		meth_ void smooth_normals();
	};

	export_ TWO_GEOM_EXPORT void generate_mikkt_tangents(span<ShapeIndex> indices, span<ShapeVertex> vertices);
}



namespace two
{
	export_ TWO_GEOM_EXPORT vector<vec3> hilbert2d(vec3 center = vec3(0.f), float size = 10.f, int iterations = 1, 
												   uint v0 = 0, uint v1 = 1, uint v2 = 2, uint v3 = 3);

	export_ TWO_GEOM_EXPORT vector<vec3> hilbert3d(vec3 center = vec3(0.f), float size = 10.f, int iterations = 1,
												   uint v0 = 0, uint v1 = 1, uint v2 = 2, uint v3 = 3, uint v4 = 4, uint v5 = 5, uint v6 = 6, uint v7 = 7);
}



namespace two
{
	export_ class refl_ TWO_GEOM_EXPORT Distribution
	{
	public:
		struct Point
		{
			vec3 position;
			float radius;
			size_t visits = 0;
		};

		//meth_ virtual vector<Circle> distribute(float radius, const vec3& offset) = 0;
		//meth_ virtual bool addPoint(float radius, vec3& point) = 0;
	};

	export_ class refl_ TWO_GEOM_EXPORT Poisson : public Distribution
	{
	public:
		constr_ Poisson(vec2 size, float maxRadius);

		vec2 m_size;
		bool m_overlap = false;
		bool m_start_from_center = false;
		//bool m_fill_closer_first;

		void uniform(float radius);

		meth_ vector<vec3> distribute(float radius);
		meth_ vector<Circle> distribute_circles(float radius);
		meth_ bool addPoint(float radius, vec3& point);

		bool insertPoint(float radius);

		void pushPoint(const Point& point);
		Point randomPointAround(const Point& point, float radius);

		bool checkInside(const Point& point);
		bool checkSpace(const Point& point);

		size_t gridIndex(const Point& point);

	protected:
		float m_cellSize;
		float m_invCellSize;

		size_t m_k = 30U;

		vector<Point> m_points;

		vector<Point> m_unprocessed;
		vector2d<vector<Point>> m_grid;
	};

	export_ TWO_GEOM_EXPORT func_ vector<vec3> distribute_poisson(vec2 size, float radius);
}



namespace two
{
	export_ class TWO_GEOM_EXPORT RandomShapePoint : public Dispatch<vec3>, public LazyGlobal<RandomShapePoint>
	{
	public:
		RandomShapePoint();
	};

	export_ TWO_GEOM_EXPORT vector<vec3> distribute_shape(const Shape& shape, size_t count);
}



namespace two
{
	export_ struct refl_ TWO_GEOM_EXPORT Polygon final : public Shape
	{
	public:
		constr_ Polygon();
		constr_ Polygon(span<vec3> vertices);

		vector<vec3> m_vertices;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Box final : public Shape
	{
	public:
		constr_ Box();
		Box(span<vec3> vertices);

		Box(const Cube& cube);

		vec3 m_vertices[8];

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Points final : public Shape
	{
	public:
		constr_ Points();
		constr_ Points(span<vec3> points);

		attr_ vector<vec3> m_points;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT Grid3 final : public Shape
	{
	public:
		constr_ Grid3();
		constr_ Grid3(const uvec2& size, span<vec3> points = {});

		attr_ uvec2 m_size;
		attr_ vector<vec3> m_points;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ TWO_GEOM_EXPORT ConvexHull final : public Shape
	{
	public:
		constr_ ConvexHull();
		constr_ ConvexHull(span<vec3> vertices);

		attr_ vector<vec3> m_vertices;

		virtual object<Shape> clone() const;
	};
}



namespace two
{
	using cstring = const char*;

	export_ enum class refl_ SymbolDetail : unsigned short
	{
		Lowest,
		Low,
		Medium,
		High,
		Highest
	};

	export_ struct refl_ TWO_GEOM_EXPORT Symbol
	{
	public:
		constr_ Symbol(Colour fill = Colour(1.f), Colour outline = Colour(0.f, 0.f), bool overlay = false, bool double_sided = false, SymbolDetail detail = SymbolDetail::Medium);
		Symbol(cstring image, float alpha = 1.f);
		Symbol(const Image256& image256, float alpha = 1.f);

		constr_ static inline Symbol plain(Colour colour, bool overlay = false) { return Symbol(colour, Colour(0.f, 0.f), overlay); }
		constr_ static inline Symbol wire(Colour colour, bool overlay = false) { return Symbol(Colour(0.f, 0.f), colour, overlay); }

		bool operator==(const Symbol& other) const;

		attr_ Colour m_outline;
		attr_ Colour m_fill;
		attr_ bool m_overlay;
		attr_ bool m_double_sided;
		attr_ SymbolDetail m_detail;
		attr_ uvec2 m_subdiv = uvec2(0U);

		attr_ cstring m_image = nullptr;
		attr_ Image256* m_image256 = nullptr;
		attr_ cstring m_program = nullptr;

		bool outline() const { return !m_outline.null(); }
		bool fill() const { return !m_fill.null(); }
	};
}


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CatmullType>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::DrawMode>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::PrimitiveType>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::SymbolDetail>();
    
    export_ template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::vec2>>();
    export_ template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::vec4>>();
    export_ template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::ivec4>>();
    export_ template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::Circle>>();
    
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Aabb>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Curve2>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Curve3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveSpline>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveSpline3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierCubic>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierCubic3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveLine>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveLine3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierQuadratic>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierQuadratic3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveCatmullRom3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Plane>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Plane3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Face3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Segment>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Ray>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::MeshAdapter>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Shape>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::ShapeVar>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Geometry>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::MeshPacker>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Line>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Rect>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Quad>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Grid2>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Triangle>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Circle>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Torus>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::TorusKnot>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Ring>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Ellipsis>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Arc>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::ArcLine>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Cylinder>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Capsule>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Cube>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Tetraedr>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Sphere>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::SphereRing>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Spheroid>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Icosaedr>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Distribution>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Poisson>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Polygon>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Box>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Points>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Grid3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::ConvexHull>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Symbol>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::MarchingCubes>();
}



namespace two
{
	// port of http://webglsamples.org/blob/blob.html
	export_ class refl_ TWO_GEOM_EXPORT MarchingCubes
	{
	public:
		attr_ float m_isolation = 80.f;
		attr_ uint32_t m_subdiv = 32;

		size_t m_size;
		float m_extent;

		float m_delta;

		uint32_t m_xd;
		uint32_t m_yd;
		uint32_t m_zd;

		vector<float> m_field;
		//vector<uint8_t> m_class;

		vector<vec3> m_colour;

		struct Cache
		{
			struct Normal { vec3 n; bool set = false; };
			vector<Normal> m_normal;

			vec3 vert[12];
			vec3 norm[12];
			vec3 color[12];
		};
		
		mutable Cache m_cache;

	public:
		constr_ MarchingCubes(uint32_t resolution);

		// immediate render mode simulator
		uint8_t classify(size_t q, float isol) const;
		uint8_t polygonize(Cache& cache, const vec3& p, size_t q, float isol) const;
		uint32_t triangulate(MeshAdapter& output, Cache& cache, uint8_t cubeindex) const;
		uint32_t triangulate(MeshPacker& output, Cache& cache, uint8_t cubeindex) const;

		meth_ void reset();

		void begin(Cache& cache) const;

		meth_ uint32_t count() const;
		meth_ void direct(MeshAdapter& output) const;
		meth_ void render(MeshPacker& output) const;
	};

	export_ TWO_GEOM_EXPORT func_ void add_ball(MarchingCubes& cubes, const vec3& ball, float strength, float subtract, const Colour& colour);
	export_ TWO_GEOM_EXPORT func_ void add_ball(MarchingCubes& cubes, const vec3& ball, float strength, float subtract);

	export_ TWO_GEOM_EXPORT func_ void add_planeX(MarchingCubes& cubes, float strength, float subtract);
	export_ TWO_GEOM_EXPORT func_ void add_planeY(MarchingCubes& cubes, float strength, float subtract);
	export_ TWO_GEOM_EXPORT func_ void add_planeZ(MarchingCubes& cubes, float strength, float subtract);
}





namespace two
{
	export_ struct TWO_GEOM_EXPORT ShapeSize
	{
		ShapeSize() : vertex_count(0), index_count(0) {}
		ShapeSize(uint32_t verts, uint32_t indices) : vertex_count(verts), index_count(indices) {}

		operator uvec2() { return vec; }

		union {
			uvec2 vec;
			struct { uint vertex_count; uint index_count; };
		};
	};

	export_ struct TWO_GEOM_EXPORT ProcShape
	{
		Symbol m_symbol;
		const Shape* m_shape;
		DrawMode m_draw_mode;
	};

	export_ TWO_GEOM_EXPORT ShapeSize symbol_line_size(const ProcShape& shape);
	export_ TWO_GEOM_EXPORT ShapeSize symbol_triangle_size(const ProcShape& shape);

	export_ TWO_GEOM_EXPORT void symbol_draw_lines(const ProcShape& shape, MeshAdapter& writer);
	export_ TWO_GEOM_EXPORT void symbol_draw_triangles(const ProcShape& shape, MeshAdapter& writer);
}

namespace two
{
	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const ArcLine& arc);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const ArcLine& arc);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer);

	TWO_GEOM_EXPORT uint16_t circle_vertices(const ProcShape& shape, const vec3& position, vec2 radius, SignedAxis axis, bool lines, MeshAdapter& writer, bool outward_normals = false);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Circle& circle);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Torus& torus);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Torus& torus, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Torus& torus);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const TorusKnot& torus);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const TorusKnot& torus, MeshAdapter& writer);
}



namespace two
{
	export_ struct TWO_GEOM_EXPORT CompoundShape
	{
		vector<ProcShape> m_shapes;
	};

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const CompoundShape& compound);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const CompoundShape& compound, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const CompoundShape& compound);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const CompoundShape& compound, MeshAdapter& writer);
}



namespace two
{
	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Box& box);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Box& box, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Box& box);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Box& box, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Tetraedr& tetra);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Tetraedr& tetra, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Icosaedr& icosa);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Icosaedr& ticosaetra, MeshAdapter& writer);

	// Cube : Box(cube)
	// Aabb : Box(aabb)
}



namespace two
{
	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Cylinder& cylinder);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Cylinder& cylinder, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Cylinder& cylinder);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Cylinder& cylinder, MeshAdapter& writer);
}





namespace two
{
	export_ TWO_GEOM_EXPORT CompoundShape shape_compound(const ProcShape& shape, const Spheroid& spheroid);
}

namespace two
{
	export_ struct TWO_GEOM_EXPORT DispatchDrawProcShape : public Global<DispatchDrawProcShape>
	{
		DispatchDrawProcShape();

		Dispatch<void, ProcShape&> m_compound_shape;
		Dispatch<ShapeSize, const ProcShape&> m_size_lines;
		Dispatch<ShapeSize, const ProcShape&> m_size_triangles;
		Dispatch<void, const ProcShape&, MeshAdapter&> m_draw_lines;
		Dispatch<void, const ProcShape&, MeshAdapter&> m_draw_triangles;
	};

	template <class T_Shape>
	inline void decl_shape_lines(DispatchDrawProcShape& dispatch)
	{
		dispatch_branch<T_Shape>(dispatch.m_size_lines, +[](T_Shape& shape, const ProcShape& procshape) { return size_shape_lines(procshape, shape); });
		dispatch_branch<T_Shape>(dispatch.m_draw_lines, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { draw_shape_lines(procshape, shape, writer); });
	}

	template <class T_Shape>
	inline void decl_shape_triangles(DispatchDrawProcShape& dispatch)
	{
		dispatch_branch<T_Shape>(dispatch.m_size_triangles, +[](T_Shape& shape, const ProcShape& procshape) { return size_shape_triangles(procshape, shape); });
		dispatch_branch<T_Shape>(dispatch.m_draw_triangles, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { draw_shape_triangles(procshape, shape, writer); });
	}

	template <class T_Shape>
	inline void decl_shape(DispatchDrawProcShape& dispatch)
	{
		decl_shape_lines<T_Shape>(dispatch);
		decl_shape_triangles<T_Shape>(dispatch);
	}

	template <class T_Shape>
	inline void decl_compound_shape(DispatchDrawProcShape& dispatch)
	{
		dispatch_branch<T_Shape>(dispatch.m_size_lines, +[](T_Shape& shape, const ProcShape& procshape) { CompoundShape compound = shape_compound(procshape, shape); return size_shape_lines(procshape, compound); });
		dispatch_branch<T_Shape>(dispatch.m_draw_lines, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { CompoundShape compound = shape_compound(procshape, shape); draw_shape_lines(procshape, compound, writer); });

		dispatch_branch<T_Shape>(dispatch.m_size_triangles, +[](T_Shape& shape, const ProcShape& procshape) { CompoundShape compound = shape_compound(procshape, shape); return size_shape_triangles(procshape, compound); });
		dispatch_branch<T_Shape>(dispatch.m_draw_triangles, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { CompoundShape compound = shape_compound(procshape, shape); draw_shape_triangles(procshape, compound, writer); });
	}
}



namespace two
{
	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Geometry& geom);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Geometry& geom, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Geometry& geom);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Geometry& geom, MeshAdapter& writer);
}



namespace two
{
	export_ class TWO_GEOM_EXPORT IcoSphere
	{
	public:
		IcoSphere(int subdiv = 1);

		using Line = ivec2;
		using Face = ivec3;

		vector<vec3> m_vertices;
		vector<Line> m_lines;
		vector<Face> m_faces;

	private:
		int vertex(const vec3& vertex);
		void triangle(int index0, int index1, int index2);
		int middle_point(int index0, int index1);
 
		map<int64_t, int> m_middle_point_cache;

	public:
		static vector<IcoSphere> s_levels;
	};
}



namespace two
{
	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Line& line);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Line& line, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Line& line);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Line& line, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Grid2& grid);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Grid2& grid);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer);
}



namespace two
{
	TWO_GEOM_EXPORT void quad_vertices(const ProcShape& shape, const vec3& center, const vec3& a, const vec3& b, const vec3& c, const vec3& d, bool fill, MeshAdapter& writer);
	TWO_GEOM_EXPORT void quad_vertices(const ProcShape& shape, const vec3& center, span<vec3> vertices, bool fill, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Quad& quad);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Quad& quad, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Quad& quad);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Quad& quad, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Grid3& grid);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Grid3& grid);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer);
}



namespace two
{
	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Sphere& sphere);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Sphere& sphere);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer);
}



namespace two
{
	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Triangle& triangle);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Triangle& triangle, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Triangle& triangle);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Triangle& triangle, MeshAdapter& writer);
}
#ifdef TWO_MODULES




namespace two
{
	inline size_t vertex_attribute_size(VertexAttribute::Enum attribute)
	{
		if(attribute == VertexAttribute::Position)			return sizeof(vec3);
		else if(attribute == VertexAttribute::Position4)	return sizeof(vec4);
		else if(attribute == VertexAttribute::QPosition)	return sizeof(half3);
		else if(attribute == VertexAttribute::Normal)		return sizeof(vec3);
		else if(attribute == VertexAttribute::QNormal)		return sizeof(uint32_t);
		else if(attribute == VertexAttribute::Colour)		return sizeof(uint32_t);
		else if(attribute == VertexAttribute::Tangent)		return sizeof(vec4);
		else if(attribute == VertexAttribute::QTangent)		return sizeof(uint32_t);
		else if(attribute == VertexAttribute::Bitangent)	return sizeof(vec3);
		else if(attribute == VertexAttribute::TexCoord0)	return sizeof(vec2);
		else if(attribute == VertexAttribute::QTexCoord0)	return sizeof(half2);
		else if(attribute == VertexAttribute::TexCoord1)	return sizeof(vec2);
		else if(attribute == VertexAttribute::QTexCoord1)	return sizeof(half2);
		else if(attribute == VertexAttribute::Joints)		return sizeof(uint32_t);
		else if(attribute == VertexAttribute::Weights)		return sizeof(vec4);
		else return 0;
	}

	inline uint32_t vertex_size(uint32_t vertex_format)
	{
		uint32_t size = 0;
		for(VertexAttribute::Enum current = VertexAttribute::Position; current != VertexAttribute::Count; current = VertexAttribute::Enum(current << 1))
		{
			if((vertex_format & current) != 0)
				size += uint32_t(vertex_attribute_size(current));
		}
		return size;
	}

	inline size_t vertex_offset(uint32_t vertex_format, VertexAttribute::Enum attribute)
	{
		size_t offset = 0;
		for(VertexAttribute::Enum current = VertexAttribute::Position; current != attribute; current = VertexAttribute::Enum(current << 1))
		{
			if((vertex_format & current) != 0)
				offset += vertex_attribute_size(current);
		}
		return offset;
	}

	inline MeshAdapter::MeshAdapter(uint32_t vertex_format, span<void> vertices, span<void> indices, bool index32)
		: m_vertex_format(vertex_format), m_index32(index32)
		, m_vertex_count(uint32_t(vertices.size()))
		, m_index_count(uint32_t(indices.size()))
		, m_vertex_stride(vertex_size(vertex_format))
	{
		uint32_t stride = vertex_size(vertex_format);

		m_start.m_position .init(vertex_format, VertexAttribute::Position,  vertices.data(), stride);
		m_start.m_position4.init(vertex_format, VertexAttribute::Position4, vertices.data(), stride);
		m_start.m_normal   .init(vertex_format, VertexAttribute::Normal,    vertices.data(), stride);
		m_start.m_colour   .init(vertex_format, VertexAttribute::Colour,    vertices.data(), stride);
		m_start.m_tangent  .init(vertex_format, VertexAttribute::Tangent,   vertices.data(), stride);
		m_start.m_bitangent.init(vertex_format, VertexAttribute::Bitangent, vertices.data(), stride);
		m_start.m_uv0	   .init(vertex_format, VertexAttribute::TexCoord0, vertices.data(), stride);
		m_start.m_uv1      .init(vertex_format, VertexAttribute::TexCoord1, vertices.data(), stride);
		m_start.m_joints   .init(vertex_format, VertexAttribute::Joints,    vertices.data(), stride);
		m_start.m_weights  .init(vertex_format, VertexAttribute::Weights,   vertices.data(), stride);
		
		m_start.m_qposition.init(vertex_format, VertexAttribute::QPosition,  vertices.data(), stride);
		m_start.m_qnormal  .init(vertex_format, VertexAttribute::QNormal,    vertices.data(), stride);
		m_start.m_qtangent .init(vertex_format, VertexAttribute::QTangent,   vertices.data(), stride);
		m_start.m_quv0     .init(vertex_format, VertexAttribute::QTexCoord0, vertices.data(), stride);
		m_start.m_quv1     .init(vertex_format, VertexAttribute::QTexCoord1, vertices.data(), stride);

		if(index32)
			m_start.m_index32.init(indices.data());
		else
			m_start.m_index.init(indices.data());

		m_cursor = m_start;
	}

	inline MeshAdapter MeshAdapter::read() const { MeshAdapter reader = *this; reader.rewind(); return reader; }

#if 0
	inline MeshAdapter& MeshAdapter::position(const vec3& p) { m_aabb.add(p); *m_cursor.m_position = p; next(m_cursor.m_position); ++m_vertex; return *this; }
	inline MeshAdapter& MeshAdapter::position4(const vec4& p) { m_aabb.add(vec3(p)); *m_cursor.m_position4 = p; next(m_cursor.m_position4); ++m_vertex; return *this; }
	inline MeshAdapter& MeshAdapter::normal(const vec3& n) { if(m_cursor.m_normal) { *m_cursor.m_normal = n; next(m_cursor.m_normal); } return *this; }
	inline MeshAdapter& MeshAdapter::colour(const Colour& c) { if(m_cursor.m_colour) { *m_cursor.m_colour = to_abgr(c); next(m_cursor.m_colour); } return *this; }
	inline MeshAdapter& MeshAdapter::tangent(const vec4& t) { if(m_cursor.m_tangent) { *m_cursor.m_tangent = t; next(m_cursor.m_tangent); } return *this; }
	inline MeshAdapter& MeshAdapter::bitangent(const vec3& b) { if(m_cursor.m_bitangent) { *m_cursor.m_bitangent = b; next(m_cursor.m_bitangent); } return *this; }
	inline MeshAdapter& MeshAdapter::uv0(const vec2& uv) { if(m_cursor.m_uv0) { m_uv0_rect.add(uv); *m_cursor.m_uv0 = uv; next(m_cursor.m_uv0); } return *this; }
	inline MeshAdapter& MeshAdapter::uv1(const vec2& uv) { if(m_cursor.m_uv1) { m_uv1_rect.add(uv); *m_cursor.m_uv1 = uv; next(m_cursor.m_uv1); } return *this; }
	inline MeshAdapter& MeshAdapter::joints(const uint32_t& j) { if(m_cursor.m_joints) { *m_cursor.m_joints = j; next(m_cursor.m_joints); } return *this; }
	inline MeshAdapter& MeshAdapter::weights(const vec4& w) { if(m_cursor.m_weights) { *m_cursor.m_weights = w; next(m_cursor.m_weights); } return *this; }
#endif

	inline MeshAdapter& MeshAdapter::dposition(const vec3& p) { m_cursor.m_position.write(p); ++m_vertex; return *this; }
	inline MeshAdapter& MeshAdapter::duv0(const vec2& uv) { if(m_cursor.m_uv0) { m_cursor.m_uv0.write(uv); } return *this; }
	inline MeshAdapter& MeshAdapter::duv1(const vec2& uv) { if(m_cursor.m_uv1) { m_cursor.m_uv1.write(uv); } return *this; }

	inline vec3 MeshAdapter::position() { return m_cursor.m_position.read(); }
	inline vec3 MeshAdapter::normal() { if(!m_cursor.m_normal) return vec3(0.f); return m_cursor.m_normal.read(); }
	inline Colour MeshAdapter::colour() { if(!m_cursor.m_colour) return Colour::None; return abgr(m_cursor.m_colour.read()); }
	inline vec4 MeshAdapter::tangent() { if(!m_cursor.m_tangent) return vec4(vec3(0.f), 1.f); return m_cursor.m_tangent.read(); }
	inline vec2 MeshAdapter::uv0() { if(!m_cursor.m_uv0) return vec2(0.f); return m_cursor.m_uv0.read(); }
	inline vec2 MeshAdapter::uv1() { if(!m_cursor.m_uv1) return vec2(0.f); return m_cursor.m_uv1.read(); }
	inline uint32_t MeshAdapter::joints() { if(!m_cursor.m_joints) return uint32_t(0U); return m_cursor.m_joints.read(); }
	inline vec4 MeshAdapter::weights() { if(!m_cursor.m_weights) return vec4(0.f); return m_cursor.m_weights.read(); }
	inline uint16_t MeshAdapter::index() { return m_cursor.m_index.read(); }
	inline uint32_t MeshAdapter::index32() { return m_cursor.m_index32.read(); }

	inline void MeshAdapter::index(uint32_t i) { uint32_t index = i + m_offset; m_index32 ? m_cursor.m_index32.write(index) : m_cursor.m_index.write(uint16_t(index)); }
	inline void MeshAdapter::line(uint32_t a, uint32_t b) { index(a); index(b); }
	inline void MeshAdapter::tri(uint32_t a, uint32_t b, uint32_t c) { index(a); index(b); index(c); }
	inline void MeshAdapter::quad(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { tri(a, b, c); tri(c, d, a); }
}
#endif
