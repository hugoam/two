

#include <obj/Generated/Types.h>
#include <obj/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> MUD_OBJ_EXPORT Type& type<bool>() { static Type ty("bool"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<char>() { static Type ty("char"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<cstring>() { static Type ty("cstring"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<double>() { static Type ty("double"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<float>() { static Type ty("float"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<int>() { static Type ty("int"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<long>() { static Type ty("long"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<long long>() { static Type ty("long long"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<short>() { static Type ty("short"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<std::string>() { static Type ty("std::string"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<unsigned char>() { static Type ty("unsigned char"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<unsigned int>() { static Type ty("unsigned int"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<unsigned long>() { static Type ty("unsigned long"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<unsigned long long>() { static Type ty("unsigned long long"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<unsigned short>() { static Type ty("unsigned short"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<void>() { static Type ty("void"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::ConstructorIndex>() { static Type ty("mud::ConstructorIndex"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Param::Flags>() { static Type ty("mud::Param::Flags"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Member::Flags>() { static Type ty("mud::Member::Flags"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::TypeClass>() { static Type ty("mud::TypeClass"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::TypeKind>() { static Type ty("mud::TypeKind"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::VarMode>() { static Type ty("mud::VarMode"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Function*>>() { static Type ty("std::vector<mud::Function*>"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Module*>>() { static Type ty("std::vector<mud::Module*>"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Prototype*>>() { static Type ty("std::vector<mud::Prototype*>"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Ref>>() { static Type ty("std::vector<mud::Ref>"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Type*>>() { static Type ty("std::vector<mud::Type*>"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Var>>() { static Type ty("std::vector<mud::Var>"); return ty; }
    
    template <> MUD_OBJ_EXPORT Type& type<mud::Call>() { static Type ty("Call"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Callable>() { static Type ty("Callable"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Class>() { static Type ty("Class"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Complex>() { static Type ty("Complex"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Construct>() { static Type ty("Construct"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Convert>() { static Type ty("Convert"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Creator>() { static Type ty("Creator"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Enum>() { static Type ty("Enum"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Index>() { static Type ty("Index"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Indexer>() { static Type ty("Indexer"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Injector>() { static Type ty("Injector"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Member>() { static Type ty("Member"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Meta>() { static Type ty("Meta"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Module>() { static Type ty("Module"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Namespace>() { static Type ty("Namespace"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::None>() { static Type ty("None"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Param>() { static Type ty("Param"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Pool>() { static Type ty("Pool"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Ref>() { static Type ty("Ref"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Signature>() { static Type ty("Signature"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Static>() { static Type ty("Static"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::System>() { static Type ty("System"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Time>() { static Type ty("Time"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::TimeSpan>() { static Type ty("TimeSpan"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Var>() { static Type ty("Var"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::array<float>>() { static Type ty("array<float>"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::array<mud::cstring>>() { static Type ty("array<mud::cstring>"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::strung>() { static Type ty("strung"); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Function>() { static Type ty("Function", type<mud::Callable>()); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Method>() { static Type ty("Method", type<mud::Callable>()); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Constructor>() { static Type ty("Constructor", type<mud::Callable>()); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::CopyConstructor>() { static Type ty("CopyConstructor", type<mud::Callable>()); return ty; }
    template <> MUD_OBJ_EXPORT Type& type<mud::Destructor>() { static Type ty("Destructor", type<mud::Callable>()); return ty; }
}
