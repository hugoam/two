//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>
#include <geom/Shape/ProcShape.h>

namespace two
{
	export_ TWO_GEOM_EXPORT ShapeSize size_shape_lines(const ProcShape& shape, const Geometry& geom);
	export_ TWO_GEOM_EXPORT void draw_shape_lines(const ProcShape& shape, const Geometry& geom, MeshAdapter& writer);

	export_ TWO_GEOM_EXPORT ShapeSize size_shape_triangles(const ProcShape& shape, const Geometry& geom);
	export_ TWO_GEOM_EXPORT void draw_shape_triangles(const ProcShape& shape, const Geometry& geom, MeshAdapter& writer);
}
