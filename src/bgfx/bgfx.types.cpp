#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.bgfx;
#else
#include <bgfx/Types.h>
#include <bgfx/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_BGFX_EXPORT Type& type<two::BgfxSystem>() { static Type ty("BgfxSystem", type<two::RenderSystem>(), sizeof(two::BgfxSystem)); return ty; }
}
