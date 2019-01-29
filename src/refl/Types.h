#pragma once

#include <refl/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <pool/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_REFL_EXPORT Type& type<mud::TypeClass>();
    
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Call>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Callable>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Class>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Convert>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Creator>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Enum>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Member>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Meta>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Module>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Namespace>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Operator>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Param>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::QualType>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Signature>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Static>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::System>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Constructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::CopyConstructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Destructor>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Function>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Injector>();
    export_ template <> MUD_REFL_EXPORT Type& type<mud::Method>();
    
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Call*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Callable*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Class*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Convert*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Creator*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Enum*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Member*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Meta*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Module*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Namespace*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Operator*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Param*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::QualType*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Signature*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Static*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::System*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Constructor*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::CopyConstructor*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Destructor*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Function*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Injector*>>();
    export_ template <> MUD_REFL_EXPORT Type& type<vector<mud::Method*>>();
}
