#pragma once

#include <wfc-gfx/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_WFC_GFX_EXPORT Type& type<two::TileModel>();
    template <> TWO_WFC_GFX_EXPORT Type& type<two::WfcBlock>();
}
