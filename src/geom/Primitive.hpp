//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Forward.h>
#include <geom/Primitive.h>

#ifndef MUD_CPP_20
#include <cstring>
#endif

namespace mud
{
	inline size_t vertex_attribute_size(VertexAttribute::Enum attribute)
	{
		if(attribute == VertexAttribute::Position)			return sizeof(vec3);
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

	inline MeshAdapter::Array::Array() : m_pointer(nullptr), m_count(0) {}
	inline MeshAdapter::Array::Array(void* pointer, uint32_t count) : m_pointer(pointer), m_count(count) {}

	inline uint32_t MeshAdapter::Array::size() { return m_count; }
	inline void* MeshAdapter::Array::data() const { return m_pointer; }

	inline MeshAdapter::MeshAdapter() {}
	inline MeshAdapter::MeshAdapter(uint32_t vertex_format, void* vertices, uint32_t num_vertices, void* indices, uint32_t num_indices, bool index32)
		: m_vertices(vertices, num_vertices), m_indices(indices, num_indices), m_vertex_format(vertex_format)
		, m_vertex_stride(vertex_size(vertex_format)), m_index_stride(index32 ? sizeof(uint32_t) : sizeof(uint16_t)), m_index(indices)
	{
		if((vertex_format & VertexAttribute::Position) != 0)
			m_start.m_position	= (vec3*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Position));
		if((vertex_format & VertexAttribute::Normal) != 0)
			m_start.m_normal	= (vec3*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Normal));
		if((vertex_format & VertexAttribute::Colour) != 0)
			m_start.m_colour	= (uint32_t*)	((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Colour));
		if((vertex_format & VertexAttribute::Tangent) != 0)
			m_start.m_tangent	= (vec4*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Tangent));
		if((vertex_format & VertexAttribute::Bitangent) != 0)
			m_start.m_bitangent	= (vec3*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Bitangent));
		if((vertex_format & VertexAttribute::TexCoord0) != 0)
			m_start.m_uv0		= (vec2*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::TexCoord0));
		if((vertex_format & VertexAttribute::TexCoord1) != 0)
			m_start.m_uv1		= (vec2*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::TexCoord1));
		if((vertex_format & VertexAttribute::Joints) != 0)
			m_start.m_joints	= (uint32_t*)	((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Joints));
		if((vertex_format & VertexAttribute::Weights) != 0)
			m_start.m_weights	= (vec4*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::Weights));
			
		if((vertex_format & VertexAttribute::QPosition) != 0)
			m_start.m_qposition	= (half3*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QPosition));
		if((vertex_format & VertexAttribute::QNormal) != 0)
			m_start.m_qnormal	= (uint32_t*)	((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QNormal));
		if((vertex_format & VertexAttribute::QTangent) != 0)
			m_start.m_qtangent	= (uint32_t*)	((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QTangent));
		if((vertex_format & VertexAttribute::QTexCoord0) != 0)
			m_start.m_quv0		= (half2*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QTexCoord0));
		if((vertex_format & VertexAttribute::QTexCoord1) != 0)
			m_start.m_quv1		= (half2*)		((char*)vertices + vertex_offset(vertex_format, VertexAttribute::QTexCoord1));

		m_cursor = m_start;
	}

	inline void MeshAdapter::rewind() { m_cursor = m_start; m_vertex = 0; m_offset = 0; m_index = m_indices.m_pointer; }
	inline void MeshAdapter::next() { m_offset = m_vertex; }

	inline MeshAdapter MeshAdapter::read() const { MeshAdapter reader = *this; reader.rewind(); return reader; }

	template <class T>
	inline void MeshAdapter::next(T*& pointer) { pointer = (T*)((char*)pointer + m_vertex_stride); }

	inline MeshAdapter& MeshAdapter::position(const vec3& p) { m_aabb.add(p); *m_cursor.m_position = p; next(m_cursor.m_position); ++m_vertex; return *this; }
	inline MeshAdapter& MeshAdapter::normal(const vec3& n) { if(m_cursor.m_normal) { *m_cursor.m_normal = n; next(m_cursor.m_normal); } return *this; }
	inline MeshAdapter& MeshAdapter::colour(const Colour& c) { if(m_cursor.m_colour) { *m_cursor.m_colour = to_abgr(c); next(m_cursor.m_colour); } return *this; }
	inline MeshAdapter& MeshAdapter::tangent(const vec4& t) { if(m_cursor.m_tangent) { *m_cursor.m_tangent = t; next(m_cursor.m_tangent); } return *this; }
	inline MeshAdapter& MeshAdapter::bitangent(const vec4& b) { if(m_cursor.m_bitangent) { *m_cursor.m_bitangent = vec3(b); next(m_cursor.m_bitangent); } return *this; }
	inline MeshAdapter& MeshAdapter::uv0(const vec2& uv) { if(m_cursor.m_uv0) { m_uv0_rect.add(uv); *m_cursor.m_uv0 = uv; next(m_cursor.m_uv0); } return *this; }
	inline MeshAdapter& MeshAdapter::uv1(const vec2& uv) { if(m_cursor.m_uv1) { m_uv1_rect.add(uv); *m_cursor.m_uv1 = uv; next(m_cursor.m_uv1); } return *this; }
	inline MeshAdapter& MeshAdapter::joints(const uint32_t& j) { if(m_cursor.m_joints) { *m_cursor.m_joints = j; next(m_cursor.m_joints); } return *this; }
	inline MeshAdapter& MeshAdapter::weights(const vec4& w) { if(m_cursor.m_weights) { *m_cursor.m_weights = w; next(m_cursor.m_weights); } return *this; }

	inline vec3 MeshAdapter::position() { vec3 value = *m_cursor.m_position; next(m_cursor.m_position); return value; }
	inline vec3 MeshAdapter::normal() { if(!m_cursor.m_normal) return Zero3; vec3 value = *m_cursor.m_normal; next(m_cursor.m_normal); return value; }
	inline Colour MeshAdapter::colour() { if(!m_cursor.m_colour) return Colour::None; Colour value = from_abgr(*m_cursor.m_colour); next(m_cursor.m_colour); return value; }
	inline vec4 MeshAdapter::tangent() { if(!m_cursor.m_tangent) return vec4(Zero3, 1.f); vec4 value = *m_cursor.m_tangent; next(m_cursor.m_tangent); return value; }
	inline vec2 MeshAdapter::uv0() { if(!m_cursor.m_uv0) return Zero2; vec2 value = *m_cursor.m_uv0; next(m_cursor.m_uv0); return value; }
	inline vec2 MeshAdapter::uv1() { if(!m_cursor.m_uv1) return Zero2; vec2 value = *m_cursor.m_uv1; next(m_cursor.m_uv1); return value; }
	inline uint16_t MeshAdapter::index() { uint16_t value = *(uint16_t*)m_index; m_index = ((char*)m_index + m_index_stride); return value; }
	inline uint32_t MeshAdapter::index32() { uint32_t value = *(uint32_t*)m_index; m_index = ((char*)m_index + m_index_stride); return value; }

	inline void MeshAdapter::index(uint32_t i) { uint32_t index = i + m_offset; memcpy(m_index, &index, m_index_stride); m_index = ((char*)m_index + m_index_stride); }
	inline void MeshAdapter::line(uint32_t a, uint32_t b) { index(a); index(b); }
	inline void MeshAdapter::tri(uint32_t a, uint32_t b, uint32_t c) { index(a); index(b); index(c); }
	inline void MeshAdapter::quad(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { tri(a, b, c); tri(c, d, a); }
}
