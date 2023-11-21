module;
#include <infra/Cpp20.h>
module two.gfx.gltf;

namespace two
{
    // Exported types
    
    
    template <> TWO_GFX_GLTF_EXPORT Type& type<two::ImporterGltf>() { static Type ty("ImporterGltf", sizeof(two::ImporterGltf)); return ty; }
}
