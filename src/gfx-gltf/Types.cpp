

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-gltf;
#else
#include <gfx-gltf/Types.h>
#include <gfx-gltf/Api.h>
#include <type/Vector.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAlphaMode>() { static Type ty("glTFAlphaMode"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFComponentType>() { static Type ty("glTFComponentType"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFInterpolation>() { static Type ty("glTFInterpolation"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPrimitiveType>() { static Type ty("glTFPrimitiveType"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFType>() { static Type ty("glTFType"); return ty; }
    
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTF>() { static Type ty("glTF"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAccessor>() { static Type ty("glTFAccessor"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimation>() { static Type ty("glTFAnimation"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationChannel>() { static Type ty("glTFAnimationChannel"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationSampler>() { static Type ty("glTFAnimationSampler"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAnimationTarget>() { static Type ty("glTFAnimationTarget"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAttributes>() { static Type ty("glTFAttributes"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFBuffer>() { static Type ty("glTFBuffer"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFBufferView>() { static Type ty("glTFBufferView"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFCamera>() { static Type ty("glTFCamera"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFImage>() { static Type ty("glTFImage"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMaterial>() { static Type ty("glTFMaterial"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMaterialPBR>() { static Type ty("glTFMaterialPBR"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMesh>() { static Type ty("glTFMesh"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFMorphTarget>() { static Type ty("glTFMorphTarget"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFNode>() { static Type ty("glTFNode"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFOrthographic>() { static Type ty("glTFOrthographic"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPerspective>() { static Type ty("glTFPerspective"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPrimitive>() { static Type ty("glTFPrimitive"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSampler>() { static Type ty("glTFSampler"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFScene>() { static Type ty("glTFScene"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSkin>() { static Type ty("glTFSkin"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparse>() { static Type ty("glTFSparse"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparseIndices>() { static Type ty("glTFSparseIndices"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFSparseValues>() { static Type ty("glTFSparseValues"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFTexture>() { static Type ty("glTFTexture"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFTextureInfo>() { static Type ty("glTFTextureInfo"); return ty; }
}
