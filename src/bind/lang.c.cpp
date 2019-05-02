#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <refl/Api.h>
#include <lang/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Script
	two::Type* DECL two_Script__type() {
		return &two::type<two::Script>();
	}
	uint32_t DECL two_Script__get_index(two::Script* self) {
		return self->m_index;
	}
	void DECL two_Script__set_index(two::Script* self, uint32_t value) {
		self->m_index = value;
	}
	two::Type* DECL two_Script__get_type(two::Script* self) {
		return &self->m_type;
	}
	const char* DECL two_Script__get_name(two::Script* self) {
		return self->m_name.c_str();
	}
	void DECL two_Script__set_name(two::Script* self, const char* value) {
		self->m_name = value;
	}
	bool DECL two_Script__get_locked(two::Script* self) {
		return self->m_locked;
	}
	void DECL two_Script__set_locked(two::Script* self, bool value) {
		self->m_locked = value;
	}
	void DECL two_Script__destroy(two::Script* self) {
		delete self;
	}
	// ScriptError
	two::Type* DECL two_ScriptError__type() {
		return &two::type<two::ScriptError>();
	}
	two::ScriptError* DECL two_ScriptError__construct_0() {
		return new two::ScriptError();
	}
	void DECL two_ScriptError__destroy(two::ScriptError* self) {
		delete self;
	}
	// TextScript
	two::Type* DECL two_TextScript__type() {
		return &two::type<two::TextScript>();
	}
	two::TextScript* DECL two_TextScript__construct_2(const char* name, two::Language language) {
		return new two::TextScript(name, language);
	}
	two::TextScript* DECL two_TextScript__construct_3(const char* name, two::Language language, const two::Signature* signature) {
		return new two::TextScript(name, language, *signature);
	}
	two::Language DECL two_TextScript__get_language(two::TextScript* self) {
		return self->m_language;
	}
	void DECL two_TextScript__set_language(two::TextScript* self, two::Language value) {
		self->m_language = value;
	}
	const char* DECL two_TextScript__get_script(two::TextScript* self) {
		return self->m_script.c_str();
	}
	void DECL two_TextScript__set_script(two::TextScript* self, const char* value) {
		self->m_script = value;
	}
	bool DECL two_TextScript__get_dirty(two::TextScript* self) {
		return self->m_dirty;
	}
	void DECL two_TextScript__set_dirty(two::TextScript* self, bool value) {
		self->m_dirty = value;
	}
	void DECL two_TextScript__destroy(two::TextScript* self) {
		delete self;
	}
	// Interpreter
	two::Type* DECL two_Interpreter__type() {
		return &two::type<two::Interpreter>();
	}
	void DECL two_Interpreter__destroy(two::Interpreter* self) {
		delete self;
	}
	// ScriptClass
	two::Type* DECL two_ScriptClass__type() {
		return &two::type<two::ScriptClass>();
	}
	const char* DECL two_ScriptClass__get_name(two::ScriptClass* self) {
		return self->m_name.c_str();
	}
	void DECL two_ScriptClass__set_name(two::ScriptClass* self, const char* value) {
		self->m_name = value;
	}
	two::Type* DECL two_ScriptClass__get_class_type(two::ScriptClass* self) {
		return &self->m_class_type;
	}
	two::Class* DECL two_ScriptClass__get_class(two::ScriptClass* self) {
		return &self->m_class;
	}
	two::Prototype* DECL two_ScriptClass__get_prototype(two::ScriptClass* self) {
		return &self->m_prototype;
	}
	void DECL two_ScriptClass__destroy(two::ScriptClass* self) {
		delete self;
	}
	// LuaInterpreter
	two::Type* DECL two_LuaInterpreter__type() {
		return &two::type<two::LuaInterpreter>();
	}
	void DECL two_LuaInterpreter__destroy(two::LuaInterpreter* self) {
		delete self;
	}
	// StreamBranch
	two::Type* DECL two_StreamBranch__type() {
		return &two::type<two::StreamBranch>();
	}
	void DECL two_StreamBranch__destroy(two::StreamBranch* self) {
		delete self;
	}
	// Stream
	two::Type* DECL two_Stream__type() {
		return &two::type<two::Stream>();
	}
	void DECL two_Stream__destroy(two::Stream* self) {
		delete self;
	}
	// Valve
	two::Type* DECL two_Valve__type() {
		return &two::type<two::Valve>();
	}
	void DECL two_Valve__destroy(two::Valve* self) {
		delete self;
	}
	// Pipe
	two::Type* DECL two_Pipe__type() {
		return &two::type<two::Pipe>();
	}
	void DECL two_Pipe__destroy(two::Pipe* self) {
		delete self;
	}
	// Process
	two::Type* DECL two_Process__type() {
		return &two::type<two::Process>();
	}
	two::Type* DECL two_Process__get_type(two::Process* self) {
		return &self->m_type;
	}
	void DECL two_Process__destroy(two::Process* self) {
		delete self;
	}
	// VisualScript
	two::Type* DECL two_VisualScript__type() {
		return &two::type<two::VisualScript>();
	}
	two::VisualScript* DECL two_VisualScript__construct_1(const char* name) {
		return new two::VisualScript(name);
	}
	two::VisualScript* DECL two_VisualScript__construct_2(const char* name, const two::Signature* signature) {
		return new two::VisualScript(name, *signature);
	}
	void DECL two_VisualScript__destroy(two::VisualScript* self) {
		delete self;
	}
	// ProcessInput
	two::Type* DECL two_ProcessInput__type() {
		return &two::type<two::ProcessInput>();
	}
	void DECL two_ProcessInput__destroy(two::ProcessInput* self) {
		delete self;
	}
	// ProcessOutput
	two::Type* DECL two_ProcessOutput__type() {
		return &two::type<two::ProcessOutput>();
	}
	void DECL two_ProcessOutput__destroy(two::ProcessOutput* self) {
		delete self;
	}
	// ProcessValue
	two::Type* DECL two_ProcessValue__type() {
		return &two::type<two::ProcessValue>();
	}
	two::ProcessValue* DECL two_ProcessValue__construct_2(two::VisualScript* script, const two::Var* value) {
		return new two::ProcessValue(*script, *value);
	}
	void DECL two_ProcessValue__destroy(two::ProcessValue* self) {
		delete self;
	}
	// ProcessCreate
	two::Type* DECL two_ProcessCreate__type() {
		return &two::type<two::ProcessCreate>();
	}
	two::ProcessCreate* DECL two_ProcessCreate__construct_3(two::VisualScript* script, two::Type* type, const two::Constructor* constructor) {
		return new two::ProcessCreate(*script, *type, *constructor);
	}
	void DECL two_ProcessCreate__destroy(two::ProcessCreate* self) {
		delete self;
	}
	// ProcessCallable
	two::Type* DECL two_ProcessCallable__type() {
		return &two::type<two::ProcessCallable>();
	}
	two::ProcessCallable* DECL two_ProcessCallable__construct_2(two::VisualScript* script, two::Callable* callable) {
		return new two::ProcessCallable(*script, *callable);
	}
	void DECL two_ProcessCallable__destroy(two::ProcessCallable* self) {
		delete self;
	}
	// ProcessScript
	two::Type* DECL two_ProcessScript__type() {
		return &two::type<two::ProcessScript>();
	}
	two::ProcessScript* DECL two_ProcessScript__construct_2(two::VisualScript* script, two::VisualScript* target) {
		return new two::ProcessScript(*script, *target);
	}
	void DECL two_ProcessScript__destroy(two::ProcessScript* self) {
		delete self;
	}
	// ProcessFunction
	two::Type* DECL two_ProcessFunction__type() {
		return &two::type<two::ProcessFunction>();
	}
	two::ProcessFunction* DECL two_ProcessFunction__construct_2(two::VisualScript* script, two::Function* function) {
		return new two::ProcessFunction(*script, *function);
	}
	void DECL two_ProcessFunction__destroy(two::ProcessFunction* self) {
		delete self;
	}
	// ProcessMethod
	two::Type* DECL two_ProcessMethod__type() {
		return &two::type<two::ProcessMethod>();
	}
	two::ProcessMethod* DECL two_ProcessMethod__construct_2(two::VisualScript* script, two::Method* method) {
		return new two::ProcessMethod(*script, *method);
	}
	void DECL two_ProcessMethod__destroy(two::ProcessMethod* self) {
		delete self;
	}
	// ProcessGetMember
	two::Type* DECL two_ProcessGetMember__type() {
		return &two::type<two::ProcessGetMember>();
	}
	two::ProcessGetMember* DECL two_ProcessGetMember__construct_2(two::VisualScript* script, two::Member* member) {
		return new two::ProcessGetMember(*script, *member);
	}
	void DECL two_ProcessGetMember__destroy(two::ProcessGetMember* self) {
		delete self;
	}
	// ProcessSetMember
	two::Type* DECL two_ProcessSetMember__type() {
		return &two::type<two::ProcessSetMember>();
	}
	two::ProcessSetMember* DECL two_ProcessSetMember__construct_2(two::VisualScript* script, two::Member* member) {
		return new two::ProcessSetMember(*script, *member);
	}
	void DECL two_ProcessSetMember__destroy(two::ProcessSetMember* self) {
		delete self;
	}
	// ProcessDisplay
	two::Type* DECL two_ProcessDisplay__type() {
		return &two::type<two::ProcessDisplay>();
	}
	void DECL two_ProcessDisplay__destroy(two::ProcessDisplay* self) {
		delete self;
	}
	// WrenInterpreter
	two::Type* DECL two_WrenInterpreter__type() {
		return &two::type<two::WrenInterpreter>();
	}
	void DECL two_WrenInterpreter__destroy(two::WrenInterpreter* self) {
		delete self;
	}
	// Language
	two::Language DECL two_Language_Cpp() {
		return two::Language::Cpp;
	}
	two::Language DECL two_Language_Lua() {
		return two::Language::Lua;
	}
	two::Language DECL two_Language_Wren() {
		return two::Language::Wren;
	}
	
}


