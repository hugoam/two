//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Generated/Forward.h>
#include <geom/Shape/ProcShape.h>

namespace mud
{
	MUD_MATH_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Box& box);
	MUD_MATH_EXPORT void draw_shape_lines(const ProcShape& shape, const Box& box, MeshData& data);

	MUD_MATH_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Box& box);
	MUD_MATH_EXPORT void draw_shape_triangles(const ProcShape& shape, const Box& box, MeshData& data);

	// Cube : Box(cube)
	// Aabb : Box(aabb)
}
