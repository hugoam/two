#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>

#ifndef TWO_FRACT_EXPORT
#define TWO_FRACT_EXPORT TWO_IMPORT
#endif

namespace two
{
    enum class PatternSampling : unsigned int;

    class Pixircle;
    class Circlifier;
    struct Pattern;
    struct FractTab;
    class Fract;
    class FractSample;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
	export_ extern template class refl_ seque_ vector<two::Circle>;
	export_ extern template class refl_ seque_ vector<two::Image256>;
}
#endif