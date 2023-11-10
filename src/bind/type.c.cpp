#include <infra/Api.h>
#include <type/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Type
	two::Type* DECL two_Type__type() {
		return &two::type<two::Type>();
	}
	uint32_t DECL two_Type__get_id(two::Type* self) {
		return self->m_id;
	}
	void DECL two_Type__set_id(two::Type* self, uint32_t value) {
		self->m_id = value;
	}
	const char* DECL two_Type__get_name(two::Type* self) {
		return self->m_name;
	}
	void DECL two_Type__set_name(two::Type* self, const char* value) {
		self->m_name = value;
	}
	size_t DECL two_Type__get_size(two::Type* self) {
		return self->m_size;
	}
	void DECL two_Type__set_size(two::Type* self, size_t value) {
		self->m_size = value;
	}
	two::Type* DECL two_Type__get_base(two::Type* self) {
		return self->m_base;
	}
	void DECL two_Type__set_base(two::Type* self, two::Type* value) {
		self->m_base = value;
	}
	void DECL two_Type__destroy(two::Type* self) {
		delete self;
	}
	// Ref
	two::Type* DECL two_Ref__type() {
		return &two::type<two::Ref>();
	}
	two::Ref* DECL two_Ref__construct_0() {
		return new two::Ref();
	}
	two::Ref* DECL two_Ref__construct_2(void* value, const two::Type* type) {
		return new two::Ref(value, *type);
	}
	const two::Type* DECL two_Ref__get_type(two::Ref* self) {
		return self->m_type;
	}
	void DECL two_Ref__set_type(two::Ref* self, const two::Type* value) {
		self->m_type = value;
	}
	void* DECL two_Ref__get_value(two::Ref* self) {
		return self->m_value;
	}
	void DECL two_Ref__set_value(two::Ref* self, void* value) {
		self->m_value = value;
	}
	void DECL two_Ref__destroy(two::Ref* self) {
		delete self;
	}
	// Var
	two::Type* DECL two_Var__type() {
		return &two::type<two::Var>();
	}
	void DECL two_Var__destroy(two::Var* self) {
		delete self;
	}
	// Indexer
	two::Type* DECL two_Indexer__type() {
		return &two::type<two::Indexer>();
	}
	const two::Type* DECL two_Indexer__get_type(two::Indexer* self) {
		return self->m_type;
	}
	void DECL two_Indexer__set_type(two::Indexer* self, const two::Type* value) {
		self->m_type = value;
	}
	void DECL two_Indexer__destroy(two::Indexer* self) {
		delete self;
	}
	// Index
	two::Type* DECL two_Index__type() {
		return &two::type<two::Index>();
	}
	two::Indexer* DECL two_Index_indexer_1(two::Index* self, const two::Type* type) {
		return &self->indexer(*type);
	}
	void DECL two_Index__destroy(two::Index* self) {
		delete self;
	}
	// Prototype
	two::Type* DECL two_Prototype__type() {
		return &two::type<two::Prototype>();
	}
	void DECL two_Prototype__destroy(two::Prototype* self) {
		delete self;
	}
	two::Ref* DECL two_indexed_2(const two::Type* type, uint32_t id) {
		static two::Ref temp;
		return (temp = two::indexed(*type, id), &temp);
	}
	
}


