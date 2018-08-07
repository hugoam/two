#pragma once

#include <ctx/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <math/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_CTX_EXPORT Type& type<mud::DeviceMask>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::DeviceType>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::EventType>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::InputMod>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Key>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::MouseButtonCode>();
    
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Context>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::RenderSystem>();
    
	export_ template struct MUD_CTX_EXPORT Typed<std::vector<mud::Context*>>;
	export_ template struct MUD_CTX_EXPORT Typed<std::vector<mud::RenderSystem*>>;
}
