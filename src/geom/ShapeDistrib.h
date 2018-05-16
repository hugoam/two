//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Util/Dispatch.h>
#include <obj/Util/Global.h>
#include <math/Vec.h>
#include <geom/Generated/Forward.h>

#include <vector>

namespace mud
{
	class MUD_MATH_EXPORT RandomShapePoint : public Dispatch<vec3>, public LazyGlobal<RandomShapePoint>
	{
	public:
		RandomShapePoint();
	};

	MUD_MATH_EXPORT std::vector<vec3> distribute_shape(const Shape& shape, size_t count);
}
