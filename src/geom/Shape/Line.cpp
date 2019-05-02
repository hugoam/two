//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.geom;
#else
#include <math/Vec.hpp>
#include <geom/Shape/Line.h>
#include <geom/Shapes.h>
#include <geom/Primitive.hpp>
#endif

namespace two
{
	void draw_line(const vec3& start, const vec3& end, const Colour& colour, MeshAdapter& writer)
	{
		writer.position(start)
			  .colour(colour);
		writer.position(end)
			  .colour(colour);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Line& line)
	{
		UNUSED(shape); UNUSED(line);
		return { 2, 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Line& line, MeshAdapter& writer)
	{
		draw_line(line.m_start, line.m_end, shape.m_symbol.m_outline, writer);
		writer.line(0, 1);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Line& line)
	{
		UNUSED(shape); UNUSED(line);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Line& line, MeshAdapter& writer)
	{
		UNUSED(shape); UNUSED(line); UNUSED(writer);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Grid2& grid)
	{
		UNUSED(shape);
		uint16_t lines = uint16_t(grid.m_size.x) + 1 + uint16_t(grid.m_size.y) + 1;
		return { lines * 2U, lines * 2U };
	}

	void draw_shape_lines(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer)
	{
		vec2 half = grid.m_size * grid.m_space / 2.f;
		vec3 origin = grid.m_center - vec3(half.x, 0.f, half.y);

		for(size_t x = 0; x < size_t(grid.m_size.x) + 1; ++x)
			draw_line(origin + to_xz(grid.m_space * vec2(float(x), 0.f)), origin + to_xz(grid.m_space * vec2(float(x), grid.m_size.y)), shape.m_symbol.m_outline, writer);
		for(size_t y = 0; y < size_t(grid.m_size.y) + 1; ++y)
			draw_line(origin + to_xz(grid.m_space * vec2(0.f, float(y))), origin + to_xz(grid.m_space * vec2(grid.m_size.x, float(y))), shape.m_symbol.m_outline, writer);

		uint16_t lines = uint16_t(grid.m_size.x) + 1 + uint16_t(grid.m_size.y) + 1;
		for(uint16_t i = 0; i < lines; ++i)
			writer.line(i * 2, i * 2 + 1);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Grid2& grid)
	{
		UNUSED(shape); UNUSED(grid);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Grid2& grid, MeshAdapter& writer)
	{
		UNUSED(shape); UNUSED(grid); UNUSED(writer);
	}
}
