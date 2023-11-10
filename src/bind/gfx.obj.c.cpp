#include <infra/Api.h>
#include <type/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gfx-obj/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// ImporterOBJ
	two::Type* DECL two_ImporterOBJ__type() {
		return &two::type<two::ImporterOBJ>();
	}
	two::ImporterOBJ* DECL two_ImporterOBJ__construct_1(two::GfxSystem* gfx) {
		return new two::ImporterOBJ(*gfx);
	}
	void DECL two_ImporterOBJ_import_3(two::ImporterOBJ* self, two::Import* import, const char* filepath, const two::ImportConfig* config) {
		self->import(*import, filepath, *config);
	}
	void DECL two_ImporterOBJ_import_model_3(two::ImporterOBJ* self, two::Model* model, const char* filepath, const two::ImportConfig* config) {
		self->import_model(*model, filepath, *config);
	}
	void DECL two_ImporterOBJ_import_prefab_3(two::ImporterOBJ* self, two::Prefab* prefab, const char* filepath, const two::ImportConfig* config) {
		self->import_prefab(*prefab, filepath, *config);
	}
	void DECL two_ImporterOBJ_repack_2(two::ImporterOBJ* self, const char* filepath, const two::ImportConfig* config) {
		self->repack(filepath, *config);
	}
	void DECL two_ImporterOBJ__destroy(two::ImporterOBJ* self) {
		delete self;
	}
	// ImporterPLY
	two::Type* DECL two_ImporterPLY__type() {
		return &two::type<two::ImporterPLY>();
	}
	two::ImporterPLY* DECL two_ImporterPLY__construct_1(two::GfxSystem* gfx) {
		return new two::ImporterPLY(*gfx);
	}
	void DECL two_ImporterPLY_import_3(two::ImporterPLY* self, two::Import* import, const char* filepath, const two::ImportConfig* config) {
		self->import(*import, filepath, *config);
	}
	void DECL two_ImporterPLY_import_model_3(two::ImporterPLY* self, two::Model* model, const char* filepath, const two::ImportConfig* config) {
		self->import_model(*model, filepath, *config);
	}
	void DECL two_ImporterPLY_import_prefab_3(two::ImporterPLY* self, two::Prefab* prefab, const char* filepath, const two::ImportConfig* config) {
		self->import_prefab(*prefab, filepath, *config);
	}
	void DECL two_ImporterPLY_repack_2(two::ImporterPLY* self, const char* filepath, const two::ImportConfig* config) {
		self->repack(filepath, *config);
	}
	void DECL two_ImporterPLY__destroy(two::ImporterPLY* self) {
		delete self;
	}
	
}


