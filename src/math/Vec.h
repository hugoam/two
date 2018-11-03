//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Array.h>
#include <math/Forward.h>

#ifndef MUD_CPP_20
#include <cstdint>
#endif

#ifndef MUD_META_GENERATOR
//#define MUD_NO_GLM
#endif

#include <math/VecMath.h>

#ifdef MUD_NO_GLM
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
#else
#ifndef MUD_META_GENERATOR
#define GLM_ENABLE_EXPERIMENTAL

#if defined _MSC_VER
#	pragma warning (push)
#	pragma warning (disable : 4701)
#endif

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

#if defined _MSC_VER
#	pragma warning (pop)
#endif

namespace mud
{
	export_ using glm::vec2;
	export_ using glm::uvec2;
	export_ using glm::ivec2;
	export_ using glm::vec3;
	export_ using glm::bvec3;
	export_ using glm::uvec3;
	export_ using glm::ivec3;
	export_ using glm::vec4;
	export_ using glm::bvec4;
	export_ using glm::uvec4;
	export_ using glm::ivec4;
	export_ using glm::quat;
	export_ using glm::mat2;
	export_ using glm::mat3;
	export_ using glm::mat4;

	export_ using half3 = glm::vec<3, ushort, glm::highp>;
	export_ using half2 = glm::vec<2, ushort, glm::highp>;
	export_ using ushort2 = glm::vec<2, ushort, glm::highp>;
	export_ using ushort3 = glm::vec<3, ushort, glm::highp>;
	export_ using ushort4 = glm::vec<4, ushort, glm::highp>;
}
#endif
#endif

#ifdef MUD_META_GENERATOR
namespace mud
{
	struct refl_ array_ extern_ vec2  { constr_ vec2();   constr_ vec2(float a);     constr_ vec2(float x, float y);                                attr_ float x; attr_ float y; };
	struct refl_ array_ extern_ uvec2 { constr_ uvec2();  constr_ uvec2(uint32_t a); constr_ uvec2(uint32_t x, uint32_t y);						   attr_ uint32_t x; attr_ uint32_t y; };
	struct refl_ array_ extern_ vec3  { constr_ vec3();   constr_ vec3(float a);     constr_ vec3(float x, float y, float z);                       attr_ float x; attr_ float y; attr_ float z; };
	struct refl_ array_ extern_ uvec3 { constr_ uvec3();  constr_ uvec3(uint32_t a); constr_ uvec3(uint32_t x, uint32_t y, uint32_t z);             attr_ uint32_t x;   attr_ uint32_t y;   attr_ uint32_t z; };
	struct refl_ array_ extern_ ivec3 { constr_ ivec3();  constr_ ivec3(int a);      constr_ ivec3(int x, int y, int z);                            attr_ int x;   attr_ int y;   attr_ int z; };
	struct refl_ array_ extern_ vec4  { constr_ vec4();   constr_ vec4(float a);     constr_ vec4(float w, float x, float y, float z);              attr_ float x; attr_ float y; attr_ float z; attr_ float w; };
	struct refl_ array_ extern_ uvec4 { constr_ uvec4();  constr_ uvec4(uint32_t a); constr_ uvec4(uint32_t w, uint32_t x, uint32_t y, uint32_t z); attr_ uint32_t x; attr_ uint32_t y; attr_ uint32_t z; attr_ uint32_t w; };
	struct refl_ array_ extern_ quat  { constr_ quat();   constr_ quat(float w, float x, float y, float z);   constr_ quat(vec3 euler_angles);      attr_ float x; attr_ float y; attr_ float z; attr_ float w; };
	struct refl_ extern_ mat4 {};

	struct refl_ extern_ bvec3 {};
	struct refl_ extern_ bvec4 {};
	struct refl_ extern_ ivec2 {};
	struct refl_ extern_ ivec4 {};
}
#endif

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