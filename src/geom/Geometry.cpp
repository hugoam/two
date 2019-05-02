//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef TWO_CPP_20
#include <cstdio>
#endif

#ifdef TWO_MODULES
module two.geom;
#else
#include <stl/unordered_map.h>
#include <stl/map.h>
#include <stl/algorithm.h>
#include <infra/Vector.h>
#include <type/Cls.h>
#include <math/Vec.hpp>
#include <geom/Geometry.h>
#include <geom/Geom.h>
#include <geom/Primitive.hpp>
#endif

#include <cassert>

#include <mikktspace.h>

namespace two
{
	inline bool operator<(const vec3& lhs, const vec3& rhs) { return all(less(lhs, rhs)); }
}

namespace two
{
	uint32_t joints(const ivec4& j)
	{
		return uint32_t(j[0]) | uint32_t(j[1]) << 8 | uint32_t(j[2]) << 16 | uint32_t(j[3]) << 24;
	}

	inline void vec_to_array(const vec3& in, float out[]) { out[0] = in.x; out[1] = in.y; out[2] = in.z; }
	inline void vec_to_array(const vec2& in, float out[]) { out[0] = in.x; out[1] = in.y; }

	inline int quantize_unorm(float v, int N)
	{
		const float scale = float((1 << N) - 1);

		v = (v >= 0) ? v : 0;
		v = (v <= 1) ? v : 1;

		return int(v * scale + 0.5f);
	}

	inline int quantize_snorm(float v, int N)
	{
		const float scale = float((1 << (N - 1)) - 1);

		float round = (v >= 0 ? 0.5f : -0.5f);

		v = (v >= -1) ? v : -1;
		v = (v <= +1) ? v : +1;

		return int(v * scale + round);
	}

	inline unsigned short quantize_half(float v)
	{
		union { float f; unsigned int ui; } u = { v };
		unsigned int ui = u.ui;

		int s = (ui >> 16) & 0x8000;
		int em = ui & 0x7fffffff;

		/* bias exponent and round to nearest; 112 is relative exponent bias (127-15) */
		int h = (em - (112 << 23) + (1 << 12)) >> 13;

		/* underflow: flush to zero; 113 encodes exponent -14 */
		h = (em < (113 << 23)) ? 0 : h;

		/* overflow: infinity; 143 encodes exponent 16 */
		h = (em >= (143 << 23)) ? 0x7c00 : h;

		/* NaN; note that we convert all types of NaN to qNaN */
		h = (em > (255 << 23)) ? 0x7e00 : h;

		return (unsigned short)(s | h);
	}

	MeshAdapter::MeshAdapter(uint32_t vertex_count, MeshPacker& geom)
		: m_vertex_format(geom.vertex_format()), m_index32(true)
		, m_vertex_stride(vertex_size(geom.vertex_format()))
		, m_vertex_count(vertex_count)
	{
		uint32_t vertex_format = geom.vertex_format();

		m_start.m_position.init(vertex_format, VertexAttribute::Position, geom.m_positions.data());
		m_start.m_normal.init(vertex_format, VertexAttribute::Normal, geom.m_normals.data());
		m_start.m_colour.init(vertex_format, VertexAttribute::Colour, geom.m_ucolours.data());
		m_start.m_tangent.init(vertex_format, VertexAttribute::Tangent, geom.m_tangents.data());
		m_start.m_uv0.init(vertex_format, VertexAttribute::TexCoord0, geom.m_uv0s.data());
		m_start.m_uv1.init(vertex_format, VertexAttribute::TexCoord1, geom.m_uv1s.data());

		m_start.m_index32.init(geom.m_indices.data());

		m_cursor = m_start;
	}

	void MeshAdapter::rewind() { m_cursor = m_start; m_vertex = 0; m_offset = 0; }
	void MeshAdapter::next() { m_offset = m_vertex; }

