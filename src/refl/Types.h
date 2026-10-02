#pragma once

#include <refl/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_REFL_EXPORT Type& type<two::TypeClass>();
    
    template <> TWO_REFL_EXPORT Type& type<stl::span<two::Type*>>();
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Var>>();
    template <> TWO_REFL_EXPORT Type& type<stl::vector<void*>>();
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Module*>>();
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Type*>>();
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Alias*>>();
    template <> TWO_REFL_EXPORT Type& type<stl::vector<two::Function*>>();
    
    template <> TWO_REFL_EXPORT Type& type<two::QualType>();
    template <> TWO_REFL_EXPORT Type& type<two::Param>();
    template <> TWO_REFL_EXPORT Type& type<two::Signature>();
    template <> TWO_REFL_EXPORT Type& type<two::Callable>();
    template <> TWO_REFL_EXPORT Type& type<two::Function>();
    template <> TWO_REFL_EXPORT Type& type<two::Operator>();
    template <> TWO_REFL_EXPORT Type& type<two::Method>();
    template <> TWO_REFL_EXPORT Type& type<two::Constructor>();
    template <> TWO_REFL_EXPORT Type& type<two::CopyConstructor>();
    template <> TWO_REFL_EXPORT Type& type<two::Destructor>();
    template <> TWO_REFL_EXPORT Type& type<two::Call>();
    template <> TWO_REFL_EXPORT Type& type<two::Meta>();
    template <> TWO_REFL_EXPORT Type& type<two::Convert>();
    template <> TWO_REFL_EXPORT Type& type<two::Static>();
    template <> TWO_REFL_EXPORT Type& type<two::Member>();
    template <> TWO_REFL_EXPORT Type& type<two::Class>();
    template <> TWO_REFL_EXPORT Type& type<two::Enum>();
    template <> TWO_REFL_EXPORT Type& type<two::Injector>();
    template <> TWO_REFL_EXPORT Type& type<two::Creator>();
    template <> TWO_REFL_EXPORT Type& type<two::Namespace>();
    template <> TWO_REFL_EXPORT Type& type<two::Alias>();
    template <> TWO_REFL_EXPORT Type& type<two::Module>();
    template <> TWO_REFL_EXPORT Type& type<two::System>();
}
