#ifndef MUD_SHADER_CUBIC
#define MUD_SHADER_CUBIC

vec4 cubic(float v)
{
    vec4 n = vec4(1.0, 2.0, 3.0, 4.0) - v;
    vec4 s = n * n * n;
    float x = s.x;
    float y = s.y - 4.0 * s.x;
    float z = s.z - 4.0 * s.y + 6.0 * s.x;
    float w = 6.0 - x - y - z;
    return vec4(x, y, z, w) * (1.0/6.0);
}

vec4 texture2DBicubic(sampler2D tex, vec2 uv, vec2 tex_size, int level)
{
    float lod = float(level);
    
#if BGFX_SHADER_LANGUAGE_GLSL < 130
	vec2 level_size = tex_size * pow(2, -level);
#else
	vec2 level_size = vec2(ivec2(tex_size) >> level);
#endif
    vec2 inv_tex_size = 1.0 / level_size;
   
    uv = uv * level_size - 0.5;

    vec2 fxy = fract(uv);
    uv -= fxy;

    vec4 xcubic = cubic(fxy.x);
    vec4 ycubic = cubic(fxy.y);

    vec4 c = uv.xxyy + vec2(-0.5, +1.5).xyxy;
    
    vec4 s = vec4(xcubic.xz + xcubic.yw, ycubic.xz + ycubic.yw);
    vec4 offset = c + vec4(xcubic.yw, ycubic.yw) / s;
    
    offset *= inv_tex_size.xxyy;
    
    vec4 sample0 = texture2DLod(tex, offset.xz, lod);
    vec4 sample1 = texture2DLod(tex, offset.yz, lod);
    vec4 sample2 = texture2DLod(tex, offset.xw, lod);
    vec4 sample3 = texture2DLod(tex, offset.yw, lod);

    float sx = s.x / (s.x + s.y);
    float sy = s.z / (s.z + s.w);

    return mix(mix(sample3, sample2, sx), mix(sample1, sample0, sx), sy);
}

#endif
