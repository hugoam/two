//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
import mud.obj;
import mud.math;
module mud.geom;
#else
#include <obj/Util/DispatchDecl.h>
#include <math/VecOps.h>
#include <math/Math.h>
#include <math/Random.h>
#include <geom/Generated/Types.h>
#include <geom/Shape.h>
#include <geom/ShapeDistrib.h>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Aabb.h>
#include <geom/Symbol.h>
#include <geom/Geom.h>
#endif

namespace mud
{
	Line::Line() : Shape(type<Line>()) {}
	Line::Line(const vec3& start, const vec3& end) : Shape(type<Line>()), m_start(start), m_end(end) {}
	object_ptr<Shape> Line::clone() const { return make_object<Line>(*this); }

	Rect::Rect() : Shape(type<Rect>()) {}
	Rect::Rect(const vec2& pos, const vec2& size) : Shape(type<Rect>()), m_position(pos), m_size(size) {}
	Rect::Rect(float x, float y, float w, float h) : Shape(type<Rect>()), m_position(x, y), m_size(w, h) {}
	object_ptr<Shape> Rect::clone() const { return make_object<Rect>(*this); }

	Quad::Quad() : Shape(type<Quad>()) {}
	Quad::Quad(const vec3& a, const vec3& b, const vec3& c, const vec3& d) : Shape(type<Quad>()), m_vertices{ a, b, c, d } {}
	object_ptr<Shape> Quad::clone() const { return make_object<Quad>(*this); }

	Polygon::Polygon() : Shape(type<Polygon>()) {}
	Polygon::Polygon(std::vector<vec3> vertices) : Shape(type<Polygon>()), m_vertices(vertices) {}
	object_ptr<Shape> Polygon::clone() const { return make_object<Polygon>(*this); }

	Grid2::Grid2() : Shape(type<Grid2>()) {}
	Grid2::Grid2(const vec2& size, const vec2& space) : Shape(type<Grid2>()), m_size(size), m_space(space) {}
	object_ptr<Shape> Grid2::clone() const { return make_object<Grid2>(*this); }

	Triangle::Triangle() : Shape(type<Triangle>()) {}
	Triangle::Triangle(const vec2& size) : Shape(type<Triangle>()), m_size(size) {}
	object_ptr<Shape> Triangle::clone() const { return make_object<Triangle>(*this); }

	Circle::Circle() : Shape(type<Circle>()) {}
	Circle::Circle(float radius, Axis axis) : Shape(type<Circle>()), m_radius(radius), m_axis(axis) {}
	Circle::Circle(const vec3& center, float radius, Axis axis) : Shape(type<Circle>(), center), m_radius(radius), m_axis(axis) {}
	object_ptr<Shape> Circle::clone() const { return make_object<Circle>(*this); }

	Torus::Torus() : Shape(type<Torus>()) {}
	Torus::Torus(float radius, float solid_radius, Axis axis) : Shape(type<Torus>()), m_radius(radius), m_solid_radius(solid_radius), m_axis(axis) {}
	Torus::Torus(const vec3& center, float radius, float solid_radius, Axis axis) : Shape(type<Torus>(), center), m_radius(radius), m_solid_radius(solid_radius), m_axis(axis) {}
	object_ptr<Shape> Torus::clone() const { return make_object<Torus>(*this); }

	Ring::Ring() : Shape(type<Ring>()) {}
	Ring::Ring(float radius, float min, float max) : Shape(type<Ring>()), m_radius(radius), m_min(min), m_max(max) {}
	object_ptr<Shape> Ring::clone() const { return make_object<Ring>(*this); }

	Ellipsis::Ellipsis() : Shape(type<Ellipsis>()) {}
	Ellipsis::Ellipsis(vec2 radius, Axis axis) : Shape(type<Ellipsis>()), m_radius(radius), m_axis(axis) {}
	object_ptr<Shape> Ellipsis::clone() const { return make_object<Ellipsis>(*this); }

	Arc::Arc() : Shape(type<Arc>()) {}
	Arc::Arc(float radius, float start, float end) : Shape(type<Arc>()), m_radius(radius), m_start(start), m_end(end) {}
	object_ptr<Shape> Arc::clone() const { return make_object<Arc>(*this); }

	Cylinder::Cylinder() : Shape(type<Cylinder>()) {}
	Cylinder::Cylinder(float radius, float height, Axis axis) : Shape(type<Cylinder>()), m_radius(radius), m_height(height), m_axis(axis) {}
	object_ptr<Shape> Cylinder::clone() const { return make_object<Cylinder>(*this); }

	Capsule::Capsule() : Shape(type<Capsule>()) {}
	Capsule::Capsule(float radius, float height, Axis axis) : Shape(type<Capsule>()), m_radius(radius), m_height(height), m_axis(axis) {}
	object_ptr<Shape> Capsule::clone() const { return make_object<Capsule>(*this); }

