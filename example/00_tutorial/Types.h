#pragma once

#include <00_tutorial/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>();
    
    export_ template <> _00_TUTORIAL_EXPORT Type& type<MyObject>();
}
