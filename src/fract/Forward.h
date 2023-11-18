#pragma once

#include <infra/Config.h>

#ifndef TWO_FRACT_EXPORT
#define TWO_FRACT_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum class PatternSampling : unsigned int;

    export_ class Pixircle;
    export_ class Circlifier;
    export_ struct Pattern;
    export_ struct FractTab;
    export_ class Fract;
    export_ class FractSample;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
	extern template class refl_ seque_ vector<two::Circle>;
	extern template class refl_ seque_ vector<two::Image256>;
}
#endif