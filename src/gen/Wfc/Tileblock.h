#pragma once

#ifndef MUD_MODULES
#include <obj/Util/Updatable.h>
#include <geom/Aabb.h>
#include <uio/Unode.h>
#endif
#include <gen/Generated/Forward.h>
#include <gen/Wfc/wfc.h>

#ifndef MUD_CPP_20
#include <map>
#endif

namespace mud
{
	export_ struct _refl_ MUD_GEN_EXPORT TileModel
	{
		Model* m_model;
		quat m_rotation;
	};

	export_ class _refl_ MUD_GEN_EXPORT Tileblock : public Updatable
	{
	public:
		_constr_ Tileblock(GfxSystem& gfx_system, const uvec3& size, const vec3& period, WaveTileset& tileset);

		_attr_ uvec3 m_size;
		_attr_ vec3 m_period;
		_attr_ Aabb m_aabb;

		WaveTileset& m_tileset;

		TileWave m_wave;
		size_t m_last_tick = 0;
		size_t m_wave_updated = 0;

		array_3d<uint16_t> m_tiles;
		array_3d<uint16_t> m_entropy;

		std::vector<TileModel> m_tile_models;

		bool m_auto_solve = false;

		uvec3 to_coord(const vec3& position);
		vec3 to_position(const uvec3& coord);

		virtual void next_frame(size_t tick, size_t delta) final;

		void load_models(GfxSystem& gfx_system);

		_meth_ void reset();
		_meth_ void observe();
		_meth_ void propagate();
		_meth_ void solve(size_t limit = 0);
		_meth_ void update(Wave& wave);
	};

	MUD_GEN_EXPORT void paint_tile_grid(Gnode& parent, Tileblock& tileblock);
	MUD_GEN_EXPORT Model& entropy_cube(Gnode& parent, Tileblock& tileblock, uint16_t x, uint16_t y, uint16_t z);

	MUD_GEN_EXPORT void paint_tiles(Gnode& parent, Tileblock& tileblock, const uvec3& focused = uvec3(UINT32_MAX));

	MUD_GEN_EXPORT void paint_tile_cube(Gnode& parent, Tileblock& tileblock, const uvec3& coord, const Colour& outline, const Colour& fill = Colour::None);
	MUD_GEN_EXPORT void paint_tile_cube(Gnode& parent, Tileblock& tileblock, const uvec3& coord);
	MUD_GEN_EXPORT void paint_tileblock(Gnode& parent, Tileblock& tileblock, const uvec3& focused = uvec3(UINT32_MAX));

	MUD_GEN_EXPORT void tileset_view(Widget& parent, Tileblock& tileblock, Tileset& tileset);
	MUD_GEN_EXPORT void tile_states_view(Widget& parent, Tileblock& tileblock, uvec3& coord);

	MUD_GEN_EXPORT void tileblock_edit(Widget& parent, Viewer& viewer, Tileblock& tileblock, uvec3& highlighted, uvec3& selected, uvec3& focused);

	MUD_GEN_EXPORT void tileblock_editor(Widget& parent, Viewer& viewer, Tileblock& tileblock);
}
