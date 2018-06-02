#pragma once

#include <gfx-gltf/Generated/Forward.h>

#ifndef MUD_MODULES
#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <geom/Generated/Types.h>
#include <gfx/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAlphaMode>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFComponentType>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFInterpolation>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPrimitiveType>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFType>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAccessor>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimation>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimationChannel>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimationSampler>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFBuffer>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFBufferView>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFCamera>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFImage>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMaterial>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMesh>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMorphTarget>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFNode>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFPrimitive>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFScene>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFSkin>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFTexture>>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<int>>();
    
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTF>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAccessor>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimation>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationChannel>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationSampler>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationTarget>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAttributes>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFBuffer>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFBufferView>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFCamera>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFImage>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMaterial>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMaterialPBR>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMesh>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMorphTarget>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFNode>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFOrthographic>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPerspective>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPrimitive>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSampler>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFScene>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSkin>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparse>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparseIndices>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparseValues>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFTexture>();
    export_ template <> MUD_GFX_GLTF_EXPORT Type& type<glTFTextureInfo>();
}
