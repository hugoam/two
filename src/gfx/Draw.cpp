//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <assert.h> // <cassert>
#include <stdint.h> // <cstdint>
#include <float.h> // <cfloat>
import std.core;
import std.memory;
#else
#include <array>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <obj/Reflect/Convert.h>
#include <obj/Reflect/Meta.h>
#include <obj/Serial/Serial.h>
#include <obj/String/StringConvert.h>
#include <geom/Mesh.h>
#include <geom/Shape/ProcShape.h>
#include <gfx/Generated/Types.h>
#include <gfx/Draw.h>
#include <gfx/GfxSystem.h>
#include <gfx/Material.h>
#include <gfx/Program.h>
#include <gfx/Node3.h>
#include <gfx/Model.h>
#endif

namespace mud
{
	void shapes_size(array<const ProcShape> shapes, array<ShapeSize> size, size_t& count)
	{
		for(const ProcShape& shape : shapes)
		{
			if(shape.m_draw_mode == PLAIN)
			{
				size[PLAIN].vec += symbol_triangle_size(shape).vec;
				count++;
			}

			if(shape.m_draw_mode == OUTLINE)
			{
				size[OUTLINE].vec += symbol_line_size(shape).vec;
				count++;
			}
		}
	}

	ImmediateDraw::ImmediateDraw(Material& material)
		: m_material(material)
	{
		m_material.m_unshaded_block.m_enabled = true;

		ms_vertex_decl = vertex_decl(VertexAttribute::Position | VertexAttribute::Colour);
	}

	inline bool checkAvailTransientBuffers(uint32_t _numVertices, const bgfx::VertexDecl& _decl, uint32_t _numIndices)
	{
		return _numVertices == bgfx::getAvailTransientVertexBuffer(_numVertices, _decl)
			&& _numIndices == bgfx::getAvailTransientIndexBuffer(_numIndices);
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
		size_t num_vertices = m_vertices[draw_mode].size();
		size_t num_indices = m_indices[draw_mode].size();

		m_vertices[draw_mode].resize(m_vertices[draw_mode].size() + size.vertex_count);
		m_indices[draw_mode].resize(m_indices[draw_mode].size() + size.index_count);

		MeshData data(m_vertices[draw_mode].data() + num_vertices, m_indices[draw_mode].data() + num_indices);
		data.m_offset = ShapeIndex(num_vertices);

		for(const ProcShape& shape : shapes)
		{
			draw_mode == OUTLINE ? symbol_draw_lines(shape, data)
								 : symbol_draw_triangles(shape, data);
			data.next();
		}

		for(size_t i = num_vertices; i < m_vertices[draw_mode].size(); ++i)
		{
			m_vertices[draw_mode][i].m_position = vec3(transform * vec4(m_vertices[draw_mode][i].m_position, 1.f));
		}
	}

	void ImmediateDraw::submit(uint8_t view, uint64_t bgfx_state)
	{
		this->submit(view, bgfx_state, PLAIN);
		this->submit(view, bgfx_state, OUTLINE);
	}

	void ImmediateDraw::submit(uint8_t view, uint64_t bgfx_state, DrawMode draw_mode)
	{
		if(m_vertices[draw_mode].empty())
			return;

		if(!checkAvailTransientBuffers(m_vertices[draw_mode].size(), ms_vertex_decl, m_indices[draw_mode].size()))
		{
			m_vertices[draw_mode].clear();
			m_indices[draw_mode].clear();
			return;
		}

		bgfx::TransientVertexBuffer vertex_buffer;
		bgfx::allocTransientVertexBuffer(&vertex_buffer, m_vertices[draw_mode].size(), ms_vertex_decl);
		bx::memCopy(vertex_buffer.data, m_vertices[draw_mode].data(), m_vertices[draw_mode].size() * sizeof(Vertex));//ms_vertex_decl.m_stride);

		bgfx::TransientIndexBuffer index_buffer;
		bgfx::allocTransientIndexBuffer(&index_buffer, m_indices[draw_mode].size());
		bx::memCopy(index_buffer.data, m_indices[draw_mode].data(), m_indices[draw_mode].size() * sizeof(ShapeIndex));

		m_material.submit(bgfx_state);

		bgfx::setVertexBuffer(0, &vertex_buffer);
		bgfx::setIndexBuffer(&index_buffer);
		bgfx::setState(draw_mode == OUTLINE ? bgfx_state | BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA : bgfx_state);
		mat4 identity = bxidentity();
		bgfx::setTransform(value_ptr(identity));
		bgfx::submit(view, m_material.m_program->default_version());

		m_vertices[draw_mode].clear();
		m_indices[draw_mode].clear();
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

	Material& SymbolIndex::symbolMaterial(GfxSystem& gfx_system, const Symbol& symbol, DrawMode draw_mode)
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

	Model& SymbolIndex::symbolModel(const Symbol& symbol, const Shape& shape, DrawMode draw_mode)
	{
		uint64_t hash = hash_symbol(symbol, draw_mode);
		std::array<char, MUD_MAX_SHAPE_SIZE> shape_mem = {};
		std::memcpy(&shape_mem[0], (void*) &shape, shape.m_type.m_meta->m_size);

		if(m_symbols[hash][shape_mem] == nullptr)
		{
			printf("INFO: created indexed Shape %s %s\n", shape.m_type.m_name, pack_json(Ref(&shape)).c_str());
			string name = "Shape:" + string(shape.m_type.m_meta->m_name);
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

	void draw_model(const ProcShape& shape, Model& model, bool readback)
	{
		draw_model(std::vector<ProcShape>{ { shape } }, model, readback);
	}

	void draw_model(const std::vector<ProcShape>& shapes, Model& model, bool readback)
	{
		ShapeSize size[2] = { { 0, 0 }, { 0, 0 } };
		size_t shape_count = 0;

		shapes_size(shapes, { size, 2 }, shape_count);

		model.m_meshes.reserve(shape_count);

		if(size[PLAIN].vertex_count)
			draw_mesh(shapes, model, size[PLAIN], PLAIN, readback);
		if(size[OUTLINE].vertex_count)
			draw_mesh(shapes, model, size[OUTLINE], OUTLINE, readback);

		model.prepare();
	}

	void draw_mesh(const std::vector<ProcShape>& shapes, Model& model, ShapeSize size, DrawMode draw_mode, bool readback)
	{
		Mesh& mesh = model.add_mesh(model.m_name, readback);

		GpuMesh gpu_mesh = mesh.allocate(draw_mode, size.vertex_count, size.index_count);
		MeshData data(gpu_mesh.m_vertices.m_pointer, gpu_mesh.m_indices.m_pointer);

		for(const ProcShape& shape : shapes)
		{
			draw_mode == OUTLINE ? symbol_draw_lines(shape, data)
								 : symbol_draw_triangles(shape, data);
			data.next();
		}

		generate_mikkt_tangents(gpu_mesh.m_indices, gpu_mesh.m_vertices);

		mesh.upload(gpu_mesh);

		model.m_items.emplace_back(ModelItem{ bxidentity(), &mesh, -1, Colour::White });
	}
}
