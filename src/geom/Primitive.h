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
			Normal = 1 << 1,
			Colour = 1 << 2,
			Tangent = 1 << 3,
			Bitangent = 1 << 4,
			TexCoord0 = 1 << 5,
			TexCoord1 = 1 << 6,
			Joints = 1 << 7,
			Weights = 1 << 8
		};
	};

	export_ template <typename T, typename = int>
	struct vertex_position { static vec3* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_position <T, decltype(std::declval<T>().m_position, 0)> { static vec3* get(T& vertex) { return &vertex.m_position; } };

	export_ template <typename T, typename = int>
	struct vertex_normal { static vec3* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_normal <T, decltype(std::declval<T>().m_normal, 0)> { static vec3* get(T& vertex) { return &vertex.m_normal; } };

	export_ template <typename T, typename = int>
	struct vertex_colour { static uint32_t* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_colour <T, decltype(std::declval<T>().m_colour, 0)> { static uint32_t* get(T& vertex) { return &vertex.m_colour; } };

	export_ template <typename T, typename = int>
	struct vertex_tangent { static vec4* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_tangent <T, decltype(std::declval<T>().m_tangent, 0)> { static vec4* get(T& vertex) { return &vertex.m_tangent; } };

	export_ template <typename T, typename = int>
	struct vertex_bitangent { static vec3* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_bitangent <T, decltype(std::declval<T>().m_bitangent, 0)> { static vec3* get(T& vertex) { return &vertex.m_bitangent; } };

	export_ template <typename T, typename = int>
	struct vertex_uv0 { static vec2* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_uv0 <T, decltype(std::declval<T>().m_uv0, 0)> { static vec2* get(T& vertex) { return &vertex.m_uv0; } };

	export_ template <typename T, typename = int>
	struct vertex_uv1 { static vec2* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_uv1 <T, decltype(std::declval<T>().m_uv1, 0)> { static vec2* get(T& vertex) { return &vertex.m_uv1; } };

	export_ template <typename T, typename = int>
	struct vertex_joints { static uint32_t* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_joints <T, decltype(std::declval<T>().m_joints, 0)> { static uint32_t* get(T& vertex) { return &vertex.m_joints; } };

	export_ template <typename T, typename = int>
	struct vertex_weights { static vec4* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	export_ template <typename T>
	struct vertex_weights <T, decltype(std::declval<T>().m_weights, 0)> { static vec4* get(T& vertex) { return &vertex.m_weights; } };

	export_ using ShapeIndex = uint16_t;
	
	export_ struct MUD_GEOM_EXPORT Vertex
	{
		static const size_t vertex_format = VertexAttribute::Position;
		vec3 m_position;
	};

	export_ struct MUD_GEOM_EXPORT Tri
	{
		uint32_t a, b, c;
	};

	export_ struct MUD_GEOM_EXPORT ShapeVertex
	{
		static const size_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::Colour 
										  | VertexAttribute::Tangent| VertexAttribute::TexCoord0 | VertexAttribute::Joints | VertexAttribute::Weights;
		vec3 m_position; vec3 m_normal; uint32_t m_colour; vec4 m_tangent; vec2 m_uv0; uint32_t m_joints; vec4 m_weights;
	};

	export_ struct MUD_GEOM_EXPORT ShapeTriangle
	{
		uint32_t a, b, c;
	};

	export_ struct MeshData
	{
		struct Array
		{
			Array() : m_pointer(nullptr), m_count(0) {}
			Array(void* pointer, size_t count) : m_pointer(pointer), m_count(count) {}
				
			size_t size() { return m_count; }
			void* data() const { return m_pointer; }

			void* m_pointer;
			size_t m_count;
		};

		MeshData() {}
		MeshData(const MeshData& other) { *this = other; this->reset(); }

		template <class T_Vertex, class T_Index>
		MeshData(array<T_Vertex> vertices, array<T_Index> indices)
			: m_vertices((void*)vertices.m_pointer, vertices.size()), m_indices((void*)indices.m_pointer, indices.size()), m_vertex_format(T_Vertex::vertex_format)
			, m_vertex_stride(sizeof(T_Vertex)), m_index_stride(sizeof(T_Index)), m_index((void*)indices.m_pointer)
		{
			m_start.m_position	= vertex_position<T_Vertex>::get(*vertices.m_pointer);
			m_start.m_colour	= vertex_colour<T_Vertex>::get(*vertices.m_pointer);
			m_start.m_normal	= vertex_normal<T_Vertex>::get(*vertices.m_pointer);
			m_start.m_tangent	= vertex_tangent<T_Vertex>::get(*vertices.m_pointer);
			m_start.m_uv		= vertex_uv0<T_Vertex>::get(*vertices.m_pointer);
			m_cursor = m_start;
		}

		Array m_vertices = {};
		Array m_indices = {};

		size_t m_vertex_format = 0;
		size_t m_vertex_stride = 0;
		size_t m_index_stride = 0;

		struct Pointers
		{
			vec3* m_position = nullptr;
			vec3* m_normal = nullptr;
			uint32_t* m_colour = nullptr;
			vec4* m_tangent = nullptr;
			vec2* m_uv = nullptr;
		};

		Pointers m_start;
		Pointers m_cursor;

		void* m_index = nullptr;

		uint32_t m_vertex = 0;
		uint32_t m_offset = 0;

		inline void reset() { m_cursor = m_start; m_vertex = 0; m_offset = 0; m_index = m_indices.m_pointer; }

		inline void next() { m_offset = m_vertex; }

		template <class T>
		inline void next(T*& pointer) { pointer = (T*)((char*)pointer + m_vertex_stride); }

		MeshData& position(const vec3& p) { *m_cursor.m_position = p; next(m_cursor.m_position); ++m_vertex; return *this; }
		MeshData& normal(const vec3& n) { if(m_cursor.m_normal) { *m_cursor.m_normal = n; next(m_cursor.m_normal); } return *this; }
		MeshData& colour(const Colour& c) { if(m_cursor.m_colour) { *m_cursor.m_colour = to_abgr(c); next(m_cursor.m_colour); } return *this; }
		MeshData& tangent(const vec4 t) { if(m_cursor.m_tangent) { *m_cursor.m_tangent = t; next(m_cursor.m_tangent); } return *this; }
		MeshData& textureCoord(const vec2& uv) { if(m_cursor.m_uv) { *m_cursor.m_uv = uv; next(m_cursor.m_uv); } return *this; }

		vec3 position() { vec3 value = *m_cursor.m_position; next(m_cursor.m_position); return value; }
		uint16_t index() { uint16_t value = *(uint16_t*)m_index; m_index = ((char*)m_index + m_index_stride); return value; }
		uint32_t index32() { uint32_t value = *(uint32_t*)m_index; m_index = ((char*)m_index + m_index_stride); return value; }

		inline void index(uint32_t i) { uint32_t index = i + m_offset; memcpy(m_index, &index, m_index_stride); m_index = ((char*)m_index + m_index_stride); }
		inline void line(uint32_t a, uint32_t b) { index(a); index(b); }
		inline void tri(uint32_t a, uint32_t b, uint32_t c) { index(a); index(b); index(c); }
		inline void quad(uint32_t a, uint32_t b, uint32_t c, uint32_t d) { tri(a, b, c); tri(c, d, a); }
	};
}
