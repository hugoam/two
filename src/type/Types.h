#pragma once

#include <type/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

namespace two
{
    // Exported types
    template <> TWO_TYPE_EXPORT Type& type<void*>();
    template <> TWO_TYPE_EXPORT Type& type<bool>();
    template <> TWO_TYPE_EXPORT Type& type<char>();
    template <> TWO_TYPE_EXPORT Type& type<schar>();
    template <> TWO_TYPE_EXPORT Type& type<short>();
    template <> TWO_TYPE_EXPORT Type& type<int>();
    template <> TWO_TYPE_EXPORT Type& type<long>();
    template <> TWO_TYPE_EXPORT Type& type<uchar>();
    template <> TWO_TYPE_EXPORT Type& type<ushort>();
    template <> TWO_TYPE_EXPORT Type& type<uint>();
    template <> TWO_TYPE_EXPORT Type& type<ulong>();
    template <> TWO_TYPE_EXPORT Type& type<ullong>();
    template <> TWO_TYPE_EXPORT Type& type<llong>();
    template <> TWO_TYPE_EXPORT Type& type<ldouble>();
    template <> TWO_TYPE_EXPORT Type& type<float>();
    template <> TWO_TYPE_EXPORT Type& type<double>();
    template <> TWO_TYPE_EXPORT Type& type<const char*>();
    template <> TWO_TYPE_EXPORT Type& type<stl::string>();
    template <> TWO_TYPE_EXPORT Type& type<void>();
    
    template <> TWO_TYPE_EXPORT Type& type<stl::vector<stl::string>>();
    template <> TWO_TYPE_EXPORT Type& type<stl::vector<two::Ref>>();
    
    template <> TWO_TYPE_EXPORT Type& type<two::Ref>();
    template <> TWO_TYPE_EXPORT Type& type<two::Var>();
    template <> TWO_TYPE_EXPORT Type& type<two::Indexer>();
    template <> TWO_TYPE_EXPORT Type& type<two::Index>();
    template <> TWO_TYPE_EXPORT Type& type<two::Prototype>();
}
