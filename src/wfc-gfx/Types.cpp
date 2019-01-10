#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.wfc-gfx;
#else
#include <wfc-gfx/Types.h>
#include <wfc-gfx/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_WFC_GFX_EXPORT Type& type<mud::TileModel>() { static Type ty("TileModel"); return ty; }
    template <> MUD_WFC_GFX_EXPORT Type& type<mud::WfcBlock>() { static Type ty("WfcBlock"); return ty; }
}
