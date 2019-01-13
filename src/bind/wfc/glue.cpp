#include <infra/Api.h>
#include <type/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <wfc/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// Tile
	mud::Tile* EMSCRIPTEN_KEEPALIVE Tile_Tile_0() {
		return new mud::Tile();
	}
	uint32_t EMSCRIPTEN_KEEPALIVE Tile_get_index(mud::Tile* self) {
		return self->m_index;
	}
	const char* EMSCRIPTEN_KEEPALIVE Tile_get_name(mud::Tile* self) {
		return self->m_name.c_str();
	}
	char EMSCRIPTEN_KEEPALIVE Tile_get_symmetry(mud::Tile* self) {
		return self->m_symmetry;
	}
	int EMSCRIPTEN_KEEPALIVE Tile_get_cardinality(mud::Tile* self) {
		return self->m_cardinality;
	}
	int EMSCRIPTEN_KEEPALIVE Tile_get_profile(mud::Tile* self) {
		return self->m_profile;
	}
	void EMSCRIPTEN_KEEPALIVE Tile___destroy__(mud::Tile* self) {
		delete self;
	}
	// Tileset
	mud::Tileset* EMSCRIPTEN_KEEPALIVE Tileset_Tileset_0() {
		return new mud::Tileset();
	}
	mud::Tileset* EMSCRIPTEN_KEEPALIVE Tileset_Tileset_0() {
		return new mud::Tileset();
	}
	const char* EMSCRIPTEN_KEEPALIVE Tileset_get_name(mud::Tileset* self) {
		return self->m_name.c_str();
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Tileset_get_tile_size(mud::Tileset* self) {
		static mud::vec3 temp;
		return (temp = self->m_tile_size, &temp);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE Tileset_get_tile_scale(mud::Tileset* self) {
		static mud::vec3 temp;
		return (temp = self->m_tile_scale, &temp);
	}
	uint16_t EMSCRIPTEN_KEEPALIVE Tileset_get_nutiles(mud::Tileset* self) {
		return self->m_num_tiles;
	}
	void EMSCRIPTEN_KEEPALIVE Tileset___destroy__(mud::Tileset* self) {
		delete self;
	}
	// Wave
	mud::Wave* EMSCRIPTEN_KEEPALIVE Wave_Wave_0() {
		return new mud::Wave();
	}
	mud::Result EMSCRIPTEN_KEEPALIVE Wave_solve_1(mud::Wave* self, size_t limit) {
		static mud::Result temp;
		return (temp = self->solve(limit), &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Wave___destroy__(mud::Wave* self) {
		delete self;
	}
	// TileWave
	mud::TileWave* EMSCRIPTEN_KEEPALIVE TileWave_TileWave_0() {
		return new mud::TileWave();
	}
	mud::TileWave* EMSCRIPTEN_KEEPALIVE TileWave_TileWave_5(mud::WaveTileset* tileset, uint16_t width, uint16_t height, uint16_t depth, bool periodic) {
		return new mud::TileWave(*tileset, width, height, depth, periodic);
	}
	void EMSCRIPTEN_KEEPALIVE TileWave___destroy__(mud::TileWave* self) {
		delete self;
	}
	// WaveTileset
	mud::WaveTileset* EMSCRIPTEN_KEEPALIVE WaveTileset_WaveTileset_0() {
		return new mud::WaveTileset();
	}
	mud::WaveTileset* EMSCRIPTEN_KEEPALIVE WaveTileset_WaveTileset_0() {
		return new mud::WaveTileset();
	}
	void EMSCRIPTEN_KEEPALIVE WaveTileset___destroy__(mud::WaveTileset* self) {
		delete self;
	}
	// Result
	mud::Result EMSCRIPTEN_KEEPALIVE Result_kSuccess() {
		return mud::kSuccess;
	}
	mud::Result EMSCRIPTEN_KEEPALIVE Result_kFail() {
		return mud::kFail;
	}
	mud::Result EMSCRIPTEN_KEEPALIVE Result_kUnfinished() {
		return mud::kUnfinished;
	}
	
}


