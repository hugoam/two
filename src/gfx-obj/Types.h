#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <gfx-obj/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <gfx/Types.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterOBJ>();
    export_ template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterPLY>();
}
