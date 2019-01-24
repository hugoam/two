#pragma once

#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/ecs.h>
#include <mud/refl.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>
#include <mud/ecs.refl.h>

#ifdef MUD_MODULES
module mud.ecs;
#else
#endif


namespace mud
{
	void mud_ecs_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// mud::Complex
	{
		static Meta meta = { type<mud::Complex>(), &namspc({ "mud" }), "Complex", sizeof(mud::Complex), TypeClass::Object };
		static Class cls = { type<mud::Complex>(),
			// bases
			{  },
			{  },
			// constructors
			{
				{ type<mud::Complex>(), [](Ref ref, array<Var> args) { new(&val<mud::Complex>(ref)) mud::Complex( val<uint32_t>(args[0]), val<mud::Type>(args[1]) ); }, { { "id", var(uint32_t()) }, { "type", Ref(type<mud::Type>()) } } },
				{ type<mud::Complex>(), [](Ref ref, array<Var> args) { new(&val<mud::Complex>(ref)) mud::Complex( val<uint32_t>(args[0]), val<mud::Type>(args[1]), val<vector<mud::Ref>>(args[2]) ); }, { { "id", var(uint32_t()) }, { "type", Ref(type<mud::Type>()) }, { "parts", var(vector<mud::Ref>()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
				{ type<mud::Complex>(), member_address(&mud::Complex::m_id), type<uint32_t>(), "id", var(uint32_t()), Member::Value, nullptr },
				{ type<mud::Complex>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Complex>(object).m_type); } },
				{ type<mud::Complex>(), Address(), type<mud::Prototype>(), "prototype", Ref(type<mud::Prototype>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Complex>(object).m_prototype); } },
				{ type<mud::Complex>(), member_address(&mud::Complex::m_parts), type<vector<mud::Ref>>(), "parts", var(vector<mud::Ref>()), Member::Value, nullptr }
			},
			// methods
			{
				{ type<mud::Complex>(), "setup", member_address<void(mud::Complex::*)(const vector<mud::Ref>&)>(&mud::Complex::setup), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Complex>(object).setup(val<vector<mud::Ref>>(args[0])); }, { { "parts", var(vector<mud::Ref>()) } }, Var() },
				{ type<mud::Complex>(), "add_part", member_address<void(mud::Complex::*)(mud::Ref)>(&mud::Complex::add_part), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Complex>(object).add_part(args[0]); }, { { "part", Ref(), Param::Nullable } }, Var() },
				{ type<mud::Complex>(), "has_part", member_address<bool(mud::Complex::*)(mud::Type&)>(&mud::Complex::has_part), [](Ref object, array<Var> args, Var& result) { val<bool>(result) = val<mud::Complex>(object).has_part(val<mud::Type>(args[0])); }, { { "type", Ref(type<mud::Type>()) } }, var(bool()) },
				{ type<mud::Complex>(), "part", member_address<mud::Ref(mud::Complex::*)(mud::Type&)>(&mud::Complex::part), [](Ref object, array<Var> args, Var& result) { result = val<mud::Complex>(object).part(val<mud::Type>(args[0])); }, { { "type", Ref(type<mud::Type>()) } }, Ref() },
				{ type<mud::Complex>(), "try_part", member_address<mud::Ref(mud::Complex::*)(mud::Type&)>(&mud::Complex::try_part), [](Ref object, array<Var> args, Var& result) { result = val<mud::Complex>(object).try_part(val<mud::Type>(args[0])); }, { { "type", Ref(type<mud::Type>()) } }, Ref() }
			},
			// static members
			{
			}
		};
		init_pool<mud::Complex>();
		meta_class<mud::Complex>();
	}
	// mud::Entity
	{
		static Meta meta = { type<mud::Entity>(), &namspc({ "mud" }), "Entity", sizeof(mud::Entity), TypeClass::Struct };
		static Class cls = { type<mud::Entity>(),
			// bases
			{  },
			{  },
			// constructors
			{
				{ type<mud::Entity>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Entity>(ref)) mud::Entity(  ); }, {} }
			},
			// copy constructor
			{
				{ type<mud::Entity>(), [](Ref ref, Ref other) { new(&val<mud::Entity>(ref)) mud::Entity(val<mud::Entity>(other)); } }
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
		meta_class<mud::Entity>();
	}
	// mud::Prototype
	{
		static Meta meta = { type<mud::Prototype>(), &namspc({ "mud" }), "Prototype", sizeof(mud::Prototype), TypeClass::Object };
		static Class cls = { type<mud::Prototype>(),
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
		meta_class<mud::Prototype>();
	}
		m.m_types.push_back(&type<mud::Complex>());
		m.m_types.push_back(&type<mud::Entity>());
		m.m_types.push_back(&type<mud::Prototype>());
	}
}

namespace mud
{
	mud_ecs::mud_ecs()
		: Module("mud::ecs", { &mud_infra::m(), &mud_type::m(), &mud_refl::m() })
	{
		// setup reflection meta data
		mud_ecs_meta(*this);
	}
}

#ifdef MUD_ECS_MODULE
extern "C"
Module& getModule()
{
		return mud_ecs::m();
}
#endif
