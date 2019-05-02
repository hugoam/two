#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.gltf;
#else
#include <gltf/Types.h>
#include <gltf/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    template <> TWO_GLTF_EXPORT Type& type<glTFComponentType>() { static Type ty("glTFComponentType", sizeof(glTFComponentType)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFType>() { static Type ty("glTFType", sizeof(glTFType)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFPrimitiveType>() { static Type ty("glTFPrimitiveType", sizeof(glTFPrimitiveType)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFInterpolation>() { static Type ty("glTFInterpolation", sizeof(glTFInterpolation)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFAlphaMode>() { static Type ty("glTFAlphaMode", sizeof(glTFAlphaMode)); return ty; }
    
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFAnimationSampler>>() { static Type ty("vector<glTFAnimationSampler>", sizeof(stl::vector<glTFAnimationSampler>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFAnimationChannel>>() { static Type ty("vector<glTFAnimationChannel>", sizeof(stl::vector<glTFAnimationChannel>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFMorphTarget>>() { static Type ty("vector<glTFMorphTarget>", sizeof(stl::vector<glTFMorphTarget>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFPrimitive>>() { static Type ty("vector<glTFPrimitive>", sizeof(stl::vector<glTFPrimitive>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFBuffer>>() { static Type ty("vector<glTFBuffer>", sizeof(stl::vector<glTFBuffer>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFBufferView>>() { static Type ty("vector<glTFBufferView>", sizeof(stl::vector<glTFBufferView>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFAccessor>>() { static Type ty("vector<glTFAccessor>", sizeof(stl::vector<glTFAccessor>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFImage>>() { static Type ty("vector<glTFImage>", sizeof(stl::vector<glTFImage>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFTexture>>() { static Type ty("vector<glTFTexture>", sizeof(stl::vector<glTFTexture>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFMaterial>>() { static Type ty("vector<glTFMaterial>", sizeof(stl::vector<glTFMaterial>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFMesh>>() { static Type ty("vector<glTFMesh>", sizeof(stl::vector<glTFMesh>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFNode>>() { static Type ty("vector<glTFNode>", sizeof(stl::vector<glTFNode>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFSkin>>() { static Type ty("vector<glTFSkin>", sizeof(stl::vector<glTFSkin>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFAnimation>>() { static Type ty("vector<glTFAnimation>", sizeof(stl::vector<glTFAnimation>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFCamera>>() { static Type ty("vector<glTFCamera>", sizeof(stl::vector<glTFCamera>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFSampler>>() { static Type ty("vector<glTFSampler>", sizeof(stl::vector<glTFSampler>)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<stl::vector<glTFScene>>() { static Type ty("vector<glTFScene>", sizeof(stl::vector<glTFScene>)); return ty; }
    
    template <> TWO_GLTF_EXPORT Type& type<glTFNodeExtras>() { static Type ty("glTFNodeExtras", sizeof(glTFNodeExtras)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFBuffer>() { static Type ty("glTFBuffer", sizeof(glTFBuffer)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFImage>() { static Type ty("glTFImage", sizeof(glTFImage)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFBufferView>() { static Type ty("glTFBufferView", sizeof(glTFBufferView)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFSparseIndices>() { static Type ty("glTFSparseIndices", sizeof(glTFSparseIndices)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFSparseValues>() { static Type ty("glTFSparseValues", sizeof(glTFSparseValues)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFSparse>() { static Type ty("glTFSparse", sizeof(glTFSparse)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFAccessor>() { static Type ty("glTFAccessor", sizeof(glTFAccessor)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFSampler>() { static Type ty("glTFSampler", sizeof(glTFSampler)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFTexture>() { static Type ty("glTFTexture", sizeof(glTFTexture)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFSkin>() { static Type ty("glTFSkin", sizeof(glTFSkin)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFAttributes>() { static Type ty("glTFAttributes", sizeof(glTFAttributes)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFMorphTarget>() { static Type ty("glTFMorphTarget", sizeof(glTFMorphTarget)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFPrimitive>() { static Type ty("glTFPrimitive", sizeof(glTFPrimitive)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFMesh>() { static Type ty("glTFMesh", sizeof(glTFMesh)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFPerspective>() { static Type ty("glTFPerspective", sizeof(glTFPerspective)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFOrthographic>() { static Type ty("glTFOrthographic", sizeof(glTFOrthographic)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFCamera>() { static Type ty("glTFCamera", sizeof(glTFCamera)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFAnimationTarget>() { static Type ty("glTFAnimationTarget", sizeof(glTFAnimationTarget)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFAnimationChannel>() { static Type ty("glTFAnimationChannel", sizeof(glTFAnimationChannel)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFAnimationSampler>() { static Type ty("glTFAnimationSampler", sizeof(glTFAnimationSampler)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFAnimation>() { static Type ty("glTFAnimation", sizeof(glTFAnimation)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFTextureInfo>() { static Type ty("glTFTextureInfo", sizeof(glTFTextureInfo)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFMaterialPBR>() { static Type ty("glTFMaterialPBR", sizeof(glTFMaterialPBR)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFMaterial>() { static Type ty("glTFMaterial", sizeof(glTFMaterial)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFNode>() { static Type ty("glTFNode", sizeof(glTFNode)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTFScene>() { static Type ty("glTFScene", sizeof(glTFScene)); return ty; }
    template <> TWO_GLTF_EXPORT Type& type<glTF>() { static Type ty("glTF", sizeof(glTF)); return ty; }
}
