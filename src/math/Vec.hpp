#pragma once

#include <math/Forward.h>
#include <math/Vec.h>
#include <math/Math.h>
#include <math/Colour.h>

// These are binary-exact approximations of pi/e constants
// http://www.exploringbinary.com/pi-and-e-in-binary/

#define MATH_fPI 3.1415927410125732421875f
#define MATH_dPI 3.141592653589793115997963468544185161590576171875
#define MATH_fE 2.71828174591064453125f
#define MATH_dE 2.718281828459045090795598298427648842334747314453125

namespace two
{
	// Experimental swizzling
	export_ template <class T> inline typename T::type2 xy(const T& v)
	{
		return typename T::type2(v.x, v.y);
	}
	export_ template <class T> inline typename T::type2 xz(const T& v)
	{
		return typename T::type2(v.x, v.z);
	}
	// These alias instead of constructing another variable, allowing modification
	export_ template <class T> inline const typename T::type3& xyz(const T& v)
	{
		return (typename T::type3&)v;
	}
	export_ template <class T> inline typename T::type3& xyz(T& v)
	{
		return (typename T::type3&)v;
	}

	export_ template <class T> inline v2<T> operator+(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x + b.x, a.y + b.y); }
	export_ template <class T> inline v3<T> operator+(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x + b.x, a.y + b.y, a.z + b.z); }
	export_ template <class T> inline v4<T> operator+(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }

	export_ template <class T> inline v2<T> operator+(const v2<T>& a, T b) { return v2<T>(a.x + b, a.y + b); }
	export_ template <class T> inline v3<T> operator+(const v3<T>& a, T b) { return v3<T>(a.x + b, a.y + b, a.z + b); }
	export_ template <class T> inline v4<T> operator+(const v4<T>& a, T b) { return v4<T>(a.x + b, a.y + b, a.z + b, a.w + b); }

	export_ template <class T> inline v2<T> operator-(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x - b.x, a.y - b.y); }
	export_ template <class T> inline v3<T> operator-(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x - b.x, a.y - b.y, a.z - b.z); }
	export_ template <class T> inline v4<T> operator-(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

	export_ template <class T> inline v2<T> operator-(const v2<T>& a, T b) { return v2<T>(a.x - b, a.y - b); }
	export_ template <class T> inline v3<T> operator-(const v3<T>& a, T b) { return v3<T>(a.x - b, a.y - b, a.z - b); }
	export_ template <class T> inline v4<T> operator-(const v4<T>& a, T b) { return v4<T>(a.x - b, a.y - b, a.z - b, a.w - b); }

	export_ template <class T> inline v2<T> operator*(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x * b.x, a.y * b.y); }
	export_ template <class T> inline v3<T> operator*(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x * b.x, a.y * b.y, a.z * b.z); }
	export_ template <class T> inline v4<T> operator*(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	export_ template <class T> inline v2<T> operator*(const v2<T>& a, T b) { return v2<T>(a.x * b, a.y * b); }
	export_ template <class T> inline v3<T> operator*(const v3<T>& a, T b) { return v3<T>(a.x * b, a.y * b, a.z * b); }
	export_ template <class T> inline v4<T> operator*(const v4<T>& a, T b) { return v4<T>(a.x * b, a.y * b, a.z * b, a.w * b); }
	export_ template <class T> inline v4<T> operator*(const v4<T>& a, const v2<T>& b) { return v4<T>(a.x * b.x, a.y * b.y, a.z * b.x, a.w * b.y); }
	export_ template <class T> inline v2<T> operator*(T a, const v2<T>& b) { return v2<T>(a * b.x, a * b.y); }
	export_ template <class T> inline v3<T> operator*(T a, const v3<T>& b) { return v3<T>(a * b.x, a * b.y, a * b.z); }
	export_ template <class T> inline v4<T> operator*(T a, const v4<T>& b) { return v4<T>(a * b.x, a * b.y, a * b.z, a * b.w); }

	export_ template <class T> inline v2<T> operator/(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x / b.x, a.y / b.y); }
	export_ template <class T> inline v3<T> operator/(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x / b.x, a.y / b.y, a.z / b.z); }
	export_ template <class T> inline v4<T> operator/(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	export_ template <class T> inline v2<T> operator/(const v2<T>& a, T b) { return v2<T>(a.x / b, a.y / b); }
	export_ template <class T> inline v3<T> operator/(const v3<T>& a, T b) { return v3<T>(a.x / b, a.y / b, a.z / b); }
	export_ template <class T> inline v4<T> operator/(const v4<T>& a, T b) { return v4<T>(a.x / b, a.y / b, a.z / b, a.w / b); }
	export_ template <class T> inline v4<T> operator/(const v4<T>& a, const v2<T>& b) { return v4<T>(a.x / b.x, a.y / b.y, a.z / b.x, a.w / b.y); }
	export_ template <class T> inline v2<T> operator/(T a, const v2<T>& b) { return v2<T>(a / b.x, a / b.y); }
	export_ template <class T> inline v3<T> operator/(T a, const v3<T>& b) { return v3<T>(a / b.x, a / b.y, a / b.z); }
	export_ template <class T> inline v4<T> operator/(T a, const v4<T>& b) { return v4<T>(a / b.x, a / b.y, a / b.z, a / b.w); }

	export_ template <class T> inline v2<T>& operator+=(v2<T>& a, const v2<T>& b) { a = a + b; return a; }
	export_ template <class T> inline v3<T>& operator+=(v3<T>& a, const v3<T>& b) { a = a + b; return a; }
	export_ template <class T> inline v4<T>& operator+=(v4<T>& a, const v4<T>& b) { a = a + b; return a; }

	export_ template <class T> inline v2<T>& operator-=(v2<T>& a, const v2<T>& b) { a = a - b; return a; }
	export_ template <class T> inline v3<T>& operator-=(v3<T>& a, const v3<T>& b) { a = a - b; return a; }
	export_ template <class T> inline v4<T>& operator-=(v4<T>& a, const v4<T>& b) { a = a - b; return a; }

	export_ template <class T> inline v2<T>& operator*=(v2<T>& a, const v2<T>& b) { a = a * b; return a; }
	export_ template <class T> inline v3<T>& operator*=(v3<T>& a, const v3<T>& b) { a = a * b; return a; }
	export_ template <class T> inline v4<T>& operator*=(v4<T>& a, const v4<T>& b) { a = a * b; return a; }
	export_ template <class T> inline v2<T>& operator*=(v2<T>& a, T b) { a = a * b; return a; }
	export_ template <class T> inline v3<T>& operator*=(v3<T>& a, T b) { a = a * b; return a; }
	export_ template <class T> inline v4<T>& operator*=(v4<T>& a, T b) { a = a * b; return a; }

	export_ template <class T> inline v2<T>& operator/=(v2<T>& a, const v2<T>& b) { a = a / b; return a; }
	export_ template <class T> inline v3<T>& operator/=(v3<T>& a, const v3<T>& b) { a = a / b; return a; }
	export_ template <class T> inline v4<T>& operator/=(v4<T>& a, const v4<T>& b) { a = a / b; return a; }
	export_ template <class T> inline v2<T>& operator/=(v2<T>& a, T b) { a = a / b; return a; }
	export_ template <class T> inline v3<T>& operator/=(v3<T>& a, T b) { a = a / b; return a; }
	export_ template <class T> inline v4<T>& operator/=(v4<T>& a, T b) { a = a / b; return a; }

	export_ template <class T> inline bool all(const v2<T>& v) { return v.x && v.y; }
	export_ template <class T> inline bool all(const v3<T>& v) { return v.x && v.y && v.z; }
	export_ template <class T> inline bool all(const v4<T>& v) { return v.x && v.y && v.z && v.w; }

	export_ template <class T> inline bool any(const v2<T>& v) { return v.x || v.y; }
	export_ template <class T> inline bool any(const v3<T>& v) { return v.x || v.y || v.z; }
	export_ template <class T> inline bool any(const v4<T>& v) { return v.x || v.y || v.z || v.w; }

	export_ template <class T> inline bool2 isinf(const v2<T>& v) { return bool2(isinf(v.x), isinf(v.y)); }
	export_ template <class T> inline bool3 isinf(const v3<T>& v) { return bool3(isinf(v.x), isinf(v.y), isinf(v.z)); }
	export_ template <class T> inline bool4 isinf(const v4<T>& v) { return bool4(isinf(v.x), isinf(v.y), isinf(v.z), isinf(v.w)); }

	export_ template <class T> inline bool2 isnan(const v2<T>& v) { return bool2(isnan(v.x), isnan(v.y)); }
	export_ template <class T> inline bool3 isnan(const v3<T>& v) { return bool3(isnan(v.x), isnan(v.y), isnan(v.z)); }
	export_ template <class T> inline bool4 isnan(const v4<T>& v) { return bool4(isnan(v.x), isnan(v.y), isnan(v.z), isnan(v.w)); }

	export_ template <class T> inline bool2 less(const v2<T>& a, const v2<T>& b) { return bool2(a.x < b.x, a.y < b.y); }
	export_ template <class T> inline bool3 less(const v3<T>& a, const v3<T>& b) { return bool3(a.x < b.x, a.y < b.y, a.z < b.z); }
	export_ template <class T> inline bool4 less(const v4<T>& a, const v4<T>& b) { return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w); }

	export_ template <class T> inline bool2 less_equal(const v2<T>& a, const v2<T>& b) { return bool2(a.x <= b.x, a.y <= b.y); }
	export_ template <class T> inline bool3 less_equal(const v3<T>& a, const v3<T>& b) { return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z); }
	export_ template <class T> inline bool4 less_equal(const v4<T>& a, const v4<T>& b) { return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w); }

	export_ template <class T> inline bool2 greater(const v2<T>& a, const v2<T>& b) { return bool2(a.x > b.x, a.y > b.y); }
	export_ template <class T> inline bool3 greater(const v3<T>& a, const v3<T>& b) { return bool3(a.x > b.x, a.y > b.y, a.z > b.z); }
	export_ template <class T> inline bool4 greater(const v4<T>& a, const v4<T>& b) { return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w); }

	export_ template <class T> inline bool2 greater_equal(const v2<T>& a, const v2<T>& b) { return bool2(a.x >= b.x, a.y >= b.y); }
	export_ template <class T> inline bool3 greater_equal(const v3<T>& a, const v3<T>& b) { return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z); }
	export_ template <class T> inline bool4 greater_equal(const v4<T>& a, const v4<T>& b) { return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w); }

	export_ template <class T> inline bool  equal(const T& a, const T& b, float eps) { return abs(b - a) < eps; }
	export_ template <class T> inline bool2 equal(const v2<T>& a, const v2<T>& b, float eps) { return less(abs(b - a), v2<T>(eps)); }
	export_ template <class T> inline bool3 equal(const v3<T>& a, const v3<T>& b, float eps) { return less(abs(b - a), v3<T>(eps)); }
	export_ template <class T> inline bool4 equal(const v4<T>& a, const v4<T>& b, float eps) { return less(abs(b - a), v4<T>(eps)); }

	export_ template <class T> inline bool2 equal(const v2<T>& a, const v2<T>& b) { return bool2(a.x == b.x, a.y == b.y); }
	export_ template <class T> inline bool3 equal(const v3<T>& a, const v3<T>& b) { return bool3(a.x == b.x, a.y == b.y, a.z == b.z); }
	export_ template <class T> inline bool4 equal(const v4<T>& a, const v4<T>& b) { return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w); }

	export_ template <class T> inline bool2 not_equal(const v2<T>& a, const v2<T>& b) { return bool2(a.x != b.x, a.y != b.y); }
	export_ template <class T> inline bool3 not_equal(const v3<T>& a, const v3<T>& b) { return bool3(a.x != b.x, a.y != b.y, a.z != b.z); }
	export_ template <class T> inline bool4 not_equal(const v4<T>& a, const v4<T>& b) { return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w); }

	//template <class T> inline T     sign(T v) { return T(T(0) < v) - T(v < T(0)); }
	export_ template <class T> inline v2<T> sign(const v2<T>& v) { return T2(less(v2<T>(T(0)), v)) - v2<T>(less(v, v2<T>(T(0)))); }
	export_ template <class T> inline v3<T> sign(const v3<T>& v) { return T3(less(v3<T>(T(0)), v)) - v3<T>(less(v, v3<T>(T(0)))); }
	export_ template <class T> inline v4<T> sign(const v4<T>& v) { return T4(less(v4<T>(T(0)), v)) - v4<T>(less(v, v4<T>(T(0)))); }

	export_ template <class T> inline T dot(const v2<T>& a, const v2<T>& b) { v2<T> tmp = a * b; return tmp.x + tmp.y; }
	export_ template <class T> inline T dot(const v3<T>& a, const v3<T>& b) { v3<T> tmp = a * b; return tmp.x + tmp.y + tmp.z; }
	export_ template <class T> inline T dot(const v4<T>& a, const v4<T>& b) { v4<T> tmp = a * b; return tmp.x + tmp.y + tmp.z + tmp.w; }

	export_ template <class T> v3<T> cross(const v3<T>& a, const v3<T>& b)
	{
		return v3<T>(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y
		);
	}

	export_ template <class T> inline T length(const v2<T>& v) { return T(sqrt(dot(v, v))); }
	export_ template <class T> inline T length(const v3<T>& v) { return T(sqrt(dot(v, v))); }
	export_ template <class T> inline T length(const v4<T>& v) { return T(sqrt(dot(v, v))); }

	export_ template <class T> inline T length2(const v2<T>& v) { return dot(v, v); }
	export_ template <class T> inline T length2(const v3<T>& v) { return dot(v, v); }
	export_ template <class T> inline T length2(const v4<T>& v) { return dot(v, v); }

	export_ template <class T> inline T distance(const v2<T>& a, const v2<T>& b) { return length(b - a); }
	export_ template <class T> inline T distance(const v3<T>& a, const v3<T>& b) { return length(b - a); }
	export_ template <class T> inline T distance(const v4<T>& a, const v4<T>& b) { return length(b - a); }

	export_ template <class T> inline T distance2(const v2<T>& a, const v2<T>& b) { return length2(b - a); }
	export_ template <class T> inline T distance2(const v3<T>& a, const v3<T>& b) { return length2(b - a); }
	export_ template <class T> inline T distance2(const v4<T>& a, const v4<T>& b) { return length2(b - a); }

	export_ template <class T> inline v2<T> normalize(const v2<T>& v) { return v * T(1) / T(sqrt(dot(v, v))); }
	export_ template <class T> inline v3<T> normalize(const v3<T>& v) { return v * T(1) / T(sqrt(dot(v, v))); }
	export_ template <class T> inline v4<T> normalize(const v4<T>& v) { return v * T(1) / T(sqrt(dot(v, v))); }

	export_ template <class T> inline v2<T> abs(const v2<T>& v) { return v2<T>(abs(v.x), abs(v.y)); }
	export_ template <class T> inline v3<T> abs(const v3<T>& v) { return v3<T>(abs(v.x), abs(v.y), abs(v.z)); }
	export_ template <class T> inline v4<T> abs(const v4<T>& v) { return v4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w)); }

	export_ template <class T> inline v2<T> mod(const v2<T>& a, const v2<T>& b) { return v2<T>(fmod(a.x, b.x), fmod(a.y, b.y)); }
	export_ template <class T> inline v3<T> mod(const v3<T>& a, const v3<T>& b) { return v3<T>(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z)); }
	export_ template <class T> inline v4<T> mod(const v4<T>& a, const v4<T>& b) { return v4<T>(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z), fmod(a.w, b.w)); }

	export_ template <class T> inline T     imod(const T& a, const T& b) { return a % b; }
	export_ template <class T> inline v2<T> imod(const v2<T>& a, const v2<T>& b) { return v2<T>(a.x % b.x, a.y % b.y); }
	export_ template <class T> inline v3<T> imod(const v3<T>& a, const v3<T>& b) { return v3<T>(a.x % b.x, a.y % b.y, a.z % b.z); }
	export_ template <class T> inline v4<T> imod(const v4<T>& a, const v4<T>& b) { return v4<T>(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w); }

	export_ template <class T> inline v2<T> min(const v2<T>& a, const v2<T>& b) { return v2<T>(min(a.x, b.x), min(a.y, b.y)); }
	export_ template <class T> inline v3<T> min(const v3<T>& a, const v3<T>& b) { return v3<T>(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)); }
	export_ template <class T> inline v4<T> min(const v4<T>& a, const v4<T>& b) { return v4<T>(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); }
	export_ template <class T> inline v2<T> min(const v2<T>& a, T b) { return v2<T>(min(a.x, b), min(a.y, b)); }
	export_ template <class T> inline v3<T> min(const v3<T>& a, T b) { return v3<T>(min(a.x, b), min(a.y, b), min(a.z, b)); }
	export_ template <class T> inline v4<T> min(const v4<T>& a, T b) { return v4<T>(min(a.x, b), min(a.y, b), min(a.z, b), min(a.w, b)); }

	export_ template <class T> inline v2<T> max(const v2<T>& a, const v2<T>& b) { return v2<T>(max(a.x, b.x), max(a.y, b.y)); }
	export_ template <class T> inline v3<T> max(const v3<T>& a, const v3<T>& b) { return v3<T>(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)); }
	export_ template <class T> inline v4<T> max(const v4<T>& a, const v4<T>& b) { return v4<T>(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); }
	export_ template <class T> inline v2<T> max(const v2<T>& a, T b) { return v2<T>(max(a.x, b), max(a.y, b)); }
	export_ template <class T> inline v3<T> max(const v3<T>& a, T b) { return v3<T>(max(a.x, b), max(a.y, b), max(a.z, b)); }
	export_ template <class T> inline v4<T> max(const v4<T>& a, T b) { return v4<T>(max(a.x, b), max(a.y, b), max(a.z, b), max(a.w, b)); }

	export_ template <class T> inline v2<T> clamp(const v2<T>& v, T lo, T hi) { return min(max(v, lo), hi); }
	export_ template <class T> inline v3<T> clamp(const v3<T>& v, T lo, T hi) { return min(max(v, lo), hi); }
	export_ template <class T> inline v4<T> clamp(const v4<T>& v, T lo, T hi) { return min(max(v, lo), hi); }

	export_ template <class T> inline v2<T> clamp(const v2<T>& v, const v2<T>& lo, const v2<T>& hi) { return min(max(v, lo), hi); }
	export_ template <class T> inline v3<T> clamp(const v3<T>& v, const v3<T>& lo, const v3<T>& hi) { return min(max(v, lo), hi); }
	export_ template <class T> inline v4<T> clamp(const v4<T>& v, const v4<T>& lo, const v4<T>& hi) { return min(max(v, lo), hi); }

	export_ template <class T> inline T     saturate(T v) { return clamp(v, T(0), T(1)); }
	export_ template <class T> inline v2<T> saturate(const v2<T>& v) { return clamp(v, T(0), T(1)); }
	export_ template <class T> inline v3<T> saturate(const v3<T>& v) { return clamp(v, T(0), T(1)); }
	export_ template <class T> inline v4<T> saturate(const v4<T>& v) { return clamp(v, T(0), T(1)); }

	export_ template <class T> inline v2<T> floor(const v2<T>& v) { return v2<T>(floor(v.x), floor(v.y)); }
	export_ template <class T> inline v3<T> floor(const v3<T>& v) { return v3<T>(floor(v.x), floor(v.y), floor(v.z)); }
	export_ template <class T> inline v4<T> floor(const v4<T>& v) { return v4<T>(floor(v.x), floor(v.y), floor(v.z), floor(v.w)); }

	export_ template <class T> inline v2<T> ceil(const v2<T>& v) { return v2<T>(ceil(v.x), ceil(v.y)); }
	export_ template <class T> inline v3<T> ceil(const v3<T>& v) { return v3<T>(ceil(v.x), ceil(v.y), ceil(v.z)); }
	export_ template <class T> inline v4<T> ceil(const v4<T>& v) { return v4<T>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)); }

	export_ template <class T> inline v2<T> pow(const v2<T>& a, const v2<T>& b) { return v2<T>(pow(a.x, b.x), pow(a.y, b.y)); }
	export_ template <class T> inline v3<T> pow(const v3<T>& a, const v3<T>& b) { return v3<T>(pow(a.x, b.x), pow(a.y, b.y), pow(a.z, b.z)); }
	export_ template <class T> inline v4<T> pow(const v4<T>& a, const v4<T>& b) { return v4<T>(pow(a.x, b.x), pow(a.y, b.y), pow(a.z, b.z), pow(a.w, b.w)); }

	export_ template <class T> inline v2<T> cos(const v2<T>& v) { return v2<T>(cos(v.x), cos(v.y)); }
	export_ template <class T> inline v3<T> cos(const v3<T>& v) { return v3<T>(cos(v.x), cos(v.y), cos(v.z)); }
	export_ template <class T> inline v4<T> cos(const v4<T>& v) { return v4<T>(cos(v.x), cos(v.y), cos(v.z), cos(v.w)); }

	export_ template <class T> inline v2<T> sin(const v2<T>& v) { return v2<T>(sin(v.x), sin(v.y)); }
	export_ template <class T> inline v3<T> sin(const v3<T>& v) { return v3<T>(sin(v.x), sin(v.y), sin(v.z)); }
	export_ template <class T> inline v4<T> sin(const v4<T>& v) { return v4<T>(sin(v.x), sin(v.y), sin(v.z), sin(v.w)); }

	// lerp
	export_ template <class T> inline T     lerp(T a, T b, float t) { return T(a + t * (b - a)); }
	export_ template <class T> inline v2<T> lerp(const v2<T>& a, const v2<T>& b, float t) { return v2<T>(a) + t * v2<T>(b - a); }
	export_ template <class T> inline v3<T> lerp(const v3<T>& a, const v3<T>& b, float t) { return v3<T>(a) + t * v3<T>(b - a); }
	export_ template <class T> inline v4<T> lerp(const v4<T>& a, const v4<T>& b, float t) { return v4<T>(a) + t * v4<T>(b - a); }

	export_ template <class T> T     spline(T a, T b, T c, T d, T t);
	export_ template <class T> v2<T> spline(const v2<T>& a, const v2<T>& b, const v2<T>& c, const v2<T>& d, T t);
	export_ template <class T> v3<T> spline(const v3<T>& a, const v3<T>& b, const v3<T>& c, const v3<T>& d, T t);
	export_ template <class T> v4<T> spline(const v4<T>& a, const v4<T>& b, const v4<T>& c, const v4<T>& d, T t);

	export_ template <class T> inline T angle(T a, T b) { return acos(clamp(a * b, T(-1), T(1))); }
	export_ template <class T> inline T angle(const v2<T>& a, const v2<T>& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }
	export_ template <class T> inline T angle(const v3<T>& a, const v3<T>& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }
	export_ template <class T> inline T angle(const v4<T>& a, const v4<T>& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }

	inline mat3::mat3() {}
	inline mat3::mat3(const float3& x, const float3& y, const float3& z)
	{
		f[0] = x.x; f[1] = x.y; f[2] = x.z;
		f[3] = y.x; f[4] = y.y; f[5] = y.z;
		f[6] = z.x; f[7] = z.y; f[8] = z.z;
	}
	inline mat3::mat3(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8)
	{
		f[0] = f0; f[1] = f1; f[2] = f2;
		f[3] = f3; f[4] = f4; f[5] = f5;
		f[6] = f6; f[7] = f7; f[8] = f8;
	}

	//inline const float3& mat3::operator[](uint index) const { return *((float3*)f + index); }
	//inline float3& mat3::operator[](uint index) { return *((float3*)f + index); }

	inline mat4::mat4() : f{} {}
	inline mat4::mat4(const float4& x, const float4& y, const float4& z, const float4& w)
	{
		f[0] = x.x; f[1] = x.y; f[2] = x.z; f[3] = x.w;
		f[4] = y.x; f[5] = y.y; f[6] = y.z; f[7] = y.w;
		f[8] = z.x; f[9] = z.y; f[10] = z.z; f[11] = z.w;
		f[12] = w.x; f[13] = w.y; f[14] = w.z; f[15] = w.w;
	}
	inline mat4::mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15)
	{
		f[0] = f0;  f[1] = f1;  f[2] = f2;  f[3] = f3;
		f[4] = f4;  f[5] = f5;  f[6] = f6;  f[7] = f7;
		f[8] = f8;  f[9] = f9;  f[10] = f10; f[11] = f11;
		f[12] = f12; f[13] = f13; f[14] = f14; f[15] = f15;
	}

	//inline const float4& mat4::operator[](uint index) const { return *((float4*)f + index); }
	//inline float4& mat4::operator[](uint index) { return *((float4*)f + index); }

	inline bool mat4::operator==(const mat4& other) const
	{
		return f[0] == other.f[0] && f[1] == other.f[1] && f[2] == other.f[2] && f[3] == other.f[3]
			&& f[4] == other.f[4] && f[5] == other.f[5] && f[6] == other.f[6] && f[7] == other.f[7]
			&& f[8] == other.f[8] && f[9] == other.f[9] && f[10] == other.f[10] && f[11] == other.f[11]
			&& f[12] == other.f[12] && f[13] == other.f[13] && f[14] == other.f[14] && f[15] == other.f[15];
	}

	//inline bool mat4::operator!=(const mat4& other) const { return !(*this == other); }

	inline quat::quat(const float3& euler_angles)
	{
		float3 c = cos(euler_angles * float(0.5));
		float3 s = sin(euler_angles * float(0.5));

		this->x = s.x * c.y * c.z - c.x * s.y * s.z;
		this->y = c.x * s.y * c.z + s.x * c.y * s.z;
		this->z = c.x * c.y * s.z - s.x * s.y * c.z;
		this->w = c.x * c.y * c.z + s.x * s.y * s.z;
	}

	export_ template <> inline float* value_ptr(mat4& m) { return &m[0][0]; }
	export_ template <> inline const float* value_ptr(const mat4& m) { return &m.f[0]; }
	export_ template <> inline float* value_ptr(quat& q) { return &q[0]; }

	export_ inline bool operator<(const uvec2& lhs, const uvec2& rhs) { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }
	export_ inline bool operator<(const ivec2& lhs, const ivec2& rhs) { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }

	export_ inline vec3 to_xz(const vec2& vec) { return{ vec.x, 0.f, vec.y }; }
	export_ inline vec2 to_xz(const vec3& vec) { return{ vec.x, vec.z }; }
	export_ inline ivec3 to_xz(const ivec2& vec) { return{ vec.x, 0, vec.y }; }
	export_ inline ivec2 to_xz(const ivec3& vec) { return{ vec.x, vec.z }; }

	export_ template <class T> inline v2<T> rect_sum(const v4<T>& rect) { return rect.pos + rect.size; }
	export_ template <class T> inline v2<T> rect_center(const v4<T>& rect) { return rect.pos + rect.size / T(2); }

	export_ inline vec3 to_vec3(const Colour& colour) { return { colour.r, colour.g, colour.b }; }
	export_ inline vec4 to_vec4(const Colour& colour) { return { colour.r, colour.g, colour.b, colour.a }; }
	export_ inline Colour to_colour(const vec3& vec) { return { vec.x, vec.y, vec.z }; }
	export_ inline Colour to_colour(const vec4& vec) { return { vec.x, vec.y, vec.z, vec.w }; }

	export_ TWO_MATH_EXPORT uint32_t pack4(const vec4& vec);
	export_ TWO_MATH_EXPORT uint32_t pack3(const vec3& vec);
	export_ TWO_MATH_EXPORT vec3 unpack3(uint32_t vec);
	export_ TWO_MATH_EXPORT vec4 unpack4(uint32_t vec);

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

