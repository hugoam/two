#pragma once

#include <uio/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <tree/Types.h>
#include <obj/Types.h>
#include <ecs/Types.h>
#include <pool/Types.h>
#include <refl/Types.h>
#include <math/Types.h>
#include <lang/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_UIO_EXPORT Type& type<mud::EditNestMode>();
    export_ template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>();
    
    export_ template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>();
    
	export_ template struct MUD_UIO_EXPORT Typed<std::vector<mud::ScriptEditor*>>;
}
