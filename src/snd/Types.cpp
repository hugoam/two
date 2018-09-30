

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.snd;
#else
#include <snd/Types.h>
#include <snd/Api.h>
#include <type/Vector.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_SND_EXPORT Type& type<mud::Sound::FadeControl>() { static Type ty("mud::Sound::FadeControl"); return ty; }
    template <> MUD_SND_EXPORT Type& type<mud::Sound::State>() { static Type ty("mud::Sound::State"); return ty; }
    
}
