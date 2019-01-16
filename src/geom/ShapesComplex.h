//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <infra/Array.h>
#endif
#include <geom/Forward.h>
#include <geom/Shape.h>

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
