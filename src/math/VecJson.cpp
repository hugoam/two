//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/VecJson.h>
#endif

#include <json11.hpp>

namespace mud
{
	void from_json(const json& j, vec3& vec)
	{
		vec = vec3(j[0].number_value(), j[1].number_value(), j[2].number_value());
	}

	void from_json(const json& j, quat& q)
	{
		// glm is w, x, y, z whereas gltf is x, y, z, w
		q = quat(j[3].number_value(), j[0].number_value(), j[1].number_value(), j[2].number_value());
	}

	void from_json(const json& j, mat4& mat)
	{
		mat = mat4(
			vec4(j[0].number_value(),  j[1].number_value(),  j[2].number_value(),  j[3].number_value()),
			vec4(j[4].number_value(),  j[5].number_value(),  j[6].number_value(),  j[7].number_value()),
			vec4(j[8].number_value(),  j[9].number_value(),  j[10].number_value(), j[11].number_value()),
			vec4(j[12].number_value(), j[13].number_value(), j[14].number_value(), j[15].number_value())
		);
	}
}

namespace mud
{
	void from_json(const json& j, Colour& col)
	{
		col = Colour(j[0].number_value(), j[1].number_value(), j[2].number_value(), j[3].number_value());
	}

	void to_json(const Colour& col, json& j)
	{
		std::vector<json> values;
		values = { col.m_r, col.m_g, col.m_b, col.m_a };
		j = values;
	}
}