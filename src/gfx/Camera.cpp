//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <geom/Geom.hpp>
#include <gfx/Camera.h>
#include <gfx/Viewport.h>
#include <gfx/Froxel.h>
#endif

#include <bgfx/bgfx.h>

namespace mud
{
	Camera::Camera()
	{
		//m_eye = vec3(10.f);
		m_far = 300.f;
	}

	Camera::Camera(mat4 transform, mat4 projection, bool ortho)
		: m_transform(transform)
		, m_projection(projection)
		, m_orthographic(ortho)
	{}

	Camera::Camera(mat4 transform, float fov, float aspect, float near, float far)
		: m_transform(transform)
		, m_projection(bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth))
		, m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
	{}

	Camera::Camera(vec3 eye, vec3 at, vec3 up, float fov, float aspect, float near, float far)
		: m_eye(eye)
		, m_target(at)
		, m_up(up)
		, m_transform(bxlookat(m_eye, m_target, m_up))
		, m_projection(bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth))
		, m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
	{}

	Camera::Camera(mat4 transform, vec2 rect, float near, float far)
		: m_transform(transform)
		, m_projection(bxortho(-rect.x / 2.f, rect.x / 2.f, -rect.y / 2.f, rect.y / 2.f, near, far, 0.0f, bgfx::getCaps()->homogeneousDepth))
		, m_aspect(rect.x / rect.y)
		, m_near(near)
		, m_far(far)
		, m_orthographic(true)
		, m_height(rect.y)
	{}

	Camera::~Camera()
	{}

	Plane Camera::near_plane() const
	{
		vec3 direction = normalize(m_target - m_eye);
		return { m_eye + direction * m_near, direction };
	}

	Plane Camera::far_plane() const
	{
		vec3 direction = normalize(m_target - m_eye);
		return { m_eye + direction * m_far, direction };
	}

	inline vec4 ortho_rect(float height, float aspect) { return { -height / 2.f * aspect, height / 2.f * aspect, -height / 2.f, height / 2.f }; };

	mat4 Camera::projection(float near, float far, bool ndc)
	{
		UNUSED(ndc);
		if(!m_orthographic)
			return bxproj(m_fov, m_aspect, near, far, bgfx::getCaps()->homogeneousDepth);
		else
			return bxortho(ortho_rect(m_height, m_aspect), near, far, 0.0f, bgfx::getCaps()->homogeneousDepth);
	}

	void Camera::update()
	{
		m_transform = bxlookat(m_eye, m_target, m_up);

		if(!m_orthographic)
			m_projection = bxproj(m_fov, m_aspect, m_near, m_far, bgfx::getCaps()->homogeneousDepth);
		else
			m_projection = bxortho(ortho_rect(m_height, m_aspect), m_near, m_far, 0.0f, bgfx::getCaps()->homogeneousDepth);
	}

	void Camera::set_look_at(const vec3& eye, const vec3& target)
	{
		m_eye = eye;
		m_target = target;
	}

	void Camera::set_isometric(IsometricAngle from_angle, const vec3& position)
	{
		static const vec3 z_angles[3] = { vec3(0.f), -Z3,  Z3 };
		static const vec3 x_angles[3] = { vec3(0.f),  X3, -X3 };

		vec3 angle = Y3 + z_angles[uint8_t(from_angle >> 0)] + x_angles[uint8_t(from_angle >> 8)];

		m_orthographic = true;
		m_height = 1.0f;

		m_target = position;
		m_eye = position + angle;
	}

	Ray Camera::ray(const vec2& offset) const
	{
		mat4 invViewProj = inverse(bxmul(m_transform, m_projection));

		vec3 start = bxmulh(invViewProj, { offset.x, offset.y, 0.0f });
		vec3 end = bxmulh(invViewProj, { offset.x, offset.y, 1.0f });

		return { start, end, normalize(end - start), 1.f / normalize(end - start) };
	}
}
