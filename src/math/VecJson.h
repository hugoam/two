//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Colour.h>
#include <math/Vec.h>

#ifdef TWO_META_GENERATOR
namespace glm
{
	struct vec3; struct quat; struct mat4;
}
#endif

namespace json11
{
	class Json;
}

namespace two
{
	export_ using Json = json11::Json;

	export_ TWO_MATH_EXPORT void from_json(const Json& j, vec3& vec);
	export_ TWO_MATH_EXPORT void from_json(const Json& j, quat& quat);
	export_ TWO_MATH_EXPORT void from_json(const Json& j, mat4& mat);
}

namespace two
{
	export_ TWO_MATH_EXPORT void from_json(const Json& j, Colour& col);
	export_ TWO_MATH_EXPORT void to_json(const Colour& col, Json& json);
}
