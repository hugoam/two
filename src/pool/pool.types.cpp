#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.pool;
#else
#include <pool/Types.h>
#include <pool/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    
    template <> MUD_POOL_EXPORT Type& type<mud::Pool>() { static Type ty("Pool", sizeof(mud::Pool)); return ty; }
    template <> MUD_POOL_EXPORT Type& type<mud::HandlePool>() { static Type ty("HandlePool", sizeof(mud::HandlePool)); return ty; }
}
