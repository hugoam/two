#pragma once

#include <wfc-gfx/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_WFC_GFX_EXPORT Type& type<two::TileModel>();
    export_ template <> TWO_WFC_GFX_EXPORT Type& type<two::WfcBlock>();
}
