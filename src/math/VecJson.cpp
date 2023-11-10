//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.math;
#else
#include <stl/vector.h>
#include <math/Vec.hpp>
#include <math/VecJson.h>
#endif

#ifndef TWO_MODULES
#include <json11.hpp>
#endif

namespace two
{
	inline float jfloat(const Json& j) { return float(j.number_value()); }

	void from_json(const Json& j, vec3& vec)
	{
		vec = vec3(jfloat(j[0]), jfloat(j[1]), jfloat(j[2]));
	}

	void from_json(const Json& j, quat& q)
	{
		q = quat(jfloat(j[0]), jfloat(j[1]), jfloat(j[2]), jfloat(j[3]));
	}

	void from_json(const Json& j, mat4& mat)
	{
		mat = mat4(
			vec4(jfloat(j[0]),  jfloat(j[1]),  jfloat(j[2]),  jfloat(j[3])),
			vec4(jfloat(j[4]),  jfloat(j[5]),  jfloat(j[6]),  jfloat(j[7])),
			vec4(jfloat(j[8]),  jfloat(j[9]),  jfloat(j[10]), jfloat(j[11])),
			vec4(jfloat(j[12]), jfloat(j[13]), jfloat(j[14]), jfloat(j[15]))
		);
	}
}

namespace two
{
	void from_json(const Json& j, Colour& col)
	{
		col = Colour(float(j[0].number_value()), float(j[1].number_value()), float(j[2].number_value()), float(j[3].number_value()));
	}

	void to_json(const Colour& col, Json& j)
	{
		std::vector<Json> values;
		values = { col.r, col.g, col.b, col.a };
		j = values;
	}
}