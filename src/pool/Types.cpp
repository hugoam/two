

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.pool;
#else
#include <pool/Types.h>
#include <pool/Api.h>
#include <obj/Vector.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_POOL_EXPORT Type& type<mud::Pool>() { static Type ty("Pool"); return ty; }
}
