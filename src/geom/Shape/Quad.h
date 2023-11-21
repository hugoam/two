//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>
#include <geom/Shape/ProcShape.h>

namespace two
{
	TWO_GEOM_EXPORT void quad_vertices(const ProcShape& shape, const vec3& center, const vec3& a, const vec3& b, const vec3& c, const vec3& d, bool fill, MeshAdapter& writer);
	TWO_GEOM_EXPORT void quad_vertices(const ProcShape& shape, const vec3& center, span<vec3> vertices, bool fill, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Quad& quad);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Quad& quad, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Quad& quad);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Quad& quad, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Grid3& grid);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Grid3& grid);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer);
}
