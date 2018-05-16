//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>
#include <math/Vec.h>

#include <sstream>
#include <string>

namespace mud
{
	using string = std::string;

	inline string read(std::istream& stream, size_t length) { string result; result.resize(length); stream.read(&result[0], length); return result; }

	template <class T>
	inline T read(std::istream& stream) { T result; stream >> result; return result; }

	template <>
	inline vec3 read(std::istream& stream) { vec3 result; stream >> result.x >> result.y >> result.z; return result; }

	template <>
	inline vec2 read(std::istream& stream) { vec2 result; stream >> result.x >> result.y; return result; }

	template <>
	inline quat read(std::istream& stream) { quat result; stream >> result.x >> result.y >> result.z >> result.w; return result; }

	template <>
	inline Colour read(std::istream& stream) { Colour result; stream >> result.m_r >> result.m_g >> result.m_b; return result; }

}
