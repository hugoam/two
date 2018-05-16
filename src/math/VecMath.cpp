#ifdef MUD_NO_GLM

#include <math/VecMath.h>

#include <cmath>
#include <limits>

namespace mud
{
/*$pycgen
	float_types = "float"
	int_types = "int,uint"
	signed_types = "float,int"
	scalar_types = "float,int,uint"
	vector_types = "float,int,uint,bool"
*/

	using std::isnan;
	using std::isinf;
	using std::abs;

	template <class T>
	T epsilon() { return std::numeric_limits<T>::epsilon(); }

/*$pycgen
	code = """
	bool all(const T2& v) { return v.x && v.y; }
	bool all(const T3& v) { return v.x && v.y && v.z; }
	bool all(const T4& v) { return v.x && v.y && v.z && v.w; }
	"""
	EmitRepl(code, "T:bool")
*/
//$pycgen-begin
	bool all(const bool2& v) { return v.x && v.y; }
	bool all(const bool3& v) { return v.x && v.y && v.z; }
	bool all(const bool4& v) { return v.x && v.y && v.z && v.w; }
//$pycgen-end
	

/*$pycgen
	code = """
	bool any(const T2& v) { return v.x || v.y; }
	bool any(const T3& v) { return v.x || v.y || v.z; }
	bool any(const T4& v) { return v.x || v.y || v.z || v.w; }
	"""
	EmitRepl(code, "T:bool")
*/
//$pycgen-begin
	bool any(const bool2& v) { return v.x || v.y; }
	bool any(const bool3& v) { return v.x || v.y || v.z; }
	bool any(const bool4& v) { return v.x || v.y || v.z || v.w; }
//$pycgen-end
	

/*$pycgen
	code = """
	bool2 isinf(const T2& v) { return bool2(isinf(v.x), isinf(v.y)); }
	bool3 isinf(const T3& v) { return bool3(isinf(v.x), isinf(v.y), isinf(v.z)); }
	bool4 isinf(const T4& v) { return bool4(isinf(v.x), isinf(v.y), isinf(v.z), isinf(v.w)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	bool2 isinf(const float2& v) { return bool2(isinf(v.x), isinf(v.y)); }
	bool3 isinf(const float3& v) { return bool3(isinf(v.x), isinf(v.y), isinf(v.z)); }
	bool4 isinf(const float4& v) { return bool4(isinf(v.x), isinf(v.y), isinf(v.z), isinf(v.w)); }
//$pycgen-end


/*$pycgen
	code = """
	bool2 isnan(const T2& v) { return bool2(isnan(v.x), isnan(v.y)); }
	bool3 isnan(const T3& v) { return bool3(isnan(v.x), isnan(v.y), isnan(v.z)); }
	bool4 isnan(const T4& v) { return bool4(isnan(v.x), isnan(v.y), isnan(v.z), isnan(v.w)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	bool2 isnan(const float2& v) { return bool2(isnan(v.x), isnan(v.y)); }
	bool3 isnan(const float3& v) { return bool3(isnan(v.x), isnan(v.y), isnan(v.z)); }
	bool4 isnan(const float4& v) { return bool4(isnan(v.x), isnan(v.y), isnan(v.z), isnan(v.w)); }
//$pycgen-end
	
	
/*$pycgen
	code = """
	bool equal(const T& a, const T& b, float eps) { return abs(b - a) < eps; }
	bool2 equal(const T2& a, const T2& b, float eps) { return less(abs(b - a), T2(eps)); }
	bool3 equal(const T3& a, const T3& b, float eps) { return less(abs(b - a), T3(eps)); }
	bool4 equal(const T4& a, const T4& b, float eps) { return less(abs(b - a), T4(eps)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	bool equal(const float& a, const float& b, float eps) { return abs(b - a) < eps; }
	bool2 equal(const float2& a, const float2& b, float eps) { return less(abs(b - a), float2(eps)); }
	bool3 equal(const float3& a, const float3& b, float eps) { return less(abs(b - a), float3(eps)); }
	bool4 equal(const float4& a, const float4& b, float eps) { return less(abs(b - a), float4(eps)); }
//$pycgen-end
	
	
/*$pycgen
	code = """
	bool2 equal(const T2& a, const T2& b) { return bool2(a.x == b.x, a.y == b.y); }
	bool3 equal(const T3& a, const T3& b) { return bool3(a.x == b.x, a.y == b.y, a.z == b.z); }
	bool4 equal(const T4& a, const T4& b) { return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w); }
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	bool2 equal(const float2& a, const float2& b) { return bool2(a.x == b.x, a.y == b.y); }
	bool3 equal(const float3& a, const float3& b) { return bool3(a.x == b.x, a.y == b.y, a.z == b.z); }
	bool4 equal(const float4& a, const float4& b) { return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w); }
	bool2 equal(const int2& a, const int2& b) { return bool2(a.x == b.x, a.y == b.y); }
	bool3 equal(const int3& a, const int3& b) { return bool3(a.x == b.x, a.y == b.y, a.z == b.z); }
	bool4 equal(const int4& a, const int4& b) { return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w); }
	bool2 equal(const uint2& a, const uint2& b) { return bool2(a.x == b.x, a.y == b.y); }
	bool3 equal(const uint3& a, const uint3& b) { return bool3(a.x == b.x, a.y == b.y, a.z == b.z); }
	bool4 equal(const uint4& a, const uint4& b) { return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w); }
	bool2 equal(const bool2& a, const bool2& b) { return bool2(a.x == b.x, a.y == b.y); }
	bool3 equal(const bool3& a, const bool3& b) { return bool3(a.x == b.x, a.y == b.y, a.z == b.z); }
	bool4 equal(const bool4& a, const bool4& b) { return bool4(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w); }
//$pycgen-end
	
	
/*$pycgen
	code = """
	bool2 not_equal(const T2& a, const T2& b) { return bool2(a.x != b.x, a.y != b.y); }
	bool3 not_equal(const T3& a, const T3& b) { return bool3(a.x != b.x, a.y != b.y, a.z != b.z); }
	bool4 not_equal(const T4& a, const T4& b) { return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w); }
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	bool2 not_equal(const float2& a, const float2& b) { return bool2(a.x != b.x, a.y != b.y); }
	bool3 not_equal(const float3& a, const float3& b) { return bool3(a.x != b.x, a.y != b.y, a.z != b.z); }
	bool4 not_equal(const float4& a, const float4& b) { return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w); }
	bool2 not_equal(const int2& a, const int2& b) { return bool2(a.x != b.x, a.y != b.y); }
	bool3 not_equal(const int3& a, const int3& b) { return bool3(a.x != b.x, a.y != b.y, a.z != b.z); }
	bool4 not_equal(const int4& a, const int4& b) { return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w); }
	bool2 not_equal(const uint2& a, const uint2& b) { return bool2(a.x != b.x, a.y != b.y); }
	bool3 not_equal(const uint3& a, const uint3& b) { return bool3(a.x != b.x, a.y != b.y, a.z != b.z); }
	bool4 not_equal(const uint4& a, const uint4& b) { return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w); }
	bool2 not_equal(const bool2& a, const bool2& b) { return bool2(a.x != b.x, a.y != b.y); }
	bool3 not_equal(const bool3& a, const bool3& b) { return bool3(a.x != b.x, a.y != b.y, a.z != b.z); }
	bool4 not_equal(const bool4& a, const bool4& b) { return bool4(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w); }
//$pycgen-end
	

/*$pycgen
	code = """
	bool2 less(const T2& a, const T2& b) { return bool2(a.x < b.x, a.y < b.y); }
	bool3 less(const T3& a, const T3& b) { return bool3(a.x < b.x, a.y < b.y, a.z < b.z); }
	bool4 less(const T4& a, const T4& b) { return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w); }
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	bool2 less(const float2& a, const float2& b) { return bool2(a.x < b.x, a.y < b.y); }
	bool3 less(const float3& a, const float3& b) { return bool3(a.x < b.x, a.y < b.y, a.z < b.z); }
	bool4 less(const float4& a, const float4& b) { return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w); }
	bool2 less(const int2& a, const int2& b) { return bool2(a.x < b.x, a.y < b.y); }
	bool3 less(const int3& a, const int3& b) { return bool3(a.x < b.x, a.y < b.y, a.z < b.z); }
	bool4 less(const int4& a, const int4& b) { return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w); }
	bool2 less(const uint2& a, const uint2& b) { return bool2(a.x < b.x, a.y < b.y); }
	bool3 less(const uint3& a, const uint3& b) { return bool3(a.x < b.x, a.y < b.y, a.z < b.z); }
	bool4 less(const uint4& a, const uint4& b) { return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w); }
	bool2 less(const bool2& a, const bool2& b) { return bool2(a.x < b.x, a.y < b.y); }
	bool3 less(const bool3& a, const bool3& b) { return bool3(a.x < b.x, a.y < b.y, a.z < b.z); }
	bool4 less(const bool4& a, const bool4& b) { return bool4(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w); }
//$pycgen-end
	
	
/*$pycgen
	code = """
	bool2 less_equal(const T2& a, const T2& b) { return bool2(a.x <= b.x, a.y <= b.y); }
	bool3 less_equal(const T3& a, const T3& b) { return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z); }
	bool4 less_equal(const T4& a, const T4& b) { return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w); }
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	bool2 less_equal(const float2& a, const float2& b) { return bool2(a.x <= b.x, a.y <= b.y); }
	bool3 less_equal(const float3& a, const float3& b) { return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z); }
	bool4 less_equal(const float4& a, const float4& b) { return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w); }
	bool2 less_equal(const int2& a, const int2& b) { return bool2(a.x <= b.x, a.y <= b.y); }
	bool3 less_equal(const int3& a, const int3& b) { return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z); }
	bool4 less_equal(const int4& a, const int4& b) { return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w); }
	bool2 less_equal(const uint2& a, const uint2& b) { return bool2(a.x <= b.x, a.y <= b.y); }
	bool3 less_equal(const uint3& a, const uint3& b) { return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z); }
	bool4 less_equal(const uint4& a, const uint4& b) { return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w); }
	bool2 less_equal(const bool2& a, const bool2& b) { return bool2(a.x <= b.x, a.y <= b.y); }
	bool3 less_equal(const bool3& a, const bool3& b) { return bool3(a.x <= b.x, a.y <= b.y, a.z <= b.z); }
	bool4 less_equal(const bool4& a, const bool4& b) { return bool4(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w); }
//$pycgen-end
	

/*$pycgen
	code = """
	bool2 greater(const T2& a, const T2& b) { return bool2(a.x > b.x, a.y > b.y); }
	bool3 greater(const T3& a, const T3& b) { return bool3(a.x > b.x, a.y > b.y, a.z > b.z); }
	bool4 greater(const T4& a, const T4& b) { return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w); }
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	bool2 greater(const float2& a, const float2& b) { return bool2(a.x > b.x, a.y > b.y); }
	bool3 greater(const float3& a, const float3& b) { return bool3(a.x > b.x, a.y > b.y, a.z > b.z); }
	bool4 greater(const float4& a, const float4& b) { return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w); }
	bool2 greater(const int2& a, const int2& b) { return bool2(a.x > b.x, a.y > b.y); }
	bool3 greater(const int3& a, const int3& b) { return bool3(a.x > b.x, a.y > b.y, a.z > b.z); }
	bool4 greater(const int4& a, const int4& b) { return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w); }
	bool2 greater(const uint2& a, const uint2& b) { return bool2(a.x > b.x, a.y > b.y); }
	bool3 greater(const uint3& a, const uint3& b) { return bool3(a.x > b.x, a.y > b.y, a.z > b.z); }
	bool4 greater(const uint4& a, const uint4& b) { return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w); }
	bool2 greater(const bool2& a, const bool2& b) { return bool2(a.x > b.x, a.y > b.y); }
	bool3 greater(const bool3& a, const bool3& b) { return bool3(a.x > b.x, a.y > b.y, a.z > b.z); }
	bool4 greater(const bool4& a, const bool4& b) { return bool4(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w); }
//$pycgen-end
	

/*$pycgen
	code = """
	bool2 greater_equal(const T2& a, const T2& b) { return bool2(a.x >= b.x, a.y >= b.y); }
	bool3 greater_equal(const T3& a, const T3& b) { return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z); }
	bool4 greater_equal(const T4& a, const T4& b) { return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w); }
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	bool2 greater_equal(const float2& a, const float2& b) { return bool2(a.x >= b.x, a.y >= b.y); }
	bool3 greater_equal(const float3& a, const float3& b) { return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z); }
	bool4 greater_equal(const float4& a, const float4& b) { return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w); }
	bool2 greater_equal(const int2& a, const int2& b) { return bool2(a.x >= b.x, a.y >= b.y); }
	bool3 greater_equal(const int3& a, const int3& b) { return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z); }
	bool4 greater_equal(const int4& a, const int4& b) { return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w); }
	bool2 greater_equal(const uint2& a, const uint2& b) { return bool2(a.x >= b.x, a.y >= b.y); }
	bool3 greater_equal(const uint3& a, const uint3& b) { return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z); }
	bool4 greater_equal(const uint4& a, const uint4& b) { return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w); }
	bool2 greater_equal(const bool2& a, const bool2& b) { return bool2(a.x >= b.x, a.y >= b.y); }
	bool3 greater_equal(const bool3& a, const bool3& b) { return bool3(a.x >= b.x, a.y >= b.y, a.z >= b.z); }
	bool4 greater_equal(const bool4& a, const bool4& b) { return bool4(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w); }
//$pycgen-end


/*$pycgen
	code = """
	T sign(T v) { return T(T(0) < v) - T(v < T(0)); }
	T2 sign(const T2& v) { return T2(less(T2(T(0)), v)) - T2(less(v, T2(T(0)))); }
	T3 sign(const T3& v) { return T3(less(T3(T(0)), v)) - T3(less(v, T3(T(0)))); }
	T4 sign(const T4& v) { return T4(less(T4(T(0)), v)) - T4(less(v, T4(T(0)))); }
	"""
	EmitRepl(code, "T:" + signed_types)
*/
//$pycgen-begin
	float sign(float v) { return float(float(0) < v) - float(v < float(0)); }
	float2 sign(const float2& v) { return float2(less(float2(float(0)), v)) - float2(less(v, float2(float(0)))); }
	float3 sign(const float3& v) { return float3(less(float3(float(0)), v)) - float3(less(v, float3(float(0)))); }
	float4 sign(const float4& v) { return float4(less(float4(float(0)), v)) - float4(less(v, float4(float(0)))); }
	int sign(int v) { return int(int(0) < v) - int(v < int(0)); }
	int2 sign(const int2& v) { return int2(less(int2(int(0)), v)) - int2(less(v, int2(int(0)))); }
	int3 sign(const int3& v) { return int3(less(int3(int(0)), v)) - int3(less(v, int3(int(0)))); }
	int4 sign(const int4& v) { return int4(less(int4(int(0)), v)) - int4(less(v, int4(int(0)))); }
//$pycgen-end



/*$pycgen
	code = """
	T dot(const T2& a, const T2& b) { T2 tmp = a * b; return tmp.x + tmp.y; }
	T dot(const T3& a, const T3& b) { T3 tmp = a * b; return tmp.x + tmp.y + tmp.z; }
	T dot(const T4& a, const T4& b) { T4 tmp = a * b; return tmp.x + tmp.y + tmp.z + tmp.w; }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	float dot(const float2& a, const float2& b) { float2 tmp = a * b; return tmp.x + tmp.y; }
	float dot(const float3& a, const float3& b) { float3 tmp = a * b; return tmp.x + tmp.y + tmp.z; }
	float dot(const float4& a, const float4& b) { float4 tmp = a * b; return tmp.x + tmp.y + tmp.z + tmp.w; }
	int dot(const int2& a, const int2& b) { int2 tmp = a * b; return tmp.x + tmp.y; }
	int dot(const int3& a, const int3& b) { int3 tmp = a * b; return tmp.x + tmp.y + tmp.z; }
	int dot(const int4& a, const int4& b) { int4 tmp = a * b; return tmp.x + tmp.y + tmp.z + tmp.w; }
	uint dot(const uint2& a, const uint2& b) { uint2 tmp = a * b; return tmp.x + tmp.y; }
	uint dot(const uint3& a, const uint3& b) { uint3 tmp = a * b; return tmp.x + tmp.y + tmp.z; }
	uint dot(const uint4& a, const uint4& b) { uint4 tmp = a * b; return tmp.x + tmp.y + tmp.z + tmp.w; }
//$pycgen-end

	
/*$pycgen
	code = """
	T3 cross(const T3& a, const T3& b)
	{
		return T3(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y
		);
	}
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float3 cross(const float3& a, const float3& b)
	{
		return float3(
			a.y * b.z - b.y * a.z,
			a.z * b.x - b.z * a.x,
			a.x * b.y - b.x * a.y
		);
	}
//$pycgen-end


/*$pycgen
	code = """
	T length(const T2& v) { return T(sqrt(dot(v, v))); }
	T length(const T3& v) { return T(sqrt(dot(v, v))); }
	T length(const T4& v) { return T(sqrt(dot(v, v))); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float length(const float2& v) { return float(sqrt(dot(v, v))); }
	float length(const float3& v) { return float(sqrt(dot(v, v))); }
	float length(const float4& v) { return float(sqrt(dot(v, v))); }
//$pycgen-end


/*$pycgen
	code = """
	T length2(const T2& v) { return dot(v, v); }
	T length2(const T3& v) { return dot(v, v); }
	T length2(const T4& v) { return dot(v, v); }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	float length2(const float2& v) { return dot(v, v); }
	float length2(const float3& v) { return dot(v, v); }
	float length2(const float4& v) { return dot(v, v); }
	int length2(const int2& v) { return dot(v, v); }
	int length2(const int3& v) { return dot(v, v); }
	int length2(const int4& v) { return dot(v, v); }
	uint length2(const uint2& v) { return dot(v, v); }
	uint length2(const uint3& v) { return dot(v, v); }
	uint length2(const uint4& v) { return dot(v, v); }
//$pycgen-end
	

/*$pycgen
	code = """
	T distance(const T2& a, const T2& b) { return length(b - a); }
	T distance(const T3& a, const T3& b) { return length(b - a); }
	T distance(const T4& a, const T4& b) { return length(b - a); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float distance(const float2& a, const float2& b) { return length(b - a); }
	float distance(const float3& a, const float3& b) { return length(b - a); }
	float distance(const float4& a, const float4& b) { return length(b - a); }
//$pycgen-end


/*$pycgen
	code = """
	T2 normalize(const T2& v) { return v * T(1) / sqrt(dot(v, v)); }
	T3 normalize(const T3& v) { return v * T(1) / sqrt(dot(v, v)); }
	T4 normalize(const T4& v) { return v * T(1) / sqrt(dot(v, v)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float2 normalize(const float2& v) { return v * float(1) / sqrt(dot(v, v)); }
	float3 normalize(const float3& v) { return v * float(1) / sqrt(dot(v, v)); }
	float4 normalize(const float4& v) { return v * float(1) / sqrt(dot(v, v)); }
//$pycgen-end



/*$pycgen
	code = """
	T2 abs(const T2& v) { return T2(abs(v.x), abs(v.y)); }
	T3 abs(const T3& v) { return T3(abs(v.x), abs(v.y), abs(v.z)); }
	T4 abs(const T4& v) { return T4(abs(v.x), abs(v.y), abs(v.z), abs(v.w)); }
	"""
	EmitRepl(code, "T:" + signed_types)
*/
//$pycgen-begin
	float2 abs(const float2& v) { return float2(abs(v.x), abs(v.y)); }
	float3 abs(const float3& v) { return float3(abs(v.x), abs(v.y), abs(v.z)); }
	float4 abs(const float4& v) { return float4(abs(v.x), abs(v.y), abs(v.z), abs(v.w)); }
	int2 abs(const int2& v) { return int2(abs(v.x), abs(v.y)); }
	int3 abs(const int3& v) { return int3(abs(v.x), abs(v.y), abs(v.z)); }
	int4 abs(const int4& v) { return int4(abs(v.x), abs(v.y), abs(v.z), abs(v.w)); }
//$pycgen-end

	
/*$pycgen
	code = """
	T2 mod(const T2& a, const T2& b) { return T2(fmod(a.x, b.x), fmod(a.y, b.y)); }
	T3 mod(const T3& a, const T3& b) { return T3(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z)); }
	T4 mod(const T4& a, const T4& b) { return T4(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z), fmod(a.w, b.w)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float2 mod(const float2& a, const float2& b) { return float2(fmod(a.x, b.x), fmod(a.y, b.y)); }
	float3 mod(const float3& a, const float3& b) { return float3(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z)); }
	float4 mod(const float4& a, const float4& b) { return float4(fmod(a.x, b.x), fmod(a.y, b.y), fmod(a.z, b.z), fmod(a.w, b.w)); }
//$pycgen-end
	
	
/*$pycgen
	code = """
	T mod(const T& a, const T& b) { return a % b; }
	T2 mod(const T2& a, const T2& b) { return T2(a.x % b.x, a.y % b.y); }
	T3 mod(const T3& a, const T3& b) { return T3(a.x % b.x, a.y % b.y, a.z % b.z); }
	T4 mod(const T4& a, const T4& b) { return T4(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w); }
	"""
	EmitRepl(code, "T:" + int_types)
*/
//$pycgen-begin
	int mod(const int& a, const int& b) { return a % b; }
	int2 mod(const int2& a, const int2& b) { return int2(a.x % b.x, a.y % b.y); }
	int3 mod(const int3& a, const int3& b) { return int3(a.x % b.x, a.y % b.y, a.z % b.z); }
	int4 mod(const int4& a, const int4& b) { return int4(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w); }
	uint mod(const uint& a, const uint& b) { return a % b; }
	uint2 mod(const uint2& a, const uint2& b) { return uint2(a.x % b.x, a.y % b.y); }
	uint3 mod(const uint3& a, const uint3& b) { return uint3(a.x % b.x, a.y % b.y, a.z % b.z); }
	uint4 mod(const uint4& a, const uint4& b) { return uint4(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w); }
//$pycgen-end


/*$pycgen
	code = """
	T2 min(const T2& a, const T2& b) { return T2(min(a.x, b.x), min(a.y, b.y)); }
	T3 min(const T3& a, const T3& b) { return T3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)); }
	T4 min(const T4& a, const T4& b) { return T4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); }
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	float2 min(const float2& a, const float2& b) { return float2(min(a.x, b.x), min(a.y, b.y)); }
	float3 min(const float3& a, const float3& b) { return float3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)); }
	float4 min(const float4& a, const float4& b) { return float4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); }
	int2 min(const int2& a, const int2& b) { return int2(min(a.x, b.x), min(a.y, b.y)); }
	int3 min(const int3& a, const int3& b) { return int3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)); }
	int4 min(const int4& a, const int4& b) { return int4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); }
	uint2 min(const uint2& a, const uint2& b) { return uint2(min(a.x, b.x), min(a.y, b.y)); }
	uint3 min(const uint3& a, const uint3& b) { return uint3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)); }
	uint4 min(const uint4& a, const uint4& b) { return uint4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); }
	bool2 min(const bool2& a, const bool2& b) { return bool2(min(a.x, b.x), min(a.y, b.y)); }
	bool3 min(const bool3& a, const bool3& b) { return bool3(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)); }
	bool4 min(const bool4& a, const bool4& b) { return bool4(min(a.x, b.x), min(a.y, b.y), min(a.z, b.z), min(a.w, b.w)); }
//$pycgen-end


/*$pycgen
	code = """
	T2 max(const T2& a, const T2& b) { return T2(max(a.x, b.x), max(a.y, b.y)); }
	T3 max(const T3& a, const T3& b) { return T3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)); }
	T4 max(const T4& a, const T4& b) { return T4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); }
	"""
	EmitRepl(code, "T:" + vector_types)
*/
//$pycgen-begin
	float2 max(const float2& a, const float2& b) { return float2(max(a.x, b.x), max(a.y, b.y)); }
	float3 max(const float3& a, const float3& b) { return float3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)); }
	float4 max(const float4& a, const float4& b) { return float4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); }
	int2 max(const int2& a, const int2& b) { return int2(max(a.x, b.x), max(a.y, b.y)); }
	int3 max(const int3& a, const int3& b) { return int3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)); }
	int4 max(const int4& a, const int4& b) { return int4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); }
	uint2 max(const uint2& a, const uint2& b) { return uint2(max(a.x, b.x), max(a.y, b.y)); }
	uint3 max(const uint3& a, const uint3& b) { return uint3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)); }
	uint4 max(const uint4& a, const uint4& b) { return uint4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); }
	bool2 max(const bool2& a, const bool2& b) { return bool2(max(a.x, b.x), max(a.y, b.y)); }
	bool3 max(const bool3& a, const bool3& b) { return bool3(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)); }
	bool4 max(const bool4& a, const bool4& b) { return bool4(max(a.x, b.x), max(a.y, b.y), max(a.z, b.z), max(a.w, b.w)); }
