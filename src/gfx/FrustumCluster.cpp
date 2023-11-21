//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
	
namespace fast {

// fast cos(x), ~8 cycles (vs. 66 cycles on ARM) // can be vectorized // x between -pi and pi
template<typename T>//, typename = typename enable_if<is_floating_point<T>::value>::type>
constexpr T cos(T x) noexcept {
    x *= T(c_invpi / 2);
    x -= T(0.25) + floor(x + T(0.25));
    x *= T(16.0) * abs(x) - T(8.0);
    x += T(0.225) * x * (abs(x) - T(1.0));
    return x;
}

// fast sin(x), ~8 cycles (vs. 66 cycles on ARM) // can be vectorized // x between -pi and pi
template <typename T>//, typename = typename enable_if<is_floating_point<T>::value>::type>
constexpr T sin(T x) noexcept {
    return cos<T>(x - T(c_pi2));
}

constexpr inline float ilog2(float x) noexcept {
    union {
        float val;
        int32_t x;
    } u = { x };
    return float(((u.x >> 23) & 0xff) - 127);
}

constexpr inline float log2(float x) noexcept {
    union {
        float val;
        int32_t x;
    } u = { x };
    float ilog2 = float(((u.x >> 23) & 0xff) - 128);
    u.x = (u.x & 0x007fffff) | 0x3f800000;
    return ilog2 + (-0.34484843f * u.val + 2.02466578f) * u.val - 0.67487759f;
}

constexpr double pow(double x, unsigned int y) noexcept {
    return y == 0 ? 1.0 : x * pow(x, y - 1);
}

constexpr unsigned int factorial(unsigned int x) noexcept {
    return x == 0 ? 1 : x * factorial(x - 1);
}

constexpr double exp(double x) noexcept {
    return 1.0 + x + pow(x, 2) / factorial(2) + pow(x, 3) / factorial(3)
                   + pow(x, 4) / factorial(4) + pow(x, 5) / factorial(5)
                   + pow(x, 6) / factorial(6) + pow(x, 7) / factorial(7)
                   + pow(x, 8) / factorial(8) + pow(x, 9) / factorial(9);
}

constexpr float exp(float x) noexcept {
    return float(exp(double(x)));
}

#if defined(__ARM_NEON) && defined(__aarch64__)
inline uint8_t  qadd(uint8_t a,  uint8_t b)  noexcept { return vuqaddb_s8(a, b);  }
inline uint16_t qadd(uint16_t a, uint16_t b) noexcept { return vuqaddh_s16(a, b); }
inline uint32_t qadd(uint32_t a, uint32_t b) noexcept { return vuqadds_s32(a, b); }

inline uint8_t  qsub(uint8_t a,  uint8_t b)  noexcept { return vqsubb_s8(a, b);  }
inline uint16_t qsub(uint16_t a, uint16_t b) noexcept { return vqsubh_s16(a, b); }
inline uint32_t qsub(uint32_t a, uint32_t b) noexcept { return vqsubs_s32(a, b); }
#else
template<typename T>/*, typename = typename enable_if<
        is_same<uint8_t, T>::value ||
        is_same<uint16_t, T>::value ||
        is_same<uint32_t, T>::value>::type>*/
inline T qadd(T a, T b)  noexcept {
    T r = a + b;
    return r | -T(r < a);
}

template<typename T>/*, typename = typename enable_if<
        is_same<uint8_t, T>::value ||
        is_same<uint16_t, T>::value ||
        is_same<uint32_t, T>::value>::type>*/
inline T qsub(T a,  T b)  noexcept {
    T r = a - b;
    return r & -T(r <= a);
}
#endif

template<typename T>
inline T qinc(T a)  noexcept {
    return qadd(a, T(1));
}

template<typename T>
inline T qdec(T a)  noexcept {
    return qsub(a, T(1));
}


}
}

namespace two
{
	void compute_frustum_subdiv(ClusteredFrustum& frustum, vec2 clip_size, size_t slices)
	{
		using stl::swap;
		// TODO: don't hardcode this
		frustum.m_subdiv_x = uint16_t(32);
		frustum.m_subdiv_y = uint16_t(16);
		if(clip_size.y > clip_size.x)
			swap(frustum.m_subdiv_x, frustum.m_subdiv_y);
		frustum.m_subdiv_z = uint16_t(slices);
		frustum.m_tile_size.x = (uint(clip_size.x) + frustum.m_subdiv_x - 1) / frustum.m_subdiv_x;
		frustum.m_tile_size.y = (uint(clip_size.y) + frustum.m_subdiv_y - 1) / frustum.m_subdiv_y;
	}

