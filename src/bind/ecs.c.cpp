#include <infra/Api.h>
#include <pool/Api.h>
#include <type/Api.h>
#include <ecs/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Entity
	two::Type* DECL two_Entity__type() {
		return &two::type<two::Entity>();
	}
	two::Entity* DECL two_Entity__construct_0() {
		return new two::Entity();
	}
	void DECL two_Entity__destroy(two::Entity* self) {
		delete self;
	}
	// Entt
	two::Type* DECL two_Entt__type() {
		return &two::type<two::Entt>();
	}
	two::Entt* DECL two_Entt__construct_0() {
		return new two::Entt();
	}
	void DECL two_Entt__destroy(two::Entt* self) {
		delete self;
	}
	// OEntt
	two::Type* DECL two_OEntt__type() {
		return &two::type<two::OEntt>();
	}
	void DECL two_OEntt__destroy(two::OEntt* self) {
		delete self;
	}
	
}


