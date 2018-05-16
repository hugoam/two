

#pragma once

#include <snd/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>

namespace mud
{
    template <> MUD_SND_EXPORT Type& type<mud::Sound::FadeControl>();
    template <> MUD_SND_EXPORT Type& type<mud::Sound::State>();
    
#ifdef MUD_SND_REFLECTION_IMPL
    void snd_meta(Module& module)
    {   
    // Base Types
    
    // Enums
    
    // Sequences
    
    
    
    
    
    
    
    
    
    
    
    

    
    
    }
#endif

}
