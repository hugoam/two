//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.math;
#else
#include <math/VecJson.h>
#endif

#include <json11.hpp>

namespace mud
{
	inline float jfloat(const json& j) { return float(j.number_value()); }

	void from_json(const json& j, vec3& vec)
	{
		vec = vec3(jfloat(j[0]), jfloat(j[1]), jfloat(j[2]));
	}

	void from_json(const json& j, quat& q)
	{
#ifdef MUD_NO_GLM
		q = quat(jfloat(j[0]), jfloat(j[1]), jfloat(j[2]), jfloat(j[3]));
#else
		// glm is w, x, y, z whereas gltf is x, y, z, w
		q = quat(jfloat(j[3]), jfloat(j[0]), jfloat(j[1]), jfloat(j[2]));
#endif
	}

	void from_json(const json& j, mat4& mat)
	{
		mat = mat4(
			vec4(jfloat(j[0]),  jfloat(j[1]),  jfloat(j[2]),  jfloat(j[3])),
			vec4(jfloat(j[4]),  jfloat(j[5]),  jfloat(j[6]),  jfloat(j[7])),
			vec4(jfloat(j[8]),  jfloat(j[9]),  jfloat(j[10]), jfloat(j[11])),
			vec4(jfloat(j[12]), jfloat(j[13]), jfloat(j[14]), jfloat(j[15]))
		);
	}
}

namespace mud
{
	void from_json(const json& j, Colour& col)
	{
		col = Colour(float(j[0].number_value()), float(j[1].number_value()), float(j[2].number_value()), float(j[3].number_value()));
	}

	void to_json(const Colour& col, json& j)
	{
		vector<json> values;
		values = { col.m_r, col.m_g, col.m_b, col.m_a };
		j = values;
	}
}