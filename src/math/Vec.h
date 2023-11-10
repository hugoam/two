//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/base.h>
#endif
#include <math/Axis.h>
#include <math/Forward.h>

#ifndef TWO_MODULES
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif

namespace two
{
	export_ template <class T>
	struct refl_ struct_ array_ v2
	{
		typedef uint length_type;
		typedef T type;
		constr_ CONSTEXPR v2() {}
		constr_ CONSTEXPR explicit v2(T v) : x(v), y(v) {}
		constr_ CONSTEXPR v2(T x, T y) : x(x), y(y) {}
		template <class V>
		explicit v2(V v) : x(T(v.x)), y(T(v.y)) {}
		T operator[](uint index) const { return f[index]; }
		T& operator[](uint index) { return f[index]; }
		T operator[](Axis axis) const { return f[size_t(axis)]; }
		T& operator[](Axis axis) { return f[size_t(axis)]; }
		bool operator==(const v2& other) const { return x == other.x && y == other.y; }
		bool operator!=(const v2& other) const { return x != other.x || y != other.y; }
		union {
			struct { attr_ T x; attr_ T y; };
			T f[2];
		};
	};

	export_ template <class T>
	struct refl_ struct_ array_ v3
	{
		typedef uint length_type;
		typedef T type;
		typedef v2<T> type2;
		constr_ CONSTEXPR v3() {}
		constr_ CONSTEXPR explicit v3(T v) : x(v), y(v), z(v) {}
		constr_ CONSTEXPR v3(T x, T y, T z) : x(x), y(y), z(z) {}
		v3(v2<T> a, T z) : x(a.x), y(a.y), z(z) {}
		template <class V>
		explicit v3(V v) : x(T(v.x)), y(T(v.y)), z(T(v.z)) {}
		T operator[](uint index) const { return f[index]; }
		T& operator[](uint index) { return f[index]; }
		T operator[](Axis axis) const { return f[size_t(axis)]; }
		T& operator[](Axis axis) { return f[size_t(axis)]; }
		bool operator==(const v3& other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const v3& other) const { return x != other.x || y != other.y || z != other.z; }
		union {
			struct { attr_ T x; attr_ T y; attr_ T z; };
			struct { T r; T g; T b; };
			T f[3];
		};
	};

	export_ template <class T>
	struct refl_ struct_ array_ v4
	{
		typedef uint length_type;
		typedef T type;
		typedef v2<T> type2;
		typedef v3<T> type3;
		constr_ CONSTEXPR v4() {}
		constr_ CONSTEXPR explicit v4(T v) : x(v), y(v), z(v), w(v) {}
		constr_ CONSTEXPR v4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		v4(v3<T> a, T w) : x(a.x), y(a.y), z(a.z), w(w) {}
		v4(T x, v3<T> b) : x(x), y(b.x), z(b.y), w(b.z) {}
		v4(v2<T> a, v2<T> b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
		v4(v2<T> a, T z, T w) : x(a.x), y(a.y), z(z), w(w) {}
		v4(T x, T y, v2<T> b) : x(x), y(y), z(b.x), w(b.y) {}
		template <class V>
		explicit v4(V v) : x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w)) {}
		T operator[](uint index) const { return f[index]; }
		T& operator[](uint index) { return f[index]; }
		T operator[](Axis axis) const { return f[size_t(axis)]; }
		T& operator[](Axis axis) { return f[size_t(axis)]; }
		bool operator==(const v4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator!=(const v4& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }
		union {
			struct { attr_ T x; attr_ T y; attr_ T z; attr_ T w; };
			struct { T r; T g; T b; T a; };
			struct { T px; T py; T width; T height; };
			struct { v2<T> pos; v2<T> size; };
			T f[4];
		};
	};

