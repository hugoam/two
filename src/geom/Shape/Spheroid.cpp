//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
module mud.geom;
#else
#include <geom/Shape/Spheroid.h>
#include <geom/Shape/Circle.h>
#endif

namespace mud
{
	CompoundShape shape_compound(const ProcShape& shape, const Spheroid& spheroid)
	{
		return { { ProcShape{ shape.m_symbol, &spheroid.m_circleX, shape.m_draw_mode },
				   ProcShape{ shape.m_symbol, &spheroid.m_circleY, shape.m_draw_mode },
				   ProcShape{ shape.m_symbol, &spheroid.m_circleZ, shape.m_draw_mode } } };
	}
}
