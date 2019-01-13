#include <infra/Api.h>
#include <jobs/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// JobSystem
	void DECL mud_JobSystem__destroy(mud::JobSystem* self) {
		delete self;
	}
	
}


