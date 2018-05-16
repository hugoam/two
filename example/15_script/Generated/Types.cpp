

#include <15_script/Generated/Types.h>
#include <15_script/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    
    template <> _15_SCRIPT_EXPORT Type& type<GameObject>() { static Type ty("GameObject"); return ty; }
}
