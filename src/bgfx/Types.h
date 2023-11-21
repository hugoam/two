#pragma once

#include <bgfx/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_BGFX_EXPORT Type& type<two::BgfxSystem>();
}
