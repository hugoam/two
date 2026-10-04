#include <infra/Api.h>
#include <type/Api.h>
#include <tree/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// NodeKey
	two::Type* DECL two_NodeKey__type() {
		return &two::type<two::NodeKey>();
	}
	two::NodeKey* DECL two_NodeKey__construct_0() {
		return new two::NodeKey();
	}
	uint64_t DECL two_NodeKey__get_value(two::NodeKey* self) {
		return self->m_value;
	}
	void DECL two_NodeKey__set_value(two::NodeKey* self, uint64_t value) {
		self->m_value = value;
	}
	void DECL two_NodeKey__destroy(two::NodeKey* self) {
		delete self;
	}
	
}


