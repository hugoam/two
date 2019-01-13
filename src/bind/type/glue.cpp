#include <infra/Api.h>
#include <type/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Index
	mud::Indexer* EMSCRIPTEN_KEEPALIVE Index_indexer_1(mud::Index* self, mud::Type* type) {
		return &self->indexer(*type);
	}
	void EMSCRIPTEN_KEEPALIVE Index___destroy__(mud::Index* self) {
		delete self;
	}
	// Indexer
	mud::Type* EMSCRIPTEN_KEEPALIVE Indexer_get_type(mud::Indexer* self) {
		return &self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE Indexer___destroy__(mud::Indexer* self) {
		delete self;
	}
	// Ref
	void EMSCRIPTEN_KEEPALIVE Ref___destroy__(mud::Ref* self) {
		delete self;
	}
	// Type
	mud::Id EMSCRIPTEN_KEEPALIVE Type_get_id(mud::Type* self) {
		return self->m_id;
	}
	void EMSCRIPTEN_KEEPALIVE Type_set_id(mud::Type* self, mud::Id value) {
		self->m_id = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE Type_get_name(mud::Type* self) {
		return self->m_name;
	}
	void EMSCRIPTEN_KEEPALIVE Type_set_name(mud::Type* self, const char* value) {
		self->m_name = value;
	}
	size_t EMSCRIPTEN_KEEPALIVE Type_get_size(mud::Type* self) {
		return self->m_size;
	}
	void EMSCRIPTEN_KEEPALIVE Type_set_size(mud::Type* self, size_t value) {
		self->m_size = value;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE Type_get_base(mud::Type* self) {
		return self->m_base;
	}
	void EMSCRIPTEN_KEEPALIVE Type_set_base(mud::Type* self, mud::Type* value) {
		self->m_base = value;
	}
	void EMSCRIPTEN_KEEPALIVE Type___destroy__(mud::Type* self) {
		delete self;
	}
	// Var
	void EMSCRIPTEN_KEEPALIVE Var___destroy__(mud::Var* self) {
		delete self;
	}
	
}


