#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <refl/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <pool/Types.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_REFL_EXPORT Type& type<mud::TypeClass>();
    
    export_ template <> MUD_REFL_EXPORT Type& type<stl::span<mud::Type*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Var>>();
    export_ template <> MUD_REFL_EXPORT Type& type<stl::vector<void*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Module*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Type*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Alias*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Function*>>();
    
    export_ template <> MUD_REFL_EXPORT Type& type<mud::QualType>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Param>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Signature>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Callable>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Function>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Operator>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Method>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Constructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::CopyConstructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Destructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Meta>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Convert>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Static>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Member>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Class>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Enum>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Call>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Injector>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Creator>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Namespace>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Alias>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Module>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::System>();
}
