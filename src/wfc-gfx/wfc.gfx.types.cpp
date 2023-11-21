module;
#include <infra/Cpp20.h>
module two.wfc-gfx;

namespace two
{
    // Exported types
    
    
    template <> TWO_WFC_GFX_EXPORT Type& type<two::TileModel>() { static Type ty("TileModel", sizeof(two::TileModel)); return ty; }
    template <> TWO_WFC_GFX_EXPORT Type& type<two::WfcBlock>() { static Type ty("WfcBlock", sizeof(two::WfcBlock)); return ty; }
}
