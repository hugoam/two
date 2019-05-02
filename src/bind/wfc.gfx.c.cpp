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

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// TileModel
	two::Type* DECL two_TileModel__type() {
		return &two::type<two::TileModel>();
	}
	two::TileModel* DECL two_TileModel__construct_0() {
		return new two::TileModel();
	}
	void DECL two_TileModel__destroy(two::TileModel* self) {
		delete self;
	}
	// WfcBlock
	two::Type* DECL two_WfcBlock__type() {
		return &two::type<two::WfcBlock>();
	}
	two::WfcBlock* DECL two_WfcBlock__construct_0() {
		return new two::WfcBlock();
	}
	two::WfcBlock* DECL two_WfcBlock__construct_4(const two::vec3* position, const two::uvec3* size, const two::vec3* scale, two::WaveTileset* tileset) {
		return new two::WfcBlock(*position, *size, *scale, *tileset);
	}
	two::WfcBlock* DECL two_WfcBlock__construct_5(const two::vec3* position, const two::uvec3* size, const two::vec3* scale, two::WaveTileset* tileset, bool auto_solve) {
		return new two::WfcBlock(*position, *size, *scale, *tileset, auto_solve);
	}
	void DECL two_WfcBlock_reset_0(two::WfcBlock* self) {
		self->reset();
	}
	void DECL two_WfcBlock_observe_0(two::WfcBlock* self) {
		self->observe();
	}
	void DECL two_WfcBlock_propagate_0(two::WfcBlock* self) {
		self->propagate();
	}
	void DECL two_WfcBlock_solve_0(two::WfcBlock* self) {
		self->solve();
	}
	void DECL two_WfcBlock_solve_1(two::WfcBlock* self, size_t limit) {
		self->solve(limit);
	}
	void DECL two_WfcBlock_update_1(two::WfcBlock* self, two::Wave* wave) {
		self->update(*wave);
	}
	two::vec3* DECL two_WfcBlock__get_position(two::WfcBlock* self) {
		return &self->m_position;
	}
	void DECL two_WfcBlock__set_position(two::WfcBlock* self, two::vec3* value) {
		self->m_position = *value;
	}
	two::uvec3* DECL two_WfcBlock__get_size(two::WfcBlock* self) {
		return &self->m_size;
	}
	void DECL two_WfcBlock__set_size(two::WfcBlock* self, two::uvec3* value) {
		self->m_size = *value;
	}
	two::vec3* DECL two_WfcBlock__get_scale(two::WfcBlock* self) {
		return &self->m_scale;
	}
	void DECL two_WfcBlock__set_scale(two::WfcBlock* self, two::vec3* value) {
		self->m_scale = *value;
	}
	two::Aabb* DECL two_WfcBlock__get_aabb(two::WfcBlock* self) {
		return &self->m_aabb;
	}
	void DECL two_WfcBlock__set_aabb(two::WfcBlock* self, two::Aabb* value) {
		self->m_aabb = *value;
	}
	void DECL two_WfcBlock__destroy(two::WfcBlock* self) {
		delete self;
	}
	
}


