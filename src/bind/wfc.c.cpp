#include <infra/Api.h>
#include <type/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <wfc/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Tile
	two::Type* DECL two_Tile__type() {
		return &two::type<two::Tile>();
	}
	two::Tile* DECL two_Tile__construct_0() {
		return new two::Tile();
	}
	uint32_t DECL two_Tile__get_index(two::Tile* self) {
		return self->m_index;
	}
	void DECL two_Tile__set_index(two::Tile* self, uint32_t value) {
		self->m_index = value;
	}
	const char* DECL two_Tile__get_name(two::Tile* self) {
		return self->m_name.c_str();
	}
	void DECL two_Tile__set_name(two::Tile* self, const char* value) {
		self->m_name = value;
	}
	char DECL two_Tile__get_symmetry(two::Tile* self) {
		return self->m_symmetry;
	}
	void DECL two_Tile__set_symmetry(two::Tile* self, char value) {
		self->m_symmetry = value;
	}
	int DECL two_Tile__get_cardinality(two::Tile* self) {
		return self->m_cardinality;
	}
	void DECL two_Tile__set_cardinality(two::Tile* self, int value) {
		self->m_cardinality = value;
	}
	int DECL two_Tile__get_profile(two::Tile* self) {
		return self->m_profile;
	}
	void DECL two_Tile__set_profile(two::Tile* self, int value) {
		self->m_profile = value;
	}
	void DECL two_Tile__destroy(two::Tile* self) {
		delete self;
	}
	// Tileset
	two::Type* DECL two_Tileset__type() {
		return &two::type<two::Tileset>();
	}
	two::Tileset* DECL two_Tileset__construct_0() {
		return new two::Tileset();
	}
	const char* DECL two_Tileset__get_name(two::Tileset* self) {
		return self->m_name.c_str();
	}
	void DECL two_Tileset__set_name(two::Tileset* self, const char* value) {
		self->m_name = value;
	}
	two::vec3* DECL two_Tileset__get_tile_size(two::Tileset* self) {
		return &self->m_tile_size;
	}
	void DECL two_Tileset__set_tile_size(two::Tileset* self, two::vec3* value) {
		self->m_tile_size = *value;
	}
	two::vec3* DECL two_Tileset__get_tile_scale(two::Tileset* self) {
		return &self->m_tile_scale;
	}
	void DECL two_Tileset__set_tile_scale(two::Tileset* self, two::vec3* value) {
		self->m_tile_scale = *value;
	}
	uint16_t DECL two_Tileset__get_nutiles(two::Tileset* self) {
		return self->m_num_tiles;
	}
	void DECL two_Tileset__set_nutiles(two::Tileset* self, uint16_t value) {
		self->m_num_tiles = value;
	}
	void DECL two_Tileset__destroy(two::Tileset* self) {
		delete self;
	}
	// Wave
	two::Type* DECL two_Wave__type() {
		return &two::type<two::Wave>();
	}
	two::Wave* DECL two_Wave__construct_0() {
		return new two::Wave();
	}
	two::Result DECL two_Wave_solve_1(two::Wave* self, size_t limit) {
		return self->solve(limit);
	}
	void DECL two_Wave__destroy(two::Wave* self) {
		delete self;
	}
	// WaveTileset
	two::Type* DECL two_WaveTileset__type() {
		return &two::type<two::WaveTileset>();
	}
	two::WaveTileset* DECL two_WaveTileset__construct_0() {
		return new two::WaveTileset();
	}
	void DECL two_WaveTileset__destroy(two::WaveTileset* self) {
		delete self;
	}
	// TileWave
	two::Type* DECL two_TileWave__type() {
		return &two::type<two::TileWave>();
	}
	two::TileWave* DECL two_TileWave__construct_5(two::WaveTileset* tileset, uint16_t width, uint16_t height, uint16_t depth, bool periodic) {
		return new two::TileWave(*tileset, width, height, depth, periodic);
	}
	void DECL two_TileWave__destroy(two::TileWave* self) {
		delete self;
	}
	void DECL two_parse_json_tileset_3(const char* path, const char* subset, two::Tileset* outputTileset) {
		two::parse_json_tileset(path, subset, *outputTileset);
	}
	void DECL two_parse_json_wave_tileset_3(const char* path, const char* subset, two::WaveTileset* outputTileset) {
		two::parse_json_wave_tileset(path, subset, *outputTileset);
	}
	// Result
	two::Result DECL two_Result_kSuccess() {
		return two::kSuccess;
	}
	two::Result DECL two_Result_kFail() {
		return two::kFail;
	}
	two::Result DECL two_Result_kUnfinished() {
		return two::kUnfinished;
	}
	
}


