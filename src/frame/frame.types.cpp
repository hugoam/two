#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.frame;
#else
#include <frame/Types.h>
#include <frame/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    
    template <> MUD_FRAME_EXPORT Type& type<mud::ShellContext>() { static Type ty("ShellContext", sizeof(mud::ShellContext)); return ty; }
    template <> MUD_FRAME_EXPORT Type& type<mud::ShellWindow>() { static Type ty("ShellWindow", type<mud::GfxWindow>(), sizeof(mud::ShellWindow)); return ty; }
    template <> MUD_FRAME_EXPORT Type& type<mud::Shell>() { static Type ty("Shell", sizeof(mud::Shell)); return ty; }
}
