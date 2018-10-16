//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <map>
#include <unordered_map>
#include <cstdio>
#endif

#ifdef MUD_MODULES
module mud.geom;
#else
#include <infra/Vector.h>
#include <math/VecOps.h>
#include <geom/Mesh.h>
#include <geom/Geom.h>
#endif

#include <mikktspace.h>

namespace glm
{
	inline bool operator<(const vec3& lhs, const vec3& rhs) { return all(lessThan(lhs, rhs)); }
}

namespace mud
{
	uint32_t joints(const ivec4& j)
	{
		return uint32_t(j[0]) | uint32_t(j[1]) << 8 | uint32_t(j[2]) << 16 | uint32_t(j[3]) << 24;
	}

	inline void vec_to_array(const vec3& in, float out[]) { out[0] = in.x; out[1] = in.y; out[2] = in.z; }
	inline void vec_to_array(const vec2& in, float out[]) { out[0] = in.x; out[1] = in.y; }

	Geometry::Geometry()
		: Shape(type<Geometry>())
		, m_vertices()
		, m_triangles()
	{}

	void Geometry::allocate(size_t vertex_count, size_t tri_count)
	{
		m_vertices.resize(vertex_count);
		m_triangles.resize(tri_count);
	}

	object_ptr<Shape> Geometry::clone() const { return make_object<Geometry>(*this); }

	MeshPacker::MeshPacker()
	{}

	uint32_t MeshPacker::vertex_format()
	{
		uint32_t format = VertexAttribute::Position;
		if(!m_normals.empty())	format |= VertexAttribute::Normal;
		if(!m_tangents.empty())	format |= VertexAttribute::Tangent;
		if(!m_uv0s.empty())		format |= VertexAttribute::TexCoord0;
		if(!m_uv1s.empty())		format |= VertexAttribute::TexCoord1;
		if(!m_bones.empty())	format |= VertexAttribute::Joints;
		if(!m_weights.empty())	format |= VertexAttribute::Weights;
		return format;
	}

	void MeshPacker::bake(bool normals, bool tangents)
	{
		UNUSED(normals);

		//if(normals)
		//	this->generate_normals();

		if(tangents)
			this->generate_tangents();
	}
	
	void MeshPacker::pack_vertices(MeshData& data, const mat4& transform)
	{
		for(uint32_t i = 0; i < uint32_t(m_positions.size()); ++i)
		{
			data.position(vec3(transform * vec4(m_positions[i], 1.f)));
			if(!m_normals.empty())	data.normal(normalize(vec3(transform * vec4(m_normals[i], 0.f))));
			if(!m_tangents.empty()) data.tangent(vec4(vec3(transform * vec4(vec3(m_tangents[i]), 0.f)), m_tangents[i].w));
			if(!m_uv0s.empty())     data.uv0(m_uv0s[i]);
			if(!m_uv1s.empty())		data.uv1(m_uv1s[i]);
			if(!m_bones.empty())	data.joints(joints(m_bones[i]));
			if(!m_weights.empty())	data.weights(m_weights[i]);

			if(m_indices.empty())
				data.index(i);
		}

		for(uint32_t i = 0; i < m_indices.size(); ++i)
		{
			data.index(m_indices[i]);
		}
	}

	void MeshPacker::generate_normals()
	{
		std::map<vec3, vec3> smooth_normals;
		//std::unordered_map<vec3, vec3> smooth_normals;

		std::vector<int> smooth_groups;

		for(int smooth_group : smooth_groups)
		{
			for(size_t i = 0; i < m_positions.size(); i += 3)
			{
				int vert_smooth_group = 0;
				if(vert_smooth_group != smooth_group)
					continue;

				vec3 normal = Plane(m_positions[i + 0], m_positions[i + 1], m_positions[i + 2]).m_normal;

				if(smooth_group == 0)
				{
					m_normals[i + 0] = normal;
					m_normals[i + 1] = normal;
					m_normals[i + 2] = normal;
				}
				else
				{
					smooth_normals[m_positions[i + 0]] += normal;
					smooth_normals[m_positions[i + 1]] += normal;
					smooth_normals[m_positions[i + 2]] += normal;
				}
			}
		
			if(smooth_group == 0)
				continue;

			for(auto& kv : smooth_normals)
				kv.second = normalize(kv.second);

			for(size_t i = 0; i < m_positions.size(); i++)
			{
				m_normals[i] = smooth_normals[m_positions[i]];
			}

			smooth_normals.clear();
		}
	}