	MeshAdapter& MeshAdapter::position(const vec3& p) { m_aabb.add(p); m_cursor.m_position.write(p); ++m_vertex; return *this; }
	MeshAdapter& MeshAdapter::position4(const vec4& p) { m_aabb.add(vec3(p)); m_cursor.m_position4.write(p); ++m_vertex; return *this; }
	MeshAdapter& MeshAdapter::normal(const vec3& n) { if(m_cursor.m_normal) { m_cursor.m_normal.write(n); } return *this; }
	MeshAdapter& MeshAdapter::colour(const Colour& c) { if(m_cursor.m_colour) { m_cursor.m_colour.write(to_abgr(c)); } return *this; }
	MeshAdapter& MeshAdapter::colour(const vec3& c) { if(m_cursor.m_colour) { m_cursor.m_colour.write(to_abgr(c.r, c.g, c.b)); } return *this; }
	MeshAdapter& MeshAdapter::tangent(const vec4& t) { if(m_cursor.m_tangent) { m_cursor.m_tangent.write(t); } return *this; }
	MeshAdapter& MeshAdapter::bitangent(const vec3& b) { if(m_cursor.m_bitangent) { m_cursor.m_bitangent.write(b); } return *this; }
	MeshAdapter& MeshAdapter::uv0(const vec2& uv) { if(m_cursor.m_uv0) { m_uv0_rect.add(uv); m_cursor.m_uv0.write(uv); } return *this; }
	MeshAdapter& MeshAdapter::uv1(const vec2& uv) { if(m_cursor.m_uv1) { m_uv1_rect.add(uv); m_cursor.m_uv1.write(uv); } return *this; }
	MeshAdapter& MeshAdapter::joints(const uint32_t& j) { if(m_cursor.m_joints) { m_cursor.m_joints.write(j); } return *this; }
	MeshAdapter& MeshAdapter::weights(const vec4& w) { if(m_cursor.m_weights) { m_cursor.m_weights.write(w); } return *this; }

	void MeshAdapter::copy(MeshAdapter& dest)
	{
		MeshAdapter reader = this->read();

		for(size_t i = 0; i < reader.m_vertex_count; ++i)
		{
			dest.position(reader.position());
			dest.normal(reader.normal());
			dest.colour(reader.colour());
			dest.tangent(reader.tangent());
			dest.uv0(reader.uv0());
			dest.uv1(reader.uv1());
			dest.joints(reader.joints());
			dest.weights(reader.weights());
		}

		for(size_t i = 0; i < reader.m_index_count; ++i)
		{
			uint32_t index = reader.m_index32 ? reader.index32() : reader.index();
			assert(index <= dest.m_vertex_count);
			dest.index(index);
		}
	}

	void MeshAdapter::xcopy(MeshAdapter& dest, const mat4& transform)
	{
		MeshAdapter reader = this->read();

		for(size_t i = 0; i < reader.m_vertex_count; ++i)
		{
			const vec3 p = mulp(transform, reader.position());
			//printf("xcopy pos %.2f, %.2f, %.2f\n", p.x, p.y, p.z);
			dest.position(p);
			dest.normal(muln(transform, reader.normal()));
			dest.colour(reader.colour());
			dest.tangent(mult(transform, reader.tangent()));
			dest.uv0(reader.uv0());
			dest.uv1(reader.uv1());
			dest.joints(reader.joints());
			dest.weights(reader.weights());
		}

		for(size_t i = 0; i < reader.m_index_count; ++i)
		{
			uint32_t index = reader.m_index32 ? reader.index32() : reader.index();
			assert(index <= dest.m_vertex_count);
			dest.index(index);
		}
	}

	MeshAdapter& MeshAdapter::qposition(const vec3& p)
	{
		half3 qposition = half3(quantize_half(p.x), quantize_half(p.y), quantize_half(p.z));
		m_cursor.m_qposition.write(qposition);
		++m_vertex;
		return *this;
	}

