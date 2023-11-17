//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>
#include <geom/Shape.h>
#include <geom/Symbol.h>

namespace two
{
	export_ struct TWO_GEOM_EXPORT ShapeSize
	{
		ShapeSize() : vertex_count(0), index_count(0) {}
		ShapeSize(uint32_t verts, uint32_t indices) : vertex_count(verts), index_count(indices) {}

		operator uvec2() { return vec; }

		union {
			uvec2 vec;
			struct { uint vertex_count; uint index_count; };
		};
	};

	export_ struct TWO_GEOM_EXPORT ProcShape
	{
		Symbol m_symbol;
		const Shape* m_shape;
		DrawMode m_draw_mode;
	};

	export_ TWO_GEOM_EXPORT ShapeSize symbol_line_size(const ProcShape& shape);
	export_ TWO_GEOM_EXPORT ShapeSize symbol_triangle_size(const ProcShape& shape);

	export_ TWO_GEOM_EXPORT void symbol_draw_lines(const ProcShape& shape, MeshAdapter& writer);
	export_ TWO_GEOM_EXPORT void symbol_draw_triangles(const ProcShape& shape, MeshAdapter& writer);
}
