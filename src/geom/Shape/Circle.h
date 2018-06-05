//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Generated/Forward.h>
#include <geom/Shape/ProcShape.h>
#include <geom/Shapes.h>

namespace mud
{
	MUD_GEOM_EXPORT uint16_t circle_vertices(const ProcShape& shape, const vec3& position, vec2 radius, SignedAxis axis, bool lines, MeshData& data, bool outward_normals = false);

	MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Circle& circle);
	MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshData& data);

	MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle);
	MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshData& data);

	MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis);
	MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis, MeshData& data);

	MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis);
	MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis, MeshData& data);

	MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Torus& torus);
	MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Torus& torus, MeshData& data);

	MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Torus& torus);
	MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshData& data);
}
