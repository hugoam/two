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

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// TileModel
	mud::Type* DECL mud_TileModel__type() {
		return mud::type<mud::TileModel>();
	}
	mud::TileModel* DECL mud_TileModel_TileModel_0() {
		return new mud::TileModel();
	}
	void DECL mud_TileModel__destroy(mud::TileModel* self) {
		delete self;
	}
	// WfcBlock
	mud::Type* DECL mud_WfcBlock__type() {
		return mud::type<mud::WfcBlock>();
	}
	mud::WfcBlock* DECL mud_WfcBlock_WfcBlock_0() {
		return new mud::WfcBlock();
	}
	mud::WfcBlock* DECL mud_WfcBlock_WfcBlock_4(const mud::vec3* position, const mud::uvec3* size, const mud::vec3* scale, mud::WaveTileset* tileset) {
		return new mud::WfcBlock(*position, *size, *scale, *tileset);
	}
	mud::WfcBlock* DECL mud_WfcBlock_WfcBlock_5(const mud::vec3* position, const mud::uvec3* size, const mud::vec3* scale, mud::WaveTileset* tileset, bool auto_solve) {
		return new mud::WfcBlock(*position, *size, *scale, *tileset, auto_solve);
	}
	void DECL mud_WfcBlock_observe_0(mud::WfcBlock* self) {
		self->observe();
	}
	void DECL mud_WfcBlock_propagate_0(mud::WfcBlock* self) {
		self->propagate();
	}
	void DECL mud_WfcBlock_reset_0(mud::WfcBlock* self) {
		self->reset();
	}
	void DECL mud_WfcBlock_solve_0(mud::WfcBlock* self) {
		self->solve();
	}
	void DECL mud_WfcBlock_solve_1(mud::WfcBlock* self, size_t limit) {
		self->solve(limit);
	}
	void DECL mud_WfcBlock_update_1(mud::WfcBlock* self, mud::Wave* wave) {
		self->update(*wave);
	}
	mud::vec3* DECL mud_WfcBlock__get_position(mud::WfcBlock* self) {
		static mud::vec3 temp;
		return (temp = self->m_position, &temp);
	}
	void DECL mud_WfcBlock__set_position(mud::WfcBlock* self, mud::vec3* value) {
		self->m_position = *value;
	}
	mud::uvec3* DECL mud_WfcBlock__get_size(mud::WfcBlock* self) {
		static mud::uvec3 temp;
		return (temp = self->m_size, &temp);
	}
	void DECL mud_WfcBlock__set_size(mud::WfcBlock* self, mud::uvec3* value) {
		self->m_size = *value;
	}
	mud::vec3* DECL mud_WfcBlock__get_scale(mud::WfcBlock* self) {
		static mud::vec3 temp;
		return (temp = self->m_scale, &temp);
	}
	void DECL mud_WfcBlock__set_scale(mud::WfcBlock* self, mud::vec3* value) {
		self->m_scale = *value;
	}
	mud::Aabb* DECL mud_WfcBlock__get_aabb(mud::WfcBlock* self) {
		static mud::Aabb temp;
		return (temp = self->m_aabb, &temp);
	}
	void DECL mud_WfcBlock__set_aabb(mud::WfcBlock* self, mud::Aabb* value) {
		self->m_aabb = *value;
	}
	void DECL mud_WfcBlock__destroy(mud::WfcBlock* self) {
		delete self;
	}
	
}


