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
    template <> MUD_TYPE_EXPORT Type& type<bool>() { static Type ty("bool", sizeof(bool)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<char>() { static Type ty("char", sizeof(char)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<const char*>() { static Type ty("const char*", sizeof(const char*)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<double>() { static Type ty("double", sizeof(double)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<float>() { static Type ty("float", sizeof(float)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<int>() { static Type ty("int", sizeof(int)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<ldouble>() { static Type ty("ldouble", sizeof(ldouble)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<llong>() { static Type ty("llong", sizeof(llong)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<long>() { static Type ty("long", sizeof(long)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<schar>() { static Type ty("schar", sizeof(schar)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<short>() { static Type ty("short", sizeof(short)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<stl::string>() { static Type ty("stl::string", sizeof(stl::string)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<uchar>() { static Type ty("uchar", sizeof(uchar)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<uint>() { static Type ty("uint", sizeof(uint)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<ullong>() { static Type ty("ullong", sizeof(ullong)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<ulong>() { static Type ty("ulong", sizeof(ulong)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<ushort>() { static Type ty("ushort", sizeof(ushort)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<void>() { static Type ty("void"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<void*>() { static Type ty("void*", sizeof(void*)); return ty; }
    
    template <> MUD_TYPE_EXPORT Type& type<stl::vector<mud::Ref>>() { static Type ty("vector<mud::Ref>", sizeof(stl::vector<mud::Ref>)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<stl::vector<stl::string>>() { static Type ty("vector<stl::string>", sizeof(stl::vector<stl::string>)); return ty; }
    
    template <> MUD_TYPE_EXPORT Type& type<mud::Index>() { static Type ty("Index", sizeof(mud::Index)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Indexer>() { static Type ty("Indexer", sizeof(mud::Indexer)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Prototype>() { static Type ty("Prototype", sizeof(mud::Prototype)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Ref>() { static Type ty("Ref", sizeof(mud::Ref)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Var>() { static Type ty("Var", sizeof(mud::Var)); return ty; }
}
