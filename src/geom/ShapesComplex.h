//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#endif
#include <geom/Forward.h>
#include <geom/Shape.h>

#ifndef MUD_CPP_20
#include <vector>
#include <array>
#endif

namespace mud
{
	export_ struct refl_ MUD_GEOM_EXPORT Polygon final : public Shape
	{
	public:
		constr_ Polygon();
		constr_ Polygon(std::vector<vec3> vertices);

		std::vector<vec3> m_vertices;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Box final : public Shape
	{
	public:
		constr_ Box();
		Box(array<vec3> vertices);

		Box(const Cube& cube);

		std::array<vec3, 8> m_vertices;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Points final : public Shape
	{
	public:
		constr_ Points();
		constr_ Points(const std::vector<vec3>& points);

		attr_ std::vector<vec3> m_points;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT Grid3 final : public Shape
	{
	public:
		constr_ Grid3();
		constr_ Grid3(const uvec2& size, const std::vector<vec3>& points = {});

		attr_ uvec2 m_size;
		attr_ std::vector<vec3> m_points;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT ConvexHull final : public Shape
	{
	public:
		constr_ ConvexHull();
		constr_ ConvexHull(const std::vector<vec3>& vertices);

		attr_ std::vector<vec3> m_vertices;

		virtual object_ptr<Shape> clone() const;
	};
}
