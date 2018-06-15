//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>
#ifndef MUD_CPP_20
#include <cstdio>
#endif

#include <bx/math.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <gfx/Node3.h>
#endif

namespace mud
{
	mat4 bxidentity() { mat4 result; bx::mtxIdentity(value_ptr(result)); return result; }
	mat4 bxinverse(const mat4& mat) { mat4 result; bx::mtxInverse(value_ptr(result), value_ptr(mat)); return result; }
	mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans) { mat4 result; bx::mtxSRT(value_ptr(result), scale.x, scale.y, scale.z, rot.x, rot.y, rot.z, trans.x, trans.y, trans.z); return result; }
	mat4 bxscale(const vec3& scale) { mat4 result; bx::mtxScale(value_ptr(result), scale.x, scale.y, scale.z); return result; }
	// transpose because we are right-handed but bgfx assumes left-handed
	mat4 bxrotation(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), value_ptr(rot)); return transpose(result); }
	//inline mat4 mtxQuat(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), &rot[0]); return result; }
	mat4 bxtranslation(const vec3& vec) { mat4 result; bx::mtxTranslate(value_ptr(result), vec.x, vec.y, vec.z); return result; }
	mat4 bxmul(const mat4& lhs, const mat4& rhs) { mat4 result; bx::mtxMul(value_ptr(result), value_ptr(lhs), value_ptr(rhs)); return result; }
	vec3 bxmul(const mat4& mat, const vec3& vec) { vec3 result; bx::vec3MulMtx(&result[0], value_ptr(vec), value_ptr(mat)); return result; }
	vec3 bxmulh(const mat4& mat, const vec3& vec) { vec3 result; bx::vec3MulMtxH(&result[0], value_ptr(vec), value_ptr(mat)); return result; }
	mat4 bxlookat(const vec3& eye, const vec3& at) { mat4 result; bx::mtxLookAtRh(value_ptr(result), value_ptr(eye), value_ptr(at)); return result; }
	mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up) { mat4 result; bx::mtxLookAtRh(value_ptr(result), value_ptr(eye), value_ptr(at), value_ptr(up)); return result; }
	mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc) { mat4 result; bx::mtxProjRh(value_ptr(result), fov, aspect, near, far, oglNdc); return result; }
	mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc) { mat4 result; bx::mtxOrthoRh(value_ptr(result), rect.x, rect.y, rect.z, rect.w, near, far, offset, oglNdc); return result; }
	mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc) { mat4 result; bx::mtxOrthoRh(value_ptr(result), left, right, bottom, top, near, far, offset, oglNdc); return result; }
	mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans) { return bxmul(bxtranslation(trans), bxmul(bxrotation(rot), bxscale(scale))); }
	mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans) { return bxmul(bxscale(scale), bxmul(bxrotation(rot), bxtranslation(trans))); }

	void debug_print_mat(const mat4& mat)
	{
		//vec3 scale = { length(vec3{ mat[0] }), length(vec3{ mat[1] }), length(vec3{ mat[2] }) };
		printf("pos %.1f, %.1f, %.1f ", mat[3].x, mat[3].y, mat[3].z);
		//printf("orientation %f, %f, %f, %f\n", m_rotation.x, bone.m_rotation.y, bone.m_rotation.z, bone.m_rotation.w);)
	}

	static uint16_t s_node_index = 0;

	Transform::Transform(const mat4& transform)
	{
		UNUSED(transform);
	}

	Node3::Node3(Scene* scene, Ref object)
		: m_scene(scene)
		, m_index(s_node_index++)
		, m_object(object)
	{}
}
