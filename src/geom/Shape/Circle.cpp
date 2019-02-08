//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <geom/Geom.hpp>
#include <math/Axes.h>
#include <geom/Shape/Circle.h>
#include <geom/Shape/Line.h>
#include <geom/Primitive.h>
#include <geom/Intersect.h>
#include <geom/Geom.h>
#endif

namespace mud
{
	uint16_t circle_subdiv(uint lod) { return uint16_t(6 + 12 * lod); }
	
	vec3 flip_point_axis(const vec3& point, SignedAxis axis)
	{
		if(axis == SignedAxis::PlusX || axis == SignedAxis::MinusX)
			return { point.y, point.x, point.z };
		else if(axis == SignedAxis::PlusZ || axis == SignedAxis::MinusZ)
			return { point.z, point.x, point.y };
		else
			return { point.z, point.y, point.x };
	}

	uint16_t circle_vertices(const ProcShape& shape, const vec3& position, vec2 radius, SignedAxis axis, bool lines, MeshAdapter& writer, bool outward_normals)
	{
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));

		float increment = 2 * c_pi / subdiv;
		float angle = 0.0f;

		for(uint16_t i = 0; i < subdiv; i++)
		{
			vec3 point = flip_point_axis({ radius.x * cos(angle), 0.f, radius.y * sin(angle) }, axis);
			writer.position(position + point)
				  .normal(outward_normals ? point : to_vec3(axis))
				  .colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill);
			angle += increment;
		}

		if(!lines)
			writer.position(position)
				  .normal(to_vec3(axis))
				  .colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill);

		return subdiv;
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv, subdiv * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), true, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv + 1, subdiv * 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	
	ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv, subdiv * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, ellipsis.m_center, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), true, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv + 1, subdiv * 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, ellipsis.m_center, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const ArcLine& arc)
	{
		UNUSED(arc);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv, (subdiv-1) * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));

		vec3 center = circumcenter(arc.m_start, arc.m_middle, arc.m_end);
		vec3 D = arc.m_start - center;
		vec3 E = arc.m_end - center;

		vec3 N = Plane(arc.m_start, arc.m_middle, arc.m_end).m_normal;
		float theta = angle(normalize(D), normalize(E));
		float dtheta = theta / subdiv;
		vec3 B = D;

		for(size_t i = 0; i < subdiv; ++i)
		{
			vec3 dir = rotate(B, float(i) * dtheta, N);
			vec3 p = dir + center;
			writer.position(arc.m_center + p)
				  .colour(shape.m_symbol.m_outline);
		}

		for(uint16_t i = 0; i < subdiv - 1; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const ArcLine& arc)
	{
		UNUSED(shape); UNUSED(arc);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer)
	{
		UNUSED(shape); UNUSED(arc); UNUSED(writer);
	}

	uint16_t torus_sides(uint lod) { return uint16_t(12 + 12 * lod); }
	uint16_t torus_rings(uint lod) { return uint16_t(12 + 12 * lod); }

	ShapeSize size_shape_lines(const ProcShape& shape, const Torus& torus)
	{
		UNUSED(shape); UNUSED(torus);
		return { 0, 0 };
	}

	void draw_shape_lines(const ProcShape& shape, const Torus& torus, MeshAdapter& writer)
	{
		UNUSED(shape); UNUSED(torus); UNUSED(writer);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Torus& torus)
	{
		UNUSED(torus);
		uint16_t sides_subdiv = torus_sides(uint(shape.m_symbol.m_detail)) + 1;
		uint16_t rings_subdiv = torus_rings(uint(shape.m_symbol.m_detail)) + 1;
		return { int(sides_subdiv * rings_subdiv), int((sides_subdiv-1) * (rings_subdiv-1) * 6) };
	}

	void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshAdapter& writer)
	{
		uint16_t sides = torus_sides(uint(shape.m_symbol.m_detail));
		uint16_t rings = torus_rings(uint(shape.m_symbol.m_detail));

		uint16_t sides_subdiv = sides + 1;
		uint16_t rings_subdiv = rings + 1;

		float vertical_delta = c_pi * 2.0f / float(rings);
		float horizontal_delta = c_pi * 2.0f / float(sides);

		for(uint16_t v = 0; v < sides_subdiv; v++)
			for(uint16_t h = 0; h < rings_subdiv; h++)
			{
				const float theta = vertical_delta * v;
				const float phi = horizontal_delta * h;

				const float x = cos(theta) * (torus.m_radius + torus.m_solid_radius * cos(phi));
				const float y = sin(theta) * (torus.m_radius + torus.m_solid_radius * cos(phi));
				const float z = torus.m_solid_radius * sin(phi);

				vec3 point = flip_point_axis({ x, z, y }, to_signed_axis(torus.m_axis, true));

				writer.position(point)
					  .colour(shape.m_symbol.m_fill);
			}

		for(uint16_t v = 0; v < sides; v++)
			for(uint16_t h = 0; h < rings; h++)
			{
				const uint16_t lt = h + v * sides_subdiv;
				const uint16_t rt = (h + 1) + v * sides_subdiv;

				const uint16_t lb = h + (v + 1) * sides_subdiv;
				const uint16_t rb = (h + 1) + (v + 1) * sides_subdiv;

				writer.tri(lt, rt, lb);
				writer.tri(rt, rb, lb);
			}
	}
}
