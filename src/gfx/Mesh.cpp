//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <cstdio>
#include <cstring>
#include <meshoptimizer.h>
#include <gfx/Cpp20.h>
module two.gfx;

namespace two
{
	bool normalize_bone_indices()
	{
#ifdef TWO_PLATFORM_EMSCRIPTEN
		return bgfx::getRendererType() == bgfx::RendererType::OpenGL;
#else
		return false;
#endif
	}

	bgfx::VertexLayout create_vertex_decl(uint32_t vertex_format)
	{
		bgfx::VertexLayout decl;

		bool half_support = (bgfx::getCaps()->supported & BGFX_CAPS_VERTEX_ATTRIB_HALF) != 0;
		bool needs_half = (vertex_format & VertexAttribute::QTexCoord0) != 0
					   || (vertex_format & VertexAttribute::QTexCoord1) != 0;
		if(needs_half && !half_support)
			warn("half vertex attribute not supported but used by texcoords");

		decl.begin();

		if((vertex_format & VertexAttribute::Position) != 0)
			decl.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float);
		if((vertex_format & VertexAttribute::Position4) != 0)
			decl.add(bgfx::Attrib::Position, 4, bgfx::AttribType::Float);
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
			decl.add(bgfx::Attrib::Indices, 4, bgfx::AttribType::Uint8, normalize_bone_indices());
		if((vertex_format & VertexAttribute::Weights) != 0)
			decl.add(bgfx::Attrib::Weight, 4, bgfx::AttribType::Float);
		
		decl.end();

