//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Shape/ProcShape.h>

#include <vector>
#include <array>
#include <map>
#include <stdint.h>

namespace mud
{
	class MUD_MATH_EXPORT IcoSphere
	{
	public:
		IcoSphere(int recursionLevel);

		using Line = ivec2;
		using Face = ivec3;

		std::vector<vec3> m_vertices;
		std::vector<Line> m_lines;
		std::vector<Face> m_faces;

	private:
		int addVertex(const vec3& vertex);
		void addTriangle(int index0, int index1, int index2);
		int addMiddlePoint(int index0, int index1);
 
		std::map<int64_t, int> m_middlePointIndexCache;

	public:
		static std::vector<IcoSphere> s_levels;
	};
}
