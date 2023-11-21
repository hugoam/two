module;
#include <infra/Cpp20.h>
module two.pool;

namespace two
{
    // Exported types
    
    
    template <> TWO_POOL_EXPORT Type& type<two::Pool>() { static Type ty("Pool", sizeof(two::Pool)); return ty; }
    template <> TWO_POOL_EXPORT Type& type<two::HandlePool>() { static Type ty("HandlePool", sizeof(two::HandlePool)); return ty; }
}
