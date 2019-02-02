#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <stl/new.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/lang/Module.h>
#include <meta/lang/Convert.h>
#endif

#include <lang/Api.h>

using namespace mud;

void mud_Language__to_string(void* val, string& str) { str = g_enu[type<mud::Language>().m_id]->name(uint32_t((*static_cast<mud::Language*>(val)))); }
void mud_Language__to_value(const string& str, void* val) { (*static_cast<mud::Language*>(val)) = mud::Language(g_enu[type<mud::Language>().m_id]->value(str.c_str())); }
void* mud_Process__get_type(void* object) { return &(*static_cast<mud::Process*>(object)).m_type; }
void mud_ScriptClass__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ScriptClass*>(ref))) mud::ScriptClass( *static_cast<string*>(args[0]), *static_cast<vector<mud::Type*>*>(args[1]) ); }
void mud_ScriptError__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::ScriptError*>(ref))) mud::ScriptError(  ); }
void mud_ScriptError__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::ScriptError*>(ref))) mud::ScriptError((*static_cast<mud::ScriptError*>(other))); }
void mud_ProcessCallable__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ProcessCallable*>(ref))) mud::ProcessCallable( *static_cast<mud::VisualScript*>(args[0]), *static_cast<mud::Callable*>(args[1]) ); }
void mud_ProcessCreate__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ProcessCreate*>(ref))) mud::ProcessCreate( *static_cast<mud::VisualScript*>(args[0]), *static_cast<mud::Type*>(args[1]), *static_cast<mud::Constructor*>(args[2]) ); }
void mud_ProcessFunction__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ProcessFunction*>(ref))) mud::ProcessFunction( *static_cast<mud::VisualScript*>(args[0]), *static_cast<mud::Function*>(args[1]) ); }
void mud_ProcessGetMember__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ProcessGetMember*>(ref))) mud::ProcessGetMember( *static_cast<mud::VisualScript*>(args[0]), *static_cast<mud::Member*>(args[1]) ); }
void mud_ProcessMethod__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ProcessMethod*>(ref))) mud::ProcessMethod( *static_cast<mud::VisualScript*>(args[0]), *static_cast<mud::Method*>(args[1]) ); }
void mud_ProcessScript__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ProcessScript*>(ref))) mud::ProcessScript( *static_cast<mud::VisualScript*>(args[0]), *static_cast<mud::VisualScript*>(args[1]) ); }
void mud_ProcessSetMember__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ProcessSetMember*>(ref))) mud::ProcessSetMember( *static_cast<mud::VisualScript*>(args[0]), *static_cast<mud::Member*>(args[1]) ); }
void mud_ProcessValue__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::ProcessValue*>(ref))) mud::ProcessValue( *static_cast<mud::VisualScript*>(args[0]), *static_cast<mud::Var*>(args[1]) ); }
void* mud_Script__get_type(void* object) { return &(*static_cast<mud::Script*>(object)).m_type; }
void mud_TextScript__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::TextScript*>(ref))) mud::TextScript( *static_cast<string*>(args[0]), *static_cast<mud::Language*>(args[1]), *static_cast<mud::Signature*>(args[2]) ); }
void mud_VisualScript__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::VisualScript*>(ref))) mud::VisualScript( static_cast<const char*>(args[0]), *static_cast<mud::Signature*>(args[1]) ); }

