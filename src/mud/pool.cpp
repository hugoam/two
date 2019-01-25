#include <mud/pool.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.pool;
#else
//#include <refl/Class.h>
#endif

namespace mud
{
	vector<unique<Pool>> g_pools = vector<unique<Pool>>(c_max_types);

	ObjectPool::ObjectPool()
		: m_pools(c_max_types)
	{}

	void ObjectPool::clear()
	{
		for(auto& pool : m_pools)
			if(pool)
				pool->clear();
	}
}


#ifdef MUD_MODULES
module mud.pool;
#else
#endif

namespace mud
{}

#ifdef MUD_MODULES
module mud.pool;
#else
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_POOL_EXPORT Type& type<mud::HandlePool>() { static Type ty("HandlePool", sizeof(mud::HandlePool)); return ty; }
    template <> MUD_POOL_EXPORT Type& type<mud::Pool>() { static Type ty("Pool", sizeof(mud::Pool)); return ty; }
}
