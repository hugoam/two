//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <limits>
#endif

#ifdef MUD_MODULES
#include <cstdlib>
module mud.math;
#else
#include <math/Vec.h>
#include <math/Vec.hpp>
#endif

#include <algorithm>

namespace mud
{
	template struct MUD_MATH_EXPORT v2<float>;
	template struct MUD_MATH_EXPORT v3<float>;
	template struct MUD_MATH_EXPORT v4<float>;

	template struct MUD_MATH_EXPORT v2<int>;
	template struct MUD_MATH_EXPORT v3<int>;
	template struct MUD_MATH_EXPORT v4<int>;

	template struct MUD_MATH_EXPORT v2<uint>;
	template struct MUD_MATH_EXPORT v3<uint>;
	template struct MUD_MATH_EXPORT v4<uint>;

	template struct MUD_MATH_EXPORT v2<bool>;
	template struct MUD_MATH_EXPORT v3<bool>;
	template struct MUD_MATH_EXPORT v4<bool>;

	template <class T>
	inline T epsilon() { return std::numeric_limits<T>::epsilon(); }

	quat operator+(const quat& q) { return q; }
	quat operator-(const quat& v) { return quat(-v.x, -v.y, -v.z, -v.w); }

	quat operator+(const quat& a, const quat& b) { return quat(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
	quat operator-(const quat& a, const quat& b) { return quat(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }

	quat operator*(const quat& q, float s) { return quat(q.x * s, q.y * s, q.z * s, q.w * s); }
	quat operator/(const quat& q, float s) { return quat(q.x / s, q.y / s, q.z / s, q.w / s); }
	quat operator*(float s, const quat& q) { return quat(q.x * s, q.y * s, q.z * s, q.w * s); }
	quat operator/(float s, const quat& q) { return quat(s / q.x, s / q.y, s / q.w, s / q.w); }

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
		float invlen = float(1) / len;
		return quat(q.x * invlen, q.y * invlen, q.z * invlen, q.w * invlen);
	}

	//bool operator==(const quat& q1, const quat& q2) { return all(equal(q1, q2, epsilon<float>())); }
	//bool operator!=(const quat& q1, const quat& q2) { return any(not_equal(q1, q2, epsilon<float>())); }

	float dot(const quat& a, const quat& b)
	{
		float4 tmp(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
		return (tmp.x + tmp.y) + (tmp.z + tmp.w);
	}

#if 0
	quat lerp(const quat& a, const quat& b, float t)
	{
		float4 vec = lerp((float4&)a, (float4&)b, t);
		return quat(vec.x, vec.y, vec.z, vec.w);
	}
#endif

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
			return quat(lerp(x.x, z.x, a), lerp(x.y, z.y, a), lerp(x.z, z.z, a), lerp(x.w, z.w, a));
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
		return lerp(angle, -angle, dot(ref, cross(a, b)) < float(0));
	}

	float oriented_angle(const float2& a, const float2& b)
	{
		float det = a.x * b.y - a.y * b.x; // determinant
		return atan2(det, dot(a, b));      // atan2(y, x) or atan2(sin, cos)

		//const float angle = acos(clamp(dot(a, b), float(-1), float(1)));
		//
		//if(all(equal(b, rotate(a, angle), epsilon<float>())))
		//	return angle;
		//else
		//	return -angle;
	}

	mat4 operator*(const mat4& m, float f)
	{
		mat4 result;
		result[0] = m[0] * f;
		result[1] = m[1] * f;
		result[2] = m[2] * f;
		result[3] = m[3] * f;
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
#if 1
		float xx = m.f[0];
		float xy = m.f[1];
		float xz = m.f[2];
		float xw = m.f[3];
		float yx = m.f[4];
		float yy = m.f[5];
		float yz = m.f[6];
		float yw = m.f[7];
		float zx = m.f[8];
		float zy = m.f[9];
		float zz = m.f[10];
		float zw = m.f[11];
		float wx = m.f[12];
		float wy = m.f[13];
		float wz = m.f[14];
		float ww = m.f[15];

		float det = 0.0f;
		det += xx * (yy*(zz*ww - zw * wz) - yz * (zy*ww - zw * wy) + yw * (zy*wz - zz * wy));
		det -= xy * (yx*(zz*ww - zw * wz) - yz * (zx*ww - zw * wx) + yw * (zx*wz - zz * wx));
		det += xz * (yx*(zy*ww - zw * wy) - yy * (zx*ww - zw * wx) + yw * (zx*wy - zy * wx));
		det -= xw * (yx*(zy*wz - zz * wy) - yy * (zx*wz - zz * wx) + yz * (zx*wy - zy * wx));

		float invDet = 1.0f / det;

		mat4 result;
		result.f[0] = +(yy*(zz*ww - wz * zw) - yz * (zy*ww - wy * zw) + yw * (zy*wz - wy * zz)) * invDet;
		result.f[1] = -(xy*(zz*ww - wz * zw) - xz * (zy*ww - wy * zw) + xw * (zy*wz - wy * zz)) * invDet;
		result.f[2] = +(xy*(yz*ww - wz * yw) - xz * (yy*ww - wy * yw) + xw * (yy*wz - wy * yz)) * invDet;
		result.f[3] = -(xy*(yz*zw - zz * yw) - xz * (yy*zw - zy * yw) + xw * (yy*zz - zy * yz)) * invDet;

		result.f[4] = -(yx*(zz*ww - wz * zw) - yz * (zx*ww - wx * zw) + yw * (zx*wz - wx * zz)) * invDet;
		result.f[5] = +(xx*(zz*ww - wz * zw) - xz * (zx*ww - wx * zw) + xw * (zx*wz - wx * zz)) * invDet;
		result.f[6] = -(xx*(yz*ww - wz * yw) - xz * (yx*ww - wx * yw) + xw * (yx*wz - wx * yz)) * invDet;
		result.f[7] = +(xx*(yz*zw - zz * yw) - xz * (yx*zw - zx * yw) + xw * (yx*zz - zx * yz)) * invDet;

		result.f[8] = +(yx*(zy*ww - wy * zw) - yy * (zx*ww - wx * zw) + yw * (zx*wy - wx * zy)) * invDet;
		result.f[9] = -(xx*(zy*ww - wy * zw) - xy * (zx*ww - wx * zw) + xw * (zx*wy - wx * zy)) * invDet;
		result.f[10] = +(xx*(yy*ww - wy * yw) - xy * (yx*ww - wx * yw) + xw * (yx*wy - wx * yy)) * invDet;
		result.f[11] = -(xx*(yy*zw - zy * yw) - xy * (yx*zw - zx * yw) + xw * (yx*zy - zx * yy)) * invDet;

		result.f[12] = -(yx*(zy*wz - wy * zz) - yy * (zx*wz - wx * zz) + yz * (zx*wy - wx * zy)) * invDet;
		result.f[13] = +(xx*(zy*wz - wy * zz) - xy * (zx*wz - wx * zz) + xz * (zx*wy - wx * zy)) * invDet;
		result.f[14] = -(xx*(yy*wz - wy * yz) - xy * (yx*wz - wx * yz) + xz * (yx*wy - wx * yy)) * invDet;
		result.f[15] = +(xx*(yy*zz - zy * yz) - xy * (yx*zz - zx * yz) + xz * (yx*zy - zx * yy)) * invDet;

		return result;
#else
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
#endif
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
	void MakeHammersleyPoints(u32 nb_points, vector<float4>& points);
	i16 Compress_DoubleToSigned16(double d, double extents);
	double Decompress_Signed16ToDouble(i16 d, double extents);
#endif
}
