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
module mud.geom;
#else
#include <geom/Shape/Line.h>
#include <geom/Shapes.h>
#include <geom/Primitive.h>
#endif

namespace mud
{
	void draw_line(const vec3& start, const vec3& end, const Colour& colour, MeshData& data)
	{
		data.position(start)
			.colour(colour);
		data.position(end)
			.colour(colour);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Line& line)
	{
		UNUSED(shape); UNUSED(line);
		return { 2, 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Line& line, MeshData& data)
	{
		draw_line(line.m_start, line.m_end, shape.m_symbol.m_outline, data);
		data.line(0, 1);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Line& line)
	{
		UNUSED(shape); UNUSED(line);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Line& line, MeshData& data)
	{
		UNUSED(shape); UNUSED(line); UNUSED(data);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Grid2& grid)
	{
		UNUSED(shape);
		uint16_t lines = uint16_t(grid.m_size.x) + 1 + uint16_t(grid.m_size.y) + 1;
		return { lines * 2, lines * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Grid2& grid, MeshData& data)
	{
		for(size_t x = 0; x < size_t(grid.m_size.x) + 1; ++x)
			draw_line(grid.m_center + vec3{ float(x), 0.f, 0.f }, grid.m_center + vec3{ float(x), 0.f, grid.m_size.y }, shape.m_symbol.m_outline, data);
		for(size_t y = 0; y < size_t(grid.m_size.y) + 1; ++y)
			draw_line(grid.m_center + vec3{ 0.f, 0.f, float(y) }, grid.m_center + vec3{ grid.m_size.x, 0.f, float(y) }, shape.m_symbol.m_outline, data);

		uint16_t lines = uint16_t(grid.m_size.x) + 1 + uint16_t(grid.m_size.y) + 1;
		for(uint16_t i = 0; i < lines; ++i)
			data.line(i * 2, i * 2 + 1);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Grid2& grid)
	{
		UNUSED(shape); UNUSED(grid);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Grid2& grid, MeshData& data)
	{
		UNUSED(shape); UNUSED(grid); UNUSED(data);
	}
}
