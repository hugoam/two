//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.geom;
#else
#include <geom/Shape/Spheroid.h>
#include <geom/Shape/Circle.h>
#endif

namespace two
{
	CompoundShape shape_compound(const ProcShape& shape, const Spheroid& spheroid)
	{
		return { { ProcShape{ shape.m_symbol, &spheroid.m_circleX, shape.m_draw_mode },
				   ProcShape{ shape.m_symbol, &spheroid.m_circleY, shape.m_draw_mode },
				   ProcShape{ shape.m_symbol, &spheroid.m_circleZ, shape.m_draw_mode } } };
	}
}
