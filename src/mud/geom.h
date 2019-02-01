#pragma once

#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifndef MUD_MODULES
#endif



#ifndef MUD_GEOM_EXPORT
#define MUD_GEOM_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum DrawMode : unsigned int;
    enum class PrimitiveType : unsigned int;
    enum class SymbolDetail : unsigned short;
    
    
    class Shape;
    struct ShapeVar;
    struct Line;
    struct Rect;
    struct Quad;
    struct Grid2;
    struct Triangle;
    struct Circle;
    struct Torus;
    struct Ring;
    struct Ellipsis;
    struct Arc;
    struct ArcLine;
    struct Cylinder;
    struct Capsule;
    struct Cube;
    struct Sphere;
    struct SphereRing;
    struct Spheroid;
    struct Aabb;
    struct Plane;
    struct Plane3;
    struct Face3;
    struct Segment;
    struct Ray;
    struct Plane6;
    struct Point8;
    struct VertexAttribute;
    struct Vertex;
    struct Tri;
    struct ShapeVertex;
    struct ShapeTriangle;
    struct MeshAdapter;
    class Geometry;
    struct MeshPacker;
    class Distribution;
    class Poisson;
    class RandomShapePoint;
    struct Polygon;
    struct Box;
    struct Points;
    struct Grid3;
    struct ConvexHull;
    struct Symbol;
    struct ShapeSize;
    struct ProcShape;
    struct CompoundShape;
    struct DispatchDrawProcShape;
    class IcoSphere;
}
//#include <geom/Shapes.h>

namespace mud
{
	export_ struct refl_ MUD_GEOM_EXPORT Aabb
	{
	public:
		constr_ Aabb();
		constr_ Aabb(const vec3& center, const vec3& extents);

		attr_ vec3 m_center;
		attr_ vec3 m_extents;
		attr_ bool m_empty;

		vec3 bmin() const { return m_center - m_extents; }
		vec3 bmax() const { return m_center + m_extents; }

		bool intersects(const Aabb& other) const;

		void merge(const vec3& point);
		void merge(const Aabb& other);
		void mergeSafe(const Aabb& other);

		bool cull(const vec3& point) const;
		bool cull(array<vec3> points) const;
	};

	export_ inline Aabb aabb(const vec3& min, const vec3& max)
	{
		vec3 extents = (max - min) / 2.f;
		return Aabb(min + extents, extents);
	}

	export_ MUD_GEOM_EXPORT Aabb face_aabb(const vec3* vertices);
	export_ MUD_GEOM_EXPORT Aabb face_aabb(const Face3& face);
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ MUD_GEOM_EXPORT Aabb transform_aabb(const Aabb& source, const mat4& transform);
	export_ MUD_GEOM_EXPORT Aabb translate_aabb(const Aabb& source, const vec3& offset);
	export_ MUD_GEOM_EXPORT vec2 project_aabb_in_plane(const Plane& plane, const Aabb& aabb);

	export_ extern MUD_GEOM_EXPORT const float c_cmp_epsilon;
	export_ extern MUD_GEOM_EXPORT const float c_cmp_epsilon2;

