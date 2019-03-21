//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/string.h>
#include <math/Forward.h>
#include <math/Vec.h>
#include <math/Colour.h>

#include <sstream>

namespace mud
{
	export_ inline void read(std::istream& stream, size_t length, string& buffer)
	{
		buffer.resize(length);
		stream.read(&buffer[0], length);
	}

	export_ inline void read(std::istream& stream, size_t length, vector<uchar>& buffer)
	{
		buffer.resize(length);
		stream.read((char*)&buffer[0], length);
	}

	export_ inline string read(std::istream& stream, size_t length) { string result; read(stream, length, result); return result; }

	export_ template <class T>
	inline T read(std::istream& stream) { T result; stream >> result; return result; }

	export_ template <>
	inline vec3 read(std::istream& stream) { vec3 result; stream >> result.x >> result.y >> result.z; return result; }

	export_ template <>
	inline vec2 read(std::istream& stream) { vec2 result; stream >> result.x >> result.y; return result; }

	export_ template <>
	inline quat read(std::istream& stream) { quat result; stream >> result.x >> result.y >> result.z >> result.w; return result; }

	export_ template <>
	inline Colour read(std::istream& stream) { Colour result; stream >> result.r >> result.g >> result.b; return result; }
}