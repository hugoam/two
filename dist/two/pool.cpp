#include <two/pool.h>
#include <two/infra.h>
#include <two/type.h>



#ifdef TWO_MODULES
module two.pool;
#else
//#include <refl/Class.h>
#endif

namespace two
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


#ifdef TWO_MODULES
module two.pool;
#else
#endif

namespace two
{}
#ifndef USE_STL
#ifdef TWO_MODULES
module two.uio;
#else
#include <stl/vector.hpp>
#endif

namespace stl
{
	using namespace two;
	template class TWO_POOL_EXPORT vector<unique<Pool>>;
}
#endif

#ifdef TWO_MODULES
module two.pool;
#else
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_POOL_EXPORT Type& type<two::Pool>() { static Type ty("Pool", sizeof(two::Pool)); return ty; }
    template <> TWO_POOL_EXPORT Type& type<two::HandlePool>() { static Type ty("HandlePool", sizeof(two::HandlePool)); return ty; }
}
