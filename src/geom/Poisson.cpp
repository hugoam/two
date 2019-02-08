//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <math/Axis.h>
#include <math/Math.h>
#include <math/Vec.hpp>
#include <math/Random.h>
#include <geom/Poisson.h>
#include <geom/Shapes.h>
#endif

namespace mud
{
	Poisson::Poisson(vec2 size, float maxRadius)
		: Distribution()
		, m_size(size)
		, m_cellSize(maxRadius / sqrt(2.f))
		, m_invCellSize(1.f / m_cellSize)
		, m_grid(size_t(ceil(m_size * m_invCellSize).x), size_t(ceil(m_size * m_invCellSize).y), 1)
	{}

	void Poisson::pushPoint(const Point& point)
	{
		size_t index = gridIndex(point);
		m_points.push_back(point);
		m_unprocessed.push_back(point);
		m_grid[index].push_back(point);
	}

	Distribution::Point Poisson::randomPointAround(const Point& point, float radius)
	{
		float distance = point.radius + radius;

		float rr = m_overlap ? random_scalar(point.radius, distance)
							 : random_scalar(distance, distance * 2.f);
		float rt = random_scalar(0.f, float(2.f * c_pi));

		float x = rr * sin(rt) + point.position.x;
		float y = rr * cos(rt) + point.position.y;

		return { vec3(x, y, 0.f), radius };
	}

	bool Poisson::checkSpace(const Point& point)
	{
		size_t index = gridIndex(point);
		
		auto neighbours = m_grid.neighbours(index, 2);
		neighbours.push_back(&m_grid.at(index));

		for(vector<Point>* cell : neighbours)
			for(Point& other : *cell)
			{
				float dist = m_overlap ? point.radius : point.radius + other.radius;
				if(distance(point.position, other.position) <= dist)
					return false;
			}
		
		return true;
	}

	bool Poisson::checkInside(const Point& point)
	{
		return (point.position.x < m_size.x && point.position.x  >= 0.f
			 && point.position.y < m_size.y && point.position.y >= 0.f);
	}

	size_t Poisson::gridIndex(const Point& point)
	{
		uvec3 index = uvec3(floor(point.position * m_invCellSize));
		return m_grid.index_at(index.x, index.y, 0);
	}

	bool Poisson::insertPoint(float radius)
	{
		if(m_points.empty())
		{
			if(!m_start_from_center)
				pushPoint({ vec3(random_scalar(0.f, m_size.x), random_scalar(0.f, m_size.y), 0.f), radius });
			else
				pushPoint({ vec3(0.5f, 0.5f, 0.f), radius });
			return true;
		}

		while(!m_unprocessed.empty())
		{
			uint index = random_integer(0U, uint(m_unprocessed.size()) - 1);
			Point& refpoint = m_unprocessed[index];

			for(; refpoint.visits < m_k; ++refpoint.visits)
			{
				Point point = randomPointAround(refpoint, radius);
				if(checkInside(point) && checkSpace(point))
				{
					pushPoint(point);
					return true;
				}
			}

			m_unprocessed.erase(m_unprocessed.begin() + index);
		}

		return false;
	}

	bool Poisson::addPoint(float radius, vec3& point)
	{
		bool added = this->insertPoint(radius);
		if(added)
			point = m_points.back().position;
		return added;
	}

	void Poisson::uniform(float radius)
	{
		while(this->insertPoint(radius))
			continue;
	}

	vector<vec3> Poisson::distribute(float radius)
	{
		while(insertPoint(radius))
			continue;

		vector<vec3> result;
		for(Point& point : m_points)
		{
			vec3 position = { point.position.x - m_size.x / 2.f, 0.f, point.position.y - m_size.y / 2.f };
			result.push_back(position);
		}
		return result;
	}

	vector<Circle> Poisson::distribute_circles(float radius)
	{
		vector<vec3> distribution = this->distribute(radius);
		vector<Circle> result;
		for(vec3& point : distribution)
			result.push_back({ point, radius, Axis::Y });
		return result;
	}

	vector<vec3> distribute_poisson(vec2 size, float radius)
	{
		Poisson distribution = { size, radius };
		return distribution.distribute(radius);
	}
}
