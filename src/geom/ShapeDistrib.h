//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>

namespace two
{
	export_ class TWO_GEOM_EXPORT RandomShapePoint : public Dispatch<vec3>, public LazyGlobal<RandomShapePoint>
	{
	public:
		RandomShapePoint();
	};

	export_ TWO_GEOM_EXPORT vector<vec3> distribute_shape(const Shape& shape, size_t count);
}
