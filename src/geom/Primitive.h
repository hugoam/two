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
		LineStrip = 2,
		Triangles = 3,
		TriangleStrip = 4,
		TriangleFan = 5,
		Count
	};

	export_ struct VertexAttribute
	{
		enum Enum
		{
			Position = 1 << 0,
			Position4 = 1 << 1,
			QPosition = 1 << 2,
			Normal = 1 << 3,
			QNormal = 1 << 4,
			Colour = 1 << 5,
			Tangent = 1 << 6,
			QTangent = 1 << 7,
			Bitangent = 1 << 8,
			TexCoord0 = 1 << 9,
			QTexCoord0 = 1 << 10,
			TexCoord1 = 1 << 11,
			QTexCoord1 = 1 << 12,
			Joints = 1 << 13,
			Weights = 1 << 14,
			MorphPosition0 = 1 << 15,
			MorphPosition1 = 1 << 16,
			MorphPosition2 = 1 << 17,
			MorphPosition3 = 1 << 18,
			MorphNormal0 = 1 << 19,
			MorphNormal1 = 1 << 20,
			MorphNormal2 = 1 << 21,
			MorphNormal3 = 1 << 22,

			Count = 1 << 17
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

	export_ struct refl_ MUD_GEOM_EXPORT MeshAdapter
	{
		MeshAdapter() {}
		MeshAdapter(uint32_t vertex_format, span<void> vertices, span<void> indices = {}, bool index32 = false);
		MeshAdapter(uint32_t vertex_count, MeshPacker& geom);

		attr_ uint32_t m_vertex_format = 0;
		attr_ bool m_index32 = false;

		attr_ uint32_t m_vertex_count = 0;
		attr_ uint32_t m_index_count = 0;

		attr_ uint32_t m_vertex_stride = 0;

		template <class T>
		struct Cursor
		{
			T* p = nullptr; uint32_t s;
			inline void init(void* data) { p = (T*)data; s = uint32_t(sizeof(T)); }
			inline void init(uint32_t vertex_format, VertexAttribute::Enum attr, void* data)
			{
				if((vertex_format & attr) != 0) this->init(data);
			}
			inline void init(uint32_t vertex_format, VertexAttribute::Enum attr, void* data, uint32_t stride)
			{
				if((vertex_format & attr) != 0)
					p = (T*)((char*)data + vertex_offset(vertex_format, attr));
				s = stride;
			}
			inline void next() { p = (T*)((char*)p + s); }
			inline void write(const T& val) { *p = val; this->next(); }
			inline T read() { T val = *p; this->next(); return val; }
			inline operator bool() { return p != nullptr; }
		};

		struct Pointers
		{
			Cursor<uint16_t> m_index;
			Cursor<uint32_t> m_index32;

			Cursor<vec3> m_position;
			Cursor<vec4> m_position4;
			Cursor<vec3> m_normal;
			Cursor<uint32_t> m_colour;
			Cursor<vec4> m_tangent;
			Cursor<vec3> m_bitangent;
			Cursor<vec2> m_uv0;
			Cursor<vec2> m_uv1;
			Cursor<uint32_t> m_joints;
			Cursor<vec4> m_weights;

			Cursor<half3> m_qposition;
			Cursor<uint32_t> m_qnormal;
			Cursor<uint32_t> m_qtangent;
			Cursor<half2> m_quv0;
			Cursor<half2> m_quv1;
		};

		Pointers m_start;
		Pointers m_cursor;

		//void* m_index = nullptr;

		uint32_t m_vertex = 0;
		uint32_t m_offset = 0;

		template <class T>
		struct Bounds { T lo = T(FLT_MAX); T hi = T(-FLT_MAX); void add(const T& val) { lo = min(val, lo); hi = max(val, hi); } };
		Bounds<vec3> m_aabb = {};
		Bounds<vec2> m_uv0_rect = {};
		Bounds<vec2> m_uv1_rect = {};

		meth_ void rewind();
		meth_ void copy(MeshAdapter& dest);
		meth_ void xcopy(MeshAdapter& dest, const mat4& transform);
		meth_ void next();

		MeshAdapter read() const;

		meth_ MeshAdapter& position(const vec3& p);
		meth_ MeshAdapter& position4(const vec4& p);
		meth_ MeshAdapter& normal(const vec3& n);
		meth_ MeshAdapter& colour(const Colour& c);
		meth_ MeshAdapter& tangent(const vec4& t);
		meth_ MeshAdapter& bitangent(const vec3& b);
		meth_ MeshAdapter& uv0(const vec2& uv);
		meth_ MeshAdapter& uv1(const vec2& uv);
		meth_ MeshAdapter& joints(const uint32_t& j);
		meth_ MeshAdapter& weights(const vec4& w);

		MeshAdapter& colour(const vec3& c);

		// direct functions (faster, no bounds computation)
		MeshAdapter& dposition(const vec3& p);
		MeshAdapter& duv0(const vec2& uv);
		MeshAdapter& duv1(const vec2& uv);

		vec3 position();
		vec3 normal();
		Colour colour();
		vec4 tangent();
		vec3 bitangent();
		vec2 uv0();
		vec2 uv1();
		uint32_t joints();
		vec4 weights();
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
