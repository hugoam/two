#pragma once

#include <uio/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

namespace two
{
    // Exported types
    export_ template <> TWO_UIO_EXPORT Type& type<two::EditNestMode>();
    export_ template <> TWO_UIO_EXPORT Type& type<two::EditorHint>();
    
    
    export_ template <> TWO_UIO_EXPORT Type& type<two::ScriptEditor>();
}
