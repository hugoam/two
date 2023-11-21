//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <bx/math.h>
#include <gfx/Cpp20.h>
module two.gfx;

namespace bx
{
	inline void mtxQuatLh(float* _result, const float* _quat)
	{
		const float x = _quat[0];
		const float y = _quat[1];
		const float z = _quat[2];
		const float w = _quat[3];

		const float x2  =  x + x;
		const float y2  =  y + y;
		const float z2  =  z + z;
		const float x2x = x2 * x;
		const float x2y = x2 * y;
		const float x2z = x2 * z;
		const float x2w = x2 * w;
		const float y2y = y2 * y;
		const float y2z = y2 * z;
		const float y2w = y2 * w;
		const float z2z = z2 * z;
		const float z2w = z2 * w;

		_result[ 0] = 1.0f - (y2y + z2z);
		_result[ 1] =         x2y + z2w;
		_result[ 2] =         x2z - y2w;
		_result[ 3] = 0.0f;

		_result[ 4] =         x2y - z2w;
		_result[ 5] = 1.0f - (x2x + z2z);
		_result[ 6] =         y2z + x2w;
		_result[ 7] = 0.0f;

		_result[ 8] =         x2z + y2w;
		_result[ 9] =         y2z - x2w;
		_result[10] = 1.0f - (x2x + y2y);
		_result[11] = 0.0f;

		_result[12] = 0.0f;
		_result[13] = 0.0f;
		_result[14] = 0.0f;
		_result[15] = 1.0f;
	}
}

namespace two
{
	bx::Vec3 bxvec3(const vec3& v) { return bx::Vec3(v.x, v.y, v.z); }
	mat4 bxidentity() { mat4 result; bx::mtxIdentity(value_ptr(result)); return result; }
	mat4 bxinverse(const mat4& mat) { mat4 result; bx::mtxInverse(value_ptr(result), value_ptr(mat)); return result; }
	mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans) { mat4 result; bx::mtxSRT(value_ptr(result), scale.x, scale.y, scale.z, rot.x, rot.y, rot.z, trans.x, trans.y, trans.z); return result; }
	mat4 bxscale(const vec3& scale) { mat4 result; bx::mtxScale(value_ptr(result), scale.x, scale.y, scale.z); return result; }
	mat4 bxrotation(const quat& rot) { mat4 result; bx::mtxQuatLh(value_ptr(result), value_ptr(rot)); return result; }
	//mat4 bxrotation(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), value_ptr(rot)); return transpose(result); }
	mat4 bxtranslation(const vec3& vec) { mat4 result; bx::mtxTranslate(value_ptr(result), vec.x, vec.y, vec.z); return result; }
	mat4 bxmul(const mat4& lhs, const mat4& rhs) { mat4 result; bx::mtxMul(value_ptr(result), value_ptr(lhs), value_ptr(rhs)); return result; }
	vec4 bxmul(const mat4& mat, const vec4& vec) { vec4 result; bx::vec4MulMtx(&result[0], value_ptr(vec), value_ptr(mat)); return result; }
	vec3 bxmul(const mat4& mat, const vec3& vec) { bx::Vec3 result = bx::mul(bxvec3(vec), value_ptr(mat)); return vec3(result.x, result.y, result.z); }
	vec3 bxmulh(const mat4& mat, const vec3& vec) { bx::Vec3 result = bx::mulH(bxvec3(vec), value_ptr(mat)); return vec3(result.x, result.y, result.z); }
	mat4 bxlookat(const vec3& eye, const vec3& at) { mat4 result; bx::mtxLookAt(value_ptr(result), bxvec3(eye), bxvec3(at), bx::Vec3(0.f, 1.f, 0.f), bx::Handness::Right); return result; }
	void bxlookat(mat4& result, const vec3& eye, const vec3& at, const vec3& up) { bx::mtxLookAt(value_ptr(result), bxvec3(eye), bxvec3(at), bxvec3(up), bx::Handness::Right); }
	mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up) { mat4 result; bx::mtxLookAt(value_ptr(result), bxvec3(eye), bxvec3(at), bxvec3(up), bx::Handness::Right); return result; }
	mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc) { mat4 result; bx::mtxProj(value_ptr(result), fov, aspect, near, far, oglNdc, bx::Handness::Right); return result; }
	mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc) { mat4 result; bx::mtxOrtho(value_ptr(result), rect.x, rect.y, rect.z, rect.w, near, far, offset, oglNdc, bx::Handness::Right); return result; }
	mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc) { mat4 result; bx::mtxOrtho(value_ptr(result), left, right, bottom, top, near, far, offset, oglNdc, bx::Handness::Right); return result; }
	mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans) { return bxmul(bxtranslation(trans), bxmul(bxrotation(rot), bxscale(scale))); }
	mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans) { return bxmul(bxscale(scale), bxmul(bxrotation(rot), bxtranslation(trans))); }

	vec3 mat4_position(const mat4& mat) { return vec3(mat[3]); }

	void debug_print_mat(const mat4& mat)
	{
		//vec3 scale = { length(vec3(mat[0])), length(vec3{ mat[1] }), length(vec3{ mat[2] }) };
		printf("pos %.1f, %.1f, %.1f \n", mat[3].x, mat[3].y, mat[3].z);
		//printf("orientation %f, %f, %f, %f\n", m_rotation.x, bone.m_rotation.y, bone.m_rotation.z, bone.m_rotation.w);)
	}

	Node3::Node3()
	{}

	Node3::Node3(const mat4& transform, uint32_t parent)
		: m_transform(transform)
		, m_parent(parent)
	{}

	Node3::Node3(const vec3& position, const quat& rotation, const vec3& scale)
		: Node3(bxTRS(scale, rotation, position))
	{}

	void Node3::apply(const vec3& position, const quat& rotation, const vec3& scale)
	{
		m_transform = bxTRS(scale, rotation, position);
	}

	void Node3::derive(const Node3& parent, const vec3& position, const quat& rotation, const vec3& scale)
	{
		m_transform = parent.m_transform * bxTRS(scale, rotation, position);
	}

	vec3 Node3::position() const { return mulp(m_transform, vec3(0.f)); }
	vec3 Node3::axis(const vec3& dir) const { return muln(m_transform, dir); }
	vec3 Node3::direction() const { return muln(m_transform, -z3); }
}
