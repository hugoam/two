//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx/Frustum.h>
#include <gfx/Camera.h>

#include <gfx/Item.h>
#include <math/Axis.h>
#include <geom/Intersect.h>

#include <bx/math.h>

namespace mud
{
	inline Plane bounding_plane(const mat4& mat, Axis component, float dir)
	{
		return {
			mat[0][3] + dir * mat[0][size_t(component)],
			mat[1][3] + dir * mat[1][size_t(component)],
			mat[2][3] + dir * mat[2][size_t(component)],
			mat[3][3] + dir * mat[3][size_t(component)]
		};
	}

	Plane6 bounding_planes(const mat4& mat)
	{
		Plane6 planes;

		planes.m_right = bounding_plane(mat, Axis::X, -1.f);
		planes.m_left = bounding_plane(mat, Axis::X, 1.f);

		planes.m_up = bounding_plane(mat, Axis::Y, -1.f);
		planes.m_down = bounding_plane(mat, Axis::Y, 1.f);

		planes.m_near = bounding_plane(mat, Axis::Z, -1.f);
		planes.m_far = bounding_plane(mat, Axis::Z, 1.f);

		for(size_t i = 0; i < 6; ++i)//Plane& plane : planes)
			planes[i] = normalize(Plane{ -planes[i].m_normal, planes[i].m_distance });

		return planes;
	}

	Plane6 frustum_planes(const mat4& projection, const mat4& transform)
	{
		return bounding_planes(projection * transform);
	}

	Point8 frustum_corners(const Plane6& planes)
	{
		Point8 points;

		const Plane* corners[8][3] =
		{
			{ &planes.m_near,  &planes.m_left,  &planes.m_up   },
			{ &planes.m_near,  &planes.m_left,  &planes.m_down },
			{ &planes.m_near,  &planes.m_right, &planes.m_down },
			{ &planes.m_near,  &planes.m_right, &planes.m_up   },
			{ &planes.m_far,   &planes.m_left,  &planes.m_down },
			{ &planes.m_far,   &planes.m_left,  &planes.m_up   },
			{ &planes.m_far,   &planes.m_right, &planes.m_up   },
			{ &planes.m_far,   &planes.m_right, &planes.m_down },
		};

		for(uint i = 0; i < 8; i++)
			points[i] = plane_3_intersection(*corners[i][0], *corners[i][1], *corners[i][2]);

		return points;
	}

	Point8 frustum_corners(const mat4& projection, const mat4& transform)
	{
		Plane6 planes = frustum_planes(projection, transform);
		return frustum_corners(planes);
	}

	Point8 frustum_corners(float near, float far, float fov, float aspect, const mat4& view)
	{
		const float proj_height = bx::tan(bx::toRad(fov) * 0.5f);
		const float proj_width = proj_height * aspect;

		// Frustum corners in view space.
		const float nw = near * proj_width;
		const float nh = near * proj_height;
		const float fw = far  * proj_width;
		const float fh = far  * proj_height;

		Point8 corners =
		{
			{ -nw,  nh, -near },
			{ -nw, -nh, -near },
			{  nw, -nh, -near },
			{  nw,  nh, -near },
			{ -fw, -fh, -far },
			{ -fw,  fh, -far },
			{  fw,  fh, -far },
			{  fw, -fh, -far },
		};

		// Convert corners to world space.
		mat4 inverse_view = inverse(view);
		for(uint i = 0; i < 8; i++)
			corners[i] = bxmul(inverse_view, corners[i]);

		return corners;
	}

	vec2 frustum_viewport_size(const mat4& projection)
	{
		Plane6 planes = bounding_planes(projection);
		vec3 intersection = plane_3_intersection(planes.m_near, planes.m_right, planes.m_up);
		return{ intersection.x, intersection.y };
	}

	Frustum::Frustum()
	{}

	Frustum::Frustum(const mat4& projection, const mat4& transform, float near, float far, float fov, float aspect)
		: m_near(near)
		, m_far(far)
		, m_planes(frustum_planes(projection, transform))
		, m_corners(frustum_corners(near, far, fov, aspect, transform))
	{
		this->compute();
	}

	void Frustum::compute()
	{
		m_center = Zero3;
		for(uint i = 0; i < 8; i++)
			m_center += m_corners[i];
		//m_center /= 8.f;
		m_center = m_center / 8.f;

		m_radius = 0.f;
		for(uint i = 0; i < 8; i++)
			m_radius = max(distance(m_center, m_corners[i]), m_radius);
	}

	Frustum optimized_frustum(Camera& camera, array<Item*> items)
	{
		if(!camera.m_optimize_ends)
			return Frustum { camera.m_projection, camera.m_transform, camera.m_near, camera.m_far, camera.m_fov, camera.m_aspect };

		Plane base = camera.near_plane();

		float z_max = -1e20f;
		float z_min = 1e20f;

		for(Item* item : items)
		{
			vec2 min_max = project_aabb_in_plane(base, item->m_aabb);

			z_min = min(min_max.x, z_min);
			z_max = max(min_max.y, z_max);
		}

		float near = max(camera.m_near, z_min);
		float far = min(camera.m_far, z_max);

		return Frustum{ camera.m_projection, camera.m_transform, near, far, camera.m_fov, camera.m_aspect };
	}

	void split_frustum_slices(Camera& camera, array<FrustumSlice> slices, uint8_t num_splits, float near, float far, float split_distribution)
	{
		const float ratio = far / near;

		for(uint8_t i = 0; i < num_splits; ++i)
		{
			float si = float(int8_t(i * 2 + 1)) / float(num_splits * 2);

			const float split = split_distribution * (near * powf(ratio, si)) + (1 - split_distribution) * (near + (far - near) * si);
			const float slice_near = i == 0 ? near : slices[i - 1].m_frustum.m_far * 1.005f;
			const float slice_far = i == num_splits - 1 ? far : split;

			Frustum frustum{ camera.projection(slice_near, slice_far), camera.m_transform, slice_near, slice_far, camera.m_fov, camera.m_aspect };
			slices[i] = { i, frustum };
		}
	}

	void split_frustum_slices(Camera& camera, array<FrustumSlice> slices, uint8_t num_splits, float split_distribution)
	{
		split_frustum_slices(camera, slices, num_splits, camera.m_near, camera.m_far, split_distribution);
	}
}
