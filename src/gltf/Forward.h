#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <refl/Forward.h>
#include <srlz/Forward.h>
#include <math/Forward.h>

#ifndef TWO_GLTF_EXPORT
#define TWO_GLTF_EXPORT TWO_IMPORT
#endif

enum class glTFComponentType : unsigned int;
enum class glTFType : unsigned int;
enum class glTFPrimitiveType : unsigned int;
enum class glTFInterpolation : unsigned int;
enum class glTFAlphaMode : unsigned int;
    
    
struct glTFBuffer;
struct glTFImage;
struct glTFBufferView;
struct glTFSparseIndices;
struct glTFSparseValues;
struct glTFSparse;
struct glTFAccessor;
struct glTFSampler;
struct glTFTexture;
struct glTFSkin;
struct glTFAttributes;
struct glTFMorphTarget;
struct glTFPrimitive;
struct glTFMesh;
struct glTFPerspective;
struct glTFOrthographic;
struct glTFCamera;
struct glTFAnimationTarget;
struct glTFAnimationChannel;
struct glTFAnimationSampler;
struct glTFAnimation;
struct glTFTextureInfo;
struct glTFMaterialPBR;
struct glTFMaterial;
struct glTFNode;
struct glTFNodeExtras;
struct glTFScene;
struct glTF;
