#include <infra/Api.h>
#include <type/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Index
	mud::Indexer* DECL mud_Index_indexer_1(mud::Index* self, mud::Type* type) {
		return &self->indexer(*type);
	}
	void DECL mud_Index__destroy(mud::Index* self) {
		delete self;
	}
	// Indexer
	mud::Type* DECL mud_Indexer__get_type(mud::Indexer* self) {
		return &self->m_type;
	}
	void DECL mud_Indexer__destroy(mud::Indexer* self) {
		delete self;
	}
	// Ref
	void DECL mud_Ref__destroy(mud::Ref* self) {
		delete self;
	}
	// Type
	mud::Id DECL mud_Type__get_id(mud::Type* self) {
		return self->m_id;
	}
	void DECL mud_Type__set_id(mud::Type* self, mud::Id value) {
		self->m_id = value;
	}
	const char* DECL mud_Type__get_name(mud::Type* self) {
		return self->m_name;
	}
	void DECL mud_Type__set_name(mud::Type* self, const char* value) {
		self->m_name = value;
	}
	size_t DECL mud_Type__get_size(mud::Type* self) {
		return self->m_size;
	}
	void DECL mud_Type__set_size(mud::Type* self, size_t value) {
		self->m_size = value;
	}
	mud::Type* DECL mud_Type__get_base(mud::Type* self) {
		return self->m_base;
	}
	void DECL mud_Type__set_base(mud::Type* self, mud::Type* value) {
		self->m_base = value;
	}
	void DECL mud_Type__destroy(mud::Type* self) {
		delete self;
	}
	// Var
	void DECL mud_Var__destroy(mud::Var* self) {
		delete self;
	}
	
}