	export_ struct refl_ Plane
	{
		attr_ vec3 m_normal;
		attr_ float m_distance;

		Plane(const vec3& normal = Zero3, float distance = 0.f);
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
		vec3 m_a, m_b, m_c, m_d, m_e, m_f, m_g, m_h;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ MUD_GEOM_EXPORT vec3 circumcenter(const vec3& a, const vec3& b, const vec3& c);

	export_ MUD_GEOM_EXPORT bool segment_triangle_intersection(const vec3& sp, const vec3& sq, const vec3& a, const vec3& b, const vec3& c, float& t);
	export_ MUD_GEOM_EXPORT bool segment_aabb_intersection(const vec3& sp, const vec3& sq, const vec3& amin, const vec3& amax, float& tmin, float& tmax);
	export_ MUD_GEOM_EXPORT bool segment_aabb_intersection_2d(const vec2& p, const vec2& q, const vec2& bmin, const vec2& bmax);

	export_ MUD_GEOM_EXPORT bool ray_aabb_intersection(const vec3& min, const vec3& max, const Ray& R);
	export_ MUD_GEOM_EXPORT bool ray_aabb_intersection(const vec3& min, const vec3& max, const Ray& R, vec3& result);
	export_ MUD_GEOM_EXPORT bool line_circle_intersection(const vec3& l0, const vec3& l1, const vec3& c0, float r, vec3& r0, vec3& r1);
	export_ MUD_GEOM_EXPORT bool circle_circle_intersection(const vec3& c0, float r0, const vec3& c1, float r1, vec3& p1, vec3& p2);
	export_ MUD_GEOM_EXPORT vec3 plane_segment_intersection(const Plane& P, const Segment& S);
	export_ MUD_GEOM_EXPORT vec3 plane_segment_intersection(const vec3& N, float d, const vec3& L1, const vec3& L2);
	export_ MUD_GEOM_EXPORT vec3 plane_segment_intersection(const vec3& P1, const vec3& P2, const vec3& P3, const vec3& L1, const vec3& L2);
	export_ MUD_GEOM_EXPORT vec3 plane_3_intersection(const Plane& plane0, const Plane& plane1, const Plane& plane2);
	export_ MUD_GEOM_EXPORT bool frustum_aabb_intersection(const Plane6& planes, const Aabb& aabb);
	export_ MUD_GEOM_EXPORT bool sphere_aabb_intersection(const vec3& center, float radius, const Aabb& aabb);

	export_ MUD_GEOM_EXPORT vec3 nearest_point_on_face(const Face3& face, const vec3& point);
	export_ MUD_GEOM_EXPORT vec3 nearest_point_on_line(const vec3& origin, const vec3& dir, const vec3& point);

	inline vec4 sphere_plane_intersection(const vec3& sphere_position, float sphere_radius_squared, const vec3& plane_normal, float plane_d)
	{
		const float d = dot(sphere_position, plane_normal) + plane_d;
		const float rr = sphere_radius_squared - d * d;
		return { sphere_position - plane_normal * d, rr };
	}

	// this version returns a false-positive intersection in a small area near the origin of the cone extended outward by the sphere's radius.
	inline bool sphere_cone_intersection_fast(const vec3& sphere_position, float sphere_radius_squared, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared)
	{
		const vec3 u = cone_position - (sphere_radius_squared * cone_sin_inverse) * cone_axis;
		vec3 d = sphere_position - u;
		float e = dot(cone_axis, d);
		float dd = dot(d, d);
		// we do the e>0 last here to avoid a branch
		return (e * e >= dd * cone_cos_squared && e > 0);
	}

	inline bool sphere_cone_intersection(const vec3& sphere_position, float sphere_radius_squared, const vec3& cone_position, const vec3& cone_axis, float cone_sin_inverse, float cone_cos_squared)
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




#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <cfloat>
#endif

namespace mud
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
		LineLoop = 2,
		LineStrip = 3,
		Triangles = 4,
		TriangleStrip = 5,
		TriangleFan = 6
	};

	export_ struct VertexAttribute
	{
		enum Enum
		{
			Position = 1 << 0,
			QPosition = 1 << 1,
			Normal = 1 << 2,
			QNormal = 1 << 3,
			Colour = 1 << 4,
			Tangent = 1 << 5,
			QTangent = 1 << 6,
			Bitangent = 1 << 7,
			TexCoord0 = 1 << 8,
			QTexCoord0 = 1 << 9,
			TexCoord1 = 1 << 10,
			QTexCoord1 = 1 << 11,
			Joints = 1 << 12,
			Weights = 1 << 13,

			Count = 1 << 14
		};
	};

	export_ using ShapeIndex = uint16_t;
	
	export_ struct MUD_GEOM_EXPORT Vertex
	{
		static const uint32_t vertex_format = VertexAttribute::Position;
		vec3 m_position;
	};

	export_ struct MUD_GEOM_EXPORT Tri
	{
		uint32_t a, b, c;
	};

	export_ struct MUD_GEOM_EXPORT ShapeVertex
	{
		static const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::Colour
										    | VertexAttribute::Tangent| VertexAttribute::TexCoord0 | VertexAttribute::Joints | VertexAttribute::Weights;
		vec3 m_position; vec3 m_normal; uint32_t m_colour; vec4 m_tangent; vec2 m_uv0; uint32_t m_joints; vec4 m_weights;
	};

	export_ struct MUD_GEOM_EXPORT ShapeTriangle
	{
		uint32_t a, b, c;
	};

	export_ size_t vertex_attribute_size(VertexAttribute::Enum attribute);

	export_ uint32_t vertex_size(uint32_t vertex_format);

	export_ size_t vertex_offset(uint32_t vertex_format, VertexAttribute::Enum attribute);

