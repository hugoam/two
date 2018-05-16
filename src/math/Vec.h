//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>
#include <stdint.h>

#ifndef MUD_META_GENERATOR
//#define MUD_NO_GLM
#endif

#include <math/VecMath.h>

#ifdef MUD_NO_GLM
namespace mud
{
	using vec2 = float2;
	using vec3 = float3;
	using vec4 = float4;
	using uvec2 = uint2;
	using uvec3 = uint3;
	using uvec4 = uint4;
	using ivec2 = int2;
	using ivec3 = int3;
	using ivec4 = int4;
	using bvec3 = bool3;
	using bvec4 = bool4;
}
#else
#ifndef MUD_META_GENERATOR
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace mud
{
	using glm::vec2;
	using glm::uvec2;
	using glm::ivec2;
	using glm::vec3;
	using glm::bvec3;
	using glm::uvec3;
	using glm::ivec3;
	using glm::vec4;
	using glm::bvec4;
	using glm::uvec4;
	using glm::ivec4;
	using glm::quat;
	using glm::mat2;
	using glm::mat3;
	using glm::mat4;
}
#endif
#endif

#ifdef  MUD_META_GENERATOR
namespace mud
{
	struct _refl_ _array_ _extern_ vec2  { _constr_ vec2();   _constr_ vec2(float a);     _constr_ vec2(float x, float y);                                _attr_ _mut_ float x; _attr_ _mut_ float y; };
	struct _refl_ _array_ _extern_ uvec2 { _constr_ uvec2();  _constr_ uvec2(uint32_t a); _constr_ uvec2(uint32_t x, uint32_t y);						   _attr_ _mut_ uint32_t x; _attr_ _mut_ uint32_t y; };
	struct _refl_ _array_ _extern_ vec3  { _constr_ vec3();   _constr_ vec3(float a);     _constr_ vec3(float x, float y, float z);                       _attr_ _mut_ float x; _attr_ _mut_ float y; _attr_ _mut_ float z; };
	struct _refl_ _array_ _extern_ uvec3 { _constr_ uvec3();  _constr_ uvec3(uint32_t a); _constr_ uvec3(uint32_t x, uint32_t y, uint32_t z);             _attr_ _mut_ uint32_t x;   _attr_ _mut_ uint32_t y;   _attr_ _mut_ uint32_t z; };
	struct _refl_ _array_ _extern_ ivec3 { _constr_ ivec3();  _constr_ ivec3(int a);      _constr_ ivec3(int x, int y, int z);                            _attr_ _mut_ int x;   _attr_ _mut_ int y;   _attr_ _mut_ int z; };
	struct _refl_ _array_ _extern_ vec4  { _constr_ vec4();   _constr_ vec4(float a);     _constr_ vec4(float w, float x, float y, float z);              _attr_ _mut_ float x; _attr_ _mut_ float y; _attr_ _mut_ float z; _attr_ _mut_ float w; };
	struct _refl_ _array_ _extern_ uvec4 { _constr_ uvec4();  _constr_ uvec4(uint32_t a); _constr_ uvec4(uint32_t w, uint32_t x, uint32_t y, uint32_t z); _attr_ _mut_ uint32_t x; _attr_ _mut_ uint32_t y; _attr_ _mut_ uint32_t z; _attr_ _mut_ uint32_t w; };
	struct _refl_ _array_ _extern_ quat  { _constr_ quat();   _constr_ quat(float w, float x, float y, float z);   _constr_ quat(vec3 euler_angles);      _attr_ _mut_ float x; _attr_ _mut_ float y; _attr_ _mut_ float z; _attr_ _mut_ float w; };
	struct _refl_ _extern_ mat4 {};

	struct _extern_ bvec3 {};
	struct _extern_ bvec4 {};
	struct _extern_ ivec2 {};
	struct _extern_ ivec4 {};
}
#endif

namespace mud
{
	extern MUD_MATH_EXPORT const vec3 X3; // = { 1.f, 0.f, 0.f };
	extern MUD_MATH_EXPORT const vec3 Y3; // = { 0.f, 1.f, 0.f };
	extern MUD_MATH_EXPORT const vec3 Z3; // = { 0.f, 0.f, 1.f };

	extern MUD_MATH_EXPORT const vec3 Zero3; // = { 0.f, 0.f, 0.f };
	extern MUD_MATH_EXPORT const vec3 Unit3; // = { 1.f, 1.f, 1.f };

	extern MUD_MATH_EXPORT const quat ZeroQuat; // = { 1.f, 0.f, 0.f, 0.f };

	extern MUD_MATH_EXPORT const vec2 Zero2; // = { 0.f, 0.f };
	extern MUD_MATH_EXPORT const vec2 Unit2; // = { 1.f, 1.f };

	extern MUD_MATH_EXPORT const vec4 Zero4; // = { 0.f, 0.f, 0.f, 0.f };
	extern MUD_MATH_EXPORT const vec4 Rect4; // = { 0.f, 0.f, 1.f, 1.f };

	inline float& rect_w(vec4& rect) { return rect.z; }
	inline float& rect_h(vec4& rect) { return rect.w; }

	inline float rect_w(const vec4& rect) { return rect.z; }
	inline float rect_h(const vec4& rect) { return rect.w; }

	inline unsigned int& rect_w(uvec4& rect) { return rect.z; }
	inline unsigned int& rect_h(uvec4& rect) { return rect.w; }

	inline vec2 rect_offset(const vec4& rect) { return{ rect.x, rect.y }; }
	inline vec2 rect_size(const vec4& rect) { return{ rect.z, rect.w }; }
	inline vec2 rect_sum(const vec4& rect) { return vec2{ rect.x, rect.y } + vec2{ rect.z, rect.w }; }
	inline vec2 rect_center(const vec4& rect) { return rect_offset(rect) + rect_size(rect) * 0.5f; }

	inline bool rect_intersects(const vec4& first, const vec4& second)
	{
		return !(second.x > first.x + first.z || second.y > first.y + first.w || second.x + second.z < first.x || second.y + second.w < first.y);
	}
}