#ifndef TWO_META_GENERATOR
	export_ template TWO_MATH_EXPORT func_ vec3 add<vec3>(vec3 a, vec3 b);
	export_ template TWO_MATH_EXPORT func_ vec3 subtract<vec3>(vec3 a, vec3 b);
	export_ template TWO_MATH_EXPORT func_ vec3 multiply<vec3>(vec3 a, vec3 b);
	export_ template TWO_MATH_EXPORT func_ vec3 divide<vec3>(vec3 a, vec3 b);
#else
	template <> func_ vec3 add<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 subtract<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 multiply<vec3>(vec3 a, vec3 b);
	template <> func_ vec3 divide<vec3>(vec3 a, vec3 b);
#endif

	export_ TWO_MATH_EXPORT quat operator*(const quat& a, const quat& b);
	//export_ TWO_MATH_EXPORT quat operator/(const quat& a, const quat& b);
	export_ TWO_MATH_EXPORT quat operator+(const quat& a, const quat& b);
	export_ TWO_MATH_EXPORT quat operator-(const quat& a, const quat& b);

	export_ TWO_MATH_EXPORT quat operator*(const quat& a, float s);
	export_ TWO_MATH_EXPORT quat operator/(const quat& a, float s);
	export_ TWO_MATH_EXPORT quat operator*(float s, const quat& a);
	export_ TWO_MATH_EXPORT quat operator/(float s, const quat& a);

	export_ TWO_MATH_EXPORT quat operator+(const quat& v);
	export_ TWO_MATH_EXPORT quat operator-(const quat& v);

	// transform position
	export_ TWO_MATH_EXPORT float3 operator*(const quat& q, const float3& v);
	export_ TWO_MATH_EXPORT float4 operator*(const quat& q, const float4& v);

	export_ TWO_MATH_EXPORT quat conjugate(const quat& q);
	export_ TWO_MATH_EXPORT quat inverse(const quat& q);
	export_ TWO_MATH_EXPORT quat negate(const quat& q);

	export_ TWO_MATH_EXPORT float dot(const quat& a, const quat& b);
	export_ TWO_MATH_EXPORT quat normalize(const quat& q);

	export_ TWO_MATH_EXPORT quat lerp(const quat& a, const quat& b, float t);
	export_ TWO_MATH_EXPORT quat slerp(const quat& a, const quat& b, float t);

	//quat qZero();
	//quat qIdentity();
	//float qNorm(const quat& q);
	//quat qScale(const quat& q, float scale);
	//quat qMultiply(const quat& a, const quat& b);
	//quat qMultiplyPure(const quat& a, const float3& b);
	//quat qRotationBetween(float3 v0, float3 v1);

	export_ inline float3 rotate(const quat& q, const float3& v) { return q * v; }

	export_ inline quat axis_angle(const float3& v, float a)
	{
		const float s = sin(a * float(0.5));
		return quat(v.x * s, v.y * s, v.z * s, cos(a * float(0.5)));
	}

	export_ inline quat angle_axis(float a, const float3& v) { return axis_angle(v, a); }
	export_ inline quat rotate(const quat& q, float a, const float3& v) { return q * angle_axis(a, v); }
	export_ inline quat rotate(const quat& q, const float3& v, float a) { return q * axis_angle(v, a); }

	export_ inline float2 rotate(const float2& v, float a)
	{
		const float c = cos(a);
		const float s = sin(a);
		return float2(v.x * c - v.y * s, v.x * s + v.y * c);
	}

	export_ TWO_MATH_EXPORT float oriented_angle(const float3& a, const float3& b, const float3& ref);
	export_ TWO_MATH_EXPORT float oriented_angle(const float2& a, const float2& b);
	export_ inline float oriented_angle_2d(const float2& a, const float2& b) { return oriented_angle(a, b); }

	export_ TWO_MATH_EXPORT mat4 inverse(const mat4& m);
	export_ TWO_MATH_EXPORT mat4 transpose(const mat4& m);
	export_ TWO_MATH_EXPORT mat4 operator*(const mat4& m0, const mat4& m1);
	export_ TWO_MATH_EXPORT float4 operator*(const mat4& m, const float4& v);

	export_ inline vec3 reflect(const vec3& i, const vec3& n) { return i - 2.f * dot(n, i) * n; };

	export_ inline vec3 rotate(const vec3& v, float angle, const vec3& axis) { return angle_axis(angle, axis) * v; }
	export_ inline vec3 rotate(const vec3& v, const vec3& axis, float angle) { return angle_axis(angle, axis) * v; }

	export_ TWO_MATH_EXPORT func_ quat look_dir(const vec3& direction, const vec3& forward = -z3);
	export_ TWO_MATH_EXPORT func_ quat look_at(const vec3& eye, const vec3& target, const vec3& forward = -z3);

	export_ TWO_MATH_EXPORT Axis nearest_axis(const vec3& direction);

	export_ TWO_MATH_EXPORT float shortest_angle(float a, float b);
	export_ TWO_MATH_EXPORT float trigo_angle(const vec3& a, const vec3& b);
	export_ TWO_MATH_EXPORT float shortest_angle(const vec3& a, const vec3& b);

	export_ TWO_MATH_EXPORT void orthonormalize(const mat4& transform, vec3& x, vec3& y, vec3& z);
	export_ TWO_MATH_EXPORT mat4 orthonormalize(const mat4& transform);
	export_ TWO_MATH_EXPORT mat4 bias_mat();
	export_ TWO_MATH_EXPORT mat4 bias_mat_bgfx(bool origin_bottom_left, bool homogeneous_depth);
	export_ TWO_MATH_EXPORT mat4 rect_mat(vec4 rect);

	export_ TWO_MATH_EXPORT mat4 abs(const mat4& mat);

	export_ inline vec3 mulp(const mat4& mat, const vec3& p) { return vec3(mat * vec4(p, 1.f)); }
	export_ inline vec3 mult(const mat4& mat, const vec3& n) { return vec3(mat * vec4(n, 0.f)); }
	export_ inline vec3 muln(const mat4& mat, const vec3& n) { return normalize(vec3(mat * vec4(n, 0.f))); }
	//export_ inline vec3 muln(const mat4& mat, const vec3& n) { return vec3(normalize(mat * vec4(n, 0.f))); }
	export_ inline vec4 mult(const mat4& mat, const vec4& t) { return vec4(vec3(mat * vec4(vec3(t), 0.f)), t.w); }

	export_ inline quat facing(const vec3& direction)
	{
		float angle = atan2(direction.x, direction.z);
		return { cosf(angle / 2.f), 0.f, sinf(angle / 2.f), 0.f };
	}

	export_ inline mat4 rotation(const mat4& mat)
	{
		mat4 result = mat;
		result[3] = vec4(0.f, 0.f, 0.f, 1.f);
		return result;
	}


