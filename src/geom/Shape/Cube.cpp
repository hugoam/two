//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <math/Vec.hpp>
#include <geom/Shape/Cube.h>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Primitive.h>
#include <geom/Shape/Quad.h>
#endif

namespace mud
{
	ShapeSize size_cube_corners_lines(const ProcShape& shape, const Box& box)
	{
		UNUSED(shape); UNUSED(box);
		return { 8 * 4, 8 * 3 * 2 };
	}

	void draw_cube_corners_lines(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
		for(int i = 0; i < 8; ++i)
		{
			vec3 position = box.m_center + box.m_vertices[i];

			static const vec3 components[3] = { X3, Y3, Z3 };
			float size_factor = 0.2f;
			
			writer.position(position)
				  .colour(shape.m_symbol.m_outline);

			for(int j = 0; j < 3; ++j)
				writer.position(position - position * components[j] * size_factor)
					  .colour(shape.m_symbol.m_outline);
		}


		for(uint16_t i = 0; i < 8 * 4; i+=4)
		{
			writer.line(i, i + 1);
			writer.line(i, i + 2);
			writer.line(i, i + 3);
		}
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Box& box)
	{
		//return size_cube_corners_lines(shape, box);
		UNUSED(shape); UNUSED(box);
		return { 8, 24 };
	}

	void draw_shape_lines(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
		//return draw_cube_corners_lines(shape, box, writer);

		for(int i = 0; i < 8; ++i)
			writer.position(box.m_center + box.m_vertices[i])
				  .colour(shape.m_symbol.m_outline);

		for(uint16_t i = 0; i < 4; ++i)
			writer.line(i, (i + 1) % 4);

		for(uint16_t i = 4; i < 8; ++i)
			writer.line(i,  i == 7 ? 4 : i + 1);

		writer.line(1, 4);
		writer.line(2, 7);
		writer.line(0, 5);
		writer.line(3, 6);
	}

#define CUBE_NORMALS 1

	ShapeSize size_shape_triangles(const ProcShape& shape, const Box& box)
	{
		UNUSED(shape); UNUSED(box);
#if CUBE_NORMALS
		return { 24, 36 };
#else
		return { 16, 36 };
#endif
	}

	void draw_cube_quad(const ProcShape& shape, const Box& box, MeshAdapter& writer, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
	{
		draw_shape_triangles(shape, Quad(box.m_vertices[a], box.m_vertices[b], box.m_vertices[c], box.m_vertices[d]), writer);
		writer.m_offset += 4;
	}

	void draw_shape_triangles(const ProcShape& shape, const Box& box, MeshAdapter& writer)
	{
#if CUBE_NORMALS
		draw_cube_quad(shape, box, writer, 0, 1, 2, 3);
		draw_cube_quad(shape, box, writer, 4, 5, 6, 7);
		draw_cube_quad(shape, box, writer, 0, 3, 6, 5);
		draw_cube_quad(shape, box, writer, 4, 7, 2, 1);
		draw_cube_quad(shape, box, writer, 3, 2, 7, 6);
		draw_cube_quad(shape, box, writer, 5, 4, 1, 0);
#else
		static vec2 quadUVs[4] = { { 1.f, 1.f }, { 1.f, 0.f }, { 0.f, 0.f }, { 0.f, 1.f } };

		for(int i = 0; i < 8; ++i)
			writer.position(shape.m_position + box.m_vertices[i])
				  .colour(Colour::White)
				  .uv0(quadUVs[i%4]);

		int i = 0;
		for(int v : { 3, 2, 7, 6, 5, 4, 1, 0 })
			writer.position(shape.m_position + box.m_vertices[v])
				  .colour(Colour::White)
				  .uv0(quadUVs[i++ % 4]);

		writer.quad(0, 1, 2, 3);
		writer.quad(4, 5, 6, 7);

		writer.quad(0, 3, 6, 5);
		writer.quad(4, 7, 2, 1);

		writer.quad(8, 9, 10, 11);
		writer.quad(12, 13, 14, 15);
#endif
	}
}
