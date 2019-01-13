#include <infra/Api.h>
#include <type/Api.h>
#include <refl/Api.h>
#include <ecs/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// Complex
	mud::Complex* EMSCRIPTEN_KEEPALIVE Complex_Complex_2(mud::Id id, mud::Type* type) {
		return new mud::Complex(id, *type);
	}
	mud::Complex* EMSCRIPTEN_KEEPALIVE Complex_Complex_3(mud::Id id, mud::Type* type, const std::vector<mud::Ref>* parts) {
		return new mud::Complex(id, *type, *parts);
	}
	bool EMSCRIPTEN_KEEPALIVE Complex_has_part_1(mud::Complex* self, mud::Type* type) {
		return self->has_part(*type);
	}
	mud::Id EMSCRIPTEN_KEEPALIVE Complex_get_id(mud::Complex* self) {
		return self->m_id;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE Complex_get_type(mud::Complex* self) {
		return &self->m_type;
	}
	mud::Prototype* EMSCRIPTEN_KEEPALIVE Complex_get_prototype(mud::Complex* self) {
		return &self->m_prototype;
	}
	void EMSCRIPTEN_KEEPALIVE Complex___destroy__(mud::Complex* self) {
		delete self;
	}
	// Entity
	mud::Entity* EMSCRIPTEN_KEEPALIVE Entity_Entity_0() {
		return new mud::Entity();
	}
	void EMSCRIPTEN_KEEPALIVE Entity___destroy__(mud::Entity* self) {
		delete self;
	}
	// Prototype
	void EMSCRIPTEN_KEEPALIVE Prototype___destroy__(mud::Prototype* self) {
		delete self;
	}
	
}