	struct ShapeData
	{
		array<ShapeIndex> m_indices;
		array<ShapeVertex> m_vertices;
	};

	inline ShapeData& mikkt_mesh(const SMikkTSpaceContext* context) { return *static_cast<ShapeData*>(context->m_pUserData); }
	inline ShapeVertex& mikkt_vertex(const SMikkTSpaceContext* context, int face, int vert)
	{
		ShapeData& shape_data = *static_cast<ShapeData*>(context->m_pUserData);
		ShapeIndex index = shape_data.m_indices[face * 3 + vert];
		return shape_data.m_vertices[index];
	}

	void generate_mikkt_tangents(array<ShapeIndex> indices, array<ShapeVertex> vertices)
	{
		ShapeData shape_data = { indices, vertices };
		std::vector<ShapeVertex> verts = to_vector(vertices);

		using Context = SMikkTSpaceContext;

		SMikkTSpaceInterface intf = {};
		intf.m_getNumFaces = [](const Context* c) -> int { return int(mikkt_mesh(c).m_indices.m_count) / 3; };
		intf.m_getNumVerticesOfFace = [](const Context* c, const int face) -> int { UNUSED(c); UNUSED(face); return 3; };
		intf.m_getPosition = [](const Context* c, float pos[], const int face, const int vert) { vec_to_array(mikkt_vertex(c, face, vert).m_position, pos); };
		intf.m_getNormal = [](const Context* c, float norm[], const int face, const int vert) { vec_to_array(mikkt_vertex(c, face, vert).m_normal, norm); };
		intf.m_getTexCoord = [](const Context* c, float uv[], const int face, const int vert) { vec_to_array(mikkt_vertex(c, face, vert).m_uv0, uv); };
		
		intf.m_setTSpaceBasic = [](const SMikkTSpaceContext * c, const float tangent[], const float sign, const int face, const int vert)
		{
			ShapeVertex& vertex = mikkt_vertex(c, face, vert);
			vertex.m_tangent = { tangent[0], tangent[1], tangent[2], sign };
		};

		SMikkTSpaceContext context;
		context.m_pInterface = &intf;
		context.m_pUserData = &shape_data;

		bool success = genTangSpaceDefault(&context) != 0;
		if(!success)
			printf("WARNING: Couldn't generate mikktspace tangents\n");
	}

	inline MeshPacker& mikkt_packer(const SMikkTSpaceContext* context) { return *static_cast<MeshPacker*>(context->m_pUserData); }
	inline size_t mikkt_index(const SMikkTSpaceContext* context, int face, int vert)
	{
		return mikkt_packer(context).m_indices.size() > 0 ? mikkt_packer(context).m_indices[face * 3 + vert]
														  : face * 3 + vert;
	}

	void MeshPacker::generate_tangents()
	{
		using Context = SMikkTSpaceContext;

		m_tangents.resize(m_positions.size());

		SMikkTSpaceInterface intf = {};
		intf.m_getNumFaces = [](const Context* c) -> int { return int(mikkt_packer(c).index_count()) / 3; };
		intf.m_getNumVerticesOfFace = [](const Context* c, const int face) -> int { UNUSED(c); UNUSED(face); return 3; };
		intf.m_getPosition = [](const Context* c, float pos[], const int face, const int vert) { vec_to_array(mikkt_packer(c).m_positions[mikkt_index(c, face, vert)], pos); };
		intf.m_getNormal = [](const Context* c, float norm[], const int face, const int vert) { vec_to_array(mikkt_packer(c).m_normals[mikkt_index(c, face, vert)], norm); };
		intf.m_getTexCoord = [](const Context* c, float uv[], const int face, const int vert) { vec_to_array(mikkt_packer(c).m_uv0s[mikkt_index(c, face, vert)], uv); };
		
		intf.m_setTSpaceBasic = [](const SMikkTSpaceContext * c, const float tangent[], const float sign, const int face, const int vert)
		{
			mikkt_packer(c).m_tangents[mikkt_index(c, face, vert)] = { tangent[0], tangent[1], tangent[2], sign };
		};

		SMikkTSpaceContext context;
		context.m_pInterface = &intf;
		context.m_pUserData = this;

		bool success = genTangSpaceDefault(&context) != 0;
		if(!success)
			printf("WARNING: Couldn't generate mikktspace tangents\n");
	}
}
