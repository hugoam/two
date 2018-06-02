#pragma once

#include <15_script/Generated/Forward.h>

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <ui/Generated/Types.h>
#include <uio/Generated/Types.h>
#include <gfx/Generated/Types.h>
#include <edit/Generated/Types.h>
#include <gen/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> _15_SCRIPT_EXPORT Type& type<GameObject>();
}