namespace mud
{
	void mud_lang_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::Language>();
		static Meta meta = { t, &namspc({ "mud" }), "Language", sizeof(mud::Language), TypeClass::Enum };
		static cstring ids[] = { "Cpp", "Lua", "Wren" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Language vars[] = { mud::Language::Cpp, mud::Language::Lua, mud::Language::Wren};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_Language__to_string,
		                           mud_Language__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// mud::Interpreter
	{
		Type& t = type<mud::Interpreter>();
		static Meta meta = { t, &namspc({ "mud" }), "Interpreter", sizeof(mud::Interpreter), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Pipe
	{
		Type& t = type<mud::Pipe>();
		static Meta meta = { t, &namspc({ "mud" }), "Pipe", sizeof(mud::Pipe), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Process
	{
		Type& t = type<mud::Process>();
		static Meta meta = { t, &namspc({ "mud" }), "Process", sizeof(mud::Process), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Process__get_type }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::ScriptClass
	{
		Type& t = type<mud::ScriptClass>();
		static Meta meta = { t, &namspc({ "mud" }), "ScriptClass", sizeof(mud::ScriptClass), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ScriptClass__construct_0, { { "name", type<string>(),  }, { "parts", type<vector<mud::Type*>>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::ScriptClass, m_name), type<string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::ScriptClass, m_class_type), type<mud::Type>(), "class_type", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::ScriptClass, m_class), type<mud::Class>(), "class", nullptr, Member::NonMutable, nullptr },
			//{ t, offsetof(mud::ScriptClass, m_prototype), type<mud::Prototype>(), "prototype", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, {}, {}, };
	}
	// mud::ScriptError
	{
		Type& t = type<mud::ScriptError>();
		static Meta meta = { t, &namspc({ "mud" }), "ScriptError", sizeof(mud::ScriptError), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ScriptError__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_ScriptError__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::StreamBranch
	{
		Type& t = type<mud::StreamBranch>();
		static Meta meta = { t, &namspc({ "mud" }), "StreamBranch", sizeof(mud::StreamBranch), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Valve
	{
		Type& t = type<mud::Valve>();
		static Meta meta = { t, &namspc({ "mud" }), "Valve", sizeof(mud::Valve), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::LuaInterpreter
	{
		Type& t = type<mud::LuaInterpreter>();
		static Meta meta = { t, &namspc({ "mud" }), "LuaInterpreter", sizeof(mud::LuaInterpreter), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Interpreter>() };
		static size_t bases_offsets[] = { base_offset<mud::LuaInterpreter, mud::Interpreter>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ProcessCallable
	{
		Type& t = type<mud::ProcessCallable>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessCallable", sizeof(mud::ProcessCallable), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Process>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessCallable, mud::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ProcessCallable__construct_0, { { "script", type<mud::VisualScript>(),  }, { "callable", type<mud::Callable>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::ProcessCreate
	{
		Type& t = type<mud::ProcessCreate>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessCreate", sizeof(mud::ProcessCreate), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Process>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessCreate, mud::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ProcessCreate__construct_0, { { "script", type<mud::VisualScript>(),  }, { "type", type<mud::Type>(),  }, { "constructor", type<mud::Constructor>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::ProcessDisplay
	{
		Type& t = type<mud::ProcessDisplay>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessDisplay", sizeof(mud::ProcessDisplay), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Process>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessDisplay, mud::Process>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ProcessFunction
	{
		Type& t = type<mud::ProcessFunction>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessFunction", sizeof(mud::ProcessFunction), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ProcessCallable>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessFunction, mud::ProcessCallable>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ProcessFunction__construct_0, { { "script", type<mud::VisualScript>(),  }, { "function", type<mud::Function>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::ProcessGetMember
	{
		Type& t = type<mud::ProcessGetMember>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessGetMember", sizeof(mud::ProcessGetMember), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Process>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessGetMember, mud::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ProcessGetMember__construct_0, { { "script", type<mud::VisualScript>(),  }, { "member", type<mud::Member>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::ProcessInput
	{
		Type& t = type<mud::ProcessInput>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessInput", sizeof(mud::ProcessInput), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Process>(), &type<mud::Param>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessInput, mud::Process>(), base_offset<mud::ProcessInput, mud::Param>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ProcessMethod
	{
		Type& t = type<mud::ProcessMethod>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessMethod", sizeof(mud::ProcessMethod), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ProcessCallable>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessMethod, mud::ProcessCallable>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ProcessMethod__construct_0, { { "script", type<mud::VisualScript>(),  }, { "method", type<mud::Method>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::ProcessOutput
	{
		Type& t = type<mud::ProcessOutput>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessOutput", sizeof(mud::ProcessOutput), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Process>(), &type<mud::Param>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessOutput, mud::Process>(), base_offset<mud::ProcessOutput, mud::Param>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::ProcessScript
	{
		Type& t = type<mud::ProcessScript>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessScript", sizeof(mud::ProcessScript), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ProcessCallable>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessScript, mud::ProcessCallable>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ProcessScript__construct_0, { { "script", type<mud::VisualScript>(),  }, { "target", type<mud::VisualScript>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::ProcessSetMember
	{
		Type& t = type<mud::ProcessSetMember>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessSetMember", sizeof(mud::ProcessSetMember), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Process>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessSetMember, mud::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ProcessSetMember__construct_0, { { "script", type<mud::VisualScript>(),  }, { "member", type<mud::Member>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::ProcessValue
	{
		Type& t = type<mud::ProcessValue>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessValue", sizeof(mud::ProcessValue), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Process>() };
		static size_t bases_offsets[] = { base_offset<mud::ProcessValue, mud::Process>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ProcessValue__construct_0, { { "script", type<mud::VisualScript>(),  }, { "value", type<mud::Var>(),  } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::Script
	{
		Type& t = type<mud::Script>();
		static Meta meta = { t, &namspc({ "mud" }), "Script", sizeof(mud::Script), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Callable>() };
		static size_t bases_offsets[] = { base_offset<mud::Script, mud::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Script, m_index), type<uint32_t>(), "index", nullptr, Member::Value, nullptr },
			{ t, SIZE_MAX, type<mud::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Script__get_type },
			{ t, offsetof(mud::Script, m_name), type<string>(), "name", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Script, m_locked), type<bool>(), "locked", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// mud::Stream
	{
		Type& t = type<mud::Stream>();
		static Meta meta = { t, &namspc({ "mud" }), "Stream", sizeof(mud::Stream), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::StreamBranch>() };
		static size_t bases_offsets[] = { base_offset<mud::Stream, mud::StreamBranch>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::TextScript
	{
		Type& t = type<mud::TextScript>();
		static Meta meta = { t, &namspc({ "mud" }), "TextScript", sizeof(mud::TextScript), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Script>() };
		static size_t bases_offsets[] = { base_offset<mud::TextScript, mud::Script>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_TextScript__construct_0, { { "name", type<string>(),  }, { "language", type<mud::Language>(),  }, { "signature", type<mud::Signature>(), Param::Default } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::TextScript, m_language), type<mud::Language>(), "language", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TextScript, m_script), type<string>(), "script", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::TextScript, m_dirty), type<bool>(), "dirty", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, members, {}, {}, };
	}
	// mud::VisualScript
	{
		Type& t = type<mud::VisualScript>();
		static Meta meta = { t, &namspc({ "mud" }), "VisualScript", sizeof(mud::VisualScript), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Script>() };
		static size_t bases_offsets[] = { base_offset<mud::VisualScript, mud::Script>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_VisualScript__construct_0, { { "name", type<const char*>(), Param::Nullable }, { "signature", type<mud::Signature>(), Param::Default } } }
		};
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, {}, {}, {}, {}, };
	}
	// mud::WrenInterpreter
	{
		Type& t = type<mud::WrenInterpreter>();
		static Meta meta = { t, &namspc({ "mud" }), "WrenInterpreter", sizeof(mud::WrenInterpreter), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Interpreter>() };
		static size_t bases_offsets[] = { base_offset<mud::WrenInterpreter, mud::Interpreter>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
		m.m_types.push_back(&type<mud::Interpreter>());
		m.m_types.push_back(&type<mud::Language>());
		m.m_types.push_back(&type<mud::Pipe>());
		m.m_types.push_back(&type<mud::Process>());
		m.m_types.push_back(&type<mud::ScriptClass>());
		m.m_types.push_back(&type<mud::ScriptError>());
		m.m_types.push_back(&type<mud::StreamBranch>());
		m.m_types.push_back(&type<mud::Valve>());
		m.m_types.push_back(&type<mud::LuaInterpreter>());
		m.m_types.push_back(&type<mud::ProcessCallable>());
		m.m_types.push_back(&type<mud::ProcessCreate>());
		m.m_types.push_back(&type<mud::ProcessDisplay>());
		m.m_types.push_back(&type<mud::ProcessFunction>());
		m.m_types.push_back(&type<mud::ProcessGetMember>());
		m.m_types.push_back(&type<mud::ProcessInput>());
		m.m_types.push_back(&type<mud::ProcessMethod>());
		m.m_types.push_back(&type<mud::ProcessOutput>());
		m.m_types.push_back(&type<mud::ProcessScript>());
		m.m_types.push_back(&type<mud::ProcessSetMember>());
		m.m_types.push_back(&type<mud::ProcessValue>());
		m.m_types.push_back(&type<mud::Script>());
		m.m_types.push_back(&type<mud::Stream>());
		m.m_types.push_back(&type<mud::TextScript>());
		m.m_types.push_back(&type<mud::VisualScript>());
		m.m_types.push_back(&type<mud::WrenInterpreter>());
	}
}

namespace mud
{
	mud_lang::mud_lang()
		: Module("mud::lang", { &mud_infra::m(), &mud_type::m(), &mud_pool::m(), &mud_refl::m() })
	{
		// setup reflection meta data
		mud_lang_meta(*this);
	}
}

#ifdef MUD_LANG_MODULE
extern "C"
Module& getModule()
{
		return mud_lang::m();
}
#endif
