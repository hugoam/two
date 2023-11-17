#include <two/infra.h>

module;
module two.lang.meta;

using namespace two;

void two_Language__to_string(void* val, string& str) { str = g_enu[type<two::Language>().m_id]->name(uint32_t((*static_cast<two::Language*>(val)))); }
void two_Language__to_value(const string& str, void* val) { (*static_cast<two::Language*>(val)) = two::Language(g_enu[type<two::Language>().m_id]->value(str.c_str())); }
void* two_Script__get_type(void* object) { return &(*static_cast<two::Script*>(object)).m_type; }
void two_ScriptError__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::ScriptError(  ); }
void two_ScriptError__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::ScriptError((*static_cast<two::ScriptError*>(other))); }
void two_TextScript__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::TextScript( *static_cast<stl::string*>(args[0]), *static_cast<two::Language*>(args[1]), *static_cast<two::Signature*>(args[2]) ); }
void two_ScriptClass__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ScriptClass( *static_cast<stl::string*>(args[0]), *static_cast<stl::span<two::Type*>*>(args[1]) ); }
void* two_Process__get_type(void* object) { return &(*static_cast<two::Process*>(object)).m_type; }
void two_VisualScript__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::VisualScript( *static_cast<stl::string*>(args[0]), *static_cast<two::Signature*>(args[1]) ); }
void two_ProcessValue__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProcessValue( *static_cast<two::VisualScript*>(args[0]), *static_cast<two::Var*>(args[1]) ); }
void two_ProcessCreate__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProcessCreate( *static_cast<two::VisualScript*>(args[0]), *static_cast<two::Type*>(args[1]), *static_cast<two::Constructor*>(args[2]) ); }
void two_ProcessCallable__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProcessCallable( *static_cast<two::VisualScript*>(args[0]), *static_cast<two::Callable*>(args[1]) ); }
void two_ProcessScript__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProcessScript( *static_cast<two::VisualScript*>(args[0]), *static_cast<two::VisualScript*>(args[1]) ); }
void two_ProcessFunction__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProcessFunction( *static_cast<two::VisualScript*>(args[0]), *static_cast<two::Function*>(args[1]) ); }
void two_ProcessMethod__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProcessMethod( *static_cast<two::VisualScript*>(args[0]), *static_cast<two::Method*>(args[1]) ); }
void two_ProcessGetMember__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProcessGetMember( *static_cast<two::VisualScript*>(args[0]), *static_cast<two::Member*>(args[1]) ); }
void two_ProcessSetMember__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ProcessSetMember( *static_cast<two::VisualScript*>(args[0]), *static_cast<two::Member*>(args[1]) ); }

