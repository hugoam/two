

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>

#if defined MUD_SND_LIB
#define MUD_SND_EXPORT MUD_EXPORT
#else
#define MUD_SND_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace mud {
namespace ui {

    
    
}
}

namespace glm {

    
    
}

namespace mud {

    
    
    class Sound;
    class SoundFileBuffer;
    class OggFileBuffer;
    class SharedBuffer;
    class SoundImplementer;
    class SoundListener;
    class SoundManager;
    class StaticSound;
    class StreamSound;
}

namespace mud {
namespace detail {

    
    
}
}

