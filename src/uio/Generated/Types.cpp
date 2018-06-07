

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <uio/Generated/Types.h>
#include <uio/Generated/Module.h>
#include <obj/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>() { static Type ty("mud::EditorHint"); return ty; }
    
    template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>() { static Type ty("ScriptEditor"); return ty; }
}
