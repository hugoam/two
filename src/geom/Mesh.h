//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>
#include <geom/Primitive.h>
#include <geom/Shape.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ class refl_ MUD_GEOM_EXPORT Geometry final : public Shape
	{
	public:
		constr_ Geometry();

		std::vector<Vertex> m_vertices;
		std::vector<Tri> m_triangles;

		vec3 m_bounds_min;
		vec3 m_bounds_max;

		void allocate(size_t vertex_count, size_t tri_count);

		array<Vertex> vertices() { return { &m_vertices[0], m_vertices.size() }; }
		array<uint32_t> indices() { return { &m_triangles[0].a, m_triangles.size() / 3 }; }

		virtual object_ptr<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT MeshPacker
	{
		constr_ MeshPacker();

		std::vector<ShapeVertex> m_vertices;
		std::vector<ShapeIndex> m_indices;

		PrimitiveType m_primitive = PrimitiveType::Triangles;

		std::vector<vec3> m_positions;		// Position
		std::vector<vec3> m_normals;		// Normal
		std::vector<vec4> m_tangents;		// Tangent
		std::vector<vec3> m_bitangents;		// Bitangent
		std::vector<vec2> m_uv0s;			// Texture Coordinates 0
		std::vector<vec2> m_uv1s;			// Texture Coordinates 1
		std::vector<Colour> m_colours;		// Colour
		std::vector<ivec4> m_bones;			// Bones Indices
		std::vector<vec4> m_weights;		// Bones Weights

		void bake(bool normals, bool tangents);

		void pack_vertices();
		void pack_vertices(const mat4& transform);
		void generate_normals();
		void generate_tangents();
		void generate_indices();

		inline ShapeVertex& vertex()
		{
			m_vertices.emplace_back();
			return m_vertices.back();
		}
	};

	export_ MUD_GEOM_EXPORT void generate_mikkt_tangents(array<ShapeIndex> indices, array<ShapeVertex> vertices);
}
