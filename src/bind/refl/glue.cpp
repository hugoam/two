#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <refl/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Call
	mud::Call* EMSCRIPTEN_KEEPALIVE mud_Call_Call_0() {
		return new mud::Call();
	}
	mud::Call* EMSCRIPTEN_KEEPALIVE mud_Call_Call_2(const mud::Callable* callable, std::vector<mud::Var>* arguments) {
		return new mud::Call(*callable, *arguments);
	}
	mud::Var* EMSCRIPTEN_KEEPALIVE mud_Call_get_result(mud::Call* self) {
		return &self->m_result;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Call___destroy__(mud::Call* self) {
		delete self;
	}
	// Callable
	void EMSCRIPTEN_KEEPALIVE mud_Callable___destroy__(mud::Callable* self) {
		delete self;
	}
	// Class
	void EMSCRIPTEN_KEEPALIVE mud_Class___destroy__(mud::Class* self) {
		delete self;
	}
	// Convert
	void EMSCRIPTEN_KEEPALIVE mud_Convert___destroy__(mud::Convert* self) {
		delete self;
	}
	// Creator
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_Creator_get_type(mud::Creator* self) {
		return &self->m_type;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Creator_get_construct(mud::Creator* self) {
		return self->m_construct;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Creator_set_construct(mud::Creator* self, bool value) {
		self->m_construct = value;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_Creator_get_prototype(mud::Creator* self) {
		return self->m_prototype;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Creator_set_prototype(mud::Creator* self, mud::Type* value) {
		self->m_prototype = value;
	}
	mud::Injector* EMSCRIPTEN_KEEPALIVE mud_Creator_get_injector(mud::Creator* self) {
		return &self->injector();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Creator___destroy__(mud::Creator* self) {
		delete self;
	}
	// Enum
	void EMSCRIPTEN_KEEPALIVE mud_Enum___destroy__(mud::Enum* self) {
		delete self;
	}
	// Member
	void EMSCRIPTEN_KEEPALIVE mud_Member___destroy__(mud::Member* self) {
		delete self;
	}
	// Meta
	void EMSCRIPTEN_KEEPALIVE mud_Meta___destroy__(mud::Meta* self) {
		delete self;
	}
	// Module
	const char* EMSCRIPTEN_KEEPALIVE mud_Module_get_name(mud::Module* self) {
		return self->m_name;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Module_set_name(mud::Module* self, const char* value) {
		self->m_name = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Module_get_path(mud::Module* self) {
		return self->m_path;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Module_set_path(mud::Module* self, const char* value) {
		self->m_path = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Module___destroy__(mud::Module* self) {
		delete self;
	}
	// Namespace
	void EMSCRIPTEN_KEEPALIVE mud_Namespace___destroy__(mud::Namespace* self) {
		delete self;
	}
	// Operator
	mud::Operator* EMSCRIPTEN_KEEPALIVE mud_Operator_Operator_0() {
		return new mud::Operator();
	}
	mud::Function* EMSCRIPTEN_KEEPALIVE mud_Operator_get_function(mud::Operator* self) {
		return self->m_function;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Operator_set_function(mud::Operator* self, mud::Function* value) {
		self->m_function = value;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE mud_Operator_get_type(mud::Operator* self) {
		return self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Operator_set_type(mud::Operator* self, mud::Type* value) {
		self->m_type = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Operator_get_name(mud::Operator* self) {
		return self->m_name;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Operator_set_name(mud::Operator* self, const char* value) {
		self->m_name = value;
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Operator_get_sign(mud::Operator* self) {
		return self->m_sign;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Operator_set_sign(mud::Operator* self, const char* value) {
		self->m_sign = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Operator___destroy__(mud::Operator* self) {
		delete self;
	}
	// Param
	void EMSCRIPTEN_KEEPALIVE mud_Param___destroy__(mud::Param* self) {
		delete self;
	}
	// Signature
	void EMSCRIPTEN_KEEPALIVE mud_Signature___destroy__(mud::Signature* self) {
		delete self;
	}
	// Static
	void EMSCRIPTEN_KEEPALIVE mud_Static___destroy__(mud::Static* self) {
		delete self;
	}
	// System
	void EMSCRIPTEN_KEEPALIVE mud_System___destroy__(mud::System* self) {
		delete self;
	}
	// Constructor
	void EMSCRIPTEN_KEEPALIVE mud_Constructor___destroy__(mud::Constructor* self) {
		delete self;
	}
	// CopyConstructor
	void EMSCRIPTEN_KEEPALIVE mud_CopyConstructor___destroy__(mud::CopyConstructor* self) {
		delete self;
	}
	// Destructor
	void EMSCRIPTEN_KEEPALIVE mud_Destructor___destroy__(mud::Destructor* self) {
		delete self;
	}
	// Function
	void EMSCRIPTEN_KEEPALIVE mud_Function___destroy__(mud::Function* self) {
		delete self;
	}
	// Injector
	void EMSCRIPTEN_KEEPALIVE mud_Injector___destroy__(mud::Injector* self) {
		delete self;
	}
	// Method
	void EMSCRIPTEN_KEEPALIVE mud_Method___destroy__(mud::Method* self) {
		delete self;
	}
	// TypeClass
	mud::TypeClass EMSCRIPTEN_KEEPALIVE mud_TypeClass_None() {
		return mud::TypeClass::None;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE mud_TypeClass_Object() {
		return mud::TypeClass::Object;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE mud_TypeClass_Struct() {
		return mud::TypeClass::Struct;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE mud_TypeClass_Sequence() {
		return mud::TypeClass::Sequence;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE mud_TypeClass_BaseType() {
		return mud::TypeClass::BaseType;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE mud_TypeClass_Enum() {
		return mud::TypeClass::Enum;
	}
	
}


