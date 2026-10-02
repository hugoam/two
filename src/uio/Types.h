#pragma once

#include <uio/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_UIO_EXPORT Type& type<two::EditNestMode>();
    template <> TWO_UIO_EXPORT Type& type<two::EditorHint>();
    
    
    template <> TWO_UIO_EXPORT Type& type<two::ScriptEditor>();
}
