//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_MODULES
module mud.geom;
#else
#include <stl/algorithm.h>
#include <stl/table.h>
#include <math/Vec.hpp>
#include <math/Interp.h>
#include <geom/Voxel.h>
#include <geom/Primitive.hpp>
#include <geom/Geometry.h>
#endif

#define FLAT false
#define FLAT_BLEND 1

namespace mud
{
	extern const int c_edge_table[];

	struct CubeSide { int num; int tris[16]; };
	extern const CubeSide c_tri_table[];

	MarchingCubes::MarchingCubes(uint32_t subdiv)
	{
		// size of field, 32 is pushing it in Javascript :)
		m_subdiv = subdiv;
		m_size = subdiv * subdiv * subdiv;
		m_extent = m_subdiv / 2.0f;

		m_delta = 2.0f / float(subdiv);

		m_xd = 1;
		m_yd = subdiv;
		m_zd = subdiv * subdiv;

		m_field.resize(m_size);
	}
	
	uint8_t MarchingCubes::classify(size_t q, float isol) const
	{
		struct Cell { size_t q; float f; };
		auto cell = [&](size_t q) -> Cell { return { q, m_field[q] }; };
		// cache indices
		const Cell c = cell(q);
		const Cell cx = cell(q + 1);
		const Cell cy = cell(q + m_yd);
		const Cell cz = cell(q + m_zd);
		const Cell cxy = cell(q + 1 + m_yd);
		const Cell cxz = cell(q + 1 + m_zd);
		const Cell cyz = cell(q + m_yd + m_zd);
		const Cell cxyz = cell(q + 1 + m_yd + m_zd);

		uint8_t cubeindex = 0;

		if(c.f    < isol) cubeindex |= 1;
		if(cx.f   < isol) cubeindex |= 2;
		if(cy.f   < isol) cubeindex |= 8;
		if(cxy.f  < isol) cubeindex |= 4;
		if(cz.f   < isol) cubeindex |= 16;
		if(cxz.f  < isol) cubeindex |= 32;
		if(cyz.f  < isol) cubeindex |= 128;
		if(cxyz.f < isol) cubeindex |= 64;

		return cubeindex;
	}

	inline void calc_normal(MarchingCubes::Cache& cache, const MarchingCubes& cubes, size_t q)
	{
		if(!cache.m_normal[q].set)
		{
			cache.m_normal[q].n.x = cubes.m_field[q - 1] - cubes.m_field[q + 1];
			cache.m_normal[q].n.y = cubes.m_field[q - cubes.m_yd] - cubes.m_field[q + cubes.m_yd];
			cache.m_normal[q].n.z = cubes.m_field[q - cubes.m_zd] - cubes.m_field[q + cubes.m_zd];
			cache.m_normal[q].set = true;
		}
	};

	struct Cell { size_t q; float f; };

	template <Axis axis, bool flat>
	inline void calc_side(MarchingCubes::Cache& cache, const MarchingCubes& cubes, int bits, int mask, int i, float isol, float x, float y, float z, const Cell& a, const Cell& b)
	{
		if(bits & mask)
		{
#if !FLAT_BLEND
			if constexpr(!flat)
#endif
			{
				calc_normal(cache, cubes, a.q);
				calc_normal(cache, cubes, b.q);
			}

			const float mu = (isol - a.f) / (b.f - a.f);

			if constexpr(axis == Axis::X)
				cache.vert[i] = vec3(x + mu * cubes.m_delta, y, z);
			else if constexpr(axis == Axis::Y)
				cache.vert[i] = vec3(x, y + mu * cubes.m_delta, z);
			else if constexpr(axis == Axis::Z)
				cache.vert[i] = vec3(x, y, z + mu * cubes.m_delta);

#if !FLAT_BLEND
			if constexpr(!flat)
#endif
				cache.norm[i] = lerp(cache.m_normal[a.q].n, cache.m_normal[b.q].n, mu);
		}
	};

