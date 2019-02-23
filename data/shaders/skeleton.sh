#ifndef MUD_SHADER_SKELETON
#define MUD_SHADER_SKELETON

#include <common.sh>

#define SKELETON_TEXTURE_WIDTH 256
#define SKELETON_TEXTURE_HEIGHT 4

SAMPLER2D(s_skeleton, 15);

#ifdef NO_TEXEL_FETCH
#define texelFetch(_sampler, _coord, _level) texture2DLod(_sampler, vec2(_coord) / vec2(float(SKELETON_TEXTURE_WIDTH), float(SKELETON_TEXTURE_HEIGHT)), _level)
#endif

mat4 skeleton_matrix(sampler2D skeleton_texture, ivec4 bone_indices, vec4 bone_weights)
{
#ifdef NO_TEXEL_FETCH // the point here is to detect WebGL //#if BGFX_SHADER_LANGUAGE_GLSL < 110
    bone_indices *= 255.0;
#endif

    highp mat4 m;
    
    for(int i = 0; i < 4; ++i)
    {
        ivec2 tex_ofs = ivec2(int(mod(bone_indices[i], SKELETON_TEXTURE_WIDTH)), (int(bone_indices[i])/SKELETON_TEXTURE_WIDTH)*4);
        m += mat4(
            texelFetch(skeleton_texture, tex_ofs, 0),
            texelFetch(skeleton_texture, tex_ofs+ivec2(0,1), 0),
            texelFetch(skeleton_texture, tex_ofs+ivec2(0,2), 0),
            texelFetch(skeleton_texture, tex_ofs+ivec2(0,3), 0)
        ) * bone_weights[i];
    }

#if BGFX_SHADER_LANGUAGE_HLSL
    return m;
#else
    return transpose(m);
#endif
}

#ifdef NO_TEXEL_FETCH
#undef texelFetch
#endif

#endif
