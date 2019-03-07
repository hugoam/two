#include <infra/Api.h>
#include <type/Api.h>
#include <refl/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gltf/Api.h>
#include <gfx-gltf/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// ImporterGltf
	mud::Type* DECL mud_ImporterGltf__type() {
		return &mud::type<mud::ImporterGltf>();
	}
	mud::ImporterGltf* DECL mud_ImporterGltf__construct_1(mud::GfxSystem* gfx) {
		return new mud::ImporterGltf(*gfx);
	}
	void DECL mud_ImporterGltf_import_3(mud::ImporterGltf* self, mud::Import* import, const char* filepath, const mud::ImportConfig* config) {
		self->import(*import, filepath, *config);
	}
	void DECL mud_ImporterGltf_import_model_3(mud::ImporterGltf* self, mud::Model* model, const char* filepath, const mud::ImportConfig* config) {
		self->import_model(*model, filepath, *config);
	}
	void DECL mud_ImporterGltf_import_prefab_3(mud::ImporterGltf* self, mud::Prefab* prefab, const char* filepath, const mud::ImportConfig* config) {
		self->import_prefab(*prefab, filepath, *config);
	}
	void DECL mud_ImporterGltf_repack_2(mud::ImporterGltf* self, const char* filepath, const mud::ImportConfig* config) {
		self->repack(filepath, *config);
	}
	void DECL mud_ImporterGltf__destroy(mud::ImporterGltf* self) {
		delete self;
	}
	
}


