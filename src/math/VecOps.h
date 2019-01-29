//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>
#include <math/Vec.h>
#include <math/Math.h>
#include <math/Colour.h>

namespace mud
{
	inline bool operator<(const uvec2& lhs, const uvec2& rhs) { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }
	inline bool operator<(const ivec2& lhs, const ivec2& rhs) { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }
}

namespace mud
{
	export_ inline vec3 to_vec3(const Colour& colour) { return { colour.m_r, colour.m_g, colour.m_b }; }
	export_ inline vec4 to_vec4(const Colour& colour) { return { colour.m_r, colour.m_g, colour.m_b, colour.m_a }; }
	export_ inline Colour to_colour(const vec3& vec) { return { vec.x, vec.y, vec.z }; }
	export_ inline Colour to_colour(const vec4& vec) { return { vec.x, vec.y, vec.z, vec.w }; }

	export_ inline vec3 rotate(const vec3& v, float angle, const vec3& axis) { return angle_axis(angle, axis) * v; }
	export_ inline vec3 rotate(const vec3& v, const vec3& axis, float angle) { return angle_axis(angle, axis) * v; }

	export_ MUD_MATH_EXPORT func_ quat look_dir(const vec3& direction, const vec3& forward = -Z3);
	export_ MUD_MATH_EXPORT func_ quat look_at(const vec3& eye, const vec3& target, const vec3& forward = -Z3);

	export_ MUD_MATH_EXPORT uint32_t pack4(const vec4& vec);
	export_ MUD_MATH_EXPORT uint32_t pack3(const vec3& vec);
	export_ MUD_MATH_EXPORT vec3 unpack3(uint32_t vec);
	export_ MUD_MATH_EXPORT vec4 unpack4(uint32_t vec);

	export_ MUD_MATH_EXPORT Axis nearest_axis(const vec3& direction);

	export_ MUD_MATH_EXPORT float float_shortest_angle(float angle1, float angle2);
	export_ MUD_MATH_EXPORT float trigo_angle(const vec3& vec1, const vec3& vec2);
	export_ MUD_MATH_EXPORT float shortest_angle(const vec3& vec1, const vec3& vec2);

	export_ MUD_MATH_EXPORT void orthonormalize(const mat4& transform, vec3& x, vec3& y, vec3& z);
	export_ MUD_MATH_EXPORT mat4 orthonormalize(const mat4& transform);
	export_ MUD_MATH_EXPORT mat4 bias_mat();
	export_ MUD_MATH_EXPORT mat4 bias_mat_bgfx(bool origin_bottom_left, bool homogeneous_depth);
	export_ MUD_MATH_EXPORT mat4 rect_mat(vec4 rect);

	export_ MUD_MATH_EXPORT mat4 abs(const mat4& mat);

	export_ inline void flatten(vec3& vector)
	{
		for(vec3::length_type i = 0; i < 3; ++i)
			if(fabs(vector[i]) < 0.0000001f)
				vector[i] = 0.f;
	}

	export_ inline void flatten(float& f)
	{
		if(fabs(f) < 0.0000001)
			f = 0.f;
	}

#ifndef MUD_META_GENERATOR
	export_ template MUD_MATH_EXPORT func_ vec3 add<vec3>(vec3 a, vec3 b);
	export_ template MUD_MATH_EXPORT func_ vec3 subtract<vec3>(vec3 a, vec3 b);
	export_ template MUD_MATH_EXPORT func_ vec3 multiply<vec3>(vec3 a, vec3 b);
	export_ template MUD_MATH_EXPORT func_ vec3 divide<vec3>(vec3 a, vec3 b);
#else
	template <> func_ vec3 add<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 subtract<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 multiply<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 divide<vec3>(vec3 a, vec3 b);
#endif

	export_ template <class T>
	struct refl_ struct_ Range
	{
		Range() {}
		Range(T min, T max) : m_min(min), m_max(max) {}
		attr_ T m_min = {};
		attr_ T m_max = {};
		bool operator==(const Range<T>& other) const { return m_min == other.m_min && m_max == other.m_max; }
	};

	export_ extern template struct refl_ Range<vec3>;
	export_ extern template struct refl_ Range<quat>;
	export_ extern template struct refl_ Range<float>;
	export_ extern template struct refl_ Range<uint32_t>;
	export_ extern template struct refl_ Range<Colour>;
}
