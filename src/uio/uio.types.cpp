#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <uio/Types.h>
#include <uio/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_UIO_EXPORT Type& type<mud::EditNestMode>() { static Type ty("mud::EditNestMode", sizeof(mud::EditNestMode)); return ty; }
    template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>() { static Type ty("mud::EditorHint", sizeof(mud::EditorHint)); return ty; }
    
    template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>() { static Type ty("ScriptEditor", sizeof(mud::ScriptEditor)); return ty; }
}
