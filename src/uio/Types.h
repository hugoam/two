#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <uio/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <tree/Types.h>
#include <type/Types.h>
#include <ecs/Types.h>
#include <pool/Types.h>
#include <refl/Types.h>
#include <math/Types.h>
#include <lang/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_UIO_EXPORT Type& type<mud::EditNestMode>();
    export_ template <> MUD_UIO_EXPORT Type& type<mud::EditorHint>();
    
    
    export_ template <> MUD_UIO_EXPORT Type& type<mud::ScriptEditor>();
}
