//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>

#ifndef MUD_CPP_20
#include <stdint.h>
#endif

#ifdef MUD_META_GENERATOR
namespace mud
{
	struct refl_ array_ extern_ vec2  { constr_ vec2();   constr_ vec2(float a);     constr_ vec2(float x, float y);                                attr_ float x; attr_ float y; };
	struct refl_ array_ extern_ uvec2 { constr_ uvec2();  constr_ uvec2(uint32_t a); constr_ uvec2(uint32_t x, uint32_t y);						    attr_ uint32_t x; attr_ uint32_t y; };
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

	struct refl_ extern_ half3 {};
	struct refl_ extern_ half2 {};
}
#else
namespace mud
{
	template <class T>
	export_ struct refl_ struct_ array_ v2
	{
		typedef uint length_type;
		typedef T type;
		v2();
		explicit v2(T v);
		v2(T x, T y);
		template <class V>
		explicit v2(V v);
		T operator[](uint index) const;
		T& operator[](uint index);
		bool operator==(const v2& other) const;
		bool operator!=(const v2& other) const;
		explicit operator T();
		union {
			struct { attr_ T x; attr_ T y; };
			T f[2];
		};
	};

	template <class T>
	export_ struct refl_ struct_ array_ v3
	{
		typedef uint length_type;
		typedef T type;
		typedef v2<T> type2;
		v3();
		explicit v3(T v);
		v3(T x, T y, T z);
		v3(v2<T> a, T z);
		template <class V>
		explicit v3(V v);
		T operator[](uint index) const;
		T& operator[](uint index);
		bool operator==(const v3& other) const;
		bool operator!=(const v3& other) const;
		explicit operator T();
		explicit operator v2<T>();
		union {
			struct { attr_ T x; attr_ T y; attr_ T z; };
			struct { T r; T g; T b; };
			T f[3];
		};
	};

	template <class T>
	export_ struct refl_ struct_ array_ v4
	{
		typedef uint length_type;
		typedef T type;
		typedef v2<T> type2;
		typedef v3<T> type3;
		v4();
		explicit v4(T v);
		v4(T x, T y, T z, T w);
		v4(v3<T> a, T w);
		v4(T x, v3<T> b);
		v4(v2<T> a, v2<T> b);
		template <class V>
		explicit v4(V v);
		T operator[](uint index) const;
		T& operator[](uint index);
		bool operator==(const v4& other) const;
		bool operator!=(const v4& other) const;
		explicit operator v2<T>();
		explicit operator v3<T>();
		union {
			struct { attr_ T x; attr_ T y; attr_ T z; attr_ T w; };
			struct { T r; T g; T b; T a; };
			T f[4];
		};
	};

	export_ extern template struct refl_ v2<float>;
	export_ extern template struct refl_ v3<float>;
	export_ extern template struct refl_ v4<float>;

	export_ extern template struct refl_ v2<int>;
	export_ extern template struct refl_ v3<int>;
	export_ extern template struct refl_ v4<int>;

	export_ extern template struct refl_ v2<uint>;
	export_ extern template struct refl_ v3<uint>;
	export_ extern template struct refl_ v4<uint>;

	export_ extern template struct refl_ v2<bool>;
	export_ extern template struct refl_ v3<bool>;
	export_ extern template struct refl_ v4<bool>;

	export_ refl_ using half2 = v2<ushort>;
	export_ refl_ using half3 = v3<ushort>;

	export_ refl_ using float2 = v2<float>;
	export_ refl_ using float3 = v3<float>;
	export_ refl_ using float4 = v4<float>;

	export_ refl_ using int2 = v2<int>;
	export_ refl_ using int3 = v3<int>;
	export_ refl_ using int4 = v4<int>;

	export_ refl_ using uint2 = v2<uint>;
	export_ refl_ using uint3 = v3<uint>;
	export_ refl_ using uint4 = v4<uint>;

	export_ refl_ using bool2 = v2<bool>;
	export_ refl_ using bool3 = v3<bool>;
	export_ refl_ using bool4 = v4<bool>;

	export_ template <class T> inline typename T::type* value_ptr(T& v) { return &v[0]; }
	export_ template <class T> inline const typename T::type* value_ptr(const T& v) { return &v.f[0]; }

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

	export_ struct refl_ struct_ array_ mat3
	{
		typedef float type;
		mat3();
		mat3(const float3& x, const float3& y, const float3& z);
		mat3(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8);

		const float3& operator[](uint index) const { return *((float3*)f + index); }
		float3& operator[](uint index) { return *((float3*)f + index); }

		union
		{
			float m[3][3];
			attr_ float f[9];
		};
	};

	export_ struct refl_ struct_ array_ mat4
	{
		typedef float type;
		typedef uint length_type;
		mat4();
		mat4(const float4& x, const float4& y, const float4& z, const float4& w);
		mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15);

		const float4& operator[](uint index) const { return *((float4*)f + index); }
		float4& operator[](uint index) { return *((float4*)f + index); }

		bool operator==(const mat4& other) const;
		bool operator!=(const mat4& other) const { return !(*this == other); }

		union
		{
			float m[4][4];
			attr_ float f[16];
		};
	};

	export_ struct refl_ struct_ array_ quat : public float4
	{
		typedef float type;
		quat();
		quat(float v);
		quat(float x, float y, float z, float w);
		explicit quat(const float3& euler_angles);
	};

	export_ enum refl_ Clockwise : unsigned int
	{
		CLOCKWISE,
		ANTI_CLOCKWISE
	};
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

	export_ inline bool rect_intersects(const vec4& first, const vec4& second)
	{
		return !(second.x > first.x + first.z || second.y > first.y + first.w || second.x + second.z < first.x || second.y + second.w < first.y);
	}

	export_ struct refl_ MUD_MATH_EXPORT Transform
	{
		attr_ vec3 m_position = Zero3;
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = Unit3;
	};

	Transform average_transforms(array<Transform*> transforms);
}