		return decl;
	}

	const bgfx::VertexLayout& vertex_decl(uint32_t vertex_format)
	{
		static map<uint32_t, bgfx::VertexLayout> decls;
		if(decls.find(vertex_format) == decls.end())
			decls[vertex_format] = create_vertex_decl(vertex_format);
		return decls[vertex_format];
	}

	GpuMesh::GpuMesh() {}
	GpuMesh::GpuMesh(PrimitiveType primitive, uint32_t vertex_count, uint32_t index_count)
		: m_primitive(primitive), m_vertex_count(vertex_count), m_index_count(index_count)
	{}

	GpuMesh alloc_mesh(PrimitiveType primitive, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count, bool index32)
	{
		GpuMesh gpu_mesh = { primitive, vertex_count, index_count };

		gpu_mesh.m_vertex_memory = bgfx::alloc(vertex_count * vertex_size(vertex_format));
		if(index_count > 0)
			gpu_mesh.m_index_memory = bgfx::alloc(index_count * (index32 ? sizeof(uint32_t) : sizeof(uint16_t)));
		gpu_mesh.m_index32 = index32;

		gpu_mesh.m_vertices = { gpu_mesh.m_vertex_memory->data, vertex_count };
		if(index_count > 0)
			gpu_mesh.m_indices = { gpu_mesh.m_index_memory->data, index_count };

		gpu_mesh.m_vertex_format = vertex_format;
		gpu_mesh.m_writer = MeshAdapter(vertex_format, gpu_mesh.m_vertices, gpu_mesh.m_indices, index32);

		return gpu_mesh;
	}

	GpuMesh alloc_mesh(PrimitiveType primitive, uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count)
	{
		return alloc_mesh(primitive, vertex_format, vertex_count, index_count, vertex_count > UINT16_MAX);
	}

	GpuMesh alloc_mesh(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count)
	{
		return alloc_mesh(PrimitiveType::Triangles, vertex_format, vertex_count, index_count, vertex_count > UINT16_MAX);
	}

	template <class T>
	void optimize_mesh(const GpuMesh& mesh, GpuMesh& optmesh)
	{
		size_t vertex_stride = vertex_size(mesh.m_vertex_format);

		vector<unsigned int> remap(mesh.m_vertex_count);
		uint32_t index_count = mesh.m_index_count > 0 ? mesh.m_index_count : mesh.m_vertex_count;
		size_t vertex_count = meshopt_generateVertexRemap(remap.data(), (T*)mesh.m_indices.data(), index_count, mesh.m_vertices.data(), mesh.m_vertex_count, vertex_stride);

		// we can't allocate a new mesh with different index size because meshoptimizer remap functions don't allow for different types of indices
		optmesh = alloc_mesh(mesh.m_primitive, mesh.m_vertex_format, uint32_t(vertex_count), index_count, mesh.m_index32);

		optmesh.m_writer.m_aabb = mesh.m_writer.m_aabb;
		optmesh.m_writer.m_uv0_rect = mesh.m_writer.m_uv0_rect;
		optmesh.m_writer.m_uv1_rect = mesh.m_writer.m_uv1_rect;

		meshopt_remapIndexBuffer((T*)optmesh.m_indices.data(), (T*)mesh.m_indices.data(), index_count, remap.data());

		meshopt_remapVertexBuffer(optmesh.m_vertices.data(), mesh.m_vertices.data(), mesh.m_vertex_count, vertex_stride, remap.data());

		meshopt_optimizeVertexCache((T*)optmesh.m_indices.data(), (T*)optmesh.m_indices.data(), index_count, vertex_count);

		meshopt_optimizeOverdraw((T*)optmesh.m_indices.data(), (T*)optmesh.m_indices.data(), index_count, (float*)optmesh.m_vertices.data(), vertex_count, vertex_stride, 1.05f);

		meshopt_optimizeVertexFetch(optmesh.m_vertices.data(), (T*)optmesh.m_indices.data(), index_count, optmesh.m_vertices.data(), vertex_count, vertex_stride);

		//meshopt_simplify(optmesh.m_indices, optmesh.m_indices, index_count, optmesh.m_vertices, vertex_count, vertex_stride);
	}

	template <class T>
	GpuMesh optimize_mesh(const GpuMesh& mesh)
	{
		GpuMesh optmesh;
		optimize_mesh<T>(mesh, optmesh);
		return optmesh;
	}

	static uint16_t s_mesh_index = 0;

	Mesh::Mesh(const string& name, bool readback)
		: m_name(name)
		, m_index(++s_mesh_index)
		, m_readback(readback)
		, m_material(nullptr)
	{}

	Mesh::~Mesh()
	{
		this->clear();
	}

	void Mesh::clear()
	{
		if(m_is_dynamic)
		{
			if(bgfx::isValid(m_dynamic.m_vertices)) bgfx::destroy(m_dynamic.m_vertices);
			if(bgfx::isValid(m_dynamic.m_indices)) bgfx::destroy(m_dynamic.m_indices);
		}
		else
		{
			if(bgfx::isValid(m_vertices)) bgfx::destroy(m_vertices);
			if(bgfx::isValid(m_indices)) bgfx::destroy(m_indices);
		}
	}

	void Mesh::upload(const GpuMesh& gpu_mesh, bool optimize)
	{
		if(optimize)
		{
			if(gpu_mesh.m_index32)
				return this->upload(optimize_mesh<uint32_t>(gpu_mesh));
			else
				return this->upload(optimize_mesh<uint16_t>(gpu_mesh));
		}

		this->clear();

		m_primitive = gpu_mesh.m_primitive;
		//m_draw_mode = draw_mode;
		m_vertex_format = gpu_mesh.m_vertex_format;
		m_vertex_count = gpu_mesh.m_vertex_count;
		m_index_count = gpu_mesh.m_index_count;
		m_index32 = gpu_mesh.m_index32;
		m_is_dynamic = gpu_mesh.m_dynamic;

		if(gpu_mesh.m_dynamic)
		{
			m_dynamic.m_vertices = bgfx::createDynamicVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
			if(gpu_mesh.m_index_count > 0)
				m_dynamic.m_indices = bgfx::createDynamicIndexBuffer(gpu_mesh.m_index_memory, m_index32 ? BGFX_BUFFER_INDEX32 : 0);
		}
		else
		{
			m_vertices = bgfx::createVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
			if(gpu_mesh.m_index_count > 0)
				m_indices = bgfx::createIndexBuffer(gpu_mesh.m_index_memory, m_index32 ? BGFX_BUFFER_INDEX32 : 0);
		}

		m_aabb = aabb(gpu_mesh.m_writer.m_aabb.lo, gpu_mesh.m_writer.m_aabb.hi);
		m_uv0_rect = { gpu_mesh.m_writer.m_uv0_rect.lo, gpu_mesh.m_writer.m_uv0_rect.hi };
		m_uv1_rect = { gpu_mesh.m_writer.m_uv1_rect.lo, gpu_mesh.m_writer.m_uv1_rect.hi };

		if((gpu_mesh.m_vertex_format & VertexAttribute::Position) != 0)
		{
			MeshAdapter reader = gpu_mesh.m_writer.read();
			m_radius = 0.f;
			for(size_t i = 0; i < reader.m_vertex_count; ++i)
				m_radius = max(m_radius, length(reader.position() - m_aabb.m_center));
		}

		m_origin = m_aabb.m_center;

		if(m_readback)
			this->cache(gpu_mesh);
	}

	void Mesh::write(const MeshPacker& packer, bool optimize, bool dynamic)
	{
		m_qnormals = packer.m_quantize;

		GpuMesh gpu_mesh = alloc_mesh(packer.m_primitive, packer.vertex_format(), packer.vertex_count(), packer.index_count());
		packer.pack(gpu_mesh.m_writer);
		gpu_mesh.m_writer.rewind();
		gpu_mesh.m_dynamic = dynamic;

		this->upload(gpu_mesh, optimize);
	}

	void Mesh::xwrite(const MeshPacker& packer, const mat4& transform, bool optimize, bool dynamic)
	{
		m_qnormals = packer.m_quantize;

		GpuMesh gpu_mesh = alloc_mesh(packer.m_primitive, packer.vertex_format(), packer.vertex_count(), packer.index_count());
		packer.xpack(gpu_mesh.m_writer, transform);
		gpu_mesh.m_writer.rewind();
		gpu_mesh.m_dynamic = dynamic;

		this->upload(gpu_mesh, optimize);
	}

	void Mesh::morph(const MeshPacker& packer)
	{
		const uint32_t vertex_format = VertexAttribute::Position 
			| (!packer.m_normals.empty() ? VertexAttribute::Normal : 0);

		GpuMesh gpu_mesh = alloc_mesh(packer.m_primitive, vertex_format, packer.vertex_count(), packer.index_count());
		packer.pack(gpu_mesh.m_writer);

		Morph& morph = push(m_morphs);
		morph.m_vertices = bgfx::createVertexBuffer(gpu_mesh.m_vertex_memory, vertex_decl(gpu_mesh.m_vertex_format));
	}

	void Mesh::cache(const GpuMesh& gpu_mesh)
	{
		m_cached_vertices.resize(gpu_mesh.m_vertex_memory->size);
		if(gpu_mesh.m_index_count)
			m_cached_indices.resize(gpu_mesh.m_index_memory->size);

		memcpy(m_cached_vertices.data(), gpu_mesh.m_vertex_memory->data, gpu_mesh.m_vertex_memory->size);
		if(gpu_mesh.m_index_count)
			memcpy(m_cached_indices.data(), gpu_mesh.m_index_memory->data, gpu_mesh.m_index_memory->size);

		m_cache = MeshAdapter(gpu_mesh.m_vertex_format, { m_cached_vertices.data(), m_vertex_count }, { m_cached_indices.data(), m_index_count }, m_index32);
		m_cache.rewind();
	}

	GpuMesh Mesh::begin()
	{
		return alloc_mesh(m_primitive, m_vertex_format, m_vertex_count, m_index_count, m_index32);
	}

	void Mesh::update(const GpuMesh& gpu_mesh)
	{
		bgfx::update(m_dynamic.m_vertices, 0U, gpu_mesh.m_vertex_memory);
		if(gpu_mesh.m_index_count > 0)
			bgfx::update(m_dynamic.m_indices, 0U, gpu_mesh.m_index_memory);
	}

	MeshAdapter& Mesh::direct(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count)
	{
		m_vertex_format = vertex_format;
		m_vertex_count = vertex_count;
		m_index_count = index_count;

		const bgfx::VertexLayout& decl = vertex_decl(vertex_format);
		bgfx::allocTransientVertexBuffer(&m_direct.m_vertices, vertex_count, decl);
		if(index_count)
			bgfx::allocTransientIndexBuffer(&m_direct.m_indices, index_count);

		m_direct.m_adapter = { vertex_format, { m_direct.m_vertices.data, vertex_count } };
		return m_direct.m_adapter;
	}

	void Mesh::submit_morph(bgfx::Encoder& encoder, size_t index, size_t morph) const
	{
		static auto morph_decl = [](VertexAttribute::Enum attrib, bgfx::Attrib::Enum battrib)
		{
			UNUSED(attrib);
			bgfx::VertexLayout decl;
			decl.begin();
			decl.add(battrib, 3, bgfx::AttribType::Float);
			decl.end();
			return bgfx::createVertexLayout(decl);
		};

		static bgfx::VertexLayoutHandle morph_decls[4] =
		{
			morph_decl(VertexAttribute::MorphPosition0, bgfx::Attrib::TexCoord2),
			morph_decl(VertexAttribute::MorphPosition1, bgfx::Attrib::TexCoord3),
			morph_decl(VertexAttribute::MorphPosition2, bgfx::Attrib::TexCoord4),
			morph_decl(VertexAttribute::MorphPosition3, bgfx::Attrib::TexCoord5),
		};

		static bgfx::VertexLayoutHandle normal_decls[4] =
		{
			morph_decl(VertexAttribute::MorphNormal0, bgfx::Attrib::TexCoord6),
			morph_decl(VertexAttribute::MorphNormal1, bgfx::Attrib::TexCoord7),
			morph_decl(VertexAttribute::MorphNormal2, bgfx::Attrib::Color1),
			morph_decl(VertexAttribute::MorphNormal3, bgfx::Attrib::Color2),
		};

		encoder.setVertexBuffer(uint8_t(1 + index), m_morphs[morph].m_vertices, 0, m_vertex_count, morph_decls[index]);
	}

	uint64_t Mesh::submit(bgfx::Encoder& encoder) const
	{
		if(m_is_dynamic)
			encoder.setVertexBuffer(0, m_dynamic.m_vertices);
		else if(m_is_direct)
			encoder.setVertexBuffer(0, &m_direct.m_vertices);
		else
			encoder.setVertexBuffer(0, m_vertices);

		if(m_index_count > 0)
		{
			if(m_is_dynamic)
				encoder.setIndexBuffer(m_dynamic.m_indices, m_range.m_start, m_range.m_count);
			else if(m_is_direct)
				encoder.setIndexBuffer(&m_direct.m_indices);
			else
				encoder.setIndexBuffer(m_indices);
		}

		constexpr table<PrimitiveType, uint64_t> bgfx_primitive =
		{
			BGFX_STATE_PT_POINTS,
			BGFX_STATE_PT_LINES,
			BGFX_STATE_PT_LINESTRIP,
			0, // default,
			BGFX_STATE_PT_TRISTRIP,
			0, // unsupported
		};

		uint64_t flags = bgfx_primitive[m_primitive];
		// line aa needs blend mode to be alpha, and it looks ugly anyway (and only works in GL)
		//if(m_primitive == PrimitiveType::Lines || m_primitive == PrimitiveType::LineStrip)
		//	flags |= BGFX_STATE_LINEAA;
		return flags;
	}
}
