

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <math/Generated/Forward.h>
#include <geom/Generated/Forward.h>
#include <ui/Generated/Forward.h>
#include <gfx/Generated/Forward.h>
#include <edit/Generated/Forward.h>

#if defined MUD_GEN_LIB
#define MUD_GEN_EXPORT MUD_EXPORT
#else
#define MUD_GEN_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace mud {
namespace ui {

    
    
}
}

namespace glm {

    
    
}

namespace bgfx {

    
    
}

namespace mud {
namespace gfx {

    
    
}
}

namespace json11 {

    
    
}

namespace mud {

    enum PatternSampling : unsigned int;
    enum Result : unsigned int;
    
    
    class Pixircle;
    class Circlifier;
    struct Pattern;
    struct FractTab;
    class Fract;
    class FractSample;
    class Noise;
    struct Tile;
    struct Tileset;
    struct DoubleGenerator;
    struct Wave;
    struct WaveTileset;
    struct TileWave;
    struct VoxelTile;
    struct RGBA;
    struct PalettedImage;
    class Patternset;
    struct TileModel;
    class Tileblock;
}

namespace mud {
namespace detail {

    
    
}
}

namespace bimg {

    
    
}

namespace bx {

    
    
}