	Cube::Cube() : Shape(type<Cube>()) {}
	Cube::Cube(const vec3& extents) : Shape(type<Cube>()), m_extents(extents) {}
	Cube::Cube(const vec3& center, const vec3& extents) : Shape(type<Cube>(), center), m_extents(extents) {}
	Cube::Cube(float side) : Shape(type<Cube>()), m_extents(side, side, side) {}
	object_ptr<Shape> Cube::clone() const { return make_object<Cube>(*this); }

	Box::Box() : Shape(type<Box>()), m_vertices() {}
	object_ptr<Shape> Box::clone() const { return make_object<Box>(*this); }

	Sphere::Sphere() : Shape(type<Sphere>()) {}
	Sphere::Sphere(float radius) : Shape(type<Sphere>()), m_radius(radius) {}
	Sphere::Sphere(const vec3& center, float radius) : Shape(type<Sphere>(), center), m_radius(radius) {}
	object_ptr<Shape> Sphere::clone() const { return make_object<Sphere>(*this); }

	SphereRing::SphereRing() : Shape(type<SphereRing>()) {}
	SphereRing::SphereRing(float radius, float min, float max) : Shape(type<SphereRing>()), m_radius(radius), m_min(min), m_max(max) {}
	object_ptr<Shape> SphereRing::clone() const { return make_object<SphereRing>(*this); }

	Spheroid::Spheroid() : Shape(type<Spheroid>()) {}
	Spheroid::Spheroid(float radius) : Shape(type<Spheroid>()), m_radius(radius), m_circleX(radius, Axis::X), m_circleY(radius, Axis::Y), m_circleZ(radius, Axis::Z) {}
	object_ptr<Shape> Spheroid::clone() const { return make_object<Spheroid>(*this); }

	Points::Points() : Shape(type<Points>()) {}
	Points::Points(const std::vector<vec3>& points) : Shape(type<Points>()), m_points(points) {}
	object_ptr<Shape> Points::clone() const { return make_object<Points>(*this); }

	ConvexHull::ConvexHull() : Shape(type<ConvexHull>()) {}
	ConvexHull::ConvexHull(const std::vector<vec3>& vertices) : Shape(type<ConvexHull>()), m_vertices(vertices) {}
	object_ptr<Shape> ConvexHull::clone() const { return make_object<ConvexHull>(*this); }

	Aabb::Aabb() : Cube(Zero3), m_null(true) {}
	Aabb::Aabb(const vec3& center, const vec3& extents) : Cube(center, extents), m_null(false) {}
	object_ptr<Shape> Aabb::clone() const { return make_object<Aabb>(*this); }

	bool Aabb::intersects(const Aabb& other) const
	{
		return !(any(less(m_center + m_extents, other.m_center - other.m_extents))
			  || any(greater(m_center - m_extents, other.m_center + other.m_extents)));
	}

	void Aabb::merge(const vec3& point)
	{
		if(m_null)
		{
			m_center = point;
			m_null = false;
			return;
		}

		vec3 bmax = max(m_center + m_extents, point);
		vec3 bmin = min(m_center - m_extents, point);

		m_center = (bmax + bmin) * 0.5f;
		m_extents = (bmax - bmin) * 0.5f;
	}

	void Aabb::mergeSafe(const Aabb& other)
	{
		if(other.m_null) return;
		if(m_null) *this = other; else this->merge(other);
		m_null = false;
	}

	void Aabb::merge(const Aabb& other)
	{
		vec3 max_bounds = max(m_center + m_extents, other.m_center + other.m_extents);
		vec3 min_bounds = min(m_center - m_extents, other.m_center - other.m_extents);

		m_center = (max_bounds + min_bounds) * 0.5f;
		m_extents = (max_bounds - min_bounds) * 0.5f;
	}

	bool Aabb::cull(const vec3& point) const
	{
		if(m_null) return false;

		vec3 max_bounds(m_center + m_extents);
		vec3 min_bounds(m_center - m_extents);

		if(any(greater(point, max_bounds)))
			return true;
		if(any(less(point, min_bounds)))
			return true;

		return false;
	}

	bool Aabb::cull(array<vec3> points) const
	{
		for(const vec3& point : points)
			if(cull(point))
				return true;
		return false;
	}

	Aabb face_aabb(const vec3* vertices)
	{
		vec3 bmin = min(vertices[0], min(vertices[1], vertices[2]));
		vec3 bmax = max(vertices[0], max(vertices[1], vertices[2]));
		vec3 extents = (bmax - bmin) * 0.5f;
		return Aabb(bmin + extents, extents);
	}

	Aabb face_aabb(const Face3& face)
	{
		return face_aabb(face.m_vertices);
	}

	Quad::Quad(const vec2& size, const vec3& x, const vec3& y)
		: Shape(type<Quad>())
	{
		m_vertices[0] = (x * size.x + y * size.y) / 2.f;
		m_vertices[1] = (x * size.x - y * size.y) / 2.f;
		m_vertices[2] = -m_vertices[0];
		m_vertices[3] = -m_vertices[1];
	}

