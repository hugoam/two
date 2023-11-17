//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.geom;

#define ICO_SPHERE_LOD 2
//#define TWO_SPHERE_ICOSPHERE

namespace two
{
	ShapeSize size_icosphere_lines(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		return { uint32_t(icosphere.m_vertices.size()), uint32_t(icosphere.m_lines.size()) * 2U };
	}

	void draw_icosphere_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		for(const vec3& vertex : icosphere.m_vertices)
			writer.position(sphere.m_center + vertex * sphere.m_radius)
				  .colour(shape.m_symbol.m_outline);

		for(const IcoSphere::Line& line : icosphere.m_lines)
			writer.line(ShapeIndex(line[0]), ShapeIndex(line[1]));
	}

	ShapeSize size_icosphere_triangles(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		return { uint32_t(icosphere.m_vertices.size()), uint32_t(icosphere.m_faces.size()) * 3U };
	}

	void draw_icosphere_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		for(const vec3& vertex : icosphere.m_vertices)
			writer.position(sphere.m_center + vertex * sphere.m_radius)
				  .normal(normalize(vertex))
				  .colour(shape.m_symbol.m_fill);

		for(IcoSphere::Face& face : icosphere.m_faces)
			writer.tri(face[0], face[1], face[2]);
	}

	uvec2 sphere_subdiv(uint lod) { return uvec2(uint(6 + 6 * lod)); }

	uvec2 sphere_subdiv(const Symbol& symbol)
	{
		return symbol.m_subdiv != uvec2(0U)
			? symbol.m_subdiv + uvec2(1U)
			: sphere_subdiv(uint(symbol.m_detail));
	}

	void sphere_vertices(MeshAdapter& writer, const vec3& center, float radius, uvec2 subdiv, const Colour& colour,
						 float phi = 0.f, float arcphi = c_2pi, float theta = 0.f, float arctheta = c_pi)
	{
		float const R = 1.f / (float)(subdiv.x - 1);
		float const S = 1.f / (float)(subdiv.y - 1);
		float repeat = 1.f;

		for(uint16_t r = 0; r < subdiv.x; r++)
		for(uint16_t s = 0; s < subdiv.y; s++)
		{
			float const x = cos(phi + arcphi * s * S) * sin(theta + arctheta * r * R);
			float const y = sin(-c_pi2 + theta + arctheta * r * R);
			float const z = sin(phi + arcphi * s * S) * sin(theta + arctheta * r * R);

			writer.position(center + vec3(x, y, z) * radius)
				  .normal({ x, y, z })
				  .uv0({ s * S * repeat, r * R * repeat })
				  .colour(colour);
		}
	}

	ShapeSize size_sphere_lines(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		const uvec2 subdiv = sphere_subdiv(shape.m_symbol);

		return { subdiv.x * subdiv.y, uint32_t((subdiv.x-1U) * (subdiv.y-1U) * 4U) };
	}

	void draw_sphere_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		const uvec2 subdiv = sphere_subdiv(shape.m_symbol);

		sphere_vertices(writer, sphere.m_center, sphere.m_radius, subdiv, shape.m_symbol.m_outline, sphere.m_start, sphere.m_end);

		for(uint16_t r = 0; r < subdiv.x - 1; r++)
		for(uint16_t s = 0; s < subdiv.y - 1; s++)
		{
			writer.line(r * subdiv.y + (s + 1),
					    r * subdiv.y + s);
			writer.line((r + 1) * subdiv.y + (s + 1),
					    r * subdiv.y + (s + 1));
		}
	}

	ShapeSize size_sphere_triangles(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		const uvec2 subdiv = sphere_subdiv(shape.m_symbol);

		return { uint32_t(subdiv.x * subdiv.y), uint32_t((subdiv.x-1U) * (subdiv.y-1U) * 6U) };
	}

	void draw_sphere_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
		const uvec2 subdiv = sphere_subdiv(shape.m_symbol);

		sphere_vertices(writer, sphere.m_center, sphere.m_radius, subdiv, shape.m_symbol.m_outline, sphere.m_start, sphere.m_end);

		for(uint16_t r = 0; r < subdiv.x - 1; r++)
		for(uint16_t s = 0; s < subdiv.y - 1; s++)
		{
			writer.quad((r + 1) * subdiv.y + s,
					    (r + 1) * subdiv.y + (s + 1),
					    r * subdiv.y + (s + 1),
					    r * subdiv.y + s);
		}
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Sphere& sphere)
	{
#ifdef TWO_SPHERE_ICOSPHERE
		return size_icosphere_lines(shape, sphere);
#else
		return size_sphere_lines(shape, sphere);
#endif
	}

	void draw_shape_lines(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
#ifdef TWO_SPHERE_ICOSPHERE
		return draw_icosphere_lines(shape, sphere, writer);
#else
		return draw_sphere_lines(shape, sphere, writer);
#endif
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Sphere& sphere)
	{
#ifdef TWO_SPHERE_ICOSPHERE
		return size_icosphere_triangles(shape, sphere);
#else
		return size_sphere_triangles(shape, sphere);
#endif
	}

	void draw_shape_triangles(const ProcShape& shape, const Sphere& sphere, MeshAdapter& writer)
	{
#ifdef TWO_SPHERE_ICOSPHERE
		return draw_icosphere_triangles(shape, sphere, writer);
#else
		return draw_sphere_triangles(shape, sphere, writer);
#endif
	}
}
