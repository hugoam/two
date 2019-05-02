//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <math/Vec.h>
#include <math/Grid.h>
#endif
#include <geom/Forward.h>
#include <geom/Shapes.h>

namespace two
{
	export_ class refl_ TWO_GEOM_EXPORT Distribution
	{
	public:
		struct Point
		{
			vec3 position;
			float radius;
			size_t visits = 0;
		};

		//meth_ virtual vector<Circle> distribute(float radius, const vec3& offset) = 0;
		//meth_ virtual bool addPoint(float radius, vec3& point) = 0;
	};

	export_ class refl_ TWO_GEOM_EXPORT Poisson : public Distribution
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
		vector2d<vector<Point>> m_grid;
	};

	TWO_GEOM_EXPORT func_ vector<vec3> distribute_poisson(vec2 size, float radius);
}