//$pycgen-end


/*$pycgen
	code = """
	//T clamp(T v, T lo, T hi) { return min(max(v, lo), hi); }
	T2 clamp(const T2& v, T lo, T hi) { return min(max(v, lo), hi); }
	T2 clamp(const T2& v, const T2& lo, const T2& hi) { return min(max(v, lo), hi); }
	T3 clamp(const T3& v, T lo, T hi) { return min(max(v, lo), hi); }
	T3 clamp(const T3& v, const T3& lo, const T3& hi) { return min(max(v, lo), hi); }
	T4 clamp(const T4& v, T lo, T hi) { return min(max(v, lo), hi); }
	T4 clamp(const T4& v, const T4& lo, const T4& hi) { return min(max(v, lo), hi); }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	//float clamp(float v, float lo, float hi) { return min(max(v, lo), hi); }
	float2 clamp(const float2& v, float lo, float hi) { return min(max(v, lo), hi); }
	float2 clamp(const float2& v, const float2& lo, const float2& hi) { return min(max(v, lo), hi); }
	float3 clamp(const float3& v, float lo, float hi) { return min(max(v, lo), hi); }
	float3 clamp(const float3& v, const float3& lo, const float3& hi) { return min(max(v, lo), hi); }
	float4 clamp(const float4& v, float lo, float hi) { return min(max(v, lo), hi); }
	float4 clamp(const float4& v, const float4& lo, const float4& hi) { return min(max(v, lo), hi); }
	//int clamp(int v, int lo, int hi) { return min(max(v, lo), hi); }
	int2 clamp(const int2& v, int lo, int hi) { return min(max(v, lo), hi); }
	int2 clamp(const int2& v, const int2& lo, const int2& hi) { return min(max(v, lo), hi); }
	int3 clamp(const int3& v, int lo, int hi) { return min(max(v, lo), hi); }
	int3 clamp(const int3& v, const int3& lo, const int3& hi) { return min(max(v, lo), hi); }
	int4 clamp(const int4& v, int lo, int hi) { return min(max(v, lo), hi); }
	int4 clamp(const int4& v, const int4& lo, const int4& hi) { return min(max(v, lo), hi); }
	//uint clamp(uint v, uint lo, uint hi) { return min(max(v, lo), hi); }
	uint2 clamp(const uint2& v, uint lo, uint hi) { return min(max(v, lo), hi); }
	uint2 clamp(const uint2& v, const uint2& lo, const uint2& hi) { return min(max(v, lo), hi); }
	uint3 clamp(const uint3& v, uint lo, uint hi) { return min(max(v, lo), hi); }
	uint3 clamp(const uint3& v, const uint3& lo, const uint3& hi) { return min(max(v, lo), hi); }
	uint4 clamp(const uint4& v, uint lo, uint hi) { return min(max(v, lo), hi); }
	uint4 clamp(const uint4& v, const uint4& lo, const uint4& hi) { return min(max(v, lo), hi); }
//$pycgen-end


/*$pycgen
	code = """
	T saturate(T v) { return clamp(v, T(0), T(1)); }
	T2 saturate(const T2& v) { return clamp(v, T(0), T(1)); }
	T3 saturate(const T3& v) { return clamp(v, T(0), T(1)); }
	T4 saturate(const T4& v) { return clamp(v, T(0), T(1)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float saturate(float v) { return clamp(v, float(0), float(1)); }
	float2 saturate(const float2& v) { return clamp(v, float(0), float(1)); }
	float3 saturate(const float3& v) { return clamp(v, float(0), float(1)); }
	float4 saturate(const float4& v) { return clamp(v, float(0), float(1)); }
//$pycgen-end


/*$pycgen
	code = """
	T2 floor(const T2& v) { return T2(floor(v.x), floor(v.y)); }
	T3 floor(const T3& v) { return T3(floor(v.x), floor(v.y), floor(v.z)); }
	T4 floor(const T4& v) { return T4(floor(v.x), floor(v.y), floor(v.z), floor(v.w)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float2 floor(const float2& v) { return float2(floor(v.x), floor(v.y)); }
	float3 floor(const float3& v) { return float3(floor(v.x), floor(v.y), floor(v.z)); }
	float4 floor(const float4& v) { return float4(floor(v.x), floor(v.y), floor(v.z), floor(v.w)); }
//$pycgen-end


/*$pycgen
	code = """
	T2 ceil(const T2& v) { return T2(ceil(v.x), ceil(v.y)); }
	T3 ceil(const T3& v) { return T3(ceil(v.x), ceil(v.y), ceil(v.z)); }
	T4 ceil(const T4& v) { return T4(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float2 ceil(const float2& v) { return float2(ceil(v.x), ceil(v.y)); }
	float3 ceil(const float3& v) { return float3(ceil(v.x), ceil(v.y), ceil(v.z)); }
	float4 ceil(const float4& v) { return float4(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w)); }
//$pycgen-end

	
/*$pycgen
	code = """
	T2 cos(const T2& v) { return T2(cos(v.x), cos(v.y)); }
	T3 cos(const T3& v) { return T3(cos(v.x), cos(v.y), cos(v.z)); }
	T4 cos(const T4& v) { return T4(cos(v.x), cos(v.y), cos(v.z), cos(v.w)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float2 cos(const float2& v) { return float2(cos(v.x), cos(v.y)); }
	float3 cos(const float3& v) { return float3(cos(v.x), cos(v.y), cos(v.z)); }
	float4 cos(const float4& v) { return float4(cos(v.x), cos(v.y), cos(v.z), cos(v.w)); }
//$pycgen-end
	

/*$pycgen
	code = """
	T2 sin(const T2& v) { return T2(sin(v.x), sin(v.y)); }
	T3 sin(const T3& v) { return T3(sin(v.x), sin(v.y), sin(v.z)); }
	T4 sin(const T4& v) { return T4(sin(v.x), sin(v.y), sin(v.z), sin(v.w)); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float2 sin(const float2& v) { return float2(sin(v.x), sin(v.y)); }
	float3 sin(const float3& v) { return float3(sin(v.x), sin(v.y), sin(v.z)); }
	float4 sin(const float4& v) { return float4(sin(v.x), sin(v.y), sin(v.z), sin(v.w)); }
//$pycgen-end


/*$pycgen
	code = """
	T lerp(T a, T b, T t) { return T(a) + t * T(b - a); }
	T2 lerp(const T2& a, const T2& b, T t) { return T2(a) + t * T2(b - a); }
	T3 lerp(const T3& a, const T3& b, T t) { return T3(a) + t * T3(b - a); }
	T4 lerp(const T4& a, const T4& b, T t) { return T4(a) + t * T4(b - a); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float lerp(float a, float b, float t) { return float(a) + t * float(b - a); }
	float2 lerp(const float2& a, const float2& b, float t) { return float2(a) + t * float2(b - a); }
	float3 lerp(const float3& a, const float3& b, float t) { return float3(a) + t * float3(b - a); }
	float4 lerp(const float4& a, const float4& b, float t) { return float4(a) + t * float4(b - a); }
//$pycgen-end


/*$pycgen
	code = """
	T spline(T a, T b, T c, T d, T t);
	T2 spline(const T2& a, const T2& b, const T2& c, const T2& d, T t);
	T3 spline(const T3& a, const T3& b, const T3& c, const T3& d, T t);
	T4 spline(const T4& a, const T4& b, const T4& c, const T4& d, T t);
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float spline(float a, float b, float c, float d, float t);
	float2 spline(const float2& a, const float2& b, const float2& c, const float2& d, float t);
	float3 spline(const float3& a, const float3& b, const float3& c, const float3& d, float t);
	float4 spline(const float4& a, const float4& b, const float4& c, const float4& d, float t);
//$pycgen-end

	
/*$pycgen
	code = """
	T angle(T a, T b) { return acos(clamp(a * b, T(-1), T(1))); }
	T angle(const T2& a, const T2& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }
	T angle(const T3& a, const T3& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }
	T angle(const T4& a, const T4& b) { return acos(clamp(dot(a, b), T(-1), T(1))); }
	"""
	EmitRepl(code, "T:" + float_types)
*/
//$pycgen-begin
	float angle(float a, float b) { return acos(clamp(a * b, float(-1), float(1))); }
	float angle(const float2& a, const float2& b) { return acos(clamp(dot(a, b), float(-1), float(1))); }
	float angle(const float3& a, const float3& b) { return acos(clamp(dot(a, b), float(-1), float(1))); }
	float angle(const float4& a, const float4& b) { return acos(clamp(dot(a, b), float(-1), float(1))); }
