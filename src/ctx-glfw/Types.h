#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <ctx-glfw/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

namespace two
{
    // Exported types
    
    template <> TWO_CTX_GLFW_EXPORT Type& type<two::GlfwContext>();
}