namespace two
{
	void two_lang_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::Language>();
		static Meta meta = { t, &namspc({ "two" }), "Language", sizeof(two::Language), TypeClass::Enum };
		static cstring ids[] = { "Cpp", "Lua", "Wren" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::Language vars[] = { two::Language::Cpp, two::Language::Lua, two::Language::Wren};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Language__to_string,
		                           two_Language__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// two::Script
	{
		Type& t = type<two::Script>();
		static Meta meta = { t, &namspc({ "two" }), "Script", sizeof(two::Script), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Callable>() };
		static size_t bases_offsets[] = { base_offset<two::Script, two::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Script, m_index), type<uint32_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, SIZE_MAX, type<two::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Script__get_type },
			{ t, offsetof(two::Script, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Script, m_locked), type<bool>(), "locked", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// two::ScriptError
	{
		Type& t = type<two::ScriptError>();
		static Meta meta = { t, &namspc({ "two" }), "ScriptError", sizeof(two::ScriptError), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ScriptError__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_ScriptError__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::TextScript
	{
		Type& t = type<two::TextScript>();
		static Meta meta = { t, &namspc({ "two" }), "TextScript", sizeof(two::TextScript), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Script>() };
		static size_t bases_offsets[] = { base_offset<two::TextScript, two::Script>() };
		// defaults
		static two::Signature construct_0_signature_default = {};
		// constructors
		static Constructor constructors[] = {
			{ t, two_TextScript__construct_0, { { "name", type<stl::string>(),  }, { "language", type<two::Language>(),  }, { "signature", type<two::Signature>(), Param::Default, &construct_0_signature_default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::TextScript, m_language), type<two::Language>(), "language", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::TextScript, m_script), type<stl::string>(), "script", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::TextScript, m_dirty), type<bool>(), "dirty", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, {}, {}, };
	}
	// two::Interpreter
	{
		Type& t = type<two::Interpreter>();
		static Meta meta = { t, &namspc({ "two" }), "Interpreter", sizeof(two::Interpreter), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::ScriptClass
	{
		Type& t = type<two::ScriptClass>();
		static Meta meta = { t, &namspc({ "two" }), "ScriptClass", sizeof(two::ScriptClass), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ScriptClass__construct_0, { { "name", type<stl::string>(),  }, { "parts", type<stl::span<two::Type*>>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::ScriptClass, m_name), type<stl::string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::ScriptClass, m_class_type), type<two::Type>(), "class_type", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::ScriptClass, m_class), type<two::Class>(), "class", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::ScriptClass, m_prototype), type<two::Prototype>(), "prototype", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, {}, {}, };
	}
	// two::LuaInterpreter
	{
		Type& t = type<two::LuaInterpreter>();
		static Meta meta = { t, &namspc({ "two" }), "LuaInterpreter", sizeof(two::LuaInterpreter), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Interpreter>() };
		static size_t bases_offsets[] = { base_offset<two::LuaInterpreter, two::Interpreter>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::StreamBranch
	{
		Type& t = type<two::StreamBranch>();
		static Meta meta = { t, &namspc({ "two" }), "StreamBranch", sizeof(two::StreamBranch), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Stream
	{
		Type& t = type<two::Stream>();
		static Meta meta = { t, &namspc({ "two" }), "Stream", sizeof(two::Stream), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::StreamBranch>() };
		static size_t bases_offsets[] = { base_offset<two::Stream, two::StreamBranch>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Valve
	{
		Type& t = type<two::Valve>();
		static Meta meta = { t, &namspc({ "two" }), "Valve", sizeof(two::Valve), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Pipe
	{
		Type& t = type<two::Pipe>();
		static Meta meta = { t, &namspc({ "two" }), "Pipe", sizeof(two::Pipe), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Process
	{
		Type& t = type<two::Process>();
		static Meta meta = { t, &namspc({ "two" }), "Process", sizeof(two::Process), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Process__get_type }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::VisualScript
	{
		Type& t = type<two::VisualScript>();
		static Meta meta = { t, &namspc({ "two" }), "VisualScript", sizeof(two::VisualScript), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Script>() };
		static size_t bases_offsets[] = { base_offset<two::VisualScript, two::Script>() };
		// defaults
		static two::Signature construct_0_signature_default = {};
		// constructors
		static Constructor constructors[] = {
			{ t, two_VisualScript__construct_0, { { "name", type<stl::string>(),  }, { "signature", type<two::Signature>(), Param::Default, &construct_0_signature_default } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessInput
	{
		Type& t = type<two::ProcessInput>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessInput", sizeof(two::ProcessInput), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Process>(), &type<two::Param>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessInput, two::Process>(), base_offset<two::ProcessInput, two::Param>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::ProcessOutput
	{
		Type& t = type<two::ProcessOutput>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessOutput", sizeof(two::ProcessOutput), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Process>(), &type<two::Param>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessOutput, two::Process>(), base_offset<two::ProcessOutput, two::Param>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::ProcessValue
	{
		Type& t = type<two::ProcessValue>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessValue", sizeof(two::ProcessValue), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Process>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessValue, two::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProcessValue__construct_0, { { "script", type<two::VisualScript>(),  }, { "value", type<two::Var>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessCreate
	{
		Type& t = type<two::ProcessCreate>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessCreate", sizeof(two::ProcessCreate), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Process>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessCreate, two::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProcessCreate__construct_0, { { "script", type<two::VisualScript>(),  }, { "type", type<two::Type>(),  }, { "constructor", type<two::Constructor>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessCallable
	{
		Type& t = type<two::ProcessCallable>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessCallable", sizeof(two::ProcessCallable), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Process>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessCallable, two::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProcessCallable__construct_0, { { "script", type<two::VisualScript>(),  }, { "callable", type<two::Callable>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessScript
	{
		Type& t = type<two::ProcessScript>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessScript", sizeof(two::ProcessScript), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ProcessCallable>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessScript, two::ProcessCallable>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProcessScript__construct_0, { { "script", type<two::VisualScript>(),  }, { "target", type<two::VisualScript>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessFunction
	{
		Type& t = type<two::ProcessFunction>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessFunction", sizeof(two::ProcessFunction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ProcessCallable>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessFunction, two::ProcessCallable>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProcessFunction__construct_0, { { "script", type<two::VisualScript>(),  }, { "function", type<two::Function>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessMethod
	{
		Type& t = type<two::ProcessMethod>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessMethod", sizeof(two::ProcessMethod), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ProcessCallable>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessMethod, two::ProcessCallable>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProcessMethod__construct_0, { { "script", type<two::VisualScript>(),  }, { "method", type<two::Method>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessGetMember
	{
		Type& t = type<two::ProcessGetMember>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessGetMember", sizeof(two::ProcessGetMember), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Process>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessGetMember, two::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProcessGetMember__construct_0, { { "script", type<two::VisualScript>(),  }, { "member", type<two::Member>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessSetMember
	{
		Type& t = type<two::ProcessSetMember>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessSetMember", sizeof(two::ProcessSetMember), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Process>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessSetMember, two::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ProcessSetMember__construct_0, { { "script", type<two::VisualScript>(),  }, { "member", type<two::Member>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// two::ProcessDisplay
	{
		Type& t = type<two::ProcessDisplay>();
		static Meta meta = { t, &namspc({ "two" }), "ProcessDisplay", sizeof(two::ProcessDisplay), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Process>() };
		static size_t bases_offsets[] = { base_offset<two::ProcessDisplay, two::Process>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::WrenInterpreter
	{
		Type& t = type<two::WrenInterpreter>();
		static Meta meta = { t, &namspc({ "two" }), "WrenInterpreter", sizeof(two::WrenInterpreter), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Interpreter>() };
		static size_t bases_offsets[] = { base_offset<two::WrenInterpreter, two::Interpreter>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::Script>());
		m.m_types.push_back(&type<two::Language>());
		m.m_types.push_back(&type<two::ScriptError>());
		m.m_types.push_back(&type<two::TextScript>());
		m.m_types.push_back(&type<two::Interpreter>());
		m.m_types.push_back(&type<two::ScriptClass>());
		m.m_types.push_back(&type<two::LuaInterpreter>());
		m.m_types.push_back(&type<two::StreamBranch>());
		m.m_types.push_back(&type<two::Stream>());
		m.m_types.push_back(&type<two::Valve>());
		m.m_types.push_back(&type<two::Pipe>());
		m.m_types.push_back(&type<two::Process>());
		m.m_types.push_back(&type<two::VisualScript>());
		m.m_types.push_back(&type<two::ProcessInput>());
		m.m_types.push_back(&type<two::ProcessOutput>());
		m.m_types.push_back(&type<two::ProcessValue>());
		m.m_types.push_back(&type<two::ProcessCreate>());
		m.m_types.push_back(&type<two::ProcessCallable>());
		m.m_types.push_back(&type<two::ProcessScript>());
		m.m_types.push_back(&type<two::ProcessFunction>());
		m.m_types.push_back(&type<two::ProcessMethod>());
		m.m_types.push_back(&type<two::ProcessGetMember>());
		m.m_types.push_back(&type<two::ProcessSetMember>());
		m.m_types.push_back(&type<two::ProcessDisplay>());
		m.m_types.push_back(&type<two::WrenInterpreter>());
	}
}

namespace two
{
	two_lang::two_lang()
		: Module("two::lang", { &two_infra::m(), &two_type::m(), &two_pool::m(), &two_refl::m() })
	{
		// setup reflection meta data
		two_lang_meta(*this);
	}
}

#ifdef TWO_LANG_MODULE
extern "C"
Module& getModule()
{
	return two_lang::m();
}
#endif
