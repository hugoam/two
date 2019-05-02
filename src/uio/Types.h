#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <uio/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
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


namespace two
{
    // Exported types
    export_ template <> TWO_UIO_EXPORT Type& type<two::EditNestMode>();
    export_ template <> TWO_UIO_EXPORT Type& type<two::EditorHint>();
    
    
    export_ template <> TWO_UIO_EXPORT Type& type<two::ScriptEditor>();
}
