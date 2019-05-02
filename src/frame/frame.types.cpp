#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.frame;
#else
#include <frame/Types.h>
#include <frame/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_FRAME_EXPORT Type& type<two::ShellContext>() { static Type ty("ShellContext", sizeof(two::ShellContext)); return ty; }
    template <> TWO_FRAME_EXPORT Type& type<two::ShellWindow>() { static Type ty("ShellWindow", type<two::GfxWindow>(), sizeof(two::ShellWindow)); return ty; }
    template <> TWO_FRAME_EXPORT Type& type<two::Shell>() { static Type ty("Shell", sizeof(two::Shell)); return ty; }
}
