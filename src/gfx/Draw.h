//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
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

#ifndef MUD_CPP_20
#include <map>
#endif

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
			static const size_t vertex_format = VertexAttribute::Position | VertexAttribute::Colour;
			vec3 m_position;
			uint32_t m_colour;
		};

		static bgfx::VertexDecl ms_vertex_decl;

		Material& m_material;

		std::vector<Vertex> m_vertices[2];
		std::vector<ShapeIndex> m_indices[2];

		void draw(const mat4& transform, const ProcShape& shapes);
		void draw(const mat4& transform, array<ProcShape> shapes);
		void draw(const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode);

		void submit(uint8_t view, uint64_t bgfx_state);
		void submit(uint8_t view, uint64_t bgfx_state, DrawMode draw_mode);
	};

	export_ class refl_ MUD_GFX_EXPORT SymbolIndex : public NonCopy, public Global<SymbolIndex>
	{
	public:
		SymbolIndex();
		~SymbolIndex();

		Model& symbolModel(const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		Material& symbolMaterial(GfxSystem& gfx_system, const Symbol& symbol, DrawMode draw_mode);

	protected:
		std::map<uint64_t, Material*> m_materials;
		std::map<uint64_t, std::map<std::array<char, c_max_shape_size>, object_ptr<Model>>> m_symbols;
	};

	export_ MUD_GFX_EXPORT object_ptr<Model> draw_model(cstring name, const ProcShape& shape, bool readback = false);
	export_ MUD_GFX_EXPORT object_ptr<Model> draw_model(cstring name, const std::vector<ProcShape>& shapes, bool readback = false);
	export_ MUD_GFX_EXPORT void draw_model(const ProcShape& shape, Model& model, bool readback = false);
	export_ MUD_GFX_EXPORT void draw_model(const std::vector<ProcShape>& shapes, Model& model, bool readback = false);
	export_ MUD_GFX_EXPORT void draw_mesh(const std::vector<ProcShape>& shapes, Model& model, ShapeSize size, DrawMode draw_mode, bool readback = false);

}
