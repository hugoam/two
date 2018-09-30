//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#include <infra/Strung.h>
#include <math/Vec.h>
#include <geom/Primitive.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ struct MUD_GFX_EXPORT GpuMesh
	{
		GpuMesh() {}
		GpuMesh(uint32_t vertex_count, uint32_t index_count)
			: m_vertex_count(vertex_count), m_index_count(index_count)
		{}

		template <class T_Vertex, class T_Index>
		void init()
		{
			m_vertex_format = T_Vertex::vertex_format;
			m_data = MeshData(this->template vertices<T_Vertex>(), this->template indices<T_Index>());
		}

		uint32_t m_vertex_format = 0;
		
		uint32_t m_vertex_count = 0;
		uint32_t m_index_count = 0;

		const bgfx::Memory* m_vertex_memory = nullptr;
		const bgfx::Memory* m_index_memory = nullptr;

		MeshData m_data = {};

		template <class T_Vertex>
		inline array<T_Vertex> vertices() {	return { reinterpret_cast<T_Vertex*>(m_vertex_memory->data), m_vertex_count }; }

		template <class T_Index>
		inline array<T_Index> indices() { return { reinterpret_cast<T_Index*>(m_index_memory->data), m_index_count }; }
	};

	template <class T_Vertex, class T_Index>
	GpuMesh alloc_mesh(uint32_t vertex_count, uint32_t index_count)
	{
		GpuMesh gpu_mesh = { vertex_count, index_count };
		
		gpu_mesh.m_vertex_memory = bgfx::alloc(uint32_t(sizeof(T_Vertex) * vertex_count));
		gpu_mesh.m_index_memory = bgfx::alloc(uint32_t(sizeof(T_Index) * index_count));

		gpu_mesh.init<T_Vertex, T_Index>();

		return gpu_mesh;
	}
	
	inline GpuMesh alloc_mesh(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count)
	{
		GpuMesh gpu_mesh = { vertex_count, index_count };

		gpu_mesh.m_vertex_memory = bgfx::alloc(vertex_size(vertex_format) * vertex_count);
		gpu_mesh.m_index_memory = bgfx::alloc(sizeof(uint16_t) * index_count);

		gpu_mesh.m_vertex_format = vertex_format;
		gpu_mesh.m_data = MeshData(vertex_format, gpu_mesh.m_vertex_memory->data, vertex_count, gpu_mesh.m_index_memory->data, index_count);

		return gpu_mesh;
	}

	export_ class refl_ MUD_GFX_EXPORT Mesh
	{
	public:
		Mesh(cstring name, bool readback = false);
		~Mesh();

		Mesh(Mesh&& other) = default;
		Mesh& operator=(Mesh&& other) = default;

		attr_ string m_name;
		attr_ uint16_t m_index;
		attr_ DrawMode m_draw_mode = PLAIN;
		attr_ Aabb m_aabb = {};
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = Zero3;
		attr_ bool m_readback = false;

		attr_ uint32_t m_vertex_count = 0;
		attr_ uint32_t m_index_count = 0;

		attr_ Material* m_material = nullptr;

		bgfx::VertexBufferHandle m_vertex_buffer = BGFX_INVALID_HANDLE;
		bgfx::IndexBufferHandle m_index_buffer = BGFX_INVALID_HANDLE;

		std::vector<uint8_t> m_cached_vertices;
		std::vector<uint8_t> m_cached_indices;

		MeshData m_cache;

		void read(MeshData& data, const mat4& transform) const;
		void write(DrawMode draw_mode, array<ShapeVertex> vertices, array<ShapeIndex> indices);
		void write(DrawMode draw_mode, MeshPacker& packer);
		void upload(DrawMode draw_mode, const GpuMesh& gpu_mesh);
		void cache(const GpuMesh& gpu_mesh);

		uint64_t submit(bgfx::Encoder& encoder) const;

		template <class T_Vertex, class T_Index>
		void cache(const GpuMesh& gpu_mesh)
		{
			this->cache(gpu_mesh);
			m_cache = MeshData(array<T_Vertex>{ (T_Vertex*)m_cached_vertices.data(), m_vertex_count }, 
							   array<T_Index>{ (T_Index*)m_cached_indices.data(), m_index_count });
		}
	};
}
