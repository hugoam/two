

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <refl/Types.h>
#include <refl/Api.h>
#include <obj/Vector.h>
//#include <proto/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_REFL_EXPORT Type& type<mud::ConstructorIndex>() { static Type ty("mud::ConstructorIndex"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Param::Flags>() { static Type ty("mud::Param::Flags"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Member::Flags>() { static Type ty("mud::Member::Flags"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::TypeClass>() { static Type ty("mud::TypeClass"); return ty; }
    
    template <> MUD_REFL_EXPORT Type& type<mud::Call>() { static Type ty("Call"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Callable>() { static Type ty("Callable"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Class>() { static Type ty("Class"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Convert>() { static Type ty("Convert"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Creator>() { static Type ty("Creator"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Enum>() { static Type ty("Enum"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Injector>() { static Type ty("Injector"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Member>() { static Type ty("Member"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Meta>() { static Type ty("Meta"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Module>() { static Type ty("Module"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Namespace>() { static Type ty("Namespace"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Param>() { static Type ty("Param"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Signature>() { static Type ty("Signature"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Static>() { static Type ty("Static"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::System>() { static Type ty("System"); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Constructor>() { static Type ty("Constructor", type<mud::Callable>()); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::CopyConstructor>() { static Type ty("CopyConstructor", type<mud::Callable>()); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Destructor>() { static Type ty("Destructor", type<mud::Callable>()); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Function>() { static Type ty("Function", type<mud::Callable>()); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Method>() { static Type ty("Method", type<mud::Callable>()); return ty; }
}
