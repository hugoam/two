//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Generated/Forward.h>
#include <geom/Shape/ProcShape.h>

#include <vector>

namespace mud
{
	struct MUD_MATH_EXPORT CompoundShape
	{
		std::vector<ProcShape> m_shapes;
	};

	MUD_MATH_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const CompoundShape& compound);
	MUD_MATH_EXPORT void draw_shape_lines(const ProcShape& shape, const CompoundShape& compound, MeshData& data);

	MUD_MATH_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const CompoundShape& compound);
	MUD_MATH_EXPORT void draw_shape_triangles(const ProcShape& shape, const CompoundShape& compound, MeshData& data);
}
