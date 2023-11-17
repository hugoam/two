#include <two/infra.h>

module;
module two.ecs.meta;

using namespace two;

void two_Entity__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Entity(  ); }
void two_Entity__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Entity((*static_cast<two::Entity*>(other))); }
void two_Entt__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Entt(  ); }
void two_Entt__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Entt((*static_cast<two::Entt*>(other))); }
void two_Complex__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Complex( *static_cast<uint32_t*>(args[0]), *static_cast<two::Type*>(args[1]) ); }
void two_Complex__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Complex( *static_cast<uint32_t*>(args[0]), *static_cast<two::Type*>(args[1]), *static_cast<stl::span<two::Ref>*>(args[2]) ); }
void* two_Complex__get_type(void* object) { return &(*static_cast<two::Complex*>(object)).m_type; }
void* two_Complex__get_prototype(void* object) { return &(*static_cast<two::Complex*>(object)).m_prototype; }
void two_Complex_setup(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Complex*>(object)).setup(*static_cast<stl::span<two::Ref>*>(args[0])); }
void two_Complex_add_part(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Complex*>(object)).add_part(*static_cast<two::Ref*>(args[0])); }
void two_Complex_has_part(void* object, span<void*> args, void*& result) { (*static_cast<bool*>(result)) = (*static_cast<two::Complex*>(object)).has_part(*static_cast<two::Type*>(args[0])); }
void two_Complex_part(void* object, span<void*> args, void*& result) { (*static_cast<two::Ref*>(result)) = (*static_cast<two::Complex*>(object)).part(*static_cast<two::Type*>(args[0])); }
void two_Complex_try_part(void* object, span<void*> args, void*& result) { (*static_cast<two::Ref*>(result)) = (*static_cast<two::Complex*>(object)).try_part(*static_cast<two::Type*>(args[0])); }

namespace two
{
	void two_ecs_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::Entity
	{
		Type& t = type<two::Entity>();
		static Meta meta = { t, &namspc({ "two" }), "Entity", sizeof(two::Entity), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Entity__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Entity__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Entt
	{
		Type& t = type<two::Entt>();
		static Meta meta = { t, &namspc({ "two" }), "Entt", sizeof(two::Entt), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Entt__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Entt__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::OEntt
	{
		Type& t = type<two::OEntt>();
		static Meta meta = { t, &namspc({ "two" }), "OEntt", sizeof(two::OEntt), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Entt>() };
		static size_t bases_offsets[] = { base_offset<two::OEntt, two::Entt>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Complex
	{
		Type& t = type<two::Complex>();
		static Meta meta = { t, &namspc({ "two" }), "Complex", sizeof(two::Complex), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Complex__construct_0, { { "id", type<uint32_t>(),  }, { "type", type<two::Type>(),  } } },
			{ t, two_Complex__construct_1, { { "id", type<uint32_t>(),  }, { "type", type<two::Type>(),  }, { "parts", type<stl::span<two::Ref>>(),  } } }
		};
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Complex, m_id), type<uint32_t>(), "id", nullptr, Member::Value, nullptr },
			{ t, SIZE_MAX, type<two::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Complex__get_type },
			{ t, SIZE_MAX, type<two::Prototype>(), "prototype", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Complex__get_prototype },
			{ t, offsetof(two::Complex, m_parts), type<stl::vector<two::Ref>>(), "parts", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "setup", Address(), two_Complex_setup, { { "parts", type<stl::span<two::Ref>>(),  } }, g_qvoid },
			{ t, "add_part", Address(), two_Complex_add_part, { { "part", type<two::Ref>(), Param::Nullable } }, g_qvoid },
			{ t, "has_part", Address(), two_Complex_has_part, { { "type", type<two::Type>(),  } }, { &type<bool>(), QualType::None } },
			{ t, "part", Address(), two_Complex_part, { { "type", type<two::Type>(),  } }, { &type<two::Ref>(), QualType::None } },
			{ t, "try_part", Address(), two_Complex_try_part, { { "type", type<two::Type>(),  } }, { &type<two::Ref>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, members, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<two::Entity>());
		m.m_types.push_back(&type<two::Entt>());
		m.m_types.push_back(&type<two::OEntt>());
		m.m_types.push_back(&type<two::Complex>());
	}
}

namespace two
{
	two_ecs::two_ecs()
		: Module("two::ecs", { &two_infra::m(), &two_pool::m(), &two_type::m() })
	{
		// setup reflection meta data
		two_ecs_meta(*this);
	}
}

#ifdef TWO_ECS_MODULE
extern "C"
Module& getModule()
{
	return two_ecs::m();
}
#endif
