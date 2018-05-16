//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Shape/CompoundShape.h>

namespace mud
{
	MUD_MATH_EXPORT CompoundShape shape_compound(const ProcShape& shape, const Spheroid& spheroid);
}
