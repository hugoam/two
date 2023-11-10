#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.uio;
#else
#include <uio/Types.h>
#include <uio/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    template <> TWO_UIO_EXPORT Type& type<two::EditNestMode>() { static Type ty("EditNestMode", sizeof(two::EditNestMode)); return ty; }
    template <> TWO_UIO_EXPORT Type& type<two::EditorHint>() { static Type ty("EditorHint", sizeof(two::EditorHint)); return ty; }
    
    
    template <> TWO_UIO_EXPORT Type& type<two::ScriptEditor>() { static Type ty("ScriptEditor", sizeof(two::ScriptEditor)); return ty; }
}
