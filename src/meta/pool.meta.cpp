#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.pool;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/pool.meta.h>
#include <meta/pool.conv.h>
#endif

#include <pool/Api.h>

using namespace two;


namespace two
{
	void two_pool_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::Pool
	{
		Type& t = type<two::Pool>();
		static Meta meta = { t, &namspc({ "two" }), "Pool", sizeof(two::Pool), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::HandlePool
	{
		Type& t = type<two::HandlePool>();
		static Meta meta = { t, &namspc({ "two" }), "HandlePool", sizeof(two::HandlePool), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::Pool>());
		m.m_types.push_back(&type<two::HandlePool>());
	}
}

namespace two
{
	two_pool::two_pool()
		: Module("two::pool", { &two_infra::m(), &two_type::m() })
	{
		// setup reflection meta data
		two_pool_meta(*this);
	}
}

#ifdef TWO_POOL_MODULE
extern "C"
Module& getModule()
{
	return two_pool::m();
}
#endif