//$pycgen-end



/*$pycgen
	code = """
	T2 operator+(const T2& a, const T2& b) { return T2(a.x + b.x, a.y + b.y); }
	T3 operator+(const T3& a, const T3& b) { return T3(a.x + b.x, a.y + b.y, a.z + b.z); }
	T4 operator+(const T4& a, const T4& b) { return T4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	T2 operator+(const T2& a, T b) { return T2(a.x + b, a.y + b); }
	T3 operator+(const T3& a, T b) { return T3(a.x + b, a.y + b, a.z + b); }
	T4 operator+(const T4& a, T b) { return T4(a.x + b, a.y + b, a.z + b, a.w + b); }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	float2 operator+(const float2& a, const float2& b) { return float2(a.x + b.x, a.y + b.y); }
	float3 operator+(const float3& a, const float3& b) { return float3(a.x + b.x, a.y + b.y, a.z + b.z); }
	float4 operator+(const float4& a, const float4& b) { return float4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	float2 operator+(const float2& a, float b) { return float2(a.x + b, a.y + b); }
	float3 operator+(const float3& a, float b) { return float3(a.x + b, a.y + b, a.z + b); }
	float4 operator+(const float4& a, float b) { return float4(a.x + b, a.y + b, a.z + b, a.w + b); }
	int2 operator+(const int2& a, const int2& b) { return int2(a.x + b.x, a.y + b.y); }
	int3 operator+(const int3& a, const int3& b) { return int3(a.x + b.x, a.y + b.y, a.z + b.z); }
	int4 operator+(const int4& a, const int4& b) { return int4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	int2 operator+(const int2& a, int b) { return int2(a.x + b, a.y + b); }
	int3 operator+(const int3& a, int b) { return int3(a.x + b, a.y + b, a.z + b); }
	int4 operator+(const int4& a, int b) { return int4(a.x + b, a.y + b, a.z + b, a.w + b); }
	uint2 operator+(const uint2& a, const uint2& b) { return uint2(a.x + b.x, a.y + b.y); }
	uint3 operator+(const uint3& a, const uint3& b) { return uint3(a.x + b.x, a.y + b.y, a.z + b.z); }
	uint4 operator+(const uint4& a, const uint4& b) { return uint4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	uint2 operator+(const uint2& a, uint b) { return uint2(a.x + b, a.y + b); }
	uint3 operator+(const uint3& a, uint b) { return uint3(a.x + b, a.y + b, a.z + b); }
	uint4 operator+(const uint4& a, uint b) { return uint4(a.x + b, a.y + b, a.z + b, a.w + b); }
//$pycgen-end


/*$pycgen
	code = """
	T2 operator-(const T2& a, const T2& b) { return T2(a.x - b.x, a.y - b.y); }
	T3 operator-(const T3& a, const T3& b) { return T3(a.x - b.x, a.y - b.y, a.z - b.z); }
	T4 operator-(const T4& a, const T4& b) { return T4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	T2 operator-(const T2& a, T b) { return T2(a.x - b, a.y - b); }
	T3 operator-(const T3& a, T b) { return T3(a.x - b, a.y - b, a.z - b); }
	T4 operator-(const T4& a, T b) { return T4(a.x - b, a.y - b, a.z - b, a.w - b); }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	float2 operator-(const float2& a, const float2& b) { return float2(a.x - b.x, a.y - b.y); }
	float3 operator-(const float3& a, const float3& b) { return float3(a.x - b.x, a.y - b.y, a.z - b.z); }
	float4 operator-(const float4& a, const float4& b) { return float4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	float2 operator-(const float2& a, float b) { return float2(a.x - b, a.y - b); }
	float3 operator-(const float3& a, float b) { return float3(a.x - b, a.y - b, a.z - b); }
	float4 operator-(const float4& a, float b) { return float4(a.x - b, a.y - b, a.z - b, a.w - b); }
	int2 operator-(const int2& a, const int2& b) { return int2(a.x - b.x, a.y - b.y); }
	int3 operator-(const int3& a, const int3& b) { return int3(a.x - b.x, a.y - b.y, a.z - b.z); }
	int4 operator-(const int4& a, const int4& b) { return int4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	int2 operator-(const int2& a, int b) { return int2(a.x - b, a.y - b); }
	int3 operator-(const int3& a, int b) { return int3(a.x - b, a.y - b, a.z - b); }
	int4 operator-(const int4& a, int b) { return int4(a.x - b, a.y - b, a.z - b, a.w - b); }
	uint2 operator-(const uint2& a, const uint2& b) { return uint2(a.x - b.x, a.y - b.y); }
	uint3 operator-(const uint3& a, const uint3& b) { return uint3(a.x - b.x, a.y - b.y, a.z - b.z); }
	uint4 operator-(const uint4& a, const uint4& b) { return uint4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
	uint2 operator-(const uint2& a, uint b) { return uint2(a.x - b, a.y - b); }
	uint3 operator-(const uint3& a, uint b) { return uint3(a.x - b, a.y - b, a.z - b); }
	uint4 operator-(const uint4& a, uint b) { return uint4(a.x - b, a.y - b, a.z - b, a.w - b); }
//$pycgen-end


/*$pycgen
	code = """
	T2 operator*(const T2& a, const T2& b) { return T2(a.x * b.x, a.y * b.y); }
	T3 operator*(const T3& a, const T3& b) { return T3(a.x * b.x, a.y * b.y, a.z * b.z); }
	T4 operator*(const T4& a, const T4& b) { return T4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	T2 operator*(const T2& a, T b) { return T2(a.x * b, a.y * b); }
	T3 operator*(const T3& a, T b) { return T3(a.x * b, a.y * b, a.z * b); }
	T4 operator*(const T4& a, T b) { return T4(a.x * b, a.y * b, a.z * b, a.w * b); }
	T2 operator*(T a, const T2& b) { return T2(a * b.x, a * b.y); }
	T3 operator*(T a, const T3& b) { return T3(a * b.x, a * b.y, a * b.z); }
	T4 operator*(T a, const T4& b) { return T4(a * b.x, a * b.y, a * b.z, a * b.w); }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	float2 operator*(const float2& a, const float2& b) { return float2(a.x * b.x, a.y * b.y); }
	float3 operator*(const float3& a, const float3& b) { return float3(a.x * b.x, a.y * b.y, a.z * b.z); }
	float4 operator*(const float4& a, const float4& b) { return float4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	float2 operator*(const float2& a, float b) { return float2(a.x * b, a.y * b); }
	float3 operator*(const float3& a, float b) { return float3(a.x * b, a.y * b, a.z * b); }
	float4 operator*(const float4& a, float b) { return float4(a.x * b, a.y * b, a.z * b, a.w * b); }
	float2 operator*(float a, const float2& b) { return float2(a * b.x, a * b.y); }
	float3 operator*(float a, const float3& b) { return float3(a * b.x, a * b.y, a * b.z); }
	float4 operator*(float a, const float4& b) { return float4(a * b.x, a * b.y, a * b.z, a * b.w); }
	int2 operator*(const int2& a, const int2& b) { return int2(a.x * b.x, a.y * b.y); }
	int3 operator*(const int3& a, const int3& b) { return int3(a.x * b.x, a.y * b.y, a.z * b.z); }
	int4 operator*(const int4& a, const int4& b) { return int4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	int2 operator*(const int2& a, int b) { return int2(a.x * b, a.y * b); }
	int3 operator*(const int3& a, int b) { return int3(a.x * b, a.y * b, a.z * b); }
	int4 operator*(const int4& a, int b) { return int4(a.x * b, a.y * b, a.z * b, a.w * b); }
	int2 operator*(int a, const int2& b) { return int2(a * b.x, a * b.y); }
	int3 operator*(int a, const int3& b) { return int3(a * b.x, a * b.y, a * b.z); }
	int4 operator*(int a, const int4& b) { return int4(a * b.x, a * b.y, a * b.z, a * b.w); }
	uint2 operator*(const uint2& a, const uint2& b) { return uint2(a.x * b.x, a.y * b.y); }
	uint3 operator*(const uint3& a, const uint3& b) { return uint3(a.x * b.x, a.y * b.y, a.z * b.z); }
	uint4 operator*(const uint4& a, const uint4& b) { return uint4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
	uint2 operator*(const uint2& a, uint b) { return uint2(a.x * b, a.y * b); }
	uint3 operator*(const uint3& a, uint b) { return uint3(a.x * b, a.y * b, a.z * b); }
	uint4 operator*(const uint4& a, uint b) { return uint4(a.x * b, a.y * b, a.z * b, a.w * b); }
	uint2 operator*(uint a, const uint2& b) { return uint2(a * b.x, a * b.y); }
	uint3 operator*(uint a, const uint3& b) { return uint3(a * b.x, a * b.y, a * b.z); }
	uint4 operator*(uint a, const uint4& b) { return uint4(a * b.x, a * b.y, a * b.z, a * b.w); }
//$pycgen-end


/*$pycgen
	code = """
	T2 operator/(const T2& a, const T2& b) { return T2(a.x / b.x, a.y / b.y); }
	T3 operator/(const T3& a, const T3& b) { return T3(a.x / b.x, a.y / b.y, a.z / b.z); }
	T4 operator/(const T4& a, const T4& b) { return T4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	T2 operator/(const T2& a, T b) { return T2(a.x / b, a.y / b); }
	T3 operator/(const T3& a, T b) { return T3(a.x / b, a.y / b, a.z / b); }
	T4 operator/(const T4& a, T b) { return T4(a.x / b, a.y / b, a.z / b, a.w / b); }
	T2 operator/(T a, const T2& b) { return T2(a / b.x, a / b.y); }
	T3 operator/(T a, const T3& b) { return T3(a / b.x, a / b.y, a / b.z); }
	T4 operator/(T a, const T4& b) { return T4(a / b.x, a / b.y, a / b.z, a / b.w); }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	float2 operator/(const float2& a, const float2& b) { return float2(a.x / b.x, a.y / b.y); }
	float3 operator/(const float3& a, const float3& b) { return float3(a.x / b.x, a.y / b.y, a.z / b.z); }
	float4 operator/(const float4& a, const float4& b) { return float4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	float2 operator/(const float2& a, float b) { return float2(a.x / b, a.y / b); }
	float3 operator/(const float3& a, float b) { return float3(a.x / b, a.y / b, a.z / b); }
	float4 operator/(const float4& a, float b) { return float4(a.x / b, a.y / b, a.z / b, a.w / b); }
	float2 operator/(float a, const float2& b) { return float2(a / b.x, a / b.y); }
	float3 operator/(float a, const float3& b) { return float3(a / b.x, a / b.y, a / b.z); }
	float4 operator/(float a, const float4& b) { return float4(a / b.x, a / b.y, a / b.z, a / b.w); }
	int2 operator/(const int2& a, const int2& b) { return int2(a.x / b.x, a.y / b.y); }
	int3 operator/(const int3& a, const int3& b) { return int3(a.x / b.x, a.y / b.y, a.z / b.z); }
	int4 operator/(const int4& a, const int4& b) { return int4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	int2 operator/(const int2& a, int b) { return int2(a.x / b, a.y / b); }
	int3 operator/(const int3& a, int b) { return int3(a.x / b, a.y / b, a.z / b); }
	int4 operator/(const int4& a, int b) { return int4(a.x / b, a.y / b, a.z / b, a.w / b); }
	int2 operator/(int a, const int2& b) { return int2(a / b.x, a / b.y); }
	int3 operator/(int a, const int3& b) { return int3(a / b.x, a / b.y, a / b.z); }
	int4 operator/(int a, const int4& b) { return int4(a / b.x, a / b.y, a / b.z, a / b.w); }
	uint2 operator/(const uint2& a, const uint2& b) { return uint2(a.x / b.x, a.y / b.y); }
	uint3 operator/(const uint3& a, const uint3& b) { return uint3(a.x / b.x, a.y / b.y, a.z / b.z); }
	uint4 operator/(const uint4& a, const uint4& b) { return uint4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }
	uint2 operator/(const uint2& a, uint b) { return uint2(a.x / b, a.y / b); }
	uint3 operator/(const uint3& a, uint b) { return uint3(a.x / b, a.y / b, a.z / b); }
	uint4 operator/(const uint4& a, uint b) { return uint4(a.x / b, a.y / b, a.z / b, a.w / b); }
	uint2 operator/(uint a, const uint2& b) { return uint2(a / b.x, a / b.y); }
	uint3 operator/(uint a, const uint3& b) { return uint3(a / b.x, a / b.y, a / b.z); }
	uint4 operator/(uint a, const uint4& b) { return uint4(a / b.x, a / b.y, a / b.z, a / b.w); }
//$pycgen-end


/*$pycgen
	code = """
	T2 operator-(const T2& a) { return T2(-a.x, -a.y); }
	T3 operator-(const T3& a) { return T3(-a.x, -a.y, -a.z); }
	T4 operator-(const T4& a) { return T4(-a.x, -a.y, -a.z, -a.w); }
	"""
	EmitRepl(code, "T:" + signed_types)
*/
//$pycgen-begin
	float2 operator-(const float2& a) { return float2(-a.x, -a.y); }
	float3 operator-(const float3& a) { return float3(-a.x, -a.y, -a.z); }
	float4 operator-(const float4& a) { return float4(-a.x, -a.y, -a.z, -a.w); }
	int2 operator-(const int2& a) { return int2(-a.x, -a.y); }
	int3 operator-(const int3& a) { return int3(-a.x, -a.y, -a.z); }
	int4 operator-(const int4& a) { return int4(-a.x, -a.y, -a.z, -a.w); }
