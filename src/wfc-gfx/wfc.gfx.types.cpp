#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module TWO(wfc-gfx);
#else
#include <wfc-gfx/Types.h>
#include <wfc-gfx/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_WFC_GFX_EXPORT Type& type<two::TileModel>() { static Type ty("TileModel", sizeof(two::TileModel)); return ty; }
    template <> TWO_WFC_GFX_EXPORT Type& type<two::WfcBlock>() { static Type ty("WfcBlock", sizeof(two::WfcBlock)); return ty; }
}
