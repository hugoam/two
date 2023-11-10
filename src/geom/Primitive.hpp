//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <cstring>
#include <cassert>
#endif
#include <geom/Forward.h>
#include <geom/Primitive.h>


namespace two
{
	inline size_t vertex_attribute_size(VertexAttribute::Enum attribute)
	{
		if(attribute == VertexAttribute::Position)			return sizeof(vec3);
		else if(attribute == VertexAttribute::Position4)	return sizeof(vec4);
		else if(attribute == VertexAttribute::QPosition)	return sizeof(half3);
		else if(attribute == VertexAttribute::Normal)		return sizeof(vec3);
		else if(attribute == VertexAttribute::QNormal)		return sizeof(uint32_t);
		else if(attribute == VertexAttribute::Colour)		return sizeof(uint32_t);
		else if(attribute == VertexAttribute::Tangent)		return sizeof(vec4);
		else if(attribute == VertexAttribute::QTangent)		return sizeof(uint32_t);
		else if(attribute == VertexAttribute::Bitangent)	return sizeof(vec3);
		else if(attribute == VertexAttribute::TexCoord0)	return sizeof(vec2);
		else if(attribute == VertexAttribute::QTexCoord0)	return sizeof(half2);
		else if(attribute == VertexAttribute::TexCoord1)	return sizeof(vec2);
		else if(attribute == VertexAttribute::QTexCoord1)	return sizeof(half2);
		else if(attribute == VertexAttribute::Joints)		return sizeof(uint32_t);
		else if(attribute == VertexAttribute::Weights)		return sizeof(vec4);
		else return 0;
	}

	inline uint32_t vertex_size(uint32_t vertex_format)
	{
		uint32_t size = 0;
		for(VertexAttribute::Enum current = VertexAttribute::Position; current != VertexAttribute::Count; current = VertexAttribute::Enum(current << 1))
		{
			if((vertex_format & current) != 0)
				size += uint32_t(vertex_attribute_size(current));
		}
		return size;
	}

	inline size_t vertex_offset(uint32_t vertex_format, VertexAttribute::Enum attribute)
	{
		size_t offset = 0;
		for(VertexAttribute::Enum current = VertexAttribute::Position; current != attribute; current = VertexAttribute::Enum(current << 1))
		{
			if((vertex_format & current) != 0)
				offset += vertex_attribute_size(current);
		}
		return offset;
	}

	inline MeshAdapter::MeshAdapter(uint32_t vertex_format, span<void> vertices, span<void> indices, bool index32)
		: m_vertex_format(vertex_format), m_index32(index32)
		, m_vertex_count(uint32_t(vertices.size()))
		, m_index_count(uint32_t(indices.size()))
		, m_vertex_stride(vertex_size(vertex_format))
	{
		uint32_t stride = vertex_size(vertex_format);

		m_start.m_position .init(vertex_format, VertexAttribute::Position,  vertices.data(), stride);
		m_start.m_position4.init(vertex_format, VertexAttribute::Position4, vertices.data(), stride);
		m_start.m_normal   .init(vertex_format, VertexAttribute::Normal,    vertices.data(), stride);
		m_start.m_colour   .init(vertex_format, VertexAttribute::Colour,    vertices.data(), stride);
		m_start.m_tangent  .init(vertex_format, VertexAttribute::Tangent,   vertices.data(), stride);
		m_start.m_bitangent.init(vertex_format, VertexAttribute::Bitangent, vertices.data(), stride);
		m_start.m_uv0	   .init(vertex_format, VertexAttribute::TexCoord0, vertices.data(), stride);
		m_start.m_uv1      .init(vertex_format, VertexAttribute::TexCoord1, vertices.data(), stride);
		m_start.m_joints   .init(vertex_format, VertexAttribute::Joints,    vertices.data(), stride);
		m_start.m_weights  .init(vertex_format, VertexAttribute::Weights,   vertices.data(), stride);
		
		m_start.m_qposition.init(vertex_format, VertexAttribute::QPosition,  vertices.data(), stride);
		m_start.m_qnormal  .init(vertex_format, VertexAttribute::QNormal,    vertices.data(), stride);
		m_start.m_qtangent .init(vertex_format, VertexAttribute::QTangent,   vertices.data(), stride);
		m_start.m_quv0     .init(vertex_format, VertexAttribute::QTexCoord0, vertices.data(), stride);
		m_start.m_quv1     .init(vertex_format, VertexAttribute::QTexCoord1, vertices.data(), stride);

		if(index32)
			m_start.m_index32.init(indices.data());
		else
			m_start.m_index.init(indices.data());

		m_cursor = m_start;
	}

