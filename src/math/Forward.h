

#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <obj/Forward.h>
#include <refl/Forward.h>
#include <srlz/Forward.h>

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
    struct Image;
    struct Palette;
    struct Image256;
    class ImageAtlas;
    class Sprite;
    class SpriteAtlas;
    struct Ratio;
    struct Gauge;
    struct Time;
    struct TimeSpan;
    class Clock;
    struct Anim;
    class Animator;
}

namespace mud {
namespace detail {

    
    
}
}

