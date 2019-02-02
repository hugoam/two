#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ecs;
#else
#include <stl/new.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/ecs/Module.h>
#include <meta/ecs/Convert.h>
#endif

#include <ecs/Api.h>

using namespace mud;

void mud_Complex__construct_0(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Complex*>(ref))) mud::Complex( *static_cast<uint32_t*>(args[0]), *static_cast<mud::Type*>(args[1]) ); }
void mud_Complex__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Complex*>(ref))) mud::Complex( *static_cast<uint32_t*>(args[0]), *static_cast<mud::Type*>(args[1]), *static_cast<vector<mud::Ref>*>(args[2]) ); }
void* mud_Complex__get_type(void* object) { return &(*static_cast<mud::Complex*>(object)).m_type; }
void* mud_Complex__get_prototype(void* object) { return &(*static_cast<mud::Complex*>(object)).m_prototype; }
void mud_Complex_setup(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Complex*>(object)).setup(*static_cast<vector<mud::Ref>*>(args[0])); }
void mud_Complex_add_part(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::Complex*>(object)).add_part(*static_cast<mud::Ref*>(args[0])); }
void mud_Complex_has_part(void* object, array<void*> args, void*& result) { (*static_cast<bool*>(result)) = (*static_cast<mud::Complex*>(object)).has_part(*static_cast<mud::Type*>(args[0])); }
void mud_Complex_part(void* object, array<void*> args, void*& result) { (*static_cast<mud::Ref*>(result)) = (*static_cast<mud::Complex*>(object)).part(*static_cast<mud::Type*>(args[0])); }
void mud_Complex_try_part(void* object, array<void*> args, void*& result) { (*static_cast<mud::Ref*>(result)) = (*static_cast<mud::Complex*>(object)).try_part(*static_cast<mud::Type*>(args[0])); }
void mud_Entity__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Entity*>(ref))) mud::Entity(  ); }
void mud_Entity__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Entity*>(ref))) mud::Entity((*static_cast<mud::Entity*>(other))); }

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
		Type& t = type<mud::Complex>();
		static Meta meta = { t, &namspc({ "mud" }), "Complex", sizeof(mud::Complex), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Complex__construct_0, { { "id", type<uint32_t>(),  }, { "type", type<mud::Type>(),  } } },
			{ t, mud_Complex__construct_1, { { "id", type<uint32_t>(),  }, { "type", type<mud::Type>(),  }, { "parts", type<vector<mud::Ref>>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Complex, m_id), type<uint32_t>(), "id", nullptr, Member::Value, nullptr },
			{ t, SIZE_MAX, type<mud::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Complex__get_type },
			{ t, SIZE_MAX, type<mud::Prototype>(), "prototype", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Complex__get_prototype },
			{ t, offsetof(mud::Complex, m_parts), type<vector<mud::Ref>>(), "parts", nullptr, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "setup", Address(), mud_Complex_setup, { { "parts", type<vector<mud::Ref>>(),  } }, g_qvoid },
			{ t, "add_part", Address(), mud_Complex_add_part, { { "part", type<mud::Ref>(), Param::Nullable } }, g_qvoid },
			{ t, "has_part", Address(), mud_Complex_has_part, { { "type", type<mud::Type>(),  } }, { &type<bool>(), QualType::None } },
			{ t, "part", Address(), mud_Complex_part, { { "type", type<mud::Type>(),  } }, { &type<mud::Ref>(), QualType::None } },
			{ t, "try_part", Address(), mud_Complex_try_part, { { "type", type<mud::Type>(),  } }, { &type<mud::Ref>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	// mud::Entity
	{
		Type& t = type<mud::Entity>();
		static Meta meta = { t, &namspc({ "mud" }), "Entity", sizeof(mud::Entity), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Entity__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Entity__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Prototype
	{
		Type& t = type<mud::Prototype>();
		static Meta meta = { t, &namspc({ "mud" }), "Prototype", sizeof(mud::Prototype), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
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
