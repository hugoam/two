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
#include <geom/Primitive.hpp>
#include <geom/Intersect.h>
#include <geom/Geom.h>
#endif

#include <cassert>

namespace mud
{
	uint16_t circle_subdiv(uint lod) { return uint16_t(6 + 12 * lod); }

	uint16_t circle_subdiv(const Symbol& symbol)
	{
		return symbol.m_subdiv == uvec2(0U)
			? circle_subdiv(uint(symbol.m_detail))
			: symbol.m_subdiv.x;
	}

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
		uint16_t subdiv = circle_subdiv(shape.m_symbol);

		float increment = c_2pi / subdiv;
		float angle = 0.0f;

		for(uint16_t i = 0; i < subdiv; i++)
		{
			vec2 xy = vec2(radius.x * cos(angle), radius.y * sin(angle));
			vec3 point = flip_point_axis({ xy.x, 0.f, xy.y }, axis);
			vec2 uv = xy / 2.f + 0.5f;
			writer.position(position + point)
				  .normal(outward_normals ? point : to_vec3(axis))
				  .colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill)
				  .uv0(uv);
			angle += increment;
		}

		if(!lines)
			writer.position(position)
				  .normal(to_vec3(axis))
				  .colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill)
				  .uv0(vec2(0.5f));

		return subdiv;
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv, subdiv * 2U };
	}

	void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), true, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv + 1U, subdiv * 3U };
	}

	void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	
	ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv, subdiv * 2U };
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
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv + 1U, subdiv * 3U };
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
		uint16_t subdiv = circle_subdiv(shape.m_symbol);
		return { subdiv, (subdiv-1U) * 2U };
	}

	void draw_shape_lines(const ProcShape& shape, const ArcLine& arc, MeshAdapter& writer)
	{
		uint16_t subdiv = circle_subdiv(shape.m_symbol);

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

	uint16_t torus_sides(uint lod) { return uint16_t(4 + 2 * lod); }
	uint16_t torus_rings(uint lod) { return uint16_t(8 + 4 * lod); }

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
		return { uint32_t(sides_subdiv * rings_subdiv), uint32_t((sides_subdiv-1U) * (rings_subdiv-1U) * 6U) };
	}

	void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshAdapter& writer)
	{
		const SignedAxis axis = to_signed_axis(torus.m_axis, true);

		const uint16_t rings = torus_rings(uint(shape.m_symbol.m_detail));
		const uint16_t sides = torus_sides(uint(shape.m_symbol.m_detail));

		const uint16_t rings_subdiv = rings + 1;
		const uint16_t sides_subdiv = sides + 1;

		const float ring_step = c_2pi / float(rings);
		const float side_step = c_2pi / float(sides);

		for(uint16_t v = 0; v < sides_subdiv; v++)
			for(uint16_t h = 0; h < rings_subdiv; h++)
			{
				const float theta = ring_step * h;
				const float phi = side_step * v;

				const float x = cos(theta) * (torus.m_radius + torus.m_tube * cos(phi));
				const float y = torus.m_tube * sin(phi);
				const float z = sin(theta) * (torus.m_radius + torus.m_tube * cos(phi));

				const vec3 circle = flip_point_axis(vec3(cos(theta), 0.f, sin(theta)) * torus.m_radius, axis);
				const vec3 point = flip_point_axis(vec3(x, y, z), axis);

				const vec3 normal = normalize(point - circle);

				writer.position(point)
					  .normal(normal)
					  .colour(shape.m_symbol.m_fill)
					  .uv0(vec2(theta / c_2pi, phi / c_2pi));
			}

		for(uint16_t v = 0; v < sides; v++)
			for(uint16_t h = 0; h < rings; h++)
			{
				const uint16_t lt = h + v * rings_subdiv;
				const uint16_t rt = (h + 1) + v * rings_subdiv;

				const uint16_t lb = h + (v + 1) * rings_subdiv;
				const uint16_t rb = (h + 1) + (v + 1) * rings_subdiv;

				writer.tri(lt, rt, lb);
				writer.tri(rt, rb, lb);
			}
	}

	uint16_t torus_tube_subdiv(uint lod) { return uint16_t(64U); }
	uint16_t torus_radial_subdiv(uint lod) { return uint16_t(8U); }

	uint16_t torus_tube_subdiv(const Symbol& symbol)
	{
		return symbol.m_subdiv == uvec2(0U)
			? torus_tube_subdiv(uint(symbol.m_detail))
			: symbol.m_subdiv.x;
	}

	uint16_t torus_radial_subdiv(const Symbol& symbol)
	{
		return symbol.m_subdiv == uvec2(0U)
			? torus_radial_subdiv(uint(symbol.m_detail))
			: symbol.m_subdiv.y;
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const TorusKnot& torus)
	{
		UNUSED(torus);
		const uint16_t tubular = torus_tube_subdiv(shape.m_symbol) + 1;
		const uint16_t radial = torus_radial_subdiv(shape.m_symbol) + 1;
		return { uint32_t(tubular * radial), uint32_t((tubular-1U) * (radial-1U) * 6U) };
	}

	void draw_shape_triangles(const ProcShape& shape, const TorusKnot& torus, MeshAdapter& writer)
	{
		const float radius = torus.m_radius;
		const float tube = torus.m_tube;
		const uint16_t tubular = torus_tube_subdiv(shape.m_symbol);
		const uint16_t radial = torus_radial_subdiv(shape.m_symbol);
		const float p = torus.m_p;
		const float q = torus.m_q;

		auto knot_curve = [](float u, float p, float q, float radius) -> vec3
		{
			const float cu = cos(u);
			const float su = sin(u);
			const float quOverP = q / p * u;
			const float cs = cos(quOverP);

			const float x = radius * (2.f + cs) * 0.5f * cu;
			const float y = radius * (2.f + cs) * su * 0.5f;
			const float z = radius * sin(quOverP) * 0.5f;
			return vec3(x, y, z);
		};

		for(uint16_t i = 0; i <= tubular; ++i)
		{
			// the radian "u" is used to calculate the position on the torus curve of the current tubular segement
			const float u = float(i) / float(tubular) * p * c_2pi;

			// now we calculate two points. P1 is our current position on the curve, P2 is a little farther ahead.
			// these points are used to create a special "coordinate space", which is necessary to calculate the correct vertex positions
			const vec3 P1 = knot_curve(u, p, q, radius);
			const vec3 P2 = knot_curve(u + 0.01f, p, q, radius);

			// calculate orthonormal basis
			const vec3 oT = P2 - P1;
			const vec3 oN = P2 + P1;
			const vec3 B = normalize(cross(oT, oN));
			const vec3 N = normalize(cross(B, oT));

			for(uint16_t j = 0; j <= radial; ++j)
			{
				// now calculate the vertices. they are nothing more than an extrusion of the torus curve.
				// because we extrude a shape in the xy-plane, there is no need to calculate a z-value.
				const float v = float(j) / float(radial) * c_2pi;
				const float cx = -tube * cos(v);
				const float cy = tube * sin(v);

				// now calculate the final vertex position.
				// first we orient the extrusion with our basis vectos, then we add it to the current position on the curve
				const float x = P1.x + (cx * N.x + cy * B.x);
				const float y = P1.y + (cx * N.y + cy * B.y);
				const float z = P1.z + (cx * N.z + cy * B.z);
				
				const vec3 p = vec3(x, y, z);
				// normal (P1 is always the center/origin of the extrusion, thus we can use it to calculate the normal)
				const vec3 n = normalize(p - P1);
				const vec2 uv = vec2(float(i) / float(tubular), float(j) / float(radial));

				writer.position(p)
					  .normal(n)
					  .colour(shape.m_symbol.m_fill)
					  .uv0(uv);
			}

		}

		for(uint16_t j = 1; j <= tubular; j++)
		{
			for(uint16_t i = 1; i <= radial; i++)
			{
				const uint16_t a = (radial + 1) * (j - 1) + (i - 1);
				const uint16_t b = (radial + 1) * j + (i - 1);
				const uint16_t c = (radial + 1) * j + i;
				const uint16_t d = (radial + 1) * (j - 1) + i;

				writer.tri(a, b, d);
				writer.tri(b, c, d);
			}
		}
	}
}
