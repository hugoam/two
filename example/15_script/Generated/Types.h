#pragma once

#include <15_script/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <obj/Forward.h>
#include <math/Forward.h>
#include <ui/Forward.h>
#include <uio/Forward.h>
#include <gfx/Forward.h>
#include <edit/Forward.h>
#include <procgen/Forward.h>
#include <procgen-gfx/Forward.h>
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
