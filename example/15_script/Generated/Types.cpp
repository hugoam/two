

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module .ex_15_script;
#else
#include <15_script/Types.h>
#include <15_script/Refl/Module.h>
#include <proto/Proto.h>
#endif

namespace mud
{
    // Exported types
    
    template <> _15_SCRIPT_EXPORT Type& type<GameObject>() { static Type ty("GameObject"); return ty; }
}
