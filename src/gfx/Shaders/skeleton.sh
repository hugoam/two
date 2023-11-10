#ifndef TWO_SHADER_SKELETON
#define TWO_SHADER_SKELETON

#include <common.sh>

#define SKELETON_TEXTURE_WIDTH 256
#define SKELETON_TEXTURE_HEIGHT 4

SAMPLER2D(s_skeleton, 15);

#ifdef NO_TEXEL_FETCH
#define texelFetch(_sampler, _coord, _level) texture2DLod(_sampler, vec2(_coord) / vec2(float(SKELETON_TEXTURE_WIDTH), float(SKELETON_TEXTURE_HEIGHT)), _level)
#endif

mat4 skeleton_matrix(sampler2D skeleton_texture, ivec4 bone_indices, vec4 bone_weights)
{
#ifdef NORMALIZED_BONES // the point here is to detect WebGL //#if BGFX_SHADER_LANGUAGE_GLSL < 110
    bone_indices *= 255.0;
#endif

#if BGFX_SHADER_LANGUAGE_GLSL || BGFX_SHADER_LANGUAGE_SPIRV
    highp mat4 m = mat4(0.f);
#else
    highp mat4 m;
#endif

    for(int i = 0; i < 4; ++i)
    {
        ivec2 tex_coord = ivec2(int(mod(bone_indices[i], SKELETON_TEXTURE_WIDTH)), (int(bone_indices[i])/SKELETON_TEXTURE_WIDTH)*4);
        m += mat4(
            texelFetch(skeleton_texture, tex_coord , 0),
            texelFetch(skeleton_texture, tex_coord + ivec2(0,1), 0),
            texelFetch(skeleton_texture, tex_coord + ivec2(0,2), 0),
            texelFetch(skeleton_texture, tex_coord + ivec2(0,3), 0)
        ) * bone_weights[i];
    }

#if BGFX_SHADER_LANGUAGE_GLSL
    return transpose(m);
#else
    return m;
#endif
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif
