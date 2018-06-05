//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Axis.h>
#endif
#include <geom/Generated/Forward.h>
#include <geom/Shape.h>

namespace mud
{
	export_ struct _refl_ MUD_GEOM_EXPORT Line : public Shape
	{
	public:
		_constr_ Line();
		_constr_ Line(const vec3& start, const vec3& end);

		_attr_ _mut_ vec3 m_start = Zero3;
		_attr_ _mut_ vec3 m_end = Unit3;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Rect : public Shape
	{
	public:
		_constr_ Rect();
		_constr_ Rect(const vec2& position, const vec2& size);
		_constr_ Rect(float x, float y, float w, float h);

		_attr_ _mut_ vec2 m_position = Zero2;
		_attr_ _mut_ vec2 m_size = Unit2;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Quad : public Shape
	{
	public:
		_constr_ Quad();
		_constr_ Quad(const vec3& a, const vec3& b, const vec3& c, const vec3& d);

		Quad(const vec2& size, const vec3& x = X3, const vec3& y = Y3);
		Quad(float size, const vec3& x = X3, const vec3& y = Y3);
		Quad(const Rect& rect);

		/*_attr_ _mut_*/ vec3 m_vertices[4];

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Grid2 : public Shape
	{
	public:
		_constr_ Grid2();
		_constr_ Grid2(const vec2& size, const vec2& space = Unit2);

		_attr_ _mut_ vec2 m_size = vec2{ 1.f };
		_attr_ _mut_ vec2 m_space = vec2{ 0.1f };

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Triangle : public Shape
	{
	public:
		_constr_ Triangle();
		_constr_ Triangle(const vec2& size);

		_attr_ _mut_ vec2 m_size = Unit2;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Circle : public Shape
	{
	public:
		_constr_ Circle();
		_constr_ Circle(float radius, Axis axis = Axis::Y);
		_constr_ Circle(const vec3& center, float radius, Axis axis = Axis::Y);

		bool operator==(const Circle& other) const { return m_radius == other.m_radius && m_axis == other.m_axis && m_center == other.m_center; }

		_attr_ _mut_ float m_radius = 1.f;
		_attr_ _mut_ Axis m_axis = Axis::X;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Torus : public Shape
	{
	public:
		_constr_ Torus();
		_constr_ Torus(float radius, float solid_radius, Axis axis = Axis::Y);
		_constr_ Torus(const vec3& center, float radius, float solid_radius, Axis axis = Axis::Y);

		bool operator==(const Torus& other) const { return m_radius == other.m_radius && m_solid_radius == other.m_solid_radius && m_axis == other.m_axis && m_center == other.m_center; }

		_attr_ _mut_ float m_radius = 1.f;
		_attr_ _mut_ float m_solid_radius = 1.f;
		_attr_ _mut_ Axis m_axis = Axis::X;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Ring : public Shape
	{
	public:
		_constr_ Ring();
		_constr_ Ring(float radius, float min, float max);

		_attr_ _mut_ float m_radius = 1.f;
		_attr_ _mut_ float m_min = 0.f;
		_attr_ _mut_ float m_max = 1.f;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Ellipsis : public Shape
	{
	public:
		_constr_ Ellipsis();
		_constr_ Ellipsis(vec2 radius, Axis axis = Axis::Y);

		_attr_ _mut_ vec2 m_radius = Unit2;
		_attr_ _mut_ Axis m_axis = Axis::Y;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Arc : public Shape
	{
	public:
		_constr_ Arc();
		_constr_ Arc(float radius, float start, float end);

		_attr_ _mut_ float m_radius = 1.f;
		_attr_ _mut_ float m_start = 0.f;
		_attr_ _mut_ float m_end = 1.f;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Cylinder : public Shape
	{
	public:
		_constr_ Cylinder();
		_constr_ Cylinder(float radius, float height, Axis axis = Axis::X);

		_attr_ _mut_ float m_radius = 1.f;
		_attr_ _mut_ float m_height = 2.f;
		_attr_ _mut_ Axis m_axis = Axis::X;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Capsule : public Shape
	{
	public:
		_constr_ Capsule();
		_constr_ Capsule(float radius, float height, Axis axis = Axis::X);

		_attr_ _mut_ float m_radius = 1.f;
		_attr_ _mut_ float m_height = 2.f;
		_attr_ _mut_ Axis m_axis = Axis::X;

		virtual object_ptr<Shape> clone() const;
	};


	export_ struct _refl_ MUD_GEOM_EXPORT Cube : public Shape
	{
	public:
		_constr_ Cube();
		_constr_ Cube(const vec3& extents);
		_constr_ Cube(const vec3& center, const vec3& extents);
		_constr_ Cube(float side);

		_attr_ _mut_ vec3 m_extents = vec3{ 0.5f };

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Sphere : public Shape
	{
	public:
		_constr_ Sphere();
		_constr_ Sphere(float radius);
		_constr_ Sphere(const vec3& center, float radius);

		_attr_ _mut_ float m_radius = 1.f;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT SphereRing : public Shape
	{
	public:
		_constr_ SphereRing();
		_constr_ SphereRing(float radius, float min, float max);

		_attr_ _mut_ float m_radius = 1.f;
		_attr_ _mut_ float m_min = -1.f;
		_attr_ _mut_ float m_max = 1.f;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_GEOM_EXPORT Spheroid : public Shape
	{
	public:
		_constr_ Spheroid();
		_constr_ Spheroid(float radius);

		_attr_ _mut_ float m_radius = 1.f;

		Circle m_circleX;
		Circle m_circleY;
		Circle m_circleZ;

		virtual object_ptr<Shape> clone() const;
	};
}
