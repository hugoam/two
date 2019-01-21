#pragma once

#include <infra/Config.h>


#ifndef MUD_SND_EXPORT
#define MUD_SND_EXPORT MUD_IMPORT
#endif

namespace mud
{
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
