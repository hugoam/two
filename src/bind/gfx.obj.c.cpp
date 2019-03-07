#include <infra/Api.h>
#include <type/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gfx-obj/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// ImporterOBJ
	mud::Type* DECL mud_ImporterOBJ__type() {
		return &mud::type<mud::ImporterOBJ>();
	}
	mud::ImporterOBJ* DECL mud_ImporterOBJ__construct_1(mud::GfxSystem* gfx) {
		return new mud::ImporterOBJ(*gfx);
	}
	void DECL mud_ImporterOBJ_import_3(mud::ImporterOBJ* self, mud::Import* import, const char* filepath, const mud::ImportConfig* config) {
		self->import(*import, filepath, *config);
	}
	void DECL mud_ImporterOBJ_import_model_3(mud::ImporterOBJ* self, mud::Model* model, const char* filepath, const mud::ImportConfig* config) {
		self->import_model(*model, filepath, *config);
	}
	void DECL mud_ImporterOBJ_import_prefab_3(mud::ImporterOBJ* self, mud::Prefab* prefab, const char* filepath, const mud::ImportConfig* config) {
		self->import_prefab(*prefab, filepath, *config);
	}
	void DECL mud_ImporterOBJ_repack_2(mud::ImporterOBJ* self, const char* filepath, const mud::ImportConfig* config) {
		self->repack(filepath, *config);
	}
	void DECL mud_ImporterOBJ__destroy(mud::ImporterOBJ* self) {
		delete self;
	}
	
}


