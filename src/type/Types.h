#pragma once

#include <type/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

namespace two
{
    // Exported types
    export_ template <> TWO_TYPE_EXPORT Type& type<void*>();
    export_ template <> TWO_TYPE_EXPORT Type& type<bool>();
    export_ template <> TWO_TYPE_EXPORT Type& type<char>();
    export_ template <> TWO_TYPE_EXPORT Type& type<schar>();
    export_ template <> TWO_TYPE_EXPORT Type& type<short>();
    export_ template <> TWO_TYPE_EXPORT Type& type<int>();
    export_ template <> TWO_TYPE_EXPORT Type& type<long>();
    export_ template <> TWO_TYPE_EXPORT Type& type<uchar>();
    export_ template <> TWO_TYPE_EXPORT Type& type<ushort>();
    export_ template <> TWO_TYPE_EXPORT Type& type<uint>();
    export_ template <> TWO_TYPE_EXPORT Type& type<ulong>();
    export_ template <> TWO_TYPE_EXPORT Type& type<ullong>();
    export_ template <> TWO_TYPE_EXPORT Type& type<llong>();
    export_ template <> TWO_TYPE_EXPORT Type& type<ldouble>();
    export_ template <> TWO_TYPE_EXPORT Type& type<float>();
    export_ template <> TWO_TYPE_EXPORT Type& type<double>();
    export_ template <> TWO_TYPE_EXPORT Type& type<const char*>();
    export_ template <> TWO_TYPE_EXPORT Type& type<stl::string>();
    export_ template <> TWO_TYPE_EXPORT Type& type<void>();
    
    export_ template <> TWO_TYPE_EXPORT Type& type<stl::vector<stl::string>>();
    export_ template <> TWO_TYPE_EXPORT Type& type<stl::vector<two::Ref>>();
    
    export_ template <> TWO_TYPE_EXPORT Type& type<two::Ref>();
    export_ template <> TWO_TYPE_EXPORT Type& type<two::Var>();
    export_ template <> TWO_TYPE_EXPORT Type& type<two::Indexer>();
    export_ template <> TWO_TYPE_EXPORT Type& type<two::Index>();
    export_ template <> TWO_TYPE_EXPORT Type& type<two::Prototype>();
}