	uint8_t MarchingCubes::polygonize(Cache& cache, const vec3& p, size_t q, float isol) const
	{
		auto cell = [&](size_t q) -> Cell { return { q, m_field[q] }; };
		// cache indices
		const Cell c = cell(q);
		const Cell cx = cell(q + 1);
		const Cell cy = cell(q + m_yd);
		const Cell cz = cell(q + m_zd);
		const Cell cxy = cell(q + 1 + m_yd);
		const Cell cxz = cell(q + 1 + m_zd);
		const Cell cyz = cell(q + m_yd + m_zd);
		const Cell cxyz = cell(q + 1 + m_yd + m_zd);

		uint8_t cubeindex = 0;

		if(c.f    < isol) cubeindex |= 1;
		if(cx.f   < isol) cubeindex |= 2;
		if(cy.f   < isol) cubeindex |= 8;
		if(cxy.f  < isol) cubeindex |= 4;
		if(cz.f   < isol) cubeindex |= 16;
		if(cxz.f  < isol) cubeindex |= 32;
		if(cyz.f  < isol) cubeindex |= 128;
		if(cxyz.f < isol) cubeindex |= 64;

		// if cube is entirely in/out of the surface - bail, nothing to draw

		const int bits = c_edge_table[cubeindex];
		if(bits == 0) return 0;

		const float d = m_delta;
		const vec3 pp = p + d;

		// top of the cube

		// top of the cube
		calc_side<Axis::X, FLAT>(cache, *this, bits, 1,    0,  isol, p.x,  p.y,  p.z,  c,   cx);
		calc_side<Axis::Y, FLAT>(cache, *this, bits, 2,    1,  isol, pp.x, p.y,  p.z,  cx,  cxy);
		calc_side<Axis::X, FLAT>(cache, *this, bits, 4,    2,  isol, p.x,  pp.y, p.z,  cy,  cxy);
		calc_side<Axis::Y, FLAT>(cache, *this, bits, 8,    3,  isol, p.x,  p.y,  p.z,  c,   cy);
		calc_side<Axis::X, FLAT>(cache, *this, bits, 16,   4,  isol, p.x,  p.y,  pp.z, cz,  cxz);
		calc_side<Axis::Y, FLAT>(cache, *this, bits, 32,   5,  isol, pp.x, p.y,  pp.z, cxz, cxyz);
		calc_side<Axis::X, FLAT>(cache, *this, bits, 64,   6,  isol, p.x,  pp.y, pp.z, cyz, cxyz);
		calc_side<Axis::Y, FLAT>(cache, *this, bits, 128,  7,  isol, p.x,  p.y,  pp.z, cz,  cyz);
		calc_side<Axis::Z, FLAT>(cache, *this, bits, 256,  8,  isol, p.x,  p.y,  p.z,  c,   cz);
		calc_side<Axis::Z, FLAT>(cache, *this, bits, 512,  9,  isol, pp.x, p.y,  p.z,  cx,  cxz);
		calc_side<Axis::Z, FLAT>(cache, *this, bits, 1024, 10, isol, pp.x, pp.y, p.z,  cxy, cxyz);
		calc_side<Axis::Z, FLAT>(cache, *this, bits, 2048, 11, isol, p.x,  pp.y, p.z,  cy,  cyz);

		return cubeindex;
	}

	uint32_t MarchingCubes::triangulate(MeshAdapter& output, Cache& cache, uint8_t cubeindex) const
	{
		const CubeSide& side = c_tri_table[cubeindex];

		auto triangle = [&](size_t o1, size_t o2, size_t o3, bool flat = false)
		{
			output.dposition(cache.vert[o1]);
			output.dposition(cache.vert[o2]);
			output.dposition(cache.vert[o3]);

			if(flat)
			{
#if FLAT_BLEND
				vec3 n = normalize(cache.norm[o1] + cache.norm[o2] + cache.norm[o3]);
#else
				vec3 n = normalize(cross(cache.vert[o2] - cache.vert[o1], cache.vert[o3] - cache.vert[o1]));
#endif
				output.normal(n);
				output.normal(n);
				output.normal(n);
			}
			else
			{
				output.normal(cache.norm[o1]);
				output.normal(cache.norm[o2]);
				output.normal(cache.norm[o3]);
			}

			if(false) //output.m_has_uvs)
			{
				output.duv0(vec2(cache.vert[o1]));
				output.duv0(vec2(cache.vert[o2]));
				output.duv0(vec2(cache.vert[o3]));
			}

			if(false) //output.m_has_colors)
			{
				output.colour(to_colour(cache.vert[o1]));
				output.colour(to_colour(cache.vert[o2]));
				output.colour(to_colour(cache.vert[o3]));
			}
		};

		size_t i = 0;
		while(side.tris[i] != -1)
		{
			triangle(side.tris[i+0], side.tris[i+1], side.tris[i+2], FLAT);
			i += 3;
		}

		//assert(i / 3 == side.num);
		return uint32_t(side.num);
	}

