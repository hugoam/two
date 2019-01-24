#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <refl/Api.h>
#include <lang/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Interpreter
	mud::Type* DECL mud_Interpreter__type() {
		return &mud::type<mud::Interpreter>();
	}
	void DECL mud_Interpreter__destroy(mud::Interpreter* self) {
		delete self;
	}
	// Pipe
	mud::Type* DECL mud_Pipe__type() {
		return &mud::type<mud::Pipe>();
	}
	void DECL mud_Pipe__destroy(mud::Pipe* self) {
		delete self;
	}
	// Process
	mud::Type* DECL mud_Process__type() {
		return &mud::type<mud::Process>();
	}
	mud::Type* DECL mud_Process__get_type(mud::Process* self) {
		return &self->m_type;
	}
	void DECL mud_Process__destroy(mud::Process* self) {
		delete self;
	}
	// ScriptClass
	mud::Type* DECL mud_ScriptClass__type() {
		return &mud::type<mud::ScriptClass>();
	}
	mud::ScriptClass* DECL mud_ScriptClass_ScriptClass_2(const char* name, const vector<mud::Type*>* parts) {
		return new mud::ScriptClass(name, *parts);
	}
	const char* DECL mud_ScriptClass__get_name(mud::ScriptClass* self) {
		return self->m_name.c_str();
	}
	void DECL mud_ScriptClass__set_name(mud::ScriptClass* self, const char* value) {
		self->m_name = value;
	}
	mud::Type* DECL mud_ScriptClass__get_class_type(mud::ScriptClass* self) {
		return &self->m_class_type;
	}
	mud::Class* DECL mud_ScriptClass__get_class(mud::ScriptClass* self) {
		return &self->m_class;
	}
	mud::Prototype* DECL mud_ScriptClass__get_prototype(mud::ScriptClass* self) {
		return &self->m_prototype;
	}
	void DECL mud_ScriptClass__destroy(mud::ScriptClass* self) {
		delete self;
	}
	// ScriptError
	mud::Type* DECL mud_ScriptError__type() {
		return &mud::type<mud::ScriptError>();
	}
	mud::ScriptError* DECL mud_ScriptError_ScriptError_0() {
		return new mud::ScriptError();
	}
	void DECL mud_ScriptError__destroy(mud::ScriptError* self) {
		delete self;
	}
	// StreamBranch
	mud::Type* DECL mud_StreamBranch__type() {
		return &mud::type<mud::StreamBranch>();
	}
	void DECL mud_StreamBranch__destroy(mud::StreamBranch* self) {
		delete self;
	}
	// Valve
	mud::Type* DECL mud_Valve__type() {
		return &mud::type<mud::Valve>();
	}
	void DECL mud_Valve__destroy(mud::Valve* self) {
		delete self;
	}
	// LuaInterpreter
	mud::Type* DECL mud_LuaInterpreter__type() {
		return &mud::type<mud::LuaInterpreter>();
	}
	void DECL mud_LuaInterpreter__destroy(mud::LuaInterpreter* self) {
		delete self;
	}
	// ProcessCallable
	mud::Type* DECL mud_ProcessCallable__type() {
		return &mud::type<mud::ProcessCallable>();
	}
	mud::ProcessCallable* DECL mud_ProcessCallable_ProcessCallable_2(mud::VisualScript* script, mud::Callable* callable) {
		return new mud::ProcessCallable(*script, *callable);
	}
	void DECL mud_ProcessCallable__destroy(mud::ProcessCallable* self) {
		delete self;
	}
	// ProcessCreate
	mud::Type* DECL mud_ProcessCreate__type() {
		return &mud::type<mud::ProcessCreate>();
	}
	mud::ProcessCreate* DECL mud_ProcessCreate_ProcessCreate_3(mud::VisualScript* script, mud::Type* type, const mud::Constructor* constructor) {
		return new mud::ProcessCreate(*script, *type, *constructor);
	}
	void DECL mud_ProcessCreate__destroy(mud::ProcessCreate* self) {
		delete self;
	}
	// ProcessDisplay
	mud::Type* DECL mud_ProcessDisplay__type() {
		return &mud::type<mud::ProcessDisplay>();
	}
	void DECL mud_ProcessDisplay__destroy(mud::ProcessDisplay* self) {
		delete self;
	}
	// ProcessFunction
	mud::Type* DECL mud_ProcessFunction__type() {
		return &mud::type<mud::ProcessFunction>();
	}
	mud::ProcessFunction* DECL mud_ProcessFunction_ProcessFunction_2(mud::VisualScript* script, mud::Function* function) {
		return new mud::ProcessFunction(*script, *function);
	}
	void DECL mud_ProcessFunction__destroy(mud::ProcessFunction* self) {
		delete self;
	}
	// ProcessGetMember
	mud::Type* DECL mud_ProcessGetMember__type() {
		return &mud::type<mud::ProcessGetMember>();
	}
	mud::ProcessGetMember* DECL mud_ProcessGetMember_ProcessGetMember_2(mud::VisualScript* script, mud::Member* member) {
		return new mud::ProcessGetMember(*script, *member);
	}
	void DECL mud_ProcessGetMember__destroy(mud::ProcessGetMember* self) {
		delete self;
	}
	// ProcessInput
	mud::Type* DECL mud_ProcessInput__type() {
		return &mud::type<mud::ProcessInput>();
	}
	void DECL mud_ProcessInput__destroy(mud::ProcessInput* self) {
		delete self;
	}
	// ProcessMethod
	mud::Type* DECL mud_ProcessMethod__type() {
		return &mud::type<mud::ProcessMethod>();
	}
	mud::ProcessMethod* DECL mud_ProcessMethod_ProcessMethod_2(mud::VisualScript* script, mud::Method* method) {
		return new mud::ProcessMethod(*script, *method);
	}
	void DECL mud_ProcessMethod__destroy(mud::ProcessMethod* self) {
		delete self;
	}
	// ProcessOutput
	mud::Type* DECL mud_ProcessOutput__type() {
		return &mud::type<mud::ProcessOutput>();
	}
	void DECL mud_ProcessOutput__destroy(mud::ProcessOutput* self) {
		delete self;
	}
	// ProcessScript
	mud::Type* DECL mud_ProcessScript__type() {
		return &mud::type<mud::ProcessScript>();
	}
	mud::ProcessScript* DECL mud_ProcessScript_ProcessScript_2(mud::VisualScript* script, mud::VisualScript* target) {
		return new mud::ProcessScript(*script, *target);
	}
	void DECL mud_ProcessScript__destroy(mud::ProcessScript* self) {
		delete self;
	}
	// ProcessSetMember
	mud::Type* DECL mud_ProcessSetMember__type() {
		return &mud::type<mud::ProcessSetMember>();
	}
	mud::ProcessSetMember* DECL mud_ProcessSetMember_ProcessSetMember_2(mud::VisualScript* script, mud::Member* member) {
		return new mud::ProcessSetMember(*script, *member);
	}
	void DECL mud_ProcessSetMember__destroy(mud::ProcessSetMember* self) {
		delete self;
	}
	// ProcessValue
	mud::Type* DECL mud_ProcessValue__type() {
		return &mud::type<mud::ProcessValue>();
	}
	mud::ProcessValue* DECL mud_ProcessValue_ProcessValue_2(mud::VisualScript* script, const mud::Var* value) {
		return new mud::ProcessValue(*script, *value);
	}
	void DECL mud_ProcessValue__destroy(mud::ProcessValue* self) {
		delete self;
	}
	// Script
	mud::Type* DECL mud_Script__type() {
		return &mud::type<mud::Script>();
	}
	uint32_t DECL mud_Script__get_index(mud::Script* self) {
		return self->m_index;
	}
	void DECL mud_Script__set_index(mud::Script* self, uint32_t value) {
		self->m_index = value;
	}
	mud::Type* DECL mud_Script__get_type(mud::Script* self) {
		return &self->m_type;
	}
	const char* DECL mud_Script__get_name(mud::Script* self) {
		return self->m_name.c_str();
	}
	void DECL mud_Script__set_name(mud::Script* self, const char* value) {
		self->m_name = value;
	}
	bool DECL mud_Script__get_locked(mud::Script* self) {
		return self->m_locked;
	}
	void DECL mud_Script__set_locked(mud::Script* self, bool value) {
		self->m_locked = value;
	}
	void DECL mud_Script__destroy(mud::Script* self) {
		delete self;
	}
	// Stream
	mud::Type* DECL mud_Stream__type() {
		return &mud::type<mud::Stream>();
	}
	void DECL mud_Stream__destroy(mud::Stream* self) {
		delete self;
	}
	// TextScript
	mud::Type* DECL mud_TextScript__type() {
		return &mud::type<mud::TextScript>();
	}
	mud::TextScript* DECL mud_TextScript_TextScript_2(const char* name, mud::Language language) {
		return new mud::TextScript(name, language);
	}
	mud::TextScript* DECL mud_TextScript_TextScript_3(const char* name, mud::Language language, const mud::Signature* signature) {
		return new mud::TextScript(name, language, *signature);
	}
	mud::Language DECL mud_TextScript__get_language(mud::TextScript* self) {
		return self->m_language;
	}
	void DECL mud_TextScript__set_language(mud::TextScript* self, mud::Language value) {
		self->m_language = value;
	}
	const char* DECL mud_TextScript__get_script(mud::TextScript* self) {
		return self->m_script.c_str();
	}
	void DECL mud_TextScript__set_script(mud::TextScript* self, const char* value) {
		self->m_script = value;
	}
	bool DECL mud_TextScript__get_dirty(mud::TextScript* self) {
		return self->m_dirty;
	}
	void DECL mud_TextScript__set_dirty(mud::TextScript* self, bool value) {
		self->m_dirty = value;
	}
	void DECL mud_TextScript__destroy(mud::TextScript* self) {
		delete self;
	}
	// VisualScript
	mud::Type* DECL mud_VisualScript__type() {
		return &mud::type<mud::VisualScript>();
	}
	mud::VisualScript* DECL mud_VisualScript_VisualScript_1(const char* name) {
		return new mud::VisualScript(name);
	}
	mud::VisualScript* DECL mud_VisualScript_VisualScript_2(const char* name, const mud::Signature* signature) {
		return new mud::VisualScript(name, *signature);
	}
	void DECL mud_VisualScript__destroy(mud::VisualScript* self) {
		delete self;
	}
	// WrenInterpreter
	mud::Type* DECL mud_WrenInterpreter__type() {
		return &mud::type<mud::WrenInterpreter>();
	}
	void DECL mud_WrenInterpreter__destroy(mud::WrenInterpreter* self) {
		delete self;
	}
	// Language
	mud::Language DECL mud_Language_Cpp() {
		return mud::Language::Cpp;
	}
	mud::Language DECL mud_Language_Lua() {
		return mud::Language::Lua;
	}
	mud::Language DECL mud_Language_Wren() {
		return mud::Language::Wren;
	}
	
}


