#pragma once

#ifndef MUD_MODULES
#include <geom/Aabb.h>
#include <uio/Unode.h>
#include <wfc/Wfc.h>
#endif
#include <wfc-gfx/Forward.h>

#ifndef MUD_CPP_20
#include <stl/map.h>
#endif

namespace mud
{
	export_ struct refl_ MUD_WFC_GFX_EXPORT TileModel
	{
		Model* m_model;
		quat m_rotation;
	};

	export_ class refl_ MUD_WFC_GFX_EXPORT WfcBlock
	{
	public:
		constr_ WfcBlock() {}
		constr_ WfcBlock(const vec3& position, const uvec3& size, const vec3& scale, WaveTileset& tileset, bool auto_solve = false);

		attr_ vec3 m_position;
		attr_ uvec3 m_size;
		attr_ vec3 m_scale;
		attr_ Aabb m_aabb;

		WaveTileset* m_tileset = nullptr;

		TileWave m_wave;
		size_t m_last_tick = 0;
		size_t m_wave_updated = 0;
		size_t m_wave_solved = 0;

		array_3d<uint16_t> m_tiles;
		array_3d<uint16_t> m_entropy;

		vector<TileModel> m_tile_models;

		bool m_auto_solve = false;

		uvec3 to_coord(const vec3& position);
		vec3 to_position(const uvec3& coord);

		void next_frame(size_t tick, size_t delta);

		void load_models(GfxSystem& gfx_system, bool from_file = true);

		meth_ void reset();
		meth_ void observe();
		meth_ void propagate();
		meth_ void solve(size_t limit = 0);
		meth_ void update(Wave& wave);
	};

	MUD_WFC_GFX_EXPORT void paint_tile_grid(Gnode& parent, WfcBlock& tileblock);
	MUD_WFC_GFX_EXPORT Model& entropy_cube(Gnode& parent, WfcBlock& tileblock, uint16_t x, uint16_t y, uint16_t z);

	MUD_WFC_GFX_EXPORT void paint_tiles(Gnode& parent, Ref object, WfcBlock& tileblock, const uvec3& focused = uvec3(UINT32_MAX), const uvec3* exclude = nullptr, bool draw_entropy = false);

	MUD_WFC_GFX_EXPORT void paint_tile_cube(Gnode& parent, WfcBlock& tileblock, const uvec3& coord, const Colour& outline, const Colour& fill = Colour::None);
	MUD_WFC_GFX_EXPORT void paint_tile_cube(Gnode& parent, WfcBlock& tileblock, const uvec3& coord);
	MUD_WFC_GFX_EXPORT void paint_tileblock(Gnode& parent, Ref object, WfcBlock& tileblock, const uvec3& focused = uvec3(UINT32_MAX), const uvec3* exclude = nullptr, bool draw_entropy = false);

	MUD_WFC_GFX_EXPORT void tileset_view(Widget& parent, WfcBlock& tileblock, Tileset& tileset);
	MUD_WFC_GFX_EXPORT void tile_states_view(Widget& parent, WfcBlock& tileblock, uvec3& coord);

	MUD_WFC_GFX_EXPORT void tileblock_edit(Widget& parent, Viewer& viewer, WfcBlock& tileblock, uvec3& highlighted, uvec3& selected, uvec3& focused);

	MUD_WFC_GFX_EXPORT void tileblock_editor(Widget& parent, Viewer& viewer, WfcBlock& tileblock);
}
