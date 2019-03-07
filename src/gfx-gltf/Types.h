#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <gfx-gltf/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <refl/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <gfx/Types.h>
#include <gltf/Types.h>
#endif


namespace mud
{
    // Exported types
    
    
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<mud::ImporterGltf>();
}
