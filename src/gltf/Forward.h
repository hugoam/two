#pragma once

#include <infra/Config.h>

#ifndef TWO_GLTF_EXPORT
#define TWO_GLTF_EXPORT TWO_IMPORT
#endif

export_ enum class glTFComponentType : unsigned int;
export_ enum class glTFType : unsigned int;
export_ enum class glTFPrimitiveType : unsigned int;
export_ enum class glTFInterpolation : unsigned int;
export_ enum class glTFAlphaMode : unsigned int;


export_ struct glTFBuffer;
export_ struct glTFImage;
export_ struct glTFBufferView;
export_ struct glTFSparseIndices;
export_ struct glTFSparseValues;
export_ struct glTFSparse;
export_ struct glTFAccessor;
export_ struct glTFSampler;
export_ struct glTFTexture;
export_ struct glTFSkin;
export_ struct glTFAttributes;
export_ struct glTFMorphTarget;
export_ struct glTFPrimitive;
export_ struct glTFMesh;
export_ struct glTFPerspective;
export_ struct glTFOrthographic;
export_ struct glTFCamera;
export_ struct glTFAnimationTarget;
export_ struct glTFAnimationChannel;
export_ struct glTFAnimationSampler;
export_ struct glTFAnimation;
export_ struct glTFTextureInfo;
export_ struct glTFMaterialPBR;
export_ struct glTFMaterial;
export_ struct glTFNode;
export_ struct glTFNodeExtras;
export_ struct glTFScene;
export_ struct glTF;
