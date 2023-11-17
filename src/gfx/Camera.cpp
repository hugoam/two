//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <bgfx/bgfx.h>
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
	Camera::Camera()
	{
		//m_eye = vec3(10.f);
		m_far = 300.f;
	}

	Camera::Camera(mat4 transform, mat4 projection, bool ortho)
		: m_view(transform)
		, m_proj(projection)
		, m_orthographic(ortho)
	{}

	Camera::Camera(mat4 transform, float fov, float aspect, float near, float far)
		: m_view(transform)
		, m_proj(bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth))
		, m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
	{}

	Camera::Camera(vec3 eye, vec3 at, vec3 up, float fov, float aspect, float near, float far)
		: m_eye(eye)
		, m_target(at)
		, m_up(up)
		, m_view(bxlookat(m_eye, m_target, m_up))
		, m_proj(bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth))
		, m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
	{}

	Camera::Camera(mat4 transform, vec2 rect, float near, float far)
		: m_view(transform)
		, m_proj(bxortho(-rect.x / 2.f, rect.x / 2.f, -rect.y / 2.f, rect.y / 2.f, near, far, 0.0f, bgfx::getCaps()->homogeneousDepth))
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
		if(m_no_update) return;

		m_view = bxlookat(m_eye, m_target, m_up);

		if(!m_orthographic)
			m_proj = bxproj(m_fov, m_aspect, m_near, m_far, bgfx::getCaps()->homogeneousDepth);
		else
			m_proj = bxortho(ortho_rect(m_height, m_aspect), m_near, m_far, 0.0f, bgfx::getCaps()->homogeneousDepth);
	}

	void Camera::set_look_at(const vec3& eye, const vec3& target)
	{
		m_eye = eye;
		m_target = target;
	}

	void Camera::set_isometric(IsometricAngle from_angle, const vec3& position)
	{
		static const vec3 z_angles[3] = { vec3(0.f), -z3,  z3 };
		static const vec3 x_angles[3] = { vec3(0.f),  x3, -x3 };

		vec3 angle = y3 + z_angles[uint8_t(from_angle >> 0)] + x_angles[uint8_t(from_angle >> 8)];

		m_orthographic = true;
		m_height = 1.0f;

		m_target = position;
		m_eye = position + angle;
	}

	Ray Camera::ray(const vec2& offset) const
	{
		const mat4 inv_viewproj = inverse(m_proj * m_view);

		const vec3 start = bxmulh(inv_viewproj, vec3(offset.x, offset.y, 0.0f));
		const vec3 end = bxmulh(inv_viewproj, vec3(offset.x, offset.y, 1.0f));

		return { start, end, normalize(end - start), 1.f / normalize(end - start) };
	}

	vec3 Camera::transform(const vec3& point) const
	{
		return mulp(m_view, point);
	}

	vec3 Camera::project(const vec3& point) const
	{
		const mat4 viewproj = m_proj * m_view;
		const vec4 clip = viewproj * vec4(point, 1.f);
		const vec3 ndc = vec3(clip) / clip.w;
		return ndc;
	}

	MirrorCamera mirror_camera(const Camera& sourcecam, Node3& node, float clipBias)
	{
		mat4 rotatemat = rotation(node.m_transform);
		vec3 position = vec3(node.m_transform[3]);
		//vec3 normal = muln(m_node->m_transform, z3);
		vec3 normal = muln(rotatemat, y3);
		vec3 dir = position - sourcecam.m_eye;

		// Avoid rendering when mirror is facing away
		if(dot(dir, normal) > 0)
			return {};

		rotatemat = rotation(inverse(sourcecam.m_view));
		vec3 eye = -reflect(dir, normal) + position;
		vec3 lookat = muln(rotatemat, -z3) + sourcecam.m_eye;
		vec3 target = -reflect(position - lookat, normal) + position;
		vec3 up = reflect(muln(rotatemat, y3), normal);

		Camera camera = Camera(eye, target, up, sourcecam.m_fov, sourcecam.m_aspect, sourcecam.m_near, sourcecam.m_far);
		camera.m_no_update = true;

		static mat4 bias = bias_mat_bgfx(bgfx::getCaps()->originBottomLeft, false);
		mat4 mirror = bias * camera.m_proj * camera.m_view;

		// Now update projection matrix with new clip plane, implementing code from: http://www.terathon.com/code/oblique.html
		// Paper explaining this technique: http://www.terathon.com/lengyel/Lengyel-Oblique.pdf
		Plane plane = Plane(position, normal);
		plane = camera.m_view * plane;

		vec4 clipPlane = vec4(plane.m_normal.x, plane.m_normal.y, plane.m_normal.z, plane.m_distance);

		mat4& proj = camera.m_proj;

		vec4 q;
		q.x = (sign(clipPlane.x) + proj.f[8]) / proj.f[0];
		q.y = (sign(clipPlane.y) + proj.f[9]) / proj.f[5];
		q.z = -1.0f;
		q.w = (1.0f + proj.f[10]) / proj.f[14];

		// Calculate the scaled plane vector
		clipPlane *= 2.f / dot(clipPlane, q);

		// Replacing the third row of the projection matrix
		proj.f[2] = clipPlane.x;
		proj.f[6] = clipPlane.y;
		proj.f[10] = clipPlane.z + 1.0f - clipBias;
		proj.f[14] = clipPlane.w;

		return { true, camera, mirror };
	}
}
