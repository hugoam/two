#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <gltf/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <refl/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFComponentType>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFType>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFPrimitiveType>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFInterpolation>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAlphaMode>();
    
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFAnimationSampler>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFAnimationChannel>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFMorphTarget>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFPrimitive>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFBuffer>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFBufferView>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFAccessor>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFImage>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFTexture>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFMaterial>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFMesh>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFNode>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFSkin>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFAnimation>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFCamera>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFSampler>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<stl::vector<glTFScene>>();
    
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFNodeExtras>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFBuffer>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFImage>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFBufferView>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSparseIndices>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSparseValues>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSparse>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAccessor>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSampler>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFTexture>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSkin>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAttributes>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFMorphTarget>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFPrimitive>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFMesh>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFPerspective>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFOrthographic>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFCamera>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAnimationTarget>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAnimationChannel>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAnimationSampler>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAnimation>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFTextureInfo>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFMaterialPBR>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFMaterial>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFNode>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFScene>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTF>();
}
