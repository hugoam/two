#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <wfc-gfx/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <tree/Types.h>
#include <type/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <wfc/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#include <uio/Types.h>
#include <gfx/Types.h>
#include <gfx-ui/Types.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_WFC_GFX_EXPORT Type& type<two::TileModel>();
    export_ template <> TWO_WFC_GFX_EXPORT Type& type<two::WfcBlock>();
}
