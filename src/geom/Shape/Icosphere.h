//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Shape/ProcShape.h>

#ifndef MUD_CPP_20
#include <vector>
#include <array>
#include <map>
#include <cstdint>
#endif

namespace mud
{
	export_ class MUD_MATH_EXPORT IcoSphere
	{
	public:
		IcoSphere(int recursionLevel);

		using Line = ivec2;
		using Face = ivec3;

		std::vector<vec3> m_vertices;
		std::vector<Line> m_lines;
		std::vector<Face> m_faces;

	private:
		int vertex(const vec3& vertex);
		void triangle(int index0, int index1, int index2);
		int middle_point(int index0, int index1);
 
		std::map<int64_t, int> m_middle_point_cache;

	public:
		static std::vector<IcoSphere> s_levels;
	};
}