	uint32_t MarchingCubes::triangulate(MeshPacker& output, Cache& cache, uint8_t cubeindex) const
	{
		const CubeSide& side = c_tri_table[cubeindex];

		auto triangle = [&](size_t o1, size_t o2, size_t o3, bool flat = false)
		{
			output.m_positions.push_back(cache.vert[o1]);
			output.m_positions.push_back(cache.vert[o2]);
			output.m_positions.push_back(cache.vert[o3]);

			if(flat)
			{
#if FLAT_BLEND
				vec3 n = normalize(cache.norm[o1] + cache.norm[o2] + cache.norm[o3]);
#else
				vec3 n = normalize(cross(cache.vert[o2] - cache.vert[o1], cache.vert[o3] - cache.vert[o1]));
#endif
				output.m_normals.push_back(n);
				output.m_normals.push_back(n);
				output.m_normals.push_back(n);
			}
			else
			{
				output.m_normals.push_back(cache.norm[o1]);
				output.m_normals.push_back(cache.norm[o2]);
				output.m_normals.push_back(cache.norm[o3]);
			}

			if(false) //output.m_has_uvs)
			{
				output.m_uv0s.push_back(vec2(cache.vert[o1]));
				output.m_uv0s.push_back(vec2(cache.vert[o2]));
				output.m_uv0s.push_back(vec2(cache.vert[o3]));
			}
			
			if(false) //output.m_has_colors)
			{
				output.m_colours.push_back(to_colour(cache.vert[o1]));
				output.m_colours.push_back(to_colour(cache.vert[o2]));
				output.m_colours.push_back(to_colour(cache.vert[o3]));
			}
		};

		size_t i = 0;
		while(side.tris[i] != -1)
		{
			triangle(side.tris[i+0], side.tris[i+1], side.tris[i+2], FLAT);
			i += 3;
		}

		//assert(i / 3 == side.num);
		return uint32_t(side.num);
	}

	void MarchingCubes::reset()
	{
		for(size_t i = 0; i < m_size; i++)
			m_field[i] = 0.f;
	}

	void MarchingCubes::begin(Cache& cache) const
	{
		if(cache.m_normal.size() != m_size)
			cache.m_normal.resize(m_size);

		//for(size_t i = 0; i < m_size; i++)
		//	cache.m_normal[i].set = false;

		memset(cache.m_normal.data(), 0, cache.m_normal.size() * sizeof(Cache::Normal));
	}

	uint32_t MarchingCubes::count() const
	{
		uint32_t num_tris = 0;

		const uint32_t subdiv = m_subdiv - 2;
		for(uint32_t z = 1; z < subdiv; z++)
			for(uint32_t y = 1; y < subdiv; y++)
				for(uint32_t x = 1; x < subdiv; x++)
				{
					const size_t q = m_zd * z + m_yd * y + x;
					const uint8_t cubeindex = classify(q, m_isolation);
					num_tris += c_tri_table[cubeindex].num;
				}

		return num_tris;
	}

	void MarchingCubes::direct(MeshAdapter& output) const
	{
		this->begin(m_cache);

		const uint32_t subdiv = m_subdiv - 2;
		for(uint32_t z = 1; z < subdiv; z++)
			for(uint32_t y = 1; y < subdiv; y++)
				for(uint32_t x = 1; x < subdiv; x++)
				{
					const size_t q = m_zd * z + m_yd * y + x;
					const vec3 f = (vec3(float(x), float(y), float(z)) - m_extent) / m_extent; //+ 1
					const uint8_t cubeindex = polygonize(m_cache, f, q, m_isolation);
					triangulate(output, m_cache, cubeindex);
				}
	}

	void MarchingCubes::render(MeshPacker& output) const
	{
		this->begin(m_cache);

		const uint32_t subdiv = m_subdiv - 2;

		for(uint32_t z = 1; z < subdiv; z++)
			for(uint32_t y = 1; y < subdiv; y++)
				for(uint32_t x = 1; x < subdiv; x++)
				{
					const size_t q = m_zd * z + m_yd * y + x;
					const vec3 f = (vec3(uvec3(x, y, z)) - m_extent) / m_extent; //+ 1
					const uint8_t cubeindex = polygonize(m_cache, f, q, m_isolation);
					triangulate(output, m_cache, cubeindex);
				}
	}

	void add_ball(MarchingCubes& cubes, const vec3& ball, float strength, float subtract)
	{
		const float sign = mud::sign(strength);
		strength = abs(strength);

		// Let's solve the equation to find the radius:
		// 1.0 / (0.000001 + radius^2) * strength - subtract = 0
		// -> radius = sqrt(strength / subtract)

		const float size = float(cubes.m_subdiv);
		const float radius = size * sqrt(strength / subtract);
		const vec3 s = ball * size;

		// Don't polygonize in the outer layer because normals aren't well-defined there.
		const uvec3 lo = max(uvec3(floor(s - radius)), uvec3(1U));
		const uvec3 hi = min(uvec3(floor(s + radius)), uvec3(cubes.m_subdiv - 1U));

		for(uint32_t z = lo.z; z < hi.z; z++)
			for(uint32_t y = lo.y; y < hi.y; y++)
				for(uint32_t x = lo.x; x < hi.x; x++)
				{
					size_t offset = cubes.m_zd * z + cubes.m_yd * y + x;

					vec3 f = vec3(uvec3(x, y, z)) / size - ball;

					float val = strength / (0.000001f + sq(f.x) + sq(f.y) + sq(f.z)) - subtract;
					if(val > 0.f) cubes.m_field[offset] += val * sign;
				}
	}

