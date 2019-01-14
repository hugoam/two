#include <infra/Api.h>
#include <type/Api.h>
#include <refl/Api.h>
#include <ecs/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Entity
	mud::Type* DECL mud_Entity__type() {
		return &mud::type<mud::Entity>();
	}
	mud::Entity* DECL mud_Entity_Entity_0() {
		return new mud::Entity();
	}
	void DECL mud_Entity__destroy(mud::Entity* self) {
		delete self;
	}
	// Prototype
	mud::Type* DECL mud_Prototype__type() {
		return &mud::type<mud::Prototype>();
	}
	void DECL mud_Prototype__destroy(mud::Prototype* self) {
		delete self;
	}
	
}


