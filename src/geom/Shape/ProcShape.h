//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Colour.h>
#include <math/Vec.h>
#endif
#include <geom/Forward.h>
#include <geom/Shape.h>
#include <geom/Symbol.h>

namespace mud
{
	export_ struct MUD_GEOM_EXPORT ShapeSize
	{
		ShapeSize() : vertex_count(0), index_count(0) {}
		ShapeSize(int verts, int indices) : vertex_count(verts), index_count(indices) {}

		operator uvec2() { return vec; }

		union {
			uvec2 vec;
			struct { int vertex_count; int index_count; };
		};
	};

	export_ struct MUD_GEOM_EXPORT ProcShape
	{
		Symbol m_symbol;
		const Shape* m_shape;
		DrawMode m_draw_mode;
	};

	export_ MUD_GEOM_EXPORT ShapeSize symbol_line_size(const ProcShape& shape);
	export_ MUD_GEOM_EXPORT ShapeSize symbol_triangle_size(const ProcShape& shape);

	export_ MUD_GEOM_EXPORT void symbol_draw_lines(const ProcShape& shape, MeshAdapter& writer);
	export_ MUD_GEOM_EXPORT void symbol_draw_triangles(const ProcShape& shape, MeshAdapter& writer);
}