//$pycgen-end


/*$pycgen
	code = """
	T2& operator+=(T2& a, const T2& b) { a = a + b; return a; }
	T3& operator+=(T3& a, const T3& b) { a = a + b; return a; }
	T4& operator+=(T4& a, const T4& b) { a = a + b; return a; }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	float2& operator+=(float2& a, const float2& b) { a = a + b; return a; }
	float3& operator+=(float3& a, const float3& b) { a = a + b; return a; }
	float4& operator+=(float4& a, const float4& b) { a = a + b; return a; }
	int2& operator+=(int2& a, const int2& b) { a = a + b; return a; }
	int3& operator+=(int3& a, const int3& b) { a = a + b; return a; }
	int4& operator+=(int4& a, const int4& b) { a = a + b; return a; }
	uint2& operator+=(uint2& a, const uint2& b) { a = a + b; return a; }
	uint3& operator+=(uint3& a, const uint3& b) { a = a + b; return a; }
	uint4& operator+=(uint4& a, const uint4& b) { a = a + b; return a; }
//$pycgen-end

	
/*$pycgen
	code = """
	T2& operator*=(T2& a, const T2& b) { a = a * b; return a; }
	T3& operator*=(T3& a, const T3& b) { a = a * b; return a; }
	T4& operator*=(T4& a, const T4& b) { a = a * b; return a; }
	"""
	EmitRepl(code, "T:" + scalar_types)
*/
//$pycgen-begin
	float2& operator*=(float2& a, const float2& b) { a = a * b; return a; }
	float3& operator*=(float3& a, const float3& b) { a = a * b; return a; }
	float4& operator*=(float4& a, const float4& b) { a = a * b; return a; }
	int2& operator*=(int2& a, const int2& b) { a = a * b; return a; }
	int3& operator*=(int3& a, const int3& b) { a = a * b; return a; }
	int4& operator*=(int4& a, const int4& b) { a = a * b; return a; }
	uint2& operator*=(uint2& a, const uint2& b) { a = a * b; return a; }
	uint3& operator*=(uint3& a, const uint3& b) { a = a * b; return a; }
	uint4& operator*=(uint4& a, const uint4& b) { a = a * b; return a; }
