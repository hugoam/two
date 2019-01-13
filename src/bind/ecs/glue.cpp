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
#include <cstdint>


extern "C" {
	
	// Complex
	mud::Complex* DECL mud_Complex_Complex_2(mud::Id id, mud::Type* type) {
		return new mud::Complex(id, *type);
	}
	mud::Complex* DECL mud_Complex_Complex_3(mud::Id id, mud::Type* type, const std::vector<mud::Ref>* parts) {
		return new mud::Complex(id, *type, *parts);
	}
	bool DECL mud_Complex_has_part_1(mud::Complex* self, mud::Type* type) {
		return self->has_part(*type);
	}
	mud::Id DECL mud_Complex__get_id(mud::Complex* self) {
		return self->m_id;
	}
	void DECL mud_Complex__set_id(mud::Complex* self, mud::Id value) {
		self->m_id = value;
	}
	mud::Type* DECL mud_Complex__get_type(mud::Complex* self) {
		return &self->m_type;
	}
	mud::Prototype* DECL mud_Complex__get_prototype(mud::Complex* self) {
		return &self->m_prototype;
	}
	void DECL mud_Complex__destroy(mud::Complex* self) {
		delete self;
	}
	// Entity
	mud::Entity* DECL mud_Entity_Entity_0() {
		return new mud::Entity();
	}
	void DECL mud_Entity__destroy(mud::Entity* self) {
		delete self;
	}
	// Prototype
	void DECL mud_Prototype__destroy(mud::Prototype* self) {
		delete self;
	}
	
}


