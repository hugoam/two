#ifndef MUD_SHADER_COMMON
#define MUD_SHADER_COMMON

#include <bgfx_shader.sh>
#include <srgb.sh>

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

float random(vec2 _uv)
{
	return fract(sin(dot(_uv.xy, vec2(12.9898, 78.233) ) ) * 43758.5453);
}

#endif
