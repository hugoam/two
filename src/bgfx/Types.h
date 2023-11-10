#pragma once

#ifndef TWO_MODULES
#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#endif
#include <bgfx/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <ctx/Types.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_BGFX_EXPORT Type& type<two::BgfxSystem>();
}
