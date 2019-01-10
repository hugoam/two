#pragma once

#include <type/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_TYPE_EXPORT Type& type<bool>();
    export_ template <> MUD_TYPE_EXPORT Type& type<char>();
    export_ template <> MUD_TYPE_EXPORT Type& type<const char*>();
    export_ template <> MUD_TYPE_EXPORT Type& type<double>();
    export_ template <> MUD_TYPE_EXPORT Type& type<float>();
    export_ template <> MUD_TYPE_EXPORT Type& type<int>();
    export_ template <> MUD_TYPE_EXPORT Type& type<long>();
    export_ template <> MUD_TYPE_EXPORT Type& type<long long>();
    export_ template <> MUD_TYPE_EXPORT Type& type<short>();
    export_ template <> MUD_TYPE_EXPORT Type& type<std::string>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned char>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned int>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned long>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned long long>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned short>();
    export_ template <> MUD_TYPE_EXPORT Type& type<void>();
    
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Index>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Indexer>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Ref>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Var>();
    
    export_ template struct MUD_TYPE_EXPORT Typed<std::vector<mud::Index*>>;
    export_ template struct MUD_TYPE_EXPORT Typed<std::vector<mud::Indexer*>>;
    export_ template struct MUD_TYPE_EXPORT Typed<std::vector<mud::Ref*>>;
    export_ template struct MUD_TYPE_EXPORT Typed<std::vector<mud::Var*>>;
}
