//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Shape/CompoundShape.h>

namespace two
{
	TWO_GEOM_EXPORT CompoundShape shape_compound(const ProcShape& shape, const Spheroid& spheroid);
}