	export_ struct MeshAdapter
	{
		struct Array
		{
			Array();
			Array(void* pointer, uint32_t count);
				
			uint32_t size();
			void* data() const;

			void* m_pointer;
			uint32_t m_count;
		};

		MeshAdapter();
		MeshAdapter(uint32_t vertex_format, void* vertices, uint32_t num_vertices, void* indices, uint32_t num_indices, bool index32);

		Array m_vertices = {};
		Array m_indices = {};

		//array<void> m_vertices = {};
		//array<void> m_indices = {};

		uint32_t m_vertex_format = 0;
		uint32_t m_vertex_stride = 0;
		uint32_t m_index_stride = 0;

		struct Pointers
		{
			vec3* m_position = nullptr;
			vec3* m_normal = nullptr;
			uint32_t* m_colour = nullptr;
			vec4* m_tangent = nullptr;
			vec3* m_bitangent = nullptr;
			vec2* m_uv0 = nullptr;
			vec2* m_uv1 = nullptr;
			uint32_t* m_joints = nullptr;
			vec4* m_weights = nullptr;

			half3* m_qposition = nullptr;
			uint32_t* m_qnormal = nullptr;
			uint32_t* m_qtangent = nullptr;
			half2* m_quv0 = nullptr;
			half2* m_quv1 = nullptr;
		};

		Pointers m_start;
		Pointers m_cursor;

		void* m_index = nullptr;

		uint32_t m_vertex = 0;
		uint32_t m_offset = 0;

		template <class T>
		struct Bounds { T lo = T(FLT_MAX); T hi = T(-FLT_MAX); void add(const T& val) { lo = min(val, lo); hi = max(val, hi); } };
		Bounds<vec3> m_aabb = {};
		Bounds<vec2> m_uv0_rect = {};
		Bounds<vec2> m_uv1_rect = {};

		void rewind();
		void next();

		MeshAdapter read() const;

		template <class T>
		inline void next(T*& pointer);

		MeshAdapter& position(const vec3& p);
		MeshAdapter& normal(const vec3& n);
		MeshAdapter& colour(const Colour& c);
		MeshAdapter& tangent(const vec4& t);
		MeshAdapter& bitangent(const vec4& b);
		MeshAdapter& uv0(const vec2& uv);
		MeshAdapter& uv1(const vec2& uv);
		MeshAdapter& joints(const uint32_t& j);
		MeshAdapter& weights(const vec4& w);

		vec3 position();
		vec3 normal();
		Colour colour();
		vec4 tangent();
		vec2 uv0();
		vec2 uv1();
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


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class refl_ MUD_GEOM_EXPORT Shape
	{
	public:
		Shape(Type& type) : m_type(type), m_center(Zero3) {}
		Shape(Type& type, const vec3& center) : m_type(type), m_center(center) {}
		virtual ~Shape() {}

		Shape(const Shape& other) : m_type(other.m_type) { *this = other; }
		Shape& operator=(const Shape& other) { m_center = other.m_center; return *this; }

		attr_ Type& m_type;
		// @todo add this to reflection need to fix serialization (must either be an argument of child constructors or init members directly)
		vec3 m_center;

		virtual object<Shape> clone() const = 0;
	};

	export_ struct refl_ MUD_GEOM_EXPORT ShapeVar
	{
	public:
		constr_ ShapeVar() : m_shape() {}
		constr_ ShapeVar(const Shape& shape) : m_shape(shape.clone()) {}

		ShapeVar(const ShapeVar& other) { *this = other; }
		ShapeVar& operator=(const ShapeVar& other) { if(other.m_shape) m_shape = other.m_shape->clone(); return *this; }

		attr_ Shape& shape() { return *m_shape; }

		operator Shape&() { return *m_shape; }
		operator const Shape&() const { return *m_shape; }
		Shape& operator*() const { return *m_shape; }

		object<Shape> m_shape;
	};
}

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_GEOM_EXPORT Geometry final : public Shape
	{
	public:
		constr_ Geometry();

		vector<Vertex> m_vertices;
		vector<Tri> m_triangles;

		vec3 m_bounds_min;
		vec3 m_bounds_max;

		void allocate(size_t vertex_count, size_t tri_count);

		array<Vertex> vertices() { return { &m_vertices[0], m_vertices.size() }; }
		array<uint32_t> indices() { return { &m_triangles[0].a, m_triangles.size() / 3 }; }

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT MeshPacker
	{
		constr_ MeshPacker();

		uint32_t vertex_format();
		uint32_t vertex_count() { return uint32_t(m_positions.size()); }
		uint32_t index_count() { return m_indices.size() > 0 ? uint32_t(m_indices.size()) : uint32_t(m_positions.size()); }

		PrimitiveType m_primitive = PrimitiveType::Triangles;

		vector<vec3> m_positions;		// Position
		vector<vec3> m_normals;		// Normal
		vector<Colour> m_colours;		// Colour
		vector<vec4> m_tangents;		// Tangent
		vector<vec3> m_bitangents;		// Bitangent
		vector<vec2> m_uv0s;			// Texture Coordinates 0
		vector<vec2> m_uv1s;			// Texture Coordinates 1
		vector<ivec4> m_bones;			// Bones Indices
		vector<vec4> m_weights;		// Bones Weights

		vector<uint32_t> m_indices;

		bool m_quantize = false;

		void bake(bool normals, bool tangents);

		void pack_vertices(MeshAdapter& writer, const mat4& transform);
		void generate_normals();
		void generate_tangents();
	};

	export_ MUD_GEOM_EXPORT void generate_mikkt_tangents(array<ShapeIndex> indices, array<ShapeVertex> vertices);
}


#ifndef MUD_MODULES
#endif


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ struct refl_ MUD_GEOM_EXPORT Line final : public Shape
	{
	public:
		constr_ Line();
		constr_ Line(const vec3& start, const vec3& end);

		attr_ vec3 m_start = Zero3;
		attr_ vec3 m_end = Unit3;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Rect final : public Shape
	{
	public:
		constr_ Rect();
		constr_ Rect(const vec2& position, const vec2& size);
		constr_ Rect(float x, float y, float w, float h);

		attr_ vec2 m_position = Zero2;
		attr_ vec2 m_size = Unit2;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Quad final : public Shape
	{
	public:
		constr_ Quad();
		constr_ Quad(const vec3& a, const vec3& b, const vec3& c, const vec3& d);

		Quad(const vec2& size, const vec3& x = X3, const vec3& y = Y3);
		Quad(const vec2& offset, const vec2& size, const vec3& x = X3, const vec3& y = Y3);
		Quad(const vec3& center, const vec2& size, const vec3& x = X3, const vec3& y = Y3);
		Quad(const vec3& center, const vec2& offset, const vec2& size, const vec3& x = X3, const vec3& y = Y3);
		Quad(float size, const vec3& x = X3, const vec3& y = Y3);
		Quad(const Rect& rect);

		Quad& operator=(const Quad& other) = default;

		/*attr_ mut_*/ vec3 m_vertices[4];

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Grid2 final : public Shape
	{
	public:
		constr_ Grid2();
		constr_ Grid2(const vec2& size, const vec2& space = Unit2);

		attr_ vec2 m_size = vec2{ 1.f };
		attr_ vec2 m_space = vec2{ 0.1f };

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Triangle final : public Shape
	{
	public:
		constr_ Triangle();
		constr_ Triangle(const vec2& size);

		attr_ vec2 m_size = Unit2;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Circle final : public Shape
	{
	public:
		constr_ Circle();
		constr_ Circle(float radius, Axis axis = Axis::Y);
		constr_ Circle(const vec3& center, float radius, Axis axis = Axis::Y);

		bool operator==(const Circle& other) const { return m_radius == other.m_radius && m_axis == other.m_axis && m_center == other.m_center; }

		attr_ float m_radius = 1.f;
		attr_ Axis m_axis = Axis::X;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Torus final : public Shape
	{
	public:
		constr_ Torus();
		constr_ Torus(float radius, float solid_radius, Axis axis = Axis::Y);
		constr_ Torus(const vec3& center, float radius, float solid_radius, Axis axis = Axis::Y);

		bool operator==(const Torus& other) const { return m_radius == other.m_radius && m_solid_radius == other.m_solid_radius && m_axis == other.m_axis && m_center == other.m_center; }

		attr_ float m_radius = 1.f;
		attr_ float m_solid_radius = 1.f;
		attr_ Axis m_axis = Axis::X;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Ring final : public Shape
	{
	public:
		constr_ Ring();
		constr_ Ring(float radius, float min, float max);

		attr_ float m_radius = 1.f;
		attr_ float m_min = 0.f;
		attr_ float m_max = 1.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Ellipsis final : public Shape
	{
	public:
		constr_ Ellipsis();
		constr_ Ellipsis(vec2 radius, Axis axis = Axis::Y);

		attr_ vec2 m_radius = Unit2;
		attr_ Axis m_axis = Axis::Y;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Arc final : public Shape
	{
	public:
		constr_ Arc();
		constr_ Arc(float radius, float start, float end);

		attr_ float m_radius = 1.f;
		attr_ float m_start = 0.f;
		attr_ float m_end = 1.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT ArcLine final : public Shape
	{
	public:
		constr_ ArcLine();
		constr_ ArcLine(const vec3& start, const vec3& middle, const vec3& end);
		constr_ ArcLine(const vec3& center, const vec3& start, const vec3& middle, const vec3& end);

		attr_ vec3 m_start = Zero3;
		attr_ vec3 m_middle;
		attr_ vec3 m_end;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Cylinder final : public Shape
	{
	public:
		constr_ Cylinder();
		constr_ Cylinder(float radius, float height, Axis axis = Axis::X);

		attr_ float m_radius = 1.f;
		attr_ float m_height = 2.f;
		attr_ Axis m_axis = Axis::X;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Capsule final : public Shape
	{
	public:
		constr_ Capsule();
		constr_ Capsule(float radius, float height, Axis axis = Axis::X);

		attr_ float m_radius = 1.f;
		attr_ float m_height = 2.f;
		attr_ Axis m_axis = Axis::X;

		virtual object<Shape> clone() const;
	};


	export_ struct refl_ MUD_GEOM_EXPORT Cube : public Shape
	{
	public:
		constr_ Cube();
		constr_ Cube(const vec3& extents);
		constr_ Cube(const vec3& center, const vec3& extents);
		Cube(float side);
		Cube(const Aabb& aabb);

		attr_ vec3 m_extents = vec3{ 0.5f };

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Sphere final : public Shape
	{
	public:
		constr_ Sphere();
		constr_ Sphere(float radius);
		constr_ Sphere(const vec3& center, float radius);

		attr_ float m_radius = 1.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT SphereRing final : public Shape
	{
	public:
		constr_ SphereRing();
		constr_ SphereRing(float radius, float min, float max);

		attr_ float m_radius = 1.f;
		attr_ float m_min = -1.f;
		attr_ float m_max = 1.f;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Spheroid final : public Shape
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
}

namespace mud
{
	export_ class refl_ MUD_GEOM_EXPORT Distribution
	{
	public:
		class Point
		{
		public:
			Point() {}
			Point(const vec3& p, float r) : position(p), radius(r), visits(0) {}

			vec3 position;
			float radius;
			size_t visits;
		};

		//meth_ virtual vector<Circle> distribute(float radius, const vec3& offset) = 0;
		//meth_ virtual bool addPoint(float radius, vec3& point) = 0;
	};

	export_ class refl_ MUD_GEOM_EXPORT Poisson : public Distribution
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
		Grid<vector<Point>> m_grid;
	};

	MUD_GEOM_EXPORT func_ vector<vec3> distribute_poisson(vec2 size, float radius);
}


#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class MUD_GEOM_EXPORT RandomShapePoint : public Dispatch<vec3>, public LazyGlobal<RandomShapePoint>
	{
	public:
		RandomShapePoint();
	};

	export_ MUD_GEOM_EXPORT vector<vec3> distribute_shape(const Shape& shape, size_t count);
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif

namespace mud
{
	export_ struct refl_ MUD_GEOM_EXPORT Polygon final : public Shape
	{
	public:
		constr_ Polygon();
		constr_ Polygon(vector<vec3> vertices);

		vector<vec3> m_vertices;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Box final : public Shape
	{
	public:
		constr_ Box();
		Box(array<vec3> vertices);

		Box(const Cube& cube);

		vec3 m_vertices[8];

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Points final : public Shape
	{
	public:
		constr_ Points();
		constr_ Points(const vector<vec3>& points);

		attr_ vector<vec3> m_points;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Grid3 final : public Shape
	{
	public:
		constr_ Grid3();
		constr_ Grid3(const uvec2& size, const vector<vec3>& points = {});

		attr_ uvec2 m_size;
		attr_ vector<vec3> m_points;

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT ConvexHull final : public Shape
	{
	public:
		constr_ ConvexHull();
		constr_ ConvexHull(const vector<vec3>& vertices);

		attr_ vector<vec3> m_vertices;

		virtual object<Shape> clone() const;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
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

	export_ struct refl_ MUD_GEOM_EXPORT Symbol
	{
	public:
		constr_ Symbol(Colour fill = Colour::White, Colour outline = Colour::None, bool overlay = false, bool double_sided = false, SymbolDetail detail = SymbolDetail::Medium);
		Symbol(cstring image, float alpha = 1.f);
		Symbol(const Image256& image256, float alpha = 1.f);

		constr_ static Symbol plain(Colour colour, bool overlay = false) { return Symbol(colour, Colour::None, overlay); }
		constr_ static Symbol wire(Colour colour, bool overlay = false) { return Symbol(Colour::None, colour, overlay); }

		bool operator==(const Symbol& other) const;

		attr_ Colour m_outline;
		attr_ Colour m_fill;
		attr_ bool m_overlay;
		attr_ bool m_double_sided;
		attr_ SymbolDetail m_detail;

		attr_ cstring m_image = nullptr;
		attr_ Image256* m_image256 = nullptr;
		attr_ cstring m_program = nullptr;

		bool outline() const { return !m_outline.null(); }
		bool fill() const { return !m_fill.null(); }
	};
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <stdint.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::DrawMode>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::PrimitiveType>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::SymbolDetail>();
    
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Distribution>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Face3>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::MeshPacker>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Plane>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Plane3>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Ray>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Segment>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Shape>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::ShapeVar>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Symbol>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Arc>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::ArcLine>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Capsule>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Cube>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Aabb>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Box>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Circle>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::ConvexHull>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Cylinder>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Ellipsis>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Geometry>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Grid2>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Grid3>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Line>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Points>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Poisson>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Polygon>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Quad>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Rect>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Ring>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Sphere>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::SphereRing>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Spheroid>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Torus>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Triangle>();
    
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Distribution*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Face3*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::MeshPacker*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Plane*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Plane3*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Ray*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Segment*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Shape*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::ShapeVar*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Symbol*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Arc*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::ArcLine*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Capsule*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Cube*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Aabb*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Box*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Circle*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::ConvexHull*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Cylinder*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Ellipsis*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Geometry*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Grid2*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Grid3*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Line*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Points*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Poisson*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Polygon*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Quad*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Rect*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Ring*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Sphere*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::SphereRing*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Spheroid*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Torus*>>();
    export_ template <> MUD_GEOM_EXPORT Type& type<vector<mud::Triangle*>>();
}




#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ struct MUD_GEOM_EXPORT ShapeSize
	{
		ShapeSize() : vertex_count(0), index_count(0) {}
		ShapeSize(int verts, int indices) : vertex_count(verts), index_count(indices) {}

		operator uvec2() { return vec; }

		union {
			uvec2 vec;
			struct { int vertex_count; int index_count; };
		};
	};

	export_ struct MUD_GEOM_EXPORT ProcShape
	{
		Symbol m_symbol;
		const Shape* m_shape;
		DrawMode m_draw_mode;
	};

	export_ MUD_GEOM_EXPORT ShapeSize symbol_line_size(const ProcShape& shape);
	export_ MUD_GEOM_EXPORT ShapeSize symbol_triangle_size(const ProcShape& shape);

	export_ MUD_GEOM_EXPORT void symbol_draw_lines(const ProcShape& shape, MeshAdapter& writer);
	export_ MUD_GEOM_EXPORT void symbol_draw_triangles(const ProcShape& shape, MeshAdapter& writer);
}

namespace mud
{
	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const ArcLine& arc);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const ArcLine& arc);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer);

	MUD_GEOM_EXPORT uint16_t circle_vertices(const ProcShape& shape, const vec3& position, vec2 radius, SignedAxis axis, bool lines, MeshAdapter& writer, bool outward_normals = false);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Circle& circle);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Torus& torus);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Torus& torus, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Torus& torus);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshAdapter& writer);
}



#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ struct MUD_GEOM_EXPORT CompoundShape
	{
		vector<ProcShape> m_shapes;
	};

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const CompoundShape& compound);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const CompoundShape& compound, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const CompoundShape& compound);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const CompoundShape& compound, MeshAdapter& writer);
}



namespace mud
{
	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Box& box);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Box& box, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Box& box);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Box& box, MeshAdapter& writer);

	// Cube : Box(cube)
	// Aabb : Box(aabb)
}



namespace mud
{
	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Cylinder& cylinder);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Cylinder& cylinder, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Cylinder& cylinder);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Cylinder& cylinder, MeshAdapter& writer);
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ struct MUD_GEOM_EXPORT DispatchDrawProcShape : public Global<DispatchDrawProcShape>
	{
		DispatchDrawProcShape();

		Dispatch<void, ProcShape&> m_compound_shape;
		Dispatch<ShapeSize, const ProcShape&> m_size_lines;
		Dispatch<ShapeSize, const ProcShape&> m_size_triangles;
		Dispatch<void, const ProcShape&, MeshAdapter&> m_draw_lines;
		Dispatch<void, const ProcShape&, MeshAdapter&> m_draw_triangles;
	};

	template <class T_Shape>
	inline void declare_shape(DispatchDrawProcShape& dispatch)
	{
		dispatch_branch<T_Shape>(dispatch.m_size_lines, +[](T_Shape& shape, const ProcShape& procshape) { return size_shape_lines(procshape, shape); });
		dispatch_branch<T_Shape>(dispatch.m_draw_lines, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { draw_shape_lines(procshape, shape, writer); });

		dispatch_branch<T_Shape>(dispatch.m_size_triangles, +[](T_Shape& shape, const ProcShape& procshape) { return size_shape_triangles(procshape, shape); });
		dispatch_branch<T_Shape>(dispatch.m_draw_triangles, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { draw_shape_triangles(procshape, shape, writer); });
	}

	template <class T_Shape>
	inline void declare_compound_shape(DispatchDrawProcShape& dispatch)
	{
		dispatch_branch<T_Shape>(dispatch.m_size_lines, +[](T_Shape& shape, const ProcShape& procshape) { CompoundShape compound = shape_compound(procshape, shape); return size_shape_lines(procshape, compound); });
		dispatch_branch<T_Shape>(dispatch.m_draw_lines, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { CompoundShape compound = shape_compound(procshape, shape); draw_shape_lines(procshape, compound, writer); });

		dispatch_branch<T_Shape>(dispatch.m_size_triangles, +[](T_Shape& shape, const ProcShape& procshape) { CompoundShape compound = shape_compound(procshape, shape); return size_shape_triangles(procshape, compound); });
		dispatch_branch<T_Shape>(dispatch.m_draw_triangles, +[](T_Shape& shape, const ProcShape& procshape, MeshAdapter& writer) { CompoundShape compound = shape_compound(procshape, shape); draw_shape_triangles(procshape, compound, writer); });
	}
}



namespace mud
{
	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Geometry& geom);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Geometry& geom, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Geometry& geom);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Geometry& geom, MeshAdapter& writer);
}


