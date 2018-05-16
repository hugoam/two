//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <gfx/Mesh.h>

#include <geom/Shape/ProcShape.h>
#include <obj/Vector.h>

#include <gfx/Node3.h>
#include <gfx/Skeleton.h>

#include <bgfx/bgfx.h>

namespace mud
{
	bgfx::VertexDecl vertex_decl(size_t vertex_format)
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

	static uint16_t meshIndex = 0;
	static uint16_t modelIndex = 0;

	Mesh::Mesh(GfxSystem& gfx_system, cstring name, bool readback)
		: m_gfx_system(gfx_system)
		, m_name(name)
		, m_index(++meshIndex)
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

	void Mesh::read(MeshData& data, const mat4& transform) const
	{
		for(const ShapeVertex& vertex : m_vertices)
		{
			vec3 vec = bxmul(transform, vertex.m_position);
			data.position(vec);
		}

		for(size_t i = 0; i < m_indexCount; ++i)
			data.index(static_cast<ShapeIndex>(m_indices[i]));

		data.next();
	}

	GpuMesh Mesh::allocate(DrawMode draw_mode, size_t vertexCount, size_t indexCount)
	{
		m_draw_mode = draw_mode;
		m_vertexCount = vertexCount;
		m_indexCount = indexCount;

		GpuMesh gpu_mesh;

		gpu_mesh.m_vertex_memory = bgfx::alloc(sizeof(ShapeVertex) * vertexCount);
		gpu_mesh.m_index_memory = bgfx::alloc(sizeof(ShapeIndex) * indexCount);

		gpu_mesh.m_vertices = { reinterpret_cast<ShapeVertex*>(gpu_mesh.m_vertex_memory->data), vertexCount };
		gpu_mesh.m_indices = { reinterpret_cast<ShapeIndex*>(gpu_mesh.m_index_memory->data), indexCount };

		memset(gpu_mesh.m_vertices.m_pointer, 64, sizeof(ShapeVertex) * vertexCount);

		return gpu_mesh;
	}

	void Mesh::upload(const GpuMesh& gpu_mesh)
	{
		size_t vertex_format = VertexAttribute::Position | VertexAttribute::Colour | VertexAttribute::Normal | VertexAttribute::Tangent
							 | VertexAttribute::TexCoord0 | VertexAttribute::Joints | VertexAttribute::Weights;
		static bgfx::VertexDecl vertex_decl = mud::vertex_decl(vertex_format);

		m_vertex_buffer = bgfx::createVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl);
		m_index_buffer = bgfx::createIndexBuffer(gpu_mesh.m_index_memory);//, BGFX_BUFFER_INDEX32);

		for(const ShapeVertex& vertex : gpu_mesh.m_vertices)
			m_aabb.merge(vertex.m_position);

		for(const ShapeVertex& vertex : gpu_mesh.m_vertices)
			m_radius = max(length(vertex.m_position - m_aabb.m_center), m_radius);

		if(m_readback)
			this->conserve(gpu_mesh);
	}

	void Mesh::write(DrawMode draw_mode, array<ShapeVertex> vertices, array<ShapeIndex> indices)
	{
		GpuMesh gpu_mesh = this->allocate(draw_mode, vertices.m_count, indices.m_count);
		vertices.copy(gpu_mesh.m_vertices);
		indices.copy(gpu_mesh.m_indices);
		this->upload(gpu_mesh);
	}

	void Mesh::conserve(const GpuMesh& gpu_mesh)
	{
		m_vertices = to_vector(gpu_mesh.m_vertices);
		m_indices = to_vector(gpu_mesh.m_indices);
	}

	uint64_t Mesh::submit() const
	{
		bgfx::setVertexBuffer(0, m_vertex_buffer);
		bgfx::setIndexBuffer(m_index_buffer);
		return m_draw_mode == PLAIN ? 0 : (BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA);
	}

	Model::Model(GfxSystem& gfx_system, cstring id)
		: m_gfx_system(gfx_system)
		, m_name(id)
		, m_index(++modelIndex)
	{}

	Model::~Model()
	{}

	Mesh& Model::add_mesh(cstring name, bool readback)
	{
		m_meshes.emplace_back(m_gfx_system, name, readback);
		return m_meshes.back();
	}

	void Model::prepare()
	{
		m_aabb = { Zero3, Zero3 };
		m_radius = 0.f;

		for(Mesh& mesh : m_meshes)
		{
			m_geometry[mesh.m_draw_mode] = true;
			m_aabb.merge(mesh.m_aabb);
			m_radius = max(mesh.m_radius, m_radius);
		}
	}
}
