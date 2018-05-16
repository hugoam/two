

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>

#if defined MUD_MATH_LIB
#define MUD_MATH_EXPORT MUD_EXPORT
#else
#define MUD_MATH_EXPORT MUD_IMPORT
#endif


    
    

namespace mud {

    enum Clockwise : unsigned int;
    enum class Axis : unsigned int;
    enum class SignedAxis : unsigned int;
    enum class Side : unsigned int;
    enum SpectrumPalette : short;
    
    template <class T> struct Grid;
    template <class T> struct array_3d;
    template <class T> struct Range;
    template <class T> class AutoStat;
    
    struct Colour;
    class Grid3;
    struct Palette;
    struct Image256;
    class Lerp;
    struct Ratio;
    struct Gauge;
}

namespace std {

    
    
}

namespace mud {
namespace detail {

    
    
}
}

namespace glm {

    
    
}

