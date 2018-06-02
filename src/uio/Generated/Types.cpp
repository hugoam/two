

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

#include <uio/Generated/Types.h>
#include <uio/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>() { static Type ty("mud::EditorHint"); return ty; }
    
    template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>() { static Type ty("ScriptEditor"); return ty; }
}
