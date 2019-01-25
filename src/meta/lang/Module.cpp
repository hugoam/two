#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <type/Vector.h>
#include <type/Any.h>
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
		meta_enum<mud::Language>();
	}
	
	// Sequences
	
	// mud::Interpreter
	{
		Type& t = type<mud::Interpreter>();
		static Meta meta = { t, &namspc({ "mud" }), "Interpreter", sizeof(mud::Interpreter), TypeClass::Object };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Interpreter>();
	}
	// mud::Pipe
	{
		Type& t = type<mud::Pipe>();
		static Meta meta = { t, &namspc({ "mud" }), "Pipe", sizeof(mud::Pipe), TypeClass::Object };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Pipe>();
	}
	// mud::Process
	{
		Type& t = type<mud::Process>();
		static Meta meta = { t, &namspc({ "mud" }), "Process", sizeof(mud::Process), TypeClass::Object };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Process>(object).m_type); } }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Process>();
	}
	// mud::ScriptClass
	{
		Type& t = type<mud::ScriptClass>();
		static Meta meta = { t, &namspc({ "mud" }), "ScriptClass", sizeof(mud::ScriptClass), TypeClass::Object };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ScriptClass>(ref)) mud::ScriptClass( val<string>(args[0]), val<vector<mud::Type*>>(args[1]) ); }, { { "name", var(string()) }, { "parts", var(vector<mud::Type*>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::ScriptClass::m_name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&mud::ScriptClass::m_class_type), type<mud::Type>(), "class_type", Ref(type<mud::Type>()), Member::NonMutable, nullptr },
				{ t, member_address(&mud::ScriptClass::m_class), type<mud::Class>(), "class", Ref(type<mud::Class>()), Member::NonMutable, nullptr },
				{ t, member_address(&mud::ScriptClass::m_prototype), type<mud::Prototype>(), "prototype", Ref(type<mud::Prototype>()), Member::NonMutable, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ScriptClass>();
		meta_class<mud::ScriptClass>();
	}
	// mud::ScriptError
	{
		Type& t = type<mud::ScriptError>();
		static Meta meta = { t, &namspc({ "mud" }), "ScriptError", sizeof(mud::ScriptError), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ScriptError>(ref)) mud::ScriptError(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ScriptError>(ref)) mud::ScriptError(val<mud::ScriptError>(other)); } }
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ScriptError>();
	}
	// mud::StreamBranch
	{
		Type& t = type<mud::StreamBranch>();
		static Meta meta = { t, &namspc({ "mud" }), "StreamBranch", sizeof(mud::StreamBranch), TypeClass::Object };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::StreamBranch>();
	}
	// mud::Valve
	{
		Type& t = type<mud::Valve>();
		static Meta meta = { t, &namspc({ "mud" }), "Valve", sizeof(mud::Valve), TypeClass::Object };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Valve>();
	}
	// mud::LuaInterpreter
	{
		Type& t = type<mud::LuaInterpreter>();
		static Meta meta = { t, &namspc({ "mud" }), "LuaInterpreter", sizeof(mud::LuaInterpreter), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Interpreter>() },
			{ base_offset<mud::LuaInterpreter, mud::Interpreter>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::LuaInterpreter>();
	}
	// mud::ProcessCallable
	{
		Type& t = type<mud::ProcessCallable>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessCallable", sizeof(mud::ProcessCallable), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Process>() },
			{ base_offset<mud::ProcessCallable, mud::Process>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ProcessCallable>(ref)) mud::ProcessCallable( val<mud::VisualScript>(args[0]), val<mud::Callable>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "callable", Ref(type<mud::Callable>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ProcessCallable>();
		meta_class<mud::ProcessCallable>();
	}
	// mud::ProcessCreate
	{
		Type& t = type<mud::ProcessCreate>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessCreate", sizeof(mud::ProcessCreate), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Process>() },
			{ base_offset<mud::ProcessCreate, mud::Process>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ProcessCreate>(ref)) mud::ProcessCreate( val<mud::VisualScript>(args[0]), val<mud::Type>(args[1]), val<mud::Constructor>(args[2]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "type", Ref(type<mud::Type>()) }, { "constructor", Ref(type<mud::Constructor>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ProcessCreate>();
		meta_class<mud::ProcessCreate>();
	}
	// mud::ProcessDisplay
	{
		Type& t = type<mud::ProcessDisplay>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessDisplay", sizeof(mud::ProcessDisplay), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Process>() },
			{ base_offset<mud::ProcessDisplay, mud::Process>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ProcessDisplay>();
	}
	// mud::ProcessFunction
	{
		Type& t = type<mud::ProcessFunction>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessFunction", sizeof(mud::ProcessFunction), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::ProcessCallable>() },
			{ base_offset<mud::ProcessFunction, mud::ProcessCallable>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ProcessFunction>(ref)) mud::ProcessFunction( val<mud::VisualScript>(args[0]), val<mud::Function>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "function", Ref(type<mud::Function>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ProcessFunction>();
		meta_class<mud::ProcessFunction>();
	}
	// mud::ProcessGetMember
	{
		Type& t = type<mud::ProcessGetMember>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessGetMember", sizeof(mud::ProcessGetMember), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Process>() },
			{ base_offset<mud::ProcessGetMember, mud::Process>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ProcessGetMember>(ref)) mud::ProcessGetMember( val<mud::VisualScript>(args[0]), val<mud::Member>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "member", Ref(type<mud::Member>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ProcessGetMember>();
		meta_class<mud::ProcessGetMember>();
	}
	// mud::ProcessInput
	{
		Type& t = type<mud::ProcessInput>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessInput", sizeof(mud::ProcessInput), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Process>(), &type<mud::Param>() },
			{ base_offset<mud::ProcessInput, mud::Process>(), base_offset<mud::ProcessInput, mud::Param>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ProcessInput>();
	}
	// mud::ProcessMethod
	{
		Type& t = type<mud::ProcessMethod>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessMethod", sizeof(mud::ProcessMethod), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::ProcessCallable>() },
			{ base_offset<mud::ProcessMethod, mud::ProcessCallable>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ProcessMethod>(ref)) mud::ProcessMethod( val<mud::VisualScript>(args[0]), val<mud::Method>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "method", Ref(type<mud::Method>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ProcessMethod>();
		meta_class<mud::ProcessMethod>();
	}
	// mud::ProcessOutput
	{
		Type& t = type<mud::ProcessOutput>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessOutput", sizeof(mud::ProcessOutput), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Process>(), &type<mud::Param>() },
			{ base_offset<mud::ProcessOutput, mud::Process>(), base_offset<mud::ProcessOutput, mud::Param>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ProcessOutput>();
	}
	// mud::ProcessScript
	{
		Type& t = type<mud::ProcessScript>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessScript", sizeof(mud::ProcessScript), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::ProcessCallable>() },
			{ base_offset<mud::ProcessScript, mud::ProcessCallable>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ProcessScript>(ref)) mud::ProcessScript( val<mud::VisualScript>(args[0]), val<mud::VisualScript>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "target", Ref(type<mud::VisualScript>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ProcessScript>();
		meta_class<mud::ProcessScript>();
	}
	// mud::ProcessSetMember
	{
		Type& t = type<mud::ProcessSetMember>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessSetMember", sizeof(mud::ProcessSetMember), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Process>() },
			{ base_offset<mud::ProcessSetMember, mud::Process>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ProcessSetMember>(ref)) mud::ProcessSetMember( val<mud::VisualScript>(args[0]), val<mud::Member>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "member", Ref(type<mud::Member>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ProcessSetMember>();
		meta_class<mud::ProcessSetMember>();
	}
	// mud::ProcessValue
	{
		Type& t = type<mud::ProcessValue>();
		static Meta meta = { t, &namspc({ "mud" }), "ProcessValue", sizeof(mud::ProcessValue), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Process>() },
			{ base_offset<mud::ProcessValue, mud::Process>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ProcessValue>(ref)) mud::ProcessValue( val<mud::VisualScript>(args[0]), val<mud::Var>(args[1]) ); }, { { "script", Ref(type<mud::VisualScript>()) }, { "value", Ref(type<mud::Var>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::ProcessValue>();
		meta_class<mud::ProcessValue>();
	}
	// mud::Script
	{
		Type& t = type<mud::Script>();
		static Meta meta = { t, &namspc({ "mud" }), "Script", sizeof(mud::Script), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Callable>() },
			{ base_offset<mud::Script, mud::Callable>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::Script::m_index), type<uint32_t>(), "index", var(uint32_t()), Member::Value, nullptr },
				{ t, Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Script>(object).m_type); } },
				{ t, member_address(&mud::Script::m_name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&mud::Script::m_locked), type<bool>(), "locked", var(bool()), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Script>();
	}
	// mud::Stream
	{
		Type& t = type<mud::Stream>();
		static Meta meta = { t, &namspc({ "mud" }), "Stream", sizeof(mud::Stream), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::StreamBranch>() },
			{ base_offset<mud::Stream, mud::StreamBranch>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Stream>();
	}
	// mud::TextScript
	{
		Type& t = type<mud::TextScript>();
		static Meta meta = { t, &namspc({ "mud" }), "TextScript", sizeof(mud::TextScript), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Script>() },
			{ base_offset<mud::TextScript, mud::Script>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::TextScript>(ref)) mud::TextScript( val<string>(args[0]), val<mud::Language>(args[1]), val<mud::Signature>(args[2]) ); }, { { "name", var(string()) }, { "language", var(mud::Language()) }, { "signature", Ref(type<mud::Signature>()), Param::Default } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ t, member_address(&mud::TextScript::m_language), type<mud::Language>(), "language", var(mud::Language()), Member::Value, nullptr },
				{ t, member_address(&mud::TextScript::m_script), type<string>(), "script", var(string()), Member::Value, nullptr },
				{ t, member_address(&mud::TextScript::m_dirty), type<bool>(), "dirty", var(bool()), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::TextScript>();
		meta_class<mud::TextScript>();
	}
	// mud::VisualScript
	{
		Type& t = type<mud::VisualScript>();
		static Meta meta = { t, &namspc({ "mud" }), "VisualScript", sizeof(mud::VisualScript), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Script>() },
			{ base_offset<mud::VisualScript, mud::Script>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::VisualScript>(ref)) mud::VisualScript( val<const char*>(args[0]), val<mud::Signature>(args[1]) ); }, { { "name", Ref(type<const char*>()), Param::Nullable }, { "signature", Ref(type<mud::Signature>()), Param::Default } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_pool<mud::VisualScript>();
		meta_class<mud::VisualScript>();
	}
	// mud::WrenInterpreter
	{
		Type& t = type<mud::WrenInterpreter>();
		static Meta meta = { t, &namspc({ "mud" }), "WrenInterpreter", sizeof(mud::WrenInterpreter), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Interpreter>() },
			{ base_offset<mud::WrenInterpreter, mud::Interpreter>() },
			// constructors
			{
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::WrenInterpreter>();
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
