//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <type/Ref.h>
#include <math/Vec.h>
#include <ecs/Entity.h>
#endif
#include <gfx/Forward.h>

namespace two
{
	export_ TWO_GFX_EXPORT func_ mat4 bxidentity();
	export_ TWO_GFX_EXPORT func_ mat4 bxinverse(const mat4& mat);
	export_ TWO_GFX_EXPORT func_ mat4 bxSRT(const vec3& scale, const vec3& rot, const vec3& trans);
	export_ TWO_GFX_EXPORT func_ mat4 bxscale(const vec3& scale);
	// transpose because we are right-handed but bgfx assumes left-handed
	export_ TWO_GFX_EXPORT func_ mat4 bxrotation(const quat& rot);
	//export_ TWO_GFX_EXPORT mat4 bxquat(const quat& rot) { mat4 result; bx::mtxQuat(value_ptr(result), &rot[0]); return result; }
	export_ TWO_GFX_EXPORT func_ mat4 bxtranslation(const vec3& vec);
	export_ TWO_GFX_EXPORT func_ mat4 bxmul(const mat4& lhs, const mat4& rhs);
	export_ TWO_GFX_EXPORT func_ vec4 bxmul(const mat4& mat, const vec4& vec);
	export_ TWO_GFX_EXPORT func_ vec3 bxmul(const mat4& mat, const vec3& vec);
	export_ TWO_GFX_EXPORT func_ vec3 bxmulh(const mat4& mat, const vec3& vec);
	export_ TWO_GFX_EXPORT func_ mat4 bxlookat(const vec3& eye, const vec3& at);
	export_ TWO_GFX_EXPORT func_ void bxlookat(mat4& result, const vec3& eye, const vec3& at, const vec3& up);
	export_ TWO_GFX_EXPORT func_ mat4 bxlookat(const vec3& eye, const vec3& at, const vec3& up);
	export_ TWO_GFX_EXPORT func_ mat4 bxproj(float fov, float aspect, float near, float far, bool oglNdc);
	export_ TWO_GFX_EXPORT func_ mat4 bxortho(const vec4& rect, float near, float far, float offset, bool oglNdc);
	export_ TWO_GFX_EXPORT func_ mat4 bxortho(float left, float right, float bottom, float top, float near, float far, float offset, bool oglNdc);
	export_ TWO_GFX_EXPORT func_ mat4 bxSRT(const vec3& scale, const quat& rot, const vec3& trans);
	export_ TWO_GFX_EXPORT func_ mat4 bxTRS(const vec3& scale, const quat& rot, const vec3& trans);
	 
	void debug_print_mat(const mat4& mat);

	export_ class refl_ TWO_GFX_EXPORT Node3
	{
	public:
		constr_ Node3();
		constr_ Node3(const vec3& position, const quat& rotation = ZeroQuat, const vec3& scale = vec3(1.f));
		Node3(const mat4& transform, uint32_t parent = UINT32_MAX);

		attr_ uint32_t m_parent = UINT32_MAX;
		attr_ mat4 m_transform = bxidentity();

		//Ref m_object;
		Entity m_object;

		meth_ void apply(const vec3& position, const quat& rotation = ZeroQuat, const vec3& scale = vec3(1.f));
		meth_ void derive(const Node3& parent, const vec3& position, const quat& rotation = ZeroQuat, const vec3& scale = vec3(1.f));

		meth_ vec3 position() const;
		meth_ vec3 axis(const vec3& dir) const;
		meth_ vec3 direction() const;
	};
}
