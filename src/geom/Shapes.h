//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Axis.h>
#endif
#include <geom/Forward.h>
#include <geom/Shape.h>

namespace mud
{
	export_ struct refl_ MUD_GEOM_EXPORT Line final : public Shape
	{
	public:
		constr_ Line();
		constr_ Line(const vec3& start, const vec3& end);

		attr_ vec3 m_start = Zero3;
		attr_ vec3 m_end = Unit3;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Rect final : public Shape
	{
	public:
		constr_ Rect();
		constr_ Rect(const vec2& position, const vec2& size);
		constr_ Rect(float x, float y, float w, float h);

		attr_ vec2 m_position = Zero2;
		attr_ vec2 m_size = Unit2;

		virtual object_ptr<Shape> clone() const;
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

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Grid2 final : public Shape
	{
	public:
		constr_ Grid2();
		constr_ Grid2(const vec2& size, const vec2& space = Unit2);

		attr_ vec2 m_size = vec2{ 1.f };
		attr_ vec2 m_space = vec2{ 0.1f };

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Triangle final : public Shape
	{
	public:
		constr_ Triangle();
		constr_ Triangle(const vec2& size);

		attr_ vec2 m_size = Unit2;

		virtual object_ptr<Shape> clone() const;
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

		virtual object_ptr<Shape> clone() const;
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

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Ring final : public Shape
	{
	public:
		constr_ Ring();
		constr_ Ring(float radius, float min, float max);

		attr_ float m_radius = 1.f;
		attr_ float m_min = 0.f;
		attr_ float m_max = 1.f;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Ellipsis final : public Shape
	{
	public:
		constr_ Ellipsis();
		constr_ Ellipsis(vec2 radius, Axis axis = Axis::Y);

		attr_ vec2 m_radius = Unit2;
		attr_ Axis m_axis = Axis::Y;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Arc final : public Shape
	{
	public:
		constr_ Arc();
		constr_ Arc(float radius, float start, float end);

		attr_ float m_radius = 1.f;
		attr_ float m_start = 0.f;
		attr_ float m_end = 1.f;

		virtual object_ptr<Shape> clone() const;
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

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Cylinder final : public Shape
	{
	public:
		constr_ Cylinder();
		constr_ Cylinder(float radius, float height, Axis axis = Axis::X);

		attr_ float m_radius = 1.f;
		attr_ float m_height = 2.f;
		attr_ Axis m_axis = Axis::X;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Capsule final : public Shape
	{
	public:
		constr_ Capsule();
		constr_ Capsule(float radius, float height, Axis axis = Axis::X);

		attr_ float m_radius = 1.f;
		attr_ float m_height = 2.f;
		attr_ Axis m_axis = Axis::X;

		virtual object_ptr<Shape> clone() const;
	};


	export_ struct refl_ MUD_GEOM_EXPORT Cube : public Shape
	{
	public:
		constr_ Cube();
		constr_ Cube(const vec3& extents);
		constr_ Cube(const vec3& center, const vec3& extents);
		Cube(float side);

		attr_ vec3 m_extents = vec3{ 0.5f };

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Sphere final : public Shape
	{
	public:
		constr_ Sphere();
		constr_ Sphere(float radius);
		constr_ Sphere(const vec3& center, float radius);

		attr_ float m_radius = 1.f;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT SphereRing final : public Shape
	{
	public:
		constr_ SphereRing();
		constr_ SphereRing(float radius, float min, float max);

		attr_ float m_radius = 1.f;
		attr_ float m_min = -1.f;
		attr_ float m_max = 1.f;

		virtual object_ptr<Shape> clone() const;
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

		virtual object_ptr<Shape> clone() const;
	};
}
