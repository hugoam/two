//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Array.h>
#include <geom/Geom.h>
#endif
#include <gfx/Generated/Forward.h>

#if defined MUD_UNIFORM_BLOCKS
#include <gfx/Uniform.h>
#endif

namespace mud
{
#if defined MUD_UNIFORM_BLOCKS
	export_ struct _refl_ MUD_GFX_EXPORT FrustumBlock
	{
		_attr_ float m_fov = 60.f;
		_attr_ float m_aspect = 1.f;
		_attr_ float m_near = 0.001f;
		_attr_ float m_far = 100.f;

		static TypedUniformBlock<FrustumBlock> s_block;
	};
#endif

	MUD_GFX_EXPORT Plane6 bounding_planes(const mat4& mat);
	MUD_GFX_EXPORT Plane6 frustum_planes(const mat4& projection, const mat4& transform);

	MUD_GFX_EXPORT vec2 frustum_viewport_size(const mat4& projection);

	export_ class _refl_ MUD_GFX_EXPORT Frustum
	{
	public:
		Frustum();
		Frustum(const mat4& projection, const mat4& transform, float near, float far, float fov, float aspect);

		void compute();

		_attr_ _mut_ float m_fov = 60.f;
		_attr_ _mut_ float m_aspect = 1.f;
		_attr_ _mut_ float m_near;
		_attr_ _mut_ float m_far;

		Plane6 m_planes;
		Point8 m_corners;

		_attr_ _mut_ vec3 m_center;
		_attr_ _mut_ float m_radius;
	};

	Frustum optimized_frustum(Camera& camera, array<Item*> items);

	export_ struct _refl_ MUD_GFX_EXPORT FrustumSlice
	{
		int m_index;
		Frustum m_frustum;
	};

	void split_frustum_slices(Camera& camera, array<FrustumSlice> slices, uint8_t num_splits, float split_distribution);
}
