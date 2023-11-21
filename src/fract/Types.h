#pragma once

#include <fract/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_FRACT_EXPORT Type& type<two::PatternSampling>();
    
    export_ template <> TWO_FRACT_EXPORT Type& type<stl::vector<two::Image256>>();
    
    export_ template <> TWO_FRACT_EXPORT Type& type<two::Circlifier>();
    export_ template <> TWO_FRACT_EXPORT Type& type<two::Pattern>();
    export_ template <> TWO_FRACT_EXPORT Type& type<two::FractTab>();
    export_ template <> TWO_FRACT_EXPORT Type& type<two::Fract>();
    export_ template <> TWO_FRACT_EXPORT Type& type<two::FractSample>();
}
