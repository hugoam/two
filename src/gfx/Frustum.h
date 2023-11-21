//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>

#if defined TWO_UNIFORM_BLOCKS
#include <gfx/Uniform.h>
#endif

namespace two
{
#if defined TWO_UNIFORM_BLOCKS
	export_ struct refl_ TWO_GFX_EXPORT FrustumBlock
	{
		attr_ float m_fov = 60.f;
		attr_ float m_aspect = 1.f;
		attr_ float m_near = 0.001f;
		attr_ float m_far = 100.f;

		static TypedUniformBlock<FrustumBlock> s_block;
	};
#endif

	export_ TWO_GFX_EXPORT Plane6 bounding_planes(const mat4& mat);
	export_ TWO_GFX_EXPORT Plane6 frustum_planes(const mat4& projection, const mat4& transform);
	export_ TWO_GFX_EXPORT Plane6 frustum_planes(const mat4& view, float fov, float aspect, float near, float far);
	export_ TWO_GFX_EXPORT Plane6 frustum_planes(const mat4& view, const vec2& rect, float near, float far);
	export_ TWO_GFX_EXPORT Point8 frustum_corners(const Plane6& planes);

	export_ TWO_GFX_EXPORT vec2 frustum_viewport_size(const mat4& projection);

	export_ class refl_ TWO_GFX_EXPORT Frustum
	{
	public:
		Frustum();
		Frustum(const mat4& transform, float fov, float aspect, float near, float far);
		Frustum(const mat4& transform, const vec2& rect, float near, float far);

		void compute();

		attr_ float m_fov = 60.f;
		attr_ float m_aspect = 1.f;
		attr_ float m_near;
		attr_ float m_far;

		Plane6 m_planes;
		Point8 m_corners;

		attr_ vec3 m_center;
		attr_ float m_radius;
	};

	export_ TWO_GFX_EXPORT Frustum optimized_frustum(Camera& camera, span<Item*> items);

	export_ struct refl_ TWO_GFX_EXPORT FrustumSlice
	{
		int m_index;
		Frustum m_frustum;
	};

	export_ TWO_GFX_EXPORT void split_frustum_slices(Camera& camera, span<FrustumSlice*> slices, uint8_t num_splits, float split_distribution);
}
