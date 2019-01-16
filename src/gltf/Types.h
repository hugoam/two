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
#include <cstdint>
#include <stl/vector.h>
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
    
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTF*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFAccessor*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFAnimation*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFAnimationChannel*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFAnimationSampler*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFAnimationTarget*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFAttributes*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFBuffer*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFBufferView*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFCamera*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFImage*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFMaterial*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFMaterialPBR*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFMesh*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFMorphTarget*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFNode*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFNodeExtras*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFOrthographic*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFPerspective*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFPrimitive*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFSampler*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFScene*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFSkin*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFSparse*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFSparseIndices*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFSparseValues*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFTexture*>>;
    export_ template struct MUD_GLTF_EXPORT Typed<vector<glTFTextureInfo*>>;
}
