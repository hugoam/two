//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/NonCopy.h>
#include <infra/Global.h>
#include <math/Vec.h>
#include <geom/Shape/ProcShape.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Mesh.h>
#include <gfx/Material.h>

namespace mud
{
	constexpr size_t c_max_shape_size = 256U;

	using cstring = const char*;

	export_ class refl_ MUD_GFX_EXPORT ImmediateDraw
	{
	public:
		ImmediateDraw(Material& material);

		struct Vertex
		{
			static const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Colour;
			vec3 m_position;
			uint32_t m_colour;
		};

		static bgfx::VertexDecl ms_vertex_decl;

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

		void draw(const mat4& transform, const ProcShape& shapes);
		void draw(const mat4& transform, array<ProcShape> shapes);
		void draw(const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode);

		void draw(Batch& batch, const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode);

		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state);
		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode);
		void submit(bgfx::Encoder& encoder, uint8_t view, uint64_t bgfx_state, DrawMode draw_mode, Batch& batch);
	};

	export_ class refl_ MUD_GFX_EXPORT SymbolIndex : public NonCopy
	{
	public:
		SymbolIndex();
		~SymbolIndex();

		Model& symbol_model(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		Material& symbol_material(GfxSystem& gfx_system, const Symbol& symbol, DrawMode draw_mode);

		class Impl;
		unique<Impl> m_impl;
	};

	export_ MUD_GFX_EXPORT object<Model> draw_model(cstring name, const ProcShape& shape, bool readback = false);
	export_ MUD_GFX_EXPORT object<Model> draw_model(cstring name, const vector<ProcShape>& shapes, bool readback = false);

	export_ MUD_GFX_EXPORT void draw_model(const ProcShape& shape, Model& model, bool readback = false, Material* material = nullptr);
	export_ MUD_GFX_EXPORT void draw_model(const vector<ProcShape>& shapes, Model& model, bool readback = false, Material* material = nullptr);

	export_ MUD_GFX_EXPORT void draw_mesh(const ProcShape& shapes, Model& model, DrawMode draw_mode, bool readback = false, Material* material = nullptr);
	export_ MUD_GFX_EXPORT void draw_mesh(const vector<ProcShape>& shapes, Model& model, DrawMode draw_mode, bool readback = false, Material* material = nullptr);
	
	export_ MUD_GFX_EXPORT void draw_mesh(const vector<ProcShape>& shapes, Model& model, ShapeSize size, DrawMode draw_mode, bool readback = false, Material* material = nullptr);

}
