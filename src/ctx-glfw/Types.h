#pragma once

#include <ctx-glfw/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Vector.h>
#endif

#ifndef MUD_MODULES
#include <math/Types.h>
#include <ctx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_CTX_GLFW_EXPORT Type& type<mud::GlfwContext>();
    
	export_ template struct MUD_CTX_GLFW_EXPORT Typed<std::vector<mud::GlfwContext*>>;
}
