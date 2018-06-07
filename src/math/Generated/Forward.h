

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <srlz/Generated/Forward.h>

#ifndef MUD_MATH_EXPORT
#define MUD_MATH_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace glm {

    
    
}

namespace json11 {

    
    
}

namespace mud {

    enum Clockwise : unsigned int;
    enum class Axis : unsigned int;
    enum class Axes : unsigned int;
    enum class SignedAxis : unsigned int;
    enum class Side : unsigned int;
    enum class TrackMode : unsigned int;
    enum SpectrumPalette : short;
    
    template <class T> struct Range;
    template <class T> struct ValueCurve;
    template <class T> struct ValueTrack;
    template <class T> struct Grid;
    template <class T> struct array_3d;
    template <class T> class AutoStat;
    
    struct Colour;
    class Lerp;
    class Grid3;
    struct Palette;
    struct Image256;
    struct Ratio;
    struct Gauge;
}

namespace mud {
namespace detail {

    
    
}
}

