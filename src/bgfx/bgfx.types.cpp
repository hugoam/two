module;
#include <infra/Cpp20.h>
module two.bgfx;

namespace two
{
    // Exported types
    
    
    template <> TWO_BGFX_EXPORT Type& type<two::BgfxSystem>() { static Type ty("BgfxSystem", type<two::RenderSystem>(), sizeof(two::BgfxSystem)); return ty; }
}
