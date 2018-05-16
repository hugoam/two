

#include <snd/Generated/Types.h>
#include <snd/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> MUD_SND_EXPORT Type& type<mud::Sound::FadeControl>() { static Type ty("mud::Sound::FadeControl"); return ty; }
    template <> MUD_SND_EXPORT Type& type<mud::Sound::State>() { static Type ty("mud::Sound::State"); return ty; }
    
}
