#include <two/infra.h>

module;
module two.pool;

namespace two
{
    // Exported types
    
    
    template <> TWO_POOL_EXPORT Type& type<two::Pool>() { static Type ty("Pool", sizeof(two::Pool)); return ty; }
    template <> TWO_POOL_EXPORT Type& type<two::HandlePool>() { static Type ty("HandlePool", sizeof(two::HandlePool)); return ty; }
}

module;
module two.pool;

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
#ifndef USE_STL
module two.uio;

namespace stl
{
	using namespace two;
	template class TWO_POOL_EXPORT vector<unique<Pool>>;
}
#endif

module;
module two.pool;

namespace two
{}
