//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <math/Vec.h>
#include <geom/Forward.h>

namespace two
{
	export_ TWO_GEOM_EXPORT vector<vec3> hilbert2d(vec3 center = vec3(0.f), float size = 10.f, int iterations = 1, 
												   uint v0 = 0, uint v1 = 1, uint v2 = 2, uint v3 = 3);

	export_ TWO_GEOM_EXPORT vector<vec3> hilbert3d(vec3 center = vec3(0.f), float size = 10.f, int iterations = 1,
												   uint v0 = 0, uint v1 = 1, uint v2 = 2, uint v3 = 3, uint v4 = 4, uint v5 = 5, uint v6 = 6, uint v7 = 7);
}
