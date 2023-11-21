module;
#include <infra/Cpp20.h>
module two.type;

namespace two
{
    // Exported types
    template <> TWO_TYPE_EXPORT Type& type<void*>() { static Type ty("void*", sizeof(void*)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<bool>() { static Type ty("bool", sizeof(bool)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<char>() { static Type ty("char", sizeof(char)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<schar>() { static Type ty("schar", sizeof(schar)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<short>() { static Type ty("short", sizeof(short)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<int>() { static Type ty("int", sizeof(int)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<long>() { static Type ty("long", sizeof(long)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<uchar>() { static Type ty("uchar", sizeof(uchar)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<ushort>() { static Type ty("ushort", sizeof(ushort)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<uint>() { static Type ty("uint", sizeof(uint)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<ulong>() { static Type ty("ulong", sizeof(ulong)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<ullong>() { static Type ty("ullong", sizeof(ullong)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<llong>() { static Type ty("llong", sizeof(llong)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<ldouble>() { static Type ty("ldouble", sizeof(ldouble)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<float>() { static Type ty("float", sizeof(float)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<double>() { static Type ty("double", sizeof(double)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<const char*>() { static Type ty("const char*", sizeof(const char*)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<stl::string>() { static Type ty("stl::string", sizeof(stl::string)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<void>() { static Type ty("void"); return ty; }
    
    template <> TWO_TYPE_EXPORT Type& type<stl::vector<stl::string>>() { static Type ty("vector<stl::string>", sizeof(stl::vector<stl::string>)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<stl::vector<two::Ref>>() { static Type ty("vector<two::Ref>", sizeof(stl::vector<two::Ref>)); return ty; }
    
    template <> TWO_TYPE_EXPORT Type& type<two::Ref>() { static Type ty("Ref", sizeof(two::Ref)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<two::Var>() { static Type ty("Var", sizeof(two::Var)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<two::Indexer>() { static Type ty("Indexer", sizeof(two::Indexer)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<two::Index>() { static Type ty("Index", sizeof(two::Index)); return ty; }
    template <> TWO_TYPE_EXPORT Type& type<two::Prototype>() { static Type ty("Prototype", sizeof(two::Prototype)); return ty; }
}
