#include <infra/Api.h>
#include <jobs/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// JobSystem
	two::Type* DECL two_JobSystem__type() {
		return &two::type<two::JobSystem>();
	}
	void DECL two_JobSystem__destroy(two::JobSystem* self) {
		delete self;
	}
	
}


