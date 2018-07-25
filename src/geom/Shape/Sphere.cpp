//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <geom/Shape/Sphere.h>
#include <geom/Shape/Icosphere.h>
#include <geom/Shapes.h>
#include <geom/Primitive.h>
#endif

#define ICO_SPHERE_LOD 2
//#define MUD_SPHERE_ICOSPHERE

namespace mud
{
	ShapeSize size_icosphere_lines(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		return { int(icosphere.m_vertices.size()), int(icosphere.m_lines.size()) * 2 };
	}

	void draw_icosphere_lines(const ProcShape& shape, const Sphere& sphere, MeshData& data)
	{
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		for(const vec3& vertex : icosphere.m_vertices)
			data.position(sphere.m_center + vertex * sphere.m_radius)
				.colour(shape.m_symbol.m_outline);

		for(const IcoSphere::Line& line : icosphere.m_lines)
			data.line(ShapeIndex(line[0]), ShapeIndex(line[1]));
	}

	ShapeSize size_icosphere_triangles(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		return { int(icosphere.m_vertices.size()), int(icosphere.m_faces.size()) * 3 };
	}

	void draw_icosphere_triangles(const ProcShape& shape, const Sphere& sphere, MeshData& data)
	{
		IcoSphere& icosphere = IcoSphere::s_levels[ICO_SPHERE_LOD];

		for(const vec3& vertex : icosphere.m_vertices)
			data.position(sphere.m_center + vertex * sphere.m_radius)
				.normal(normalize(vertex))
				.colour(shape.m_symbol.m_fill);

		for(IcoSphere::Face& face : icosphere.m_faces)
			data.tri(face[0], face[1], face[2]);
	}

	uint16_t sphere_rings(uint lod) { return uint16_t(6 + 6 * lod); }
	uint16_t sphere_sectors(uint lod) { return uint16_t(6 + 6 * lod); }

	void sphere_vertices(const vec3& center, float radius, uint16_t rings, uint16_t sectors, const Colour& colour, MeshData& data)
	{
		float const R = 1.f / (float)(rings - 1);
		float const S = 1.f / (float)(sectors - 1);
		float repeat = 1.f;

		for(uint16_t r = 0; r < rings; r++) for(uint16_t s = 0; s < sectors; s++)
		{
			float const x = cos(2 * c_pi * s * S) * sin(c_pi * r * R);
			float const y = sin(-c_pi / 2.f + c_pi * r * R);
			float const z = sin(2 * c_pi * s * S) * sin(c_pi * r * R);

			data.position(center + vec3(x, y, z) * radius)
				.normal({ x, y, z })
				.uv0({ s * S * repeat, r * R * repeat })
				.colour(colour);
		}
	}

	ShapeSize size_sphere_lines(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		uint16_t rings = sphere_rings(uint(shape.m_symbol.m_detail));
		uint16_t sectors = sphere_sectors(uint(shape.m_symbol.m_detail));

		return { int(rings * sectors), int((rings-1) * (sectors-1) * 4) };
	}

	void draw_sphere_lines(const ProcShape& shape, const Sphere& sphere, MeshData& data)
	{
		uint16_t rings = sphere_rings(uint(shape.m_symbol.m_detail));
		uint16_t sectors = sphere_sectors(uint(shape.m_symbol.m_detail));

		sphere_vertices(sphere.m_center, sphere.m_radius, rings, sectors, shape.m_symbol.m_outline, data);

		for(uint16_t r = 0; r < rings - 1; r++) for(uint16_t s = 0; s < sectors - 1; s++)
		{
			data.line(r * sectors + (s + 1),
					  r * sectors + s);
			data.line((r + 1) * sectors + (s + 1),
					  r * sectors + (s + 1));
		}
	}

	ShapeSize size_sphere_triangles(const ProcShape& shape, const Sphere& sphere)
	{
		UNUSED(shape); UNUSED(sphere);
		uint16_t rings = sphere_rings(uint(shape.m_symbol.m_detail));
		uint16_t sectors = sphere_sectors(uint(shape.m_symbol.m_detail));

		return { int(rings * sectors), int((rings-1) * (sectors-1) * 6) };
	}

	void draw_sphere_triangles(const ProcShape& shape, const Sphere& sphere, MeshData& data)
	{
		uint16_t rings = sphere_rings(uint(shape.m_symbol.m_detail));
		uint16_t sectors = sphere_sectors(uint(shape.m_symbol.m_detail));

		sphere_vertices(sphere.m_center, sphere.m_radius, rings, sectors, shape.m_symbol.m_fill, data);

		for(uint16_t r = 0; r < rings - 1; r++) for(uint16_t s = 0; s < sectors - 1; s++)
		{
			data.quad((r + 1) * sectors + s,
					  (r + 1) * sectors + (s + 1),
					  r * sectors + (s + 1),
					  r * sectors + s);
		}
	}

	ShapeSize size_shape_lines(const ProcShape& shape, const Sphere& sphere)
	{
#ifdef MUD_SPHERE_ICOSPHERE
		return size_icosphere_lines(shape, sphere);
#else
		return size_sphere_lines(shape, sphere);
#endif
	}

	void draw_shape_lines(const ProcShape& shape, const Sphere& sphere, MeshData& data)
	{
#ifdef MUD_SPHERE_ICOSPHERE
		return draw_icosphere_lines(shape, sphere, data);
#else
		return draw_sphere_lines(shape, sphere, data);
#endif
	}

	ShapeSize size_shape_triangles(const ProcShape& shape, const Sphere& sphere)
	{
#ifdef MUD_SPHERE_ICOSPHERE
		return size_icosphere_triangles(shape, sphere);
#else
		return size_sphere_triangles(shape, sphere);
#endif
	}

	void draw_shape_triangles(const ProcShape& shape, const Sphere& sphere, MeshData& data)
	{
#ifdef MUD_SPHERE_ICOSPHERE
		return draw_icosphere_triangles(shape, sphere, data);
#else
		return draw_sphere_triangles(shape, sphere, data);
#endif
	}
}
