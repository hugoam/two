#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// HandlePool
	void EMSCRIPTEN_KEEPALIVE HandlePool___destroy__(mud::HandlePool* self) {
		delete self;
	}
	// Pool
	void EMSCRIPTEN_KEEPALIVE Pool___destroy__(mud::Pool* self) {
		delete self;
	}
	
}


