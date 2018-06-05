

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module .ex_15_script;
#else
#include <15_script/Generated/Types.h>
#include <15_script/Generated/Module.h>
#include <obj/Proto.h>
#endif

namespace mud
{
    // Exported types
    
    template <> _15_SCRIPT_EXPORT Type& type<GameObject>() { static Type ty("GameObject"); return ty; }
}
