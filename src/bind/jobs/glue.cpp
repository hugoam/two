#include <infra/Api.h>
#include <jobs/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// JobSystem
	void EMSCRIPTEN_KEEPALIVE mud_JobSystem___destroy__(mud::JobSystem* self) {
		delete self;
	}
	
}