//$pycgen-end


	quat operator+(const quat& q) { return q; }
	quat operator-(const quat& v) { return quat(-v.x, -v.y, -v.z, -v.w); }

	quat operator+(const quat& a, const quat& b) { return quat(a.w + b.w, a.x + b.x, a.y + b.y, a.z + b.z); }
	quat operator-(const quat& a, const quat& b) { return quat(a.w - b.w, a.x - b.x, a.y - b.y, a.z - b.z); }

	quat operator*(const quat& q, float s) { return quat(q.w * s, q.x * s, q.y * s, q.z * s); }
	quat operator/(const quat& q, float s) { return quat(q.w / s, q.x / s, q.y / s, q.z / s); }
	quat operator*(float s, const quat& q) { return quat(q.w * s, q.x * s, q.y * s, q.z * s); }
	quat operator/(float s, const quat& q) { return quat(q.w / s, q.x / s, q.y / s, q.z / s); }

	quat operator*(const quat& a, const quat& b)
	{
		return quat(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
			a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
		);
	}

	float3 operator*(const quat& q, const float3& v)
	{
		const float3 QuatVector(q.x, q.y, q.z);
		const float3 uv(cross(QuatVector, v));
		const float3 uuv(cross(QuatVector, uv));

		return v + ((uv * q.w) + uuv) * float(2);
	}

	float4 operator*(const quat& q, const float4& v)
	{
		return float4(q * xyz(v), v.w);
	}

	quat conjugate(const quat& q) { return quat(-q.x, -q.y, -q.z, q.w); }
	quat inverse(const quat& q) { return conjugate(q) / dot(q, q); }
		
	quat normalize(const quat& q)
	{
		float len = length(q);
		if(len <= float(0))
			return quat(float(0), float(0), float(0), float(1));
		float inverse_len = float(1) / len;
		return quat(q.x * inverse_len, q.y * inverse_len, q.z * inverse_len, q.w * inverse_len);
	}

	//bool operator==(const quat& q1, const quat& q2) { return all(equal(q1, q2, epsilon<float>())); }
	//bool operator!=(const quat& q1, const quat& q2) { return any(not_equal(q1, q2, epsilon<float>())); }

	float dot(const quat& a, const quat& b)
	{
		float4 tmp(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
		return (tmp.x + tmp.y) + (tmp.z + tmp.w);
	}

	quat lerp(const quat& a, const quat& b, float t)
	{
		float4 vec = lerp((float4&)a, (float4&)b, t);
		return quat(vec.x, vec.y, vec.z, vec.w);
	}

	quat slerp(const quat& x, const quat& y, float a)
	{
		quat z = y;

		float cosTheta = dot(x, y);

		// If cosTheta < 0, the interpolation will take the long way around the sphere. 
		// To fix this, one quat must be negated.
		if(cosTheta < float(0))
		{
			z = -y;
			cosTheta = -cosTheta;
		}

		// Perform a linear interpolation when cosTheta is close to 1 to avoid side effect of sin(angle) becoming a zero denominator
		if(cosTheta > float(1) - epsilon<float>())
		{
			// Linear interpolation
			return quat(mix(x.x, z.x, a), mix(x.y, z.y, a), mix(x.z, z.z, a), mix(x.w, z.w, a));
		}
		else
		{
			// Essential Mathematics, page 467
			float angle = acos(cosTheta);
			return (sin((float(1) - a) * angle) * x + sin(a * angle) * z) / sin(angle);
		}
	}

	float oriented_angle(const float3& a, const float3& b, const float3& ref)
	{
		const float angle = acos(clamp(dot(a, b), float(-1), float(1)));
		return mix(angle, -angle, dot(ref, cross(a, b)) < float(0));
	}

	float oriented_angle(const float2& a, const float2& b)
	{
		const float angle = acos(clamp(dot(a, b), float(-1), float(1)));

		if(all(equal(b, rotate(a, angle), epsilon<float>())))
			return angle;
		else
			return -angle;
	}

	mat4 operator*(const mat4& m, float f)
	{
		mat4 result;
		result[0] = m[0] * f;
		result[1] = m[0] * f;
		result[2] = m[0] * f;
		result[3] = m[0] * f;
		return result;
	}

	mat4 transpose(const mat4& m)
	{
		mat4 result;
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[0][3] = m[3][0];

		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		result[1][3] = m[3][1];

		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		result[2][3] = m[3][2];

		result[3][0] = m[0][3];
		result[3][1] = m[1][3];
		result[3][2] = m[2][3];
		result[3][3] = m[3][3];
		return result;
	}

	mat4 inverse(const mat4& m)
	{
		const float c00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		const float c02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		const float c03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		const float c04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		const float c06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		const float c07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		const float c08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		const float c10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		const float c11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		const float c12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		const float c14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		const float c15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		const float c16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		const float c18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		const float c19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		const float c20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		const float c22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		const float c23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		float4 Fac0 = float4(c00, c00, c02, c03);
		float4 Fac1 = float4(c04, c04, c06, c07);
		float4 Fac2 = float4(c08, c08, c10, c11);
		float4 Fac3 = float4(c12, c12, c14, c15);
		float4 Fac4 = float4(c16, c16, c18, c19);
		float4 Fac5 = float4(c20, c20, c22, c23);

		float4 Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		float4 Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		float4 Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		float4 Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		float4 Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		float4 Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		float4 Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		float4 Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		float4 SignA(+1, -1, +1, -1);
		float4 SignB(-1, +1, -1, +1);
		mat4 Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		float4 Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		float4 Dot0(m[0] * Row0);
		float Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		float OneOverDeterminant = float(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}

	mat4 operator*(const mat4& m1, const mat4& m2)
	{
		const float4 a0 = m1[0];
		const float4 a1 = m1[1];
		const float4 a2 = m1[2];
		const float4 a3 = m1[3];

		const float4 b0 = m2[0];
		const float4 b1 = m2[1];
		const float4 b2 = m2[2];
		const float4 b3 = m2[3];

		mat4 result;
		result[0] = a0 * b0[0] + a1 * b0[1] + a2 * b0[2] + a3 * b0[3];
		result[1] = a0 * b1[0] + a1 * b1[1] + a2 * b1[2] + a3 * b1[3];
		result[2] = a0 * b2[0] + a1 * b2[1] + a2 * b2[2] + a3 * b2[3];
		result[3] = a0 * b3[0] + a1 * b3[1] + a2 * b3[2] + a3 * b3[3];
		return result;
	}

	float4 operator*(const mat4& m, const float4& v)
	{
		const float4 mov0(v[0]);
		const float4 mov1(v[1]);
		const float4 mul0 = m[0] * mov0;
		const float4 mul1 = m[1] * mov1;
		const float4 add0 = mul0 + mul1;
		const float4 mov2(v[2]);
		const float4 mov3(v[3]);
		const float4 mul2 = m[2] * mov2;
		const float4 mul3 = m[3] * mov3;
		const float4 add1 = mul2 + mul3;
		const float4 add2 = add0 + add1;
		return add2;
	}

#if 0

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
	bool 	vEquals(const int3& a, const int3& b, float epsilon);
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
	// Quaternion functions
	//
	quat qZero();
	quat qIdentity();
	quat qAxisAngle(const float3& v, float angle);
	float qNorm(const quat& q);
	quat qNormalise(const quat& q);
	quat qNegate(const quat& q);
	quat qConjugate(const quat& q);
	quat qInverse(const quat& q);
	quat qScale(const quat& q, float scale);
	float qDot(const quat& a, const quat& b);
	quat qMultiply(const quat& a, const quat& b);
	quat qMultiplyPure(const quat& a, const float3& b);
	float3 qTransformPos(const quat& q, const float3& p);
	double3 qTransformPos(const quat& q, const double3& p);
	quat qRotationBetween(float3 v0, float3 v1);
	quat qLerp(const quat& a, const quat& b, float t);
	quat qSlerp(quat a, const quat& b, float t);


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


	//
	// Some utility functions
	//
	float QuadAreaApproximateSphereProjectionSize(const float3& pos, float radius, const mat4& w2c, const mat4& c2s, float near_z);
	double SphereAngularProjectionOntoPosition(const double3& sphere_pos, double radius, const double3& position);
	void MakeHammersleyPoints(u32 nb_points, std::vector<float4>& points);
	i16 Compress_DoubleToSigned16(double d, double extents);
	double Decompress_Signed16ToDouble(i16 d, double extents);
#endif
}

#endif
