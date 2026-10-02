#pragma once

#include <gfx-obj/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterOBJ>();
    template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterPLY>();
}
