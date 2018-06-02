

#ifdef MUD_CPP_20
#include <cassert>
#include <cstdint>
#include <climits>
#include <cfloat>
import std.core;
import std.memory;
import std.threading;
import std.regex;
#endif

#include <gfx-gltf/Generated/Types.h>
#include <gfx-gltf/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFAlphaMode>() { static Type ty("glTFAlphaMode"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFComponentType>() { static Type ty("glTFComponentType"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFInterpolation>() { static Type ty("glTFInterpolation"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFPrimitiveType>() { static Type ty("glTFPrimitiveType"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<glTFType>() { static Type ty("glTFType"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAccessor>>() { static Type ty("std::vector<glTFAccessor>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimation>>() { static Type ty("std::vector<glTFAnimation>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimationChannel>>() { static Type ty("std::vector<glTFAnimationChannel>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFAnimationSampler>>() { static Type ty("std::vector<glTFAnimationSampler>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFBuffer>>() { static Type ty("std::vector<glTFBuffer>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFBufferView>>() { static Type ty("std::vector<glTFBufferView>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFCamera>>() { static Type ty("std::vector<glTFCamera>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFImage>>() { static Type ty("std::vector<glTFImage>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMaterial>>() { static Type ty("std::vector<glTFMaterial>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMesh>>() { static Type ty("std::vector<glTFMesh>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFMorphTarget>>() { static Type ty("std::vector<glTFMorphTarget>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFNode>>() { static Type ty("std::vector<glTFNode>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFPrimitive>>() { static Type ty("std::vector<glTFPrimitive>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFScene>>() { static Type ty("std::vector<glTFScene>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFSkin>>() { static Type ty("std::vector<glTFSkin>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<glTFTexture>>() { static Type ty("std::vector<glTFTexture>"); return ty; }
    template <> MUD_GFX_GLTF_EXPORT Type& type<std::vector<int>>() { static Type ty("std::vector<int>"); return ty; }
    
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
