#pragma once

#include <gltf/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <refl/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAlphaMode>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFComponentType>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFInterpolation>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFPrimitiveType>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFType>();
    
    export_ template <> MUD_GLTF_EXPORT Type& type<glTF>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAccessor>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAnimation>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAnimationChannel>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAnimationSampler>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAnimationTarget>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFAttributes>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFBuffer>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFBufferView>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFCamera>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFImage>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFMaterial>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFMaterialPBR>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFMesh>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFMorphTarget>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFNode>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFNodeExtras>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFOrthographic>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFPerspective>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFPrimitive>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSampler>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFScene>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSkin>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSparse>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSparseIndices>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFSparseValues>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFTexture>();
    export_ template <> MUD_GLTF_EXPORT Type& type<glTFTextureInfo>();
    
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTF*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFAccessor*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFAnimation*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFAnimationChannel*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFAnimationSampler*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFAnimationTarget*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFAttributes*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFBuffer*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFBufferView*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFCamera*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFImage*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFMaterial*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFMaterialPBR*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFMesh*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFMorphTarget*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFNode*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFNodeExtras*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFOrthographic*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFPerspective*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFPrimitive*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFSampler*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFScene*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFSkin*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFSparse*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFSparseIndices*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFSparseValues*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFTexture*>>();
    export_ template <> MUD_GLTF_EXPORT Type& type<vector<glTFTextureInfo*>>();
}
