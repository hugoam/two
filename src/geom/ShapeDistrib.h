//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <type/Dispatch.h>
#include <infra/Global.h>
#include <math/Vec.h>
#endif
#include <geom/Forward.h>

namespace mud
{
	export_ class MUD_GEOM_EXPORT RandomShapePoint : public Dispatch<vec3>, public LazyGlobal<RandomShapePoint>
	{
	public:
		RandomShapePoint();
	};

	export_ MUD_GEOM_EXPORT vector<vec3> distribute_shape(const Shape& shape, size_t count);
}
