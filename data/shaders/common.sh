#ifndef TOY_SHADER_COMMON
#define TOY_SHADER_COMMON

#include <bgfx_shader.sh>
#include "shaderlib.sh"

uniform vec4 u_render_params;
#define u_time u_render_params.x
#define u_origin_bottom_left u_render_params.y
#define u_point_size u_render_params.zw

uniform vec4 u_camera_params;
#define u_z_near u_camera_params.x
#define u_z_far u_camera_params.y
#define u_fov u_camera_params.z
#define u_aspect u_camera_params.w

uniform vec4 u_screen_size_pixel_size;
#define u_screen_size u_screen_size_pixel_size.xy
#define u_pixel_size u_screen_size_pixel_size.zw

uniform vec4 u_material_params_0;
uniform vec4 u_material_params_1;
#define u_uv1_scale u_material_params_0.xy
#define u_uv1_offset u_material_params_0.zw
#define u_uv2_scale u_material_params_1.xy
#define u_uv2_offset u_material_params_1.zw

#if BGFX_SHADER_LANGUAGE_GLSL == 110
mat4 transpose(in mat4 mat)
{
    vec4 i0 = mat[0];
    vec4 i1 = mat[1];
    vec4 i2 = mat[2];
    vec4 i3 = mat[3];

    mat4 result = mat4(
        vec4(i0.x, i1.x, i2.x, i3.x),
        vec4(i0.y, i1.y, i2.y, i3.y),
        vec4(i0.z, i1.z, i2.z, i3.z),
        vec4(i0.w, i1.w, i2.w, i3.w)
    );

    return result;
}
#endif

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

vec4 textureTriplanar(sampler2D tex, vec3 weights, vec3 world_pos)
{
	vec4 color = vec4_splat(0.0);
	color += texture2D(tex, world_pos.xy) * weights.z;
	color += texture2D(tex, world_pos.xz) * weights.y;
	color += texture2D(tex, world_pos.zy * vec2(-1.0,1.0)) * weights.x;
	return color;
}

vec4 sample_material_texture(sampler2D tex, vec2 uv)
{
    return texture2D(tex, uv);
}

float linear_depth(float depth)
{
    depth = 2.0 * depth - 1.0;
    return 2.0 * u_z_near * u_z_far / (u_z_far + u_z_near - depth * (u_z_far - u_z_near));
}

mat4 mat4_from_vec4(vec4 v0, vec4 v1, vec4 v2, vec4 v3)
{
    mat4 mat;
	mat[0] = v0;
	mat[1] = v1;
	mat[2] = v2;
	mat[3] = v3;
#if BGFX_SHADER_LANGUAGE_HLSL
    return transpose(mat);
#else
    return mat;
#endif
}

vec3 hsv_to_rgb(vec3 hsv)
{
    hsv.x = mod(100.0 + hsv.x, 1.0);       // Ensure [0,1[

    float slice = 6.0 * hsv.x;             // In [0,6[
    float islice = floor(slice);
    float interp_slice = slice - islice;   // In [0,1[ for each hue slice

    vec3 rgb_no_hue = vec3(hsv.z * (1.0 - hsv.y),
                           hsv.z * (1.0 - hsv.y * interp_slice),
                           hsv.z * (1.0 - hsv.y * (1.0 - interp_slice)) );

    float is_odd = mod(islice, 2.0);                 // 0 if even (slices 0, 2, 4), 1 if odd (slices 1, 3, 5)
    float slice_index = 0.5 * (islice - is_odd);     // (0, 1, 2) corresponding to slices (0, 2, 4) and (1, 3, 5)

    vec3 rgb_even_slices = vec3(hsv.z, rgb_no_hue.zx);               // (V, Temp Blue, Temp Red) for even slices (0, 2, 4)
    vec3 rgb_odd_slices = vec3(rgb_no_hue.y, hsv.z, rgb_no_hue.x);   // (Temp Green, V, Temp Red) for odd slices (1, 3, 5)
    vec3 rgb_slices = mix(rgb_even_slices, rgb_odd_slices, is_odd);

    float is_not_first_slice = saturate(slice_index);                   // 1 if NOT the first slice (true for slices 1 and 2)
    float is_not_second_slice = saturate(slice_index - 1.0);            // 1 if NOT the first or second slice (true only for slice 2)

    return mix(rgb_slices.xyz, mix(rgb_slices.zxy, rgb_slices.yzx, is_not_second_slice), is_not_first_slice);    // Make the RGB rotate right depending on final slice index
}

vec3 to_reindhart(vec3 color, float white)
{
    return color * (1.0 + (color / white)) / (1.0 + color);
}

vec3 to_filmic(vec3 color, float white)
{
    float A = 0.15;
    float B = 0.50;
    float C = 0.10;
    float D = 0.20;
    float E = 0.02;
    float F = 0.30;
    float W = 11.2;

    vec3 coltn = ((color*(A*color+C*B)+D*E)/(color*(A*color+B)+D*F))-E/F;
    float whitetn = ((white*(A*white+C*B)+D*E)/(white*(A*white+B)+D*F))-E/F;

    return coltn / whitetn;
}
#endif
