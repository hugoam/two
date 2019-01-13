#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <refl/Api.h>
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
	// Call
	mud::Call* EMSCRIPTEN_KEEPALIVE Call_Call_0() {
		return new mud::Call();
	}
	mud::Call* EMSCRIPTEN_KEEPALIVE Call_Call_0() {
		return new mud::Call();
	}
	mud::Call* EMSCRIPTEN_KEEPALIVE Call_Call_2(const mud::Callable* callable, std::vector<mud::Var>* arguments) {
		return new mud::Call(*callable, *arguments);
	}
	mud::Var* EMSCRIPTEN_KEEPALIVE Call_get_result(mud::Call* self) {
		static mud::Var temp;
		return (temp = self->m_result, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE Call___destroy__(mud::Call* self) {
		delete self;
	}
	// Callable
	void EMSCRIPTEN_KEEPALIVE Callable___destroy__(mud::Callable* self) {
		delete self;
	}
	// Class
	void EMSCRIPTEN_KEEPALIVE Class___destroy__(mud::Class* self) {
		delete self;
	}
	// Convert
	void EMSCRIPTEN_KEEPALIVE Convert___destroy__(mud::Convert* self) {
		delete self;
	}
	// Creator
	mud::Type* EMSCRIPTEN_KEEPALIVE Creator_get_type(mud::Creator* self) {
		return &self->m_type;
	}
	bool EMSCRIPTEN_KEEPALIVE Creator_get_construct(mud::Creator* self) {
		return self->m_construct;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE Creator_get_prototype(mud::Creator* self) {
		return self->m_prototype;
	}
	mud::Injector* EMSCRIPTEN_KEEPALIVE Creator_get_injector(mud::Creator* self) {
		return &self->injector;
	}
	void EMSCRIPTEN_KEEPALIVE Creator___destroy__(mud::Creator* self) {
		delete self;
	}
	// Enum
	void EMSCRIPTEN_KEEPALIVE Enum___destroy__(mud::Enum* self) {
		delete self;
	}
	// Member
	void EMSCRIPTEN_KEEPALIVE Member___destroy__(mud::Member* self) {
		delete self;
	}
	// Meta
	void EMSCRIPTEN_KEEPALIVE Meta___destroy__(mud::Meta* self) {
		delete self;
	}
	// Module
	const char* EMSCRIPTEN_KEEPALIVE Module_get_name(mud::Module* self) {
		return self->m_name;
	}
	const char* EMSCRIPTEN_KEEPALIVE Module_get_path(mud::Module* self) {
		return self->m_path;
	}
	void EMSCRIPTEN_KEEPALIVE Module___destroy__(mud::Module* self) {
		delete self;
	}
	// Namespace
	void EMSCRIPTEN_KEEPALIVE Namespace___destroy__(mud::Namespace* self) {
		delete self;
	}
	// Operator
	mud::Operator* EMSCRIPTEN_KEEPALIVE Operator_Operator_0() {
		return new mud::Operator();
	}
	mud::Function* EMSCRIPTEN_KEEPALIVE Operator_get_function(mud::Operator* self) {
		return self->m_function;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE Operator_get_type(mud::Operator* self) {
		return self->m_type;
	}
	const char* EMSCRIPTEN_KEEPALIVE Operator_get_name(mud::Operator* self) {
		return self->m_name;
	}
	const char* EMSCRIPTEN_KEEPALIVE Operator_get_sign(mud::Operator* self) {
		return self->m_sign;
	}
	void EMSCRIPTEN_KEEPALIVE Operator___destroy__(mud::Operator* self) {
		delete self;
	}
	// Param
	void EMSCRIPTEN_KEEPALIVE Param___destroy__(mud::Param* self) {
		delete self;
	}
	// Signature
	void EMSCRIPTEN_KEEPALIVE Signature___destroy__(mud::Signature* self) {
		delete self;
	}
	// Static
	void EMSCRIPTEN_KEEPALIVE Static___destroy__(mud::Static* self) {
		delete self;
	}
	// System
	void EMSCRIPTEN_KEEPALIVE System___destroy__(mud::System* self) {
		delete self;
	}
	// Constructor
	void EMSCRIPTEN_KEEPALIVE Constructor___destroy__(mud::Constructor* self) {
		delete self;
	}
	// CopyConstructor
	void EMSCRIPTEN_KEEPALIVE CopyConstructor___destroy__(mud::CopyConstructor* self) {
		delete self;
	}
	// Destructor
	void EMSCRIPTEN_KEEPALIVE Destructor___destroy__(mud::Destructor* self) {
		delete self;
	}
	// Function
	void EMSCRIPTEN_KEEPALIVE Function___destroy__(mud::Function* self) {
		delete self;
	}
	// Injector
	void EMSCRIPTEN_KEEPALIVE Injector___destroy__(mud::Injector* self) {
		delete self;
	}
	// Method
	void EMSCRIPTEN_KEEPALIVE Method___destroy__(mud::Method* self) {
		delete self;
	}
	// TypeClass
	mud::TypeClass EMSCRIPTEN_KEEPALIVE TypeClass_None() {
		return mud::TypeClass::None;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE TypeClass_Object() {
		return mud::TypeClass::Object;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE TypeClass_Struct() {
		return mud::TypeClass::Struct;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE TypeClass_Sequence() {
		return mud::TypeClass::Sequence;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE TypeClass_BaseType() {
		return mud::TypeClass::BaseType;
	}
	mud::TypeClass EMSCRIPTEN_KEEPALIVE TypeClass_Enum() {
		return mud::TypeClass::Enum;
	}
	
}


