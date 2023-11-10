//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.geom;
#else
#include <math/Vec.hpp>
#include <geom/Shape/Cylinder.h>
#include <geom/Shape/Circle.h>
#include <geom/Primitive.hpp>
#endif

namespace two
{
	ShapeSize size_shape_lines(const ProcShape& shape, const Cylinder& cylinder)
	{
		ShapeSize circle_size = size_shape_lines(shape, Circle(cylinder.m_radius));
		return { circle_size.vertex_count * 2, circle_size.index_count * 3 };
	}
	
	void draw_shape_lines(const ProcShape& shape, const Cylinder& cylinder, MeshAdapter& writer)
	{
		vec3 offset = cylinder.m_axis == Axis::X ? x3 * cylinder.m_height / 2.f
					: cylinder.m_axis == Axis::Y ? y3 * cylinder.m_height / 2.f
												 : z3 * cylinder.m_height / 2.f;

		Circle circle = { cylinder.m_radius, cylinder.m_axis };
		uint16_t subdiv = circle_vertices(shape, cylinder.m_center + offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), true, writer);
						  circle_vertices(shape, cylinder.m_center - offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, false), true, writer);

		for(uint16_t i = 0; i < subdiv; i++)
		{
			writer.line(i, i + 1 < subdiv ? i + 1 : 0);
			writer.line(subdiv + i, i + 1 < subdiv ? subdiv + i + 1 : subdiv);
			writer.line(i, subdiv + i);
		}
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Cylinder& cylinder)
	{
		ShapeSize circle_size = size_shape_triangles(shape, Circle(cylinder.m_radius));
		return { circle_size.vertex_count * 4, circle_size.index_count * 4 };
	}
	
	void draw_shape_triangles(const ProcShape& shape, const Cylinder& cylinder, MeshAdapter& writer)
	{
		vec3 offset = cylinder.m_axis == Axis::X ? x3 * cylinder.m_height / 2.f
					: cylinder.m_axis == Axis::Y ? y3 * cylinder.m_height / 2.f
												: z3 * cylinder.m_height / 2.f;

		Circle circle = { cylinder.m_radius, cylinder.m_axis };

		uint16_t subdiv = circle_vertices(shape, cylinder.m_center - offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, false), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i + 1 < subdiv ? i + 1 : 0, i, subdiv);
		writer.next();

		circle_vertices(shape, cylinder.m_center + offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), false, writer);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.tri(i, i + 1 < subdiv ? i + 1 : 0, subdiv);
		writer.next();

		circle_vertices(shape, cylinder.m_center - offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, false), false, writer, true);
		circle_vertices(shape, cylinder.m_center + offset, vec2(circle.m_radius), to_signed_axis(circle.m_axis, true), false, writer, true);

		for(uint16_t i = 0; i < subdiv; i++)
			writer.quad(i, i + 1 < subdiv ? i + 1 : 0, i + 1 < subdiv ? (subdiv + 1) + i + 1 : (subdiv + 1), (subdiv + 1) + i);
	}
}
