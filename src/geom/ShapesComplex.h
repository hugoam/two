//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>
#include <geom/Shape.h>

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
