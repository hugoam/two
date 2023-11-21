//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.geom;

namespace two
{
	ShapeSize size_shape_lines(const ProcShape& shape, const Geometry& geometry)
	{
		UNUSED(shape);
		return { uint32_t(geometry.m_vertices.size()), uint32_t(geometry.m_triangles.size()) * 6U };
	}

	void draw_shape_lines(const ProcShape& shape, const Geometry& geometry, MeshAdapter& writer)
	{
		for(const Vertex& vertex : geometry.m_vertices)
			writer.position(geometry.m_center + vertex.m_position)
				  .colour(shape.m_symbol.m_outline);

		for(const Tri& triangle : geometry.m_triangles)
		{
			writer.line(uint16_t(triangle.a), uint16_t(triangle.b));
			writer.line(uint16_t(triangle.b), uint16_t(triangle.c));
			writer.line(uint16_t(triangle.c), uint16_t(triangle.a));
		}
	}
	
	ShapeSize size_shape_triangles(const ProcShape& shape, const Geometry& geometry)
	{
		UNUSED(shape);
		return { uint32_t(geometry.m_vertices.size()), uint32_t(geometry.m_triangles.size()) * 3U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Geometry& geometry, MeshAdapter& writer)
	{
		UNUSED(shape);
		for(const Vertex& vertex : geometry.m_vertices)
			writer.position(geometry.m_center + vertex.m_position)
				  .colour(Colour::White);

		for(const Tri& triangle : geometry.m_triangles)
			writer.tri(triangle.a, triangle.b, triangle.c);
	}
}
