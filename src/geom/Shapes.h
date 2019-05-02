//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <math/Axis.h>
#include <math/Math.h>
#endif
#include <geom/Forward.h>
#include <geom/Shape.h>

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
