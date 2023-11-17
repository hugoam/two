//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Mesh.h>
#include <gfx/Material.h>

namespace two
{
	constexpr size_t c_max_shape_size = 256U;

	struct ShapeHash
	{
		void hash(const Shape& shape);
		bool operator==(const ShapeHash& other) const;
		bool operator<(const ShapeHash& other) const;
		stl::array<char, c_max_shape_size> m_hash;
	};

	using cstring = const char*;

	export_ class refl_ TWO_GFX_EXPORT Direct
	{
	public:
		constr_ Direct();
		constr_ Direct(Item& item);

		//void begin();
		//Mesh& batch(uint32_t vertex_format, uint32_t vertex_count, uint32_t index_count = 0);

		//attr_ Mesh m_mesh;
		//attr_ Model m_model;
		attr_ Item* m_item = nullptr;

		//vector<Mesh> m_batches;
	};

	export_ class refl_ TWO_GFX_EXPORT ImmediateDraw
	{
	public:
		ImmediateDraw(Material& material);

		struct Vertex
		{
			static const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Colour;
			vec3 m_position;
			uint32_t m_colour;
		};

		static bgfx::VertexLayout ms_vertex_decl;

		Material& m_material;

		struct Batch
		{
			//DrawMode m_draw_mode;
			vector<Vertex> m_vertices;
			vector<uint16_t> m_indices;
		};

		vector<Batch> m_batches[2];
		size_t m_cursor[2];

		void begin();

		Batch* batch(DrawMode draw_mode, size_t vertex_count);

		void shape(const mat4& transform, const ProcShape& shape);
		void draw(const mat4& transform, span<ProcShape> shapes);
		void draw(const mat4& transform, span<ProcShape> shapes, DrawMode draw_mode);

		void draw(Batch& batch, const mat4& transform, span<ProcShape> shapes, ShapeSize size, DrawMode draw_mode);

		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state);
		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode);
		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode, Batch& batch);
	};

	export_ class refl_ TWO_GFX_EXPORT SymbolIndex
	{
	public:
		SymbolIndex();
		~SymbolIndex();

		Model& symbol_model(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		Material& symbol_material(GfxSystem& gfx, const Symbol& symbol, DrawMode draw_mode);

		struct Impl;
		unique<Impl> m_impl;
	};

	export_ TWO_GFX_EXPORT object<Model> gen_model(cstring name, const ProcShape& shape, bool readback = false);
	export_ TWO_GFX_EXPORT object<Model> gen_model(cstring name, span<ProcShape> shapes, bool readback = false);

	export_ TWO_GFX_EXPORT void gen_model(const ProcShape& shape, Model& model, bool readback = false, Material* material = nullptr);
	export_ TWO_GFX_EXPORT void gen_model(span<ProcShape> shapes, Model& model, bool readback = false, Material* material = nullptr);

	export_ TWO_GFX_EXPORT void gen_mesh(const ProcShape& shapes, Model& model, DrawMode draw_mode, bool readback = false, Material* material = nullptr);
	export_ TWO_GFX_EXPORT void gen_mesh(span<ProcShape> shapes, Model& model, DrawMode draw_mode, bool readback = false, Material* material = nullptr);

	export_ TWO_GFX_EXPORT void gen_geom(const ProcShape& shapes, MeshPacker& model, DrawMode draw_mode);
	export_ TWO_GFX_EXPORT void gen_geom(span<ProcShape> shapes, MeshPacker& model, DrawMode draw_mode);


	export_ class refl_ TWO_GFX_EXPORT Lines
	{
	public:
		constr_ Lines();
		constr_ Lines(const vector<vec3>& points);
		constr_ Lines(const Curve3& curve, size_t subdiv);

		struct Segment { vec3 pos0; float dist0; vec3 pos1; float dist1; Colour col0; Colour col1; };
		vector<Segment> m_segments;
		bool m_started = false;

		Aabb m_aabb;
		float m_radius;

		meth_ void add(const vec3& start, const vec3& end, const Colour& start_colour = Colour(1.f), const Colour& end_colour = Colour(1.f));
		meth_ void start(const vec3& position, const Colour& colour = Colour(1.f));
		meth_ void next(const vec3& position, const Colour& colour = Colour(1.f));
		meth_ void setup();
		meth_ void write(Mesh& mesh);
		meth_ void commit(Batch& batch);

		void update_aabb();
		void update_sphere();
	};
}
