#pragma once

#include <gltf/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_GLTF_EXPORT Type& type<glTFComponentType>();
    template <> TWO_GLTF_EXPORT Type& type<glTFType>();
    template <> TWO_GLTF_EXPORT Type& type<glTFPrimitiveType>();
    template <> TWO_GLTF_EXPORT Type& type<glTFInterpolation>();
    template <> TWO_GLTF_EXPORT Type& type<glTFAlphaMode>();
    
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFAnimationSampler>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFAnimationChannel>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFMorphTarget>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFPrimitive>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFBuffer>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFBufferView>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFAccessor>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFImage>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFTexture>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFMaterial>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFMesh>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFNode>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFSkin>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFAnimation>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFCamera>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFSampler>>();
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFScene>>();
    
    template <> TWO_GLTF_EXPORT Type& type<glTFNodeExtras>();
    template <> TWO_GLTF_EXPORT Type& type<glTFBuffer>();
    template <> TWO_GLTF_EXPORT Type& type<glTFImage>();
    template <> TWO_GLTF_EXPORT Type& type<glTFBufferView>();
    template <> TWO_GLTF_EXPORT Type& type<glTFSparseIndices>();
    template <> TWO_GLTF_EXPORT Type& type<glTFSparseValues>();
    template <> TWO_GLTF_EXPORT Type& type<glTFSparse>();
    template <> TWO_GLTF_EXPORT Type& type<glTFAccessor>();
    template <> TWO_GLTF_EXPORT Type& type<glTFSampler>();
    template <> TWO_GLTF_EXPORT Type& type<glTFTexture>();
    template <> TWO_GLTF_EXPORT Type& type<glTFSkin>();
    template <> TWO_GLTF_EXPORT Type& type<glTFAttributes>();
    template <> TWO_GLTF_EXPORT Type& type<glTFMorphTarget>();
    template <> TWO_GLTF_EXPORT Type& type<glTFPrimitive>();
    template <> TWO_GLTF_EXPORT Type& type<glTFMesh>();
    template <> TWO_GLTF_EXPORT Type& type<glTFPerspective>();
    template <> TWO_GLTF_EXPORT Type& type<glTFOrthographic>();
    template <> TWO_GLTF_EXPORT Type& type<glTFCamera>();
    template <> TWO_GLTF_EXPORT Type& type<glTFAnimationTarget>();
    template <> TWO_GLTF_EXPORT Type& type<glTFAnimationChannel>();
    template <> TWO_GLTF_EXPORT Type& type<glTFAnimationSampler>();
    template <> TWO_GLTF_EXPORT Type& type<glTFAnimation>();
    template <> TWO_GLTF_EXPORT Type& type<glTFTextureInfo>();
    template <> TWO_GLTF_EXPORT Type& type<glTFMaterialPBR>();
    template <> TWO_GLTF_EXPORT Type& type<glTFMaterial>();
    template <> TWO_GLTF_EXPORT Type& type<glTFNode>();
    template <> TWO_GLTF_EXPORT Type& type<glTFScene>();
    template <> TWO_GLTF_EXPORT Type& type<glTF>();
}
