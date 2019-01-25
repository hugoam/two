#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/refl/Convert.h>
#endif

#include <refl/Api.h>

namespace mud
{
	void mud_refl_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::TypeClass>();
		static Meta meta = { t, &namspc({ "mud" }), "TypeClass", sizeof(mud::TypeClass), TypeClass::Enum };
		static cstring ids[] = { "None", "Object", "Struct", "Sequence", "BaseType", "Enum" };
		static uint32_t values[] = { 0, 1, 2, 4, 5, 6 };
		static mud::TypeClass vars[] = { mud::TypeClass::None, mud::TypeClass::Object, mud::TypeClass::Struct, mud::TypeClass::Sequence, mud::TypeClass::BaseType, mud::TypeClass::Enum};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::TypeClass>();
	}
	
	// Sequences
	{
		Type& t = type<vector<mud::Function*>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Function*>", sizeof(vector<mud::Function*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Function>();
		meta_vector<vector<mud::Function*>, mud::Function*>();
	}
	{
		Type& t = type<vector<mud::Module*>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Module*>", sizeof(vector<mud::Module*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Module>();
		meta_vector<vector<mud::Module*>, mud::Module*>();
	}
	{
		Type& t = type<vector<mud::Type*>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Type*>", sizeof(vector<mud::Type*>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Type>();
		meta_vector<vector<mud::Type*>, mud::Type*>();
	}
	{
		Type& t = type<vector<mud::Var>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Var>", sizeof(vector<mud::Var>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Var>();
		meta_vector<vector<mud::Var>, mud::Var>();
	}
	
	// mud::Call
	{
		Type& t = type<mud::Call>();
		static Meta meta = { t, &namspc({ "mud" }), "Call", sizeof(mud::Call), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Call>(ref)) mud::Call(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Call>(ref)) mud::Call( val<mud::Callable>(args[0]), val<vector<mud::Var>>(args[1]) ); }, { { "callable", Ref(type<mud::Callable>()) }, { "arguments", var(vector<mud::Var>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Call>(ref)) mud::Call(val<mud::Call>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Call::m_arguments), type<vector<mud::Var>>(), "arguments", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Call::m_result), type<mud::Var>(), "result", Ref(), Member::NonMutable, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Call>();
	}
	// mud::Callable
	{
		Type& t = type<mud::Callable>();
		static Meta meta = { t, &namspc({ "mud" }), "Callable", sizeof(mud::Callable), TypeClass::Object };
		// defaults
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
		meta_class<mud::Callable>();
	}
	// mud::Class
	{
		Type& t = type<mud::Class>();
		static Meta meta = { t, &namspc({ "mud" }), "Class", sizeof(mud::Class), TypeClass::Object };
		// defaults
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
		meta_class<mud::Class>();
	}
	// mud::Convert
	{
		Type& t = type<mud::Convert>();
		static Meta meta = { t, &namspc({ "mud" }), "Convert", sizeof(mud::Convert), TypeClass::Object };
		// defaults
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
		meta_class<mud::Convert>();
	}
	// mud::Creator
	{
		Type& t = type<mud::Creator>();
		static Meta meta = { t, &namspc({ "mud" }), "Creator", sizeof(mud::Creator), TypeClass::Object };
		// defaults
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
				{ t, Address(), type<mud::Type>(), "type", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Creator>(object).m_type); } },
				{ t, member_address(&mud::Creator::m_construct), type<bool>(), "construct", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Creator::m_prototype), type<mud::Type>(), "prototype", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address<mud::Injector&(mud::Creator::*)() const>(&mud::Creator::injector), type<mud::Injector>(), "injector", Ref(), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Creator>(object).injector()); } }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Creator>();
	}
	// mud::Enum
	{
		Type& t = type<mud::Enum>();
		static Meta meta = { t, &namspc({ "mud" }), "Enum", sizeof(mud::Enum), TypeClass::Object };
		// defaults
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
		meta_class<mud::Enum>();
	}
	// mud::Member
	{
		Type& t = type<mud::Member>();
		static Meta meta = { t, &namspc({ "mud" }), "Member", sizeof(mud::Member), TypeClass::Object };
		// defaults
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
		meta_class<mud::Member>();
	}
	// mud::Meta
	{
		Type& t = type<mud::Meta>();
		static Meta meta = { t, &namspc({ "mud" }), "Meta", sizeof(mud::Meta), TypeClass::Object };
		// defaults
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
		meta_class<mud::Meta>();
	}
	// mud::Module
	{
		Type& t = type<mud::Module>();
		static Meta meta = { t, &namspc({ "mud" }), "Module", sizeof(mud::Module), TypeClass::Object };
		// defaults
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
				{ t, member_address(&mud::Module::m_name), type<const char*>(), "name", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Module::m_deps), type<vector<mud::Module*>>(), "deps", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Module::m_types), type<vector<mud::Type*>>(), "types", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Module::m_functions), type<vector<mud::Function*>>(), "functions", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Module::m_path), type<const char*>(), "path", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Module>();
	}
	// mud::Namespace
	{
		Type& t = type<mud::Namespace>();
		static Meta meta = { t, &namspc({ "mud" }), "Namespace", sizeof(mud::Namespace), TypeClass::Object };
		// defaults
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
		meta_class<mud::Namespace>();
	}
	// mud::Operator
	{
		Type& t = type<mud::Operator>();
		static Meta meta = { t, &namspc({ "mud" }), "Operator", sizeof(mud::Operator), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Operator>(ref)) mud::Operator(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Operator>(ref)) mud::Operator(val<mud::Operator>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Operator::m_function), type<mud::Function>(), "function", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Operator::m_type), type<mud::Type>(), "type", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Operator::m_name), type<const char*>(), "name", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Operator::m_sign), type<const char*>(), "sign", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Operator>();
	}
	// mud::Param
	{
		Type& t = type<mud::Param>();
		static Meta meta = { t, &namspc({ "mud" }), "Param", sizeof(mud::Param), TypeClass::Object };
		// defaults
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
		meta_class<mud::Param>();
	}
	// mud::Signature
	{
		Type& t = type<mud::Signature>();
		static Meta meta = { t, &namspc({ "mud" }), "Signature", sizeof(mud::Signature), TypeClass::Object };
		// defaults
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
		meta_class<mud::Signature>();
	}
	// mud::Static
	{
		Type& t = type<mud::Static>();
		static Meta meta = { t, &namspc({ "mud" }), "Static", sizeof(mud::Static), TypeClass::Object };
		// defaults
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
		meta_class<mud::Static>();
	}
	// mud::System
	{
		Type& t = type<mud::System>();
		static Meta meta = { t, &namspc({ "mud" }), "System", sizeof(mud::System), TypeClass::Object };
		// defaults
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
				{ t, member_address(&mud::System::m_modules), type<vector<mud::Module*>>(), "modules", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::System::m_types), type<vector<mud::Type*>>(), "types", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::System::m_functions), type<vector<mud::Function*>>(), "functions", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::System>();
	}
	// mud::Constructor
	{
		Type& t = type<mud::Constructor>();
		static Meta meta = { t, &namspc({ "mud" }), "Constructor", sizeof(mud::Constructor), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Callable>() },
			{ base_offset<mud::Constructor, mud::Callable>() },
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
		meta_class<mud::Constructor>();
	}
	// mud::CopyConstructor
	{
		Type& t = type<mud::CopyConstructor>();
		static Meta meta = { t, &namspc({ "mud" }), "CopyConstructor", sizeof(mud::CopyConstructor), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Callable>() },
			{ base_offset<mud::CopyConstructor, mud::Callable>() },
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
		meta_class<mud::CopyConstructor>();
	}
	// mud::Destructor
	{
		Type& t = type<mud::Destructor>();
		static Meta meta = { t, &namspc({ "mud" }), "Destructor", sizeof(mud::Destructor), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Callable>() },
			{ base_offset<mud::Destructor, mud::Callable>() },
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
		meta_class<mud::Destructor>();
	}
	// mud::Function
	{
		Type& t = type<mud::Function>();
		static Meta meta = { t, &namspc({ "mud" }), "Function", sizeof(mud::Function), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Callable>() },
			{ base_offset<mud::Function, mud::Callable>() },
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
		meta_class<mud::Function>();
	}
	// mud::Injector
	{
		Type& t = type<mud::Injector>();
		static Meta meta = { t, &namspc({ "mud" }), "Injector", sizeof(mud::Injector), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Call>() },
			{ base_offset<mud::Injector, mud::Call>() },
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
		meta_class<mud::Injector>();
	}
	// mud::Method
	{
		Type& t = type<mud::Method>();
		static Meta meta = { t, &namspc({ "mud" }), "Method", sizeof(mud::Method), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Callable>() },
			{ base_offset<mud::Method, mud::Callable>() },
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
		meta_class<mud::Method>();
	}
		m.m_types.push_back(&type<mud::Call>());
		m.m_types.push_back(&type<mud::Callable>());
		m.m_types.push_back(&type<mud::Class>());
		m.m_types.push_back(&type<mud::Convert>());
		m.m_types.push_back(&type<mud::Creator>());
		m.m_types.push_back(&type<mud::Enum>());
		m.m_types.push_back(&type<mud::Member>());
		m.m_types.push_back(&type<mud::Meta>());
		m.m_types.push_back(&type<mud::Module>());
		m.m_types.push_back(&type<mud::Namespace>());
		m.m_types.push_back(&type<mud::Operator>());
		m.m_types.push_back(&type<mud::Param>());
		m.m_types.push_back(&type<mud::Signature>());
		m.m_types.push_back(&type<mud::Static>());
		m.m_types.push_back(&type<mud::System>());
		m.m_types.push_back(&type<mud::TypeClass>());
		m.m_types.push_back(&type<vector<mud::Function*>>());
		m.m_types.push_back(&type<vector<mud::Module*>>());
		m.m_types.push_back(&type<vector<mud::Type*>>());
		m.m_types.push_back(&type<vector<mud::Var>>());
		m.m_types.push_back(&type<mud::Constructor>());
		m.m_types.push_back(&type<mud::CopyConstructor>());
		m.m_types.push_back(&type<mud::Destructor>());
		m.m_types.push_back(&type<mud::Function>());
		m.m_types.push_back(&type<mud::Injector>());
		m.m_types.push_back(&type<mud::Method>());
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(args);  result = Ref(&mud::system()); };
			vector<Param> params = {};
			static Function f = { &namspc({ "mud" }), "system", funcptr<mud::System&(*)()>(&mud::system), func, params, Ref(type<mud::System>()) };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_refl::mud_refl()
		: Module("mud::refl", { &mud_infra::m(), &mud_type::m(), &mud_pool::m() })
	{
		// setup reflection meta data
		mud_refl_meta(*this);
	}
}

#ifdef MUD_REFL_MODULE
extern "C"
Module& getModule()
{
		return mud_refl::m();
}
#endif
