#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.type;
#else
#endif


namespace mud
{
	void mud_type_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	{
		Type& t = type<bool>();
		static Meta meta = { t, &namspc({}), "bool", sizeof(bool), TypeClass::BaseType };
		meta_basetype<bool>();
	}
	{
		Type& t = type<char>();
		static Meta meta = { t, &namspc({}), "char", sizeof(char), TypeClass::BaseType };
		meta_basetype<char>();
	}
	{
		Type& t = type<const char*>();
		static Meta meta = { t, &namspc({}), "const char*", sizeof(const char*), TypeClass::BaseType };
		meta_basetype<const char*>();
	}
	{
		Type& t = type<double>();
		static Meta meta = { t, &namspc({}), "double", sizeof(double), TypeClass::BaseType };
		meta_basetype<double>();
	}
	{
		Type& t = type<float>();
		static Meta meta = { t, &namspc({}), "float", sizeof(float), TypeClass::BaseType };
		meta_basetype<float>();
	}
	{
		Type& t = type<int>();
		static Meta meta = { t, &namspc({}), "int", sizeof(int), TypeClass::BaseType };
		meta_basetype<int>();
	}
	{
		Type& t = type<long>();
		static Meta meta = { t, &namspc({}), "long", sizeof(long), TypeClass::BaseType };
		meta_basetype<long>();
	}
	{
		Type& t = type<long long>();
		static Meta meta = { t, &namspc({}), "long long", sizeof(long long), TypeClass::BaseType };
		meta_basetype<long long>();
	}
	{
		Type& t = type<short>();
		static Meta meta = { t, &namspc({}), "short", sizeof(short), TypeClass::BaseType };
		meta_basetype<short>();
	}
	{
		Type& t = type<string>();
		static Meta meta = { t, &namspc({}), "string", sizeof(string), TypeClass::BaseType };
		meta_basetype<string>();
	}
	{
		Type& t = type<unsigned char>();
		static Meta meta = { t, &namspc({}), "unsigned char", sizeof(unsigned char), TypeClass::BaseType };
		meta_basetype<unsigned char>();
	}
	{
		Type& t = type<unsigned int>();
		static Meta meta = { t, &namspc({}), "unsigned int", sizeof(unsigned int), TypeClass::BaseType };
		meta_basetype<unsigned int>();
	}
	{
		Type& t = type<unsigned long>();
		static Meta meta = { t, &namspc({}), "unsigned long", sizeof(unsigned long), TypeClass::BaseType };
		meta_basetype<unsigned long>();
	}
	{
		Type& t = type<unsigned long long>();
		static Meta meta = { t, &namspc({}), "unsigned long long", sizeof(unsigned long long), TypeClass::BaseType };
		meta_basetype<unsigned long long>();
	}
	{
		Type& t = type<unsigned short>();
		static Meta meta = { t, &namspc({}), "unsigned short", sizeof(unsigned short), TypeClass::BaseType };
		meta_basetype<unsigned short>();
	}
	{
		Type& t = type<void>();
		static Meta meta = { t, &namspc({}), "void", 0, TypeClass::BaseType };
		meta_basetype<void>();
	}
	{
		Type& t = type<void*>();
		static Meta meta = { t, &namspc({}), "void*", sizeof(void*), TypeClass::BaseType };
		meta_basetype<void*>();
	}
	
	// Enums
	
	// Sequences
	{
		Type& t = type<vector<mud::Ref>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Ref>", sizeof(vector<mud::Ref>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Ref>();
		meta_vector<vector<mud::Ref>, mud::Ref>();
	}
	