	Quad::Quad(float size, const vec3& x, const vec3& y)
		: Quad({ size, size }, x, y)
	{}

	Quad::Quad(const Rect& rect)
		: Quad({ rect.m_size.x, rect.m_size.y }, X3, Z3)
	{}

	Box::Box(array<vec3> vertices)
		: Shape(type<Box>())
	{
		array<vec3> dest = { m_vertices.data(), 8 };
		vertices.copy(dest);
	}

	Box::Box(const Cube& cube)
		: Shape(type<Box>())
	{
		vec3 min = cube.m_center - cube.m_extents;
		vec3 max = cube.m_center + cube.m_extents;

		m_vertices[0] = { min.x, min.y, max.z };
		m_vertices[1] = { max.x, min.y, max.z };
		m_vertices[2] = { max.x, max.y, max.z };
		m_vertices[3] = { min.x, max.y, max.z };
		m_vertices[4] = { max.x, min.y, min.z };
		m_vertices[5] = { min.x, min.y, min.z };
		m_vertices[6] = { min.x, max.y, min.z };
		m_vertices[7] = { max.x, max.y, min.z };
	}

	Symbol::Symbol(Colour outline, Colour fill, bool overlay, bool double_sided, SymbolDetail detail)
		: m_outline(outline)
		, m_fill(fill)
		, m_overlay(overlay)
		, m_double_sided(double_sided)
		, m_detail(detail)
	{}

	Symbol::Symbol(cstring image, float alpha)
		: Symbol(Colour::None, Colour::White)
	{
		m_image = image;
		m_fill.m_a = alpha;
	}

	Symbol::Symbol(const Image256& image, float alpha)
		: Symbol(Colour::None, Colour::White)
	{
		m_image256 = &const_cast<Image256&>(image);
		m_fill.m_a = alpha;
	}

	bool Symbol::operator==(const Symbol& other) const
	{
		UNUSED(other);
		return true;
	}

	inline vec3 distribute_sphere(float radius, float h = 2.f, float maxh = 1.f)
	{
		const float rand0 = random_scalar(0.f, 1.f) * h - maxh;
		const float rand1 = random_scalar(0.f, 1.f) * M_PI * 2.f;
		const float sqrtf1 = sqrt(1.0f - rand0 * rand0);

		return vec3{ sqrtf1 * cos(rand1), sqrtf1 * sin(rand1), rand0 } * radius;
	}

	inline vec3 distribute_spherical(float radius, float min, float max)
	{
		const float maxh = max * 2.0f - 1.0f;
		const float minh = min * 2.0f - 1.0f;
		return distribute_sphere(radius, maxh - minh, maxh);
	}

	inline vec3 distribute_circle(float radius)
	{
		const float angle = random_scalar(0.f, 1.f) * M_PI * 2.f;
		return vec3{ cos(angle), 0.0f, sin(angle) } * radius;
	}

	inline vec3 distribute_ring(float radius, float min = 0.f, float max = 1.f)
	{
		const float size = random_scalar(min, max);
		vec3 pos = distribute_circle(radius);
		return pos * size;
	}

	inline vec3 distribute_rect(float width = 1.f, float height = 1.f)
	{
		const float x = random_scalar(-1.f, 1.f);
		const float y = random_scalar(-1.f, 1.f);
		return { x * width, 0.f, y * height };
	}

	inline vec3 distribute_points(const std::vector<vec3>& points)
	{
		size_t index = random_integer(size_t(0U), points.size() - 1U);
		return points[index];
	}

	RandomShapePoint::RandomShapePoint()
	{
		dispatch_branch<Sphere>(*this, [](const Sphere& sphere) { return distribute_sphere(sphere.m_radius); });
		dispatch_branch<SphereRing>(*this, [](const SphereRing& sphere) { return distribute_spherical(sphere.m_radius, sphere.m_min, sphere.m_max); });
		dispatch_branch<Circle>(*this, [](const Circle& circle) { return distribute_circle(circle.m_radius); });
		dispatch_branch<Ring>(*this, [](const Ring& ring) { return distribute_ring(ring.m_radius, ring.m_min, ring.m_max); });
		dispatch_branch<Rect>(*this, [](const Rect& rect) { return distribute_rect(rect.m_size.x, rect.m_size.y); });
		dispatch_branch<Points>(*this, [](const Points& points) { return distribute_points(points.m_points); });
	}

	std::vector<vec3> distribute_shape(const Shape& shape, size_t count)
	{
		if(!RandomShapePoint::me().check(Ref(&shape)))
			return std::vector<vec3>(count, Zero3);

		std::vector<vec3> points(count);
		for(size_t i = 0; i < count; ++i)
			points[i] = RandomShapePoint::me().dispatch(Ref(&shape));
		return points;
	}
}
