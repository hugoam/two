//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <geom/Shape/Spheroid.h>
#include <geom/Shape/Circle.h>

namespace mud
{
	CompoundShape shape_compound(const ProcShape& shape, const Spheroid& spheroid)
	{
		return { { ProcShape{ shape.m_symbol, &spheroid.m_circleX, shape.m_draw_mode, shape.m_position },
				   ProcShape{ shape.m_symbol, &spheroid.m_circleY, shape.m_draw_mode, shape.m_position },
				   ProcShape{ shape.m_symbol, &spheroid.m_circleZ, shape.m_draw_mode, shape.m_position } } };
	}
}
