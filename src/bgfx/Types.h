#pragma once

#include <bgfx/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_BGFX_EXPORT Type& type<two::BgfxSystem>();
}
