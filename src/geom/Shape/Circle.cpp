//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <geom/Shape/Circle.h>
#include <math/Axes.h>
#include <geom/Primitive.h>

namespace mud
{
	uint16_t circle_subdiv(uint lod) { return uint16_t(6 + 12 * lod); }
	
	vec3 circle_point(vec2 radius, SignedAxis axis, float angle)
	{
		vec3 position(radius.x * cos(angle), 0.f, radius.y * sin(angle));

		if(axis == SignedAxis::PlusX || axis == SignedAxis::MinusX)
			position = { position.y, position.x, position.z };
		else if(axis == SignedAxis::PlusZ || axis == SignedAxis::MinusZ)
			position = { position.z, position.x, position.y };

		return position;
	}

	uint16_t circle_vertices(const ProcShape& shape, const vec3& position, vec2 radius, SignedAxis axis, bool lines, MeshData& data, bool outward_normals)
	{
		uint16_t subdiv = circle_subdiv(uint(shape.m_symbol.m_detail));

		float increment = 2 * float(M_PI) / subdiv;
		float angle = 0.0f;

		for(uint16_t i = 0; i < subdiv; i++)
		{
			vec3 point = circle_point(radius, axis, angle);
			data.position(position + point)
				.normal(outward_normals ? point : to_vec3(axis))
				.colour(lines ? shape.m_symbol.m_outline : shape.m_symbol.m_fill);
			angle += increment;
		}

		if(!lines)
			data.position(position)
				.normal(to_vec3(axis))
				.colour(shape.m_symbol.m_outline);

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
		uint16_t subdiv = circle_vertices(shape, shape.m_position, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), true, data);

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
		uint16_t subdiv = circle_vertices(shape, shape.m_position, vec2{ circle.m_radius }, to_signed_axis(circle.m_axis, true), false, data);

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
		uint16_t subdiv = circle_vertices(shape, shape.m_position, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), true, data);

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
		uint16_t subdiv = circle_vertices(shape, shape.m_position, ellipsis.m_radius, to_signed_axis(ellipsis.m_axis, true), false, data);

		for (uint16_t i = 0; i < subdiv; i++)
			data.tri(i + 1 < subdiv ? i + 1 : 0, i,  subdiv);
	}
}
