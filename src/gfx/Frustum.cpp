//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <math/Axis.h>
#include <geom/Geom.hpp>
#include <geom/Intersect.h>
#include <gfx/Frustum.h>
#include <gfx/Camera.h>
#include <gfx/Item.h>
#endif

#include <stl/stddef.h>
#include <stdint.h>

#if defined WIN32
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

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
		planes.m_left  = bounding_plane(mat, Axis::X,  1.f);

		planes.m_up    = bounding_plane(mat, Axis::Y, -1.f);
		planes.m_down  = bounding_plane(mat, Axis::Y,  1.f);

		planes.m_near  = bounding_plane(mat, Axis::Z, -1.f);
		planes.m_far   = bounding_plane(mat, Axis::Z,  1.f);

		for(size_t i = 0; i < 6; ++i)//Plane& plane : planes)
			planes[i] = normalize(Plane{ -planes[i].m_normal, planes[i].m_distance });

		return planes;
	}

	Plane6 frustum_planes(const mat4& projection, const mat4& transform)
	{
		return bounding_planes(projection * transform);
	}

	Plane6 frustum_planes(const mat4& view, float fov, float aspect, float near, float far)
	{
		mat4 projection = bxproj(fov, aspect, near, far, bgfx::getCaps()->homogeneousDepth);
		return frustum_planes(projection, view);
	}

	Plane6 frustum_planes(const mat4& view, const vec2& rect, float near, float far)
	{
		mat4 projection = bxortho(-rect.x / 2.f, rect.x / 2.f, -rect.y / 2.f, rect.y / 2.f, near, far, 0.0f, bgfx::getCaps()->homogeneousDepth);
		return frustum_planes(projection, view);
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

	Point8 frustum_corners(float nw, float nh, float fw, float fh, float near, float far, const mat4& view)
	{
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

	Point8 frustum_corners(const vec2& size, float near, float far, const mat4& view)
	{
		return frustum_corners(size.x / 2.f, size.y / 2.f, size.x / 2.f, size.y / 2.f, near, far, view);
	}

	Point8 frustum_corners(float fov, float aspect, float near, float far, const mat4& view)
	{
		auto torad = [](float d) { return d * c_pi / 180.0f; };

		const float proj_height = tan(torad(fov) * 0.5f);
		const float proj_width = proj_height * aspect;

		// Frustum corners in view space.
		const float nw = near * proj_width;
		const float nh = near * proj_height;
		const float fw = far  * proj_width;
		const float fh = far  * proj_height;

		return frustum_corners(nw, nh, fw, fh, near, far, view);
	}

	vec2 frustum_viewport_size(const mat4& projection)
	{
		Plane6 planes = bounding_planes(projection);
		vec3 intersection = plane_3_intersection(planes.m_near, planes.m_right, planes.m_up);
		return{ intersection.x, intersection.y };
	}

	Frustum::Frustum()
	{}

	Frustum::Frustum(const mat4& transform, float fov, float aspect, float near, float far)
		: m_fov(fov)
		, m_aspect(aspect)
		, m_near(near)
		, m_far(far)
		, m_planes(frustum_planes(transform, fov, aspect, near, far))
		, m_corners(frustum_corners(fov, aspect, near, far, transform))
	{
		this->compute();
	}

	Frustum::Frustum(const mat4& transform, const vec2& rect, float near, float far)
		: m_near(near)
		, m_far(far)
		, m_planes(frustum_planes(transform, rect, near, far))
		, m_corners(frustum_corners(rect, near, far, transform))
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

	Frustum optimized_frustum(Camera& camera, span<Item*> items)
	{
		if(!camera.m_optimize_ends)
			return Frustum{ camera.m_transform, camera.m_fov, camera.m_aspect, camera.m_near, camera.m_far };

		Plane near_plane = camera.near_plane();

		float z_max = -1e20f;
		float z_min = 1e20f;

		for(Item* item : items)
		{
			vec2 min_max = project_aabb_in_plane(near_plane, item->m_aabb);

			z_min = min(min_max.x, z_min);
			z_max = max(min_max.y, z_max);
		}

		float near = max(camera.m_near, z_min);
		float far = min(camera.m_far, z_max);

		return Frustum{ camera.m_transform, camera.m_fov, camera.m_aspect, near, far };
	}

	void split_frustum_slices(Camera& camera, span<FrustumSlice> slices, uint8_t num_splits, float near, float far, float split_distribution)
	{
		const float ratio = far / near;

		for(uint8_t i = 0; i < num_splits; ++i)
		{
			float si = float(int8_t(i * 2 + 1)) / float(num_splits * 2);

			const float split = split_distribution * (near * powf(ratio, si)) + (1 - split_distribution) * (near + (far - near) * si);
			const float slice_near = i == 0 ? near : slices[i - 1].m_frustum.m_far * 1.005f;
			const float slice_far = i == num_splits - 1 ? far : split;

			Frustum frustum;
			if(camera.m_orthographic)
			{
				vec2 rect = { camera.m_height * camera.m_aspect, camera.m_height };
				frustum = { camera.m_transform, rect, slice_near, slice_far };
			}
			else
			{
				frustum = { camera.m_transform, camera.m_fov, camera.m_aspect, slice_near, slice_far };
			}

			slices[i] = { i, frustum };
		}
	}

	void split_frustum_slices(Camera& camera, span<FrustumSlice> slices, uint8_t num_splits, float split_distribution)
	{
		split_frustum_slices(camera, slices, num_splits, camera.m_near, camera.m_far, split_distribution);
	}
}
