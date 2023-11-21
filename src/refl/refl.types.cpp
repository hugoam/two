module;
#include <infra/Cpp20.h>
module two.refl;

namespace two
{
    // Exported types
    template <> TWO_REFL_EXPORT Type& type<two::TypeClass>() { static Type ty("TypeClass", sizeof(two::TypeClass)); return ty; }
    
    template <> TWO_REFL_EXPORT Type& type<stl::span<two::Type*>>() { static Type ty("span<two::Type*>", sizeof(stl::span<two::Type*>)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Var>>() { static Type ty("vector<two::Var>", sizeof(stl::vector<two::Var>)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<stl::vector<void*>>() { static Type ty("vector<void*>", sizeof(stl::vector<void*>)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Module*>>() { static Type ty("vector<two::Module*>", sizeof(stl::vector<two::Module*>)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Type*>>() { static Type ty("vector<two::Type*>", sizeof(stl::vector<two::Type*>)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Alias*>>() { static Type ty("vector<two::Alias*>", sizeof(stl::vector<two::Alias*>)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Function*>>() { static Type ty("vector<two::Function*>", sizeof(stl::vector<two::Function*>)); return ty; }
    
    template <> TWO_REFL_EXPORT Type& type<two::QualType>() { static Type ty("QualType", sizeof(two::QualType)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Param>() { static Type ty("Param", sizeof(two::Param)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Signature>() { static Type ty("Signature", sizeof(two::Signature)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Callable>() { static Type ty("Callable", sizeof(two::Callable)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Function>() { static Type ty("Function", type<two::Callable>(), sizeof(two::Function)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Operator>() { static Type ty("Operator", sizeof(two::Operator)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Method>() { static Type ty("Method", type<two::Callable>(), sizeof(two::Method)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Constructor>() { static Type ty("Constructor", type<two::Callable>(), sizeof(two::Constructor)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::CopyConstructor>() { static Type ty("CopyConstructor", type<two::Callable>(), sizeof(two::CopyConstructor)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Destructor>() { static Type ty("Destructor", type<two::Callable>(), sizeof(two::Destructor)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Call>() { static Type ty("Call", sizeof(two::Call)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Meta>() { static Type ty("Meta", sizeof(two::Meta)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Convert>() { static Type ty("Convert", sizeof(two::Convert)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Static>() { static Type ty("Static", sizeof(two::Static)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Member>() { static Type ty("Member", sizeof(two::Member)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Class>() { static Type ty("Class", sizeof(two::Class)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Enum>() { static Type ty("Enum", sizeof(two::Enum)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Injector>() { static Type ty("Injector", type<two::Call>(), sizeof(two::Injector)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Creator>() { static Type ty("Creator", sizeof(two::Creator)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Namespace>() { static Type ty("Namespace", sizeof(two::Namespace)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Alias>() { static Type ty("Alias", sizeof(two::Alias)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::Module>() { static Type ty("Module", sizeof(two::Module)); return ty; }
    template <> TWO_REFL_EXPORT Type& type<two::System>() { static Type ty("System", sizeof(two::System)); return ty; }
}
