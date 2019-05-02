//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <gfx/Forward.h>
#include <gfx/Frustum.h>

namespace two
{
	export_ struct refl_ TWO_GFX_EXPORT ClusteredFrustum : public Frustum
	{
		uint16_t m_subdiv_x = 0;
		uint16_t m_subdiv_y = 0;
		uint16_t m_subdiv_z = 0;
		uint16_t m_cluster_count = 0;

		uvec2 m_tile_size = {};
		vec2 m_inv_tile_size = {};

		float m_linearizer = 0.f;
		float m_far_log2 = 0.f;
		vec2 m_clip_to_cluster = vec2(0.f);

		vector<float> m_distances_z;                // max 2.1 MiB (actual: resolution dependant)
		vector<vec4> m_planes_x;
		vector<vec4> m_planes_y;
		vector<vec4> m_bounding_spheres;

		uint16_t index(uint ix, uint iy, uint iz) const { return uint16_t(ix + (iy * m_subdiv_x) + (iz * m_subdiv_x * m_subdiv_y)); }

		uvec2 tile_index(const vec2& clip) const;
		uint slice(float z) const;

		Frustum cluster_frustum(uint x, uint y, uint z) const;

		void resize(const vec2& clip_size);
		void recompute(const mat4& projection, const vec2& clip_size);
	};

	export_ TWO_GFX_EXPORT void compute_frustum_subdiv(ClusteredFrustum& frustum, vec2 clip_size, size_t slices = 16);
	export_ TWO_GFX_EXPORT void compute_frustum_subdiv_square(ClusteredFrustum& frustum, vec2 clip_size, size_t slices = 16, size_t max_clusters = 8192);
}
