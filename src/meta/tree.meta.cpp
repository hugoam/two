module;
#include <infra/Cpp20.h>
module two.tree.meta;

using namespace two;

void two_NodeKey__default_construct(void* ref) { new(stl::placeholder(), ref) two::NodeKey(); }
void two_NodeKey__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::NodeKey((*static_cast<two::NodeKey*>(other))); }

namespace two
{
	void two_tree_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::NodeKey
	{
		Type& t = type<two::NodeKey>();
		static Meta meta = { t, &namspc({ "two" }), "NodeKey", sizeof(two::NodeKey), TypeClass::Struct };
		// bases
		// defaults
		static uint64_t value_default = 0;
		// default constructor
		static DefaultConstructor default_constructor[] = {
			{ t, two_NodeKey__default_construct }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_NodeKey__copy_construct }
		};
		// constructors
		// members
		static Member members[] = {
			{ t, offsetof(two::NodeKey, m_value), type<uint64_t>(), "value", &value_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, default_constructor, copy_constructor, {}, members, {}, {}, };
		meta.m_empty_var = var(two::NodeKey());
	}
	
	
		m.m_types.push_back(&type<two::NodeKey>());
	}
}

namespace two
{
	two_tree::two_tree()
		: Module("two::tree", { &two_infra::m(), &two_type::m(), &two_pool::m() })
	{
		// setup reflection meta data
		two_tree_meta(*this);
	}
}

#ifdef TWO_TREE_MODULE
extern "C"
Module& getModule()
{
	return two_tree::m();
}
#endif
