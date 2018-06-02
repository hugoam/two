//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Serial/Serial.h>
#include <math/Colour.h>
#include <math/Vec.h>

#ifdef MUD_META_GENERATOR
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
	MUD_MATH_EXPORT void from_json(const json& j, vec3& vec);
	MUD_MATH_EXPORT void from_json(const json& j, quat& quat);
	MUD_MATH_EXPORT void from_json(const json& j, mat4& mat);
}

namespace mud
{
	MUD_MATH_EXPORT void from_json(const json& j, Colour& col);
	MUD_MATH_EXPORT void to_json(const Colour& col, json& json);
}
