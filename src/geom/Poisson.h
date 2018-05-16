//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <math/Grid.h>
#include <geom/Generated/Forward.h>
#include <geom/Shapes.h>

namespace mud
{
	class _refl_ MUD_MATH_EXPORT Distribution
	{
	public:
		class Point
		{
		public:
			Point(const vec3& p, float r) : position(p), radius(r), visits(0) {}

			vec3 position;
			float radius;
			size_t visits;
		};

		//_meth_ virtual std::vector<Circle> distribute(float radius, const vec3& offset) = 0;
		//_meth_ virtual bool addPoint(float radius, vec3& point) = 0;
	};

	class _refl_ MUD_MATH_EXPORT Poisson : public Distribution
	{
	public:
		_constr_ Poisson(vec2 size, float maxRadius);

		vec2 m_size;
		bool m_overlap = false;
		bool m_start_from_center = false;
		//bool m_fill_closer_first;

		void uniform(float radius);

		_meth_ std::vector<vec3> distribute(float radius);
		_meth_ std::vector<Circle> distribute_circles(float radius);
		_meth_ bool addPoint(float radius, vec3& point);

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

		std::vector<Point> m_points;

		std::vector<Point> m_unprocessed;
		Grid<std::vector<Point>> m_grid;
	};

	MUD_MATH_EXPORT _func_ std::vector<vec3> distribute_poisson(vec2 size, float radius);
}
