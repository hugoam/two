

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

#include <15_script/Generated/Types.h>
#include <15_script/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    
    template <> _15_SCRIPT_EXPORT Type& type<GameObject>() { static Type ty("GameObject"); return ty; }
}
