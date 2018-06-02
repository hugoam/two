//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <geom/Generated/Forward.h>
#include <geom/Shape.h>

#ifndef MUD_CPP_20
#include <vector>
#include <array>
#endif

namespace mud
{
	export_ struct _refl_ MUD_MATH_EXPORT Polygon : public Shape
	{
	public:
		_constr_ Polygon();
		_constr_ Polygon(std::vector<vec3> vertices);

		std::vector<vec3> m_vertices;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_MATH_EXPORT Box : public Shape
	{
	public:
		_constr_ Box();
		Box(array<vec3> vertices);

		Box(const Cube& cube);

		std::array<vec3, 8> m_vertices;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_MATH_EXPORT Points : public Shape
	{
	public:
		_constr_ Points();
		_constr_ Points(const std::vector<vec3>& points);

		_attr_ _mut_ std::vector<vec3> m_points;

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct _refl_ MUD_MATH_EXPORT ConvexHull : public Shape
	{
	public:
		_constr_ ConvexHull();
		_constr_ ConvexHull(const std::vector<vec3>& vertices);

		_attr_ _mut_ std::vector<vec3> m_vertices;

		virtual object_ptr<Shape> clone() const;
	};
}