#include <stl/vector.h>
#include <stl/map.h>

#ifndef MUD_CPP_20
#include <stdint.h>
#endif

namespace mud
{
	export_ class MUD_GEOM_EXPORT IcoSphere
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



namespace mud
{
	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Line& line);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Line& line, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Line& line);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Line& line, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Grid2& grid);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Grid2& grid);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer);
}



namespace mud
{
	MUD_GEOM_EXPORT void quad_vertices(const ProcShape& shape, const vec3& center, const vec3& a, const vec3& b, const vec3& c, const vec3& d, bool fill, MeshAdapter& writer);
	MUD_GEOM_EXPORT void quad_vertices(const ProcShape& shape, const vec3& center, array<vec3> vertices, bool fill, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Quad& quad);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Quad& quad, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Quad& quad);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Quad& quad, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Grid3& grid);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Grid3& grid);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer);
}



namespace mud
{
	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Sphere& sphere);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Sphere& sphere);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer);
}



namespace mud
{
	MUD_GEOM_EXPORT CompoundShape shape_compound(const ProcShape& shape, const Spheroid& spheroid);
}



namespace mud
{
	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Triangle& triangle);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Triangle& triangle, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Triangle& triangle);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Triangle& triangle, MeshAdapter& writer);
}


#include <stl/vector.h>
#include <stl/unordered_map.h>

