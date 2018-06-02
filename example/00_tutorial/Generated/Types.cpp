

#ifdef MUD_CPP_20
#include <cassert>
#include <cstdint>
#include <climits>
#include <cfloat>
import std.core;
import std.memory;
import std.threading;
import std.regex;
#endif

#include <00_tutorial/Generated/Types.h>
#include <00_tutorial/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>() { static Type ty("ShapeType"); return ty; }
    
    template <> _00_TUTORIAL_EXPORT Type& type<MyObject>() { static Type ty("MyObject"); return ty; }
}
