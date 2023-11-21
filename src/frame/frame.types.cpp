module;
#include <infra/Cpp20.h>
module two.frame;

namespace two
{
    // Exported types
    
    
    template <> TWO_FRAME_EXPORT Type& type<two::ShellContext>() { static Type ty("ShellContext", sizeof(two::ShellContext)); return ty; }
    template <> TWO_FRAME_EXPORT Type& type<two::ShellWindow>() { static Type ty("ShellWindow", type<two::GfxWindow>(), sizeof(two::ShellWindow)); return ty; }
    template <> TWO_FRAME_EXPORT Type& type<two::Shell>() { static Type ty("Shell", sizeof(two::Shell)); return ty; }
}