namespace stl
{
	using namespace mud;
	export_ extern template class vector<Poisson*>;
	export_ extern template class vector<Geometry*>;
	export_ extern template class vector<Geometry>;
	export_ extern template class vector<Circle>;
	export_ extern template class vector<IcoSphere>;
	export_ extern template class vector<ProcShape>;
	export_ extern template class vector<Distribution::Point>;
	export_ extern template class vector<vector<Distribution::Point>>;
	export_ extern template class vector<vector<Distribution::Point>*>;
	export_ extern template class unordered_map<int64_t, int>;
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	inline float distance(const Plane& plane, const vec3& p)
	{
		return dot(plane.m_normal, p) - plane.m_distance;
	}

	inline vec3 project(const Plane& plane, const vec3& p)
	{
		return p - plane.m_normal * distance(plane, p);
	}	// Implementation

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
			return { Zero3, 0.f };
		return { plane.m_normal / l, plane.m_distance / l };
	}

	inline Ray to_ray(const vec3& pos, const vec3& dir, float distance) { return { pos, pos + dir * distance, dir, 1.f / dir }; };
	inline Segment to_segment(const Ray& ray) { return { ray.m_start, ray.m_end }; }

	inline Plane6::Plane6() {}
	inline Plane6::Plane6(Plane right, Plane left, Plane up, Plane down, Plane near, Plane far) : m_right(right), m_left(left), m_up(up), m_down(down), m_near(near), m_far(far) {}

	inline Point8::Point8() {}
	inline Point8::Point8(vec3 a, vec3 b, vec3 c, vec3 d, vec3 e, vec3 f, vec3 g, vec3 h) : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e), m_f(f), m_g(g), m_h(h) {}
}



