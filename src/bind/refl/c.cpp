#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <refl/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Call
	mud::Call* DECL mud_Call_Call_0() {
		return new mud::Call();
	}
	mud::Call* DECL mud_Call_Call_2(const mud::Callable* callable, std::vector<mud::Var>* arguments) {
		return new mud::Call(*callable, *arguments);
	}
	mud::Var* DECL mud_Call__get_result(mud::Call* self) {
		return &self->m_result;
	}
	void DECL mud_Call__destroy(mud::Call* self) {
		delete self;
	}
	// Callable
	void DECL mud_Callable__destroy(mud::Callable* self) {
		delete self;
	}
	// Class
	void DECL mud_Class__destroy(mud::Class* self) {
		delete self;
	}
	// Convert
	void DECL mud_Convert__destroy(mud::Convert* self) {
		delete self;
	}
	// Creator
	mud::Type* DECL mud_Creator__get_type(mud::Creator* self) {
		return &self->m_type;
	}
	bool DECL mud_Creator__get_construct(mud::Creator* self) {
		return self->m_construct;
	}
	void DECL mud_Creator__set_construct(mud::Creator* self, bool value) {
		self->m_construct = value;
	}
	mud::Type* DECL mud_Creator__get_prototype(mud::Creator* self) {
		return self->m_prototype;
	}
	void DECL mud_Creator__set_prototype(mud::Creator* self, mud::Type* value) {
		self->m_prototype = value;
	}
	mud::Injector* DECL mud_Creator__get_injector(mud::Creator* self) {
		return &self->injector();
	}
	void DECL mud_Creator__destroy(mud::Creator* self) {
		delete self;
	}
	// Enum
	void DECL mud_Enum__destroy(mud::Enum* self) {
		delete self;
	}
	// Member
	void DECL mud_Member__destroy(mud::Member* self) {
		delete self;
	}
	// Meta
	void DECL mud_Meta__destroy(mud::Meta* self) {
		delete self;
	}
	// Module
	const char* DECL mud_Module__get_name(mud::Module* self) {
		return self->m_name;
	}
	void DECL mud_Module__set_name(mud::Module* self, const char* value) {
		self->m_name = value;
	}
	const char* DECL mud_Module__get_path(mud::Module* self) {
		return self->m_path;
	}
	void DECL mud_Module__set_path(mud::Module* self, const char* value) {
		self->m_path = value;
	}
	void DECL mud_Module__destroy(mud::Module* self) {
		delete self;
	}
	// Namespace
	void DECL mud_Namespace__destroy(mud::Namespace* self) {
		delete self;
	}
	// Operator
	mud::Operator* DECL mud_Operator_Operator_0() {
		return new mud::Operator();
	}
	mud::Function* DECL mud_Operator__get_function(mud::Operator* self) {
		return self->m_function;
	}
	void DECL mud_Operator__set_function(mud::Operator* self, mud::Function* value) {
		self->m_function = value;
	}
	mud::Type* DECL mud_Operator__get_type(mud::Operator* self) {
		return self->m_type;
	}
	void DECL mud_Operator__set_type(mud::Operator* self, mud::Type* value) {
		self->m_type = value;
	}
	const char* DECL mud_Operator__get_name(mud::Operator* self) {
		return self->m_name;
	}
	void DECL mud_Operator__set_name(mud::Operator* self, const char* value) {
		self->m_name = value;
	}
	const char* DECL mud_Operator__get_sign(mud::Operator* self) {
		return self->m_sign;
	}
	void DECL mud_Operator__set_sign(mud::Operator* self, const char* value) {
		self->m_sign = value;
	}
	void DECL mud_Operator__destroy(mud::Operator* self) {
		delete self;
	}
	// Param
	void DECL mud_Param__destroy(mud::Param* self) {
		delete self;
	}
	// Signature
	void DECL mud_Signature__destroy(mud::Signature* self) {
		delete self;
	}
	// Static
	void DECL mud_Static__destroy(mud::Static* self) {
		delete self;
	}
	// System
	void DECL mud_System__destroy(mud::System* self) {
		delete self;
	}
	// Constructor
	void DECL mud_Constructor__destroy(mud::Constructor* self) {
		delete self;
	}
	// CopyConstructor
	void DECL mud_CopyConstructor__destroy(mud::CopyConstructor* self) {
		delete self;
	}
	// Destructor
	void DECL mud_Destructor__destroy(mud::Destructor* self) {
		delete self;
	}
	// Function
	void DECL mud_Function__destroy(mud::Function* self) {
		delete self;
	}
	// Injector
	void DECL mud_Injector__destroy(mud::Injector* self) {
		delete self;
	}
	// Method
	void DECL mud_Method__destroy(mud::Method* self) {
		delete self;
	}
	// TypeClass
	mud::TypeClass DECL mud_TypeClass_None() {
		return mud::TypeClass::None;
	}
	mud::TypeClass DECL mud_TypeClass_Object() {
		return mud::TypeClass::Object;
	}
	mud::TypeClass DECL mud_TypeClass_Struct() {
		return mud::TypeClass::Struct;
	}
	mud::TypeClass DECL mud_TypeClass_Sequence() {
		return mud::TypeClass::Sequence;
	}
	mud::TypeClass DECL mud_TypeClass_BaseType() {
		return mud::TypeClass::BaseType;
	}
	mud::TypeClass DECL mud_TypeClass_Enum() {
		return mud::TypeClass::Enum;
	}
	
}