	export_ template <class T> inline CONSTEXPR v2<T> operator-(const v2<T>& a) { return v2<T>(-a.x, -a.y); }
	export_ template <class T> inline CONSTEXPR v3<T> operator-(const v3<T>& a) { return v3<T>(-a.x, -a.y, -a.z); }
	export_ template <class T> inline CONSTEXPR v4<T> operator-(const v4<T>& a) { return v4<T>(-a.x, -a.y, -a.z, -a.w); }

#ifdef TWO_META_GENERATOR
	// extern is not actually necessary, only hiding the implementations + explicit instantiation
	// deactived because of an apparent gcc bug with the inline definition of constructors above not playing well with those extern declarations
	extern template struct refl_ v2<float>;
	extern template struct refl_ v3<float>;
	extern template struct refl_ v4<float>;

	extern template struct refl_ v2<int>;
	extern template struct refl_ v3<int>;
	extern template struct refl_ v4<int>;

	extern template struct refl_ v2<uint>;
	extern template struct refl_ v3<uint>;
	extern template struct refl_ v4<uint>;

	extern template struct refl_ v2<bool>;
	extern template struct refl_ v3<bool>;
	extern template struct refl_ v4<bool>;
#endif

	export_ using half2 = v2<ushort>;
	export_ using half3 = v3<ushort>;

	export_ using float2 = v2<float>;
	export_ using float3 = v3<float>;
	export_ using float4 = v4<float>;

	export_ using int2 = v2<int>;
	export_ using int3 = v3<int>;
	export_ using int4 = v4<int>;

	export_ using uint2 = v2<uint>;
	export_ using uint3 = v3<uint>;
	export_ using uint4 = v4<uint>;

	export_ using bool2 = v2<bool>;
	export_ using bool3 = v3<bool>;
	export_ using bool4 = v4<bool>;

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
		constr_ mat3();
		constr_ mat3(const float3& x, const float3& y, const float3& z);
		constr_ mat3(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8);

		const float3& operator[](uint index) const { return v[index]; }
		float3& operator[](uint index) { return v[index]; }

		union
		{
			float m[3][3];
			float3 v[3];
			attr_ float f[9];
		};
	};

	export_ struct refl_ struct_ array_ mat4
	{
		typedef float type;
		typedef uint length_type;
		constr_ mat4();
		constr_ mat4(const float4& x, const float4& y, const float4& z, const float4& w);
		constr_ mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15);

		const float4& operator[](uint index) const { return v[index]; }
		float4& operator[](uint index) { return v[index]; }

		bool operator==(const mat4& other) const;
		bool operator!=(const mat4& other) const { return !(*this == other); }

		union
		{
			float m[4][4];
			float4 v[4];
			attr_ float f[16];
		};
	};

	export_ struct refl_ struct_ quat : public float4 // array_
	{
		typedef float type;
		constr_ CONSTEXPR quat() : float4() {}
		constr_ CONSTEXPR quat(float x, float y, float z, float w) : float4(x, y, z, w) {}
		constr_ explicit quat(const float3& euler_angles);
	};

	export_ enum refl_ Clockwise : unsigned int
	{
		CLOCKWISE,
		ANTI_CLOCKWISE,
	};
}

namespace two
{
	export_ CONSTEXPR vec3 x3 = { 1.f, 0.f, 0.f };
	export_ CONSTEXPR vec3 y3 = { 0.f, 1.f, 0.f };
	export_ CONSTEXPR vec3 z3 = { 0.f, 0.f, 1.f };

	export_ CONSTEXPR quat ZeroQuat = { 0.f, 0.f, 0.f, 1.f };

	export_ CONSTEXPR vec4 Rect4 = { 0.f, 0.f, 1.f, 1.f };

	export_ inline bool rect_intersects(const vec4& first, const vec4& second)
	{
		return !(second.x > first.x + first.z || second.y > first.y + first.w || second.x + second.z < first.x || second.y + second.w < first.y);
	}

	export_ struct refl_ TWO_MATH_EXPORT Transform
	{
		attr_ vec3 m_position = vec3(0.f);
		attr_ quat m_rotation = ZeroQuat;
		attr_ vec3 m_scale = vec3(1.f);
	};

	Transform average_transforms(span<Transform*> transforms);
}