#if 0 // not implemented
	// For float->float16 conversion
	half float_to_half(float f);
	float half_to_float(const half& h);

	// Uniform distribution mapping functions
	float3 UniformUVToSphere(const float2& uv, float r);
	float3 UniformUVToHemisphere(const float2& uv);
	float3 UniformUVToHemisphere(const float2& uv, float max_theta);
	float3 UniformUVToHemisphereCosine(const float2& uv);
	float3 UniformUVToHemisphereCosine(const float2& uv, float max_theta);

	// Signed distance functions
	// TODO: Move for use in HLSL
	float sdSphere(const float3& p, float r);
	float sdCylinder(const float3& p, const float2& h);
	float sdBox(const float3& p, const float3& b);
	float sdCapsule(const float3& p, const float3& a, const float3& b, float r);
	float sdEllipsoid(const float3& p, const float3& r);
	float sdUnion(float a, float b);
	float sdSubtract(float a, float b0);
	float sdIntersect(float a, float b);
	float sdSmoothUnion(float a, float b, float k);

//
// Vector conversion functions
//
float3 double3_to_float3(const double3& v);
double3 float3_to_double3(const float3& v);


/*$pycgen
	code = """
	T coserp_t(T t);
	T2 coserp_t(const T2& t);
	T3 coserp_t(const T3& t);
	T4 coserp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float coserp_t(float t);
	float2 coserp_t(const float2& t);
	float3 coserp_t(const float3& t);
	float4 coserp_t(const float4& t);
//$pycgen-end


/*$pycgen
	code = """
	T cuberp_t(T t);
	T2 cuberp_t(const T2& t);
	T3 cuberp_t(const T3& t);
	T4 cuberp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float cuberp_t(float t);
	float2 cuberp_t(const float2& t);
	float3 cuberp_t(const float3& t);
	float4 cuberp_t(const float4& t);
//$pycgen-end


/*$pycgen
	code = """
	T quinterp_t(T t);
	T2 quinterp_t(const T2& t);
	T3 quinterp_t(const T3& t);
	T4 quinterp_t(const T4& t);
	"""
	EmitRepl(code, "T:float")
*/
//$pycgen-begin
	float quinterp_t(float t);
	float2 quinterp_t(const float2& t);
	float3 quinterp_t(const float3& t);
	float4 quinterp_t(const float4& t);
