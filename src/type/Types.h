#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <type/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
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
    export_ template <> MUD_TYPE_EXPORT Type& type<long double>();
    export_ template <> MUD_TYPE_EXPORT Type& type<long long>();
    export_ template <> MUD_TYPE_EXPORT Type& type<short>();
    export_ template <> MUD_TYPE_EXPORT Type& type<signed char>();
    export_ template <> MUD_TYPE_EXPORT Type& type<stl::string>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned char>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned int>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned long>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned long long>();
    export_ template <> MUD_TYPE_EXPORT Type& type<unsigned short>();
    export_ template <> MUD_TYPE_EXPORT Type& type<void>();
    export_ template <> MUD_TYPE_EXPORT Type& type<void*>();
    
    export_ template <> MUD_TYPE_EXPORT Type& type<stl::vector<mud::Ref>>();
    export_ template <> MUD_TYPE_EXPORT Type& type<stl::vector<stl::string>>();
    
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Index>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Indexer>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Prototype>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Ref>();
    export_ template <> MUD_TYPE_EXPORT Type& type<mud::Var>();
}
