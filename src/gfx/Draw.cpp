//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>
#ifndef MUD_CPP_20
#include <array>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <refl/Convert.h>
#include <refl/Meta.h>
#include <srlz/Serial.h>
#include <infra/StringConvert.h>
#include <geom/Mesh.h>
#include <geom/Shape/ProcShape.h>
#include <gfx/Types.h>
#include <gfx/Draw.h>
#include <gfx/GfxSystem.h>
#include <gfx/Material.h>
#include <gfx/Program.h>
#include <gfx/Node3.h>
#include <gfx/Model.h>
#endif

namespace mud
{
	void shapes_size(array<const ProcShape> shapes, DrawMode draw_mode, ShapeSize& size, size_t& count)
	{
		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				size.vec += draw_mode == PLAIN ? symbol_triangle_size(shape).vec
											   : symbol_line_size(shape).vec;
				count++;
			}
	}

	void shapes_size(array<const ProcShape> shapes, array<ShapeSize> size, size_t& count)
	{
		shapes_size(shapes, PLAIN, size[PLAIN], count);
		shapes_size(shapes, OUTLINE, size[OUTLINE], count);
	}

	ImmediateDraw::ImmediateDraw(Material& material)
		: m_material(material)
		, m_cursor{ 0, 0 }
	{
		m_material.m_unshaded_block.m_enabled = true;

		m_batches[PLAIN].resize(64);
		m_batches[OUTLINE].resize(64);

		ms_vertex_decl = vertex_decl(VertexAttribute::Position | VertexAttribute::Colour);
	}

	inline bool checkAvailTransientBuffers(uint32_t _numVertices, const bgfx::VertexDecl& _decl, uint32_t _numIndices)
	{
		return _numVertices == bgfx::getAvailTransientVertexBuffer(_numVertices, _decl)
			&& _numIndices == bgfx::getAvailTransientIndexBuffer(_numIndices);
	}

	void ImmediateDraw::begin()
	{
		DrawMode draw_modes[2] = { PLAIN, OUTLINE };
		for(DrawMode draw_mode : draw_modes)
			for(Batch& batch : m_batches[draw_mode])
			{
				batch.m_vertices.clear();
				batch.m_indices.clear();
			}
	}

	void ImmediateDraw::draw(const mat4& transform, const ProcShape& shape)
	{
		this->draw(transform, carray<ProcShape, 1>{ shape });
	}

	void ImmediateDraw::draw(const mat4& transform, array<ProcShape> shapes)
	{
		ShapeSize size[2] = { { 0, 0 }, { 0, 0 } };
		size_t shape_count = 0;

		shapes_size(shapes, { size, 2 }, shape_count);

		if(size[PLAIN].vertex_count)
			this->draw(transform, shapes, size[PLAIN], PLAIN);
		if(size[OUTLINE].vertex_count)
			this->draw(transform, shapes, size[OUTLINE], OUTLINE);
	}

	void ImmediateDraw::draw(const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode)
	{
		size_t& cursor = m_cursor[draw_mode];
		if(m_batches[draw_mode][cursor].m_vertices.size() + size.vertex_count > UINT16_MAX)
			cursor++;
		if(cursor > m_batches[draw_mode].size())
			return;
		this->draw(m_batches[draw_mode][cursor], transform, shapes, size, draw_mode);
	}

	void ImmediateDraw::draw(Batch& batch, const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode)
	{
		size_t vertex_offset = batch.m_vertices.size();
		size_t index_offset = batch.m_indices.size();

		batch.m_vertices.resize(batch.m_vertices.size() + size.vertex_count);
		batch.m_indices.resize(batch.m_indices.size() + size.index_count);

		array<Vertex> vertices = { &batch.m_vertices[vertex_offset], size_t(size.vertex_count) };
		array<uint16_t> indices = { &batch.m_indices[index_offset], size_t(size.index_count) };

		MeshData data(vertices, indices);
		data.m_offset = uint32_t(vertex_offset);

		for(const ProcShape& shape : shapes)
		{
			draw_mode == OUTLINE ? symbol_draw_lines(shape, data)
								 : symbol_draw_triangles(shape, data);
			data.next();
		}

		for(size_t i = vertex_offset; i < batch.m_vertices.size(); ++i)
		{
			batch.m_vertices[i].m_position = vec3(transform * vec4(batch.m_vertices[i].m_position, 1.f));
		}
	}

	void ImmediateDraw::submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state)
	{
		this->submit(encoder, view, bgfx_state, PLAIN);
		this->submit(encoder, view, bgfx_state, OUTLINE);
	}

	void ImmediateDraw::submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode)
	{
		for(Batch& batch : m_batches[draw_mode])
			this->submit(encoder, view, bgfx_state, draw_mode, batch);
		m_cursor[draw_mode] = 0;
	}

	void ImmediateDraw::submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode, Batch& batch)
	{
		if(batch.m_vertices.empty())
			return;

		if(!checkAvailTransientBuffers(batch.m_vertices.size(), ms_vertex_decl, batch.m_indices.size()))
			return;

		bgfx::TransientVertexBuffer vertex_buffer;
		bgfx::allocTransientVertexBuffer(&vertex_buffer, batch.m_vertices.size(), ms_vertex_decl);
		bx::memCopy(vertex_buffer.data, batch.m_vertices.data(), batch.m_vertices.size() * sizeof(Vertex));//ms_vertex_decl.m_stride);

		bgfx::TransientIndexBuffer index_buffer;
		bgfx::allocTransientIndexBuffer(&index_buffer, batch.m_indices.size());
		bx::memCopy(index_buffer.data, batch.m_indices.data(), batch.m_indices.size() * sizeof(uint16_t));

		m_material.submit(encoder, bgfx_state);

		encoder.setVertexBuffer(0, &vertex_buffer);
		encoder.setIndexBuffer(&index_buffer);
		encoder.setState(draw_mode == OUTLINE ? bgfx_state | BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA : bgfx_state);

		mat4 identity = bxidentity();
		encoder.setTransform(value_ptr(identity));

		encoder.submit(view, m_material.m_program->default_version());
	}

	bgfx::VertexDecl ImmediateDraw::ms_vertex_decl;

	SymbolIndex::SymbolIndex()
	{}

	SymbolIndex::~SymbolIndex()
	{}

	uint64_t hash_symbol(const Symbol& symbol, DrawMode draw_mode)
	{
		return uint64_t(symbol.m_detail) | uint64_t(draw_mode << 16);
	}

	uint64_t hash_symbol_material(const Symbol& symbol, DrawMode draw_mode)
	{
		return draw_mode == PLAIN ? uint64_t(to_abgr(symbol.m_fill)) | uint64_t(symbol.m_overlay) << 32 | uint64_t(symbol.m_double_sided) << 33
								  : uint64_t(to_abgr(symbol.m_outline)) | uint64_t(symbol.m_overlay) << 32 | uint64_t(symbol.m_double_sided) << 33;
	}

	Material& SymbolIndex::symbol_material(GfxSystem& gfx_system, const Symbol& symbol, DrawMode draw_mode)
	{
		Colour colour = draw_mode == PLAIN ? symbol.m_fill : symbol.m_outline;

		uint64_t hash = hash_symbol_material(symbol, draw_mode);
		if(m_materials[hash] == nullptr)
		{
			m_materials[hash] = &gfx_system.fetch_material(("Symbol" + to_string(hash)).c_str(), "unshaded");
			m_materials[hash]->m_base_block.m_depth_test = symbol.m_overlay ? DepthTest::Disabled : DepthTest::Enabled;
			m_materials[hash]->m_base_block.m_cull_mode = symbol.m_double_sided ? CullMode::None : CullMode::Back;
			m_materials[hash]->m_unshaded_block.m_enabled = true;
			m_materials[hash]->m_unshaded_block.m_colour.m_value = colour;
		}
		return *m_materials[hash];
	}

	Model& SymbolIndex::symbol_model(const Symbol& symbol, const Shape& shape, DrawMode draw_mode)
	{
		uint64_t hash = hash_symbol(symbol, draw_mode);
		std::array<char, c_max_shape_size> shape_mem = {};
		std::memcpy(&shape_mem[0], (void*) &shape, meta(shape.m_type).m_size);

		if(m_symbols[hash][shape_mem] == nullptr)
		{
			printf("INFO: created indexed Shape %s %s\n", shape.m_type.m_name, pack_json(Ref(&shape)).c_str());
			string name = "Shape:" + string(meta(shape.m_type).m_name);
			m_symbols[hash][shape_mem] = draw_model(name.c_str(), ProcShape{ symbol, &shape, draw_mode });
		}

		return *m_symbols[hash][shape_mem];
	}

	object_ptr<Model> draw_model(cstring id, const ProcShape& shape, bool readback)
	{
		return draw_model(id, std::vector<ProcShape>{ { shape } }, readback);
	}

	object_ptr<Model> draw_model(cstring id, const std::vector<ProcShape>& shapes, bool readback)
	{
		object_ptr<Model> model = make_object<Model>(id);
		draw_model(shapes, *model, readback);
		return model;
	}

	void draw_model(const ProcShape& shape, Model& model, bool readback, Material* material)
	{
		draw_model(std::vector<ProcShape>{ { shape } }, model, readback, material);
	}

	void draw_model(const std::vector<ProcShape>& shapes, Model& model, bool readback, Material* material)
	{
		ShapeSize size[2] = { { 0, 0 }, { 0, 0 } };
		size_t shape_count = 0;

		shapes_size(shapes, { size, 2 }, shape_count);

		if(size[PLAIN].vertex_count)
			draw_mesh(shapes, model, size[PLAIN], PLAIN, readback, material);
		if(size[OUTLINE].vertex_count)
			draw_mesh(shapes, model, size[OUTLINE], OUTLINE, readback, material);

		model.prepare();
	}

	void draw_mesh(const ProcShape& shape, Model& model, DrawMode draw_mode, bool readback, Material* material)
	{
		draw_mesh(std::vector<ProcShape>{ { shape } }, model, draw_mode, readback, material);
	}

	void draw_mesh(const std::vector<ProcShape>& shapes, Model& model, DrawMode draw_mode, bool readback, Material* material)
	{
		ShapeSize size = { 0, 0 };
		size_t shape_count = 0;

		shapes_size(shapes, draw_mode, size, shape_count);
		draw_mesh(shapes, model, size, draw_mode, readback, material);
	}

	void draw_mesh(const std::vector<ProcShape>& shapes, Model& model, ShapeSize size, DrawMode draw_mode, bool readback, Material* material)
	{
		Mesh& mesh = model.add_mesh((model.m_name + to_string(draw_mode)).c_str(), readback);
		mesh.m_material = material;

		GpuMesh gpu_mesh = alloc_mesh<ShapeVertex, ShapeIndex>(size.vertex_count, size.index_count);
		
		MeshData data = gpu_mesh.m_data;

		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				draw_mode == OUTLINE ? symbol_draw_lines(shape, data)
									 : symbol_draw_triangles(shape, data);
				data.next();
			}

		if(draw_mode == PLAIN)
			generate_mikkt_tangents(gpu_mesh.indices<ShapeIndex>(), gpu_mesh.vertices<ShapeVertex>());

		mesh.upload(draw_mode, gpu_mesh);
		if(readback)
			mesh.cache<ShapeVertex, ShapeIndex>(gpu_mesh);

		model.add_item(bxidentity(), mesh);
	}
}
