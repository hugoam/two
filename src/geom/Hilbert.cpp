//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.geom;

namespace two
{
	// ref http://www.openprocessing.org/visuals/?visualID=15599

	vector<vec3> hilbert2d(vec3 center, float size, int iterations, uint v0, uint v1, uint v2, uint v3)
	{
		float half = size / 2.f;

		const vec3 corners[] = {
			vec3(center.x - half, center.y, center.z - half),
			vec3(center.x - half, center.y, center.z + half),
			vec3(center.x + half, center.y, center.z + half),
			vec3(center.x + half, center.y, center.z - half)
		};

		const vector<vec3> curve = {
			corners[v0],
			corners[v1],
			corners[v2],
			corners[v3]
		};

		// Recurse iterations
		if(0 <= --iterations)
		{
			vector<vec3> result = {};

			extend(result, hilbert2d(curve[0], half, iterations, v0, v3, v2, v1));
			extend(result, hilbert2d(curve[1], half, iterations, v0, v1, v2, v3));
			extend(result, hilbert2d(curve[2], half, iterations, v0, v1, v2, v3));
			extend(result, hilbert2d(curve[3], half, iterations, v2, v1, v0, v3));

			// Return recursive call
			return result;
		}

		// Return complete Hilbert Curve.
		return curve;

	}

	vector<vec3> hilbert3d(vec3 center, float size, int iterations, uint v0, uint v1, uint v2, uint v3, uint v4, uint v5, uint v6, uint v7)
	{
		float half = size / 2.f;

		const vec3 corners[] =
		{
			vec3(center.x - half, center.y + half, center.z - half),
			vec3(center.x - half, center.y + half, center.z + half),
			vec3(center.x - half, center.y - half, center.z + half),
			vec3(center.x - half, center.y - half, center.z - half),
			vec3(center.x + half, center.y - half, center.z - half),
			vec3(center.x + half, center.y - half, center.z + half),
			vec3(center.x + half, center.y + half, center.z + half),
			vec3(center.x + half, center.y + half, center.z - half)
		};

		const vector<vec3> curve = {
			corners[v0],
			corners[v1],
			corners[v2],
			corners[v3],
			corners[v4],
			corners[v5],
			corners[v6],
			corners[v7]
		};

		// Recurse iterations
		if (--iterations >= 0)
		{
			vector<vec3> result = {};

			extend(result, hilbert3d(curve[0], half, iterations, v0, v3, v4, v7, v6, v5, v2, v1 ));
			extend(result, hilbert3d(curve[1], half, iterations, v0, v7, v6, v1, v2, v5, v4, v3 ));
			extend(result, hilbert3d(curve[2], half, iterations, v0, v7, v6, v1, v2, v5, v4, v3 ));
			extend(result, hilbert3d(curve[3], half, iterations, v2, v3, v0, v1, v6, v7, v4, v5 ));
			extend(result, hilbert3d(curve[4], half, iterations, v2, v3, v0, v1, v6, v7, v4, v5 ));
			extend(result, hilbert3d(curve[5], half, iterations, v4, v3, v2, v5, v6, v1, v0, v7 ));
			extend(result, hilbert3d(curve[6], half, iterations, v4, v3, v2, v5, v6, v1, v0, v7 ));
			extend(result, hilbert3d(curve[7], half, iterations, v6, v5, v2, v1, v0, v3, v4, v7 ));

			// Return recursive call
			return result;
		}

		// Return complete Hilbert Curve.
		return curve;
	}
}