	void add_planeX(MarchingCubes& cubes, float strength, float subtract)
	{
		const size_t subdiv = cubes.m_subdiv;
		const float size = float(cubes.m_subdiv);
		const size_t yd = cubes.m_yd;
		const size_t zd = cubes.m_zd;
		vector<float>& field = cubes.m_field;

		//const size_t dist = size_t(min(size, size * sqrt(strength / subtract)));
		const size_t dist = size_t(min(size, size * float(sqrt(strength / subtract)))); // clang, why do you hate me

		for(size_t x = 0; x < dist; x++)
		{
			const float xdiv = float(x) / size;
			const float xx = xdiv * xdiv;
			const float val = strength / (0.0001f + xx) - subtract;

			if(val <= 0.0) continue;

			for(size_t y = 0; y < subdiv; y++)
			{
				const size_t cxy = x + y * yd;

				for(size_t z = 0; z < subdiv; z++)
					field[zd * z + cxy] += val;
			}
		}
	}

	void add_planeY(MarchingCubes& cubes, float strength, float subtract)
	{
		const size_t subdiv = cubes.m_subdiv;
		const float size = float(cubes.m_subdiv);
		const size_t yd = cubes.m_yd;
		const size_t zd = cubes.m_zd;
		vector<float>& field = cubes.m_field;

		//const size_t dist = size_t(min(size, size * sqrt(strength / subtract)));
		const size_t dist = size_t(min(size, size * float(sqrt(strength / subtract)))); // clang, why do you hate me

		for(size_t y = 0; y < dist; y++)
		{
			const float ydiv = y / size;
			const float yy = ydiv * ydiv;
			const float val = strength / (0.0001f + yy) - subtract;

			if(val <= 0.f) continue;

			const size_t cy = y * yd;

			for(size_t x = 0; x < subdiv; x++)
			{
				const size_t cxy = cy + x;

				for(size_t z = 0; z < subdiv; z++)
					field[zd * z + cxy] += val;
			}
		}
	}

	void add_planeZ(MarchingCubes& cubes, float strength, float subtract)
	{
		const size_t subdiv = cubes.m_subdiv;
		const float size = float(cubes.m_subdiv);
		const size_t yd = cubes.m_yd;
		const size_t zd = cubes.m_zd;
		vector<float>& field = cubes.m_field;

		//const size_t dist = size_t(min(size, size * sqrt(strength / subtract)));
		const size_t dist = size_t(min(size, size * float(sqrt(strength / subtract)))); // clang, why do you hate me

		for(size_t z = 0; z < dist; z++)
		{
			const float zdiv = z / size;
			const float zz = zdiv * zdiv;
			const float val = strength / (0.0001f + zz) - subtract;
			if(val <= 0.f) continue;

			const size_t cz = zd * z;

			for(size_t y = 0; y < subdiv; y++)
			{
				const size_t cyz = cz + y * yd;

				for(size_t x = 0; x < subdiv; x++)
					field[cyz + x] += val;
			}
		}
	}


	// These tables are straight from Paul Bourke's page:
	// http://paulbourke.net/geometry/polygonise/
	// who in turn got them from Cory Gene Bloyd.

	const int c_edge_table[] =
	{
		0x0, 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
		0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
		0x190, 0x99, 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
		0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
		0x230, 0x339, 0x33, 0x13a, 0x636, 0x73f, 0x435, 0x53c,
		0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
		0x3a0, 0x2a9, 0x1a3, 0xaa, 0x7a6, 0x6af, 0x5a5, 0x4ac,
		0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
		0x460, 0x569, 0x663, 0x76a, 0x66, 0x16f, 0x265, 0x36c,
		0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
		0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff, 0x3f5, 0x2fc,
		0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
		0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55, 0x15c,
		0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
		0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc,
		0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
		0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
		0xcc, 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
		0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
		0x15c, 0x55, 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
		0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
		0x2fc, 0x3f5, 0xff, 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
		0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
		0x36c, 0x265, 0x16f, 0x66, 0x76a, 0x663, 0x569, 0x460,
		0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
		0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa, 0x1a3, 0x2a9, 0x3a0,
		0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
		0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33, 0x339, 0x230,
		0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
		0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99, 0x190,
		0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
		0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0
	};

