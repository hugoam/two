//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <math/Math.h>
#include <math/Vec.hpp>
#include <geom/Shape/Icosphere.h>
#endif

namespace mud
{
	vector<IcoSphere> IcoSphere::s_levels = { 1, 2, 3 };

	IcoSphere::IcoSphere(int recursionLevel)
	{
		float t = (1.0f + sqrt(5.0f)) / 2.0f;

		vec3 vertices[] = {
			{ -1.0f,  t,  0.0f },
			{  1.0f,  t,  0.0f },
			{ -1.0f, -t,  0.0f },
			{  1.0f, -t,  0.0f },
							
			{  0.0f, -1.0f,  t },
			{  0.0f,  1.0f,  t },
			{  0.0f, -1.0f, -t },
			{  0.0f,  1.0f, -t },
							
			{  t,  0.0f, -1.0f },
			{  t,  0.0f,  1.0f },
			{ -t,  0.0f, -1.0f },
			{ -t,  0.0f,  1.0f },
		};

		for(vec3& vert : vertices)
			this->vertex(vert);

		Face faces[] = {
			{ 0, 11, 5 }, { 0, 5,  1  }, { 0,  1,  7  }, { 0,  7, 10 }, { 0, 10, 11 },
			{ 1, 5,  9 }, { 5, 11, 4  }, { 11, 10, 2  }, { 10, 7, 6  }, { 7, 1,  8  },
			{ 3, 9,  4 }, { 3, 4,  2  }, { 3,  2,  6  }, { 3,  6, 8  }, { 3, 8,  9  },
			{ 4, 9,  5 }, { 2, 4,  11 }, { 6,  2,  10 }, { 8,  6, 7  }, { 9, 8,  1  },
		};

		for(Face& face : faces)
			m_faces.push_back(face);

		Line lines[] = {
			{ 1, 0 }, { 1, 5 }, { 1, 7 }, { 1, 8  }, { 1, 9  },
			{ 2, 3 }, { 2, 4 }, { 2, 6 }, { 2, 10 }, { 2, 11 },
			{ 0, 5 }, { 5, 9 }, { 9, 8 }, { 8, 7 }, { 7, 0 },
			{ 10, 11 }, { 11, 4 }, { 4, 3 }, { 3, 6 }, { 6, 10 },

			{ 0, 11 }, { 11, 5 }, { 5, 4 }, { 4, 9 }, { 9, 3 },
			{ 3, 8 }, { 8, 6 }, { 6, 7 }, { 7, 10 }, { 10, 0 },
		};

		for(Line& line : lines)
			m_lines.push_back(line);

		for(int r = 0; r < recursionLevel; r++)
		{
			vector<Face> prevfaces = m_faces;

			m_faces.clear();
			m_lines.clear();

			for(Face& face : prevfaces)
			{
				int a = this->middle_point(face[0], face[1]);
				int b = this->middle_point(face[1], face[2]);
				int c = this->middle_point(face[2], face[0]);

				m_faces.push_back({ face[0], a, c });
				m_faces.push_back({ face[1], b, a });
				m_faces.push_back({ face[2], c, b });
				m_faces.push_back({ a, b, c });

				this->triangle(face[0], a, c);
				this->triangle(face[1], b, a);
				this->triangle(face[2], c, b);
			}
		}
	}

	void IcoSphere::triangle(int index0, int index1, int index2)
	{
		m_lines.push_back({ index0, index1 });
		m_lines.push_back({ index1, index2 });
		m_lines.push_back({ index2, index0 });
	}
	
	int IcoSphere::vertex(const vec3& vertex)
	{
		m_vertices.push_back(normalize(vertex));
		return int(m_vertices.size() - 1);
	}

	int IcoSphere::middle_point(int index0, int index1)
	{
		int64_t lo = index0 < index1 ? index0 : index1;
		int64_t hi = index0 < index1 ? index1 : index0;
		int64_t key = (lo << 32) | hi;

		if (m_middle_point_cache.find(key) != m_middle_point_cache.end())
			return m_middle_point_cache[key];

		vec3 point1 = m_vertices[index0];
		vec3 point2 = m_vertices[index1];
		vec3 middle = (point1 + point2) / 2.f;

		int index = this->vertex(middle);
		m_middle_point_cache[key] = index;
		return index;
	}
}
