#include <infra/Api.h>
#include <type/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <wfc/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif
#include <cstdint>


extern "C" {
	
	// Tile
	mud::Tile* DECL mud_Tile_Tile_0() {
		return new mud::Tile();
	}
	uint32_t DECL mud_Tile__get_index(mud::Tile* self) {
		return self->m_index;
	}
	void DECL mud_Tile__set_index(mud::Tile* self, uint32_t value) {
		self->m_index = value;
	}
	const char* DECL mud_Tile__get_name(mud::Tile* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Tile__set_name(mud::Tile* self, const char* value) {
		self->m_name = value;
	}
	char DECL mud_Tile__get_symmetry(mud::Tile* self) {
		return self->m_symmetry;
	}
	void DECL mud_Tile__set_symmetry(mud::Tile* self, char value) {
		self->m_symmetry = value;
	}
	int DECL mud_Tile__get_cardinality(mud::Tile* self) {
		return self->m_cardinality;
	}
	void DECL mud_Tile__set_cardinality(mud::Tile* self, int value) {
		self->m_cardinality = value;
	}
	int DECL mud_Tile__get_profile(mud::Tile* self) {
		return self->m_profile;
	}
	void DECL mud_Tile__set_profile(mud::Tile* self, int value) {
		self->m_profile = value;
	}
	void DECL mud_Tile__destroy(mud::Tile* self) {
		delete self;
	}
	// Tileset
	mud::Tileset* DECL mud_Tileset_Tileset_0() {
		return new mud::Tileset();
	}
	const char* DECL mud_Tileset__get_name(mud::Tileset* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Tileset__set_name(mud::Tileset* self, const char* value) {
		self->m_name = value;
	}
	mud::vec3* DECL mud_Tileset__get_tile_size(mud::Tileset* self) {
		static mud::vec3 temp;
		return (temp = self->m_tile_size, &temp);
	}
	void DECL mud_Tileset__set_tile_size(mud::Tileset* self, mud::vec3* value) {
		self->m_tile_size = *value;
	}
	mud::vec3* DECL mud_Tileset__get_tile_scale(mud::Tileset* self) {
		static mud::vec3 temp;
		return (temp = self->m_tile_scale, &temp);
	}
	void DECL mud_Tileset__set_tile_scale(mud::Tileset* self, mud::vec3* value) {
		self->m_tile_scale = *value;
	}
	uint16_t DECL mud_Tileset__get_nutiles(mud::Tileset* self) {
		return self->m_num_tiles;
	}
	void DECL mud_Tileset__set_nutiles(mud::Tileset* self, uint16_t value) {
		self->m_num_tiles = value;
	}
	void DECL mud_Tileset__destroy(mud::Tileset* self) {
		delete self;
	}
	// Wave
	mud::Wave* DECL mud_Wave_Wave_0() {
		return new mud::Wave();
	}
	mud::Result DECL mud_Wave_solve_1(mud::Wave* self, size_t limit) {
		return self->solve(limit);
	}
	void DECL mud_Wave__destroy(mud::Wave* self) {
		delete self;
	}
	// TileWave
	mud::TileWave* DECL mud_TileWave_TileWave_5(mud::WaveTileset* tileset, uint16_t width, uint16_t height, uint16_t depth, bool periodic) {
		return new mud::TileWave(*tileset, width, height, depth, periodic);
	}
	void DECL mud_TileWave__destroy(mud::TileWave* self) {
		delete self;
	}
	// WaveTileset
	mud::WaveTileset* DECL mud_WaveTileset_WaveTileset_0() {
		return new mud::WaveTileset();
	}
	void DECL mud_WaveTileset__destroy(mud::WaveTileset* self) {
		delete self;
	}
	// Result
	mud::Result DECL mud_Result_kSuccess() {
		return mud::kSuccess;
	}
	mud::Result DECL mud_Result_kFail() {
		return mud::kFail;
	}
	mud::Result DECL mud_Result_kUnfinished() {
		return mud::kUnfinished;
	}
	
}


