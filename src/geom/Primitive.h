//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <cfloat>
#include <stl/span.h>
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

	export_ size_t vertex_attribute_size(VertexAttribute::Enum attribute);

	export_ uint32_t vertex_size(uint32_t vertex_format);

	export_ size_t vertex_offset(uint32_t vertex_format, VertexAttribute::Enum attribute);

	export_ struct MUD_GEOM_EXPORT MeshAdapter
	{
		struct Array
		{
			Array();
			Array(void* pointer, uint32_t count);
				
			uint32_t size();
			void* data() const;

			void* m_pointer;
			uint32_t m_count;
		};

		MeshAdapter();
		MeshAdapter(uint32_t vertex_format, void* vertices, uint32_t num_vertices, void* indices, uint32_t num_indices, bool index32);

		Array m_vertices = {};
		Array m_indices = {};

		//span<void> m_vertices = {};
		//span<void> m_indices = {};

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

		void rewind();
		void next();

		MeshAdapter read() const;

		template <class T>
		inline void next(T*& pointer);

		MeshAdapter& position(const vec3& p);
		MeshAdapter& normal(const vec3& n);
		MeshAdapter& colour(const Colour& c);
		MeshAdapter& tangent(const vec4& t);
		MeshAdapter& bitangent(const vec4& b);
		MeshAdapter& uv0(const vec2& uv);
		MeshAdapter& uv1(const vec2& uv);
		MeshAdapter& joints(const uint32_t& j);
		MeshAdapter& weights(const vec4& w);

		vec3 position();
		vec3 normal();
		Colour colour();
		vec4 tangent();
		vec2 uv0();
		vec2 uv1();
		uint16_t index();
		uint32_t index32();

		void index(uint32_t i);
		void line(uint32_t a, uint32_t b);
		void tri(uint32_t a, uint32_t b, uint32_t c);
		void quad(uint32_t a, uint32_t b, uint32_t c, uint32_t d);

		MeshAdapter& qposition(const vec3& p);
		MeshAdapter& qnormal(const vec3& n);
		MeshAdapter& qtangent(const vec4& t);
		MeshAdapter& quv0(const vec2& uv);
		MeshAdapter& quv1(const vec2& uv);
	};
}
