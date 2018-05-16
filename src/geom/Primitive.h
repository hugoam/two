//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <math/Vec.h>
#include <math/Colour.h>
#include <geom/Generated/Forward.h>

namespace mud
{
	enum _refl_ DrawMode : unsigned int
	{
		OUTLINE = 0,
		PLAIN = 1
	};

	enum class _refl_ PrimitiveType : unsigned int
	{
		Points = 0,
		Lines = 1,
		LineLoop = 2,
		LineStrip = 3,
		Triangles = 4,
		TriangleStrip = 5,
		TriangleFan = 6
	};

	struct VertexAttribute
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

	template <typename T, typename = int>
	struct vertex_position { static vec3* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_position <T, decltype(std::declval<T>().m_position, 0)> { static vec3* get(T& vertex) { return &vertex.m_position; } };

	template <typename T, typename = int>
	struct vertex_normal { static vec3* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_normal <T, decltype(std::declval<T>().m_normal, 0)> { static vec3* get(T& vertex) { return &vertex.m_normal; } };

	template <typename T, typename = int>
	struct vertex_colour { static uint32_t* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_colour <T, decltype(std::declval<T>().m_colour, 0)> { static uint32_t* get(T& vertex) { return &vertex.m_colour; } };

	template <typename T, typename = int>
	struct vertex_tangent { static vec4* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_tangent <T, decltype(std::declval<T>().m_tangent, 0)> { static vec4* get(T& vertex) { return &vertex.m_tangent; } };

	template <typename T, typename = int>
	struct vertex_bitangent { static vec3* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_bitangent <T, decltype(std::declval<T>().m_bitangent, 0)> { static vec3* get(T& vertex) { return &vertex.m_bitangent; } };

	template <typename T, typename = int>
	struct vertex_uv0 { static vec2* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_uv0 <T, decltype(std::declval<T>().m_uv0, 0)> { static vec2* get(T& vertex) { return &vertex.m_uv0; } };

	template <typename T, typename = int>
	struct vertex_uv1 { static vec2* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_uv1 <T, decltype(std::declval<T>().m_uv1, 0)> { static vec2* get(T& vertex) { return &vertex.m_uv1; } };

	template <typename T, typename = int>
	struct vertex_joints { static uint32_t* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_joints <T, decltype(std::declval<T>().m_joints, 0)> { static uint32_t* get(T& vertex) { return &vertex.m_joints; } };

	template <typename T, typename = int>
	struct vertex_weights { static vec4* get(T& vertex) { UNUSED(vertex); return nullptr; } };

	template <typename T>
	struct vertex_weights <T, decltype(std::declval<T>().m_weights, 0)> { static vec4* get(T& vertex) { return &vertex.m_weights; } };

	using ShapeIndex = uint16_t;
	
	struct MUD_MATH_EXPORT Vertex
	{
		static const size_t vertex_format = VertexAttribute::Position;
		vec3 m_position;
	};

	struct MUD_MATH_EXPORT Tri
	{
		ShapeIndex a, b, c;
	};

	struct MUD_MATH_EXPORT ShapeVertex
	{
		static const size_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::Colour 
										  | VertexAttribute::Tangent| VertexAttribute::TexCoord0 | VertexAttribute::Joints | VertexAttribute::Weights;
		vec3 m_position; vec3 m_normal; uint32_t m_colour; vec4 m_tangent; vec2 m_uv0; uint32_t m_joints; vec4 m_weights;
	};

	struct MUD_MATH_EXPORT ShapeTriangle
	{
		uint32_t a, b, c;
	};

	struct MeshData
	{
		MeshData() {}

		template <class T_Vertex>
		MeshData(T_Vertex* vertices, ShapeIndex* indices)
			: m_vertices((void*)vertices), m_indices(indices), m_vertex_format(T_Vertex::vertex_format), m_stride(sizeof(T_Vertex)), m_index(indices)
		{
			m_position	= vertex_position<T_Vertex>::get(*vertices);
			m_colour	= vertex_colour<T_Vertex>::get(*vertices);
			m_normal	= vertex_normal<T_Vertex>::get(*vertices);
			m_tangent	= vertex_tangent<T_Vertex>::get(*vertices);
			m_uv		= vertex_uv0<T_Vertex>::get(*vertices);
		}

		void* m_vertices = nullptr;
		ShapeIndex* m_indices = nullptr;

		size_t m_vertex_format = 0;
		size_t m_stride = 0;

		vec3* m_position = nullptr;
		vec3* m_normal = nullptr;
		uint32_t* m_colour = nullptr;
		vec4* m_tangent = nullptr;
		vec2* m_uv = nullptr;

		ShapeIndex* m_index = nullptr;

		ShapeIndex m_vertex = 0;
		ShapeIndex m_offset = 0;

		inline void next() { m_offset = m_vertex; }

		template <class T>
		inline void increment(T*& pointer) { if(m_stride > 0) pointer = (T*)((char*)pointer + m_stride); else pointer++; }

		MeshData& position(const vec3& p) { *m_position = p; increment(m_position); ++m_vertex; return *this; }
		MeshData& normal(const vec3& n) { if(m_normal) { *m_normal = n; increment(m_normal); } return *this; }
		MeshData& colour(const Colour& c) { if(m_colour) { *m_colour = to_abgr(c); increment(m_colour); } return *this; }
		MeshData& tangent(const vec4 t) { if(m_tangent) { *m_tangent = t; increment(m_tangent); } return *this; }
		MeshData& textureCoord(const vec2& uv) { if(m_uv) { *m_uv = uv; increment(m_uv); } return *this; }

		inline void index(ShapeIndex index) { *m_index++ = m_offset + index; }
		inline void line(ShapeIndex a, ShapeIndex b) { index(a); index(b); }
		inline void tri(ShapeIndex a, ShapeIndex b, ShapeIndex c) { index(a); index(b); index(c); }
		inline void quad(ShapeIndex a, ShapeIndex b, ShapeIndex c, ShapeIndex d) { tri(a, b, c); tri(c, d, a); }
	};
}
