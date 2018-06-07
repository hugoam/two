#pragma once

#include <math/Generated/Forward.h>
#include <math/Math.h>

#ifndef MUD_CPP_20
#include <cstdint>
#include <cmath>
#endif

#ifdef MUD_NO_GLM
#ifndef MUD_META_GENERATOR



//
// These are binary-exact approximations of pi/e constants
// http://www.exploringbinary.com/pi-and-e-in-binary/
//
#define MATH_fPI 3.1415927410125732421875f
#define MATH_dPI 3.141592653589793115997963468544185161590576171875
#define MATH_fE 2.71828174591064453125f
#define MATH_dE 2.718281828459045090795598298427648842334747314453125

#define MUD_VEC_FUN export_ MUD_MATH_EXPORT

namespace mud
{
	// float_types = "float,double"
	// signed_types = "float,double,char,short,int"
	// vector_types = signed_types + ",uchar,ushort,uint,bool"

/*$pycgen
	float_types = "float"
	int_types = "int,uint"
	signed_types = "float,int"
	scalar_types = "float,int,uint"
	vector_types = "float,int,uint,bool"
*/

	using std::sin;
	using std::cos;

	using std::floor;
	using std::ceil;

	// A 16-bit floating point number
	export_ struct refl_ struct_ array_ half
	{
		u16 x;
	};
	export_ struct refl_ struct_ array_ half2
	{
		u16 x, y;
	};
	export_ struct refl_ struct_ array_ half3
	{
		u16 x, y, z;
	};
	export_ struct refl_ struct_ array_ half4
	{
		u16 x, y, z, w;
	};

/*$pycgen
	tuple2 = """
	export_ struct refl_ struct_ array_ T2
	{
		typedef T type;
		T2() { }
		T2(T v) : x(v), y(v) {}
		T2(T x, T y) : x(x), y(y) {}
		template <class V>
		explicit T2(V v) : x(T(v.x)), y(T(v.y)) {}
		T operator[](uint index) const { return *((T*)&x + index); }
		T& operator[](uint index) { return *((T*)&x + index); }
		bool operator==(const T2& other) const { return x == other.x && y == other.y; }
		bool operator!=(const T2& other) const { return x != other.x || y != other.y; }
		//T x, y;
		union {
			T f[2];
			struct { attr_ T x; attr_ T y; };
		};
	};
	"""

	tuple3 = """
	export_ struct refl_ struct_ array_ T3
	{
		typedef T type;
		typedef T2 type2;
		T3() { }
		T3(T v) : x(v), y(v), z(v) {}
		T3(T x, T y, T z) : x(x), y(y), z(z) {}
		template <class V>
		explicit T3(V v) : x(T(v.x)), y(T(v.y)), z(T(v.z)) {}
		T operator[](uint index) const { return *((T*)&x + index); }
		T& operator[](uint index) { return *((T*)&x + index); }
		bool operator==(const T3& other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const T3& other) const { return x != other.x || y == other.y || z != other.z; }
		//T x, y, z;
		union {
			T f[3];
			struct { attr_ T x; attr_ T y; attr_ T z; };
		};
	};
	"""

	tuple4 = """
	export_ struct refl_ struct_ array_ T4
	{
		typedef T type;
		typedef T2 type2;
		typedef T3 type3;
		T4() { }
		T4(T v) : x(v), y(v), z(v), w(v) {}
		T4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		T4(T3 a, T w) : x(a.x), y(a.y), z(a.z), w(w) {}
		T4(T2 a, T2 b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
		template <class V>
		explicit T4(V v) : x(T(v.x)), y(T(v.y)), z(T(v.z)), w(T(v.w)) {}
		T operator[](uint index) const { return *((T*)&x + index); }
		T& operator[](uint index) { return *((T*)&x + index); }
		bool operator==(const T4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator!=(const T4& other) const { return x != other.x || y == other.y || z != other.z || w != other.w; }
		//T x, y, z, w;
		union {
			T f[4];
			struct { attr_ T x; attr_ T y; attr_ T z; attr_ T w; };
		};
	};
	"""

	EmitRepl(tuple2, "T:" + vector_types)
	EmitRepl(tuple3, "T:" + vector_types)
	EmitRepl(tuple4, "T:" + vector_types)
*/
//$pycgen-begin
	export_ struct refl_ struct_ array_ float2
	{
		typedef float type;
		float2() { }
		float2(float v) : x(v), y(v) {}
		float2(float x, float y) : x(x), y(y) {}
		template <class V>
		explicit float2(V v) : x(float(v.x)), y(float(v.y)) {}
		float operator[](uint index) const { return *((float*)&x + index); }
		float& operator[](uint index) { return *((float*)&x + index); }
		bool operator==(const float2& other) const { return x == other.x && y == other.y; }
		bool operator!=(const float2& other) const { return x != other.x || y != other.y; }
		//float x, y;
		union {
			float f[2];
			struct { attr_ float x; attr_ float y; };
		};
	};
	export_ struct refl_ struct_ array_ int2
	{
		typedef int type;
		int2() { }
		int2(int v) : x(v), y(v) {}
		int2(int x, int y) : x(x), y(y) {}
		template <class V>
		explicit int2(V v) : x(int(v.x)), y(int(v.y)) {}
		int operator[](uint index) const { return *((int*)&x + index); }
		int& operator[](uint index) { return *((int*)&x + index); }
		bool operator==(const int2& other) const { return x == other.x && y == other.y; }
		bool operator!=(const int2& other) const { return x != other.x || y != other.y; }
		//int x, y;
		union {
			int f[2];
			struct { attr_ int x; attr_ int y; };
		};
	};
	export_ struct refl_ struct_ array_ uint2
	{
		typedef uint type;
		uint2() { }
		uint2(uint v) : x(v), y(v) {}
		uint2(uint x, uint y) : x(x), y(y) {}
		template <class V>
		explicit uint2(V v) : x(uint(v.x)), y(uint(v.y)) {}
		uint operator[](uint index) const { return *((uint*)&x + index); }
		uint& operator[](uint index) { return *((uint*)&x + index); }
		bool operator==(const uint2& other) const { return x == other.x && y == other.y; }
		bool operator!=(const uint2& other) const { return x != other.x || y != other.y; }
		//uint x, y;
		union {
			uint f[2];
			struct { attr_ uint x; attr_ uint y; };
		};
	};
	export_ struct refl_ struct_ array_ bool2
	{
		typedef bool type;
		bool2() { }
		bool2(bool v) : x(v), y(v) {}
		bool2(bool x, bool y) : x(x), y(y) {}
		template <class V>
		explicit bool2(V v) : x(bool(v.x)), y(bool(v.y)) {}
		bool operator[](uint index) const { return *((bool*)&x + index); }
		bool& operator[](uint index) { return *((bool*)&x + index); }
		bool operator==(const bool2& other) const { return x == other.x && y == other.y; }
		bool operator!=(const bool2& other) const { return x != other.x || y != other.y; }
		//bool x, y;
		union {
			bool f[2];
			struct { attr_ bool x; attr_ bool y; };
		};
	};
	export_ struct refl_ struct_ array_ float3
	{
		typedef float type;
		typedef float2 type2;
		float3() { }
		float3(float v) : x(v), y(v), z(v) {}
		float3(float x, float y, float z) : x(x), y(y), z(z) {}
		template <class V>
		explicit float3(V v) : x(float(v.x)), y(float(v.y)), z(float(v.z)) {}
		float operator[](uint index) const { return *((float*)&x + index); }
		float& operator[](uint index) { return *((float*)&x + index); }
		bool operator==(const float3& other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const float3& other) const { return x != other.x || y == other.y || z != other.z; }
		//float x, y, z;
		union {
			float f[3];
			struct { attr_ float x; attr_ float y; attr_ float z; };
		};
	};
	export_ struct refl_ struct_ array_ int3
	{
		typedef int type;
		typedef int2 type2;
		int3() { }
		int3(int v) : x(v), y(v), z(v) {}
		int3(int x, int y, int z) : x(x), y(y), z(z) {}
		template <class V>
		explicit int3(V v) : x(int(v.x)), y(int(v.y)), z(int(v.z)) {}
		int operator[](uint index) const { return *((int*)&x + index); }
		int& operator[](uint index) { return *((int*)&x + index); }
		bool operator==(const int3& other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const int3& other) const { return x != other.x || y == other.y || z != other.z; }
		//int x, y, z;
		union {
			int f[3];
			struct { attr_ int x; attr_ int y; attr_ int z; };
		};
	};
	export_ struct refl_ struct_ array_ uint3
	{
		typedef uint type;
		typedef uint2 type2;
		uint3() { }
		uint3(uint v) : x(v), y(v), z(v) {}
		uint3(uint x, uint y, uint z) : x(x), y(y), z(z) {}
		template <class V>
		explicit uint3(V v) : x(uint(v.x)), y(uint(v.y)), z(uint(v.z)) {}
		uint operator[](uint index) const { return *((uint*)&x + index); }
		uint& operator[](uint index) { return *((uint*)&x + index); }
		bool operator==(const uint3& other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const uint3& other) const { return x != other.x || y == other.y || z != other.z; }
		//uint x, y, z;
		union {
			uint f[3];
			struct { attr_ uint x; attr_ uint y; attr_ uint z; };
		};
	};
	export_ struct refl_ struct_ array_ bool3
	{
		typedef bool type;
		typedef bool2 type2;
		bool3() { }
		bool3(bool v) : x(v), y(v), z(v) {}
		bool3(bool x, bool y, bool z) : x(x), y(y), z(z) {}
		template <class V>
		explicit bool3(V v) : x(bool(v.x)), y(bool(v.y)), z(bool(v.z)) {}
		bool operator[](uint index) const { return *((bool*)&x + index); }
		bool& operator[](uint index) { return *((bool*)&x + index); }
		bool operator==(const bool3& other) const { return x == other.x && y == other.y && z == other.z; }
		bool operator!=(const bool3& other) const { return x != other.x || y == other.y || z != other.z; }
		//bool x, y, z;
		union {
			bool f[3];
			struct { attr_ bool x; attr_ bool y; attr_ bool z; };
		};
	};
	export_ struct refl_ struct_ array_ float4
	{
		typedef float type;
		typedef float2 type2;
		typedef float3 type3;
		float4() { }
		float4(float v) : x(v), y(v), z(v), w(v) {}
		float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		float4(float3 a, float w) : x(a.x), y(a.y), z(a.z), w(w) {}
		float4(float2 a, float2 b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
		template <class V>
		explicit float4(V v) : x(float(v.x)), y(float(v.y)), z(float(v.z)), w(float(v.w)) {}
		float operator[](uint index) const { return *((float*)&x + index); }
		float& operator[](uint index) { return *((float*)&x + index); }
		bool operator==(const float4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator!=(const float4& other) const { return x != other.x || y == other.y || z != other.z || w != other.w; }
		//float x, y, z, w;
		union {
			float f[4];
			struct { attr_ float x; attr_ float y; attr_ float z; attr_ float w; };
		};
	};
	export_ struct refl_ struct_ array_ int4
	{
		typedef int type;
		typedef int2 type2;
		typedef int3 type3;
		int4() { }
		int4(int v) : x(v), y(v), z(v), w(v) {}
		int4(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}
		int4(int3 a, int w) : x(a.x), y(a.y), z(a.z), w(w) {}
		int4(int2 a, int2 b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
		template <class V>
		explicit int4(V v) : x(int(v.x)), y(int(v.y)), z(int(v.z)), w(int(v.w)) {}
		int operator[](uint index) const { return *((int*)&x + index); }
		int& operator[](uint index) { return *((int*)&x + index); }
		bool operator==(const int4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator!=(const int4& other) const { return x != other.x || y == other.y || z != other.z || w != other.w; }
		//int x, y, z, w;
		union {
			int f[4];
			struct { attr_ int x; attr_ int y; attr_ int z; attr_ int w; };
		};
	};
	export_ struct refl_ struct_ array_ uint4
	{
		typedef uint type;
		typedef uint2 type2;
		typedef uint3 type3;
		uint4() { }
		uint4(uint v) : x(v), y(v), z(v), w(v) {}
		uint4(uint x, uint y, uint z, uint w) : x(x), y(y), z(z), w(w) {}
		uint4(uint3 a, uint w) : x(a.x), y(a.y), z(a.z), w(w) {}
		uint4(uint2 a, uint2 b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
		template <class V>
		explicit uint4(V v) : x(uint(v.x)), y(uint(v.y)), z(uint(v.z)), w(uint(v.w)) {}
		uint operator[](uint index) const { return *((uint*)&x + index); }
		uint& operator[](uint index) { return *((uint*)&x + index); }
		bool operator==(const uint4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator!=(const uint4& other) const { return x != other.x || y == other.y || z != other.z || w != other.w; }
		//uint x, y, z, w;
		union {
			uint f[4];
			struct { attr_ uint x; attr_ uint y; attr_ uint z; attr_ uint w; };
		};
	};
	export_ struct refl_ struct_ array_ bool4
	{
		typedef bool type;
		typedef bool2 type2;
		typedef bool3 type3;
		bool4() { }
		bool4(bool v) : x(v), y(v), z(v), w(v) {}
		bool4(bool x, bool y, bool z, bool w) : x(x), y(y), z(z), w(w) {}
		bool4(bool3 a, bool w) : x(a.x), y(a.y), z(a.z), w(w) {}
		bool4(bool2 a, bool2 b) : x(a.x), y(a.y), z(b.x), w(b.y) {}
		template <class V>
		explicit bool4(V v) : x(bool(v.x)), y(bool(v.y)), z(bool(v.z)), w(bool(v.w)) {}
		bool operator[](uint index) const { return *((bool*)&x + index); }
		bool& operator[](uint index) { return *((bool*)&x + index); }
		bool operator==(const bool4& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
		bool operator!=(const bool4& other) const { return x != other.x || y == other.y || z != other.z || w != other.w; }
		//bool x, y, z, w;
		union {
			bool f[4];
			struct { attr_ bool x; attr_ bool y; attr_ bool z; attr_ bool w; };
		};
	};
//$pycgen-end

	export_ template <class T> inline typename T::type* value_ptr(T& v) { return &v[0]; }
	export_ template <class T> inline const typename T::type* value_ptr(const T& v) { return &v.f[0]; }

	// Experimental swizzling
	export_ template <typename T> inline typename T::type2 xy(const T& v)
	{
		return typename T::type2(v.x, v.y);
	}
	export_ template <typename T> inline typename T::type2 xz(const T& v)
	{
		return typename T::type2(v.x, v.z);
	}
	// These alias instead of constructing another variable, allowing modification
	export_ template <typename T> inline const typename T::type3& xyz(const T& v)
	{
		return (typename T::type3&)v;
	}
	export_ template <typename T> inline typename T::type3& xyz(T& v)
	{
		return (typename T::type3&)v;
	}


/*$pycgen
	code = """
	MUD_VEC_FUN bool all(const T2& v);
	MUD_VEC_FUN bool all(const T3& v);
	MUD_VEC_FUN bool all(const T4& v);
	"""
	EmitRepl(code, "T:bool")
*/
//$pycgen-begin
	MUD_VEC_FUN bool all(const bool2& v);
	MUD_VEC_FUN bool all(const bool3& v);
	MUD_VEC_FUN bool all(const bool4& v);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN bool any(const T2& v);
	MUD_VEC_FUN bool any(const T3& v);
	MUD_VEC_FUN bool any(const T4& v);
	"""
	EmitRepl(code, "T:bool")
*/
//$pycgen-begin
	MUD_VEC_FUN bool any(const bool2& v);
	MUD_VEC_FUN bool any(const bool3& v);
	MUD_VEC_FUN bool any(const bool4& v);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN bool2 isinf(const T2& v);
	MUD_VEC_FUN bool3 isinf(const T3& v);
	MUD_VEC_FUN bool4 isinf(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 isinf(const float2& v);
	MUD_VEC_FUN bool3 isinf(const float3& v);
	MUD_VEC_FUN bool4 isinf(const float4& v);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN bool2 isnan(const T2& v);
	MUD_VEC_FUN bool3 isnan(const T3& v);
	MUD_VEC_FUN bool4 isnan(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 isnan(const float2& v);
	MUD_VEC_FUN bool3 isnan(const float3& v);
	MUD_VEC_FUN bool4 isnan(const float4& v);
//$pycgen-end
	
	
/*$pycgen
	code = """
	MUD_VEC_FUN bool2 equal(const T2& a, const T2& b, float eps);
	MUD_VEC_FUN bool3 equal(const T3& a, const T3& b, float eps);
	MUD_VEC_FUN bool4 equal(const T4& a, const T4& b, float eps);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 equal(const float2& a, const float2& b, float eps);
	MUD_VEC_FUN bool3 equal(const float3& a, const float3& b, float eps);
	MUD_VEC_FUN bool4 equal(const float4& a, const float4& b, float eps);
	MUD_VEC_FUN bool2 equal(const int2& a, const int2& b, float eps);
	MUD_VEC_FUN bool3 equal(const int3& a, const int3& b, float eps);
	MUD_VEC_FUN bool4 equal(const int4& a, const int4& b, float eps);
	MUD_VEC_FUN bool2 equal(const uint2& a, const uint2& b, float eps);
	MUD_VEC_FUN bool3 equal(const uint3& a, const uint3& b, float eps);
	MUD_VEC_FUN bool4 equal(const uint4& a, const uint4& b, float eps);
	MUD_VEC_FUN bool2 equal(const bool2& a, const bool2& b, float eps);
	MUD_VEC_FUN bool3 equal(const bool3& a, const bool3& b, float eps);
	MUD_VEC_FUN bool4 equal(const bool4& a, const bool4& b, float eps);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN bool2 equal(const T2& a, const T2& b);
	MUD_VEC_FUN bool3 equal(const T3& a, const T3& b);
	MUD_VEC_FUN bool4 equal(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 equal(const float2& a, const float2& b);
	MUD_VEC_FUN bool3 equal(const float3& a, const float3& b);
	MUD_VEC_FUN bool4 equal(const float4& a, const float4& b);
	MUD_VEC_FUN bool2 equal(const int2& a, const int2& b);
	MUD_VEC_FUN bool3 equal(const int3& a, const int3& b);
	MUD_VEC_FUN bool4 equal(const int4& a, const int4& b);
	MUD_VEC_FUN bool2 equal(const uint2& a, const uint2& b);
	MUD_VEC_FUN bool3 equal(const uint3& a, const uint3& b);
	MUD_VEC_FUN bool4 equal(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool2 equal(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool3 equal(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool4 equal(const bool4& a, const bool4& b);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN bool2 not_equal(const T2& a, const T2& b);
	MUD_VEC_FUN bool3 not_equal(const T3& a, const T3& b);
	MUD_VEC_FUN bool4 not_equal(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 not_equal(const float2& a, const float2& b);
	MUD_VEC_FUN bool3 not_equal(const float3& a, const float3& b);
	MUD_VEC_FUN bool4 not_equal(const float4& a, const float4& b);
	MUD_VEC_FUN bool2 not_equal(const int2& a, const int2& b);
	MUD_VEC_FUN bool3 not_equal(const int3& a, const int3& b);
	MUD_VEC_FUN bool4 not_equal(const int4& a, const int4& b);
	MUD_VEC_FUN bool2 not_equal(const uint2& a, const uint2& b);
	MUD_VEC_FUN bool3 not_equal(const uint3& a, const uint3& b);
	MUD_VEC_FUN bool4 not_equal(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool2 not_equal(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool3 not_equal(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool4 not_equal(const bool4& a, const bool4& b);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN bool2 less(const T2& a, const T2& b);
	MUD_VEC_FUN bool3 less(const T3& a, const T3& b);
	MUD_VEC_FUN bool4 less(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 less(const float2& a, const float2& b);
	MUD_VEC_FUN bool3 less(const float3& a, const float3& b);
	MUD_VEC_FUN bool4 less(const float4& a, const float4& b);
	MUD_VEC_FUN bool2 less(const int2& a, const int2& b);
	MUD_VEC_FUN bool3 less(const int3& a, const int3& b);
	MUD_VEC_FUN bool4 less(const int4& a, const int4& b);
	MUD_VEC_FUN bool2 less(const uint2& a, const uint2& b);
	MUD_VEC_FUN bool3 less(const uint3& a, const uint3& b);
	MUD_VEC_FUN bool4 less(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool2 less(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool3 less(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool4 less(const bool4& a, const bool4& b);
//$pycgen-end
	
	
/*$pycgen
	code = """
	MUD_VEC_FUN bool2 less_equal(const T2& a, const T2& b);
	MUD_VEC_FUN bool3 less_equal(const T3& a, const T3& b);
	MUD_VEC_FUN bool4 less_equal(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 less_equal(const float2& a, const float2& b);
	MUD_VEC_FUN bool3 less_equal(const float3& a, const float3& b);
	MUD_VEC_FUN bool4 less_equal(const float4& a, const float4& b);
	MUD_VEC_FUN bool2 less_equal(const int2& a, const int2& b);
	MUD_VEC_FUN bool3 less_equal(const int3& a, const int3& b);
	MUD_VEC_FUN bool4 less_equal(const int4& a, const int4& b);
	MUD_VEC_FUN bool2 less_equal(const uint2& a, const uint2& b);
	MUD_VEC_FUN bool3 less_equal(const uint3& a, const uint3& b);
	MUD_VEC_FUN bool4 less_equal(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool2 less_equal(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool3 less_equal(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool4 less_equal(const bool4& a, const bool4& b);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN bool2 greater(const T2& a, const T2& b);
	MUD_VEC_FUN bool3 greater(const T3& a, const T3& b);
	MUD_VEC_FUN bool4 greater(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 greater(const float2& a, const float2& b);
	MUD_VEC_FUN bool3 greater(const float3& a, const float3& b);
	MUD_VEC_FUN bool4 greater(const float4& a, const float4& b);
	MUD_VEC_FUN bool2 greater(const int2& a, const int2& b);
	MUD_VEC_FUN bool3 greater(const int3& a, const int3& b);
	MUD_VEC_FUN bool4 greater(const int4& a, const int4& b);
	MUD_VEC_FUN bool2 greater(const uint2& a, const uint2& b);
	MUD_VEC_FUN bool3 greater(const uint3& a, const uint3& b);
	MUD_VEC_FUN bool4 greater(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool2 greater(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool3 greater(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool4 greater(const bool4& a, const bool4& b);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN bool2 greater_equal(const T2& a, const T2& b);
	MUD_VEC_FUN bool3 greater_equal(const T3& a, const T3& b);
	MUD_VEC_FUN bool4 greater_equal(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN bool2 greater_equal(const float2& a, const float2& b);
	MUD_VEC_FUN bool3 greater_equal(const float3& a, const float3& b);
	MUD_VEC_FUN bool4 greater_equal(const float4& a, const float4& b);
	MUD_VEC_FUN bool2 greater_equal(const int2& a, const int2& b);
	MUD_VEC_FUN bool3 greater_equal(const int3& a, const int3& b);
	MUD_VEC_FUN bool4 greater_equal(const int4& a, const int4& b);
	MUD_VEC_FUN bool2 greater_equal(const uint2& a, const uint2& b);
	MUD_VEC_FUN bool3 greater_equal(const uint3& a, const uint3& b);
	MUD_VEC_FUN bool4 greater_equal(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool2 greater_equal(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool3 greater_equal(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool4 greater_equal(const bool4& a, const bool4& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T sign(T v);
	MUD_VEC_FUN T2 sign(const T2& v);
	MUD_VEC_FUN T3 sign(const T3& v);
	MUD_VEC_FUN T4 sign(const T4& v);
	"""
	EmitRepl(code, "T:" + signed_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float sign(float v);
	MUD_VEC_FUN float2 sign(const float2& v);
	MUD_VEC_FUN float3 sign(const float3& v);
	MUD_VEC_FUN float4 sign(const float4& v);
	MUD_VEC_FUN int sign(int v);
	MUD_VEC_FUN int2 sign(const int2& v);
	MUD_VEC_FUN int3 sign(const int3& v);
	MUD_VEC_FUN int4 sign(const int4& v);
//$pycgen-end



/*$pycgen
	code = """
	MUD_VEC_FUN T dot(const T2& a, const T2& b);
	MUD_VEC_FUN T dot(const T3& a, const T3& b);
	MUD_VEC_FUN T dot(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float dot(const float2& a, const float2& b);
	MUD_VEC_FUN float dot(const float3& a, const float3& b);
	MUD_VEC_FUN float dot(const float4& a, const float4& b);
	MUD_VEC_FUN int dot(const int2& a, const int2& b);
	MUD_VEC_FUN int dot(const int3& a, const int3& b);
	MUD_VEC_FUN int dot(const int4& a, const int4& b);
	MUD_VEC_FUN uint dot(const uint2& a, const uint2& b);
	MUD_VEC_FUN uint dot(const uint3& a, const uint3& b);
	MUD_VEC_FUN uint dot(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool dot(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool dot(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool dot(const bool4& a, const bool4& b);
//$pycgen-end

	
/*$pycgen
	code = """
	MUD_VEC_FUN T3 cross(const T3& a, const T3& b);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float3 cross(const float3& a, const float3& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T length(const T2& v);
	MUD_VEC_FUN T length(const T3& v);
	MUD_VEC_FUN T length(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float length(const float2& v);
	MUD_VEC_FUN float length(const float3& v);
	MUD_VEC_FUN float length(const float4& v);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T length2(const T2& v);
	MUD_VEC_FUN T length2(const T3& v);
	MUD_VEC_FUN T length2(const T4& v);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float length2(const float2& v);
	MUD_VEC_FUN float length2(const float3& v);
	MUD_VEC_FUN float length2(const float4& v);
	MUD_VEC_FUN int length2(const int2& v);
	MUD_VEC_FUN int length2(const int3& v);
	MUD_VEC_FUN int length2(const int4& v);
	MUD_VEC_FUN uint length2(const uint2& v);
	MUD_VEC_FUN uint length2(const uint3& v);
	MUD_VEC_FUN uint length2(const uint4& v);
	MUD_VEC_FUN bool length2(const bool2& v);
	MUD_VEC_FUN bool length2(const bool3& v);
	MUD_VEC_FUN bool length2(const bool4& v);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN T distance(const T2& a, const T2& b);
	MUD_VEC_FUN T distance(const T3& a, const T3& b);
	MUD_VEC_FUN T distance(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float distance(const float2& a, const float2& b);
	MUD_VEC_FUN float distance(const float3& a, const float3& b);
	MUD_VEC_FUN float distance(const float4& a, const float4& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 normalize(const T2& v);
	MUD_VEC_FUN T3 normalize(const T3& v);
	MUD_VEC_FUN T4 normalize(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 normalize(const float2& v);
	MUD_VEC_FUN float3 normalize(const float3& v);
	MUD_VEC_FUN float4 normalize(const float4& v);
//$pycgen-end



/*$pycgen
	code = """
	MUD_VEC_FUN T2 abs(const T2& v);
	MUD_VEC_FUN T3 abs(const T3& v);
	MUD_VEC_FUN T4 abs(const T4& v);
	"""
	EmitRepl(code, "T:" + signed_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 abs(const float2& v);
	MUD_VEC_FUN float3 abs(const float3& v);
	MUD_VEC_FUN float4 abs(const float4& v);
	MUD_VEC_FUN int2 abs(const int2& v);
	MUD_VEC_FUN int3 abs(const int3& v);
	MUD_VEC_FUN int4 abs(const int4& v);
//$pycgen-end

	
/*$pycgen
	code = """
	MUD_VEC_FUN T2 mod(const T2& a, const T2& b);
	MUD_VEC_FUN T3 mod(const T3& a, const T3& b);
	MUD_VEC_FUN T4 mod(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + float_types)
	EmitRepl(code, "T:" + int_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 mod(const float2& a, const float2& b);
	MUD_VEC_FUN float3 mod(const float3& a, const float3& b);
	MUD_VEC_FUN float4 mod(const float4& a, const float4& b);
	MUD_VEC_FUN int2 mod(const int2& a, const int2& b);
	MUD_VEC_FUN int3 mod(const int3& a, const int3& b);
	MUD_VEC_FUN int4 mod(const int4& a, const int4& b);
	MUD_VEC_FUN uint2 mod(const uint2& a, const uint2& b);
	MUD_VEC_FUN uint3 mod(const uint3& a, const uint3& b);
	MUD_VEC_FUN uint4 mod(const uint4& a, const uint4& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 min(const T2& a, const T2& b);
	MUD_VEC_FUN T3 min(const T3& a, const T3& b);
	MUD_VEC_FUN T4 min(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 min(const float2& a, const float2& b);
	MUD_VEC_FUN float3 min(const float3& a, const float3& b);
	MUD_VEC_FUN float4 min(const float4& a, const float4& b);
	MUD_VEC_FUN int2 min(const int2& a, const int2& b);
	MUD_VEC_FUN int3 min(const int3& a, const int3& b);
	MUD_VEC_FUN int4 min(const int4& a, const int4& b);
	MUD_VEC_FUN uint2 min(const uint2& a, const uint2& b);
	MUD_VEC_FUN uint3 min(const uint3& a, const uint3& b);
	MUD_VEC_FUN uint4 min(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool2 min(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool3 min(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool4 min(const bool4& a, const bool4& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 max(const T2& a, const T2& b);
	MUD_VEC_FUN T3 max(const T3& a, const T3& b);
	MUD_VEC_FUN T4 max(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 max(const float2& a, const float2& b);
	MUD_VEC_FUN float3 max(const float3& a, const float3& b);
	MUD_VEC_FUN float4 max(const float4& a, const float4& b);
	MUD_VEC_FUN int2 max(const int2& a, const int2& b);
	MUD_VEC_FUN int3 max(const int3& a, const int3& b);
	MUD_VEC_FUN int4 max(const int4& a, const int4& b);
	MUD_VEC_FUN uint2 max(const uint2& a, const uint2& b);
	MUD_VEC_FUN uint3 max(const uint3& a, const uint3& b);
	MUD_VEC_FUN uint4 max(const uint4& a, const uint4& b);
	MUD_VEC_FUN bool2 max(const bool2& a, const bool2& b);
	MUD_VEC_FUN bool3 max(const bool3& a, const bool3& b);
	MUD_VEC_FUN bool4 max(const bool4& a, const bool4& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T clamp(T v, T lo, T hi);
	MUD_VEC_FUN T2 clamp(const T2& v, T lo, T hi);
	MUD_VEC_FUN T2 clamp(const T2& v, const T2& lo, const T2& hi);
	MUD_VEC_FUN T3 clamp(const T3& v, T lo, T hi);
	MUD_VEC_FUN T3 clamp(const T3& v, const T3& lo, const T3& hi);
	MUD_VEC_FUN T4 clamp(const T4& v, T lo, T hi);
	MUD_VEC_FUN T4 clamp(const T4& v, const T4& lo, const T4& hi);
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float clamp(float v, float lo, float hi);
	MUD_VEC_FUN float2 clamp(const float2& v, float lo, float hi);
	MUD_VEC_FUN float2 clamp(const float2& v, const float2& lo, const float2& hi);
	MUD_VEC_FUN float3 clamp(const float3& v, float lo, float hi);
	MUD_VEC_FUN float3 clamp(const float3& v, const float3& lo, const float3& hi);
	MUD_VEC_FUN float4 clamp(const float4& v, float lo, float hi);
	MUD_VEC_FUN float4 clamp(const float4& v, const float4& lo, const float4& hi);
	MUD_VEC_FUN int clamp(int v, int lo, int hi);
	MUD_VEC_FUN int2 clamp(const int2& v, int lo, int hi);
	MUD_VEC_FUN int2 clamp(const int2& v, const int2& lo, const int2& hi);
	MUD_VEC_FUN int3 clamp(const int3& v, int lo, int hi);
	MUD_VEC_FUN int3 clamp(const int3& v, const int3& lo, const int3& hi);
	MUD_VEC_FUN int4 clamp(const int4& v, int lo, int hi);
	MUD_VEC_FUN int4 clamp(const int4& v, const int4& lo, const int4& hi);
	MUD_VEC_FUN uint clamp(uint v, uint lo, uint hi);
	MUD_VEC_FUN uint2 clamp(const uint2& v, uint lo, uint hi);
	MUD_VEC_FUN uint2 clamp(const uint2& v, const uint2& lo, const uint2& hi);
	MUD_VEC_FUN uint3 clamp(const uint3& v, uint lo, uint hi);
	MUD_VEC_FUN uint3 clamp(const uint3& v, const uint3& lo, const uint3& hi);
	MUD_VEC_FUN uint4 clamp(const uint4& v, uint lo, uint hi);
	MUD_VEC_FUN uint4 clamp(const uint4& v, const uint4& lo, const uint4& hi);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T saturate(T v);
	MUD_VEC_FUN T2 saturate(const T2& v);
	MUD_VEC_FUN T3 saturate(const T3& v);
	MUD_VEC_FUN T4 saturate(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float saturate(float v);
	MUD_VEC_FUN float2 saturate(const float2& v);
	MUD_VEC_FUN float3 saturate(const float3& v);
	MUD_VEC_FUN float4 saturate(const float4& v);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 floor(const T2& v);
	MUD_VEC_FUN T3 floor(const T3& v);
	MUD_VEC_FUN T4 floor(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 floor(const float2& v);
	MUD_VEC_FUN float3 floor(const float3& v);
	MUD_VEC_FUN float4 floor(const float4& v);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 ceil(const T2& v);
	MUD_VEC_FUN T3 ceil(const T3& v);
	MUD_VEC_FUN T4 ceil(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 ceil(const float2& v);
	MUD_VEC_FUN float3 ceil(const float3& v);
	MUD_VEC_FUN float4 ceil(const float4& v);
//$pycgen-end

	
/*$pycgen
	code = """
	MUD_VEC_FUN T2 cos(const T2& v);
	MUD_VEC_FUN T3 cos(const T3& v);
	MUD_VEC_FUN T4 cos(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 cos(const float2& v);
	MUD_VEC_FUN float3 cos(const float3& v);
	MUD_VEC_FUN float4 cos(const float4& v);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN T2 sin(const T2& v);
	MUD_VEC_FUN T3 sin(const T3& v);
	MUD_VEC_FUN T4 sin(const T4& v);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 sin(const float2& v);
	MUD_VEC_FUN float3 sin(const float3& v);
	MUD_VEC_FUN float4 sin(const float4& v);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T lerp(T a, T b, T t);
	MUD_VEC_FUN T2 lerp(const T2& a, const T2& b, T t);
	MUD_VEC_FUN T3 lerp(const T3& a, const T3& b, T t);
	MUD_VEC_FUN T4 lerp(const T4& a, const T4& b, T t);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float lerp(float a, float b, float t);
	MUD_VEC_FUN float2 lerp(const float2& a, const float2& b, float t);
	MUD_VEC_FUN float3 lerp(const float3& a, const float3& b, float t);
	MUD_VEC_FUN float4 lerp(const float4& a, const float4& b, float t);
//$pycgen-end
	

/*$pycgen
	code = """
	inline T mix(T a, T b, T t) { return lerp(a, b, t); }
	inline T2 mix(const T2& a, const T2& b, T t) { return lerp(a, b, t); }
	inline T3 mix(const T3& a, const T3& b, T t) { return lerp(a, b, t); }
	inline T4 mix(const T4& a, const T4& b, T t) { return lerp(a, b, t); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	inline float mix(float a, float b, float t) { return lerp(a, b, t); }
	inline float2 mix(const float2& a, const float2& b, float t) { return lerp(a, b, t); }
	inline float3 mix(const float3& a, const float3& b, float t) { return lerp(a, b, t); }
	inline float4 mix(const float4& a, const float4& b, float t) { return lerp(a, b, t); }
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T spline(T a, T b, T c, T d, T t);
	MUD_VEC_FUN T2 spline(const T2& a, const T2& b, const T2& c, const T2& d, T t);
	MUD_VEC_FUN T3 spline(const T3& a, const T3& b, const T3& c, const T3& d, T t);
	MUD_VEC_FUN T4 spline(const T4& a, const T4& b, const T4& c, const T4& d, T t);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float spline(float a, float b, float c, float d, float t);
	MUD_VEC_FUN float2 spline(const float2& a, const float2& b, const float2& c, const float2& d, float t);
	MUD_VEC_FUN float3 spline(const float3& a, const float3& b, const float3& c, const float3& d, float t);
	MUD_VEC_FUN float4 spline(const float4& a, const float4& b, const float4& c, const float4& d, float t);
//$pycgen-end

	
/*$pycgen
	code = """
	MUD_VEC_FUN T angle(T a, T b);
	MUD_VEC_FUN T angle(const T2& a, const T2& b);
	MUD_VEC_FUN T angle(const T3& a, const T3& b);
	MUD_VEC_FUN T angle(const T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float angle(float a, float b);
	MUD_VEC_FUN float angle(const float2& a, const float2& b);
	MUD_VEC_FUN float angle(const float3& a, const float3& b);
	MUD_VEC_FUN float angle(const float4& a, const float4& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 operator+(const T2& a, const T2& b);
	MUD_VEC_FUN T3 operator+(const T3& a, const T3& b);
	MUD_VEC_FUN T4 operator+(const T4& a, const T4& b);
	MUD_VEC_FUN T2 operator+(const T2& a, T b);
	MUD_VEC_FUN T3 operator+(const T3& a, T b);
	MUD_VEC_FUN T4 operator+(const T4& a, T b);
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 operator+(const float2& a, const float2& b);
	MUD_VEC_FUN float3 operator+(const float3& a, const float3& b);
	MUD_VEC_FUN float4 operator+(const float4& a, const float4& b);
	MUD_VEC_FUN float2 operator+(const float2& a, float b);
	MUD_VEC_FUN float3 operator+(const float3& a, float b);
	MUD_VEC_FUN float4 operator+(const float4& a, float b);
	MUD_VEC_FUN int2 operator+(const int2& a, const int2& b);
	MUD_VEC_FUN int3 operator+(const int3& a, const int3& b);
	MUD_VEC_FUN int4 operator+(const int4& a, const int4& b);
	MUD_VEC_FUN int2 operator+(const int2& a, int b);
	MUD_VEC_FUN int3 operator+(const int3& a, int b);
	MUD_VEC_FUN int4 operator+(const int4& a, int b);
	MUD_VEC_FUN uint2 operator+(const uint2& a, const uint2& b);
	MUD_VEC_FUN uint3 operator+(const uint3& a, const uint3& b);
	MUD_VEC_FUN uint4 operator+(const uint4& a, const uint4& b);
	MUD_VEC_FUN uint2 operator+(const uint2& a, uint b);
	MUD_VEC_FUN uint3 operator+(const uint3& a, uint b);
	MUD_VEC_FUN uint4 operator+(const uint4& a, uint b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 operator-(const T2& a, const T2& b);
	MUD_VEC_FUN T3 operator-(const T3& a, const T3& b);
	MUD_VEC_FUN T4 operator-(const T4& a, const T4& b);
	MUD_VEC_FUN T2 operator-(const T2& a, T b);
	MUD_VEC_FUN T3 operator-(const T3& a, T b);
	MUD_VEC_FUN T4 operator-(const T4& a, T b);
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 operator-(const float2& a, const float2& b);
	MUD_VEC_FUN float3 operator-(const float3& a, const float3& b);
	MUD_VEC_FUN float4 operator-(const float4& a, const float4& b);
	MUD_VEC_FUN float2 operator-(const float2& a, float b);
	MUD_VEC_FUN float3 operator-(const float3& a, float b);
	MUD_VEC_FUN float4 operator-(const float4& a, float b);
	MUD_VEC_FUN int2 operator-(const int2& a, const int2& b);
	MUD_VEC_FUN int3 operator-(const int3& a, const int3& b);
	MUD_VEC_FUN int4 operator-(const int4& a, const int4& b);
	MUD_VEC_FUN int2 operator-(const int2& a, int b);
	MUD_VEC_FUN int3 operator-(const int3& a, int b);
	MUD_VEC_FUN int4 operator-(const int4& a, int b);
	MUD_VEC_FUN uint2 operator-(const uint2& a, const uint2& b);
	MUD_VEC_FUN uint3 operator-(const uint3& a, const uint3& b);
	MUD_VEC_FUN uint4 operator-(const uint4& a, const uint4& b);
	MUD_VEC_FUN uint2 operator-(const uint2& a, uint b);
	MUD_VEC_FUN uint3 operator-(const uint3& a, uint b);
	MUD_VEC_FUN uint4 operator-(const uint4& a, uint b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 operator*(const T2& a, const T2& b);
	MUD_VEC_FUN T3 operator*(const T3& a, const T3& b);
	MUD_VEC_FUN T4 operator*(const T4& a, const T4& b);
	MUD_VEC_FUN T2 operator*(const T2& a, T b);
	MUD_VEC_FUN T3 operator*(const T3& a, T b);
	MUD_VEC_FUN T4 operator*(const T4& a, T b);
	MUD_VEC_FUN T2 operator*(T a, const T2& b);
	MUD_VEC_FUN T3 operator*(T a, const T3& b);
	MUD_VEC_FUN T4 operator*(T a, const T4& b);
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 operator*(const float2& a, const float2& b);
	MUD_VEC_FUN float3 operator*(const float3& a, const float3& b);
	MUD_VEC_FUN float4 operator*(const float4& a, const float4& b);
	MUD_VEC_FUN float2 operator*(const float2& a, float b);
	MUD_VEC_FUN float3 operator*(const float3& a, float b);
	MUD_VEC_FUN float4 operator*(const float4& a, float b);
	MUD_VEC_FUN float2 operator*(float a, const float2& b);
	MUD_VEC_FUN float3 operator*(float a, const float3& b);
	MUD_VEC_FUN float4 operator*(float a, const float4& b);
	MUD_VEC_FUN int2 operator*(const int2& a, const int2& b);
	MUD_VEC_FUN int3 operator*(const int3& a, const int3& b);
	MUD_VEC_FUN int4 operator*(const int4& a, const int4& b);
	MUD_VEC_FUN int2 operator*(const int2& a, int b);
	MUD_VEC_FUN int3 operator*(const int3& a, int b);
	MUD_VEC_FUN int4 operator*(const int4& a, int b);
	MUD_VEC_FUN int2 operator*(int a, const int2& b);
	MUD_VEC_FUN int3 operator*(int a, const int3& b);
	MUD_VEC_FUN int4 operator*(int a, const int4& b);
	MUD_VEC_FUN uint2 operator*(const uint2& a, const uint2& b);
	MUD_VEC_FUN uint3 operator*(const uint3& a, const uint3& b);
	MUD_VEC_FUN uint4 operator*(const uint4& a, const uint4& b);
	MUD_VEC_FUN uint2 operator*(const uint2& a, uint b);
	MUD_VEC_FUN uint3 operator*(const uint3& a, uint b);
	MUD_VEC_FUN uint4 operator*(const uint4& a, uint b);
	MUD_VEC_FUN uint2 operator*(uint a, const uint2& b);
	MUD_VEC_FUN uint3 operator*(uint a, const uint3& b);
	MUD_VEC_FUN uint4 operator*(uint a, const uint4& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 operator/(const T2& a, const T2& b);
	MUD_VEC_FUN T3 operator/(const T3& a, const T3& b);
	MUD_VEC_FUN T4 operator/(const T4& a, const T4& b);
	MUD_VEC_FUN T2 operator/(const T2& a, T b);
	MUD_VEC_FUN T3 operator/(const T3& a, T b);
	MUD_VEC_FUN T4 operator/(const T4& a, T b);
	MUD_VEC_FUN T2 operator/(T a, const T2& b);
	MUD_VEC_FUN T3 operator/(T a, const T3& b);
	MUD_VEC_FUN T4 operator/(T a, const T4& b);
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 operator/(const float2& a, const float2& b);
	MUD_VEC_FUN float3 operator/(const float3& a, const float3& b);
	MUD_VEC_FUN float4 operator/(const float4& a, const float4& b);
	MUD_VEC_FUN float2 operator/(const float2& a, float b);
	MUD_VEC_FUN float3 operator/(const float3& a, float b);
	MUD_VEC_FUN float4 operator/(const float4& a, float b);
	MUD_VEC_FUN float2 operator/(float a, const float2& b);
	MUD_VEC_FUN float3 operator/(float a, const float3& b);
	MUD_VEC_FUN float4 operator/(float a, const float4& b);
	MUD_VEC_FUN int2 operator/(const int2& a, const int2& b);
	MUD_VEC_FUN int3 operator/(const int3& a, const int3& b);
	MUD_VEC_FUN int4 operator/(const int4& a, const int4& b);
	MUD_VEC_FUN int2 operator/(const int2& a, int b);
	MUD_VEC_FUN int3 operator/(const int3& a, int b);
	MUD_VEC_FUN int4 operator/(const int4& a, int b);
	MUD_VEC_FUN int2 operator/(int a, const int2& b);
	MUD_VEC_FUN int3 operator/(int a, const int3& b);
	MUD_VEC_FUN int4 operator/(int a, const int4& b);
	MUD_VEC_FUN uint2 operator/(const uint2& a, const uint2& b);
	MUD_VEC_FUN uint3 operator/(const uint3& a, const uint3& b);
	MUD_VEC_FUN uint4 operator/(const uint4& a, const uint4& b);
	MUD_VEC_FUN uint2 operator/(const uint2& a, uint b);
	MUD_VEC_FUN uint3 operator/(const uint3& a, uint b);
	MUD_VEC_FUN uint4 operator/(const uint4& a, uint b);
	MUD_VEC_FUN uint2 operator/(uint a, const uint2& b);
	MUD_VEC_FUN uint3 operator/(uint a, const uint3& b);
	MUD_VEC_FUN uint4 operator/(uint a, const uint4& b);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2 operator-(const T2& a);
	MUD_VEC_FUN T3 operator-(const T3& a);
	MUD_VEC_FUN T4 operator-(const T4& a);
	"""
	EmitRepl(code, "T:" + signed_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2 operator-(const float2& a);
	MUD_VEC_FUN float3 operator-(const float3& a);
	MUD_VEC_FUN float4 operator-(const float4& a);
	MUD_VEC_FUN int2 operator-(const int2& a);
	MUD_VEC_FUN int3 operator-(const int3& a);
	MUD_VEC_FUN int4 operator-(const int4& a);
//$pycgen-end


/*$pycgen
	code = """
	MUD_VEC_FUN T2& operator+=(T2& a, const T2& b);
	MUD_VEC_FUN T3& operator+=(T3& a, const T3& b);
	MUD_VEC_FUN T4& operator+=(T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2& operator+=(float2& a, const float2& b);
	MUD_VEC_FUN float3& operator+=(float3& a, const float3& b);
	MUD_VEC_FUN float4& operator+=(float4& a, const float4& b);
	MUD_VEC_FUN int2& operator+=(int2& a, const int2& b);
	MUD_VEC_FUN int3& operator+=(int3& a, const int3& b);
	MUD_VEC_FUN int4& operator+=(int4& a, const int4& b);
	MUD_VEC_FUN uint2& operator+=(uint2& a, const uint2& b);
	MUD_VEC_FUN uint3& operator+=(uint3& a, const uint3& b);
	MUD_VEC_FUN uint4& operator+=(uint4& a, const uint4& b);
//$pycgen-end
	

/*$pycgen
	code = """
	MUD_VEC_FUN T2& operator*=(T2& a, const T2& b);
	MUD_VEC_FUN T3& operator*=(T3& a, const T3& b);
	MUD_VEC_FUN T4& operator*=(T4& a, const T4& b);
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	MUD_VEC_FUN float2& operator*=(float2& a, const float2& b);
	MUD_VEC_FUN float3& operator*=(float3& a, const float3& b);
	MUD_VEC_FUN float4& operator*=(float4& a, const float4& b);
	MUD_VEC_FUN int2& operator*=(int2& a, const int2& b);
	MUD_VEC_FUN int3& operator*=(int3& a, const int3& b);
	MUD_VEC_FUN int4& operator*=(int4& a, const int4& b);
	MUD_VEC_FUN uint2& operator*=(uint2& a, const uint2& b);
	MUD_VEC_FUN uint3& operator*=(uint3& a, const uint3& b);
	MUD_VEC_FUN uint4& operator*=(uint4& a, const uint4& b);
//$pycgen-end


	//
	// Single precision 3x3 matrix
	//
	export_ struct refl_ struct_ array_ mat3
	{
		typedef float type;
		mat3() { }
		mat3(const float3& x, const float3& y, const float3& z)
		{
			f[0] = x.x; f[1] = x.y; f[2] = x.z;
			f[3] = y.x; f[4] = y.y; f[5] = y.z;
			f[6] = z.x; f[7] = z.y; f[8] = z.z;
		}
		mat3(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8)
		{
			f[0] = f0; f[1] = f1; f[2] = f2;
			f[3] = f3; f[4] = f4; f[5] = f5;
			f[6] = f6; f[7] = f7; f[8] = f8;
		}

		const float3& operator[](uint index) const { return *((float3*)f + index); }
		float3& operator[](uint index) { return *((float3*)f + index); }

		union
		{
			float m[3][3];
			attr_ float f[9];
		};
	};


#if 0
	//
	// Double precision 3x3 matrix
	// C++ only
	//
	export_ struct refl_ struct_ array_ mat3d
	{
		typedef double type;
		mat3d() { }
		mat3d(const double3& x, const double3& y, const double3& z)
		{
			f[0] = x.x; f[1] = x.y; f[2] = x.z;
			f[3] = y.x; f[4] = y.y; f[5] = y.z;
			f[6] = z.x; f[7] = z.y; f[8] = z.z;
		}
		mat3d(double f0, double f1, double f2, double f3, double f4, double f5, double f6, double f7, double f8)
		{
			f[0] = f0; f[1] = f1; f[2] = f2;
			f[3] = f3; f[4] = f4; f[5] = f5;
			f[6] = f6; f[7] = f7; f[8] = f8;
		}

		const double3& operator[](uint index) const { return *((double3*)f + index); }
		double3& operator[](uint index) { return *((double3*)f + index); }

		union
		{
			double m[3][3];
			attr_ double f[9];
		};
	};
#endif

	//
	// Single precision 4x4 matrix
	//
	export_ struct refl_ struct_ array_ mat4
	{
		typedef float type;
		mat4() {}
		mat4(const float4& x, const float4& y, const float4& z, const float4& w)
		{
			f[0] = x.x; f[1] = x.y; f[2] = x.z; f[3] = x.w;
			f[4] = y.x; f[5] = y.y; f[6] = y.z; f[7] = y.w;
			f[8] = z.x; f[9] = z.y; f[10] = z.z; f[11] = z.w;
			f[12] = w.x; f[13] = w.y; f[14] = w.z; f[15] = w.w;
		}
		mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15)
		{
			f[0] = f0;  f[1] = f1;  f[2] = f2;  f[3] = f3;
			f[4] = f4;  f[5] = f5;  f[6] = f6;  f[7] = f7;
			f[8] = f8;  f[9] = f9;  f[10] = f10; f[11] = f11;
			f[12] = f12; f[13] = f13; f[14] = f14; f[15] = f15;
		}

		const float4& operator[](uint index) const { return *((float4*)f + index); }
		float4& operator[](uint index) { return *((float4*)f + index); }

		bool operator==(const mat4& other) const
		{
			return f[0] == other.f[0] && f[1] == other.f[1] && f[2] == other.f[2] && f[3] == other.f[3]
				&& f[4] == other.f[4] && f[5] == other.f[5] && f[6] == other.f[6] && f[7] == other.f[7]
				&& f[8] == other.f[8] && f[9] == other.f[9] && f[10] == other.f[10] && f[11] == other.f[11]
				&& f[12] == other.f[12] && f[13] == other.f[13] && f[14] == other.f[14] && f[15] == other.f[15];
		}

		union
		{
			float m[4][4];
			attr_ float f[16];
		};
	};


	//
	// Single precision quaternion
	//
	export_ struct refl_ struct_ array_ quat : public float4
	{
		typedef float type;
		quat() { }
		quat(float v) : float4(v) { }
		quat(float x, float y, float z, float w) : float4(x, y, z, w) { }
		quat(const float3& euler_angles) 
		{
			float3 c = cos(euler_angles * float(0.5));
			float3 s = sin(euler_angles * float(0.5));

			this->x = s.x * c.y * c.z - c.x * s.y * s.z;
			this->y = c.x * s.y * c.z + s.x * c.y * s.z;
			this->z = c.x * c.y * s.z - s.x * s.y * c.z;
			this->w = c.x * c.y * c.z + s.x * s.y * s.z;
		}
	};

	export_ template <> inline float* value_ptr(mat4& m) { return &m[0][0]; }
	export_ template <> inline const float* value_ptr(const mat4& m) { return &m.f[0]; }
	export_ template <> inline float* value_ptr(quat& q) { return &q[0]; }

	//
	// Quaternion functions
	//
	MUD_VEC_FUN quat operator*(const quat& a, const quat& b);
	//MUD_VEC_FUN quat operator/(const quat& a, const quat& b);
	MUD_VEC_FUN quat operator+(const quat& a, const quat& b);
	MUD_VEC_FUN quat operator-(const quat& a, const quat& b);

	MUD_VEC_FUN quat operator*(const quat& a, float s);
	MUD_VEC_FUN quat operator/(const quat& a, float s);
	MUD_VEC_FUN quat operator*(float s, const quat& a);
	MUD_VEC_FUN quat operator/(float s, const quat& a);

	MUD_VEC_FUN quat operator+(const quat& v);
	MUD_VEC_FUN quat operator-(const quat& v);

	// transform position
	MUD_VEC_FUN float3 operator*(const quat& q, const float3& v);
	MUD_VEC_FUN float4 operator*(const quat& q, const float4& v);

	MUD_VEC_FUN quat conjugate(const quat& q);
	MUD_VEC_FUN quat inverse(const quat& q);
	MUD_VEC_FUN quat negate(const quat& q);

	MUD_VEC_FUN float dot(const quat& a, const quat& b);
	MUD_VEC_FUN quat normalize(const quat& q);

	MUD_VEC_FUN quat lerp(const quat& a, const quat& b, float t);
	MUD_VEC_FUN quat slerp(const quat& a, const quat& b, float t);

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

	MUD_VEC_FUN float oriented_angle(const float3& a, const float3& b, const float3& ref);
	MUD_VEC_FUN float oriented_angle(const float2& a, const float2& b);

	MUD_VEC_FUN mat4 inverse(const mat4& m);
	MUD_VEC_FUN mat4 transpose(const mat4& m);
	MUD_VEC_FUN mat4 operator*(const mat4& m0, const mat4& m1);
	MUD_VEC_FUN float4 operator*(const mat4& m, const float4& v);

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

#if 0 // MUD_NOT_IMPLEMENTED
#include <vector>

namespace mud
{
	//
	// Some utility functions
	//
	float QuadAreaApproximateSphereProjectionSize(const float3& pos, float radius, const mat4& w2c, const mat4& c2s, float near_z);
	double SphereAngularProjectionOntoPosition(const double3& sphere_pos, double radius, const double3& position);
	void MakeHammersleyPoints(u32 nb_points, std::vector<float4>& points);
	i16 Compress_DoubleToSigned16(double d, double extents);
	double Decompress_Signed16ToDouble(i16 d, double extents);
}
#endif

#endif
#endif
