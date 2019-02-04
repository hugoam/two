#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx-glfw;
#else
#include <ctx-glfw/Types.h>
#include <ctx-glfw/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_CTX_GLFW_EXPORT Type& type<mud::GlfwContext>() { static Type ty("GlfwContext", type<mud::Context>()); return ty; }
}
