

#include <uio/Generated/Types.h>
#include <uio/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>() { static Type ty("mud::EditorHint"); return ty; }
    
    template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>() { static Type ty("ScriptEditor"); return ty; }
}
