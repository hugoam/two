#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.pool;
#else
#include <pool/Types.h>
#include <pool/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_POOL_EXPORT Type& type<two::Pool>() { static Type ty("Pool", sizeof(two::Pool)); return ty; }
    template <> TWO_POOL_EXPORT Type& type<two::HandlePool>() { static Type ty("HandlePool", sizeof(two::HandlePool)); return ty; }
}
