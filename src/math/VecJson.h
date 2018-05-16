//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Colour.h>
#include <math/Vec.h>

#ifndef MUD_META_GENERATOR
#include <json.hpp>
using nlohmann::json;
#else
struct json;
namespace glm
{
	struct vec3; struct quat; struct mat4;
}
#endif

#ifdef MUD_NO_GLM
namespace mud
#else
namespace glm
#endif
{
	inline void from_json(const json& j, vec3& vec)
	{
		vec = { j[0], j[1], j[2] };
	}

	inline void from_json(const json& j, quat& quat)
	{
		// glm is w, x, y, z whereas gltf is x, y, z, w
		quat = { j[3], j[0], j[1], j[2] };
	}

	inline void from_json(const json& j, mat4& mat)
	{
		mat = { { j[0],  j[1],  j[2],  j[3]  },
				{ j[4],  j[5],  j[6],  j[7]  },
				{ j[8],  j[9],  j[10], j[11] },
				{ j[12], j[13], j[14], j[15] } };
	}
}

namespace mud
{
	inline void from_json(const json& j, Colour& col)
	{
		col = { j[0], j[1], j[2], j[3] };
	}
}
