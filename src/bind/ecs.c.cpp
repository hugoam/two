#include <infra/Api.h>
#include <pool/Api.h>
#include <type/Api.h>
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
	mud::Entity* DECL mud_Entity__construct_0() {
		return new mud::Entity();
	}
	void DECL mud_Entity__destroy(mud::Entity* self) {
		delete self;
	}
	// Entt
	mud::Type* DECL mud_Entt__type() {
		return &mud::type<mud::Entt>();
	}
	mud::Entt* DECL mud_Entt__construct_0() {
		return new mud::Entt();
	}
	void DECL mud_Entt__destroy(mud::Entt* self) {
		delete self;
	}
	// OEntt
	mud::Type* DECL mud_OEntt__type() {
		return &mud::type<mud::OEntt>();
	}
	void DECL mud_OEntt__destroy(mud::OEntt* self) {
		delete self;
	}
	
}


