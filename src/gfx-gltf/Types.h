#pragma once

#include <gfx-gltf/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_GFX_GLTF_EXPORT Type& type<two::ImporterGltf>();
}
