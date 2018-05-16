//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <geom/Shape/Triangle.h>
#include <geom/Shapes.h>
#include <geom/Primitive.h>

//#define PK_GLITCH

namespace mud
{
	void triangle_vertices(const ProcShape& shape, const Triangle& triangle, bool fill, MeshData& data)
	{
		vec3 vertices[3] = { { -triangle.m_size.x / 2.f, -triangle.m_size.y / 2.f, 0.f },
							 {  triangle.m_size.x / 2.f, -triangle.m_size.y / 2.f, 0.f },
							 {  0.f,                      triangle.m_size.y / 2.f, 0.f } };

		for(int i = 0; i < 3; i++)
			data.position(shape.m_position + vertices[i])
				.colour(fill ? shape.m_symbol.m_fill : shape.m_symbol.m_outline);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Triangle& triangle)
	{
		UNUSED(shape); UNUSED(triangle);
		return { 3, 6 };
	}

	void draw_shape_lines(const ProcShape& shape, const Triangle& triangle, MeshData& data)
	{
		triangle_vertices(shape, triangle, false, data);
		for(int i = 0; i < 3; i++)
			data.line(i, (i + 1) % 3);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Triangle& triangle)
	{
		UNUSED(shape); UNUSED(triangle);
		return { 3, 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Triangle& triangle, MeshData& data)
	{
		triangle_vertices(shape, triangle, true, data);
		data.tri(0, 1, 2);
	}
}
