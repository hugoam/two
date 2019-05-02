#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <frame/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <gfx/Types.h>
#include <gfx-ui/Types.h>
#endif


namespace two
{
    // Exported types
    
    
    export_ template <> TWO_FRAME_EXPORT Type& type<two::ShellContext>();
    export_ template <> TWO_FRAME_EXPORT Type& type<two::ShellWindow>();
    export_ template <> TWO_FRAME_EXPORT Type& type<two::Shell>();
}
