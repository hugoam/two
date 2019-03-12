//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>
#ifndef MUD_CPP_20
#include <array>
#include <map>
#include <cstring>
#endif

#ifdef MUD_MODULES
module mud.gfx;
#else
#include <infra/ToString.h>
#include <infra/Vector.h>
#include <math/Vec.hpp>
#include <geom/Geometry.h>
#include <geom/Curve.h>
#include <geom/Primitive.hpp>
#include <geom/Shape/ProcShape.h>
#include <gfx/Types.h>
#include <gfx/Draw.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx/Material.h>
#include <gfx/Program.h>
#include <gfx/Node3.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Item.h>
#endif

namespace mud
{
	void shapes_size(span<const ProcShape> shapes, DrawMode draw_mode, ShapeSize& size, size_t& count)
	{
		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				size.vec += draw_mode == PLAIN ? symbol_triangle_size(shape).vec
											   : symbol_line_size(shape).vec;
				count++;
			}
	}

	void shapes_size(span<const ProcShape> shapes, span<ShapeSize> size, size_t& count)
	{
		shapes_size(shapes, PLAIN, size[PLAIN], count);
		shapes_size(shapes, OUTLINE, size[OUTLINE], count);
	}

	ImmediateDraw::ImmediateDraw(Material& material)
		: m_material(material)
		, m_cursor{ 0, 0 }
	{
		m_batches[PLAIN].resize(64);
		m_batches[OUTLINE].resize(64);

		ms_vertex_decl = vertex_decl(VertexAttribute::Position | VertexAttribute::Colour);
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

	ImmediateDraw::Batch* ImmediateDraw::batch(DrawMode draw_mode, size_t vertex_count)
	{
		size_t& cursor = m_cursor[draw_mode];
		if(m_batches[draw_mode][cursor].m_vertices.size() + vertex_count > UINT16_MAX)
			cursor++;
		if(cursor > m_batches[draw_mode].size())
			return nullptr;
		return &m_batches[draw_mode][cursor];
	}

	void ImmediateDraw::shape(const mat4& transform, const ProcShape& shape)
	{
		this->draw(transform, { shape });
	}

	void ImmediateDraw::draw(const mat4& transform, span<ProcShape> shapes)
	{
		ShapeSize size[2] = { { 0, 0 }, { 0, 0 } };
		size_t shape_count = 0;

		shapes_size(shapes, { size, 2 }, shape_count);

		if(size[PLAIN].vertex_count)
			this->draw(transform, shapes, size[PLAIN], PLAIN);
		if(size[OUTLINE].vertex_count)
			this->draw(transform, shapes, size[OUTLINE], OUTLINE);
	}

	void ImmediateDraw::draw(const mat4& transform, span<ProcShape> shapes, ShapeSize size, DrawMode draw_mode)
	{
		Batch* batch = this->batch(draw_mode, size.vertex_count);
		if(batch)
			this->draw(*batch, transform, shapes, size, draw_mode);
	}

	void ImmediateDraw::draw(Batch& batch, const mat4& transform, span<ProcShape> shapes, ShapeSize size, DrawMode draw_mode)
	{
		size_t vertex_offset = batch.m_vertices.size();
		size_t index_offset = batch.m_indices.size();

		batch.m_vertices.resize(batch.m_vertices.size() + size.vertex_count);
		batch.m_indices.resize(batch.m_indices.size() + size.index_count);

		MeshAdapter data(Vertex::vertex_format, { &batch.m_vertices[vertex_offset], size.vertex_count }, { &batch.m_indices[index_offset], size.index_count }, false);
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
			//batch.m_vertices[i].m_position = batch.m_vertices[i].m_position;
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

		uint32_t num_vertices = uint32_t(batch.m_vertices.size());
		uint32_t num_indices = uint32_t(batch.m_indices.size());

		if(num_vertices != bgfx::getAvailTransientVertexBuffer(num_vertices, ms_vertex_decl)
		|| num_indices != bgfx::getAvailTransientIndexBuffer(num_indices))
			return;

		bgfx::TransientVertexBuffer vertex_buffer;
		bgfx::allocTransientVertexBuffer(&vertex_buffer, num_vertices, ms_vertex_decl);
		memcpy(vertex_buffer.data, batch.m_vertices.data(), num_vertices * sizeof(Vertex));//ms_vertex_decl.m_stride);

		bgfx::TransientIndexBuffer index_buffer;
		bgfx::allocTransientIndexBuffer(&index_buffer, num_indices);
		memcpy(index_buffer.data, batch.m_indices.data(), num_indices * sizeof(uint16_t));

		m_material.submit(*m_material.m_program, encoder, bgfx_state);

		encoder.setVertexBuffer(0, &vertex_buffer);
		encoder.setIndexBuffer(&index_buffer);
		encoder.setState(draw_mode == OUTLINE ? bgfx_state | BGFX_STATE_PT_LINES | BGFX_STATE_LINEAA : bgfx_state);

		static const mat4 identity = bxidentity();
		encoder.setTransform(value_ptr(identity));

		encoder.submit(view, m_material.m_program->default_version());
	}

	bgfx::VertexDecl ImmediateDraw::ms_vertex_decl;

	static size_t s_direct_index = 0;

	Direct::Direct()
	{}

	Direct::Direct(Item& item)
		: m_item(&item)
		//, m_mesh("direct" + to_string(s_direct_index++))
		//, m_model("direct" + to_string(s_direct_index++))
	{}

	struct SymbolIndex::Impl
	{
		std::map<uint64_t, Material*> m_materials;
		std::map<uint64_t, std::map<std::array<char, c_max_shape_size>, object<Model>>> m_symbols;
	};

	SymbolIndex::SymbolIndex()
		: m_impl(make_unique<Impl>())
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

	Material& SymbolIndex::symbol_material(GfxSystem& gfx, const Symbol& symbol, DrawMode draw_mode)
	{
		Colour colour = draw_mode == PLAIN ? symbol.m_fill : symbol.m_outline;

		uint64_t hash = hash_symbol_material(symbol, draw_mode);
		if(m_impl->m_materials.find(hash) == m_impl->m_materials.end())
		{
			Material& m = gfx.fetch_material("Symbol" + to_string(hash), "solid");
			m.m_base.m_depth_draw = DepthDraw::Disabled;
			m.m_base.m_depth_test = symbol.m_overlay ? DepthTest::Disabled : DepthTest::Enabled;
			m.m_base.m_cull_mode = symbol.m_double_sided ? CullMode::None : CullMode::Back;
			m.m_solid.m_colour.m_value = colour;
			m_impl->m_materials[hash] = &m;
		}
		return *m_impl->m_materials[hash];
	}

	Model& SymbolIndex::symbol_model(const Symbol& symbol, const Shape& shape, DrawMode draw_mode)
	{
		uint64_t hash = hash_symbol(symbol, draw_mode);
		std::array<char, c_max_shape_size> shape_mem = {};
		std::memcpy(&shape_mem[0], (void*) &shape, shape.m_type.m_size);

		auto& shapes = m_impl->m_symbols[hash];
		if(shapes.find(shape_mem) == shapes.end())
		{
			//printf("INFO: created indexed Shape %s %s\n", shape.m_type.m_name, pack_json(Ref(&shape)).c_str());
			string name = "Shape:" + string(shape.m_type.m_name);
			shapes[shape_mem] = draw_model(name.c_str(), ProcShape{ symbol, &shape, draw_mode }, true);
		}

		return *shapes[shape_mem];
	}

	object<Model> draw_model(cstring id, const ProcShape& shape, bool readback)
	{
		return draw_model(id, vector<ProcShape>{ shape }, readback);
	}

	object<Model> draw_model(cstring id, span<ProcShape> shapes, bool readback)
	{
		object<Model> model = oconstruct<Model>(id);
		draw_model(shapes, *model, readback);
		return model;
	}

	void draw_model(const ProcShape& shape, Model& model, bool readback, Material* material)
	{
		draw_model(span<ProcShape>{ shape }, model, readback, material);
	}

	void draw_model(span<ProcShape> shapes, Model& model, bool readback, Material* material)
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
		draw_mesh(span<ProcShape>{ shape }, model, draw_mode, readback, material);
	}

	void draw_mesh(span<ProcShape> shapes, Model& model, DrawMode draw_mode, bool readback, Material* material)
	{
		ShapeSize size = { 0, 0 };
		size_t shape_count = 0;

		shapes_size(shapes, draw_mode, size, shape_count);
		draw_mesh(shapes, model, size, draw_mode, readback, material);
	}

	void draw_mesh(span<ProcShape> shapes, Model& model, ShapeSize size, DrawMode draw_mode, bool readback, Material* material)
	{
		Mesh& mesh = model.add_mesh(model.m_name + to_string(uint(draw_mode)), readback);
		mesh.m_material = material;

		const PrimitiveType primitive = draw_mode == PLAIN ? PrimitiveType::Triangles : PrimitiveType::Lines;
		GpuMesh gpu_mesh = alloc_mesh(primitive, ShapeVertex::vertex_format, size.vertex_count, size.index_count);

		MeshAdapter& writer = gpu_mesh.m_writer;
		for(const ProcShape& shape : shapes)
			if(shape.m_draw_mode == draw_mode)
			{
				draw_mode == OUTLINE ? symbol_draw_lines(shape, writer)
									 : symbol_draw_triangles(shape, writer);
				writer.next();
			}

		if(draw_mode == PLAIN)
			generate_mikkt_tangents({ (ShapeIndex*)gpu_mesh.m_indices.data(), gpu_mesh.m_index_count }, { (ShapeVertex*)gpu_mesh.m_vertices.data(), gpu_mesh.m_vertex_count });

		mesh.upload(gpu_mesh);

		model.add_item(mesh, bxidentity());
	}

	Lines::Lines()
	{}

	Lines::Lines(const vector<vec3>& points)
	{
		this->start(points[0]);
		for(const vec3& p : points)
		{
			this->next(p);
		}
	}

	Lines::Lines(const Curve3& curve, size_t subdiv)
		: Lines(curve.points(subdiv))
	{}

	void Lines::add(const vec3& start, const vec3& end, const Colour& start_colour, const Colour& end_colour)
	{
		const float start_distance = m_segments.size() > 0 ? m_segments.back().dist1 : 0.f;
		const float end_distance = start_distance + distance(start, end);
		m_segments.push_back({ start, start_distance, end, end_distance, start_colour, end_colour });
	}

	void Lines::start(const vec3& position, const Colour& colour)
	{
		m_segments.push_back({ position, 0.f, position, 0.f, colour, colour });
	}

	void Lines::next(const vec3& end, const Colour& colour)
	{
		const Segment& last = m_segments.back();
		const float dist = last.dist1 + distance(last.pos1, end);
		m_segments.push_back({ last.pos1, last.dist1, end, dist, last.col1, colour });
	}

	void Lines::setup()
	{
		for(size_t i = 0; i < m_segments.size(); ++i)
		{
			Segment& seg = m_segments[i];
			seg.dist0 = i > 0 ? m_segments[i - 1].dist1 : 0.f;
			seg.dist1 = seg.dist0 + distance(seg.pos0, seg.pos1);
		}
	}

	void Lines::write(Mesh& mesh)
	{
		const uint32_t vertex_format = VertexAttribute::Position4 | VertexAttribute::Colour;
		GpuMesh gpu_mesh = alloc_mesh(PrimitiveType::Lines, vertex_format, uint32_t(m_segments.size() * 2), 0U);
		MeshAdapter& writer = gpu_mesh.m_writer;

		for(const Segment& seg : m_segments)
		{
			writer.position4(vec4(seg.pos0, seg.dist0));
			writer.colour(seg.col0);

			writer.position4(vec4(seg.pos1, seg.dist1));
			writer.colour(seg.col1);
		}

		mesh.upload(gpu_mesh);
	}

	void Lines::commit(Batch& batch)
	{
		span<float> memory = batch.begin(uint32_t(m_segments.size())); // , sizeof(Segment)
		memcpy(memory.data(), m_segments.data(), memory.size() * sizeof(float));
	}

	void Lines::update_aabb()
	{
		m_aabb = {};

		for(Segment& seg : m_segments)
		{
			m_aabb.merge(seg.pos0);
			m_aabb.merge(seg.pos1);
		}
	}

	void Lines::update_sphere()
	{
		const vec3 center = m_aabb.m_center;
		float radius2 = 0.f;

		for(Segment& seg : m_segments)
		{
			radius2 = max(radius2, distance2(center, seg.pos0));
			radius2 = max(radius2, distance2(center, seg.pos1));
		}

		m_radius = sqrt(radius2);
	}
}
