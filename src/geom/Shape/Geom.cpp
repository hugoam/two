//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#endif

#ifdef MUD_MODULES
import mud.math;
module mud.geom;
#else
#include <geom/Shape/Geom.h>
#include <geom/Mesh.h>
#endif

namespace mud
{
	ShapeSize size_shape_lines(const ProcShape& shape, const Geometry& geometry)
	{
		UNUSED(shape);
		return { int(geometry.m_vertices.size()), int(geometry.m_triangles.size()) * 6 };
	}

	void draw_shape_lines(const ProcShape& shape, const Geometry& geometry, MeshData& data)
	{
		for(const Vertex& vertex : geometry.m_vertices)
			data.position(geometry.m_center + vertex.m_position)
				.colour(shape.m_symbol.m_outline);

		for(const Tri& triangle : geometry.m_triangles)
		{
			data.line(triangle.a, triangle.b);
			data.line(triangle.b, triangle.c);
			data.line(triangle.c, triangle.a);
		}
	}
	
	ShapeSize size_shape_triangles(const ProcShape& shape, const Geometry& geometry)
	{
		UNUSED(shape);
		return { int(geometry.m_vertices.size()), int(geometry.m_triangles.size()) * 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Geometry& geometry, MeshData& data)
	{
		for(const Vertex& vertex : geometry.m_vertices)
			data.position(geometry.m_center + vertex.m_position)
				.colour(Colour::White);

		for(const Tri& triangle : geometry.m_triangles)
			data.tri(triangle.a, triangle.b, triangle.c);
	}
}
