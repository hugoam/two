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
	void test()
	{
		Var v = var(vector<mud::Ref>());
		vector<Ref> a; vector<Ref> b;
		any_compare(a, b);
	}
    // Exported types
    template <> MUD_TYPE_EXPORT Type& type<bool>() { static Type ty("bool", sizeof(bool)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<char>() { static Type ty("char", sizeof(char)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<const char*>() { static Type ty("const char*", sizeof(const char*)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<double>() { static Type ty("double", sizeof(double)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<float>() { static Type ty("float", sizeof(float)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<int>() { static Type ty("int", sizeof(int)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<long>() { static Type ty("long", sizeof(long)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<long long>() { static Type ty("long long", sizeof(long long)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<short>() { static Type ty("short", sizeof(short)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<string>() { static Type ty("string", sizeof(string)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned char>() { static Type ty("unsigned char", sizeof(unsigned char)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned int>() { static Type ty("unsigned int", sizeof(unsigned int)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned long>() { static Type ty("unsigned long", sizeof(unsigned long)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned long long>() { static Type ty("unsigned long long", sizeof(unsigned long long)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<unsigned short>() { static Type ty("unsigned short", sizeof(unsigned short)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<void>() { static Type ty("void"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<void*>() { static Type ty("void*", sizeof(void*)); return ty; }
    
    template <> MUD_TYPE_EXPORT Type& type<mud::Index>() { static Type ty("Index", sizeof(mud::Index)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Indexer>() { static Type ty("Indexer", sizeof(mud::Indexer)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Ref>() { static Type ty("Ref", sizeof(mud::Ref)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Var>() { static Type ty("Var", sizeof(mud::Var)); return ty; }
}