	// mud::Index
	{
		Type& t = type<mud::Index>();
		static Meta meta = { t, &namspc({ "mud" }), "Index", sizeof(mud::Index), TypeClass::Object };
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
				{ t, "indexer", member_address<mud::Indexer&(mud::Index::*)(mud::Type&)>(&mud::Index::indexer), [](Ref object, array<Var> args, Var& result) { result = Ref(&val<mud::Index>(object).indexer(val<mud::Type>(args[0]))); }, { { "type", Ref(type<mud::Type>()) } }, Ref(type<mud::Indexer>()) }
			},
			// static members
			{
				{ t, "me", Ref(&mud::Index::me) }
			}
		};
		meta_class<mud::Index>();
	}
	// mud::Indexer
	{
		Type& t = type<mud::Indexer>();
		static Meta meta = { t, &namspc({ "mud" }), "Indexer", sizeof(mud::Indexer), TypeClass::Object };
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
				{ t, Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Indexer>(object).m_type); } },
				{ t, member_address(&mud::Indexer::m_objects), type<vector<mud::Ref>>(), "objects", var(vector<mud::Ref>()), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Indexer>();
	}
	// mud::Ref
	{
		Type& t = type<mud::Ref>();
		static Meta meta = { t, &namspc({ "mud" }), "Ref", sizeof(mud::Ref), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Ref>(ref)) mud::Ref(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Ref>(ref)) mud::Ref( val<void*>(args[0]), val<mud::Type>(args[1]) ); }, { { "value", Ref(), Param::Nullable }, { "type", Ref(type<mud::Type>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Ref>(ref)) mud::Ref(val<mud::Ref>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Ref::m_type), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Ref::m_value), type<void*>(), "value", Ref(), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Ref>();
	}
	// mud::Type
	{
		Type& t = type<mud::Type>();
		static Meta meta = { t, &namspc({ "mud" }), "Type", sizeof(mud::Type), TypeClass::Object };
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
				{ t, member_address(&mud::Type::m_id), type<uint32_t>(), "id", var(uint32_t()), Member::Value, nullptr },
				{ t, member_address(&mud::Type::m_name), type<const char*>(), "name", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Type::m_size), type<size_t>(), "size", var(size_t()), Member::Value, nullptr },
				{ t, member_address(&mud::Type::m_base), type<mud::Type>(), "base", Ref(type<mud::Type>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Type>();
	}
	// mud::Var
	{
		Type& t = type<mud::Var>();
		static Meta meta = { t, &namspc({ "mud" }), "Var", sizeof(mud::Var), TypeClass::Object };
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
		meta_class<mud::Var>();
	}
		m.m_types.push_back(&type<mud::Index>());
		m.m_types.push_back(&type<mud::Indexer>());
		m.m_types.push_back(&type<mud::Ref>());
		m.m_types.push_back(&type<mud::Type>());
		m.m_types.push_back(&type<mud::Var>());
		m.m_types.push_back(&type<bool>());
		m.m_types.push_back(&type<char>());
		m.m_types.push_back(&type<const char*>());
		m.m_types.push_back(&type<double>());
		m.m_types.push_back(&type<float>());
		m.m_types.push_back(&type<int>());
		m.m_types.push_back(&type<long>());
		m.m_types.push_back(&type<long long>());
		m.m_types.push_back(&type<short>());
		m.m_types.push_back(&type<string>());
		m.m_types.push_back(&type<unsigned char>());
		m.m_types.push_back(&type<unsigned int>());
		m.m_types.push_back(&type<unsigned long>());
		m.m_types.push_back(&type<unsigned long long>());
		m.m_types.push_back(&type<unsigned short>());
		m.m_types.push_back(&type<vector<mud::Ref>>());
		m.m_types.push_back(&type<void>());
		m.m_types.push_back(&type<void*>());
		{
			auto func = [](array<Var> args, Var& result) {  result = mud::indexed(val<mud::Type>(args[0]), val<uint32_t>(args[1])); };
			vector<Param> params = { { "type", Ref(type<mud::Type>()) }, { "id", var(uint32_t()) } };
			static Function f = { &namspc({ "mud" }), "indexed", funcptr<mud::Ref(*)(mud::Type&, uint32_t)>(&mud::indexed), func, params, Ref() };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_type::mud_type()
		: Module("mud::type", { &mud_infra::m() })
	{
		// setup reflection meta data
		mud_type_meta(*this);
	}
}

#ifdef MUD_TYPE_MODULE
extern "C"
Module& getModule()
{
		return mud_type::m();
}
#endif
