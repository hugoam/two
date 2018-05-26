#pragma once

#include <gfx-gltf/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <geom/Generated/Types.h>
#include <gfx/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAlphaMode>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFComponentType>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFInterpolation>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPrimitiveType>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFType>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAccessor>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimation>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimationChannel>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimationSampler>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFBuffer>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFBufferView>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFCamera>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFImage>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMaterial>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMesh>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMorphTarget>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFNode>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFPrimitive>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFScene>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFSkin>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFTexture>>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<int>>();
    
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTF>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAccessor>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimation>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationChannel>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationSampler>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationTarget>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAttributes>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFBuffer>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFBufferView>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFCamera>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFImage>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<mud::glTFImport>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMaterial>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMaterialPBR>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMesh>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMorphTarget>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFNode>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFOrthographic>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPerspective>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPrimitive>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSampler>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFScene>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSkin>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparse>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparseIndices>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparseValues>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFTexture>();
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFTextureInfo>();
}
