

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>

#if defined MUD_SRLZ_LIB
#define MUD_SRLZ_EXPORT MUD_EXPORT
#else
#define MUD_SRLZ_EXPORT MUD_IMPORT
#endif


    
    

namespace mud {

    
    
    class FromJson;
    class ToJson;
}

namespace json11 {

    
    
}

