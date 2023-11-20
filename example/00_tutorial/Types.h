#pragma once

#include <00_tutorial/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>();
    
    export_ template <> _00_TUTORIAL_EXPORT Type& type<MyObject>();
    
	export_ template struct _00_TUTORIAL_EXPORT Typed<std::vector<MyObject*>>;
}
