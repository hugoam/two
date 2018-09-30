

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.procgen-gfx;
#else
#include <procgen-gfx/Types.h>
#include <procgen-gfx/Api.h>
#include <type/Vector.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_PROCGEN_GFX_EXPORT Type& type<mud::TileModel>() { static Type ty("TileModel"); return ty; }
    template <> MUD_PROCGEN_GFX_EXPORT Type& type<mud::WfcBlock>() { static Type ty("WfcBlock"); return ty; }
}