	void compute_frustum_subdiv_square(ClusteredFrustum& frustum, vec2 clip_size, size_t slices, size_t max_clusters)
	{
		// calculate cluster dimension from CLUSTER_BUFFER_ENTRY_COUNT_MAX and viewport
		// - Start from the maximum number of clusters we can use in the x-y plane
		size_t per_slice = max_clusters / slices;
		// - compute the number of square clusters we need in width and height, rounded down
		//   solving: |  cluster_count_x * cluster_count_y == per_slice
		//            |  cluster_count_x / cluster_count_y == width / height
		size_t count_x = size_t(sqrt(per_slice * clip_size.x / clip_size.y));
		size_t count_y = size_t(sqrt(per_slice * clip_size.y / clip_size.x));
		// - copmute the clusters dimensions, rounded up
		size_t size_x = (size_t(clip_size.x) + count_x - 1) / count_x;
		size_t size_y = (size_t(clip_size.y) + count_y - 1) / count_y;
		// - and since our clusters must be square, only keep the largest dimension
		size_t size = max(size_x, size_y);

		// Here we recompute the cluster counts which may have changed a little due to the rounding
		// and the squareness requirement of clusters
		count_x = (size_t(clip_size.x) + size - 1) / size;
		count_y = (size_t(clip_size.y) + size - 1) / size;

		frustum.m_tile_size = uvec2(uint(size));
		frustum.m_subdiv_x = uint16_t(count_x);
		frustum.m_subdiv_y = uint16_t(count_y);
		frustum.m_subdiv_z = uint16_t(slices);
	}

	uvec2 ClusteredFrustum::tile_index(const vec2& clip) const
	{
		// clip coordinates between [-1, 1], conversion to index between [0, count[
		//  = floor((clip + 1) * ((0.5 * dimension) / clustersize))
		//  = floor((clip + 1) * constant
		//  = floor(clip * constant + constant)
		const uint xi = uint(clamp(int(clip.x * m_clip_to_cluster.x + m_clip_to_cluster.x), 0, int(m_subdiv_x - 1)));
		const uint yi = uint(clamp(int(clip.y * m_clip_to_cluster.y + m_clip_to_cluster.y), 0, int(m_subdiv_y - 1)));
		return { xi, yi };
	}

	uint ClusteredFrustum::slice(float z) const
	{
		// The vastly common case is that z<0, so we always do the math for this case
		// and we "undo" it below otherwise. This works because we're using fast::log2 which
		// doesn't care if given a negative number (we'd have to use abs() otherwise).

		// This whole function is now branch-less.

		int s = int((fast::log2(-z) - m_far_log2) * m_linearizer + m_subdiv_z);

		// there are cases where z can be negative here, e.g.:
		// - the light is visible, but its center is behind the camera
		// - the camera's near is behind the camera (e.g. with shadowmap cameras)
		// in that case just return the first slice
		s = z < 0.f ? s : 0U;

		// clamp between [0, m_subdiv_z)
		return uint(clamp(s, 0, int(m_subdiv_z - 1U)));
	}

	Plane to_plane(const vec4& p) { return{ vec3(p), p.w }; }

	Frustum ClusteredFrustum::cluster_frustum(uint x, uint y, uint z) const
	{
		assert(x < m_subdiv_x);
		assert(y < m_subdiv_y);
		assert(z < m_subdiv_z);
		Frustum cluster;
		cluster.m_planes.m_left = to_plane(m_planes_x[x]);
		cluster.m_planes.m_down = to_plane(m_planes_y[y]);
		cluster.m_planes.m_near = to_plane({ 0.f, 0.f, 1.f, -m_distances_z[z] });
		cluster.m_planes.m_right = to_plane(-m_planes_x[x + 1]);
		cluster.m_planes.m_up = to_plane(-m_planes_y[y + 1]);
		cluster.m_planes.m_far = to_plane({ 0.f, 0.f, 1.f, -m_distances_z[z + 1] });
		cluster.m_corners = frustum_corners(cluster.m_planes);
		cluster.compute();
		return cluster;
	}

	void ClusteredFrustum::resize(const vec2& clip_size)
	{
		//compute_frustum_subdiv(*this, clip_size);
		compute_frustum_subdiv_square(*this, clip_size);

		m_distances_z.resize(m_subdiv_z + 1);
		m_planes_x.resize(m_subdiv_x + 1);
		m_planes_y.resize(m_subdiv_y + 1);

		m_cluster_count = uint16_t(m_subdiv_x * m_subdiv_y * m_subdiv_z);
		m_bounding_spheres.resize(m_cluster_count);

		m_clip_to_cluster = (0.5f * vec2(clip_size)) / vec2(m_tile_size);
		m_inv_tile_size = 1.0f / vec2(m_tile_size);

		const float linearizer = log2(m_far / m_near) / float(m_subdiv_z - 1);

		m_distances_z[0] = 0.0f;

		for(int i = 1, n = m_subdiv_z; i <= n; i++)
		{
			m_distances_z[i] = m_far * exp2f(float(i - n) * linearizer);
		}

		// for the inverse-transformation (view-space z to z-slice)
		m_linearizer = 1 / linearizer;
		m_far_log2 = log2(m_far);
	}

