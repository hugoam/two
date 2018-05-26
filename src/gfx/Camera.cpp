//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx/Camera.h>

#include <bgfx/bgfx.h>

namespace mud
{
	Camera::Camera(Scene* scene)
		: m_scene(scene)
		, m_node(scene)
		, m_target(scene)
	{
		m_node.m_position = 2.f * Z3;
		m_far = 300.f;
	}

	Camera::Camera(mat4 transform, mat4 projection)
		: m_transform(transform)
		, m_projection(projection)
	{}

	Plane Camera::near_plane()
	{
		vec3 direction = normalize(m_target.m_position - m_node.m_position);
		return Plane{ m_node.m_position + direction * m_near, direction };
	}

	Plane Camera::far_plane()
	{
		vec3 direction = normalize(m_target.m_position - m_node.m_position);
		return Plane{ m_node.m_position + direction * m_far, direction };
	}

	mat4 Camera::projection(float near, float far, bool ndc)
	{
		UNUSED(ndc);
		if(!m_orthogonal)
			return bxproj(m_fov, m_aspect, near, far, bgfx::getCaps()->homogeneousDepth);
		else
			return bxortho(this->ortho_rect(), near, far, 0.0f, bgfx::getCaps()->homogeneousDepth);
	}

	void Camera::update()
	{
		//vec3 up = normalize(rotate(m_node.m_rotation, Y_vec));
		//m_transform = mtxLookAt(m_node.m_position, m_target.m_position, up);

		m_transform = bxlookat(m_node.m_position, m_target.m_position);

		if(!m_orthogonal)
			m_projection = bxproj(m_fov, m_aspect, m_near, m_far, bgfx::getCaps()->homogeneousDepth);
		else
			m_projection = bxortho(this->ortho_rect(), m_near, m_far, 0.0f, bgfx::getCaps()->homogeneousDepth);
	}

	void Camera::set_look_at(const vec3& eye, const vec3& target)
	{
		m_node.m_position = eye;
		m_target.m_position = target;
	}

	void Camera::set_isometric(IsometricAngle from_angle, const vec3& position)
	{
		static const vec3 z_angles[3] = { Zero3, -Z3, Z3 };
		static const vec3 x_angles[3] = { Zero3, X3, -X3 };

		vec3 angle = Y3 + z_angles[uint8_t(from_angle >> 0)] + x_angles[uint8_t(from_angle >> 8)];

		m_orthogonal = true;
		m_height = 1.0f;

		m_target.m_position = position;
		m_node.m_position = position + angle;
	}

	Ray Camera::ray(const vec2& offset)
	{
		mat4 invViewProj = inverse(bxmul(m_transform, m_projection));

		vec3 start = bxmulh(invViewProj, { offset.x, offset.y, 0.0f });
		vec3 end = bxmulh(invViewProj, { offset.x, offset.y, 1.0f });

		return { start, end, normalize(end - start), 1.f / normalize(end - start) };
	}
}
