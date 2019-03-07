#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-gltf;
#else
#include <gfx-gltf/Types.h>
#include <gfx-gltf/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    
    template <> MUD_GFX_GLTF_EXPORT Type& type<mud::ImporterGltf>() { static Type ty("ImporterGltf", sizeof(mud::ImporterGltf)); return ty; }
}
