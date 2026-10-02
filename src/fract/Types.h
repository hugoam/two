#pragma once

#include <fract/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_FRACT_EXPORT Type& type<two::PatternSampling>();
    
    template <> TWO_FRACT_EXPORT Type& type<stl::vector<two::Image256>>();
    
    template <> TWO_FRACT_EXPORT Type& type<two::Circlifier>();
    template <> TWO_FRACT_EXPORT Type& type<two::Pattern>();
    template <> TWO_FRACT_EXPORT Type& type<two::FractTab>();
    template <> TWO_FRACT_EXPORT Type& type<two::Fract>();
    template <> TWO_FRACT_EXPORT Type& type<two::FractSample>();
}
