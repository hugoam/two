//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <geom/Forward.h>
#include <geom/Primitive.h>
#include <geom/Shape.h>

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

		span<Vertex> vertices() { return { &m_vertices[0], m_vertices.size() }; }
		span<uint32_t> indices() { return { &m_triangles[0].a, m_triangles.size() / 3 }; }

		virtual object<Shape> clone() const;
	};

	export_ struct refl_ MUD_GEOM_EXPORT MeshPacker
	{
		constr_ MeshPacker();

		uint32_t vertex_format() const;
		uint32_t vertex_count() const { return uint32_t(m_positions.size()); }
		uint32_t index_count() const { return uint32_t(m_indices.size()); }

		attr_ PrimitiveType m_primitive = PrimitiveType::Triangles;

		attr_ vector<vec3> m_positions;		// Position
		attr_ vector<vec3> m_normals;		// Normal
		attr_ vector<Colour> m_colours;		// Colour
		attr_ vector<vec4> m_tangents;		// Tangent
		attr_ vector<vec3> m_bitangents;	// Bitangent
		attr_ vector<vec2> m_uv0s;			// Texture Coordinates 0
		attr_ vector<vec2> m_uv1s;			// Texture Coordinates 1
		attr_ vector<ivec4> m_bones;		// Bones Indices
		attr_ vector<vec4> m_weights;		// Bones Weights

		attr_ vector<uint32_t> m_indices;

		meth_ void position(const vec3& p) { m_positions.push_back(p); }
		meth_ void normal(const vec3& n) { m_normals.push_back(n); }
		meth_ void colour(const Colour& c) { m_colours.push_back(c); }
		meth_ void tangent(const vec4& t) { m_tangents.push_back(t); }
		meth_ void bitangent(const vec3& b) { m_bitangents.push_back(b); }
		meth_ void uv0(const vec2& uv) { m_uv0s.push_back(uv); }
		meth_ void uv1(const vec2& uv) { m_uv1s.push_back(uv); }
		meth_ void bones(const ivec4& j) { m_bones.push_back(j); }
		meth_ void weights(const vec4& w) { m_weights.push_back(w); }

		meth_ void index(uint32_t i) { m_indices.push_back(i); }

		attr_ bool m_quantize = false;

		meth_ void clear();
		meth_ void pack(MeshAdapter& writer) const;
		meth_ void xpack(MeshAdapter& writer, const mat4& transform) const;

		void bake(bool normals, bool tangents);

		meth_ void generate_normals();
		meth_ void generate_tangents();
	};

	export_ MUD_GEOM_EXPORT void generate_mikkt_tangents(span<ShapeIndex> indices, span<ShapeVertex> vertices);
}
