//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>
#include <geom/Shape/ProcShape.h>
#include <geom/Shapes.h>

namespace mud
{
	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const ArcLine& arc);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const ArcLine& arc);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer);

	MUD_GEOM_EXPORT uint16_t circle_vertices(const ProcShape& shape, const vec3& position, vec2 radius, SignedAxis axis, bool lines, MeshAdapter& writer, bool outward_normals = false);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Circle& circle);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Torus& torus);
	export_ MUD_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Torus& torus, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Torus& torus);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshAdapter& writer);

	export_ MUD_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const TorusKnot& torus);
	export_ MUD_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const TorusKnot& torus, MeshAdapter& writer);
}