	MeshAdapter& MeshAdapter::qnormal(const vec3& n)
	{
		if(m_cursor.m_qnormal)
		{
			uint32_t qnormal;
			uint8_t* packed = (uint8_t*)&qnormal;
			*packed++ = uint8_t(n.x * 127.0f + 128.0f); // quantize_snorm(n.x, 8)
			*packed++ = uint8_t(n.y * 127.0f + 128.0f);
			*packed++ = uint8_t(n.z * 127.0f + 128.0f);

			m_cursor.m_qnormal.write(qnormal);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::qtangent(const vec4& t)
	{
		if(m_cursor.m_qtangent)
		{
			uint32_t qtangent;
			uint8_t* packed = (uint8_t*)&qtangent;
			*packed++ = uint8_t(t.x * 127.0f + 128.0f);  // quantize_snorm(t.x, 8)
			*packed++ = uint8_t(t.y * 127.0f + 128.0f);
			*packed++ = uint8_t(t.z * 127.0f + 128.0f);
			*packed++ = uint8_t(t.w * 127.0f + 128.0f);

			m_cursor.m_qtangent.write(qtangent);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::quv0(const vec2& uv)
	{
		if(m_cursor.m_quv0)
		{
			m_uv0_rect.add(uv);
			half2 quv = half2(quantize_half(uv.x), quantize_half(uv.y));
			m_cursor.m_quv0.write(quv);
		}
		return *this;
	}

	MeshAdapter& MeshAdapter::quv1(const vec2& uv)
	{
		if(m_cursor.m_quv1)
		{
			m_uv1_rect.add(uv);
			half2 quv = half2(quantize_half(uv.x), quantize_half(uv.y));
			m_cursor.m_quv1.write(quv);
		}
		return *this;
	}

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

	object<Shape> Geometry::clone() const { return oconstruct<Geometry>(*this); }

	MeshPacker::MeshPacker()
	{}

	uint32_t MeshPacker::vertex_format() const
	{
		//uint32_t format = m_quantize ? VertexAttribute::QPosition : VertexAttribute::Position;
		uint32_t format = VertexAttribute::Position;
		if(!m_normals.empty())	format |= (m_quantize ? VertexAttribute::QNormal : VertexAttribute::Normal);
		if(!m_colours.empty())	format |= VertexAttribute::Colour;
		if(!m_tangents.empty())	format |= (m_quantize ? VertexAttribute::QTangent : VertexAttribute::Tangent);
		if(!m_uv0s.empty())		format |= (m_quantize ? VertexAttribute::QTexCoord0 : VertexAttribute::TexCoord0);
		if(!m_uv1s.empty())		format |= (m_quantize ? VertexAttribute::QTexCoord1 : VertexAttribute::TexCoord1);
		if(!m_bones.empty())	format |= VertexAttribute::Joints;
		if(!m_weights.empty())	format |= VertexAttribute::Weights;
		return format;
	}

	void MeshPacker::bake(bool normals, bool tangents)
	{
		if(normals && m_normals.empty()) this->gen_normals();
		if(tangents && m_tangents.empty()) this->gen_tangents();
	}

	void MeshPacker::resize(uint32_t vertex_count, uint32_t index_count, uint32_t vertex_format)
	{
		m_positions.resize(vertex_count);
		if((vertex_format & VertexAttribute::Normal)    != 0) m_normals.resize(vertex_count);
		//if((vertex_format & VertexAttribute::Colour)    != 0) m_colours.resize(vertex_count);
		// for now this is used exclusively for packing using MeshAdapter, so this doesn't break... yet
		if((vertex_format & VertexAttribute::Colour)    != 0) m_ucolours.resize(vertex_count);
		if((vertex_format & VertexAttribute::Tangent)   != 0) m_tangents.resize(vertex_count);
		if((vertex_format & VertexAttribute::TexCoord0) != 0) m_uv0s.resize(vertex_count);
		if((vertex_format & VertexAttribute::TexCoord1) != 0) m_uv1s.resize(vertex_count);
		if((vertex_format & VertexAttribute::Joints)    != 0) m_bones.resize(vertex_count);
		if((vertex_format & VertexAttribute::Weights)   != 0) m_weights.resize(vertex_count);

		m_indices.resize(index_count);
	}

	void MeshPacker::clear()
	{
		m_positions.clear();
		m_normals.clear();
		m_colours.clear();
		m_tangents.clear();
		m_uv0s.clear();
		m_uv1s.clear();
		m_bones.clear();
		m_weights.clear();

		m_indices.clear();
	}

	void MeshPacker::pack(MeshAdapter& writer) const
	{
		for(const vec3&   p  : m_positions)	 writer.position(p);
		for(const vec3&   n  : m_normals)	 m_quantize ? writer.qnormal(n) : writer.normal(n);
		for(const Colour& c  : m_colours)	 writer.colour(c);
		for(const vec4&   t  : m_tangents)	 m_quantize ? writer.qtangent(t) : writer.tangent(t);
		for(const vec2&   uv : m_uv0s)		 m_quantize ? writer.quv0(uv) : writer.uv0(uv);
		for(const vec2&   uv : m_uv1s)		 m_quantize ? writer.quv1(uv) : writer.uv1(uv);
		for(const ivec4&  b  : m_bones)		 writer.joints(joints(b));
		for(const vec4&   w  : m_weights)	 writer.weights(w);

		for(uint32_t i : m_indices) writer.index(i);
	}

	void MeshPacker::xpack(MeshAdapter& writer, const mat4& transform) const
	{
		for(const vec3&   p  : m_positions)	 writer.position(mulp(transform, p));
		for(const vec3&   n  : m_normals)	 m_quantize ? writer.qnormal(muln(transform, n)) : writer.normal(muln(transform, n));
		for(const Colour& c  : m_colours)	 writer.colour(c);
		for(const vec4&   t  : m_tangents)	 m_quantize ? writer.qtangent(mult(transform, t)) : writer.tangent(mult(transform, t));
		for(const vec2&   uv : m_uv0s)		 m_quantize ? writer.quv0(uv) : writer.uv0(uv);
		for(const vec2&   uv : m_uv1s)		 m_quantize ? writer.quv1(uv) : writer.uv1(uv);
		for(const ivec4&  b  : m_bones)		 writer.joints(joints(b));
		for(const vec4&   w  : m_weights)	 writer.weights(w);

		for(uint32_t i : m_indices) writer.index(i);
	}

	void MeshPacker::unpack(const MeshAdapter& source, const mat4& transform)
	{
		MeshAdapter reader = source.read();

		for(size_t i = 0; i < reader.m_vertex_count; ++i)
		{
			m_positions.push_back(mulp(transform, reader.position()));
			if((reader.m_vertex_format & VertexAttribute::Normal) != 0)
				m_normals.push_back(muln(transform, reader.normal()));
			if((reader.m_vertex_format & VertexAttribute::Colour) != 0)
				m_colours.push_back(reader.colour());
			if((reader.m_vertex_format & VertexAttribute::Tangent) != 0)
				m_tangents.push_back(mult(transform, reader.tangent()));
			if((reader.m_vertex_format & VertexAttribute::TexCoord0) != 0)
				m_uv0s.push_back(reader.uv0());
			if((reader.m_vertex_format & VertexAttribute::TexCoord1) != 0)
				m_uv1s.push_back(reader.uv1());
			//packer.m_bones.push_back(source.bones());
			//packer.m_weights.push_back(source.weights());
		}

		for(size_t i = 0; i < reader.m_index_count; ++i)
		{
			m_indices.push_back(reader.m_index32 ? reader.index32() : reader.index());
		}
	}

	void MeshPacker::gen_flat_normals()
	{
		const vector<vec3>& positions = m_positions;

		m_normals.resize(positions.size());

		for(size_t i = 0; i < m_indices.size(); i += 3)
		{
			const uint32_t a = m_indices[i+0];
			const uint32_t b = m_indices[i+1];
			const uint32_t c = m_indices[i+2];

			const vec3 cb = positions[c] - positions[b];
			const vec3 ab = positions[a] - positions[b];
			const vec3 normal = normalize(cross(cb, ab));

			m_normals[a] = m_normals[b] = m_normals[c] = normal;
		}
	}

	void MeshPacker::gen_normals(bool area_weighted)
	{
		vector<vec3> normals = vector<vec3>(m_positions.size(), vec3(0.f));

		// vertex normals weighted by triangle areas
		// http://www.iquilezles.org/www/articles/normals/normals.htm

		const vector<vec3>& positions = m_positions;

		for(size_t i = 0; i < m_indices.size(); i += 3)
		{
			const uint32_t a = m_indices[i+0];
			const uint32_t b = m_indices[i+1];
			const uint32_t c = m_indices[i+2];

			const vec3 cb = positions[c] - positions[b];
			const vec3 ab = positions[a] - positions[b];
			const vec3 normal = area_weighted
				? cross(cb, ab)
				: normalize(cross(cb, ab));

			normals[a] += normal;
			normals[b] += normal;
			normals[c] += normal;
		}
		
		for(vec3& n : normals)
			n = normalize(n);

		m_normals = normals;
	}

	void MeshPacker::smooth_normals()
	{
#if 0
		map<vec3, vec3> smooth_normals;
		//std::unordered_map<vec3, vec3> smooth_normals;

		vector<int> smooth_groups;

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
#endif
	}

	struct ShapeData
	{
		span<ShapeIndex> m_indices;
		span<ShapeVertex> m_vertices;
	};

	inline ShapeData& mikkt_mesh(const SMikkTSpaceContext* context) { return *static_cast<ShapeData*>(context->m_pUserData); }
	inline ShapeVertex& mikkt_vertex(const SMikkTSpaceContext* context, int face, int vert)
	{
		ShapeData& shape_data = *static_cast<ShapeData*>(context->m_pUserData);
		ShapeIndex index = shape_data.m_indices[face * 3 + vert];
		return shape_data.m_vertices[index];
	}

	void generate_mikkt_tangents(span<ShapeIndex> indices, span<ShapeVertex> vertices)
	{
		ShapeData shape_data = { indices, vertices };
		vector<ShapeVertex> verts = to_vector(vertices);

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
			printf("[warning] Couldn't generate mikktspace tangents\n");
	}

	void MeshPacker::gen_tangents()
	{
		using Context = SMikkTSpaceContext;

		m_tangents.resize(m_positions.size());

		static auto p = [](const SMikkTSpaceContext* context) -> MeshPacker& { return *static_cast<MeshPacker*>(context->m_pUserData); };
		static auto index = [](const SMikkTSpaceContext* context, int face, int vert)
		{
			MeshPacker& pp = p(context);
			return pp.m_indices.size() > 0
				? pp.m_indices[face * 3 + vert]
				: face * 3 + vert;
		};

		SMikkTSpaceInterface intf = {};
		intf.m_getNumFaces = [](const Context* c) -> int { return int(p(c).face_count()); };
		intf.m_getNumVerticesOfFace = [](const Context* c, const int face) -> int { UNUSED(c); UNUSED(face); return 3; };
		intf.m_getPosition = [](const Context* c, float pos[], const int face, const int vert) { vec_to_array(p(c).m_positions[index(c, face, vert)], pos); };
		intf.m_getNormal = [](const Context* c, float norm[], const int face, const int vert) { vec_to_array(p(c).m_normals[index(c, face, vert)], norm); };
		intf.m_getTexCoord = [](const Context* c, float uv[], const int face, const int vert) { vec_to_array(p(c).m_uv0s[index(c, face, vert)], uv); };
		
		intf.m_setTSpaceBasic = [](const SMikkTSpaceContext * c, const float tangent[], const float sign, const int face, const int vert)
		{
			p(c).m_tangents[index(c, face, vert)] = { tangent[0], tangent[1], tangent[2], sign };
		};

		SMikkTSpaceContext context;
		context.m_pInterface = &intf;
		context.m_pUserData = this;

		bool success = genTangSpaceDefault(&context) != 0;
		if(!success)
			printf("[warning] Couldn't generate mikktspace tangents\n");
	}
}
