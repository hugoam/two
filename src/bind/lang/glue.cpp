#include <infra/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <refl/Api.h>
#include <lang/Api.h>
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
	// Interpreter
	void EMSCRIPTEN_KEEPALIVE Interpreter___destroy__(mud::Interpreter* self) {
		delete self;
	}
	// Pipe
	void EMSCRIPTEN_KEEPALIVE Pipe___destroy__(mud::Pipe* self) {
		delete self;
	}
	// Process
	mud::Type* EMSCRIPTEN_KEEPALIVE Process_get_type(mud::Process* self) {
		return &self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE Process_set_type(mud::Process* self, mud::Type* type) {
		self->m_type = *type;
	}
	void EMSCRIPTEN_KEEPALIVE Process___destroy__(mud::Process* self) {
		delete self;
	}
	// ScriptClass
	mud::ScriptClass* EMSCRIPTEN_KEEPALIVE ScriptClass_ScriptClass_2(const char* name, const std::vector<mud::Type*>* parts) {
		return new mud::ScriptClass(name, *parts);
	}
	const char* EMSCRIPTEN_KEEPALIVE ScriptClass_get_name(mud::ScriptClass* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE ScriptClass_set_name(mud::ScriptClass* self, const char* name) {
		self->m_name = name;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE ScriptClass_get_class_type(mud::ScriptClass* self) {
		return &self->m_class_type;
	}
	void EMSCRIPTEN_KEEPALIVE ScriptClass_set_class_type(mud::ScriptClass* self, mud::Type* class_type) {
		self->m_class_type = *class_type;
	}
	mud::Class* EMSCRIPTEN_KEEPALIVE ScriptClass_get_class(mud::ScriptClass* self) {
		return &self->m_class;
	}
	void EMSCRIPTEN_KEEPALIVE ScriptClass_set_class(mud::ScriptClass* self, mud::Class* class) {
		self->m_class = *class;
	}
	void EMSCRIPTEN_KEEPALIVE ScriptClass___destroy__(mud::ScriptClass* self) {
		delete self;
	}
	// ScriptError
	mud::ScriptError* EMSCRIPTEN_KEEPALIVE ScriptError_ScriptError_0() {
		return new mud::ScriptError();
	}
	void EMSCRIPTEN_KEEPALIVE ScriptError___destroy__(mud::ScriptError* self) {
		delete self;
	}
	// StreamBranch
	void EMSCRIPTEN_KEEPALIVE StreamBranch___destroy__(mud::StreamBranch* self) {
		delete self;
	}
	// Valve
	void EMSCRIPTEN_KEEPALIVE Valve___destroy__(mud::Valve* self) {
		delete self;
	}
	// LuaInterpreter
	void EMSCRIPTEN_KEEPALIVE LuaInterpreter___destroy__(mud::LuaInterpreter* self) {
		delete self;
	}
	// ProcessCallable
	mud::ProcessCallable* EMSCRIPTEN_KEEPALIVE ProcessCallable_ProcessCallable_2(mud::VisualScript* script, mud::Callable* callable) {
		return new mud::ProcessCallable(*script, *callable);
	}
	void EMSCRIPTEN_KEEPALIVE ProcessCallable___destroy__(mud::ProcessCallable* self) {
		delete self;
	}
	// ProcessCreate
	mud::ProcessCreate* EMSCRIPTEN_KEEPALIVE ProcessCreate_ProcessCreate_3(mud::VisualScript* script, mud::Type* type, const mud::Constructor* constructor) {
		return new mud::ProcessCreate(*script, *type, *constructor);
	}
	void EMSCRIPTEN_KEEPALIVE ProcessCreate___destroy__(mud::ProcessCreate* self) {
		delete self;
	}
	// ProcessDisplay
	void EMSCRIPTEN_KEEPALIVE ProcessDisplay___destroy__(mud::ProcessDisplay* self) {
		delete self;
	}
	// ProcessFunction
	mud::ProcessFunction* EMSCRIPTEN_KEEPALIVE ProcessFunction_ProcessFunction_2(mud::VisualScript* script, mud::Function* function) {
		return new mud::ProcessFunction(*script, *function);
	}
	void EMSCRIPTEN_KEEPALIVE ProcessFunction___destroy__(mud::ProcessFunction* self) {
		delete self;
	}
	// ProcessGetMember
	mud::ProcessGetMember* EMSCRIPTEN_KEEPALIVE ProcessGetMember_ProcessGetMember_2(mud::VisualScript* script, mud::Member* member) {
		return new mud::ProcessGetMember(*script, *member);
	}
	void EMSCRIPTEN_KEEPALIVE ProcessGetMember___destroy__(mud::ProcessGetMember* self) {
		delete self;
	}
	// ProcessInput
	void EMSCRIPTEN_KEEPALIVE ProcessInput___destroy__(mud::ProcessInput* self) {
		delete self;
	}
	// ProcessMethod
	mud::ProcessMethod* EMSCRIPTEN_KEEPALIVE ProcessMethod_ProcessMethod_2(mud::VisualScript* script, mud::Method* method) {
		return new mud::ProcessMethod(*script, *method);
	}
	void EMSCRIPTEN_KEEPALIVE ProcessMethod___destroy__(mud::ProcessMethod* self) {
		delete self;
	}
	// ProcessOutput
	void EMSCRIPTEN_KEEPALIVE ProcessOutput___destroy__(mud::ProcessOutput* self) {
		delete self;
	}
	// ProcessScript
	mud::ProcessScript* EMSCRIPTEN_KEEPALIVE ProcessScript_ProcessScript_2(mud::VisualScript* script, mud::VisualScript* target) {
		return new mud::ProcessScript(*script, *target);
	}
	void EMSCRIPTEN_KEEPALIVE ProcessScript___destroy__(mud::ProcessScript* self) {
		delete self;
	}
	// ProcessSetMember
	mud::ProcessSetMember* EMSCRIPTEN_KEEPALIVE ProcessSetMember_ProcessSetMember_2(mud::VisualScript* script, mud::Member* member) {
		return new mud::ProcessSetMember(*script, *member);
	}
	void EMSCRIPTEN_KEEPALIVE ProcessSetMember___destroy__(mud::ProcessSetMember* self) {
		delete self;
	}
	// ProcessValue
	mud::ProcessValue* EMSCRIPTEN_KEEPALIVE ProcessValue_ProcessValue_2(mud::VisualScript* script, const mud::Var* value) {
		return new mud::ProcessValue(*script, *value);
	}
	void EMSCRIPTEN_KEEPALIVE ProcessValue___destroy__(mud::ProcessValue* self) {
		delete self;
	}
	// Script
	uint32_t EMSCRIPTEN_KEEPALIVE Script_get_index(mud::Script* self) {
		return self->m_index;
	}
	void EMSCRIPTEN_KEEPALIVE Script_set_index(mud::Script* self, uint32_t index) {
		self->m_index = index;
	}
	mud::Type* EMSCRIPTEN_KEEPALIVE Script_get_type(mud::Script* self) {
		return &self->m_type;
	}
	void EMSCRIPTEN_KEEPALIVE Script_set_type(mud::Script* self, mud::Type* type) {
		self->m_type = *type;
	}
	const char* EMSCRIPTEN_KEEPALIVE Script_get_name(mud::Script* self) {
		return self->m_name.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE Script_set_name(mud::Script* self, const char* name) {
		self->m_name = name;
	}
	bool EMSCRIPTEN_KEEPALIVE Script_get_locked(mud::Script* self) {
		return self->m_locked;
	}
	void EMSCRIPTEN_KEEPALIVE Script_set_locked(mud::Script* self, bool locked) {
		self->m_locked = locked;
	}
	void EMSCRIPTEN_KEEPALIVE Script___destroy__(mud::Script* self) {
		delete self;
	}
	// Stream
	void EMSCRIPTEN_KEEPALIVE Stream___destroy__(mud::Stream* self) {
		delete self;
	}
	// TextScript
	mud::TextScript* EMSCRIPTEN_KEEPALIVE TextScript_TextScript_2(const char* name, mud::Language language) {
		return new mud::TextScript(name, language);
	}
	mud::TextScript* EMSCRIPTEN_KEEPALIVE TextScript_TextScript_3(const char* name, mud::Language language, const mud::Signature* signature) {
		return new mud::TextScript(name, language, *signature);
	}
	mud::Language EMSCRIPTEN_KEEPALIVE TextScript_get_language(mud::TextScript* self) {
		return self->m_language;
	}
	void EMSCRIPTEN_KEEPALIVE TextScript_set_language(mud::TextScript* self, mud::Language language) {
		self->m_language = language;
	}
	const char* EMSCRIPTEN_KEEPALIVE TextScript_get_script(mud::TextScript* self) {
		return self->m_script.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE TextScript_set_script(mud::TextScript* self, const char* script) {
		self->m_script = script;
	}
	bool EMSCRIPTEN_KEEPALIVE TextScript_get_dirty(mud::TextScript* self) {
		return self->m_dirty;
	}
	void EMSCRIPTEN_KEEPALIVE TextScript_set_dirty(mud::TextScript* self, bool dirty) {
		self->m_dirty = dirty;
	}
	void EMSCRIPTEN_KEEPALIVE TextScript___destroy__(mud::TextScript* self) {
		delete self;
	}
	// VisualScript
	mud::VisualScript* EMSCRIPTEN_KEEPALIVE VisualScript_VisualScript_1(const char* name) {
		return new mud::VisualScript(name);
	}
	mud::VisualScript* EMSCRIPTEN_KEEPALIVE VisualScript_VisualScript_2(const char* name, const mud::Signature* signature) {
		return new mud::VisualScript(name, *signature);
	}
	void EMSCRIPTEN_KEEPALIVE VisualScript___destroy__(mud::VisualScript* self) {
		delete self;
	}
	// WrenInterpreter
	void EMSCRIPTEN_KEEPALIVE WrenInterpreter___destroy__(mud::WrenInterpreter* self) {
		delete self;
	}
	// Language
	mud::Language EMSCRIPTEN_KEEPALIVE Language_Cpp() {
		return mud::Language::Cpp;
	}
	mud::Language EMSCRIPTEN_KEEPALIVE Language_Lua() {
		return mud::Language::Lua;
	}
	mud::Language EMSCRIPTEN_KEEPALIVE Language_Wren() {
		return mud::Language::Wren;
	}
	
}


