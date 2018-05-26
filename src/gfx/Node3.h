//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <math/Vec.h>
#include <gfx/Generated/Forward.h>

namespace mud
{
	MUD_GFX_EXPORT mat4 bxidentity();
	MUD_GFX_EXPORT mat4 bxinverse(const mat4& mat);
	MUD_GFX_EXPORT mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans);
	MUD_GFX_EXPORT mat4 bxscale(const vec3& scale);
	// transpose because we are right-handed but bgfx assumes left-handed
	MUD_GFX_EXPORT mat4 bxrotation(const quat& rot);
	//MUD_GFX_EXPORT mat4 bxquat(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), &rot[0]); return result; }
	MUD_GFX_EXPORT mat4 bxtranslation(const vec3& vec);
	MUD_GFX_EXPORT mat4 bxmul(const mat4& lhs, const mat4& rhs);
	MUD_GFX_EXPORT vec3 bxmul(const mat4& mat, const vec3& vec);
	MUD_GFX_EXPORT vec3 bxmulh(const mat4& mat, const vec3& vec);
	MUD_GFX_EXPORT mat4 bxlookat(const vec3& eye, const vec3& at);
	MUD_GFX_EXPORT mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up);
	MUD_GFX_EXPORT mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc);
	MUD_GFX_EXPORT mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc);
	MUD_GFX_EXPORT mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc);
	MUD_GFX_EXPORT mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans);
	MUD_GFX_EXPORT mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans);
	 
	void debug_print_mat(const mat4& mat);

	struct _refl_ MUD_GFX_EXPORT Transform
	{
		Transform() {}
		Transform(const mat4& mat);
		_attr_ _mut_ vec3 m_position = Zero3;
		_attr_ _mut_ quat m_rotation = ZeroQuat;
		_attr_ _mut_ vec3 m_scale = Unit3;
	};

	class _refl_ MUD_GFX_EXPORT Node3
	{
	public:
		// @todo factor out scene management stuff from items, nodes, lights and add it to the graph / scene
		Node3(Scene* scene = nullptr, Ref object = {});

		_attr_ Scene* m_scene = nullptr;
		_attr_ uint16_t m_index = 0;

		_attr_ _mut_ vec3 m_position = Zero3;
		_attr_ _mut_ quat m_rotation = ZeroQuat;
		_attr_ _mut_ vec3 m_scale = Unit3;
		_attr_ _mut_ bool m_visible = true;

		Ref m_object;
		size_t m_lastUpdated = 0;

		mat4 transformTRS() { return bxTRS(m_scale, m_rotation, m_position); }
		mat4 transformSRT() { return bxSRT(m_scale, m_rotation, m_position); }
		mat4 transform() { return transformTRS(); }

		vec3 axis(const vec3& dir) { return normalize(rotate(m_rotation, dir)); }
		vec3 direction() { return normalize(rotate(m_rotation, -Z3)); }

		//std::vector<Item*> m_items;
	};
}
