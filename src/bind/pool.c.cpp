#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Pool
	two::Type* DECL two_Pool__type() {
		return &two::type<two::Pool>();
	}
	void DECL two_Pool__destroy(two::Pool* self) {
		delete self;
	}
	// HandlePool
	two::Type* DECL two_HandlePool__type() {
		return &two::type<two::HandlePool>();
	}
	void DECL two_HandlePool__destroy(two::HandlePool* self) {
		delete self;
	}
	
}


