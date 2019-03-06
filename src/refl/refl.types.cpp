#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <refl/Types.h>
#include <refl/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_REFL_EXPORT Type& type<mud::TypeClass>() { static Type ty("TypeClass", sizeof(mud::TypeClass)); return ty; }
    
    template <> MUD_REFL_EXPORT Type& type<stl::span<mud::Type*>>() { static Type ty("span<mud::Type*>", sizeof(stl::span<mud::Type*>)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Alias*>>() { static Type ty("vector<mud::Alias*>", sizeof(stl::vector<mud::Alias*>)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Function*>>() { static Type ty("vector<mud::Function*>", sizeof(stl::vector<mud::Function*>)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Module*>>() { static Type ty("vector<mud::Module*>", sizeof(stl::vector<mud::Module*>)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Type*>>() { static Type ty("vector<mud::Type*>", sizeof(stl::vector<mud::Type*>)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<stl::vector<mud::Var>>() { static Type ty("vector<mud::Var>", sizeof(stl::vector<mud::Var>)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<stl::vector<void*>>() { static Type ty("vector<void*>", sizeof(stl::vector<void*>)); return ty; }
    
    template <> MUD_REFL_EXPORT Type& type<mud::Alias>() { static Type ty("Alias", sizeof(mud::Alias)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Call>() { static Type ty("Call", sizeof(mud::Call)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Callable>() { static Type ty("Callable", sizeof(mud::Callable)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Class>() { static Type ty("Class", sizeof(mud::Class)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Convert>() { static Type ty("Convert", sizeof(mud::Convert)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Creator>() { static Type ty("Creator", sizeof(mud::Creator)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Enum>() { static Type ty("Enum", sizeof(mud::Enum)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Member>() { static Type ty("Member", sizeof(mud::Member)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Meta>() { static Type ty("Meta", sizeof(mud::Meta)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Module>() { static Type ty("Module", sizeof(mud::Module)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Namespace>() { static Type ty("Namespace", sizeof(mud::Namespace)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Operator>() { static Type ty("Operator", sizeof(mud::Operator)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Param>() { static Type ty("Param", sizeof(mud::Param)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::QualType>() { static Type ty("QualType", sizeof(mud::QualType)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Signature>() { static Type ty("Signature", sizeof(mud::Signature)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Static>() { static Type ty("Static", sizeof(mud::Static)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::System>() { static Type ty("System", sizeof(mud::System)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Constructor>() { static Type ty("Constructor", type<mud::Callable>(), sizeof(mud::Constructor)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::CopyConstructor>() { static Type ty("CopyConstructor", type<mud::Callable>(), sizeof(mud::CopyConstructor)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Destructor>() { static Type ty("Destructor", type<mud::Callable>(), sizeof(mud::Destructor)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Function>() { static Type ty("Function", type<mud::Callable>(), sizeof(mud::Function)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Injector>() { static Type ty("Injector", type<mud::Call>(), sizeof(mud::Injector)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Method>() { static Type ty("Method", type<mud::Callable>(), sizeof(mud::Method)); return ty; }
}
