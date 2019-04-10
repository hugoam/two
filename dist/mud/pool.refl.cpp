#include <mud/pool.h>
#include <mud/pool.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.pool;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace mud;


namespace mud
{
	void mud_pool_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// mud::HandlePool
	{
		Type& t = type<mud::HandlePool>();
		static Meta meta = { t, &namspc({ "mud" }), "HandlePool", sizeof(mud::HandlePool), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Pool
	{
		Type& t = type<mud::Pool>();
		static Meta meta = { t, &namspc({ "mud" }), "Pool", sizeof(mud::Pool), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::HandlePool>());
		m.m_types.push_back(&type<mud::Pool>());
	}
}

namespace mud
{
	mud_pool::mud_pool()
		: Module("mud::pool", { &mud_infra::m(), &mud_type::m() })
	{
		// setup reflection meta data
		mud_pool_meta(*this);
	}
}

#ifdef MUD_POOL_MODULE
extern "C"
Module& getModule()
{
	return mud_pool::m();
}
#endif
