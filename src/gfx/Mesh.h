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
	export_ struct refl_ MUD_GFX_EXPORT GpuMesh
	{
		GpuMesh();
		GpuMesh(PrimitiveType primitive, uint32_t vertex_count, uint32_t index_count);

		PrimitiveType m_primitive = PrimitiveType::Triangles;
		uint32_t m_vertex_format = 0;
		
		uint32_t m_vertex_count = 0;
		uint32_t m_index_count = 0;
		bool m_index32 = false;
		bool m_dynamic = false;

		const bgfx::Memory* m_vertex_memory = nullptr;
		const bgfx::Memory* m_index_memory = nullptr;

		span<void> m_vertices = {};
		span<void> m_indices = {};

		MeshAdapter m_writer = {};
	};
	
	export_ MUD_GFX_EXPORT const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format);

	export_ MUD_GFX_EXPORT GpuMesh alloc_mesh(PrimitiveType primitive, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count, bool index32);
	export_ MUD_GFX_EXPORT GpuMesh alloc_mesh(PrimitiveType primitive, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count);
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
		attr_ PrimitiveType m_primitive = PrimitiveType::Triangles;
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

		bgfx::VertexBufferHandle m_vertices = BGFX_INVALID_HANDLE;
		bgfx::IndexBufferHandle m_indices = BGFX_INVALID_HANDLE;

		struct Morph
		{
			bgfx::VertexBufferHandle m_vertices = BGFX_INVALID_HANDLE;
		};

		vector<Morph> m_morphs;

		attr_ bool m_is_dynamic = false;
		attr_ bool m_is_direct = false;

		struct Range { uint32_t m_start = 0U; uint32_t m_count = 0U; };
		Range m_range;

		struct Dynamic
		{
			bgfx::DynamicVertexBufferHandle m_vertices = BGFX_INVALID_HANDLE;
			bgfx::DynamicIndexBufferHandle m_indices = BGFX_INVALID_HANDLE;

		} m_dynamic;

		struct Direct
		{
			bgfx::TransientVertexBuffer m_vertices;
			bgfx::TransientIndexBuffer m_indices;
			MeshAdapter m_adapter;

		} m_direct;

		struct UvBounds { vec2 min; vec2 max; };
		UvBounds m_uv0_rect = {};
		UvBounds m_uv1_rect = {};

		vector<uint8_t> m_cached_vertices;
		vector<uint8_t> m_cached_indices;

		attr_ MeshAdapter m_cache;

		meth_ void clear();
		meth_ void write(const MeshPacker& packer, bool optimize = false, bool dynamic = false);
		meth_ void xwrite(const MeshPacker& packer, const mat4& transform, bool optimize = false, bool dynamic = false);
		meth_ void morph(const MeshPacker& packer);
		meth_ void upload(const GpuMesh& gpu_mesh, bool optimize = false);
		meth_ void cache(const GpuMesh& gpu_mesh);

		GpuMesh begin();
		void update(const GpuMesh& gpu_mesh);

		meth_ MeshAdapter& direct(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count = 0);

		uint64_t submit(bgfx::Encoder& encoder) const;

		void submit_morph(bgfx::Encoder& encoder, size_t index, size_t morph) const;
	};
}
