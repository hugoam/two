#include <infra/Api.h>
#include <type/Api.h>
#include <refl/Api.h>
#include <srlz/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <gfx/Api.h>
#include <gltf/Api.h>
#include <gfx-gltf/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// ImporterGltf
	two::Type* DECL two_ImporterGltf__type() {
		return &two::type<two::ImporterGltf>();
	}
	two::ImporterGltf* DECL two_ImporterGltf__construct_1(two::GfxSystem* gfx) {
		return new two::ImporterGltf(*gfx);
	}
	void DECL two_ImporterGltf_import_3(two::ImporterGltf* self, two::Import* import, const char* filepath, const two::ImportConfig* config) {
		self->import(*import, filepath, *config);
	}
	void DECL two_ImporterGltf_import_model_3(two::ImporterGltf* self, two::Model* model, const char* filepath, const two::ImportConfig* config) {
		self->import_model(*model, filepath, *config);
	}
	void DECL two_ImporterGltf_import_prefab_3(two::ImporterGltf* self, two::Prefab* prefab, const char* filepath, const two::ImportConfig* config) {
		self->import_prefab(*prefab, filepath, *config);
	}
	void DECL two_ImporterGltf_repack_2(two::ImporterGltf* self, const char* filepath, const two::ImportConfig* config) {
		self->repack(filepath, *config);
	}
	void DECL two_ImporterGltf__destroy(two::ImporterGltf* self) {
		delete self;
	}
	
}


