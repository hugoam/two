#include <infra/Api.h>
#include <type/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Index
	mud::Indexer* EMSCRIPTEN_KEEPALIVE mud_Index_indexer_1(mud::Index* self, mud::Type* type) {
		return &self->indexer(*type);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Index___destroy__(mud::Index* self) {
		delete self;
	}
	// Indexer
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_Indexer_get_type(mud::Indexer* self) {
		return &self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Indexer___destroy__(mud::Indexer* self) {
		delete self;
	}
	// Ref
	void EMSCRIPTEN_KEEPALIVE mud_Ref___destroy__(mud::Ref* self) {
		delete self;
	}
	// Type
	mud::Id EMSCRIPTEN_KEEPALIVE mud_Type_get_id(mud::Type* self) {
		return self->m_id;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Type_set_id(mud::Type* self, mud::Id value) {
		self->m_id = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Type_get_name(mud::Type* self) {
		return self->m_name;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Type_set_name(mud::Type* self, const char* value) {
		self->m_name = value;
	}
	size_t EMSCRIPTEN_KEEPALIVE mud_Type_get_size(mud::Type* self) {
		return self->m_size;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Type_set_size(mud::Type* self, size_t value) {
		self->m_size = value;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_Type_get_base(mud::Type* self) {
		return self->m_base;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Type_set_base(mud::Type* self, mud::Type* value) {
		self->m_base = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Type___destroy__(mud::Type* self) {
		delete self;
	}
	// Var
	void EMSCRIPTEN_KEEPALIVE mud_Var___destroy__(mud::Var* self) {
		delete self;
	}
	
}


