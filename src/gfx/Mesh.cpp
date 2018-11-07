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

#include <meshoptimizer.h>

namespace mud
{
	bgfx::VertexDecl create_vertex_decl(uint32_t vertex_format)
	{
		bgfx::VertexDecl decl;

		bool half_support = (bgfx::getCaps()->supported & BGFX_CAPS_VERTEX_ATTRIB_HALF) != 0;
		bool needs_half = (vertex_format & VertexAttribute::QTexCoord0) != 0
					   || (vertex_format & VertexAttribute::QTexCoord1) != 0;
		if(needs_half && !half_support)
			printf("WARNING: half vertex attribute not supported but used by texcoords\n");

		bool normalize_indices = false;
#ifdef MUD_PLATFORM_EMSCRIPTEN
		normalize_indices = true;
#endif

		decl.begin();

		if((vertex_format & VertexAttribute::Position) != 0)
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QPosition) != 0)
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Half);
		if((vertex_format & VertexAttribute::Normal) != 0)
			decl.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QNormal) != 0)
			decl.add(bgfx::Attrib::Normal, 4, bgfx::AttribType::Uint8);
		if((vertex_format & VertexAttribute::Colour) != 0)
			decl.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true);
		if((vertex_format & VertexAttribute::Tangent) != 0)
			decl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QTangent) != 0)
			decl.add(bgfx::Attrib::Tangent, 4, bgfx::AttribType::Uint8);
		if((vertex_format & VertexAttribute::Bitangent) != 0)
			decl.add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::TexCoord0) != 0)
			decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QTexCoord0) != 0)
			decl.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Half);
		if((vertex_format & VertexAttribute::TexCoord1) != 0)
			decl.add(bgfx::Attrib::TexCoord1, 2, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::QTexCoord1) != 0)
			decl.add(bgfx::Attrib::TexCoord1, 2, bgfx::AttribType::Half);
		if((vertex_format & VertexAttribute::Joints) != 0)
			decl.add(bgfx::Attrib::Indices, 4, bgfx::AttribType::Uint8, normalize_indices);
		if((vertex_format & VertexAttribute::Weights) != 0)
			decl.add(bgfx::Attrib::Weight, 4, bgfx::AttribType::Float);

		decl.end();

		return decl;
	}

	const bgfx::VertexDecl& vertex_decl(uint32_t vertex_format)
	{
		static std::map<uint32_t, bgfx::VertexDecl> decls;
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
		this->clear();
	}

	void Mesh::clear()
	{
		if(bgfx::isValid(m_vertex_buffer))
			bgfx::destroy(m_vertex_buffer);
		if(bgfx::isValid(m_index_buffer))
			bgfx::destroy(m_index_buffer);
	}

	void Mesh::read(MeshAdapter& writer, const mat4& transform) const
	{
		MeshAdapter reader = m_cache.read();

		for(size_t i = 0; i < reader.m_vertices.size(); ++i)
		{
			writer.position(transform * vec4(reader.position(), 1.f));
			if(writer.m_cursor.m_normal)
				writer.normal(transform * vec4(reader.normal(), 0.f));
			if(writer.m_cursor.m_uv0)
				writer.uv0(reader.uv0());
		}

		for(size_t i = 0; i < reader.m_indices.size(); ++i)
		{
			uint32_t index = m_index32 ? reader.index32() : reader.index();
			assert(index <= writer.m_vertices.size());
			writer.index(index);
		}

		writer.next();
	}

	inline vec3 mulp(const mat4& mat, const vec3& p) { return vec3(mat * vec4(p, 1.f)); }
	inline vec3 muln(const mat4& mat, const vec3& n) { return normalize(vec3(mat * vec4(n, 0.f))); }
	inline vec4 mult(const mat4& mat, const vec4& t) { return vec4(vec3(mat * vec4(vec3(t), 0.f)), t.w); }

	void Mesh::read(MeshPacker& packer, const mat4& transform) const
	{
		MeshAdapter reader = m_cache.read();

		for(size_t i = 0; i < reader.m_vertices.size(); ++i)
		{
			packer.m_positions.push_back(mulp(transform, reader.position()));
			if((m_vertex_format & VertexAttribute::Normal) != 0)
				packer.m_normals.push_back(muln(transform, reader.normal()));
			if((m_vertex_format & VertexAttribute::Colour) != 0)
				packer.m_colours.push_back(reader.colour());
			if((m_vertex_format & VertexAttribute::Tangent) != 0)
				packer.m_tangents.push_back(mult(transform, reader.tangent()));
			if((m_vertex_format & VertexAttribute::TexCoord0) != 0)
				packer.m_uv0s.push_back(reader.uv0());
			if((m_vertex_format & VertexAttribute::TexCoord1) != 0)
				packer.m_uv1s.push_back(reader.uv1());
			//packer.m_bones.push_back(source.bones());
			//packer.m_weights.push_back(source.weights());
		}

		for(size_t i = 0; i < reader.m_indices.size(); ++i)
		{
			packer.m_indices.push_back(m_index32 ? reader.index32() : reader.index());
		}
	}

	void Mesh::upload(DrawMode draw_mode, const GpuMesh& gpu_mesh)
	{
		this->clear();

		m_draw_mode = draw_mode;
		m_vertex_format = gpu_mesh.m_vertex_format;
		m_vertex_count = gpu_mesh.m_vertex_count;
		m_index_count = gpu_mesh.m_index_count;
		m_index32 = gpu_mesh.m_index32;

		m_vertex_buffer = bgfx::createVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
		m_index_buffer = bgfx::createIndexBuffer(gpu_mesh.m_index_memory, m_index32 ? BGFX_BUFFER_INDEX32 : 0);

		m_aabb = aabb(gpu_mesh.m_writer.m_aabb.lo, gpu_mesh.m_writer.m_aabb.hi);
		m_uv0_rect = { gpu_mesh.m_writer.m_uv0_rect.lo, gpu_mesh.m_writer.m_uv0_rect.hi };
		m_uv1_rect = { gpu_mesh.m_writer.m_uv1_rect.lo, gpu_mesh.m_writer.m_uv1_rect.hi };

		MeshAdapter reader = gpu_mesh.m_writer.read();
		m_radius = 0.f;
		for(size_t i = 0; i < reader.m_vertices.size(); ++i)
			m_radius = max(length(reader.position() - m_aabb.m_center), m_radius);

		m_origin = m_aabb.m_center;

		if(m_readback)
			this->cache(gpu_mesh);
	}

	template <class T>
	void optimize(const GpuMesh& mesh, GpuMesh& optmesh)
	{
		size_t vertex_stride = vertex_size(mesh.m_vertex_format);

		std::vector<unsigned int> remap(mesh.m_vertex_count);
		uint32_t index_count = mesh.m_index_count;
		size_t vertex_count = meshopt_generateVertexRemap(remap.data(), (T*)mesh.m_indices, index_count, mesh.m_vertices, mesh.m_vertex_count, vertex_stride);

		// we can't allocate a new mesh with different index size because meshoptimizer remap functions don't allow for different types of indices
		optmesh = alloc_mesh(mesh.m_vertex_format, uint32_t(vertex_count), index_count, mesh.m_index32);

		meshopt_remapIndexBuffer((T*)optmesh.m_indices, (T*)mesh.m_indices, index_count, remap.data());

		meshopt_remapVertexBuffer(optmesh.m_vertices, mesh.m_vertices, mesh.m_vertex_count, vertex_stride, remap.data());

		meshopt_optimizeVertexCache((T*)optmesh.m_indices, (T*)optmesh.m_indices, index_count, vertex_count);

		meshopt_optimizeOverdraw((T*)optmesh.m_indices, (T*)optmesh.m_indices, index_count, (float*)optmesh.m_vertices, vertex_count, vertex_stride, 1.05f);

		meshopt_optimizeVertexFetch(optmesh.m_vertices, (T*)optmesh.m_indices, index_count, optmesh.m_vertices, vertex_count, vertex_stride);

		//meshopt_simplify(optmesh.m_indices, optmesh.m_indices, index_count, optmesh.m_vertices, vertex_count, vertex_stride);
	}

	void Mesh::upload_opt(DrawMode draw_mode, const GpuMesh& mesh)
	{
		GpuMesh optmesh;

		if(mesh.m_index32)
			optimize<uint32_t>(mesh, optmesh);
		else
			optimize<uint16_t>(mesh, optmesh);

		//printf("optimized mesh %s from %i to %i vertices\n", m_name.c_str(), mesh.m_vertex_count, optmesh.m_vertex_count);

		this->upload(draw_mode, optmesh);
	}

	void Mesh::write(DrawMode draw_mode, MeshPacker& packer, bool optimize)
	{
		m_qnormals = packer.m_quantize;

		GpuMesh gpu_mesh = alloc_mesh(packer.vertex_format(), packer.vertex_count(), packer.index_count());
		packer.pack_vertices(gpu_mesh.m_writer, bxidentity());
		gpu_mesh.m_writer.rewind();

		if(optimize)
			this->upload_opt(draw_mode, gpu_mesh);
		else
			this->upload(draw_mode, gpu_mesh);
	}

	void Mesh::cache(const GpuMesh& gpu_mesh)
	{
		m_cached_vertices.resize(gpu_mesh.m_vertex_memory->size);
		m_cached_indices.resize(gpu_mesh.m_index_memory->size);

		memcpy(m_cached_vertices.data(), gpu_mesh.m_vertex_memory->data, gpu_mesh.m_vertex_memory->size);
		memcpy(m_cached_indices.data(), gpu_mesh.m_index_memory->data, gpu_mesh.m_index_memory->size);

		m_cache = MeshAdapter(gpu_mesh.m_vertex_format, m_cached_vertices.data(), m_vertex_count, m_cached_indices.data(), m_index_count, m_index32);
		m_cache.rewind();
	}

	uint64_t Mesh::submit(bgfx::Encoder& encoder) const
	{
		encoder.setVertexBuffer(0, m_vertex_buffer);
		encoder.setIndexBuffer(m_index_buffer);
		return m_draw_mode == PLAIN ? 0 : (BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA);
	}
}
