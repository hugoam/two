#pragma once

#include <frame/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_FRAME_EXPORT Type& type<two::ShellContext>();
    template <> TWO_FRAME_EXPORT Type& type<two::ShellWindow>();
    template <> TWO_FRAME_EXPORT Type& type<two::Shell>();
}
