#include <infra/Api.h>
#include <tree/Api.h>
#include <type/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <wfc/Api.h>
#include <ctx/Api.h>
#include <ui/Api.h>
#include <uio/Api.h>
#include <gfx/Api.h>
#include <gfx-ui/Api.h>
#include <wfc-gfx/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// TileModel
	mud::TileModel* EMSCRIPTEN_KEEPALIVE mud_TileModel_TileModel_0() {
		return new mud::TileModel();
	}
	void EMSCRIPTEN_KEEPALIVE mud_TileModel___destroy__(mud::TileModel* self) {
		delete self;
	}
	// WfcBlock
	mud::WfcBlock* EMSCRIPTEN_KEEPALIVE mud_WfcBlock_WfcBlock_0() {
		return new mud::WfcBlock();
	}
	mud::WfcBlock* EMSCRIPTEN_KEEPALIVE mud_WfcBlock_WfcBlock_4(const mud::vec3* position, const mud::uvec3* size, const mud::vec3* scale, mud::WaveTileset* tileset) {
		return new mud::WfcBlock(*position, *size, *scale, *tileset);
	}
	mud::WfcBlock* EMSCRIPTEN_KEEPALIVE mud_WfcBlock_WfcBlock_5(const mud::vec3* position, const mud::uvec3* size, const mud::vec3* scale, mud::WaveTileset* tileset, bool auto_solve) {
		return new mud::WfcBlock(*position, *size, *scale, *tileset, auto_solve);
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_observe_0(mud::WfcBlock* self) {
		self->observe();
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_propagate_0(mud::WfcBlock* self) {
		self->propagate();
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_reset_0(mud::WfcBlock* self) {
		self->reset();
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_solve_0(mud::WfcBlock* self) {
		self->solve();
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_solve_1(mud::WfcBlock* self, size_t limit) {
		self->solve(limit);
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_update_1(mud::WfcBlock* self, mud::Wave* wave) {
		self->update(*wave);
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_WfcBlock_get_position(mud::WfcBlock* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_set_position(mud::WfcBlock* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::uvec3* EMSCRIPTEN_KEEPALIVE mud_WfcBlock_get_size(mud::WfcBlock* self) {
		static mud::uvec3 temp;
		return (temp = self->m_size, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_set_size(mud::WfcBlock* self, mud::uvec3* value) {
		self->m_size = *value;
	}
	mud::vec3* EMSCRIPTEN_KEEPALIVE mud_WfcBlock_get_scale(mud::WfcBlock* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_set_scale(mud::WfcBlock* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	mud::Aabb* EMSCRIPTEN_KEEPALIVE mud_WfcBlock_get_aabb(mud::WfcBlock* self) {
		static mud::Aabb temp;
		return (temp = self->m_aabb, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock_set_aabb(mud::WfcBlock* self, mud::Aabb* value) {
		self->m_aabb = *value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_WfcBlock___destroy__(mud::WfcBlock* self) {
		delete self;
	}
	
}


