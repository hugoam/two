#pragma once

#include <infra/Config.h>


#ifndef TWO_SND_EXPORT
#define TWO_SND_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ class Sound;
    export_ class SoundFileBuffer;
    export_ class OggFileBuffer;
    export_ class SharedBuffer;
    export_ class SoundImplementer;
    export_ class SoundListener;
    export_ class SoundManager;
    export_ class StaticSound;
    export_ class StreamSound;
}
