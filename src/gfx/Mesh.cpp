//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <infra/Vector.h>
#include <geom/Mesh.h>
#include <gfx/Mesh.h>
#include <gfx/Node3.h>
#endif

#include <map>

namespace mud
{
	bgfx::VertexDecl create_vertex_decl(size_t vertex_format)
	{
		bgfx::VertexDecl decl;

		bool normalize_indices = false;
#ifdef MUD_PLATFORM_EMSCRIPTEN
		normalize_indices = true;
#endif

		decl.begin();
		if((vertex_format & VertexAttribute::Position) != 0)
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::Normal) != 0)
			decl.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::Colour) != 0)
			decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
		if((vertex_format & VertexAttribute::Tangent) != 0)
			decl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::Bitangent) != 0)
			decl.add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::TexCoord0) != 0)
			decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::TexCoord1) != 0)
			decl.add(bgfx::Attrib::TexCoord1, 2, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::Joints) != 0)
			decl.add(bgfx::Attrib::Indices, 4, bgfx::AttribType::Uint8, normalize_indices);
		if((vertex_format & VertexAttribute::Weights) != 0)
			decl.add(bgfx::Attrib::Weight, 4, bgfx::AttribType::Float);
		decl.end();

		return decl;
	}

	const bgfx::VertexDecl& vertex_decl(size_t vertex_format)
	{
		static std::map<size_t, bgfx::VertexDecl> decls;
		if(decls.find(vertex_format) == decls.end())
			decls[vertex_format] = create_vertex_decl(vertex_format);
		return decls[vertex_format];
	}

	static uint16_t s_mesh_index = 0;

	Mesh::Mesh(cstring name, bool readback)
		: m_name(name)
		, m_index(++s_mesh_index)
		, m_readback(readback)
		//, m_material(&gfx_system.debug_material())
		, m_material(nullptr)
	{}

	Mesh::~Mesh()
	{
		if(bgfx::isValid(m_vertex_buffer))
			bgfx::destroy(m_vertex_buffer);
		if(bgfx::isValid(m_index_buffer))
			bgfx::destroy(m_index_buffer);
	}

	void Mesh::read(MeshData& dest, const mat4& transform) const
	{
		MeshData source = m_cache;

		for(size_t i = 0; i < source.m_vertices.size(); ++i)
		{
			vec3 vec = bxmul(transform, source.position());
			dest.position(vec);
		}

		for(size_t i = 0; i < source.m_indices.size(); ++i)
		{
			dest.index(source.index());
		}

		dest.next();
	}

	void Mesh::upload(DrawMode draw_mode, const GpuMesh& gpu_mesh)
	{
		m_draw_mode = draw_mode;
		m_vertex_count = gpu_mesh.m_vertex_count;
		m_index_count = gpu_mesh.m_index_count;

		m_vertex_buffer = bgfx::createVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
		m_index_buffer = bgfx::createIndexBuffer(gpu_mesh.m_index_memory);//, BGFX_BUFFER_INDEX32);

		MeshData data = gpu_mesh.m_data;

		for(size_t i = 0; i < data.m_vertices.size(); ++i)
			m_aabb.merge(data.position());

		data = gpu_mesh.m_data;

		for(size_t i = 0; i < data.m_vertices.size(); ++i)
			m_radius = max(length(data.position() - m_aabb.m_center), m_radius);

		m_origin = m_aabb.m_center;
	}

	void Mesh::write(DrawMode draw_mode, array<ShapeVertex> vertices, array<ShapeIndex> indices)
	{
		GpuMesh gpu_mesh = alloc_mesh<ShapeVertex, ShapeIndex>(vertices.m_count, indices.m_count);
		vertices.copy(gpu_mesh.vertices<ShapeVertex>());
		indices.copy(gpu_mesh.indices<ShapeIndex>());
		this->upload(draw_mode, gpu_mesh);
		if(m_readback)
			this->cache<ShapeVertex, ShapeIndex>(gpu_mesh);
	}

	void Mesh::write(DrawMode draw_mode, MeshPacker& packer)
	{
		GpuMesh gpu_mesh = alloc_mesh(packer.vertex_format(), packer.vertex_count(), packer.index_count());
		MeshData data = gpu_mesh.m_data;
		packer.pack_vertices(data, bxidentity());
		this->upload(draw_mode, gpu_mesh);
		if(m_readback)
		{
			this->cache(gpu_mesh);
			m_cache = MeshData(packer.vertex_format(), m_cached_vertices.data(), m_vertex_count, m_cached_indices.data(), m_index_count);
		}
	}

	void Mesh::cache(const GpuMesh& gpu_mesh)
	{
		m_cached_vertices.resize(gpu_mesh.m_vertex_memory->size);
		m_cached_indices.resize(gpu_mesh.m_index_memory->size);

		memcpy(m_cached_vertices.data(), gpu_mesh.m_vertex_memory->data, gpu_mesh.m_vertex_memory->size);
		memcpy(m_cached_indices.data(), gpu_mesh.m_index_memory->data, gpu_mesh.m_index_memory->size);
	}

	uint64_t Mesh::submit(bgfx::Encoder& encoder) const
	{
		encoder.setVertexBuffer(0, m_vertex_buffer);
		encoder.setIndexBuffer(m_index_buffer);
		return m_draw_mode == PLAIN ? 0 : (BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA);
	}
}
