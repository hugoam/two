//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stdint.h>
#include <stl/vector.h>
#include <stl/map.h>
#include <geom/Shape/ProcShape.h>

namespace two
{
	export_ class TWO_GEOM_EXPORT IcoSphere
	{
	public:
		IcoSphere(int subdiv = 1);

		using Line = ivec2;
		using Face = ivec3;

		vector<vec3> m_vertices;
		vector<Line> m_lines;
		vector<Face> m_faces;

	private:
		int vertex(const vec3& vertex);
		void triangle(int index0, int index1, int index2);
		int middle_point(int index0, int index1);
 
		map<int64_t, int> m_middle_point_cache;

	public:
		static vector<IcoSphere> s_levels;
	};
}
