#pragma once

#include <fract/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::PatternSampling>();
    
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::Circlifier>();
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::Fract>();
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::FractSample>();
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::FractTab>();
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::Pattern>();
    
    export_ template struct MUD_FRACT_EXPORT Typed<std::vector<mud::Circlifier*>>;
    export_ template struct MUD_FRACT_EXPORT Typed<std::vector<mud::Fract*>>;
    export_ template struct MUD_FRACT_EXPORT Typed<std::vector<mud::FractSample*>>;
    export_ template struct MUD_FRACT_EXPORT Typed<std::vector<mud::FractTab*>>;
    export_ template struct MUD_FRACT_EXPORT Typed<std::vector<mud::Pattern*>>;
}
