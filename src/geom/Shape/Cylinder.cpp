//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <geom/Shape/Cylinder.h>
#include <geom/Shape/Circle.h>
#include <geom/Primitive.h>
#endif

namespace mud
{
	ShapeSize size_shape_lines(const ProcShape& shape, const Cylinder& cylinder)
	{
		ShapeSize circle_size = size_shape_lines(shape, Circle(cylinder.m_radius));
		return { circle_size.vertex_count * 2, circle_size.index_count * 3 };
	}
	
	void draw_shape_lines(const ProcShape& shape, const Cylinder& cylinder, MeshData& data)
	{
		vec3 offset = cylinder.m_axis == Axis::X ? X3 * cylinder.m_height / 2.f
					: cylinder.m_axis == Axis::Y ? Y3 * cylinder.m_height / 2.f
												 : Z3 * cylinder.m_height / 2.f;

		Circle circle = { cylinder.m_radius, cylinder.m_axis };
		uint16_t subdiv = circle_vertices(shape, cylinder.m_center + offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), true, data);
						  circle_vertices(shape, cylinder.m_center - offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, false), true, data);

		for (uint16_t i = 0; i < subdiv; i++)
		{
			data.line(i, i + 1 < subdiv ? i + 1 : 0);
			data.line(subdiv + i, i + 1 < subdiv ? subdiv + i + 1 : subdiv);
			data.line(i, subdiv + i);
		}
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Cylinder& cylinder)
	{
		ShapeSize circle_size = size_shape_triangles(shape, Circle(cylinder.m_radius));
		return { circle_size.vertex_count * 4, circle_size.index_count * 4 };
	}
	
	void draw_shape_triangles(const ProcShape& shape, const Cylinder& cylinder, MeshData& data)
	{
		vec3 offset = cylinder.m_axis == Axis::X ? X3 * cylinder.m_height / 2.f
					: cylinder.m_axis == Axis::Y ? Y3 * cylinder.m_height / 2.f
												: Z3 * cylinder.m_height / 2.f;

		Circle circle = { cylinder.m_radius, cylinder.m_axis };

		uint16_t subdiv = circle_vertices(shape, cylinder.m_center - offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, false), false, data);

		for(uint16_t i = 0; i < subdiv; i++)
			data.tri(i + 1 < subdiv ? i + 1 : 0, i, subdiv);

		data.next();

		circle_vertices(shape, cylinder.m_center + offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), false, data);

		for(uint16_t i = 0; i < subdiv; i++)
			data.tri(i, i + 1 < subdiv ? i + 1 : 0, subdiv);

		data.next();

		circle_vertices(shape, cylinder.m_center - offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, false), false, data, true);
		circle_vertices(shape, cylinder.m_center + offset, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), false, data, true);

		for(uint16_t i = 0; i < subdiv; i++)
			data.quad(i, i + 1 < subdiv ? i + 1 : 0, i + 1 < subdiv ? (subdiv + 1) + i + 1 : (subdiv + 1), (subdiv + 1) + i);
	}
}