	const CubeSide c_tri_table[] =
	{
		{ 0, { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1 } },
		{ 2, { 8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1 } },
		{ 3, { 3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1 } },
		{ 4, { 4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1 } },
		{ 3, { 4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1 } },
		{ 2, { 9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1 } },
		{ 3, { 10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1 } },
		{ 4, { 5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1 } },
		{ 3, { 5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1 } },
		{ 4, { 8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1 } },
		{ 3, { 2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1 } },
		{ 4, { 2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1 } },
		{ 3, { 11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1 } },
		{ 5, { 5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1 } },
		{ 5, { 11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1 } },
		{ 2, { 11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1 } },
		{ 2, { 2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1 } },
		{ 3, { 6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1 } },
		{ 4, { 3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1 } },
		{ 3, { 6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1 } },
		{ 3, { 6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1 } },
		{ 4, { 8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1 } },
		{ 5, { 7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1 } },
		{ 3, { 3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1 } },
		{ 4, { 0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1 } },
		{ 5, { 9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1 } },
		{ 4, { 8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1 } },
		{ 5, { 5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1 } },
		{ 5, { 0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1 } },
		{ 4, { 6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1 } },
		{ 2, { 10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1 } },
		{ 3, { 1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1 } },
		{ 2, { 0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1 } },
		{ 4, { 3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1 } },
		{ 5, { 6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1 } },
		{ 4, { 9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1 } },
		{ 5, { 8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1 } },
		{ 3, { 3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1 } },
		{ 4, { 10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1 } },
		{ 3, { 10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1 } },
		{ 5, { 2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1 } },
		{ 3, { 7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1 } },
		{ 5, { 2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1 } },
		{ 5, { 1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1 } },
		{ 4, { 11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1 } },
		{ 5, { 8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1 } },
		{ 2, { 0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1 } },
		{ 1, { 7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1 } },
		{ 2, { 7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1 } },
		{ 3, { 10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1 } },
		{ 4, { 0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1 } },
		{ 3, { 7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1 } },
		{ 3, { 6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1 } },
		{ 4, { 4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1 } },
		{ 5, { 10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1 } },
		{ 3, { 8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1 } },
		{ 3, { 1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1 } },
		{ 3, { 10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1 } },
		{ 5, { 4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1 } },
		{ 2, { 10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1 } },
		{ 3, { 9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1, } },
		{ 4, { 7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1 } },
		{ 5, { 3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1 } },
		{ 3, { 7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1 } },
		{ 4, { 3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1 } },
		{ 5, { 6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1 } },
		{ 4, { 9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1 } },
		{ 5, { 1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1 } },
		{ 5, { 4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1 } },
		{ 4, { 7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1 } },
		{ 3, { 6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1 } },
		{ 4, { 0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1 } },
		{ 3, { 6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1 } },
		{ 5, { 0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1 } },
		{ 5, { 11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1 } },
		{ 4, { 6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1 } },
		{ 4, { 5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1 } },
		{ 3, { 9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1 } },
		{ 5, { 1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1 } },
		{ 2, { 1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 5, { 1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1 } },
		{ 4, { 10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1 } },
		{ 2, { 0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1 } },
		{ 3, { 11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1 } },
		{ 4, { 9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1 } },
		{ 5, { 7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1 } },
		{ 3, { 2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1 } },
		{ 4, { 9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1 } },
		{ 5, { 9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1 } },
		{ 2, { 1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1 } },
		{ 4, { 0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1 } },
		{ 5, { 10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1 } },
		{ 4, { 2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1 } },
		{ 5, { 0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1 } },
		{ 5, { 0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1 } },
		{ 2, { 9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1 } },
		{ 3, { 5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 5, { 3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1 } },
		{ 4, { 5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1 } },
		{ 3, { 8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1 } },
		{ 1, { 9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1 } },
		{ 4, { 1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1 } },
		{ 5, { 3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1 } },
		{ 4, { 4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1 } },
		{ 5, { 9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1 } },
		{ 3, { 11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1 } },
		{ 4, { 2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1 } },
		{ 5, { 9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1 } },
		{ 5, { 3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1 } },
		{ 2, { 1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1 } },
		{ 2, { 4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1 } },
		{ 2, { 0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 3, { 2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 4, { 2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1 } },
		{ 1, { 1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 2, { 1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 1, { 0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } },
		{ 0, { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 } }
	};
}
