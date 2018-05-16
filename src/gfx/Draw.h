//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/NonCopy.h>
#include <obj/Util/Global.h>
#include <math/Vec.h>
#include <geom/Shape/ProcShape.h>
#include <gfx/Generated/Forward.h>
#include <gfx/Mesh.h>
#include <gfx/Material.h>

#ifdef MUD_VAL_BUFFER
#define MUD_MAX_SHAPE_SIZE MUD_VAL_BUFFER
#else
#define MUD_MAX_SHAPE_SIZE 256
#endif

#include <map>

namespace mud
{
	using cstring = const char*;

	class _refl_ MUD_GFX_EXPORT ImmediateDraw
	{
	public:
		ImmediateDraw();

		struct Vertex
		{
			static const size_t vertex_format = VertexAttribute::Position | VertexAttribute::Colour;
			vec3 m_position;
			uint32_t m_colour;
		};

		static bgfx::VertexDecl ms_vertex_decl;

		Material m_material;

		std::vector<Vertex> m_vertices[2];
		std::vector<ShapeIndex> m_indices[2];

		void draw(const mat4& transform, const ProcShape& shapes);
		void draw(const mat4& transform, array<ProcShape> shapes);
		void draw(const mat4& transform, array<ProcShape> shapes, ShapeSize size, DrawMode draw_mode);

		void submit(uint8_t view, uint64_t bgfx_state);
		void submit(uint8_t view, uint64_t bgfx_state, DrawMode draw_mode);
	};

	class _refl_ MUD_GFX_EXPORT SymbolIndex : public NonCopy, public Global<SymbolIndex>
	{
	public:
		SymbolIndex();
		~SymbolIndex();

		Model& symbolModel(GfxSystem& gfx_system, const Symbol& symbol, const Shape& shape, DrawMode draw_mode);
		Material& symbolMaterial(GfxSystem& gfx_system, const Symbol& symbol, DrawMode draw_mode);

	protected:
		std::map<uint64_t, Material*> m_materials;
		std::map<uint64_t, std::map<std::array<char, MUD_MAX_SHAPE_SIZE>, object_ptr<Model>>> m_symbols;
	};

	MUD_GFX_EXPORT object_ptr<Model> draw_model(GfxSystem& gfx_system, cstring name, const ProcShape& shape, bool readback = false);
	MUD_GFX_EXPORT object_ptr<Model> draw_model(GfxSystem& gfx_system, cstring name, const std::vector<ProcShape>& shapes, bool readback = false);
	MUD_GFX_EXPORT void draw_model(const ProcShape& shape, Model& model, bool readback = false);
	MUD_GFX_EXPORT void draw_model(const std::vector<ProcShape>& shapes, Model& model, bool readback = false);
	MUD_GFX_EXPORT void draw_mesh(const std::vector<ProcShape>& shapes, Model& model, ShapeSize size, DrawMode draw_mode, bool readback = false);

}
