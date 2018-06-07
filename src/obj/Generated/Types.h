#pragma once

#include <obj/Generated/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Proto.h>
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_OBJ_EXPORT Type& type<bool>();
    export_ template <> MUD_OBJ_EXPORT Type& type<char>();
    export_ template <> MUD_OBJ_EXPORT Type& type<cstring>();
    export_ template <> MUD_OBJ_EXPORT Type& type<double>();
    export_ template <> MUD_OBJ_EXPORT Type& type<float>();
    export_ template <> MUD_OBJ_EXPORT Type& type<int>();
    export_ template <> MUD_OBJ_EXPORT Type& type<long>();
    export_ template <> MUD_OBJ_EXPORT Type& type<long long>();
    export_ template <> MUD_OBJ_EXPORT Type& type<short>();
    export_ template <> MUD_OBJ_EXPORT Type& type<std::string>();
    export_ template <> MUD_OBJ_EXPORT Type& type<unsigned char>();
    export_ template <> MUD_OBJ_EXPORT Type& type<unsigned int>();
    export_ template <> MUD_OBJ_EXPORT Type& type<unsigned long>();
    export_ template <> MUD_OBJ_EXPORT Type& type<unsigned long long>();
    export_ template <> MUD_OBJ_EXPORT Type& type<unsigned short>();
    export_ template <> MUD_OBJ_EXPORT Type& type<void>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::ConstructorIndex>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::TypeClass>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::TypeKind>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::VarMode>();
    export_ template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Function*>>();
    export_ template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Module*>>();
    export_ template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Prototype*>>();
    export_ template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Ref>>();
    export_ template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Type*>>();
    export_ template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Var>>();
    
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Call>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Callable>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Class>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Complex>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Construct>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Convert>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Creator>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Enum>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Index>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Indexer>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Injector>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Member>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Meta>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Module>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Namespace>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::None>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Param>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Pool>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Ref>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Signature>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Static>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::System>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Time>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::TimeSpan>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Var>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::array<float>>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::array<mud::cstring>>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Constructor>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::CopyConstructor>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Destructor>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Function>();
    export_ template <> MUD_OBJ_EXPORT Type& type<mud::Method>();
}
