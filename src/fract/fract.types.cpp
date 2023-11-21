module;
#include <infra/Cpp20.h>
module two.fract;

namespace two
{
    // Exported types
    template <> TWO_FRACT_EXPORT Type& type<two::PatternSampling>() { static Type ty("PatternSampling", sizeof(two::PatternSampling)); return ty; }
    
    template <> TWO_FRACT_EXPORT Type& type<stl::vector<two::Image256>>() { static Type ty("vector<two::Image256>", sizeof(stl::vector<two::Image256>)); return ty; }
    
    template <> TWO_FRACT_EXPORT Type& type<two::Circlifier>() { static Type ty("Circlifier", sizeof(two::Circlifier)); return ty; }
    template <> TWO_FRACT_EXPORT Type& type<two::Pattern>() { static Type ty("Pattern", sizeof(two::Pattern)); return ty; }
    template <> TWO_FRACT_EXPORT Type& type<two::FractTab>() { static Type ty("FractTab", sizeof(two::FractTab)); return ty; }
    template <> TWO_FRACT_EXPORT Type& type<two::Fract>() { static Type ty("Fract", sizeof(two::Fract)); return ty; }
    template <> TWO_FRACT_EXPORT Type& type<two::FractSample>() { static Type ty("FractSample", sizeof(two::FractSample)); return ty; }
}
