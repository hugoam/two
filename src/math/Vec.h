//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>

#ifndef MUD_CPP_20
#include <cstdint>
#endif

#include <math/VecMath.h>

namespace mud
{
	export_ using vec2 = float2;
	export_ using vec3 = float3;
	export_ using vec4 = float4;
	export_ using uvec2 = uint2;
	export_ using uvec3 = uint3;
	export_ using uvec4 = uint4;
	export_ using ivec2 = int2;
	export_ using ivec3 = int3;
	export_ using ivec4 = int4;
	export_ using bvec3 = bool3;
	export_ using bvec4 = bool4;
}

namespace mud
{
	export_ extern MUD_MATH_EXPORT const vec3 X3; // = { 1.f, 0.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec3 Y3; // = { 0.f, 1.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec3 Z3; // = { 0.f, 0.f, 1.f };

	export_ extern MUD_MATH_EXPORT const vec3 Zero3; // = { 0.f, 0.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec3 Unit3; // = { 1.f, 1.f, 1.f };

	export_ extern MUD_MATH_EXPORT const quat ZeroQuat; // = { 1.f, 0.f, 0.f, 0.f };

	export_ extern MUD_MATH_EXPORT const vec2 Zero2; // = { 0.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec2 Unit2; // = { 1.f, 1.f };

	export_ extern MUD_MATH_EXPORT const vec4 Zero4; // = { 0.f, 0.f, 0.f, 0.f };
	export_ extern MUD_MATH_EXPORT const vec4 Rect4; // = { 0.f, 0.f, 1.f, 1.f };

	export_ inline vec3 mulp(const mat4& mat, const vec3& p) { return vec3(mat * vec4(p, 1.f)); }
	export_ inline vec3 mult(const mat4& mat, const vec3& n) { return vec3(mat * vec4(n, 0.f)); }
	export_ inline vec3 muln(const mat4& mat, const vec3& n) { return normalize(vec3(mat * vec4(n, 0.f))); }
	//export_ inline vec3 muln(const mat4& mat, const vec3& n) { return vec3(normalize(mat * vec4(n, 0.f))); }
	export_ inline vec4 mult(const mat4& mat, const vec4& t) { return vec4(vec3(mat * vec4(vec3(t), 0.f)), t.w); }

	export_ inline vec3 to_xz(const vec2& vec) { return{ vec.x, 0.f, vec.y }; }
	export_ inline vec2 to_xz(const vec3& vec) { return{ vec.x, vec.z }; }
	export_ inline ivec3 to_xz(const ivec2& vec) { return{ vec.x, 0, vec.y }; }
	export_ inline ivec2 to_xz(const ivec3& vec) { return{ vec.x, vec.z }; }

	export_ inline float& rect_w(vec4& rect) { return rect.z; }
	export_ inline float& rect_h(vec4& rect) { return rect.w; }

	export_ inline float rect_w(const vec4& rect) { return rect.z; }
	export_ inline float rect_h(const vec4& rect) { return rect.w; }

	export_ inline unsigned int& rect_w(uvec4& rect) { return rect.z; }
	export_ inline unsigned int& rect_h(uvec4& rect) { return rect.w; }

	export_ inline vec2 rect_offset(const vec4& rect) { return{ rect.x, rect.y }; }
	export_ inline vec2 rect_size(const vec4& rect) { return{ rect.z, rect.w }; }
	export_ inline vec2 rect_sum(const vec4& rect) { return vec2{ rect.x, rect.y } + vec2{ rect.z, rect.w }; }
	export_ inline vec2 rect_center(const vec4& rect) { return rect_offset(rect) + rect_size(rect) * 0.5f; }

	export_ inline bool rect_intersects(const vec4& first, const vec4& second)
	{
		return !(second.x > first.x + first.z || second.y > first.y + first.w || second.x + second.z < first.x || second.y + second.w < first.y);
	}

	export_ struct refl_ MUD_MATH_EXPORT Transform
	{
		constr_ Transform() {}
		constr_ Transform(const vec3& position, const quat& rotation, const vec3& scale) : m_position(position), m_rotation(rotation), m_scale(scale) {}
		attr_ vec3 m_position = Zero3;
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = Unit3;
	};

	Transform average_transforms(array<Transform*> transforms);
}