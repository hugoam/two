//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Generated/Forward.h>
#include <geom/Shape/ProcShape.h>

namespace mud
{
	MUD_GEOM_EXPORT void quad_vertices(const ProcShape& shape, const Quad& quad, MeshData& data);

	MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Quad& quad);
	MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Quad& quad, MeshData& data);

	MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Quad& quad);
	MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Quad& quad, MeshData& data);
}
