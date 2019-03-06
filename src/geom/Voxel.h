//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/function.h>
#include <math/Vec.h>
#include <math/Colour.h>
#endif
#include <geom/Forward.h>

namespace mud
{
	// port of http://webglsamples.org/blob/blob.html
	class MarchingCubes
	{
	public:
		float m_isolation = 80.f;

		uint32_t m_subdiv = 32;
		size_t m_size;
		float m_extent;

		float m_delta;

		uint32_t m_xd;
		uint32_t m_yd;
		uint32_t m_zd;

		vector<float> m_field;
		//vector<uint8_t> m_class;

		struct Cache
		{
			struct Normal { vec3 n; bool set = false; };
			vector<Normal> m_normal;

			vec3 vert[12];
			vec3 norm[12];
		};

	public:
		MarchingCubes(uint32_t resolution);

		// immediate render mode simulator
		uint8_t classify(size_t q, float isol) const;
		uint8_t polygonize(Cache& cache, const vec3& p, size_t q, float isol) const;
		uint32_t triangulate(MeshAdapter& output, Cache& cache, uint8_t cubeindex) const;
		uint32_t triangulate(MeshPacker& output, Cache& cache, uint8_t cubeindex) const;

		void reset();

		void begin(Cache& cache) const;
		uint32_t count() const;
		void render(MeshAdapter& output, Cache& cache) const;
		void render(MeshPacker& output, Cache& cache) const;
	};

	void add_ball(MarchingCubes& cubes, vec3 ball, float strength, float subtract);

	void add_planeX(MarchingCubes& cubes, float strength, float subtract);
	void add_planeY(MarchingCubes& cubes, float strength, float subtract);
	void add_planeZ(MarchingCubes& cubes, float strength, float subtract);
}
