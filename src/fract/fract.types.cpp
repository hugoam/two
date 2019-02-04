#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.fract;
#else
#include <fract/Types.h>
#include <fract/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_FRACT_EXPORT Type& type<mud::PatternSampling>() { static Type ty("mud::PatternSampling", sizeof(mud::PatternSampling)); return ty; }
    
    template <> MUD_FRACT_EXPORT Type& type<mud::Circlifier>() { static Type ty("Circlifier", sizeof(mud::Circlifier)); return ty; }
    template <> MUD_FRACT_EXPORT Type& type<mud::Fract>() { static Type ty("Fract", sizeof(mud::Fract)); return ty; }
    template <> MUD_FRACT_EXPORT Type& type<mud::FractSample>() { static Type ty("FractSample", sizeof(mud::FractSample)); return ty; }
    template <> MUD_FRACT_EXPORT Type& type<mud::FractTab>() { static Type ty("FractTab", sizeof(mud::FractTab)); return ty; }
    template <> MUD_FRACT_EXPORT Type& type<mud::Pattern>() { static Type ty("Pattern", sizeof(mud::Pattern)); return ty; }
}
