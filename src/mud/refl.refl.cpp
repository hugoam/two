#pragma once

#include <mud/pool.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#endif


namespace mud
{
	void mud_refl_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		static Meta meta = { type<mud::TypeClass>(), &namspc({ "mud" }), "TypeClass", sizeof(mud::TypeClass), TypeClass::Enum };
		static Enum enu = { type<mud::TypeClass>(),
			true,
			{ "None", "Object", "Struct", "Sequence", "BaseType", "Enum" },
			{ 0, 1, 2, 4, 5, 6 },
			{ var(mud::TypeClass::None), var(mud::TypeClass::Object), var(mud::TypeClass::Struct), var(mud::TypeClass::Sequence), var(mud::TypeClass::BaseType), var(mud::TypeClass::Enum) }
		};
		meta_enum<mud::TypeClass>();
	}
	
	// Sequences
	{
		static Meta meta = { type<vector<mud::Function*>>(), &namspc({}), "vector<mud::Function*>", sizeof(vector<mud::Function*>), TypeClass::Sequence };
		static Class cls = { type<vector<mud::Function*>>() };
		cls.m_content = &type<mud::Function>();
		meta_vector<vector<mud::Function*>, mud::Function*>();
	}
	{
		static Meta meta = { type<vector<mud::Module*>>(), &namspc({}), "vector<mud::Module*>", sizeof(vector<mud::Module*>), TypeClass::Sequence };
		static Class cls = { type<vector<mud::Module*>>() };
		cls.m_content = &type<mud::Module>();
		meta_vector<vector<mud::Module*>, mud::Module*>();
	}
	{
		static Meta meta = { type<vector<mud::Type*>>(), &namspc({}), "vector<mud::Type*>", sizeof(vector<mud::Type*>), TypeClass::Sequence };
		static Class cls = { type<vector<mud::Type*>>() };
		cls.m_content = &type<mud::Type>();
		meta_vector<vector<mud::Type*>, mud::Type*>();
	}
	{
		static Meta meta = { type<vector<mud::Var>>(), &namspc({}), "vector<mud::Var>", sizeof(vector<mud::Var>), TypeClass::Sequence };
		static Class cls = { type<vector<mud::Var>>() };
		cls.m_content = &type<mud::Var>();
		meta_vector<vector<mud::Var>, mud::Var>();
	}
	
	// mud::Call
	{
		static Meta meta = { type<mud::Call>(), &namspc({ "mud" }), "Call", sizeof(mud::Call), TypeClass::Struct };
		static Class cls = { type<mud::Call>(),
			// bases
			{  },
			{  },
			// constructors
			{
				{ type<mud::Call>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Call>(ref)) mud::Call(  ); }, {} },
				{ type<mud::Call>(), [](Ref ref, array<Var> args) { new(&val<mud::Call>(ref)) mud::Call( val<mud::Callable>(args[0]), val<vector<mud::Var>>(args[1]) ); }, { { "callable", Ref(type<mud::Callable>()) }, { "arguments", var(vector<mud::Var>()) } } }
			},
			// copy constructor
			{
				{ type<mud::Call>(), [](Ref ref, Ref other) { new(&val<mud::Call>(ref)) mud::Call(val<mud::Call>(other)); } }
			},
			// members
			{
				{ type<mud::Call>(), member_address(&mud::Call::m_arguments), type<vector<mud::Var>>(), "arguments", var(vector<mud::Var>()), Member::Value, nullptr },
				{ type<mud::Call>(), member_address(&mud::Call::m_result), type<mud::Var>(), "result", Ref(type<mud::Var>()), Member::NonMutable, nullptr }
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
		static Meta meta = { type<mud::Callable>(), &namspc({ "mud" }), "Callable", sizeof(mud::Callable), TypeClass::Object };
		static Class cls = { type<mud::Callable>(),
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
		static Meta meta = { type<mud::Class>(), &namspc({ "mud" }), "Class", sizeof(mud::Class), TypeClass::Object };
		static Class cls = { type<mud::Class>(),
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
		static Meta meta = { type<mud::Convert>(), &namspc({ "mud" }), "Convert", sizeof(mud::Convert), TypeClass::Object };
		static Class cls = { type<mud::Convert>(),
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
		static Meta meta = { type<mud::Creator>(), &namspc({ "mud" }), "Creator", sizeof(mud::Creator), TypeClass::Object };
		static Class cls = { type<mud::Creator>(),
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
				{ type<mud::Creator>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Creator>(object).m_type); } },
				{ type<mud::Creator>(), member_address(&mud::Creator::m_construct), type<bool>(), "construct", var(bool()), Member::Value, nullptr },
				{ type<mud::Creator>(), member_address(&mud::Creator::m_prototype), type<mud::Type>(), "prototype", Ref(type<mud::Type>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ type<mud::Creator>(), member_address<mud::Injector&(mud::Creator::*)() const>(&mud::Creator::injector), type<mud::Injector>(), "injector", Ref(type<mud::Injector>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Creator>(object).injector()); } }
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
		static Meta meta = { type<mud::Enum>(), &namspc({ "mud" }), "Enum", sizeof(mud::Enum), TypeClass::Object };
		static Class cls = { type<mud::Enum>(),
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
		static Meta meta = { type<mud::Member>(), &namspc({ "mud" }), "Member", sizeof(mud::Member), TypeClass::Object };
		static Class cls = { type<mud::Member>(),
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
		static Meta meta = { type<mud::Meta>(), &namspc({ "mud" }), "Meta", sizeof(mud::Meta), TypeClass::Object };
		static Class cls = { type<mud::Meta>(),
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
		static Meta meta = { type<mud::Module>(), &namspc({ "mud" }), "Module", sizeof(mud::Module), TypeClass::Object };
		static Class cls = { type<mud::Module>(),
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
				{ type<mud::Module>(), member_address(&mud::Module::m_name), type<const char*>(), "name", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ type<mud::Module>(), member_address(&mud::Module::m_deps), type<vector<mud::Module*>>(), "deps", var(vector<mud::Module*>()), Member::Value, nullptr },
				{ type<mud::Module>(), member_address(&mud::Module::m_types), type<vector<mud::Type*>>(), "types", var(vector<mud::Type*>()), Member::Value, nullptr },
				{ type<mud::Module>(), member_address(&mud::Module::m_functions), type<vector<mud::Function*>>(), "functions", var(vector<mud::Function*>()), Member::Value, nullptr },
				{ type<mud::Module>(), member_address(&mud::Module::m_path), type<const char*>(), "path", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
		static Meta meta = { type<mud::Namespace>(), &namspc({ "mud" }), "Namespace", sizeof(mud::Namespace), TypeClass::Object };
		static Class cls = { type<mud::Namespace>(),
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
		static Meta meta = { type<mud::Operator>(), &namspc({ "mud" }), "Operator", sizeof(mud::Operator), TypeClass::Struct };
		static Class cls = { type<mud::Operator>(),
			// bases
			{  },
			{  },
			// constructors
			{
				{ type<mud::Operator>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Operator>(ref)) mud::Operator(  ); }, {} }
			},
			// copy constructor
			{
				{ type<mud::Operator>(), [](Ref ref, Ref other) { new(&val<mud::Operator>(ref)) mud::Operator(val<mud::Operator>(other)); } }
			},
			// members
			{
				{ type<mud::Operator>(), member_address(&mud::Operator::m_function), type<mud::Function>(), "function", Ref(type<mud::Function>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ type<mud::Operator>(), member_address(&mud::Operator::m_type), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ type<mud::Operator>(), member_address(&mud::Operator::m_name), type<const char*>(), "name", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ type<mud::Operator>(), member_address(&mud::Operator::m_sign), type<const char*>(), "sign", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
		static Meta meta = { type<mud::Param>(), &namspc({ "mud" }), "Param", sizeof(mud::Param), TypeClass::Object };
		static Class cls = { type<mud::Param>(),
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
		static Meta meta = { type<mud::Signature>(), &namspc({ "mud" }), "Signature", sizeof(mud::Signature), TypeClass::Object };
		static Class cls = { type<mud::Signature>(),
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
		static Meta meta = { type<mud::Static>(), &namspc({ "mud" }), "Static", sizeof(mud::Static), TypeClass::Object };
		static Class cls = { type<mud::Static>(),
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
		static Meta meta = { type<mud::System>(), &namspc({ "mud" }), "System", sizeof(mud::System), TypeClass::Object };
		static Class cls = { type<mud::System>(),
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
				{ type<mud::System>(), member_address(&mud::System::m_modules), type<vector<mud::Module*>>(), "modules", var(vector<mud::Module*>()), Member::Value, nullptr },
				{ type<mud::System>(), member_address(&mud::System::m_types), type<vector<mud::Type*>>(), "types", var(vector<mud::Type*>()), Member::Value, nullptr },
				{ type<mud::System>(), member_address(&mud::System::m_functions), type<vector<mud::Function*>>(), "functions", var(vector<mud::Function*>()), Member::Value, nullptr }
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
		static Meta meta = { type<mud::Constructor>(), &namspc({ "mud" }), "Constructor", sizeof(mud::Constructor), TypeClass::Object };
		static Class cls = { type<mud::Constructor>(),
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
		static Meta meta = { type<mud::CopyConstructor>(), &namspc({ "mud" }), "CopyConstructor", sizeof(mud::CopyConstructor), TypeClass::Object };
		static Class cls = { type<mud::CopyConstructor>(),
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
		static Meta meta = { type<mud::Destructor>(), &namspc({ "mud" }), "Destructor", sizeof(mud::Destructor), TypeClass::Object };
		static Class cls = { type<mud::Destructor>(),
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
		static Meta meta = { type<mud::Function>(), &namspc({ "mud" }), "Function", sizeof(mud::Function), TypeClass::Object };
		static Class cls = { type<mud::Function>(),
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
		static Meta meta = { type<mud::Injector>(), &namspc({ "mud" }), "Injector", sizeof(mud::Injector), TypeClass::Object };
		static Class cls = { type<mud::Injector>(),
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
		static Meta meta = { type<mud::Method>(), &namspc({ "mud" }), "Method", sizeof(mud::Method), TypeClass::Object };
		static Class cls = { type<mud::Method>(),
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