	void ClusteredFrustum::recompute(const mat4& projection, const vec2& clip_size)
	{
		// clip-space dimensions
		const vec2 cluster_clip_size = (2.0f * vec2(m_tile_size)) / clip_size;
		const mat4 inv_projection = inverse(projection);
		
		auto to_view_space = [](const mat4& inv_projection, vec4 p0, vec4 p1)
		{
			p0 = inv_projection * p0;
			p1 = inv_projection * p1;
			return vec4(normalize(cross(vec3(p1), vec3(p0))), 0.f);
		};

		for(uint16_t i = 0, n = m_subdiv_x; i <= n; ++i)
		{
			float x = (i * cluster_clip_size.x) - 1.0f;
			vec4 p0 = { x, -1, -1, 1 };
			vec4 p1 = { x,  1, -1, 1 };
			m_planes_x[i] = to_view_space(inv_projection, p0, p1);
		}

		for(uint16_t i = 0, n = m_subdiv_y; i <= n; ++i)
		{
			float y = (i * cluster_clip_size.y) - 1.0f;
			vec4 p0 = { -1, y, -1, 1 };
			vec4 p1 = {  1, y, -1, 1 };
			m_planes_y[i] = to_view_space(inv_projection, p0, p1);
		}

		// 3-planes intersection:
		//      -d0.(n1 x n2) - d1.(n2 x n0) - d2.(n0 x n1)
		// P = ---------------------------------------------
		//                      n0.(n1 x n2)

		// use stack memory here, it's only 16 KiB max
		assert(m_subdiv_x <= 2048);
		typename std::aligned_storage<sizeof(vec2), alignof(vec2)>::type stack[2048];
		vec2* const minMaxX = reinterpret_cast<vec2*>(stack);

		for(uint iz = 0, fi = 0, nz = m_subdiv_z; iz < nz; ++iz)
		{
			vec4 planes[6];
			vec3 minp;
			vec3 maxp;

			// near/far planes for all clusters at iz
			planes[4] =  vec4(0.f, 0.f, 1.f, m_distances_z[iz + 0]);
			planes[5] = -vec4(0.f, 0.f, 1.f, m_distances_z[iz + 1]);

			// min/max for z is calculated trivially because near/far planes are parallel to
			// the camera.
			minp.z = -m_distances_z[iz + 1];
			maxp.z = -m_distances_z[iz];
			assert(minp.z < maxp.z);

			for(uint16_t ix = 0; ix < m_subdiv_x; ++ix)
			{
				// left, right planes for all clusters at ix
				planes[0] = m_planes_x[ix];
				planes[1] = -m_planes_x[ix + 1];
				minp.x = limits<float>::max();
				maxp.x = limits<float>::min();
				// min/max for x is calculated by intersecting the near/far and left/right planes
				for(uint16_t c = 0; c < 4; ++c)
				{
					vec4 const& p0 = planes[0 + (c & 1)];     // {x,0,z,0}
					vec4 const& p2 = planes[4 + (c >> 1)];    // {0,0,+/-1,d}
					float px = (p2.z * p2.w * p0.z) / p0.x;
					minp.x = min(minp.x, px);
					maxp.x = max(maxp.x, px);
				}
				assert(minp.x < maxp.x);
				minMaxX[ix] = vec2(minp.x, maxp.x);
			}

			for(uint16_t iy = 0; iy < m_subdiv_y; ++iy)
			{
				// bottom, top planes for all clusters at iy
				planes[2] = m_planes_y[iy];
				planes[3] = -m_planes_y[iy + 1];
				minp.y = limits<float>::max();
				maxp.y = limits<float>::min();
				// min/max for y is calculated by intersecting the near/far and bottom/top planes
				for(uint16_t c = 0; c < 4; ++c)
				{
					vec4 const& p1 = planes[2 + (c & 1)];     // {0,y,z,0}
					vec4 const& p2 = planes[4 + (c >> 1)];    // {0,0,+/-1,d}
					float py = (p2.z * p2.w * p1.z) / p1.y;
					minp.y = min(minp.y, py);
					maxp.y = max(maxp.y, py);
				}
				assert(minp.y < maxp.y);

				for(uint16_t ix = 0, nx = m_subdiv_x; ix < nx; ++ix)
				{
					// note: clang vectorizes this loop!
					assert(this->index(ix, iy, iz) == fi);
					minp.x = minMaxX[ix][0];
					maxp.x = minMaxX[ix][1];
					m_bounding_spheres[fi++] = { (maxp + minp) * 0.5f, length((maxp - minp) * 0.5f) };
				}
			}
		}
	}
}
