#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <refl/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <pool/Types.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_REFL_EXPORT Type& type<two::TypeClass>();
    
    export_ template <> TWO_REFL_EXPORT Type& type<stl::span<two::Type*>>();
    export_ template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Var>>();
    export_ template <> TWO_REFL_EXPORT Type& type<stl::vector<void*>>();
    export_ template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Module*>>();
    export_ template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Type*>>();
    export_ template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Alias*>>();
    export_ template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Function*>>();
    
    export_ template <> TWO_REFL_EXPORT Type& type<two::QualType>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Param>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Signature>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Callable>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Function>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Operator>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Method>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Constructor>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::CopyConstructor>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Destructor>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Meta>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Convert>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Static>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Member>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Class>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Enum>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Call>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Injector>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Creator>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Namespace>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Alias>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::Module>();
    export_ template <> TWO_REFL_EXPORT Type& type<two::System>();
}