//$pycgen-end


	//
	// Single precision dual quaternion
	//
	export_ struct refl_ struct_ array_ dualquat
	{
		quat r;
		quat d;
	};


	//
	// This is an affine frame with origin and basis as rotation operator
	//
	export_ struct refl_ struct_ array_ frame
	{
		quat rotation;
		float3 position;
	};
	export_ struct refl_ struct_ array_ framed
	{
		quat rotation;
		double3 position;
	};

	//
	// Scalar math
	//
	float2 SinCos(float angle);
	float DegreesToRadians(float degrees);
	double DegreesToRadians(double degrees);
	float RadiansToDegrees(float radians);
	double RadiansToDegrees(double radians);
	uint Factorial(uint v);


	//
	// Procedural operations on vectors
	//
	float3	vSlerp(const float3& a, const float3& b, float t);
	float3 	vPerpendicular(const float3& v);
	double3	vPerpendicular(const double3& v);
	bool 	vEquals(const int3& a, const int3& b, float epsilon = 0);
	float3	vProjectOnto(const float3& a, const float3& b);
	double3	vMapCubeToSphere(const double3& v);
	double3	vMapNonUnitCubeToSphere(const double3& v, double extents);
	float3	vFraction(const float3& v);
	double3	vFraction(const double3& v);
	void	vOrthogonalise(const float3& a, float3& b, float3& c);


	//
	// Matrix generation functions
	//
	mat3 m3Zero();
	mat4 m4Zero();
	mat3 m3Identity();
	mat4 m4Identity();
	mat3 m3RotateX(float angle);
	mat4 m4RotateX(float angle);
	mat3 m3RotateY(float angle);
	mat4 m4RotateY(float angle);
	mat3 m3RotateZ(float angle);
	mat4 m4RotateZ(float angle);
	mat3 m3Scale(float x, float y, float z);
	mat3 m3Scale(const float3& s);
	mat3 m3Direction(const float3& z);
	mat3 m3Direction(const float3& z, float3 y);
	mat4 m4Translate(float x, float y, float z);
	mat4 m4Translate(const float3& v);
	mat4 m4PerspectiveFovLH(float fov_y, float aspect_ratio, float near_z, float far_z);
	mat4 m4PerspectiveFovOffCenterLH(float fov_y, float aspect_ratio, const float4& rect, float near_z, float far_z);
	mat3 m3Up(const double3& y);
	mat3d m3dZero();
	mat3d m3dIdentity();


	//
	// Matrix conversion functions
	//
	mat3 mat4_to_mat3(const mat4& m4);
	mat4 mat3_to_mat4(const mat3& m3);
	mat3 mat3d_to_mat3(const mat3d& m3d);
	mat3d mat3_to_mat3d(const mat3& m3);


	//
	// Procedural operations on matrices
	// Disabled in HLSL for now as it's easy to mess up during porting
	//
	mat3 m3Multiply(const mat3& a, const mat3& b);
	mat4 m4Multiply(const mat4& a, const mat4& b);
	mat3d m3dMultiply(const mat3d& a, const mat3d& b);
	float m3Determinant(const mat3& m);
	float m4Determinant(const mat4& m);
	bool m3Inverse(const mat3& m, mat3& inv_m);
	bool m4Inverse(const mat4& m, mat4& inv_m);
	mat3 m3Transpose(const mat3& m);
	mat4 m4Transpose(const mat4& m);
	mat3 m3Orthogonalise(const mat3& m, int axis);
	mat3 m3Orthonormalise(const mat3& m, int axis);
	float3 m3Transform(const mat3& m, const float3& v);
	double3 m3Transform(const mat3& m, const double3& v);
	float4 m4Transform(const mat4& m, const float4& v);
	float3 m3TransformTransposed(const mat3& m, const float3& v);
	double3 m3TransformTransposed(const mat3& m, const double3& v);
	float3 m4TransformPos(const mat4& m, const float3& v);
	double3 m4TransformPos(const mat4& m, const double3& v);
	float3 m4TransformDir(const mat4& m, const float3& v);
	bool m3ToEulerXYZ(const mat3& m, float3& angles);
	bool m3ToEulerYXZ(const mat3& m, float3& angles);
	bool m3ToEulerZXY(const mat3& m, float3& angles);
	bool m3ToEulerZYX(const mat3& m, float3& angles);
	void m3dDiagonalise(const mat3d& m, mat3d& Q, mat3d& D);




	//
	// Quaternion conversion functions
	//
	mat3 quat_to_mat3(const quat& q);
	mat4 quat_to_mat4(const quat& q);
	quat mat3_to_quat(const mat3& m);


	//
	// Dual quaternion generation functions
	//
	dualquat dqIdentity();


	//
	// Frame functions
	//
	frame fIdentity();
	framed fdIdentity();
	frame fPosition(const float3& position);
	framed fdPosition(const double3& position);
	frame fPositionRotation(const float3& position, const quat& rotation);
	framed fdPositionRotation(const double3& position, const quat& rotation);
	frame fInverse(const frame& f);
	framed fInverse(const framed& f);
	frame fMultiply(const frame& a, const frame& b);
	framed fMultiply(const framed& a, const framed& b);
	frame fLerp(const frame& a, const frame& b, float t);
	float3 fTransformPos(const frame& f, const float3& v);
	double3 fTransformPos(const framed& f, const double3& v);


	//
	// Frame conversion functions
	//
	frame framed_to_frame(const framed& f);

	//
	// Rigid transform with position stored in double precision
	//
	export_ struct refl_ struct_ array_ transform
	{
		double3 position;
		mat3 rotation;
		float3 scale;
	};


	export_ struct refl_ struct_ array_ boxi
	{
		int3 min;
		int3 max;
	};


	//
	// A plane in 3 dimensions, composed of a normal and distance along the normal from the origin
	//
	export_ struct refl_ struct_ array_ planef
	{
		planef() { }
		planef(float x, float y, float z, float d)
			: n(x, y, z), d(d)
		{
		}
		planef(const float3& n, float d)
			: n(n), d(d)
		{
		}
		float3 n;
		float d;
	};
	export_ struct refl_ struct_ array_ planed
	{
		planed() { }
		planed(double x, double y, double z, double d)
			: n(x, y, z), d(d)
		{
		}
		planed(const double3& n, double d)
			: n(n), d(d)
		{
		}
		double3 n;
		double d;
	};


	//
	// A camera view volume bounded by 6 planes
	//
	export_ struct refl_ struct_ array_ frustumf
	{
		planef planes[6];
	};
	export_ struct refl_ struct_ array_ frustumd
	{
		planed planes[6];
	};


	
	//
	// Shared location for voxel type that all subsystems can reference
	// TODO: This is probably not the ideal place for this but it's better than in
	//       the VDB or Transvoxel libraries.
	//
	export_ struct refl_ struct_ array_ Voxel
	{
		// Fixed-point compressed distance to zero-surface
		i16 distance;

		// Material ID for this voxel
		u16 material_id;
	};


	//
	// Mutually exclusive flags for storing normal voxels in voxel grids
	//
	export_ enum refl_ struct_ array_ VoxelGridFlags
	{
		VoxelGridFlags_NoNormals = 0,
		VoxelGridFlags_StoreNormals = 1,
	};


	//
	// Describes the layout of a collection of voxels and cells constructed out of them.
	// There are equal number of cells/voxels on each axis.
	// The number of voxels is determined by the number of cells and whether an extra padding
	// layer of voxels is added round the outside for normal calculation.
	//
	export_ struct refl_ struct_ array_ VoxelGrid
	{
		VoxelGrid();
		VoxelGrid(i32 nb_cells_axis, VoxelGridFlags flags);

		// Cell count
		i32 nb_cells_axis;
		i32 nb_cells_axis_2;
		i32 nb_cells;
		i32 max_cell_index;

		// Flags about normal storage
		u32 stores_normals;

		// Voxel count - 1 extra voxel to cover last cell corner, 2 extra voxels for normal sampling either side
		i32 nb_voxels_axis;
		i32 nb_voxels_axis_2;
		i32 nb_voxels;
	};



	//
	// A unique node ID within a grid hierarchy stored as a 96-bit value.
	// Node x,y,z and level integer locations are bit-packed into this.
	//
	export_ struct refl_ struct_ array_ NodeID
	{
		NodeID();
		NodeID(const int3& node_index, int level_index);

		// Recalculate 3D index from the ID
		int3 Index() const;

		// Extract level index
		u32 Level() const;

		// Calculate a well-distributed hash from the ID
		u32 Hash() const;

		bool operator==(const NodeID& rhs) const;
		bool operator!=(const NodeID& rhs) const;

		u32 v[3];
	};


	struct BoxIterator
	{
		BoxIterator(const boxi& range)
			: range(range)
		{
			// Clamp any negative deltas to zero before calculating volume
			// Also add 1 to make the max inclusive
			delta = max(range.max - range.min + 1, 0);

			slice_size = delta.x * delta.y;
			size = slice_size * delta.z;
		}
		
		void GetPos(int i, int3& pos) const
		{
			// Calculate position within the range delta
			pos.z = i / slice_size;
			i -= pos.z * slice_size;
			pos.y = i / delta.x;
			pos.x = i - pos.y * delta.x;

			// Offset that to get the actual position
			pos.x += range.min.x;
			pos.y += range.min.y;
			pos.z += range.min.z;
		}

		const boxi& range;
		int3 delta;
		i32 slice_size;
		i32 size;
	};


	//
	// Transform functions
	//
	transform tZero();
	transform tIdentity();
	transform tPosition(const double3& position);
	transform tPositionRotation(const double3& position, const mat3& rotation);
	mat4 tToMat4(const transform& t);
	mat4 tToMat4Rigid(const transform& t);
	double3 tTransformPos(const transform& t, const double3& v);
	transform tMultiplyRigid(const transform& a, const transform& b);


	//
	// Box functions
	//
	boxi biScale(const boxi& box, i32 scale);
	boxi biInvScale(const boxi& box, i32 inv_scale);
	boxi biUnion(const boxi& a, const boxi& b);
	boxi biIntersection(const boxi& a, const boxi& b);
	bool biIntersects(const boxi& a, const boxi& b);
	i32 biVolume(const boxi& b);


	//
	// Plane generation functions
	//
	planef pPositionNormal(const float3& position, const float3& normal);
	planed pPositionNormal(const double3& position, const double3& normal);
	planef pTriangle(const float3& a, const float3& b, const float3& c);
	planed pTriangle(const double3& a, const double3& b, const double3& c);


	//
	// Procedural operations with planes
	//
	float pDistanceFrom(const planef& p, const float3& v);
	double pDistanceFrom(const planed& p, const double3& v);
	float pDistanceFrom(const planef& p, const float3& pos, const float3& extents);
	double pDistanceFrom(const planed& p, const double3& pos, const double3& extents);
	float3 pProjectVector(const planef& p, const float3& v);
	double3 pProjectVector(const planed& p, const double3& v);
	planef pNormalise(const planef& p);
	planed pNormalise(const planed& p);
	planef pTransform(const planef& p, const mat4& m);
	planed pTransform(const planed& p, const mat4& m);
	planef pTranslate(const planef& p, const float3& v);
	planed pTranslate(const planed& p, const double3& v);
	float3 pIntersectionPoint(const planef& a, const planef& b, const planef& c);
	double3 pIntersectionPoint(const planed& a, const planed& b, const planed& c);
	bool pIntersectionPoint(const planef& a, const planef& b, const planef& c, float3& Q);
	bool pIntersectionPoint(const planed& a, const planed& b, const planed& c, double3& Q);
	bool pIntersectionLine(const planef& a, const planef& b, float3& Q, float3& V);
	bool pIntersectionLine(const planed& a, const planed& b, double3& Q, double3& V);


	// Frustum functions
	frustumf frustumfMake(const mat4& m);
	frustumd frustumdMake(const mat4& m);
	frustumf frustumTransform(const frustumf& f, const mat4& m);
	frustumd frustumTransform(const frustumd& f, const mat4& m);
	frustumf frustumTranslate(const frustumf& f, const float3& v);
	frustumd frustumTranslate(const frustumd& f, const double3& v);
	bool frustumContains(const frustumf& f, const float3& pos, const float3& extents);
	bool frustumContains(const frustumd& f, const double3& pos, const double3& extents);
#endif
}

#if 0 // TWO_NOT_IMPLEMENTED
#include <stl/vector.h>

namespace two
{
	//
	// Some utility functions
	//
	float QuadAreaApproximateSphereProjectionSize(const float3& pos, float radius, const mat4& w2c, const mat4& c2s, float near_z);
	double SphereAngularProjectionOntoPosition(const double3& sphere_pos, double radius, const double3& position);
	void MakeHammersleyPoints(u32 nb_points, vector<float4>& points);
	i16 Compress_DoubleToSigned16(double d, double extents);
	double Decompress_Signed16ToDouble(i16 d, double extents);
}
#endif
