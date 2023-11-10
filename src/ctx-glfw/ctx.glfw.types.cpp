#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ctx.glfw;
#else
#include <ctx-glfw/Types.h>
#include <ctx-glfw/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    
    template <> TWO_CTX_GLFW_EXPORT Type& type<two::GlfwContext>() { static Type ty("GlfwContext", type<two::Context>()); return ty; }
}
