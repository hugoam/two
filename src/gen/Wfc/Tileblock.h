#pragma once

#include <obj/Util/Updatable.h>
#include <gen/Generated/Forward.h>
#include <gen/Wfc/wfc.h>
#include <uio/Unode.h>

#include <map>

namespace mud
{
	class _refl_ MUD_GEN_EXPORT Tileblock : public Updatable
	{
	public:
		_constr_ Tileblock(const uvec3& size, const vec3& period, WaveTileset& tileset);

		_attr_ uvec3 m_size;
		_attr_ vec3 m_period;
		WaveTileset& m_tileset;
		TileWave m_wave;
		size_t m_last_tick = 0;
		size_t m_wave_updated = 0;
		array_3d<uint16_t> m_tiles;
		array_3d<uint16_t> m_entropy;

		uvec3 m_highlight = uvec3(UINT32_MAX);

		virtual void next_frame(size_t tick, size_t delta) final;

		_meth_ void reset();
		_meth_ void observe();
		_meth_ void propagate();
		_meth_ void solve(size_t limit = 0);
		_meth_ void update(Wave& wave);
	};

	MUD_GEN_EXPORT void paint_tile_grid(Gnode& parent, Tileblock& tileblock);
	MUD_GEN_EXPORT Model& entropy_cube(Gnode& parent, Tileblock& tileblock, uint16_t x, uint16_t y, uint16_t z);

	MUD_GEN_EXPORT void paint_tiles(Gnode& parent, Tileblock& tileblock);

	MUD_GEN_EXPORT void paint_tileblock(Gnode& parent, Tileblock& tileblock);
	MUD_GEN_EXPORT void tile_view(Widget& parent, Tile& tile);

	MUD_GEN_EXPORT void tileset_view(Widget& parent, Tileset& tileset);
	MUD_GEN_EXPORT void tileblock_view(Widget& parent, Tileblock& tileblock);

	MUD_GEN_EXPORT void tileblock_edit(Widget& parent, Tileblock& tileblock);

	MUD_GEN_EXPORT void tileblock_editor(Widget& parent, Viewer& viewport, Tileblock& tileblock);
}
