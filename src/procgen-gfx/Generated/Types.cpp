

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.procgen.gfx;
#else
#include <procgen-gfx/Generated/Types.h>
#include <procgen-gfx/Generated/Module.h>
#include <obj/Proto.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_PROCGEN_GFX_EXPORT Type& type<mud::TileModel>() { static Type ty("TileModel"); return ty; }
    template <> MUD_PROCGEN_GFX_EXPORT Type& type<mud::Tileblock>() { static Type ty("Tileblock"); return ty; }
}
