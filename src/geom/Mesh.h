//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>
#include <geom/Primitive.h>
#include <geom/Shape.h>

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_GEOM_EXPORT Geometry final : public Shape
	{
	public:
		constr_ Geometry();

		vector<Vertex> m_vertices;
		vector<Tri> m_triangles;

		vec3 m_bounds_min;
		vec3 m_bounds_max;

		void allocate(size_t vertex_count, size_t tri_count);

		array<Vertex> vertices() { return { &m_vertices[0], m_vertices.size() }; }
		array<uint32_t> indices() { return { &m_triangles[0].a, m_triangles.size() / 3 }; }

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT MeshPacker
	{
		constr_ MeshPacker();

		uint32_t vertex_format();
		uint32_t vertex_count() { return uint32_t(m_positions.size()); }
		uint32_t index_count() { return m_indices.size() > 0 ? uint32_t(m_indices.size()) : uint32_t(m_positions.size()); }

		PrimitiveType m_primitive = PrimitiveType::Triangles;

		vector<vec3> m_positions;		// Position
		vector<vec3> m_normals;		// Normal
		vector<Colour> m_colours;		// Colour
		vector<vec4> m_tangents;		// Tangent
		vector<vec3> m_bitangents;		// Bitangent
		vector<vec2> m_uv0s;			// Texture Coordinates 0
		vector<vec2> m_uv1s;			// Texture Coordinates 1
		vector<ivec4> m_bones;			// Bones Indices
		vector<vec4> m_weights;		// Bones Weights

		vector<uint32_t> m_indices;

		bool m_quantize = false;

		void bake(bool normals, bool tangents);

		void pack_vertices(MeshAdapter& writer, const mat4& transform);
		void generate_normals();
		void generate_tangents();
	};

	export_ MUD_GEOM_EXPORT void generate_mikkt_tangents(array<ShapeIndex> indices, array<ShapeVertex> vertices);
}
