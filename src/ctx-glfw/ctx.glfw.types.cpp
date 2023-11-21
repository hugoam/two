module;
#include <infra/Cpp20.h>
module two.ctx.glfw;

namespace two
{
    // Exported types
    
    template <> TWO_CTX_GLFW_EXPORT Type& type<two::GlfwContext>() { static Type ty("GlfwContext", type<two::Context>()); return ty; }
}