#ifndef MUD_CPP_20
#include <cstring>
#endif

namespace mud
{
	inline size_t vertex_attribute_size(VertexAttribute::Enum attribute)
	{
		if(attribute == VertexAttribute::Position)			return sizeof(vec3);
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

	inline MeshAdapter::Array::Array() : m_pointer(nullptr), m_count(0) {}
	inline MeshAdapter::Array::Array(void* pointer, uint32_t count) : m_pointer(pointer), m_count(count) {}

	inline uint32_t MeshAdapter::Array::size() { return m_count; }
	inline void* MeshAdapter::Array::data() const { return m_pointer; }

	inline MeshAdapter::MeshAdapter() {}
	inline MeshAdapter::MeshAdapter(uint32_t vertex_format, void* vertices, uint32_t num_vertices, void* indices, uint32_t num_indices, bool index32)
		: m_vertices(vertices, num_vertices), m_indices(indices, num_indices), m_vertex_format(vertex_format)
		, m_vertex_stride(vertex_size(vertex_format)), m_index_stride(index32 ? sizeof(uint32_t) : sizeof(uint16_t)), m_index(indices)
	{
		if((vertex_format & VertexAttribute::Position) != 0)
			m_start.m_position	= (vec3*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Position));
		if((vertex_format & VertexAttribute::Normal) != 0)
			m_start.m_normal	= (vec3*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Normal));
		if((vertex_format & VertexAttribute::Colour) != 0)
			m_start.m_colour	= (uint32_t*)	((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Colour));
		if((vertex_format & VertexAttribute::Tangent) != 0)
			m_start.m_tangent	= (vec4*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Tangent));
		if((vertex_format & VertexAttribute::Bitangent) != 0)
			m_start.m_bitangent	= (vec3*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Bitangent));
		if((vertex_format & VertexAttribute::TexCoord0) != 0)
			m_start.m_uv0		= (vec2*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::TexCoord0));
		if((vertex_format & VertexAttribute::TexCoord1) != 0)
			m_start.m_uv1		= (vec2*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::TexCoord1));
		if((vertex_format & VertexAttribute::Joints) != 0)
			m_start.m_joints	= (uint32_t*)	((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Joints));
		if((vertex_format & VertexAttribute::Weights) != 0)
			m_start.m_weights	= (vec4*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Weights));
			
		if((vertex_format & VertexAttribute::QPosition) != 0)
			m_start.m_qposition	= (half3*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QPosition));
		if((vertex_format & VertexAttribute::QNormal) != 0)
			m_start.m_qnormal	= (uint32_t*)	((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QNormal));
		if((vertex_format & VertexAttribute::QTangent) != 0)
			m_start.m_qtangent	= (uint32_t*)	((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QTangent));
		if((vertex_format & VertexAttribute::QTexCoord0) != 0)
			m_start.m_quv0		= (half2*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QTexCoord0));
		if((vertex_format & VertexAttribute::QTexCoord1) != 0)
			m_start.m_quv1		= (half2*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QTexCoord1));

		m_cursor = m_start;
	}

	inline void MeshAdapter::rewind() { m_cursor = m_start; m_vertex = 0; m_offset = 0; m_index = m_indices.m_pointer; }
	inline void MeshAdapter::next() { m_offset = m_vertex; }

	inline MeshAdapter MeshAdapter::read() const { MeshAdapter reader = *this; reader.rewind(); return reader; }

	template <class T>
	inline void MeshAdapter::next(T*& pointer) { pointer = (T*)((char*)pointer + m_vertex_stride); }

	inline MeshAdapter& MeshAdapter::position(const vec3& p) { m_aabb.add(p); *m_cursor.m_position = p; next(m_cursor.m_position); ++m_vertex; return *this; }
	inline MeshAdapter& MeshAdapter::normal(const vec3& n) { if(m_cursor.m_normal) { *m_cursor.m_normal = n; next(m_cursor.m_normal); } return *this; }
	inline MeshAdapter& MeshAdapter::colour(const Colour& c) { if(m_cursor.m_colour) { *m_cursor.m_colour = to_abgr(c); next(m_cursor.m_colour); } return *this; }
	inline MeshAdapter& MeshAdapter::tangent(const vec4& t) { if(m_cursor.m_tangent) { *m_cursor.m_tangent = t; next(m_cursor.m_tangent); } return *this; }
	inline MeshAdapter& MeshAdapter::bitangent(const vec4& b) { if(m_cursor.m_bitangent) { *m_cursor.m_bitangent = vec3(b); next(m_cursor.m_bitangent); } return *this; }
	inline MeshAdapter& MeshAdapter::uv0(const vec2& uv) { if(m_cursor.m_uv0) { m_uv0_rect.add(uv); *m_cursor.m_uv0 = uv; next(m_cursor.m_uv0); } return *this; }
	inline MeshAdapter& MeshAdapter::uv1(const vec2& uv) { if(m_cursor.m_uv1) { m_uv1_rect.add(uv); *m_cursor.m_uv1 = uv; next(m_cursor.m_uv1); } return *this; }
	inline MeshAdapter& MeshAdapter::joints(const uint32_t& j) { if(m_cursor.m_joints) { *m_cursor.m_joints = j; next(m_cursor.m_joints); } return *this; }
	inline MeshAdapter& MeshAdapter::weights(const vec4& w) { if(m_cursor.m_weights) { *m_cursor.m_weights = w; next(m_cursor.m_weights); } return *this; }

	inline vec3 MeshAdapter::position() { vec3 value = *m_cursor.m_position; next(m_cursor.m_position); return value; }
	inline vec3 MeshAdapter::normal() { if(!m_cursor.m_normal) return Zero3; vec3 value = *m_cursor.m_normal; next(m_cursor.m_normal); return value; }
	inline Colour MeshAdapter::colour() { if(!m_cursor.m_colour) return Colour::None; Colour value = from_abgr(*m_cursor.m_colour); next(m_cursor.m_colour); return value; }
	inline vec4 MeshAdapter::tangent() { if(!m_cursor.m_tangent) return vec4(Zero3, 1.f); vec4 value = *m_cursor.m_tangent; next(m_cursor.m_tangent); return value; }
	inline vec2 MeshAdapter::uv0() { if(!m_cursor.m_uv0) return Zero2; vec2 value = *m_cursor.m_uv0; next(m_cursor.m_uv0); return value; }
	inline vec2 MeshAdapter::uv1() { if(!m_cursor.m_uv1) return Zero2; vec2 value = *m_cursor.m_uv1; next(m_cursor.m_uv1); return value; }
	inline uint16_t MeshAdapter::index() { uint16_t value = *(uint16_t*)m_index; m_index = ((char*)m_index + m_index_stride); return value; }
	inline uint32_t MeshAdapter::index32() { uint32_t value = *(uint32_t*)m_index; m_index = ((char*)m_index + m_index_stride); return value; }

	inline void MeshAdapter::index(uint32_t i) { uint32_t index = i + m_offset; memcpy(m_index, &index, m_index_stride); m_index = ((char*)m_index + m_index_stride); }
	inline void MeshAdapter::line(uint32_t a, uint32_t b) { index(a); index(b); }
	inline void MeshAdapter::tri(uint32_t a, uint32_t b, uint32_t c) { index(a); index(b); index(c); }
	inline void MeshAdapter::quad(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { tri(a, b, c); tri(c, d, a); }
}
