//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>
#include <math/Vec.h>
#include <math/Math.h>
#include <math/Colour.h>

namespace mud
{
	inline vec3 to_vec3(const Colour& colour) { return { colour.m_r, colour.m_g, colour.m_b }; }
	inline vec4 to_vec4(const Colour& colour) { return { colour.m_r, colour.m_g, colour.m_b, colour.m_a }; }
	inline Colour to_colour(const vec3& vec) { return { vec.x, vec.y, vec.z }; }
	inline Colour to_colour(const vec4& vec) { return { vec.x, vec.y, vec.z, vec.w }; }

#ifndef MUD_NO_GLM
	inline bvec3 greater(const vec3& lhs, const vec3& rhs) { return glm::greaterThan(lhs, rhs); }
	inline bvec4 greater(const vec4& lhs, const vec4& rhs) { return glm::greaterThan(lhs, rhs); }
	inline bvec3 greater_equal(const vec3& lhs, const vec3& rhs) { return glm::greaterThanEqual(lhs, rhs); }
	inline bvec3 less(const vec3& lhs, const vec3& rhs) { return glm::lessThan(lhs, rhs); }
	inline float oriented_angle(const vec2& lhs, const vec2& rhs) { return glm::orientedAngle(lhs, rhs); }
	inline float oriented_angle(const vec3& lhs, const vec3& rhs, const vec3& ref) { return glm::orientedAngle(lhs, rhs, ref); }
	inline quat angle_axis(float angle, const vec3& axis) { return glm::angleAxis(angle, axis); }
	inline quat rotate(const quat& q, float angle, const vec3& axis) { return glm::rotate(q, angle, axis); }
	//inline vec3 rotate(const vec3& v, float angle, const vec3& axis) { return glm::rotate(v, angle, axis); }
	inline vec3 rotate(const quat& q, const vec3& vec) { return q * vec; }
#endif

	inline vec3 rotate(const vec3& v, float angle, const vec3& axis) { return angle_axis(angle, axis) * v; }

	MUD_MATH_EXPORT uint32_t pack4(const vec4& vec);
	MUD_MATH_EXPORT uint32_t pack3(const vec3& vec);
	MUD_MATH_EXPORT vec3 unpack3(uint32_t vec);
	MUD_MATH_EXPORT vec4 unpack4(uint32_t vec);

	MUD_MATH_EXPORT Axis nearest_axis(const vec3& direction);

	MUD_MATH_EXPORT float float_shortest_angle(float angle1, float angle2);
	MUD_MATH_EXPORT float trigo_angle(const vec3& vec1, const vec3& vec2);
	MUD_MATH_EXPORT float shortest_angle(const vec3& vec1, const vec3& vec2);

	MUD_MATH_EXPORT void orthonormalize(const mat4& transform, vec3& x, vec3& y, vec3& z);
	MUD_MATH_EXPORT mat4 orthonormalize(const mat4& transform);
	MUD_MATH_EXPORT mat4 bias_mat();
	MUD_MATH_EXPORT mat4 bias_mat_bgfx(bool origin_bottom_left, bool homogeneous_depth);
	MUD_MATH_EXPORT mat4 rect_mat(vec4 rect);

	MUD_MATH_EXPORT mat4 abs(const mat4& mat);

	inline void flatten(vec3& vector)
	{
		for(size_t i = 0; i < 3; ++i)
			if(fabs(vector[i]) < 0.0000001f)
				vector[i] = 0.f;
	}

	inline void flatten(float& f)
	{
		if(fabs(f) < 0.0000001)
			f = 0.f;
	}

#ifndef MUD_META_GENERATOR
	template MUD_MATH_EXPORT _func_ vec3 add<vec3>(vec3 a, vec3 b);
	template MUD_MATH_EXPORT _func_ vec3 subtract<vec3>(vec3 a, vec3 b);
	template MUD_MATH_EXPORT _func_ vec3 multiply<vec3>(vec3 a, vec3 b);
	template MUD_MATH_EXPORT _func_ vec3 divide<vec3>(vec3 a, vec3 b);
#else
	template <> _func_ vec3 add<vec3>(vec3 a, vec3 b);
	template <> _func_ vec3 subtract<vec3>(vec3 a, vec3 b);
	template <> _func_ vec3 multiply<vec3>(vec3 a, vec3 b);
	template <> _func_ vec3 divide<vec3>(vec3 a, vec3 b);
#endif

	template <class T>
	struct _refl_ _struct_ Range
	{
		Range() {}
		Range(T min, T max) : m_min(min), m_max(max) {}
		_attr_ _mut_ T m_min = {};
		_attr_ _mut_ T m_max = {};
		bool operator==(const Range<T>& other) const { return m_min == other.m_min && m_max == other.m_max; }
	};

	template struct _refl_ _struct_ Range<vec3>;
	template struct _refl_ _struct_ Range<quat>;
	template struct _refl_ _struct_ Range<float>;
	template struct _refl_ _struct_ Range<uint32_t>;
	template struct _refl_ _struct_ Range<Colour>;
}
