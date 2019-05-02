#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx-gltf;
#else
#include <gfx-gltf/Types.h>
#include <gfx-gltf/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_GFX_GLTF_EXPORT Type& type<two::ImporterGltf>() { static Type ty("ImporterGltf", sizeof(two::ImporterGltf)); return ty; }
}
