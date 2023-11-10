#pragma once

#ifndef TWO_MODULES
#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#endif
#include <gfx-gltf/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <refl/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <gfx/Types.h>
#include <gltf/Types.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_GFX_GLTF_EXPORT Type& type<two::ImporterGltf>();
}
