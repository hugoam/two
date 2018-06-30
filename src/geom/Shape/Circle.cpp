//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <math/Axes.h>
#include <geom/Shape/Circle.h>
#include <geom/Primitive.h>
#include <geom/Intersect.h>
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
			return point;
	}

	uint16_t circle_vertices(const ProcShape& shape, const vec3& position, vec2 radius, SignedAxis axis, bool lines, MeshData& data, bool outward_normals)
	{
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));

		float increment = 2 * c_pi / subdiv;
		float angle = 0.0f;

		for(uint16_t i = 0; i < subdiv; i++)
		{
			vec3 point = flip_point_axis({ radius.x * cos(angle), 0.f, radius.y * sin(angle) }, axis);
			data.position(position + point)
				.normal(outward_normals ? point : to_vec3(axis))
				.colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill);
			angle += increment;
		}

		if(!lines)
			data.position(position)
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

	void draw_shape_lines(const ProcShape& shape, const Circle& circle, MeshData& data)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), true, data);

		for (uint16_t i = 0; i < subdiv; i++)
			data.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Circle& circle)
	{
		UNUSED(circle);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv + 1, subdiv * 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Circle& circle, MeshData& data)
	{
		uint16_t subdiv = circle_vertices(shape, circle.m_center, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), false, data);

		for (uint16_t i = 0; i < subdiv; i++)
			data.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	
	ShapeSize size_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv, subdiv * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const Ellipsis& ellipsis, MeshData& data)
	{
		uint16_t subdiv = circle_vertices(shape, ellipsis.m_center, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), true, data);

		for (uint16_t i = 0; i < subdiv; i++)
			data.line(i, i + 1 < subdiv ? i + 1 : 0);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis)
	{
		UNUSED(ellipsis);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv + 1, subdiv * 3 };
	}

	void draw_shape_triangles(const ProcShape& shape, const Ellipsis& ellipsis, MeshData& data)
	{
		uint16_t subdiv = circle_vertices(shape, ellipsis.m_center, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), false, data);

		for (uint16_t i = 0; i < subdiv; i++)
			data.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const ArcLine& arc)
	{
		UNUSED(arc);
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));
		return { subdiv, subdiv * 2 };
	}

	void draw_shape_lines(const ProcShape& shape, const ArcLine& arc, MeshData& data)
	{
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));

		vec3 center = circumcenter(arc.m_start, arc.m_middle, arc.m_end);
		vec3 A = Zero3;
		vec3 D = arc.m_start - center;
		vec3 E = arc.m_end - center;

		vec3 N = cross(D, E);
		float theta = angle(D, E);
		float dtheta = theta / subdiv;
		vec3 B = normalize(D);

		for(size_t i = 1; i < subdiv; ++i)
		{
			vec3 p = rotate(B, float(i) * dtheta, N) + center;
			data.position(p)
				.colour(shape.m_symbol.m_outline);
		}

		for(uint16_t i = 0; i < subdiv; i++)
			data.line(i, i + 1 < subdiv ? i + 1 : 0);

		/*
		First translate your 3 points to the origin by subtracting the vector A from each point.
		This will give you D' = D - A, E' = E - A, and A' which is at the origin.
		The plane containing the points A', D', and E' is defined by its normal vector N.
		Vector N is simply D' x E' (i.e.the vector cross product of D' and E').
		You will also need to find the angle(theta) between D' and E'.
		Now select a point somewhere on D', call it B. It could be D' normalized.
		Points making up an arc from D' to E' are simply vector B rotated around N.
		To get an arc made up of 10 points, divide theta by 10.
		Rotate B around N by 10 * i, which i steps from 1 to 10.
		So you'll need a generic rotation routine which can rotate a vector around another vector.
		These can be found on the Internet if you don't have one already.
		All of the above will create an arc from D' to E'.
		Since you want an arc from D to E, you must translate the D'E' arc by A.


		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));

		vec2 center;
		float radius;
		float start_angle;
		float end_angle;

		float theta = (end_angle - start_angle) / float(subdiv - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open

		float tangential_factor = tanf(theta);
		float radial_factor = cosf(theta);

		float x = radius * cosf(start_angle);//we now start at the start angle
		float y = radius * sinf(start_angle);

		for(int ii = 0; ii < subdiv; ii++)
		{
			data.position({ x + center.x, 0.f, y + center.y });

			float tx = -y;
			float ty = x;

			x += tx * tangential_factor;
			y += ty * tangential_factor;

			x *= radial_factor;
			y *= radial_factor;
		}

		for(uint16_t i = 0; i < subdiv; i++)
			data.tri(i + 1 < subdiv ? i + 1 : 0, i, subdiv);
		*/
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const ArcLine& arc)
	{
		UNUSED(shape); UNUSED(arc);
		return { 0, 0 };
	}

	void draw_shape_triangles(const ProcShape& shape, const ArcLine& arc, MeshData& data)
	{
		UNUSED(shape); UNUSED(arc); UNUSED(data);
	}

	uint16_t torus_sides(uint lod) { return uint16_t(12 + 12 * lod); }
	uint16_t torus_rings(uint lod) { return uint16_t(12 + 12 * lod); }

	ShapeSize size_shape_lines(const ProcShape& shape, const Torus& torus)
	{
		UNUSED(shape); UNUSED(torus);
		return { 0, 0 };
	}

	void draw_shape_lines(const ProcShape& shape, const Torus& torus, MeshData& data)
	{
		UNUSED(shape); UNUSED(torus); UNUSED(data);
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Torus& torus)
	{
		UNUSED(torus);
		uint16_t sides_subdiv = torus_sides(uint(shape.m_symbol.m_detail)) + 1;
		uint16_t rings_subdiv = torus_rings(uint(shape.m_symbol.m_detail)) + 1;
		return { int(sides_subdiv * rings_subdiv), int((sides_subdiv-1) * (rings_subdiv-1) * 6) };
	}

	void draw_shape_triangles(const ProcShape& shape, const Torus& torus, MeshData& data)
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

				data.position(point)
					.colour(shape.m_symbol.m_fill);
			}

		for(uint16_t v = 0; v < sides; v++)
			for(uint16_t h = 0; h < rings; h++)
			{
				const uint16_t lt = h + v * sides_subdiv;
				const uint16_t rt = (h + 1) + v * sides_subdiv;

				const uint16_t lb = h + (v + 1) * sides_subdiv;
				const uint16_t rb = (h + 1) + (v + 1) * sides_subdiv;

				data.tri(lt, rt, lb);
				data.tri(rt, rb, lb);
			}
	}
}
