//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <math/Vec.h>
#include <math/Colour.h>
#endif
#include <geom/Forward.h>

namespace mud
{
	export_ enum refl_ DrawMode : unsigned int
	{
		OUTLINE = 0,
		PLAIN = 1
	};

	export_ enum class refl_ PrimitiveType : unsigned int
	{
		Points = 0,
		Lines = 1,
		LineLoop = 2,
		LineStrip = 3,
		Triangles = 4,
		TriangleStrip = 5,
		TriangleFan = 6
	};

	export_ struct VertexAttribute
	{
		enum Enum
		{
			Position = 1 << 0,
			QPosition = 1 << 1,
			Normal = 1 << 2,
			QNormal = 1 << 3,
			Colour = 1 << 4,
			Tangent = 1 << 5,
			QTangent = 1 << 6,
			Bitangent = 1 << 7,
			TexCoord0 = 1 << 8,
			QTexCoord0 = 1 << 9,
			TexCoord1 = 1 << 10,
			QTexCoord1 = 1 << 11,
			Joints = 1 << 12,
			Weights = 1 << 13,

			Count = 1 << 14
		};
	};

	export_ using ShapeIndex = uint16_t;
	
	export_ struct MUD_GEOM_EXPORT Vertex
	{
		static const uint32_t vertex_format = VertexAttribute::Position;
		vec3 m_position;
	};

	export_ struct MUD_GEOM_EXPORT Tri
	{
		uint32_t a, b, c;
	};

	export_ struct MUD_GEOM_EXPORT ShapeVertex
	{
		static const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::Colour
										    | VertexAttribute::Tangent| VertexAttribute::TexCoord0 | VertexAttribute::Joints | VertexAttribute::Weights;
		vec3 m_position; vec3 m_normal; uint32_t m_colour; vec4 m_tangent; vec2 m_uv0; uint32_t m_joints; vec4 m_weights;
	};

	export_ struct MUD_GEOM_EXPORT ShapeTriangle
	{
		uint32_t a, b, c;
	};

	export_ inline size_t vertex_attribute_size(VertexAttribute::Enum attribute)
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

	export_ inline uint32_t vertex_size(uint32_t vertex_format)
	{
		uint32_t size = 0;
		for(VertexAttribute::Enum current = VertexAttribute::Position; current != VertexAttribute::Count; current = VertexAttribute::Enum(current << 1))
		{
			if((vertex_format & current) != 0)
				size += uint32_t(vertex_attribute_size(current));
		}
		return size;
	}

	export_ inline size_t vertex_offset(uint32_t vertex_format, VertexAttribute::Enum attribute)
	{
		size_t offset = 0;
		for(VertexAttribute::Enum current = VertexAttribute::Position; current != attribute; current = VertexAttribute::Enum(current << 1))
		{
			if((vertex_format & current) != 0)
				offset += vertex_attribute_size(current);
		}
		return offset;
	}

