

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.procgen-gfx;
#else
#include <procgen-gfx/Types.h>
#include <procgen-gfx/Api.h>
#include <obj/Vector.h>
//#include <proto/Proto.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_PROCGEN_GFX_EXPORT Type& type<mud::TileModel>() { static Type ty("TileModel"); return ty; }
    template <> MUD_PROCGEN_GFX_EXPORT Type& type<mud::Tileblock>() { static Type ty("Tileblock"); return ty; }
}