	inline MeshAdapter MeshAdapter::read() const { MeshAdapter reader = *this; reader.rewind(); return reader; }

#if 0
	inline MeshAdapter& MeshAdapter::position(const vec3& p) { m_aabb.add(p); *m_cursor.m_position = p; next(m_cursor.m_position); ++m_vertex; return *this; }
	inline MeshAdapter& MeshAdapter::position4(const vec4& p) { m_aabb.add(vec3(p)); *m_cursor.m_position4 = p; next(m_cursor.m_position4); ++m_vertex; return *this; }
	inline MeshAdapter& MeshAdapter::normal(const vec3& n) { if(m_cursor.m_normal) { *m_cursor.m_normal = n; next(m_cursor.m_normal); } return *this; }
	inline MeshAdapter& MeshAdapter::colour(const Colour& c) { if(m_cursor.m_colour) { *m_cursor.m_colour = to_abgr(c); next(m_cursor.m_colour); } return *this; }
	inline MeshAdapter& MeshAdapter::tangent(const vec4& t) { if(m_cursor.m_tangent) { *m_cursor.m_tangent = t; next(m_cursor.m_tangent); } return *this; }
	inline MeshAdapter& MeshAdapter::bitangent(const vec3& b) { if(m_cursor.m_bitangent) { *m_cursor.m_bitangent = b; next(m_cursor.m_bitangent); } return *this; }
	inline MeshAdapter& MeshAdapter::uv0(const vec2& uv) { if(m_cursor.m_uv0) { m_uv0_rect.add(uv); *m_cursor.m_uv0 = uv; next(m_cursor.m_uv0); } return *this; }
	inline MeshAdapter& MeshAdapter::uv1(const vec2& uv) { if(m_cursor.m_uv1) { m_uv1_rect.add(uv); *m_cursor.m_uv1 = uv; next(m_cursor.m_uv1); } return *this; }
	inline MeshAdapter& MeshAdapter::joints(const uint32_t& j) { if(m_cursor.m_joints) { *m_cursor.m_joints = j; next(m_cursor.m_joints); } return *this; }
	inline MeshAdapter& MeshAdapter::weights(const vec4& w) { if(m_cursor.m_weights) { *m_cursor.m_weights = w; next(m_cursor.m_weights); } return *this; }
#endif

	inline MeshAdapter& MeshAdapter::dposition(const vec3& p) { m_cursor.m_position.write(p); ++m_vertex; return *this; }
	inline MeshAdapter& MeshAdapter::duv0(const vec2& uv) { if(m_cursor.m_uv0) { m_cursor.m_uv0.write(uv); } return *this; }
	inline MeshAdapter& MeshAdapter::duv1(const vec2& uv) { if(m_cursor.m_uv1) { m_cursor.m_uv1.write(uv); } return *this; }

	inline vec3 MeshAdapter::position() { return m_cursor.m_position.read(); }
	inline vec3 MeshAdapter::normal() { if(!m_cursor.m_normal) return vec3(0.f); return m_cursor.m_normal.read(); }
	inline Colour MeshAdapter::colour() { if(!m_cursor.m_colour) return Colour::None; return abgr(m_cursor.m_colour.read()); }
	inline vec4 MeshAdapter::tangent() { if(!m_cursor.m_tangent) return vec4(vec3(0.f), 1.f); return m_cursor.m_tangent.read(); }
	inline vec2 MeshAdapter::uv0() { if(!m_cursor.m_uv0) return vec2(0.f); return m_cursor.m_uv0.read(); }
	inline vec2 MeshAdapter::uv1() { if(!m_cursor.m_uv1) return vec2(0.f); return m_cursor.m_uv1.read(); }
	inline uint32_t MeshAdapter::joints() { if(!m_cursor.m_joints) return uint32_t(0U); return m_cursor.m_joints.read(); }
	inline vec4 MeshAdapter::weights() { if(!m_cursor.m_weights) return vec4(0.f); return m_cursor.m_weights.read(); }
	inline uint16_t MeshAdapter::index() { return m_cursor.m_index.read(); }
	inline uint32_t MeshAdapter::index32() { return m_cursor.m_index32.read(); }

	inline void MeshAdapter::index(uint32_t i) { uint32_t index = i + m_offset; m_index32 ? m_cursor.m_index32.write(index) : m_cursor.m_index.write(uint16_t(index)); }
	inline void MeshAdapter::line(uint32_t a, uint32_t b) { index(a); index(b); }
	inline void MeshAdapter::tri(uint32_t a, uint32_t b, uint32_t c) { index(a); index(b); index(c); }
	inline void MeshAdapter::quad(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { tri(a, b, c); tri(c, d, a); }
}
