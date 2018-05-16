//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <geom/Shape/Icosphere.h>

namespace mud
{
	std::vector<IcoSphere> IcoSphere::s_levels = { 1, 2, 3 };

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

		for(vec3& vertex : vertices)
			addVertex(vertex);

		Face faces[] = {
			{ 0, 11, 5 }, { 0, 5,  1  }, { 0,  1,  7  }, { 0,  7, 10 }, { 0, 10, 11 },
			{ 1, 5,  9 }, { 5, 11, 4  }, { 11, 10, 2  }, { 10, 7, 6  }, { 7, 1,  8  },
			{ 3, 9,  4 }, { 3, 4,  2  }, { 3,  2,  6  }, { 3,  6, 8  }, { 3, 8,  9  },
			{ 4, 9,  5 }, { 2, 4,  11 }, { 6,  2,  10 }, { 8,  6, 7  }, { 9, 8,  1  },
		};

		for(Face& face : faces)
			m_faces.emplace_back(face);

		Line lines[] = {
			{ 1, 0 }, { 1, 5 }, { 1, 7 }, { 1, 8  }, { 1, 9  },
			{ 2, 3 }, { 2, 4 }, { 2, 6 }, { 2, 10 }, { 2, 11 },
			{ 0, 5 }, { 5, 9 }, { 9, 8 }, { 8, 7 }, { 7, 0 },
			{ 10, 11 }, { 11, 4 }, { 4, 3 }, { 3, 6 }, { 6, 10 },

			{ 0, 11 }, { 11, 5 }, { 5, 4 }, { 4, 9 }, { 9, 3 },
			{ 3, 8 }, { 8, 6 }, { 6, 7 }, { 7, 10 }, { 10, 0 },
		};

		for(Line& line : lines)
			m_lines.emplace_back(line);

		for(int r = 0; r < recursionLevel; r++)
		{
			std::vector<Face> prevfaces = m_faces;

			m_faces.clear();
			m_lines.clear();

			for(Face& face : prevfaces)
			{
				int a = addMiddlePoint(face[0], face[1]);
				int b = addMiddlePoint(face[1], face[2]);
				int c = addMiddlePoint(face[2], face[0]);

				m_faces.push_back({ face[0], a, c });
				m_faces.push_back({ face[1], b, a });
				m_faces.push_back({ face[2], c, b });
				m_faces.push_back({ a, b, c });

				addTriangle(face[0], a, c);
				addTriangle(face[1], b, a);
				addTriangle(face[2], c, b);
			}
		}
	}

	void IcoSphere::addTriangle(int index0, int index1, int index2)
	{
		m_lines.push_back({ index0, index1 });
		m_lines.push_back({ index1, index2 });
		m_lines.push_back({ index2, index0 });
	}
	
	int IcoSphere::addVertex(const vec3& vertex)
	{
		m_vertices.emplace_back(normalize(vertex));
		return m_vertices.size()-1;
	}

	int IcoSphere::addMiddlePoint(int index0, int index1)
	{
		bool isFirstSmaller = index0 < index1;
		int64_t smallerIndex = isFirstSmaller ? index0 : index1;
		int64_t largerIndex = isFirstSmaller ? index1 : index0;
		int64_t key = (smallerIndex << 32) | largerIndex;

		if (m_middlePointIndexCache.find(key) != m_middlePointIndexCache.end())
			return m_middlePointIndexCache[key];

		vec3 point1 = m_vertices[index0];
		vec3 point2 = m_vertices[index1];
		vec3 middle = (point1 + point2) / 2.f;

		int index = addVertex(middle);
		m_middlePointIndexCache[key] = index;
		return index;
	}
}
