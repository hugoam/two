//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.geom;
#else
#include <math/Vec.hpp>
#include <geom/Shape/Quad.h>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Primitive.hpp>
#endif

//#define PK_GLITCH

namespace two
{
	static vec2 quadUVs[4] = { { 1.f, 1.f }, { 1.f, 0.f }, { 0.f, 0.f }, { 0.f, 1.f } };

	vec3 quad_normal(const vec3& a, const vec3& b, const vec3& c, const vec3& d)
	{
		UNUSED(d);
#ifndef PK_GLITCH
		vec3 x = b - a;
		vec3 y = c - a;
		return normalize(cross(x, y));
#else
		return 1.f;
#endif
	}

	void quad_vertices(const ProcShape& shape, const vec3& center, const vec3& a, const vec3& b, const vec3& c, const vec3& d, bool fill, MeshAdapter& writer)
	{
		auto vertex = [&](const vec3& p, const vec3& n, const vec2& uv)
		{
			writer.position(center + p)
				  .colour(fill ? shape.m_symbol.m_fill : shape.m_symbol.m_outline)
				  .normal(n)
				  .uv0(uv);
		};

		vec3 normal = quad_normal(a, b, c, d);
		vertex(a, normal, quadUVs[0]);
		vertex(b, normal, quadUVs[1]);
		vertex(c, normal, quadUVs[2]);
		vertex(d, normal, quadUVs[3]);
	}

	void quad_vertices(const ProcShape& shape, const vec3& center, span<vec3> vertices, bool fill, MeshAdapter& writer)
	{
		quad_vertices(shape, center, vertices[0], vertices[1], vertices[2], vertices[3], fill, writer);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Quad& quad)
	{
		UNUSED(shape); UNUSED(quad);
		return { 4, 8 };
	}

	void draw_shape_lines(const ProcShape& shape, const Quad& quad, MeshAdapter& writer)
	{
		quad_vertices(shape, quad.m_center, { const_cast<vec3*>(quad.m_vertices), 4 }, false, writer);
		for(uint16_t i = 0; i < 4; i++)
			writer.line(i, (i + 1) % 4);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Quad& quad)
	{
		UNUSED(shape); UNUSED(quad);
		return { 4, 6 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Quad& quad, MeshAdapter& writer)
	{
		quad_vertices(shape, quad.m_center, { const_cast<vec3*>(quad.m_vertices), 4 }, true, writer);
		writer.quad(0, 1, 2, 3);
	}

	uint32_t num_rects(const Grid3& grid) { return (grid.m_size.x-1) * (grid.m_size.y-1); }

	ShapeSize size_shape_lines(const ProcShape& shape, const Grid3& grid)
	{
		UNUSED(shape);
		uint32_t rects = num_rects(grid);
		return { rects * 4U, rects * 8U };
	}

	void draw_shape_lines(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer)
	{
		// @todo: could draw it like a grid instead of per quads...
		span2d<vec3> points = { const_cast<vec3*>(grid.m_points.data()), grid.m_size.x, grid.m_size.y };

		uint32_t offset = 0;

		for(uint32_t x = 0; x < grid.m_size.x - 1; ++x)
			for(uint32_t y = 0; y < grid.m_size.y - 1; ++y)
			{
				quad_vertices(shape, grid.m_center, points.at(x, y), points.at(x + 1, y), points.at(x + 1, y + 1), points.at(x, y + 1), true, writer);
				for(uint16_t i = 0; i < 4; i++)
					writer.line(offset + i, offset + (i + 1) % 4);
			}
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Grid3& grid)
	{
		UNUSED(shape);
		uint32_t rects = num_rects(grid);
		return { rects * 4U, rects * 6U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Grid3& grid, MeshAdapter& writer)
	{
		span2d<vec3> points = { const_cast<vec3*>(grid.m_points.data()), grid.m_size.x, grid.m_size.y };

		uint32_t offset = 0;

		for(uint32_t x = 0; x < grid.m_size.x-1; ++x)
			for(uint32_t y = 0; y < grid.m_size.y-1; ++y)
			{
				quad_vertices(shape, grid.m_center, points.at(x, y), points.at(x+1, y), points.at(x+1, y+1), points.at(x, y+1), true, writer);
				writer.quad(offset + 0, offset + 1, offset + 2, offset + 3);
				offset += 4;
			}
	}
}
