#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.type;
#else
#include <type/Types.h>
#include <type/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_TYPE_EXPORT Type& type<bool>() { static Type ty("bool"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<char>() { static Type ty("char"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<const char*>() { static Type ty("const char*"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<double>() { static Type ty("double"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<float>() { static Type ty("float"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<int>() { static Type ty("int"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<long>() { static Type ty("long"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<long long>() { static Type ty("long long"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<short>() { static Type ty("short"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<std::string>() { static Type ty("std::string"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned char>() { static Type ty("unsigned char"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned int>() { static Type ty("unsigned int"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned long>() { static Type ty("unsigned long"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned long long>() { static Type ty("unsigned long long"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned short>() { static Type ty("unsigned short"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<void>() { static Type ty("void"); return ty; }
    
    template <> MUD_TYPE_EXPORT Type& type<mud::Index>() { static Type ty("Index"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Indexer>() { static Type ty("Indexer"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Ref>() { static Type ty("Ref"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Var>() { static Type ty("Var"); return ty; }
}
