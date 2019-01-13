#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.core;
#else
#include <core/Types.h>
#include <core/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_CORE_EXPORT Type& type<mud::Shell>() { static Type ty("Shell", sizeof(mud::Shell)); return ty; }
    template <> MUD_CORE_EXPORT Type& type<mud::ShellContext>() { static Type ty("ShellContext", sizeof(mud::ShellContext)); return ty; }
}
