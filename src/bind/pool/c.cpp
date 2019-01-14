#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// HandlePool
	mud::Type* DECL mud_HandlePool__type() {
		return &mud::type<mud::HandlePool>();
	}
	void DECL mud_HandlePool__destroy(mud::HandlePool* self) {
		delete self;
	}
	// Pool
	mud::Type* DECL mud_Pool__type() {
		return &mud::type<mud::Pool>();
	}
	void DECL mud_Pool__destroy(mud::Pool* self) {
		delete self;
	}
	
}


