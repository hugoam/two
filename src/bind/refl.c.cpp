#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <refl/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// QualType
	two::Type* DECL two_QualType__type() {
		return &two::type<two::QualType>();
	}
	two::QualType* DECL two_QualType__construct_0() {
		return new two::QualType();
	}
	void DECL two_QualType__destroy(two::QualType* self) {
		delete self;
	}
	// Param
	two::Type* DECL two_Param__type() {
		return &two::type<two::Param>();
	}
	void DECL two_Param__destroy(two::Param* self) {
		delete self;
	}
	// Signature
	two::Type* DECL two_Signature__type() {
		return &two::type<two::Signature>();
	}
	void DECL two_Signature__destroy(two::Signature* self) {
		delete self;
	}
	// Callable
	two::Type* DECL two_Callable__type() {
		return &two::type<two::Callable>();
	}
	void DECL two_Callable__destroy(two::Callable* self) {
		delete self;
	}
	// Function
	two::Type* DECL two_Function__type() {
		return &two::type<two::Function>();
	}
	void DECL two_Function__destroy(two::Function* self) {
		delete self;
	}
	// Operator
	two::Type* DECL two_Operator__type() {
		return &two::type<two::Operator>();
	}
	two::Operator* DECL two_Operator__construct_0() {
		return new two::Operator();
	}
	two::Function* DECL two_Operator__get_function(two::Operator* self) {
		return self->m_function;
	}
	void DECL two_Operator__set_function(two::Operator* self, two::Function* value) {
		self->m_function = value;
	}
	two::Type* DECL two_Operator__get_type(two::Operator* self) {
		return self->m_type;
	}
	void DECL two_Operator__set_type(two::Operator* self, two::Type* value) {
		self->m_type = value;
	}
	const char* DECL two_Operator__get_name(two::Operator* self) {
		return self->m_name;
	}
	void DECL two_Operator__set_name(two::Operator* self, const char* value) {
		self->m_name = value;
	}
	const char* DECL two_Operator__get_sign(two::Operator* self) {
		return self->m_sign;
	}
	void DECL two_Operator__set_sign(two::Operator* self, const char* value) {
		self->m_sign = value;
	}
	void DECL two_Operator__destroy(two::Operator* self) {
		delete self;
	}
	// Method
	two::Type* DECL two_Method__type() {
		return &two::type<two::Method>();
	}
	void DECL two_Method__destroy(two::Method* self) {
		delete self;
	}
	// Constructor
	two::Type* DECL two_Constructor__type() {
		return &two::type<two::Constructor>();
	}
	void DECL two_Constructor__destroy(two::Constructor* self) {
		delete self;
	}
	// CopyConstructor
	two::Type* DECL two_CopyConstructor__type() {
		return &two::type<two::CopyConstructor>();
	}
	void DECL two_CopyConstructor__destroy(two::CopyConstructor* self) {
		delete self;
	}
	// Destructor
	two::Type* DECL two_Destructor__type() {
		return &two::type<two::Destructor>();
	}
	void DECL two_Destructor__destroy(two::Destructor* self) {
		delete self;
	}
	// Call
	two::Type* DECL two_Call__type() {
		return &two::type<two::Call>();
	}
	two::Call* DECL two_Call__construct_0() {
		return new two::Call();
	}
	void** DECL two_Call__get_vargs(two::Call* self) {
		return (void**)self->m_vargs.data();
	}
	two::Var* DECL two_Call__get_result(two::Call* self) {
		return &self->m_result;
	}
	void DECL two_Call__destroy(two::Call* self) {
		delete self;
	}
	// Meta
	two::Type* DECL two_Meta__type() {
		return &two::type<two::Meta>();
	}
	void DECL two_Meta__destroy(two::Meta* self) {
		delete self;
	}
	// Convert
	two::Type* DECL two_Convert__type() {
		return &two::type<two::Convert>();
	}
	void DECL two_Convert__destroy(two::Convert* self) {
		delete self;
	}
	// Static
	two::Type* DECL two_Static__type() {
		return &two::type<two::Static>();
	}
	void DECL two_Static__destroy(two::Static* self) {
		delete self;
	}
	// Member
	two::Type* DECL two_Member__type() {
		return &two::type<two::Member>();
	}
	void DECL two_Member__destroy(two::Member* self) {
		delete self;
	}
	// Class
	two::Type* DECL two_Class__type() {
		return &two::type<two::Class>();
	}
	void DECL two_Class__destroy(two::Class* self) {
		delete self;
	}
	// Enum
	two::Type* DECL two_Enum__type() {
		return &two::type<two::Enum>();
	}
	void DECL two_Enum__destroy(two::Enum* self) {
		delete self;
	}
	// Injector
	two::Type* DECL two_Injector__type() {
		return &two::type<two::Injector>();
	}
	void DECL two_Injector__destroy(two::Injector* self) {
		delete self;
	}
	// Creator
	two::Type* DECL two_Creator__type() {
		return &two::type<two::Creator>();
	}
	two::Type* DECL two_Creator__get_type(two::Creator* self) {
		return &self->m_type;
	}
	bool DECL two_Creator__get_construct(two::Creator* self) {
		return self->m_construct;
	}
	void DECL two_Creator__set_construct(two::Creator* self, bool value) {
		self->m_construct = value;
	}
	two::Type* DECL two_Creator__get_prototype(two::Creator* self) {
		return self->m_prototype;
	}
	void DECL two_Creator__set_prototype(two::Creator* self, two::Type* value) {
		self->m_prototype = value;
	}
	two::Injector* DECL two_Creator__get_injector(two::Creator* self) {
		return &self->injector();
	}
	void DECL two_Creator__destroy(two::Creator* self) {
		delete self;
	}
	// Namespace
	two::Type* DECL two_Namespace__type() {
		return &two::type<two::Namespace>();
	}
	void DECL two_Namespace__destroy(two::Namespace* self) {
		delete self;
	}
	// Alias
	two::Type* DECL two_Alias__type() {
		return &two::type<two::Alias>();
	}
	two::Alias* DECL two_Alias__construct_0() {
		return new two::Alias();
	}
	void DECL two_Alias__destroy(two::Alias* self) {
		delete self;
	}
	// System
	two::Type* DECL two_System__type() {
		return &two::type<two::System>();
	}
	void DECL two_System__destroy(two::System* self) {
		delete self;
	}
	two::System* DECL two_system_0() {
		return &two::system();
	}
	// TypeClass
	two::TypeClass DECL two_TypeClass_None() {
		return two::TypeClass::None;
	}
	two::TypeClass DECL two_TypeClass_Object() {
		return two::TypeClass::Object;
	}
	two::TypeClass DECL two_TypeClass_Struct() {
		return two::TypeClass::Struct;
	}
	two::TypeClass DECL two_TypeClass_Sequence() {
		return two::TypeClass::Sequence;
	}
	two::TypeClass DECL two_TypeClass_BaseType() {
		return two::TypeClass::BaseType;
	}
	two::TypeClass DECL two_TypeClass_Enum() {
		return two::TypeClass::Enum;
	}
	
}


