//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <stl/span.h>
#include <math/Vec.h>
#include <geom/Primitive.h>
#include <geom/Aabb.h>
#endif
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

namespace mud
{
	export_ struct MUD_GFX_EXPORT GpuMesh
	{
		GpuMesh() {}
		GpuMesh(uint32_t vertex_count, uint32_t index_count)
			: m_vertex_count(vertex_count), m_index_count(index_count)
		{}

		uint32_t m_vertex_format = 0;
		
		uint32_t m_vertex_count = 0;
		uint32_t m_index_count = 0;
		bool m_index32 = false;

		const bgfx::Memory* m_vertex_memory = nullptr;
		const bgfx::Memory* m_index_memory = nullptr;

		void* m_vertices = nullptr;
		void* m_indices = nullptr;

		MeshAdapter m_writer = {};
	};
	
	export_ MUD_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

	export_ MUD_GFX_EXPORT GpuMesh alloc_mesh(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count, bool index32);
	export_ MUD_GFX_EXPORT GpuMesh alloc_mesh(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count);

	export_ class refl_ MUD_GFX_EXPORT Mesh
	{
	public:
		Mesh(const string& name, bool readback = false);
		~Mesh();

		Mesh(Mesh&& other) = default;
		Mesh& operator=(Mesh&& other) = default;

		attr_ string m_name;
		attr_ uint16_t m_index;
		attr_ DrawMode m_draw_mode = PLAIN;
		attr_ Aabb m_aabb = {};
		attr_ float m_radius = 0.f;
		attr_ vec3 m_origin = vec3(0.f);
		attr_ bool m_readback = false;

		attr_ uint32_t m_vertex_format = 0;
		attr_ bool m_qnormals = false;

		attr_ uint32_t m_vertex_count = 0;
		attr_ uint32_t m_index_count = 0;
		attr_ bool m_index32 = false;

		attr_ Material* m_material = nullptr;

		bgfx::VertexBufferHandle m_vertex_buffer = BGFX_INVALID_HANDLE;
		bgfx::IndexBufferHandle m_index_buffer = BGFX_INVALID_HANDLE;

		struct UvBounds { vec2 min; vec2 max; };
		UvBounds m_uv0_rect = {};
		UvBounds m_uv1_rect = {};

		vector<uint8_t> m_cached_vertices;
		vector<uint8_t> m_cached_indices;

		MeshAdapter m_cache;

		void clear();
		void read(MeshAdapter& writer, const mat4& transform) const;
		void read(MeshPacker& packer, const mat4& transform) const;
		void write(DrawMode draw_mode, MeshPacker& packer, bool optimize = false);
		void upload(DrawMode draw_mode, const GpuMesh& gpu_mesh);
		void upload_opt(DrawMode draw_mode, const GpuMesh& gpu_mesh);
		void cache(const GpuMesh& gpu_mesh);
		
		uint64_t submit(bgfx::Encoder& encoder) const;
	};
}
