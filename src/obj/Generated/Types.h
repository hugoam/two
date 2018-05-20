#pragma once

#include <obj/Generated/Forward.h>


#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_OBJ_EXPORT Type& type<bool>();
    template <> MUD_OBJ_EXPORT Type& type<char>();
    template <> MUD_OBJ_EXPORT Type& type<cstring>();
    template <> MUD_OBJ_EXPORT Type& type<double>();
    template <> MUD_OBJ_EXPORT Type& type<float>();
    template <> MUD_OBJ_EXPORT Type& type<int>();
    template <> MUD_OBJ_EXPORT Type& type<long>();
    template <> MUD_OBJ_EXPORT Type& type<long long>();
    template <> MUD_OBJ_EXPORT Type& type<short>();
    template <> MUD_OBJ_EXPORT Type& type<std::string>();
    template <> MUD_OBJ_EXPORT Type& type<unsigned char>();
    template <> MUD_OBJ_EXPORT Type& type<unsigned int>();
    template <> MUD_OBJ_EXPORT Type& type<unsigned long>();
    template <> MUD_OBJ_EXPORT Type& type<unsigned long long>();
    template <> MUD_OBJ_EXPORT Type& type<unsigned short>();
    template <> MUD_OBJ_EXPORT Type& type<void>();
    template <> MUD_OBJ_EXPORT Type& type<mud::ConstructorIndex>();
    template <> MUD_OBJ_EXPORT Type& type<mud::TypeClass>();
    template <> MUD_OBJ_EXPORT Type& type<mud::TypeKind>();
    template <> MUD_OBJ_EXPORT Type& type<mud::VarMode>();
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Function*>>();
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Module*>>();
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Prototype*>>();
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Ref>>();
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Type*>>();
    template <> MUD_OBJ_EXPORT Type& type<std::vector<mud::Var>>();
    
    template <> MUD_OBJ_EXPORT Type& type<mud::Call>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Callable>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Class>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Complex>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Construct>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Convert>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Creator>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Enum>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Index>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Indexer>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Injector>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Member>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Meta>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Module>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Namespace>();
    template <> MUD_OBJ_EXPORT Type& type<mud::None>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Param>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Pool>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Ref>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Signature>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Static>();
    template <> MUD_OBJ_EXPORT Type& type<mud::System>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Time>();
    template <> MUD_OBJ_EXPORT Type& type<mud::TimeSpan>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Var>();
    template <> MUD_OBJ_EXPORT Type& type<mud::array<float>>();
    template <> MUD_OBJ_EXPORT Type& type<mud::array<mud::cstring>>();
    template <> MUD_OBJ_EXPORT Type& type<mud::strung>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Constructor>();
    template <> MUD_OBJ_EXPORT Type& type<mud::CopyConstructor>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Destructor>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Function>();
    template <> MUD_OBJ_EXPORT Type& type<mud::Method>();
}