	export_ struct MeshAdapter
	{
		struct Array
		{
			Array() : m_pointer(nullptr), m_count(0) {}
			Array(void* pointer, uint32_t count) : m_pointer(pointer), m_count(count) {}
				
			uint32_t size() { return m_count; }
			void* data() const { return m_pointer; }

			void* m_pointer;
			uint32_t m_count;
		};

		MeshAdapter() {}
		MeshAdapter(uint32_t vertex_format, void* vertices, uint32_t num_vertices, void* indices, uint32_t num_indices, bool index32)
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

		Array m_vertices = {};
		Array m_indices = {};

		uint32_t m_vertex_format = 0;
		uint32_t m_vertex_stride = 0;
		uint32_t m_index_stride = 0;

		struct Pointers
		{
			vec3* m_position = nullptr;
			vec3* m_normal = nullptr;
			uint32_t* m_colour = nullptr;
			vec4* m_tangent = nullptr;
			vec3* m_bitangent = nullptr;
			vec2* m_uv0 = nullptr;
			vec2* m_uv1 = nullptr;
			uint32_t* m_joints = nullptr;
			vec4* m_weights = nullptr;

			half3* m_qposition = nullptr;
			uint32_t* m_qnormal = nullptr;
			uint32_t* m_qtangent = nullptr;
			half2* m_quv0 = nullptr;
			half2* m_quv1 = nullptr;
		};

		Pointers m_start;
		Pointers m_cursor;

		void* m_index = nullptr;

		uint32_t m_vertex = 0;
		uint32_t m_offset = 0;

		template <class T>
		struct Bounds { T lo = T(FLT_MAX); T hi = T(-FLT_MAX); void add(const T& val) { lo = min(val, lo); hi = max(val, hi); } };
		Bounds<vec3> m_aabb = {};
		Bounds<vec2> m_uv0_rect = {};
		Bounds<vec2> m_uv1_rect = {};

		inline void rewind() { m_cursor = m_start; m_vertex = 0; m_offset = 0; m_index = m_indices.m_pointer; }
		inline void next() { m_offset = m_vertex; }

		MeshAdapter read() const { MeshAdapter reader = *this; reader.rewind(); return reader; }

		template <class T>
		inline void next(T*& pointer) { pointer = (T*)((char*)pointer + m_vertex_stride); }

		MeshAdapter& position(const vec3& p) { m_aabb.add(p); *m_cursor.m_position = p; next(m_cursor.m_position); ++m_vertex; return *this; }
		MeshAdapter& normal(const vec3& n) { if(m_cursor.m_normal) { *m_cursor.m_normal = n; next(m_cursor.m_normal); } return *this; }
		MeshAdapter& colour(const Colour& c) { if(m_cursor.m_colour) { *m_cursor.m_colour = to_abgr(c); next(m_cursor.m_colour); } return *this; }
		MeshAdapter& tangent(const vec4& t) { if(m_cursor.m_tangent) { *m_cursor.m_tangent = t; next(m_cursor.m_tangent); } return *this; }
		MeshAdapter& bitangent(const vec4& b) { if(m_cursor.m_bitangent) { *m_cursor.m_bitangent = b; next(m_cursor.m_bitangent); } return *this; }
		MeshAdapter& uv0(const vec2& uv) { if(m_cursor.m_uv0) { m_uv0_rect.add(uv); *m_cursor.m_uv0 = uv; next(m_cursor.m_uv0); } return *this; }
		MeshAdapter& uv1(const vec2& uv) { if(m_cursor.m_uv1) { m_uv1_rect.add(uv); *m_cursor.m_uv1 = uv; next(m_cursor.m_uv1); } return *this; }
		MeshAdapter& joints(const uint32_t& j) { if(m_cursor.m_joints) { *m_cursor.m_joints = j; next(m_cursor.m_joints); } return *this; }
		MeshAdapter& weights(const vec4& w) { if(m_cursor.m_weights) { *m_cursor.m_weights = w; next(m_cursor.m_weights); } return *this; }

		vec3 position() { vec3 value = *m_cursor.m_position; next(m_cursor.m_position); return value; }
		vec3 normal() { if(!m_cursor.m_normal) return Zero3; vec3 value = *m_cursor.m_normal; next(m_cursor.m_normal); return value; }
		Colour colour() { if(!m_cursor.m_colour) return Colour::None; Colour value = from_abgr(*m_cursor.m_colour); next(m_cursor.m_colour); return value; }
		vec4 tangent() { if(!m_cursor.m_tangent) return vec4(Zero3, 1.f); vec4 value = *m_cursor.m_tangent; next(m_cursor.m_tangent); return value; }
		vec2 uv0() { if(!m_cursor.m_uv0) return Zero2; vec2 value = *m_cursor.m_uv0; next(m_cursor.m_uv0); return value; }
		vec2 uv1() { if(!m_cursor.m_uv1) return Zero2; vec2 value = *m_cursor.m_uv1; next(m_cursor.m_uv1); return value; }
		uint16_t index() { uint16_t value = *(uint16_t*)m_index; m_index = ((char*)m_index + m_index_stride); return value; }
		uint32_t index32() { uint32_t value = *(uint32_t*)m_index; m_index = ((char*)m_index + m_index_stride); return value; }

		inline void index(uint32_t i) { uint32_t index = i + m_offset; memcpy(m_index, &index, m_index_stride); m_index = ((char*)m_index + m_index_stride); }
		inline void line(uint32_t a, uint32_t b) { index(a); index(b); }
		inline void tri(uint32_t a, uint32_t b, uint32_t c) { index(a); index(b); index(c); }
		inline void quad(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { tri(a, b, c); tri(c, d, a); }

		MeshAdapter& qposition(const vec3& p);
		MeshAdapter& qnormal(const vec3& n);
		MeshAdapter& qtangent(const vec4& t);
		MeshAdapter& quv0(const vec2& uv);
		MeshAdapter& quv1(const vec2& uv);
	};
}
