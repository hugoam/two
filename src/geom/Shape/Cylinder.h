//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Shape/ProcShape.h>

namespace mud
{
	MUD_MATH_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Cylinder& cylinder);
	MUD_MATH_EXPORT void draw_shape_lines(const ProcShape& shape, const Cylinder& cylinder, MeshData& data);

	MUD_MATH_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Cylinder& cylinder);
	MUD_MATH_EXPORT void draw_shape_triangles(const ProcShape& shape, const Cylinder& cylinder, MeshData& data);
}
