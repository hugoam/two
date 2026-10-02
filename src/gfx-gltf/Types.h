#pragma once

#include <gfx-gltf/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_GFX_GLTF_EXPORT Type& type<two::ImporterGltf>();
}
